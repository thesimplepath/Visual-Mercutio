/****************************************************************************
 * ==> PSS_DAOTableList ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a data access object (DAO) table listbox          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_DAOTableList.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32\zWinUtil32Res.h"
#endif
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DAOTableList, CListBox)
    //{{AFX_MSG_MAP(PSS_DAOTableList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DAOTableList
//---------------------------------------------------------------------------
PSS_DAOTableList::PSS_DAOTableList(CDaoDatabase* pDB) :
    m_pDB(pDB)
{}
//---------------------------------------------------------------------------
PSS_DAOTableList::PSS_DAOTableList(const PSS_DAOTableList& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_DAOTableList::~PSS_DAOTableList()
{}
//---------------------------------------------------------------------------
const PSS_DAOTableList& PSS_DAOTableList::operator = (const PSS_DAOTableList& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
int PSS_DAOTableList::Initialize(CDaoDatabase* pDB)
{
    m_pDB = pDB;

    return Refresh();
}
//---------------------------------------------------------------------------
CString PSS_DAOTableList::GetSelectedTable() const
{
    const int index = GetCurSel();

    if (index != CB_ERR)
    {
        CString text;
        GetText(index, text);

        return text;
    }

    return "";
}
//---------------------------------------------------------------------------
int PSS_DAOTableList::GetSelectedTables(CStringArray& tableArray) const
{
    tableArray.RemoveAll();

    const int count = GetSelCount();

    if (count > 0)
    {
        int* pItems = NULL;

        try
        {
            // get the selection identifier list
            pItems = new int[count];
            GetSelItems(count, pItems);

            for (int i = 0; i < count; ++i)
            {
                CString text;
                GetText(pItems[i], text);
                tableArray.Add(text);
            }
        }
        catch (...)
        {
            // clear the memory
            if (pItems)
                delete[] pItems;

            throw;
        }

        // done with the item list
        delete[] pItems;
    }

    return count;
}
//---------------------------------------------------------------------------
int PSS_DAOTableList::Refresh()
{
    ResetContent();

    CDaoTableDefInfo tabInfo;

    const int tableDefCount = m_pDB->GetTableDefCount();

    for (int i = 0; i < tableDefCount; ++i)
    {
        m_pDB->GetTableDefInfo(i, tabInfo);

        if (tabInfo.m_lAttributes & dbSystemObject)
            continue;

        AddString(tabInfo.m_strName);
    }

    const int count = GetCount();

    if (count && count != LB_ERR)
        SetCurSel(0);

    return count;
}
//---------------------------------------------------------------------------
