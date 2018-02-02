//## begin module%363481AB01AE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%363481AB01AE.cm

//## begin module%363481AB01AE.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%363481AB01AE.cp

//## Module: HistFld%363481AB01AE; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\HistFld.h

#ifndef HistFld_h
#define HistFld_h 1

//## begin module%363481AB01AE.additionalIncludes preserve=no
//## end module%363481AB01AE.additionalIncludes

//## begin module%363481AB01AE.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%363481AB01AE.includes

// Mfc
#include "Mfc.h"
//## begin module%363481AB01AE.declarations preserve=no
//## end module%363481AB01AE.declarations

//## begin module%363481AB01AE.additionalDeclarations preserve=yes
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
//## end module%363481AB01AE.additionalDeclarations


//## Class: ZAHistoryField%36347E3600E3
//## Category: ZBaseLib::History Field manager%36347B0E0308
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZAHistoryField : public CObject  //## Inherits: <unnamed>%36347F4A0325
{
  //## begin ZAHistoryField%36347E3600E3.initialDeclarations preserve=yes
	public:
	// Inherited feature
		typedef CObject inherited;
  //## end ZAHistoryField%36347E3600E3.initialDeclarations

  public:
    //## Constructors (generated)
      ZAHistoryField();

      ZAHistoryField(const ZAHistoryField &right);

    //## Destructor (generated)
      virtual ~ZAHistoryField();

    //## Assignment Operation (generated)
      const ZAHistoryField & operator=(const ZAHistoryField &right);


    //## Other Operations (specified)
      //## Operation: Serialize%909410992
      //	Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: GetCount%909410993
      //	Return the number of values.
      size_t GetCount ();

      //## Operation: AddFieldValue%909410994
      //	Add a new historic value into the FieldValueHistoryArray.
      void AddFieldValue (const CString& Value);

      //## Operation: RemoveFieldValue%909410995
      //	Remove a specific historic value from the manager.
      BOOL RemoveFieldValue (const CString& Value);

      //## Operation: GetValueArray%909410996
      const CStringArray& GetValueArray () const;

      //## Operation: IsReadOnly%909410997
      //	If the field history is read-only.
      BOOL IsReadOnly () const;

      //## Operation: FreeList%909411006
      //	remove the history.
      void FreeList ();

      //## Operation: Clone%939069934
      ZAHistoryField* Clone ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ReadOnly%363480D5034B
      //	If the list can growth.
      void SetReadOnly (BOOL value);

      //## Attribute: FieldName%363489DA02A1
      //	The field name.
      const CString GetFieldName () const;
      void SetFieldName (CString value);

    // Additional Public Declarations
      //## begin ZAHistoryField%36347E3600E3.public preserve=yes
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
      //## end ZAHistoryField%36347E3600E3.public
  protected:
    // Additional Protected Declarations
      //## begin ZAHistoryField%36347E3600E3.protected preserve=yes
	DECLARE_SERIAL(ZAHistoryField)
      //## end ZAHistoryField%36347E3600E3.protected
  private:
    // Data Members for Class Attributes

      //## Attribute: FieldValueHistoryArray%36347EF80133
      //	Contains the history string values.
      //## begin ZAHistoryField::FieldValueHistoryArray%36347EF80133.attr preserve=no  public: CStringArray {U} 
      CStringArray m_FieldValueHistoryArray;
      //## end ZAHistoryField::FieldValueHistoryArray%36347EF80133.attr

      //## begin ZAHistoryField::ReadOnly%363480D5034B.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_ReadOnly;
      //## end ZAHistoryField::ReadOnly%363480D5034B.attr

      //## begin ZAHistoryField::FieldName%363489DA02A1.attr preserve=no  public: CString {U} 
      CString m_FieldName;
      //## end ZAHistoryField::FieldName%363489DA02A1.attr

    // Additional Private Declarations
      //## begin ZAHistoryField%36347E3600E3.private preserve=yes
      //## end ZAHistoryField%36347E3600E3.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZAHistoryField%36347E3600E3.implementation preserve=yes
      //## end ZAHistoryField%36347E3600E3.implementation

};

//## begin ZAHistoryField%36347E3600E3.postscript preserve=yes
//## end ZAHistoryField%36347E3600E3.postscript

// Class ZAHistoryField 


//## Other Operations (inline)
inline size_t ZAHistoryField::GetCount ()
{
  //## begin ZAHistoryField::GetCount%909410993.body preserve=yes
  	return m_FieldValueHistoryArray.GetSize();
  //## end ZAHistoryField::GetCount%909410993.body
}

inline const CStringArray& ZAHistoryField::GetValueArray () const
{
  //## begin ZAHistoryField::GetValueArray%909410996.body preserve=yes
  	return m_FieldValueHistoryArray;
  //## end ZAHistoryField::GetValueArray%909410996.body
}

inline BOOL ZAHistoryField::IsReadOnly () const
{
  //## begin ZAHistoryField::IsReadOnly%909410997.body preserve=yes
  	return m_ReadOnly;
  //## end ZAHistoryField::IsReadOnly%909410997.body
}

//## Get and Set Operations for Class Attributes (inline)

inline void ZAHistoryField::SetReadOnly (BOOL value)
{
  //## begin ZAHistoryField::SetReadOnly%363480D5034B.set preserve=no
  m_ReadOnly = value;
  //## end ZAHistoryField::SetReadOnly%363480D5034B.set
}

inline const CString ZAHistoryField::GetFieldName () const
{
  //## begin ZAHistoryField::GetFieldName%363489DA02A1.get preserve=no
  return m_FieldName;
  //## end ZAHistoryField::GetFieldName%363489DA02A1.get
}

inline void ZAHistoryField::SetFieldName (CString value)
{
  //## begin ZAHistoryField::SetFieldName%363489DA02A1.set preserve=no
  m_FieldName = value;
  //## end ZAHistoryField::SetFieldName%363489DA02A1.set
}

//## begin module%363481AB01AE.epilog preserve=yes
//## end module%363481AB01AE.epilog


#endif
