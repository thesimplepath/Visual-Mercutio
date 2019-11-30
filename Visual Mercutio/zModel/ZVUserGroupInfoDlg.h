#if !defined(AFX_ZVUserGroupInfoDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_)
#define AFX_ZVUserGroupInfoDlg_H__5CDA1CC0_FE18_47C1_BBCB_4FF3CA656F62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVUserGroupInfoDlg.h : header file
//

#include "zModelRes.h"

// forward class declaration
class ZBUserGroupEntity;


/////////////////////////////////////////////////////////////////////////////
// ZVUserGroupInfoDlg dialog

class ZVUserGroupInfoDlg : public CDialog
{
// Construction
public:
    ZVUserGroupInfoDlg(UINT nTitleID = -1, 
                       ZBUserGroupEntity* pGroup = NULL, 
                       const CString Name = "", 
                       const CString Description = "", 
                       const float Cost = 0, 
                       bool IsARole = false,
                       bool ModifyMode = false, 
                       CWnd* pParent = NULL);   // standard constructor

    CString    GetDescription() const
    {
        return m_Description;
    };
    CString    GetName() const
    {
        return m_Name;
    };
    float GetCost() const
    {
        return m_fCost;
    };

private:
// Dialog Data
    //{{AFX_DATA(ZVUserGroupInfoDlg)
    enum { IDD = IDD_UGP_INFO };
    CString    m_Description;
    CString    m_Name;
    CString m_Cost;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVUserGroupInfoDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVUserGroupInfoDlg)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    ZBUserGroupEntity* m_pGroup;
    float m_fCost;
    CString m_Title;
    bool m_IsARole;
    bool m_ModifyMode;
};

#endif
