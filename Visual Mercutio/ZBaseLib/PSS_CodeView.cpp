/****************************************************************************
 * ==> PSS_CodeView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a code view                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_CodeView.h"

 // processsoft
#include "PSS_PlanFinObjects.h"
#include "PSS_PLFNAutoNumbered.h"
#include "PSS_PLFNBitmap.h"
#include "PSS_Document.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_CodeView, PSS_View)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_CodeView, PSS_View)
    //{{AFX_MSG_MAP(PSS_CodeView)
    ON_WM_RBUTTONDOWN()
    ON_COMMAND(ID_ONLY_NUMERICFIELDS, OnOnlyNumericFields)
    ON_UPDATE_COMMAND_UI(ID_ONLY_NUMERICFIELDS, OnUpdateOnlyNumericFields)
    ON_MESSAGE(ID_DISPLAY_FIELD_TYPE, OnDisplayFieldType)
    ON_MESSAGE(ID_SYNCHRONIZE_VSCROLL, OnSynchronizeVScroll)
    ON_MESSAGE(ID_SYNCHRONIZE_HSCROLL, OnSynchronizeHScroll)
    ON_COMMAND(ID_DISPLAYCALCULATEDCODE, OnDisplayCalculatedCode)
    ON_UPDATE_COMMAND_UI(ID_DISPLAYCALCULATEDCODE, OnUpdateDisplayCalculatedCode)
    ON_COMMAND(ID_DISPLAYALLCODE, OnDisplayallCode)
    ON_UPDATE_COMMAND_UI(ID_DISPLAYALLCODE, OnUpdateDisplayallCode)
    ON_COMMAND(ID_DISPLAYSTATICCODE, OnDisplayStaticCode)
    ON_UPDATE_COMMAND_UI(ID_DISPLAYSTATICCODE, OnUpdateDisplayStaticCode)
    ON_COMMAND(ID_DISPLAYTEXTCODE, OnDisplayTextCode)
    ON_UPDATE_COMMAND_UI(ID_DISPLAYTEXTCODE, OnUpdateDisplayTextCode)
    ON_COMMAND(ID_DISPLAYGRAPHICCODE, OnDisplayGraphicCode)
    ON_UPDATE_COMMAND_UI(ID_DISPLAYGRAPHICCODE, OnUpdateDisplayGraphicCode)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_FILEPRINT_PAGE_FIELDNAME, CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILEPRINTPREVIEW_PAGE_FIELDNAME, CScrollView::OnFilePrintPreview)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_CodeView
//---------------------------------------------------------------------------
PSS_CodeView::PSS_CodeView() :
    PSS_View(),
    m_CodeType(E_CT_AllObjects),
    m_SavePageForPrinting(0)
{
    m_ViewType = PSS_View::IE_VT_FormFieldCode;
}
//---------------------------------------------------------------------------
PSS_CodeView::PSS_CodeView(const PSS_CodeView& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_CodeView::~PSS_CodeView()
{}
//---------------------------------------------------------------------------
const PSS_CodeView& PSS_CodeView::operator = (const PSS_CodeView& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnInitialUpdate()
{
    PSS_View::OnInitialUpdate();
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnDraw(CDC* pDC)
{
    PSS_Document* pDoc = GetDocument();
    ASSERT(pDoc);

    // translate to absolute coordinates
    OnPrepareDC(pDC);

    // get the current page
    const int page = pDoc->GetCurrentPage();

    DrawPageRect(pDC);

    PSS_PlanFinObject* pObj;

    // optimisation first step, call the function list directly
    POSITION pPosition = (pDoc->GetObjectList()).GetHeadPosition();

    while (pPosition)
    {
        pObj = (PSS_PlanFinObject *)(pDoc->GetObjectList()).GetNext(pPosition);

        // it's not necessary to continue if the next object page is greater than the actual one
        if (pObj->GetObjectPage() > page)
            break;

        if (page != pObj->GetObjectPage())
            continue;

        switch (GetDisplayCode())
        {
            case E_CT_AllObjects:
                // show object on the right page, if visible in the viewport
                pObj->ShowObjectName(pDC);
                break;

            case E_CT_Long:
                if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNLong)))
                    pObj->ShowObjectName(pDC);

                break;

            case E_CT_Calculated:
            {
                PSS_PLFNLong* pLongObj = dynamic_cast<PSS_PLFNLong*>(pObj);

                if (pLongObj && pLongObj->IsCalculatedField())
                    pObj->ShowObjectName(pDC);

                break;
            }

            case E_CT_Static:
            {
                PSS_PLFNText* pTextObj = dynamic_cast<PSS_PLFNText*>(pObj);

                if (pTextObj && pTextObj->GetIsStatic())
                    pObj->ShowObjectName(pDC);

                break;
            }

            case E_CT_Text:
            {
                PSS_PLFNText* pTextObj = dynamic_cast<PSS_PLFNText*>(pObj);

                if ((pTextObj && !pTextObj->GetIsStatic()) || pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNAutoNumbered)))
                    pObj->ShowObjectName(pDC);

                break;
            }

            case E_CT_Graphic:
                if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNGraphic)) && pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNBitmap)))
                    pObj->ShowObjectName(pDC);

                break;
        }
    }
}
//---------------------------------------------------------------------------
BOOL PSS_CodeView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // don't check for evaluation version
    pInfo->SetMaxPage(GetDocument()->GetPageCount());
    return(DoPreparePrinting(pInfo));
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    // save the current page before printing
    m_SavePageForPrinting = GetDocument()->GetCurrentPage();
    SetLogicalCoordinates(pDC);
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    // don't check for evaluation version, put back the current page
    GetDocument()->SetCurrentPage(m_SavePageForPrinting);
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
    // assign the current page
    GetDocument()->SetCurrentPage(pInfo->m_nCurPage);

    // print the page
    OnDraw(pDC);
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnRButtonDown(UINT nFlags, CPoint point)
{
    CPoint pt(point);
    ReleaseCapture();

    // show the context menu
    CMenu dummyMenu;
    dummyMenu.LoadMenu(IDR_CONTEXT_VIEWCODE);

    CMenu* pMenu = dummyMenu.GetSubMenu(0);
    ASSERT(pMenu);

    ClientToScreen(&pt);
    pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, AfxGetMainWnd());

    CScrollView::OnRButtonDown(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnOnlyNumericFields()
{
    m_CodeType = (m_CodeType == E_CT_Long ? E_CT_AllObjects : E_CT_Long);
    RedrawWindow();
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnUpdateOnlyNumericFields(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CodeType == E_CT_Long);
}
//---------------------------------------------------------------------------
afx_msg LONG PSS_CodeView::OnDisplayFieldType(UINT message, LONG lParam)
{
    m_CodeType = EClassType(lParam);
    RedrawWindow();
    return(1);
}
//---------------------------------------------------------------------------
afx_msg LONG PSS_CodeView::OnSynchronizeVScroll(UINT message, LONG lParam)
{
    ScrollToPosition(*(POINT*)lParam);
    return(1);
}
//---------------------------------------------------------------------------
afx_msg LONG PSS_CodeView::OnSynchronizeHScroll(UINT message, LONG lParam)
{
    ScrollToPosition(*(POINT*)lParam);
    return(1);
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnDisplayCalculatedCode()
{
    m_CodeType = (m_CodeType == E_CT_Calculated ? E_CT_AllObjects : E_CT_Calculated);
    RedrawWindow();
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnUpdateDisplayCalculatedCode(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CodeType == E_CT_Calculated);
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnDisplayallCode()
{
    m_CodeType = E_CT_AllObjects;
    RedrawWindow();
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnUpdateDisplayallCode(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CodeType == E_CT_AllObjects);
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnDisplayStaticCode()
{
    m_CodeType = (m_CodeType == E_CT_Static ? E_CT_AllObjects : E_CT_Static);
    RedrawWindow();
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnUpdateDisplayStaticCode(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CodeType == E_CT_Static);
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnDisplayTextCode()
{
    m_CodeType = (m_CodeType == E_CT_Text ? E_CT_AllObjects : E_CT_Text);
    RedrawWindow();
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnUpdateDisplayTextCode(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CodeType == E_CT_Text);
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnDisplayGraphicCode()
{
    m_CodeType = (m_CodeType == E_CT_Graphic ? E_CT_AllObjects : E_CT_Graphic);
    RedrawWindow();
}
//---------------------------------------------------------------------------
void PSS_CodeView::OnUpdateDisplayGraphicCode(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_CodeType == E_CT_Graphic);
}
//---------------------------------------------------------------------------
