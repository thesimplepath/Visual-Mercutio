//## begin module%3713991C036E.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%3713991C036E.cm

//## begin module%3713991C036E.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%3713991C036E.cp

//## Module: ZBRect%3713991C036E; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZBRect.cpp

//## begin module%3713991C036E.additionalIncludes preserve=no
//## end module%3713991C036E.additionalIncludes

//## begin module%3713991C036E.includes preserve=yes
#include <StdAfx.h>
//## end module%3713991C036E.includes

// ZBRect
#include "ZBRect.h"
//## begin module%3713991C036E.declarations preserve=no
//## end module%3713991C036E.declarations

//## begin module%3713991C036E.additionalDeclarations preserve=yes
#include "BaseDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//## end module%3713991C036E.additionalDeclarations


// Class ZBRect 

ZBRect::ZBRect()
  //## begin ZBRect::ZBRect%.hasinit preserve=no
  //## end ZBRect::ZBRect%.hasinit
  //## begin ZBRect::ZBRect%.initialization preserve=yes
  //## end ZBRect::ZBRect%.initialization
{
  //## begin ZBRect::ZBRect%.body preserve=yes
  //## end ZBRect::ZBRect%.body
}


ZBRect::~ZBRect()
{
  //## begin ZBRect::~ZBRect%.body preserve=yes
  //## end ZBRect::~ZBRect%.body
}



//## Other Operations (implementation)
void ZBRect::Serialize (CArchive& ar)
{
  //## begin ZBRect::Serialize%924031309.body preserve=yes
    if (ar.IsStoring())
    {    // Write the elements
        ar << *this;
    }
    else
    {    // Read the elements
        ar >> *this;
    }
  //## end ZBRect::Serialize%924031309.body
}

CArchive& operator >> (CArchive& ar, ZBRect& Rect)
{
  //## begin ZBRect::operator >>%924031311.body preserve=yes
    if (((ZDBaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() <= 12)
    {
        WORD    wTemp;
        ar >> wTemp;
        Rect.left = (int)wTemp;
          ar >> wTemp;
        Rect.top = (int)wTemp;
          ar >> wTemp;
        Rect.right = (int)wTemp;
          ar >> wTemp;
        Rect.bottom = (int)wTemp;
    }
    else
    {
        DWORD    dwTemp;
        ar >> dwTemp;
        Rect.left = (int)dwTemp;
          ar >> dwTemp;
        Rect.top = (int)dwTemp;
          ar >> dwTemp;
        Rect.right = (int)dwTemp;
          ar >> dwTemp;
        Rect.bottom = (int)dwTemp;
    }
    return ar;
  //## end ZBRect::operator >>%924031311.body
}

CArchive& operator << (CArchive& ar, ZBRect& Rect)
{
  //## begin ZBRect::operator <<%924031312.body preserve=yes
    ar << (DWORD)Rect.left;
    ar << (DWORD)Rect.top;
    ar << (DWORD)Rect.right;
    ar << (DWORD)Rect.bottom;
    return ar;
  //## end ZBRect::operator <<%924031312.body
}

// Additional Declarations
  //## begin ZBRect%3713985D0356.declarations preserve=yes
  //## end ZBRect%3713985D0356.declarations

//## begin module%3713991C036E.epilog preserve=yes
//## end module%3713991C036E.epilog
