/****************************************************************************
 * ==> PSS_RiskOptionsDlg --------------------------------------------------*
 ****************************************************************************
 * Description : Provides a risk options dialog box                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_RiskOptionsDlg.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zMediator\PSS_Application.h"
#include "PSS_RiskModifyDlg.h"
#include "PSS_RiskModifyStaticDlg.h"
#include "PSS_RiskTypeContainer.h"
#include "PSS_RiskImpactContainer.h"
#include "PSS_RiskProbabilityContainer.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_RiskOptionsDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_RiskOptionsDlg)
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
//---------------------------------------------------------------------------
// PSS_RiskOptionsDlg
//---------------------------------------------------------------------------
PSS_RiskOptionsDlg::PSS_RiskOptionsDlg(const CString& riskName,
                                       const CString& riskDesc,
                                       const CString& riskType,
                                       int            riskImpact,
                                       int            riskProbability,
                                       float          riskUE,
                                       float          riskPOA,
                                       bool           riskAction,
                                       const CString& currencySymbol,
                                       CWnd*          pParent) :
    CDialog(PSS_RiskOptionsDlg::IDD, pParent),
    m_RiskName(riskName),
    m_RiskDesc(riskDesc),
    m_RiskType(riskType),
    m_CurrencySymbol(currencySymbol),
    m_RiskUE(riskUE),
    m_RiskPOA(riskPOA),
    m_RiskImpact(riskImpact),
    m_RiskProbability(riskProbability),
    m_RiskAction(riskAction)
{}
//---------------------------------------------------------------------------
PSS_RiskOptionsDlg::~PSS_RiskOptionsDlg()
{}
//---------------------------------------------------------------------------
CString PSS_RiskOptionsDlg::GetRiskTitle() const
{
    return m_RiskName;
}
//---------------------------------------------------------------------------
CString PSS_RiskOptionsDlg::GetRiskDescription() const
{
    return m_RiskDesc;
}
//---------------------------------------------------------------------------
CString PSS_RiskOptionsDlg::GetRiskType() const
{
    return m_RiskType;
}
//---------------------------------------------------------------------------
int PSS_RiskOptionsDlg::GetRiskImpact() const
{
    return m_RiskImpact;
}
//---------------------------------------------------------------------------
int PSS_RiskOptionsDlg::GetRiskProbability() const
{
    return m_RiskProbability;
}
//---------------------------------------------------------------------------
int PSS_RiskOptionsDlg::GetRiskSeverity() const
{
    return m_RiskImpact * m_RiskProbability;
}
//---------------------------------------------------------------------------
float PSS_RiskOptionsDlg::GetRiskUE() const
{
    return m_RiskUE;
}
//---------------------------------------------------------------------------
float PSS_RiskOptionsDlg::GetRiskPOA() const
{
    return m_RiskPOA;
}
//---------------------------------------------------------------------------
bool PSS_RiskOptionsDlg::GetRiskAction() const
{
    return m_RiskAction;
}
//---------------------------------------------------------------------------
void PSS_RiskOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_RiskOptionsDlg)
    DDX_Text    (pDX, IDC_RISK_TITLE_EDIT,       m_RiskName);
    DDX_Text    (pDX, IDC_RISK_DESCRIPTION_EDIT, m_RiskDesc);
    DDX_Control (pDX, IDC_RISK_IMPACT,           m_RiskImpactCtrl);
    DDX_Control (pDX, IDC_RISK_PROBABILITY,      m_RiskProbabilityCtrl);
    DDX_Control (pDX, IDC_RISK_SEVERITY,         m_RiskSeverityCtrl);
    DDX_Control (pDX, IDC_RISK_TYPE,             m_RiskTypeCtrl);
    DDX_Control (pDX, IDC_UE_FRS_LABEL,          m_UEFrsLabelCtrl);
    DDX_Control (pDX, IDC_POA_FRS_LABEL,         m_POAFrsLabelCtrl);
    DDX_Text    (pDX, IDC_UE,                    m_RiskUE);
    DDX_Text    (pDX, IDC_POA,                   m_RiskPOA);
    DDX_Check   (pDX, IDC_ACTION,                m_RiskAction);
    DDX_CBString(pDX, IDC_RISK_TYPE,             m_RiskType);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_RiskOptionsDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    LoadTypeList();
    LoadImpactList();
    LoadProbabilityList();

    m_RiskImpactCtrl.SetCurSel(m_RiskImpact);
    m_RiskProbabilityCtrl.SetCurSel(m_RiskProbability);

    UpdateSeverity();

    m_UEFrsLabelCtrl.SetWindowText(m_CurrencySymbol);
    m_POAFrsLabelCtrl.SetWindowText(m_CurrencySymbol);

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_RiskOptionsDlg::OnCbnSelchangeRiskImpact()
{
    m_RiskImpact = GetImpactIndex();
    UpdateSeverity();
}
//---------------------------------------------------------------------------
void PSS_RiskOptionsDlg::OnCbnSelchangeRiskProbability()
{
    m_RiskProbability = GetProbabilityIndex();
    UpdateSeverity();
}
//---------------------------------------------------------------------------
void PSS_RiskOptionsDlg::OnBnClickedModifyRiskType()
{
    PSS_Application* pInstance = PSS_Application::Instance();

    if (!pInstance)
        return;

    PSS_MainForm* pMainForm = pInstance->GetMainForm();

    if (!pMainForm)
        return;

    PSS_RiskTypeContainer* pContainer = pMainForm->GetRiskTypeContainer();

    if (!pContainer)
        return;

    PSS_RiskModifyDlg modifyTypeDlg(pContainer->GetFileName(), g_RiskTypeExtension);

    if (modifyTypeDlg.DoModal())
        ReloadTypeFile(modifyTypeDlg.GetFileName());
}
//---------------------------------------------------------------------------
void PSS_RiskOptionsDlg::OnBnClickedOpenRiskType()
{
    PSS_Application* pInstance = PSS_Application::Instance();
    
    if (!pInstance)
        return;
    
    PSS_MainForm* pMainForm = pInstance->GetMainForm();
    
    if (!pMainForm)
        return;

    CString desc;
    desc.LoadString(IDS_RISK_TYPE_FILE_DESCRIPTION);

    CString fileName;

    SelectFileToOpen(pMainForm->GetApplicationDir() + g_RiskDirectory,
                     desc,
                     g_RiskTypeExtension,
                     fileName);

    if (!fileName.IsEmpty())
        ReloadTypeFile(fileName);
}
//---------------------------------------------------------------------------
void PSS_RiskOptionsDlg::OnBnClickedModifyRiskImpact()
{
    PSS_Application* pInstance = PSS_Application::Instance();

    if (!pInstance)
        return;

    PSS_MainForm* pMainForm = pInstance->GetMainForm();

    if (!pMainForm)
        return;

    PSS_RiskImpactContainer* pContainer = pMainForm->GetRiskImpactContainer();

    if (!pContainer)
        return;

    PSS_RiskModifyStaticDlg riskModifyStatic(pContainer->GetFileName(), g_RiskImpactExtension, 5);

    if (riskModifyStatic.DoModal() == IDOK)
        ReloadImpactFile(riskModifyStatic.GetFileName());
}
//---------------------------------------------------------------------------
void PSS_RiskOptionsDlg::OnBnClickedModifyRiskProbability()
{
    PSS_Application* pInstance = PSS_Application::Instance();

    if (!pInstance)
        return;

    PSS_MainForm* pMainForm = pInstance->GetMainForm();

    if (!pMainForm)
        return;

    PSS_RiskProbabilityContainer* pContainer = pMainForm->GetRiskProbabilityContainer();

    if (!pContainer)
        return;

    PSS_RiskModifyStaticDlg riskModifyStatic(pContainer->GetFileName(), g_RiskProbabilityExtension, 6);

    if (riskModifyStatic.DoModal() == IDOK)
        ReloadProbabilityFile(riskModifyStatic.GetFileName());
}
//---------------------------------------------------------------------------
void PSS_RiskOptionsDlg::OnBnClickedOpenRiskImpact()
{
    PSS_Application* pInstance = PSS_Application::Instance();

    if (!pInstance)
        return;

    PSS_MainForm* pMainForm = pInstance->GetMainForm();

    if (!pMainForm)
        return;

    CString desc;
    desc.LoadString(IDS_RISK_IMPACT_FILE_DESCRIPTION);

    CString fileName;

    SelectFileToOpen(pMainForm->GetApplicationDir() + g_RiskDirectory,
                     desc,
                     g_RiskImpactExtension,
                     fileName);

    if (!fileName.IsEmpty())
        ReloadImpactFile(fileName);
}
//---------------------------------------------------------------------------
void PSS_RiskOptionsDlg::OnBnClickedOpenRiskProbability()
{
    PSS_Application* pInstance = PSS_Application::Instance();

    if (!pInstance)
        return;

    PSS_MainForm* pMainForm = pInstance->GetMainForm();

    if (!pMainForm)
        return;

    CString desc;
    desc.LoadString(IDS_RISK_PROBABILITY_FILE_DESCRIPTION);

    CString fileName;

    SelectFileToOpen(pMainForm->GetApplicationDir() + g_RiskDirectory,
                     desc,
                     g_RiskProbabilityExtension,
                     fileName);

    if (!fileName.IsEmpty())
        ReloadProbabilityFile(fileName);
}
//---------------------------------------------------------------------------
void PSS_RiskOptionsDlg::OnOK()
{
    CDialog::OnOK();
}
//---------------------------------------------------------------------------
int PSS_RiskOptionsDlg::GetImpactIndex() const
{
    return m_RiskImpactCtrl.GetCurSel();
}
//---------------------------------------------------------------------------
int PSS_RiskOptionsDlg::GetProbabilityIndex() const
{
    return m_RiskProbabilityCtrl.GetCurSel();
}
//---------------------------------------------------------------------------
void PSS_RiskOptionsDlg::LoadTypeList()
{
    PSS_Application* pInstance = PSS_Application::Instance();

    if (!pInstance)
        return;

    PSS_MainForm* pMainForm = pInstance->GetMainForm();

    if (!pMainForm)
        return;

    PSS_RiskTypeContainer* pContainer = pMainForm->GetRiskTypeContainer();

    if (!pContainer)
        return;

    while (m_RiskTypeCtrl.GetCount() > 0)
        m_RiskTypeCtrl.DeleteString(0);

    const int elementCount = pContainer->GetElementCount();

    for (int i = 0; i < elementCount; ++i)
        m_RiskTypeCtrl.AddString(pContainer->GetElementAt(i));
}
//---------------------------------------------------------------------------
void PSS_RiskOptionsDlg::LoadImpactList()
{
    PSS_Application* pInstance = PSS_Application::Instance();

    if (!pInstance)
        return;

    PSS_MainForm* pMainForm = pInstance->GetMainForm();

    if (!pMainForm)
        return;

    PSS_RiskImpactContainer* pContainer = pMainForm->GetRiskImpactContainer();

    if (!pContainer)
        return;

    while (m_RiskImpactCtrl.GetCount() > 0)
        m_RiskImpactCtrl.DeleteString(0);

    const int elementCount = pContainer->GetElementCount();

    for (int i = 0; i < elementCount; ++i)
        m_RiskImpactCtrl.AddString(pContainer->GetElementAt(i));
}
//---------------------------------------------------------------------------
void PSS_RiskOptionsDlg::LoadProbabilityList()
{
    PSS_Application* pInstance = PSS_Application::Instance();

    if (!pInstance)
        return;

    PSS_MainForm* pMainForm = pInstance->GetMainForm();

    if (!pMainForm)
        return;

    PSS_RiskProbabilityContainer* pContainer = pMainForm->GetRiskProbabilityContainer();

    if (!pContainer)
        return;

    while (m_RiskProbabilityCtrl.GetCount() > 0)
        m_RiskProbabilityCtrl.DeleteString(0);

    const int elementCount = pContainer->GetElementCount();

    for (int i = 0; i < elementCount; ++i)
        m_RiskProbabilityCtrl.AddString(pContainer->GetElementAt(i));
}
//---------------------------------------------------------------------------
void PSS_RiskOptionsDlg::UpdateSeverity()
{
    CString severityResult;
    severityResult.Format(_T("%d"), (GetImpactIndex()) * (GetProbabilityIndex()));
    m_RiskSeverityCtrl.SetWindowText(severityResult);
}
//---------------------------------------------------------------------------
void PSS_RiskOptionsDlg::SelectFileToOpen(const CString& dir, const CString& caption, const CString& extension, CString& fileName)
{
    CFileDialog dlgFile(TRUE);

    CString title;
    VERIFY(title.LoadString(IDS_RISK_OPENFILE));

    // configure the open file dialog
    dlgFile.m_ofn.lpstrTitle  = title;
    dlgFile.m_ofn.hwndOwner   = AfxGetMainWnd()->GetSafeHwnd();
    dlgFile.m_ofn.Flags      |= OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

    CString filter;

    // create ini file extension filter (*.ini)
    filter += caption;
    filter += (char)'\0';
    filter += _T("*") + extension;
    filter += (char)'\0';

    ++dlgFile.m_ofn.nMaxCustFilter;

    // create all files extension filter (*.*)
    CString allFilter;
    VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));

    filter += allFilter;
    filter += '\0';
    filter += _T("*.*");
    filter += '\0';

    ++dlgFile.m_ofn.nMaxCustFilter;

    CString fn;

    // add file data
    dlgFile.m_ofn.nMaxFile        = _MAX_PATH;
    dlgFile.m_ofn.lpstrFile       = fn.GetBuffer(_MAX_PATH);
    dlgFile.m_ofn.lpstrFilter     = filter;
    dlgFile.m_ofn.lpstrInitialDir = dir;

    // show the open file dialog
    if (dlgFile.DoModal() == IDOK)
    {
        fileName = fn.GetBuffer();
        return;
    }

    fileName = _T("");
}
//---------------------------------------------------------------------------
BOOL PSS_RiskOptionsDlg::ReloadTypeFile(const CString& fileName)
{
    PSS_Application* pInstance = PSS_Application::Instance();

    if (!pInstance)
        return FALSE;

    PSS_MainForm* pMainForm = pInstance->GetMainForm();

    if (!pMainForm)
        return FALSE;

    PSS_RiskTypeContainer* pContainer = pMainForm->GetRiskTypeContainer();

    if (!pContainer)
        return FALSE;

    pContainer->RemoveAllElements();

    if (pContainer->LoadFile(fileName))
    {
        LoadTypeList();

        CString noRiskType = _T("");
        noRiskType.LoadString(IDS_NO_RISK_TYPE);
        m_RiskTypeCtrl.SetWindowText(noRiskType);

        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskOptionsDlg::ReloadImpactFile(const CString& fileName)
{
    PSS_Application* pInstance = PSS_Application::Instance();

    if (!pInstance)
        return FALSE;

    PSS_MainForm* pMainForm = pInstance->GetMainForm();

    if (!pMainForm)
        return FALSE;

    PSS_RiskImpactContainer* pContainer = pMainForm->GetRiskImpactContainer();

    if (!pContainer)
        return FALSE;

    pContainer->RemoveAllElements();

    if (pContainer->LoadFile(fileName))
    {
        LoadImpactList();
        m_RiskImpactCtrl.SetCurSel(m_RiskImpact);
        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_RiskOptionsDlg::ReloadProbabilityFile(const CString& fileName)
{
    PSS_Application* pInstance = PSS_Application::Instance();

    if (!pInstance)
        return FALSE;

    PSS_MainForm* pMainForm = pInstance->GetMainForm();

    if (!pMainForm)
        return FALSE;

    PSS_RiskProbabilityContainer* pContainer = pMainForm->GetRiskProbabilityContainer();

    if (!pContainer)
        return FALSE;

    pContainer->RemoveAllElements();

    if (pContainer->LoadFile(fileName))
    {
        LoadProbabilityList();
        m_RiskProbabilityCtrl.SetCurSel(m_RiskProbability);
        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
