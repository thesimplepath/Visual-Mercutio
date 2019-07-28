/****************************************************************************
 * ==> PSS_UserPropertyCtrl ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user property control                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_UserPropertyCtrl.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
#endif
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#ifdef _WIN32
    static int g_UserPropertyColText[] =
    {
        IDS_COLUMN1_FOLDERINFO,
        IDS_COLUMN2_FOLDERINFO
    };

    static int g_UserPropertyColSize[] =
    {
        100,
        300
    };
#endif
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
#ifdef _WIN32
    BEGIN_MESSAGE_MAP(PSS_UserPropertyCtrl, ZIListCtrl)
#else
    BEGIN_MESSAGE_MAP(PSS_UserPropertyCtrl, CListBox)
#endif
    //{{AFX_MSG_MAP(PSS_UserPropertyCtrl)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UserPropertyCtrl
//---------------------------------------------------------------------------
PSS_UserPropertyCtrl::PSS_UserPropertyCtrl(ZUser* pUser, BOOL enableModify) :
    m_pUser(pUser),
    m_EnableModify(enableModify),
    m_ColumnsBuilt(FALSE),
    m_IsModified(FALSE)
{}
//---------------------------------------------------------------------------
PSS_UserPropertyCtrl::PSS_UserPropertyCtrl(const PSS_UserPropertyCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_UserPropertyCtrl::~PSS_UserPropertyCtrl()
{}
//---------------------------------------------------------------------------
const PSS_UserPropertyCtrl& PSS_UserPropertyCtrl::operator = (const PSS_UserPropertyCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
int PSS_UserPropertyCtrl::Initialize(ZUser* pUser, BOOL enableModify)
{
    m_pUser        = pUser;
    m_EnableModify = enableModify;

    BuildColumns();

    return Refresh();
}
//---------------------------------------------------------------------------
int PSS_UserPropertyCtrl::Refresh()
{
    #ifdef _WIN32
        DeleteAllItems();
    #else
        ResetContent();
    #endif

    if (!m_pUser)
        return 0;

    std::size_t lineCounter = 0;
    CString     text;

    #ifdef _WIN32
        // add the display name
        text.LoadString(IDS_DISPLAYNAMECOLUMN_USER);
        InsertItem(lineCounter, text);
        SetItem(lineCounter, 1, LVIF_TEXT, m_pUser->GetDisplayName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the user name
        text.LoadString(IDS_NAMECOLUMN_USER);
        InsertItem(++lineCounter, text);
        SetItem(lineCounter, 1, LVIF_TEXT, m_pUser->GetUserName(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the departement
        text.LoadString(IDS_DEPARTEMENTCOLUMN_USER);
        InsertItem(++lineCounter, text);
        SetItem(lineCounter, 1, LVIF_TEXT, m_pUser->GetDepartement(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the mail address
        text.LoadString(IDS_ADDRESSCOLUMN_USER);
        InsertItem(++lineCounter, text);
        SetItem(lineCounter, 1, LVIF_TEXT, m_pUser->GetMailAddress(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the administrator flag
        text.LoadString(IDS_ADMINCOLUMN_USER);
        InsertItem(++lineCounter, text);
        SetItem(lineCounter, 1, LVIF_TEXT, m_pUser->IsAdministrator() ? "1" : "0", 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the responsible
        text.LoadString(IDS_RESPONSIBLECOLUMN_USER);
        InsertItem(++lineCounter, text);
        SetItem(lineCounter, 1, LVIF_TEXT, m_pUser->GetResponsible(), 0, LVIF_TEXT, LVIF_TEXT, 0);

        // add the description
        text.LoadString(IDS_DESCRIPTIONCOLUMN_USER);
        InsertItem(++lineCounter, text);
        SetItem(lineCounter, 1, LVIF_TEXT, m_pUser->GetDescription(), 0, LVIF_TEXT, LVIF_TEXT, 0);
    #endif

    return 1;
}
//---------------------------------------------------------------------------
void PSS_UserPropertyCtrl::BuildColumns()
{
    if (m_ColumnsBuilt)
        return;

    #ifdef _WIN32
        ZIListCtrl::BuildColumns(2, g_UserPropertyColSize, g_UserPropertyColText);
    #endif

    SetFullRowSelect(TRUE);
    EnableSort(TRUE);

    m_ColumnsBuilt = TRUE;
}
//---------------------------------------------------------------------------
