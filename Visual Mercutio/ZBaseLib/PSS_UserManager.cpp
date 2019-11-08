/****************************************************************************
 * ==> PSS_UserManager -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides an user manager                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_UserManager.h"

 //---------------------------------------------------------------------------
 // PSS_UserManager
 //---------------------------------------------------------------------------
PSS_UserManager::PSS_UserManager()
{}
//---------------------------------------------------------------------------
PSS_UserManager::PSS_UserManager(const PSS_UserManager& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_UserManager::~PSS_UserManager()
{
    RemoveAllUsers();
}
//---------------------------------------------------------------------------
const PSS_UserManager& PSS_UserManager::operator = (const PSS_UserManager& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_UserManager::AddUser(const CString& userName,
                              const CString& mailAddress,
                              const CString& description,
                              const CString& responsible,
                              const CString& departement,
                              BOOL           isAdministrator,
                              const CString& displayName)
{
    std::unique_ptr<PSS_User> pUser(new PSS_User(userName,
                                                 mailAddress,
                                                 description,
                                                 responsible,
                                                 departement,
                                                 isAdministrator,
                                                 displayName));

    m_UserArray.Add(pUser.get());
    pUser.release();
}
//---------------------------------------------------------------------------
void PSS_UserManager::AddUser(PSS_User& user)
{
    m_UserArray.Add(&user);
}
//---------------------------------------------------------------------------
PSS_User* PSS_UserManager::FindUser(const CString& userName, BOOL byDisplayName) const
{
    const std::size_t count = GetCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_User* pUser = GetAt(i);

        if (byDisplayName)
        {
            if (pUser && pUser->GetDisplayName() == userName)
                return pUser;
        }
        else
        if (pUser && *pUser == userName)
            return pUser;
    }

    return NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_UserManager::RemoveUser(const CString& userName, BOOL byDisplayName)
{
    const std::size_t count = GetCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_User* pUser = GetAt(i);

        if (byDisplayName)
        {
            if (pUser && pUser->GetDisplayName() == userName)
            {
                delete pUser;
                m_UserArray.RemoveAt(i);
                return TRUE;
            }
        }
        else
        if (pUser && *pUser == userName)
        {
            delete pUser;
            m_UserArray.RemoveAt(i);
            return TRUE;
        }
    }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_UserManager::RemoveAllUsers()
{
    const std::size_t count = GetCount();

    for (std::size_t i = 0; i < count; ++i)
        delete GetAt(i);

    m_UserArray.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_UserManager::Serialize(CArchive& ar)
{
    m_UserArray.Serialize(ar);
}
//---------------------------------------------------------------------------
