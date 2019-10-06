/****************************************************************************
 * ==> PSS_NetResourceWrapper ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a net resource wrapper                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "ZNetResourceWrapper.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_NetResourceWrapper, CObject)
//---------------------------------------------------------------------------
// PSS_NetResourceWrapper
//---------------------------------------------------------------------------
PSS_NetResourceWrapper::PSS_NetResourceWrapper(const CString& fileName, NETRESOURCE* pNetResource, bool isDir) :
    CObject(),
    m_pNetResource(pNetResource),
    m_FileName(fileName),
    m_IsDir(IsDir)
{}
//---------------------------------------------------------------------------
PSS_NetResourceWrapper::~PSS_NetResourceWrapper()
{
    if (m_pNetResource)
    {
        delete[] m_pNetResource->lpLocalName;
        delete[] m_pNetResource->lpRemoteName;
        delete[] m_pNetResource->lpComment;
        delete[] m_pNetResource->lpProvider;
        delete   m_pNetResource;
    }
}
//---------------------------------------------------------------------------
void PSS_NetResourceWrapper::Initialize(const CString& fileName, NETRESOURCE* pNetResource, bool isDir)
{
    m_pNetResource = pNetResource;
    m_FileName     = fileName;
    m_IsDir        = isDir;
}
//---------------------------------------------------------------------------
