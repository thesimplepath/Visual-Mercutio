// PrcTkOwner.cpp : implementation file
//

#include "stdafx.h"
#include "PrcTkOwner.h"
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
// ZVTakeOwnerShipActions dialog


ZVTakeOwnerShipActions::ZVTakeOwnerShipActions(const CString Filename, const CString ActivityName, CWnd* pParent /*=NULL*/)
    : ZIDialog(ZVTakeOwnerShipActions::IDD, TRUE, pParent),
    m_Filename(Filename), m_ActivityName(ActivityName)
{
    //{{AFX_DATA_INIT(ZVTakeOwnerShipActions)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void ZVTakeOwnerShipActions::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVTakeOwnerShipActions)
    DDX_Control(pDX, IDC_VISUALIZE, m_ViewCommandBtn);
    DDX_Control(pDX, IDC_CANCELCOMMAND, m_CancelCommandBtn);
    DDX_Control(pDX, IDC_TAKEOWNERSHIP, m_AcceptCommandBtn);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVTakeOwnerShipActions, ZIDialog)
    //{{AFX_MSG_MAP(ZVTakeOwnerShipActions)
    ON_BN_CLICKED(IDC_VISUALIZE, OnViewCommand)
    ON_BN_CLICKED(IDC_CANCELCOMMAND, OnCancelCommand)
    ON_BN_CLICKED(IDC_TAKEOWNERSHIP, OnAcceptCommand)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVTakeOwnerShipActions message handlers

void ZVTakeOwnerShipActions::OnAcceptCommand() 
{
    EndDialog( IDOK );
}

void ZVTakeOwnerShipActions::OnCancelCommand() 
{
    EndDialog( IDCANCEL );
}

void ZVTakeOwnerShipActions::OnViewCommand() 
{
    // Launch the file in preview
    ZFile    File(m_Filename);
    if (File.Exist())
    {
        ZVFormFilePreviewDlg    FilePreviewDlg( m_Filename, ZAGlobal::GetpProcessDocTemplate() );
        FilePreviewDlg.DoModal();
    }
}


BOOL ZVTakeOwnerShipActions::OnInitDialog() 
{
    ZIDialog::OnInitDialog();

    if (GetDlgItem(IDC_OWNERSHIP_TEXT))
    {
        CString    Text;
        GetDlgItem(IDC_OWNERSHIP_TEXT)->GetWindowText( Text );
        CString prompt;
        prompt.Format( Text, m_ActivityName );
        GetDlgItem(IDC_OWNERSHIP_TEXT)->SetWindowText( prompt );

    }
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


