/****************************************************************************
 * ==> PSS_VisualTool ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a visual tools base class. These tools can be     *
 *               selected, edited, add a new rectangle, line, text, etc...  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_VisualTool.h"

// processsoft
#include "ZDDoc.h"
#include "PSS_Global.h"

//---------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------
PSS_VisualTool::IEToolType        PSS_VisualTool::m_CurrentToolType = PSS_VisualTool::IE_TT_VToolEdit;
PSS_VisualTool::IEVisualToolModes PSS_VisualTool::m_ToolMode        = PSS_VisualTool::IE_TM_Normal;
CPtrList                          PSS_VisualTool::m_ToolsList;
CRect                             PSS_VisualTool::m_Rect;
CPoint                            PSS_VisualTool::m_DownPoint;
CPoint                            PSS_VisualTool::m_LastPoint;
UINT                              PSS_VisualTool::m_DownFlags;
//---------------------------------------------------------------------------
// PSS_VisualTool
//---------------------------------------------------------------------------
PSS_VisualTool::PSS_VisualTool(IEToolType objectToolType) :
    m_ObjectToolType(objectToolType)
{
    m_hCurNormal = AfxGetApp()->LoadStandardCursor(IDC_ARROW);

    m_ToolsList.AddTail(this);
}
//---------------------------------------------------------------------------
PSS_VisualTool::PSS_VisualTool(const PSS_VisualTool& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_VisualTool::~PSS_VisualTool()
{}
//---------------------------------------------------------------------------
const PSS_VisualTool& PSS_VisualTool::operator = (const PSS_VisualTool& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_VisualTool::OnLButtonDown(ZIView* pView, UINT flags, const CPoint& point)
{
    // deactivate any in-place active item on this view
    m_DownFlags = flags;
    m_DownPoint = point;
    m_LastPoint = point;
}
//---------------------------------------------------------------------------
void PSS_VisualTool::OnLButtonDblClk(ZIView* pView, UINT flags, const CPoint& point)
{}
//---------------------------------------------------------------------------
void PSS_VisualTool::OnLButtonUp(ZIView* pView, UINT flags, const CPoint& point)
{
    ReleaseCapture();
}
//---------------------------------------------------------------------------
void PSS_VisualTool::OnMouseMove(ZIView* pView, UINT flags, const CPoint& point)
{
    m_LastPoint = point;
}
//---------------------------------------------------------------------------
void PSS_VisualTool::OnCancel()
{
    m_CurrentToolType = IE_TT_VToolEdit;
}
//---------------------------------------------------------------------------
PSS_VisualTool* PSS_VisualTool::FindTool(IEToolType objectToolType)
{
    POSITION pPos = m_ToolsList.GetHeadPosition();

    while (pPos)
    {
        PSS_VisualTool* pTool = (PSS_VisualTool*)m_ToolsList.GetNext(pPos);

        if (pTool->m_ObjectToolType == objectToolType)
            return pTool;
    }

    return NULL;
}
//---------------------------------------------------------------------------
// PSS_VisualToolEdit
//---------------------------------------------------------------------------
PSS_VisualToolEdit::PSS_VisualToolEdit() :
    PSS_VisualTool(IE_TT_VToolEdit)
{
    HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(IDC_EDITABLE), RT_GROUP_CURSOR);
    m_hCurEdit      = ::LoadCursor(hInst, MAKEINTRESOURCE(IDC_EDITABLE));
}
//---------------------------------------------------------------------------
PSS_VisualToolEdit::PSS_VisualToolEdit(const PSS_VisualToolEdit& other) :
    PSS_VisualTool(IE_TT_VToolEdit)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_VisualToolEdit::~PSS_VisualToolEdit()
{}
//---------------------------------------------------------------------------
const PSS_VisualToolEdit& PSS_VisualToolEdit::operator = (const PSS_VisualToolEdit& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_VisualToolEdit::OnLButtonDown(ZIView* pView, UINT flags, const CPoint& point)
{
    // check read-only mode
    if (!pView->GetDocument() || pView->GetDocument()->IsReadOnlyAtRuntime())
        return;

    CPoint local = point;
    pView->ClientToDoc(local);

    ZDDocument* pDoc = pView->GetDocument();
    ASSERT(pDoc);

    PlanFinObject* pObj;

    // get the current page
    const int page = pDoc->GetCurrentPage();

    // search wich element is selected
    if ((pObj = pDoc->GetHead()) == NULL)
        return;

    // iterate thought the object list and detect if the cursor in above one object
    do
    {
        // is on the right page and on the object?
        if (page == pObj->GetObjectPage() && pObj->IsSelected(local))
        {
            switch (pView->GetViewType())
            {
                case FormModifyView:
                    // is the cursor on the object?
                    if (!pObj->IsReadOnlyAtRuntime())
                        if (!pObj->IsSelectObject() && !pObj->GetIsStatic())
                        {
                            // save the pointer to the object only to be able to remove the flag later
                            pDoc->SetEditedObject(pObj);
                            pView->EditObject(pObj);
                        }

                    break;

                case FormDesignView:
                    // is the cursor on the object?
                    if (!pObj->IsSelectObject())
                    {
                        // save the pointer to the object only to be able to remove the flag later
                        pDoc->SetEditedObject(pObj);
                        pView->EditObject(pObj);
                    }

                    break;

                default: break;
            }

            break;
        }
    }
    while ((pObj = pDoc->GetNext()) != NULL);

    // set the focus to this view, required for the edit control. With it, all edit control will loose the focus
    // and save the buffer. Otherwise the caret will continue to run in the edit control
    if (!pObj)
        pView->SetFocus();
}
//---------------------------------------------------------------------------
void PSS_VisualToolEdit::OnLButtonUp(ZIView* pView, UINT flags, const CPoint& point)
{
    PSS_VisualTool::OnLButtonUp(pView, flags, point);
}
//---------------------------------------------------------------------------
void PSS_VisualToolEdit::OnMouseMove(ZIView* pView, UINT flags, const CPoint& point)
{
    CWnd* pActiveWnd = pView->GetActiveWindow();

    // also check for NULL for Win32
    if (!pActiveWnd || !pActiveWnd->IsChild(pView))
        return;

    CPoint local = point;
    pView->ClientToDoc(local);

    // check read-only mode
    if (!pView->GetDocument() || pView->GetDocument()->IsReadOnlyAtRuntime())
    {
        PSS_VisualTool::OnMouseMove(pView, flags, local);

        if (::IsWindow(pView->GetToolTip().m_hWnd))
            // use Activate() to hide the tooltip
            pView->GetToolTip().Activate(FALSE);

        return;
    }

    // reader view cannot change anything
    if (pView->GetViewType() != FormReadView)
    {
        BOOL releaseCapture = FALSE;

        if (PSS_Global::ShowAnimation())
        {
            ZDDocument* pDoc = pView->GetDocument();
            ASSERT(pDoc);

            PlanFinObject* pObj;

            // get the current page
            const int page = pDoc->GetCurrentPage();

            // search wich element is selected
            if ((pObj = pDoc->GetHead()) != NULL)
                do
                {
                    // is on the right page and object?
                    if (page == pObj->GetObjectPage() && pObj->IsSelected(local))
                    {
                        switch (pView->GetViewType())
                        {
                            case FormModifyView:
                                // If the cursor is on the object
                                if (!pObj->IsReadOnlyAtRuntime())
                                {
                                    if (!pObj->IsSelectObject() && !pObj->GetIsStatic())
                                    {
                                        pView->SetCapture();

                                        if (GetCursor() != m_hCurEdit)
                                            SetCursor(m_hCurEdit);

                                        if (::IsWindow(pView->GetToolTip().m_hWnd))
                                            // use Activate() to hide the tooltip
                                            pView->GetToolTip().Activate(TRUE);

                                        return;
                                    }
                                }

                                break;

                            case FormDesignView:
                                // If the cursor is on the object
                                if (!pObj->IsSelectObject())
                                {
                                    pView->SetCapture();

                                    if (GetCursor() != m_hCurEdit)
                                        SetCursor(m_hCurEdit);
                                }

                                if (::IsWindow(pView->GetToolTip().m_hWnd))
                                    // use Activate() to hide the tooltip
                                    pView->GetToolTip().Activate(TRUE);

                                return;

                            default: break;
                        }

                        // do or not the right processing
                        break;
                    }
                }
                while ((pObj = pDoc->GetNext()) != NULL);
        }

        PSS_VisualTool::OnMouseMove(pView, flags, local);
    }

    if (::IsWindow(pView->GetToolTip().m_hWnd))
        // use Activate() to hide the tooltip
        pView->GetToolTip().Activate(FALSE);

    ReleaseCapture();
}
//---------------------------------------------------------------------------
// PSS_VisualToolObjectCreator
//---------------------------------------------------------------------------
PSS_VisualToolObjectCreator::PSS_VisualToolObjectCreator(IEToolType objectToolType) :
    PSS_VisualTool(objectToolType),
    m_CreationStarted(FALSE)
{
    m_hCurCreation = AfxGetApp()->LoadCursor(IDC_NEWOBJECT);
}
//---------------------------------------------------------------------------
PSS_VisualToolObjectCreator::PSS_VisualToolObjectCreator(const PSS_VisualToolObjectCreator& other) :
    PSS_VisualTool(IE_TT_VToolEdit)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_VisualToolObjectCreator::~PSS_VisualToolObjectCreator()
{}
//---------------------------------------------------------------------------
const PSS_VisualToolObjectCreator& PSS_VisualToolObjectCreator::operator = (const PSS_VisualToolObjectCreator& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_VisualToolObjectCreator::OnLButtonDown(ZIView* pView, UINT flags, const CPoint& point)
{
    // check read-only mode
    if (!pView->GetDocument() || pView->GetDocument()->IsReadOnlyAtRuntime())
        return;

    CPoint local = point;
    pView->ClientToDoc(local);

    PSS_VisualTool::OnLButtonDown(pView, flags, local);

    m_CreationStarted = TRUE;
    pView->SetCapture();
}
//---------------------------------------------------------------------------
void PSS_VisualToolObjectCreator::OnLButtonUp(ZIView* pView, UINT flags, const CPoint& point)
{
    CPoint local = point;
    pView->ClientToDoc(local);

    PSS_VisualTool::OnLButtonUp(pView, flags, local);

    // if multiple selection, clear the rectangle
    if (m_CreationStarted)
    {
        CClientDC tempDC(pView);
        pView->OnPrepareDC(&tempDC);

        CRect rect(m_DownPoint.x, m_DownPoint.y, m_LastPoint.x, m_LastPoint.y);
        tempDC.SetROP2(R2_NOTXORPEN);

        CPen  pen(PS_DOT, 1, defCOLOR_RED);
        CPen* pOldPen = tempDC.SelectObject(&pen);

        tempDC.Rectangle(rect);
        tempDC.SelectObject(pOldPen);

        m_LastPoint       = local;
        m_CreationStarted = FALSE;

        // check if the rect is large enough to create an object
        if (rect.Width() > 2 && rect.Height() > 1)
        {
            rect.NormalizeRect();

            // assign the rectangle
            m_Rect = rect;
            CreateObject(rect);
        }

        ZDDocument* pDoc = pView->GetDocument();
        ASSERT(pDoc);

        // the position have changed
        pDoc->SetModifiedFlag(TRUE);
    }

    ReleaseCapture();
}
//---------------------------------------------------------------------------
void PSS_VisualToolObjectCreator::OnMouseMove(ZIView* pView, UINT flags, const CPoint& point)
{
    CPoint local = point;
    pView->ClientToDoc(local);

    CWnd* pActiveWnd = pView->GetActiveWindow();

    // also check for NULL for Win32
    if (pActiveWnd && pActiveWnd->IsChild(pView))
    {
        if (GetCursor() != m_hCurCreation)
            SetCursor(m_hCurCreation);

        // if is in creation, draw a rectangle from the initial point to the current point
        if (m_CreationStarted)
        {
            CClientDC tempDC(pView);
            pView->OnPrepareDC(&tempDC);

            CRect rect(m_DownPoint.x, m_DownPoint.y, m_LastPoint.x, m_LastPoint.y);
            tempDC.SetROP2(R2_NOTXORPEN);

            CPen  pen(PS_DOT, 1, defCOLOR_RED);
            CPen* pOldPen = tempDC.SelectObject(&pen);
            tempDC.Rectangle(rect);

            PSS_VisualTool::OnMouseMove(pView, flags, local);

            rect = CRect(m_DownPoint.x, m_DownPoint.y, m_LastPoint.x, m_LastPoint.y);
            tempDC.Rectangle(rect);
            tempDC.SelectObject(pOldPen);
        }
    }
}
//---------------------------------------------------------------------------
