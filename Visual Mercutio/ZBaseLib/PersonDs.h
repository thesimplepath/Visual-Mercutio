//## begin module%36722E760178.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%36722E760178.cm

//## begin module%36722E760178.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%36722E760178.cp

//## Module: PersonDs%36722E760178; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\PersonDs.h

#ifndef PersonDs_h
#define PersonDs_h 1

//## begin module%36722E760178.additionalIncludes preserve=no
//## end module%36722E760178.additionalIncludes

//## begin module%36722E760178.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%36722E760178.includes

// ZUser
#include "ZUser.h"
// Mfc
#include "Mfc.h"
//## begin module%36722E760178.declarations preserve=no
//## end module%36722E760178.declarations

//## begin module%36722E760178.additionalDeclarations preserve=yes
#ifndef _WIN32
	#ifndef Mapi_h
	#define Mapi_h 1
		#include <mapi.h>
	#endif
#else
	#include <mapi.h>
#endif

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
//## end module%36722E760178.additionalDeclarations


//## Class: ZBMailUser%36722CE80067
//## Category: ZBaseLib::Mail classes%37B3EF830338
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%36755410017F;ZUser { -> }

class AFX_EXT_CLASS ZBMailUser : public CObject  //## Inherits: <unnamed>%37542F2302DE
{
  //## begin ZBMailUser%36722CE80067.initialDeclarations preserve=yes
  //## end ZBMailUser%36722CE80067.initialDeclarations

  public:
    //## Constructors (generated)
      ZBMailUser(const ZBMailUser &right);

    //## Constructors (specified)
      //## Operation: ZBMailUser%913452742
      ZBMailUser (CString PersonName = "", ULONG RecipClass = MAPI_TO);

      //## Operation: ZBMailUser%913659111
      ZBMailUser (ZUser& PersonName, ULONG RecipClass = MAPI_TO);

    //## Destructor (generated)
      virtual ~ZBMailUser();

    //## Assignment Operation (generated)
      const ZBMailUser & operator=(const ZBMailUser &right);


    //## Other Operations (specified)
      //## Operation: Clone%913452743
      ZBMailUser* Clone ();

      //## Operation: operator >>%928176921
      //	Store from the archive to the object Stamp.
      friend CArchive& operator >> (CArchive& ar, ZBMailUser& User);

      //## Operation: operator <<%928176922
      //	Store the object Stamp to the archive.
      friend CArchive& operator << (CArchive& ar, ZBMailUser& User);

      //## Operation: Serialize%928263998
      //	Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: PersonName%36722D2D00E8
      const CString& GetPersonName () const;
      void SetPersonName (const CString& value);

      //## Attribute: RecipClass%36722D45033C
      //	Define the recipicient class.
      const ULONG GetRecipClass () const;
      void SetRecipClass (ULONG value);

    // Additional Public Declarations
      //## begin ZBMailUser%36722CE80067.public preserve=yes
      //## end ZBMailUser%36722CE80067.public

  protected:
    // Additional Protected Declarations
      //## begin ZBMailUser%36722CE80067.protected preserve=yes
	DECLARE_SERIAL(ZBMailUser)
      //## end ZBMailUser%36722CE80067.protected
  private:
    // Data Members for Class Attributes

      //## begin ZBMailUser::PersonName%36722D2D00E8.attr preserve=no  public: CString {U} 
      CString m_PersonName;
      //## end ZBMailUser::PersonName%36722D2D00E8.attr

      //## begin ZBMailUser::RecipClass%36722D45033C.attr preserve=no  public: ULONG {U} 
      ULONG m_RecipClass;
      //## end ZBMailUser::RecipClass%36722D45033C.attr

    // Additional Private Declarations
      //## begin ZBMailUser%36722CE80067.private preserve=yes
      //## end ZBMailUser%36722CE80067.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZBMailUser%36722CE80067.implementation preserve=yes
      //## end ZBMailUser%36722CE80067.implementation

};

//## begin ZBMailUser%36722CE80067.postscript preserve=yes
//## end ZBMailUser%36722CE80067.postscript

// Class ZBMailUser 

//## Get and Set Operations for Class Attributes (inline)

inline const CString& ZBMailUser::GetPersonName () const
{
  //## begin ZBMailUser::GetPersonName%36722D2D00E8.get preserve=no
  return m_PersonName;
  //## end ZBMailUser::GetPersonName%36722D2D00E8.get
}

inline void ZBMailUser::SetPersonName (const CString& value)
{
  //## begin ZBMailUser::SetPersonName%36722D2D00E8.set preserve=no
  m_PersonName = value;
  //## end ZBMailUser::SetPersonName%36722D2D00E8.set
}

inline const ULONG ZBMailUser::GetRecipClass () const
{
  //## begin ZBMailUser::GetRecipClass%36722D45033C.get preserve=no
  return m_RecipClass;
  //## end ZBMailUser::GetRecipClass%36722D45033C.get
}

inline void ZBMailUser::SetRecipClass (ULONG value)
{
  //## begin ZBMailUser::SetRecipClass%36722D45033C.set preserve=no
  m_RecipClass = value;
  //## end ZBMailUser::SetRecipClass%36722D45033C.set
}

//## begin module%36722E760178.epilog preserve=yes
//## end module%36722E760178.epilog


#endif
