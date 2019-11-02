/****************************************************************************
 * ==> PSS_DatabaseListCtrl ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a database list controller                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DatabaseListCtrl.h"

// resources
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DatabaseListCtrl, PSS_ListCtrl)
    //{{AFX_MSG_MAP(PSS_DatabaseListCtrl)
    ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetDispInfo)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DatabaseListCtrl
//---------------------------------------------------------------------------
PSS_DatabaseListCtrl::PSS_DatabaseListCtrl(const CString& fileName, const CString& tableName) :
    PSS_ListCtrl(),
    m_pRecordSet(NULL),
    m_pDataBase(NULL),
    m_FileName(fileName),
    m_TableName(tableName),
    m_ColumnsBuilt(FALSE)
{}
//---------------------------------------------------------------------------
PSS_DatabaseListCtrl::PSS_DatabaseListCtrl(const PSS_DatabaseListCtrl& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_DatabaseListCtrl::~PSS_DatabaseListCtrl()
{
    CloseDatabase();
}
//---------------------------------------------------------------------------
const PSS_DatabaseListCtrl& PSS_DatabaseListCtrl::operator = (const PSS_DatabaseListCtrl& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_DatabaseListCtrl::Initialize(const CString& fileName, const CString& tableName)
{
    m_FileName  = fileName;
    m_TableName = tableName;

    if (!OpenDatabase())
        return FALSE;

    BuildColumns();
    return TRUE;
}
//---------------------------------------------------------------------------
CDaoRecordset* PSS_DatabaseListCtrl::GetRecordSet()
{
    return m_pRecordSet;
}
//---------------------------------------------------------------------------
long PSS_DatabaseListCtrl::GetRecordCount() const
{
    if (m_pRecordSet)
        return m_pRecordSet->GetRecordCount();

    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_DatabaseListCtrl::Refresh()
{
    DeleteAllItems();
    CloseDatabase();
    return OpenDatabase();
}
//---------------------------------------------------------------------------
BOOL PSS_DatabaseListCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.lpszName  =  WC_LISTVIEW;
    cs.style    &= ~LVS_TYPEMASK;
    cs.style    |=  LVS_REPORT;
    cs.style    |=  LVS_OWNERDATA;

    return PSS_ListCtrl::PreCreateWindow(cs);
}
//---------------------------------------------------------------------------
void PSS_DatabaseListCtrl::OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
    LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

    TCHAR value[MAX_PATH];
    value[0] = '\0';

    CDaoRecordset* pRecordSet = GetRecordSet();

    if (!pRecordSet)
        return;

    const long index   = pDispInfo->item.iItem;
    const long subItem = pDispInfo->item.iSubItem;


    if (pDispInfo->item.mask & LVIF_TEXT)
    {
        try
        {
            // set the file to desired index
            pRecordSet->SetAbsolutePosition(index);
        }
        catch (CDaoException* e)
        {
            AfxMessageBox(e->m_pErrorInfo->m_strDescription, MB_ICONEXCLAMATION);
            e->Delete();
            return;
        }

        COleVariant varValue;

        try
        {
            if (subItem)
                pRecordSet->GetFieldValue(subItem, varValue);
            else
                pRecordSet->GetFieldValue(0, varValue);
        }
        catch (CDaoException* e)
        {
            AfxMessageBox(e->m_pErrorInfo->m_strDescription, MB_ICONEXCLAMATION);
            e->Delete();
            return;
        }

        const VARIANT* variant = LPCVARIANT(varValue);

        if (variant->vt & VT_BYREF)
            return;

        switch (variant->vt)
        {
            case VT_ERROR:
                strcpy_s(value, _tcslen(value), "Error");
                break;

            case VT_I2:
                wsprintf(value, "%d", variant->iVal);
                break;

            case VT_I4:
                wsprintf(value, "%d", variant->lVal);
                break;

            case VT_R4:
                wsprintf(value, "%f", variant->fltVal);
                break;

            case VT_R8:
                wsprintf(value, "%f", variant->dblVal);
                break;

            case VT_CY:
            {
                COleCurrency c(varValue);

                // i.e. 1.00
                CString s = c.Format();
                strcpy_s(value, _tcslen(value), s.GetBuffer(s.GetLength()));
                s.ReleaseBuffer();
                break;
            }

            case VT_DATE:
            {
                COleDateTime t(variant->date);

                // day of week, month, day, year
                CString s = t.Format("%B %d, %Y");
                strcpy_s(value, _tcslen(value), s.GetBuffer(s.GetLength()));
                s.ReleaseBuffer();
                break;
            }

            case VT_BSTR:
            {
                // convert BSTR to CString
                CString str = V_BSTRT(&varValue);
                strcpy_s(value, _tcslen(value), str.GetBuffer(str.GetLength()));
                str.ReleaseBuffer();
                break;
            }

            case VT_BOOL:
                if (variant->boolVal)
                    strcpy_s(value, _tcslen(value), "TRUE");
                else
                    strcpy_s(value, _tcslen(value), "FALSE");

                break;

            case VT_UI1:
                wsprintf(value, "%d", variant->bVal);
                break;

            default:
                value[0] = '\0';
                break;
        }

        // set item text
        lstrcpyn(pDispInfo->item.pszText, value, pDispInfo->item.cchTextMax);
    }

    // set image to first in list
    if (pDispInfo->item.mask & LVIF_IMAGE)
        pDispInfo->item.iImage = 0;

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_DatabaseListCtrl::BuildColumns()
{
    if (m_ColumnsBuilt)
        return;

    // set list item count to record set item count and create image list
    CDaoRecordset* pRecordSet = GetRecordSet();

    if (pRecordSet)
    {
        m_pImageList = new CImageList();
        m_pImageList->Create(IDB_DATABASEIMAGELIST, 16, 1, RGB(0, 0, 0));

        // set extended stlye
        SetImageList(m_pImageList, LVSIL_SMALL);

        const DWORD exStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_TRACKSELECT;
        SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LPARAM(exStyle));

        LV_COLUMN lvColumn;
        lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvColumn.fmt  = LVCFMT_LEFT;
        lvColumn.cx   = 120;

        // setup columns
        for (int i = 0; i < pRecordSet->GetFieldCount(); ++i)
        {
            CDaoFieldInfo m_fieldinfo;
            pRecordSet->GetFieldInfo(i, m_fieldinfo);

            TCHAR* pBuffer = NULL;

            try
            {
                const int len  = m_fieldinfo.m_strName.GetLength();
                CString   temp = m_fieldinfo.m_strName;

                // get field name
                pBuffer = new TCHAR[len + 1];
                strcpy_s(pBuffer, _tcslen(pBuffer), temp.GetBuffer(len));
                temp.ReleaseBuffer();
                lvColumn.pszText = pBuffer;

                // insert column
                InsertColumn(i, &lvColumn);
            }
            catch (...)
            {
                if (pBuffer)
                    delete pBuffer;

                throw;
            }

            delete pBuffer;
        }

        // set list view item count
        const long count = GetRecordCount();
        SendMessage(LVM_SETITEMCOUNT, WPARAM(count), LPARAM(LVSICF_NOINVALIDATEALL));
    }

    m_ColumnsBuilt = TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DatabaseListCtrl::OpenDatabase()
{
    // close the database if already opened
    CloseDatabase();

    // open the database
    m_pDataBase = new CDaoDatabase;

    try
    {
        m_pDataBase->Open(m_FileName);
    }
    catch (CDaoException* e)
    {
        AfxMessageBox(e->m_pErrorInfo->m_strDescription, MB_ICONEXCLAMATION);
        delete m_pDataBase;
        e->Delete();

        return FALSE;
    }

    m_pRecordSet               = new CDaoRecordset(m_pDataBase);
    const CString sqlStatement = "SELECT * FROM " + m_TableName;

    try
    {
        // open recordset using SQL statement
        m_pRecordSet->Open(dbOpenDynaset, sqlStatement);
    }
    catch (CDaoException* e)
    {
        AfxMessageBox(e->m_pErrorInfo->m_strDescription, MB_ICONEXCLAMATION);
        delete m_pRecordSet;

        m_pDataBase->Close();

        delete m_pDataBase;
        e->Delete();

        return FALSE;
    }

    // access the records in the dynaset to get GCDaoRecordSet::SetRecordCount() to work
    if (!m_pRecordSet->IsEOF())
        m_pRecordSet->MoveLast();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DatabaseListCtrl::CloseDatabase()
{
    if (m_pRecordSet)
    {
        ASSERT_VALID(m_pRecordSet);

        if (m_pRecordSet->IsOpen())
            m_pRecordSet->Close();

        delete m_pRecordSet;
        m_pRecordSet = NULL;
    }

    if (m_pDataBase)
    {
        ASSERT_VALID(m_pDataBase);

        if (m_pDataBase->IsOpen())
            m_pDataBase->Close();

        delete m_pDataBase;
        m_pDataBase = NULL;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
