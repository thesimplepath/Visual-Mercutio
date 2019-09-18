//## begin module%374C3AB50066.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%374C3AB50066.cm

//## begin module%374C3AB50066.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%374C3AB50066.cp

//## Module: ZResourc%374C3AB50066; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZResourc.h

#ifndef ZResourc_h
#define ZResourc_h 1

//## begin module%374C3AB50066.additionalIncludes preserve=no
//## end module%374C3AB50066.additionalIncludes

//## begin module%374C3AB50066.includes preserve=yes

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_Date.h"

enum ActivityUserType { Users, ResponsibleOfUser, AttributionOfUsers, UserFromActivity };

// PersonLs
#include "zBaseLib\PSS_MailUserList.h"
// UserMng
#include "zBaseLib\PSS_UserManager.h"
// Mfc
#include "Mfc.h"
//## begin module%374C3AB50066.declarations preserve=no
//## end module%374C3AB50066.declarations

//## begin module%374C3AB50066.additionalDeclarations preserve=yes
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

class ZProcess;    // Forward declaration
//## end module%374C3AB50066.additionalDeclarations


//## Class: ZBResources%374C378F0049
//    This class encapsulates the resouces defined for an
//    activity.
//## Category: ZUtil library::Process classes%3751815B0322
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%374C3EA40281;ZUMailUserList { -> }
//## Uses: <unnamed>%374C3EA80006;ZUUserManager { -> }

class AFX_EXT_CLASS ZBResources : public CObject  //## Inherits: <unnamed>%374C3B8100A6
{
  //## begin ZBResources%374C378F0049.initialDeclarations preserve=yes
public:
// Inherited feature
    typedef CObject inherited;
  //## end ZBResources%374C378F0049.initialDeclarations

  public:
    //## Constructors (generated)
      ZBResources();

      ZBResources(const ZBResources &right);

    //## Destructor (generated)
      virtual ~ZBResources();

    //## Assignment Operation (generated)
      const ZBResources & operator=(const ZBResources &right);


    //## Other Operations (specified)
      //## Operation: operator >>%927742723
      //    Store from the archive to the object Stamp.
      friend CArchive& operator >> (CArchive& ar, ZBResources& ActivityResource);

      //## Operation: operator <<%927742724
      //    Store the object Stamp to the archive.
      friend CArchive& operator << (CArchive& ar, ZBResources& ActivityResource);

      //## Operation: AddUser%927742725
      //    Add a new user.
      void AddUser (const CString UserName);

      //    Take the delimiter string and add them
      BOOL AddUsers (CString DelimiterString);

      //## Operation: RemoveUser%927742726
      //    Remove a specific user.
      BOOL RemoveUser (const CString& UserName);

      //## Operation: UserExist%927742727
      //    Search if a specific user exists.
      BOOL UserExist (const CString& UserName);

      //## Operation: GetUserCount%927742728
      //    Return the number of users.
      size_t GetUserCount () const;

      //## Operation: GetUserAt%927742729
      //    Returns the user at the index position.
      CString GetUserAt (int Index) const;

      //## Operation: RemoveAllUsers%927742734
      //    Remove all users.
      void RemoveAllUsers ();

      //## Operation: CreatePersonList%927742730
      //    Take the activity and build the person list for the
      //    email.
      PSS_MailUserList* CreatePersonList (ZProcess* pMainProcess, PSS_UserManager& UserManager, CString ConnectedUser);

      //## Operation: FillPersonArray%927742731
      //    Take the activity and fill a person array.
      BOOL FillPersonArray (ZProcess* pMainProcess, PSS_UserManager& UserManager, CStringArray& UserArray, CString ConnectedUser);

      //## Operation: CreatePersonDelimStr%927742732
      //    Take the activity and build a delimited string
      //    containing the person list.
      CString CreatePersonDelimStr (ZProcess* pMainProcess, PSS_UserManager& UserManager, CString ConnectedUser, CString Delimiter = ";");

      //## Operation: Clone%927742733
      //    Clone this class.
      ZBResources* Clone ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: UserType%374C3C7F0173
      const ActivityUserType GetUserType () const;
      void SetUserType (ActivityUserType value);

    // Additional Public Declarations
      //## begin ZBResources%374C378F0049.public preserve=yes
      //## end ZBResources%374C378F0049.public

  protected:
    // Additional Protected Declarations
      //## begin ZBResources%374C378F0049.protected preserve=yes
    DECLARE_DYNAMIC(ZBResources)
      //## end ZBResources%374C378F0049.protected
  private:
    // Data Members for Class Attributes

      //## Attribute: UserArray%374C39C002BD
      //    Contains the list of users.
      //## begin ZBResources::UserArray%374C39C002BD.attr preserve=no  public: CStringArray {U} 
      CStringArray m_UserArray;
      //## end ZBResources::UserArray%374C39C002BD.attr

      //## begin ZBResources::UserType%374C3C7F0173.attr preserve=no  public: ActivityUserType {U} Users
      ActivityUserType m_UserType;
      //## end ZBResources::UserType%374C3C7F0173.attr

    // Additional Private Declarations
      //## begin ZBResources%374C378F0049.private preserve=yes
      //## end ZBResources%374C378F0049.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZBResources%374C378F0049.implementation preserve=yes
      //## end ZBResources%374C378F0049.implementation

};

//## begin ZBResources%374C378F0049.postscript preserve=yes
//## end ZBResources%374C378F0049.postscript

// Class ZBResources 


//## Other Operations (inline)
inline size_t ZBResources::GetUserCount () const
{
  //## begin ZBResources::GetUserCount%927742728.body preserve=yes
      return m_UserArray.GetSize();
  //## end ZBResources::GetUserCount%927742728.body
}

inline CString ZBResources::GetUserAt (int Index) const
{
  //## begin ZBResources::GetUserAt%927742729.body preserve=yes
      return m_UserArray.GetAt( Index );
  //## end ZBResources::GetUserAt%927742729.body
}

inline void ZBResources::RemoveAllUsers ()
{
  //## begin ZBResources::RemoveAllUsers%927742734.body preserve=yes
      m_UserArray.RemoveAll();
  //## end ZBResources::RemoveAllUsers%927742734.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const ActivityUserType ZBResources::GetUserType () const
{
  //## begin ZBResources::GetUserType%374C3C7F0173.get preserve=no
  return m_UserType;
  //## end ZBResources::GetUserType%374C3C7F0173.get
}

inline void ZBResources::SetUserType (ActivityUserType value)
{
  //## begin ZBResources::SetUserType%374C3C7F0173.set preserve=no
  m_UserType = value;
  //## end ZBResources::SetUserType%374C3C7F0173.set
}

//## begin module%374C3AB50066.epilog preserve=yes
//## end module%374C3AB50066.epilog


#endif
