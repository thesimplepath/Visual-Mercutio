//## begin module%3675496C018C.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%3675496C018C.cm

//## begin module%3675496C018C.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%3675496C018C.cp

//## Module: Activity%3675496C018C; Package body
//## Subsystem: ZEvent%378A5F7E02DB
//## Source file: z:\adsoft~1\ZEvent\Activity.cpp

//## begin module%3675496C018C.additionalIncludes preserve=no
//## end module%3675496C018C.additionalIncludes

//## begin module%3675496C018C.includes preserve=yes
#include <StdAfx.h>
//## end module%3675496C018C.includes

// Activity
#include "Activity.h"
//## begin module%3675496C018C.declarations preserve=no
//## end module%3675496C018C.declarations

//## begin module%3675496C018C.additionalDeclarations preserve=yes
#include "zBaseLib\BaseDoc.h"
#include "zRes32\ZRes.h"

#include "zBaseLib\ZMessage.h"
#include "zBaseLib\MsgBox.h"

#include "zBaseLib\ZBTokenizer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(ZActivity, ZBaseActivity, g_DefVersion)
//## end module%3675496C018C.additionalDeclarations


// Class ZActivity 




















ZActivity::ZActivity (const CString ActivityName, const CString ActivityDescription, int ActivityType, ActivityStatus ActivityStatus)
  //## begin ZActivity::ZActivity%915355672.hasinit preserve=no
      : m_pBaseOnFormFile(NULL), m_pBaseOnProcFile(NULL), m_RequireFormFile(E_TS_False), m_RequireProcFile(E_TS_False), m_FormAttachementType(InsertedFile), m_ProcessAttachementType(InsertedFile), m_PreConditionsDone(FALSE), m_PostConditionsDone(FALSE)
  //## end ZActivity::ZActivity%915355672.hasinit
  //## begin ZActivity::ZActivity%915355672.initialization preserve=yes
  , ZBaseActivity( ActivityName, ActivityDescription, ActivityStatus ),
    m_pMailMessage(NULL), m_pCommandLine(NULL),
    m_RejectedToActivity(RejectActivityToPrevious),
    m_PreFormReadOnly(FALSE), m_PreProcReadOnly(FALSE)
  //## end ZActivity::ZActivity%915355672.initialization
{
  //## begin ZActivity::ZActivity%915355672.body preserve=yes
    m_ActivityType = ActivityType;
  //## end ZActivity::ZActivity%915355672.body
}


ZActivity::~ZActivity()
{
  //## begin ZActivity::~ZActivity%.body preserve=yes
    if (m_pMailMessage)
        delete m_pMailMessage;
    m_pMailMessage = NULL;
    if (m_pCommandLine)
        delete m_pCommandLine;
    m_pCommandLine = NULL;

    if (m_pBaseOnFormFile)
        delete m_pBaseOnFormFile;
    m_pBaseOnFormFile = NULL;
    
    if (m_pBaseOnProcFile)
        delete m_pBaseOnProcFile;
    m_pBaseOnProcFile = NULL;
  //## end ZActivity::~ZActivity%.body
}



//## Other Operations (implementation)
void ZActivity::Serialize (CArchive& ar)
{
  //## begin ZActivity::Serialize%913664904.body preserve=yes
    ZBaseActivity::Serialize( ar );
    if (ar.IsStoring())
    {
          ar << m_RejectedToActivity;
        ar << m_AttributedByActivity;
        // Serialize the mail message pointer
        ar << m_pMailMessage;
        // Serialize the command line object pointer
        ar << m_pCommandLine;
        // Serialize the Form file manager
        ar << m_pBaseOnFormFile;
        // Serialize the Process file manager
        ar << m_pBaseOnProcFile;
        ar << (WORD)m_RequireFormFile;
        ar << (WORD)m_RequireProcFile;
        ar << (WORD)m_FormAttachementType;
        ar << (WORD)m_ProcessAttachementType;
        ar << (WORD)m_PreFormReadOnly;
        ar << (WORD)m_PreProcReadOnly;
        // Flag for pre-conditions
        ar << (WORD)m_PreConditionsDone;
        // Flag for post-conditions
        ar << (WORD)m_PostConditionsDone;

    }
    else
    {
        if (((ZDBaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() < 17)
        {
            ar >> m_ActivityType;
        }

        WORD    wValue;

        ar >> m_RejectedToActivity;
          
        ar >> m_AttributedByActivity;

        // Serialize the mail message pointer
        ar >> (CObject*&)m_pMailMessage;
        // Serialize the command line object pointer
        ar >> (CObject*&)m_pCommandLine;
        // Serialize the Form file manager
        ar >> (CObject*&)m_pBaseOnFormFile;
        // Serialize the Process file manager
        ar >> (CObject*&)m_pBaseOnProcFile;

        ar >> wValue;
        m_RequireFormFile = (EThreeState)wValue;
        ar >> wValue;
        m_RequireProcFile = (EThreeState)wValue;

        ar >> wValue;
        m_FormAttachementType = (AttachementType)wValue;
        ar >> wValue;
        m_ProcessAttachementType = (AttachementType)wValue;

        ar >> wValue;
        m_PreFormReadOnly = (BOOL)wValue;
        ar >> wValue;
        m_PreProcReadOnly = (BOOL)wValue;

        // Flag for pre-conditions
        ar >> wValue;
        m_PreConditionsDone = (BOOL)wValue;
        // Flag for post-conditions
        ar >> wValue;
        m_PostConditionsDone = (BOOL)wValue;

    }
    // Serialize the base forms and process and the template
    m_BaseFormNames.Serialize( ar );
    m_BaseProcNames.Serialize( ar );
    m_TemplateArray.Serialize( ar );
    GetProcessToStartArray().Serialize( ar );
  //## end ZActivity::Serialize%913664904.body
}

void ZActivity::AddTemplate (const CString& TemplateName)
{
  //## begin ZActivity::AddTemplate%913885063.body preserve=yes
      if (TemplateExist( TemplateName ))
          return;
    m_TemplateArray.Add( TemplateName );
  //## end ZActivity::AddTemplate%913885063.body
}

BOOL ZActivity::RemoveTemplate (const CString& TemplateName)
{
  //## begin ZActivity::RemoveTemplate%913885064.body preserve=yes
      for (size_t i = 0; i < GetTemplateCount(); ++i)
          if (GetTemplateAt(i) == TemplateName)
          {
              m_TemplateArray.RemoveAt(i);
              return TRUE;
          }
      return FALSE;
  //## end ZActivity::RemoveTemplate%913885064.body
}

BOOL ZActivity::TemplateExist (const CString& TemplateName)
{
  //## begin ZActivity::TemplateExist%913885068.body preserve=yes
      for (size_t i = 0; i < GetTemplateCount(); ++i)
          if (GetTemplateAt(i) == TemplateName)
              return TRUE;
      return FALSE;
  //## end ZActivity::TemplateExist%913885068.body
}

CString ZActivity::BuildTemplateListString (const char SeparatorChar /*= ';'*/)
{
    ZBTokenizer    Tokenizer(SeparatorChar);
      for (size_t i = 0; i < GetTemplateCount(); ++i)
          Tokenizer.AddToken(GetTemplateAt(i));
      return Tokenizer.GetString();
}

CString ZActivity::GetDefaultString ()
{
  //## begin ZActivity::GetDefaultString%915355671.body preserve=yes
    CString    Line = "Activité:" + GetName();
//    if (GetIsVisible())
//    {
//        Line += " désactivée";
//    }
    Line += GetActivityStatusString();
    if (GetActivityStatus() != ActivityNotStarted)
    {
        Line += " Démarré le: ";

        char buf[30];
        sprintf_s(buf, _tcslen(buf), "%d.%d.%d", GetStartDate().GetDay(), GetStartDate().GetMonth(), GetStartDate().GetYear());

        Line += buf;
    }
    return Line;
  //## end ZActivity::GetDefaultString%915355671.body
}

BOOL ZActivity::ActivityFillPersonArray (ZUUserManager& UserManager, CStringArray& UserArray, CString ConnectedUser)
{
  //## begin ZActivity::ActivityFillPersonArray%927439013.body preserve=yes
    return GetCurrentResources().FillPersonArray( GetMainProcess(), UserManager, UserArray, ConnectedUser );
  //## end ZActivity::ActivityFillPersonArray%927439013.body
}

ZUMailUserList* ZActivity::ActivityCreatePersonList (ZUUserManager& UserManager, CString ConnectedUser)
{
  //## begin ZActivity::ActivityCreatePersonList%927439012.body preserve=yes
    return GetCurrentResources().CreatePersonList( GetMainProcess(), UserManager, ConnectedUser );
  //## end ZActivity::ActivityCreatePersonList%927439012.body
}

CString ZActivity::ActivityCreatePersonDelimStr (ZUUserManager& UserManager, CString ConnectedUser, CString Delimiter)
{
  //## begin ZActivity::ActivityCreatePersonDelimStr%927439014.body preserve=yes
    return GetCurrentResources().CreatePersonDelimStr( GetMainProcess(), UserManager, ConnectedUser, Delimiter );
  //## end ZActivity::ActivityCreatePersonDelimStr%927439014.body
}

void ZActivity::DeleteEMailToSend ()
{
  //## begin ZActivity::DeleteEMailToSend%928085166.body preserve=yes
    if (m_pMailMessage)
        delete m_pMailMessage;
    m_pMailMessage = NULL;
    SetActivityAsSendMail( FALSE );
  //## end ZActivity::DeleteEMailToSend%928085166.body
}

void ZActivity::DeleteCommandLine ()
{
  //## begin ZActivity::DeleteCommandLine%928085171.body preserve=yes
    if (m_pCommandLine)
        delete m_pCommandLine;
    m_pCommandLine = NULL;
    SetActivityAsCommandLine( FALSE );
  //## end ZActivity::DeleteCommandLine%928085171.body
}

void ZActivity::CalculateForecastedEndDate ()
{
  //## begin ZActivity::CalculateForecastedEndDate%929033121.body preserve=yes
    // Sets the forecasted end date 
    // by adding the duration to the start date
#ifdef _WIN32    // In 32bit
    if (GetStartDate() > 0)
        SetForecastedEndDate( GetStartDate() + COleDateTimeSpan(GetDurationDays()) );
    else
        SetForecastedEndDate( GetForecastedStartDate() + COleDateTimeSpan(GetDurationDays()) );
#endif
#ifndef _WIN32    // In 16bit
    if (GetStartDate() > 0)
        SetForecastedEndDate( GetStartDate() + CTimeSpan(GetDurationDays()) );
    else
        SetForecastedEndDate( GetForecastedStartDate() + CTimeSpan(GetDurationDays()) );
#endif
  //## end ZActivity::CalculateForecastedEndDate%929033121.body
}

void ZActivity::CalculateForecastedStartDate ()
{
  //## begin ZActivity::CalculateForecastedStartDate%931585007.body preserve=yes
  //## end ZActivity::CalculateForecastedStartDate%931585007.body
}

BOOL ZActivity::AddFormFile (CString FileName, AttachementType Attachement)
{
  //## begin ZActivity::AddFormFile%933697291.body preserve=yes
    if (!m_pBaseOnFormFile)
        m_pBaseOnFormFile = new ZFileManager;
    m_pBaseOnFormFile->AddFile( FileName, Attachement );
    return m_pBaseOnFormFile->GetCount() > 0;
  //## end ZActivity::AddFormFile%933697291.body
}

BOOL ZActivity::AddFormFiles (CStringArray& FileNameArray, AttachementType Attachement)
{
  //## begin ZActivity::AddFormFiles%933697292.body preserve=yes
    if (!m_pBaseOnFormFile)
        m_pBaseOnFormFile = new ZFileManager;
    for (int i = 0; i < FileNameArray.GetSize(); ++i)
        m_pBaseOnFormFile->AddFile( FileNameArray.GetAt(i), Attachement );
    return m_pBaseOnFormFile->GetCount() > 0;
  //## end ZActivity::AddFormFiles%933697292.body
}

BOOL ZActivity::RemoveAllFormFiles ()
{
  //## begin ZActivity::RemoveAllFormFiles%933697293.body preserve=yes
    if (m_pBaseOnFormFile)
        delete m_pBaseOnFormFile;
    m_pBaseOnFormFile = NULL;
    return TRUE;
  //## end ZActivity::RemoveAllFormFiles%933697293.body
}

BOOL ZActivity::AddProcFile (CString FileName, AttachementType Attachement)
{
  //## begin ZActivity::AddProcFile%933697294.body preserve=yes
    if (!m_pBaseOnProcFile)
        m_pBaseOnProcFile = new ZFileManager;
    m_pBaseOnProcFile->AddFile( FileName, Attachement );
    return m_pBaseOnProcFile->GetCount() > 0;
  //## end ZActivity::AddProcFile%933697294.body
}

BOOL ZActivity::AddProcFiles (CStringArray& FileNameArray, AttachementType Attachement)
{
  //## begin ZActivity::AddProcFiles%933697295.body preserve=yes
    if (!m_pBaseOnProcFile)
        m_pBaseOnProcFile = new ZFileManager;
    for (int i = 0; i < FileNameArray.GetSize(); ++i)
        m_pBaseOnProcFile->AddFile( FileNameArray.GetAt(i), Attachement );
    return m_pBaseOnProcFile->GetCount() > 0;
  //## end ZActivity::AddProcFiles%933697295.body
}

BOOL ZActivity::RemoveAllProcFiles ()
{
  //## begin ZActivity::RemoveAllProcFiles%933697296.body preserve=yes
    if (m_pBaseOnProcFile)
        delete m_pBaseOnProcFile;
    m_pBaseOnProcFile = NULL;
    return TRUE;
  //## end ZActivity::RemoveAllProcFiles%933697296.body
}

size_t ZActivity::GetFormFileCount () const
{
  //## begin ZActivity::GetFormFileCount%933795322.body preserve=yes
    if (m_pBaseOnFormFile)
        return m_pBaseOnFormFile->GetCount();
    return 0;
  //## end ZActivity::GetFormFileCount%933795322.body
}

size_t ZActivity::GetProcFileCount () const
{
  //## begin ZActivity::GetProcFileCount%933795323.body preserve=yes
    if (m_pBaseOnProcFile)
        return m_pBaseOnProcFile->GetCount();
    return 0;
  //## end ZActivity::GetProcFileCount%933795323.body
}

ZFile* ZActivity::GetFormFileAt (size_t Index)
{
  //## begin ZActivity::GetFormFileAt%933795324.body preserve=yes
    if (Index < GetFormFileCount())
        return m_pBaseOnFormFile->GetAt( Index );
    return NULL;
  //## end ZActivity::GetFormFileAt%933795324.body
}

ZFile* ZActivity::GetProcFileAt (size_t Index)
{
  //## begin ZActivity::GetProcFileAt%933795325.body preserve=yes
    if (Index < GetProcFileCount())
        return m_pBaseOnProcFile->GetAt( Index );
    return NULL;
  //## end ZActivity::GetProcFileAt%933795325.body
}

// Additional Declarations
  //## begin ZActivity%36725B6400FF.declarations preserve=yes
  //## end ZActivity%36725B6400FF.declarations

//## begin module%3675496C018C.epilog preserve=yes
void ZActivity::DeleteProcessToStart()
{
    m_ProcessToStartArray.RemoveAll();
    SetActivityAsStartProcess ( FALSE );
}

void ZActivity::DeleteBaseOnFormFile()
{
    RemoveAllFormFiles();
    SetRequireFormFile(E_TS_False);
    SetFormAttachementType( InsertedFile );
    SetPreFormReadOnly( TRUE );
}

void ZActivity::DeleteBaseOnProcFile()
{
    RemoveAllProcFiles();
    SetRequireProcFile(E_TS_False);
    SetProcessAttachementType( InsertedFile );
    SetPreProcReadOnly( TRUE );
}

void ZActivity::SetDefaultProperty()
{
    // Call the base class function first
    ZBaseActivity::SetDefaultProperty();


    RemoveAllTemplates();

    DeleteEMailToSend ();
    DeleteCommandLine ();
    DeleteProcessToStart();

    SetActivityAsInput ( FALSE );
    SetActivityAsScanning ( FALSE );
    SetActivityAsArchiving ( FALSE );


    DeleteBaseOnFormFile();
    DeleteBaseOnProcFile();

}


CString ZActivity::GetActivityTypeKeyString ()
{
    ZBTokenizer    Tokenizer( ';' );

    if (ActivityIsAttribution())
        Tokenizer.AddToken( ActivityTypeAttributionKey );

    if (ActivityIsAcceptation())
        Tokenizer.AddToken( ActivityTypeAcceptationKey );

    if (ActivityIsInput())
        Tokenizer.AddToken( ActivityTypeInputInformationKey );

    if (ActivityIsSendMail())
        Tokenizer.AddToken( ActivityTypeSendMailKey );

    if (ActivityIsStartProcess())
        Tokenizer.AddToken( ActivityTypeStartProcessKey );

    if (ActivityIsCommandLine())
        Tokenizer.AddToken( ActivityTypeCommandLineKey );

    if (ActivityIsScanning())
        Tokenizer.AddToken( ActivityTypeScanningKey );

    if (ActivityIsArchiving())
        Tokenizer.AddToken( ActivityTypeArchivingKey );

    return Tokenizer.GetString();
}

void ZActivity::SetActivityTypeFromKeyString ( const CString KeyString )
{
    ZBTokenizer    Tokenizer( ';' );
    // Run through key string
    CString    Token = Tokenizer.GetFirstToken( KeyString );
    while (!Token.IsEmpty())
    {
        // if we found the user, return true
        if (Token == ActivityTypeAttributionKey)
            SetActivityAsAttribution();
        else
        if (Token == ActivityTypeAcceptationKey)
            SetActivityAsAcceptation();
        else
        if (Token == ActivityTypeInputInformationKey)
            SetActivityAsInput();
        else
        if (Token == ActivityTypeSendMailKey)
            SetActivityAsSendMail();
        else
        if (Token == ActivityTypeStartProcessKey)
            SetActivityAsStartProcess();
        else
        if (Token == ActivityTypeCommandLineKey)
            SetActivityAsCommandLine();
        else
        if (Token == ActivityTypeScanningKey)
            SetActivityAsScanning();
        else
        if (Token == ActivityTypeArchivingKey)
            SetActivityAsArchiving();
        // If not recognized, do noting

        // Get next token
        Token = Tokenizer.GetNextToken();
    }
}

//## end module%3675496C018C.epilog
