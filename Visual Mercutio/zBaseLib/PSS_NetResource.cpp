/****************************************************************************
 * ==> PSS_NetResource -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a net resource                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_NetResource.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_NetResource, CObject)
//---------------------------------------------------------------------------
// PSS_NetResource
//---------------------------------------------------------------------------
PSS_NetResource::PSS_NetResource(NETRESOURCE* pNetResource, bool isDirectory) :
    CObject(),
    m_Scope(0),
    m_Type(0),
    m_DisplayType(0),
    m_Usage(0),
    m_IsDirectory(isDirectory)
{
    *this = *pNetResource;
}
//---------------------------------------------------------------------------
PSS_NetResource::PSS_NetResource(const PSS_NetResource& netResource, bool isDirectory) :
    CObject(),
    m_Scope(0),
    m_Type(0),
    m_DisplayType(0),
    m_Usage(0),
    m_IsDirectory(isDirectory)
{
    *this = netResource;
}
//---------------------------------------------------------------------------
PSS_NetResource::~PSS_NetResource()
{}
//---------------------------------------------------------------------------
const PSS_NetResource& PSS_NetResource::operator = (const PSS_NetResource& other)
{
    m_LocalName   = other.m_LocalName;
    m_RemoteName  = other.m_RemoteName;
    m_Comment     = other.m_Comment;
    m_Provider    = other.m_Provider;
    m_Scope       = other.m_Scope;
    m_Type        = other.m_Type;
    m_DisplayType = other.m_DisplayType;
    m_Usage       = other.m_Usage;
    m_IsDirectory = other.m_IsDirectory;
    return *this;
}
//---------------------------------------------------------------------------
const PSS_NetResource& PSS_NetResource::operator = (const NETRESOURCE& other)
{
    m_LocalName   = other.lpLocalName;
    m_RemoteName  = other.lpRemoteName;
    m_Comment     = other.lpComment;
    m_Provider    = other.lpProvider;
    m_Scope       = other.dwScope;
    m_Type        = other.dwType;
    m_DisplayType = other.dwDisplayType;
    m_Usage       = other.dwUsage;
    return *this;
}
//---------------------------------------------------------------------------
void PSS_NetResource::Initialize(NETRESOURCE& netResource, bool isDirectory)
{
    *this = netResource;
    m_IsDirectory = isDirectory;
}
//---------------------------------------------------------------------------
PSS_NetResource* PSS_NetResource::Clone() const
{
    return new PSS_NetResource(*this);
}
//---------------------------------------------------------------------------
NETRESOURCE* PSS_NetResource::GetNetResourceObject()
{
    std::unique_ptr<NETRESOURCE> pNetResource(new NETRESOURCE());
    pNetResource->dwScope       = m_Scope;
    pNetResource->dwType        = m_Type;
    pNetResource->dwDisplayType = m_DisplayType;
    pNetResource->dwUsage       = m_Usage;

    _tcscpy(pNetResource->lpLocalName,  m_LocalName);
    _tcscpy(pNetResource->lpRemoteName, m_RemoteName);
    _tcscpy(pNetResource->lpComment,    m_Comment);
    _tcscpy(pNetResource->lpProvider,   m_Provider);

    return pNetResource.release();
}
//---------------------------------------------------------------------------
