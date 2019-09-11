/****************************************************************************
 * ==> PSS_ReadView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a read view                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_ReadView.h"

// processsoft
#include "PSS_DocumentData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_ReadView, ZIView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ReadView, ZIView)
    //{{AFX_MSG_MAP(PSS_ReadView)
    ON_WM_RBUTTONDOWN()
    ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomIn)
    ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomOut)
    ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMIN, OnUpdateViewZoomIn)
    ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMOUT, OnUpdateViewZoomOut)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ReadView
//---------------------------------------------------------------------------
PSS_ReadView::PSS_ReadView() :
    ZIView(),
    m_SavePageForPrinting(0)
{
    m_ViewType = FormReadView;
}
//---------------------------------------------------------------------------
PSS_ReadView::PSS_ReadView(const PSS_ReadView& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_ReadView::~PSS_ReadView()
{}
//---------------------------------------------------------------------------
const PSS_ReadView& PSS_ReadView::operator = (const PSS_ReadView& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_ReadView::OnDraw(CDC* pDC)
{
    ZDDocument* pDoc = GetDocument();

    if (!pDoc || !pDoc->GetActiveDocumentData())
        return;

    PSS_DocumentData* pDocData = pDoc->GetActiveDocumentData();

    if (pDocData)
    {
        // translate to absolute coordinates
        OnPrepareDC(pDC);

        if (!pDC->IsPrinting())
            DrawPageRect(pDC);

        pDocData->OnDraw(pDC, this);
    }
}
//---------------------------------------------------------------------------
void PSS_ReadView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
    // set the current page
    GetDocument()->SetCurrentPage(pInfo->m_nCurPage);

    // print the page
    OnDraw(pDC);
}
//---------------------------------------------------------------------------
BOOL PSS_ReadView::OnPreparePrinting(CPrintInfo* pInfo)
{
    #ifdef _EVALUATION_VERSION
        if (!pInfo->m_bPreview)
            if (!ZAApp::ZAGetApp()->GetSecurity().Check())
            {
                ZAApp::ZAGetApp()->GetSecurity().DisplayStopWnd();
                return FALSE;
            }
    #endif

    pInfo->SetMaxPage(GetDocument()->GetMaxPage());
    return(DoPreparePrinting(pInfo));
}
//---------------------------------------------------------------------------
void PSS_ReadView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    // save the current page before printing
    m_SavePageForPrinting = GetDocument()->GetCurrentPage();
    SetLogicalCoordinates(pDC);
}
//---------------------------------------------------------------------------
void PSS_ReadView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    // put back the current page
    GetDocument()->SetCurrentPage(m_SavePageForPrinting);

    #ifdef _EVALUATION_VERSION
        // increment the page only if is printing
        if (!pInfo->m_bPreview)
            ZAApp::ZAGetApp()->GetSecurity().IncrementCounter();
    #endif
}
//---------------------------------------------------------------------------
BOOL PSS_ReadView::PreTranslateMessage(MSG* pMsg)
{
    // do process a message? Only coming from the view. NOTE the old style mesage handling should be processed here
    if (pMsg->hwnd == GetSafeHwnd() && pMsg->message == WM_KEYDOWN)
    {
        if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
        {
            CFrameWnd* pFrameWnd = (CFrameWnd*)AfxGetMainWnd();

            // translate accelerators for frame and any children
            if (pFrameWnd                &&
                pFrameWnd->m_hAccelTable &&
                ::TranslateAccelerator(pFrameWnd->GetSafeHwnd(), pFrameWnd->m_hAccelTable, pMsg))
                return TRUE;
        }

        // get selected object array
        CObArray& selectedObjectArray = GetArrayOfSelectedObject();

        if (selectedObjectArray.GetSize() > 0)
        {
            CSize  reportSize = GetReportPageSizeInPixels();
            CPoint movePointValue(0, 0);
            bool   messageCaptured = true;

            switch (pMsg->wParam)
            {
                case VK_PRIOR: movePointValue.y -= 10;    break;
                case VK_NEXT:  movePointValue.y += 10;    break;
                case VK_LEFT:  movePointValue.x -= 1;     break;
                case VK_RIGHT: movePointValue.x += 1;     break;
                case VK_END:   movePointValue.x += 10;    break;
                case VK_HOME:  movePointValue.x -= 10;    break;
                case VK_UP:    movePointValue.y -= 1;     break;
                case VK_DOWN:  movePointValue.y += 1;     break;
                default:       messageCaptured   = false; break;
            }

            if (messageCaptured)
            {
                const int arraySize = selectedObjectArray.GetSize();

                for (int i = 0; i < arraySize; ++i)
                {
                    PSS_PlanFinObject* pObject = (PSS_PlanFinObject*)selectedObjectArray[i];

                    // move all objects
                    pObject->MoveObject(movePointValue);
                    KeepObjectInPage(pObject, reportSize);
                    pObject->SizePositionHasChanged();
                }

                RedrawWindow();

                // document has been modified
                GetDocument()->SetModifiedFlag();

                // message processed
                return TRUE;
            }
        }
        else
        {
            CPoint currentPosition = GetScrollPosition();

            switch (pMsg->wParam)
            {
                case VK_PRIOR:
                {
                    currentPosition.y = __max(currentPosition.y - m_PageSize.cy, 0);
                    ScrollToPosition(currentPosition);
                    return TRUE;
                }

                case VK_NEXT:
                {
                    currentPosition.y = __min(currentPosition.y + m_PageSize.cy, m_TotalSize.cy);
                    ScrollToPosition(currentPosition);
                    return TRUE;
                }

                case VK_LEFT:
                {
                    currentPosition.x = __max(currentPosition.x - m_LineSize.cx, 0);
                    ScrollToPosition(currentPosition);
                    return TRUE;
                }

                case VK_RIGHT:
                {
                    currentPosition.x = __min(currentPosition.x + m_LineSize.cx, m_TotalSize.cx);
                    ScrollToPosition(currentPosition);
                    return TRUE;
                }

                case VK_END:
                {
                    currentPosition.x = m_TotalSize.cx;
                    ScrollToPosition(currentPosition);
                    return TRUE;
                }

                case VK_HOME:
                {
                    currentPosition.x = 0;
                    ScrollToPosition(currentPosition);
                    return TRUE;
                }

                case VK_UP:
                {
                    currentPosition.y = __max(currentPosition.y - m_LineSize.cy, 0);
                    ScrollToPosition(currentPosition);
                    return TRUE;
                }

                case VK_DOWN:
                {
                    currentPosition.y = __min(currentPosition.y + m_LineSize.cy, m_TotalSize.cy);
                    ScrollToPosition(currentPosition);
                    return TRUE;
                }

                default:
                    break;
            }
        }
    }

    // tooltip 
    if (::IsWindow(m_ToolTip.m_hWnd) && pMsg->hwnd == m_hWnd)
    {
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
    }

    // not handled, only borrowed
    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_ReadView::OnRButtonDown(UINT nFlags, CPoint point)
{
    CPoint pt(point);
    ReleaseCapture();

    CDC* pDC = GetDC();
    ASSERT(pDC);
    OnPrepareDC(pDC);

    // translate the point in logical coordinates
    pDC->DPtoLP(&point);
    VERIFY(ReleaseDC(pDC));

    // show the context menu
    CMenu* pMenu, dummyMenu;
    dummyMenu.LoadMenu(GetRightPopupMenuID());
    ReleaseCapture();

    PSS_PlanFinObject* pSelectedObject;

    if ((pSelectedObject = ActiveSelectedObject(point)))
        pMenu = dummyMenu.GetSubMenu(pSelectedObject->GetRightSubMenu());
    else
        pMenu = dummyMenu.GetSubMenu(g_OnPageRightSubMenu);

    if (pMenu)
    {
        ClientToScreen(&pt);
        pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, AfxGetMainWnd());
        SetCapture();
    }

    CScrollView::OnRButtonDown(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_ReadView::OnViewZoomIn()
{
    const int currentZoom = GetZoomPercentage() + 25;

    // set the new zoom percentage
    SetZoomPercentage(currentZoom);

    ((ZDDocument*)GetDocument())->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
void PSS_ReadView::OnViewZoomOut()
{
    const int currentZoom = GetZoomPercentage() - 25;

    // set the new zoom percentage
    SetZoomPercentage(currentZoom);

    ((ZDDocument*)GetDocument())->UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
void PSS_ReadView::OnUpdateViewZoomIn(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetZoomPercentage() + 25 <= 400);
}
//---------------------------------------------------------------------------
void PSS_ReadView::OnUpdateViewZoomOut(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetZoomPercentage() - 25 >= 25);
}
//---------------------------------------------------------------------------
