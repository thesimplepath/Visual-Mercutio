// **********************************************************************************************************
// *                                        Classe ZVDocumentPageSetupDlg                                    *
// **********************************************************************************************************
// * Cette classe mets à disposition la boîte de dialogue pour la sélection du format de page.                *
// **********************************************************************************************************

#include "stdafx.h"
#include "ZVDocumentPageSetupDlg.h"

// **********************************************************************************************************
// *                                             Mappage des messages                                        *
// **********************************************************************************************************

IMPLEMENT_DYNAMIC( ZVDocumentPageSetupDlg, ZIWizardDialog )

BEGIN_MESSAGE_MAP( ZVDocumentPageSetupDlg, ZIWizardDialog )
    ON_BN_CLICKED(IDC_PORTRAIT, OnBnClickedPortrait)
    ON_BN_CLICKED(IDC_LANDSCAPE, OnBnClickedLandscape)
    ON_BN_CLICKED(IDC_BT_OPENFILE, OnBnClickedBtOpenfile)
    ON_EN_CHANGE(IDC_EDIT_FILENAME, OnEnChangeEditFilename)
END_MESSAGE_MAP()

// **********************************************************************************************************
// *                                        Constructeur(s) et destructeur                                    *
// **********************************************************************************************************

// Constructeur par défaut de la classe ZVDocumentPageSetupDlg.
ZVDocumentPageSetupDlg::ZVDocumentPageSetupDlg( CWnd* pParent /*=NULL*/ )
    : ZIWizardDialog    ( ZVDocumentPageSetupDlg::IDD,
                          IDB_WZBMP1,
                          0,
                          0,
                          IDS_WZ_PAGESETUP_S,
                          IDS_WZ_PAGESETUP_T )
{
    m_PaperSize        = DefaultPaperSize;
    m_StandardSize    = DefaultStandardSize;
    m_Orientation    = DefaultOrientation;

    sBkGndName        = _T( "" );
}

// Destructeur de la classe ZVDocumentPageSetupDlg.
ZVDocumentPageSetupDlg::~ZVDocumentPageSetupDlg()
{
}

// **********************************************************************************************************
// *                             Fonction protégées de la classe ZVDocumentPageSetupDlg                        *
// **********************************************************************************************************

void ZVDocumentPageSetupDlg::DoDataExchange( CDataExchange* pDX )
{
    CDialog::DoDataExchange(pDX);
}

// **********************************************************************************************************
// *                             Fonction publiques de la classe ZVDocumentPageSetupDlg                        *
// **********************************************************************************************************

// Cette fonction permet de mettre à jour les boutons du formulaire.
void ZVDocumentPageSetupDlg::UpdateDatas()
{
    if ( m_Orientation == DMORIENT_PORTRAIT )
    {
        CheckDlgButton( IDC_PORTRAIT, TRUE );
        CheckDlgButton( IDC_LANDSCAPE, FALSE );
    }
    else
    {
        CheckDlgButton( IDC_PORTRAIT, FALSE );
        CheckDlgButton( IDC_LANDSCAPE, TRUE );
    }
}

// Cette fonction permet de définir la dimension du papier.
void ZVDocumentPageSetupDlg::SetPaperSize( CSize PaperSize )
{
    m_PaperSize = PaperSize;
}

// Cette fonction permet de définir la taille standard du papier.
void ZVDocumentPageSetupDlg::SetStandardSize( short StandardSize )
{
    m_StandardSize = StandardSize;
}

// Cette fonction permet de définir l'orientation du papier.
void ZVDocumentPageSetupDlg::SetOrientation( short Orientation )
{
    m_Orientation = Orientation;
}

// Cette fonction retourne la dimension du papier.
CSize ZVDocumentPageSetupDlg::GetPaperSize()
{
    return m_PaperSize;
}

// Cette fonction retourne la taille standard du papier.
short ZVDocumentPageSetupDlg::GetStandardSize()
{
    return m_StandardSize;
}

// Cette fonction retourne l'orientation du papier.
short ZVDocumentPageSetupDlg::GetOrientation()
{
    return m_Orientation;
}

// Cette fonction retourne le nom de la trame de fond choisie par l'utilisateur.
CString ZVDocumentPageSetupDlg::GetBackGroundFilename()
{
    return sBkGndName;
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton Portrait.
void ZVDocumentPageSetupDlg::OnBnClickedPortrait()
{
    if ( m_Orientation == DMORIENT_LANDSCAPE )
    {
        CSize m_TmpPaperSize;

        m_TmpPaperSize    = m_PaperSize;
        m_PaperSize.cx    = m_TmpPaperSize.cy;
        m_PaperSize.cy    = m_TmpPaperSize.cx;
    }

    m_Orientation = DMORIENT_PORTRAIT;

    CheckDlgButton( IDC_PORTRAIT, TRUE );
    CheckDlgButton( IDC_LANDSCAPE, FALSE );
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton Paysage.
void ZVDocumentPageSetupDlg::OnBnClickedLandscape()
{
    if ( m_Orientation == DMORIENT_PORTRAIT )
    {
        CSize m_TmpPaperSize;

        m_TmpPaperSize    = m_PaperSize;
        m_PaperSize.cx    = m_TmpPaperSize.cy;
        m_PaperSize.cy    = m_TmpPaperSize.cx;
    }

    m_Orientation = DMORIENT_LANDSCAPE;

    CheckDlgButton( IDC_PORTRAIT, FALSE );
    CheckDlgButton( IDC_LANDSCAPE, TRUE );
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton de sélection d'un fichier.
void ZVDocumentPageSetupDlg::OnBnClickedBtOpenfile()
{
    CString FiltersJpg = _T( "Images au format jpeg (*.jpg)|*.jpg|" );
    CString FiltersGif = _T( "Images au format gif (*.gif)|*.gif|" );
    CString FiltersPcx = _T( "Images au format pcx (*.pcx)|*.pcx|" );
    CString FiltersDib = _T( "Images au format dib (*.dib)|*.dib|" );
    CString FiltersTga = _T( "Images au format tga (*.tga)|*.tga|" );
    CString FiltersTif = _T( "Images au format tif (*.tif)|*.tif|" );

    CString Filters = FiltersJpg + FiltersGif + FiltersPcx + FiltersDib + FiltersTga + FiltersTif + _T( "|" );

    CFileDialog m_FileDialog( TRUE, NULL, NULL ,OFN_OVERWRITEPROMPT, Filters );

    if ( m_FileDialog.DoModal() == IDOK )
    {
        sBkGndName = m_FileDialog.GetPathName();

        CWnd* m_pFilenameTxtBox = GetDlgItem( IDC_EDIT_FILENAME );
        m_pFilenameTxtBox->SetWindowText( sBkGndName );
    }
}

// Cette fonction est appelée lorsque l'utilisateur change de texte de la boîte d'édition du nom de fichier.
void ZVDocumentPageSetupDlg::OnEnChangeEditFilename()
{
        CWnd* m_pFilenameTxtBox = GetDlgItem( IDC_EDIT_FILENAME );
        m_pFilenameTxtBox->GetWindowText( sBkGndName );
}

// Cette fonction est appelée lorsque la boîte de dialogue s'initialise.
BOOL ZVDocumentPageSetupDlg::OnInitDialog()
{
    ZIWizardDialog::OnInitDialog();

    UpdateDatas();

    CWnd* m_pFilenameTxtBox = GetDlgItem( IDC_EDIT_FILENAME );
    m_pFilenameTxtBox->SetWindowText( _T( "" ) );

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION : les pages de propriétés OCX devraient retourner FALSE
}
