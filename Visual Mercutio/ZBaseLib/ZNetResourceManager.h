// ZNetResourceManager.h: interface for the ZNetResourceManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZNETRESOURCEMANAGER_H__F7642919_778A_41A3_9F2E_32C21F48C85E__INCLUDED_)
#define AFX_ZNETRESOURCEMANAGER_H__F7642919_778A_41A3_9F2E_32C21F48C85E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "ZNetResource.h"


#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS


class AFX_EXT_CLASS ZNetResourceManager : public CObject
{
public:
    ZNetResourceManager();
    virtual ~ZNetResourceManager();

    virtual bool AddNetResource(LPNETRESOURCE pNetResource);
    virtual bool AddNetResource(PSS_NetResource* pNetResource);
    virtual bool RemoveNetResource(PSS_NetResource* pNetResource);
    virtual bool RemoveNetResourceAt(std::size_t index);
    virtual PSS_NetResource* GetNetResourceAt(std::size_t index);
    virtual bool RemoveAllNetResources(bool deleteFromMemory = true);

    virtual inline std::size_t GetNetResourceCount() const;

private:
    CObArray m_NetResourceArray;
};


std::size_t ZNetResourceManager::GetNetResourceCount() const
{
    return m_NetResourceArray.GetSize();
}

#endif
