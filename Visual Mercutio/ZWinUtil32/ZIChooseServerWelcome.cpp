// ZIChooseServerWelcome.cpp : implementation file

#include "stdafx.h"
#include "ZIChooseServerWelcome.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 9 avril 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

BEGIN_MESSAGE_MAP( ZIChooseServerWelcome, ZIWizardDialog )
    //{{AFX_MSG_MAP(ZIChooseServerWelcome)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIChooseServerWelcome dialog

ZIChooseServerWelcome::ZIChooseServerWelcome( BOOL Local, CWnd* pParent /*=NULL*/ )
    : ZIWizardDialog( ZIChooseServerWelcome::IDD,    // Dialog template
                      IDB_WZBMP3,                    // Bitmap to display
                      0,                            // Icon do display
                      0,                            // Window Title
                      IDS_SELECTIONSERVERWLC_SL,    // Wizard title
                      IDS_SELECTIONSERVERWLC_TL ),    // Wizard text
      m_Local        ( Local )
{
    //{{AFX_DATA_INIT(ZIChooseServerWelcome)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT

    if ( !m_Local )
    {
        SetWizardSubjectText( IDS_SELECTIONSERVERWLC_SG );
        SetWizardBodyText( IDS_SELECTIONSERVERWLC_TG );
    }
}

void ZIChooseServerWelcome::DoDataExchange( CDataExchange* pDX )
{
    ZIWizardDialog::DoDataExchange( pDX );

    //{{AFX_DATA_MAP(ZIChooseServerWelcome)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZIChooseServerWelcome message handlers

BOOL ZIChooseServerWelcome::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();

    if ( GetDlgItem( IDC_STATIC_LOCAL ) )
    {
        GetDlgItem( IDC_STATIC_LOCAL )->ShowWindow( ( m_Local ) ? SW_SHOW : SW_HIDE );
    }

    if ( GetDlgItem( IDC_STATIC_GLOBAL ) )
    {
        GetDlgItem( IDC_STATIC_GLOBAL )->ShowWindow( ( m_Local ) ? SW_HIDE : SW_SHOW );
    }

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}
