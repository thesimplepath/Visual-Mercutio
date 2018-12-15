// ProcessNameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ProcessNameDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIProcessNameDialog dialog


ZIProcessNameDialog::ZIProcessNameDialog(CWnd* pParent /*=NULL*/)
    : CDialog(ZIProcessNameDialog::IDD, pParent)
{
    //{{AFX_DATA_INIT(ZIProcessNameDialog)
    m_ProcessName = _T("");
    //}}AFX_DATA_INIT
}


void ZIProcessNameDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIProcessNameDialog)
    DDX_Text(pDX, IDC_PROCESSNAME_MODEL, m_ProcessName);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZIProcessNameDialog, CDialog)
    //{{AFX_MSG_MAP(ZIProcessNameDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIProcessNameDialog message handlers

void ZIProcessNameDialog::OnOK() 
{
    
    CDialog::OnOK();
}
