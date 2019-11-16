/****************************************************************************
 * ==> PSS_UserLoader ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user loader                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_UserLoader.h"

//---------------------------------------------------------------------------
// PSS_UserLoader
//---------------------------------------------------------------------------
PSS_UserLoader::PSS_UserLoader(const PSS_UserLoader& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_UserLoader::~PSS_UserLoader()
{}
//---------------------------------------------------------------------------
const PSS_UserLoader& PSS_UserLoader::operator = (const PSS_UserLoader& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_UserLoader::LoadAllUsers()
{
    ASSERT(m_pUserManager);
    m_UserImport.Create(m_FileName, m_pUserManager, FALSE, E_SS_Tab);

    return m_UserImport.Import();
}
//---------------------------------------------------------------------------
BOOL PSS_UserLoader::SaveAllUsers()
{
    ASSERT(m_pUserManager);
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_UserLoader::AssignUserManager(PSS_UserManager* pUserManager)
{
    ASSERT(pUserManager);
    m_pUserManager = pUserManager;
}
//---------------------------------------------------------------------------
void PSS_UserLoader::AssignFileName(CString FileName)
{
    ASSERT(!FileName.IsEmpty());
    m_FileName = FileName;
}
//---------------------------------------------------------------------------
