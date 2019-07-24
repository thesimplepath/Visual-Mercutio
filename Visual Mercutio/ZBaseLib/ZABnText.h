//## begin module%334FC46302F2.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%334FC46302F2.cm

//## begin module%334FC46302F2.cp preserve=no
//    ADSoft Copyright 1994-1995
//    Dominique Aigroz
//## end module%334FC46302F2.cp

//## Module: ZABnText%334FC46302F2; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZABnText.h

#ifndef ZABnText_h
#define ZABnText_h 1

//## begin module%334FC46302F2.additionalIncludes preserve=no
//## end module%334FC46302F2.additionalIncludes

//## begin module%334FC46302F2.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%334FC46302F2.includes

// ZAString
#include "ZAString.h"
//## begin module%334FC46302F2.declarations preserve=no
//## end module%334FC46302F2.declarations

//## begin module%334FC46302F2.additionalDeclarations preserve=yes
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
//## end module%334FC46302F2.additionalDeclarations


//## Class: PLFNBoundText%334FC461030D
//    Bound Text is class that is like String but let the text
//    be wrapped into a bound.
//## Category: ZBaseLib::Base objects%37E9429A0111
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS PLFNBoundText : public PLFNString  //## Inherits: <unnamed>%334FC461030E
{
  //## begin PLFNBoundText%334FC461030D.initialDeclarations preserve=yes
    public:
    // Inherited feature
        typedef PLFNString inherited;
          virtual UINT GetRightSubMenu() const { return g_BoundTextRightSubMenu; };
  //## end PLFNBoundText%334FC461030D.initialDeclarations

  public:
    //## Constructors (generated)
      PLFNBoundText(const PLFNBoundText &right);

    //## Constructors (specified)
      //## Operation: PLFNBoundText%829516132
      //    A constructor with as default parameter, Static = False.
      PLFNBoundText (BOOL bStatic = FALSE);

    //## Destructor (generated)
      virtual ~PLFNBoundText();

    //## Assignment Operation (generated)
      const PLFNBoundText & operator=(const PLFNBoundText &right);


    //## Other Operations (specified)
      //## Operation: operator =%829516133
      //    A copy constructor with a pointer.
      const PLFNBoundText& operator = (const PLFNBoundText* right);

      //## Operation: Clone%849755977
      //    Make a clone of the object.
      virtual PlanFinObject* Clone ();

      //## Operation: CopyObject%863615084
      virtual void CopyObject (PlanFinObject* pSrc);

      //## Operation: DrawObject%882107400
      //    Draw the object with the current DC.
      virtual void DrawObject (CDC* pDC, ZIView* pView);

      //## Operation: DrawEmpty%882107401
      //    Draw an empty object with the current DC.
      virtual void DrawEmpty (CDC* pDC, ZIView* pView);

      //## Operation: Serialize%882107402
      //    Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: GetPropertyTabs%885128493
      //    Return the list of tabs that should be displayed when
      //    the user asks for object properties.
      virtual UINT GetPropertyTabs () const;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Hanging%34AFD8000276
      //    Defines the hanging in centimeters.
      const double GetHanging () const;
      void SetHanging (double value);

      //## Attribute: HangingLines%34AFDD6D00D2
      //    Defines the number of lines that must follow the hanging.
      const UINT GetHangingLines () const;
      void SetHangingLines (UINT value);

      //## Attribute: InterLine%34AFDDF703B6
      //    Defines the interline value. Expressed in centimeters.
      const double GetInterLine () const;
      void SetInterLine (double value);

    // Additional Public Declarations
      //## begin PLFNBoundText%334FC461030D.public preserve=yes
      //## end PLFNBoundText%334FC461030D.public

  protected:
    // Additional Protected Declarations
      //## begin PLFNBoundText%334FC461030D.protected preserve=yes
    DECLARE_SERIAL(PLFNBoundText)
      //## end PLFNBoundText%334FC461030D.protected
  private:
    // Data Members for Class Attributes

      //## begin PLFNBoundText::Hanging%34AFD8000276.attr preserve=no  public: double {U} 0
      double m_Hanging;
      //## end PLFNBoundText::Hanging%34AFD8000276.attr

      //## begin PLFNBoundText::HangingLines%34AFDD6D00D2.attr preserve=no  public: UINT {U} 0
      UINT m_HangingLines;
      //## end PLFNBoundText::HangingLines%34AFDD6D00D2.attr

      //## begin PLFNBoundText::InterLine%34AFDDF703B6.attr preserve=no  public: double {U} 0
      double m_InterLine;
      //## end PLFNBoundText::InterLine%34AFDDF703B6.attr

    // Additional Private Declarations
      //## begin PLFNBoundText%334FC461030D.private preserve=yes
      //## end PLFNBoundText%334FC461030D.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin PLFNBoundText%334FC461030D.implementation preserve=yes
      //## end PLFNBoundText%334FC461030D.implementation

};

//## begin PLFNBoundText%334FC461030D.postscript preserve=yes
//## end PLFNBoundText%334FC461030D.postscript

// Class PLFNBoundText 


//## Other Operations (inline)
inline UINT PLFNBoundText::GetPropertyTabs () const
{
  //## begin PLFNBoundText::GetPropertyTabs%885128493.body preserve=yes
      return PropertyGeneralBoundTextPage | PropertySizePage | PropertyBoundTextPage;
  //## end PLFNBoundText::GetPropertyTabs%885128493.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const double PLFNBoundText::GetHanging () const
{
  //## begin PLFNBoundText::GetHanging%34AFD8000276.get preserve=no
  return m_Hanging;
  //## end PLFNBoundText::GetHanging%34AFD8000276.get
}

inline void PLFNBoundText::SetHanging (double value)
{
  //## begin PLFNBoundText::SetHanging%34AFD8000276.set preserve=no
  m_Hanging = value;
  //## end PLFNBoundText::SetHanging%34AFD8000276.set
}

inline const UINT PLFNBoundText::GetHangingLines () const
{
  //## begin PLFNBoundText::GetHangingLines%34AFDD6D00D2.get preserve=no
  return m_HangingLines;
  //## end PLFNBoundText::GetHangingLines%34AFDD6D00D2.get
}

inline void PLFNBoundText::SetHangingLines (UINT value)
{
  //## begin PLFNBoundText::SetHangingLines%34AFDD6D00D2.set preserve=no
  m_HangingLines = value;
  //## end PLFNBoundText::SetHangingLines%34AFDD6D00D2.set
}

inline const double PLFNBoundText::GetInterLine () const
{
  //## begin PLFNBoundText::GetInterLine%34AFDDF703B6.get preserve=no
  return m_InterLine;
  //## end PLFNBoundText::GetInterLine%34AFDDF703B6.get
}

inline void PLFNBoundText::SetInterLine (double value)
{
  //## begin PLFNBoundText::SetInterLine%34AFDDF703B6.set preserve=no
  m_InterLine = value;
  //## end PLFNBoundText::SetInterLine%34AFDDF703B6.set
}

//## begin module%334FC46302F2.epilog preserve=yes
//## end module%334FC46302F2.epilog


#endif
