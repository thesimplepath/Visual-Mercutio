// **************************************************************************************************************
// *                                           Classe ZVRiskOptionsDlg                                            *
// **************************************************************************************************************
// * JMR-MODIF - Le 25 juin 2007 - Ajout de la classe ZVRiskOptionsDlg.                                            *
// **************************************************************************************************************
// * Cette classe permet à l'utilisateur de paramétrer les différentes données d'un risque.                        *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVRiskOptionsDlg.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zMediator\PSS_Application.h"
#include "ZVRiskModifyDlg.h"
#include "ZVRiskModifyStaticDlg.h"
#include "PSS_RiskTypeContainer.h"
#include "ZVRiskImpactContainer.h"
#include "PSS_RiskProbabilityContainer.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

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

ZVRiskOptionsDlg::ZVRiskOptionsDlg( CString    RiskName,
                                    CString    RiskDesc,
                                    CString    RiskType,
                                    int        RiskImpact,
                                    int        RiskProbability,
                                    float    RiskUE,
                                    float    RiskPOA,
                                    bool    RiskAction,
                                    CString    CurrencySymbol,
                                    CWnd*    pParent            /*= NULL*/ )
    : CDialog            ( ZVRiskOptionsDlg::IDD, pParent ),
      m_RiskName        ( RiskName ),
      m_RiskDesc        ( RiskDesc ),
      m_RiskType        ( RiskType ),
      m_RiskImpact        ( RiskImpact ),
      m_RiskProbability    ( RiskProbability ),
      m_RiskUE            ( RiskUE ),
      m_RiskPOA            ( RiskPOA ),
      m_RiskAction        ( RiskAction ),
      m_CurrencySymbol    ( CurrencySymbol )
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
void ZVRiskOptionsDlg::SelectFileToOpen(const CString& dir, const CString& caption, const CString& extension, CString& fileName)
{
    CFileDialog dlgFile(TRUE);

    CString title = _T("");
    VERIFY(title.LoadString(IDS_RISK_OPENFILE));

    // configure the Open File dialog
    dlgFile.m_ofn.lpstrTitle  = title;
    dlgFile.m_ofn.hwndOwner   = AfxGetMainWnd()->GetSafeHwnd();
    dlgFile.m_ofn.Flags      |= OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

    CString filter = _T("");

    // create ini file extension filter (*.ini)
    filter += caption;
    filter += (char)'\0';
    filter += _T( "*" ) + extension;
    filter += (char)'\0';

    ++dlgFile.m_ofn.nMaxCustFilter;

    // create all files extension filter (*.*)
    CString allFilter = _T("");
    VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));

    filter += allFilter;
    filter += '\0';
    filter += _T("*.*");
    filter += '\0';

    ++dlgFile.m_ofn.nMaxCustFilter;

    CString fn = _T("");

    // add file data
    dlgFile.m_ofn.nMaxFile        = _MAX_PATH;
    dlgFile.m_ofn.lpstrFile       = fn.GetBuffer(_MAX_PATH);
    dlgFile.m_ofn.lpstrFilter     = filter;
    dlgFile.m_ofn.lpstrInitialDir = dir;

    // show the Open File dialog
    if (dlgFile.DoModal() == IDOK)
    {
        fileName = fn.GetBuffer();
        return;
    }

    fileName = _T("");
}

// Cette fonction mets à jour les données des types après un changement de fichier.
BOOL ZVRiskOptionsDlg::ReloadTypeFile(const CString& fileName)
{
    PSS_Application::Instance()->GetMainForm()->GetRiskTypeContainer()->RemoveAllElements();

    if (PSS_Application::Instance()->GetMainForm()->GetRiskTypeContainer()->LoadFile(fileName))
    {
        LoadTypeList();

        CString noRiskType = _T("");
        noRiskType.LoadString(IDS_NO_RISK_TYPE);
        m_RiskTypeCtrl.SetWindowText(noRiskType);

        return TRUE;
    }

    return FALSE;
}

// Cette fonction mets à jour les données des impacts après un changement de fichier.
BOOL ZVRiskOptionsDlg::ReloadImpactFile(const CString& fileName)
{
    PSS_Application::Instance()->GetMainForm()->GetRiskImpactContainer()->RemoveAllElements();

    if (PSS_Application::Instance()->GetMainForm()->GetRiskImpactContainer()->LoadFile(fileName))
    {
        LoadImpactList();
        m_RiskImpactCtrl.SetCurSel(m_RiskImpact);
        return TRUE;
    }

    return FALSE;
}

// Cette fonction mets à jour les données des probabilités après un changement de fichier.
BOOL ZVRiskOptionsDlg::ReloadProbabilityFile(const CString& fileName)
{
    PSS_Application::Instance()->GetMainForm()->GetRiskProbabilityContainer()->RemoveAllElements();

    if (PSS_Application::Instance()->GetMainForm()->GetRiskProbabilityContainer()->LoadFile(fileName))
    {
        LoadProbabilityList();
        m_RiskProbabilityCtrl.SetCurSel(m_RiskProbability);
        return TRUE;
    }

    return FALSE;
}

// Cette fonction remplit la liste des types de risques.
void ZVRiskOptionsDlg::LoadTypeList()
{
    while (m_RiskTypeCtrl.GetCount() > 0)
        m_RiskTypeCtrl.DeleteString(0);

    for (int i = 0; i < PSS_Application::Instance()->GetMainForm()->GetRiskTypeContainer()->GetElementCount(); ++i)
        m_RiskTypeCtrl.AddString(PSS_Application::Instance()->GetMainForm()->GetRiskTypeContainer()->GetElementAt(i));
}

// Cette fonction remplit la liste des impacts des risques.
void ZVRiskOptionsDlg::LoadImpactList()
{
    while (m_RiskImpactCtrl.GetCount() > 0)
        m_RiskImpactCtrl.DeleteString(0);

    for (int i = 0; i < PSS_Application::Instance()->GetMainForm()->GetRiskImpactContainer()->GetElementCount(); ++i)
        m_RiskImpactCtrl.AddString(PSS_Application::Instance()->GetMainForm()->GetRiskImpactContainer()->GetElementAt(i));
}

// Cette fonction remplit la liste des probabilités des risques.
void ZVRiskOptionsDlg::LoadProbabilityList()
{
    while (m_RiskProbabilityCtrl.GetCount() > 0)
        m_RiskProbabilityCtrl.DeleteString(0);

    for (int i = 0; i < PSS_Application::Instance()->GetMainForm()->GetRiskProbabilityContainer()->GetElementCount(); ++i)
        m_RiskProbabilityCtrl.AddString
                (PSS_Application::Instance()->GetMainForm()->GetRiskProbabilityContainer()->GetElementAt(i));
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
    const CString         typeFileName = PSS_Application::Instance()->GetMainForm()->GetRiskTypeContainer()->GetFileName();
          ZVRiskModifyDlg modifyTypeDlg(typeFileName, g_RiskTypeExtension);

    if (modifyTypeDlg.DoModal())
        ReloadTypeFile(modifyTypeDlg.GetFileName());
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "ouvrir un fichier de type".
void ZVRiskOptionsDlg::OnBnClickedOpenRiskType()
{
    CString fileName = _T("");
    CString desc     = _T("");

    desc.LoadString(IDS_RISK_TYPE_FILE_DESCRIPTION);

    SelectFileToOpen(PSS_Application::Instance()->GetMainForm()->GetApplicationDir() + g_RiskDirectory,
                     desc,
                     g_RiskTypeExtension,
                     fileName );

    if (!fileName.IsEmpty())
        ReloadTypeFile(fileName);
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "modifier un fichier d'impact".
void ZVRiskOptionsDlg::OnBnClickedModifyRiskImpact()
{
    const CString               impactFileName = PSS_Application::Instance()->GetMainForm()->GetRiskImpactContainer()->GetFileName();
          ZVRiskModifyStaticDlg riskModifyStatic(impactFileName, g_RiskImpactExtension, 5);

    if (riskModifyStatic.DoModal() == IDOK)
        ReloadImpactFile(riskModifyStatic.GetFileName());
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "ouvrir un fichier d'impact".
void ZVRiskOptionsDlg::OnBnClickedOpenRiskImpact()
{
    CString fileName = _T("");
    CString desc     = _T("");

    desc.LoadString(IDS_RISK_IMPACT_FILE_DESCRIPTION);

    SelectFileToOpen(PSS_Application::Instance()->GetMainForm()->GetApplicationDir() + g_RiskDirectory,
                     desc,
                     g_RiskImpactExtension,
                     fileName);

    if (!fileName.IsEmpty())
        ReloadImpactFile(fileName);
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "modifier un fichier de probabilités".
void ZVRiskOptionsDlg::OnBnClickedModifyRiskProbability()
{
    const CString               probabilityFileName = PSS_Application::Instance()->GetMainForm()->GetRiskProbabilityContainer()->GetFileName();
          ZVRiskModifyStaticDlg riskModifyStatic(probabilityFileName, g_RiskProbabilityExtension, 6);

    if (riskModifyStatic.DoModal() == IDOK)
        ReloadProbabilityFile(riskModifyStatic.GetFileName());
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "ouvrir un fichier de probabilités".
void ZVRiskOptionsDlg::OnBnClickedOpenRiskProbability()
{
    CString fileName = _T("");
    CString desc     = _T("");

    desc.LoadString(IDS_RISK_PROBABILITY_FILE_DESCRIPTION);

    SelectFileToOpen(PSS_Application::Instance()->GetMainForm()->GetApplicationDir() + g_RiskDirectory,
                     desc,
                     g_RiskProbabilityExtension,
                     fileName);

    if (!fileName.IsEmpty())
        ReloadProbabilityFile(fileName);
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "OK".
void ZVRiskOptionsDlg::OnOK()
{
    CDialog::OnOK();
}
