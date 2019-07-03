// HtmlDlg.cpp: implementation of the ZHtmlDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <mshtmhst.h>
#include "HtmlDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 26 janvier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commenatires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZHtmlDialog::ZHtmlDialog()
{
    TRACE0( _T( "Warning: Initialization may not be done: Non Functional contructor" ) );
}

ZHtmlDialog::~ZHtmlDialog()
{
    //Free the Mshtml.dll
    ::FreeLibrary( m_hInstMSHTML );
}

ZHtmlDialog::ZHtmlDialog( UINT nResID, CWnd* pParent/*= NULL*/ )
{
    m_hWndParent = pParent ? pParent->GetSafeHwnd() : NULL;

    CString strTemp;
    strTemp.Format( _T( "%d" ), nResID );
    
    ResourceToURL( strTemp );
    CommonConstruct();
}

ZHtmlDialog::ZHtmlDialog( LPCTSTR lpszURL, BOOL bRes, CWnd* pParent/*= NULL*/ )
{
    m_hWndParent = pParent ?  pParent->GetSafeHwnd() : NULL;

    if ( bRes )
    {
        ResourceToURL( lpszURL );
    }
    else
    {
        m_strURL = lpszURL;
    }

    CommonConstruct();
}

int ZHtmlDialog::DoModal()
{
    //First get the proc ShowHTMLDialog
    SHOWHTMLDIALOGFN *pfnShowHTMLDialog;

    pfnShowHTMLDialog = (SHOWHTMLDIALOGFN*)GetProcAddress( m_hInstMSHTML, TEXT( _T( "ShowHTMLDialog" ) ) );
    
    if ( !pfnShowHTMLDialog )
        return -1;

    // Now create a URL Moniker
    IMoniker*    pmk        = NULL;
    BSTR        bstrURL    = m_strURL.AllocSysString();

    CreateURLMoniker( NULL, bstrURL, &pmk );

    if ( !pmk )
    {
        return -1;
    }

    TCHAR* pchOptions = m_strOptions.IsEmpty() ? NULL : m_strOptions.GetBuffer( 0 );

    VARIANT varArgs;
    VARIANT varReturn;

    VariantInit( &varReturn );
    VariantInit( &varArgs );

//    varArgs.vt        = VT_BSTR;
//    varArgs.bstrVal    = SysAllocString( L"Argument 1;Argument 2;Argument 3;Argument 4" );

    // Now show the HTML Dialog
    HRESULT hr = (*pfnShowHTMLDialog)( m_hWndParent, pmk, &varArgs, NULL/*pchOptions*/, &varReturn );
//    HRESULT hr = NULL;

    pmk->Release();

    if ( FAILED( hr ) )
    {
        return -1;
    }

    return 0;
}

void ZHtmlDialog::CommonConstruct()
{
    m_hInstMSHTML = ::LoadLibrary( TEXT( _T( "MSHTML.DLL" ) ) );
    
}

void ZHtmlDialog::ResourceToURL( LPCTSTR lpszURL )
{
    HINSTANCE hInstance = AfxGetResourceHandle();
    ASSERT( hInstance != NULL );
    
    LPTSTR lpszModule = new TCHAR[_MAX_PATH];
    
    if( GetModuleFileName( hInstance, lpszModule, _MAX_PATH ) )
    {
        m_strURL.Format( _T( "res://%s/%s" ), lpszModule, lpszURL );
    }

    delete []lpszModule;
}


void ZHtmlDialog::SetParam( VARIANT *pvarArgs )
{
    m_varArgs = pvarArgs;
}

void ZHtmlDialog::SetParam( LPCTSTR lpszArgs )
{
    m_varArgs = lpszArgs;
}

CString ZHtmlDialog::GetReturnString()
{
    ASSERT( m_varReturn.vt == VT_BSTR );
    CString str = m_varReturn.bstrVal;

    return str;
}

LPCVARIANT ZHtmlDialog::GetReturnVariant()
{
    return (LPCVARIANT)m_varReturn;
}

void ZHtmlDialog::SetSize( int x, int y )
{
    m_strOptions.Format( _T( "dialogWidth: %d; dialogHeight: %d" ), x, y );
}

void ZHtmlDialog::SetDlgOptions( LPCTSTR lpszOptions )
{
    m_strOptions = lpszOptions;
}
