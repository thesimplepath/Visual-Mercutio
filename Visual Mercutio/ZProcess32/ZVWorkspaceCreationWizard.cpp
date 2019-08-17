// ZVWorkspaceCreationWizard.cpp: implementation of the ZVWorkspaceCreationWizard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZVWorkspaceCreationWizard.h"
#include "zBaseLib\ZBWorkspaceWizardTemplateMg.h"

#include "zBaseLib\PSS_File.h"
#include "zBaseLib\ZDirectory.h"
#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 14 juin 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZVWorkspaceCreationWizard::ZVWorkspaceCreationWizard( ZBWorkspaceWizardTemplateMg*    pWorkspaceTemplateManager    /*= NULL*/,
                                                      const CString                    InitialDirectory            /*= ""*/,
                                                      const CString                    WorkspaceExtension            /*= ""*/,
                                                      bool                            Modify                        /*= false*/ )
    : m_InitialDirectory            ( InitialDirectory ),
      m_WorkspaceExtension            ( WorkspaceExtension ),
      m_Modify                        ( Modify ),
      m_pWorkspaceTemplateManager    ( pWorkspaceTemplateManager )
{
}

ZVWorkspaceCreationWizard::~ZVWorkspaceCreationWizard()
{
}

int ZVWorkspaceCreationWizard::DoModal()
{
    ZVWorkspaceStart Start( m_InitialDirectory, m_WorkspaceExtension, m_Modify );

    if ( Start.DoModal() == IDCANCEL )
    {
        return IDCANCEL;
    }

    ZVWorkspaceTemplate Template( m_pWorkspaceTemplateManager );

    if ( Template.DoModal() == IDCANCEL )
    {
        return IDCANCEL;
    }

    // Save options
    m_WorkspaceName        = Start.GetWorkspaceName();
    m_Directory            = Start.GetDirectory();
    m_WorkspaceFilename    = Start.GetWorkspaceFilename();

    return IDOK;
}

/////////////////////////////////////////////////////////////////////////////
// ZVWorkspaceStart dialog

BEGIN_MESSAGE_MAP( ZVWorkspaceStart, ZIWizardDialog )
    //{{AFX_MSG_MAP(ZVWorkspaceStart)
    ON_BN_CLICKED(IDNEXT, OnNext)
    ON_EN_CHANGE(IDC_WORKSPACE_NAME, OnChangeWorkspaceName)
    ON_EN_CHANGE(IDC_WORKSPACE_FOLDER, OnChangeWorkspaceFolder)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVWorkspaceStart::ZVWorkspaceStart( const CString    InitialDirectory    /*= ""*/,
                                    const CString    WorkspaceExtension    /*= ""*/,
                                    bool            Modify                /*= false*/,
                                    CWnd*            pParent                /*= NULL*/ )
    : ZIWizardDialog        ( ZVWorkspaceStart::IDD,
                              IDB_WZBMP1,
                              0,
                              0,
                              IDS_WZ_WORKSPACE_ST_S,
                              IDS_WZ_WORKSPACE_ST_T ),
      m_InitialDirectory    ( InitialDirectory ),
      m_WorkspaceExtension    ( WorkspaceExtension ),
      m_Modify                ( Modify )
{
    //{{AFX_DATA_INIT(ZVWorkspaceStart)
    m_WorkspaceName = _T("");
    //}}AFX_DATA_INIT

    // Defines the edit as search for file
    m_Directory.SetSearchType(PSS_SearchEditButton::IE_T_Directory, IDS_SELWORKSPACE_DIR_T, InitialDirectory);
}

bool ZVWorkspaceStart::Validate()
{
    UpdateData( TRUE );

    if ( m_WorkspaceName.IsEmpty() )
    {
        // Error message, cannot be empty
        return false;
    }
    m_Directory.GetWindowText( m_DirectoryStr );

    // Normalize the directory
    ZDirectory::NormalizeDirectory( m_DirectoryStr );

    // Build the workspace filename
    m_WorkspaceFilename  = ZDirectory::NormalizeDirectory( m_DirectoryStr ) + _T( "\\" );
    m_WorkspaceFilename += m_WorkspaceName;
    m_WorkspaceFilename += m_WorkspaceExtension;

    if ( !ZDirectory::Exist( m_DirectoryStr ) )
    {
        // Asks the user to create the directory
        PSS_MsgBox mBox;

        if (mBox.ShowMsgBox( IDS_WKSPACE_DIR_NEEDCREATE, MB_YESNO ) == IDNO )
        {
            return false;
        }

        // Then, try to create it
        ZDirectory::CreateDirectory( m_DirectoryStr );

        // If is still not created, error message
        if ( !ZDirectory::Exist( m_DirectoryStr ) )
        {
            PSS_MsgBox mBox;
            mBox.ShowMsgBox( IDS_WKSPACE_DIR_FAILCREATE, MB_OK );
            return false;
        }
    }
    else
    {
        // Check if the workspace already exist. If exit, ask to replace
        if (PSS_File::Exist( m_WorkspaceFilename ) )
        {
            PSS_MsgBox mBox;

            if ( mBox.ShowMsgBox( IDS_WKSPACE_ALREADYEXIST, MB_YESNO ) == IDNO )
            {
                return false;
            }
        }
    }

    return true;
}

void ZVWorkspaceStart::DoDataExchange( CDataExchange* pDX )
{
    ZIWizardDialog::DoDataExchange( pDX );

    //{{AFX_DATA_MAP(ZVWorkspaceStart)
    DDX_Control(pDX, IDC_WORKSPACE_FOLDER, m_Directory);
    DDX_Text(pDX, IDC_WORKSPACE_NAME, m_WorkspaceName);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVWorkspaceStart message handlers

BOOL ZVWorkspaceStart::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();
    
    ZDirectory::NormalizeDirectory( m_InitialDirectory );
    m_InitialDirectory += _T( "\\" );
    m_Directory.SetWindowText( m_InitialDirectory );

    m_HasChanged = false;

    if ( !m_Modify )
    {
        if ( GetDlgItem( IDOK ) )
        {
            GetDlgItem( IDOK )->ShowWindow( SW_HIDE );
        }
    }
    
    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVWorkspaceStart::OnChangeWorkspaceFolder()
{
    m_HasChanged = true;
}

void ZVWorkspaceStart::OnChangeWorkspaceName()
{
    // If the directory has not changed,
    // continue to add caracters typed to the directory
    if ( !m_HasChanged )
    {
        if ( GetDlgItem( IDC_WORKSPACE_NAME ) )
        {
            CString Name;
            GetDlgItem( IDC_WORKSPACE_NAME )->GetWindowText( Name );

            // Add the name typed
            m_Directory.SetWindowText( m_InitialDirectory + Name );

            // Due to the SetWindowText, on change is called,
            // then reset the flag just after this call
            m_HasChanged = false;

            // If directly changed by the user, then the flag will not be reset
        }
    }
}

void ZVWorkspaceStart::OnOK()
{
    if ( !Validate() )
    {
        return;
    }

    ZIWizardDialog::OnOK();
}

void ZVWorkspaceStart::OnNext()
{
    if ( !Validate() )
    {
        return;
    }

    EndDialog( IDNEXT );
}

/////////////////////////////////////////////////////////////////////////////
// ZVWorkspaceTemplate dialog

BEGIN_MESSAGE_MAP( ZVWorkspaceTemplate, ZIWizardDialog )
    //{{AFX_MSG_MAP(ZVWorkspaceTemplate)
    ON_NOTIFY(NM_CLICK, IDC_WKS_TEMPLATELIST, OnClickWksTemplatelist)
    ON_NOTIFY(NM_DBLCLK, IDC_WKS_TEMPLATELIST, OnDblclkWksTemplatelist)
    ON_NOTIFY(NM_RCLICK, IDC_WKS_TEMPLATELIST, OnRclickWksTemplatelist)
    ON_NOTIFY(NM_RDBLCLK, IDC_WKS_TEMPLATELIST, OnRdblclkWksTemplatelist)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVWorkspaceTemplate::ZVWorkspaceTemplate( ZBWorkspaceWizardTemplateMg*    pWorkspaceTemplateManager    /*= NULL*/,
                                          CWnd*                            pParent                        /*= NULL*/ )
    : ZIWizardDialog                ( ZVWorkspaceTemplate::IDD,
                                      IDB_WZBMP1,
                                      0,
                                      0,
                                      IDS_WZ_WORKSPACE_TMPL_S,
                                      IDS_WZ_WORKSPACE_TMPL_T ),
      m_pWorkspaceTemplateManager    ( pWorkspaceTemplateManager )
{
    //{{AFX_DATA_INIT(ZVWorkspaceTemplate)
    m_Comment = _T("");
    //}}AFX_DATA_INIT
}

void ZVWorkspaceTemplate::DoDataExchange( CDataExchange* pDX )
{
    ZIWizardDialog::DoDataExchange( pDX );

    //{{AFX_DATA_MAP(ZVWorkspaceTemplate)
    DDX_Control(pDX, IDC_WKS_TEMPLATELIST, m_TemplateList);
    DDX_Text(pDX, IDC_WKS_COMMENT, m_Comment);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVWorkspaceTemplate message handlers

void ZVWorkspaceTemplate::OnOK()
{
    ZIWizardDialog::OnOK();
}

BOOL ZVWorkspaceTemplate::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();
    
    m_TemplateList.Initialize( m_pWorkspaceTemplateManager );
    m_TemplateList.SetCurSel( 0 );
    SelChanged();
    
    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVWorkspaceTemplate::SelChanged()
{
    
    ZBWorkspaceWizardTemplateItem* pItem = m_TemplateList.GetSelectedItem();

    if ( pItem )
    {
        m_Comment = pItem->GetTemplateDescription();
        UpdateData( FALSE );
    }
}

void ZVWorkspaceTemplate::OnClickWksTemplatelist( NMHDR* pNMHDR, LRESULT* pResult )
{
    SelChanged();
    *pResult = 0;
}

void ZVWorkspaceTemplate::OnDblclkWksTemplatelist( NMHDR* pNMHDR, LRESULT* pResult )
{
    SelChanged();
    *pResult = 0;
}

void ZVWorkspaceTemplate::OnRclickWksTemplatelist( NMHDR* pNMHDR, LRESULT* pResult )
{
    SelChanged();
    *pResult = 0;
}

void ZVWorkspaceTemplate::OnRdblclkWksTemplatelist( NMHDR* pNMHDR, LRESULT* pResult )
{
    SelChanged();
    *pResult = 0;
}
