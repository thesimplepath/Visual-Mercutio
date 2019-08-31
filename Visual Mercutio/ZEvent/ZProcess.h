//## begin module%367549960100.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%367549960100.cm

//## begin module%367549960100.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%367549960100.cp

//## Module: ZProcess%367549960100; Package specification
//## Subsystem: ZEvent%378A5F7E02DB
//## Source file: z:\adsoft~1\ZEvent\ZProcess.h

#ifndef ZProcess_h
#define ZProcess_h 1

//## begin module%367549960100.additionalIncludes preserve=no
//## end module%367549960100.additionalIncludes

//## begin module%367549960100.includes preserve=yes

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

//## end module%367549960100.includes

// Activity
#include "Activity.h"
// ProcIter
#include "ProcIter.h"
// BActvt
#include "BActvt.h"
//## begin module%367549960100.declarations preserve=no
//## end module%367549960100.declarations

//## begin module%367549960100.additionalDeclarations preserve=yes
enum     ProcessStatus
{
    ProcessStarted, ProcessInProcess, ProcessCompleted, ProcessAborted, ProcessNotStarted, ProcessSuspend
};

#ifdef _ZEVENTEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif


//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

//## end module%367549960100.additionalDeclarations


//## Class: ZProcess%36725B570291
//    This function defines a complete process.
//## Category: ZEvent::Process Classes - Event%378A5FD903A4
//## Subsystem: ZEvent%378A5F7E02DB
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3675469003E2;ZActivity { -> }
//## Uses: <unnamed>%37905224005E;ZProcessIterator { -> }

class AFX_EXT_CLASS ZProcess : public ZBaseActivity  //## Inherits: <unnamed>%3786DA75035C
{
    //## begin ZProcess%36725B570291.initialDeclarations preserve=yes
public:
    // Inherited feature
    typedef ZBaseActivity inherited;
    DECLARE_SERIAL(ZProcess)
    //## end ZProcess%36725B570291.initialDeclarations

public:
    //## Constructors (specified)
      //## Operation: ZProcess%915870188
    ZProcess(ProcessStatus ProcessStatus = ProcessNotStarted, CString ConnectedUser = "");

    //## Destructor (generated)
    ~ZProcess();


    //## Other Operations (specified)

      //## Operation: Serialize%913664905
      //    Serialization function required for MFC mecanism.
    virtual void Serialize(CArchive& ar);

    //## Operation: RemoveAllAuthUsers%915926630
    void RemoveAllAuthUsers();

    //## Operation: AddAuthUser%915926631
    //    Add a new authorized user.
    BOOL AddAuthUser(const CString UserName);

    //## Operation: GetAuthUserCount%915926632
    //    Return the number of authorized users.
    size_t GetAuthUserCount();

    //## Operation: GetAuthUserAt%915926633
    //    Returns the authorized username at the index position.
    CString GetAuthUserAt(int Index);

    //## Operation: FillAuthUser%915992439
    //    Fill the authorization user list with the activity.
    void FillAuthUser(ZBaseActivity& Activity, PSS_UserManager& UserManager);

    //## Operation: FillAuthUser%940840074
    //    Fill the authorization user list with a ZBResource
    //    object.
    void FillAuthUser(ZBResources& Resources);

    //    Fill the authorization user list directly with a user delimiter string
    void FillAuthUser(CString UserDelimiter);

    //## Operation: GetActivityNameArray%916072770
    //    Fill the string array with activity name. Return the
    //    number of activities.
    size_t GetActivityNameArray(CStringArray& ActivityArray, WORD ActivityType = 0, CString ExcludedActivity = "", BOOL StopWhenFound = TRUE, BOOL AttributedActivityOnly = FALSE);

    //## Operation: TemplateExist%916261170
    //    Search if a specific template name exists.
    BOOL TemplateExist(const CString& TemplateName);

    //## Operation: CreatePersonList%927439016
    //    Take the activity and build the person list for the
    //    email.
    virtual PSS_MailUserList* CreatePersonList(ZBaseActivity& Activity, PSS_UserManager& UserManager);

    //## Operation: CreatePersonList%927439017
    //    Take the activity and build the person list for the
    //    email.
    virtual PSS_MailUserList* CreatePersonList(int Index, PSS_UserManager& UserManager);

    //## Operation: FillPersonArray%927439018
    //    Take the activity and fill a person array.
    virtual BOOL FillPersonArray(ZBaseActivity& Activity, PSS_UserManager& UserManager, CStringArray& UserArray);

    //## Operation: FillPersonArray%927439019
    //    Take the activity and fill a person array.
    virtual BOOL FillPersonArray(int Index, PSS_UserManager& UserManager, CStringArray& UserArray);

    //## Operation: CreatePersonDelimStr%927439020
    //    Take the activity and build a delimited string
    //    containing the person list.
    virtual CString CreatePersonDelimStr(ZBaseActivity& Activity, PSS_UserManager& UserManager, CString Delimiter = ";");

    //## Operation: CreatePersonDelimStr%927439021
    //    Take the activity and build a delimited string
    //    containing the person list.
    virtual CString CreatePersonDelimStr(int Index, PSS_UserManager& UserManager, CString Delimiter = ";");

    //## Operation: GetAttributedActivities%927535108
    //    For a specific activity, find its attributed activities.
    CObArray* GetAttributedActivities(const CString Name);

    //## Operation: CalculateForecastedStartDate%931585006
    //    This function calculates the forecasted start date by
    //    taking all activities.
    virtual void CalculateForecastedStartDate();

    //## Operation: CalculateForecastedEndDate%929033120
    //    This function calculates the forecasted end date by
    //    taking all activities.
    virtual void CalculateForecastedEndDate();

    //## Operation: GetDurationDays%931585010
    virtual WORD GetDurationDays();

    //## Operation: GetStatusKeyString%931585016
    //    Return the Activity Status string.
    virtual CString GetStatusKeyString(ZBaseActivity* pActivity = NULL);

    //## Operation: SetStatusFromKeyString%943181049
    //    Set the Activity Status based on a keystring.
    virtual void SetStatusFromKeyString(const CString KeyString);

    //## Operation: IsChoiceActivityDone%934700760
    //## Operation: SetVisibility%935776836
    //    Set the visibility of an activity or process.
    virtual void SetVisibility(const EThreeState value);


    //## Operation: GetActivityStatusString%935923759
    virtual CString GetActivityStatusString();

    //## Operation: GetMainProcess%945000549
    //    Return the main process.
    virtual ZProcess* GetMainProcess();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ProcessStatus%3697133A00B4
      //    The process status.
    const ProcessStatus GetProcessStatus() const;
    void SetProcessStatus(ProcessStatus value);

    //## Attribute: AuthorizedUser%3697EE070096
    //    Contains the list of users authorized to modify the
    //    process. It is function of the activity.
    CStringArray& GetAuthorizedUser();

    //## Attribute: UseMail%3763A53B03BD
    //    Use also the mail as workflow support.
    const BOOL GetUseMail() const;
    void SetUseMail(BOOL value);

    //## Attribute: AutoStart%37B42F980310
    //    Defines if the process can be automatically started
    //    without human intervention.
    const BOOL GetAutoStart() const;
    void SetAutoStart(BOOL value);

    //## Attribute: ChoiceActivityArray%37B51FAB03B0

    //## Attribute: DoNotUseInternalMessage%3809A028029C
    //    Set to TRUE if the process do not must use the internal
    //    messagerie.
    const BOOL GetDoNotUseInternalMessage() const;
    void SetDoNotUseInternalMessage(BOOL value);

    // Additional Public Declarations
      //## begin ZProcess%36725B570291.public preserve=yes
    virtual void    SetDefaultProperty();

    //## end ZProcess%36725B570291.public

protected:

    //## Other Operations (specified)
      //## Operation: RecalculateProcessAllLinks%932406381
    // Data Members for Class Attributes

      //## Attribute: pCurrentActivity%36754A250232

    // Additional Protected Declarations
      //## begin ZProcess%36725B570291.protected preserve=yes
      //## end ZProcess%36725B570291.protected

private:
    //## Constructors (generated)
    ZProcess(const ZProcess &right);

    //## Assignment Operation (generated)
    const ZProcess & operator=(const ZProcess &right);

    // Data Members for Class Attributes

      //## Attribute: ActivityArray%36754AAB01C7
      //    Contains the array of activities.
      //## begin ZProcess::ActivityArray%36754AAB01C7.attr preserve=no  public: CObArray {U} 
      //## end ZProcess::ActivityArray%36754AAB01C7.attr

      //## begin ZProcess::ProcessStatus%3697133A00B4.attr preserve=no  public: ProcessStatus {U} 
    ProcessStatus m_ProcessStatus;
    //## end ZProcess::ProcessStatus%3697133A00B4.attr

    //## begin ZProcess::AuthorizedUser%3697EE070096.attr preserve=no  public: CStringArray {U} 
    CStringArray m_AuthorizedUser;
    //## end ZProcess::AuthorizedUser%3697EE070096.attr

    //## Attribute: pAttributedActivitiesArray%37490F450357
    //    Contains the attributed activities array.
    //## begin ZProcess::pAttributedActivitiesArray%37490F450357.attr preserve=no  public: CObArray* {V} 
    CObArray* m_pAttributedActivitiesArray;
    //## end ZProcess::pAttributedActivitiesArray%37490F450357.attr

    //## begin ZProcess::UseMail%3763A53B03BD.attr preserve=no  public: BOOL {U} 
    BOOL m_UseMail;
    //## end ZProcess::UseMail%3763A53B03BD.attr

    //## begin ZProcess::RunMode%37A2AA430062.attr preserve=no  public: ActivityRunMode {U} SequenceRun
    //## end ZProcess::RunMode%37A2AA430062.attr

    //## begin ZProcess::AutoStart%37B42F980310.attr preserve=no  public: BOOL {U} 
    BOOL m_AutoStart;
    //## end ZProcess::AutoStart%37B42F980310.attr

    //## begin ZProcess::ChoiceActivityArray%37B51FAB03B0.attr preserve=no  public: CStringArray {V} 
    //## end ZProcess::ChoiceActivityArray%37B51FAB03B0.attr

    //## begin ZProcess::DoNotUseInternalMessage%3809A028029C.attr preserve=no  public: BOOL {U} 
    BOOL m_DoNotUseInternalMessage;
    //## end ZProcess::DoNotUseInternalMessage%3809A028029C.attr

  // Additional Private Declarations
    //## begin ZProcess%36725B570291.private preserve=yes
    //## end ZProcess%36725B570291.private

private:  //## implementation
  // Additional Implementation Declarations
    //## begin ZProcess%36725B570291.implementation preserve=yes
    //## end ZProcess%36725B570291.implementation

};

//## begin ZProcess%36725B570291.postscript preserve=yes
//#undef  AFX_DATA
//#define AFX_DATA
//## end ZProcess%36725B570291.postscript

// Class ZProcess 


//## Other Operations (inline)
inline void ZProcess::RemoveAllAuthUsers()
{
    //## begin ZProcess::RemoveAllAuthUsers%915926630.body preserve=yes
    m_AuthorizedUser.RemoveAll();
    //## end ZProcess::RemoveAllAuthUsers%915926630.body
}

inline BOOL ZProcess::AddAuthUser(const CString UserName)
{
    //## begin ZProcess::AddAuthUser%915926631.body preserve=yes
    return m_AuthorizedUser.Add(UserName) >= 0;
    //## end ZProcess::AddAuthUser%915926631.body
}

inline size_t ZProcess::GetAuthUserCount()
{
    //## begin ZProcess::GetAuthUserCount%915926632.body preserve=yes
    return (size_t)m_AuthorizedUser.GetSize();
    //## end ZProcess::GetAuthUserCount%915926632.body
}

inline CString ZProcess::GetAuthUserAt(int Index)
{
    //## begin ZProcess::GetAuthUserAt%915926633.body preserve=yes
    return (CString)m_AuthorizedUser.GetAt(Index);
    //## end ZProcess::GetAuthUserAt%915926633.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const ProcessStatus ZProcess::GetProcessStatus() const
{
    //## begin ZProcess::GetProcessStatus%3697133A00B4.get preserve=no
    return m_ProcessStatus;
    //## end ZProcess::GetProcessStatus%3697133A00B4.get
}

inline void ZProcess::SetProcessStatus(ProcessStatus value)
{
    //## begin ZProcess::SetProcessStatus%3697133A00B4.set preserve=no
    m_ProcessStatus = value;
    //## end ZProcess::SetProcessStatus%3697133A00B4.set
}

inline CStringArray& ZProcess::GetAuthorizedUser()
{
    //## begin ZProcess::GetAuthorizedUser%3697EE070096.get preserve=no
    return m_AuthorizedUser;
    //## end ZProcess::GetAuthorizedUser%3697EE070096.get
}

inline const BOOL ZProcess::GetUseMail() const
{
    //## begin ZProcess::GetUseMail%3763A53B03BD.get preserve=no
    return m_UseMail;
    //## end ZProcess::GetUseMail%3763A53B03BD.get
}

inline void ZProcess::SetUseMail(BOOL value)
{
    //## begin ZProcess::SetUseMail%3763A53B03BD.set preserve=no
    m_UseMail = value;
    //## end ZProcess::SetUseMail%3763A53B03BD.set
}

inline const BOOL ZProcess::GetAutoStart() const
{
    //## begin ZProcess::GetAutoStart%37B42F980310.get preserve=no
    return m_AutoStart;
    //## end ZProcess::GetAutoStart%37B42F980310.get
}

inline void ZProcess::SetAutoStart(BOOL value)
{
    //## begin ZProcess::SetAutoStart%37B42F980310.set preserve=no
    m_AutoStart = value;
    //## end ZProcess::SetAutoStart%37B42F980310.set
}

inline const BOOL ZProcess::GetDoNotUseInternalMessage() const
{
    //## begin ZProcess::GetDoNotUseInternalMessage%3809A028029C.get preserve=no
    return m_DoNotUseInternalMessage;
    //## end ZProcess::GetDoNotUseInternalMessage%3809A028029C.get
}

inline void ZProcess::SetDoNotUseInternalMessage(BOOL value)
{
    //## begin ZProcess::SetDoNotUseInternalMessage%3809A028029C.set preserve=no
    m_DoNotUseInternalMessage = value;
    //## end ZProcess::SetDoNotUseInternalMessage%3809A028029C.set
}

#endif
