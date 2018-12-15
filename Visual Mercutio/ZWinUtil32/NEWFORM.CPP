// newform.cpp : implementation file

#include "stdafx.h"
#include "newform.h"
#include "zBaseLib\msgbox.h"
#include "planfin.hdf"
#include "zRes32\ZRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 13 juin 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_DYNAMIC( ZINewFormPropertySheet, ZIBasePropSheet )

BEGIN_MESSAGE_MAP( ZINewFormPropertySheet, CPropertySheet )
    //{{AFX_MSG_MAP(ZINewFormPropertySheet)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZINewFormPropertySheet property sheet

ZINewFormPropertySheet::ZINewFormPropertySheet( ZDTemplateManager* pTemplateManager )
    : ZIBasePropSheet(),
      m_FirstInitialization( TRUE ),
      m_pTemplateManager( pTemplateManager )
{
    ASSERT( m_pTemplateManager );
    Initialize();
    m_FirstInitialization = FALSE;
}

void ZINewFormPropertySheet::Initialize()
{
    ASSERT( m_pTemplateManager );

    // Set the size of the internal array for pointer page
    if ( m_FirstInitialization )
    {
        ZIBasePropSheet::GetPageArray().SetSize( m_pTemplateManager->GetSize() );
    }

    // Run throughout all template directory
    ZDTemplateDir* pTemplateDir;

    for ( size_t i = 0; i < (size_t)m_pTemplateManager->GetSize(); ++i )
    {
        pTemplateDir = m_pTemplateManager->GetTemplateDirAt( i );

        if ( pTemplateDir )
        {
            ZIGenericFormPage* pFormPage =
                new ZIGenericFormPage( NULL,
                                       pTemplateDir->GetTitle(),
                                       m_pTemplateManager );

            if ( !m_FirstInitialization )
            {
                // Remove the old page
                RemovePage( 0 );
                delete ( (ZIGenericFormPage*)(m_PageArray[i]) );
            }

            // Replace the pointer to the previous page
            // or insert the right pointer
            ZIBasePropSheet::GetPageArray().SetAt( i, pFormPage );
            AddPage( pFormPage );
        }
    }

    m_RootCaption = m_pTemplateManager->GetRootCaption();

    // Activate the first page to refresh the contents
    // Not in Initialization mode
    if ( !m_FirstInitialization )
    {
        SetActivePage( 0 );
    }
}

void ZINewFormPropertySheet::ClearContents()
{
    // Free the pages allocated on the fly by the ZINewForm class
    for ( int i = 0; i < m_PageArray.GetSize(); ++i )
    {
        delete ( (ZIGenericFormPage*)(m_PageArray[i]) );
    }

    ZIBasePropSheet::GetPageArray().RemoveAll();
}

ZINewFormPropertySheet::~ZINewFormPropertySheet()
{
    ClearContents();
}

/////////////////////////////////////////////////////////////////////////////
// ZINewForm dialog

BEGIN_MESSAGE_MAP( ZINewForm, ZIWizardDialog )
    //{{AFX_MSG_MAP(ZINewForm)
    ON_BN_CLICKED(IDC_MOVE_TOGENERAL, OnMoveToGeneralTab)
    ON_MESSAGE(UM_SETCOMMENT, OnCommentChange)
    ON_MESSAGE(UM_FORMS_SELECTED, OnFormsSelected)
    ON_MESSAGE(UM_FORMACTIVATE, OnFormActivate)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZINewForm::ZINewForm( ZDTemplateManager*        pTemplateManager,
                      DialogFormType            Type,
                      DialogFormExtensionType    ExtensionType)
    : ZIWizardDialog( ZINewForm::IDD,
                      IDB_WZBMP2,
                      0,
                      0,
                      0,
                      0),
      m_pTemplateManager( pTemplateManager ),
      m_Type( Type ),
      m_SelectedFilename( _T( "" ) ),
      m_pCurrentTemplateFile( NULL ),
      m_pCurrentTemplateDir( NULL ),
      m_ExtensionType( ExtensionType )
{
    //{{AFX_DATA_INIT(ZINewForm)
    m_sComment = _T( "" );
    m_bCopyFormat = TRUE;
    //}}AFX_DATA_INIT

    ASSERT( m_pTemplateManager );

    m_pSystemPropertySheet = new ZINewFormPropertySheet( m_pTemplateManager );
}

ZINewForm::~ZINewForm()
{
    if ( m_pSystemPropertySheet )
    {
        delete m_pSystemPropertySheet;
        m_pSystemPropertySheet = NULL;
    }
}

void ZINewForm::DoDataExchange( CDataExchange* pDX )
{
    ZIWizardDialog::DoDataExchange( pDX );

    //{{AFX_DATA_MAP(ZINewForm)
    DDX_Control(pDX, IDC_COPYFORMAT, m_CopyFormatWnd);
    DDX_Control(pDX, IDOK, m_Button);
    DDX_Text(pDX, IDC_COMMENT, m_sComment);
    DDX_Check(pDX, IDC_COPYFORMAT, m_bCopyFormat);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZINewForm message handlers

BOOL ZINewForm::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();

    UINT nResID;

    m_MoveToGeneralTabBtn.AutoLoad( IDC_MOVE_TOGENERAL, this );
    m_MoveToGeneralTabBtn.EnableWindow( FALSE );
    m_Button.EnableWindow( FALSE );

    // If attach, change the window title
    // and the button text.
    switch ( m_Type )
    {
        case AttachForm:
        {
            SetWizardWindowTitle( IDS_ATTACHTITLE );

            switch ( m_ExtensionType )
            {
                case ProcessFormType:
                {
                    nResID = IDS_PROCESSTEXT;
                    break;
                }

                case ModelFormType:
                {
                    nResID = IDS_MODELTEXT;
                    break;
                }

                case FormType:
                default:
                {
                    nResID = IDS_FORMSTEXT;
                    break;
                }
            }

            SetWizardSubjectText( nResID );
            SetWizardBodyText( IDS_ATTACHFORMDLG_TEXT );

            // The button text
            CString sText;

            sText.LoadString( IDS_ATTACHBUTTONTEXT );

            m_Button.SetWindowText( sText );
            m_MoveToGeneralTabBtn.ShowWindow( SW_HIDE );

            break;
        }

        case OpenForm:
        {
            switch ( m_ExtensionType )
            {
                case ProcessFormType:
                {
                    nResID = IDS_OPENPROCESSTITLE;
                    break;
                }

                case ModelFormType:
                {
                    nResID = IDS_OPENMODELTITLE;
                    break;
                }

                case FormType:
                default:
                {
                    nResID = IDS_OPENTITLE;
                    break;
                }
            }

            SetWizardWindowTitle( nResID );

            switch ( m_ExtensionType )
            {
                case ProcessFormType:
                {
                    nResID = IDS_PROCESSTEXT;
                    break;
                }

                case ModelFormType:
                {
                    nResID = IDS_MODELTEXT;
                    break;
                }

                case FormType:
                default:
                {
                    nResID = IDS_FORMSTEXT;
                    break;
                }
            }

            SetWizardSubjectText( nResID );

            switch ( m_ExtensionType )
            {
                case ProcessFormType:
                {
                    nResID = IDS_OPENPROCESSDLG_TEXT;
                    break;
                }

                case ModelFormType:
                {
                    nResID = IDS_OPENMODELDLG_TEXT;
                    break;
                }

                case FormType:
                default:
                {
                    nResID = IDS_OPENFORMDLG_TEXT;
                    break;
                }
            }

            SetWizardBodyText( nResID  );

            // The button text
            CString sText;

            sText.LoadString( IDS_OPENBUTTONTEXT );
            m_Button.SetWindowText( sText );
            m_MoveToGeneralTabBtn.ShowWindow( SW_HIDE );
            m_CopyFormatWnd.ShowWindow( SW_HIDE );

            break;
        }

        case StartForm:
        {
            switch ( m_ExtensionType )
            {
                case ProcessFormType:
                {
                    nResID = IDS_STARTPROCESSTITLE;
                    break;
                }

                case ModelFormType:
                {
                    nResID = IDS_STARTMODELTITLE;
                    break;
                }

                case FormType:
                default:
                {
                    nResID = IDS_STARTTITLE;
                    break;
                }
            }

            SetWizardWindowTitle( nResID );

            switch ( m_ExtensionType )
            {
                case ProcessFormType:
                {
                    nResID = IDS_PROCESSTEXT;
                    break;
                }

                case ModelFormType:
                {
                    nResID = IDS_MODELTEXT;
                    break;
                }

                case FormType:
                default:
                {
                    nResID = IDS_FORMSTEXT;
                    break;
                }
            }

            SetWizardSubjectText( nResID );

            switch ( m_ExtensionType )
            {
                case ProcessFormType:
                {
                    nResID = IDS_STARTPROCESSDLG_TEXT;
                    break;
                }

                case ModelFormType:
                {
                    nResID = IDS_STARTMODELDLG_TEXT;
                    break;
                }

                case FormType:
                default:
                {
                    nResID = IDS_STARTFORMDLG_TEXT;
                    break;
                }
            }

            SetWizardBodyText( nResID );

            // The button text
            CString sText;

            sText.LoadString( IDS_STARTBUTTONTEXT );
            m_Button.SetWindowText( sText );
            m_CopyFormatWnd.ShowWindow( SW_HIDE );
            m_MoveToGeneralTabBtn.ShowWindow( SW_SHOW );

            break;
        }

        case SelectForm:
        {
            switch ( m_ExtensionType )
            {
                case ProcessFormType:
                {
                    nResID = IDS_SELECTPROCESSTITLE;
                    break;
                }

                case ModelFormType:
                {
                    nResID = IDS_SELECTMODELTITLE;
                    break;
                }

                case FormType:
                default:
                {
                    nResID = IDS_SELECTTITLE;
                    break;
                }
            }

            SetWizardWindowTitle( nResID );

            switch ( m_ExtensionType )
            {
                case ProcessFormType:
                {
                    nResID = IDS_PROCESSTEXT;
                    break;
                }

                case ModelFormType:
                {
                    nResID = IDS_MODELTEXT;
                    break;
                }

                case FormType:
                default:
                {
                    nResID = IDS_FORMSTEXT;
                    break;
                }
            }

            SetWizardSubjectText( nResID );

            switch ( m_ExtensionType )
            {
                case ProcessFormType:
                {
                    nResID = IDS_SELECTPROCESSDLG_TEXT;
                    break;
                }

                case ModelFormType:
                {
                    nResID = IDS_SELECTMODELDLG_TEXT;
                    break;
                }

                case FormType:
                default:
                {
                    nResID = IDS_SELECTFORMDLG_TEXT;
                    break;
                }
            }

            SetWizardBodyText( nResID );

            // The button text
            CString sText;

            sText.LoadString( IDS_SELECTBUTTONTEXT );
            m_Button.SetWindowText( sText );
            m_CopyFormatWnd.ShowWindow( SW_HIDE );
            m_MoveToGeneralTabBtn.ShowWindow( SW_SHOW );

            break;
        }
    }

    // Get the client rect of the dialog
    // to reposition the property sheet
    CRect rect;
    GetClientRect( &rect );

    // Create the property sheet child of the dialog
    m_pSystemPropertySheet->Create( this, WS_SYSMENU | WS_CHILD | DS_MODALFRAME );

    // Resize the property sheet
    CRect PropRect;
    m_pSystemPropertySheet->GetClientRect( &PropRect );

#ifndef _WIN32
    m_pSystemPropertySheet->MoveWindow( rect.left + 3, rect.top + 75, PropRect.Width(), PropRect.Height() - 25 );
#else
    m_pSystemPropertySheet->MoveWindow( rect.left + 3, rect.top + 75, PropRect.Width(), PropRect.Height() );
#endif

    // And after only show the property sheet
    m_pSystemPropertySheet->ShowWindow( SW_SHOW );

    // return TRUE unless you set the focus to a control
    return TRUE;
}

afx_msg LONG ZINewForm::OnCommentChange( UINT message, LONG lParam )
{
    ASSERT( m_pTemplateManager );

    // message contains the current selection
    ZIGenericFormPage* pFormPage =
        ( (ZIGenericFormPage*)( m_pSystemPropertySheet->GetPageArray()[m_pSystemPropertySheet->GetCurPage()] ) );

    // Find the right template directory
    m_pCurrentTemplateDir = m_pTemplateManager->FindTemplateDir( pFormPage->GetCaption() );

    // If no template, out
    if ( !m_pCurrentTemplateDir )
    {
        return 0;
    }

    // Find the right file
    m_pCurrentTemplateFile = m_pCurrentTemplateDir->GetTemplateFileAt( message );

    if ( m_pCurrentTemplateFile )
    {
        m_sComment            = m_pCurrentTemplateFile->GetDescription();
        m_SelectedFilename    = m_pCurrentTemplateFile->GetFilename();
        m_SelectedFormName    = m_pCurrentTemplateFile->GetTitle();

        UpdateData( FALSE );
    }

    // Test if the move to Général button can be enabled
    m_MoveToGeneralTabBtn.EnableWindow( pFormPage->GetCaption() != m_pSystemPropertySheet->GetRootCaption() );
    m_Button.EnableWindow( TRUE );

    return 1;
}

afx_msg LONG ZINewForm::OnFormActivate( UINT message, LONG lParam )
{
    m_MoveToGeneralTabBtn.EnableWindow( FALSE );
    m_Button.EnableWindow( FALSE );

    return 1;
}

afx_msg LONG ZINewForm::OnFormsSelected( UINT message, LONG lParam )
{
    OnOK();

    return 1;
}

void ZINewForm::OnMoveToGeneralTab()
{
    ASSERT( m_pTemplateManager );

    // Find the right template directory
    if ( m_pTemplateManager->MoveTemplateFile( m_pCurrentTemplateFile->GetFilename(),
                                               m_pCurrentTemplateDir->GetTitle(),
                                               m_pSystemPropertySheet->GetRootCaption() ) )
    {
        m_pSystemPropertySheet->Initialize();
        m_SelectedFilename        = _T( "" );
        m_pCurrentTemplateFile    = NULL;
        m_pCurrentTemplateDir    = NULL;
    }
}

void ZINewForm::OnOK()
{
    ZIWizardDialog::OnOK();
}
