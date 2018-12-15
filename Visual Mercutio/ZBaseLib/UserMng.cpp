//## begin module%36725FC1029F.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%36725FC1029F.cm

//## begin module%36725FC1029F.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%36725FC1029F.cp

//## Module: UserMng%36725FC1029F; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\UserMng.cpp

//## begin module%36725FC1029F.additionalIncludes preserve=no
//## end module%36725FC1029F.additionalIncludes

//## begin module%36725FC1029F.includes preserve=yes
#include <StdAfx.h>
//## end module%36725FC1029F.includes

// UserMng
#include "UserMng.h"
//## begin module%36725FC1029F.declarations preserve=no
//## end module%36725FC1029F.declarations

//## begin module%36725FC1029F.additionalDeclarations preserve=yes
//## end module%36725FC1029F.additionalDeclarations


// Class ZUUserManager 


ZUUserManager::ZUUserManager()
  //## begin ZUUserManager::ZUUserManager%.hasinit preserve=no
  //## end ZUUserManager::ZUUserManager%.hasinit
  //## begin ZUUserManager::ZUUserManager%.initialization preserve=yes
  //## end ZUUserManager::ZUUserManager%.initialization
{
  //## begin ZUUserManager::ZUUserManager%.body preserve=yes
  //## end ZUUserManager::ZUUserManager%.body
}


ZUUserManager::~ZUUserManager()
{
  //## begin ZUUserManager::~ZUUserManager%.body preserve=yes
      RemoveAllUsers();
  //## end ZUUserManager::~ZUUserManager%.body
}



//## Other Operations (implementation)
void ZUUserManager::AddUser (CString UserName, CString MailAddress, CString Description, CString Responsible, CString Departement, BOOL IsAdministrator, CString DisplayName)
{
  //## begin ZUUserManager::AddUser%913459633.body preserve=yes
      m_UserArray.Add( (CObject*)new ZUser(UserName, MailAddress, Description, Responsible, Departement, IsAdministrator, DisplayName) );
  //## end ZUUserManager::AddUser%913459633.body
}

void ZUUserManager::AddUser (ZUser& User)
{
  //## begin ZUUserManager::AddUser%913459634.body preserve=yes
      m_UserArray.Add( (CObject*)&User );
  //## end ZUUserManager::AddUser%913459634.body
}

void ZUUserManager::Serialize (CArchive& ar)
{
  //## begin ZUUserManager::Serialize%913459635.body preserve=yes
      m_UserArray.Serialize( ar );
  //## end ZUUserManager::Serialize%913459635.body
}

void ZUUserManager::RemoveAllUsers ()
{
  //## begin ZUUserManager::RemoveAllUsers%913459636.body preserve=yes
      for (size_t i = 0; i < GetCount(); ++i)
          delete GetAt(i);
      m_UserArray.RemoveAll();
  //## end ZUUserManager::RemoveAllUsers%913459636.body
}

ZUser* ZUUserManager::FindUser (const CString& UserName, BOOL ByDisplayName)
{
  //## begin ZUUserManager::FindUser%913459637.body preserve=yes
      for (size_t i = 0; i < GetCount(); ++i)
    {
        if (ByDisplayName)
        {
              if (GetAt(i) && GetAt(i)->GetDisplayName() == UserName)
                  return GetAt(i);
        }
        else
        {
              if (GetAt(i) && *GetAt(i) == UserName)
                  return GetAt(i);
        }
    }
      return NULL;
  //## end ZUUserManager::FindUser%913459637.body
}

BOOL ZUUserManager::RemoveUser (const CString& UserName, BOOL ByDisplayName)
{
  //## begin ZUUserManager::RemoveUser%913459638.body preserve=yes
      for (size_t i = 0; i < GetCount(); ++i)
    {
        if (ByDisplayName)
        {
              if (GetAt(i) && GetAt(i)->GetDisplayName() == UserName)
              {
                  delete GetAt(i);
                  m_UserArray.RemoveAt(i);
                  return TRUE;
              }
        }
        else
        {
              if (GetAt(i) && *GetAt(i) == UserName)
              {
                  delete GetAt(i);
                  m_UserArray.RemoveAt(i);
                  return TRUE;
              }
        }
    }        
      return FALSE;
  //## end ZUUserManager::RemoveUser%913459638.body
}

// Additional Declarations
  //## begin ZUUserManager%36725E3B017C.declarations preserve=yes
  //## end ZUUserManager%36725E3B017C.declarations

//## begin module%36725FC1029F.epilog preserve=yes
//## end module%36725FC1029F.epilog
