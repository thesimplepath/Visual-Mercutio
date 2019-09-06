// ZVPublishToMessengerWizard.cpp: implementation of the ZVPublishToMessengerWizard class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZVPublishToMessengerWizard.h"

// processsoft
#include "zBaseLib\ZILog.h"
#include "zBaseLib\ZUSystemOption.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_Global.h"
#include "zModel\ProcGraphModelDoc.h"
#define _ZMODELEXPORT
#include "zModel\ProcGraphModelView.h"
#undef _ZMODELEXPORT
#include "zModel\ZBInfoModelGraphicGeneration.h"
#include "zModel\ZBGenericSymbolErrorLine.h"
#include "zSOAP\PSS_SoapData_Settings.h"
#include "zSOAP\PSS_SoapPublisher_MessengerInfo.h"
#include "zSOAP\PSS_SoapException.h"
#include "ZBPublishMessengerModelInformation.h"
#include "PSS_SoapPublishUserGroup.h"
#include "PSS_SoapPublishLogicalSystem.h"
#include "PSS_SoapPublishPrestations.h"
#include "PSS_SoapPublishMessengerUniverse.h"
#include "PSS_SoapPublishModelDefinition.h"
#include "PSS_SoapPublishModelAttributes.h"
#include "PSS_SOAPPublishModelGenerateFiles.h"
#include "ZUCheckValidUnit.h"
#include "ZUCheckMessengerValidUnit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 2 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Global definitions

// JMR-MODIF - Le 30 mai 2006 - Ajout de la constante gPublishMessengerIncludePrestationsEntityName.
// JMR-MODIF - Le 21 juin 2006 - Ajout de la constante gPublishMessengerAliasName.
const CString gPublishMessengerSectionName = _T("PublishToMessenger");
const CString gPublishMessengerAddressEntityName = _T("PublishAddress");
const CString gPublishMessengerLastAddressEntityName = _T("LastPublishAddress");
const CString gPublishMessengerIncludeModelEntityName = _T("IncludeModel");
const CString gPublishMessengerIncludeGroupsEntityName = _T("IncludeGroups");
const CString gPublishMessengerIncludeSystemsEntityName = _T("IncludeSystems");
const CString gPublishMessengerIncludePrestationsEntityName = _T("IncludePrestations");
const CString gPublishMessengerAliasName = _T("Alias");

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZVPublishToMessengerWizard::ZVPublishToMessengerWizard(ZDProcessGraphModelDoc*    pModelDoc,
                                                       ZILog*                    pLog            /*= NULL*/,
                                                       const                    CString IniFile    /*= ""*/)
    : m_pModelDoc(pModelDoc),
    m_pLog(pLog),
    m_IniFile(IniFile)
{}

ZVPublishToMessengerWizard::~ZVPublishToMessengerWizard()
{}

int ZVPublishToMessengerWizard::DoModal()
{
    if (!m_pModelDoc)
    {
        return IDCANCEL;
    }

    try
    {
        // If log
        if (m_pLog)
        {
            m_pLog->ClearLog();
            CString message;
            message.LoadString(IDS_AL_START_MESSENGERCHECK);
            ZBGenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }

        // Do a unit check before lauching the wizard for the messenger publication
        ZUCheckMessengerValidUnit CheckUnit(m_pModelDoc->GetModel());
        CheckUnit.SetLog(m_pLog);
        CheckUnit.Navigate();

        // Do a second unit check to be sure all units defined in symbol are still exist
        ZUCheckValidUnit Check(m_pModelDoc->GetModel());
        Check.SetLog(m_pLog);
        Check.Navigate();

        if (CheckUnit.GetErrorCounter() > 0 || Check.GetErrorCounter() > 0)
        {
            if (m_pLog)
            {
                CString message;
                message.Format(IDS_ZS_STOP2,
                               CheckUnit.GetErrorCounter() + Check.GetErrorCounter(),
                               CheckUnit.GetWarningCounter() + Check.GetWarningCounter());

                ZBGenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            return IDCANCEL;
        }

        if (m_pLog)
        {
            CString message;

            if (CheckUnit.GetWarningCounter() > 0 || Check.GetWarningCounter() > 0)
            {
                message.Format(IDS_ZS_STOP2,
                               CheckUnit.GetErrorCounter() + Check.GetErrorCounter(),
                               CheckUnit.GetWarningCounter() + Check.GetWarningCounter());
            }
            else
            {
                message.LoadString(IDS_ZS_STOP);
            }

            ZBGenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }

        ZVPublishToMessengerStart Start(m_IniFile);

        if (Start.DoModal() == IDCANCEL)
        {
            return IDCANCEL;
        }

        // JMR-MODIF - Le 21 juin 2006 - Ajout de l'alias dans les paramètres.
        ZBPublishMessengerModelInformation Info(m_pModelDoc,
                                                Start.GetMessengerAddress(),
                                                Start.GetMessengerAlias());

        ZVPublishToMessengerLogon Logon(&Info);

        if (Logon.DoModal() == IDCANCEL)
        {
            if (m_pLog)
            {
                CString message;
                message.LoadString(IDS_AL_CANCEL_SOAPPUBLICATION);
                ZBGenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            return IDCANCEL;
        }

        if (m_pLog)
        {
            CString message;
            message.LoadString(IDS_AL_AUTHENTICATIONOK_SOAPPUBLICATION);
            ZBGenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }

        // JMR-MODIF - Le 21 juin 2006 - Ajout des dates de validité dans les informations de publication.
        Info.m_BeginDate = Logon.GetBeginDate();
        Info.m_EndDate = Logon.GetEndDate();

        // Starts the publication
        if (m_pLog)
        {
            CString message;
            message.Format(IDS_AL_START_SOAPPUBLICATION, m_pModelDoc->GetModel()->GetModelName());
            ZBGenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }

        // JMR-MODIF - Le 21 juin 2006 - Ajout de la fonction de test pour les multi-modèles.
        if (m_pLog)
        {
            CString message;
            message.LoadString(IDS_AL_GROUP_MULTIMODELS_CHECK_START);
            ZBGenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }

        // ***************************************************************************************************
        // JMR-MODIF - Le 21 juin 2006 - Ajout du contrôle des référentiels pour la publication multi-modèles.

        int                              nbCheck = 0;
        BOOL                             IsCheckOK = FALSE;
        PSS_SoapPublishMessengerUniverse SOAPPubCheckUniverse(&Info, m_pLog);

        do
        {
            if (SOAPPubCheckUniverse.Publish())
            {
                if (m_pLog)
                {
                    CString message;
                    message.LoadString(IDS_AL_GROUP_MULTIMODELS_CHECK_END);
                    ZBGenericSymbolErrorLine e(message);
                    m_pLog->AddLine(e);
                }

                IsCheckOK = TRUE;

                // ok
                break;
            }

            ++nbCheck;
        }
        while (nbCheck < 5);

        if (IsCheckOK == FALSE)
        {
            if (m_pLog)
            {
                CString message;
                message.LoadString(IDS_AL_GROUP_MULTIMODELS_CHECK_ERR);
                ZBGenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            return IDCANCEL;
        }
        // ***************************************************************************************************

        // Publish the groups
        if (Start.GetIncludeGroups())
        {
            // JMR-MODIF - Le 29 mai 2006 - Ajout du message d'information "Publication en cours..."
            if (m_pLog)
            {
                CString message;
                message.LoadString(IDS_AL_GROUP_SOAPPUBLICATION_START);
                ZBGenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            PSS_SoapPublishUserGroup SOAPPublishGroups(&Info, m_pLog);

            int retries = 0;

            do
            {
                if (SOAPPublishGroups.Publish())
                {
                    if (m_pLog)
                    {
                        CString message;
                        message.LoadString(IDS_AL_GROUP_SOAPPUBLICATION);
                        ZBGenericSymbolErrorLine e(message);
                        m_pLog->AddLine(e);
                    }

                    // ok
                    break;
                }

                ++retries;

                if (m_pLog)
                {
                    CString message;
                    message.LoadString(IDS_AL_GROUP_SOAPPUBLICATION_ERR);
                    ZBGenericSymbolErrorLine e(message);
                    m_pLog->AddLine(e);
                }
            }
            while (retries < 5);
        }

        // Publish the logical systems
        if (Start.GetIncludeSystems())
        {
            // JMR-MODIF - Le 29 mai 2006 - Ajout du message d'information "Publication en cours..."
            if (m_pLog)
            {
                CString message;
                message.LoadString(IDS_AL_SYSTEM_SOAPPUBLICATION_START);
                ZBGenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            PSS_SoapPublishLogicalSystem SOAPPublishLogicalSystem(&Info, m_pLog);

            int retries = 0;

            do
            {
                if (SOAPPublishLogicalSystem.Publish())
                {
                    if (m_pLog)
                    {
                        CString message;
                        message.LoadString(IDS_AL_SYSTEM_SOAPPUBLICATION);
                        ZBGenericSymbolErrorLine e(message);
                        m_pLog->AddLine(e);
                    }

                    // ok
                    break;
                }

                ++retries;

                if (m_pLog)
                {
                    CString message;
                    message.LoadString(IDS_AL_SYSTEM_SOAPPUBLICATION_ERR);
                    ZBGenericSymbolErrorLine e(message);
                    m_pLog->AddLine(e);
                }
            }
            while (retries < 5);
        }

        //******************************************************************************************************
        // JMR-MODIF - Le 6 avril 2006 - Publie les prestations dans Messenger.

        if (Start.GetIncludePrestations())
        {
            // JMR-MODIF - Le 29 mai 2006 - Ajout du message d'information "Publication en cours..."
            if (m_pLog)
            {
                CString message;
                message.LoadString(IDS_AL_PRESTATIONS_SOAPPUBLICATION_START);
                ZBGenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            PSS_SoapPublishPrestations SOAPPublishPrestations(&Info, m_pLog);

            int retries = 0;

            do
            {
                if (SOAPPublishPrestations.Publish())
                {
                    if (m_pLog)
                    {
                        CString message;
                        message.LoadString(IDS_AL_PRESTATIONS_SOAPPUBLICATION);
                        ZBGenericSymbolErrorLine e(message);
                        m_pLog->AddLine(e);
                    }

                    // ok
                    break;
                }

                ++retries;

                if (m_pLog)
                {
                    CString message;
                    message.LoadString(IDS_AL_PRESTATIONS_SOAPPUBLICATION_ERR);
                    ZBGenericSymbolErrorLine e(message);
                    m_pLog->AddLine(e);
                }
            }
            while (retries < 5);
        }
        //******************************************************************************************************

        // Publish the model, with all attributes and HTML dependant publications.
        if (Start.GetIncludeModel())
        {
            // *************************************************************************************************
            // JMR-MODIF - Le 21 juin 2006 - Les attributs sont maintenant publiés en même temps que le modèle.
            // JMR-MODIF - Le 29 mai 2006 - Ajout du message d'information "Publication en cours..."
            if (m_pLog)
            {
                CString message;
                message.LoadString(IDS_AL_ATTRIBUTES_SOAPPUBLICATION_START);
                ZBGenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            PSS_SoapPublishModelAttributes SOAPPublishAttributes(&Info,
                                                                 m_pModelDoc->GetModel(),
                                                                 (void*)((const char*)Start.GetMessengerAddress()));

            // Assigns the log pointer
            SOAPPublishAttributes.SetLog(m_pLog);

            int retries = 0;

            do
            {
                if (SOAPPublishAttributes.Navigate())
                {
                    if (m_pLog)
                    {
                        CString message;
                        message.LoadString(IDS_AL_ATTRIBUTES_SOAPPUBLICATION);
                        ZBGenericSymbolErrorLine e(message);
                        m_pLog->AddLine(e);
                    }

                    // ok
                    break;
                }

                ++retries;

                if (m_pLog)
                {
                    CString message;
                    message.LoadString(IDS_AL_ATTRIBUTES_SOAPPUBLICATION_ERR);
                    ZBGenericSymbolErrorLine e(message);
                    m_pLog->AddLine(e);
                }
            }
            while (retries < 5);
            // *************************************************************************************************

            // Publication du modèle.
            // JMR-MODIF - Le 29 mai 2006 - Ajout du message d'information "Publication en cours..."
            if (m_pLog)
            {
                CString message;
                message.LoadString(IDS_AL_MODEL_SOAPPUBLICATION_START);
                ZBGenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            // Publish the model
            PSS_SoapPublishModelDefinition SOAPPublishModel(&Info,
                                                            m_pModelDoc->GetModel(),
                                                            static_cast<void*>(&Info));

            // Assigns the log pointer
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
                        ZBGenericSymbolErrorLine e(message);
                        m_pLog->AddLine(e);
                    }

                    // ok
                    break;
                }

                ++retries;

                if (m_pLog)
                {
                    CString message;
                    message.LoadString(IDS_AL_MODEL_SOAPPUBLICATION_ERR);
                    ZBGenericSymbolErrorLine e(message);
                    m_pLog->AddLine(e);
                }
            }
            while (retries < 5);

            // *************************************************************************************************
            // JMR-MODIF - Le 21 juin 2006 - La publication HTML se fait maintenant en même temps que le modèle.
            // JMR-MODIF - Le 29 mai 2006 - Ajout du message d'information "Publication en cours..."
            if (m_pLog)
            {
                CString message;
                message.LoadString(IDS_AL_MODELHTML_SOAPPUBLICATION_START);
                ZBGenericSymbolErrorLine e(message);
                m_pLog->AddLine(e);
            }

            CDC* pDC = m_pModelDoc->GetFirstModelView()->GetDC();

            ZBInfoModelGraphicGeneration ModelInfo(m_pModelDoc->GetModel(),
                                                   m_pModelDoc->GetFirstModelView()->GetModelController(),
                                                   _T(""),
                                                   FALSE,
                                                   false,
                                                   false,        // JMR-MODIF - Rapport pas généré dans Messenger.
                                                   false,        // JMR-MODIF - Livre des règles pas généré dans Messenger.
                                                   _T(""),
                                                   _T(""),
                                                   pDC,
                                                   PSS_Global::GetServer());

            PSS_SoapPublishModelGenerateFiles ModelGen(m_pModelDoc->GetModel(), &ModelInfo, &Info);

            // Assigns the log pointer
            ModelGen.SetLog(m_pLog);

            retries = 0;

            do
            {
                if (ModelGen.Navigate())
                {
                    if (m_pLog)
                    {
                        CString message;
                        message.LoadString(IDS_AL_MODELHTML_SOAPPUBLICATION);
                        ZBGenericSymbolErrorLine e(message);
                        m_pLog->AddLine(e);
                    }

                    // ok
                    break;
                }

                ++retries;

                if (m_pLog)
                {
                    CString message;
                    message.LoadString(IDS_AL_MODELHTML_SOAPPUBLICATION_ERR);
                    ZBGenericSymbolErrorLine e(message);
                    m_pLog->AddLine(e);
                }
            }
            while (retries < 5);

            // Don't forget to release the dc used
            ReleaseDC(m_pModelDoc->GetFirstModelView()->GetSafeHwnd(), pDC->GetSafeHdc());
            // *************************************************************************************************
        }

        // If log
        if (m_pLog)
        {
            CString message;
            message.LoadString(IDS_AL_STOP_SOAPPUBLICATION);
            ZBGenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }
    }
    catch (SOAPException&)
    {
        if (m_pLog)
        {
            CString message;
            message.LoadString(IDS_AL_MODELHTML_SOAPPUBLICATION_ERR);
            ZBGenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }
    }

    return IDOK;
}

/////////////////////////////////////////////////////////////////////////////
// ZVPublishToMessengerStart dialog

BEGIN_MESSAGE_MAP(ZVPublishToMessengerStart, PSS_WizardDialog)
    //{{AFX_MSG_MAP(ZVPublishToMessengerStart)
    ON_BN_CLICKED(IDNEXT, OnNext)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVPublishToMessengerStart::ZVPublishToMessengerStart(const CString IniFile /*= ""*/, CWnd* pParent /*=NULL*/) :
    PSS_WizardDialog(ZVPublishToMessengerStart::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZ_PUBLISHTOMESSENGER_ST_S,
                     IDS_WZ_PUBLISHTOMESSENGER_ST_T),
    m_IniFile(IniFile)
{
    //{{AFX_DATA_INIT(ZVPublishToMessengerStart)
    m_IncludeModel = TRUE;
    m_IncludeGroups = TRUE;
    m_IncludeSystems = TRUE;
    m_IncludePrestations = TRUE;
    m_MessengerAddress = _T("");
    m_MessengerAlias = _T("");
    //}}AFX_DATA_INIT
}

void ZVPublishToMessengerStart::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVPublishToMessengerStart)
    DDX_Control(pDX, IDC_MESSENGER_ADR, m_MessengerAddressEdit);
    DDX_Control(pDX, IDC_MESSENGER_ALIAS, m_MessengerAliasEdit);
    DDX_Check(pDX, IDC_INCLUDE_MODEL, m_IncludeModel);
    DDX_Check(pDX, IDC_INCLUDE_GROUPS, m_IncludeGroups);
    DDX_Check(pDX, IDC_INCLUDE_SYSTEMS, m_IncludeSystems);
    DDX_Check(pDX, IDC_INCLUDE_PRESTATIONS, m_IncludePrestations);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVPublishToMessengerStart message handlers

BOOL ZVPublishToMessengerStart::OnInitDialog()
{
    // Load all the values
    LoadStateFromIniFile();

    PSS_WizardDialog::OnInitDialog();

    // Load the address edit
    m_MessengerAddressEdit.Initialize(&m_ArrayOfAddress);
    m_MessengerAddressEdit.SetWindowText(m_MessengerAddress);

    // JMR-MODIF - Le 21 juin 2006 - Ajout du code d'initialisation de la plage Alias.
    m_MessengerAliasEdit.SetWindowText(m_MessengerAlias);

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVPublishToMessengerStart::OnNext()
{
    UpdateData(TRUE);

    // JMR-MODIF - Le 21 juin 2006 - Ajout du code pour la mise à jour de l'adresse et de l'alias.
    m_MessengerAddressEdit.GetWindowText(m_MessengerAddress);
    m_MessengerAliasEdit.GetWindowText(m_MessengerAlias);

    // JMR-MODIF - Le 21 juin 2006 - Teste que l'adresse et l'alias ne soient pas vides.
    if (m_MessengerAddress == _T("") || m_MessengerAlias == _T(""))
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_ADRESS_ALIAS_IS_EMPTY, MB_OK);
        return;
    }

    // Save input values
    SaveStateToIniFile();

    EndDialog(IDNEXT);
}

bool ZVPublishToMessengerStart::LoadStateFromIniFile()
{
    ZUSystemOption SystemOption(m_IniFile, gPublishMessengerSectionName);

    // Read the options
    // JMR-MODIF - Le 30 mai 2006 - Ajouté la ligne pour la lecture de m_IncludePrestations.
    m_IncludeModel = SystemOption.ReadOption(gPublishMessengerIncludeModelEntityName, true);
    m_IncludeGroups = SystemOption.ReadOption(gPublishMessengerIncludeGroupsEntityName, true);
    m_IncludeSystems = SystemOption.ReadOption(gPublishMessengerIncludeSystemsEntityName, true);
    m_IncludePrestations = SystemOption.ReadOption(gPublishMessengerIncludePrestationsEntityName, true);
    m_MessengerAddress = SystemOption.ReadOption(gPublishMessengerLastAddressEntityName, _T(""));
    m_MessengerAlias = SystemOption.ReadOption(gPublishMessengerAliasName, _T(""));

    CString KeyName;
    CString Addr;
    size_t Idx = 0;

    // Remove all elements
    m_ArrayOfAddress.RemoveAll();

    do
    {
        // Format the key
        KeyName.Format(_T("%s_%d"), (const char*)gPublishMessengerAddressEntityName, Idx);
        Addr = SystemOption.ReadOption(KeyName, _T(""));

        if (Addr.IsEmpty())
        {
            break;
        }

        // Add element to the table
        m_ArrayOfAddress.Add(Addr);

        ++Idx;
    }
    while (Idx < 1000);    // Sets the maximum loop at thousand objects
                            // which is big already

    return true;
}
//---------------------------------------------------------------------------
bool ZVPublishToMessengerStart::SaveStateToIniFile()
{
    ZUSystemOption systemOption(m_IniFile, gPublishMessengerSectionName);

    // save the options
    // JMR-MODIF - Le 30 mai 2006 - Ajouté la ligne pour l'écritue de m_IncludePrestations.
    systemOption.WriteOption(gPublishMessengerIncludeModelEntityName, m_IncludeModel);
    systemOption.WriteOption(gPublishMessengerIncludeGroupsEntityName, m_IncludeGroups);
    systemOption.WriteOption(gPublishMessengerIncludeSystemsEntityName, m_IncludeSystems);
    systemOption.WriteOption(gPublishMessengerIncludePrestationsEntityName, m_IncludePrestations);
    systemOption.WriteOption(gPublishMessengerLastAddressEntityName, m_MessengerAddress);
    systemOption.WriteOption(gPublishMessengerAliasName, m_MessengerAlias);

    CString keyName;

    // add the address to the array
    bool found = false;

    for (int idx = 0; idx < m_ArrayOfAddress.GetSize(); ++idx)
        if (m_ArrayOfAddress.GetAt(idx) == m_MessengerAddress)
            found = true;

    if (!found)
        m_ArrayOfAddress.Add(m_MessengerAddress);

    for (int idx = 0; idx < m_ArrayOfAddress.GetSize(); ++idx)
    {
        // format the key
        keyName.Format(_T("%s_%d"), (const char*)gPublishMessengerAddressEntityName, idx);

        // Write the string to the ini file
        systemOption.WriteOption(keyName, m_ArrayOfAddress.GetAt(idx));
    }

    return true;
}
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// ZVPublishToMessengerLogon dialog

BEGIN_MESSAGE_MAP(ZVPublishToMessengerLogon, PSS_WizardDialog)
    //{{AFX_MSG_MAP(ZVPublishToMessengerLogon)
    ON_BN_CLICKED(IDOK, OnOK)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

ZVPublishToMessengerLogon::ZVPublishToMessengerLogon(ZBPublishMessengerModelInformation*    pInfo,
                                                     CWnd*                                    pParent /*=NULL*/) :
    PSS_WizardDialog(ZVPublishToMessengerLogon::IDD,
                     IDB_WZBMP1,
                     0,
                     0,
                     IDS_WZ_PUBLISHTOMESSENGERLOGON_ST_S,
                     IDS_WZ_PUBLISHTOMESSENGERLOGON_ST_T),
    m_pInfo(pInfo)
{
    // JMR-MODIF - Le 19 juin 2006 - Ajout de l'initialisation des variables m_Date_Begin et m_Date_End;
    m_Date_Begin = _T("");
    m_Date_End = _T("");

    //{{AFX_DATA_INIT(ZVPublishToMessengerLogon)
    m_Password = _T("");
    m_Username = _T("");
    //}}AFX_DATA_INIT
}

void ZVPublishToMessengerLogon::DoDataExchange(CDataExchange* pDX)
{
    PSS_WizardDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVPublishToMessengerLogon)
    DDX_Text(pDX, IDC_MESSENGER_PASSWORD, m_Password);
    DDX_Text(pDX, IDC_MESSENGER_USERNAME, m_Username);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ZVPublishToMessengerLogon message handlers

BOOL ZVPublishToMessengerLogon::OnInitDialog()
{
    PSS_WizardDialog::OnInitDialog();

    // Sets the correct address
    if (m_pInfo)
    {
        PSS_SoapData_Settings::m_Url = (const char*)m_pInfo->m_MessengerAddress;
    }

    return TRUE;    // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVPublishToMessengerLogon::OnOK()
{
    UpdateData(TRUE);

    PSS_SoapPublisher_MessengerInfo info;

    if (info.Authenticate((const char*)m_Username, (const char*)m_Password) < 0)
    {
        // error message
        PSS_MsgBox mBox;
        mBox.Show(IDS_INVALID_MESSENGER_USERPSWD, MB_OK);
        return;
    }

    CWnd* m_DateBox_Begin = GetDlgItem(IDC_MESSENGER_DATE_BEGIN);

    if (m_DateBox_Begin)
        m_DateBox_Begin->GetWindowText(m_Date_Begin);

    m_Date_End = _T("null");

    PSS_WizardDialog::OnOK();
}
