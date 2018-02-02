//## begin module%336D05320172.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%336D05320172.cm

//## begin module%336D05320172.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%336D05320172.cp

//## Module: ZASquare%336D05320172; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZASquare.h

#ifndef ZASquare_h
#define ZASquare_h 1

//## begin module%336D05320172.additionalIncludes preserve=no
//## end module%336D05320172.additionalIncludes

//## begin module%336D05320172.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%336D05320172.includes

// ZAObject
#include "ZAObject.h"
//## begin module%336D05320172.declarations preserve=no
//## end module%336D05320172.declarations

//## begin module%336D05320172.additionalDeclarations preserve=yes
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
//## end module%336D05320172.additionalDeclarations


//## Class: PLFNSquare%336D04BA0208
//	Manage squares for formulars. One square can have only
//	one character.
//## Category: ZBaseLib::Base objects%37E9429A0111
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS PLFNSquare : public PlanFinObject  //## Inherits: <unnamed>%336D04EA0050
{
  //## begin PLFNSquare%336D04BA0208.initialDeclarations preserve=yes
	public:
	// Inherited feature
		typedef PlanFinObject inherited;
  //## end PLFNSquare%336D04BA0208.initialDeclarations

  public:
    //## Constructors (generated)
      PLFNSquare();

      PLFNSquare(const PLFNSquare &right);

    //## Constructors (specified)
      //## Operation: PLFNSquare%863099799
      PLFNSquare (CSize SquareSize, int iMaxLength);

    //## Destructor (generated)
      virtual ~PLFNSquare();

    //## Assignment Operation (generated)
      const PLFNSquare & operator=(const PLFNSquare &right);


    //## Other Operations (specified)
      //## Operation: operator =%862783356
      //	A copy constructor with a pointer.
      const PLFNSquare& operator = (const PLFNSquare* right);

      //## Operation: Clone%862783358
      //	Make a clone of the object.
      virtual PlanFinObject* Clone ();

      //## Operation: Serialize%862783359
      //	Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: DrawObject%862783360
      //	Draw the object with the current DC.
      virtual void DrawObject (CDC* pDC, ZIView* pView);

      //## Operation: CopyObject%863615081
      virtual void CopyObject (PlanFinObject* pSrc);

      //## Operation: GetPropertyTabs%885128492
      //	Return the list of tabs that should be displayed when
      //	the user asks for object properties.
      virtual UINT GetPropertyTabs () const;

      //## Operation: IsEmpty%909073220
      //	Is it an empty field.
      virtual BOOL IsEmpty () const;

      //## Operation: GetFormatedObject%909073221
      //	Format the object with the current object's attributes.
      //## Semantics:
      //	This function return the string
      //	represented the object formated
      //	with the current format type
      //	this function is virtual
      //	The base function returns an empty string
      virtual CString GetFormatedObject ();

      //## Operation: ConvertFormatedObject%909073222
      //	Convert a formatted object to numeric, date, string, etc.
      //	Returns true if the value has changed.
      //## Semantics:
      //	This function convert the string
      //	and set the object with the right value
      //	For the base class nothing to do
      virtual BOOL ConvertFormatedObject (const CString& sValue, BOOL bLocateFormat = TRUE, BOOL EmptyWhenZero = FALSE);

      //## Operation: IsSelected%909073223
      //	Is this object selected.
      virtual BOOL IsSelected (const CPoint& point) const;

      //## Operation: GetRightSubMenu%909073224
      //	Return the number of the submenu when the user click the
      //	right mouse button.
      virtual UINT GetRightSubMenu () const;

      //## Operation: GetUnformatedObject%909073225
      //	Return an unformated string of the object image.
      virtual CString GetUnformatedObject ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: SizeSquare%3371DB18029E
      //	Define the size of each square
      const CSize GetSizeSquare () const;
      void SetSizeSquare (CSize value);

      //## Attribute: SquareMaxLength%3371DB3F03B6
      //	Define the maximum length of the text included within
      //	the squares. Put -1 if you do not want to limit the
      //	input.
      const int GetSquareMaxLength () const;
      void SetSquareMaxLength (int value);

      //## Attribute: bAutoAdjustSize%3372025D0168
      const BOOL GetbAutoAdjustSize () const;
      void SetbAutoAdjustSize (BOOL value);

      //## Attribute: nCharPerSquare%3378676D00FA
      const unsigned int GetnCharPerSquare () const;
      void SetnCharPerSquare (unsigned int value);

      //## Attribute: pObject%362DF9940391
      const PlanFinObject* GetpObject () const;
      void SetpObject (PlanFinObject* value);

      //## Attribute: TypeOfSquare%36305ABB03C1
      //	Defines the way the square should be represented.
      const SquareType GetTypeOfSquare () const;
      void SetTypeOfSquare (SquareType value);

      //## Attribute: ParsingMode%36305B92030C
      //	Defines the way the parsing should be done.
      const ParsingModeType GetParsingMode () const;
      void SetParsingMode (ParsingModeType value);

    // Additional Public Declarations
      //## begin PLFNSquare%336D04BA0208.public preserve=yes
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
      //## end PLFNSquare%336D04BA0208.public
  protected:
    // Additional Protected Declarations
      //## begin PLFNSquare%336D04BA0208.protected preserve=yes
	DECLARE_SERIAL(PLFNSquare)
      //## end PLFNSquare%336D04BA0208.protected
  private:

    //## Other Operations (specified)
      //## Operation: DrawSquares%863099801
      //	Draw all squares.
      void DrawSquares (CDC* pDC);

    // Data Members for Class Attributes

      //## begin PLFNSquare::SquareMaxLength%3371DB3F03B6.attr preserve=no  public: int {V} 
      int m_SquareMaxLength;
      //## end PLFNSquare::SquareMaxLength%3371DB3F03B6.attr

      //## begin PLFNSquare::bAutoAdjustSize%3372025D0168.attr preserve=no  public: BOOL {U} 
      BOOL m_bAutoAdjustSize;
      //## end PLFNSquare::bAutoAdjustSize%3372025D0168.attr

      //## begin PLFNSquare::nCharPerSquare%3378676D00FA.attr preserve=no  public: unsigned int {U} 1
      unsigned int m_nCharPerSquare;
      //## end PLFNSquare::nCharPerSquare%3378676D00FA.attr

      //## begin PLFNSquare::pObject%362DF9940391.attr preserve=no  public: PlanFinObject* {U} NULL
      PlanFinObject* m_pObject;
      //## end PLFNSquare::pObject%362DF9940391.attr

      //## begin PLFNSquare::TypeOfSquare%36305ABB03C1.attr preserve=no  public: SquareType {U} NormalSquare
      SquareType m_TypeOfSquare;
      //## end PLFNSquare::TypeOfSquare%36305ABB03C1.attr

      //## begin PLFNSquare::ParsingMode%36305B92030C.attr preserve=no  public: ParsingModeType {U} NormalParsing
      ParsingModeType m_ParsingMode;
      //## end PLFNSquare::ParsingMode%36305B92030C.attr

    // Additional Private Declarations
      //## begin PLFNSquare%336D04BA0208.private preserve=yes
      //## end PLFNSquare%336D04BA0208.private

  private:  //## implementation
    // Data Members for Class Attributes

      //## begin PLFNSquare::SizeSquare%3371DB18029E.attr preserve=no  public: CSize {V} 
      CSize m_SizeSquare;
      //## end PLFNSquare::SizeSquare%3371DB18029E.attr

    // Additional Implementation Declarations
      //## begin PLFNSquare%336D04BA0208.implementation preserve=yes
      //## end PLFNSquare%336D04BA0208.implementation

};

//## begin PLFNSquare%336D04BA0208.postscript preserve=yes
//## end PLFNSquare%336D04BA0208.postscript

// Class PLFNSquare 


//## Other Operations (inline)
inline UINT PLFNSquare::GetPropertyTabs () const
{
  //## begin PLFNSquare::GetPropertyTabs%885128492.body preserve=yes
  	return PropertyGeneralPage | PropertySizePage | PropertySquarePage;
  //## end PLFNSquare::GetPropertyTabs%885128492.body
}

inline BOOL PLFNSquare::IsEmpty () const
{
  //## begin PLFNSquare::IsEmpty%909073220.body preserve=yes
  	if (m_pObject)
	  	return m_pObject->IsEmpty();
	return TRUE;
  //## end PLFNSquare::IsEmpty%909073220.body
}

inline BOOL PLFNSquare::IsSelected (const CPoint& point) const
{
  //## begin PLFNSquare::IsSelected%909073223.body preserve=yes
  	if (m_pObject)
	  	return m_pObject->IsSelected( point );
	return FALSE;
  //## end PLFNSquare::IsSelected%909073223.body
}

inline UINT PLFNSquare::GetRightSubMenu () const
{
  //## begin PLFNSquare::GetRightSubMenu%909073224.body preserve=yes
  	if (m_pObject)
	  	return m_pObject->GetRightSubMenu();
	return ObjectRightSubMenu;
  //## end PLFNSquare::GetRightSubMenu%909073224.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const CSize PLFNSquare::GetSizeSquare () const
{
  //## begin PLFNSquare::GetSizeSquare%3371DB18029E.get preserve=no
  return m_SizeSquare;
  //## end PLFNSquare::GetSizeSquare%3371DB18029E.get
}

inline void PLFNSquare::SetSizeSquare (CSize value)
{
  //## begin PLFNSquare::SetSizeSquare%3371DB18029E.set preserve=no
  m_SizeSquare = value;
  //## end PLFNSquare::SetSizeSquare%3371DB18029E.set
}

inline const int PLFNSquare::GetSquareMaxLength () const
{
  //## begin PLFNSquare::GetSquareMaxLength%3371DB3F03B6.get preserve=no
  return m_SquareMaxLength;
  //## end PLFNSquare::GetSquareMaxLength%3371DB3F03B6.get
}

inline void PLFNSquare::SetSquareMaxLength (int value)
{
  //## begin PLFNSquare::SetSquareMaxLength%3371DB3F03B6.set preserve=no
  m_SquareMaxLength = value;
  //## end PLFNSquare::SetSquareMaxLength%3371DB3F03B6.set
}

inline const BOOL PLFNSquare::GetbAutoAdjustSize () const
{
  //## begin PLFNSquare::GetbAutoAdjustSize%3372025D0168.get preserve=no
  return m_bAutoAdjustSize;
  //## end PLFNSquare::GetbAutoAdjustSize%3372025D0168.get
}

inline void PLFNSquare::SetbAutoAdjustSize (BOOL value)
{
  //## begin PLFNSquare::SetbAutoAdjustSize%3372025D0168.set preserve=no
  m_bAutoAdjustSize = value;
  //## end PLFNSquare::SetbAutoAdjustSize%3372025D0168.set
}

inline const unsigned int PLFNSquare::GetnCharPerSquare () const
{
  //## begin PLFNSquare::GetnCharPerSquare%3378676D00FA.get preserve=no
  return m_nCharPerSquare;
  //## end PLFNSquare::GetnCharPerSquare%3378676D00FA.get
}

inline void PLFNSquare::SetnCharPerSquare (unsigned int value)
{
  //## begin PLFNSquare::SetnCharPerSquare%3378676D00FA.set preserve=no
  m_nCharPerSquare = value;
  //## end PLFNSquare::SetnCharPerSquare%3378676D00FA.set
}

inline const PlanFinObject* PLFNSquare::GetpObject () const
{
  //## begin PLFNSquare::GetpObject%362DF9940391.get preserve=no
  return m_pObject;
  //## end PLFNSquare::GetpObject%362DF9940391.get
}

inline void PLFNSquare::SetpObject (PlanFinObject* value)
{
  //## begin PLFNSquare::SetpObject%362DF9940391.set preserve=no
  m_pObject = value;
  //## end PLFNSquare::SetpObject%362DF9940391.set
}

inline const SquareType PLFNSquare::GetTypeOfSquare () const
{
  //## begin PLFNSquare::GetTypeOfSquare%36305ABB03C1.get preserve=no
  return m_TypeOfSquare;
  //## end PLFNSquare::GetTypeOfSquare%36305ABB03C1.get
}

inline void PLFNSquare::SetTypeOfSquare (SquareType value)
{
  //## begin PLFNSquare::SetTypeOfSquare%36305ABB03C1.set preserve=no
  m_TypeOfSquare = value;
  //## end PLFNSquare::SetTypeOfSquare%36305ABB03C1.set
}

inline const ParsingModeType PLFNSquare::GetParsingMode () const
{
  //## begin PLFNSquare::GetParsingMode%36305B92030C.get preserve=no
  return m_ParsingMode;
  //## end PLFNSquare::GetParsingMode%36305B92030C.get
}

inline void PLFNSquare::SetParsingMode (ParsingModeType value)
{
  //## begin PLFNSquare::SetParsingMode%36305B92030C.set preserve=no
  m_ParsingMode = value;
  //## end PLFNSquare::SetParsingMode%36305B92030C.set
}

//## begin module%336D05320172.epilog preserve=yes
//## end module%336D05320172.epilog


#endif
