//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//    Source file: UserPrp.cpp

#include <StdAfx.h>

#include "UserPrp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _WIN32
BEGIN_MESSAGE_MAP(ZCUserProperty, ZIListCtrl)
#endif
#ifndef _WIN32
BEGIN_MESSAGE_MAP(ZCUserProperty, CListBox)
#endif
    //{{AFX_MSG_MAP(ZCUserProperty)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Class ZCUserProperty 

#ifndef _WIN32
    #include "ZWinUtil.h"
#endif
#ifdef _WIN32
    #include "ZWinUtil32.h"
#endif
#include "zRes32\ZRes.h"

#ifdef _WIN32
static int _gUserPropertyColText[] = { IDS_COLUMN1_FOLDERINFO, IDS_COLUMN2_FOLDERINFO };
static int _gUserPropertyColSize[] = { 100, 300 };
#endif

ZCUserProperty::ZCUserProperty (ZUser* pUser, BOOL EnableModify)
 : m_pUser(pUser), m_EnableModify(EnableModify), m_ColumnsBuilt(FALSE)
{
}


ZCUserProperty::~ZCUserProperty()
{
}


void    ZCUserProperty::BuildColumns()
{
    if (m_ColumnsBuilt)
        return;
    ZIListCtrl::BuildColumns(2, _gUserPropertyColSize, _gUserPropertyColText );
    ZIListCtrl::SetFullRowSelect( TRUE );
    ZIListCtrl::EnableSort( TRUE );

    m_ColumnsBuilt = TRUE;
}

int ZCUserProperty::Initialize (ZUser* pUser, BOOL EnableModify)
{
    m_pUser = pUser;
    m_EnableModify = EnableModify;
    ZCUserProperty::BuildColumns();

    return ZCUserProperty::Refresh();
}

int ZCUserProperty::Refresh ()
{
#ifdef _WIN32
    DeleteAllItems();
#endif

#ifndef _WIN32
    ResetContent();
#endif

    if (!m_pUser)
        return 0;
    size_t    LineCounter = 0;
    CString    Text;
#ifndef _WIN32

#endif

#ifdef _WIN32

    // Add the display name
    Text.LoadString( IDS_DISPLAYNAMECOLUMN_USER );
    InsertItem( LineCounter, Text );
    SetItem( LineCounter, 1, LVIF_TEXT,
             m_pUser->GetDisplayName(),
             0, LVIF_TEXT, LVIF_TEXT, 0 );

    // Add the user name
    Text.LoadString( IDS_NAMECOLUMN_USER );
    InsertItem( ++LineCounter, Text );
    SetItem( LineCounter, 1, LVIF_TEXT,
             m_pUser->GetUserName(),
             0, LVIF_TEXT, LVIF_TEXT, 0 );

    // Add the departement
    Text.LoadString( IDS_DEPARTEMENTCOLUMN_USER );
    InsertItem( ++LineCounter, Text );
    SetItem( LineCounter, 1, LVIF_TEXT,
             m_pUser->GetDepartement(),
             0, LVIF_TEXT, LVIF_TEXT, 0 );

    // Add the mail address
    Text.LoadString( IDS_ADDRESSCOLUMN_USER );
    InsertItem( ++LineCounter, Text );
    SetItem( LineCounter, 1, LVIF_TEXT,
             m_pUser->GetMailAddress(),
             0, LVIF_TEXT, LVIF_TEXT, 0 );

    // Add the administrator flag
    Text.LoadString( IDS_ADMINCOLUMN_USER );
    InsertItem( ++LineCounter, Text );
    SetItem( LineCounter, 1, LVIF_TEXT,
        (m_pUser->IsAdministrator()) ? "1" : "0",
             0, LVIF_TEXT, LVIF_TEXT, 0 );

    // Add the responsible
    Text.LoadString( IDS_RESPONSIBLECOLUMN_USER );
    InsertItem( ++LineCounter, Text );
    SetItem( LineCounter, 1, LVIF_TEXT,
             m_pUser->GetResponsible(),
             0, LVIF_TEXT, LVIF_TEXT, 0 );

    // Add the description
    Text.LoadString( IDS_DESCRIPTIONCOLUMN_USER );
    InsertItem( ++LineCounter, Text );
    SetItem( LineCounter, 1, LVIF_TEXT,
             m_pUser->GetDescription(),
             0, LVIF_TEXT, LVIF_TEXT, 0 );

#endif

    return 1;
}

