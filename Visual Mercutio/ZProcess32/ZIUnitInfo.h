#if !defined(AFX_ZIUNITINFO_H__B82E6C6F_E48E_45C3_BCA0_AB9BDF8F9354__INCLUDED_)
#define AFX_ZIUNITINFO_H__B82E6C6F_E48E_45C3_BCA0_AB9BDF8F9354__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZIUnitInfo.h : header file
//

#include "Resource.h"
#include "zWinUtil32\ZSearchEdit.h"


/////////////////////////////////////////////////////////////////////////////
// ZIUnitInfo dialog

class ZIUnitInfo : public CDialog
{
// Construction
public:
    ZIUnitInfo(const CString Name = "", 
               const CString Directory = "", 
               bool DisplayOnly = false, 
               CWnd* pParent = NULL);   // standard constructor

    CString    GetDirectory() const { return m_Directory; };
    CString    GetUnitName() const { return m_UnitName; };

private:
// Dialog Data
    //{{AFX_DATA(ZIUnitInfo)
    enum { IDD = IDD_UNIT_INFO };
    ZCSearchEdit    m_UnitDirectory;
    CString    m_UnitName;
    //}}AFX_DATA

    CString    m_Directory;
    bool    m_DisplayOnly;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIUnitInfo)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZIUnitInfo)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZIUNITINFO_H__B82E6C6F_E48E_45C3_BCA0_AB9BDF8F9354__INCLUDED_)
