/****************************************************************************
 * ==> PSS_UserListCtrl ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user list control                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_UserListCtrl.h"

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
// Global variables
//---------------------------------------------------------------------------
#ifdef _WIN32
    static int g_UserColText[] =
    {
        IDS_NOCOLUMNHEADER,
        IDS_DISPLAYNAMECOLUMN_USER,
        IDS_NAMECOLUMN_USER,
        IDS_DEPARTEMENTCOLUMN_USER,
        IDS_ADDRESSCOLUMN_USER,
        IDS_ADMINCOLUMN_USER,
        IDS_RESPONSIBLECOLUMN_USER,
        IDS_DESCRIPTIONCOLUMN_USER
    };

    static int g_UserColSize[] =
    {
        20,
        120,
        80,
        80,
        80,
        20,
        80,
        265
    };
#endif
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
#ifdef _WIN32
    BEGIN_MESSAGE_MAP(PSS_UserListCtrl, ZIListCtrl)
#else
    BEGIN_MESSAGE_MAP(PSS_UserListCtrl, CListBox)
#endif
    //{{AFX_MSG_MAP(PSS_UserListCtrl)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_UserListCtrl
//---------------------------------------------------------------------------
PSS_UserListCtrl::PSS_UserListCtrl(PSS_UserManager* pUserManager, const CString& departement) :
    m_pUserManager(pUserManager),
    m_Departement(departement),
    m_AdminOnly(FALSE),
    m_NonAdminOnly(FALSE),
    m_ColumnsBuilt(FALSE)
{}
//---------------------------------------------------------------------------
PSS_UserListCtrl::PSS_UserListCtrl(const PSS_UserListCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_UserListCtrl::~PSS_UserListCtrl()
{}
//---------------------------------------------------------------------------
const PSS_UserListCtrl& PSS_UserListCtrl::operator = (const PSS_UserListCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
int PSS_UserListCtrl::Initialize(PSS_UserManager* pUserManager, const CString& departement)
{
    m_pUserManager = pUserManager;
    m_Departement  = departement;

    BuildColumns();

    return Refresh();
}
//---------------------------------------------------------------------------
CString PSS_UserListCtrl::GetSelectedUserName() const
{
    #ifndef _WIN32
        // 16 bit version
        const int index = GetCurSel();

        if (index != CB_ERR)
        {
            CString text;
            GetLBText(index, text);
            return text;
        }
    #endif

    #ifdef _WIN32
        // 32 bit version
        POSITION pPos = GetFirstSelectedItemPosition();

        if (pPos)
            return GetItemText(GetNextSelectedItem(pPos), 1);
    #endif

    return "";
}
//---------------------------------------------------------------------------
int PSS_UserListCtrl::GetSelectedUserNames(CStringArray& userNameArray) const
{
    userNameArray.RemoveAll();

    #ifndef _WIN32
        // 16 bit version
        const int count = GetSelCount();

        if (count > 0)
        {
            // get the selected items
            int* pItems = new int[count];
            GetSelItems(count, pItems);

            for (int i = 0; i < count; ++i)
            {
                CString text;
                GetLBText(pItems[i], text);
                userNameArray.Add(text);
            }

            // done with the item list
            delete pItems;
        }
    #endif

    #ifdef _WIN32
        // 32 bit version
        const int      count = GetSelectedCount();
              POSITION pPos  = GetFirstSelectedItemPosition();

        while (pPos)
            userNameArray.Add(GetItemText(GetNextSelectedItem(pPos), 0));
    #endif

    return count;
}
//---------------------------------------------------------------------------
int PSS_UserListCtrl::Refresh()
{
    #ifdef _WIN32
        DeleteAllItems();
    #else
        ResetContent();
    #endif

    const std::size_t count       = m_pUserManager->GetCount();
          std::size_t lineCounter = 0;
          std::size_t columnCounter;

    for (int index = 0; index < count; ++index)
    {
        ZUser* pUser = m_pUserManager->GetAt(index);

        if (!pUser)
            continue;

        if (!(m_Departement.IsEmpty() || m_Departement == pUser->GetDepartement()))
            continue;

        #ifdef _WIN32
            const int imageIndex = (pUser->IsAdministrator() ? 1 : 2);

            // add the user type icon
            InsertItem(LVIF_IMAGE | LVIF_PARAM, lineCounter, NULL, 0, 0, imageIndex, 0);

            columnCounter = 1;

            SetItem(lineCounter, columnCounter, LVIF_TEXT, pUser->GetDisplayName(), 0, LVIF_TEXT, LVIF_TEXT, 0);
            ++columnCounter;

            SetItem(lineCounter, columnCounter, LVIF_TEXT, pUser->GetUserName(), 0, LVIF_TEXT, LVIF_TEXT, 0);
            ++columnCounter;

            SetItem(lineCounter, columnCounter, LVIF_TEXT, pUser->GetDepartement(), 0, LVIF_TEXT, LVIF_TEXT, 0);
            ++columnCounter;

            SetItem(lineCounter, columnCounter, LVIF_TEXT, pUser->GetMailAddress(), 0, LVIF_TEXT, LVIF_TEXT, 0);
            ++columnCounter;

            SetItem(lineCounter, columnCounter, LVIF_TEXT, pUser->IsAdministrator() ? "1" : "0", 0, LVIF_TEXT, LVIF_TEXT, 0);
            ++columnCounter;

            SetItem(lineCounter, columnCounter, LVIF_TEXT, pUser->GetResponsible(), 0, LVIF_TEXT, LVIF_TEXT, 0);
            ++columnCounter;

            SetItem(lineCounter, columnCounter, LVIF_TEXT, pUser->GetDescription(), 0, LVIF_TEXT, LVIF_TEXT, 0);

            // increment the line counter
            ++lineCounter;
        #else
            AddString(pUser->GetName());
        #endif
    }

    return count;
}
//---------------------------------------------------------------------------
void PSS_UserListCtrl::BuildColumns()
{
    if (m_ColumnsBuilt)
        return;

    // load images
    LoadImageListMasked(IDB_USERDEPT, IDB_ADMIN);

    #ifdef _WIN32
        ZIListCtrl::BuildColumns(8, g_UserColSize, g_UserColText);
    #endif

    SetFullRowSelect(TRUE);
    EnableSort(TRUE);

    m_ColumnsBuilt = TRUE;
}
//---------------------------------------------------------------------------
