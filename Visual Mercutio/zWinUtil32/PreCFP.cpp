// PreCFP.cpp : implementation file
//

#include "stdafx.h"
#include "PreCFP.h"
// FldStamp
#include "zBaseLib\FldStamp.h"

#include "zBaseLib\MsgBox.h"
#include "zRes32\ZRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 5 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZIPreConditionFormProc dialog

BEGIN_MESSAGE_MAP( ZIPreConditionFormProc, ZIWizardDialog )
    //{{AFX_MSG_MAP(ZIPreConditionFormProc)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZIPreConditionFormProc::ZIPreConditionFormProc( CString            ActivityName,
                                                CStringArray&    FormNameArray,
                                                BOOL            FileRequired,
                                                BOOL            IsLast,
                                                BOOL            IsProcess,
                                                CStringArray&    FileArray,
                                                CWnd*            pParent /*=NULL*/ )
    : ZIWizardDialog    ( ZIPreConditionFormProc::IDD,        // Dialog template
                          IDB_WZBMP1,                        // Bitmap to display
                          0,                                // Icon do display
                          0,                                // Window Title
                          IDS_WZPREACTIVITYTITLE_WZ,        // Wizard title
                          IDS_WZPREACTIVITYTITLEFORM_T ),    // Wizard text
      m_FormNameArray    ( FormNameArray ),
      m_FileRequired    ( FileRequired ),
      m_IsLast            ( IsLast ),
      m_IsProcess        ( IsProcess ),
      m_FileArray        ( FileArray ),
      m_CurrentFormIndex( 0 )
{
    //{{AFX_DATA_INIT(ZIPreConditionFormProc)
    m_ActivityName = _T(ActivityName);
    m_FormName = _T("");
    //}}AFX_DATA_INIT

    CString title;

    if ( m_IsProcess )
    {
        VERIFY( title.LoadString( IDS_SELECTPROCESS_TITLE ) );
    }
    else
    {
        VERIFY( title.LoadString( IDS_SELECTFORM_TITLE ) );
    }

    // set the right file filter
    CString strFilter;

    if (m_IsProcess)
        VERIFY(strFilter.LoadString(IDS_PROCESSFILE_FILTERTXT));
    else
        VERIFY(strFilter.LoadString(IDS_FORMFILE_FILTERTXT));

    // Next string please
    strFilter += (char)'\0';

    if (m_IsProcess)
        strFilter += g_SearchAllProcessExtension;
    else
        strFilter += g_SearchAllFormExtension;

    // Last string
    strFilter += (char)'\0';

    // append the "*.*" all files filter
    CString allFilter;
    VERIFY( allFilter.LoadString( AFX_IDS_ALLFILTER ) );

    strFilter += allFilter;
    strFilter += (char)'\0';            // next string please
    strFilter += "*.*";
    strFilter += (char)'\0';            // last string

    // Defines the edit as search for file
    m_Filename.SetSearchType( ZSEARCHEDIT_FILE, title, _T( "" ), strFilter, 2 );
}

void ZIPreConditionFormProc::DoDataExchange( CDataExchange* pDX )
{
    ZIWizardDialog::DoDataExchange( pDX );
    //{{AFX_DATA_MAP(ZIPreConditionFormProc)
    DDX_Control(pDX, IDC_PROCFORMFILENAME, m_Filename);
    DDX_Text(pDX, IDC_ACTIVITYNAME, m_ActivityName);
    DDX_Text(pDX, IDC_FORMPROCNAME, m_FormName);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZIPreConditionFormProc message handlers

BOOL ZIPreConditionFormProc::OnInitDialog()
{
    // If at least one form name, sets the form name
    if ( m_FormNameArray.GetSize() > 0 )
    {
        m_FormName = m_FormNameArray.GetAt( 0 );
    }

    ZIWizardDialog::OnInitDialog();
    
    if ( m_IsProcess )
    {
        SetWizardBodyText( IDS_WZPREACTIVITYTITLEPROC_T );
    }

    if ( GetDlgItem( IDC_FORM_TEXT ) )
    {
        GetDlgItem( IDC_FORM_TEXT )->ShowWindow( ( m_IsProcess ) ? SW_HIDE : SW_SHOW );
    }

    if ( GetDlgItem( IDC_PROC_TEXT ) )
    {
        GetDlgItem( IDC_PROC_TEXT )->ShowWindow( ( !m_IsProcess ) ? SW_HIDE : SW_SHOW );
    }

    BuildText( ( m_FormNameArray.GetSize() > 0 ) ? 0 : -1 );

    CheckStates();

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZIPreConditionFormProc::BuildText( int FormIndex )
{
    CString Text;

    if ( FormIndex < 0 )
    {
        if ( m_IsProcess )
        {
            AfxFormatString1( Text, IDS_BASEONPROCNONAME_EXPLANATION, m_ActivityName );
        }
        else
        {
            AfxFormatString1( Text, IDS_BASEONFORMNONAME_EXPLANATION, m_ActivityName );
        }
    }
    else if ( m_IsProcess )
    {
        AfxFormatString2( Text, IDS_BASEONPROC_EXPLANATION, m_ActivityName, m_FormNameArray.GetAt( FormIndex ) );
    }
    else
    {
        AfxFormatString2( Text, IDS_BASEONFORM_EXPLANATION, m_ActivityName, m_FormNameArray.GetAt( FormIndex ) );
    }

    if ( GetDlgItem( IDC_FORMPROC_EXPLANATION ) )
    {
        GetDlgItem( IDC_FORMPROC_EXPLANATION )->SetWindowText( Text );
    }
}

void ZIPreConditionFormProc::CheckStates()
{
    if ( m_IsLast && ( m_FormNameArray.GetSize() > 0 || m_CurrentFormIndex == m_FormNameArray.GetSize() - 1 ) )
    {
        if ( GetDlgItem( IDOK ) )
        {
            GetDlgItem( IDOK )->ShowWindow( SW_SHOW );
        }

        if ( GetDlgItem( IDNEXT ) )
        {
            GetDlgItem( IDNEXT )->ShowWindow( SW_HIDE );
        }
    }
    else
    {
        if ( GetDlgItem( IDOK ) )
        {
            GetDlgItem( IDOK )->ShowWindow( SW_HIDE );
        }

        if ( GetDlgItem( IDNEXT ) )
        {
            GetDlgItem( IDNEXT )->ShowWindow( SW_SHOW );
        }
    }
}

BOOL ZIPreConditionFormProc::CheckFiles()
{
    CString Filename;
    m_Filename.GetWindowText( Filename );

    if ( m_FileRequired )
    {
        if ( Filename.IsEmpty() )
        {
            MsgBox mbox;
            mbox.DisplayMsgBox( IDS_PROCFORMFILEMISSING, MB_OK );

            return FALSE;
        }

        if ( ( m_FormNameArray.GetSize() > 0 && m_CurrentFormIndex <= m_FormNameArray.GetSize() - 1 ) )
        {
            ZDFolderStamp Stamp;

            if ( !Stamp.ReadFromFile( Filename ) )
            {
                MsgBox mbox;
                mbox.DisplayMsgBox( IDS_PROCFORMFILEINVALID, MB_OK );

                return FALSE;
            }

            if ( Stamp.GetTitle() != m_FormNameArray.GetAt( m_CurrentFormIndex ) )
            {
                MsgBox mbox;
                mbox.DisplayMsgBox( IDS_PROCFORMFILE_TITLENEQ, MB_OK );

                return FALSE;
            }
        }
    }

    return TRUE;
}

void ZIPreConditionFormProc::OnOK()
{
    if ( !CheckFiles() )
    {
        return;
    }

    CString Filename;
    m_Filename.GetWindowText( Filename );

    // Save filename
    m_FileArray.Add( Filename );

    ZIWizardDialog::OnOK();
}

void ZIPreConditionFormProc::OnNext()
{
    if ( !CheckFiles() )
    {
        return;
    }

    CString Filename;
    m_Filename.GetWindowText( Filename );

    // Save filename
    m_FileArray.Add( Filename );

    // If we are at the end
    if ( m_CurrentFormIndex >= m_FormNameArray.GetSize() - 1 )
    {
        EndDialog( IDNEXT );
        return;
    }

    // Next form
    ++m_CurrentFormIndex;

    BuildText( m_CurrentFormIndex  );
    
    // Defines the edit as search for file
    m_Filename.SetWindowText( _T( "" ) );

    CheckStates();

    UpdateData( FALSE );

    // We are not at the end, continue
    return;
}
