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

	bool			AddNetResource( LPNETRESOURCE pNetResource );
	bool			AddNetResource( ZNetResource* pNetResource );
	bool			RemoveNetResource( ZNetResource* pNetResource );
	bool			RemoveNetResourceAt( size_t Index );
	ZNetResource*	GetNetResourceAt( size_t Index );
	bool			RemoveAllNetResources( bool DeleteFromMemory = true );
	size_t			GetNetResourceCount();

private:
	CObArray	m_NetResourceArray;

};


inline	size_t	ZNetResourceManager::GetNetResourceCount()
{
	return m_NetResourceArray.GetSize();
}

#endif // !defined(AFX_ZNETRESOURCEMANAGER_H__F7642919_778A_41A3_9F2E_32C21F48C85E__INCLUDED_)
