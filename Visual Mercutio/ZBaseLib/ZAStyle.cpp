//## begin module%33D8F92B00C8.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%33D8F92B00C8.cm

//## begin module%33D8F92B00C8.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%33D8F92B00C8.cp

//## Module: ZAStyle%33D8F92B00C8; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\ZAStyle.cpp

//## begin module%33D8F92B00C8.additionalIncludes preserve=no
//## end module%33D8F92B00C8.additionalIncludes

//## begin module%33D8F92B00C8.includes preserve=yes
#include <StdAfx.h>
//## end module%33D8F92B00C8.includes

// ZAStyle
#include "ZAStyle.h"
//## begin module%33D8F92B00C8.declarations preserve=no
//## end module%33D8F92B00C8.declarations

//## begin module%33D8F92B00C8.additionalDeclarations preserve=yes
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(ZAStyle, CObject, g_DefVersion)
//## end module%33D8F92B00C8.additionalDeclarations


// Class ZAStyle 







ZAStyle::ZAStyle()
  //## begin ZAStyle::ZAStyle%.hasinit preserve=no
      : m_hFont(0), m_BackColor(-1), m_pBorder(NULL), m_Justify(DT_LEFT | DT_BOTTOM | DT_SINGLELINE)
  //## end ZAStyle::ZAStyle%.hasinit
  //## begin ZAStyle::ZAStyle%.initialization preserve=yes
  //## end ZAStyle::ZAStyle%.initialization
{
  //## begin ZAStyle::ZAStyle%.body preserve=yes
  //## end ZAStyle::ZAStyle%.body
}

ZAStyle::ZAStyle(const ZAStyle &right)
  //## begin ZAStyle::ZAStyle%copy.hasinit preserve=no
      : m_hFont(0), m_BackColor(-1), m_pBorder(NULL), m_Justify(DT_LEFT | DT_BOTTOM | DT_SINGLELINE)
  //## end ZAStyle::ZAStyle%copy.hasinit
  //## begin ZAStyle::ZAStyle%copy.initialization preserve=yes
  //## end ZAStyle::ZAStyle%copy.initialization
{
  //## begin ZAStyle::ZAStyle%copy.body preserve=yes
  *this = right;
  //## end ZAStyle::ZAStyle%copy.body
}


ZAStyle::~ZAStyle()
{
  //## begin ZAStyle::~ZAStyle%.body preserve=yes
    if (m_pBorder)
        delete m_pBorder;
  //## end ZAStyle::~ZAStyle%.body
}


const ZAStyle & ZAStyle::operator=(const ZAStyle &right)
{
  //## begin ZAStyle::operator=%.body preserve=yes
    m_hFont = right.m_hFont;
    m_BackColor = right.m_BackColor;
    m_hStyleNumber = right.m_hStyleNumber;
    m_StyleName = right.m_StyleName;
    m_Justify = right.m_Justify;
    if (right.m_pBorder)
        m_pBorder = right.m_pBorder->Clone();
    return *this;
  //## end ZAStyle::operator=%.body
}



//## Other Operations (implementation)
void ZAStyle::Serialize (CArchive& ar)
{
  //## begin ZAStyle::Serialize%869857712.body preserve=yes
    if (ar.IsStoring())
    {    // Write the elements
        ar << m_hFont;
        ar << m_BackColor;
        ar << m_pBorder;
        ar << (LONG)m_hStyleNumber;
        ar << m_StyleName;
        ar << (DWORD)m_Justify;
    }
    else
    {
        ar >> m_hFont;
        ar >> m_BackColor;
        ar >> m_pBorder;
        LONG    lValue;
        ar >> lValue;
        m_hStyleNumber = (HandleStyle)lValue;
        ar >> m_StyleName;
        DWORD    dwValue;
        ar >> dwValue;
        m_Justify = (UINT)dwValue;
    }
  //## end ZAStyle::Serialize%869857712.body
}

ZAStyle* ZAStyle::Clone ()
{
  //## begin ZAStyle::Clone%869857713.body preserve=yes
    ZAStyle*    pObject = new ZAStyle( *this );
    return pObject;
  //## end ZAStyle::Clone%869857713.body
}

// Additional Declarations
  //## begin ZAStyle%33D8F8010118.declarations preserve=yes
/////////////////////////////////////////////////////////////////////////////
// ZAStyle diagnostics

#ifdef _DEBUG
void ZAStyle::AssertValid() const
{
    CObject::AssertValid();
}

void ZAStyle::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif //_DEBUG

  //## end ZAStyle%33D8F8010118.declarations
//## begin module%33D8F92B00C8.epilog preserve=yes
//## end module%33D8F92B00C8.epilog
