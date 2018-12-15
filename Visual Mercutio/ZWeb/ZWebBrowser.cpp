// ZWebBrowser.cpp: implementation of the ZWebBrowser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZWebBrowser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 26 janvier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commenatires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZWebBrowser::ZWebBrowser()
{
}

ZWebBrowser::~ZWebBrowser()
{
}

void ZWebBrowser::SetOptions( LPCTSTR lpszOptions )
{
    m_strOptions = lpszOptions;
}

void ZWebBrowser::SetParam( VARIANT *pvarArgs )
{
    m_varArgs = pvarArgs;
}

void ZWebBrowser::SetParam( LPCTSTR lpszArgs )
{
    m_varArgs = lpszArgs;
}

void ZWebBrowser::Navigate()
{
    TCHAR* pchOptions = m_strOptions.IsEmpty() ? NULL : m_strOptions.GetBuffer( 0 );

    COleVariant noArg;
    CWebBrowser::Navigate( m_strURL, &noArg, &noArg, &noArg, &noArg );
}

void ZWebBrowser::Navigate( const CString strURL )
{
    TCHAR* pchOptions = m_strOptions.IsEmpty() ? NULL : m_strOptions.GetBuffer( 0 );

    COleVariant noArg;
    CWebBrowser::Navigate( strURL, &noArg, &noArg, &noArg, &noArg );
}

void ZWebBrowser::Navigate( UINT nResID, HINSTANCE hInstance /*= NULL*/ )
{
    SetURL( nResID, hInstance );
}

void ZWebBrowser::Navigate( LPCTSTR lpszURL, BOOL bRes, HINSTANCE hInstance /*= NULL*/ )
{
    SetURL( lpszURL, bRes, hInstance );
}

void ZWebBrowser::Navigate( UINT nResID, LPCTSTR lpszParam, HINSTANCE hInstance /*= NULL*/ )
{
    SetURL( nResID, lpszParam, hInstance );
}

void ZWebBrowser::Navigate( LPCTSTR lpszURL, BOOL bRes, LPCTSTR lpszParam, HINSTANCE hInstance /*= NULL*/ )
{
    SetURL( lpszURL, bRes, lpszParam, hInstance );
}

void ZWebBrowser::SetURL( UINT nResID, HINSTANCE hInstance /*= NULL*/ )
{
    CString strTemp;
    strTemp.Format( _T( "%d" ), nResID );
    
    ResourceToURL( strTemp, hInstance );
    COleVariant noArg;
    CWebBrowser::Navigate( m_strURL, &noArg, &noArg, &noArg, &noArg );
}

void ZWebBrowser::SetURL( LPCTSTR lpszURL, BOOL bRes, HINSTANCE hInstance /*= NULL*/ )
{
    if ( bRes )
    {
        ResourceToURL( lpszURL, hInstance );
    }
    else
    {
        m_strURL = lpszURL;
    }

    COleVariant noArg;
    CWebBrowser::Navigate( m_strURL, &noArg, &noArg, &noArg, &noArg );
}

void ZWebBrowser::SetURL( UINT nResID, LPCTSTR lpszParam, HINSTANCE hInstance /*= NULL*/ )
{
    CString strTemp;
    strTemp.Format( _T( "%d" ), nResID );

    ResourceToURL( strTemp, hInstance );

    // Add parameters
    m_strURL += _T( "?" );
    m_strURL += lpszParam;

    COleVariant noArg;
    CWebBrowser::Navigate( m_strURL, &noArg, &noArg, &noArg, &noArg );
}

void ZWebBrowser::SetURL( LPCTSTR lpszURL, BOOL bRes, LPCTSTR lpszParam, HINSTANCE hInstance /*= NULL*/ )
{
    if ( bRes )
    {
        ResourceToURL( lpszURL, hInstance );
    }
    else
    {
        m_strURL = lpszURL;
    }

    // Add parameters
    m_strURL += _T( "?" );
    m_strURL += lpszParam;

    COleVariant noArg;
    CWebBrowser::Navigate( m_strURL, &noArg, &noArg, &noArg, &noArg );
}

void ZWebBrowser::ResourceToURL( LPCTSTR lpszURL, HINSTANCE hInstance /*= NULL*/ )
{
    if ( hInstance == NULL )
    {
        hInstance = AfxGetResourceHandle();
    }

    ASSERT( hInstance != NULL );

    LPTSTR lpszModule = new TCHAR[_MAX_PATH];

    if ( GetModuleFileName( hInstance, lpszModule, _MAX_PATH ) )
    {
        m_strURL.Format( _T( "res://%s/%s" ), lpszModule, lpszURL );
    }

    delete []lpszModule;
}

CString ZWebBrowser::BuildResourceToURL( LPCTSTR lpszURL, HINSTANCE hInstance /*= NULL*/ )
{
    CString strURL;

    if ( hInstance == NULL )
    {
        hInstance = AfxGetResourceHandle();
    }

    ASSERT( hInstance != NULL );

    LPTSTR lpszModule = new TCHAR[_MAX_PATH];

    if ( GetModuleFileName( hInstance, lpszModule, _MAX_PATH ) )
    {
        strURL.Format( _T( "res://%s/%s" ), lpszModule, lpszURL );
    }

    delete []lpszModule;
    return strURL;
}
