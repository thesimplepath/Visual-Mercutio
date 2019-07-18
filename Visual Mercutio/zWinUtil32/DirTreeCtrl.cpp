// DirTreeCtrl.cpp : implementation file

#include "stdafx.h"
#include "shlobj.h"

// processsoft
#include "DirTreeCtrl.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

#define NETWORK_NEIGHBOUR _T("Network Neighborhood")

/////////////////////////////////////////////////////////////////////////////
//Handy local functions.
TCHAR*    MakeObjectDynamic    ( LPTSTR szData );
CString    WindowName            ( CString sName );
bool    ParsePath            ( CString sPath, int nLevel, CString *const psDirName );

/////////////////////////////////////////////////////////////////////////////
// ZIDirTreeCtrl

BEGIN_MESSAGE_MAP( ZIDirTreeCtrl, ZITreeCtrl )
    //{{AFX_MSG_MAP(ZIDirTreeCtrl)
    ON_NOTIFY_REFLECT_EX(TVN_SELCHANGED, OnSelchangedTree)
    ON_NOTIFY_REFLECT_EX(TVN_ITEMEXPANDING, OnItemexpandingTree)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZIDirTreeCtrl::ZIDirTreeCtrl( bool IncludeFile /*= false*/ )
    : m_IsValid                ( false ),
      m_IncludeFile            ( IncludeFile ),
      m_HasBeenInitialized    ( false )
{
}

ZIDirTreeCtrl::~ZIDirTreeCtrl()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZIDirTreeCtrl message handlers

void ZIDirTreeCtrl::Initialize( const CString InitialPath, bool clear, bool IncludeFile )
{
    if ( !m_HasBeenInitialized )
    {
        // Sets styles
        HasButtons();
        HasLines();
        LinesAtRoot();

        //Setup the Image lists
        if( !m_ImageListTree.Create( IDB_FILE_TYPES, 17, 1, RGB( 255, 255, 255 ) ) )
        {
            TRACE( _T( "Image list creation fault" ) );
        }

        SetImageList( &m_ImageListTree, TVSIL_NORMAL );
        m_HasBeenInitialized = true;
    }

    // Assigns variable
    m_IncludeFile = IncludeFile;

    ZIDirTreeCtrl::Refresh();

    if ( !InitialPath.IsEmpty() )
    {
        SetPath( InitialPath );
    }
}

void ZIDirTreeCtrl::Refresh()
{
    // JMR-MODIF - Le 31 août 2005 - On nettoie les ressources courantes avant d'en initialiser des nouvelles.
    EmptyNetRessources();

    // First, delete all items
    DeleteAllItems();

    //List the local drives
    for ( TCHAR cLetter = _T( 'A' ); cLetter <= _T( 'Z' ); cLetter++ )
    {
        CString sDrive     = cLetter;
        sDrive            += _T( ":\\" );
        UINT    nType     = GetDriveType( sDrive );

        switch( nType )
        {
            case DRIVE_REMOVABLE:
            case DRIVE_FIXED:
            case DRIVE_REMOTE:
            case DRIVE_CDROM:
            case DRIVE_RAMDISK:
            {
                sDrive = cLetter;
                sDrive += _T( ':' );
                InsertPathItem( TVI_ROOT, NULL, sDrive, sDrive, nType );
                break;
            }

            case DRIVE_UNKNOWN:
            case DRIVE_NO_ROOT_DIR:
            default:
            {
                break;
            }
        }
    }

    //Network neighbour hood
    m_hNetworkRoot = InsertPathItem( TVI_ROOT, NULL, NETWORK_NEIGHBOUR, NETWORK_NEIGHBOUR, DRIVE_RAMDISK + 1 );
}

void ZIDirTreeCtrl::SetPath( const CString Path )
{
    m_sPath = Path;

    if ( m_sPath.IsEmpty() )
    {
        return;
    }

    //Expand the Tree to the Inital Path.
    //
    int            nLevel        = 0;
    CString        sDirName;
    HTREEITEM    hCurrent    = TVI_ROOT;                    //Current item in the list being expanded.

    while ( ParsePath( m_sPath, nLevel, &sDirName ) )
    {
        //Network or Drive expand
        if ( !nLevel && sDirName.IsEmpty() )
        {
            sDirName = NETWORK_NEIGHBOUR;
        }

        //Search for the matching tree item and expand
        HTREEITEM hItem = GetChildItem( hCurrent );

        while ( hItem )
        {
            if ( sDirName.CompareNoCase( GetItemText( hItem ) ) == 0 )
            {
                hCurrent = hItem;
                Expand( hCurrent, TVE_EXPAND );
                break;
            }

            hItem = GetNextSiblingItem( hItem );
        }

        nLevel++;
    }
}

int ZIDirTreeCtrl::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
    if ( ZITreeCtrl::OnCreate( lpCreateStruct ) == -1 )
    {
        return -1;
    }
    
    Initialize();
    
    return 0;
}

HTREEITEM ZIDirTreeCtrl::InsertPathItem( HTREEITEM        hParent,
                                         NETRESOURCE*    pNetResource,
                                         CString        sText,
                                         CString        FullName,
                                         int            iImage,
                                         int            iImageSelected /* = -1 */ )
{
    TRACE( _T( "ZIDirTreeCtrl::InsertPathItem(%p,%p,%s +++ )\n" ), hParent, pNetResource, sText );

    sText = WindowName( sText );

    TVINSERTSTRUCT InsertStruct;

    InsertStruct.hParent            = hParent;
    InsertStruct.hInsertAfter        = TVI_LAST;
    InsertStruct.itemex.mask        = TVIF_IMAGE | TVIF_TEXT | TVIF_CHILDREN | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    InsertStruct.itemex.pszText        = sText.GetBuffer( sText.GetLength() );
    sText.ReleaseBuffer();
    InsertStruct.itemex.iImage        = iImage;
    InsertStruct.itemex.cChildren    = 1;
    InsertStruct.itemex.lParam        = (LPARAM) new ZNetResourceWrapper( FullName, pNetResource, true );

    if( iImageSelected == -1 )
    {
        InsertStruct.itemex.iSelectedImage = iImage;
    }
    else
    {
        InsertStruct.itemex.iSelectedImage = iImageSelected;
    }

    return InsertItem( &InsertStruct );
}

HTREEITEM ZIDirTreeCtrl::InsertFileItem( HTREEITEM        hParent,
                                         NETRESOURCE*    pNetResource,
                                         CString        sText,
                                         CString        FullName,
                                         int            iImage,
                                         int            iImageSelected /* = -1 */ )
{
    TRACE( _T( "ZIDirTreeCtrl::InsertFileItem(%p,%p,%s +++ )\n" ), hParent, pNetResource, sText );

    sText = WindowName( sText );

    TVINSERTSTRUCT InsertStruct;

    InsertStruct.hParent        = hParent;
    InsertStruct.hInsertAfter    = TVI_LAST;
    InsertStruct.itemex.mask    = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    InsertStruct.itemex.pszText    = sText.GetBuffer( sText.GetLength() );
    sText.ReleaseBuffer();
    InsertStruct.itemex.iImage    = iImage;
    InsertStruct.itemex.lParam    = (LPARAM)new ZNetResourceWrapper( FullName, pNetResource, false );

    if( iImageSelected == -1 )
    {
        InsertStruct.itemex.iSelectedImage = iImage;
    }
    else
    {
        InsertStruct.itemex.iSelectedImage = iImageSelected;
    }

    return InsertItem( &InsertStruct );
}

bool ZIDirTreeCtrl::PopulateTree( CString sPath, HTREEITEM hParent )
{
    TRACE( _T( "ZIDirTreeCtrl::PopulateTree( %s )\n" ), sPath );

    // True if a child is added.
    bool bGotChildren = false;

    // Populate Network neighbourhood tree (Entire network and Local-Computers)
    if ( hParent == m_hNetworkRoot )
    {
        bGotChildren = EnumNetwork( hParent );
    }
    else if ( GetItemData( hParent ) && ( (ZNetResourceWrapper*)( GetItemData( hParent ) ) )->GetNetResource() )
    {
        // Network item (Search deep into the network)
        bGotChildren = EnumNetwork( hParent );
    }
    else
    {
        // Search for files and populate the CTreeCtrl
        CFileFind finder;
        BOOL bWorking = finder.FindFile( sPath + _T( "*.*" ) );
        
        while ( bWorking )
        {
            bWorking = finder.FindNextFile();

            if( finder.IsDots() )
            {
                continue;
            }

            if( finder.IsDirectory() )
            {
                InsertPathItem( hParent,
                                NULL,
                                finder.GetFileName(),
                                finder.GetFilePath(),
                                DRIVE_NO_ROOT_DIR,
                                DRIVE_UNKNOWN );

                bGotChildren = true;
            }
            else if ( m_IncludeFile )
            {
                InsertFileItem( hParent,
                                NULL,
                                finder.GetFileName(),
                                finder.GetFilePath(),
                                DRIVE_RAMDISK + 2,
                                DRIVE_RAMDISK + 2 );
            }
        }
    }

    //Remove the [+] if no children
    if( !bGotChildren )
    {
        TVITEM item        = { 0 };
        item.mask        = TVIF_HANDLE | TVIF_CHILDREN;
        item.hItem        = hParent;
        item.cChildren    = 0;
        SetItem( &item );
    }

    return bGotChildren;
}

CString ZIDirTreeCtrl::GetItemPath( HTREEITEM hItem )
{
    TRACE( _T( "ZIDirTreeCtrl::GetItemPath(%p)\n" ), hItem );
    CString sRet;

    do
    {
        //End with a share name.
        NETRESOURCE* pNetResource = ( (ZNetResourceWrapper*)( GetItemData( hItem ) ) )->GetNetResource();

        if( pNetResource )
        {
            sRet = CString( pNetResource->lpRemoteName ) + _T( '\\' ) + sRet;
            break;
        }

        //Add the directory name to the path.
        sRet = GetItemText( hItem ) + _T( '\\' ) + sRet;
        hItem = GetParentItem( hItem );
    }
    while( hItem );

    return sRet;
}

BOOL ZIDirTreeCtrl::OnItemexpandingTree( NMHDR* pNMHDR, LRESULT* pResult )
{
    TRACE( _T( "ZIDirTreeCtrl::OnItemexpandingTree(%p)\n" ), pNMHDR );

    // Show the wait cursor while expanding
    CWaitCursor CursorWaiting;

    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    //Only action 2 notifications
    if ( pNMTreeView->action == 2 )
    {
        //Update location display
        CString sPath = GetItemPath( pNMTreeView->itemNew.hItem );

        //Refresh children
        if ( !GetChildItem( pNMTreeView->itemNew.hItem ) )
        {
            PopulateTree( sPath, pNMTreeView->itemNew.hItem );

            if( GetSelectedItem() != pNMTreeView->itemNew.hItem )
            {
                SelectItem( pNMTreeView->itemNew.hItem );
            }
        }
    }

    *pResult = 0;

    // Keep routing
    return TRUE;
}

BOOL ZIDirTreeCtrl::OnSelchangedTree( NMHDR* pNMHDR, LRESULT* pResult )
{
    TRACE( _T( "CDlgGetPath::OnSelchangedTree(%p)\n" ), pNMHDR );
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    //Disable search on Workstation roots
    if ( (GetItemData( pNMTreeView->itemNew.hItem ) &&
         ( (ZNetResourceWrapper*)( GetItemData( pNMTreeView->itemNew.hItem ) ) )->GetNetResource() ) ||
         pNMTreeView->itemNew.hItem == m_hNetworkRoot )
    {
        m_IsValid = false;
    }
    else
    {
        m_IsValid = true;
    }

    *pResult = 0;

    // Keep routing
    return TRUE;
}

TCHAR* MakeObjectDynamic( LPTSTR szData )
{
    TRACE( _T( "MakeObjectDynamic( %s )\n" ), szData );

    //Assume a NULL empty string
    TCHAR * szRet    = NULL;
    int nLength        = 0;

    if( szData )
    {
        nLength = _tcslen( szData ) + 1;
    }

    if( nLength > 0 )
    {
        szRet = new TCHAR[nLength];
        _tcscpy( szRet, szData );
    }

    return szRet;
}

CString WindowName( CString sName )
{
    CString sRet;

    //Scan all charactors to determine if their are any lower case items
    for( int n = 0; n < sName.GetLength(); n++ )
    {
        TCHAR ch = sName[n];

        if ( ( ch >= _T( 'a' ) ) && ( ch <= _T( 'z' ) ) )
        {
            return sName;
        }
    }

    sName.MakeLower();

    if( sName.GetLength() > 0 )
    {
        CString sFirstChar = sName[0];
        sFirstChar.MakeUpper();
        sName = sFirstChar + sName.Mid( 1 );
    }

    return sName;
}

bool ParsePath( CString sPath, int nLevel, CString *const psDirName )
{
    //find first match. Location in sPath to search from
    int nStart = 0;

    while( nLevel )
    {
        nStart = sPath.Find( _T( '\\' ), nStart );

        if( nStart < 0 )
        {
            return false;
        }

        nLevel--;
        nStart++;
    }

    //We now have the start point to find the end.
    int nEnd = sPath.Find( _T( '\\' ), nStart );

    if( nEnd < 0 )
    {
        *psDirName = sPath.Mid( nStart );
    }
    else
    {
        *psDirName = sPath.Mid( nStart, nEnd - nStart );
    }

    return true;
}

bool ZIDirTreeCtrl::EnumNetwork( HTREEITEM hParent )
{
    TRACE( _T( "ZIDirTreeCtrl::EnumNetwork( %p )\n" ), hParent );

    // True if a child is added.
    bool bGotChildren = false;

    //Check if the item already has a network resource and use it.
    NETRESOURCE* pNetResource = ( (ZNetResourceWrapper*)( GetItemData( hParent ) ) )->GetNetResource();

    //Setup
    DWORD dwResult;
    HANDLE hEnum;
    DWORD cbBuffer = 16384;
    DWORD cEntries = 0xFFFFFFFF;
    LPNETRESOURCE lpnrDrv;
    DWORD i;

    dwResult = WNetOpenEnum( pNetResource ? RESOURCE_GLOBALNET : RESOURCE_CONTEXT,
                             RESOURCETYPE_ANY,
                             0,
                             pNetResource ? pNetResource : NULL,
                             &hEnum );

    //Was the read sucessfull
    if ( dwResult != NO_ERROR )
    {
        TRACE( _T( "*** ERROR %d - Cannot enumerate network drives.\n" ), dwResult );
        return false;
    }
    
    //Get items until no more remain.
    do
    {
        lpnrDrv        = (LPNETRESOURCE) GlobalAlloc( GPTR, cbBuffer );
        dwResult    = WNetEnumResource( hEnum, &cEntries, lpnrDrv, &cbBuffer );

        if ( dwResult == NO_ERROR )
        {
            //Scann through the results
            for( i = 0; i < cEntries; i++ )
            {
                CString    sNameRemote    = lpnrDrv[i].lpRemoteName;
                CString    sFullName    = lpnrDrv[i].lpRemoteName;
                int        nType        = 9;

                if( sNameRemote.IsEmpty() )
                {
                    sNameRemote = lpnrDrv[i].lpComment;
                    nType = 8;
                }

                //Remove leading back slashes 
                if( sNameRemote.GetLength() > 0 && sNameRemote[0] == _T( '\\' ) )
                {
                    sNameRemote = sNameRemote.Mid( 1 );
                }

                if( sNameRemote.GetLength() > 0 && sNameRemote[0] == _T( '\\' ) )
                {
                    sNameRemote = sNameRemote.Mid( 1 );
                }

                //Display a share or the appropiate icon
                if( lpnrDrv[i].dwDisplayType == RESOURCEDISPLAYTYPE_SHARE )
                {
                    //Display only the share name
                    int nPos = sNameRemote.Find( _T('\\') );

                    if( nPos >= 0 )
                    {
                        sNameRemote = sNameRemote.Mid( nPos + 1 );
                    }

                    InsertPathItem( hParent, NULL, sNameRemote, sFullName, DRIVE_NO_ROOT_DIR, DRIVE_UNKNOWN );
                }
                else
                {
                    NETRESOURCE* pResource    = new NETRESOURCE;
                    *pResource                = lpnrDrv[i];
                    pResource->lpLocalName    = MakeObjectDynamic( pResource->lpLocalName );
                    pResource->lpRemoteName = MakeObjectDynamic( pResource->lpRemoteName );
                    pResource->lpComment    = MakeObjectDynamic( pResource->lpComment );
                    pResource->lpProvider    = MakeObjectDynamic( pResource->lpProvider );
                    InsertPathItem( hParent, pResource, sNameRemote, sFullName, pResource->dwDisplayType + 7 );
                }

                bGotChildren = true;
            }
        }

        GlobalFree( (HGLOBAL) lpnrDrv );

        if( dwResult != ERROR_NO_MORE_ITEMS )
        {
            TRACE( _T( "*** ERROR %d - Cannot complete network drive enumeration\n" ), dwResult );
            break;
        }
    }
    while( dwResult != ERROR_NO_MORE_ITEMS );

    //Let go and go home
    WNetCloseEnum( hEnum );
    return bGotChildren;
}

// JMR-MODIF - Le 31 août 2005 - Cette fonction permet de nettoyer les ressources utilisées pour le net.
void ZIDirTreeCtrl::EmptyNetRessources()
{
    // Start at the root deleting. Current item under inspection
    HTREEITEM hItemCur = GetRootItem();

    // While their is still data in the tree
    while( hItemCur )
    {
        HTREEITEM hItem = GetChildItem( hItemCur );

        // Has children then make the child current
        if( hItem )
        {
            hItemCur = hItem;
            continue;
        }

        // Item has not children so we shall destroy it.
        // but first we must decide who is to take its place.
        HTREEITEM hNextSibItem = GetNextSiblingItem( hItemCur );
        HTREEITEM hPrevSibItem = GetPrevSiblingItem( hItemCur );
        HTREEITEM hParentItem  = GetParentItem( hItemCur );

        //Get item data to check if lparam is to be destroyed
        ZNetResourceWrapper* pNetResource = (ZNetResourceWrapper*)( GetItemData( hItemCur ) );

        if( pNetResource )
        {
            delete pNetResource;
            pNetResource = NULL;
        }

        DeleteItem( hItemCur );
        hItemCur = NULL;

        //Determine which item is next to recieve the focus
        if( hParentItem )
        {
            hItemCur = hParentItem;
        }

        if( hPrevSibItem )
        {
            hItemCur = hPrevSibItem;
        }

        if( hNextSibItem )
        {
            hItemCur = hNextSibItem;
        }
    }
}

void ZIDirTreeCtrl::OnDestroy()
{
    TRACE( _T( "ZIDirTreeCtrl::OnDestroy beginning\n" ) );

    // JMR-MODIF - Code de destruction dans la fonction EmptyNetRessources.
    EmptyNetRessources();

    CTreeCtrl::OnDestroy();

    // JMR-MODIF - Le 20 mars 2006 - Ajout de la ligne de traçage OnDestroy terminating.
    TRACE( _T( "ZIDirTreeCtrl::OnDestroy terminating.\n" ) );
}

CString    ZIDirTreeCtrl::GetSelectedDirectory()
{
    if ( m_IsValid == true )
    {
        return ZIDirTreeCtrl::GetItemPath( GetSelectedItem() );
    }

    return _T( "" );
}
