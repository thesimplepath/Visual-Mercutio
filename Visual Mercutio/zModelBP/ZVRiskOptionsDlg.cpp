// **************************************************************************************************************
// *										   Classe ZVRiskOptionsDlg											*
// **************************************************************************************************************
// * JMR-MODIF - Le 25 juin 2007 - Ajout de la classe ZVRiskOptionsDlg.											*
// **************************************************************************************************************
// * Cette classe permet à l'utilisateur de paramétrer les différentes données d'un risque.						*
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVRiskOptionsDlg.h"

#include "zBaseLib\ZAGlobal.h"
#include "zMediator\ZBMediator.h"

#include "ZVRiskModifyDlg.h"
#include "ZVRiskModifyStaticDlg.h"

#include "ZVRiskTypeContainer.h"
#include "ZVRiskImpactContainer.h"
#include "ZVRiskProbabilityContainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 12 juin 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

BEGIN_MESSAGE_MAP( ZVRiskOptionsDlg, CDialog )
	//{{AFX_MSG_MAP(ZVRiskOptionsDlg)
	ON_CBN_SELCHANGE(IDC_RISK_IMPACT, OnCbnSelchangeRiskImpact)
	ON_CBN_SELCHANGE(IDC_RISK_PROBABILITY, OnCbnSelchangeRiskProbability)
	ON_BN_CLICKED(IDC_MODIFY_RISK_TYPE, OnBnClickedModifyRiskType)
	ON_BN_CLICKED(IDC_OPEN_RISK_TYPE, OnBnClickedOpenRiskType)
	ON_BN_CLICKED(IDC_MODIFY_RISK_IMPACT, OnBnClickedModifyRiskImpact)
	ON_BN_CLICKED(IDC_MODIFY_RISK_PROBABILITY, OnBnClickedModifyRiskProbability)
	ON_BN_CLICKED(IDC_OPEN_RISK_IMPACT, OnBnClickedOpenRiskImpact)
	ON_BN_CLICKED(IDC_OPEN_RISK_PROBABILITY, OnBnClickedOpenRiskProbability)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVRiskOptionsDlg dialog

ZVRiskOptionsDlg::ZVRiskOptionsDlg( CString	RiskName,
									CString	RiskDesc,
									CString	RiskType,
									int		RiskImpact,
									int		RiskProbability,
									float	RiskUE,
									float	RiskPOA,
									bool	RiskAction,
									CString	CurrencySymbol,
									CWnd*	pParent			/*= NULL*/ )
	: CDialog			( ZVRiskOptionsDlg::IDD, pParent ),
	  m_RiskName		( RiskName ),
	  m_RiskDesc		( RiskDesc ),
	  m_RiskType		( RiskType ),
	  m_RiskImpact		( RiskImpact ),
	  m_RiskProbability	( RiskProbability ),
	  m_RiskUE			( RiskUE ),
	  m_RiskPOA			( RiskPOA ),
	  m_RiskAction		( RiskAction ),
	  m_CurrencySymbol	( CurrencySymbol )
{
	//{{AFX_DATA_INIT(ZVReferenceFileDlg)
	//}}AFX_DATA_INIT
}

// Cette fonction retourne le titre du risque.
CString ZVRiskOptionsDlg::GetRiskTitle()
{
	return m_RiskName;
}

// Cette fonction retourne la description du risque.
CString ZVRiskOptionsDlg::GetRiskDescription()
{
	return m_RiskDesc;
}

// Cette fonction retourne le type du risque.
CString ZVRiskOptionsDlg::GetRiskType()
{
	return m_RiskType;
}

// Cette fonction retourne le niveau d'impact du risque.
int ZVRiskOptionsDlg::GetRiskImpact()
{
	return m_RiskImpact;
}

// Cette fonction retourne le niveau de probabilité du risque.
int ZVRiskOptionsDlg::GetRiskProbability()
{
	return m_RiskProbability;
}

// Cette fonction retourne la sévérité du risque.
int ZVRiskOptionsDlg::GetRiskSeverity()
{
	return m_RiskImpact * m_RiskProbability;
}

// Cette fonction retourne l'estimation unitaire du risque.
float ZVRiskOptionsDlg::GetRiskUE()
{
	return m_RiskUE;
}

// Cette fonction retourne la perte opérationnelle annuelle du risque.
float ZVRiskOptionsDlg::GetRiskPOA()
{
	return m_RiskPOA;
}

// Cette fonction retourne l'action du risque.
bool ZVRiskOptionsDlg::GetRiskAction()
{
	return m_RiskAction;
}

// Cette fonction retourne l'index de l'impact sélectionné.
int ZVRiskOptionsDlg::GetImpactIndex()
{
	return m_RiskImpactCtrl.GetCurSel();
}

// Cette fonction retourne l'index de la probabilité sélectionnée.
int ZVRiskOptionsDlg::GetProbabilityIndex()
{
	return m_RiskProbabilityCtrl.GetCurSel();
}

// Cette fonction mets à jour l'affichage de la sévérité.
void ZVRiskOptionsDlg::UpdateSeverity()
{
	CString SeverityResult = _T( "" );
	SeverityResult.Format( _T( "%d" ), ( GetImpactIndex() ) * ( GetProbabilityIndex() ) );
	m_RiskSeverityCtrl.SetWindowText( SeverityResult );
}

// Cette fonction permet à l'utilisateur de sélectionner un fichier exstant.
void ZVRiskOptionsDlg::SelectFileToOpen( CString Directory, CString Caption, CString Extension, CString& Filename )
{
	CString s_Filename	= _T( "" );
	CString s_Filter	= _T( "" );

	CFileDialog m_DlgFile( TRUE );

	CString s_Title = _T( "" );
	VERIFY( s_Title.LoadString( IDS_RISK_OPENFILE ) );

	// Configuration de la fenêtre "Ouvrir un fichier..."
	m_DlgFile.m_ofn.lpstrTitle		= s_Title;
	m_DlgFile.m_ofn.hwndOwner		= AfxGetMainWnd()->GetSafeHwnd();
	m_DlgFile.m_ofn.Flags		   |= OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

	// Crée le filtre d'extension des fichiers d'initialisation (*.ini)
	s_Filter += Caption;
	s_Filter += (char)'\0';
	s_Filter += _T( "*" ) + Extension;
	s_Filter += (char)'\0';

	m_DlgFile.m_ofn.nMaxCustFilter++;

	// Crée le filtre d'extension pour tous les fichiers (*.*)
	CString s_AllFilter = _T( "" );
	VERIFY( s_AllFilter.LoadString( AFX_IDS_ALLFILTER ) );

	s_Filter += s_AllFilter;
	s_Filter += (char)'\0';
	s_Filter += _T( "*.*" );
	s_Filter += (char)'\0';

	m_DlgFile.m_ofn.nMaxCustFilter++;

	// Ajoute les données nécessaires pour les fichiers.
	m_DlgFile.m_ofn.nMaxFile		= _MAX_PATH;
	m_DlgFile.m_ofn.lpstrFile		= s_Filename.GetBuffer( _MAX_PATH );
	m_DlgFile.m_ofn.lpstrFilter		= s_Filter;
	m_DlgFile.m_ofn.lpstrInitialDir	= Directory;

	if ( m_DlgFile.DoModal() == IDOK )
	{
		Filename = s_Filename.GetBuffer();
		return;
	}

	Filename = _T( "" );
}

// Cette fonction mets à jour les données des types après un changement de fichier.
BOOL ZVRiskOptionsDlg::ReloadTypeFile( CString Filename )
{
	ZBMediator::Instance()->GetMainApp()->GetRiskTypeContainer()->RemoveAllElements();

	if ( ZBMediator::Instance()->GetMainApp()->GetRiskTypeContainer()->LoadFile( Filename ) == TRUE )
	{
		LoadTypeList();

		CString s_NoRiskType = _T( "" );
		s_NoRiskType.LoadString( IDS_NO_RISK_TYPE );
		m_RiskTypeCtrl.SetWindowText( s_NoRiskType );

		return TRUE;
	}

	return FALSE;
}

// Cette fonction mets à jour les données des impacts après un changement de fichier.
BOOL ZVRiskOptionsDlg::ReloadImpactFile( CString Filename )
{
	ZBMediator::Instance()->GetMainApp()->GetRiskImpactContainer()->RemoveAllElements();

	if ( ZBMediator::Instance()->GetMainApp()->GetRiskImpactContainer()->LoadFile( Filename ) == TRUE )
	{
		LoadImpactList();

		m_RiskImpactCtrl.SetCurSel( m_RiskImpact );

		return TRUE;
	}

	return FALSE;
}

// Cette fonction mets à jour les données des probabilités après un changement de fichier.
BOOL ZVRiskOptionsDlg::ReloadProbabilityFile( CString Filename )
{
	ZBMediator::Instance()->GetMainApp()->GetRiskProbabilityContainer()->RemoveAllElements();

	if ( ZBMediator::Instance()->GetMainApp()->GetRiskProbabilityContainer()->LoadFile( Filename ) == TRUE )
	{
		LoadProbabilityList();

		m_RiskProbabilityCtrl.SetCurSel( m_RiskProbability );

		return TRUE;
	}

	return FALSE;
}

// Cette fonction remplit la liste des types de risques.
void ZVRiskOptionsDlg::LoadTypeList()
{
	if ( m_RiskTypeCtrl.GetCount() > 0 )
	{
		while ( m_RiskTypeCtrl.GetCount() > 0 )
		{
			m_RiskTypeCtrl.DeleteString( 0 );
		}
	}

	for ( int i = 0; i < ZBMediator::Instance()->GetMainApp()->GetRiskTypeContainer()->GetElementCount(); i++ )
	{
		m_RiskTypeCtrl.AddString( ZBMediator::Instance()->GetMainApp()->GetRiskTypeContainer()->GetElementAt( i ) );
	}
}

// Cette fonction remplit la liste des impacts des risques.
void ZVRiskOptionsDlg::LoadImpactList()
{
	if ( m_RiskImpactCtrl.GetCount() > 0 )
	{
		while ( m_RiskImpactCtrl.GetCount() > 0 )
		{
			m_RiskImpactCtrl.DeleteString( 0 );
		}
	}

	for ( int i = 0; i < ZBMediator::Instance()->GetMainApp()->GetRiskImpactContainer()->GetElementCount(); i++ )
	{
		m_RiskImpactCtrl.AddString( ZBMediator::Instance()->GetMainApp()->GetRiskImpactContainer()->GetElementAt( i ) );
	}
}

// Cette fonction remplit la liste des probabilités des risques.
void ZVRiskOptionsDlg::LoadProbabilityList()
{
	if ( m_RiskProbabilityCtrl.GetCount() > 0 )
	{
		while ( m_RiskProbabilityCtrl.GetCount() > 0 )
		{
			m_RiskProbabilityCtrl.DeleteString( 0 );
		}
	}

	for ( int i = 0; i < ZBMediator::Instance()->GetMainApp()->GetRiskProbabilityContainer()->GetElementCount(); i++ )
	{
		m_RiskProbabilityCtrl.AddString
			( ZBMediator::Instance()->GetMainApp()->GetRiskProbabilityContainer()->GetElementAt( i ) );
	}
}

void ZVRiskOptionsDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange( pDX );

	//{{AFX_DATA_MAP(ZVRiskOptionsDlg)
	DDX_Text(pDX, IDC_RISK_TITLE_EDIT, m_RiskName);
	DDX_Text(pDX, IDC_RISK_DESCRIPTION_EDIT, m_RiskDesc);
	DDX_Control(pDX, IDC_RISK_IMPACT, m_RiskImpactCtrl);
	DDX_Control(pDX, IDC_RISK_PROBABILITY, m_RiskProbabilityCtrl);
	DDX_Control(pDX, IDC_RISK_SEVERITY, m_RiskSeverityCtrl);
	DDX_Control(pDX, IDC_RISK_TYPE, m_RiskTypeCtrl);
	DDX_Control(pDX, IDC_UE_FRS_LABEL, m_UEFrsLabelCtrl);
	DDX_Control(pDX, IDC_POA_FRS_LABEL, m_POAFrsLabelCtrl);
	DDX_Text(pDX, IDC_UE, m_RiskUE);
	DDX_Text(pDX, IDC_POA, m_RiskPOA);
	DDX_Check(pDX, IDC_ACTION, m_RiskAction);
	DDX_CBString(pDX, IDC_RISK_TYPE, m_RiskType);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVRiskOptionsDlg message handlers

// Cette fonction est appelée lorsque la fenêtre s'initialise.
BOOL ZVRiskOptionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadTypeList();
	LoadImpactList();
	LoadProbabilityList();

	m_RiskImpactCtrl.SetCurSel( m_RiskImpact );
	m_RiskProbabilityCtrl.SetCurSel( m_RiskProbability );

	UpdateSeverity();

	m_UEFrsLabelCtrl.SetWindowText( m_CurrencySymbol );
	m_POAFrsLabelCtrl.SetWindowText( m_CurrencySymbol );

	return TRUE;
}

// Cette fonction est appelée lorsque la liste des impacts change.
void ZVRiskOptionsDlg::OnCbnSelchangeRiskImpact()
{
	m_RiskImpact = GetImpactIndex();
	UpdateSeverity();
}

// Cette fonction est appelée lorsque la liste des probabilités change.
void ZVRiskOptionsDlg::OnCbnSelchangeRiskProbability()
{
	m_RiskProbability = GetProbabilityIndex();
	UpdateSeverity();
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "modifier un fichier de type".
void ZVRiskOptionsDlg::OnBnClickedModifyRiskType()
{
	CString m_TypeFilename = ZBMediator::Instance()->GetMainApp()->GetRiskTypeContainer()->GetFilename();

	ZVRiskModifyDlg m_ModifyTypeDlg( m_TypeFilename, sRiskTypeExtension );

	if ( m_ModifyTypeDlg.DoModal() == TRUE )
	{
		ReloadTypeFile( m_ModifyTypeDlg.GetFilename() );
	}
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "ouvrir un fichier de type".
void ZVRiskOptionsDlg::OnBnClickedOpenRiskType()
{
	CString m_Filename	= _T( "" );
	CString m_Desc		= _T( "" );

	m_Desc.LoadString( IDS_RISK_TYPE_FILE_DESCRIPTION );

	SelectFileToOpen( ZBMediator::Instance()->GetMainApp()->GetApplicationDirectory() + szRiskDirectory,
					  m_Desc,
					  sRiskTypeExtension,
					  m_Filename );

	if ( !m_Filename.IsEmpty() )
	{
		ReloadTypeFile( m_Filename );
	}
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "modifier un fichier d'impact".
void ZVRiskOptionsDlg::OnBnClickedModifyRiskImpact()
{
	CString m_ImpactFilename = ZBMediator::Instance()->GetMainApp()->GetRiskImpactContainer()->GetFilename();

	ZVRiskModifyStaticDlg m_RiskModifyStatic( m_ImpactFilename, sRiskImpactExtension, 5 );

	if ( m_RiskModifyStatic.DoModal() == IDOK )
	{
		ReloadImpactFile( m_RiskModifyStatic.GetFilename() );
	}
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "ouvrir un fichier d'impact".
void ZVRiskOptionsDlg::OnBnClickedOpenRiskImpact()
{
	CString m_Filename	= _T( "" );
	CString m_Desc		= _T( "" );

	m_Desc.LoadString( IDS_RISK_IMPACT_FILE_DESCRIPTION );

	SelectFileToOpen( ZBMediator::Instance()->GetMainApp()->GetApplicationDirectory() + szRiskDirectory,
					  m_Desc,
					  sRiskImpactExtension,
					  m_Filename );

	if ( !m_Filename.IsEmpty() )
	{
		ReloadImpactFile( m_Filename );
	}
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "modifier un fichier de probabilités".
void ZVRiskOptionsDlg::OnBnClickedModifyRiskProbability()
{
	CString m_ProbabilityFilename = ZBMediator::Instance()->GetMainApp()->GetRiskProbabilityContainer()->GetFilename();

	ZVRiskModifyStaticDlg m_RiskModifyStatic( m_ProbabilityFilename, sRiskProbabilityExtension, 6 );

	if ( m_RiskModifyStatic.DoModal() == IDOK )
	{
		ReloadProbabilityFile( m_RiskModifyStatic.GetFilename() );
	}
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "ouvrir un fichier de probabilités".
void ZVRiskOptionsDlg::OnBnClickedOpenRiskProbability()
{
	CString m_Filename = _T( "" );
	CString m_Desc		= _T( "" );

	m_Desc.LoadString( IDS_RISK_PROBABILITY_FILE_DESCRIPTION );

	SelectFileToOpen( ZBMediator::Instance()->GetMainApp()->GetApplicationDirectory() + szRiskDirectory,
					  m_Desc,
					  sRiskProbabilityExtension,
					  m_Filename );

	if ( !m_Filename.IsEmpty() )
	{
		ReloadProbabilityFile( m_Filename );
	}
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "OK".
void ZVRiskOptionsDlg::OnOK()
{
	CDialog::OnOK();
}
