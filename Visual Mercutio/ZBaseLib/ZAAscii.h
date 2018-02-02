//## begin module%334FC4630323.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%334FC4630323.cm

//## begin module%334FC4630323.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%334FC4630323.cp

//## Module: ZAAscii%334FC4630323; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZAAscii.h

#ifndef ZAAscii_h
#define ZAAscii_h 1

//## begin module%334FC4630323.additionalIncludes preserve=no
//## end module%334FC4630323.additionalIncludes

//## begin module%334FC4630323.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT



// Define different type of strikes
enum	StrikeStyles{ NormalStrike, UpDownStrike, CrossStrike, WaveStrike };
//## end module%334FC4630323.includes

// ZAObject
#include "ZAObject.h"
//## begin module%334FC4630323.declarations preserve=no
//## end module%334FC4630323.declarations

//## begin module%334FC4630323.additionalDeclarations preserve=yes
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
//## end module%334FC4630323.additionalDeclarations


//## Class: PLFNAscii%334FC4610319
//	Non graphic objects functionnalities.
//## Category: ZBaseLib::Base objects%37E9429A0111
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS PLFNAscii : public PlanFinObject  //## Inherits: <unnamed>%334FC461031A
{
  //## begin PLFNAscii%334FC4610319.initialDeclarations preserve=yes
	public:
	// Inherited feature
		typedef PlanFinObject inherited;
  //## end PLFNAscii%334FC4610319.initialDeclarations

  public:
    //## Constructors (generated)
      PLFNAscii();

      PLFNAscii(const PLFNAscii &right);

    //## Destructor (generated)
      virtual ~PLFNAscii();

    //## Assignment Operation (generated)
      const PLFNAscii & operator=(const PLFNAscii &right);


    //## Other Operations (specified)
      //## Operation: operator =%829516133
      //	A copy constructor with a pointer.
      const PLFNAscii& operator = (const PLFNAscii* right);

      //## Operation: Serialize%829516183
      //	Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: GetJustify%833261594
      virtual UINT GetJustify (ZDDocument* pDoc) const;

      //## Operation: SetJustify%833261595
      virtual void SetJustify (UINT nValue);

      //## Operation: Clone%849755977
      //	Make a clone of the object.
      PlanFinObject* Clone ();

      //## Operation: GetPropertyTabs%885128491
      //	Return the list of tabs that should be displayed when
      //	the user asks for object properties.
      virtual UINT GetPropertyTabs () const;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: IsStriked%34AFE22C01EA
      //	Defines if the object is striked.
      const BOOL GetIsStriked () const;
      void SetIsStriked (BOOL value);

      //## Attribute: StrikeStyle%34AFE28D02F8
      //	Defines the style of the strike.
      const StrikeStyles GetStrikeStyle () const;
      void SetStrikeStyle (StrikeStyles value);

      //## Attribute: KeepHistory%3618FD610182
      //	Flag that defines if the field must keep an history of
      //	values entered.
      const BOOL GetKeepHistory () const;
      void SetKeepHistory (BOOL value);

    // Additional Public Declarations
      //## begin PLFNAscii%334FC4610319.public preserve=yes
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
      //## end PLFNAscii%334FC4610319.public
  protected:
    // Additional Protected Declarations
      //## begin PLFNAscii%334FC4610319.protected preserve=yes
	DECLARE_SERIAL(PLFNAscii)
      //## end PLFNAscii%334FC4610319.protected
  private:
    // Data Members for Class Attributes

      //## Attribute: iJustify%334FC461033D
      //	Define how to justify the text.
      //## begin PLFNAscii::iJustify%334FC461033D.attr preserve=no  public: UINT {U} NoAlignement
      UINT m_iJustify;
      //## end PLFNAscii::iJustify%334FC461033D.attr

      //## begin PLFNAscii::IsStriked%34AFE22C01EA.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_IsStriked;
      //## end PLFNAscii::IsStriked%34AFE22C01EA.attr

      //## begin PLFNAscii::StrikeStyle%34AFE28D02F8.attr preserve=no  public: StrikeStyles {U} NormalStrike
      StrikeStyles m_StrikeStyle;
      //## end PLFNAscii::StrikeStyle%34AFE28D02F8.attr

      //## begin PLFNAscii::KeepHistory%3618FD610182.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_KeepHistory;
      //## end PLFNAscii::KeepHistory%3618FD610182.attr

    // Additional Private Declarations
      //## begin PLFNAscii%334FC4610319.private preserve=yes
      //## end PLFNAscii%334FC4610319.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin PLFNAscii%334FC4610319.implementation preserve=yes
      //## end PLFNAscii%334FC4610319.implementation

};

//## begin PLFNAscii%334FC4610319.postscript preserve=yes
//## end PLFNAscii%334FC4610319.postscript

// Class PLFNAscii 


//## Other Operations (inline)
inline void PLFNAscii::SetJustify (UINT nValue)
{
  //## begin PLFNAscii::SetJustify%833261595.body preserve=yes
  	m_iJustify = nValue;
  //## end PLFNAscii::SetJustify%833261595.body
}

inline UINT PLFNAscii::GetPropertyTabs () const
{
  //## begin PLFNAscii::GetPropertyTabs%885128491.body preserve=yes
  	return PropertyGeneralTextPage | PropertySizePage;
  //## end PLFNAscii::GetPropertyTabs%885128491.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const BOOL PLFNAscii::GetIsStriked () const
{
  //## begin PLFNAscii::GetIsStriked%34AFE22C01EA.get preserve=no
  return m_IsStriked;
  //## end PLFNAscii::GetIsStriked%34AFE22C01EA.get
}

inline void PLFNAscii::SetIsStriked (BOOL value)
{
  //## begin PLFNAscii::SetIsStriked%34AFE22C01EA.set preserve=no
  m_IsStriked = value;
  //## end PLFNAscii::SetIsStriked%34AFE22C01EA.set
}

inline const StrikeStyles PLFNAscii::GetStrikeStyle () const
{
  //## begin PLFNAscii::GetStrikeStyle%34AFE28D02F8.get preserve=no
  return m_StrikeStyle;
  //## end PLFNAscii::GetStrikeStyle%34AFE28D02F8.get
}

inline void PLFNAscii::SetStrikeStyle (StrikeStyles value)
{
  //## begin PLFNAscii::SetStrikeStyle%34AFE28D02F8.set preserve=no
  m_StrikeStyle = value;
  //## end PLFNAscii::SetStrikeStyle%34AFE28D02F8.set
}

inline const BOOL PLFNAscii::GetKeepHistory () const
{
  //## begin PLFNAscii::GetKeepHistory%3618FD610182.get preserve=no
  return m_KeepHistory;
  //## end PLFNAscii::GetKeepHistory%3618FD610182.get
}

inline void PLFNAscii::SetKeepHistory (BOOL value)
{
  //## begin PLFNAscii::SetKeepHistory%3618FD610182.set preserve=no
  m_KeepHistory = value;
  //## end PLFNAscii::SetKeepHistory%3618FD610182.set
}

//## begin module%334FC4630323.epilog preserve=yes
//## end module%334FC4630323.epilog


#endif
