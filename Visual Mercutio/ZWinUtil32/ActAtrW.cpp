// ActAtrW.cpp : implementation file
//

#include "stdafx.h"
#include "ActAtrW.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIActivityAttributionWelcome dialog


ZIActivityAttributionWelcome::ZIActivityAttributionWelcome(ZActivity* pActivity, CWnd* pParent /*=NULL*/)
    : ZIWizardDialog(ZIActivityAttributionWelcome::IDD, // Dialog template
                     IDB_WZBMP1,    // Bitmap to display
                     0,            // Icon do display
                     0,                    // Window Title
                     IDS_ATTRIBUTIONTITLEST_WZ, // Wizard title
                     IDS_ATTRIBUTIONSTTEXTE_WZ    // Wizard text
                    ), 
                    m_pActivity(pActivity)
{
    //{{AFX_DATA_INIT(ZIActivityAttributionWelcome)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void ZIActivityAttributionWelcome::DoDataExchange(CDataExchange* pDX)
{
    ZIWizardDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIActivityAttributionWelcome)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZIActivityAttributionWelcome, ZIWizardDialog)
    //{{AFX_MSG_MAP(ZIActivityAttributionWelcome)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIActivityAttributionWelcome message handlers

BOOL ZIActivityAttributionWelcome::OnInitDialog() 
{
    ZIWizardDialog::OnInitDialog();
    
    CString    prompt;
    AfxFormatString1( prompt, IDS_ATTRIBUTIONACTIVITY_WTEXT, m_pActivity->GetName() );
    
    if (GetDlgItem(IDC_STATIC_TEXTATTR))
       GetDlgItem(IDC_STATIC_TEXTATTR)->SetWindowText( prompt );

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
