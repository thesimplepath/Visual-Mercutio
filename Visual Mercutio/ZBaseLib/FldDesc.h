//## begin module%363DC9C701C0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%363DC9C701C0.cm

//## begin module%363DC9C701C0.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%363DC9C701C0.cp

//## Module: FldDesc%363DC9C701C0; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\FldDesc.h

#ifndef FldDesc_h
#define FldDesc_h 1

//## begin module%363DC9C701C0.additionalIncludes preserve=no
//## end module%363DC9C701C0.additionalIncludes

//## begin module%363DC9C701C0.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%363DC9C701C0.includes

// Mfc
#include "Mfc.h"
//## begin module%363DC9C701C0.declarations preserve=no
//## end module%363DC9C701C0.declarations

//## begin module%363DC9C701C0.additionalDeclarations preserve=yes
#include "ZAObject.h"


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

//## end module%363DC9C701C0.additionalDeclarations


//## Class: ZAObjectDefinition%363DC8FB02A3
//	This class defines the object.
//## Category: ZBaseLib::History Field manager%36347B0E0308
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZAObjectDefinition : public CObject  //## Inherits: <unnamed>%363DC8FB02A4
{
  //## begin ZAObjectDefinition%363DC8FB02A3.initialDeclarations preserve=yes
	public:
	// Inherited feature
		typedef CObject inherited;
  //## end ZAObjectDefinition%363DC8FB02A3.initialDeclarations

  public:
    //## Constructors (generated)
      ZAObjectDefinition();

      ZAObjectDefinition(const ZAObjectDefinition &right);

    //## Destructor (generated)
      virtual ~ZAObjectDefinition();

    //## Assignment Operation (generated)
      const ZAObjectDefinition & operator=(const ZAObjectDefinition &right);


    //## Other Operations (specified)
      //## Operation: Serialize%910019970
      //	Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: Clone%939069933
      ZAObjectDefinition* Clone ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Description%363DC8FB02B1
      //	The field description.
      const CString GetDescription () const;
      void SetDescription (CString value);

      //## Attribute: ClassName%363DCB0502FE
      //	The class name.
      const CString GetClassName () const;
      void SetClassName (CString value);

      //## Attribute: pObject%363DCCEF02BD
      //	This is the pointer to an object.
      PlanFinObject* GetpObject ();
      void SetpObject (PlanFinObject* value);

      //## Attribute: FieldName%363DD5B200C3
      //	The field name.
      const CString GetFieldName () const;
      void SetFieldName (CString value);

      //## Attribute: HelpUserDescription%36CE7ACC020F
      //	The field description used for wizard. Destinated to
      //	users.
      const CString GetHelpUserDescription () const;
      void SetHelpUserDescription (CString value);

    // Additional Public Declarations
      //## begin ZAObjectDefinition%363DC8FB02A3.public preserve=yes
      // The sorting key
      const BOOL IsSorted () const;
      void SetSorted (BOOL value = TRUE);



#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
      //## end ZAObjectDefinition%363DC8FB02A3.public
  protected:
    // Additional Protected Declarations
      //## begin ZAObjectDefinition%363DC8FB02A3.protected preserve=yes
	DECLARE_SERIAL(ZAObjectDefinition)
      //## end ZAObjectDefinition%363DC8FB02A3.protected
  private:
    // Data Members for Class Attributes

      //## begin ZAObjectDefinition::Description%363DC8FB02B1.attr preserve=no  public: CString {U} 
      CString m_Description;
      //## end ZAObjectDefinition::Description%363DC8FB02B1.attr

      //## begin ZAObjectDefinition::ClassName%363DCB0502FE.attr preserve=no  public: CString {U} 
      CString m_ClassName;
      //## end ZAObjectDefinition::ClassName%363DCB0502FE.attr

      //## begin ZAObjectDefinition::pObject%363DCCEF02BD.attr preserve=no  public: PlanFinObject* {U} NULL
      PlanFinObject* m_pObject;
      //## end ZAObjectDefinition::pObject%363DCCEF02BD.attr

      //## begin ZAObjectDefinition::FieldName%363DD5B200C3.attr preserve=no  public: CString {U} 
      CString m_FieldName;
      //## end ZAObjectDefinition::FieldName%363DD5B200C3.attr

      //## begin ZAObjectDefinition::HelpUserDescription%36CE7ACC020F.attr preserve=no  public: CString {U} 
      CString m_HelpUserDescription;
      //## end ZAObjectDefinition::HelpUserDescription%36CE7ACC020F.attr

    // Additional Private Declarations
      //## begin ZAObjectDefinition%363DC8FB02A3.private preserve=yes
	  BOOL	m_Sorted;
      //## end ZAObjectDefinition%363DC8FB02A3.private
  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZAObjectDefinition%363DC8FB02A3.implementation preserve=yes
      //## end ZAObjectDefinition%363DC8FB02A3.implementation

};

//## begin ZAObjectDefinition%363DC8FB02A3.postscript preserve=yes
//## end ZAObjectDefinition%363DC8FB02A3.postscript

// Class ZAObjectDefinition 

//## Get and Set Operations for Class Attributes (inline)

inline const CString ZAObjectDefinition::GetDescription () const
{
  //## begin ZAObjectDefinition::GetDescription%363DC8FB02B1.get preserve=no
  return m_Description;
  //## end ZAObjectDefinition::GetDescription%363DC8FB02B1.get
}

inline void ZAObjectDefinition::SetDescription (CString value)
{
  //## begin ZAObjectDefinition::SetDescription%363DC8FB02B1.set preserve=no
  m_Description = value;
  //## end ZAObjectDefinition::SetDescription%363DC8FB02B1.set
}

inline const CString ZAObjectDefinition::GetClassName () const
{
  //## begin ZAObjectDefinition::GetClassName%363DCB0502FE.get preserve=no
  return m_ClassName;
  //## end ZAObjectDefinition::GetClassName%363DCB0502FE.get
}

inline void ZAObjectDefinition::SetClassName (CString value)
{
  //## begin ZAObjectDefinition::SetClassName%363DCB0502FE.set preserve=no
  m_ClassName = value;
  //## end ZAObjectDefinition::SetClassName%363DCB0502FE.set
}

inline PlanFinObject* ZAObjectDefinition::GetpObject ()
{
  //## begin ZAObjectDefinition::GetpObject%363DCCEF02BD.get preserve=no
  return m_pObject;
  //## end ZAObjectDefinition::GetpObject%363DCCEF02BD.get
}

inline void ZAObjectDefinition::SetpObject (PlanFinObject* value)
{
  //## begin ZAObjectDefinition::SetpObject%363DCCEF02BD.set preserve=no
  m_pObject = value;
  //## end ZAObjectDefinition::SetpObject%363DCCEF02BD.set
}

inline const CString ZAObjectDefinition::GetFieldName () const
{
  //## begin ZAObjectDefinition::GetFieldName%363DD5B200C3.get preserve=no
  return m_FieldName;
  //## end ZAObjectDefinition::GetFieldName%363DD5B200C3.get
}

inline void ZAObjectDefinition::SetFieldName (CString value)
{
  //## begin ZAObjectDefinition::SetFieldName%363DD5B200C3.set preserve=no
  m_FieldName = value;
  //## end ZAObjectDefinition::SetFieldName%363DD5B200C3.set
}

inline const CString ZAObjectDefinition::GetHelpUserDescription () const
{
  //## begin ZAObjectDefinition::GetHelpUserDescription%36CE7ACC020F.get preserve=no
  return m_HelpUserDescription;
  //## end ZAObjectDefinition::GetHelpUserDescription%36CE7ACC020F.get
}

inline void ZAObjectDefinition::SetHelpUserDescription (CString value)
{
  //## begin ZAObjectDefinition::SetHelpUserDescription%36CE7ACC020F.set preserve=no
  m_HelpUserDescription = value;
  //## end ZAObjectDefinition::SetHelpUserDescription%36CE7ACC020F.set
}

//## begin module%363DC9C701C0.epilog preserve=yes
inline const BOOL ZAObjectDefinition::IsSorted () const
{
	return m_Sorted;
}
inline void ZAObjectDefinition::SetSorted (BOOL value)
{
	m_Sorted = value;
}
//## end module%363DC9C701C0.epilog


#endif


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin ZAObjectDefinition%363DC8FB02A3.preface preserve=no
//## end ZAObjectDefinition%363DC8FB02A3.preface

#endif
