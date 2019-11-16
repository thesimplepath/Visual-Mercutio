/****************************************************************************
 * ==> PSS_Activity --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an activity                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Activity.h"

// processsoft
#include "zBaseLib\PSS_BaseDocument.h"
#include "zBaseLib\PSS_MessageDlg.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_Tokenizer.h"

// resources
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_Activity, PSS_BaseActivity, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_Activity
//---------------------------------------------------------------------------
PSS_Activity::PSS_Activity(const CString& activityName,
                           const CString& activityDescription,
                           int            activityType,
                           IEStatus       activityStatus) :
    PSS_BaseActivity(activityName, activityDescription, activityStatus),
    m_pMailMessage(NULL),
    m_pCommandLine(NULL),
    m_pBaseOnFormFile(NULL),
    m_pBaseOnProcFile(NULL),
    m_FormAttachmentType(PSS_File::IE_AT_InsertedFile),
    m_ProcessAttachmentType(PSS_File::IE_AT_InsertedFile),
    m_RequireFormFile(E_TS_False),
    m_RequireProcFile(E_TS_False),
    m_RejectedToActivity(g_RejectActivityToPrevious),
    m_PreConditionsDone(FALSE),
    m_PostConditionsDone(FALSE),
    m_PreFormReadOnly(FALSE),
    m_PreProcReadOnly(FALSE)
{
    m_ActivityType = activityType;
}
//---------------------------------------------------------------------------
PSS_Activity::PSS_Activity(const PSS_Activity& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_Activity::~PSS_Activity()
{
    if (m_pMailMessage)
        delete m_pMailMessage;

    if (m_pCommandLine)
        delete m_pCommandLine;

    if (m_pBaseOnFormFile)
        delete m_pBaseOnFormFile;

    if (m_pBaseOnProcFile)
        delete m_pBaseOnProcFile;
}
//---------------------------------------------------------------------------
const PSS_Activity& PSS_Activity::operator = (const PSS_Activity& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_Activity::AddTemplate(const CString& templateName)
{
    if (TemplateExist(templateName))
        return;

    m_TemplateArray.Add(templateName);
}
//---------------------------------------------------------------------------
BOOL PSS_Activity::RemoveTemplate(const CString& templateName)
{
    const std::size_t templateCount = GetTemplateCount();

    for (std::size_t i = 0; i < templateCount; ++i)
        if (GetTemplateAt(i) == templateName)
        {
            m_TemplateArray.RemoveAt(i);
            return TRUE;
        }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Activity::TemplateExist(const CString& templateName) const
{
    const std::size_t templateCount = GetTemplateCount();

    for (std::size_t i = 0; i < templateCount; ++i)
        if (GetTemplateAt(i) == templateName)
            return TRUE;

    return FALSE;
}
//---------------------------------------------------------------------------
CString PSS_Activity::BuildTemplateListString(const char separatorChar) const
{
    PSS_Tokenizer     tokenizer(separatorChar);
    const std::size_t templateCount = GetTemplateCount();

    for (std::size_t i = 0; i < templateCount; ++i)
        tokenizer.AddToken(GetTemplateAt(i));

    return tokenizer.GetString();
}
//---------------------------------------------------------------------------
CString PSS_Activity::GetDefaultString() const
{
    CString line = "Activité:" + GetName() + GetActivityStatusString();

    if (GetActivityStatus() != IE_AS_NotStarted)
    {
        line += " Démarré le: ";

        char buffer[30];
        ::sprintf_s(buffer,
                    ::_tcslen(buffer),
                    "%d.%d.%d",
                    GetStartDate().GetDay(),
                    GetStartDate().GetMonth(),
                    GetStartDate().GetYear());

        line += buffer;
    }

    return line;
}
//---------------------------------------------------------------------------
BOOL PSS_Activity::ActivityFillPersonArray(const PSS_UserManager& userManager,
                                           CStringArray&          userArray,
                                           const CString&         connectedUser)
{
    return GetCurrentResources().FillPersonArray(GetMainProcess(), userManager, userArray, connectedUser);
}
//---------------------------------------------------------------------------
PSS_MailUserList* PSS_Activity::ActivityCreatePersonList(const PSS_UserManager& userManager, const CString& connectedUser)
{
    return GetCurrentResources().CreatePersonList(GetMainProcess(), userManager, connectedUser);
}
//---------------------------------------------------------------------------
CString PSS_Activity::ActivityCreatePersonDelimStr(const PSS_UserManager& userManager,
                                                   const CString&         connectedUser,
                                                   const CString&         delimiter)
{
    return GetCurrentResources().CreatePersonDelimStr(GetMainProcess(), userManager, connectedUser, delimiter);
}
//---------------------------------------------------------------------------
void PSS_Activity::DeleteEmailToSend()
{
    if (m_pMailMessage)
        delete m_pMailMessage;

    m_pMailMessage = NULL;

    SetActivityAsSendMail(FALSE);
}
//---------------------------------------------------------------------------
void PSS_Activity::DeleteCommandLine()
{
    if (m_pCommandLine)
        delete m_pCommandLine;

    m_pCommandLine = NULL;

    SetActivityAsCommandLine(FALSE);
}
//---------------------------------------------------------------------------
void PSS_Activity::CalculateForecastedStartDate()
{}
//---------------------------------------------------------------------------
void PSS_Activity::CalculateForecastedEndDate()
{
    // set the forecasted end date by adding the duration to the start date
    #ifndef _WIN32
        // in 16bit
        if (GetStartDate() > 0)
            SetForecastedEndDate(GetStartDate() + CTimeSpan(GetDurationDays()));
        else
            SetForecastedEndDate(GetForecastedStartDate() + CTimeSpan(GetDurationDays()));
    #else
        // in 32bit
        if (GetStartDate() > 0)
            SetForecastedEndDate(GetStartDate() + COleDateTimeSpan(GetDurationDays()));
        else
            SetForecastedEndDate(GetForecastedStartDate() + COleDateTimeSpan(GetDurationDays()));
    #endif
}
//---------------------------------------------------------------------------
BOOL PSS_Activity::AddFormFile(const CString& fileName, PSS_File::IEAttachmentType attachment)
{
    if (!m_pBaseOnFormFile)
        m_pBaseOnFormFile = new PSS_FileManager;

    m_pBaseOnFormFile->AddFile(fileName, attachment);

    return m_pBaseOnFormFile->GetCount() > 0;
}
//---------------------------------------------------------------------------
BOOL PSS_Activity::AddFormFiles(const CStringArray& fileNameArray, PSS_File::IEAttachmentType attachment)
{
    if (!m_pBaseOnFormFile)
        m_pBaseOnFormFile = new PSS_FileManager;

    const int fileNameCount = fileNameArray.GetSize();

    for (int i = 0; i < fileNameCount; ++i)
        m_pBaseOnFormFile->AddFile(fileNameArray.GetAt(i), attachment);

    return m_pBaseOnFormFile->GetCount() > 0;
}
//---------------------------------------------------------------------------
BOOL PSS_Activity::RemoveAllFormFiles()
{
    if (m_pBaseOnFormFile)
        delete m_pBaseOnFormFile;

    m_pBaseOnFormFile = NULL;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Activity::AddProcFile(const CString& fileName, PSS_File::IEAttachmentType attachment)
{
    if (!m_pBaseOnProcFile)
        m_pBaseOnProcFile = new PSS_FileManager;

    m_pBaseOnProcFile->AddFile(fileName, attachment);

    return m_pBaseOnProcFile->GetCount() > 0;
}
//---------------------------------------------------------------------------
BOOL PSS_Activity::AddProcFiles(const CStringArray& fileNameArray, PSS_File::IEAttachmentType attachment)
{
    if (!m_pBaseOnProcFile)
        m_pBaseOnProcFile = new PSS_FileManager;

    const int fileNameCount = fileNameArray.GetSize();

    for (int i = 0; i < fileNameCount; ++i)
        m_pBaseOnProcFile->AddFile(fileNameArray.GetAt(i), attachment);

    return m_pBaseOnProcFile->GetCount() > 0;
}
//---------------------------------------------------------------------------
BOOL PSS_Activity::RemoveAllProcFiles()
{
    if (m_pBaseOnProcFile)
        delete m_pBaseOnProcFile;

    m_pBaseOnProcFile = NULL;

    return TRUE;
}
//---------------------------------------------------------------------------
std::size_t PSS_Activity::GetFormFileCount() const
{
    if (m_pBaseOnFormFile)
        return m_pBaseOnFormFile->GetCount();

    return 0;
}
//---------------------------------------------------------------------------
std::size_t PSS_Activity::GetProcFileCount() const
{
    if (m_pBaseOnProcFile)
        return m_pBaseOnProcFile->GetCount();

    return 0;
}
//---------------------------------------------------------------------------
PSS_File* PSS_Activity::GetFormFileAt(std::size_t index)
{
    if (index < GetFormFileCount())
        return m_pBaseOnFormFile->GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------
PSS_File* PSS_Activity::GetProcFileAt(std::size_t index)
{
    if (index < GetProcFileCount())
        return m_pBaseOnProcFile->GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_Activity::SetDefaultProperty()
{
    // call the base class function first
    PSS_BaseActivity::SetDefaultProperty();

    RemoveAllTemplates();

    DeleteEmailToSend();
    DeleteCommandLine();
    DeleteProcessToStart();

    SetActivityAsInput(FALSE);
    SetActivityAsScanning(FALSE);
    SetActivityAsArchiving(FALSE);

    DeleteBaseOnFormFile();
    DeleteBaseOnProcFile();

}
//---------------------------------------------------------------------------
CString PSS_Activity::GetActivityTypeKeyString() const
{
    PSS_Tokenizer tokenizer(';');

    if (ActivityIsAttribution())
        tokenizer.AddToken(g_ActivityTypeAttributionKey);

    if (ActivityIsAcceptation())
        tokenizer.AddToken(g_ActivityTypeAcceptationKey);

    if (ActivityIsInput())
        tokenizer.AddToken(g_ActivityTypeInputInformationKey);

    if (ActivityIsSendMail())
        tokenizer.AddToken(g_ActivityTypeSendMailKey);

    if (ActivityIsStartProcess())
        tokenizer.AddToken(g_ActivityTypeStartProcessKey);

    if (ActivityIsCommandLine())
        tokenizer.AddToken(g_ActivityTypeCommandLineKey);

    if (ActivityIsScanning())
        tokenizer.AddToken(g_ActivityTypeScanningKey);

    if (ActivityIsArchiving())
        tokenizer.AddToken(g_ActivityTypeArchivingKey);

    return tokenizer.GetString();
}
//---------------------------------------------------------------------------
void PSS_Activity::SetActivityTypeFromKeyString(const CString& key)
{
    PSS_Tokenizer tokenizer(';');
    CString       token = tokenizer.GetFirstToken(key);

    // iterate through key string
    while (!token.IsEmpty())
    {
        // if the user was found, return true
        if (token == g_ActivityTypeAttributionKey)
            SetActivityAsAttribution();
        else
        if (token == g_ActivityTypeAcceptationKey)
            SetActivityAsAcceptation();
        else
        if (token == g_ActivityTypeInputInformationKey)
            SetActivityAsInput();
        else
        if (token == g_ActivityTypeSendMailKey)
            SetActivityAsSendMail();
        else
        if (token == g_ActivityTypeStartProcessKey)
            SetActivityAsStartProcess();
        else
        if (token == g_ActivityTypeCommandLineKey)
            SetActivityAsCommandLine();
        else
        if (token == g_ActivityTypeScanningKey)
            SetActivityAsScanning();
        else
        if (token == g_ActivityTypeArchivingKey)
            SetActivityAsArchiving();

        // get the next token
        token = tokenizer.GetNextToken();
    }
}
//---------------------------------------------------------------------------
void PSS_Activity::DeleteProcessToStart()
{
    m_ProcessToStartArray.RemoveAll();
    SetActivityAsStartProcess(FALSE);
}
//---------------------------------------------------------------------------
void PSS_Activity::DeleteBaseOnFormFile()
{
    RemoveAllFormFiles();
    SetRequireFormFile(E_TS_False);
    SetFormAttachmentType(PSS_File::IE_AT_InsertedFile);
    SetPreFormReadOnly(TRUE);
}
//---------------------------------------------------------------------------
void PSS_Activity::DeleteBaseOnProcFile()
{
    RemoveAllProcFiles();
    SetRequireProcFile(E_TS_False);
    SetProcessAttachmentType(PSS_File::IE_AT_InsertedFile);
    SetPreProcReadOnly(TRUE);
}
//---------------------------------------------------------------------------
void PSS_Activity::Serialize(CArchive& ar)
{
    PSS_BaseActivity::Serialize(ar);

    if (ar.IsStoring())
    {
        ar << m_RejectedToActivity;
        ar << m_AttributedByActivity;

        // serialize the mail message
        ar << m_pMailMessage;

        // serialize the command line object
        ar << m_pCommandLine;

        // serialize the form file manager
        ar << m_pBaseOnFormFile;

        // serialize the process file manager
        ar << m_pBaseOnProcFile;

        ar << WORD(m_RequireFormFile);
        ar << WORD(m_RequireProcFile);
        ar << WORD(m_FormAttachmentType);
        ar << WORD(m_ProcessAttachmentType);
        ar << WORD(m_PreFormReadOnly);
        ar << WORD(m_PreProcReadOnly);

        // flag for pre-conditions
        ar << WORD(m_PreConditionsDone);

        // flag for post-conditions
        ar << WORD(m_PostConditionsDone);
    }
    else
    {
        if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 17)
            ar >> m_ActivityType;

        WORD wValue;

        ar >> m_RejectedToActivity;
        ar >> m_AttributedByActivity;

        // serialize the mail message pointer
        ar >> (CObject*&)m_pMailMessage;

        // serialize the command line object pointer
        ar >> (CObject*&)m_pCommandLine;

        // serialize the Form file manager
        ar >> (CObject*&)m_pBaseOnFormFile;

        // serialize the Process file manager
        ar >> (CObject*&)m_pBaseOnProcFile;

        ar >> wValue;
        m_RequireFormFile = EThreeState(wValue);

        ar >> wValue;
        m_RequireProcFile = EThreeState(wValue);

        ar >> wValue;
        m_FormAttachmentType = PSS_File::IEAttachmentType(wValue);

        ar >> wValue;
        m_ProcessAttachmentType = PSS_File::IEAttachmentType(wValue);

        ar >> wValue;
        m_PreFormReadOnly = BOOL(wValue);

        ar >> wValue;
        m_PreProcReadOnly = BOOL(wValue);

        // flag for pre-conditions
        ar >> wValue;
        m_PreConditionsDone = BOOL(wValue);
 
        // flag for post-conditions
        ar >> wValue;
        m_PostConditionsDone = BOOL(wValue);
    }

    // serialize the base forms and process and the template
    m_BaseFormNames.Serialize(ar);
    m_BaseProcNames.Serialize(ar);
    m_TemplateArray.Serialize(ar);
    GetProcessToStartArray().Serialize(ar);
}
//---------------------------------------------------------------------------
