// DBLstC.h : interface of the ZCDatabaseListCtrl class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(DATABASELISTCTRL_H__A1E706A2_5F36_11D1_959E_D1A30ED05A05__INCLUDED_)
#define DATABASELISTCTRL_H__A1E706A2_5F36_11D1_959E_D1A30ED05A05__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zBaseLib\ZIListCtrl.h"


#ifdef _ZDBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

class AFX_EXT_CLASS ZCDatabaseListCtrl : public ZIListCtrl
{
// Attributes
public:
    ZCDatabaseListCtrl( const CString DatabaseFilename = "", const CString Tablename = "" );
    virtual CDaoRecordset* GetRecordSet();
    virtual long GetRecordCount();
    BOOL    Initialize( const CString DatabaseFilename, const CString Tablename );
    BOOL    Refresh();

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCDatabaseListCtrl)
    public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    protected:
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~ZCDatabaseListCtrl();

protected:
    CImageList* m_pImageList;
// Generated message map functions
protected:
    //{{AFX_MSG(ZCDatabaseListCtrl)
    afx_msg void OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    ZCDatabaseListCtrl(const ZCDatabaseListCtrl &right);
    const    ZCDatabaseListCtrl & operator=(const ZCDatabaseListCtrl &right);
    void    BuildColumns();
    BOOL    OpenDatabase();
    BOOL    CloseDatabase();

private:
    CDaoRecordset*    m_pRecordSet;
    CDaoDatabase*    m_pDataBase;
    BOOL            m_ColumnsBuilt;
    CString            m_DatabaseFilename;
    CString            m_Tablename;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(DATABASELISTCTRL_H__A1E706A2_5F36_11D1_959E_D1A30ED05A05__INCLUDED_)
