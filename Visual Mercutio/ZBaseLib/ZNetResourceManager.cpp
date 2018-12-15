// ZNetResourceManager.cpp: implementation of the ZNetResourceManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZNetResourceManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZNetResourceManager::ZNetResourceManager()
{

}

ZNetResourceManager::~ZNetResourceManager()
{
    RemoveAllNetResources( true );
}


bool    ZNetResourceManager::AddNetResource( LPNETRESOURCE pNetResource )
{
    // Construct the network class object
    ZNetResource*    pResource = new ZNetResource( pNetResource );

    return AddNetResource( pResource );
}

bool    ZNetResourceManager::AddNetResource( ZNetResource* pNetResource )
{
    return m_NetResourceArray.Add( (CObject*)pNetResource ) >= 0;
}

bool    ZNetResourceManager::RemoveNetResource( ZNetResource* pNetResource )
{
    for (int i = 0; i < m_NetResourceArray.GetSize(); ++i)
    {
        if (m_NetResourceArray.GetAt(i) == (CObject*)pNetResource)
        {
            m_NetResourceArray.RemoveAt(i);
            return true;
        }
    }
    return false;
}

bool    ZNetResourceManager::RemoveNetResourceAt( size_t Index )
{
    if ((int)Index < m_NetResourceArray.GetSize())
    {
        m_NetResourceArray.RemoveAt( Index );
        return true;
    }
    return false;
}

ZNetResource*    ZNetResourceManager::GetNetResourceAt( size_t Index )
{
    if ((int)Index < m_NetResourceArray.GetSize())
    {
        return (ZNetResource*)m_NetResourceArray.GetAt( Index );
    }
    return NULL;;
}


bool    ZNetResourceManager::RemoveAllNetResources( bool DeleteFromMemory /*= true*/ )
{
    if (DeleteFromMemory)
    {
        // Run throught objects and delete the pointer
        for (int i = 0; i < m_NetResourceArray.GetSize(); ++i)
        {
            if (m_NetResourceArray.GetAt(i))
                delete (ZNetResource*)m_NetResourceArray.GetAt(i);
            m_NetResourceArray.SetAt(i, NULL);
        }

    }
    m_NetResourceArray.RemoveAll();
    return m_NetResourceArray.GetSize() == 0;
}
