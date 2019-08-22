//## begin module%36754981018C.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%36754981018C.cm

//## begin module%36754981018C.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%36754981018C.cp

//## Module: Activity%36754981018C; Package specification
//## Subsystem: ZEvent%378A5F7E02DB
//## Source file: z:\adsoft~1\ZEvent\Activity.h

#ifndef Activity_h
#define Activity_h 1

//## begin module%36754981018C.additionalIncludes preserve=no
//## end module%36754981018C.additionalIncludes

//## begin module%36754981018C.includes preserve=yes

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_FileManager.h"
#include "zBaseLib\PSS_MailMessage.h"
#include "zBaseLib\PSS_CommandLine.h"
#include "BActvt.h"

const char RejectActivityToPrevious[] = "/P";

#ifdef _ZEVENTEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//## Class: ZActivity%36725B6400FF
//    Implements an activity.
//## Category: ZEvent::Process Classes - Event%378A5FD903A4
//## Subsystem: ZEvent%378A5F7E02DB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%374C3AD5015D; { -> }
//## Uses: <unnamed>%37500DF5033D;ZBMailMessage { -> }
//## Uses: <unnamed>%3751A3A00060;ZUCommandLine { -> }

class AFX_EXT_CLASS ZActivity : public ZBaseActivity  //## Inherits: <unnamed>%3786DA820224
{
  //## begin ZActivity%36725B6400FF.initialDeclarations preserve=yes
public:
// Inherited feature
    typedef ZBaseActivity inherited;
    DECLARE_SERIAL(ZActivity)
  //## end ZActivity%36725B6400FF.initialDeclarations

  public:
    //## Constructors (specified)
      //## Operation: ZActivity%915355672
      //    The default constructor.
      ZActivity (const CString ActivityName = "", const CString ActivityDescription = "", int ActivityType = ActivityTypeInputInformation, ActivityStatus ActivityStatus = ActivityNotStarted);

    //## Destructor (generated)
      ~ZActivity();


    //## Other Operations (specified)
      //## Operation: Serialize%913664904
      //    Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: AddTemplate%913885063
      //    Add a new template name.
      void AddTemplate (const CString& TemplateName);

      //## Operation: RemoveTemplate%913885064
      //    Remove an existing template name.
      BOOL RemoveTemplate (const CString& TemplateName);

      //## Operation: RemoveAllTemplates%913885065
      //    Remove all existing templates.
      void RemoveAllTemplates ();

      //## Operation: GetTemplateCount%913885066
      //    Return the number of templates.
      size_t GetTemplateCount ();

      //## Operation: GetTemplateAt%913885067
      //    Returns the template name at the index position.
      CString GetTemplateAt (int Index);

      //## Operation: TemplateExist%913885068
      //    Search if a specific template name exists.
      BOOL TemplateExist (const CString& TemplateName);

      CString BuildTemplateListString (const char SeparatorChar = ';');

      //## Operation: GetDefaultString%915355671
      //    Return the activity on string shape.
      CString GetDefaultString ();

      //## Operation: SetActivityAsAttribution%927367541
      //    Sets the activity type for attribution. Default value is
      //    true
      void SetActivityAsAttribution (BOOL value = TRUE);

      //## Operation: SetActivityAsAcceptation%927367542
      //    Sets the activity type for acceptation. Default value is
      //    true
      void SetActivityAsAcceptation (BOOL value = TRUE);

      //## Operation: SetActivityAsInput%927367543
      //    Sets the activity type for input. Default value is true
      void SetActivityAsInput (BOOL value = TRUE);

      //## Operation: SetActivityAsSendMail%927742744
      //    Sets the activity type for send mail. Default value is
      //    true
      void SetActivityAsSendMail (BOOL value = TRUE);

      //## Operation: SetActivityAsStartProcess%927742745
      //    Sets the activity type for start process. Default value
      //    is true
      void SetActivityAsStartProcess (BOOL value = TRUE);

      //## Operation: SetActivityAsCommandLine%927742746
      //    Sets the activity type for command line. Default value
      //    is true
      void SetActivityAsCommandLine (BOOL value = TRUE);

      //## Operation: SetActivityAsScanning%940156899
      //    Sets the activity type for scanning. Default value is
      //    true
      void SetActivityAsScanning (BOOL value = TRUE);

      //## Operation: SetActivityAsArchiving%940156900
      //    Sets the activity type for archaving. Default value is
      //    true
      void SetActivityAsArchiving (BOOL value = TRUE);

      //## Operation: ActivityFillPersonArray%927439013
      //    Take the activity and fill a person array.
      virtual BOOL ActivityFillPersonArray (ZUUserManager& UserManager, CStringArray& UserArray, CString ConnectedUser);

      //## Operation: ActivityCreatePersonList%927439012
      //    Take the activity and build the person list for the
      //    email.
      virtual ZUMailUserList* ActivityCreatePersonList (ZUUserManager& UserManager, CString ConnectedUser);

      //## Operation: ActivityCreatePersonDelimStr%927439014
      //    Take the activity and build a delimited string
      //    containing the person list.
      virtual CString ActivityCreatePersonDelimStr (ZUUserManager& UserManager, CString ConnectedUser, CString Delimiter = ";");

      //## Operation: IsAttributedActivity%927535109
      //    Returns true if the activity is an attributed activity.
      virtual BOOL IsAttributedActivity () const;

      //## Operation: DeleteEMailToSend%928085166
      //    Delete the pointer used to send email.
      void DeleteEMailToSend ();

      //## Operation: DeleteCommandLine%928085171
      //    Delete the command line object pointer.
      void DeleteCommandLine ();

      //## Operation: CalculateForecastedEndDate%929033121
      //    This function calculates the forecasted end date by
      //    taking all activities.
      virtual void CalculateForecastedEndDate ();

      //## Operation: CalculateForecastedStartDate%931585007
      //    This function calculates the forecasted start date by
      //    taking all activities.
      virtual void CalculateForecastedStartDate ();

      //## Operation: GetAttributedByActivity%931585034
      virtual CString GetAttributedByActivity () const;

      //## Operation: SetAttributedByActivity%931585035
      virtual void SetAttributedByActivity (const CString value = "");

      //## Operation: AddFormFile%933697291
      //    Add a filename
      BOOL AddFormFile (CString FileName, PSS_File::IEAttachementType Attachement = PSS_File::IE_AT_InsertedFile);

      //## Operation: AddFormFiles%933697292
      //    Add several filenames
      BOOL AddFormFiles (CStringArray& FileNameArray, PSS_File::IEAttachementType Attachement = PSS_File::IE_AT_InsertedFile);

      //## Operation: RemoveAllFormFiles%933697293
      //    Remove all filenames
      BOOL RemoveAllFormFiles ();

      //## Operation: AddProcFile%933697294
      //    Add a filename
      BOOL AddProcFile (CString FileName, PSS_File::IEAttachementType Attachement = PSS_File::IE_AT_InsertedFile);

      //## Operation: AddProcFiles%933697295
      //    Add several filenames
      BOOL AddProcFiles (CStringArray& FileNameArray, PSS_File::IEAttachementType Attachement = PSS_File::IE_AT_InsertedFile);

      //## Operation: RemoveAllProcFiles%933697296
      //    Remove all filenames
      BOOL RemoveAllProcFiles ();

      //## Operation: GetFormFileCount%933795322
      //    return the number of form files.
      size_t GetFormFileCount () const;

      //## Operation: GetProcFileCount%933795323
      //    return the number of process file.
      size_t GetProcFileCount () const;

      //## Operation: GetFormFileAt%933795324
      //    Return the ZFile pointer at the specified position.
      PSS_File* GetFormFileAt (size_t Index);

      //## Operation: GetProcFileAt%933795325
      //    Return the ZFile pointer at the specified position.
      PSS_File* GetProcFileAt (size_t Index);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: RejectedToActivity%369A28FD01B8
      //    It gives the possibility to reject an activity to
      //    another activity. By default RejectActivityToPrevious,
      //    it is rejected to the sender.
      const CString GetRejectedToActivity () const;
      void SetRejectedToActivity (CString value);

      //## Attribute: pMailMessage%37500DB1008C
      //    Contains the pointer to mail message.
      PSS_MailMessage* GetpMailMessage ();
      void SetpMailMessage (PSS_MailMessage* value);

      //## Attribute: pCommandLine%3751A33D032F
      //    A pointer to the command line.
      PSS_CommandLine* GetpCommandLine ();
      void SetpCommandLine(PSS_CommandLine* value);

      //## Attribute: ProcessToStartArray%378B91690060
      //    Contains the array of process to start
      CStringArray& GetProcessToStartArray ();

      //## Attribute: RequireFormFile%37A09D4C03E5
      //    Defines if when the process starts, a form file is
      //    necessary before starting the activity.
      const EThreeState GetRequireFormFile () const;
      void SetRequireFormFile (EThreeState value);

      //## Attribute: RequireProcFile%37A09D4D0057
      //    Defines if when the process starts, a process file is
      //    necessary before starting the activity.
      const EThreeState GetRequireProcFile () const;
      void SetRequireProcFile (EThreeState value);

      //## Attribute: BaseFormNames%37A2A42C031D
      //    Contains the optional form name.
      CStringArray& GetBaseFormNames ();

      //## Attribute: BaseProcNames%37A2A4770325
      //    Contains the optional process name.
      CStringArray& GetBaseProcNames ();

      //## Attribute: FormAttachementType%37A3F0550153
      //    Defines the form attachement type.
      const PSS_File::IEAttachementType GetFormAttachementType () const;
      void SetFormAttachementType (PSS_File::IEAttachementType value);

      //## Attribute: ProcessAttachementType%37A3F0780262
      //    Defines the process attachement type.
      const PSS_File::IEAttachementType GetProcessAttachementType () const;
      void SetProcessAttachementType (PSS_File::IEAttachementType value);

      //## Attribute: PreConditionsDone%37A400820139
      //    Flag for preconditions. TRUE if already completed.
      const BOOL GetPreConditionsDone () const;
      void SetPreConditionsDone (BOOL value);

      //## Attribute: PostConditionsDone%37A400AB0373
      //    Flag for postconditions. TRUE if already completed.
      const BOOL GetPostConditionsDone () const;
      void SetPostConditionsDone (BOOL value);

      //## Attribute: PreFormReadOnly%37D0EC23021E
      //    Defines if for pre-conditions, the form import must be
      //    set as read-only.
      const BOOL GetPreFormReadOnly () const;
      void SetPreFormReadOnly (BOOL value);

      //## Attribute: PreProcReadOnly%37D0EC5D01EF
      //    Defines if for pre-conditions, the process import must
      //    be set as read-only.
      const BOOL GetPreProcReadOnly () const;
      void SetPreProcReadOnly (BOOL value);

    // Additional Public Declarations
      //## begin ZActivity%36725B6400FF.public preserve=yes
      virtual void    SetDefaultProperty();
      CString GetActivityTypeKeyString();
      void      SetActivityTypeFromKeyString( const CString KeyString );
      //    Delete process to start
      void DeleteProcessToStart();
      //    Delete based on form file
      void DeleteBaseOnFormFile();
      //    Delete based on process file
      void DeleteBaseOnProcFile();

      //## end ZActivity%36725B6400FF.public
  protected:
    // Data Members for Class Attributes

      //## begin ZActivity::ProcessToStartArray%378B91690060.attr preserve=no  public: CStringArray {U} 
      CStringArray m_ProcessToStartArray;
      //## end ZActivity::ProcessToStartArray%378B91690060.attr

      //## begin ZActivity::BaseFormNames%37A2A42C031D.attr preserve=no  public: CStringArray {U} 
      CStringArray m_BaseFormNames;
      //## end ZActivity::BaseFormNames%37A2A42C031D.attr

      //## begin ZActivity::BaseProcNames%37A2A4770325.attr preserve=no  public: CStringArray {U} 
      CStringArray m_BaseProcNames;
      //## end ZActivity::BaseProcNames%37A2A4770325.attr

    // Additional Protected Declarations
      //## begin ZActivity%36725B6400FF.protected preserve=yes
      //## end ZActivity%36725B6400FF.protected

  private:
    //## Constructors (generated)
      ZActivity(const ZActivity& other);

    //## Assignment Operation (generated)
      const ZActivity& operator = (const ZActivity& other);

    // Data Members for Class Attributes

      //## begin ZActivity::RejectedToActivity%369A28FD01B8.attr preserve=no  public: CString {U} 
      CString m_RejectedToActivity;
      //## end ZActivity::RejectedToActivity%369A28FD01B8.attr

      //## Attribute: TemplateArray%3678C5C300A9
      //    The list of templates.
      //## begin ZActivity::TemplateArray%3678C5C300A9.attr preserve=no  public: CStringArray {V} 
      CStringArray m_TemplateArray;
      //## end ZActivity::TemplateArray%3678C5C300A9.attr

      //## Attribute: AttributedByActivity%374687E20108
      //## begin ZActivity::AttributedByActivity%374687E20108.attr preserve=no  public: CString {U} 
      CString m_AttributedByActivity;
      //## end ZActivity::AttributedByActivity%374687E20108.attr

      //## begin ZActivity::pMailMessage%37500DB1008C.attr preserve=no  public: ZBMailMessage* {U} 
      PSS_MailMessage* m_pMailMessage;
      //## end ZActivity::pMailMessage%37500DB1008C.attr

      //## begin ZActivity::pCommandLine%3751A33D032F.attr preserve=no  public: ZUCommandLine* {U} 
      PSS_CommandLine* m_pCommandLine;
      //## end ZActivity::pCommandLine%3751A33D032F.attr

      //## Attribute: pBaseOnFormFile%37A09D4C031D
      //    The pointer to the file manager of form files.
      //## begin ZActivity::pBaseOnFormFile%37A09D4C031D.attr preserve=no  public: ZFileManager* {U} NULL
      PSS_FileManager* m_pBaseOnFormFile;
      //## end ZActivity::pBaseOnFormFile%37A09D4C031D.attr

      //## Attribute: pBaseOnProcFile%37A09D4C0381
      //    The pointer to the file manager of processus files.
      //## begin ZActivity::pBaseOnProcFile%37A09D4C0381.attr preserve=no  public: ZFileManager* {U} NULL
      PSS_FileManager* m_pBaseOnProcFile;
      //## end ZActivity::pBaseOnProcFile%37A09D4C0381.attr

      //## begin ZActivity::RequireFormFile%37A09D4C03E5.attr preserve=no  public: ThreeState {U} FalseState
      EThreeState m_RequireFormFile;
      //## end ZActivity::RequireFormFile%37A09D4C03E5.attr

      //## begin ZActivity::RequireProcFile%37A09D4D0057.attr preserve=no  public: ThreeState {U} FalseState
      EThreeState m_RequireProcFile;
      //## end ZActivity::RequireProcFile%37A09D4D0057.attr

      //## begin ZActivity::FormAttachementType%37A3F0550153.attr preserve=no  public: AttachementType {U} InsertedFile
      PSS_File::IEAttachementType m_FormAttachementType;
      //## end ZActivity::FormAttachementType%37A3F0550153.attr

      //## begin ZActivity::ProcessAttachementType%37A3F0780262.attr preserve=no  public: AttachementType {U} InsertedFile
      PSS_File::IEAttachementType m_ProcessAttachementType;
      //## end ZActivity::ProcessAttachementType%37A3F0780262.attr

      //## begin ZActivity::PreConditionsDone%37A400820139.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_PreConditionsDone;
      //## end ZActivity::PreConditionsDone%37A400820139.attr

      //## begin ZActivity::PostConditionsDone%37A400AB0373.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_PostConditionsDone;
      //## end ZActivity::PostConditionsDone%37A400AB0373.attr

      //## begin ZActivity::PreFormReadOnly%37D0EC23021E.attr preserve=no  public: BOOL {U} 
      BOOL m_PreFormReadOnly;
      //## end ZActivity::PreFormReadOnly%37D0EC23021E.attr

      //## begin ZActivity::PreProcReadOnly%37D0EC5D01EF.attr preserve=no  public: BOOL {U} 
      BOOL m_PreProcReadOnly;
      //## end ZActivity::PreProcReadOnly%37D0EC5D01EF.attr

    // Additional Private Declarations
      //## begin ZActivity%36725B6400FF.private preserve=yes
      //## end ZActivity%36725B6400FF.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZActivity%36725B6400FF.implementation preserve=yes
      //## end ZActivity%36725B6400FF.implementation

};

//## begin ZActivity%36725B6400FF.postscript preserve=yes
//#undef  AFX_DATA
//#define AFX_DATA
//## end ZActivity%36725B6400FF.postscript

// Class ZActivity 


//## Other Operations (inline)
inline void ZActivity::RemoveAllTemplates ()
{
  //## begin ZActivity::RemoveAllTemplates%913885065.body preserve=yes
      m_TemplateArray.RemoveAll();
  //## end ZActivity::RemoveAllTemplates%913885065.body
}

inline size_t ZActivity::GetTemplateCount ()
{
  //## begin ZActivity::GetTemplateCount%913885066.body preserve=yes
      return m_TemplateArray.GetSize();
  //## end ZActivity::GetTemplateCount%913885066.body
}

inline CString ZActivity::GetTemplateAt (int Index)
{
  //## begin ZActivity::GetTemplateAt%913885067.body preserve=yes
      return m_TemplateArray.GetAt( Index );
  //## end ZActivity::GetTemplateAt%913885067.body
}

inline void ZActivity::SetActivityAsAttribution (BOOL value)
{
  //## begin ZActivity::SetActivityAsAttribution%927367541.body preserve=yes
    if (value)
        m_ActivityType |= ActivityTypeAttribution;
    else
        m_ActivityType &= ~ActivityTypeAttribution;
  //## end ZActivity::SetActivityAsAttribution%927367541.body
}

inline void ZActivity::SetActivityAsAcceptation (BOOL value)
{
  //## begin ZActivity::SetActivityAsAcceptation%927367542.body preserve=yes
    if (value)
        m_ActivityType |= ActivityTypeAcceptation;
    else
        m_ActivityType &= ~ActivityTypeAcceptation;
  //## end ZActivity::SetActivityAsAcceptation%927367542.body
}

inline void ZActivity::SetActivityAsInput (BOOL value)
{
  //## begin ZActivity::SetActivityAsInput%927367543.body preserve=yes
    if (value)
        m_ActivityType |= ActivityTypeInputInformation;
    else
        m_ActivityType &= ~ActivityTypeInputInformation;
  //## end ZActivity::SetActivityAsInput%927367543.body
}

inline void ZActivity::SetActivityAsSendMail (BOOL value)
{
  //## begin ZActivity::SetActivityAsSendMail%927742744.body preserve=yes
    if (value)
        m_ActivityType |= ActivityTypeSendMail;
    else
        m_ActivityType &= ~ActivityTypeSendMail;
  //## end ZActivity::SetActivityAsSendMail%927742744.body
}

inline void ZActivity::SetActivityAsStartProcess (BOOL value)
{
  //## begin ZActivity::SetActivityAsStartProcess%927742745.body preserve=yes
    if (value)
        m_ActivityType |= ActivityTypeStartProcess;
    else
        m_ActivityType &= ~ActivityTypeStartProcess;
  //## end ZActivity::SetActivityAsStartProcess%927742745.body
}

inline void ZActivity::SetActivityAsCommandLine (BOOL value)
{
  //## begin ZActivity::SetActivityAsCommandLine%927742746.body preserve=yes
    if (value)
        m_ActivityType |= ActivityTypeCommandLine;
    else
        m_ActivityType &= ~ActivityTypeCommandLine;
  //## end ZActivity::SetActivityAsCommandLine%927742746.body
}

inline void ZActivity::SetActivityAsScanning (BOOL value)
{
  //## begin ZActivity::SetActivityAsScanning%940156899.body preserve=yes
    if (value)
        m_ActivityType |= ActivityTypeScanning;
    else
        m_ActivityType &= ~ActivityTypeScanning;
  //## end ZActivity::SetActivityAsScanning%940156899.body
}

inline void ZActivity::SetActivityAsArchiving (BOOL value)
{
  //## begin ZActivity::SetActivityAsArchiving%940156900.body preserve=yes
    if (value)
        m_ActivityType |= ActivityTypeArchiving;
    else
        m_ActivityType &= ~ActivityTypeArchiving;
  //## end ZActivity::SetActivityAsArchiving%940156900.body
}

inline BOOL ZActivity::IsAttributedActivity () const
{
  //## begin ZActivity::IsAttributedActivity%927535109.body preserve=yes
    return    GetVisibilityType() == AttributionOfVisibility ||
            m_PrincipalResources.GetUserType() == AttributionOfUsers ||
            m_BackupResources.GetUserType() == AttributionOfUsers ||
            GetTimeType() == AttributionOfTimeOut;
  //## end ZActivity::IsAttributedActivity%927535109.body
}

inline CString ZActivity::GetAttributedByActivity () const
{
  //## begin ZActivity::GetAttributedByActivity%931585034.body preserve=yes
    return m_AttributedByActivity;
  //## end ZActivity::GetAttributedByActivity%931585034.body
}

inline void ZActivity::SetAttributedByActivity (const CString value)
{
  //## begin ZActivity::SetAttributedByActivity%931585035.body preserve=yes
    m_AttributedByActivity = value;
  //## end ZActivity::SetAttributedByActivity%931585035.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const CString ZActivity::GetRejectedToActivity () const
{
  //## begin ZActivity::GetRejectedToActivity%369A28FD01B8.get preserve=no
  return m_RejectedToActivity;
  //## end ZActivity::GetRejectedToActivity%369A28FD01B8.get
}

inline void ZActivity::SetRejectedToActivity (CString value)
{
  //## begin ZActivity::SetRejectedToActivity%369A28FD01B8.set preserve=no
  m_RejectedToActivity = value;
  //## end ZActivity::SetRejectedToActivity%369A28FD01B8.set
}

inline PSS_MailMessage* ZActivity::GetpMailMessage ()
{
  //## begin ZActivity::GetpMailMessage%37500DB1008C.get preserve=no
  return m_pMailMessage;
  //## end ZActivity::GetpMailMessage%37500DB1008C.get
}

inline void ZActivity::SetpMailMessage (PSS_MailMessage* value)
{
  //## begin ZActivity::SetpMailMessage%37500DB1008C.set preserve=no
  m_pMailMessage = value;
  //## end ZActivity::SetpMailMessage%37500DB1008C.set
}

inline PSS_CommandLine* ZActivity::GetpCommandLine()
{
    return m_pCommandLine;
}

inline void ZActivity::SetpCommandLine(PSS_CommandLine* value)
{
    m_pCommandLine = value;
}

inline CStringArray& ZActivity::GetProcessToStartArray ()
{
  //## begin ZActivity::GetProcessToStartArray%378B91690060.get preserve=no
  return m_ProcessToStartArray;
  //## end ZActivity::GetProcessToStartArray%378B91690060.get
}

inline const EThreeState ZActivity::GetRequireFormFile () const
{
  //## begin ZActivity::GetRequireFormFile%37A09D4C03E5.get preserve=no
  return m_RequireFormFile;
  //## end ZActivity::GetRequireFormFile%37A09D4C03E5.get
}

inline void ZActivity::SetRequireFormFile (EThreeState value)
{
  //## begin ZActivity::SetRequireFormFile%37A09D4C03E5.set preserve=no
  m_RequireFormFile = value;
  //## end ZActivity::SetRequireFormFile%37A09D4C03E5.set
}

inline const EThreeState ZActivity::GetRequireProcFile () const
{
  //## begin ZActivity::GetRequireProcFile%37A09D4D0057.get preserve=no
  return m_RequireProcFile;
  //## end ZActivity::GetRequireProcFile%37A09D4D0057.get
}

inline void ZActivity::SetRequireProcFile (EThreeState value)
{
  //## begin ZActivity::SetRequireProcFile%37A09D4D0057.set preserve=no
  m_RequireProcFile = value;
  //## end ZActivity::SetRequireProcFile%37A09D4D0057.set
}

inline CStringArray& ZActivity::GetBaseFormNames ()
{
  //## begin ZActivity::GetBaseFormNames%37A2A42C031D.get preserve=no
  return m_BaseFormNames;
  //## end ZActivity::GetBaseFormNames%37A2A42C031D.get
}

inline CStringArray& ZActivity::GetBaseProcNames ()
{
  //## begin ZActivity::GetBaseProcNames%37A2A4770325.get preserve=no
  return m_BaseProcNames;
  //## end ZActivity::GetBaseProcNames%37A2A4770325.get
}

inline const PSS_File::IEAttachementType ZActivity::GetFormAttachementType () const
{
  //## begin ZActivity::GetFormAttachementType%37A3F0550153.get preserve=no
  return m_FormAttachementType;
  //## end ZActivity::GetFormAttachementType%37A3F0550153.get
}

inline void ZActivity::SetFormAttachementType (PSS_File::IEAttachementType value)
{
  //## begin ZActivity::SetFormAttachementType%37A3F0550153.set preserve=no
  m_FormAttachementType = value;
  //## end ZActivity::SetFormAttachementType%37A3F0550153.set
}

inline const PSS_File::IEAttachementType ZActivity::GetProcessAttachementType () const
{
  //## begin ZActivity::GetProcessAttachementType%37A3F0780262.get preserve=no
  return m_ProcessAttachementType;
  //## end ZActivity::GetProcessAttachementType%37A3F0780262.get
}

inline void ZActivity::SetProcessAttachementType (PSS_File::IEAttachementType value)
{
  //## begin ZActivity::SetProcessAttachementType%37A3F0780262.set preserve=no
  m_ProcessAttachementType = value;
  //## end ZActivity::SetProcessAttachementType%37A3F0780262.set
}

inline const BOOL ZActivity::GetPreConditionsDone () const
{
  //## begin ZActivity::GetPreConditionsDone%37A400820139.get preserve=no
  return m_PreConditionsDone;
  //## end ZActivity::GetPreConditionsDone%37A400820139.get
}

inline void ZActivity::SetPreConditionsDone (BOOL value)
{
  //## begin ZActivity::SetPreConditionsDone%37A400820139.set preserve=no
  m_PreConditionsDone = value;
  //## end ZActivity::SetPreConditionsDone%37A400820139.set
}

inline const BOOL ZActivity::GetPostConditionsDone () const
{
  //## begin ZActivity::GetPostConditionsDone%37A400AB0373.get preserve=no
  return m_PostConditionsDone;
  //## end ZActivity::GetPostConditionsDone%37A400AB0373.get
}

inline void ZActivity::SetPostConditionsDone (BOOL value)
{
  //## begin ZActivity::SetPostConditionsDone%37A400AB0373.set preserve=no
  m_PostConditionsDone = value;
  //## end ZActivity::SetPostConditionsDone%37A400AB0373.set
}

inline const BOOL ZActivity::GetPreFormReadOnly () const
{
  //## begin ZActivity::GetPreFormReadOnly%37D0EC23021E.get preserve=no
  return m_PreFormReadOnly;
  //## end ZActivity::GetPreFormReadOnly%37D0EC23021E.get
}

inline void ZActivity::SetPreFormReadOnly (BOOL value)
{
  //## begin ZActivity::SetPreFormReadOnly%37D0EC23021E.set preserve=no
  m_PreFormReadOnly = value;
  //## end ZActivity::SetPreFormReadOnly%37D0EC23021E.set
}

inline const BOOL ZActivity::GetPreProcReadOnly () const
{
  //## begin ZActivity::GetPreProcReadOnly%37D0EC5D01EF.get preserve=no
  return m_PreProcReadOnly;
  //## end ZActivity::GetPreProcReadOnly%37D0EC5D01EF.get
}

inline void ZActivity::SetPreProcReadOnly (BOOL value)
{
  //## begin ZActivity::SetPreProcReadOnly%37D0EC5D01EF.set preserve=no
  m_PreProcReadOnly = value;
  //## end ZActivity::SetPreProcReadOnly%37D0EC5D01EF.set
}

//## begin module%36754981018C.epilog preserve=yes
//## end module%36754981018C.epilog


#endif
