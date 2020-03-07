/****************************************************************************
 * ==> PSS_PublishToMessengerWizard ----------------------------------------*
 ****************************************************************************
 * Description : Provides a publish to Messenger wizard                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PublishToMessengerWizard.h"

// processsoft
#include "zBaseLib\PSS_Log.h"
#include "zBaseLib\PSS_SystemOption.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_Global.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#define _ZMODELEXPORT
    #include "zModel\PSS_ProcessGraphModelView.h"
#undef _ZMODELEXPORT
#include "zModel\PSS_InfoModelGraphicGeneration.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"
#include "zSOAP\PSS_SoapData_Settings.h"
#include "zSOAP\PSS_SoapPublisher_MessengerInfo.h"
#include "zSOAP\PSS_SoapException.h"
#include "PSS_PublishMessengerModelInformation.h"
#include "PSS_SoapPublishUserGroup.h"
#include "PSS_SoapPublishLogicalSystem.h"
#include "PSS_SoapPublishPrestations.h"
#include "PSS_SoapPublishMessengerUniverse.h"
#include "PSS_SoapPublishModelDefinition.h"
#include "PSS_SoapPublishModelAttributes.h"
#include "PSS_SOAPPublishModelGenerateFiles.h"
#include "PSS_CheckValidUnit.h"
#include "PSS_CheckMessengerValidUnit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Global constants
//---------------------------------------------------------------------------
const CString g_PublishMessengerSectionName                  = _T("PublishToMessenger");
const CString g_PublishMessengerAddressEntityName            = _T("PublishAddress");
const CString g_PublishMessengerLastAddressEntityName        = _T("LastPublishAddress");
const CString g_PublishMessengerIncludeModelEntityName       = _T("IncludeModel");
const CString g_PublishMessengerIncludeGroupsEntityName      = _T("IncludeGroups");
const CString g_PublishMessengerIncludeSystemsEntityName     = _T("IncludeSystems");
const CString g_PublishMessengerIncludePrestationsEntityName = _T("IncludePrestations");
const CString g_PublishMessengerAliasName                    = _T("Alias");
//---------------------------------------------------------------------------
// PSS_PublishToMessengerWizard
//---------------------------------------------------------------------------
PSS_PublishToMessengerWizard::PSS_PublishToMessengerWizard(PSS_ProcessGraphModelDoc* pModelDoc,
                                                           PSS_Log*                  pLog,
                                                           const CString&            iniFile) :
    m_pModelDoc(pModelDoc),
    m_pLog(pLog),
    m_IniFile(iniFile)
{}
//---------------------------------------------------------------------------
PSS_PublishToMessengerWizard::~PSS_PublishToMessengerWizard()
{}
//---------------------------------------------------------------------------
int PSS_PublishToMessengerWizard::DoModal()
{
    if (!m_pModelDoc)
        return IDCANCEL;

    try
    {
        // can log?
        if (m_pLog)
        {
            m_pLog->ClearLog();
            CString message;
            message.LoadString(IDS_AL_START_MESSENGERCHECK);
            PSS_GenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }

        // perform a unit check before starting the wizard for the messenger publication
        PSS_CheckMessengerValidUnit checkUnit(m_pModelDoc->GetModel());
        checkUnit.SetLog(m_pLog);
        checkUnit.Navigate();

        // perform a second unit check to be sure that all units defined in symbol still exist
        PSS_CheckValidUnit check(m_pModelDoc->GetModel());
        check.SetLog(m_pLog);
        check.Navigate();

        if (checkUnit.GetErrorCounter() > 0 || check.GetErrorCounter() > 0)
        {
            if (m_pLog)
            {
                CString message;
                message.Format(IDS_ZS_STOP2,
                               checkUnit.GetErrorCounter()   + check.GetErrorCounter(),
                               checkUnit.GetWarningCounter() + check.GetWarningCounter());

                PSS_GenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            return IDCANCEL;
        }

        if (m_pLog)
        {
            CString message;

            if (checkUnit.GetWarningCounter() > 0 || check.GetWarningCounter() > 0)
                message.Format(IDS_ZS_STOP2,
                               checkUnit.GetErrorCounter()   + check.GetErrorCounter(),
                               checkUnit.GetWarningCounter() + check.GetWarningCounter());
            else
                message.LoadString(IDS_ZS_STOP);

            PSS_GenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }

        PSS_PublishToMessengerStartWizardDlg startWizard(m_IniFile);

        if (startWizard.DoModal() == IDCANCEL)
            return IDCANCEL;

        PSS_PublishMessengerModelInformation info(m_pModelDoc,
                                                  startWizard.GetMessengerAddress(),
                                                  startWizard.GetMessengerAlias());

        PSS_PublishToMessengerLogonWizardDlg logonWizard(&info);

        if (logonWizard.DoModal() == IDCANCEL)
        {
            if (m_pLog)
            {
                CString message;
                message.LoadString(IDS_AL_CANCEL_SOAPPUBLICATION);
                PSS_GenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            return IDCANCEL;
        }

        if (m_pLog)
        {
            CString message;
            message.LoadString(IDS_AL_AUTHENTICATIONOK_SOAPPUBLICATION);
            PSS_GenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }

        info.m_BeginDate = logonWizard.GetBeginDate();
        info.m_EndDate   = logonWizard.GetEndDate();

        // start the publication
        if (m_pLog)
        {
            CString message;

            message.Format(IDS_AL_START_SOAPPUBLICATION, m_pModelDoc->GetModel()->GetModelName());
            PSS_GenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);

            message.LoadString(IDS_AL_GROUP_MULTIMODELS_CHECK_START);
            e = PSS_GenericSymbolErrorLine(message);
            m_pLog->AddLine(e);
        }

        int                              nbCheck   = 0;
        BOOL                             isCheckOK = FALSE;
        PSS_SoapPublishMessengerUniverse soapPubCheckUniverse(&info, m_pLog);

        do
        {
            if (soapPubCheckUniverse.Publish())
            {
                if (m_pLog)
                {
                    CString message;
                    message.LoadString(IDS_AL_GROUP_MULTIMODELS_CHECK_END);
                    PSS_GenericSymbolErrorLine e(message);
                    m_pLog->AddLine(e);
                }

                isCheckOK = TRUE;
                break;
            }

            ++nbCheck;
        }
        while (nbCheck < 5);

        if (!isCheckOK)
        {
            if (m_pLog)
            {
                CString message;
                message.LoadString(IDS_AL_GROUP_MULTIMODELS_CHECK_ERR);
                PSS_GenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            return IDCANCEL;
        }

        // publish the groups
        if (startWizard.GetIncludeGroups())
        {
            if (m_pLog)
            {
                CString message;
                message.LoadString(IDS_AL_GROUP_SOAPPUBLICATION_START);
                PSS_GenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            PSS_SoapPublishUserGroup soapPublishGroups(&info, m_pLog);

            int retries = 0;

            do
            {
                if (soapPublishGroups.Publish())
                {
                    if (m_pLog)
                    {
                        CString message;
                        message.LoadString(IDS_AL_GROUP_SOAPPUBLICATION);
                        PSS_GenericSymbolErrorLine e(message);
                        m_pLog->AddLine(e);
                    }

                    break;
                }

                ++retries;

                if (m_pLog)
                {
                    CString message;
                    message.LoadString(IDS_AL_GROUP_SOAPPUBLICATION_ERR);
                    PSS_GenericSymbolErrorLine e(message);
                    m_pLog->AddLine(e);
                }
            }
            while (retries < 5);
        }

        // publish the logical systems
        if (startWizard.GetIncludeSystems())
        {
            if (m_pLog)
            {
                CString message;
                message.LoadString(IDS_AL_SYSTEM_SOAPPUBLICATION_START);
                PSS_GenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            PSS_SoapPublishLogicalSystem soapPublishLogicalSystem(&info, m_pLog);

            int retries = 0;

            do
            {
                if (soapPublishLogicalSystem.Publish())
                {
                    if (m_pLog)
                    {
                        CString message;
                        message.LoadString(IDS_AL_SYSTEM_SOAPPUBLICATION);
                        PSS_GenericSymbolErrorLine e(message);
                        m_pLog->AddLine(e);
                    }

                    break;
                }

                ++retries;

                if (m_pLog)
                {
                    CString message;
                    message.LoadString(IDS_AL_SYSTEM_SOAPPUBLICATION_ERR);
                    PSS_GenericSymbolErrorLine e(message);
                    m_pLog->AddLine(e);
                }
            }
            while (retries < 5);
        }

        // publish the prestations
        if (startWizard.GetIncludePrestations())
        {
            if (m_pLog)
            {
                CString message;
                message.LoadString(IDS_AL_PRESTATIONS_SOAPPUBLICATION_START);
                PSS_GenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            PSS_SoapPublishPrestations soapPublishPrestations(&info, m_pLog);

            int retries = 0;

            do
            {
                if (soapPublishPrestations.Publish())
                {
                    if (m_pLog)
                    {
                        CString message;
                        message.LoadString(IDS_AL_PRESTATIONS_SOAPPUBLICATION);
                        PSS_GenericSymbolErrorLine e(message);
                        m_pLog->AddLine(e);
                    }

                    break;
                }

                ++retries;

                if (m_pLog)
                {
                    CString message;
                    message.LoadString(IDS_AL_PRESTATIONS_SOAPPUBLICATION_ERR);
                    PSS_GenericSymbolErrorLine e(message);
                    m_pLog->AddLine(e);
                }
            }
            while (retries < 5);
        }

        // publish the model, with all attributes and HTML publications
        if (startWizard.GetIncludeModel())
        {
            if (m_pLog)
            {
                CString message;
                message.LoadString(IDS_AL_ATTRIBUTES_SOAPPUBLICATION_START);
                PSS_GenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            PSS_SoapPublishModelAttributes soapPublishAttributes(&info,
                                                                 m_pModelDoc->GetModel(),
                                                                 (void*)((const char*)startWizard.GetMessengerAddress()));

            // assign the log
            soapPublishAttributes.SetLog(m_pLog);

            int retries = 0;

            do
            {
                if (soapPublishAttributes.Navigate())
                {
                    if (m_pLog)
                    {
                        CString message;
                        message.LoadString(IDS_AL_ATTRIBUTES_SOAPPUBLICATION);
                        PSS_GenericSymbolErrorLine e(message);
                        m_pLog->AddLine(e);
                    }

                    break;
                }

                ++retries;

                if (m_pLog)
                {
                    CString message;
                    message.LoadString(IDS_AL_ATTRIBUTES_SOAPPUBLICATION_ERR);
                    PSS_GenericSymbolErrorLine e(message);
                    m_pLog->AddLine(e);
                }
            }
            while (retries < 5);

            if (m_pLog)
            {
                CString message;
                message.LoadString(IDS_AL_MODEL_SOAPPUBLICATION_START);
                PSS_GenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            // publish the model
            PSS_SoapPublishModelDefinition SOAPPublishModel(&info,
                                                            m_pModelDoc->GetModel(),
                                                            static_cast<void*>(&info));

            // assign the log
            SOAPPublishModel.SetLog(m_pLog);

            retries = 0;

            do
            {
                if (SOAPPublishModel.Navigate())
                {
                    if (m_pLog)
                    {
                        CString message;
                        message.LoadString(IDS_AL_MODEL_SOAPPUBLICATION);
                        PSS_GenericSymbolErrorLine e(message);
                        m_pLog->AddLine(e);
                    }

                    break;
                }

                ++retries;

                if (m_pLog)
                {
                    CString message;
                    message.LoadString(IDS_AL_MODEL_SOAPPUBLICATION_ERR);
                    PSS_GenericSymbolErrorLine e(message);
                    m_pLog->AddLine(e);
                }
            }
            while (retries < 5);

            if (m_pLog)
            {
                CString message;
                message.LoadString(IDS_AL_MODELHTML_SOAPPUBLICATION_START);
                PSS_GenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            CDC* pDC = m_pModelDoc->GetFirstModelView()->GetDC();

            try
            {
                PSS_InfoModelGraphicGeneration modelInfo(m_pModelDoc->GetModel(),
                                                         m_pModelDoc->GetFirstModelView()->GetModelController(),
                                                         _T(""),
                                                         FALSE,
                                                         false,
                                                         false,
                                                         false,
                                                         _T(""),
                                                         _T(""),
                                                         pDC,
                                                         PSS_Global::GetServer());

                PSS_SoapPublishModelGenerateFiles modelGen(m_pModelDoc->GetModel(), &modelInfo, &info);

                // assign the log pointer
                modelGen.SetLog(m_pLog);

                retries = 0;

                do
                {
                    if (modelGen.Navigate())
                    {
                        if (m_pLog)
                        {
                            CString message;
                            message.LoadString(IDS_AL_MODELHTML_SOAPPUBLICATION);
                            PSS_GenericSymbolErrorLine e(message);
                            m_pLog->AddLine(e);
                        }

                        break;
                    }

                    ++retries;

                    if (m_pLog)
                    {
                        CString message;
                        message.LoadString(IDS_AL_MODELHTML_SOAPPUBLICATION_ERR);
                        PSS_GenericSymbolErrorLine e(message);
                        m_pLog->AddLine(e);
                    }
                }
                while (retries < 5);
            }
            catch (...)
            {
                PSS_ProcessGraphModelView* pView = m_pModelDoc->GetFirstModelView();

                // don't forget to release the dc
                if (pView && pDC)
                    ::ReleaseDC(pView->GetSafeHwnd(), pDC->GetSafeHdc());

                throw;
            }

            PSS_ProcessGraphModelView* pView = m_pModelDoc->GetFirstModelView();

            // don't forget to release the dc
            if (pView && pDC)
                ::ReleaseDC(pView->GetSafeHwnd(), pDC->GetSafeHdc());
        }

        // can log?
        if (m_pLog)
        {
            CString message;
            message.LoadString(IDS_AL_STOP_SOAPPUBLICATION);
            PSS_GenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }
    }
    catch (SOAPException&)
    {
        if (m_pLog)
        {
            CString message;
            message.LoadString(IDS_AL_MODELHTML_SOAPPUBLICATION_ERR);
            PSS_GenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }
    }

    return IDOK;
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PublishToMessengerStartWizardDlg, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_PublishToMessengerStartWizardDlg)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PublishToMessengerStartWizardDlg
//---------------------------------------------------------------------------
PSS_PublishToMessengerStartWizardDlg::PSS_PublishToMessengerStartWizardDlg(const CString& iniFile, CWnd* pParent) :
    PSS_WizardDialog(PSS_PublishToMessengerStartWizardDlg::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZ_PUBLISHTOMESSENGER_ST_S,
                     IDS_WZ_PUBLISHTOMESSENGER_ST_T),
    m_IniFile(iniFile),
    m_IncludeModel(TRUE),
    m_IncludeGroups(TRUE),
    m_IncludeSystems(TRUE),
    m_IncludePrestations(TRUE)
{}
//---------------------------------------------------------------------------
void PSS_PublishToMessengerStartWizardDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_PublishToMessengerStartWizardDlg)
    DDX_Control(pDX, IDC_MESSENGER_ADR,       m_MessengerAddressEdit);
    DDX_Control(pDX, IDC_MESSENGER_ALIAS,     m_MessengerAliasEdit);
    DDX_Check  (pDX, IDC_INCLUDE_MODEL,       m_IncludeModel);
    DDX_Check  (pDX, IDC_INCLUDE_GROUPS,      m_IncludeGroups);
    DDX_Check  (pDX, IDC_INCLUDE_SYSTEMS,     m_IncludeSystems);
    DDX_Check  (pDX, IDC_INCLUDE_PRESTATIONS, m_IncludePrestations);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_PublishToMessengerStartWizardDlg::OnInitDialog()
{
    // load all the values
    LoadStateFromIniFile();

    PSS_WizardDialog::OnInitDialog();

    // load the address edit
    m_MessengerAddressEdit.Initialize(&m_ArrayOfAddress);
    m_MessengerAddressEdit.SetWindowText(m_MessengerAddress);

    // initialize the alias
    m_MessengerAliasEdit.SetWindowText(m_MessengerAlias);

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PublishToMessengerStartWizardDlg::OnNext()
{
    UpdateData(TRUE);

    // update the alias address
    m_MessengerAddressEdit.GetWindowText(m_MessengerAddress);
    m_MessengerAliasEdit.GetWindowText(m_MessengerAlias);

    // check if address and alias are empty
    if (m_MessengerAddress.IsEmpty() || m_MessengerAlias.IsEmpty())
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_ADRESS_ALIAS_IS_EMPTY, MB_OK);
        return;
    }

    // save input values
    SaveStateToIniFile();

    EndDialog(IDNEXT);
}
//---------------------------------------------------------------------------
bool PSS_PublishToMessengerStartWizardDlg::LoadStateFromIniFile()
{
    PSS_SystemOption SystemOption(m_IniFile, g_PublishMessengerSectionName);

    // read the options
    m_IncludeModel       = SystemOption.ReadOption(g_PublishMessengerIncludeModelEntityName,       true);
    m_IncludeGroups      = SystemOption.ReadOption(g_PublishMessengerIncludeGroupsEntityName,      true);
    m_IncludeSystems     = SystemOption.ReadOption(g_PublishMessengerIncludeSystemsEntityName,     true);
    m_IncludePrestations = SystemOption.ReadOption(g_PublishMessengerIncludePrestationsEntityName, true);
    m_MessengerAddress   = SystemOption.ReadOption(g_PublishMessengerLastAddressEntityName,        _T(""));
    m_MessengerAlias     = SystemOption.ReadOption(g_PublishMessengerAliasName,                    _T(""));

    // remove all elements
    m_ArrayOfAddress.RemoveAll();

    CString     keyName;
    CString     addr;
    std::size_t index = 0;

    do
    {
        // format the key
        keyName.Format(_T("%s_%d"), (const char*)g_PublishMessengerAddressEntityName, index);
        addr = SystemOption.ReadOption(keyName, _T(""));

        if (addr.IsEmpty())
            break;

        // add the element to the table
        m_ArrayOfAddress.Add(addr);

        ++index;
    }
    while (index < 1000); // set the maximum loop to a thousand of objects, which is enough

    return true;
}
//---------------------------------------------------------------------------
bool PSS_PublishToMessengerStartWizardDlg::SaveStateToIniFile()
{
    PSS_SystemOption systemOption(m_IniFile, g_PublishMessengerSectionName);

    // save the options
    systemOption.WriteOption(g_PublishMessengerIncludeModelEntityName,       m_IncludeModel);
    systemOption.WriteOption(g_PublishMessengerIncludeGroupsEntityName,      m_IncludeGroups);
    systemOption.WriteOption(g_PublishMessengerIncludeSystemsEntityName,     m_IncludeSystems);
    systemOption.WriteOption(g_PublishMessengerIncludePrestationsEntityName, m_IncludePrestations);
    systemOption.WriteOption(g_PublishMessengerLastAddressEntityName,        m_MessengerAddress);
    systemOption.WriteOption(g_PublishMessengerAliasName,                    m_MessengerAlias);

    const int addressCount = m_ArrayOfAddress.GetSize();

    CString keyName;
    bool    found = false;

    // add the address to the array
    for (int i = 0; i < addressCount; ++i)
        if (m_ArrayOfAddress.GetAt(i) == m_MessengerAddress)
            found = true;

    if (!found)
        m_ArrayOfAddress.Add(m_MessengerAddress);

    for (int i = 0; i < addressCount; ++i)
    {
        // format the key
        keyName.Format(_T("%s_%d"), (const char*)g_PublishMessengerAddressEntityName, i);

        // write the string to the ini file
        systemOption.WriteOption(keyName, m_ArrayOfAddress.GetAt(i));
    }

    return true;
}
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_PublishToMessengerLogonWizardDlg, PSS_WizardDialog)
    //{{AFX_MSG_MAP(PSS_PublishToMessengerLogonWizardDlg)
    ON_BN_CLICKED(IDOK, OnOK)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_PublishToMessengerLogonWizardDlg
//---------------------------------------------------------------------------
PSS_PublishToMessengerLogonWizardDlg::PSS_PublishToMessengerLogonWizardDlg(PSS_PublishMessengerModelInformation* pInfo,
                                                                           CWnd*                                 pParent) :
    PSS_WizardDialog(PSS_PublishToMessengerLogonWizardDlg::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZ_PUBLISHTOMESSENGERLOGON_ST_S,
                     IDS_WZ_PUBLISHTOMESSENGERLOGON_ST_T),
    m_pInfo(pInfo)
{}
//---------------------------------------------------------------------------
PSS_PublishToMessengerLogonWizardDlg::~PSS_PublishToMessengerLogonWizardDlg()
{}
//---------------------------------------------------------------------------
void PSS_PublishToMessengerLogonWizardDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_PublishToMessengerLogonWizardDlg)
    DDX_Text(pDX, IDC_MESSENGER_PASSWORD, m_Password);
    DDX_Text(pDX, IDC_MESSENGER_USERNAME, m_UserName);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_PublishToMessengerLogonWizardDlg::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    // set the correct address
    if (m_pInfo)
        PSS_SoapData_Settings::m_Url = (const char*)m_pInfo->m_MessengerAddress;

    // return TRUE unless you set the focus to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_PublishToMessengerLogonWizardDlg::OnOK()
{
    UpdateData(TRUE);

    PSS_SoapPublisher_MessengerInfo info;

    if (info.Authenticate((const char*)m_UserName, (const char*)m_Password) < 0)
    {
        // error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_INVALID_MESSENGER_USERPSWD, MB_OK);
        return;
    }

    CWnd* beginDateBox = GetDlgItem(IDC_MESSENGER_DATE_BEGIN);

    if (beginDateBox)
        beginDateBox->GetWindowText(m_BeginDate);

    m_EndDate = _T("null");

    PSS_WizardDialog::OnOK();
}
//---------------------------------------------------------------------------
