/****************************************************************************
 * ==> PSS_RiskCalculateParametersDlg --------------------------------------*
 ****************************************************************************
 * Description : Provides a calculate risk parameters dialog box            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RiskCalculateParametersDlg.h"

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

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const CString g_RulesCalculationSectionName           = _T("RulesCalculation");
const CString g_RulesCalculationOrangeSeverity        = _T("OrangeSeverity");
const CString g_RulesCalculationRedSeverity           = _T("RedSeverity");
const CString g_RulesCalculationOrangeUE              = _T("OrangeUE");
const CString g_RulesCalculationOrangePOA             = _T("OrangePOA");
const CString g_RulesCalculationRedUE                 = _T("RedUE");
const CString g_RulesCalculationRedPOA                = _T("RedPOA");
const CString g_RulesCalculationOrangeAction          = _T("OrangeAction");
const CString g_RulesCalculationOrangeNoAction        = _T("OrangeNoAction");
const CString g_RulesCalculationOrangeActionChecked   = _T("OrangeActionChecked");
const CString g_RulesCalculationOrangeNoActionChecked = _T("OrangeNoActionChecked");
const CString g_RulesCalculationRedAction             = _T("RedAction");
const CString g_RulesCalculationRedNoAction           = _T("RedNoAction");
const CString g_RulesCalculationDefaultColors         = _T("DefaultColors");
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_RiskCalculateParametersDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_RiskCalculateParametersDlg)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_ORANGE_SEVERITY, OnNMReleasedcaptureOrangeSeverity)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_RED_SEVERITY, OnNMReleasedcaptureRedSeverity)
    ON_BN_CLICKED(IDC_ORANGE_ACTION, OnBnClickedOrangeAction)
    ON_BN_CLICKED(IDC_ORANGE_NO_ACTION, OnBnClickedOrangeNoAction)
    ON_BN_CLICKED(IDC_RED_ACTION, OnBnClickedRedAction)
    ON_BN_CLICKED(IDC_RED_NO_ACTION, OnBnClickedRedNoAction)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_RiskCalculateParametersDlg
//---------------------------------------------------------------------------
PSS_RiskCalculateParametersDlg::PSS_RiskCalculateParametersDlg(const CString& iniFileName,
                                                               const CString& currencySymbol,
                                                               CWnd*          pParent) :
    CDialog(PSS_RiskCalculateParametersDlg::IDD, pParent),
    m_IniFileName(iniFileName),
    m_CurrencySymbol(currencySymbol),
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
{}
//---------------------------------------------------------------------------
int PSS_RiskCalculateParametersDlg::GetOrangeSeverityLevel()
{
    return m_OrangeSeverity;
}
//---------------------------------------------------------------------------
int PSS_RiskCalculateParametersDlg::GetRedSeverityLevel()
{
    return m_RedSeverity;
}
//---------------------------------------------------------------------------
float PSS_RiskCalculateParametersDlg::GetOrangeUE()
{
    return m_OrangeUE;
}
//---------------------------------------------------------------------------
float PSS_RiskCalculateParametersDlg::GetRedUE()
{
    return m_RedUE;
}
//---------------------------------------------------------------------------
float PSS_RiskCalculateParametersDlg::GetOrangePOA()
{
    return m_OrangePOA;
}
//---------------------------------------------------------------------------
float PSS_RiskCalculateParametersDlg::GetRedPOA()
{
    return m_RedPOA;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskCalculateParametersDlg::IsOrangeActionEnabled()
{
    return m_OrangeAction;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskCalculateParametersDlg::IsOrangeNoActionEnabled()
{
    return m_OrangeNoAction;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskCalculateParametersDlg::IsRedActionEnabled()
{
    return m_RedAction;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskCalculateParametersDlg::IsRedNoActionEnabled()
{
    return m_RedNoAction;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskCalculateParametersDlg::IsDefaultColorsEnabled()
{
    return m_DefaultColors;
}
//---------------------------------------------------------------------------
void PSS_RiskCalculateParametersDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_RiskCalculateParametersDlg)
    DDX_Control(pDX, IDC_ORANGE_SEVERITY,       m_OrangeSeverityCtrl);
    DDX_Control(pDX, IDC_RED_SEVERITY,          m_RedSeverityCtrl);
    DDX_Control(pDX, IDC_ORANGE_SEVERITY_LEVEL, m_OrangeLevelCtrl);
    DDX_Control(pDX, IDC_RED_SEVERITY_LEVEL,    m_RedLevelCtrl);
    DDX_Control(pDX, IDC_ORANGE_ACTION,         m_OrangeActionCtrl);
    DDX_Control(pDX, IDC_RED_ACTION,            m_RedActionCtrl);
    DDX_Control(pDX, IDC_ORANGE_NO_ACTION,      m_OrangeNoActionCtrl);
    DDX_Control(pDX, IDC_RED_NO_ACTION,         m_RedNoActionCtrl);
    DDX_Control(pDX, IDOK,                      m_OKCtrl);
    DDX_Control(pDX, IDC_ORANGE_UE_FRS_LABEL,   m_OrangeUEFrsLabelCtrl);
    DDX_Control(pDX, IDC_ORANGE_POA_FRS_LABEL,  m_OrangePOAFrsLabelCtrl);
    DDX_Control(pDX, IDC_RED_UE_FRS_LABEL,      m_RedUEFrsLabelCtrl);
    DDX_Control(pDX, IDC_RED_POA_FRS_LABEL,     m_RedPOAFrsLabelCtrl);
    DDX_Slider (pDX, IDC_ORANGE_SEVERITY,       m_OrangeSeverity);
    DDX_Slider (pDX, IDC_RED_SEVERITY,          m_RedSeverity);
    DDX_Check  (pDX, IDC_ORANGE_ACTION,         m_OrangeAction);
    DDX_Check  (pDX, IDC_ORANGE_NO_ACTION,      m_OrangeNoAction);
    DDX_Check  (pDX, IDC_RED_ACTION,            m_RedAction);
    DDX_Check  (pDX, IDC_RED_NO_ACTION,         m_RedNoAction);
    DDX_Check  (pDX, IDC_DEFAULT_COLORS,        m_DefaultColors);
    DDX_Text   (pDX, IDC_ORANGE_UE,             m_OrangeUE);
    DDX_Text   (pDX, IDC_ORANGE_POA,            m_OrangePOA);
    DDX_Text   (pDX, IDC_RED_UE,                m_RedUE);
    DDX_Text   (pDX, IDC_RED_POA,               m_RedPOA);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_RiskCalculateParametersDlg::OnInitDialog()
{
    // this call should be placed at the start, before the initialization
    LoadStateFromIniFile();

    CDialog::OnInitDialog();

    // initialize the risk slidebar
    m_OrangeSeverityCtrl.SetRange(1, 20, TRUE);
    m_RedSeverityCtrl.SetRange(1, 20, TRUE);

    // initialize the level indicator
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
//---------------------------------------------------------------------------
void PSS_RiskCalculateParametersDlg::OnNMReleasedcaptureOrangeSeverity(NMHDR *pNMHDR, LRESULT *pResult)
{
    if (m_OrangeSeverityCtrl.GetPos() > 19)
        m_OrangeSeverityCtrl.SetPos(19);

    if ((m_OrangeSeverityCtrl.GetPos() + 1) > m_RedSeverityCtrl.GetPos())
        m_RedSeverityCtrl.SetPos(m_OrangeSeverityCtrl.GetPos() + 1);

    UpdateOrangeLevel();
    UpdateRedLevel();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_RiskCalculateParametersDlg::OnNMReleasedcaptureRedSeverity(NMHDR *pNMHDR, LRESULT *pResult)
{
    if (m_RedSeverityCtrl.GetPos() < 2)
        m_RedSeverityCtrl.SetPos(2);

    if ((m_RedSeverityCtrl.GetPos() - 1) < m_OrangeSeverityCtrl.GetPos())
        m_OrangeSeverityCtrl.SetPos(m_RedSeverityCtrl.GetPos() - 1);

    UpdateOrangeLevel();
    UpdateRedLevel();

    *pResult = 0;
}
//---------------------------------------------------------------------------
void PSS_RiskCalculateParametersDlg::OnBnClickedOrangeAction()
{
    UpdateOKButton();
}
//---------------------------------------------------------------------------
void PSS_RiskCalculateParametersDlg::OnBnClickedOrangeNoAction()
{
    UpdateOKButton();
}
//---------------------------------------------------------------------------
void PSS_RiskCalculateParametersDlg::OnBnClickedRedAction()
{
    if (m_RedActionCtrl.GetCheck())
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
//---------------------------------------------------------------------------
void PSS_RiskCalculateParametersDlg::OnBnClickedRedNoAction()
{
    if (m_RedNoActionCtrl.GetCheck())
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
//---------------------------------------------------------------------------
void PSS_RiskCalculateParametersDlg::OnBnClickedOk()
{
    OnOK();
    SaveStateToIniFile();
}
//---------------------------------------------------------------------------
void PSS_RiskCalculateParametersDlg::UpdateOrangeLevel()
{
    CString level = _T("");

    level.Format(_T("%d"), m_OrangeSeverityCtrl.GetPos());
    m_OrangeLevelCtrl.SetWindowText(level);
}
//---------------------------------------------------------------------------
void PSS_RiskCalculateParametersDlg::UpdateRedLevel()
{
    CString level = _T("");

    level.Format(_T("%d"), m_RedSeverityCtrl.GetPos());
    m_RedLevelCtrl.SetWindowText(level);
}
//---------------------------------------------------------------------------
void PSS_RiskCalculateParametersDlg::UpdateOKButton()
{
    if (!m_OrangeActionCtrl.GetCheck()   &&
        !m_OrangeNoActionCtrl.GetCheck() &&
        !m_RedActionCtrl.GetCheck()      &&
        !m_RedNoActionCtrl.GetCheck())
        m_OKCtrl.EnableWindow(FALSE);
    else
        m_OKCtrl.EnableWindow(TRUE);
}
//---------------------------------------------------------------------------
bool PSS_RiskCalculateParametersDlg::LoadStateFromIniFile()
{
    PSS_SystemOption SystemOption(m_IniFileName, g_RulesCalculationSectionName);

    // read the options
    m_OrangeSeverity        = SystemOption.ReadOption(g_RulesCalculationOrangeSeverity,        1);
    m_RedSeverity           = SystemOption.ReadOption(g_RulesCalculationRedSeverity,           2);
    m_OrangeUE              = SystemOption.ReadOption(g_RulesCalculationOrangeUE,              0.0f);
    m_OrangePOA             = SystemOption.ReadOption(g_RulesCalculationOrangePOA,             0.0f);
    m_RedUE                 = SystemOption.ReadOption(g_RulesCalculationRedUE,                 0.0f);
    m_RedPOA                = SystemOption.ReadOption(g_RulesCalculationRedPOA,                0.0f);
    m_OrangeAction          = SystemOption.ReadOption(g_RulesCalculationOrangeAction,          FALSE);
    m_OrangeNoAction        = SystemOption.ReadOption(g_RulesCalculationOrangeNoAction,        FALSE);
    m_OrangeActionChecked   = SystemOption.ReadOption(g_RulesCalculationOrangeActionChecked,   FALSE);
    m_OrangeNoActionChecked = SystemOption.ReadOption(g_RulesCalculationOrangeNoActionChecked, FALSE);
    m_RedAction             = SystemOption.ReadOption(g_RulesCalculationRedAction,             FALSE);
    m_RedNoAction           = SystemOption.ReadOption(g_RulesCalculationRedNoAction,           FALSE);
    m_DefaultColors         = SystemOption.ReadOption(g_RulesCalculationDefaultColors,         FALSE);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_RiskCalculateParametersDlg::SaveStateToIniFile()
{
    PSS_SystemOption SystemOption(m_IniFileName, g_RulesCalculationSectionName);

    // save the options
    SystemOption.WriteOption(g_RulesCalculationOrangeSeverity,        m_OrangeSeverity);
    SystemOption.WriteOption(g_RulesCalculationRedSeverity,           m_RedSeverity);
    SystemOption.WriteOption(g_RulesCalculationOrangeUE,              m_OrangeUE);
    SystemOption.WriteOption(g_RulesCalculationOrangePOA,             m_OrangePOA);
    SystemOption.WriteOption(g_RulesCalculationRedUE,                 m_RedUE);
    SystemOption.WriteOption(g_RulesCalculationRedPOA,                m_RedPOA);
    SystemOption.WriteOption(g_RulesCalculationOrangeAction,          m_OrangeAction);
    SystemOption.WriteOption(g_RulesCalculationOrangeNoAction,        m_OrangeNoAction);
    SystemOption.WriteOption(g_RulesCalculationOrangeActionChecked,   m_OrangeActionChecked);
    SystemOption.WriteOption(g_RulesCalculationOrangeNoActionChecked, m_OrangeNoActionChecked);
    SystemOption.WriteOption(g_RulesCalculationRedAction,             m_RedAction);
    SystemOption.WriteOption(g_RulesCalculationRedNoAction,           m_RedNoAction);
    SystemOption.WriteOption(g_RulesCalculationDefaultColors,         m_DefaultColors);

    return true;
}
//---------------------------------------------------------------------------
