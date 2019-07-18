// ProcGraphChildFrm.cpp : implementation of the ZIProcessGraphChildFrame class

#include "StdAfx.h"
#include "ProcGraphChildFrm.h"

#include "zResMgr\PSS_ResourceManager.h"
#include "zBaseLib\ZUFloatingToolbar.h"
#include "zBaseLib\ZBDocumentObserverMsg.h"
#include "ProcGraphModelDoc.h"
#include "ProcGraphModelView.h"
#include "ZDProcessGraphPage.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 28 septembre 2005 - Ajout des décorations unicode _T( ), nettoyage du code non utilisé.

CDocument* ZIProcessGraphChildFrame::m_pLastDocumentActivated = NULL;

/////////////////////////////////////////////////////////////////////////////
// ZIProcessGraphChildFrame

IMPLEMENT_DYNCREATE( ZIProcessGraphChildFrame, SECMDIChildWnd )

BEGIN_MESSAGE_MAP( ZIProcessGraphChildFrame, SECMDIChildWnd )
    //{{AFX_MSG_MAP(ZIProcessGraphChildFrame)
    ON_WM_MDIACTIVATE()
    ON_WM_MOUSEACTIVATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIProcessGraphChildFrame construction/destruction

ZIProcessGraphChildFrame::ZIProcessGraphChildFrame()
{
}

ZIProcessGraphChildFrame::~ZIProcessGraphChildFrame()
{
}

BOOL ZIProcessGraphChildFrame::PreCreateWindow( CREATESTRUCT& cs )
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    if( !SECMDIChildWnd::PreCreateWindow( cs ) )
    {
        return FALSE;
    }

    return TRUE;
}

//////////////////
// Override to change the model title.
//
void ZIProcessGraphChildFrame::OnUpdateFrameTitle( BOOL bAddToTitle )
{
    SECMDIChildWnd::OnUpdateFrameTitle( bAddToTitle );
    CDocument* pDoc = GetActiveDocument();

    if ( pDoc && ISA( pDoc, ZDProcessGraphModelDoc ) )
    {
        CView* pView = GetActiveView();

        if ( pView && ISA( pView, ZIProcessGraphModelView ) )
        {
            // JMR-MODIF - Le 29 septembre 2005 - Si le document est en cours de fermeture, abandonne l'opération.
            if ( dynamic_cast<ZDProcessGraphModelDoc*>( pDoc )->IsClosing() == FALSE )
            {
                if ( !( (ZIProcessGraphModelView*)pView )->GetModel()->GetAbsolutePath().IsEmpty() )
                {
                    CString WndText = ( (ZIProcessGraphModelView*)pView )->GetModel()->GetAbsolutePath();

                    // If has a page set, add the page name
                    if ( ( (ZIProcessGraphModelView*)pView )->GetModel()->HasPageSet() )
                    {
                        ZDProcessGraphPage* pPage =
                            ( (ZIProcessGraphModelView*)pView )->GetModel()->FindModelPage( ( (ZIProcessGraphModelView*)pView )->GetModel() );

                        if ( pPage )
                        {
                            WndText += _T( "[" ) + pPage->GetPageName() + _T( "]" );
                        }
                    }

                    SetWindowText( WndText );
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZIProcessGraphChildFrame diagnostics

#ifdef _DEBUG
void ZIProcessGraphChildFrame::AssertValid() const
{
    SECMDIChildWnd::AssertValid();
}

void ZIProcessGraphChildFrame::Dump( CDumpContext& dc ) const
{
    SECMDIChildWnd::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZIProcessGraphChildFrame message handlers

void ZIProcessGraphChildFrame::OnMDIActivate( BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd )
{
    SECMDIChildWnd::OnMDIActivate( bActivate, pActivateWnd, pDeactivateWnd );
    
    if ( m_pLastDocumentActivated && m_pLastDocumentActivated != GetActiveDocument() )
    {
        AfxGetMainWnd()->SendMessageToDescendants( UM_DOCUMENTHASBEENSELECTED, 0, (LPARAM)GetActiveDocument() );
    }

    m_pLastDocumentActivated = GetActiveDocument();

    if ( m_pLastDocumentActivated && ISA( m_pLastDocumentActivated, ZDProcessGraphModelDoc ) )
    {
        // Switch the context
        ZUFloatingToolbar::SwitchContext( dynamic_cast<ZDProcessGraphModelDoc*>( m_pLastDocumentActivated )->GetModel()->GetNotation() );

        // Request the change of the resource language
        PSS_ResourceManager::ChangeLanguage( dynamic_cast<ZDProcessGraphModelDoc*>( m_pLastDocumentActivated )->GetLanguage() );

        // Notify all document's observers about the frame activation
        ZBDocumentObserverMsg Msg( UM_FRAMEHASBEENACTIVATED,
                                   m_pLastDocumentActivated,
                                   GetActiveView() );

        dynamic_cast<ZDProcessGraphModelDoc*>( m_pLastDocumentActivated )->NotifyAllObservers( &Msg );
    }
}

int ZIProcessGraphChildFrame::OnMouseActivate( CWnd* pDesktopWnd, UINT nHitTest, UINT message )
{
    int nResult = SECMDIChildWnd::OnMouseActivate( pDesktopWnd, nHitTest, message );

    if ( m_pLastDocumentActivated && ISA( m_pLastDocumentActivated, ZDProcessGraphModelDoc ) )
    {
        // Switch the context
        ZUFloatingToolbar::SwitchContext( dynamic_cast<ZDProcessGraphModelDoc*>( m_pLastDocumentActivated )->GetModel()->GetNotation() );

        // Request the change of the resource language
        PSS_ResourceManager::ChangeLanguage( dynamic_cast<ZDProcessGraphModelDoc*>( m_pLastDocumentActivated )->GetLanguage() );

        // Notify all document's observers about the frame activation
        ZBDocumentObserverMsg Msg( UM_FRAMEHASBEENACTIVATED,
                                   m_pLastDocumentActivated,
                                   GetActiveView() );

        dynamic_cast<ZDProcessGraphModelDoc*>( m_pLastDocumentActivated )->NotifyAllObservers( &Msg );
    }

    return nResult;
}
