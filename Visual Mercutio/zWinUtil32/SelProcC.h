#if !defined(AFX_SELPROCC_H__B6801F53_4E39_11D3_9604_0000B45D7C6F__INCLUDED_)
#define AFX_SELPROCC_H__B6801F53_4E39_11D3_9604_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZWizard.h"
#include "ZSearchEdit.h"

// resources
#ifndef _WIN32
    #include "ZWinUtilRes.h"
#else
    #include "ZWinUtil32Res.h"
#endif

#include "zEvent\ZProcess.h"
#include "PSS_ActivityListCtrl.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// ZISelectProcessWizardChoose dialog

class ZISelectProcessWizardChoose : public ZIWizardDialog
{
// Construction
public:
    ZISelectProcessWizardChoose(ZProcess& Process, CWnd* pParent = NULL);   // standard constructor
    CString    GetBaseActivityName() const { return m_BaseActivityName; };

private:
// Dialog Data
    //{{AFX_DATA(ZISelectProcessWizardChoose)
    enum { IDD = IDD_WZCHOOSEPROC_SEL };
    PSS_ActivityListCtrl m_ActivityProcList;
    CString              m_ProcessName;
    //}}AFX_DATA

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZISelectProcessWizardChoose)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZISelectProcessWizardChoose)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnClickActivityProcList(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    ZProcess&         m_Process;
    CString            m_BaseActivityName;

private:
    void CheckControlStates();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELPROCC_H__B6801F53_4E39_11D3_9604_0000B45D7C6F__INCLUDED_)
