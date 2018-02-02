//## begin module%33747B910140.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%33747B910140.cm

//## begin module%33747B910140.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%33747B910140.cp

//## Module: ZAGraphc%33747B910140; Package specification
//## Subsystem: PlanFin%334FC46302B2
//## Source file: z:\adsoft~1\ZDesigner\ZAGraphc.h

#ifndef ZAGraphc_h
#define ZAGraphc_h 1

//## begin module%33747B910140.additionalIncludes preserve=no
//## end module%33747B910140.additionalIncludes

//## begin module%33747B910140.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%33747B910140.includes

// ZAObject
#include "ZAObject.h"
//## begin module%33747B910140.declarations preserve=no
//## end module%33747B910140.declarations

//## begin module%33747B910140.additionalDeclarations preserve=yes
//## end module%33747B910140.additionalDeclarations


//## begin PLFNGraphic%33747B5B0226.preface preserve=yes
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
//## end PLFNGraphic%33747B5B0226.preface

//## Class: PLFNGraphic%33747B5B0226
//	Graphic object functionnalities.
//## Category: PlanFin::Objects%334FC461017C
//## Subsystem: PlanFin%334FC46302B2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS PLFNGraphic : public PlanFinObject  //## Inherits: <unnamed>%33747B5B0227
{
  //## begin PLFNGraphic%33747B5B0226.initialDeclarations preserve=yes
	public:
	// Inherited feature
		typedef PlanFinObject inherited;
  //## end PLFNGraphic%33747B5B0226.initialDeclarations

  public:
    //## Constructors (generated)
      PLFNGraphic();

      PLFNGraphic(const PLFNGraphic &right);

    //## Destructor (generated)
      virtual ~PLFNGraphic();

    //## Assignment Operation (generated)
      const PLFNGraphic & operator=(const PLFNGraphic &right);


    //## Other Operations (specified)
      //## Operation: operator =%863265788
      //	A copy constructor with a pointer.
      const PLFNGraphic& operator = (const PLFNGraphic* right);

      //## Operation: Serialize%863265789
      //	Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: Clone%863265790
      //	Make a clone of the object.
      virtual PlanFinObject* Clone ();

      //## Operation: GetGraphicPen%863265791
      //	With the pen passed in parameters, build a corresponding
      //	pen to the graphic color and the width.
      CPen& GetGraphicPen (CPen& pen);

      //## Operation: GetGraphicBrush%863265792
      //	Return a brush corresponding to the brush defined in the
      //	object. The brush returned is the brush passed in
      //	parameter.
      CBrush& GetGraphicBrush (CBrush& brush);

      //## Operation: CopyObject%863615077
      virtual void CopyObject (PlanFinObject* pSrc);

      //## Operation: GetRightSubMenu%864336731
      //	Return the number of the submenu when the user click the
      //	right mouse button.
      virtual UINT GetRightSubMenu () const;

      //## Operation: GetPropertyTabs%925634619
      //	Return the list of tabs that should be displayed when
      //	the user asks for object properties.
      virtual UINT GetPropertyTabs () const;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: GraphicColor%33747C220258
      //	Define the color of graphic object.
      const COLORREF GetGraphicColor () const;
      void SetGraphicColor (COLORREF value);

      //## Attribute: GraphicWidth%33747C5A02A8
      //	Define the widht of all graphic objects.
      const WORD GetGraphicWidth () const;
      void SetGraphicWidth (WORD value);

      //## Attribute: bShadow%33747CC900BE
      //	Define if the graphic object has a shadow
      const BOOL GetbShadow () const;
      void SetbShadow (BOOL value);

      //## Attribute: GraphicStyle%3374812403B6
      //	Define the style of the graphic object.
      const WORD GetGraphicStyle () const;
      void SetGraphicStyle (WORD value);

    // Additional Public Declarations
      //## begin PLFNGraphic%33747B5B0226.public preserve=yes
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
      //## end PLFNGraphic%33747B5B0226.public
  protected:
    // Additional Protected Declarations
      //## begin PLFNGraphic%33747B5B0226.protected preserve=yes
	DECLARE_SERIAL(PLFNGraphic)
      //## end PLFNGraphic%33747B5B0226.protected
  private:
    // Data Members for Class Attributes

      //## begin PLFNGraphic::GraphicColor%33747C220258.attr preserve=no  public: COLORREF {U} defCOLOR_BLACK
      COLORREF m_GraphicColor;
      //## end PLFNGraphic::GraphicColor%33747C220258.attr

      //## begin PLFNGraphic::GraphicWidth%33747C5A02A8.attr preserve=no  public: WORD {U} 1
      WORD m_GraphicWidth;
      //## end PLFNGraphic::GraphicWidth%33747C5A02A8.attr

      //## begin PLFNGraphic::bShadow%33747CC900BE.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_bShadow;
      //## end PLFNGraphic::bShadow%33747CC900BE.attr

      //## begin PLFNGraphic::GraphicStyle%3374812403B6.attr preserve=no  public: WORD {U} PS_SOLID
      WORD m_GraphicStyle;
      //## end PLFNGraphic::GraphicStyle%3374812403B6.attr

    // Additional Private Declarations
      //## begin PLFNGraphic%33747B5B0226.private preserve=yes
      //## end PLFNGraphic%33747B5B0226.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin PLFNGraphic%33747B5B0226.implementation preserve=yes
      //## end PLFNGraphic%33747B5B0226.implementation

};

//## begin PLFNGraphic%33747B5B0226.postscript preserve=yes
//## end PLFNGraphic%33747B5B0226.postscript

// Class PLFNGraphic 


//## Other Operations (inline)
inline UINT PLFNGraphic::GetRightSubMenu () const
{
  //## begin PLFNGraphic::GetRightSubMenu%864336731.body preserve=yes
  	return GraphicRightSubMenu;
  //## end PLFNGraphic::GetRightSubMenu%864336731.body
}

inline UINT PLFNGraphic::GetPropertyTabs () const
{
  //## begin PLFNGraphic::GetPropertyTabs%925634619.body preserve=yes
  	return PropertyGeneralBasicPage | PropertySizePage;
  //## end PLFNGraphic::GetPropertyTabs%925634619.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const COLORREF PLFNGraphic::GetGraphicColor () const
{
  //## begin PLFNGraphic::GetGraphicColor%33747C220258.get preserve=no
  return m_GraphicColor;
  //## end PLFNGraphic::GetGraphicColor%33747C220258.get
}

inline void PLFNGraphic::SetGraphicColor (COLORREF value)
{
  //## begin PLFNGraphic::SetGraphicColor%33747C220258.set preserve=no
  m_GraphicColor = value;
  //## end PLFNGraphic::SetGraphicColor%33747C220258.set
}

inline const WORD PLFNGraphic::GetGraphicWidth () const
{
  //## begin PLFNGraphic::GetGraphicWidth%33747C5A02A8.get preserve=no
  return m_GraphicWidth;
  //## end PLFNGraphic::GetGraphicWidth%33747C5A02A8.get
}

inline void PLFNGraphic::SetGraphicWidth (WORD value)
{
  //## begin PLFNGraphic::SetGraphicWidth%33747C5A02A8.set preserve=no
  m_GraphicWidth = value;
  //## end PLFNGraphic::SetGraphicWidth%33747C5A02A8.set
}

inline const BOOL PLFNGraphic::GetbShadow () const
{
  //## begin PLFNGraphic::GetbShadow%33747CC900BE.get preserve=no
  return m_bShadow;
  //## end PLFNGraphic::GetbShadow%33747CC900BE.get
}

inline void PLFNGraphic::SetbShadow (BOOL value)
{
  //## begin PLFNGraphic::SetbShadow%33747CC900BE.set preserve=no
  m_bShadow = value;
  //## end PLFNGraphic::SetbShadow%33747CC900BE.set
}

inline const WORD PLFNGraphic::GetGraphicStyle () const
{
  //## begin PLFNGraphic::GetGraphicStyle%3374812403B6.get preserve=no
  return m_GraphicStyle;
  //## end PLFNGraphic::GetGraphicStyle%3374812403B6.get
}

inline void PLFNGraphic::SetGraphicStyle (WORD value)
{
  //## begin PLFNGraphic::SetGraphicStyle%3374812403B6.set preserve=no
  m_GraphicStyle = value;
  //## end PLFNGraphic::SetGraphicStyle%3374812403B6.set
}

//## begin module%33747B910140.epilog preserve=yes
//## end module%33747B910140.epilog


#endif
