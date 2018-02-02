//## begin module%36725CAD008A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%36725CAD008A.cm

//## begin module%36725CAD008A.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%36725CAD008A.cp

//## Module: ZUser%36725CAD008A; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZUser.h

#ifndef ZUser_h
#define ZUser_h 1

//## begin module%36725CAD008A.additionalIncludes preserve=no
//## end module%36725CAD008A.additionalIncludes

//## begin module%36725CAD008A.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%36725CAD008A.includes

//## begin module%36725CAD008A.declarations preserve=no
//## end module%36725CAD008A.declarations

//## begin module%36725CAD008A.additionalDeclarations preserve=yes
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
//## end module%36725CAD008A.additionalDeclarations


//## Class: ZUser%36725BAA0204
//	Defines a user.
//## Category: ZUtil library::Network classes%366D71CA007D
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZUser : public CObject
{
  //## begin ZUser%36725BAA0204.initialDeclarations preserve=yes
	DECLARE_DYNCREATE(ZUser)
  //## end ZUser%36725BAA0204.initialDeclarations

  public:
    //## Constructors (generated)
      ZUser(const ZUser &right);

    //## Constructors (specified)
      //## Operation: ZUser%913459631
      //	Build a user
      ZUser (CString UserName = "", CString MailAddress = "", CString Description = "", CString Responsible = "", CString Departement = "", BOOL IsAdministrator = FALSE, CString DisplayName = "");

    //## Destructor (generated)
      ~ZUser();

    //## Assignment Operation (generated)
      const ZUser & operator=(const ZUser &right);


    //## Other Operations (specified)
      //## Operation: operator==%936516041
      //	compare to a CString
      BOOL operator == (const ZUser& User);

      //## Operation: operator==%936516039
      //	compare to a CString
      BOOL operator == (const CString str);

      //## Operation: operator==%936516040
      //	compare to a const char*
      BOOL operator == (LPCTSTR lpsz);

      //## Operation: Clone%913459632
      //	Clone a user.
      ZUser* Clone ();

      //## Operation: operator >>%913659096
      //	Store from the archive to the object Stamp.
      AFX_EXT_API friend CArchive& operator >> (CArchive& ar, ZUser& User);

      //## Operation: operator <<%913659097
      //	Store the object Stamp to the archive.
      AFX_EXT_API friend CArchive& operator << (CArchive& ar, ZUser& User);

      //## Operation: IsAdministrator%933697289
      //	Return TRUE if the user has administrator rights.
      BOOL IsAdministrator () const;

      //## Operation: SetAdministrator%933697290
      //	Set administrator. Default value is true.
      void SetAdministrator (BOOL value = TRUE);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: UserName%36725BCB00CB
      //	The username.
      const CString GetUserName () const;
      void SetUserName (CString value);

      //## Attribute: MailAddress%36725BED01BA
      //	Defines the Mail Address
      const CString GetMailAddress () const;
      void SetMailAddress (CString value);

      //## Attribute: Description%3675550500FF
      //	The user description.
      const CString GetDescription () const;
      void SetDescription (CString value);

      //## Attribute: Responsible%368CD1DE01AE
      //	Contains the reponsible person name.
      const CString& GetResponsible () const;
      void SetResponsible (const CString& value);

      //## Attribute: Departement%37A7168902AE
      //	Contains the departement name.
      const CString GetDepartement () const;
      void SetDepartement (CString value);

      //## Attribute: DisplayName%382A8D31015B
      //	The display name.
      const CString GetDisplayName () const;
      void SetDisplayName (CString value);

    // Additional Public Declarations
      //## begin ZUser%36725BAA0204.public preserve=yes
      //## end ZUser%36725BAA0204.public

  protected:
    // Additional Protected Declarations
      //## begin ZUser%36725BAA0204.protected preserve=yes
      //## end ZUser%36725BAA0204.protected

  private:
    // Data Members for Class Attributes

      //## begin ZUser::UserName%36725BCB00CB.attr preserve=no  public: CString {U} 
      CString m_UserName;
      //## end ZUser::UserName%36725BCB00CB.attr

      //## begin ZUser::MailAddress%36725BED01BA.attr preserve=no  public: CString {U} 
      CString m_MailAddress;
      //## end ZUser::MailAddress%36725BED01BA.attr

      //## begin ZUser::Responsible%368CD1DE01AE.attr preserve=no  public: CString {U} 
      CString m_Responsible;
      //## end ZUser::Responsible%368CD1DE01AE.attr

      //## begin ZUser::Departement%37A7168902AE.attr preserve=no  public: CString {U} 
      CString m_Departement;
      //## end ZUser::Departement%37A7168902AE.attr

      //## Attribute: IsAdministrator%37A7169E01FA
      //	Defines if the user has administrator rights.
      //## begin ZUser::IsAdministrator%37A7169E01FA.attr preserve=no  public: BOOL {U} 
      BOOL m_IsAdministrator;
      //## end ZUser::IsAdministrator%37A7169E01FA.attr

      //## begin ZUser::DisplayName%382A8D31015B.attr preserve=no  public: CString {U} 
      CString m_DisplayName;
      //## end ZUser::DisplayName%382A8D31015B.attr

    // Additional Private Declarations
      //## begin ZUser%36725BAA0204.private preserve=yes
      //## end ZUser%36725BAA0204.private

  private:  //## implementation
    // Data Members for Class Attributes

      //## begin ZUser::Description%3675550500FF.attr preserve=no  public: CString {V} 
      CString m_Description;
      //## end ZUser::Description%3675550500FF.attr

    // Additional Implementation Declarations
      //## begin ZUser%36725BAA0204.implementation preserve=yes
      //## end ZUser%36725BAA0204.implementation

};

//## begin ZUser%36725BAA0204.postscript preserve=yes
//## end ZUser%36725BAA0204.postscript

// Class ZUser 


//## Other Operations (inline)
inline BOOL ZUser::IsAdministrator () const
{
  //## begin ZUser::IsAdministrator%933697289.body preserve=yes
	return m_IsAdministrator;
  //## end ZUser::IsAdministrator%933697289.body
}

inline void ZUser::SetAdministrator (BOOL value)
{
  //## begin ZUser::SetAdministrator%933697290.body preserve=yes
	m_IsAdministrator = value;
  //## end ZUser::SetAdministrator%933697290.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const CString ZUser::GetUserName () const
{
  //## begin ZUser::GetUserName%36725BCB00CB.get preserve=no
  return m_UserName;
  //## end ZUser::GetUserName%36725BCB00CB.get
}

inline void ZUser::SetUserName (CString value)
{
  //## begin ZUser::SetUserName%36725BCB00CB.set preserve=no
  m_UserName = value;
  //## end ZUser::SetUserName%36725BCB00CB.set
}

inline const CString ZUser::GetMailAddress () const
{
  //## begin ZUser::GetMailAddress%36725BED01BA.get preserve=no
  return m_MailAddress;
  //## end ZUser::GetMailAddress%36725BED01BA.get
}

inline void ZUser::SetMailAddress (CString value)
{
  //## begin ZUser::SetMailAddress%36725BED01BA.set preserve=no
  m_MailAddress = value;
  //## end ZUser::SetMailAddress%36725BED01BA.set
}

inline const CString ZUser::GetDescription () const
{
  //## begin ZUser::GetDescription%3675550500FF.get preserve=no
  return m_Description;
  //## end ZUser::GetDescription%3675550500FF.get
}

inline void ZUser::SetDescription (CString value)
{
  //## begin ZUser::SetDescription%3675550500FF.set preserve=no
  m_Description = value;
  //## end ZUser::SetDescription%3675550500FF.set
}

inline const CString& ZUser::GetResponsible () const
{
  //## begin ZUser::GetResponsible%368CD1DE01AE.get preserve=no
  return m_Responsible;
  //## end ZUser::GetResponsible%368CD1DE01AE.get
}

inline void ZUser::SetResponsible (const CString& value)
{
  //## begin ZUser::SetResponsible%368CD1DE01AE.set preserve=no
  m_Responsible = value;
  //## end ZUser::SetResponsible%368CD1DE01AE.set
}

inline const CString ZUser::GetDepartement () const
{
  //## begin ZUser::GetDepartement%37A7168902AE.get preserve=no
  return m_Departement;
  //## end ZUser::GetDepartement%37A7168902AE.get
}

inline void ZUser::SetDepartement (CString value)
{
  //## begin ZUser::SetDepartement%37A7168902AE.set preserve=no
  m_Departement = value;
  //## end ZUser::SetDepartement%37A7168902AE.set
}

inline const CString ZUser::GetDisplayName () const
{
  //## begin ZUser::GetDisplayName%382A8D31015B.get preserve=no
  return m_DisplayName;
  //## end ZUser::GetDisplayName%382A8D31015B.get
}

inline void ZUser::SetDisplayName (CString value)
{
  //## begin ZUser::SetDisplayName%382A8D31015B.set preserve=no
  m_DisplayName = value;
  //## end ZUser::SetDisplayName%382A8D31015B.set
}

//## begin module%36725CAD008A.epilog preserve=yes
//## end module%36725CAD008A.epilog


#endif
