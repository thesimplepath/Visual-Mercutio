//## begin module%334FC46302F9.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC46302F9.cm

//## begin module%334FC46302F9.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%334FC46302F9.cp

//## Module: ZIView%334FC46302F9; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZIView.cpp

//## begin module%334FC46302F9.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%334FC46302F9.additionalIncludes

//## begin module%334FC46302F9.includes preserve=yes
//## end module%334FC46302F9.includes

// VTools
#include "PSS_VisualTool.h"

// ZIView
#include "ZIView.h"

//## begin module%334FC46302F9.declarations preserve=no
//## end module%334FC46302F9.declarations

//## begin module%334FC46302F9.additionalDeclarations preserve=yes
#include "PSS_PLFNCheckBtn.h"
#include "PSS_PLFNRadioBtn.h"
#include "PSS_MsgBox.h"
#include "ZDDoc.h"

// PaintRes
#include "PSS_PaintResources.h"

// PaintOp
#include "PSS_PaintOperations.h"

#include "PSS_FieldObserverMsg.h"
#include "ZISubject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_DYNCREATE(ZIView, PSS_DropScrollView)

BEGIN_MESSAGE_MAP(ZIView, PSS_DropScrollView)
    //{{AFX_MSG_MAP(ZIView)
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
//## end module%334FC46302F9.additionalDeclarations

/////////////////////////////////////////////////////////////////////////////////////////////////
// Class ZIView 

//## begin ZIView::pOldPointerSelectedObj%334FC460037D.attr preserve=no  protected: static PlanFinObject* {V} NULL
PSS_PlanFinObject* ZIView::m_pOldPointerSelectedObj = NULL;
//## end ZIView::pOldPointerSelectedObj%334FC460037D.attr

ZIView::ZIView()
//## begin ZIView::ZIView%.hasinit preserve=no
    : m_ChoosedObject(NULL),
    m_bChooseObjectMode(FALSE),
    //## end ZIView::ZIView%.hasinit
    //## begin ZIView::ZIView%.initialization preserve=yes
    m_LineSize(10, 10),
    m_iZoom(100),
    m_ViewType(UnknownView)        // Construct the view with unknown view
    //## end ZIView::ZIView%.initialization
{

    //## begin ZIView::ZIView%.body preserve=yes
    //## end ZIView::ZIView%.body
}

ZIView::~ZIView()
{
    //## begin ZIView::~ZIView%.body preserve=yes
    m_ToolTip.DestroyWindow();
    //## end ZIView::~ZIView%.body
}

void ZIView::Initialize()
{
    // Retreive the logical size of the screen
    CDC*    pDC = GetDC();
    ASSERT(pDC);
    PSS_PaintOperations::SetLogicalBasicUnits(CSize(pDC->GetDeviceCaps(LOGPIXELSX),
                                                    pDC->GetDeviceCaps(LOGPIXELSY)));

    m_iLogUnitX = PSS_PaintOperations::GetLogicalBasicUnits().cx;
    m_iLogUnitY = PSS_PaintOperations::GetLogicalBasicUnits().cy;

    VERIFY(ReleaseDC(pDC));

    m_hSelectorCursor = ::LoadCursor(AfxFindResourceHandle(MAKEINTRESOURCE(IDC_SELECTOROBJECT), RT_GROUP_CURSOR),
                                     MAKEINTRESOURCE(IDC_SELECTOROBJECT));

    m_PageRect = CRect(CPoint(0, 0), GetReportPageSizeInPixels());

    CalculateTheDocumentSize();
    SetScrollSizes();

    if (m_ToolTip.Create(this, TTS_ALWAYSTIP) && m_ToolTip.AddTool(this))
    {
        m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, SHRT_MAX);
        m_ToolTip.SendMessage(TTM_SETDELAYTIME, TTDT_AUTOPOP, SHRT_MAX);
        m_ToolTip.SendMessage(TTM_SETDELAYTIME, TTDT_INITIAL, 200);
        m_ToolTip.SendMessage(TTM_SETDELAYTIME, TTDT_RESHOW, 200);

        // Set the text color and the background color
        m_ToolTip.SendMessage(TTM_SETTIPTEXTCOLOR, defCOLOR_WHITE, 0L);
        m_ToolTip.SendMessage(TTM_SETTIPBKCOLOR, defCOLOR_BLUE, 0L);
    }
    else
    {
        TRACE(_T("Error in creating ToolTip"));
    }
}

//## Other Operations (implementation)
void ZIView::OnInitialUpdate()
{
    //## begin ZIView::OnInitialUpdate%832201961.body preserve=yes
    PSS_DropScrollView::OnInitialUpdate();

    Initialize();
    //## end ZIView::OnInitialUpdate%832201961.body
}

void ZIView::CalculateTheDocumentSize()
{
    //## begin ZIView::CalculateTheDocumentSize%832201962.body preserve=yes
    // Calculate the size of the document
    CRect rect;
    CRect WndRect;

    // Calculate the size of the page
    // regarding the size of the view
    GetClientRect(&WndRect);
    m_PageSize.cx = WndRect.right / 2;
    m_PageSize.cy = WndRect.bottom / 2;

    // Add one page to the total 
    // of the document
    m_TotalSize = GetReportPageSizeInPixels();
    m_TotalSize += m_PageSize;
    //## end ZIView::CalculateTheDocumentSize%832201962.body
}

void ZIView::SetLogicalCoordinates(CDC* pDC)
{
    //## begin ZIView::SetLogicalCoordinates%832201963.body preserve=yes
    pDC->SetMapMode(MM_ANISOTROPIC);

    // Apply the ratio as 
    if (pDC->IsPrinting() == FALSE)
    {
        pDC->SetWindowExt((int)((double)m_iLogUnitX / (double)((double)m_iZoom / (double)100)),
            (int)((double)m_iLogUnitY / (double)((double)m_iZoom / (double)100)));
    }
    else
    {
        pDC->SetWindowExt(m_iLogUnitX, m_iLogUnitY);
    }

    pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),
                        pDC->GetDeviceCaps(LOGPIXELSY));
    //## end ZIView::SetLogicalCoordinates%832201963.body
}

void ZIView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    //## begin ZIView::OnPrepareDC%832201965.body preserve=yes
    PSS_DropScrollView::OnPrepareDC(pDC, pInfo);
    SetLogicalCoordinates(pDC);
    //## end ZIView::OnPrepareDC%832201965.body
}

PSS_PlanFinObject* ZIView::ActiveSelectedObject(CPoint& point, BOOL bAutoReset)
{
    //## begin ZIView::ActiveSelectedObject%832201974.body preserve=yes
    ZDDocument*    pDoc = GetDocument();
    ASSERT(pDoc);
    PSS_PlanFinObject*    obj;
    PSS_PlanFinObject*    ReturnedObject = NULL;

    // Retreive the current page
    int iPage;
    iPage = pDoc->GetCurrentPage();

    // translate the point in logical coordinates
    CDC *pDC = GetDC();
    ASSERT(pDC);

    CPoint pt(point);
    OnPrepareDC(pDC);

    // Search wich element is selected
    if ((obj = pDoc->GetHead()) == NULL)
    {
        VERIFY(ReleaseDC(pDC));
        return FALSE;
    }

    do
    {
        // Test if one object is already selected
        // deselect it before
        if (!bAutoReset)
            obj->SelectObject(this, pDC, FALSE);

        // Display object on the right page
        if (iPage == obj->GetObjectPage())
        {
            if (obj->IsHint(point))
            {
                // Notify observer about object selection

                if (obj->IsObjectSelected())
                    obj->SelectObject(this, pDC, FALSE);
                else
                {
                    obj->SelectObject(this, pDC, TRUE);
                    PSS_FieldObserverMsg msg(UM_NOTIFY_OBJECTSELECTED, obj);
                    dynamic_cast<ZISubject*>(AfxGetMainWnd())->NotifyAllObservers(&msg);
                }

                ReturnedObject = obj;            // Assign the current 
                                                // proceed object
                if (bAutoReset)                // If automatic auto-reset of
                    break;                        // the current selected object
                                                // Then it is not necessary to
                                                // continue.
            }
        }
    }
    while ((obj = pDoc->GetNext()) != NULL);

    VERIFY(ReleaseDC(pDC));

    return ReturnedObject;
    //## end ZIView::ActiveSelectedObject%832201974.body
}

void ZIView::SelectObjectInRect(const CRect& rect, CWnd* pWnd, CDC* pDC)
{
    //## begin ZIView::SelectObjectInRect%832201975.body preserve=yes
    ZDDocument* pDoc = GetDocument();
    ASSERT(pDoc);

    PSS_PlanFinObject *obj;

    // Retreive the current page
    int iPage = pDoc->GetCurrentPage();

    // Search wich element has been modified
    if ((obj = pDoc->GetHead()) == NULL)
        return;

    do
    {
        // If the page of the next object is greater than
        // the actual page, it is not necessary to continue.
        if (obj->GetObjectPage() > iPage)
            break;

        // Display object on the right page
        if (iPage == obj->GetObjectPage())
        {
            // If the rect is contained in the rect, then
            // select it
            if (rect.PtInRect(obj->GetClientRect().TopLeft()) ||
                rect.PtInRect(obj->GetClientRect().BottomRight()))
            {
                obj->SelectObject(pWnd, pDC, TRUE, FALSE);
            }
            else
            {
                // Or remove the selection.
                obj->SelectObject(pWnd, pDC, FALSE);
            }
        }
    }
    while ((obj = pDoc->GetNext()) != NULL);
    //## end ZIView::SelectObjectInRect%832201975.body
}

BOOL ZIView::GetRectOfSelectedObject(CRect& rect)
{
    //## begin ZIView::GetRectOfSelectedObject%832201973.body preserve=yes
    ZDDocument* pDoc = GetDocument();
    ASSERT(pDoc);

    PSS_PlanFinObject  *obj;
    BOOL            bRetValue = FALSE;

    // Retreive the current page
    int iPage = pDoc->GetCurrentPage();
    rect.SetRect(0, 0, 0, 0);

    // Search wich element has been modified
    if ((obj = pDoc->GetHead()) == NULL)
        return FALSE;

    do
    {
        if (obj->GetObjectPage() == iPage)
        {
            if (obj->IsObjectSelected())
            {
                rect.UnionRect(&rect, obj->GetClientRect());
                bRetValue = TRUE;
            }
        }
    }
    while ((obj = pDoc->GetNext()) != NULL);

    return bRetValue;
    //## end ZIView::GetRectOfSelectedObject%832201973.body
}

void ZIView::DeselectAllObject(CWnd* pWnd, CDC* pDC, ZDDocument* pDoc)
{
    //## begin ZIView::DeselectAllObject%832201976.body preserve=yes
    PSS_PlanFinObject  *obj;

    // Retreive the current page
    int iPage = pDoc->GetCurrentPage();

    // Search wich element is selected and deselect it
    if ((obj = pDoc->GetHead()) == NULL)
        return;

    do
    {
        if (obj->GetObjectPage() == iPage)
        {
            if (obj->IsObjectSelected())
                obj->SelectObject(pWnd, pDC, FALSE);
        }
    }
    while ((obj = pDoc->GetNext()) != NULL);
    //## end ZIView::DeselectAllObject%832201976.body
}

void ZIView::ClientToDoc(CPoint& point)
{
    //## begin ZIView::ClientToDoc%832637469.body preserve=yes
    CClientDC dc(this);
    OnPrepareDC(&dc, NULL);
    dc.DPtoLP(&point);
    //## end ZIView::ClientToDoc%832637469.body
}

void ZIView::ClientToDoc(CRect& rect)
{
    //## begin ZIView::ClientToDoc%832637470.body preserve=yes
    CClientDC dc(this);
    OnPrepareDC(&dc, NULL);
    dc.DPtoLP(rect);
    //## end ZIView::ClientToDoc%832637470.body
}

void ZIView::DocToClient(CPoint& point)
{
    //## begin ZIView::DocToClient%832637471.body preserve=yes
    CClientDC dc(this);
    OnPrepareDC(&dc, NULL);
    dc.LPtoDP(&point);
    //## end ZIView::DocToClient%832637471.body
}

void ZIView::DocToClient(CRect& rect)
{
    //## begin ZIView::DocToClient%832637472.body preserve=yes
    CClientDC dc(this);
    OnPrepareDC(&dc, NULL);
    dc.LPtoDP(rect);

    rect.NormalizeRect();
    //## end ZIView::DocToClient%832637472.body
}

PSS_PlanFinObject* ZIView::FindHitObject(CPoint& point)
{
    //## begin ZIView::FindHitObject%837834739.body preserve=yes
    ZDDocument* pDoc = GetDocument();
    ASSERT(pDoc);

    PSS_PlanFinObject *obj;
    // Retreive the current page
    int iPage;
    iPage = pDoc->GetCurrentPage();

    // Search wich element is selected
    if ((obj = pDoc->GetHead()) == NULL)
        return NULL;

    do
    {
        if (iPage == obj->GetObjectPage())
            if (obj->IsHint(point))
                return obj;
    }
    while ((obj = pDoc->GetNext()) != NULL);

    return NULL;
    //## end ZIView::FindHitObject%837834739.body
}

PSS_PlanFinObject* ZIView::ChooseObject()
{
    //## begin ZIView::ChooseObject%850768721.body preserve=yes
    m_bChooseObjectMode = TRUE;
    m_ChoosedObject = NULL;
    MSG msg;

    SetCapture();
    SetCursor(m_hSelectorCursor);

    while (GetMessage(&msg, (HWND)NULL, 0, 0) && m_bChooseObjectMode == TRUE)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        SetCapture();

        if (GetCursor() != m_hSelectorCursor)
            SetCursor(m_hSelectorCursor);
    }

    if (m_ChoosedObject)
    {
        CDC *pDC = GetDC();
        ASSERT(pDC);
        OnPrepareDC(pDC);

        m_ChoosedObject->SelectObject(this, pDC, TRUE);
        VERIFY(ReleaseDC(pDC));
    }

    return m_ChoosedObject;
    //## end ZIView::ChooseObject%850768721.body
}

CObArray& ZIView::GetArrayOfSelectedObject()
{
    //## begin ZIView::GetArrayOfSelectedObject%863883947.body preserve=yes
    ZDDocument* pDoc = GetDocument();
    ASSERT(pDoc);

    // Remove all elements
    m_ArrayOfSelectedObject.RemoveAll();
    PSS_PlanFinObject *obj;

    // Search wich element is selected
    if ((obj = pDoc->GetHead()) != NULL)
    {
        do
        {
            if (obj->IsObjectSelected())
                m_ArrayOfSelectedObject.Add(obj);
        }
        while ((obj = pDoc->GetNext()) != NULL);
    }

    return m_ArrayOfSelectedObject;
    //## end ZIView::GetArrayOfSelectedObject%863883947.body
}

void ZIView::KeepObjectInPage(PSS_PlanFinObject* pObj, CSize& ReportSize)
{
    //## begin ZIView::KeepObjectInPage%901975365.body preserve=yes
    // Tests if the object stills in the page
    // Saves the height and the width of the object
    int    iWidth = pObj->GetClientRect().Width();
    int    iHeight = pObj->GetClientRect().Height();

    // If too left
    if (pObj->GetClientRect().left < 0)
    {
        pObj->GetClientRect().left = 0;
        pObj->GetClientRect().right = pObj->GetClientRect().left + iWidth;
    }

    // If too right
    if (pObj->GetClientRect().right > ReportSize.cx)
    {
        pObj->GetClientRect().right = ReportSize.cx;
        pObj->GetClientRect().left = pObj->GetClientRect().right - iWidth;
    }

    // If too top
    if (pObj->GetClientRect().top < 0)
    {
        pObj->GetClientRect().top = 0;
        pObj->GetClientRect().bottom = pObj->GetClientRect().top + iHeight;
    }

    // If too bottom
    if (pObj->GetClientRect().bottom > ReportSize.cy)
    {
        pObj->GetClientRect().bottom = ReportSize.cy;
        pObj->GetClientRect().top = pObj->GetClientRect().bottom - iHeight;
    }
    //## end ZIView::KeepObjectInPage%901975365.body
}

CSize ZIView::GetReportPageSize()
{
    //## begin ZIView::GetReportPageSize%908446783.body preserve=yes
    // get the printer default page size
    PRINTDLG printDlg;
    CSize pageSize(210, 297);    // default page size set to a4

    if (AfxGetApp()->GetPrinterDeviceDefaults(&printDlg))
    {
        DEVNAMES FAR* lpDevNames = (DEVNAMES FAR*)GlobalLock(printDlg.hDevNames);
        DEVNAMES FAR* lpDevMode = (DEVNAMES FAR*)GlobalLock(printDlg.hDevMode);

        CString szDriver((LPSTR)lpDevNames + lpDevNames->wDriverOffset);
        CString szDevice((LPSTR)lpDevNames + lpDevNames->wDeviceOffset);
        CString szOutput((LPSTR)lpDevNames + lpDevNames->wOutputOffset);

        CDC printDC;

        printDC.CreateDC(szDriver, szDevice, szOutput, lpDevMode);

        pageSize = CSize(printDC.GetDeviceCaps(HORZSIZE),
                         printDC.GetDeviceCaps(VERTSIZE));

        printDC.DeleteDC();

        GlobalUnlock(printDlg.hDevNames);
        GlobalUnlock(printDlg.hDevMode);
    }

    return pageSize;    // return the size in millimeters
    //## end ZIView::GetReportPageSize%908446783.body
}

CSize ZIView::GetReportPageSizeInPixels()
{
    //## begin ZIView::GetReportPageSizeInPixels%908446784.body preserve=yes
    CSize pageSize(GetReportPageSize());        // Get the page size in millimeters

    // Adjust the ratio between printer page and screen
    // get millimeters because we have pixels per inches
    pageSize.cy = (int)((double)pageSize.cy * (double)m_iLogUnitY / (double)25.4);
    pageSize.cx = (int)((double)pageSize.cx * (double)m_iLogUnitX / (double)25.4);

    return pageSize;
    //## end ZIView::GetReportPageSizeInPixels%908446784.body
}

void ZIView::DrawPageRect(CDC* pDC)
{
    //## begin ZIView::DrawPageRect%908446785.body preserve=yes

    // Draw the page rect
    CRect    PageRect(m_PageRect);
    CBrush*    pOldBrush = pDC->SelectObject(&PSS_PaintResources::GetWhiteBrush());
    CPen*    pOldPen = pDC->SelectObject(&PSS_PaintResources::GetBlackPen());

    pDC->Rectangle(&PageRect);
    pDC->SelectObject(&PSS_PaintResources::GetGrayPen());
    pDC->MoveTo(PageRect.right + 1, PageRect.top + 2);
    pDC->LineTo(PageRect.right + 1, PageRect.bottom + 1);
    pDC->LineTo(PageRect.left + 2, PageRect.bottom + 1);
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
    //## end ZIView::DrawPageRect%908446785.body
}

void ZIView::OnDraw(CDC* pDC)
{
    //## begin ZIView::OnDraw%908620922.body preserve=yes
      // Do nothing in the base class
    //## end ZIView::OnDraw%908620922.body
}

void ZIView::SetZoomPercentage(int iZoom)
{
    //## begin ZIView::SetZoomPercentage%938112086.body preserve=yes
    m_iZoom = iZoom;
    SetScrollSizes();
    //## end ZIView::SetZoomPercentage%938112086.body
}

void ZIView::EditObject(PSS_PlanFinObject* pObj)
{
    //## begin ZIView::EditObject%938177648.body preserve=yes
    //## end ZIView::EditObject%938177648.body
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Additional Declarations

//## begin ZIView%334FC46002A6.declarations preserve=yes
void ZIView::OnLButtonDown(UINT nFlags, CPoint point)
{
    ReleaseCapture();

    if (m_bChooseObjectMode)
    {
        ClientToDoc(point);
        m_ChoosedObject = FindHitObject(point);
        m_bChooseObjectMode = FALSE;

        return;
    }

    // Find the current select tool
    // and keep its pointer.
    // But if control key pressed
    // Take the selection tool directly
    PSS_VisualTool* pTool = PSS_VisualTool::FindTool(PSS_VisualTool::m_CurrentToolType);

    if (pTool != NULL)
        pTool->OnLButtonDown(this, nFlags, point);
}

void ZIView::OnLButtonUp(UINT nFlags, CPoint point)
{
    ReleaseCapture();

    if (m_bChooseObjectMode)
        return;

    // Find the current select tool
    // and keep its pointer.
    // But if control key pressed
    // Take the selection tool directly
    PSS_VisualTool* pTool = PSS_VisualTool::FindTool(PSS_VisualTool::m_CurrentToolType);

    if (pTool != NULL)
        pTool->OnLButtonUp(this, nFlags, point);
}

void ZIView::OnKillFocus(CWnd* pNewWnd)
{
    PSS_DropScrollView::OnKillFocus(pNewWnd);

    // Stop the choose object mode if started
    m_bChooseObjectMode = FALSE;
    ReleaseCapture();
}

BOOL ZIView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    if (pWnd == this)
    {
        // Test all tracked objects
        CDocument *pDoc = GetDocument();
        ASSERT(pDoc);
        PSS_PlanFinObject *obj;

        // Search wich element is selected
        if ((obj = ((ZDDocument*)pDoc)->GetHead()) == NULL)
            return PSS_DropScrollView::OnSetCursor(pWnd, nHitTest, message);

        do
        {
            if (obj->IsObjectSelected())
            {
                // If processed then go out
                if (obj->GetRectTracker())
                    if (obj->GetRectTracker()->SetCursor(this, nHitTest))
                        return TRUE;
            }
        }
        while ((obj = ((ZDDocument*)pDoc)->GetNext()) != NULL);
    }

    return PSS_DropScrollView::OnSetCursor(pWnd, nHitTest, message);
}

void ZIView::SetScrollSizes()
{
    // Resize the page rect
    CSize SizePage(GetReportPageSizeInPixels());
    m_PageRect.bottom = SizePage.cy;
    m_PageRect.right = SizePage.cx;

    CSize    TotalSize((int)((double)m_TotalSize.cx * (double)((double)GetZoomPercentage() / (double)100)),
        (int)((double)m_TotalSize.cy * (double)((double)GetZoomPercentage() / (double)100)));

    CSize    PageSize((int)((double)m_PageSize.cx * (double)((double)GetZoomPercentage() / (double)100)),
        (int)((double)m_PageSize.cy * (double)((double)GetZoomPercentage() / (double)100)));

    CSize    LineSize((int)((double)m_LineSize.cx * (double)((double)GetZoomPercentage() / (double)100)),
        (int)((double)m_LineSize.cy * (double)((double)GetZoomPercentage() / (double)100)));

    PSS_DropScrollView::SetScrollSizes(MM_TEXT, TotalSize, PageSize, LineSize);
}

void ZIView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    PSS_DropScrollView::OnVScroll(nSBCode, nPos, pScrollBar);

    // If the view ZIViewScroll is present, 
    // Send message to synchronize the scroll bars
    CPoint pt = GetScrollPosition();
    AfxGetMainWnd()->SendMessageToDescendants(ID_SYNCHRONIZE_VSCROLL, 0, (LPARAM)&pt);
}

void ZIView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    PSS_DropScrollView::OnHScroll(nSBCode, nPos, pScrollBar);

    // If the view ZIViewScroll is present, 
    // Send message to synchronize the scroll bars
    CPoint pt = GetScrollPosition();
    AfxGetMainWnd()->SendMessageToDescendants(ID_SYNCHRONIZE_HSCROLL, 0, (LPARAM)&pt);
}

//## end ZIView%334FC46002A6.declarations

//## begin module%334FC46302F9.epilog preserve=yes
//## end module%334FC46302F9.epilog
