//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//    Source file: DAOTableLst.cpp

#include <StdAfx.h>
#include "DAOTableLst.h"

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

BEGIN_MESSAGE_MAP(ZCDAOTableList, CListBox)
    //{{AFX_MSG_MAP(ZCDAOTableList)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZCDAOTableList::ZCDAOTableList (CDaoDatabase* pDB)
 : m_pDB(pDB)
{
}


ZCDAOTableList::~ZCDAOTableList()
{
}


int ZCDAOTableList::Initialize (CDaoDatabase* pDB)
{
    m_pDB = pDB;

    return ZCDAOTableList::Refresh();
}

int ZCDAOTableList::Refresh ()
{
    ResetContent();

    CDaoTableDefInfo tabInfo;
    int nTableDefCount = m_pDB->GetTableDefCount();
    for (int i = 0; i < nTableDefCount; i++)
    {
        m_pDB->GetTableDefInfo(i,tabInfo);
        if (tabInfo.m_lAttributes & dbSystemObject)
            continue;
        AddString(tabInfo.m_strName);
    }
    
    int count = GetCount();
    if(count != LB_ERR || count != 0)
        SetCurSel(0);

    return count;
}

CString    ZCDAOTableList::GetSelectedTable()
{
    int    Index = GetCurSel();
    if (Index != CB_ERR)
    {
        CString    Text;
        GetText( Index, Text );
        return Text;
    }
    return "";
}


int    ZCDAOTableList::GetSelectedTables( CStringArray& Array )
{
    Array.RemoveAll();
    int    Count = 0;

    Count = GetSelCount();
    if (Count > 0)
    {
        // Get the list of selection IDs.
        int* pItems = new int [Count];
        GetSelItems( Count, pItems );
        for (int i = 0; i < Count; ++i) 
        {
            CString    Text;
            GetText( pItems[i], Text );
            Array.Add( Text );
        }
        // Done with the item list.
        delete pItems;
    }
    return Count;
}
