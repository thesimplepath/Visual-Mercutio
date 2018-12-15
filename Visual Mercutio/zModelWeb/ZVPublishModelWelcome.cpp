// ZVPublishModelWelcome.cpp : implementation file

#include "stdafx.h"
#include "ZVPublishModelWelcome.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 8 août 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelWelcome dialog

BEGIN_MESSAGE_MAP( ZVPublishModelWelcome, ZIWizardDialog )
    //{{AFX_MSG_MAP(ZVPublishModelWelcome)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVPublishModelWelcome::ZVPublishModelWelcome( CWnd* pParent /*= NULL*/ )
    : ZIWizardDialog( ZVPublishModelWelcome::IDD,    // Dialog template
                      IDB_WZBMP1,                    // Bitmap to display
                      0,                            // Icon do display
                      0,                            // Window Title
                      IDS_PUBLISHMODELWELCOME_S,    // Wizard title
                      IDS_PUBLISHMODELWELCOME_T )    // Wizard text
{
    //{{AFX_DATA_INIT(ZVPublishModelWelcome)
    //}}AFX_DATA_INIT
}

void ZVPublishModelWelcome::DoDataExchange( CDataExchange* pDX )
{
    ZIWizardDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(ZVPublishModelWelcome)
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelWelcome message handlers

BOOL ZVPublishModelWelcome::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}
