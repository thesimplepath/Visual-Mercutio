//## begin module%33CA78FC01AE.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%33CA78FC01AE.cm

//## begin module%33CA78FC01AE.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%33CA78FC01AE.cp

//## Module: ZAFontMg%33CA78FC01AE; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZAFontMg.cpp

//## begin module%33CA78FC01AE.additionalIncludes preserve=no
//## end module%33CA78FC01AE.additionalIncludes

//## begin module%33CA78FC01AE.includes preserve=yes
#include <StdAfx.h>
//## end module%33CA78FC01AE.includes

// ZAFontMg
#include "ZAFontMg.h"
//## begin module%33CA78FC01AE.declarations preserve=no
//## end module%33CA78FC01AE.declarations

//## begin module%33CA78FC01AE.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(ZAFontManager, CObject, def_Version)
//## end module%33CA78FC01AE.additionalDeclarations


// Class ZAFontManager 


ZAFontManager::ZAFontManager()
  //## begin ZAFontManager::ZAFontManager%.hasinit preserve=no
  //## end ZAFontManager::ZAFontManager%.hasinit
  //## begin ZAFontManager::ZAFontManager%.initialization preserve=yes
  //## end ZAFontManager::ZAFontManager%.initialization
{
  //## begin ZAFontManager::ZAFontManager%.body preserve=yes
  //## end ZAFontManager::ZAFontManager%.body
}

ZAFontManager::ZAFontManager(const ZAFontManager &right)
  //## begin ZAFontManager::ZAFontManager%copy.hasinit preserve=no
  //## end ZAFontManager::ZAFontManager%copy.hasinit
  //## begin ZAFontManager::ZAFontManager%copy.initialization preserve=yes
  //## end ZAFontManager::ZAFontManager%copy.initialization
{
  //## begin ZAFontManager::ZAFontManager%copy.body preserve=yes
      *this = right;
  //## end ZAFontManager::ZAFontManager%copy.body
}


ZAFontManager::~ZAFontManager()
{
  //## begin ZAFontManager::~ZAFontManager%.body preserve=yes
      for (int i = 0; i < m_FontArray.GetSize(); ++i)
          delete ((ZAFont*)(m_FontArray[i]));

    m_FontArray.RemoveAll();
  //## end ZAFontManager::~ZAFontManager%.body
}


const ZAFontManager & ZAFontManager::operator=(const ZAFontManager &right)
{
  //## begin ZAFontManager::operator=%.body preserve=yes
      if (right.m_FontArray.GetSize() > 0)
      {
          m_FontArray.SetSize( right.m_FontArray.GetSize() );
          for (int i = 0; i < right.m_FontArray.GetSize(); ++i)
              if (right.m_FontArray[i])
                  m_FontArray.InsertAt(i, ((ZAFont*)right.m_FontArray[i])->Clone());
    }
      return *this;
  //## end ZAFontManager::operator=%.body
}



//## Other Operations (implementation)
BOOL ZAFontManager::RemoveFont (HandleFont hFont)
{
  //## begin ZAFontManager::RemoveFont%868907716.body preserve=yes
      for (int i = 0; i < m_FontArray.GetSize(); ++i)
          if ( ((ZAFont*)(m_FontArray[i]))->GethFontNumber() == hFont)
          {
              // First free memory pointed at location
              delete ((ZAFont*)(m_FontArray[i]));
              // Second remove the element from the array
              m_FontArray.RemoveAt( i );    
              return TRUE;
          }
      return FALSE;
  //## end ZAFontManager::RemoveFont%868907716.body
}

HandleFont ZAFontManager::FindFont (LOGFONT* pLogFont, COLORREF Col)
{
  //## begin ZAFontManager::FindFont%868907717.body preserve=yes
    LOGFONT        lf;
        
      for (int i = 0; i < m_FontArray.GetSize(); ++i)
      {
          // Check the color first
          if (((ZAFont*)(m_FontArray[i]))->GetFontColor() != Col)
              continue;
          // Check each element of the LOGFONT
        ((ZAFont*)(m_FontArray[i]))->GetObject( sizeof(LOGFONT), &lf );
          if (
            strcmp( pLogFont->lfFaceName, lf.lfFaceName ) == 0 &&
            pLogFont->lfHeight == lf.lfHeight &&
            pLogFont->lfWidth == lf.lfWidth &&
            pLogFont->lfEscapement == lf.lfEscapement &&
            pLogFont->lfOrientation == lf.lfOrientation &&
            pLogFont->lfWeight == lf.lfWeight &&
            pLogFont->lfItalic == lf.lfItalic &&
            pLogFont->lfUnderline == lf.lfUnderline &&
            pLogFont->lfStrikeOut == lf.lfStrikeOut &&
            pLogFont->lfCharSet == lf.lfCharSet )
              // Return the handle
              return ((ZAFont*)(m_FontArray[i]))->GethFontNumber();
      }
      return NoFontDefined;
  //## end ZAFontManager::FindFont%868907717.body
}

HandleFont ZAFontManager::FindFont (ZAFont* pFont)
{
  //## begin ZAFontManager::FindFont%869402481.body preserve=yes
      for (int i = 0; i < m_FontArray.GetSize(); ++i)
          if ( ((ZAFont*)(m_FontArray[i])) == pFont)
          {
              // Return the handle
              return ((ZAFont*)(m_FontArray[i]))->GethFontNumber();
          }
      return NoFontDefined;
  //## end ZAFontManager::FindFont%869402481.body
}

void ZAFontManager::Serialize (CArchive& ar)
{
  //## begin ZAFontManager::Serialize%869764511.body preserve=yes
      m_FontArray.Serialize( ar );
  //## end ZAFontManager::Serialize%869764511.body
}

HandleFont ZAFontManager::RotateFont (HandleFont hFont, int iAngle)
{
  //## begin ZAFontManager::RotateFont%880893867.body preserve=yes
    LOGFONT        lf;
    ZAFont*        pInitialFont = GetFont( hFont );
    pInitialFont->GetObject( sizeof(LOGFONT), &lf );
    // Set the new angle
    lf.lfEscapement = iAngle;
    // Return the specific Font assigned directly
    HandleFont hRetFont;
    if ((hRetFont=FindFont( &lf, pInitialFont->GetFontColor() )) == NoFontDefined)
    {
        ZAFont*    pFont = new ZAFont;
        pFont->Create( &lf, pInitialFont->GetFontColor() );
        hRetFont = AddFont( pFont );
      }
      return hRetFont;
  //## end ZAFontManager::RotateFont%880893867.body
}

// Additional Declarations
  //## begin ZAFontManager%33CA5F860104.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// ZAFontManager diagnostics

#ifdef _DEBUG
void ZAFontManager::AssertValid() const
{
    CObject::AssertValid();
}

void ZAFontManager::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG

  //## end ZAFontManager%33CA5F860104.declarations
//## begin module%33CA78FC01AE.epilog preserve=yes
//## end module%33CA78FC01AE.epilog
