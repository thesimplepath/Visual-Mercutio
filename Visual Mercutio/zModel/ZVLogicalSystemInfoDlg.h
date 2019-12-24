#if !defined(AFX_ZVLogicalSystemInfoDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_)
#define AFX_ZVLogicalSystemInfoDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zModelRes.h"

// old class name mapping
#ifndef PSS_LogicalSystemEntity
    #define PSS_LogicalSystemEntity ZBLogicalSystemEntity
#endif

// forward class declaration
class PSS_LogicalSystemEntity;

/////////////////////////////////////////////////////////////////////////////
// ZVLogicalSystemInfoDlg dialog

class ZVLogicalSystemInfoDlg : public CDialog
{
    // Construction
public:

    // Standard constructor
    ZVLogicalSystemInfoDlg(UINT                    nTitleID = -1,
                           PSS_LogicalSystemEntity*    pLogicalSystem = NULL,
                           const CString            Name = _T(""),
                           const CString            Description = _T(""),
                           bool                    ModifyMode = false,
                           CWnd*                    pParent = NULL);

    CString GetDescription() const
    {
        return m_Description;
    };

    CString GetName() const
    {
        return m_Name;
    };

    // Dialog Data
private:

    //{{AFX_DATA(ZVLogicalSystemInfoDlg)
    enum
    {
        IDD = IDD_LOGICALSYSTEM_INFO
    };
    CString m_Description;
    CString m_Name;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVLogicalSystemInfoDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVLogicalSystemInfoDlg)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    PSS_LogicalSystemEntity* m_pLogicalSystem;
    CString                  m_Title;
    bool                     m_ModifyMode;
};

#endif
