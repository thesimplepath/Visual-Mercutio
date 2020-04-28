/****************************************************************************
 * ==> PSS_ProcessGraphModelView -------------------------------------------*
 ****************************************************************************
 * Description : Provides a graphic process model view                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessGraphModelView.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zBaseLib\PSS_MathHelper.h"
#include "zBaseLib\PSS_SpanWnd.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_FileDialog.h"
#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_ProcessGraphModelController.h"
#include "PSS_ProcessGraphModelDoc.h"
#include "PSS_ModelObserverMsg.h"

// resources
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_MvcScrollView
//---------------------------------------------------------------------------
PSS_MvcScrollView::PSS_MvcScrollView() :
    PSS_DropScrollView(),
    MvcWrapper_T<PSS_ProcessGraphModelViewport>(),
    m_LineScroll(CSize(10, 10)),
    m_UpdateScrollBars(FALSE)
{}
//---------------------------------------------------------------------------
PSS_MvcScrollView::~PSS_MvcScrollView()
{}
//---------------------------------------------------------------------------
BOOL PSS_MvcScrollView::Create(LPCTSTR         pClassName,
                               LPCTSTR         pWindowName,
                               DWORD           style,
                               const RECT&     rect,
                               CWnd*           pParentWnd,
                               UINT            id,
                               CCreateContext* pContext)
{
    SetContainer(NULL);

    BOOL success = PSS_DropScrollView::Create(pClassName,
                                              pWindowName,
                                              style,
                                              rect,
                                              pParentWnd,
                                              id,
                                              pContext);

    if (success)
    {
        success = PSS_ProcessGraphModelViewport::Create(this, NULL);

        if (success && m_pCtlr)
            // make sure model is set on controller, because model may have been assigned
            // to this viewport before the controller was created
            m_pCtlr->SetModel(m_pModel);
    }

    return success;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelViewport* PSS_MvcScrollView::GetViewport()
{
    return static_cast<PSS_ProcessGraphModelViewport*>(this);
}
//---------------------------------------------------------------------------
CPoint PSS_MvcScrollView::SetOrigin(int x, int y)
{
    const CPoint point = MvcWrapper_T<PSS_ProcessGraphModelViewport>::SetOrigin(x, y);
    UpdateScrollBarPos();
    return point;
}
//---------------------------------------------------------------------------
CPoint PSS_MvcScrollView::SetLogOrigin(int x, int y)
{
    const CPoint point = MvcWrapper_T<PSS_ProcessGraphModelViewport>::SetLogOrigin(x, y);
    UpdateScrollBarPos();
    return point;
}
//---------------------------------------------------------------------------
CSize PSS_MvcScrollView::SetExtents(int cx, int cy)
{
    const CSize size   = MvcWrapper_T<PSS_ProcessGraphModelViewport>::SetExtents(cx, cy);
    m_UpdateScrollBars = TRUE;
    return size;
}
//---------------------------------------------------------------------------
CSize PSS_MvcScrollView::SetLogExtents(int cx, int cy)
{
    const CSize sizeExtents = MvcWrapper_T<PSS_ProcessGraphModelViewport>::SetLogExtents(cx, cy);
    m_UpdateScrollBars      = TRUE;
    return sizeExtents;
}
//---------------------------------------------------------------------------
CSize PSS_MvcScrollView::SetSize(int cx, int cy)
{
    const CSize size = MvcWrapper_T<PSS_ProcessGraphModelViewport>::SetSize(cx, cy);
    UpdateScrollBarPos();
    UpdateScrollBarSize();
    return size;
}
//---------------------------------------------------------------------------
CSize PSS_MvcScrollView::SetLogSize(int cx, int cy)
{
    const CSize size = MvcWrapper_T<PSS_ProcessGraphModelViewport>::SetLogSize(cx, cy);
    UpdateScrollBarPos();
    UpdateScrollBarSize();
    return size;
}
//---------------------------------------------------------------------------
CSize PSS_MvcScrollView::SetLogScaling(float fScaleWidth, float fScaleHeight)
{
    const CSize sizeExtents = MvcWrapper_T<PSS_ProcessGraphModelViewport>::SetLogScaling(fScaleWidth, fScaleHeight);
    UpdateScrollBarPos();
    UpdateScrollBarSize();
    return sizeExtents;
}
//---------------------------------------------------------------------------
void PSS_MvcScrollView::SetVirtualOrigin(int x, int y)
{
    MvcWrapper_T<PSS_ProcessGraphModelViewport>::SetVirtualOrigin(x, y);
    UpdateScrollBarPos();
}
//---------------------------------------------------------------------------
void PSS_MvcScrollView::SetVirtualSize(int cx, int cy)
{
    MvcWrapper_T<PSS_ProcessGraphModelViewport>::SetVirtualSize(cx, cy);
    UpdateScrollBarPos();
    UpdateScrollBarSize();
}
//---------------------------------------------------------------------------
void PSS_MvcScrollView::OnInitialUpdate()
{
    // build the viewport in the derived class constructor and delete it in the destructor
    PSS_DropScrollView::OnInitialUpdate();

    CRect rect;

    // viewport initialization
    GetClientRect(&rect);
    MvcWrapper_T<PSS_ProcessGraphModelViewport>::SetSize(rect.Size());
    MvcWrapper_T<PSS_ProcessGraphModelViewport>::OnInitialUpdate();

    UpdateScrollBarPos();
    UpdateScrollBarSize();
}
//---------------------------------------------------------------------------
void PSS_MvcScrollView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    ASSERT(PSS_DropScrollView::m_nMapMode == MM_TEXT);
    MvcWrapper_T<PSS_ProcessGraphModelViewport>::OnPrepareDC(pDC);

    // for default printing behavior
    CView::OnPrepareDC(pDC, pInfo);
}
//---------------------------------------------------------------------------
BOOL PSS_MvcScrollView::OnScrollBy(CSize scrollSize, BOOL doScroll)
{
    // don't scroll if there is no valid scroll range (i.e no scrollbar)
    const DWORD style = GetStyle();
    CScrollBar* pBar  = GetScrollBarCtrl(SB_VERT);

    // is vertical scrollbar enabled?
    if ((pBar && !pBar->IsWindowEnabled()) || (!pBar && !(style & WS_VSCROLL)))
        scrollSize.cy = 0;

    pBar = GetScrollBarCtrl(SB_HORZ);

    // is horizontal scrollbar enabled?
    if ((pBar && !pBar->IsWindowEnabled()) || (!pBar && !(style & WS_HSCROLL)))
        scrollSize.cx = 0;

    // adjust current x position
    const int xOrig = GetScrollPos(SB_HORZ);
    const int x     = PSS_MathHelper::Clamp(int(xOrig + scrollSize.cx), 0, GetScrollLimit(SB_HORZ));

    // adjust current y position
    const int yOrig = GetScrollPos(SB_VERT);
    const int y     = PSS_MathHelper::Clamp(int(yOrig + scrollSize.cy), 0, GetScrollLimit(SB_VERT));

    // did anything change?
    if (x == xOrig && y == yOrig)
        return FALSE;

    if (doScroll)
    {
        // scroll and update positions
        if (x != xOrig)
            SetScrollPos(SB_HORZ, x);

        if (y != yOrig)
            SetScrollPos(SB_VERT, y);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_MvcScrollView::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    BOOL handled = PSS_ProcessGraphModelViewport::OnWndMsg(message, wParam, lParam, pResult);

    if (!handled)
        handled = PSS_DropScrollView::OnWndMsg(message, wParam, lParam, pResult);

    // handle messages here that could cause scrolling
    switch (message)
    {
        case WM_SIZE:
        {
            // resize the logical viewport rect
            MvcWrapper_T<PSS_ProcessGraphModelViewport>::SetSize(LOWORD(lParam), HIWORD(lParam));

            // viewport scrolling
            int  mapMode;
            SIZE sizeTotal;
            SIZE sizePage;
            SIZE sizeLine;
            GetDeviceScrollSizes(mapMode, sizeTotal, sizePage, sizeLine);

            // need to call SetScrollSizes() in the OnInitialUpdate() override
            if (mapMode > 0)
                DoScrollViewport(GetScrollPosition());

            break;
        }

        case WM_HSCROLL:
        case WM_VSCROLL:
        {
            const int scrollCode = int(LOWORD(wParam));

            if (scrollCode != SB_ENDSCROLL)
            {
                CPoint     ptScroll;
                SCROLLINFO siH;
                SCROLLINFO siV;

                GetScrollInfo(SB_HORZ, &siH);
                GetScrollInfo(SB_VERT, &siV);

                if (scrollCode == SB_THUMBTRACK)
                {
                    ptScroll.x = siH.nTrackPos;
                    ptScroll.y = siV.nTrackPos;
                }
                else
                {
                    ptScroll.x = siH.nPos;
                    ptScroll.y = siV.nPos;
                }

                DoScrollViewport(ptScroll);
                handled = TRUE;
            }

            break;
        }

        case WM_MOUSEWHEEL:
        {
            DoScrollViewport(GetScrollPosition());
        }
    }

    return handled;
}
//---------------------------------------------------------------------------
BOOL PSS_MvcScrollView::OnCmdMsg(UINT id, int code, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    BOOL handled = PSS_ProcessGraphModelViewport::OnCmdMsg(id, code, pExtra, pHandlerInfo);

    if (!handled)
        handled = PSS_DropScrollView::OnCmdMsg(id, code, pExtra, pHandlerInfo);

    return handled;
}
//---------------------------------------------------------------------------
void PSS_MvcScrollView::DoScrollViewport(const CPoint& scrollPos)
{
    CSize logSize(scrollPos.x, scrollPos.y);
    PSS_ProcessGraphModelViewport::DPtoLP(&logSize);

    CPoint newPos;
    newPos.x = logSize.cx;
    newPos.y = logSize.cy;

    // same as Pan, except using absolute coordinates, not offsets
    PSS_ProcessGraphModelViewport::SetLogOrigin(newPos);
    PSS_ProcessGraphModelViewport::InvalidateVisual(this, FALSE, TRUE);
}
//---------------------------------------------------------------------------
void PSS_MvcScrollView::UpdateScrollBarPos()
{
    const CPoint logOrigin = PSS_ProcessGraphModelViewport::GetLogOrigin();

    // convert viewport logical origin to device coordinates, which can be used to adjust the scrollbars
    CSize devSize(logOrigin.x, logOrigin.y);
    PSS_ProcessGraphModelViewport::LPtoDP(&devSize);
    CPoint scrollPos(devSize.cx, devSize.cy);

    SetScrollPos(SB_HORZ, scrollPos.x, TRUE);
    SetScrollPos(SB_VERT, scrollPos.y, TRUE);
}
//---------------------------------------------------------------------------
void PSS_MvcScrollView::UpdateScrollBarSize()
{
    // the scroll view mapping mode is always set to MM_TEXT, so device coordinates in the viewport
    // are the same as logical coordinates used by the scrollbars. Logical coordinates in the viewport
    // must be converted to device units before being used to set the scrollbar positions or sizes
    CSize totalSize = PSS_ProcessGraphModelViewport::GetVirtualSize();
    PSS_ProcessGraphModelViewport::LPtoDP(&totalSize);

    const CSize pageSize(GetBounds().Size());

    CRect innerMarginsRect;
    PSS_ProcessGraphModelViewport::GetMargins(innerMarginsRect);

    const CSize innerMarginsSize(innerMarginsRect.left + innerMarginsRect.right,
                                 innerMarginsRect.top  + innerMarginsRect.bottom);

    totalSize = totalSize + innerMarginsSize;

    SetScrollSizes(MM_TEXT, totalSize, pageSize, m_LineScroll);
}
//---------------------------------------------------------------------------
void PSS_MvcScrollView::OnDraw(CDC* pDC)
{
    // do update scrollbars?
    if (m_UpdateScrollBars)
    {
        UpdateScrollBarPos();
        UpdateScrollBarSize();

        m_UpdateScrollBars = FALSE;
    }

    PSS_ProcessGraphModelViewport::Draw(pDC);
}
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_ProcessGraphModelView, PSS_MvcScrollView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProcessGraphModelView, PSS_MvcScrollView)
    //{{AFX_MSG_MAP(PSS_ProcessGraphModelView)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
    ON_COMMAND(ID_CREATEMETAFILE, OnExportModelToImageFile)
    ON_MESSAGE(UM_REFRESH_SYMBOL, OnRefreshSymbol)
    ON_MESSAGE(UM_REFRESH_SYMBOLSET, OnRefreshSymbolSet)
    ON_MESSAGE(UM_BROWSE_SYMBOL, OnBrowseSymbol)
    ON_MESSAGE(UM_OPEN_MODELPAGE, OnOpenModelPage)
    ON_MESSAGE(UM_ENSUREVISIBLE_SYMBOL, OnEnsureVisibleSymbol)
    ON_MESSAGE(UM_DOCUMENTMODELHASCHANGED, OnModelDocumentHasChanged)
    ON_MESSAGE(UM_START_PROPERTY_EDITION, OnAdviseStartPropertyEdition)
    ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNeedText)
    ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProcessGraphModelView
//---------------------------------------------------------------------------
PSS_ProcessGraphModelView::PSS_ProcessGraphModelView() :
    PSS_MvcScrollView(),
    m_CurrentRatio(1),
    m_PanInitialized(false),
    m_pViewModel(NULL)
{}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelView::~PSS_ProcessGraphModelView()
{
    m_ToolTip.DestroyWindow();
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelController* PSS_ProcessGraphModelView::GetModelController()
{
    return PSS_ProcessGraphModelViewport::GetModelController();
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessGraphModelView::GetModel()
{
    if (m_pViewModel)
        return m_pViewModel;

    PSS_ProcessGraphModelDoc* pDocument = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    // if can't activate a view with model name, create a new one
    if (pDocument)
        return pDocument->GetModel();

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelView::SetModel(PSS_ProcessGraphModelMdl* pModel, bool doSizeVp)
{
    m_pViewModel = pModel;

    PSS_ProcessGraphModelViewport::SetModel(pModel);

    if (doSizeVp)
        SizeVpToModel();

    PSS_ProcessGraphModelViewport::UpdateAll();

    // protect here, so callers don't have to
    if (!m_pOverview || !m_PanInitialized)
        return;

    // set the model to the pan viewport
    m_PanVp.SetModel(pModel);

    // update the area, but only if the pan is initialized
    if (m_PanInitialized)
        m_PanVp.UpdateAll();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelView::SizeVpToModel()
{
    if (!::IsWindow(GetSafeHwnd()) || !PSS_ProcessGraphModelViewport::GetWnd())
        return;

    PSS_ProcessGraphModelDoc* pDocument = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    if (pDocument)
        PSS_ProcessGraphModelViewport::SizeVp(pDocument->GetPrinterPageSize());
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelView::AcceptDrop() const
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelView::AcceptDropItem(CObject* pObj, const CPoint& point)
{
    PSS_ProcessGraphModelController* pCtrl = PSS_ProcessGraphModelViewport::GetModelController();

    if (pCtrl)
        return pCtrl->AcceptDropItem(pObj, point);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelView::DropItem(CObject* pObj, const CPoint& point)
{
    PSS_ProcessGraphModelController* pCtrl = PSS_ProcessGraphModelViewport::GetModelController();

    if (pCtrl)
        return pCtrl->DropItem(pObj, point);

    return false;
}
//---------------------------------------------------------------------------
const CString PSS_ProcessGraphModelView::GetViewName()
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (pModel)
        return pModel->GetAbsolutePath();

    return _T("");
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelView::SelectExportModelToImageFile()
{
    CString title;
    VERIFY(title.LoadString(IDS_EXPORTFILE_CHOOSETITLE));

    CString filterName;
    CString filters;

    // append the "*.jpg" files filter
    VERIFY(filterName.LoadString(IDS_EXPORTFILE_FILTERJPEG));
    filters += filterName;
    filters += (char)'\0';
    filters += _T("*.jpg");
    filters += (char)'\0';

    // set the "*.gif" files filter
    VERIFY(filterName.LoadString(IDS_EXPORTFILE_FILTERGIF));
    filters += filterName;
    filters += (char)'\0';
    filters += _T("*.gif");
    filters += (char)'\0';

    // append the "*.pcx" files filter
    VERIFY(filterName.LoadString(IDS_EXPORTFILE_FILTERPCX));
    filters += filterName;
    filters += (char)'\0';
    filters += _T("*.pcx");
    filters += (char)'\0';

    // append the "*.dib" files filter
    VERIFY(filterName.LoadString(IDS_EXPORTFILE_FILTERDIB));
    filters += filterName;
    filters += (char)'\0';
    filters += _T("*.dib");
    filters += (char)'\0';

    // append the "*.tga" files filter
    VERIFY(filterName.LoadString(IDS_EXPORTFILE_FILTERTGA));
    filters += filterName;
    filters += (char)'\0';
    filters += _T("*.tga");
    filters += (char)'\0';

    // append the "*.tif" files filter
    VERIFY(filterName.LoadString(IDS_EXPORTFILE_FILTERTIF));
    filters += filterName;
    filters += (char)'\0';
    filters += _T("*.tif");
    filters += (char)'\0';

    PSS_FileDialog fileDialog(title, filters, 6, _T(""));

    if (fileDialog.DoModal() == IDCANCEL)
        return false;

    CClientDC attribDC(this);

    if (!ExportModelToImageFile(fileDialog.GetFileName(), attribDC))
    {
        // in write mode, no chance, file corruption
        PSS_MsgBox mBox;
        mBox.Show(IDS_EXPORTFILE_FAIL, MB_OK);
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ProcessGraphModelView::AssertValid() const
    {
        PSS_DropScrollView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ProcessGraphModelView::Dump(CDumpContext& dc) const
    {
        PSS_DropScrollView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelView::OnDrawPan(CDC* pDC)
{
    if (m_pOverview)
    {
        if (!m_PanInitialized)
            InitializePanViewport();

        // setup a special zoom mode for the pan overview window, so that the view OnDraw()
        // will be tricked into drawing the overview window
        m_bCenter = FALSE;

        // update the window with the viewport buffer contents
        m_PanVp.Draw(pDC);
        TRACE("DRAW PAN");
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelView::OnInitialUpdate()
{
    PSS_MvcScrollView::OnInitialUpdate();

    PSS_ProcessGraphModelDoc* pDocument = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    // set the document page units
    if (pDocument)
        PSS_ProcessGraphModelViewport::SetPageUnits(pDocument->GetPageUnits());

    // size the viewport
    SizeVpToModel();

    // create the floating tooltip
    if (m_ToolTip.Create(this, TTS_ALWAYSTIP) && m_ToolTip.AddTool(this))
    {
        m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0,            SHRT_MAX);
        m_ToolTip.SendMessage(TTM_SETDELAYTIME,   TTDT_AUTOPOP, SHRT_MAX);
        m_ToolTip.SendMessage(TTM_SETDELAYTIME,   TTDT_INITIAL, 200);
        m_ToolTip.SendMessage(TTM_SETDELAYTIME,   TTDT_RESHOW,  200);

        // set the text and the background colors
        m_ToolTip.SendMessage(TTM_SETTIPTEXTCOLOR, defCOLOR_WHITE, 0L);
        m_ToolTip.SendMessage(TTM_SETTIPBKCOLOR,   defCOLOR_BLUE,  0L);
    }
    else
        TRACE("Error while the ToolTip was created");
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelView::OnDraw(CDC* pDC)
{
    // update the window with the viewport buffer contents
    PSS_ProcessGraphModelViewport::Draw(pDC);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    PSS_ProcessGraphModelViewport::OnPrepareDC(pDC, pInfo);
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelView::PreCreateWindow(CREATESTRUCT& cs)
{
    // modify the Window class or styles here by modifying the CREATESTRUCT cs
    return PSS_DropScrollView::PreCreateWindow(cs);
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelView::OnPreparePrinting(CPrintInfo* pInfo)
{
    PSS_DocumentPageSetup* pPageSetup = GetPrinterPageSize();

    if (pPageSetup)
        pPageSetup->OnUpdatePrinterSettings();

    // todo -cImprovement -oJean: for now only 1 page is allowed to be printed, this should be improved in the future
    // prepare the number of pages to print
    pInfo->SetMinPage(1);
    pInfo->SetMaxPage(1);

    return DoPreparePrinting(pInfo);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
    // print the canvas
    PSS_ProcessGraphModelViewport::Print(pDC, pInfo);
}
//---------------------------------------------------------------------------
int PSS_ProcessGraphModelView::OnCreate(LPCREATESTRUCT lpcs)
{
    if (PSS_DropScrollView::OnCreate(lpcs) == -1)
        return -1;

    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return -1;

    PSS_ProcessGraphModelViewport::SetModel(pModel);

    SizeVpToModel();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelView::OnSize(UINT nType, int cx, int cy)
{
    PSS_DropScrollView::OnSize(nType, cx, cy);

    if (PSS_ProcessGraphModelViewport::GetWnd())
        // the canvas viewport takes up entire container
        PSS_ProcessGraphModelViewport::SetSize(cx, cy);
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelView::OnEraseBkgnd(CDC* pDC)
{
    // don't erase the background!
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelView::OnExportModelToImageFile()
{
    SelectExportModelToImageFile();
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessGraphModelView::OnRefreshSymbol(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 0;

    PSS_ObserverMsg*      pMsg      = reinterpret_cast<PSS_ObserverMsg*>(lParam);
    PSS_ModelObserverMsg* pModelMsg = dynamic_cast<PSS_ModelObserverMsg*>(pMsg);

    if (pModelMsg)
    {
        PSS_ProcessGraphModelController* pModelCtrl = PSS_ProcessGraphModelViewport::GetModelController();

        if (pModelCtrl)
        {
            CODComponent* pElement = pModelMsg->GetElement();

            if (pElement)
            {
                pModelCtrl->RedrawComponent(*pElement);
                return 1;
            }
        }
    }

    return 0;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessGraphModelView::OnRefreshSymbolSet(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 0;

    PSS_ObserverMsg*      pMsg      = reinterpret_cast<PSS_ObserverMsg*>(lParam);
    PSS_ModelObserverMsg* pModelMsg = dynamic_cast<PSS_ModelObserverMsg*>(pMsg);

    if (pModelMsg)
    {
        PSS_ProcessGraphModelController* pModelCtrl = PSS_ProcessGraphModelViewport::GetModelController();

        if (pModelCtrl)
        {
            CODComponentSet* pElementSet = pModelMsg->GetElementSet();

            if (pElementSet)
            {
                pModelCtrl->RedrawComponentSet(*pElementSet);
                return 1;
            }
        }
    }

    return 0;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessGraphModelView::OnBrowseSymbol(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 0;

    PSS_ObserverMsg*      pMsg      = reinterpret_cast<PSS_ObserverMsg*>(lParam);
    PSS_ModelObserverMsg* pModelMsg = dynamic_cast<PSS_ModelObserverMsg*>(pMsg);

    if (pModelMsg)
    {
        PSS_ProcessGraphModelController* pModelCtrl = PSS_ProcessGraphModelViewport::GetModelController();

        if (pModelCtrl)
        {
            CODComponent* pElement = pModelMsg->GetElement();

            if (pElement)
                if (pModelCtrl->OpenSymbol(pElement))
                    return 1;
        }
    }

    return 0;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessGraphModelView::OnOpenModelPage(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 0;

    PSS_ObserverMsg*      pMsg      = reinterpret_cast<PSS_ObserverMsg*>(lParam);
    PSS_ModelObserverMsg* pModelMsg = dynamic_cast<PSS_ModelObserverMsg*>(pMsg);

    if (pModelMsg)
    {
        PSS_ProcessGraphModelController* pModelCtrl = PSS_ProcessGraphModelViewport::GetModelController();

        if (pModelCtrl)
        {
            PSS_ProcessGraphPage*     pPage  = pModelMsg->GetPage();
            PSS_ProcessGraphModelMdl* pModel = pModelMsg->GetModel();

            // if a page specified
            if (pModelMsg->GetPage())
            {
                if (pModelCtrl->OpenPage(pPage))
                    return 1;
            }
            else
            if (pModel)
                // browse the model
                if (pModelCtrl->BrowseModel(pModel, pModel->GetParent()))
                    return 1;
        }
    }

    return 0;
}
//---------------------------------------------------------------------------
afx_msg LRESULT PSS_ProcessGraphModelView::OnEnsureVisibleSymbol(WPARAM wParam, LPARAM lParam)
{
    if (!::IsWindow(GetSafeHwnd()))
        return 0;

    PSS_ObserverMsg*      pMsg      = reinterpret_cast<PSS_ObserverMsg*>(lParam);
    PSS_ModelObserverMsg* pModelMsg = dynamic_cast<PSS_ModelObserverMsg*>(pMsg);

    if (pModelMsg)
    {
        PSS_ProcessGraphModelController* pModelCtrl = PSS_ProcessGraphModelViewport::GetModelController();

        if (pModelCtrl)
        {
            CODComponent* pElement = pModelMsg->GetElement();

            if (pElement)
                if (pModelCtrl->EnsureSymbolVisible(pElement))
                {
                    // process the selection if necessary
                    if (pModelMsg->GetActionType() == PSS_ModelObserverMsg::IE_AT_SelectElement)
                        pModelCtrl->SelectComponent(*pElement);

                    return 1;
                }
        }
    }

    return 0;
}
//---------------------------------------------------------------------------
LRESULT PSS_ProcessGraphModelView::OnModelDocumentHasChanged(WPARAM wParam, LPARAM lParam)
{
    PSS_ProcessGraphModelController* pModelCtrl = PSS_ProcessGraphModelViewport::GetModelController();

    if (pModelCtrl)
        pModelCtrl->OnModelDocumentHasChanged();

    return 0;
}
//---------------------------------------------------------------------------
LRESULT PSS_ProcessGraphModelView::OnAdviseStartPropertyEdition(WPARAM wParam, LPARAM lParam)
{
    PSS_ProcessGraphModelController* pModelCtrl = PSS_ProcessGraphModelViewport::GetModelController();

    if (pModelCtrl)
        pModelCtrl->OnStartEditProperty();

    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelView::OnToolTipNeedText(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
    TOOLTIPTEXT* pTTT = (TOOLTIPTEXT *)pNMHDR;
    pTTT->hinst       = NULL;

    CPoint cursorPos;
    VERIFY(::GetCursorPos(&cursorPos));
    ScreenToClient(&cursorPos);

    CRect ClientRect;
    GetClientRect(ClientRect);

    BOOL handledNotify = FALSE;

    // make certain that the cursor is in the client rect, because the mainframe also wants these messages
    // to provide tooltips for the toolbar
    if (pTTT->uFlags & TTF_IDISHWND && ClientRect.PtInRect(cursorPos))
    {
        m_StrToolTip.Empty();

        PSS_ProcessGraphModelController* pModelCtrl = PSS_ProcessGraphModelViewport::GetModelController();

        if (pModelCtrl && pModelCtrl->OnToolTip(m_StrToolTip,
                                                cursorPos,
                                                PSS_Global::GetType() == PSS_Global::IE_AT_Process ?
                                                        PSS_Symbol::IE_TT_Design :
                                                        PSS_Symbol::IE_TT_Normal))
        {
            pTTT->hinst    = NULL;
            pTTT->lpszText = m_StrToolTip.GetBuffer(m_StrToolTip.GetLength() + 1);
            handledNotify  = TRUE;
            TRACE((const char*)m_StrToolTip);
        }
    }

    return handledNotify;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelView::PreTranslateMessage(MSG* pMsg)
{
    // forward to tooltip
    if (::IsWindow(m_ToolTip.m_hWnd) && pMsg->hwnd == m_hWnd)
        switch (pMsg->message)
        {
            case WM_LBUTTONDOWN:
            case WM_MOUSEMOVE:
            case WM_LBUTTONUP:
            case WM_RBUTTONDOWN:
            case WM_MBUTTONDOWN:
            case WM_RBUTTONUP:
            case WM_MBUTTONUP:
                m_ToolTip.RelayEvent(pMsg);
                break;
        }

    // do follow
    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelView::InitializePanViewport()
{
    // create the pan viewport
    m_PanVp.SetModel(GetModel());
    m_PanVp.Create(m_pOverview, NULL);

    CRect clientRect;
    GetClientRect(&clientRect);
    m_PanVp.SetSize(clientRect.Width(), clientRect.Height());

    // hide the rulers
    m_PanVp.SetRulerVisible(odg_nHorizontalRuler, FALSE);
    m_PanVp.SetRulerVisible(odg_nVerticalRuler,   FALSE);
    m_PanVp.OnInitialUpdate();

    m_PanInitialized = true;

    UpdateOverviewRect();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelView::UpdateOverviewRect()
{
    ASSERT_VALID(this);

    // ok for m_pOverview to be NULL. Protect here, so callers don't have to take care of that
    if (!m_pOverview)
        return;

    SetRatio();

    CRect clientRect;
    GetClientRect(&clientRect);

    // BLOCK for DC
    clientRect.left   = static_cast<int>(double(clientRect.left)   * m_CurrentRatio);
    clientRect.top    = static_cast<int>(double(clientRect.top)    * m_CurrentRatio);
    clientRect.right  = static_cast<int>(double(clientRect.right)  * m_CurrentRatio);
    clientRect.bottom = static_cast<int>(double(clientRect.bottom) * m_CurrentRatio);

    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.DPtoLP(&clientRect);

    m_pOverview->SetPanRect(clientRect);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelView::PreOverview()
{
    m_InVirtualDraw = TRUE;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelView::PostOverview()
{
    m_InVirtualDraw = FALSE;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelView::SetRatio()
{
    // protect here, so callers don't have to take care of that
    if (!m_pOverview || !m_PanInitialized)
        return;

    CRect clientRect;

    // the overview window shows the entire view in it's borders, so setup the device size to
    // the client size
    m_pOverview->GetClientRect(&clientRect);
    ASSERT(!clientRect.top && !clientRect.left);

    CPoint point;

    // make sure that the overview looks just like the pan view derivative
    PersistRatio(m_totalLog, m_totalDev, point);

    const double ratioX = double(clientRect.right)  / double(m_totalDev.cx);
    const double ratioY = double(clientRect.bottom) / double(m_totalDev.cy);
    m_CurrentRatio      = __min(ratioX, ratioY);

    m_PanVp.SetMagnification(static_cast<int>(100.0 * m_CurrentRatio), static_cast<int>(100.0 * m_CurrentRatio));
}
//---------------------------------------------------------------------------
