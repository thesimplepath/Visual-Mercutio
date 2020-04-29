/****************************************************************************
 * ==> PSS_View ------------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic view                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_View.h"

// processsoft
#include "PSS_VisualTool.h"
#include "PSS_PLFNCheckBtn.h"
#include "PSS_PLFNRadioBtn.h"
#include "PSS_Document.h"
#include "PSS_MsgBox.h"
#include "PSS_PaintResources.h"
#include "PSS_PaintOperations.h"
#include "PSS_FieldObserverMsg.h"
#include "PSS_Subject.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_View, PSS_DropScrollView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_View, PSS_DropScrollView)
    //{{AFX_MSG_MAP(PSS_View)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_KILLFOCUS()
    ON_WM_SETCURSOR()
    ON_WM_VSCROLL()
    ON_WM_HSCROLL()
    ON_COMMAND(ID_FILE_PRINT, PSS_DropScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, PSS_DropScrollView::OnFilePrintPreview)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_View::m_pOldPointerSelectedObj = NULL;
//---------------------------------------------------------------------------
// PSS_View
//---------------------------------------------------------------------------
PSS_View::PSS_View() :
    PSS_DropScrollView(),
    m_ViewType(IE_VT_Unknown),
    m_LineSize(10, 10),
    m_hSelectorCursor(NULL),
    m_SelectObjectMode(FALSE),
    m_pSelectedObject(NULL),
    m_LogUnitX(0),
    m_LogUnitY(0),
    m_Zoom(100)
{}
//---------------------------------------------------------------------------
PSS_View::PSS_View(const PSS_View& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_View::~PSS_View()
{
    m_ToolTip.DestroyWindow();
}
//---------------------------------------------------------------------------
const PSS_View& PSS_View::operator = (const PSS_View& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_View::Initialize()
{
    // get the screen logical size
    CDC* pDC = GetDC();
    PSS_Assert(pDC);

    try
    {
        PSS_PaintOperations::SetLogicalBasicUnits(CSize(pDC->GetDeviceCaps(LOGPIXELSX),
                                                        pDC->GetDeviceCaps(LOGPIXELSY)));

        m_LogUnitX = PSS_PaintOperations::GetLogicalBasicUnits().cx;
        m_LogUnitY = PSS_PaintOperations::GetLogicalBasicUnits().cy;
    }
    catch (...)
    {
        ReleaseDC(pDC);
        throw;
    }

    VERIFY(ReleaseDC(pDC));

    m_hSelectorCursor = ::LoadCursor(::AfxFindResourceHandle(MAKEINTRESOURCE(IDC_SELECTOROBJECT), RT_GROUP_CURSOR),
                                     MAKEINTRESOURCE(IDC_SELECTOROBJECT));

    m_PageRect = CRect(CPoint(0, 0), GetReportPageSizeInPixels());

    CalculateDocumentSize();
    SetScrollSizes();

    if (m_ToolTip.Create(this, TTS_ALWAYSTIP) && m_ToolTip.AddTool(this))
    {
        m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0,            SHRT_MAX);
        m_ToolTip.SendMessage(TTM_SETDELAYTIME,   TTDT_AUTOPOP, SHRT_MAX);
        m_ToolTip.SendMessage(TTM_SETDELAYTIME,   TTDT_INITIAL, 200);
        m_ToolTip.SendMessage(TTM_SETDELAYTIME,   TTDT_RESHOW,  200);

        // set the text and background colors
        m_ToolTip.SendMessage(TTM_SETTIPTEXTCOLOR, defCOLOR_WHITE, 0L);
        m_ToolTip.SendMessage(TTM_SETTIPBKCOLOR, defCOLOR_BLUE, 0L);
    }
    else
    {
        TRACE("Error in creating ToolTip");
    }
}
//---------------------------------------------------------------------------
void PSS_View::CalculateDocumentSize()
{
    // calculate the document size
    CRect rect;
    CRect wndRect;

    // calculate the page size, regarding the view size
    GetClientRect(&wndRect);
    m_PageSize.cx = wndRect.right  / 2;
    m_PageSize.cy = wndRect.bottom / 2;

    // add one page to the document
    m_TotalSize  = GetReportPageSizeInPixels();
    m_TotalSize += m_PageSize;
}
//---------------------------------------------------------------------------
void PSS_View::SetLogicalCoordinates(CDC* pDC)
{
    pDC->SetMapMode(MM_ANISOTROPIC);

    // apply the ratio
    if (!pDC->IsPrinting())
        pDC->SetWindowExt(int(double(m_LogUnitX) / (double(m_Zoom) / 100.0)),
                          int(double(m_LogUnitY) / (double(m_Zoom) / 100.0)));
    else
        pDC->SetWindowExt(m_LogUnitX, m_LogUnitY);

    pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX), pDC->GetDeviceCaps(LOGPIXELSY));
}
//---------------------------------------------------------------------------
void PSS_View::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    PSS_DropScrollView::OnPrepareDC(pDC, pInfo);
    SetLogicalCoordinates(pDC);
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_View::ActiveSelectedObject(CPoint& point, BOOL autoReset)
{
    PSS_Document* pDoc = GetDocument();
    PSS_Assert(pDoc);

    PSS_PlanFinObject* pObj;
    PSS_PlanFinObject* pReturnedObject = NULL;

    // get the current page
    const int page = pDoc->GetCurrentPage();

    // translate the point in logical coordinates
    CDC* pDC = GetDC();
    PSS_Assert(pDC);

    CPoint pt(point);
    OnPrepareDC(pDC);

    // search which element is selected
    if ((pObj = pDoc->GetHead()) == NULL)
    {
        VERIFY(ReleaseDC(pDC));
        return FALSE;
    }

    do
    {
        // check if one object is already selected, deselect it before
        if (!autoReset)
            pObj->SelectObject(this, pDC, FALSE);

        // show object on the right page
        if (page == pObj->GetObjectPage())
            if (pObj->IsHint(point))
            {
                // notify observer about object selection
                if (pObj->IsObjectSelected())
                    pObj->SelectObject(this, pDC, FALSE);
                else
                {
                    pObj->SelectObject(this, pDC, TRUE);

                    PSS_Subject* pSubject = dynamic_cast<PSS_Subject*>(::AfxGetMainWnd());

                    if (pSubject)
                    {
                        PSS_FieldObserverMsg msg(UM_NOTIFY_OBJECTSELECTED, pObj);
                        pSubject->NotifyAllObservers(&msg);
                    }
                }

                // assign the current object to proceed
                pReturnedObject = pObj;

                // it's not necessary to continue if the current selected object should be auto-reseted
                if (autoReset)
                    break;
            }
    }
    while ((pObj = pDoc->GetNext()) != NULL);

    VERIFY(ReleaseDC(pDC));

    return pReturnedObject;
}
//---------------------------------------------------------------------------
void PSS_View::SelectObjectInRect(const CRect& rect, CWnd* pWnd, CDC* pDC)
{
    PSS_Document* pDoc = GetDocument();
    PSS_Assert(pDoc);

    PSS_PlanFinObject* pObj;

    // get the current page
    const int page = pDoc->GetCurrentPage();

    // Search wich element has been modified
    if ((pObj = pDoc->GetHead()) == NULL)
        return;

    do
    {
        // it's not necessary to continue if the next object page is greater than the actual one
        if (pObj->GetObjectPage() > page)
            break;

        // show object on the right page
        if (page == pObj->GetObjectPage())
            // if the object rect is contained in the rect, select it
            if (rect.PtInRect(pObj->GetClientRect().TopLeft()) ||
                rect.PtInRect(pObj->GetClientRect().BottomRight()))
                pObj->SelectObject(pWnd, pDC, TRUE, FALSE);
            else
                // otherwise remove the selection
                pObj->SelectObject(pWnd, pDC, FALSE);
    }
    while ((pObj = pDoc->GetNext()) != NULL);
}
//---------------------------------------------------------------------------
BOOL PSS_View::GetRectOfSelectedObject(CRect& rect)
{
    PSS_Document* pDoc = GetDocument();
    PSS_Assert(pDoc);

    PSS_PlanFinObject* pObj;
    BOOL               result = FALSE;

    // get the current page
    const int page = pDoc->GetCurrentPage();
    rect.SetRect(0, 0, 0, 0);

    // search which element has been modified
    if ((pObj = pDoc->GetHead()) == NULL)
        return FALSE;

    do
    {
        if (pObj->GetObjectPage() == page)
            if (pObj->IsObjectSelected())
            {
                rect.UnionRect(&rect, pObj->GetClientRect());
                result = TRUE;
            }
    }
    while ((pObj = pDoc->GetNext()) != NULL);

    return result;
}
//---------------------------------------------------------------------------
void PSS_View::DeselectAllObject(CWnd* pWnd, CDC* pDC, PSS_Document* pDoc)
{
    PSS_PlanFinObject* pObj;

    // get the current page
    const int page = pDoc->GetCurrentPage();

    // search which element is selected and deselect it
    if ((pObj = pDoc->GetHead()) == NULL)
        return;

    do
    {
        if (pObj->GetObjectPage() == page)
            if (pObj->IsObjectSelected())
                pObj->SelectObject(pWnd, pDC, FALSE);
    }
    while ((pObj = pDoc->GetNext()) != NULL);
}
//---------------------------------------------------------------------------
void PSS_View::ClientToDoc(CPoint& point)
{
    CClientDC dc(this);
    OnPrepareDC(&dc, NULL);
    dc.DPtoLP(&point);
}
//---------------------------------------------------------------------------
void PSS_View::ClientToDoc(CRect& rect)
{
    CClientDC dc(this);
    OnPrepareDC(&dc, NULL);
    dc.DPtoLP(rect);
}
//---------------------------------------------------------------------------
void PSS_View::DocToClient(CPoint& point)
{
    CClientDC dc(this);
    OnPrepareDC(&dc, NULL);
    dc.LPtoDP(&point);
}
//---------------------------------------------------------------------------
void PSS_View::DocToClient(CRect& rect)
{
    CClientDC dc(this);
    OnPrepareDC(&dc, NULL);
    dc.LPtoDP(rect);

    rect.NormalizeRect();
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_View::FindHitObject(CPoint& point)
{
    PSS_Document* pDoc = GetDocument();
    PSS_Assert(pDoc);

    PSS_PlanFinObject* pObj;

    // get the current page
    const int page = pDoc->GetCurrentPage();

    // search which element is selected
    if ((pObj = pDoc->GetHead()) == NULL)
        return NULL;

    do
    {
        if (page == pObj->GetObjectPage())
            if (pObj->IsHint(point))
                return pObj;
    }
    while ((pObj = pDoc->GetNext()) != NULL);

    return NULL;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_View::SelectAndGet()
{
    m_SelectObjectMode = TRUE;
    m_pSelectedObject  = NULL;

    SetCapture();
    SetCursor(m_hSelectorCursor);

    MSG msg;

    while (GetMessage(&msg, HWND(NULL), 0, 0) && m_SelectObjectMode)
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
        SetCapture();

        if (GetCursor() != m_hSelectorCursor)
            SetCursor(m_hSelectorCursor);
    }

    if (m_pSelectedObject)
    {
        CDC* pDC = GetDC();
        PSS_Assert(pDC);
        OnPrepareDC(pDC);

        m_pSelectedObject->SelectObject(this, pDC, TRUE);
        VERIFY(ReleaseDC(pDC));
    }

    return m_pSelectedObject;
}
//---------------------------------------------------------------------------
CObArray& PSS_View::GetArrayOfSelectedObject()
{
    PSS_Document* pDoc = GetDocument();
    PSS_Assert(pDoc);

    // remove all elements
    m_ArrayOfSelectedObject.RemoveAll();

    PSS_PlanFinObject* pObj;

    // search which element is selected
    if ((pObj = pDoc->GetHead()) != NULL)
        do
        {
            if (pObj->IsObjectSelected())
                m_ArrayOfSelectedObject.Add(pObj);
        }
        while ((pObj = pDoc->GetNext()) != NULL);

    return m_ArrayOfSelectedObject;
}
//---------------------------------------------------------------------------
void PSS_View::KeepObjectInPage(PSS_PlanFinObject* pObj, const CSize& reportSize)
{
    // check if the object is still in the page, save the object width and height
    const int width  = pObj->GetClientRect().Width();
    const int height = pObj->GetClientRect().Height();

    // if too left
    if (pObj->GetClientRect().left < 0)
    {
        pObj->GetClientRect().left  = 0;
        pObj->GetClientRect().right = pObj->GetClientRect().left + width;
    }

    // if too right
    if (pObj->GetClientRect().right > reportSize.cx)
    {
        pObj->GetClientRect().right = reportSize.cx;
        pObj->GetClientRect().left  = pObj->GetClientRect().right - width;
    }

    // if too top
    if (pObj->GetClientRect().top < 0)
    {
        pObj->GetClientRect().top    = 0;
        pObj->GetClientRect().bottom = pObj->GetClientRect().top + height;
    }

    // if too bottom
    if (pObj->GetClientRect().bottom > reportSize.cy)
    {
        pObj->GetClientRect().bottom = reportSize.cy;
        pObj->GetClientRect().top    = pObj->GetClientRect().bottom - height;
    }
}
//---------------------------------------------------------------------------
void PSS_View::SetZoomPercentage(int value)
{
    m_Zoom = value;
    SetScrollSizes();
}
//---------------------------------------------------------------------------
void PSS_View::EditObject(PSS_PlanFinObject* pObj)
{}
//---------------------------------------------------------------------------
void PSS_View::SetScrollSizes()
{
    // resize the page rect
    const CSize sizePage(GetReportPageSizeInPixels());
    m_PageRect.bottom = sizePage.cy;
    m_PageRect.right  = sizePage.cx;

    const CSize totalSize(int(double(m_TotalSize.cx) * (double(GetZoomPercentage()) / 100.0)),
                          int(double(m_TotalSize.cy) * (double(GetZoomPercentage()) / 100.0)));

    const CSize pageSize(int(double(m_PageSize.cx) * (double(GetZoomPercentage()) / 100.0)),
                         int(double(m_PageSize.cy) * (double(GetZoomPercentage()) / 100.0)));

    const CSize lineSize(int(double(m_LineSize.cx) * (double(GetZoomPercentage()) / 100.0)),
                         int(double(m_LineSize.cy) * (double(GetZoomPercentage()) / 100.0)));

    PSS_DropScrollView::SetScrollSizes(MM_TEXT, totalSize, pageSize, lineSize);
}
//---------------------------------------------------------------------------
void PSS_View::OnInitialUpdate()
{
    PSS_DropScrollView::OnInitialUpdate();

    Initialize();
}
//---------------------------------------------------------------------------
CSize PSS_View::GetReportPageSize()
{
    // get the printer default page size (the default page size is set to A4)
    PRINTDLG printDlg;
    CSize pageSize(210, 297);

    if (AfxGetApp()->GetPrinterDeviceDefaults(&printDlg))
    {
        DEVNAMES FAR* pDevNames = NULL;
        DEVNAMES FAR* pDevMode  = NULL;

        try
        {
            pDevNames = (DEVNAMES FAR*)::GlobalLock(printDlg.hDevNames);

            if (!pDevNames)
                return CSize();

            pDevMode = (DEVNAMES FAR*)::GlobalLock(printDlg.hDevMode);

            if (!pDevMode)
            {
                ::GlobalUnlock(printDlg.hDevNames);
                return CSize();
            }

            const CString driver(LPSTR(pDevNames) + pDevNames->wDriverOffset);
            const CString device(LPSTR(pDevNames) + pDevNames->wDeviceOffset);
            const CString output(LPSTR(pDevNames) + pDevNames->wOutputOffset);

            CDC printDC;
            printDC.CreateDC(driver, device, output, pDevMode);

            pageSize = CSize(printDC.GetDeviceCaps(HORZSIZE), printDC.GetDeviceCaps(VERTSIZE));

            printDC.DeleteDC();
        }
        catch (...)
        {
            if (pDevNames)
                ::GlobalUnlock(printDlg.hDevNames);

            if (pDevMode)
                ::GlobalUnlock(printDlg.hDevMode);

            throw;
        }

        ::GlobalUnlock(printDlg.hDevNames);
        ::GlobalUnlock(printDlg.hDevMode);
    }

    // return the size in millimeters
    return pageSize;
}
//---------------------------------------------------------------------------
CSize PSS_View::GetReportPageSizeInPixels()
{
    // get the page size in millimeters
    CSize pageSize(GetReportPageSize());

    // adjust the ratio between printer page and screen. Get in millimeters to consider the pixels per inches
    pageSize.cy = int(double(pageSize.cy) * double(m_LogUnitY) / 25.4);
    pageSize.cx = int(double(pageSize.cx) * double(m_LogUnitX) / 25.4);

    return pageSize;
}
//---------------------------------------------------------------------------
void PSS_View::DrawPageRect(CDC* pDC)
{
    // draw the page rect
    const CRect pageRect(m_PageRect);
    CBrush*     pOldBrush = pDC->SelectObject(&PSS_PaintResources::GetWhiteBrush());
    CPen*       pOldPen   = pDC->SelectObject(&PSS_PaintResources::GetBlackPen());

    pDC->Rectangle(&pageRect);
    pDC->SelectObject(&PSS_PaintResources::GetGrayPen());
    pDC->MoveTo(pageRect.right + 1, pageRect.top    + 2);
    pDC->LineTo(pageRect.right + 1, pageRect.bottom + 1);
    pDC->LineTo(pageRect.left  + 2, pageRect.bottom + 1);
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
}
//---------------------------------------------------------------------------
void PSS_View::OnDraw(CDC* pDC)
{}
//---------------------------------------------------------------------------
void PSS_View::OnLButtonDown(UINT nFlags, CPoint point)
{
    ReleaseCapture();

    if (m_SelectObjectMode)
    {
        ClientToDoc(point);
        m_pSelectedObject  = FindHitObject(point);
        m_SelectObjectMode = FALSE;
        return;
    }

    // find the currently selected tool and keep it. But if control key is pressed, take the selection tool directly
    PSS_VisualTool* pTool = PSS_VisualTool::FindTool(PSS_VisualTool::m_CurrentToolType);

    if (pTool)
        pTool->OnLButtonDown(this, nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_View::OnLButtonUp(UINT nFlags, CPoint point)
{
    ReleaseCapture();

    if (m_SelectObjectMode)
        return;

    // find the currently selected tool and keep it. But if control key is pressed, take the selection tool directly
    PSS_VisualTool* pTool = PSS_VisualTool::FindTool(PSS_VisualTool::m_CurrentToolType);

    if (pTool)
        pTool->OnLButtonUp(this, nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_View::OnKillFocus(CWnd* pNewWnd)
{
    PSS_DropScrollView::OnKillFocus(pNewWnd);

    // stop the selection object mode if started
    m_SelectObjectMode = FALSE;
    ReleaseCapture();
}
//---------------------------------------------------------------------------
BOOL PSS_View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    if (pWnd == this)
    {
        // test all tracked objects
        CDocument* pDoc = GetDocument();
        PSS_Assert(pDoc);

        PSS_PlanFinObject* pObj;

        // search which element is selected
        if ((pObj = ((PSS_Document*)pDoc)->GetHead()) == NULL)
            return PSS_DropScrollView::OnSetCursor(pWnd, nHitTest, message);

        do
        {
            if (pObj->IsObjectSelected())
                // if processed then go out
                if (pObj->GetRectTracker())
                    if (pObj->GetRectTracker()->SetCursor(this, nHitTest))
                        return TRUE;
        }
        while ((pObj = ((PSS_Document*)pDoc)->GetNext()) != NULL);
    }

    return PSS_DropScrollView::OnSetCursor(pWnd, nHitTest, message);
}
//---------------------------------------------------------------------------
void PSS_View::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    PSS_DropScrollView::OnVScroll(nSBCode, nPos, pScrollBar);

    CPoint pt   = GetScrollPosition();
    CWnd*  pWnd = ::AfxGetMainWnd();

    // if the PSS_ViewScroll view exists, send message to synchronize the scrollbars
    if (pWnd)
        pWnd->SendMessageToDescendants(ID_SYNCHRONIZE_VSCROLL, 0, LPARAM(&pt));
}
//---------------------------------------------------------------------------
void PSS_View::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    PSS_DropScrollView::OnHScroll(nSBCode, nPos, pScrollBar);

    CPoint pt   = GetScrollPosition();
    CWnd*  pWnd = ::AfxGetMainWnd();

    // if the PSS_ViewScroll view exists, send message to synchronize the scrollbars
    if (pWnd)
        pWnd->SendMessageToDescendants(ID_SYNCHRONIZE_HSCROLL, 0, LPARAM(&pt));
}
//---------------------------------------------------------------------------
