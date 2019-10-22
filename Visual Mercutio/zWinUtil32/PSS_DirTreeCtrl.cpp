/****************************************************************************
 * ==> PSS_DirTreeCtrl -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a directory tree control                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DirTreeCtrl.h"

// Windows
#include "shlobj.h"

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

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define NETWORK_NEIGHBOUR _T("Network Neighborhood")
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DirTreeCtrl, PSS_TreeCtrl)
    //{{AFX_MSG_MAP(PSS_DirTreeCtrl)
    ON_NOTIFY_REFLECT_EX(TVN_SELCHANGED, OnSelchangedTree)
    ON_NOTIFY_REFLECT_EX(TVN_ITEMEXPANDING, OnItemexpandingTree)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DirTreeCtrl
//---------------------------------------------------------------------------
PSS_DirTreeCtrl::PSS_DirTreeCtrl(bool includeFile) :
    PSS_TreeCtrl(),
    m_IsValid(false),
    m_IncludeFile(includeFile),
    m_HasBeenInitialized(false)
{}
//---------------------------------------------------------------------------
PSS_DirTreeCtrl::~PSS_DirTreeCtrl()
{}
//---------------------------------------------------------------------------
void PSS_DirTreeCtrl::Initialize(const CString& initialPath, bool clear, bool includeFile)
{
    if (!m_HasBeenInitialized)
    {
        // sets styles
        HasButtons();
        HasLines();
        LinesAtRoot();

        // setup the Image lists
        if(!m_ImageListTree.Create(IDB_FILE_TYPES, 17, 1, RGB(255, 255, 255)))
            TRACE(_T("Image list creation fault"));

        SetImageList(&m_ImageListTree, TVSIL_NORMAL);
        m_HasBeenInitialized = true;
    }

    m_IncludeFile = includeFile;

    Refresh();

    if (!initialPath.IsEmpty())
        SetPath(initialPath);
}
//---------------------------------------------------------------------------
CString PSS_DirTreeCtrl::GetSelectedDirectory()
{
    if (m_IsValid)
        return GetItemPath(GetSelectedItem());

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_DirTreeCtrl::SetPath(const CString& path)
{
    m_Path = path;

    if (m_Path.IsEmpty())
        return;

    // expand the tree to the inital path
    int       level = 0;
    CString   dirName;
    HTREEITEM hCurrent = TVI_ROOT;

    while (ParsePath(m_Path, level, dirName))
    {
        // network or drive expand
        if (!level && dirName.IsEmpty())
            dirName = NETWORK_NEIGHBOUR;

        // search for the matching tree item and expand
        HTREEITEM hItem = GetChildItem(hCurrent);

        while (hItem)
        {
            if (!dirName.CompareNoCase(GetItemText(hItem)))
            {
                hCurrent = hItem;
                Expand(hCurrent, TVE_EXPAND);
                break;
            }

            hItem = GetNextSiblingItem(hItem);
        }

        ++level;
    }
}
//---------------------------------------------------------------------------
void PSS_DirTreeCtrl::Refresh()
{
    // cleanup the previously used resources
    ClearNetRessources();

    // delete all items
    DeleteAllItems();

    // list the local drives
    for (TCHAR letter = _T('A'); letter <= _T('Z'); ++letter)
    {
        CString drive  = letter;
        drive         += _T( ":\\" );
        UINT    type   = GetDriveType(drive);

        switch (type)
        {
            case DRIVE_REMOVABLE:
            case DRIVE_FIXED:
            case DRIVE_REMOTE:
            case DRIVE_CDROM:
            case DRIVE_RAMDISK:
                drive  = letter;
                drive += _T(':');
                InsertPathItem(TVI_ROOT, NULL, drive, drive, type);
                break;

            default:
                break;
        }
    }

    // network neighbourhood
    m_hNetworkRoot = InsertPathItem(TVI_ROOT, NULL, NETWORK_NEIGHBOUR, NETWORK_NEIGHBOUR, DRIVE_RAMDISK + 1);
}
//---------------------------------------------------------------------------
int PSS_DirTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (PSS_TreeCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;

    Initialize();

    return 0;
}
//---------------------------------------------------------------------------
void PSS_DirTreeCtrl::OnDestroy()
{
    TRACE(_T("ZIDirTreeCtrl::OnDestroy beginning\n"));

    ClearNetRessources();

    PSS_TreeCtrl::OnDestroy();

    TRACE(_T("ZIDirTreeCtrl::OnDestroy terminating.\n"));
}
//---------------------------------------------------------------------------
BOOL PSS_DirTreeCtrl::OnItemexpandingTree(NMHDR* pNMHDR, LRESULT* pResult)
{
    TRACE(_T("ZIDirTreeCtrl::OnItemexpandingTree(%p)\n"), pNMHDR);

    // show the wait cursor while expanding
    CWaitCursor cursorWaiting;

    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    // only notifications
    if (pNMTreeView->action == 2)
    {
        // update location display
        const CString path = GetItemPath(pNMTreeView->itemNew.hItem);

        // refresh children
        if (!GetChildItem(pNMTreeView->itemNew.hItem))
        {
            PopulateTree(path, pNMTreeView->itemNew.hItem);

            if (GetSelectedItem() != pNMTreeView->itemNew.hItem)
                SelectItem(pNMTreeView->itemNew.hItem);
        }
    }

    *pResult = 0;

    // keep routing
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DirTreeCtrl::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult)
{
    TRACE(_T("CDlgGetPath::OnSelchangedTree(%p)\n"), pNMHDR);

    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    // disable search on workstation roots
    m_IsValid = !((GetItemData(pNMTreeView->itemNew.hItem) &&
            ((PSS_NetResourceWrapper*)GetItemData(pNMTreeView->itemNew.hItem))->GetNetResource()) ||
                    pNMTreeView->itemNew.hItem == m_hNetworkRoot);

    *pResult = 0;

    // keep routing
    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_DirTreeCtrl::GetItemPath(HTREEITEM hItem)
{
    TRACE(_T("ZIDirTreeCtrl::GetItemPath(%p)\n"), hItem);

    CString result;

    do
    {
        // end with a share name
        NETRESOURCE* pNetResource = ((PSS_NetResourceWrapper*)GetItemData(hItem))->GetNetResource();

        if (pNetResource)
        {
            result = CString(pNetResource->lpRemoteName) + _T('\\') + result;
            break;
        }

        // add the directory name to the path.
        result = GetItemText(hItem) + _T('\\') + result;
        hItem  = GetParentItem(hItem);
    } while (hItem);

    return result;
}
//---------------------------------------------------------------------------
bool PSS_DirTreeCtrl::PopulateTree(const CString& path, HTREEITEM hParent)
{
    TRACE(_T("ZIDirTreeCtrl::PopulateTree( %s )\n"), path);

    // true if at least one child is added
    bool childrenAdded = false;

    // populate network neighbourhood tree (entire network and local computers)
    if (hParent == m_hNetworkRoot)
        childrenAdded = EnumNetwork(hParent);
    else
    if (GetItemData(hParent) && ((PSS_NetResourceWrapper*)GetItemData(hParent))->GetNetResource())
        // network item (search deep in the network)
        childrenAdded = EnumNetwork(hParent);
    else
    {
        CFileFind finder;

        // search for files and populate the CTreeCtrl
        BOOL working = finder.FindFile(path + _T("*.*"));

        while (working)
        {
            working = finder.FindNextFile();

            if (finder.IsDots())
                continue;

            if (finder.IsDirectory())
            {
                InsertPathItem(hParent,
                               NULL,
                               finder.GetFileName(),
                               finder.GetFilePath(),
                               DRIVE_NO_ROOT_DIR,
                               DRIVE_UNKNOWN);

                childrenAdded = true;
            }
            else
            if (m_IncludeFile)
                InsertFileItem(hParent,
                               NULL,
                               finder.GetFileName(),
                               finder.GetFilePath(),
                               DRIVE_RAMDISK + 2,
                               DRIVE_RAMDISK + 2);
        }
    }

    // remove the [+] if no children
    if (!childrenAdded)
    {
        TVITEM item    = { 0 };
        item.mask      = TVIF_HANDLE | TVIF_CHILDREN;
        item.hItem     = hParent;
        item.cChildren = 0;
        SetItem(&item);
    }

    return childrenAdded;
}
//---------------------------------------------------------------------------
bool PSS_DirTreeCtrl::EnumNetwork(HTREEITEM hParent)
{
    TRACE(_T("ZIDirTreeCtrl::EnumNetwork( %p )\n"), hParent);

    // true if at least one child is added
    bool childrenAdded = false;

    // check if the item already has a network resource and use it
    NETRESOURCE* pNetResource = ((PSS_NetResourceWrapper*)GetItemData(hParent))->GetNetResource();

    DWORD         result;
    HANDLE        hEnum;
    DWORD         buffer  = 16384;
    DWORD         entries = 0xFFFFFFFF;
    LPNETRESOURCE pDrv;

    result = ::WNetOpenEnum(pNetResource ? RESOURCE_GLOBALNET : RESOURCE_CONTEXT,
                            RESOURCETYPE_ANY,
                            0,
                            pNetResource ? pNetResource : NULL,
                            &hEnum);

    // read sucessfully?
    if (result != NO_ERROR)
    {
        TRACE(_T("*** ERROR %d - Cannot enumerate network drives.\n"), result);
        return false;
    }

    // get items until none remains
    do
    {
        pDrv   = (LPNETRESOURCE)::GlobalAlloc(GPTR, buffer);
        result = ::WNetEnumResource(hEnum, &entries, pDrv, &buffer);

        if (result == NO_ERROR)
        {
            // iterate through the results
            for (DWORD i = 0; i < entries; ++i)
            {
                CString nameRemote = pDrv[i].lpRemoteName;
                CString fullName   = pDrv[i].lpRemoteName;
                int     type       = 9;

                if (nameRemote.IsEmpty())
                {
                    nameRemote = pDrv[i].lpComment;
                    type       = 8;
                }

                // remove leading back slashes 
                if (nameRemote.GetLength() > 0 && nameRemote[0] == _T('\\'))
                    nameRemote = nameRemote.Mid(1);

                if (nameRemote.GetLength() > 0 && nameRemote[0] == _T('\\'))
                    nameRemote = nameRemote.Mid(1);

                // show a share or the appropiate icon
                if (pDrv[i].dwDisplayType == RESOURCEDISPLAYTYPE_SHARE)
                {
                    // show only the share name
                    const int pos = nameRemote.Find(_T('\\'));

                    if (pos >= 0)
                        nameRemote = nameRemote.Mid(pos + 1);

                    InsertPathItem(hParent, NULL, nameRemote, fullName, DRIVE_NO_ROOT_DIR, DRIVE_UNKNOWN);
                }
                else
                {
                    NETRESOURCE* pResource = new NETRESOURCE;
                    *pResource = pDrv[i];
                    pResource->lpLocalName  = MakeObjectDynamic(pResource->lpLocalName);
                    pResource->lpRemoteName = MakeObjectDynamic(pResource->lpRemoteName);
                    pResource->lpComment    = MakeObjectDynamic(pResource->lpComment);
                    pResource->lpProvider   = MakeObjectDynamic(pResource->lpProvider);
                    InsertPathItem(hParent, pResource, nameRemote, fullName, pResource->dwDisplayType + 7);
                }

                childrenAdded = true;
            }
        }

        ::GlobalFree(HGLOBAL(pDrv));

        if (result != ERROR_NO_MORE_ITEMS)
        {
            TRACE(_T("*** ERROR %d - Cannot complete network drive enumeration\n"), result);
            break;
        }
    }
    while (result != ERROR_NO_MORE_ITEMS);

    // close and clear the network context
    ::WNetCloseEnum(hEnum);

    return childrenAdded;
}
//---------------------------------------------------------------------------
HTREEITEM PSS_DirTreeCtrl::InsertPathItem(HTREEITEM      hParent,
                                          NETRESOURCE*   pNetResource,
                                          const CString& text,
                                          const CString& fullName,
                                          int            imageIndex,
                                          int            imageSelectedIndex)
{
    TRACE(_T("ZIDirTreeCtrl::InsertPathItem(%p,%p,%s +++)\n"), hParent, pNetResource, text);

    CString formattedText = FormatName(text);

    TVINSERTSTRUCT insertStruct;
    insertStruct.hParent          = hParent;
    insertStruct.hInsertAfter     = TVI_LAST;
    insertStruct.itemex.mask      = TVIF_IMAGE | TVIF_TEXT | TVIF_CHILDREN | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    insertStruct.itemex.iImage    = imageIndex;
    insertStruct.itemex.cChildren = 1;
    insertStruct.itemex.lParam    = LPARAM(new PSS_NetResourceWrapper(fullName, pNetResource, true));
    insertStruct.itemex.pszText   = formattedText.GetBuffer(formattedText.GetLength());
    formattedText.ReleaseBuffer();

    if (imageSelectedIndex == -1)
        insertStruct.itemex.iSelectedImage = imageIndex;
    else
        insertStruct.itemex.iSelectedImage = imageSelectedIndex;

    return InsertItem(&insertStruct);
}
//---------------------------------------------------------------------------
HTREEITEM PSS_DirTreeCtrl::InsertFileItem(HTREEITEM      hParent,
                                          NETRESOURCE*   pNetResource,
                                          const CString& text,
                                          const CString& fullName,
                                          int            imageIndex,
                                          int            imageSelectedIndex)
{
    TRACE(_T("ZIDirTreeCtrl::InsertFileItem(%p,%p,%s +++)\n"), hParent, pNetResource, text);

    CString formattedText = FormatName(text);

    TVINSERTSTRUCT insertStruct;
    insertStruct.hParent        = hParent;
    insertStruct.hInsertAfter   = TVI_LAST;
    insertStruct.itemex.mask    = TVIF_IMAGE | TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_PARAM;
    insertStruct.itemex.iImage  = imageIndex;
    insertStruct.itemex.lParam  = LPARAM(new PSS_NetResourceWrapper(fullName, pNetResource, false));
    insertStruct.itemex.pszText = formattedText.GetBuffer(formattedText.GetLength());
    formattedText.ReleaseBuffer();

    if (imageSelectedIndex == -1)
        insertStruct.itemex.iSelectedImage = imageIndex;
    else
        insertStruct.itemex.iSelectedImage = imageSelectedIndex;

    return InsertItem(&insertStruct);
}
//---------------------------------------------------------------------------
void PSS_DirTreeCtrl::ClearNetRessources()
{
    // start deleting at root. Current item under inspection
    HTREEITEM hItemCur = GetRootItem();

    // while there is data remaining in the tree
    while (hItemCur)
    {
        HTREEITEM hItem = GetChildItem(hItemCur);

        // has children? Make the child current if yes
        if (hItem)
        {
            hItemCur = hItem;
            continue;
        }

        // item has no children, so delete it. But first another item should be found to replace it
        HTREEITEM hNextSibItem = GetNextSiblingItem(hItemCur);
        HTREEITEM hPrevSibItem = GetPrevSiblingItem(hItemCur);
        HTREEITEM hParentItem  = GetParentItem(hItemCur);

        // get item data to check if lparam is deleted
        PSS_NetResourceWrapper* pNetResource = (PSS_NetResourceWrapper*)(GetItemData(hItemCur));

        if (pNetResource)
            delete pNetResource;

        DeleteItem(hItemCur);
        hItemCur = NULL;

        // set the focus to next item
        if (hParentItem)
            hItemCur = hParentItem;

        if (hPrevSibItem)
            hItemCur = hPrevSibItem;

        if (hNextSibItem)
            hItemCur = hNextSibItem;
    }
}
//---------------------------------------------------------------------------
TCHAR* PSS_DirTreeCtrl::MakeObjectDynamic(LPTSTR pData)
{
    TRACE(_T("MakeObjectDynamic( %s )\n"), pData);

    // assume a NULL empty string
    TCHAR*      pRet   = NULL;
    std::size_t length = 0;

    if (pData)
        length = std::_tcslen(pData) + 1;

    if (length > 0)
    {
        pRet = new TCHAR[length];
        _tcscpy_s(pRet, _tcslen(pRet), pData);
    }

    return pRet;
}
//---------------------------------------------------------------------------
CString PSS_DirTreeCtrl::FormatName(const CString& name)
{
    CString   result = name;
    const int length = result.GetLength();

    // scan all chars to determine if they contain any lower case item
    for (int n = 0; n < length; ++n)
    {
        TCHAR ch = result[n];

        if ((ch >= _T('a')) && (ch <= _T('z')))
            return result;
    }

    // make the whole string in lower case
    result.MakeLower();

    // make the first char in upper case
    if (result.GetLength() > 0)
    {
        CString firstChar = result[0];
        firstChar.MakeUpper();
        result = firstChar + result.Mid(1);
    }

    return result;
}
//---------------------------------------------------------------------------
bool PSS_DirTreeCtrl::ParsePath(const CString& path, int level, CString& dirName)
{
    int start = 0;

    // search for location in path to start from
    while (level)
    {
        start = path.Find(_T('\\'), start);

        if (start < 0)
            return false;

        --level;
        ++start;
    }

    // search for end point from start
    const int end = path.Find(_T('\\'), start);

    if (end < 0)
        dirName = path.Mid(start);
    else
        dirName = path.Mid(start, end - start);

    return true;
}
//---------------------------------------------------------------------------
