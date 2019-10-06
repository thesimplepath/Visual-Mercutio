/****************************************************************************
 * ==> PSS_NetResourceManager ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a net resource manager                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "ZNetResourceManager.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_NetResourceManager
//---------------------------------------------------------------------------
PSS_NetResourceManager::PSS_NetResourceManager() :
    CObject()
{}
//---------------------------------------------------------------------------
PSS_NetResourceManager::~PSS_NetResourceManager()
{
    RemoveAllNetResources(true);
}
//---------------------------------------------------------------------------
bool PSS_NetResourceManager::AddNetResource(LPNETRESOURCE pNetResource)
{
    // construct the network class object
    std::unique_ptr<PSS_NetResource> pResource(new PSS_NetResource(pNetResource));

    if (AddNetResource(pResource.get()))
    {
        pResource.release();
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_NetResourceManager::AddNetResource(PSS_NetResource* pNetResource)
{
    return m_NetResourceArray.Add(pNetResource) >= 0;
}
//---------------------------------------------------------------------------
bool PSS_NetResourceManager::RemoveNetResource(PSS_NetResource* pNetResource)
{
    const int count = m_NetResourceArray.GetSize();

    for (int i = 0; i < count; ++i)
        if (m_NetResourceArray.GetAt(i) == pNetResource)
        {
            m_NetResourceArray.RemoveAt(i);
            return true;
        }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_NetResourceManager::RemoveNetResourceAt(std::size_t index)
{
    if (int(index) < m_NetResourceArray.GetSize())
    {
        m_NetResourceArray.RemoveAt(index);
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_NetResourceManager::RemoveAllNetResources(bool deleteFromMemory)
{
    if (deleteFromMemory)
    {
        const int count = m_NetResourceArray.GetSize();

        // iterate throught objects and delete the pointer
        for (int i = 0; i < count; ++i)
        {
            if (m_NetResourceArray.GetAt(i))
                delete m_NetResourceArray.GetAt(i);

            m_NetResourceArray.SetAt(i, NULL);
        }
    }

    m_NetResourceArray.RemoveAll();
    return !m_NetResourceArray.GetSize();
}
//---------------------------------------------------------------------------
PSS_NetResource* PSS_NetResourceManager::GetNetResourceAt(std::size_t index)
{
    if (int(index) < m_NetResourceArray.GetSize())
        return static_cast<PSS_NetResource*>(m_NetResourceArray.GetAt(index));

    return NULL;;
}
//---------------------------------------------------------------------------
