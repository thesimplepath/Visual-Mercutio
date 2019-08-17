// **************************************************************************************************************
// *                                             Classe ZVRiskModifyDlg                                            *
// **************************************************************************************************************
// * JMR-MODIF - Le 25 juin 2007 - Ajout de la classe ZVRiskModifyDlg.                                            *
// **************************************************************************************************************
// * Cette classe permet à l'utilisateur de modifier un élément dans les listes déroulantes utilisées par les    *
// * risques.                                                                                                    *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVRiskModifyDlg.h"

#include "ZVRiskNewFileDlg.h"

#include "zBaseLib\ZDTextFile.h"
#include "zBaseLib\PSS_File.h"

#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP( ZVRiskModifyDlg, CDialog )
    //{{AFX_MSG_MAP(ZVRiskModifyDlg)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_ADD_ELEMENT, OnBnClickedAddElement)
    ON_BN_CLICKED(IDC_DEL_ELEMENT, OnBnClickedDelElement)
    ON_EN_CHANGE(IDC_NEW_ELEMENT, OnEnChangeNewElement)
    ON_LBN_SELCHANGE(IDC_ELEMENTS_LIST, OnLbnSelchangeElementsList)
    ON_BN_CLICKED(IDC_NEW_FILE, OnBnClickedNewFile)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVRiskModifyDlg dialog

ZVRiskModifyDlg::ZVRiskModifyDlg( CString    Filename,
                                  CString    Extension,
                                  CWnd*        pParent        /*= NULL*/ )
    : CDialog        ( ZVRiskModifyDlg::IDD, pParent ),
      m_Filename    ( Filename ),
      m_Extension    ( Extension ),
      m_Element        ( _T( "" ) )
{
    //{{AFX_DATA_INIT(ZVRiskModifyDlg)
    //}}AFX_DATA_INIT
}

// Cette fonction retourne le nom du fichier utilisé pour la liste en cours de modification.
CString ZVRiskModifyDlg::GetFilename()
{
    return m_Filename;
}

void ZVRiskModifyDlg::DoDataExchange( CDataExchange* pDX )
{
    CDialog::DoDataExchange( pDX );

    //{{AFX_DATA_MAP(ZVRiskModifyDlg)
    DDX_Control(pDX, IDC_ELEMENTS_LIST, m_ElementsListCtrl);
    DDX_Control(pDX, IDC_NEW_ELEMENT, m_ElementCtrl);
    DDX_Text(pDX, IDC_NEW_ELEMENT, m_Element);
    DDX_Control(pDX, IDC_ADD_ELEMENT, m_Add);
    DDX_Control(pDX, IDC_DEL_ELEMENT, m_Del);
    DDX_Control(pDX, IDOK, m_OK);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVRiskModifyDlg message handlers

// Cette fonction est appelée lorsque la fenêtre s'initialise.
BOOL ZVRiskModifyDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    ZDTextFile p_File;

    if ( p_File.OpenRead( m_Filename ) == TRUE )
    {
        BOOL    m_EndReached    = FALSE;
        CString    m_Text            = _T( "" );

        while( m_EndReached != TRUE )
        {
            p_File >> m_Text;

            if ( m_Text.IsEmpty() == false )
            {
                m_ElementsListCtrl.AddString( m_Text );
            }
            else
            {
                m_EndReached = TRUE;
            }
        }

        p_File.CloseFile();
    }
    else
    {
        PSS_MsgBox mBox;
        mBox.ShowMsgBox( IDS_CANNOT_OPEN_RISK_FILE, MB_OK );

        m_ElementsListCtrl.EnableWindow( FALSE );
        m_ElementCtrl.EnableWindow( FALSE );
        m_Add.EnableWindow( FALSE );
        m_Del.EnableWindow( FALSE );
        m_OK.EnableWindow( FALSE );
    }

    return TRUE;
}

// Cette fonction est appelée lorsque l'utilisateur entre une saisie dans la boîte de texte des nouveaux éléments.
void ZVRiskModifyDlg::OnEnChangeNewElement()
{
    m_ElementCtrl.GetWindowText( m_Element );

    if ( m_Element.IsEmpty() == false )
    {
        m_Add.EnableWindow( TRUE );
    }
    else
    {
        m_Add.EnableWindow( FALSE );
    }
}

// Cette fonction est appelée lorsque la sélection de la liste des éléments a changé.
void ZVRiskModifyDlg::OnLbnSelchangeElementsList()
{
    m_Del.EnableWindow( TRUE );
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton Ajouter.
void ZVRiskModifyDlg::OnBnClickedAddElement()
{
    if ( m_Element.IsEmpty() == false )
    {
        m_ElementsListCtrl.AddString( m_Element );
    }

    m_Element = _T( "" );
    m_ElementCtrl.SetWindowText( m_Element );
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton Supprimer.
void ZVRiskModifyDlg::OnBnClickedDelElement()
{
    if ( ( m_ElementsListCtrl.GetCurSel() ) >= 0 && ( m_ElementsListCtrl.GetCurSel() < m_ElementsListCtrl.GetCount() ) )
    {
        m_ElementsListCtrl.DeleteString( m_ElementsListCtrl.GetCurSel() );
        m_Del.EnableWindow( FALSE );
    }
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Nouveau"
void ZVRiskModifyDlg::OnBnClickedNewFile()
{
    ZVRiskNewFileDlg m_NewFileDlg( m_Extension );

    if ( m_NewFileDlg.DoModal() == IDOK )
    {
        m_Filename = m_NewFileDlg.GetDirectory() + _T( "\\" ) + m_NewFileDlg.GetFilename() + m_Extension;

        while ( m_ElementsListCtrl.GetCount() > 0 )
        {
            m_ElementsListCtrl.DeleteString( 0 );
        }
    }
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton OK.
void ZVRiskModifyDlg::OnBnClickedOk()
{
    PSS_File m_File;

    if ( m_File.Exist( m_Filename ) == TRUE )
    {
        CFile::Remove( m_Filename );
    }

    ZDTextFile p_NewFile;

    p_NewFile.OpenWrite( m_Filename );

    for ( int i = 0; i < m_ElementsListCtrl.GetCount(); i++ )
    {
        CString s = _T( "" );
        m_ElementsListCtrl.GetText( i, s );
        p_NewFile << s + _T( "\r\n" );
    }

    p_NewFile.CloseFile();

    OnOK();
}
