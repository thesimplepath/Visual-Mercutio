//## begin module%36722E89031A.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%36722E89031A.cm

//## begin module%36722E89031A.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%36722E89031A.cp

//## Module: PersonLs%36722E89031A; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\PersonLs.h

#ifndef PersonLs_h
#define PersonLs_h 1

//## begin module%36722E89031A.additionalIncludes preserve=no
//## end module%36722E89031A.additionalIncludes

//## begin module%36722E89031A.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%36722E89031A.includes

// UserMng
#include "UserMng.h"
// PersonDs
#include "PersonDs.h"
// Mfc
#include "Mfc.h"
//## begin module%36722E89031A.declarations preserve=no
//## end module%36722E89031A.declarations

//## begin module%36722E89031A.additionalDeclarations preserve=yes
//## end module%36722E89031A.additionalDeclarations


//## begin ZUMailUserList%36722C490253.preface preserve=yes
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
//## end ZUMailUserList%36722C490253.preface

//## Class: ZUMailUserList%36722C490253
//## Category: ZUtil library::Email classes%36722AB50003
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%36723168005A;ZBMailUser { -> }
//## Uses: <unnamed>%367554130382;ZUUserManager { -> }

class AFX_EXT_CLASS ZUMailUserList : public CObject  //## Inherits: <unnamed>%375129D902C5
{
  //## begin ZUMailUserList%36722C490253.initialDeclarations preserve=yes
  //## end ZUMailUserList%36722C490253.initialDeclarations

  public:
    //## Constructors (generated)
      ZUMailUserList();

    //## Constructors (specified)
      //## Operation: ZUMailUserList%913452744
      ZUMailUserList (CStringArray& PersonListName, ULONG RecipClass = MAPI_TO);

      //## Operation: ZUMailUserList%913659112
      ZUMailUserList (ZUUserManager& PersonListName, ULONG RecipClass = MAPI_TO);

      //## Operation: ZUMailUserList%921575859
      ZUMailUserList (lpMapiRecipDesc* pMapiDesc, ULONG Count = 1);

    //## Destructor (generated)
      virtual ~ZUMailUserList();


    //## Other Operations (specified)
      //## Operation: Serialize%928062192
      //	Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: GetMapiRecipDescPtr%913452745
      //	Build the mapi recipicient description pointer.
      MapiRecipDesc* GetMapiRecipDescPtr ();

      //## Operation: AddPerson%913452746
      //	Add a new person.
      BOOL AddPerson (CString PersonName, ULONG RecipClass = MAPI_TO);

      //## Operation: AddPerson%913452747
      //	Add a new person.
      BOOL AddPerson (ZBMailUser& Person, ULONG RecipClass = MAPI_TO);

      //## Operation: AddPerson%913659113
      //	Add a new person.
      BOOL AddPerson (ZUser& Person, ULONG RecipClass = MAPI_TO);

      //## Operation: AddPerson%921575861
      //	Add a new person.
      BOOL AddPerson (MapiRecipDesc* pMapiDesc);

      //## Operation: GetCount%913452748
      int GetCount () const;

      //## Operation: RemoveAllPersons%913452749
      void RemoveAllPersons ();

      //## Operation: GetAt%913452750
      //	Get the person at the position i.
      //	Returns null if not found.
      ZBMailUser* GetAt (int Index);

      //## Operation: Fill%913659114
      void Fill (CStringArray& PersonList, ULONG RecipClass = MAPI_TO);

      //## Operation: Fill%913659115
      void Fill (ZUUserManager& PersonList, ULONG RecipClass = MAPI_TO);

      //## Operation: Fill%921575860
      void Fill (lpMapiRecipDesc* pMapiDesc, ULONG Count);

    // Additional Public Declarations
      //## begin ZUMailUserList%36722C490253.public preserve=yes
      //## end ZUMailUserList%36722C490253.public

  protected:
    // Additional Protected Declarations
      //## begin ZUMailUserList%36722C490253.protected preserve=yes
	DECLARE_SERIAL(ZUMailUserList)
      //## end ZUMailUserList%36722C490253.protected
  private:
    //## Constructors (generated)
      ZUMailUserList(const ZUMailUserList &right);

    //## Assignment Operation (generated)
      const ZUMailUserList & operator=(const ZUMailUserList &right);

    // Data Members for Class Attributes

      //## Attribute: MapiRecipDescPtr%36722C940002
      //	Used to export to MAPI structure.
      //## begin ZUMailUserList::MapiRecipDescPtr%36722C940002.attr preserve=no  public: MapiRecipDesc* {U} NULL
      MapiRecipDesc* m_MapiRecipDescPtr;
      //## end ZUMailUserList::MapiRecipDescPtr%36722C940002.attr

      //## Attribute: PersonList%367230B100BB
      //	Contains the person list.
      //## begin ZUMailUserList::PersonList%367230B100BB.attr preserve=no  public: CObArray {U} 
      CObArray m_PersonList;
      //## end ZUMailUserList::PersonList%367230B100BB.attr

    // Additional Private Declarations
      //## begin ZUMailUserList%36722C490253.private preserve=yes
      //## end ZUMailUserList%36722C490253.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ZUMailUserList%36722C490253.implementation preserve=yes
      //## end ZUMailUserList%36722C490253.implementation

};

//## begin ZUMailUserList%36722C490253.postscript preserve=yes
//## end ZUMailUserList%36722C490253.postscript

// Class ZUMailUserList 


//## Other Operations (inline)
inline BOOL ZUMailUserList::AddPerson (CString PersonName, ULONG RecipClass)
{
  //## begin ZUMailUserList::AddPerson%913452746.body preserve=yes
  	ZBMailUser*	pNewPerson = new ZBMailUser( PersonName, RecipClass );
  	return m_PersonList.Add( (CObject*)pNewPerson ) >= 0;
  //## end ZUMailUserList::AddPerson%913452746.body
}

inline BOOL ZUMailUserList::AddPerson (ZBMailUser& Person, ULONG RecipClass)
{
  //## begin ZUMailUserList::AddPerson%913452747.body preserve=yes
  	return m_PersonList.Add( (CObject*)&Person ) >= 0;
  //## end ZUMailUserList::AddPerson%913452747.body
}

inline BOOL ZUMailUserList::AddPerson (ZUser& Person, ULONG RecipClass)
{
  //## begin ZUMailUserList::AddPerson%913659113.body preserve=yes
  	ZBMailUser*	pNewPerson = new ZBMailUser( Person.GetMailAddress(), RecipClass );
  	return m_PersonList.Add( (CObject*)pNewPerson ) >= 0;
  //## end ZUMailUserList::AddPerson%913659113.body
}

inline BOOL ZUMailUserList::AddPerson (MapiRecipDesc* pMapiDesc)
{
  //## begin ZUMailUserList::AddPerson%921575861.body preserve=yes
  	ZBMailUser*	pNewPerson = new ZBMailUser( pMapiDesc->lpszName, pMapiDesc->ulRecipClass );
  	return m_PersonList.Add( (CObject*)pNewPerson ) >= 0;
  //## end ZUMailUserList::AddPerson%921575861.body
}

inline int ZUMailUserList::GetCount () const
{
  //## begin ZUMailUserList::GetCount%913452748.body preserve=yes
  	return m_PersonList.GetSize();
  //## end ZUMailUserList::GetCount%913452748.body
}

inline void ZUMailUserList::RemoveAllPersons ()
{
  //## begin ZUMailUserList::RemoveAllPersons%913452749.body preserve=yes
  	for (int i = 0; i < GetCount(); ++i)
  		delete GetAt( i );
  	m_PersonList.RemoveAll();
  //## end ZUMailUserList::RemoveAllPersons%913452749.body
}

inline ZBMailUser* ZUMailUserList::GetAt (int Index)
{
  //## begin ZUMailUserList::GetAt%913452750.body preserve=yes
  	if (Index < GetCount())
  		return (ZBMailUser*) m_PersonList.GetAt( Index );
  	return NULL;
  //## end ZUMailUserList::GetAt%913452750.body
}

//## begin module%36722E89031A.epilog preserve=yes
//## end module%36722E89031A.epilog


#endif
