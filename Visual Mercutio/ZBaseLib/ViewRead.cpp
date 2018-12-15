//## begin module%3620D873038F.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%3620D873038F.cm

//## begin module%3620D873038F.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%3620D873038F.cp

//## Module: ViewRead%3620D873038F; Package body
//## Subsystem: PlanFin%334FC46302B2
//## Source file: ViewRead.cpp

//## begin module%3620D873038F.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%3620D873038F.additionalIncludes

//## begin module%3620D873038F.includes preserve=yes
//## end module%3620D873038F.includes

// ViewRead
#include "ViewRead.h"
// DocData
#include "DocData.h"

//## begin module%3620D873038F.additionalDeclarations preserve=yes

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(ZIViewRead, ZIView)


BEGIN_MESSAGE_MAP(ZIViewRead, ZIView)
    //{{AFX_MSG_MAP(ZIViewRead)
    ON_WM_RBUTTONDOWN()
    ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomin)
    ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
    ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMIN, OnUpdateViewZoomin)
    ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMOUT, OnUpdateViewZoomout)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//## end module%3620D873038F.additionalDeclarations


// Class ZIViewRead 


ZIViewRead::ZIViewRead()
  //## begin ZIViewRead::ZIViewRead%.hasinit preserve=no
  //## end ZIViewRead::ZIViewRead%.hasinit
  //## begin ZIViewRead::ZIViewRead%.initialization preserve=yes
  //## end ZIViewRead::ZIViewRead%.initialization
{
  //## begin ZIViewRead::ZIViewRead%.body preserve=yes
    m_ViewType = FormReadView;
  //## end ZIViewRead::ZIViewRead%.body
}


ZIViewRead::~ZIViewRead()
{
  //## begin ZIViewRead::~ZIViewRead%.body preserve=yes
  //## end ZIViewRead::~ZIViewRead%.body
}

//## Other Operations (implementation)
void ZIViewRead::OnDraw (CDC* pDC)
{
  //## begin ZIViewRead::OnDraw%908122317.body preserve=yes
    ZDDocument*    pDoc = GetDocument();
    if (!pDoc || !pDoc->GetActiveDocumentData())
        return;
    ZDDocumentData*    pDocData = pDoc->GetActiveDocumentData();
    if (pDocData)
    {
        // Translate to absolute coordinates
        OnPrepareDC( pDC );
        if (pDC->IsPrinting() == FALSE)
            DrawPageRect( pDC );

        pDocData->OnDraw( pDC, this );
    }
  //## end ZIViewRead::OnDraw%908122317.body
}

void ZIViewRead::OnPrint (CDC* pDC, CPrintInfo* pInfo)
{
  //## begin ZIViewRead::OnPrint%908122321.body preserve=yes
    // Assign the current page
    GetDocument()->SetCurrentPage( pInfo->m_nCurPage );
    // Now print the page
    OnDraw(pDC);
  //## end ZIViewRead::OnPrint%908122321.body
}

BOOL ZIViewRead::OnPreparePrinting (CPrintInfo* pInfo)
{
  //## begin ZIViewRead::OnPreparePrinting%908122322.body preserve=yes
#ifdef _EVALUATION_VERSION
    if (!pInfo->m_bPreview)
        if (!ZAApp::ZAGetApp()->GetSecurity().Check())
        {
            ZAApp::ZAGetApp()->GetSecurity().DisplayStopWnd();
            return FALSE;
        }
#endif
    
    pInfo->SetMaxPage( GetDocument()->GetMaxPage() );
    return( DoPreparePrinting(pInfo) );
  //## end ZIViewRead::OnPreparePrinting%908122322.body
}

void ZIViewRead::OnBeginPrinting (CDC* pDC, CPrintInfo* pInfo)
{
  //## begin ZIViewRead::OnBeginPrinting%908122323.body preserve=yes
    // Save the current page before printing
    m_iSavePageForPrinting = GetDocument()->GetCurrentPage();
    SetLogicalCoordinates( pDC );
  //## end ZIViewRead::OnBeginPrinting%908122323.body
}

void ZIViewRead::OnEndPrinting (CDC* pDC, CPrintInfo* pInfo)
{
  //## begin ZIViewRead::OnEndPrinting%908122324.body preserve=yes
    // Put back the current page
    GetDocument()->SetCurrentPage( m_iSavePageForPrinting );
#ifdef _EVALUATION_VERSION
    // Increment the page only if is printing
    if (!pInfo->m_bPreview)
        ZAApp::ZAGetApp()->GetSecurity().IncrementCounter();
#endif
  //## end ZIViewRead::OnEndPrinting%908122324.body
}

BOOL ZIViewRead::PreTranslateMessage (MSG* pMsg)
{
  //## begin ZIViewRead::PreTranslateMessage%938177645.body preserve=yes

    // is it a message we want to process?
    // only coming from the view
    // (NOTE: we have to do old style mesage handling here)
    if (pMsg->hwnd == GetSafeHwnd() && pMsg->message == WM_KEYDOWN)
    {
        if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
        {
            // translate accelerators for frame and any children
            if (AfxGetMainWnd() && ((CFrameWnd*)AfxGetMainWnd())->m_hAccelTable != NULL &&
                ::TranslateAccelerator(((CFrameWnd*)AfxGetMainWnd())->GetSafeHwnd(), ((CFrameWnd*)AfxGetMainWnd())->m_hAccelTable, pMsg))
            {
                return TRUE;
            }
        }
        // Get selected object array
        CObArray&            ArrayOfSelectedObjects = GetArrayOfSelectedObject();
        if (ArrayOfSelectedObjects.GetSize() > 0)
        {
            CSize    ReportSize = GetReportPageSizeInPixels();
            CPoint    MovePointValue( 0, 0 );
            bool    MessageCaptured = true;
            switch (pMsg->wParam)
            {
                case VK_PRIOR:    // Page Up
                {
                    // 10 pixels up
                    MovePointValue.y -= 10;
                    break;
                }
                case VK_NEXT:    // Page Down
                {
                    // 10 pixels down
                    MovePointValue.y += 10;
                    break;
                }
                case VK_LEFT:
                {
                    // One pixel left
                    MovePointValue.x -= 1;
                    break;
                }
                case VK_RIGHT:
                {
                    // One pixel right
                    MovePointValue.x += 1;
                    break;
                }
                case VK_END:
                {
                    // 10 pixels right
                    MovePointValue.x += 10;
                    break;
                }
                case VK_HOME:
                {
                    // 10 pixels left
                    MovePointValue.x -= 10;
                    break;
                }
                case VK_UP:
                {
                    // One pixel up
                    MovePointValue.y -= 1;
                    break;
                }
                case VK_DOWN:
                {
                    // One pixel down
                    MovePointValue.y += 1;
                    break;
                }
                // Default do noting
                default: 
                {
                    MessageCaptured = false;
                    break;
                }
            }
            if (MessageCaptured == true)
            {
                for (int i=0; i < ArrayOfSelectedObjects.GetSize(); ++i)
                {
                    // Move all objects
                    ((PlanFinObject*)(ArrayOfSelectedObjects[i]))->MoveObject( MovePointValue );
                    KeepObjectInPage( ((PlanFinObject*)(ArrayOfSelectedObjects[i])), ReportSize );
                    ((PlanFinObject*)(ArrayOfSelectedObjects[i]))->SizePositionHasChanged();
                }
                RedrawWindow();
                // Document has been modified
                GetDocument()->SetModifiedFlag();
                // Message processed
                return TRUE;
            }
        }
        else
        {
            CPoint    CurrentPosition = GetScrollPosition();
            switch (pMsg->wParam)
            {
                case VK_PRIOR:    // Page Up
                {
                    CurrentPosition.y = __max( CurrentPosition.y - m_PageSize.cy, 0 );
                    ScrollToPosition( CurrentPosition );
                    return TRUE;
                }
                case VK_NEXT:    // Page Down
                {
                    CurrentPosition.y = __min( CurrentPosition.y + m_PageSize.cy, m_TotalSize.cy );
                    ScrollToPosition( CurrentPosition );
                    return TRUE;
                }
                case VK_LEFT:
                {
                    CurrentPosition.x = __max( CurrentPosition.x - m_LineSize.cx, 0 );
                    ScrollToPosition( CurrentPosition );
                    return TRUE;
                }
                case VK_RIGHT:
                {
                    CurrentPosition.x = __min( CurrentPosition.x + m_LineSize.cx, m_TotalSize.cx );
                    ScrollToPosition( CurrentPosition );
                    return TRUE;
                }
                case VK_END:
                {
                    CurrentPosition.x = m_TotalSize.cx;
                    ScrollToPosition( CurrentPosition );
                    return TRUE;
                }
                case VK_HOME:
                {
                    CurrentPosition.x = 0;
                    ScrollToPosition( CurrentPosition );
                    return TRUE;
                }
                case VK_UP:
                {
                    CurrentPosition.y = __max( CurrentPosition.y - m_LineSize.cy, 0 );
                    ScrollToPosition( CurrentPosition );
                    return TRUE;
                }
                case VK_DOWN:
                {
                    CurrentPosition.y = __min( CurrentPosition.y + m_LineSize.cy, m_TotalSize.cy );
                    ScrollToPosition( CurrentPosition );
                    return TRUE;
                }
                default: break;
            }
        }
    }    
    // Tooltip 
    if (::IsWindow(m_ToolTip.m_hWnd) && pMsg->hwnd == m_hWnd)
    {
        switch(pMsg->message)
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
    
    // not handled by us, only borrowed
    return FALSE;
  //## end ZIViewRead::PreTranslateMessage%938177645.body
}

// Additional Declarations
  //## begin ZIViewRead%3620D7FF0234.declarations preserve=yes


void ZIViewRead::OnRButtonDown(UINT nFlags, CPoint point)
{
    CPoint    pt(point);
    ReleaseCapture();
    // translate the point in logical coordinates
    CDC            *pDC = GetDC();
    ASSERT( pDC );
    OnPrepareDC( pDC );
    pDC->DPtoLP( &point );      
    VERIFY( ReleaseDC( pDC ) );
    // Display the context menu
    CMenu   *pMenu, DummyMenu;
    DummyMenu.LoadMenu( GetRightPopupMenuID() );
    ReleaseCapture();

    PlanFinObject*    SelectedObject;
    if ((SelectedObject=ActiveSelectedObject( point )))
        pMenu = DummyMenu.GetSubMenu( SelectedObject->GetRightSubMenu() );
    else
        pMenu = DummyMenu.GetSubMenu( OnPageRightSubMenu );
       if (pMenu)
       {
        ClientToScreen( &pt );
        pMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, AfxGetMainWnd() );
        SetCapture();
    }
    CScrollView::OnRButtonDown(nFlags, point);
}


void ZIViewRead::OnViewZoomin() 
{
    int CurrentZoom = GetZoomPercentage();
    CurrentZoom += 25;
    // Assign the new zoom percentage
    SetZoomPercentage( CurrentZoom );

    ((ZDDocument*)GetDocument())->UpdateAllViews( NULL );
}
void ZIViewRead::OnUpdateViewZoomin(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable( GetZoomPercentage()+25 <= 400 );
}


void ZIViewRead::OnViewZoomout() 
{
    int CurrentZoom = GetZoomPercentage();
    CurrentZoom -= 25;
    // Assign the new zoom percentage
    SetZoomPercentage( CurrentZoom );

    ((ZDDocument*)GetDocument())->UpdateAllViews( NULL );
}

void ZIViewRead::OnUpdateViewZoomout(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable( GetZoomPercentage()-25 >= 25 );
}

