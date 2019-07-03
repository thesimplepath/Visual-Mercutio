//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//    Source file: UserLst.cpp

#include <StdAfx.h>

#include "UserLst.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _WIN32
BEGIN_MESSAGE_MAP(ZCUserList, ZIListCtrl)
#endif
#ifndef _WIN32
BEGIN_MESSAGE_MAP(ZCUserList, CListBox)
#endif
    //{{AFX_MSG_MAP(ZCUserList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCUserList 

#ifndef _WIN32
    #include "ZWinUtil.h"
#endif
#ifdef _WIN32
    #include "ZWinUtil32.h"
#endif
#include "zRes32\ZRes.h"

#ifdef _WIN32
static int _gUserColText[] = {    IDS_NOCOLUMNHEADER, 
                                IDS_DISPLAYNAMECOLUMN_USER,
                                IDS_NAMECOLUMN_USER, 
                                IDS_DEPARTEMENTCOLUMN_USER, 
                                IDS_ADDRESSCOLUMN_USER, 
                                IDS_ADMINCOLUMN_USER,
                                IDS_RESPONSIBLECOLUMN_USER,
                                IDS_DESCRIPTIONCOLUMN_USER };
static int _gUserColSize[] = {    20,
                                120, 
                                80, 
                                80,
                                80,
                                20,
                                80,
                                265 };
#endif

ZCUserList::ZCUserList (ZUUserManager* pUserManager, CString Departement)
 : m_pUserManager(pUserManager), m_Departement(Departement), m_ColumnsBuilt(FALSE)
{
}


ZCUserList::~ZCUserList()
{
}


void    ZCUserList::BuildColumns()
{
    if (m_ColumnsBuilt)
        return;
    // Load images
    LoadImageListMasked( IDB_USERDEPT, IDB_ADMIN );
    ZIListCtrl::BuildColumns(8, _gUserColSize, _gUserColText );
    ZIListCtrl::SetFullRowSelect( TRUE );
    ZIListCtrl::EnableSort( TRUE );

    m_ColumnsBuilt = TRUE;
}

int ZCUserList::Initialize (ZUUserManager* pUserManager, CString Departement)
{
    m_pUserManager = pUserManager;
    m_Departement = Departement;
    ZCUserList::BuildColumns();

    return ZCUserList::Refresh();
}

int ZCUserList::Refresh ()
{
#ifdef _WIN32
    DeleteAllItems();
#endif

#ifndef _WIN32
    ResetContent();
#endif

    size_t        Count = m_pUserManager->GetCount();
    size_t        LineCounter = 0;
    size_t        ColumnCounter;

    for (int Index = 0; Index < Count; ++Index)
    {
#ifndef _WIN32
        if (m_Departement.IsEmpty() || m_Departement == m_pUserManager->GetAt(Index)->GetDepartement())
            AddString( m_pUserManager->GetAt(Index)->GetName() );
#endif
#ifdef _WIN32
        if (!(m_Departement.IsEmpty() || m_Departement == m_pUserManager->GetAt(Index)->GetDepartement()))
            continue;
        int    ImageIndex;
        ZUser*    pUser = m_pUserManager->GetAt(Index);

          if (pUser->IsAdministrator())
        {
            ImageIndex = 1;
        }
        else
            ImageIndex = 2;
        // Add the user type icon
        InsertItem( LVIF_IMAGE | LVIF_PARAM, LineCounter, 
                    NULL,
                    0, 0, 
                    ImageIndex, 
                    0);
        ColumnCounter = 1;
        SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
                 pUser->GetDisplayName(),
                 0, LVIF_TEXT, LVIF_TEXT, 0 );
        SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
                 pUser->GetUserName(),
                 0, LVIF_TEXT, LVIF_TEXT, 0 );
        SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
                 pUser->GetDepartement(),
                 0, LVIF_TEXT, LVIF_TEXT, 0 );
        SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
                 pUser->GetMailAddress(),
                 0, LVIF_TEXT, LVIF_TEXT, 0 );
        SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
            (pUser->IsAdministrator()) ? "1" : "0",
                 0, LVIF_TEXT, LVIF_TEXT, 0 );
        SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
                 pUser->GetResponsible(),
                 0, LVIF_TEXT, LVIF_TEXT, 0 );
        SetItem( LineCounter, ColumnCounter++, LVIF_TEXT,
                 pUser->GetDescription(),
                 0, LVIF_TEXT, LVIF_TEXT, 0 );
        // Increment Line counter
        ++LineCounter;

#endif
    }

    return Count;
}

CString    ZCUserList::GetSelectedUsername()
{
#ifndef _WIN32    // In 16bit
    int    Index = GetCurSel();
    if (Index != CB_ERR)
    {
        CString    Text;
        GetLBText( Index, Text );
        return Text;
    }
#endif

#ifdef _WIN32    // In 32bit
    int    Index;
    POSITION pos = GetFirstSelectedItemPosition();
    if (pos != NULL)     
    {
        Index = GetNextSelectedItem( pos );
        return GetItemText( Index, 1 );
    }
#endif

    return "";
}


int    ZCUserList::GetSelectedUsernames( CStringArray Array )
{
    Array.RemoveAll();
    int    Count = 0;

#ifndef _WIN32    // In 16bit
    Count = GetSelCount();
    if (Count > 0)
    {
        // Get the list of selection IDs.
        int* pItems = new int [Count];
        GetSelItems( Count, pItems );
        for (int i = 0; i < Count; ++i) 
        {
            CString    Text;
            GetLBText( pItems[i], Text );
            Array.Add( Text );
        }
        // Done with the item list.
        delete pItems;
    }
#endif
    
#ifdef _WIN32    // In 32bit
    Count = GetSelectedCount();
    POSITION pos = GetFirstSelectedItemPosition();
    while (pos)
    {
        int nItem = GetNextSelectedItem(pos);
        Array.Add( GetItemText( nItem, 0 ) );
    }
#endif

    return Count;
}
