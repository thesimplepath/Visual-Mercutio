// ScanInfo.cpp : implementation file
//

#include "stdafx.h"
#include "ScanInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIScanInformation dialog


ZIScanInformation::ZIScanInformation(const CString Name /*= ""*/, const CString Description /*= ""*/, CWnd* pParent /*=NULL*/)
    : ZIWizardDialog(ZIScanInformation::IDD, // Dialog template
                     IDB_WZBMP3,    // Bitmap to display
                     0,            // Icon do display
                     0,                    // Window Title
                     IDS_SCANNINGINFO_S,    // Wizard title
                     IDS_SCANNINGINFO_T    // Wizard text
                    )
{
    //{{AFX_DATA_INIT(ZIScanInformation)
    m_Description = Description;
    m_Name = Name;
    //}}AFX_DATA_INIT
}


void ZIScanInformation::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIScanInformation)
    DDX_Text(pDX, IDC_SCAN_DESCRIPTION, m_Description);
    DDX_Text(pDX, IDC_SCAN_NAME, m_Name);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZIScanInformation, ZIWizardDialog)
    //{{AFX_MSG_MAP(ZIScanInformation)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIScanInformation message handlers

BOOL ZIScanInformation::OnInitDialog() 
{
    ZIWizardDialog::OnInitDialog();
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void ZIScanInformation::OnOK() 
{
    if (m_Name.IsEmpty())
    {
        return;
    }
    
    ZIWizardDialog::OnOK();
}
