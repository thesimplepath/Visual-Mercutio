//## begin module%33D8F933017C.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%33D8F933017C.cm

//## begin module%33D8F933017C.cp preserve=no
//## end module%33D8F933017C.cp

//## Module: ZAStyle%33D8F933017C; Package specification
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZAStyle.h

#ifndef ZAStyle_h
#define ZAStyle_h 1

//## begin module%33D8F933017C.additionalIncludes preserve=no
//## end module%33D8F933017C.additionalIncludes

//## begin module%33D8F933017C.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%33D8F933017C.includes

// ZABorder
#include "ZABorder.h"
// ZAFont
#include "ZAFont.h"
// Mfc
#include "Mfc.h"
//## begin module%33D8F933017C.declarations preserve=no
//## end module%33D8F933017C.declarations

//## begin module%33D8F933017C.additionalDeclarations preserve=yes
typedef     int        HandleStyle;
const        int        NormalStyle = 0;    // Define the handle of the Normal Style
const        int        NoStyleDefined = -1;


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

//## end module%33D8F933017C.additionalDeclarations


//## begin ZAStyle%33D8F8010118.preface preserve=yes
//## end ZAStyle%33D8F8010118.preface

//## Class: ZAStyle%33D8F8010118
//    Defines what is a style.
//## Category: ZUtil library::Font & Style classes%36F91D94013C
//## Subsystem: ZUtil%366D71940075
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%33D8FC5D035C;ZAFont { -> }
//## Uses: <unnamed>%33EC6F3A035C;ZABorder { -> }

class AFX_EXT_CLASS ZAStyle : public CObject  //## Inherits: <unnamed>%33D8F81100A0
{
  //## begin ZAStyle%33D8F8010118.initialDeclarations preserve=yes
    public:
    // Inherited feature
        typedef CObject inherited;
  //## end ZAStyle%33D8F8010118.initialDeclarations

  public:
    //## Constructors (generated)
      ZAStyle();

      ZAStyle(const ZAStyle &right);

    //## Destructor (generated)
      virtual ~ZAStyle();

    //## Assignment Operation (generated)
      const ZAStyle & operator=(const ZAStyle &right);


    //## Other Operations (specified)
      //## Operation: Serialize%869857712
      //    Serialization function required for MFC mecanism.
      virtual void Serialize (CArchive& ar);

      //## Operation: Clone%869857713
      //    Make a clone of the object.
      virtual ZAStyle* Clone ();

      //## Operation: HasBorder%871228837
      //    Inform if the style has a border defined.
      BOOL HasBorder () const;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: hFont%33D8F81F0334
      //    Points to the handle of a font.
      const HandleFont GethFont () const;
      void SethFont (HandleFont value);

      //## Attribute: BackColor%33D8F86902BC
      //    Define the back color. -1 for none.
      const COLORREF GetBackColor () const;
      void SetBackColor (COLORREF value);

      //## Attribute: hStyleNumber%33D8F96B02A8
      //    Used to keep the Style Handle.
      const HandleStyle GethStyleNumber () const;
      void SethStyleNumber (HandleStyle value);

      //## Attribute: StyleName%33D8F9E803CA
      //    Stores the name of the style.
      const CString GetStyleName () const;
      void SetStyleName (CString value);

      //## Attribute: pBorder%33EC67B30136
      //    Define border for fields.
      ZABorder* GetpBorder ();
      void SetpBorder (ZABorder* value);

      //## Attribute: Justify%34118F2200B4
      //    Define the justification such as
      //    DT_LEFT
      //    DT_BOTTOM
      //    DT_SINGLELINE
      //    etc.
      const UINT GetJustify () const;
      void SetJustify (UINT value);

    // Additional Public Declarations
      //## begin ZAStyle%33D8F8010118.public preserve=yes
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
      //## end ZAStyle%33D8F8010118.public
  protected:
    // Additional Protected Declarations
      //## begin ZAStyle%33D8F8010118.protected preserve=yes
    DECLARE_SERIAL(ZAStyle)
      //## end ZAStyle%33D8F8010118.protected
  private:
    // Data Members for Class Attributes

      //## begin ZAStyle::hFont%33D8F81F0334.attr preserve=no  public: HandleFont {U} 0
      HandleFont m_hFont;
      //## end ZAStyle::hFont%33D8F81F0334.attr

      //## begin ZAStyle::BackColor%33D8F86902BC.attr preserve=no  public: COLORREF {U} -1
      COLORREF m_BackColor;
      //## end ZAStyle::BackColor%33D8F86902BC.attr

      //## begin ZAStyle::hStyleNumber%33D8F96B02A8.attr preserve=no  public: HandleStyle {U} 
      HandleStyle m_hStyleNumber;
      //## end ZAStyle::hStyleNumber%33D8F96B02A8.attr

      //## begin ZAStyle::StyleName%33D8F9E803CA.attr preserve=no  public: CString {U} 
      CString m_StyleName;
      //## end ZAStyle::StyleName%33D8F9E803CA.attr

      //## begin ZAStyle::Justify%34118F2200B4.attr preserve=no  public: UINT {U} DT_LEFT | DT_BOTTOM | DT_SINGLELINE
      UINT m_Justify;
      //## end ZAStyle::Justify%34118F2200B4.attr

    // Additional Private Declarations
      //## begin ZAStyle%33D8F8010118.private preserve=yes
      //## end ZAStyle%33D8F8010118.private

  private: //## implementation
    // Data Members for Class Attributes

      //## begin ZAStyle::pBorder%33EC67B30136.attr preserve=no  public: ZABorder* {U} NULL
      ZABorder* m_pBorder;
      //## end ZAStyle::pBorder%33EC67B30136.attr

    // Additional Implementation Declarations
      //## begin ZAStyle%33D8F8010118.implementation preserve=yes
      //## end ZAStyle%33D8F8010118.implementation

};

//## begin ZAStyle%33D8F8010118.postscript preserve=yes
//## end ZAStyle%33D8F8010118.postscript

// Class ZAStyle 


//## Other Operations (inline)
inline BOOL ZAStyle::HasBorder () const
{
  //## begin ZAStyle::HasBorder%871228837.body preserve=yes
      return m_pBorder != NULL;
  //## end ZAStyle::HasBorder%871228837.body
}

//## Get and Set Operations for Class Attributes (inline)

inline const HandleFont ZAStyle::GethFont () const
{
  //## begin ZAStyle::GethFont%33D8F81F0334.get preserve=no
  return m_hFont;
  //## end ZAStyle::GethFont%33D8F81F0334.get
}

inline void ZAStyle::SethFont (HandleFont value)
{
  //## begin ZAStyle::SethFont%33D8F81F0334.set preserve=no
  m_hFont = value;
  //## end ZAStyle::SethFont%33D8F81F0334.set
}

inline const COLORREF ZAStyle::GetBackColor () const
{
  //## begin ZAStyle::GetBackColor%33D8F86902BC.get preserve=no
  return m_BackColor;
  //## end ZAStyle::GetBackColor%33D8F86902BC.get
}

inline void ZAStyle::SetBackColor (COLORREF value)
{
  //## begin ZAStyle::SetBackColor%33D8F86902BC.set preserve=no
  m_BackColor = value;
  //## end ZAStyle::SetBackColor%33D8F86902BC.set
}

inline const HandleStyle ZAStyle::GethStyleNumber () const
{
  //## begin ZAStyle::GethStyleNumber%33D8F96B02A8.get preserve=no
  return m_hStyleNumber;
  //## end ZAStyle::GethStyleNumber%33D8F96B02A8.get
}

inline void ZAStyle::SethStyleNumber (HandleStyle value)
{
  //## begin ZAStyle::SethStyleNumber%33D8F96B02A8.set preserve=no
  m_hStyleNumber = value;
  //## end ZAStyle::SethStyleNumber%33D8F96B02A8.set
}

inline const CString ZAStyle::GetStyleName () const
{
  //## begin ZAStyle::GetStyleName%33D8F9E803CA.get preserve=no
  return m_StyleName;
  //## end ZAStyle::GetStyleName%33D8F9E803CA.get
}

inline void ZAStyle::SetStyleName (CString value)
{
  //## begin ZAStyle::SetStyleName%33D8F9E803CA.set preserve=no
  m_StyleName = value;
  //## end ZAStyle::SetStyleName%33D8F9E803CA.set
}

inline ZABorder* ZAStyle::GetpBorder ()
{
  //## begin ZAStyle::GetpBorder%33EC67B30136.get preserve=no
  return m_pBorder;
  //## end ZAStyle::GetpBorder%33EC67B30136.get
}

inline void ZAStyle::SetpBorder (ZABorder* value)
{
  //## begin ZAStyle::SetpBorder%33EC67B30136.set preserve=no
  m_pBorder = value;
  //## end ZAStyle::SetpBorder%33EC67B30136.set
}

inline const UINT ZAStyle::GetJustify () const
{
  //## begin ZAStyle::GetJustify%34118F2200B4.get preserve=no
  return m_Justify;
  //## end ZAStyle::GetJustify%34118F2200B4.get
}

inline void ZAStyle::SetJustify (UINT value)
{
  //## begin ZAStyle::SetJustify%34118F2200B4.set preserve=no
  m_Justify = value;
  //## end ZAStyle::SetJustify%34118F2200B4.set
}

//## begin module%33D8F933017C.epilog preserve=yes
//## end module%33D8F933017C.epilog


#endif
