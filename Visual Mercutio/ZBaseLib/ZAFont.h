//## begin module%33CA55BC01C2.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%33CA55BC01C2.cm

//## begin module%33CA55BC01C2.cp preserve=no
//## end module%33CA55BC01C2.cp

//## Module: ZAFont%33CA55BC01C2; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZAFont.h

#ifndef ZAFont_h
#define ZAFont_h 1

//## begin module%33CA55BC01C2.additionalIncludes preserve=no
//## end module%33CA55BC01C2.additionalIncludes

//## begin module%33CA55BC01C2.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%33CA55BC01C2.includes

// Mfc
#include "Mfc.h"
//## begin module%33CA55BC01C2.declarations preserve=no
//## end module%33CA55BC01C2.declarations

//## begin module%33CA55BC01C2.additionalDeclarations preserve=yes

typedef 	LONG	HandleFont;
const		LONG	NoFontDefined = -1;
//## end module%33CA55BC01C2.additionalDeclarations


//## begin ZAFont%33CA554D0078.preface preserve=yes
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
//## end ZAFont%33CA554D0078.preface

//## Class: ZAFont%33CA554D0078
//## Category: ZUtil library::Font & Style classes%36F91D94013C
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZAFont : public CFont  //## Inherits: <unnamed>%33CA55530258
{
  //## begin ZAFont%33CA554D0078.initialDeclarations preserve=yes
	public:
	// Inherited feature
		typedef CFont inherited;
  //## end ZAFont%33CA554D0078.initialDeclarations

  public:
    //## Constructors (generated)
      ZAFont();

      ZAFont(const ZAFont &right);

    //## Destructor (generated)
      virtual ~ZAFont();

    //## Assignment Operation (generated)
      const ZAFont & operator=(const ZAFont &right);


    //## Other Operations (specified)
      //## Operation: Clone%868898986
      //	Make a clone of the object.
      virtual ZAFont* Clone ();

      //## Operation: Serialize%868898987
      //	Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: GetFontColor%869402479
      //	Return the color of the font.
      COLORREF GetFontColor () const;

      //## Operation: SetFontColor%869402480
      //	Assign a new color to the font.
      void SetFontColor (COLORREF col);

      //## Operation: Create%870115417
      //	Create a font with a LOGFONT and a color
      BOOL Create (LOGFONT* pLogFont, COLORREF col = RGB(0,0,0));

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: hFontNumber%33CA568802D0
      const HandleFont GethFontNumber () const;
      void SethFontNumber (HandleFont value);

    // Additional Public Declarations
      //## begin ZAFont%33CA554D0078.public preserve=yes
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
      //## end ZAFont%33CA554D0078.public
  protected:
    // Additional Protected Declarations
      //## begin ZAFont%33CA554D0078.protected preserve=yes
	DECLARE_SERIAL(ZAFont)
      //## end ZAFont%33CA554D0078.protected
  private:
    // Data Members for Class Attributes

      //## begin ZAFont::hFontNumber%33CA568802D0.attr preserve=no  public: HandleFont {V} -1
      HandleFont m_hFontNumber;
      //## end ZAFont::hFontNumber%33CA568802D0.attr

      //## Attribute: colFont%33D204340186
      //	The color of the font.
      //## begin ZAFont::colFont%33D204340186.attr preserve=no  public: COLORREF {U} 
      COLORREF m_colFont;
      //## end ZAFont::colFont%33D204340186.attr

    // Additional Private Declarations
      //## begin ZAFont%33CA554D0078.private preserve=yes
      //## end ZAFont%33CA554D0078.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin ZAFont%33CA554D0078.implementation preserve=yes
      //## end ZAFont%33CA554D0078.implementation

};

//## begin ZAFont%33CA554D0078.postscript preserve=yes
//## end ZAFont%33CA554D0078.postscript

// Class ZAFont 


//## Other Operations (inline)
inline COLORREF ZAFont::GetFontColor () const
{
  //## begin ZAFont::GetFontColor%869402479.body preserve=yes
  	return m_colFont;
  //## end ZAFont::GetFontColor%869402479.body
}

inline void ZAFont::SetFontColor (COLORREF col)
{
  //## begin ZAFont::SetFontColor%869402480.body preserve=yes
  	m_colFont = col;
  //## end ZAFont::SetFontColor%869402480.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const HandleFont ZAFont::GethFontNumber () const
{
  //## begin ZAFont::GethFontNumber%33CA568802D0.get preserve=no
  return m_hFontNumber;
  //## end ZAFont::GethFontNumber%33CA568802D0.get
}

inline void ZAFont::SethFontNumber (HandleFont value)
{
  //## begin ZAFont::SethFontNumber%33CA568802D0.set preserve=no
  m_hFontNumber = value;
  //## end ZAFont::SethFontNumber%33CA568802D0.set
}

//## begin module%33CA55BC01C2.epilog preserve=yes
//## end module%33CA55BC01C2.epilog


#endif
