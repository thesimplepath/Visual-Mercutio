// ZIChooseServerSel.cpp : implementation file

#include "stdafx.h"
#include "ZIChooseServerSel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 9 avril 2007 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZIChooseServerSelect dialog

BEGIN_MESSAGE_MAP( ZIChooseServerSelect, ZIWizardDialog )
    //{{AFX_MSG_MAP(ZIChooseServerSelect)
    ON_NOTIFY(TVN_SELCHANGED, IDC_SERVERDIRECTORY, OnSelchangedDirectory)
    ON_NOTIFY(NM_DBLCLK, IDC_SERVERDIRECTORY, OnDblclkDirectory)
    ON_NOTIFY(NM_CLICK, IDC_SERVERDIRECTORY, OnClickDirectory)
    ON_EN_CHANGE(IDC_SERVERCHOOSED, OnChangeServerChoosed)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZIChooseServerSelect::ZIChooseServerSelect( BOOL Local, CWnd* pParent /*=NULL*/ )
    : ZIWizardDialog( ZIChooseServerSelect::IDD,    // Dialog template
                      IDB_WZBMP3,                    // Bitmap to display
                      0,                            // Icon do display
                      0,                            // Window Title
                      IDS_SELECTIONSERVERWLC_SL,    // Wizard title
                      IDS_SELECTIONSERVERWLC_TL ),    // Wizard text
      m_Local        ( Local )
{
    //{{AFX_DATA_INIT(ZIChooseServerSelect)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT

    if ( !m_Local )
    {
        SetWizardSubjectText( IDS_SELECTIONSERVERWLC_SG );
        SetWizardBodyText( IDS_SELECTIONSERVERWLC_TG );
    }
}

void ZIChooseServerSelect::DoDataExchange( CDataExchange* pDX )
{
    ZIWizardDialog::DoDataExchange( pDX );

    //{{AFX_DATA_MAP(ZIChooseServerSelect)
    DDX_Control(pDX, IDC_SERVERDIRECTORY, m_DirTreeCtrl);
    DDX_Text(pDX, IDC_SERVERCHOOSED, m_Directory);
    //}}AFX_DATA_MAP
}

void ZIChooseServerSelect::CheckControlStates()
{
    UpdateData();

    if ( GetDlgItem( IDOK ) )
    {
        GetDlgItem( IDOK )->EnableWindow( !m_DirTreeCtrl.GetSelectedDirectory().IsEmpty() || !m_Directory.IsEmpty() );
    }
}

/////////////////////////////////////////////////////////////////////////////
// ZIChooseServerSelect message handlers

BOOL ZIChooseServerSelect::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();
    m_DirTreeCtrl.Initialize();
    CheckControlStates();

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZIChooseServerSelect::ReflectChangedDirectory()
{
    CheckControlStates();

    if ( m_DirTreeCtrl.IsValid() )
    {
        m_Directory = m_DirTreeCtrl.GetSelectedDirectory();
        UpdateData( FALSE );
    }
}

void ZIChooseServerSelect::OnSelchangedDirectory( NMHDR* pNMHDR, LRESULT* pResult )
{
    ReflectChangedDirectory();
    *pResult = 0;
}

void ZIChooseServerSelect::OnDblclkDirectory( NMHDR* pNMHDR, LRESULT* pResult )
{
    ReflectChangedDirectory();
    *pResult = 0;
}

void ZIChooseServerSelect::OnClickDirectory( NMHDR* pNMHDR, LRESULT* pResult )
{
    ReflectChangedDirectory();
    *pResult = 0;
}

void ZIChooseServerSelect::OnOK()
{
    m_Directory = m_DirTreeCtrl.GetSelectedDirectory();
    ZIWizardDialog::OnOK();
}

void ZIChooseServerSelect::OnChangeServerChoosed()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the ZIWizardDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    CheckControlStates();
}
