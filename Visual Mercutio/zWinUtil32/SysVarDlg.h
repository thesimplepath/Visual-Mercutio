#if !defined(AFX_SYSVARDLG_H__685ED326_C840_11D3_96A9_0000B45D7C6F__INCLUDED_)
#define AFX_SYSVARDLG_H__685ED326_C840_11D3_96A9_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysVarDlg.h : header file
//
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zwinutil32.h"
#include "zBaseLib\ZIDialog.h"



#ifdef _ZWINUTIL32EXPORT
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


/////////////////////////////////////////////////////////////////////////////
// ZISysVarDlg dialog

class AFX_EXT_CLASS ZISysVarDlg : public ZIDialog
{
// Construction
public:
    ZISysVarDlg(CWnd* pParent = NULL);   // standard constructor
    const CString GetKeyword() const { return m_Keyword; };

private:
// Dialog Data
    //{{AFX_DATA(ZISysVarDlg)
    enum { IDD = IDD_SYSTEMVAR };
    CListBox    m_SysVarList;
    //}}AFX_DATA

    CString    m_Keyword;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZISysVarDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZISysVarDlg)
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnSelchangeSystemVarlist();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSVARDLG_H__685ED326_C840_11D3_96A9_0000B45D7C6F__INCLUDED_)
