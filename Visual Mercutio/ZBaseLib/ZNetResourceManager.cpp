// ZNetResourceManager.cpp: implementation of the ZNetResourceManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZNetResourceManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZNetResourceManager::ZNetResourceManager() :
    CObject()
{}

ZNetResourceManager::~ZNetResourceManager()
{
    RemoveAllNetResources(true);
}

bool ZNetResourceManager::AddNetResource(LPNETRESOURCE pNetResource)
{
    // Construct the network class object
    std::unique_ptr<PSS_NetResource> pResource(new PSS_NetResource(pNetResource));
    
    if (AddNetResource(pResource.get()))
    {
        pResource.release();
        return true;
    }

    return false;
}

bool ZNetResourceManager::AddNetResource(PSS_NetResource* pNetResource)
{
    return m_NetResourceArray.Add(pNetResource) >= 0;
}

bool ZNetResourceManager::RemoveNetResource(PSS_NetResource* pNetResource)
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

bool ZNetResourceManager::RemoveNetResourceAt(std::size_t index)
{
    if (int(index) < m_NetResourceArray.GetSize())
    {
        m_NetResourceArray.RemoveAt(index);
        return true;
    }

    return false;
}

PSS_NetResource* ZNetResourceManager::GetNetResourceAt(std::size_t index)
{
    if (int(index) < m_NetResourceArray.GetSize())
        return static_cast<PSS_NetResource*>(m_NetResourceArray.GetAt(index));

    return NULL;;
}

bool ZNetResourceManager::RemoveAllNetResources(bool deleteFromMemory)
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
