//## begin module%36722E8103D6.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%36722E8103D6.cm

//## begin module%36722E8103D6.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%36722E8103D6.cp

//## Module: PersonLs%36722E8103D6; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\PersonLs.cpp

//## begin module%36722E8103D6.additionalIncludes preserve=no
//## end module%36722E8103D6.additionalIncludes

//## begin module%36722E8103D6.includes preserve=yes
#include <StdAfx.h>
//## end module%36722E8103D6.includes

// PersonLs
#include "PersonLs.h"
//## begin module%36722E8103D6.declarations preserve=no
//## end module%36722E8103D6.declarations

//## begin module%36722E8103D6.additionalDeclarations preserve=yes
#include <afxdisp.h>
#include "Define.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
IMPLEMENT_SERIAL(ZUMailUserList, CObject, g_DefVersion)
//## end module%36722E8103D6.additionalDeclarations


// Class ZUMailUserList 



ZUMailUserList::ZUMailUserList()
  //## begin ZUMailUserList::ZUMailUserList%.hasinit preserve=no
      : m_MapiRecipDescPtr(NULL)
  //## end ZUMailUserList::ZUMailUserList%.hasinit
  //## begin ZUMailUserList::ZUMailUserList%.initialization preserve=yes
  //## end ZUMailUserList::ZUMailUserList%.initialization
{
  //## begin ZUMailUserList::ZUMailUserList%.body preserve=yes
  //## end ZUMailUserList::ZUMailUserList%.body
}

ZUMailUserList::ZUMailUserList (CStringArray& PersonListName, ULONG RecipClass)
  //## begin ZUMailUserList::ZUMailUserList%913452744.hasinit preserve=no
      : m_MapiRecipDescPtr(NULL)
  //## end ZUMailUserList::ZUMailUserList%913452744.hasinit
  //## begin ZUMailUserList::ZUMailUserList%913452744.initialization preserve=yes
  //## end ZUMailUserList::ZUMailUserList%913452744.initialization
{
  //## begin ZUMailUserList::ZUMailUserList%913452744.body preserve=yes
      Fill( PersonListName, RecipClass );
  //## end ZUMailUserList::ZUMailUserList%913452744.body
}

ZUMailUserList::ZUMailUserList (ZUUserManager& PersonListName, ULONG RecipClass)
  //## begin ZUMailUserList::ZUMailUserList%913659112.hasinit preserve=no
      : m_MapiRecipDescPtr(NULL)
  //## end ZUMailUserList::ZUMailUserList%913659112.hasinit
  //## begin ZUMailUserList::ZUMailUserList%913659112.initialization preserve=yes
  //## end ZUMailUserList::ZUMailUserList%913659112.initialization
{
  //## begin ZUMailUserList::ZUMailUserList%913659112.body preserve=yes
      Fill( PersonListName, RecipClass );
  //## end ZUMailUserList::ZUMailUserList%913659112.body
}

ZUMailUserList::ZUMailUserList (lpMapiRecipDesc* pMapiDesc, ULONG Count)
  //## begin ZUMailUserList::ZUMailUserList%921575859.hasinit preserve=no
      : m_MapiRecipDescPtr(NULL)
  //## end ZUMailUserList::ZUMailUserList%921575859.hasinit
  //## begin ZUMailUserList::ZUMailUserList%921575859.initialization preserve=yes
  //## end ZUMailUserList::ZUMailUserList%921575859.initialization
{
  //## begin ZUMailUserList::ZUMailUserList%921575859.body preserve=yes
      Fill( pMapiDesc, Count );
  //## end ZUMailUserList::ZUMailUserList%921575859.body
}


ZUMailUserList::~ZUMailUserList()
{
  //## begin ZUMailUserList::~ZUMailUserList%.body preserve=yes
      if (m_MapiRecipDescPtr)
          delete [] m_MapiRecipDescPtr;
      RemoveAllPersons();
  //## end ZUMailUserList::~ZUMailUserList%.body
}



//## Other Operations (implementation)
void ZUMailUserList::Serialize (CArchive& ar)
{
  //## begin ZUMailUserList::Serialize%928062192.body preserve=yes
    m_PersonList.Serialize( ar );
  //## end ZUMailUserList::Serialize%928062192.body
}
//---------------------------------------------------------------------------
MapiRecipDesc* ZUMailUserList::GetMapiRecipDescPtr()
{
    if (m_MapiRecipDescPtr)
        delete[] m_MapiRecipDescPtr;
      
    m_MapiRecipDescPtr = new FAR MapiRecipDesc[GetCount()];
      
    for (register int i = 0; i < GetCount(); ++i)
    {
        std::memset(lpMapiFileDesc(&m_MapiRecipDescPtr[i]), 0, sizeof(MapiRecipDesc));
        m_MapiRecipDescPtr[i].ulRecipClass = GetAt(i)->GetRecipClass();
        m_MapiRecipDescPtr[i].lpszName     = (char*)((const char*)(GetAt(i)->GetPersonName()));
    }

    return m_MapiRecipDescPtr;
}
//---------------------------------------------------------------------------
void ZUMailUserList::Fill(CStringArray& PersonList, ULONG RecipClass)
{
      RemoveAllPersons();

      for (register int i = 0; i < PersonList.GetSize(); ++i)
          AddPerson( PersonList[i], RecipClass );
}
//---------------------------------------------------------------------------
void ZUMailUserList::Fill(ZUUserManager& PersonList, ULONG RecipClass)
{
      RemoveAllPersons();

      for (register size_t i = 0; i < PersonList.GetCount(); ++i)
          AddPerson( *PersonList.GetAt(i), RecipClass );
}
//---------------------------------------------------------------------------
void ZUMailUserList::Fill(lpMapiRecipDesc* pMapiDesc, ULONG Count)
{
  //## begin ZUMailUserList::Fill%921575860.body preserve=yes
      RemoveAllPersons();
      for (register size_t i = 0; i < Count; ++i)
        if (pMapiDesc[i])
            AddPerson( pMapiDesc[i] );
  //## end ZUMailUserList::Fill%921575860.body
}

// Additional Declarations
  //## begin ZUMailUserList%36722C490253.declarations preserve=yes
  //## end ZUMailUserList%36722C490253.declarations

//## begin module%36722E8103D6.epilog preserve=yes
//## end module%36722E8103D6.epilog
