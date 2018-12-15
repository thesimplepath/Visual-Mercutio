//## begin module%36725FCA0248.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%36725FCA0248.cm

//## begin module%36725FCA0248.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%36725FCA0248.cp

//## Module: UserMng%36725FCA0248; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\UserMng.h

#ifndef UserMng_h
#define UserMng_h 1

//## begin module%36725FCA0248.additionalIncludes preserve=no
//## end module%36725FCA0248.additionalIncludes

//## begin module%36725FCA0248.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%36725FCA0248.includes

// ZUser
#include "ZUser.h"
//## begin module%36725FCA0248.declarations preserve=no
//## end module%36725FCA0248.declarations

//## begin module%36725FCA0248.additionalDeclarations preserve=yes
#ifdef _ZBASELIBEXPORT
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
//## end module%36725FCA0248.additionalDeclarations


//## Class: ZUUserManager%36725E3B017C
//## Category: ZUtil library::Network classes%366D71CA007D
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%36725FDF023E;ZUser { -> }

class AFX_EXT_CLASS ZUUserManager 
{
  //## begin ZUUserManager%36725E3B017C.initialDeclarations preserve=yes
  //## end ZUUserManager%36725E3B017C.initialDeclarations

  public:
    //## Constructors (generated)
      ZUUserManager();

    //## Destructor (generated)
      ~ZUUserManager();


    //## Other Operations (specified)
      //## Operation: AddUser%913459633
      //    Add a new user.
      void AddUser (CString UserName, CString MailAddress = "", CString Description = "", CString Responsible = "", CString Departement = "", BOOL IsAdministrator = FALSE, CString DisplayName = "");

      //## Operation: AddUser%913459634
      //    Add a new user.
      void AddUser (ZUser& User);

      //## Operation: Serialize%913459635
      //    Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: GetCount%913459639
      //    Return the number of elements of the History manager.
      size_t GetCount ();

      //## Operation: RemoveAllUsers%913459636
      //    Remove all users.
      void RemoveAllUsers ();

      //## Operation: FindUser%913459637
      //    Search if a specific user exists.
      //    .
      ZUser* FindUser (const CString& UserName, BOOL ByDisplayName = FALSE);

      //## Operation: RemoveUser%913459638
      //    Remove a specific user.
      BOOL RemoveUser (const CString& UserName, BOOL ByDisplayName = FALSE);

      //## Operation: GetAt%913459640
      //    Returns the user at the index position.
      //    .
      ZUser* GetAt (int Index);

    // Additional Public Declarations
      //## begin ZUUserManager%36725E3B017C.public preserve=yes
      //## end ZUUserManager%36725E3B017C.public

  protected:
    // Additional Protected Declarations
      //## begin ZUUserManager%36725E3B017C.protected preserve=yes
      //## end ZUUserManager%36725E3B017C.protected

  private:
    //## Constructors (generated)
      ZUUserManager(const ZUUserManager &right);

    //## Assignment Operation (generated)
      const ZUUserManager & operator=(const ZUUserManager &right);

    // Data Members for Class Attributes

      //## Attribute: UserArray%36725EA700D7
      //    Contains all users.
      //## begin ZUUserManager::UserArray%36725EA700D7.attr preserve=no  public: CObArray {U} 
      CObArray m_UserArray;
      //## end ZUUserManager::UserArray%36725EA700D7.attr

    // Additional Private Declarations
      //## begin ZUUserManager%36725E3B017C.private preserve=yes
      //## end ZUUserManager%36725E3B017C.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZUUserManager%36725E3B017C.implementation preserve=yes
      //## end ZUUserManager%36725E3B017C.implementation

};

//## begin ZUUserManager%36725E3B017C.postscript preserve=yes
//## end ZUUserManager%36725E3B017C.postscript

// Class ZUUserManager 


//## Other Operations (inline)
inline size_t ZUUserManager::GetCount ()
{
  //## begin ZUUserManager::GetCount%913459639.body preserve=yes
      return m_UserArray.GetSize();
  //## end ZUUserManager::GetCount%913459639.body
}

inline ZUser* ZUUserManager::GetAt (int Index)
{
  //## begin ZUUserManager::GetAt%913459640.body preserve=yes
      if (Index < (int)GetCount())
          return (ZUser*) m_UserArray.GetAt( Index );
      return NULL;
  //## end ZUUserManager::GetAt%913459640.body
}

//## begin module%36725FCA0248.epilog preserve=yes
//## end module%36725FCA0248.epilog


#endif
