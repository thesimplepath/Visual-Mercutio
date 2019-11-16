// **************************************************************************************************************
// *                                       Classe ZVRiskCalculateParametersDlg                                    *
// **************************************************************************************************************
// * JMR-MODIF - Le 21 juillet 2007 - Ajout de la classe ZVRiskCalculateParametersDlg.                            *
// **************************************************************************************************************
// * Cette classe permet à l'utilisateur de paramétrer les données pour calculer les risques dans le modèle.    *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZVRiskCalculateParametersDlg.h"

// processsoft
#include "zMediator\PSS_Application.h"
#include "zBaseLib\PSS_File.h"
#include "zBaseLib\PSS_TextFile.h"
#include "zBaseLib\PSS_SystemOption.h"
#include "zBaseLib\PSS_MsgBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Définition des clés pour le fichier de configuration.
const CString gRulesCalculationSectionName = _T("RulesCalculation");
const CString gRulesCalculationOrangeSeverity = _T("OrangeSeverity");
const CString gRulesCalculationRedSeverity = _T("RedSeverity");
const CString gRulesCalculationOrangeUE = _T("OrangeUE");
const CString gRulesCalculationOrangePOA = _T("OrangePOA");
const CString gRulesCalculationRedUE = _T("RedUE");
const CString gRulesCalculationRedPOA = _T("RedPOA");
const CString gRulesCalculationOrangeAction = _T("OrangeAction");
const CString gRulesCalculationOrangeNoAction = _T("OrangeNoAction");
const CString gRulesCalculationOrangeActionChecked = _T("OrangeActionChecked");
const CString gRulesCalculationOrangeNoActionChecked = _T("OrangeNoActionChecked");
const CString gRulesCalculationRedAction = _T("RedAction");
const CString gRulesCalculationRedNoAction = _T("RedNoAction");
const CString gRulesCalculationDefaultColors = _T("DefaultColors");

BEGIN_MESSAGE_MAP(ZVRiskCalculateParametersDlg, CDialog)
    //{{AFX_MSG_MAP(ZVRiskCalculateParametersDlg)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_ORANGE_SEVERITY, OnNMReleasedcaptureOrangeSeverity)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_RED_SEVERITY, OnNMReleasedcaptureRedSeverity)
    ON_BN_CLICKED(IDC_ORANGE_ACTION, OnBnClickedOrangeAction)
    ON_BN_CLICKED(IDC_ORANGE_NO_ACTION, OnBnClickedOrangeNoAction)
    ON_BN_CLICKED(IDC_RED_ACTION, OnBnClickedRedAction)
    ON_BN_CLICKED(IDC_RED_NO_ACTION, OnBnClickedRedNoAction)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVRiskNewFileDlg dialog

ZVRiskCalculateParametersDlg::ZVRiskCalculateParametersDlg(CString    iniFileName,
                                                           CString    CurrencySymbol,
                                                           CWnd*    pParent            /*= NULL*/)
    : CDialog(ZVRiskCalculateParametersDlg::IDD, pParent),
    m_IniFileName(iniFileName),
    m_CurrencySymbol(CurrencySymbol),
    m_OrangeSeverity(0),
    m_RedSeverity(0),
    m_OrangeAction(FALSE),
    m_OrangeNoAction(FALSE),
    m_OrangeActionChecked(FALSE),
    m_OrangeNoActionChecked(FALSE),
    m_RedAction(FALSE),
    m_RedNoAction(FALSE),
    m_DefaultColors(FALSE),
    m_OrangeUE(0.0f),
    m_OrangePOA(0.0f),
    m_RedUE(0.0f),
    m_RedPOA(0.0f)
{
    //{{AFX_DATA_INIT(ZVRiskCalculateParametersDlg)
    //}}AFX_DATA_INIT
}

// Cette fonction retourne le niveau de sévérité du groupe orange.
int ZVRiskCalculateParametersDlg::GetOrangeSeverityLevel()
{
    return m_OrangeSeverity;
}

// Cette fonction retourne le niveau de sévérité du groupe rouge.
int ZVRiskCalculateParametersDlg::GetRedSeverityLevel()
{
    return m_RedSeverity;
}

// Cette fonction retourne l'estimation unitaire du groupe orange.
float ZVRiskCalculateParametersDlg::GetOrangeUE()
{
    return m_OrangeUE;
}

// Cette fonction retourne l'estimation unitaire du groupe rouge.
float ZVRiskCalculateParametersDlg::GetRedUE()
{
    return m_RedUE;
}

// Cette fonction retourne la perte opérationnelle annuelle du groupe orange.
float ZVRiskCalculateParametersDlg::GetOrangePOA()
{
    return m_OrangePOA;
}

// Cette fonction retourne la perte opérationnelle annuelle du groupe rouge.
float ZVRiskCalculateParametersDlg::GetRedPOA()
{
    return m_RedPOA;
}

// Cette fonction indique si le bouton "Action en cours" du groupe orange est cochée.
BOOL ZVRiskCalculateParametersDlg::IsOrangeActionEnabled()
{
    return m_OrangeAction;
}

// Cette fonction indique si le bouton "Pas d'action en cours" du groupe orange est cochée.
BOOL ZVRiskCalculateParametersDlg::IsOrangeNoActionEnabled()
{
    return m_OrangeNoAction;
}

// Cette fonction indique si le bouton "Action en cours" du groupe rouge est cochée.
BOOL ZVRiskCalculateParametersDlg::IsRedActionEnabled()
{
    return m_RedAction;
}

// Cette fonction indique si le bouton "Pas d'action en cours" du groupe rouge est cochée.
BOOL ZVRiskCalculateParametersDlg::IsRedNoActionEnabled()
{
    return m_RedNoAction;
}

// Cette fonction indique si la case "Couleurs par défaut" est cochée.
BOOL ZVRiskCalculateParametersDlg::IsDefaultColorsEnabled()
{
    return m_DefaultColors;
}

// Cette fonction mets à jour l'affichage du niveau de risque orange.
void ZVRiskCalculateParametersDlg::UpdateOrangeLevel()
{
    CString s_Level = _T("");

    s_Level.Format(_T("%d"), m_OrangeSeverityCtrl.GetPos());
    m_OrangeLevelCtrl.SetWindowText(s_Level);
}

// Cette fonction mets à jour l'affichage du niveau de risques rouge.
void ZVRiskCalculateParametersDlg::UpdateRedLevel()
{
    CString s_Level = _T("");

    s_Level.Format(_T("%d"), m_RedSeverityCtrl.GetPos());
    m_RedLevelCtrl.SetWindowText(s_Level);
}

// Cette fonction permet de mettre à jour le bouton OK en fonction des sélections de l'utilisateur.
void ZVRiskCalculateParametersDlg::UpdateOKButton()
{
    if (m_OrangeActionCtrl.GetCheck() == FALSE &&
        m_OrangeNoActionCtrl.GetCheck() == FALSE &&
        m_RedActionCtrl.GetCheck() == FALSE &&
        m_RedNoActionCtrl.GetCheck() == FALSE)
    {
        m_OKCtrl.EnableWindow(FALSE);
    }
    else
    {
        m_OKCtrl.EnableWindow(TRUE);
    }
}

// Cette fonction permet de charger les données des paramètres depuis le fichier de configuration.
bool ZVRiskCalculateParametersDlg::LoadStateFromIniFile()
{
    PSS_SystemOption SystemOption(m_IniFileName, gRulesCalculationSectionName);

    // Read the options
    m_OrangeSeverity = SystemOption.ReadOption(gRulesCalculationOrangeSeverity, 1);
    m_RedSeverity = SystemOption.ReadOption(gRulesCalculationRedSeverity, 2);
    m_OrangeUE = SystemOption.ReadOption(gRulesCalculationOrangeUE, 0.0f);
    m_OrangePOA = SystemOption.ReadOption(gRulesCalculationOrangePOA, 0.0f);
    m_RedUE = SystemOption.ReadOption(gRulesCalculationRedUE, 0.0f);
    m_RedPOA = SystemOption.ReadOption(gRulesCalculationRedPOA, 0.0f);
    m_OrangeAction = SystemOption.ReadOption(gRulesCalculationOrangeAction, FALSE);
    m_OrangeNoAction = SystemOption.ReadOption(gRulesCalculationOrangeNoAction, FALSE);
    m_OrangeActionChecked = SystemOption.ReadOption(gRulesCalculationOrangeActionChecked, FALSE);
    m_OrangeNoActionChecked = SystemOption.ReadOption(gRulesCalculationOrangeNoActionChecked, FALSE);
    m_RedAction = SystemOption.ReadOption(gRulesCalculationRedAction, FALSE);
    m_RedNoAction = SystemOption.ReadOption(gRulesCalculationRedNoAction, FALSE);
    m_DefaultColors = SystemOption.ReadOption(gRulesCalculationDefaultColors, FALSE);

    return true;
}

// Cette fonction permet de sauvegarder les données des paramètres dans le fichier de configuration.
bool ZVRiskCalculateParametersDlg::SaveStateToIniFile()
{
    PSS_SystemOption SystemOption(m_IniFileName, gRulesCalculationSectionName);

    // Saves the options
    SystemOption.WriteOption(gRulesCalculationOrangeSeverity, m_OrangeSeverity);
    SystemOption.WriteOption(gRulesCalculationRedSeverity, m_RedSeverity);
    SystemOption.WriteOption(gRulesCalculationOrangeUE, m_OrangeUE);
    SystemOption.WriteOption(gRulesCalculationOrangePOA, m_OrangePOA);
    SystemOption.WriteOption(gRulesCalculationRedUE, m_RedUE);
    SystemOption.WriteOption(gRulesCalculationRedPOA, m_RedPOA);
    SystemOption.WriteOption(gRulesCalculationOrangeAction, m_OrangeAction);
    SystemOption.WriteOption(gRulesCalculationOrangeNoAction, m_OrangeNoAction);
    SystemOption.WriteOption(gRulesCalculationOrangeActionChecked, m_OrangeActionChecked);
    SystemOption.WriteOption(gRulesCalculationOrangeNoActionChecked, m_OrangeNoActionChecked);
    SystemOption.WriteOption(gRulesCalculationRedAction, m_RedAction);
    SystemOption.WriteOption(gRulesCalculationRedNoAction, m_RedNoAction);
    SystemOption.WriteOption(gRulesCalculationDefaultColors, m_DefaultColors);

    return true;
}

void ZVRiskCalculateParametersDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(ZVRiskCalculateParametersDlg)
    DDX_Control(pDX, IDC_ORANGE_SEVERITY, m_OrangeSeverityCtrl);
    DDX_Control(pDX, IDC_RED_SEVERITY, m_RedSeverityCtrl);
    DDX_Control(pDX, IDC_ORANGE_SEVERITY_LEVEL, m_OrangeLevelCtrl);
    DDX_Control(pDX, IDC_RED_SEVERITY_LEVEL, m_RedLevelCtrl);
    DDX_Control(pDX, IDC_ORANGE_ACTION, m_OrangeActionCtrl);
    DDX_Control(pDX, IDC_RED_ACTION, m_RedActionCtrl);
    DDX_Control(pDX, IDC_ORANGE_NO_ACTION, m_OrangeNoActionCtrl);
    DDX_Control(pDX, IDC_RED_NO_ACTION, m_RedNoActionCtrl);
    DDX_Control(pDX, IDOK, m_OKCtrl);
    DDX_Control(pDX, IDC_ORANGE_UE_FRS_LABEL, m_OrangeUEFrsLabelCtrl);
    DDX_Control(pDX, IDC_ORANGE_POA_FRS_LABEL, m_OrangePOAFrsLabelCtrl);
    DDX_Control(pDX, IDC_RED_UE_FRS_LABEL, m_RedUEFrsLabelCtrl);
    DDX_Control(pDX, IDC_RED_POA_FRS_LABEL, m_RedPOAFrsLabelCtrl);
    DDX_Slider(pDX, IDC_ORANGE_SEVERITY, m_OrangeSeverity);
    DDX_Slider(pDX, IDC_RED_SEVERITY, m_RedSeverity);
    DDX_Check(pDX, IDC_ORANGE_ACTION, m_OrangeAction);
    DDX_Check(pDX, IDC_ORANGE_NO_ACTION, m_OrangeNoAction);
    DDX_Check(pDX, IDC_RED_ACTION, m_RedAction);
    DDX_Check(pDX, IDC_RED_NO_ACTION, m_RedNoAction);
    DDX_Check(pDX, IDC_DEFAULT_COLORS, m_DefaultColors);
    DDX_Text(pDX, IDC_ORANGE_UE, m_OrangeUE);
    DDX_Text(pDX, IDC_ORANGE_POA, m_OrangePOA);
    DDX_Text(pDX, IDC_RED_UE, m_RedUE);
    DDX_Text(pDX, IDC_RED_POA, m_RedPOA);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVRiskCalculateParametersDlg message handlers

// Cette fonction est appelée lorsque la fenêtre s'initialise.
BOOL ZVRiskCalculateParametersDlg::OnInitDialog()
{
    // Cet appel doit être placé avant l'appel à l'initialisation de la classe de base.
    LoadStateFromIniFile();

    CDialog::OnInitDialog();

    // Initialise les barres de niveau des risques.
    m_OrangeSeverityCtrl.SetRange(1, 20, TRUE);
    m_RedSeverityCtrl.SetRange(1, 20, TRUE);

    // Initialise l'affichage des indicateurs des niveaux.
    UpdateOrangeLevel();
    UpdateRedLevel();

    m_OrangeActionCtrl.EnableWindow(m_OrangeActionChecked);
    m_OrangeNoActionCtrl.EnableWindow(m_OrangeNoActionChecked);

    UpdateOKButton();

    m_OrangeUEFrsLabelCtrl.SetWindowText(m_CurrencySymbol);
    m_OrangePOAFrsLabelCtrl.SetWindowText(m_CurrencySymbol);
    m_RedUEFrsLabelCtrl.SetWindowText(m_CurrencySymbol);
    m_RedPOAFrsLabelCtrl.SetWindowText(m_CurrencySymbol);

    return TRUE;
}

// Cette fonction est appelée lorsque l'utilisateur a changé le niveau du risque orange.
void ZVRiskCalculateParametersDlg::OnNMReleasedcaptureOrangeSeverity(NMHDR *pNMHDR, LRESULT *pResult)
{
    if (m_OrangeSeverityCtrl.GetPos() > 19)
    {
        m_OrangeSeverityCtrl.SetPos(19);
    }

    if ((m_OrangeSeverityCtrl.GetPos() + 1) > m_RedSeverityCtrl.GetPos())
    {
        m_RedSeverityCtrl.SetPos(m_OrangeSeverityCtrl.GetPos() + 1);
    }

    UpdateOrangeLevel();
    UpdateRedLevel();

    *pResult = 0;
}

// Cette fonction est appelée lorsque l'utilisateur a changé le niveau du risque rouge.
void ZVRiskCalculateParametersDlg::OnNMReleasedcaptureRedSeverity(NMHDR *pNMHDR, LRESULT *pResult)
{
    if (m_RedSeverityCtrl.GetPos() < 2)
    {
        m_RedSeverityCtrl.SetPos(2);
    }

    if ((m_RedSeverityCtrl.GetPos() - 1) < m_OrangeSeverityCtrl.GetPos())
    {
        m_OrangeSeverityCtrl.SetPos(m_RedSeverityCtrl.GetPos() - 1);
    }

    UpdateOrangeLevel();
    UpdateRedLevel();

    *pResult = 0;
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Action en cours" du groupe orange.
void ZVRiskCalculateParametersDlg::OnBnClickedOrangeAction()
{
    UpdateOKButton();
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Pas d'action en cours" du groupe orange.
void ZVRiskCalculateParametersDlg::OnBnClickedOrangeNoAction()
{
    UpdateOKButton();
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Action en cours" du groupe rouge.
void ZVRiskCalculateParametersDlg::OnBnClickedRedAction()
{
    if (m_RedActionCtrl.GetCheck() == TRUE)
    {
        m_OrangeActionCtrl.SetCheck(TRUE);
        m_OrangeActionCtrl.EnableWindow(FALSE);

        m_OrangeActionChecked = FALSE;
    }
    else
    {
        m_OrangeActionCtrl.EnableWindow(TRUE);

        m_OrangeActionChecked = TRUE;
    }

    UpdateOKButton();
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Pas d'action en cours" du groupe rouge.
void ZVRiskCalculateParametersDlg::OnBnClickedRedNoAction()
{
    if (m_RedNoActionCtrl.GetCheck() == TRUE)
    {
        m_OrangeNoActionCtrl.SetCheck(TRUE);
        m_OrangeNoActionCtrl.EnableWindow(FALSE);

        m_OrangeNoActionChecked = FALSE;
    }
    else
    {
        m_OrangeNoActionCtrl.EnableWindow(TRUE);

        m_OrangeNoActionChecked = TRUE;
    }

    UpdateOKButton();
}

// Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Ok".
void ZVRiskCalculateParametersDlg::OnBnClickedOk()
{
    OnOK();

    SaveStateToIniFile();
}
