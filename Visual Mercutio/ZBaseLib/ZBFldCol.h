//## begin module%38819A270147.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%38819A270147.cm

//## begin module%38819A270147.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%38819A270147.cp

//## Module: ZBFldCol%38819A270147; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZBFldCol.h

#ifndef ZBFldCol_h
#define ZBFldCol_h 1

//## begin module%38819A270147.additionalIncludes preserve=no
//## end module%38819A270147.additionalIncludes

//## begin module%38819A270147.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%38819A270147.includes

// Mfc
#include "Mfc.h"
//## begin module%38819A270147.declarations preserve=no
//## end module%38819A270147.declarations

//## begin module%38819A270147.additionalDeclarations preserve=yes
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
//## end module%38819A270147.additionalDeclarations


//## Class: ZBFieldColumn%3881998D038A
//## Category: ZBaseLib::Base objects%37E9429A0111
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZBFieldColumn : public CObject  //## Inherits: <unnamed>%38819B590147
{
  //## begin ZBFieldColumn%3881998D038A.initialDeclarations preserve=yes
    public:
    // Inherited feature
        typedef CObject inherited;
  //## end ZBFieldColumn%3881998D038A.initialDeclarations

  public:
    //## Constructors (generated)
      ZBFieldColumn();

      ZBFieldColumn(const ZBFieldColumn &right);

    //## Constructors (specified)
      //## Operation: ZBFieldColumn%948017507
      //    Another constructor.
      ZBFieldColumn (const CString HeaderName, const CStringArray& Values);

      //## Operation: ZBFieldColumn%948222400
      //    Another constructor.
      ZBFieldColumn (const CString HeaderName, size_t Width = 40);

    //## Destructor (generated)
      virtual ~ZBFieldColumn();

    //## Assignment Operation (generated)
      const ZBFieldColumn & operator=(const ZBFieldColumn &right);


    //## Other Operations (specified)
      //## Operation: Serialize%948017485
      //    Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: Clone%948017487
      //    Make a clone of the object.
      virtual ZBFieldColumn* Clone ();

      //## Operation: GetValueCount%948017499
      //    Return the number of values.
      size_t GetValueCount () const;

      //## Operation: GetValueAt%948017500
      //    Return the value at the specific index.
      CString GetValueAt (size_t Index) const;

      //## Operation: AddValue%948017501
      //    Add a new value into the ValueArray.
      void AddValue (const CString& Value);

      //## Operation: InsertValueAt%948017502
      //    Insert a new value into the ValueArray at a specific
      //    position.
      void InsertValueAt (const CString& Value, size_t Index);

      //## Operation: SetValueAt%948222401
      //    Set a new value into the ValueArray at a specific
      //    position.
      void SetValueAt (const CString& Value, size_t Index);

      //## Operation: RemoveValue%948017503
      //    Remove a specific value from the manager.
      bool RemoveValue (const CString& Value);

      //## Operation: RemoveValueAt%948017504
      //    Remove the value at the specific index.
      bool RemoveValueAt (size_t Index);

      //## Operation: GetValueArray%948017505
      //    Fill the array with column values.
      //    return the number of elements.
      const CStringArray& GetValueArray () const;

      //## Operation: FreeValueArray%948017506
      //    remove all the values from the value array.
      void FreeValueArray ();

      //## Operation: AutoSizeColumn%948017529
      //    Auto size the column.
      void AutoSizeColumn ();

      //## Operation: GetValueRow%948400970
      //    Return the row of a value.
      int GetValueRow (const CString& Value);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: HeaderName%3881A7F4029C
      //    The column header name.
      const CString GetHeaderName () const;
      void SetHeaderName (CString value);

      //## Attribute: Width%3881F15500A8
      //    The column width.
      const size_t GetWidth () const;
      void SetWidth (size_t value);

    // Additional Public Declarations
      //## begin ZBFieldColumn%3881998D038A.public preserve=yes
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
      //## end ZBFieldColumn%3881998D038A.public
  protected:
    // Additional Protected Declarations
      //## begin ZBFieldColumn%3881998D038A.protected preserve=yes
    DECLARE_SERIAL(ZBFieldColumn)
      //## end ZBFieldColumn%3881998D038A.protected
  private:
    // Data Members for Class Attributes

      //## begin ZBFieldColumn::HeaderName%3881A7F4029C.attr preserve=no  public: CString {U} 
      CString m_HeaderName;
      //## end ZBFieldColumn::HeaderName%3881A7F4029C.attr

      //## begin ZBFieldColumn::Width%3881F15500A8.attr preserve=no  public: size_t {U} 
      size_t m_Width;
      //## end ZBFieldColumn::Width%3881F15500A8.attr

      //## Attribute: ValueArray%3881A80E00D6
      //    The array containing the values.
      //## begin ZBFieldColumn::ValueArray%3881A80E00D6.attr preserve=no  private: CStringArray {U} 
      CStringArray m_ValueArray;
      //## end ZBFieldColumn::ValueArray%3881A80E00D6.attr

    // Additional Private Declarations
      //## begin ZBFieldColumn%3881998D038A.private preserve=yes
      //## end ZBFieldColumn%3881998D038A.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZBFieldColumn%3881998D038A.implementation preserve=yes
      //## end ZBFieldColumn%3881998D038A.implementation

};

//## begin ZBFieldColumn%3881998D038A.postscript preserve=yes
//## end ZBFieldColumn%3881998D038A.postscript

// Class ZBFieldColumn 


//## Other Operations (inline)
inline size_t ZBFieldColumn::GetValueCount () const
{
  //## begin ZBFieldColumn::GetValueCount%948017499.body preserve=yes
    return m_ValueArray.GetSize();
  //## end ZBFieldColumn::GetValueCount%948017499.body
}

inline const CStringArray& ZBFieldColumn::GetValueArray () const
{
  //## begin ZBFieldColumn::GetValueArray%948017505.body preserve=yes
    return m_ValueArray;
  //## end ZBFieldColumn::GetValueArray%948017505.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const CString ZBFieldColumn::GetHeaderName () const
{
  //## begin ZBFieldColumn::GetHeaderName%3881A7F4029C.get preserve=no
  return m_HeaderName;
  //## end ZBFieldColumn::GetHeaderName%3881A7F4029C.get
}

inline void ZBFieldColumn::SetHeaderName (CString value)
{
  //## begin ZBFieldColumn::SetHeaderName%3881A7F4029C.set preserve=no
  m_HeaderName = value;
  //## end ZBFieldColumn::SetHeaderName%3881A7F4029C.set
}

inline const size_t ZBFieldColumn::GetWidth () const
{
  //## begin ZBFieldColumn::GetWidth%3881F15500A8.get preserve=no
  return m_Width;
  //## end ZBFieldColumn::GetWidth%3881F15500A8.get
}

inline void ZBFieldColumn::SetWidth (size_t value)
{
  //## begin ZBFieldColumn::SetWidth%3881F15500A8.set preserve=no
  m_Width = value;
  //## end ZBFieldColumn::SetWidth%3881F15500A8.set
}

//## begin module%38819A270147.epilog preserve=yes
//## end module%38819A270147.epilog


#endif
