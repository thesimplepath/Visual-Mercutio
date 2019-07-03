#if !defined(AFX_ZIScanContinueSelect_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
#define AFX_ZIScanContinueSelect_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanContinue.h : header file
//

#include "zBaseLib\ZWizard.h"
#include "ZSearchEdit.h"

#ifndef _WIN32
    #include "ZWinUtil.h"
#endif
#ifdef _WIN32
    #include "ZWinUtil32.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIScanContinueSelect dialog

class ZIScanContinueSelect : public ZIWizardDialog
{
// Construction
public:
    ZIScanContinueSelect(bool FirstTime, CWnd* pParent = NULL);   // standard constructor
    // Get information, if successful
    CString    GetFilename() const { return m_CompleteFilename; };

private:
// Dialog Data
    //{{AFX_DATA(ZIScanContinueSelect)
    enum { IDD = IDD_WZSCANNING_CONTINUESEL };
    ZCSearchEdit    m_File;
    int        m_ScanType;
    //}}AFX_DATA
    CString m_CompleteFilename;
    bool    m_FirstTime;


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIScanContinueSelect)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZIScanContinueSelect)
    virtual BOOL OnInitDialog();
    afx_msg void OnContinue();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()


private:

};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZIScanContinueSelect_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
