/****************************************************************************
 * ==> PSS_ModelWorkflowOptionsWizard --------------------------------------*
 ****************************************************************************
 * Description : Provides a model workflow options wizard and its related   *
 *               dialog boxes                                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ModelWorkflowOptionsWizard.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_ModelWorkflowOptionsWizard::IData
//---------------------------------------------------------------------------
PSS_ModelWorkflowOptionsWizard::IData::IData() :
    m_Language(E_LN_Unknown),
    m_Notation(E_MN_Unknown),
    m_HourPerDay(0),
    m_DayPerWeek(0),
    m_DayPerMonth(0),
    m_DayPerYear(0),
    m_Modify(FALSE),
    m_CheckConsistency(FALSE),
    m_IntegrateCostSimulation(FALSE),
    m_UseModelAsWorkflow(FALSE),
    m_BrowseInSameModel(FALSE)
{}
//---------------------------------------------------------------------------
// PSS_ModelWorkflowOptionsWizard
//---------------------------------------------------------------------------
PSS_ModelWorkflowOptionsWizard::PSS_ModelWorkflowOptionsWizard(BOOL modify, PSS_ProcessGraphModelDoc* pDoc, CWnd* pParent) :
    m_pDoc(pDoc),
    m_Modify(modify)
{}
//---------------------------------------------------------------------------
PSS_ModelWorkflowOptionsWizard::~PSS_ModelWorkflowOptionsWizard()
{}
//---------------------------------------------------------------------------
int PSS_ModelWorkflowOptionsWizard::DoModal()
{
    if (!m_pDoc)
        return IDABORT;

    // initialize the dialog data
    m_Data.m_Modify = m_Modify;

    // if in modification get values, otherwise set default values
    if (m_Modify)
    {
        m_Data.m_UseModelAsWorkflow = m_pDoc->GetUseWorkflow();
        m_Data.m_CheckConsistency   = m_pDoc->GetCheckConsistency();

        switch (m_pDoc->GetNotation())
        {
            case E_MN_Beryl: m_Data.m_Notation = 0; break;
            case E_MN_ABC:   m_Data.m_Notation = 1; break;
            case E_MN_UML:   m_Data.m_Notation = 2; break;
            default:         m_Data.m_Notation = 3; break;
        }

        m_Data.m_IntegrateCostSimulation = m_pDoc->GetIntegrateCostSimulation();
        m_Data.m_BrowseInSameModel       = m_pDoc->GetBrowseInSameWindow();
        m_Data.m_HourPerDay              = m_pDoc->GetHourPerDay();
        m_Data.m_DayPerWeek              = m_pDoc->GetDayPerWeek();
        m_Data.m_DayPerMonth             = m_pDoc->GetDayPerMonth();
        m_Data.m_DayPerYear              = m_pDoc->GetDayPerYear();
        m_Data.m_CurrencySymbol          = m_pDoc->GetCurrencySymbol();
        m_Data.m_Language                = m_pDoc->GetLanguage();
    }
    else
    {
        m_Data.m_UseModelAsWorkflow      = TRUE;
        m_Data.m_CheckConsistency        = TRUE;
        m_Data.m_Notation                = 0;
        m_Data.m_IntegrateCostSimulation = TRUE;
        m_Data.m_BrowseInSameModel       = TRUE;
        m_Data.m_HourPerDay              = 8;
        m_Data.m_DayPerWeek              = 5;
        m_Data.m_DayPerMonth             = 22;
        m_Data.m_DayPerYear              = 220;
        m_Data.m_CurrencySymbol          = PSS_Global::GetLocaleCurrency();

        // set the French language as default
        m_Data.m_Language = E_LN_French;
    }

    // the notation can't be modified in modification mode
    if (!m_Modify)
    {
        PSS_ModelWorkflowNotationOptionsDlg notation(m_Data);

        if (notation.DoModal() == IDCANCEL)
            return IDCANCEL;
    }

    PSS_ModelWorkflowOptionsDlg options(m_Data);
    int                         result;

    if ((result = options.DoModal()) == IDCANCEL)
        return IDCANCEL;

    if (result == IDNEXT)
    {
        PSS_ModelWorkflowCostsOptionsDlg costs(m_Data);

        if (costs.DoModal() == IDCANCEL)
            return IDCANCEL;
    }

    // save options
    m_pDoc->SetUseWorkflow(m_Data.m_UseModelAsWorkflow);
    m_pDoc->SetCheckConsistency(m_Data.m_CheckConsistency);

    switch (m_Data.m_Notation)
    {
        case 0:  m_pDoc->SetNotation(E_MN_Beryl);   break;
        case 1:  m_pDoc->SetNotation(E_MN_ABC);     break;
        case 2:  m_pDoc->SetNotation(E_MN_UML);     break;
        default: m_pDoc->SetNotation(E_MN_Unknown); break;
    }

    m_pDoc->SetIntegrateCostSimulation(m_Data.m_IntegrateCostSimulation);
    m_pDoc->SetBrowseInSameWindow(m_Data.m_BrowseInSameModel);
    m_pDoc->SetHourPerDay(m_Data.m_HourPerDay);
    m_pDoc->SetDayPerWeek(m_Data.m_DayPerWeek);
    m_pDoc->SetDayPerMonth(m_Data.m_DayPerMonth);
    m_pDoc->SetDayPerYear(m_Data.m_DayPerYear);
    m_pDoc->SetCurrencySymbol(m_Data.m_CurrencySymbol);
    m_pDoc->SetLanguage(m_Data.m_Language);

    return IDOK;
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ModelWorkflowNotationOptionsDlg, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_ModelWorkflowNotationOptionsDlg)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ModelWorkflowNotationOptionsDlg
//---------------------------------------------------------------------------
PSS_ModelWorkflowNotationOptionsDlg::PSS_ModelWorkflowNotationOptionsDlg(PSS_ModelWorkflowOptionsWizard::IData& data,
                                                                         CWnd*                                  pParent) :
    PSS_WizardDialog(PSS_ModelWorkflowNotationOptionsDlg::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZ_MODELNOTATION_S,
                     IDS_WZ_MODELNOTATION_T),
    m_Data(data),
    m_Notation(E_MN_Unknown)
{
    m_Notation = m_Data.m_Notation;
}
//---------------------------------------------------------------------------
PSS_ModelWorkflowNotationOptionsDlg::~PSS_ModelWorkflowNotationOptionsDlg()
{}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowNotationOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ModelWorkflowNotationOptionsDlg)
    DDX_Radio(pDX, IDC_MODEL_NOTATION, m_Notation);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ModelWorkflowNotationOptionsDlg::OnInitDialog()
{
    const BOOL result = PSS_WizardDialog::OnInitDialog();

    if (GetDlgItem(IDOK) && !m_Data.m_Modify)
        GetDlgItem(IDOK)->ShowWindow(SW_HIDE);

    return result;
}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowNotationOptionsDlg::OnNext()
{
    SaveToData();
    EndDialog(IDNEXT);
}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowNotationOptionsDlg::OnOK()
{
    SaveToData();

    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowNotationOptionsDlg::SaveToData()
{
    UpdateData(TRUE);
    m_Data.m_Notation = m_Notation;
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ModelWorkflowOptionsDlg, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_ModelWorkflowOptionsDlg)
    ON_BN_CLICKED(IDC_INTEGRATE_COSTSIMULATION, OnIntegrateCostsimulation)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ModelWorkflowOptionsDlg
//---------------------------------------------------------------------------
PSS_ModelWorkflowOptionsDlg::PSS_ModelWorkflowOptionsDlg(PSS_ModelWorkflowOptionsWizard::IData& data, CWnd* pParent) :
    PSS_WizardDialog(PSS_ModelWorkflowOptionsDlg::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZ_MODELPARAM_S,
                     IDS_WZ_MODELPARAM_T),
    m_Data(data),
    m_CheckConsistency(FALSE),
    m_IntegrateCostSimulation(FALSE),
    m_UseModelAsWorkflow(FALSE),
    m_BrowseInSameModel(FALSE)
{
    m_CheckConsistency        = m_Data.m_CheckConsistency;
    m_IntegrateCostSimulation = m_Data.m_IntegrateCostSimulation;
    m_UseModelAsWorkflow      = m_Data.m_UseModelAsWorkflow;
    m_BrowseInSameModel       = m_Data.m_BrowseInSameModel;
}
//---------------------------------------------------------------------------
PSS_ModelWorkflowOptionsDlg::~PSS_ModelWorkflowOptionsDlg()
{}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ModelWorkflowOptionsDlg)
    DDX_Control(pDX, IDC_MODEL_LANGUAGE,           m_LanguageCombo);
    DDX_Check  (pDX, IDC_CHECKMODEL_CONSISTENCY,   m_CheckConsistency);
    DDX_Check  (pDX, IDC_INTEGRATE_COSTSIMULATION, m_IntegrateCostSimulation);
    DDX_Check  (pDX, IDC_USEMODEL_ASWORKFLOW,      m_UseModelAsWorkflow);
    DDX_Check  (pDX, IDC_BROWSEMODEL_INSAMEWINDOW, m_BrowseInSameModel);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ModelWorkflowOptionsDlg::OnInitDialog()
{
    const BOOL result = PSS_WizardDialog::OnInitDialog();

    switch (m_Data.m_Notation)
    {
        case 0:
            break;

        case 1:
            if (GetDlgItem(IDC_CHECKMODEL_CONSISTENCY))
                GetDlgItem(IDC_CHECKMODEL_CONSISTENCY)->EnableWindow(FALSE);

            if (GetDlgItem(IDC_USEMODEL_ASWORKFLOW))
                GetDlgItem(IDC_USEMODEL_ASWORKFLOW)->EnableWindow(FALSE);

            if (GetDlgItem(IDC_INTEGRATE_COSTSIMULATION))
                GetDlgItem(IDC_INTEGRATE_COSTSIMULATION)->EnableWindow(FALSE);

            break;

        case 2:
            if (GetDlgItem(IDC_CHECKMODEL_CONSISTENCY))
                GetDlgItem(IDC_CHECKMODEL_CONSISTENCY)->EnableWindow(FALSE);

            if (GetDlgItem(IDC_USEMODEL_ASWORKFLOW))
                GetDlgItem(IDC_USEMODEL_ASWORKFLOW)->EnableWindow(FALSE);

            if (GetDlgItem(IDC_INTEGRATE_COSTSIMULATION))
                GetDlgItem(IDC_INTEGRATE_COSTSIMULATION)->EnableWindow(FALSE);

            break;

        default:
            if (GetDlgItem(IDC_CHECKMODEL_CONSISTENCY))
                GetDlgItem(IDC_CHECKMODEL_CONSISTENCY)->EnableWindow(FALSE);

            if (GetDlgItem(IDC_USEMODEL_ASWORKFLOW))
                GetDlgItem(IDC_USEMODEL_ASWORKFLOW)->EnableWindow(FALSE);

            if (GetDlgItem(IDC_INTEGRATE_COSTSIMULATION))
                GetDlgItem(IDC_INTEGRATE_COSTSIMULATION)->EnableWindow(FALSE);

            break;
    }

    // initialize the language combobox
    m_LanguageCombo.Initialize(m_Data.m_Language);

    CheckStates();

    return result;
}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowOptionsDlg::OnIntegrateCostsimulation()
{
    UpdateData();
    CheckStates();
}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowOptionsDlg::OnNext()
{
    SaveToData();
    EndDialog(IDNEXT);
}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowOptionsDlg::OnOK()
{
    SaveToData();
    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowOptionsDlg::SaveToData()
{
    UpdateData(TRUE);

    m_Data.m_CheckConsistency        = m_CheckConsistency;
    m_Data.m_IntegrateCostSimulation = m_IntegrateCostSimulation;
    m_Data.m_UseModelAsWorkflow      = m_UseModelAsWorkflow;
    m_Data.m_BrowseInSameModel       = m_BrowseInSameModel;

    // save the selected language
    m_Data.m_Language = m_LanguageCombo.GetLanguage();
}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowOptionsDlg::CheckStates()
{
    // enable the next button, depending on the cost simulation state
    if (GetDlgItem(IDNEXT) && GetDlgItem(IDOK))
    {
        GetDlgItem(IDNEXT)->EnableWindow(m_IntegrateCostSimulation);

        if (m_IntegrateCostSimulation)
            SetDefID(IDNEXT);
        else
            SetDefID(IDOK);
    }
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ModelWorkflowCostsOptionsDlg, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_ModelWorkflowCostsOptionsDlg)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ModelWorkflowCostsOptionsDlg
//---------------------------------------------------------------------------
PSS_ModelWorkflowCostsOptionsDlg::PSS_ModelWorkflowCostsOptionsDlg(PSS_ModelWorkflowOptionsWizard::IData& data, CWnd* pParent) :
    PSS_WizardDialog(PSS_ModelWorkflowCostsOptionsDlg::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZ_MODELCOSTS_S,
                     IDS_WZ_MODELCOSTS_T),
    m_Data(data)
{
    m_DayPerMonth.Format("%d", m_Data.m_DayPerMonth);
    m_DayPerWeek.Format ("%d", m_Data.m_DayPerWeek);
    m_DayPerYear.Format ("%d", m_Data.m_DayPerYear);
    m_HourPerDay.Format ("%d", m_Data.m_HourPerDay);
}
//---------------------------------------------------------------------------
PSS_ModelWorkflowCostsOptionsDlg::~PSS_ModelWorkflowCostsOptionsDlg()
{}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowCostsOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_ModelWorkflowCostsOptionsDlg)
    DDX_Control(pDX, IDC_CURRENCY_SYMBOL, m_CurrencySymbolCombo);
    DDX_Text   (pDX, IDC_DAY_PERMONTH,    m_DayPerMonth);
    DDX_Text   (pDX, IDC_DAY_PERWEEK,     m_DayPerWeek);
    DDX_Text   (pDX, IDC_DAY_PERYEAR,     m_DayPerYear);
    DDX_Text   (pDX, IDC_HOUR_PERDAY,     m_HourPerDay);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_ModelWorkflowCostsOptionsDlg::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    m_CurrencySymbolCombo.AddString(m_Data.m_CurrencySymbol);

    if (m_CurrencySymbolCombo.FindStringExact(-1, _T("$")) == CB_ERR)
        m_CurrencySymbolCombo.AddString(_T("$"));

    if (m_CurrencySymbolCombo.FindStringExact(-1, _T("£")) == CB_ERR)
        m_CurrencySymbolCombo.AddString(_T("£"));

    if (m_CurrencySymbolCombo.FindStringExact(-1, _T("€")) == CB_ERR)
        m_CurrencySymbolCombo.AddString(_T("€"));

    // select the currency symbol
    if (m_CurrencySymbolCombo.SelectString(-1, m_Data.m_CurrencySymbol) == CB_ERR)
        // on error select the first element
        m_CurrencySymbolCombo.SetCurSel(0);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowCostsOptionsDlg::OnNext()
{
    if (!CheckData())
        return;

    SaveToData();
    EndDialog(IDNEXT);
}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowCostsOptionsDlg::OnOK()
{
    if (!CheckData())
        return;

    SaveToData();
    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
void PSS_ModelWorkflowCostsOptionsDlg::SaveToData()
{
    UpdateData(TRUE);

    m_Data.m_HourPerDay  = std::atoi(m_HourPerDay);
    m_Data.m_DayPerWeek  = std::atoi(m_DayPerWeek);
    m_Data.m_DayPerMonth = std::atoi(m_DayPerMonth);
    m_Data.m_DayPerYear  = std::atoi(m_DayPerYear);

    // initialize text with the previous value
    CString   text  = m_Data.m_CurrencySymbol;
    const int index = m_CurrencySymbolCombo.GetCurSel();

    // if no error, get the text
    if (index != CB_ERR)
        m_CurrencySymbolCombo.GetLBText(index, text);

    m_Data.m_CurrencySymbol = text;
}
//---------------------------------------------------------------------------
bool PSS_ModelWorkflowCostsOptionsDlg::CheckData()
{
    UpdateData(TRUE);

    // check the currency symbol
    CString text;

    // check if the entered text is already in the list
    m_CurrencySymbolCombo.GetWindowText(text);

    if (text.IsEmpty())
    {
        // todo -cFeature -oJean: Warn the user
    }
    else
    if (m_CurrencySymbolCombo.FindStringExact(-1, text) == CB_ERR)
    {
        m_CurrencySymbolCombo.InsertString( 0, text);
        m_CurrencySymbolCombo.SelectString(-1, text);
    }
    else
    {
        const int index = m_CurrencySymbolCombo.GetCurSel();

        // if no error, get the text
        if (index == CB_ERR)
            // todo -cFeature -oJean: Warn the user
            return false;

        m_CurrencySymbolCombo.GetLBText(index, text);

        if (text.IsEmpty())
        {
            // todo -cFeature -oJean: Warn the user
        }
    }

    return true;
}
//---------------------------------------------------------------------------
