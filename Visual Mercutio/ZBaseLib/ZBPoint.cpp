//## begin module%3719856300CE.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%3719856300CE.cm

//## begin module%3719856300CE.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%3719856300CE.cp

//## Module: ZBPoint%3719856300CE; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZBPoint.cpp

//## begin module%3719856300CE.additionalIncludes preserve=no
//## end module%3719856300CE.additionalIncludes

//## begin module%3719856300CE.includes preserve=yes
#include <StdAfx.h>
//## end module%3719856300CE.includes

// ZBPoint
#include "ZBPoint.h"
//## begin module%3719856300CE.declarations preserve=no
//## end module%3719856300CE.declarations

//## begin module%3719856300CE.additionalDeclarations preserve=yes
#include "PSS_BaseDocument.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//## end module%3719856300CE.additionalDeclarations


// Class ZBPoint 

ZBPoint::ZBPoint()
  //## begin ZBPoint::ZBPoint%.hasinit preserve=no
  //## end ZBPoint::ZBPoint%.hasinit
  //## begin ZBPoint::ZBPoint%.initialization preserve=yes
  //## end ZBPoint::ZBPoint%.initialization
{
  //## begin ZBPoint::ZBPoint%.body preserve=yes
  //## end ZBPoint::ZBPoint%.body
}


ZBPoint::~ZBPoint()
{
  //## begin ZBPoint::~ZBPoint%.body preserve=yes
  //## end ZBPoint::~ZBPoint%.body
}



//## Other Operations (implementation)
void ZBPoint::Serialize (CArchive& ar)
{
  //## begin ZBPoint::Serialize%924419478.body preserve=yes
    if (ar.IsStoring())
    {    // Write the elements
        ar << *this;
    }
    else
    {    // Read the elements
        ar >> *this;
    }
  //## end ZBPoint::Serialize%924419478.body
}

CArchive& operator >> (CArchive& ar, ZBPoint& Point)
{
  //## begin ZBPoint::operator >>%924419479.body preserve=yes
    if (((PSS_BaseDocument*)ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() <= 12)
    {
        WORD    wTemp;
        ar >> wTemp;
        Point.x = (int)wTemp;
          ar >> wTemp;
        Point.y = (int)wTemp;
    }
    else
    {
        DWORD    dwTemp;
        ar >> dwTemp;
        Point.x = (int)dwTemp;
          ar >> dwTemp;
        Point.x = (int)dwTemp;
    }
    return ar;
  //## end ZBPoint::operator >>%924419479.body
}

CArchive& operator << (CArchive& ar, ZBPoint& Point)
{
  //## begin ZBPoint::operator <<%924419480.body preserve=yes
    ar << (DWORD)Point.x;
    ar << (DWORD)Point.y;
    return ar;
  //## end ZBPoint::operator <<%924419480.body
}

// Additional Declarations
  //## begin ZBPoint%371984F6035C.declarations preserve=yes
  //## end ZBPoint%371984F6035C.declarations

//## begin module%3719856300CE.epilog preserve=yes
//## end module%3719856300CE.epilog
