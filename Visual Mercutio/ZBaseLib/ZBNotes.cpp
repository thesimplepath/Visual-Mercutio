//## begin module%37E4CD2600F2.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%37E4CD2600F2.cm

//## begin module%37E4CD2600F2.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%37E4CD2600F2.cp

//## Module: ZBNotes%37E4CD2600F2; Package body
//## Subsystem: ZBaseLib%37A08E0C019D
//## Source file: z:\adsoft~1\ZBaseLib\ZBNotes.cpp

//## begin module%37E4CD2600F2.additionalIncludes preserve=no
#include <StdAfx.h>
//## end module%37E4CD2600F2.additionalIncludes

//## begin module%37E4CD2600F2.includes preserve=yes
//## end module%37E4CD2600F2.includes

// ZBNotes
#include "ZBNotes.h"
//## begin module%37E4CD2600F2.declarations preserve=no
//## end module%37E4CD2600F2.declarations

//## begin module%37E4CD2600F2.additionalDeclarations preserve=yes

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_SERIAL(ZBNotes, CObject, def_Version)
//## end module%37E4CD2600F2.additionalDeclarations


// Class ZBNotes 



ZBNotes::ZBNotes(const ZBNotes &right)
  //## begin ZBNotes::ZBNotes%copy.hasinit preserve=no
  //## end ZBNotes::ZBNotes%copy.hasinit
  //## begin ZBNotes::ZBNotes%copy.initialization preserve=yes
  //## end ZBNotes::ZBNotes%copy.initialization
{
  //## begin ZBNotes::ZBNotes%copy.body preserve=yes
      *this = right;
  //## end ZBNotes::ZBNotes%copy.body
}

ZBNotes::ZBNotes (CString Comment, CString Username)
  //## begin ZBNotes::ZBNotes%937741717.hasinit preserve=no
  //## end ZBNotes::ZBNotes%937741717.hasinit
  //## begin ZBNotes::ZBNotes%937741717.initialization preserve=yes
    : m_Comment( Comment ), m_Username( Username )
  //## end ZBNotes::ZBNotes%937741717.initialization
{
  //## begin ZBNotes::ZBNotes%937741717.body preserve=yes
  //## end ZBNotes::ZBNotes%937741717.body
}


ZBNotes::~ZBNotes()
{
  //## begin ZBNotes::~ZBNotes%.body preserve=yes
  //## end ZBNotes::~ZBNotes%.body
}


const ZBNotes & ZBNotes::operator=(const ZBNotes &right)
{
  //## begin ZBNotes::operator=%.body preserve=yes
      m_Comment = right.m_Comment;
      m_Username = right.m_Username;
      return *this;
  //## end ZBNotes::operator=%.body
}



//## Other Operations (implementation)
ZBNotes* ZBNotes::Clone ()
{
  //## begin ZBNotes::Clone%937741718.body preserve=yes
      ZBNotes*    pNotes = new ZBNotes(*this);
      return pNotes;
  //## end ZBNotes::Clone%937741718.body
}

void ZBNotes::ClearNotes ()
{
  //## begin ZBNotes::ClearNotes%937741722.body preserve=yes
    ClearComment();
    ClearUsername();
  //## end ZBNotes::ClearNotes%937741722.body
}

void ZBNotes::ClearComment ()
{
  //## begin ZBNotes::ClearComment%937741723.body preserve=yes
    m_Comment.Empty();
  //## end ZBNotes::ClearComment%937741723.body
}

void ZBNotes::ClearUsername ()
{
  //## begin ZBNotes::ClearUsername%937741724.body preserve=yes
    m_Username.Empty();
  //## end ZBNotes::ClearUsername%937741724.body
}

CString ZBNotes::GetFormatedNotes (CRect* pRect)
{
  //## begin ZBNotes::GetFormatedNotes%937741725.body preserve=yes
    return m_Username + "\r\n" + m_Comment;
  //## end ZBNotes::GetFormatedNotes%937741725.body
}

CArchive& operator >> (CArchive& ar, ZBNotes& Notes)
{
  //## begin ZBNotes::operator >>%937741719.body preserve=yes
    ar >> Notes.m_Username;
      ar >> Notes.m_Comment;
    return ar;
  //## end ZBNotes::operator >>%937741719.body
}

CArchive& operator << (CArchive& ar, ZBNotes& Notes)
{
  //## begin ZBNotes::operator <<%937741720.body preserve=yes
    ar << Notes.m_Username;
      ar << Notes.m_Comment;
    return ar;
  //## end ZBNotes::operator <<%937741720.body
}

void ZBNotes::Serialize (CArchive& ar)
{
  //## begin ZBNotes::Serialize%937741721.body preserve=yes
    if (ar.IsStoring())
    {    // Write the elements
        ar << *this;
    }
    else
    {
        ar >> *this;
    }
  //## end ZBNotes::Serialize%937741721.body
}

// Additional Declarations
  //## begin ZBNotes%37E4CC9F024D.declarations preserve=yes
  //## end ZBNotes%37E4CC9F024D.declarations

//## begin module%37E4CD2600F2.epilog preserve=yes
//## end module%37E4CD2600F2.epilog
