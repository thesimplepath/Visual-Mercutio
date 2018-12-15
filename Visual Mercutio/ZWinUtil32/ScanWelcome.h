#if !defined(AFX_ZIScanWelcome_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
#define AFX_ZIScanWelcome_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanWelcome.h : header file
//

#include "zBaseLib\ZWizard.h"

#ifndef _WIN32
    #include "ZWinUtil.h"
#endif
#ifdef _WIN32
    #include "ZWinUtil32.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIScanWelcome dialog

class ZIScanWelcome : public ZIWizardDialog
{
// Construction
public:
    ZIScanWelcome(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(ZIScanWelcome)
    enum { IDD = IDD_WZSCANNING_WELCOME };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIScanWelcome)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZIScanWelcome)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()


private:

};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZIScanWelcome_H__4CB3C463_579F_11D3_9612_0000B45D7C6F__INCLUDED_)
