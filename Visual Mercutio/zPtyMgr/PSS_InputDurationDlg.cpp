/****************************************************************************
 * ==> PSS_InputDurationDlg ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a dialog box to input a duration                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_InputDurationDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_InputDurationDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_InputDurationDlg)
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_InputDurationDlg
//---------------------------------------------------------------------------
PSS_InputDurationDlg::PSS_InputDurationDlg(int  days,
                                           int  hours,
                                           int  minutes,
                                           int  seconds,
                                           CWnd*pParent) :
    CDialog(PSS_InputDurationDlg::IDD, pParent),
    m_Days(days),
    m_Hours(hours),
    m_Minutes(minutes),
    m_Seconds(seconds)
{}
//---------------------------------------------------------------------------
void PSS_InputDurationDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_InputDurationDlg)
    DDX_Text(pDX, IDC_DURATION_DAY,    m_Days);
    DDX_Text(pDX, IDC_DURATION_HOUR,   m_Hours);
    DDX_Text(pDX, IDC_DURATION_MINUTE, m_Minutes);
    DDX_Text(pDX, IDC_DURATION_SECOND, m_Seconds);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_InputDurationDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_InputDurationDlg::OnOK()
{
    UpdateData(TRUE);
    CDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_InputDurationDlg::OnCancel()
{
    UpdateData(TRUE);
    CDialog::OnCancel();
}
//---------------------------------------------------------------------------
void PSS_InputDurationDlg::OnClose()
{
    CDialog::OnClose();
}
//---------------------------------------------------------------------------
