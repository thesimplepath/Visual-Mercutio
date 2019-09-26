// **********************************************************************************************************************
// *                                                Classe ZITreeCtrl                                                    *
// **********************************************************************************************************************
// *                                                   DESCRIPTION                                                        *
// * Cette classe mets à disposition du logiciel un contrôle de type Tree View, avec toutes les ressources associées.    *
// **********************************************************************************************************************

#include <StdAfx.h>
#include "ZITreeCtl.h"

#include "PSS_DropView.h"
#include "PSS_DropScrollView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 12 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_DYNAMIC( ZITreeCtrl, CTreeCtrl )

// **********************************************************************************************************************
// *                                Table de mappage des messages de la classe ZITreeCtrl                                *
// **********************************************************************************************************************
// *                                                   DESCRIPTION                                                        *
// * Cette fonction organise la distribution des messages nécessaires au bon fonctionnement des classes MFC.            *
// **********************************************************************************************************************
BEGIN_MESSAGE_MAP( ZITreeCtrl, CTreeCtrl )
    //{{AFX_MSG_MAP(ZITreeCtrl)
    ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndLabelEdit)
    ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBeginDrag)
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONUP()
    ON_WM_RBUTTONUP()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// **********************************************************************************************************************
// *                                       Constructeur de la classe ZITreeCtrl                                            *
// **********************************************************************************************************************
// *                                                   DESCRIPTION                                                        *
// * Cette fonction prend en charge l'initialisation des ressources pour permettre l'utilisation de l'objet.            *
// **********************************************************************************************************************
ZITreeCtrl::ZITreeCtrl()
    : m_bDragging    ( FALSE ),
      m_pImageList    ( NULL ),
      m_pDragImage    ( NULL ),
      m_pDragObj    ( NULL )
{
}

// **********************************************************************************************************************
// *                                        Destructeur de la classe ZITreeCtrl                                            *
// **********************************************************************************************************************
// *                                                   DESCRIPTION                                                        *
// * Cette fonction prend en charge le nettoyage des ressources à la fin de l'utilisation de l'objet.                    *
// **********************************************************************************************************************
ZITreeCtrl::~ZITreeCtrl()
{
    // JMR-MODIF - Le 31 août 2005 - Teste si m_pImageList a bien été détruit. Sinon, nettoie la mémoire.
    if ( m_pImageList )
    {
        m_pImageList->DeleteImageList();
        delete m_pImageList;
        m_pImageList = NULL;
    }

    _EmptySaveStateDataSet();
}

void ZITreeCtrl::ExpandRoot( BOOL Deep )
{
    ExpandBranch( GetRootItem(), Deep );
}

void ZITreeCtrl::ExpandBranch( HTREEITEM hTreeItem, BOOL Deep )
{
    if ( hTreeItem && ItemHasChildren( hTreeItem ) )
    {
        Expand( hTreeItem, TVE_EXPAND );

        if ( Deep )
        {
            hTreeItem = GetChildItem( hTreeItem );

            do
            {
                ExpandBranch( hTreeItem, Deep );
            }
            while( ( hTreeItem = GetNextSiblingItem( hTreeItem ) ) != NULL );
        }
    }

    EnsureVisible( GetSelectedItem() );
}

void ZITreeCtrl::CollapseRoot( BOOL Deep )
{
    CollapseBranch( GetRootItem(), Deep );
}

void ZITreeCtrl::CollapseBranch( HTREEITEM hTreeItem, BOOL Deep )
{
    if (hTreeItem && ItemHasChildren( hTreeItem ))
    {
        Expand( hTreeItem, TVE_COLLAPSE );

        if ( Deep )
        {
            hTreeItem = GetChildItem( hTreeItem );

            do
            {
                CollapseBranch( hTreeItem, Deep );
            }
            while( ( hTreeItem = GetNextSiblingItem( hTreeItem ) ) != NULL );
        }
    }
}

// **********************************************************************************************************************
// *                                    Fonction LoadImageList de la classe ZITreeCtrl                                    *
// **********************************************************************************************************************
// *                                                 SURCHARGES : 1/2                                                    *
// **********************************************************************************************************************
// *                                                   DESCRIPTION                                                        *
// * Cette fonction charge une liste d'images pour le contrôle depuis une ressource spécifiée.                            *
// **********************************************************************************************************************
// *                                                   PARAMETRES                                                        *
// * -> UINT nID        : ID de la ressource à utiliser pour charger la liste des images.                                *
// * -> int cx            : Largeur, en pixels, de chacune des icônes.                                                    *
// * -> int Grow        : Nombre de nouvelles images que peut contenir la liste redimensionnée.    CF doc officielle de    *
// *                      Microsoft, concernant la classe CImageList.                                                    *
// * -> COLORREF crMask    : Clé de couleur pour le masque; La couleur spécifiée ici sera transparente lors de l'affichage.*
// **********************************************************************************************************************
void ZITreeCtrl::LoadImageList( UINT nID, int cx, int Grow, COLORREF crMask )
{
    if ( m_pImageList )
    {
        m_pImageList->DeleteImageList();
        delete m_pImageList;
        m_pImageList = NULL;
    }

    m_pImageList = new CImageList();
    m_pImageList->Create( nID, cx, Grow, crMask );

    SetImageList( m_pImageList, TVSIL_NORMAL );
}

// **********************************************************************************************************************
// *                                    Fonction LoadImageList de la classe ZITreeCtrl                                    *
// **********************************************************************************************************************
// *                                                 SURCHARGES : 2/2                                                    *
// **********************************************************************************************************************
// *                                                   DESCRIPTION                                                        *
// * Cette fonction charge une liste d'images pour le contrôle depuis une ressource spécifiée.                            *
// **********************************************************************************************************************
// *                                                   PARAMETRES                                                        *
// * -> UINT nIDStart    : ID de la ressource contenant la première image à charger.                                        *
// * -> UINT nIDEnd        : ID de la ressource contenant la dernière image à charger.                                        *
// * -> UINT nFlags        : Combinaison de différents drapeaux de rendus. CF doc officielle de Microsoft, concernant la    *
// *                      classe CImageList.                                                                            *
// * -> int cx            : Largeur, en pixels, de chaque image.                                                            *
// * -> int cy            : Hauteur, en pixels, de chaque image.                                                            *
// **********************************************************************************************************************
void ZITreeCtrl::LoadImageList( UINT nIDStart, UINT nIDEnd, UINT nFlags, int cx, int cy )
{
    CBitmap bitmap;

    m_pImageList = new CImageList();
    m_pImageList->Create( cx, cy, nFlags, 2, 2 );

    // If nIDEnd is zero assigns to start
    if ( !nIDEnd )
    {
        nIDEnd = nIDStart;
    }

    // Load bitmaps
    for ( UINT nID = nIDStart; nID <= nIDEnd; ++nID )
    {
        bitmap.LoadBitmap( nID );
        m_pImageList->Add( &bitmap, static_cast<COLORREF>(NULL) );
        bitmap.DeleteObject();
    }

    SetImageList( m_pImageList, TVSIL_NORMAL );
}

// **********************************************************************************************************************
// *                               Fonction LoadImageListMasked de la classe ZITreeCtrl                                    *
// **********************************************************************************************************************
// *                                                 SURCHARGES : 2/2                                                    *
// **********************************************************************************************************************
// *                                                   DESCRIPTION                                                        *
// * Cette fonction charge une liste d'images pour le contrôle depuis une ressource spécifiée, en utilisant une clé de    *
// * couleurs.                                                                                                            *
// **********************************************************************************************************************
// *                                                   PARAMETRES                                                        *
// * -> UINT nIDStart    : ID de la ressource contenant la première image à charger.                                        *
// * -> UINT nIDEnd        : ID de la ressource contenant la dernière image à charger.                                        *
// * -> int cx            : Largeur, en pixels, de chaque image.                                                            *
// * -> int cy            : Hauteur, en pixels, de chaque image.                                                            *
// * -> COLORREF crMask    : Clé de couleur pour le masque; La couleur spécifiée ici sera transparente lors de l'affichage.*
// **********************************************************************************************************************
void ZITreeCtrl::LoadImageListMasked( UINT nIDStart, UINT nIDEnd, int cx, int cy, COLORREF crMask )
{
    CBitmap bitmap;

    m_pImageList = new CImageList();
    m_pImageList->Create( cx, cy, ILC_MASK, 2, 2 );

    // If nIDEnd is zero assigns to start
    if ( !nIDEnd )
    {
        nIDEnd = nIDStart;
    }

    // Load bitmaps
    for ( UINT nID = nIDStart; nID <= nIDEnd; ++nID )
    {
        bitmap.LoadBitmap( nID );
        m_pImageList->Add( &bitmap, crMask );
        bitmap.DeleteObject();
    }

    SetImageList( m_pImageList, TVSIL_NORMAL );
}

// **********************************************************************************************************************
// *                                  Fonction DeleteAllItems de la classe ZITreeCtrl                                    *
// **********************************************************************************************************************
// *                                                   DESCRIPTION                                                        *
// * Cette fonction désalloue la mémoire utilisée pour les composants.                                                    *
// **********************************************************************************************************************
// *                                                   PARAMETRES                                                        *
// * -> BOOL DeleteImageList    : Drapeau déterminant si la liste d'images doit aussi être détruite.                    *
// **********************************************************************************************************************
void ZITreeCtrl::DeleteAllItems( BOOL DeleteImageList )
{
    // JMR-MODIF - Le 31 août 2005 - Nettoyage de l'objet m_pImageList directement plutôt qu'en utilisant son
    // pointeur par copie.
    //if ( DeleteImageList )
    //{
    //    CImageList *pimagelist;

    //    pimagelist = GetImageList( TVSIL_NORMAL );

    //    if ( pimagelist )
    //    {
    //        pimagelist->DeleteImageList();
    //        delete pimagelist;
    //        pimagelist        = NULL;
    //    }
    //}

    if ( DeleteImageList )
    {
        if ( m_pImageList )
        {
            m_pImageList->DeleteImageList();
            delete m_pImageList;
            m_pImageList = NULL;
        }
    }

    // Therefore, call the base class DeleteAllItems function
    CTreeCtrl::DeleteAllItems();
}

/////////////////////////////////////////////////////////////////////////////
// ZITreeCtrl message handlers
void ZITreeCtrl::OnDestroy()
{
    DeleteAllItems( TRUE );
    CTreeCtrl::OnDestroy();
}

void ZITreeCtrl::SetNewStyle( long lStyleMask, BOOL bSetBits )
{
    long lStyleOld;

    lStyleOld  =  GetWindowLong( m_hWnd, GWL_STYLE );
    lStyleOld &= ~lStyleMask;

    if ( bSetBits )
    {
        lStyleOld |= lStyleMask;
    }

    SetWindowLong( m_hWnd, GWL_STYLE, lStyleOld );
    SetWindowPos( NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER );
}

void ZITreeCtrl::OnEndLabelEdit( LPNMHDR pnmhdr, LRESULT *pLResult )
{
    TV_DISPINFO *ptvinfo;
    ptvinfo = (TV_DISPINFO *)pnmhdr;

    if ( ptvinfo->item.pszText != NULL )
    {
        ptvinfo->item.mask = TVIF_TEXT;
        SetItem( &ptvinfo->item );
    }

    *pLResult = TRUE;
}

BOOL ZITreeCtrl::IsChildNodeOf( HTREEITEM hitemChild, HTREEITEM hitemSuspectedParent )
{
    do
    {
        if ( hitemChild == hitemSuspectedParent )
        {
            break;
        }
    }
    while ( ( hitemChild = GetParentItem( hitemChild ) ) != NULL );

    return ( hitemChild != NULL );
}

BOOL ZITreeCtrl::TransferItem( HTREEITEM hitemDrag, HTREEITEM hitemDrop )
{
    TV_INSERTSTRUCT        tvstruct;
    TCHAR                sztBuffer[50];
    HTREEITEM            hNewItem;
    HTREEITEM            hFirstChild;

    // avoid an infinite recursion situation
    tvstruct.item.hItem            = hitemDrag;
    tvstruct.item.cchTextMax    = 49;
    tvstruct.item.pszText        = sztBuffer;
    tvstruct.item.mask            = TVIF_CHILDREN | TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;

    // get information of the dragged element
    GetItem( &tvstruct.item );

    tvstruct.hParent            = hitemDrop;
    tvstruct.hInsertAfter        = TVI_SORT;
    tvstruct.item.mask            = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
    hNewItem                    = InsertItem( &tvstruct );

    while ( ( hFirstChild = GetChildItem( hitemDrag ) ) != NULL )
    {
        TransferItem( hFirstChild, hNewItem );    // recursively transfer all the items
        DeleteItem( hFirstChild );                // delete the first child and all its children
    }

    return TRUE;
}

void ZITreeCtrl::OnButtonUp( CPoint point )
{
    if ( m_bDragging )
    {
        // End dragging
        VERIFY ( m_pDragImage->DragLeave ( GetDesktopWindow () ) );
        m_pDragImage->EndDrag ();

        // Show the cursor again
        ShowCursor( TRUE );

        // stop intercepting all mouse messages
        VERIFY ( ::ReleaseCapture () );
        m_bDragging = FALSE;

        CPoint pt ( point );
        ClientToScreen ( &pt );

        // get the CWnd pointer of the window that is under the mouse cursor
        CWnd* pDropWnd = WindowFromPoint ( pt );
        ASSERT ( pDropWnd );

        // if window accepts drop of symbol
        if ( ( ISA( pDropWnd, PSS_DropView ) && ( (PSS_DropView*)pDropWnd )->AcceptDrop() ) ||
             ( ISA( pDropWnd, PSS_DropScrollView ) && ( (PSS_DropScrollView*)pDropWnd )->AcceptDrop() ) )
        {
            // convert from screen coordinates to drop target client coordinates
            pDropWnd->ScreenToClient ( &pt );

            if ( m_pDragObj )
            {
                if ( ISA( pDropWnd, PSS_DropView ) )
                {
                    ( (PSS_DropView*)pDropWnd )->DropItem( m_pDragObj, pt );
                }
                else if ( ISA( pDropWnd, PSS_DropScrollView ) )
                {
                    ( (PSS_DropScrollView*)pDropWnd )->DropItem( m_pDragObj, pt );
                }
            }
        }
    }
}

void ZITreeCtrl::OnRButtonUp( UINT nFlags, CPoint point )
{
    OnButtonUp( point );
    CTreeCtrl::OnRButtonUp( nFlags, point );
}

void ZITreeCtrl::OnBeginDrag( LPNMHDR pnmhdr, LRESULT *pLResult )
{
    m_hDragItem = ( (NM_TREEVIEW *)pnmhdr )->itemNew.hItem;
    int nSelectedImage;
    GetItemImage( m_hDragItem, m_DragImageIndex, nSelectedImage );

    // create a drag image
    m_pDragImage = GetImageList( LVSIL_NORMAL );

    if ( !m_pDragImage )
    {
        m_pDragImage = GetImageList( LVSIL_SMALL );
    }

    ASSERT ( m_pDragImage );

    // Changes the cursor to the drag image (DragMove() is still required in OnMouseMove()
    VERIFY ( m_pDragImage->BeginDrag ( m_DragImageIndex, CPoint ( 0, 0 ) ) );
    VERIFY ( m_pDragImage->DragEnter ( GetDesktopWindow (), ( (NM_TREEVIEW *)pnmhdr )->ptDrag ) );

    // Set dragging flag
    m_bDragging = TRUE;
    m_pDropWnd    = this;

    // Set the drag object
    m_pDragObj = GetDragObject( m_hDragItem );

    // Hide the cursor
    ShowCursor( FALSE );

    // capture all mouse messages
    SetCapture ();
}

// **********************************************************************************************************************
// *                                    Fonction OnMouseMove de la classe ZITreeCtrl                                    *
// **********************************************************************************************************************
// *                                                   DESCRIPTION                                                        *
// * Cette fonction est appelée lorsque le curseur de la souris est déplaçé. Si à ce moment l'utilisateur tente de        *
// * faire glisser un objet sélectionné, le curseur de la souris est mis à jour en fonction des possibilités : Soit il    *
// * reprend l'icône de l'objet, soit une icône "opération impossible" est affichée, soit le curseur est réaffiché avec    *
// * son image d'origine.                                                                                                *
// **********************************************************************************************************************
void ZITreeCtrl::OnMouseMove( UINT nFlags, CPoint point )
{
    if ( m_bDragging )
    {
        CPoint pt ( point );
        ClientToScreen ( &pt );

        // move the drag image
        VERIFY ( m_pDragImage->DragMove ( pt ) );

        // unlock window updates
        VERIFY ( m_pDragImage->DragShowNolock ( FALSE ) );

        // get the CWnd pointer of the window that is under the mouse cursor
        CWnd* pDropWnd = WindowFromPoint ( pt );
        ASSERT ( pDropWnd );

        // if we drag outside current window
        if ( pDropWnd != m_pDropWnd )
        {
        }

        // save current window pointer
        m_pDropWnd = pDropWnd;

        // convert from screen coordinates to drop target client coordinates
        pDropWnd->ScreenToClient ( &pt );

        // if window accepts drop of symbol
        if ( ( ISA( pDropWnd, PSS_DropView ) && ( (PSS_DropView*)pDropWnd )->AcceptDrop() ) ||
             ( ISA( pDropWnd, PSS_DropScrollView ) && ( (PSS_DropScrollView*)pDropWnd )->AcceptDrop() ) )
        {
            if ( m_pDragObj )
            {
                // If do accept drop
                if ( (ISA( pDropWnd, PSS_DropView ) && ( (PSS_DropView*)pDropWnd )->AcceptDropItem( m_pDragObj, pt ) ) ||
                     (ISA( pDropWnd, PSS_DropScrollView ) &&
                     ( (PSS_DropScrollView*)pDropWnd )->AcceptDropItem( m_pDragObj, pt ) ) )
                {
                    // change the drag image
                    // JMR-MODIF - Le 2 juin 2005 - Suppression de la macro VERIFY, car il semble que SetDragCursorImage
                    // puisse parfois retourner FALSE.
                    /*VERIFY*/ ( m_pDragImage->SetDragCursorImage ( m_DragImageIndex, CPoint( 0, 0 ) ) );
                }
                else
                {
                    // change the drag image to impossible
                    // JMR-MODIF - Le 2 juin 2005 - Suppression de la macro VERIFY, car il semble que SetDragCursorImage
                    // puisse parfois retourner FALSE.
                    /*VERIFY*/ ( m_pDragImage->SetDragCursorImage ( GetIndexOfNoDropImage(), CPoint( 0, 0 ) ) );
                }
            }
        }

        // lock window updates
        VERIFY ( m_pDragImage->DragShowNolock ( TRUE ) );
    }

    CTreeCtrl::OnMouseMove( nFlags, point );
}

void ZITreeCtrl::OnLButtonUp( UINT nFlags, CPoint point )
{
    OnButtonUp( point );
    CTreeCtrl::OnLButtonUp( nFlags, point );
}

HTREEITEM ZITreeCtrl::FindItem( CString Label, HTREEITEM hStartItem )
{
    // If hItem is NULL, start search from root item.
    if ( hStartItem == NULL )
    {
        hStartItem = (HTREEITEM)SendMessage( TVM_GETNEXTITEM, TVGN_ROOT, 0 );
    }

    while ( hStartItem != NULL )
    {
        char szBuffer[_MAX_FNAME + 1];
        TV_ITEM item;

        item.hItem        = hStartItem;
        item.mask        = TVIF_TEXT | TVIF_CHILDREN;
        item.pszText    = szBuffer;
        item.cchTextMax    = _MAX_FNAME;
        SendMessage( TVM_GETITEM, 0, (LPARAM)&item );

        // Did we find it?
        if ( lstrcmp( szBuffer, (const char*)Label ) == 0 )
        {
            return hStartItem;
        }

        // Check whether we have child items.
        if ( item.cChildren )
        {
            // Recursively traverse child items.
            HTREEITEM hItemFound;
            HTREEITEM hItemChild;

            hItemChild = (HTREEITEM)SendMessage( TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)hStartItem );
            hItemFound = FindItem( Label, hItemChild );

            // Did we find it?
            if ( hItemFound != NULL )
            {
                return hItemFound;
            }
        }

        // Go to next sibling item.
        hStartItem = (HTREEITEM)SendMessage( TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hStartItem );
    }

    // Not found.
    return NULL;
}

HTREEITEM ZITreeCtrl::FindItemData( void* pData, HTREEITEM hStartItem )
{
    // If hItem is NULL, start search from root item.
    if ( hStartItem == NULL )
    {
        hStartItem = (HTREEITEM)SendMessage( TVM_GETNEXTITEM, TVGN_ROOT, 0 );
    }

    while ( hStartItem != NULL )
    {
        char szBuffer[_MAX_FNAME + 1];
        TV_ITEM item;

        item.hItem        = hStartItem;
        item.mask        = TVIF_TEXT | TVIF_PARAM | TVIF_CHILDREN;
        item.pszText    = szBuffer;
        item.cchTextMax    = _MAX_FNAME;
        GetItem( &item );

        // Did we find it?
        if ( (void*)item.lParam == pData )
        {
            return hStartItem;
        }

        // Check whether we have child items.
        if ( item.cChildren )
        {
            // Recursively traverse child items.
            HTREEITEM hItemFound;
            HTREEITEM hItemChild;

            hItemChild = (HTREEITEM)SendMessage( TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)hStartItem );
            hItemFound = FindItemData( pData, hItemChild );

            // Did we find it?
            if ( hItemFound != NULL )
            {
                return hItemFound;
            }
        }

        // Go to next sibling item.
        hStartItem = (HTREEITEM)SendMessage( TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hStartItem );
    }

    // Not found.
    return NULL;
}

int    ZITreeCtrl::GetSelectItemPosition( HTREEITEM hParentItem )
{
    HTREEITEM hSelected = GetSelectedItem();

    if ( hParentItem == NULL )
    {
        hParentItem = GetRootItem();
    }

    if ( hSelected )
    {
        HTREEITEM hPos;

        if ( hParentItem )
        {
            hPos = GetChildItem( hParentItem );
            int Index = 0;

            while ( hPos )
            {
                if ( hPos == hSelected )
                {
                    return Index;
                }

                ++Index;
                hPos = CTreeCtrl::GetNextItem( hPos, TVGN_NEXT );
            }
        }
    }

    return -1;
}

BOOL ZITreeCtrl::IsSelectedItemRootItem()
{
    HTREEITEM hSelected = GetSelectedItem();
    return hSelected && hSelected == GetRootItem();
}

BOOL ZITreeCtrl::IsRootItemName ( const CString Name )
{
    HTREEITEM    hRoot = GetRootItem();

    if ( hRoot && GetItemText( hRoot ) == Name )
    {
        return TRUE;
    }

    return FALSE;
}

BOOL ZITreeCtrl::IsLastItemName ( const CString Name )
{
    return FALSE;
}

BOOL ZITreeCtrl::ItemNameExist ( const CString Name )
{
    return FindItem( Name, NULL ) != NULL;
}

CString ZITreeCtrl::GetNameSelectedItem ()
{
    HTREEITEM hSelected = GetSelectedItem();

    if ( hSelected )
    {
        return GetItemText( hSelected );
    }

    return _T( "" );
}

BOOL ZITreeCtrl::SelectItemName ( const CString Name )
{
    HTREEITEM hItemToSelect = FindItem( Name, (HTREEITEM)NULL );

    if ( hItemToSelect )
        return SelectItem( hItemToSelect );

    return FALSE;
}

// GetLastItem  - Gets last item in the branch
// Returns      - Last item
// hItem        - Node identifying the branch. NULL will 
//                return the last item in outine
HTREEITEM ZITreeCtrl::GetLastItem( HTREEITEM hItem )
{
    // Last child of the last child of the last child ...
    HTREEITEM htiNext;

    if ( hItem == NULL )
    {
        // Get the last item at the top level
        htiNext = CTreeCtrl::GetRootItem();

        while ( htiNext )
        {
            hItem = htiNext;
            htiNext = CTreeCtrl::GetNextSiblingItem( htiNext );
        }
    }

    while ( CTreeCtrl::ItemHasChildren( hItem ) )
    {
        htiNext = CTreeCtrl::GetChildItem( hItem );

        while ( htiNext )
        {
            hItem = htiNext;
            htiNext = CTreeCtrl::GetNextSiblingItem( htiNext );
        }
    }

    return hItem;
}

// GetNextItem  - Get next item as if outline was completely expanded
// Returns      - The item immediately below the reference item
// hItem        - The reference item
HTREEITEM ZITreeCtrl::GetNextItem( HTREEITEM hItem )
{
    HTREEITEM hti;

    if ( CTreeCtrl::ItemHasChildren( hItem ) )
    {
        // Return first child
        return CTreeCtrl::GetChildItem( hItem );
    }
    else
    {
        // return next sibling item
        // Go up the tree to find a parent's sibling if needed.
        while ( ( hti = CTreeCtrl::GetNextSiblingItem( hItem ) ) == NULL )
        {
            if ( ( hItem = CTreeCtrl::GetParentItem( hItem ) ) == NULL )
            {
                return NULL;
            }
        }
    }

    return hti;
}

// GetNextItem  - Get previous item as if outline was completely expanded
// Returns              - The item immediately above the reference item
// hItem                - The reference item
HTREEITEM ZITreeCtrl::GetPrevItem( HTREEITEM hItem )
{
    HTREEITEM hti;

    hti = CTreeCtrl::GetPrevSiblingItem( hItem );

    if ( hti == NULL )
    {
        hti = CTreeCtrl::GetParentItem( hItem );
    }
    else
    {
        hti = GetLastItem( hti );
    }

    return hti;
}

// FindItem        - Finds an item that contains the search string
// Returns        - Handle to the item or NULL
// str            - String to search for
// bCaseSensitive    - Should the search be case sensitive
// bDownDir        - Search direction - TRUE for down
// bWholeWord        - True if search should match whole words
// hItem        - Item to start searching from. NULL for
//                - currently selected item
HTREEITEM ZITreeCtrl::FindItem( CString str,
                                BOOL bCaseSensitive    /*= FALSE*/,
                                BOOL bDownDir        /*= TRUE*/,
                                BOOL bWholeWord        /*= FALSE*/,
                                HTREEITEM hItem        /*= NULL*/ )
{
    int lenSearchStr = str.GetLength();

    if ( lenSearchStr == 0 )
    {
        return NULL;
    }

    HTREEITEM htiSel = hItem ? hItem : CTreeCtrl::GetSelectedItem();
    HTREEITEM htiCur = bDownDir ? GetNextItem( htiSel ) : GetPrevItem( htiSel );

    CString sSearch = str;

    if ( htiCur == NULL )
    {
        if ( bDownDir )
        {
            htiCur = CTreeCtrl::GetRootItem();
        }
        else
        {
            htiCur = GetLastItem( NULL );
        }
    }

    if( !bCaseSensitive )
    {
        sSearch.MakeLower();
    }

    while ( htiCur && htiCur != htiSel )
    {
        CString sItemText = CTreeCtrl::GetItemText( htiCur );

        if ( !bCaseSensitive )
        {
            sItemText.MakeLower();
        }

        int n;

        while ( ( n = sItemText.Find( sSearch ) ) != -1 )
        {
            // Search string found
            if ( bWholeWord )
            {
                // Check preceding char
                if ( n != 0 )
                {
                    if ( isalpha( sItemText[n - 1] ) || sItemText[n - 1] == '_' )
                    {
                        // Not whole word
                        sItemText = sItemText.Right( sItemText.GetLength() - n - lenSearchStr );
                        continue;
                    }
                }

                // Check succeeding char
                if ( sItemText.GetLength() > n + lenSearchStr &&
                     ( isalpha( sItemText[n + lenSearchStr] ) ||
                     sItemText[n + lenSearchStr] == '_' ) )
                {
                    // Not whole word
                    sItemText = sItemText.Right( sItemText.GetLength() - n - sSearch.GetLength() );
                    continue;
                }
            }
            
            if ( IsFindValid( htiCur ) )
            {
                return htiCur;
            }
            else
            {
                break;
            }
        }

        htiCur = bDownDir ? GetNextItem( htiCur ) : GetPrevItem( htiCur );

        if ( htiCur == NULL )
        {
            if ( bDownDir )
            {
                htiCur = CTreeCtrl::GetRootItem();
            }
            else
            {
                htiCur = GetLastItem( NULL );
            }
        }
    }

    return NULL;
}

// IsFindValid    - Virtual function used by FindItem to allow this
//                  function to filter the result of FindItem
// Returns    - True if item matches the criteria
// Arg        - Handle of the item
BOOL ZITreeCtrl::IsFindValid( HTREEITEM )
{
    return TRUE;
}

void ZITreeCtrl::SaveCollapsedState()
{
    _EmptySaveStateDataSet();

    _SaveCollapsedState( GetRootItem() );
}

void ZITreeCtrl::_SaveCollapsedState( HTREEITEM hTreeItem )
{
    if ( hTreeItem && ItemHasChildren( hTreeItem ) )
    {
        // Retreive the item text
        CString sItemText = CTreeCtrl::GetItemText( hTreeItem );
        _ZTreeData* pObj = _AddSaveStateDataToSet( sItemText );

        // If exist, sets the collapsed state
        if ( pObj != NULL )
        {
            pObj->SetCollapsed( ( GetItemState( hTreeItem, TVIS_EXPANDED ) & TVIS_EXPANDED ) ? false : true );
        }

        hTreeItem = GetChildItem( hTreeItem );

        do
        {
            _SaveCollapsedState( hTreeItem );
        }
        while( ( hTreeItem = GetNextSiblingItem( hTreeItem ) ) != NULL );
    }
}

void ZITreeCtrl::RestoreCollapsedStateToTreeCtrl()
{
    _RestoreCollapsedStateToTreeCtrl( GetRootItem() );
}

void ZITreeCtrl::_RestoreCollapsedStateToTreeCtrl( HTREEITEM hTreeItem )
{
    if ( hTreeItem && ItemHasChildren( hTreeItem ) )
    {
        // Retreive the item text
        CString sItemText = CTreeCtrl::GetItemText( hTreeItem );

        // Retreive the data object
        _ZTreeData*    pObj = _FindElementFromSaveStateDataSet( sItemText );

        // If exist, sets the previously saved state
        if ( pObj != NULL )
        {
            Expand( hTreeItem, ( pObj->IsCollapsed() ) ? TVE_COLLAPSE : TVE_EXPAND );
        }

        hTreeItem = GetChildItem( hTreeItem );

        do
        {
            _RestoreCollapsedStateToTreeCtrl( hTreeItem );
        }
        while( ( hTreeItem = GetNextSiblingItem( hTreeItem ) ) != NULL );
    }
}

_ZTreeData::_ZTreeData( CString Str )
{
    m_Str        = Str;
    m_Collapsed    = false;
}

_ZTreeData::~_ZTreeData()
{
    // In the destructor, just reset all values
    m_Collapsed = false;
    m_Str.Empty();
}

void ZITreeCtrl::_EmptySaveStateDataSet()
{
    _ZTreeDataIterator i( &m_TreeDataSet );

    for ( _ZTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        delete pElement;
    }

    m_TreeDataSet.RemoveAll();
}

_ZTreeData* ZITreeCtrl::_FindElementFromSaveStateDataSet( CString Str )
{
    _ZTreeDataIterator i( &m_TreeDataSet );

    for ( _ZTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_Str == Str )
        {
            return pElement;
        }
    }

    return NULL;
}

_ZTreeData* ZITreeCtrl::_AddSaveStateDataToSet( CString Str )
{
    _ZTreeData* pData = new _ZTreeData( Str );
    m_TreeDataSet.Add( pData );
    return pData;
}

bool ZITreeCtrl::_DeleteElementFromSaveStateDataSet( CString Str )
{
    _ZTreeDataIterator i( &m_TreeDataSet );

    for ( _ZTreeData* pElement = i.GetFirst(); pElement != NULL; pElement = i.GetNext() )
    {
        if ( pElement->m_Str == Str )
        {
            delete pElement;
            i.Remove();
            return true;
        }
    }

    return false;
}
