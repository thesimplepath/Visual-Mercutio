//## begin module%334FC46302EF.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC46302EF.cm

//## begin module%334FC46302EF.cp preserve=no
//## end module%334FC46302EF.cp

//## Module: ZAText%334FC46302EF; Package specification
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\PLANFIN\ZAText.h

#ifndef ZAText_h
#define ZAText_h 1

//## begin module%334FC46302EF.additionalIncludes preserve=no
//## end module%334FC46302EF.additionalIncludes

//## begin module%334FC46302EF.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%334FC46302EF.includes

// ZAAscii
#include "PSS_PLFNAscii.h"
//## begin module%334FC46302EF.declarations preserve=no
//## end module%334FC46302EF.declarations

//## begin module%334FC46302EF.additionalDeclarations preserve=yes
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
//## end module%334FC46302EF.additionalDeclarations


//## begin PLFNText%334FC46102A4.preface preserve=yes
//## end PLFNText%334FC46102A4.preface

//## Class: PLFNText%334FC46102A4
//    Visual objects functionnalities.
//## Category: PlanFin::Objects%334FC461017C
//## Subsystem: PlanFin%334FC46302B2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS PLFNText : public PSS_PLFNAscii
{
  //## begin PLFNText%334FC46102A4.initialDeclarations preserve=yes
    public:
    // Inherited feature
        typedef PSS_PLFNAscii inherited;
  //## end PLFNText%334FC46102A4.initialDeclarations

  public:
    //## Constructors (generated)
      PLFNText();

      PLFNText(const PLFNText &right);

    //## Destructor (generated)
      virtual ~PLFNText();

    //## Assignment Operation (generated)
      const PLFNText & operator=(const PLFNText &right);


    //## Other Operations (specified)
      //## Operation: operator =%829516133
      //    A copy constructor with a pointer.
      const PLFNText& operator = (const PLFNText* right);

      //## Operation: GetFormattedObject%829516158
      //    Format the object with the current object's attributes.
      //## Semantics:
      //    This function return the string
      //    represented the object formatted
      //    with the current format type
      //    this function is virtual
      //    The base function returns an empty string
      virtual CString GetFormattedObject ();

      //## Operation: ConvertFormattedObject%829516157
      //    Convert a formatted object to numeric, date, string, etc.
      //    Returns true if the value has changed.
      //## Semantics:
      //    This function convert the string
      //    and set the object with the right value
      //    For the base class nothing to do
      virtual BOOL ConvertFormattedObject (const CString& sValue, BOOL bLocateFormat = TRUE, BOOL EmptyWhenZero = FALSE);

      //## Operation: IsSelected%829516175
      //    Is this object selected.
      virtual BOOL IsSelected (const CPoint& point) const;

      //## Operation: Serialize%829516183
      //    Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: GetContains%831692953
      //    Return the contains of the text. The parameter strLine
      //    contains the definition of the object and the function
      //    retreive the contains from this line.
      void GetContains (const CString& line);

      //## Operation: Clone%849755977
      //    Make a clone of the object.
      virtual PlanFinObject* Clone ();

      //## Operation: CopyObject%863615082
      virtual void CopyObject (PlanFinObject* pSrc);

      //## Operation: GetUnformattedObject%901298463
      //    Return an unformatted string of the object image.
      virtual CString GetUnformattedObject ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Str%334FC46102D4
      //    The text object.
      const CString& GetStr () const;
      void SetStr (const CString& value);

      //## Attribute: IsStatic%351647DA037A
      //    Defines if the field is static or not.
      virtual const BOOL GetIsStatic () const;
      virtual void SetIsStatic (BOOL value);

    // Additional Public Declarations
      //## begin PLFNText%334FC46102A4.public preserve=yes
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
      //## end PLFNText%334FC46102A4.public
  protected:
    // Data Members for Class Attributes

      //## begin PLFNText::Str%334FC46102D4.attr preserve=no  public: CString {V} 
      CString m_Str;
      //## end PLFNText::Str%334FC46102D4.attr

    // Additional Protected Declarations
      //## begin PLFNText%334FC46102A4.protected preserve=yes
        DECLARE_SERIAL(PLFNText)
      //## end PLFNText%334FC46102A4.protected
  private:
    // Data Members for Class Attributes

      //## begin PLFNText::IsStatic%351647DA037A.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_IsStatic;
      //## end PLFNText::IsStatic%351647DA037A.attr

    // Additional Private Declarations
      //## begin PLFNText%334FC46102A4.private preserve=yes
      //## end PLFNText%334FC46102A4.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin PLFNText%334FC46102A4.implementation preserve=yes
      //## end PLFNText%334FC46102A4.implementation

};

//## begin PLFNText%334FC46102A4.postscript preserve=yes
//## end PLFNText%334FC46102A4.postscript

// Class PLFNText 


//## Other Operations (inline)
inline BOOL PLFNText::IsSelected (const CPoint& point) const
{
  //## begin PLFNText::IsSelected%829516175.body preserve=yes
    return( m_rctObject.PtInRect( point ) );
  //## end PLFNText::IsSelected%829516175.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const CString& PLFNText::GetStr () const
{
  //## begin PLFNText::GetStr%334FC46102D4.get preserve=no
  return m_Str;
  //## end PLFNText::GetStr%334FC46102D4.get
}

inline void PLFNText::SetStr (const CString& value)
{
  //## begin PLFNText::SetStr%334FC46102D4.set preserve=no
  m_Str = value;
  //## end PLFNText::SetStr%334FC46102D4.set
}

inline const BOOL PLFNText::GetIsStatic () const
{
  //## begin PLFNText::GetIsStatic%351647DA037A.get preserve=no
  return m_IsStatic;
  //## end PLFNText::GetIsStatic%351647DA037A.get
}

inline void PLFNText::SetIsStatic (BOOL value)
{
  //## begin PLFNText::SetIsStatic%351647DA037A.set preserve=no
  m_IsStatic = value;
  //## end PLFNText::SetIsStatic%351647DA037A.set
}

//## begin module%334FC46302EF.epilog preserve=yes
//## end module%334FC46302EF.epilog


#endif
