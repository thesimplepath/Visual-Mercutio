// ZNetResourceWrapper.cpp: implementation of the ZNetResourceWrapper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZNetResourceWrapper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( ZNetResourceWrapper, CObject )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZNetResourceWrapper::ZNetResourceWrapper( const CString    Filename,
                                          NETRESOURCE*    pNetResource    /*= NULL*/,
                                          bool            IsDirectory        /*= false*/ )
    : m_IsDirectory    ( IsDirectory ),
      m_pNetResource( pNetResource ),
      m_Filename    ( Filename )
{
}

ZNetResourceWrapper::~ZNetResourceWrapper()
{
    if ( m_pNetResource )
    {
        delete [] ( m_pNetResource->lpLocalName );
        ( m_pNetResource->lpLocalName ) = NULL;

        delete [] ( m_pNetResource->lpRemoteName );
        ( m_pNetResource->lpRemoteName ) = NULL;

        delete [] ( m_pNetResource->lpComment );
        ( m_pNetResource->lpComment ) = NULL;

        delete [] ( m_pNetResource->lpProvider );
        ( m_pNetResource->lpProvider ) = NULL;

        delete m_pNetResource;
    }

    m_pNetResource = NULL;
}

void ZNetResourceWrapper::Initialize( const CString    Filename,
                                      NETRESOURCE*    pNetResource    /*= NULL*/,
                                      bool            IsDirectory        /*= false*/ )
{
    m_Filename        = Filename;
    m_pNetResource    = pNetResource;
    m_IsDirectory    = IsDirectory;
}
