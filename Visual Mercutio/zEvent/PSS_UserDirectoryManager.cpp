/****************************************************************************
 * ==> PSS_UserDirectoryManager --------------------------------------------*
 ****************************************************************************
 * Description : Provides an user directory manager                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_UserDirectoryManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_UserDirectoryManager
//---------------------------------------------------------------------------
PSS_UserDirectoryManager::PSS_UserDirectoryManager(const CString& directory) :
    m_Directory(directory),
    m_BufferLength(sizeof(m_CurrentDir) - 1)
{}
//---------------------------------------------------------------------------
PSS_UserDirectoryManager::~PSS_UserDirectoryManager()
{}
//---------------------------------------------------------------------------
BOOL PSS_UserDirectoryManager::SetDirectory(const CString& value)
{
    if (value.GetAt(value.GetLength() - 1) == '\\')
        m_Directory = value.Left(value.GetLength() - 1);
    else
        m_Directory = value;

    // make the queue directory in lower case
    m_Directory.MakeLower();

    // save the current directory
    SaveCurrentDirectory();

    // check if the directory already exists
    if (!::SetCurrentDirectory((const char*)m_Directory))
        // the directory does not exists, create it
        if (!::CreateDirectory((const char*)m_Directory, NULL))
        {
            m_Directory.Empty();
            return FALSE;
        }

    // set back the directory
    SetLastCurrentDirectory();
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UserDirectoryManager::CreateUser(const CString& userName)
{
    if (UserExist(userName))
        return TRUE;

    if (!::CreateDirectory((const char*)BuildUserDirectory(userName), NULL))
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_UserDirectoryManager::UserExist(const CString& userName)
{
    // save the current directory
    SaveCurrentDirectory();

    // check if the directory already exists
    if (SetCurrentDirectory((const char*)BuildUserDirectory(userName)) == 0)
        return FALSE;

    // set back the directory
    SetLastCurrentDirectory();
    return TRUE;
}
//---------------------------------------------------------------------------
