/************************************************************************************************************
 *                                             Classe ZVInputDurationDlg                                    *
 ************************************************************************************************************
 * Cette classe s'occupe de la gestion de la boîte de dialogue permettant de paramétrer la durée.            *
 ************************************************************************************************************/

#if !defined(AFX_ZVINPUTDURATIONDLG_H__3442D651_5356_49DC_B47B_8DA85B5CB2DB__INCLUDED_)
#define AFX_ZVINPUTDURATIONDLG_H__3442D651_5356_49DC_B47B_8DA85B5CB2DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZVInputDurationDlg.h : header file

#include "zPtyMgrRes.h"

/////////////////////////////////////////////////////////////////////////////
// ZVInputDurationDlg dialog

class ZVInputDurationDlg : public CDialog
{
// Construction
public:

    ZVInputDurationDlg( int        Days    = 0,
                        int        Hours    = 0,
                        int        Minutes    = 0,
                        int        Seconds    = 0,
                        CWnd*    pParent    = NULL );   // standard constructor

    int GetDays() const
    {
        return m_Days;
    };

    int GetHours() const
    {
        return m_Hours;
    };

    int GetMinutes() const
    {
        return m_Minutes;
    };

    int GetSeconds() const
    {
        return m_Seconds;
    };

private:

    // Dialog Data
    //{{AFX_DATA(ZVInputDurationDlg)
    enum { IDD = IDD_INPUT_DURATION };
    int        m_Days;
    int        m_Hours;
    int        m_Minutes;
    int        m_Seconds;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL( ZVInputDurationDlg )
    protected:
    virtual void DoDataExchange( CDataExchange* pDX );    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    virtual void OnOK( );
    virtual void OnCancel();
    // Generated message map functions
    //{{AFX_MSG( ZVInputDurationDlg )
    virtual BOOL OnInitDialog();
    afx_msg void OnClose();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    CString m_InitialValue;
    CString m_ValueString;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZVINPUTDURATIONDLG_H__3442D651_5356_49DC_B47B_8DA85B5CB2DB__INCLUDED_)