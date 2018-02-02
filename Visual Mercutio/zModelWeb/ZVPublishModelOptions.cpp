// ZVPublishModelOptions.cpp : implementation file

#include "stdafx.h"
#include "ZVPublishModelOptions.h"
#include ".\zvpublishmodeloptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 27 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// ******************************************************************************************************************
// * JMR-MODIF - Le 4 juillet 2005 - Supprimé l'option de publication HTML en chemin relatif ou absolu. Ajouté		*
// * l'option de publication du rapport Conceptor.																	*
// ******************************************************************************************************************

BEGIN_MESSAGE_MAP( ZVPublishModelOptions, ZIWizardDialog )
	//{{AFX_MSG_MAP(ZVPublishModelOptions)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_PUBLISH_CONCEPTOR, OnBnClickedPublishConceptor)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelOptions dialog

ZVPublishModelOptions::ZVPublishModelOptions( BOOL		Visualize								/*= TRUE*/,
											  BOOL		PublishConceptorIsChecked				/*= TRUE*/,
					 						  BOOL		PublishConceptorDetailsIsChecked		/*= FALSE*/,
											  BOOL		PublishConceptorDeliverablesIsChecked	/*= FALSE*/,
											  BOOL		PublishProcessIsChecked					/*= TRUE*/,
											  BOOL		PublishRuleBookIsChecked				/*= FALSE*/,
											  Language	InitialLanguage							/*= ZCLanguageCombo::UnknownLang*/,
											  CWnd*		pParent									/*= NULL*/ )
	: ZIWizardDialog( ZVPublishModelOptions::IDD,												// Dialog template
					  IDB_WZBMP1,																// Bitmap to display
					  0,																		// Icon do display
					  0,																		// Window Title
					  IDS_PUBLISHMODELOPTIONS_S,												// Wizard title
					  IDS_PUBLISHMODELOPTIONS_T													// Wizard text
					),
					m_Language								( InitialLanguage ),
					m_PublishConceptorDetailsIsChecked		( FALSE ),
					m_PublishConceptorDeliverablesIsChecked	( FALSE )
{
	//{{AFX_DATA_INIT(ZVPublishModelOptions)
	m_Visualize								= Visualize;
	m_PublishConceptorIsChecked				= PublishConceptorIsChecked;
	m_PublishConceptorDetailsIsChecked		= PublishConceptorDetailsIsChecked;
	m_PublishConceptorDeliverablesIsChecked	= PublishConceptorDeliverablesIsChecked;
	m_PublishProcessIsChecked				= PublishProcessIsChecked;
	m_PublishRuleBookIsChecked				= PublishRuleBookIsChecked;
	//}}AFX_DATA_INIT
}

void ZVPublishModelOptions::DoDataExchange( CDataExchange* pDX )
{
	ZIWizardDialog::DoDataExchange( pDX );

	//{{AFX_DATA_MAP(ZVPublishModelOptions)
	DDX_Control	(pDX, IDC_LANGUAGE,					m_cbLanguage);
	DDX_Check	(pDX, IDC_VISUALIZERESULT,			m_Visualize);
	DDX_Check	(pDX, IDC_PUBLISH_CONCEPTOR,		m_PublishConceptorIsChecked);
	DDX_Check	(pDX, IDC_CONCEPTOR_DETAILS,		m_PublishConceptorDetailsIsChecked);
	DDX_Check	(pDX, IDC_CONCEPTOR_DELIVERABLES,	m_PublishConceptorDeliverablesIsChecked);
	DDX_Check	(pDX, IDC_PUBLISH_PROCESS,			m_PublishProcessIsChecked);
	DDX_Check	(pDX, IDC_PUBLISH_RULEBOOK,			m_PublishRuleBookIsChecked);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVPublishModelOptions message handlers

BOOL ZVPublishModelOptions::OnInitDialog()
{
	ZIWizardDialog::OnInitDialog();

	// Initialize the language combo-box
	m_cbLanguage.Initialize( m_Language );

	// JMR-MODIF - Le 5 août 2005 - Ajout du code de mise à jour des boutons.
	OnBnClickedPublishConceptor();

	return TRUE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}

void ZVPublishModelOptions::OnOK()
{
	UpdateData();
	
	// Saves the language selected
	m_Language = m_cbLanguage.GetLanguage();

	ZIWizardDialog::OnOK();
}

// JMR-MODIF - Le 5 août 2005 - Ajout du code pour la mise à jour des options de publication Conceptor.
void ZVPublishModelOptions::OnBnClickedPublishConceptor()
{
	CWnd* m_pIncludeDetailsCheckBox			= GetDlgItem( IDC_CONCEPTOR_DETAILS );
	CWnd* m_pIncludeDeliverablesCheckBox	= GetDlgItem( IDC_CONCEPTOR_DELIVERABLES );

	if ( m_pIncludeDetailsCheckBox != NULL && IDC_CONCEPTOR_DELIVERABLES != NULL )
	{
		m_pIncludeDetailsCheckBox->EnableWindow( IsDlgButtonChecked( IDC_PUBLISH_CONCEPTOR ) );
		m_pIncludeDeliverablesCheckBox->EnableWindow( IsDlgButtonChecked( IDC_PUBLISH_CONCEPTOR ) );
	}
}
