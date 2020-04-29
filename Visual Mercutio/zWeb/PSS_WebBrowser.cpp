/****************************************************************************
 * ==> PSS_WebBrowser ------------------------------------------------------*
 ****************************************************************************
 * Description : Web browser dialog                                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_WebBrowser.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_WebBrowser
//---------------------------------------------------------------------------
PSS_WebBrowser::PSS_WebBrowser()
{}
//---------------------------------------------------------------------------
PSS_WebBrowser::~PSS_WebBrowser()
{}
//---------------------------------------------------------------------------
void PSS_WebBrowser::SetOptions(LPCTSTR pOptions)
{
    m_Options = pOptions;
}
//---------------------------------------------------------------------------
void PSS_WebBrowser::SetParam(VARIANT* pArgs)
{
    m_Args = pArgs;
}
//---------------------------------------------------------------------------
void PSS_WebBrowser::SetParam(LPCTSTR pArgs)
{
    m_Args = pArgs;
}
//---------------------------------------------------------------------------
void PSS_WebBrowser::SetURL(UINT resID, HINSTANCE hInstance)
{
    CString strTemp;
    strTemp.Format(_T("%d"), resID);

    ResourceToURL(strTemp, hInstance);

    COleVariant noArg;
    PSS_WebBrowserBase::Navigate(m_URL, &noArg, &noArg, &noArg, &noArg);
}
//---------------------------------------------------------------------------
void PSS_WebBrowser::SetURL(LPCTSTR pURL, BOOL isRes, HINSTANCE hInstance)
{
    if (isRes)
        ResourceToURL(pURL, hInstance);
    else
        m_URL = pURL;

    COleVariant noArg;
    PSS_WebBrowserBase::Navigate(m_URL, &noArg, &noArg, &noArg, &noArg);
}
//---------------------------------------------------------------------------
void PSS_WebBrowser::SetURL(UINT resID, LPCTSTR pParam, HINSTANCE hInstance)
{
    CString strTemp;
    strTemp.Format(_T("%d"), resID);

    ResourceToURL(strTemp, hInstance);

    // add parameters
    m_URL += _T("?");
    m_URL += pParam;

    COleVariant noArg;
    PSS_WebBrowserBase::Navigate(m_URL, &noArg, &noArg, &noArg, &noArg);
}
//---------------------------------------------------------------------------
void PSS_WebBrowser::SetURL(LPCTSTR pURL, BOOL isRes, LPCTSTR pParam, HINSTANCE hInstance)
{
    if (isRes)
        ResourceToURL(pURL, hInstance);
    else
        m_URL = pURL;

    // add parameters
    m_URL += _T("?");
    m_URL += pParam;

    COleVariant noArg;
    PSS_WebBrowserBase::Navigate(m_URL, &noArg, &noArg, &noArg, &noArg);
}
//---------------------------------------------------------------------------
void PSS_WebBrowser::Navigate()
{
    TCHAR* pOptions = m_Options.IsEmpty() ? NULL : m_Options.GetBuffer(0);

    COleVariant noArg;
    PSS_WebBrowserBase::Navigate(m_URL, &noArg, &noArg, &noArg, &noArg);
}
//---------------------------------------------------------------------------
void PSS_WebBrowser::Navigate(const CString& url)
{
    TCHAR* pOptions = m_Options.IsEmpty() ? NULL : m_Options.GetBuffer(0);

    COleVariant noArg;
    PSS_WebBrowserBase::Navigate(url, &noArg, &noArg, &noArg, &noArg);
}
//---------------------------------------------------------------------------
void PSS_WebBrowser::Navigate( UINT resID, HINSTANCE hInstance)
{
    SetURL(resID, hInstance);
}
//---------------------------------------------------------------------------
void PSS_WebBrowser::Navigate(LPCTSTR pURL, BOOL isRes, HINSTANCE hInstance)
{
    SetURL(pURL, isRes, hInstance);
}
//---------------------------------------------------------------------------
void PSS_WebBrowser::Navigate( UINT resID, LPCTSTR pParam, HINSTANCE hInstance)
{
    SetURL(resID, pParam, hInstance);
}
//---------------------------------------------------------------------------
void PSS_WebBrowser::Navigate(LPCTSTR pURL, BOOL isRes, LPCTSTR pParam, HINSTANCE hInstance)
{
    SetURL(pURL, isRes, pParam, hInstance );
}
//---------------------------------------------------------------------------
CString PSS_WebBrowser::BuildResourceToURL(LPCTSTR pURL, HINSTANCE hInstance)
{
    CString strURL;

    if (!hInstance)
        hInstance = ::AfxGetResourceHandle();

    PSS_Assert(hInstance);

    LPTSTR pModule = NULL;

    try
    {
        pModule = new TCHAR[_MAX_PATH];

        if (::GetModuleFileName(hInstance, pModule, _MAX_PATH))
            strURL.Format(_T("res://%s/%s"), pModule, pURL);
    }
    catch (...)
    {
        delete[] pModule;
        throw;
    }

    delete[] pModule;

    return strURL;
}
//---------------------------------------------------------------------------
