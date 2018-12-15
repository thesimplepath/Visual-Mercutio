#if !defined(AFX_PROCESSNAMEDIALOG_H__C2497BE8_2C08_4C57_90D2_86331395988F__INCLUDED_)
#define AFX_PROCESSNAMEDIALOG_H__C2497BE8_2C08_4C57_90D2_86331395988F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcessNameDialog.h : header file
//

#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// ZIProcessNameDialog dialog

class ZIProcessNameDialog : public CDialog
{
// Construction
public:
    ZIProcessNameDialog(CWnd* pParent = NULL);   // standard constructor

    const CString    ProcessName() const { return m_ProcessName; };

private:
// Dialog Data
    //{{AFX_DATA(ZIProcessNameDialog)
    enum { IDD = IDD_PROCESSNAME };
    CString    m_ProcessName;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIProcessNameDialog)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZIProcessNameDialog)
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCESSNAMEDIALOG_H__C2497BE8_2C08_4C57_90D2_86331395988F__INCLUDED_)
