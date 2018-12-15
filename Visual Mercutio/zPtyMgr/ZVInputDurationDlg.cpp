/************************************************************************************************************
 *                                             Classe ZVInputDurationDlg                                    *
 ************************************************************************************************************
 * Cette classe s'occupe de la gestion de la boîte de dialogue permettant de paramétrer la durée.            *
 ************************************************************************************************************/

#include "stdafx.h"
#include "ZVInputDurationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVInputDurationDlg dialog

ZVInputDurationDlg::ZVInputDurationDlg( int        Days    /*= 0*/,
                                        int        Hours    /*= 0*/,
                                        int        Minutes    /*= 0*/,
                                        int        Seconds    /*= 0*/,
                                        CWnd*    pParent    /*=NULL*/)
    : CDialog( ZVInputDurationDlg::IDD, pParent )
{
    //{{AFX_DATA_INIT(ZVInputDurationDlg)
    m_Days        = Days;
    m_Hours        = Hours;
    m_Minutes    = Minutes;
    m_Seconds    = Seconds;
    //}}AFX_DATA_INIT
}

void ZVInputDurationDlg::DoDataExchange( CDataExchange* pDX )
{
    CDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(ZVInputDurationDlg)
    DDX_Text( pDX, IDC_DURATION_DAY, m_Days );
    DDX_Text( pDX, IDC_DURATION_HOUR, m_Hours );
    DDX_Text( pDX, IDC_DURATION_MINUTE, m_Minutes );
    DDX_Text( pDX, IDC_DURATION_SECOND, m_Seconds );
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP( ZVInputDurationDlg, CDialog )
    //{{AFX_MSG_MAP(ZVInputDurationDlg)
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVInputDurationDlg message handlers

BOOL ZVInputDurationDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVInputDurationDlg::OnOK() 
{
    UpdateData( TRUE );
    CDialog::OnOK();
}
void ZVInputDurationDlg::OnCancel() 
{
    UpdateData( TRUE );
    CDialog::OnCancel();
}

void ZVInputDurationDlg::OnClose() 
{    
    CDialog::OnClose();
}
