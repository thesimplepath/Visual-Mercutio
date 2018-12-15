// DBLstC.cpp : implementation of the ZCDatabaseListCtrl class
//

#include "stdafx.h"
#include "DBLstC.h"
#include "zRes32\ZRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZCDatabaseListCtrl

BEGIN_MESSAGE_MAP(ZCDatabaseListCtrl, ZIListCtrl)
    //{{AFX_MSG_MAP(ZCDatabaseListCtrl)
    ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetDispInfo)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZCDatabaseListCtrl construction/destruction

ZCDatabaseListCtrl::ZCDatabaseListCtrl( const CString DatabaseFilename, const CString Tablename )
: m_DatabaseFilename(DatabaseFilename), m_Tablename(Tablename), m_ColumnsBuilt(FALSE)
{
    m_pDataBase = NULL;
    m_pRecordSet = NULL;
}

ZCDatabaseListCtrl::~ZCDatabaseListCtrl()
{
//    CImageList* pImageList = GetImageList(NULL, LVSIL_SMALL);
//    delete pImageList;
    
    CloseDatabase();
}


BOOL ZCDatabaseListCtrl::OpenDatabase()
{
    // First, close the database if one already open
    CloseDatabase();
    // Then, open the database
    m_pDataBase = new CDaoDatabase;
    try
    {
        m_pDataBase->Open(m_DatabaseFilename);
    }
    catch(CDaoException* e)
    {
        AfxMessageBox(e->m_pErrorInfo->m_strDescription, 
                MB_ICONEXCLAMATION );
        delete m_pDataBase;
        e->Delete();
        return FALSE;
    }
/*
    CPickTableDlg  pickDlg(m_pDataBase);
    if(pickDlg.DoModal() == IDCANCEL)
        return FALSE;
    CString TableName;
    pickDlg.GetTableName(TableName);
*/
    m_pRecordSet = new CDaoRecordset(m_pDataBase);
    CString strSQL = "SELECT * FROM " + m_Tablename;//Set up SQL statement    
    try
    {
        m_pRecordSet->Open(dbOpenDynaset, strSQL);//Open recordset using SQL statement
    }
    catch(CDaoException* e)
    {
        AfxMessageBox(e->m_pErrorInfo->m_strDescription, 
                MB_ICONEXCLAMATION );
        delete m_pRecordSet;
        m_pDataBase->Close();
        delete m_pDataBase;
        e->Delete();
        return FALSE;
    }

    if (!m_pRecordSet->IsEOF())
        m_pRecordSet->MoveLast();//you have to access the records in the dynaset to get GCDaoRecordSet::SetRecordCount() to work    return TRUE;
    return TRUE;
}

BOOL ZCDatabaseListCtrl::CloseDatabase()
{
    if(m_pRecordSet != NULL)
    {
        ASSERT_VALID(m_pRecordSet);
        if(m_pRecordSet->IsOpen())
            m_pRecordSet->Close();
        delete m_pRecordSet;
        m_pRecordSet = NULL;
    }

    if(m_pDataBase != NULL)
    {
        ASSERT_VALID(m_pDataBase);
        if(m_pDataBase->IsOpen())
            m_pDataBase->Close();
        delete m_pDataBase;
        m_pDataBase = NULL;
    }
    return TRUE;
}

BOOL ZCDatabaseListCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.lpszName = WC_LISTVIEW;
    cs.style &= ~LVS_TYPEMASK;
    cs.style |= LVS_REPORT;
    cs.style |= LVS_OWNERDATA;
    return ZIListCtrl::PreCreateWindow(cs);
}


BOOL ZCDatabaseListCtrl::Initialize( const CString DatabaseFilename, const CString Tablename )
{
    m_DatabaseFilename = DatabaseFilename;
    m_Tablename = Tablename;
    if (!OpenDatabase())
        return FALSE;

    ZCDatabaseListCtrl::BuildColumns();
    return TRUE;
}


BOOL ZCDatabaseListCtrl::Refresh()
{
    DeleteAllItems();
    CloseDatabase();
    return OpenDatabase();
}


void ZCDatabaseListCtrl::BuildColumns()
{
    if (m_ColumnsBuilt)
        return;

    /*set number of items in list to number of items in RecordSet*/    
    /* create image list*/
    CDaoRecordset* pRecordSet = GetRecordSet();
    if(pRecordSet != NULL)
    {
        m_pImageList = new CImageList();
        m_pImageList->Create(IDB_DATABASEIMAGELIST, 16, 1, RGB(0,0,0));
        SetImageList(m_pImageList, LVSIL_SMALL);    /* set extended stlyes*/
        
        DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | /*LVS_EX_SUBITEMIMAGES |*/
                            LVS_EX_HEADERDRAGDROP | LVS_EX_TRACKSELECT;
        SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LPARAM(dwExStyle));    
        
        LV_COLUMN lvColumn;
        lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvColumn.fmt = LVCFMT_LEFT;    lvColumn.cx = 120;
        for(int i = 0; i < pRecordSet->GetFieldCount(); i++) // set up columns
        {
            CDaoFieldInfo m_fieldinfo;
            pRecordSet->GetFieldInfo(i, m_fieldinfo);//get field name
            int len = m_fieldinfo.m_strName.GetLength();
            CString temp = m_fieldinfo.m_strName;
            TCHAR* szBuffer = new TCHAR[len + 1];
            strcpy(szBuffer, temp.GetBuffer(len));
            temp.ReleaseBuffer();
            lvColumn.pszText = szBuffer;
            InsertColumn(i, &lvColumn);//insert column        
            delete szBuffer;
        }
        /*set number of items in ListView*/
        long count = GetRecordCount();//Get number of records
        SendMessage(LVM_SETITEMCOUNT, (WPARAM)count, (LPARAM)LVSICF_NOINVALIDATEALL);
    }
    
    m_ColumnsBuilt = TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// ZCDatabaseListCtrl message handlers

void ZCDatabaseListCtrl::OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
    LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
    TCHAR szValue[MAX_PATH];
    szValue[0] = '\0';
    CDaoRecordset* pRecordSet = GetRecordSet();
    if(!pRecordSet)
        return;

    COleVariant varValue;
    long index = pDispInfo->item.iItem;
    long subItem =     pDispInfo->item.iSubItem;


    if(pDispInfo->item.mask & LVIF_TEXT)
    {
        try
        {
            pRecordSet->SetAbsolutePosition(index);//Set the file to desired index
        }
        catch(CDaoException* e)
        {
            AfxMessageBox(e->m_pErrorInfo->m_strDescription, 
                    MB_ICONEXCLAMATION );
            e->Delete();
            return;
        }
        
        try
        {
            if(subItem)    
                pRecordSet->GetFieldValue(subItem, varValue);
            else
                pRecordSet->GetFieldValue(0, varValue);
        }
        catch(CDaoException* e)
        {
            AfxMessageBox(e->m_pErrorInfo->m_strDescription, 
                    MB_ICONEXCLAMATION );
            e->Delete();
            return;
        }

        const VARIANT* variant = LPCVARIANT(varValue);
        
        if(variant->vt & VT_BYREF)
            return;
        
        switch(variant->vt)
        {
            case VT_ERROR:{    
                            strcpy(szValue, "Error");                    
                            break;
                          }
            case VT_I2:{    wsprintf(szValue, "%d", variant->iVal);
                            break;
                       }
            case VT_I4:{    wsprintf(szValue, "%d", variant->lVal);
                            break;
                       }
            case VT_R4:{    wsprintf(szValue, "%f", variant->fltVal);
                            break;
                       }    
            case VT_R8:{    wsprintf(szValue, "%f", variant->dblVal);
                            break;
                       }
            case VT_CY:{    COleCurrency c(varValue);
                            CString s = c.Format();//ie. 1.00
                            strcpy(szValue, s.GetBuffer(s.GetLength()));
                            s.ReleaseBuffer();
                            break;
                       }
            case VT_DATE:{    COleDateTime t(variant->date);
                            CString s = t.Format( "%B %d, %Y" );//Day of Week, Month Day, Year
                            strcpy(szValue, s.GetBuffer(s.GetLength()));
                            s.ReleaseBuffer();
                            break;
                         }
            case VT_BSTR:{  CString str = V_BSTRT( &varValue );//convert BSTR to CString
                            strcpy(szValue, str.GetBuffer(str.GetLength()));
                            str.ReleaseBuffer();
                            break;
                        }
            case VT_BOOL:{    if(variant->boolVal)
                                strcpy(szValue, "TRUE");
                            else
                                strcpy(szValue, "FALSE");
                            break;
                         }
            case VT_UI1:{    wsprintf(szValue, "%d", variant->bVal);
                            break;
                        }

                default:{
                            szValue[0] = '\0';
                            break;
                        }

        }
        lstrcpyn(pDispInfo->item.pszText, szValue, pDispInfo->item.cchTextMax);//set item text
    }
    
    if(pDispInfo->item.mask & LVIF_IMAGE)
        pDispInfo->item.iImage = 0;//set image to first in list

    *pResult = 0;
} 


CDaoRecordset* ZCDatabaseListCtrl::GetRecordSet()
{
    return m_pRecordSet;
}

long ZCDatabaseListCtrl::GetRecordCount()
{
    if(m_pRecordSet)
        return m_pRecordSet->GetRecordCount();

    return 0;
}


