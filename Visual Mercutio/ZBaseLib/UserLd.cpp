//## begin module%368CD3690384.cm preserve=no
//      %X% %Q% %Z% %W%
//## end module%368CD3690384.cm

//## begin module%368CD3690384.cp preserve=no
//    ADSoft / Advanced Dedicated Software
//    Dominique AIGROZ
//## end module%368CD3690384.cp

//## Module: UserLd%368CD3690384; Package body
//## Subsystem: ZUtil%366D71940075
//## Source file: z:\adsoft~1\ZUtil\UserLd.cpp

//## begin module%368CD3690384.additionalIncludes preserve=no
//## end module%368CD3690384.additionalIncludes

//## begin module%368CD3690384.includes preserve=yes
#include <StdAfx.h>
//## end module%368CD3690384.includes

// UserLd
#include "UserLd.h"
//## begin module%368CD3690384.declarations preserve=no
//## end module%368CD3690384.declarations

//## begin module%368CD3690384.additionalDeclarations preserve=yes
//## end module%368CD3690384.additionalDeclarations


// Class ZDUserLoader 




ZDUserLoader::~ZDUserLoader()
{
  //## begin ZDUserLoader::~ZDUserLoader%.body preserve=yes
  //## end ZDUserLoader::~ZDUserLoader%.body
}



//## Other Operations (implementation)
BOOL ZDUserLoader::LoadAllUsers ()
{
  //## begin ZDUserLoader::LoadAllUsers%915200904.body preserve=yes
      ASSERT( m_pUserManager );
    m_UserImport.Create( m_FileName, m_pUserManager, FALSE, E_SS_Tab);
    return m_UserImport.Import();
  //## end ZDUserLoader::LoadAllUsers%915200904.body
}

BOOL ZDUserLoader::SaveAllUsers ()
{
  //## begin ZDUserLoader::SaveAllUsers%915200905.body preserve=yes
      ASSERT( m_pUserManager );
      return TRUE;
  //## end ZDUserLoader::SaveAllUsers%915200905.body
}

void ZDUserLoader::AssignUserManager (ZUUserManager* pUserManager)
{
  //## begin ZDUserLoader::AssignUserManager%915200906.body preserve=yes
      ASSERT( pUserManager );
      m_pUserManager = pUserManager;
  //## end ZDUserLoader::AssignUserManager%915200906.body
}

void ZDUserLoader::AssignFileName (CString FileName)
{
  //## begin ZDUserLoader::AssignFileName%922203372.body preserve=yes
      ASSERT( !FileName.IsEmpty() );
    m_FileName = FileName;
  //## end ZDUserLoader::AssignFileName%922203372.body
}

// Additional Declarations
  //## begin ZDUserLoader%368CD2BE0136.declarations preserve=yes
  //## end ZDUserLoader%368CD2BE0136.declarations

//## begin module%368CD3690384.epilog preserve=yes
//## end module%368CD3690384.epilog
