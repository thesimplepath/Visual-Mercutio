// ZNetResource.cpp: implementation of the ZNetResource class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZNetResource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(ZNetResource, CObject)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZNetResource::ZNetResource(NETRESOURCE* pNetResource /*= NULL*/, bool IsDirectory /*= false*/)
: m_IsDirectory(IsDirectory)
{
    *this = *pNetResource;
}

ZNetResource::ZNetResource(ZNetResource& NetResource, bool IsDirectory /*= false*/)
: m_IsDirectory(IsDirectory)
{
    *this = NetResource;
}

const ZNetResource& ZNetResource::operator=(const ZNetResource &right)
{
    m_Scope = right.m_Scope; 
    m_Type = right.m_Type; 
    m_DisplayType = right.m_DisplayType; 
    m_Usage = right.m_Usage; 
    m_LocalName = right.m_LocalName; 
    m_RemoteName = right.m_RemoteName; 
    m_Comment = right.m_Comment; 
    m_Provider = right.m_Provider; 
    m_IsDirectory = right.m_IsDirectory;
    return *this;
}

const ZNetResource& ZNetResource::operator=(const NETRESOURCE &right)
{
    m_Scope = right.dwScope; 
    m_Type = right.dwType; 
    m_DisplayType = right.dwDisplayType; 
    m_Usage = right.dwUsage; 
    m_LocalName = right.lpLocalName; 
    m_RemoteName = right.lpRemoteName; 
    m_Comment = right.lpComment; 
    m_Provider = right.lpProvider; 
    return *this;
}


NETRESOURCE*    ZNetResource::GetNetResourceObject()
{
    NETRESOURCE*    pNetResource = new NETRESOURCE;
    pNetResource->dwScope = m_Scope;
    pNetResource->dwType = m_Type;
    pNetResource->dwDisplayType = m_DisplayType;
    pNetResource->dwUsage = m_Usage;
    _tcscpy( pNetResource->lpLocalName, m_LocalName );
    _tcscpy( pNetResource->lpRemoteName, m_RemoteName );
    _tcscpy( pNetResource->lpComment, m_Comment );
    _tcscpy( pNetResource->lpProvider, m_Provider ); 
    return pNetResource;
}

ZNetResource*    ZNetResource::Clone()
{
    ZNetResource*    pNewResource = new ZNetResource( *this );
    return pNewResource;
}

ZNetResource::~ZNetResource()
{

}


void ZNetResource::Initialize( NETRESOURCE& NetResource, bool IsDirectory /*= false*/ )
{
    *this = NetResource;
    m_IsDirectory = IsDirectory;
}
