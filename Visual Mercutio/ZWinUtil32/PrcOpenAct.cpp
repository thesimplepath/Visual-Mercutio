// PrcOpenAct.cpp : implementation file
//

#include "stdafx.h"
#include "PrcOpenAct.h"
#include "zBaseLib\File.h"

// ZAGlobal
#include "zBaseLib\ZAGlobal.h"

#include "ZVFormFilePreviewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVOpenProcessActions dialog


ZVOpenProcessActions::ZVOpenProcessActions(const CString Filename, const CString ActivityName, CWnd* pParent /*=NULL*/)
    : ZIDialog(ZVOpenProcessActions::IDD, TRUE, pParent),
    m_Filename(Filename), m_ActivityName(ActivityName)
{
    //{{AFX_DATA_INIT(ZVOpenProcessActions)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void ZVOpenProcessActions::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVOpenProcessActions)
    DDX_Control(pDX, IDC_VISUALIZE, m_ViewCommandBtn);
    DDX_Control(pDX, IDC_CANCELCOMMAND, m_CancelCommandBtn);
    DDX_Control(pDX, IDC_OPENPROCESS, m_AcceptCommandBtn);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVOpenProcessActions, ZIDialog)
    //{{AFX_MSG_MAP(ZVOpenProcessActions)
    ON_BN_CLICKED(IDC_VISUALIZE, OnViewCommand)
    ON_BN_CLICKED(IDC_CANCELCOMMAND, OnCancelCommand)
    ON_BN_CLICKED(IDC_OPENPROCESS, OnAcceptCommand)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVOpenProcessActions message handlers

void ZVOpenProcessActions::OnAcceptCommand() 
{
    EndDialog( IDOK );
}

void ZVOpenProcessActions::OnCancelCommand() 
{
    EndDialog( IDCANCEL );
}

void ZVOpenProcessActions::OnViewCommand() 
{
    // Launch the file in preview
    ZFile    File(m_Filename);
    if (File.Exist())
    {
        ZVFormFilePreviewDlg    FilePreviewDlg( m_Filename, ZAGlobal::GetpProcessDocTemplate() );
        FilePreviewDlg.DoModal();
    }
}


BOOL ZVOpenProcessActions::OnInitDialog() 
{
    ZIDialog::OnInitDialog();

    if (GetDlgItem(IDC_OPENADMIN_TEXT))
    {
        CString    Text;
        GetDlgItem(IDC_OPENADMIN_TEXT)->GetWindowText( Text );
        CString prompt;
        prompt.Format( Text, m_ActivityName );
        GetDlgItem(IDC_OPENADMIN_TEXT)->SetWindowText( prompt );

    }
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


