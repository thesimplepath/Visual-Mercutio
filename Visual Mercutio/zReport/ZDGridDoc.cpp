// ZDGridDoc.cpp : implementation of the ZDGridDocument class

#include "stdafx.h"

#include "ZDGridDoc.h"
#include "ZVGridView.h"

#include "ZVGridChildFrm.h"
#include "ZCGridGroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 7 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZDGridDocument

GXIMPLEMENT_DYNCREATE( ZDGridDocument, CGXDocument )

BEGIN_MESSAGE_MAP( ZDGridDocument, CGXDocument )
    //{{AFX_MSG_MAP(ZDGridDocument)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZDGridDocument construction/destruction

ZDGridDocument::ZDGridDocument()
    : m_pParam            ( NULL ),
      m_FrozenRow        ( 0 ),
      m_FrozenCol        ( 0 ),
      m_FrozenHeaderRow    ( 0 ),
      m_FrozenHeaderCol    ( 0 )
{
}

ZDGridDocument::~ZDGridDocument()
{
    DeleteContents();
}

void ZDGridDocument::DeleteContents()
{
    RemoveAllGroupCtrl();

    if ( m_pParam )
    {
        delete m_pParam;
        m_pParam = NULL;
    }
}

bool ZDGridDocument::SetNewGridParamPtr( CGXGridParam* ptr )
{
    if ( ptr )
    {
        DeleteContents();
        m_pParam = ptr;

        return true;
    }

    return false;
}

CGXGridParam* ZDGridDocument::GetGridParam( size_t Index )
{
    ZDGridDocument* pDoc = GetDocumentAt( Index );
    return ( pDoc ) ? pDoc->GetGridParam() : NULL;
}

CGXTabCreateInfo* ZDGridDocument::GetTabCreateInfo( size_t Index )
{
    if ( Index >= GetGridTabCount() )
    {
        return NULL;
    }

    CGXTabWndMgr* pMgr = GetPrimaryDocument()->GetTabManager();
    
    if ( !pMgr )
    {
        return NULL;
    }

    CArray<CGXTabCreateInfo*, CGXTabCreateInfo*>* pTabInfoArray = pMgr->GetTabCreateInfoArray();

    return pTabInfoArray->GetAt( Index );
}

ZDGridDocument* ZDGridDocument::GetDocumentAt( size_t Index )
{
    CGXTabCreateInfo* pTabInfo = GetTabCreateInfo( Index );

    if ( !pTabInfo )
    {
        return NULL;
    }

    return ( pTabInfo->GetDocument() && ISA( pTabInfo->GetDocument(), ZDGridDocument ) ) ?
        dynamic_cast<ZDGridDocument*>( pTabInfo->GetDocument() ) : NULL;
}

size_t ZDGridDocument::GetGridTabCount()
{
    ASSERT( GetPrimaryDocument() );
    return (GetPrimaryDocument()->GetTabManager()) ? GetPrimaryDocument()->GetTabManager()->GetTabCount() : 0;
}

bool ZDGridDocument::DeleteGridTab( size_t Index /*= 0*/ )
{
    ASSERT( GetPrimaryDocument() );

    if ( GetPrimaryDocument()->GetTabManager() )
    {
        return ( GetPrimaryDocument()->GetTabManager()->DeleteWorkSheet( Index ) ) ? true : false;
    }

    return  false;
}

bool ZDGridDocument::_InsertNewGridTabAt( size_t Index /*= 0*/ )
{
    ZVGridView* pView = GetFirstView();

    ASSERT( pView );

    CFrameWnd* pWnd = pView->GetParentFrame();

    if ( !pWnd || !ISA( pWnd, ZVGridChildFrame ) )
    {
        return false;
    }

    dynamic_cast<ZVGridChildFrame*>( pWnd )->InsertWorkSheetHandler();

    return true;
}

CGXTabWnd* ZDGridDocument::GetTabWnd( size_t Index )
{
    ZDGridDocument* pDoc = GetDocumentAt( Index );

    if ( pDoc )
    {
        return ( pDoc->GetFirstView() ) ? pDoc->GetFirstView()->GetTabWnd() : NULL;
    }

    return NULL;
}

ZVGridView* ZDGridDocument::GetTabView( size_t Index )
{
    ZDGridDocument* pDoc = GetDocumentAt( Index );
    return ( pDoc ) ? pDoc->GetFirstView() : NULL;
}

CGXGridCore* ZDGridDocument::GetTabGridCore( size_t Index )
{
    return ZDGridDocument::GetTabView( Index );
}

ZVGridView* ZDGridDocument::GetFirstView()
{
    POSITION pos = GetFirstViewPosition();
    CView* pView = GetNextView( pos );

    while ( pView )
    {
        if ( ISA( pView, ZVGridView ) )
        {
            return (ZVGridView*)pView;
        }

        pView = GetNextView( pos );
    }

    return NULL;
}

const CString ZDGridDocument::GetTabName( size_t Index )
{
    if ( GetPrimaryDocument() == this )
    {
        CGXTabWnd* pTabWnd = GetTabWnd( Index );

        if ( !pTabWnd )
        {
            return _T( "" );
        }

        return pTabWnd->GetTabName( Index );
    }

    // Call the function from the primary document
    return ( GetPrimaryDocument() &&
             ISA( GetPrimaryDocument(), ZDGridDocument ) ) ?
                dynamic_cast<ZDGridDocument*>( GetPrimaryDocument() )->GetTabName( Index ) : _T( "" );
}

void ZDGridDocument::SetTabName( const CString Name, size_t Index )
{
    if ( GetPrimaryDocument() == this )
    {
        CGXTabWnd* pTabWnd = GetTabWnd( Index );

        if ( !pTabWnd )
        {
            return;
        }

        pTabWnd->SetTabName( Index, Name );
        return;
    }

    // Call the function from the primary document
    if ( GetPrimaryDocument() && ISA( GetPrimaryDocument(), ZDGridDocument ) )
    {
        dynamic_cast<ZDGridDocument*>( GetPrimaryDocument() )->SetTabName( Name, Index );
    }
}

void ZDGridDocument::SetPathName( LPCTSTR lpszPathName, BOOL bAddToMRU /*= TRUE*/ )
{
    CGXTabWndMgr* pMgr = ( GetPrimaryDocument() ) ? GetPrimaryDocument()->GetTabManager() : NULL;
    
    if ( pMgr )
    {
        // Retreive the tab create info pointer array
        CArray<CGXTabCreateInfo*, CGXTabCreateInfo*>* pTabInfoArray = pMgr->GetTabCreateInfoArray();

        // Retreive the size
        int Count = pTabInfoArray->GetSize();

        for ( int i = 0; i < Count; ++i )
        {
            CGXTabCreateInfo* pInfo = pTabInfoArray->GetAt( i );
            ASSERT( pInfo );

            if ( pInfo->GetDocument() )
            {
                dynamic_cast<ZDGridDocument*>( pInfo->GetDocument() )->_BaseClassSetPathName( lpszPathName, bAddToMRU );
            }
        }

        return;
    }

    CGXDocument::SetPathName( lpszPathName, bAddToMRU );
}

void ZDGridDocument::_BaseClassSetPathName( LPCTSTR lpszPathName, BOOL bAddToMRU /*= TRUE*/ )
{
    CGXDocument::SetPathName( lpszPathName, bAddToMRU );
}

void ZDGridDocument::RemoveAllGroupCtrl()
{
    // Sets the iterator to the right entity set
    ZCGridGroupIterator i(&m_GroupCtrlSet);

    for ( ZCGridGroup* pCtrl = i.GetFirst(); pCtrl != NULL; pCtrl = i.GetNext() )
    {
        delete pCtrl;
    }

    m_GroupCtrlSet.RemoveAll();
}

void ZDGridDocument::InsertGroupCtrl( ROWCOL        Row,
                                      ROWCOL        Col,
                                      int            CoveringCells,
                                      bool            Horizontal,
                                      bool            Collapsed,
                                      const CString    Label            /*= ""*/,
                                      const CString    ToolTipText        /*= ""*/ )
{
    ZVGridView* pView = GetFirstView();

    ZCGridGroup* pCtrl = new ZCGridGroup( pView,
                                          Row,
                                          Col,
                                          CoveringCells,
                                          Horizontal,
                                          Collapsed,
                                          Label,
                                          ToolTipText );

    m_GroupCtrlSet.Add( pCtrl );
}

ZCGridGroup* ZDGridDocument::FindGroupCtrl( ROWCOL Row, ROWCOL Col )
{
    ZCGridGroupIterator i( &m_GroupCtrlSet );

    for ( ZCGridGroup* pCtrl = i.GetFirst(); pCtrl != NULL; pCtrl = i.GetNext() )
    {
        if ( pCtrl->GetRow() == Row && pCtrl->GetCol() == Col )
        {
            return pCtrl;
        }
    }

    return NULL;
}

void ZDGridDocument::InitializeGroupControls( ZVGridView* pView )
{
    ZCGridGroupIterator i( &m_GroupCtrlSet );

    for ( ZCGridGroup* pCtrl = i.GetFirst(); pCtrl != NULL; pCtrl = i.GetNext() )
    {
        if ( pCtrl->GetGridCore() == NULL )
        {
            pCtrl->SetGridCore( pView );
            pCtrl->CreateControl();
        }
    }
}

BOOL ZDGridDocument::OnNewDocument()
{
    if ( !CGXDocument::OnNewDocument() )
    {
        return FALSE;
    }

    DeleteContents();
    SetModifiedFlag();

    return TRUE;
}

BOOL ZDGridDocument::UpdateFrameTitle()
{
    // Force the refresh of the active window title
    if ( AfxGetMainWnd() &&
         ISA( AfxGetMainWnd(), CFrameWnd ) &&
         dynamic_cast<CFrameWnd*>( AfxGetMainWnd() )->GetActiveFrame() )
    {
        dynamic_cast<CFrameWnd*>( AfxGetMainWnd() )->GetActiveFrame()->OnUpdateFrameTitle( TRUE );
        return TRUE;
    }

    return FALSE;
}

BOOL ZDGridDocument::OnOpenDocument( LPCTSTR pszPathName )
{
    CGXGridParam* pParam = m_pParam;
    m_pParam = NULL;

    if ( !CGXDocument::OnOpenDocument( pszPathName ) )
    {
        SetModifiedFlag( FALSE );
        m_pParam = pParam;
        return FALSE;
    }

    delete pParam;

    return TRUE;
}

BOOL ZDGridDocument::OnSaveDocument( LPCTSTR pszPathName )
{
    // Ensure that each views current cell is stored
    CGXGridHint hint( gxHintTransferCurrentCell );
    hint.lParam = TRUE;

    UpdateAllViews( NULL, 0, &hint );

    // Now, you can save the document
    if ( !CGXDocument::OnSaveDocument( pszPathName ) )
    {
        return FALSE;
    }

    SetModifiedFlag( FALSE );

    return TRUE;
}

BOOL ZDGridDocument::SaveModified()
{
    POSITION pos = GetFirstViewPosition();

    while ( pos != NULL )
    {
        CView* pView = GetNextView( pos );
        ASSERT_VALID( pView );

        if ( !CanExitGridView( pView ) )
        {
            CMDIChildWnd* pFrame = ( (CMDIChildWnd*)pView->GetParentFrame() );

            if ( pFrame && pFrame->IsKindOf( RUNTIME_CLASS( CMDIChildWnd ) ) )
            {
                pFrame->MDIActivate();
            }

            return FALSE;
        }
    }

    return CDocument::SaveModified();
}

BOOL ZDGridDocument::CanCloseFrame( CFrameWnd* pFrame )
{
    // Ensure that views can be deactivated
    CView* pView = pFrame->GetActiveView();

    if ( pView && !CanExitGridView( pView ) )
    {
        return FALSE;
    }

    // Now, I can close the view
    return CDocument::CanCloseFrame( pFrame );
}

BOOL ZDGridDocument::CanExitGridView( CView* pView )
{
    if ( pView && pView->SendMessage( WM_GX_CANACTIVATE, 0, 0 ) )
    {
        return FALSE;
    }

    // Is it a grid?
    CGXGridCore* pGrid = NULL;

    if ( pView->IsKindOf( RUNTIME_CLASS( CGXGridView ) ) )
    {
        pGrid = (CGXGridCore*)( (CGXGridView*) pView );
    }
    else if ( pView->IsKindOf( RUNTIME_CLASS( CGXGridHandleView ) ) )
    {
        pGrid = ( (CGXGridHandleView*) pView )->GetGrid();
    }

    if ( pGrid )
    {
        // Ensure that the current cell can be stored
        if ( !pGrid->TransferCurrentCell( TRUE, GX_UPDATENOW, FALSE ) )
        {
            // grid state is invalid, don't close the frame
            return FALSE;
        }
    }

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// ZDGridDocument diagnostics

#ifdef _DEBUG
void ZDGridDocument::AssertValid() const
{
    CGXDocument::AssertValid();
}

void ZDGridDocument::Dump( CDumpContext& dc ) const
{
    CGXDocument::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZDGridDocument serialization

void ZDGridDocument::WorkBookSerialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        ar << m_pParam;
        ar << m_FrozenRow;
        ar << m_FrozenCol;
        ar << m_FrozenHeaderRow;
        ar << m_FrozenHeaderCol;

        ar << static_cast<int>( m_GroupCtrlSet.GetSize() );

        ZCGridGroupIterator i( &m_GroupCtrlSet );

        for ( ZCGridGroup* pCtrl = i.GetFirst(); pCtrl != NULL; pCtrl = i.GetNext() )
        {
            ar << pCtrl;
        }
    }
    else
    {
        ar >> m_pParam;
        ar >> m_FrozenRow;
        ar >> m_FrozenCol;
        ar >> m_FrozenHeaderRow;
        ar >> m_FrozenHeaderCol;

        // Before reading elements, remove all
        RemoveAllGroupCtrl();
        
        int nCount;
        ZCGridGroup* pCtrl;

        ar >> nCount;

        for ( int i=0; i<nCount; i++ )
        {
            ar >> pCtrl;
            m_GroupCtrlSet.Add( pCtrl );
        }
    }
}
