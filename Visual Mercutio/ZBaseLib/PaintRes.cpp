//## begin module%37EA73A90260.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%37EA73A90260.cm

//## begin module%37EA73A90260.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%37EA73A90260.cp

//## Module: PaintRes%37EA73A90260; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\PaintRes.cpp

//## begin module%37EA73A90260.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%37EA73A90260.additionalIncludes

//## begin module%37EA73A90260.includes preserve=yes
//## end module%37EA73A90260.includes

// PaintRes
#include "PaintRes.h"
//## begin module%37EA73A90260.declarations preserve=no
//## end module%37EA73A90260.declarations

//## begin module%37EA73A90260.additionalDeclarations preserve=yes
//## end module%37EA73A90260.additionalDeclarations


// Class ZBPaintResources 

//## begin ZBPaintResources::SystemFont%37EA71FA02C5.attr preserve=no  public: static CFont {V} 
CFont ZBPaintResources::m_SystemFont;
//## end ZBPaintResources::SystemFont%37EA71FA02C5.attr

//## begin ZBPaintResources::SmallSystemFont%37EA724700BD.attr preserve=no  public: static CFont {V} 
CFont ZBPaintResources::m_SmallSystemFont;
//## end ZBPaintResources::SmallSystemFont%37EA724700BD.attr

//## begin ZBPaintResources::BlackPen%37EA725502C6.attr preserve=no  public: static CPen {V} 
CPen ZBPaintResources::m_BlackPen;
//## end ZBPaintResources::BlackPen%37EA725502C6.attr

//## begin ZBPaintResources::WhitePen%37EA72A80379.attr preserve=no  public: static CPen {V} 
CPen ZBPaintResources::m_WhitePen;
//## end ZBPaintResources::WhitePen%37EA72A80379.attr

//## begin ZBPaintResources::BluePen%37EA72AA01E2.attr preserve=no  public: static CPen {V} 
CPen ZBPaintResources::m_BluePen;
//## end ZBPaintResources::BluePen%37EA72AA01E2.attr

//## begin ZBPaintResources::GrayPen%37EA72AC02FD.attr preserve=no  public: static CPen {V} 
CPen ZBPaintResources::m_GrayPen;
//## end ZBPaintResources::GrayPen%37EA72AC02FD.attr

//## begin ZBPaintResources::YellowPen%37EA72AD039F.attr preserve=no  public: static CPen {V} 
CPen ZBPaintResources::m_YellowPen;
//## end ZBPaintResources::YellowPen%37EA72AD039F.attr

//## begin ZBPaintResources::GreenPen%37EA72D201F3.attr preserve=no  public: static CPen {V} 
CPen ZBPaintResources::m_GreenPen;
//## end ZBPaintResources::GreenPen%37EA72D201F3.attr

//## begin ZBPaintResources::RedPen%37EA72D30263.attr preserve=no  public: static CPen {V} 
CPen ZBPaintResources::m_RedPen;
//## end ZBPaintResources::RedPen%37EA72D30263.attr

//## begin ZBPaintResources::WhiteBrush%37EA72E7017B.attr preserve=no  public: static CBrush {V} 
CBrush ZBPaintResources::m_WhiteBrush;
//## end ZBPaintResources::WhiteBrush%37EA72E7017B.attr

//## begin ZBPaintResources::LtBlueBrush%37EA72F60335.attr preserve=no  public: static CBrush {V} 
CBrush ZBPaintResources::m_LtBlueBrush;
//## end ZBPaintResources::LtBlueBrush%37EA72F60335.attr

//## begin ZBPaintResources::RedBrush%37EA72F80356.attr preserve=no  public: static CBrush {V} 
CBrush ZBPaintResources::m_RedBrush;
//## end ZBPaintResources::RedBrush%37EA72F80356.attr

//## begin ZBPaintResources::BlackBrush%37EA72FA0010.attr preserve=no  public: static CBrush {V} 
CBrush ZBPaintResources::m_BlackBrush;
//## end ZBPaintResources::BlackBrush%37EA72FA0010.attr

//## begin ZBPaintResources::GrayBrush%37EA72FB0076.attr preserve=no  public: static CBrush {V} 
CBrush ZBPaintResources::m_GrayBrush;
//## end ZBPaintResources::GrayBrush%37EA72FB0076.attr

//## begin ZBPaintResources::BlueBrush%37EA732400F7.attr preserve=no  public: static CBrush {V} 
CBrush ZBPaintResources::m_BlueBrush;
//## end ZBPaintResources::BlueBrush%37EA732400F7.attr

ZBPaintResources::ZBPaintResources()
  //## begin ZBPaintResources::ZBPaintResources%.hasinit preserve=no
  //## end ZBPaintResources::ZBPaintResources%.hasinit
  //## begin ZBPaintResources::ZBPaintResources%.initialization preserve=yes
  //## end ZBPaintResources::ZBPaintResources%.initialization
{
  //## begin ZBPaintResources::ZBPaintResources%.body preserve=yes
  //## end ZBPaintResources::ZBPaintResources%.body
}


ZBPaintResources::~ZBPaintResources()
{
  //## begin ZBPaintResources::~ZBPaintResources%.body preserve=yes
  //## end ZBPaintResources::~ZBPaintResources%.body
}



//## Other Operations (implementation)
void ZBPaintResources::Initialize ()
{
  //## begin ZBPaintResources::Initialize%938112080.body preserve=yes
	// Creation of pens	
  	m_BlackPen.CreatePen( PS_SOLID, 1, defCOLOR_BLACK );
    m_WhitePen.CreatePen( PS_SOLID, 1, defCOLOR_WHITE );
    m_BluePen.CreatePen( PS_SOLID, 1, defCOLOR_BLUE );
    m_GrayPen.CreatePen( PS_SOLID, 1, defCOLOR_GRAY );
    m_RedPen.CreatePen( PS_SOLID, 1, defCOLOR_RED );
    m_YellowPen.CreatePen( PS_SOLID, 1, defCOLOR_YELLOW );
    m_GreenPen.CreatePen( PS_SOLID, 1, defCOLOR_GREEN );

	// Creation of brushes
    m_WhiteBrush.CreateSolidBrush( defCOLOR_WHITE );
    m_LtBlueBrush.CreateSolidBrush( defCOLOR_LTBLUE );
    m_RedBrush.CreateSolidBrush( defCOLOR_RED );
    m_BlackBrush.CreateSolidBrush( defCOLOR_BLACK );
    m_GrayBrush.CreateSolidBrush( defCOLOR_GRAY );
    m_BlueBrush.CreateSolidBrush( defCOLOR_BLUE );

	// Creation of fonts
	m_SystemFont.CreateFont( 14, 10, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, 0, "Arial" );
	m_SmallSystemFont.CreateFont( 10, 6, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, 0, "Arial" );

  //## end ZBPaintResources::Initialize%938112080.body
}

// Additional Declarations
  //## begin ZBPaintResources%37EA70C2030C.declarations preserve=yes
  //## end ZBPaintResources%37EA70C2030C.declarations

//## begin module%37EA73A90260.epilog preserve=yes
//## end module%37EA73A90260.epilog
