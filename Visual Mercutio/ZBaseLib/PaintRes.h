//## begin module%37EA73B300A2.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%37EA73B300A2.cm

//## begin module%37EA73B300A2.cp preserve=no
//	ADSoft Copyright 1994-1995
//	Dominique Aigroz
//## end module%37EA73B300A2.cp

//## Module: PaintRes%37EA73B300A2; Package specification
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\PaintRes.h

#ifndef PaintRes_h
#define PaintRes_h 1

//## begin module%37EA73B300A2.additionalIncludes preserve=no
//## end module%37EA73B300A2.additionalIncludes

//## begin module%37EA73B300A2.includes preserve=yes
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
//## end module%37EA73B300A2.includes

//## begin module%37EA73B300A2.declarations preserve=no
//## end module%37EA73B300A2.declarations

//## begin module%37EA73B300A2.additionalDeclarations preserve=yes
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
//## end module%37EA73B300A2.additionalDeclarations


//## Class: ZBPaintResources%37EA70C2030C
//	Contains static method used for painting purpose.
//## Category: ZBaseLib::Painting classes%37EA70B902D7
//## Subsystem: ZBaseLib%37A08E0C019D
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class AFX_EXT_CLASS ZBPaintResources 
{
  //## begin ZBPaintResources%37EA70C2030C.initialDeclarations preserve=yes
  //## end ZBPaintResources%37EA70C2030C.initialDeclarations

  public:
    //## Constructors (generated)
      ZBPaintResources();

    //## Destructor (generated)
      ~ZBPaintResources();


    //## Other Operations (specified)
      //## Operation: Initialize%938112080
      //	Initialize all paint resources.
      static void Initialize ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: SystemFont%37EA71FA02C5
      static CFont& GetSystemFont ();

      //## Attribute: SmallSystemFont%37EA724700BD
      static CFont& GetSmallSystemFont ();

      //## Attribute: BlackPen%37EA725502C6
      static CPen& GetBlackPen ();

      //## Attribute: WhitePen%37EA72A80379
      static CPen& GetWhitePen ();

      //## Attribute: BluePen%37EA72AA01E2
      static CPen& GetBluePen ();

      //## Attribute: GrayPen%37EA72AC02FD
      static CPen& GetGrayPen ();

      //## Attribute: YellowPen%37EA72AD039F
      static CPen& GetYellowPen ();

      //## Attribute: GreenPen%37EA72D201F3
      static CPen& GetGreenPen ();

      //## Attribute: RedPen%37EA72D30263
      static CPen& GetRedPen ();

      //## Attribute: WhiteBrush%37EA72E7017B
      static CBrush& GetWhiteBrush ();

      //## Attribute: LtBlueBrush%37EA72F60335
      static CBrush& GetLtBlueBrush ();

      //## Attribute: RedBrush%37EA72F80356
      static CBrush& GetRedBrush ();

      //## Attribute: BlackBrush%37EA72FA0010
      static CBrush& GetBlackBrush ();

      //## Attribute: GrayBrush%37EA72FB0076
      static CBrush& GetGrayBrush ();

      //## Attribute: BlueBrush%37EA732400F7
      static CBrush& GetBlueBrush ();

    // Additional Public Declarations
      //## begin ZBPaintResources%37EA70C2030C.public preserve=yes
      //## end ZBPaintResources%37EA70C2030C.public

  protected:
    // Additional Protected Declarations
      //## begin ZBPaintResources%37EA70C2030C.protected preserve=yes
      //## end ZBPaintResources%37EA70C2030C.protected

  private:
    //## Constructors (generated)
      ZBPaintResources(const ZBPaintResources &right);

    //## Assignment Operation (generated)
      const ZBPaintResources & operator=(const ZBPaintResources &right);

    // Data Members for Class Attributes

      //## begin ZBPaintResources::SystemFont%37EA71FA02C5.attr preserve=no  public: static CFont {V} 
      static CFont m_SystemFont;
      //## end ZBPaintResources::SystemFont%37EA71FA02C5.attr

      //## begin ZBPaintResources::SmallSystemFont%37EA724700BD.attr preserve=no  public: static CFont {V} 
      static CFont m_SmallSystemFont;
      //## end ZBPaintResources::SmallSystemFont%37EA724700BD.attr

      //## begin ZBPaintResources::BlackPen%37EA725502C6.attr preserve=no  public: static CPen {V} 
      static CPen m_BlackPen;
      //## end ZBPaintResources::BlackPen%37EA725502C6.attr

      //## begin ZBPaintResources::WhitePen%37EA72A80379.attr preserve=no  public: static CPen {V} 
      static CPen m_WhitePen;
      //## end ZBPaintResources::WhitePen%37EA72A80379.attr

      //## begin ZBPaintResources::BluePen%37EA72AA01E2.attr preserve=no  public: static CPen {V} 
      static CPen m_BluePen;
      //## end ZBPaintResources::BluePen%37EA72AA01E2.attr

      //## begin ZBPaintResources::GrayPen%37EA72AC02FD.attr preserve=no  public: static CPen {V} 
      static CPen m_GrayPen;
      //## end ZBPaintResources::GrayPen%37EA72AC02FD.attr

      //## begin ZBPaintResources::YellowPen%37EA72AD039F.attr preserve=no  public: static CPen {V} 
      static CPen m_YellowPen;
      //## end ZBPaintResources::YellowPen%37EA72AD039F.attr

      //## begin ZBPaintResources::GreenPen%37EA72D201F3.attr preserve=no  public: static CPen {V} 
      static CPen m_GreenPen;
      //## end ZBPaintResources::GreenPen%37EA72D201F3.attr

      //## begin ZBPaintResources::RedPen%37EA72D30263.attr preserve=no  public: static CPen {V} 
      static CPen m_RedPen;
      //## end ZBPaintResources::RedPen%37EA72D30263.attr

      //## begin ZBPaintResources::WhiteBrush%37EA72E7017B.attr preserve=no  public: static CBrush {V} 
      static CBrush m_WhiteBrush;
      //## end ZBPaintResources::WhiteBrush%37EA72E7017B.attr

      //## begin ZBPaintResources::LtBlueBrush%37EA72F60335.attr preserve=no  public: static CBrush {V} 
      static CBrush m_LtBlueBrush;
      //## end ZBPaintResources::LtBlueBrush%37EA72F60335.attr

      //## begin ZBPaintResources::RedBrush%37EA72F80356.attr preserve=no  public: static CBrush {V} 
      static CBrush m_RedBrush;
      //## end ZBPaintResources::RedBrush%37EA72F80356.attr

      //## begin ZBPaintResources::BlackBrush%37EA72FA0010.attr preserve=no  public: static CBrush {V} 
      static CBrush m_BlackBrush;
      //## end ZBPaintResources::BlackBrush%37EA72FA0010.attr

      //## begin ZBPaintResources::GrayBrush%37EA72FB0076.attr preserve=no  public: static CBrush {V} 
      static CBrush m_GrayBrush;
      //## end ZBPaintResources::GrayBrush%37EA72FB0076.attr

      //## begin ZBPaintResources::BlueBrush%37EA732400F7.attr preserve=no  public: static CBrush {V} 
      static CBrush m_BlueBrush;
      //## end ZBPaintResources::BlueBrush%37EA732400F7.attr

    // Additional Private Declarations
      //## begin ZBPaintResources%37EA70C2030C.private preserve=yes
      //## end ZBPaintResources%37EA70C2030C.private

  private:  //## implementation
    // Additional Implementation Declarations
      //## begin ZBPaintResources%37EA70C2030C.implementation preserve=yes
      //## end ZBPaintResources%37EA70C2030C.implementation

};

//## begin ZBPaintResources%37EA70C2030C.postscript preserve=yes
//## end ZBPaintResources%37EA70C2030C.postscript

// Class ZBPaintResources 

//## Get and Set Operations for Class Attributes (inline)

inline CFont& ZBPaintResources::GetSystemFont ()
{
  //## begin ZBPaintResources::GetSystemFont%37EA71FA02C5.get preserve=no
  return m_SystemFont;
  //## end ZBPaintResources::GetSystemFont%37EA71FA02C5.get
}

inline CFont& ZBPaintResources::GetSmallSystemFont ()
{
  //## begin ZBPaintResources::GetSmallSystemFont%37EA724700BD.get preserve=no
  return m_SmallSystemFont;
  //## end ZBPaintResources::GetSmallSystemFont%37EA724700BD.get
}

inline CPen& ZBPaintResources::GetBlackPen ()
{
  //## begin ZBPaintResources::GetBlackPen%37EA725502C6.get preserve=no
  return m_BlackPen;
  //## end ZBPaintResources::GetBlackPen%37EA725502C6.get
}

inline CPen& ZBPaintResources::GetWhitePen ()
{
  //## begin ZBPaintResources::GetWhitePen%37EA72A80379.get preserve=no
  return m_WhitePen;
  //## end ZBPaintResources::GetWhitePen%37EA72A80379.get
}

inline CPen& ZBPaintResources::GetBluePen ()
{
  //## begin ZBPaintResources::GetBluePen%37EA72AA01E2.get preserve=no
  return m_BluePen;
  //## end ZBPaintResources::GetBluePen%37EA72AA01E2.get
}

inline CPen& ZBPaintResources::GetGrayPen ()
{
  //## begin ZBPaintResources::GetGrayPen%37EA72AC02FD.get preserve=no
  return m_GrayPen;
  //## end ZBPaintResources::GetGrayPen%37EA72AC02FD.get
}

inline CPen& ZBPaintResources::GetYellowPen ()
{
  //## begin ZBPaintResources::GetYellowPen%37EA72AD039F.get preserve=no
  return m_YellowPen;
  //## end ZBPaintResources::GetYellowPen%37EA72AD039F.get
}

inline CPen& ZBPaintResources::GetGreenPen ()
{
  //## begin ZBPaintResources::GetGreenPen%37EA72D201F3.get preserve=no
  return m_GreenPen;
  //## end ZBPaintResources::GetGreenPen%37EA72D201F3.get
}

inline CPen& ZBPaintResources::GetRedPen ()
{
  //## begin ZBPaintResources::GetRedPen%37EA72D30263.get preserve=no
  return m_RedPen;
  //## end ZBPaintResources::GetRedPen%37EA72D30263.get
}

inline CBrush& ZBPaintResources::GetWhiteBrush ()
{
  //## begin ZBPaintResources::GetWhiteBrush%37EA72E7017B.get preserve=no
  return m_WhiteBrush;
  //## end ZBPaintResources::GetWhiteBrush%37EA72E7017B.get
}

inline CBrush& ZBPaintResources::GetLtBlueBrush ()
{
  //## begin ZBPaintResources::GetLtBlueBrush%37EA72F60335.get preserve=no
  return m_LtBlueBrush;
  //## end ZBPaintResources::GetLtBlueBrush%37EA72F60335.get
}

inline CBrush& ZBPaintResources::GetRedBrush ()
{
  //## begin ZBPaintResources::GetRedBrush%37EA72F80356.get preserve=no
  return m_RedBrush;
  //## end ZBPaintResources::GetRedBrush%37EA72F80356.get
}

inline CBrush& ZBPaintResources::GetBlackBrush ()
{
  //## begin ZBPaintResources::GetBlackBrush%37EA72FA0010.get preserve=no
  return m_BlackBrush;
  //## end ZBPaintResources::GetBlackBrush%37EA72FA0010.get
}

inline CBrush& ZBPaintResources::GetGrayBrush ()
{
  //## begin ZBPaintResources::GetGrayBrush%37EA72FB0076.get preserve=no
  return m_GrayBrush;
  //## end ZBPaintResources::GetGrayBrush%37EA72FB0076.get
}

inline CBrush& ZBPaintResources::GetBlueBrush ()
{
  //## begin ZBPaintResources::GetBlueBrush%37EA732400F7.get preserve=no
  return m_BlueBrush;
  //## end ZBPaintResources::GetBlueBrush%37EA732400F7.get
}

//## begin module%37EA73B300A2.epilog preserve=yes
//## end module%37EA73B300A2.epilog


#endif
