//## begin module%33CA55B500C8.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%33CA55B500C8.cm

//## begin module%33CA55B500C8.cp preserve=no
//	ADSoft / Advanced Dedicated Software
//	Dominique AIGROZ
//## end module%33CA55B500C8.cp

//## Module: ZAFont%33CA55B500C8; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZAFont.cpp

//## begin module%33CA55B500C8.additionalIncludes preserve=no
//## end module%33CA55B500C8.additionalIncludes

//## begin module%33CA55B500C8.includes preserve=yes
#include <StdAfx.h>
//## end module%33CA55B500C8.includes

// ZAFont
#include "ZAFont.h"
//## begin module%33CA55B500C8.declarations preserve=no
//## end module%33CA55B500C8.declarations

//## begin module%33CA55B500C8.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(ZAFont, CFont, def_Version)
//## end module%33CA55B500C8.additionalDeclarations


// Class ZAFont 



ZAFont::ZAFont()
  //## begin ZAFont::ZAFont%.hasinit preserve=no
      : m_hFontNumber(-1)
  //## end ZAFont::ZAFont%.hasinit
  //## begin ZAFont::ZAFont%.initialization preserve=yes
  //## end ZAFont::ZAFont%.initialization
{
  //## begin ZAFont::ZAFont%.body preserve=yes
  //## end ZAFont::ZAFont%.body
}

ZAFont::ZAFont(const ZAFont &right)
  //## begin ZAFont::ZAFont%copy.hasinit preserve=no
      : m_hFontNumber(-1)
  //## end ZAFont::ZAFont%copy.hasinit
  //## begin ZAFont::ZAFont%copy.initialization preserve=yes
  //## end ZAFont::ZAFont%copy.initialization
{
  //## begin ZAFont::ZAFont%copy.body preserve=yes
  *this = right;
  //## end ZAFont::ZAFont%copy.body
}


ZAFont::~ZAFont()
{
  //## begin ZAFont::~ZAFont%.body preserve=yes
  //## end ZAFont::~ZAFont%.body
}


const ZAFont & ZAFont::operator=(const ZAFont &right)
{
  //## begin ZAFont::operator=%.body preserve=yes
	LOGFONT		lf;
		
	right.GetObject( sizeof(LOGFONT), &lf );
	CreateFont( lf.lfHeight, lf.lfWidth, lf.lfEscapement, lf.lfOrientation,
				lf.lfWeight, lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
				OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
				DEFAULT_QUALITY, DEFAULT_PITCH, lf.lfFaceName );
	m_colFont = right.m_colFont;
	m_hFontNumber = right.m_hFontNumber;
	return *this;
  //## end ZAFont::operator=%.body
}



//## Other Operations (implementation)
ZAFont* ZAFont::Clone ()
{
  //## begin ZAFont::Clone%868898986.body preserve=yes
	ZAFont*	pObject = new ZAFont( *this );
	return pObject;
  //## end ZAFont::Clone%868898986.body
}

void ZAFont::Serialize (CArchive& ar)
{
  //## begin ZAFont::Serialize%868898987.body preserve=yes
	if (ar.IsStoring())
	{	// Write the elements$
		LOGFONT		lf;
		
		GetObject( sizeof(LOGFONT), &lf );
#ifndef _WIN32		
		ar << lf.lfFaceName;
#else
		ar << (CString)lf.lfFaceName;
#endif
		ar << (WORD)lf.lfHeight;
		ar << (WORD)lf.lfWidth;
		ar << (WORD)lf.lfEscapement;
		ar << (WORD)lf.lfOrientation;
		ar << (WORD)lf.lfWeight;
		ar << lf.lfItalic;
		ar << lf.lfUnderline;
		ar << lf.lfStrikeOut;
		ar << lf.lfCharSet;
		ar << m_colFont;
		ar << m_hFontNumber;
	}
	else
	{
		CString		strFaceName;
		short		sHeight;
		short 		sWidth;
		short 		sEscape;
		short 		sOrientation;
		short 		sWeight;
		BYTE 		bItalic;
		BYTE 		bUnder;
		BYTE 		bStrikeOut;
		BYTE		bCharSet;

		ar >> strFaceName;
		WORD	wData;
		ar >> wData;
		sHeight = (short)wData;
		ar >> wData;
		sWidth = (short)wData;
		ar >> wData;
		sEscape = (short)wData;
		ar >> wData;
		sOrientation = (short)wData;
		ar >> wData;
		sWeight = (short)wData;
		ar >> bItalic;
		ar >> bUnder;
		ar >> bStrikeOut;
		ar >> bCharSet;
		CreateFont( sHeight, sWidth, sEscape, sOrientation,
					sWeight, bItalic, bUnder, bStrikeOut, bCharSet,
					OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH, strFaceName );
		ar >> m_colFont;
		ar >> m_hFontNumber;
	}
  //## end ZAFont::Serialize%868898987.body
}

BOOL ZAFont::Create (LOGFONT* pLogFont, COLORREF col)
{
  //## begin ZAFont::Create%870115417.body preserve=yes
	m_colFont = col;
	m_hFontNumber = NoFontDefined;
	return CreateFont( 	pLogFont->lfHeight, pLogFont->lfWidth, pLogFont->lfEscapement, pLogFont->lfOrientation,
						pLogFont->lfWeight, pLogFont->lfItalic, pLogFont->lfUnderline, pLogFont->lfStrikeOut, pLogFont->lfCharSet,
						OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
						DEFAULT_QUALITY, DEFAULT_PITCH, pLogFont->lfFaceName );
  //## end ZAFont::Create%870115417.body
}

// Additional Declarations
  //## begin ZAFont%33CA554D0078.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// ZAFont diagnostics

#ifdef _DEBUG
void ZAFont::AssertValid() const
{
	CObject::AssertValid();
}

void ZAFont::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

  //## end ZAFont%33CA554D0078.declarations
//## begin module%33CA55B500C8.epilog preserve=yes
//## end module%33CA55B500C8.epilog
