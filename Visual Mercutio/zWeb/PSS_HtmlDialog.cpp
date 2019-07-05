/****************************************************************************
 * ==> PSS_HtmlDialog ------------------------------------------------------*
 ****************************************************************************
 * Description : Dialog to show a html content                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_HtmlDialog.h"

// Windows
#include <mshtmhst.h>

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_HtmlDialog
//---------------------------------------------------------------------------
PSS_HtmlDialog::PSS_HtmlDialog() :
    m_hParent(NULL),
    m_hMSHTML(NULL)
{
    TRACE0(_T("Warning: Initialization may not be done: Non Functional contructor"));
}
//---------------------------------------------------------------------------
PSS_HtmlDialog::PSS_HtmlDialog(UINT resID, CWnd* pParent) :
    m_hParent(NULL),
    m_hMSHTML(NULL)
{
    m_hParent = pParent ? pParent->GetSafeHwnd() : NULL;

    CString strTemp;
    strTemp.Format(_T( "%d" ), resID);

    ResourceToURL(strTemp);
    Init();
}
//---------------------------------------------------------------------------
PSS_HtmlDialog::PSS_HtmlDialog(LPCTSTR pURL, BOOL isRes, CWnd* pParent) :
    m_hParent(NULL),
    m_hMSHTML(NULL)
{
    m_hParent = pParent ?  pParent->GetSafeHwnd() : NULL;

    if (isRes)
        ResourceToURL(pURL);
    else
        m_URL = pURL;

    Init();
}
//---------------------------------------------------------------------------
PSS_HtmlDialog::~PSS_HtmlDialog()
{
    // release the Mshtml.dll
    ::FreeLibrary(m_hMSHTML);
}
//---------------------------------------------------------------------------
void PSS_HtmlDialog::SetOptions(LPCTSTR pOptions)
{
    m_Options = pOptions;
}
//---------------------------------------------------------------------------
void PSS_HtmlDialog::SetSize(int width, int height)
{
    m_Options.Format(_T("dialogWidth: %d; dialogHeight: %d"), width, height);
}
//---------------------------------------------------------------------------
void PSS_HtmlDialog::SetParam(VARIANT* pArgs)
{
    m_Args = pArgs;
}
//---------------------------------------------------------------------------
void PSS_HtmlDialog::SetParam(LPCTSTR pArgs)
{
    m_Args = pArgs;
}
//---------------------------------------------------------------------------
LPCVARIANT PSS_HtmlDialog::GetReturnVariant()
{
    return LPCVARIANT(m_Return);
}
//---------------------------------------------------------------------------
CString PSS_HtmlDialog::GetReturnString()
{
    ASSERT(m_Return.vt == VT_BSTR);
    return m_Return.bstrVal;
}
//---------------------------------------------------------------------------
int PSS_HtmlDialog::DoModal()
{
    // get the ShowHTMLDialog proc
    SHOWHTMLDIALOGFN* pShowHTMLDialog = (SHOWHTMLDIALOGFN*)::GetProcAddress(m_hMSHTML, TEXT(_T("ShowHTMLDialog")));
    
    if (!pShowHTMLDialog)
        return -1;

    // create a URL Moniker
    IMoniker* pMK = NULL;
    BSTR      url = m_URL.AllocSysString();

    ::CreateURLMoniker(NULL, url, &pMK);

    if (!pMK)
        return -1;

    HRESULT hr;

    try
    {
        TCHAR* pOptions = m_Options.IsEmpty() ? NULL : m_Options.GetBuffer(0);

        VARIANT varArgs;
        VARIANT varReturn;

        ::VariantInit(&varReturn);
        ::VariantInit(&varArgs);

        // show the HTML dialog
        hr = (*pShowHTMLDialog)(m_hParent, pMK, &varArgs, NULL, &varReturn);
    }
    catch (...)
    {
        pMK->Release();
        throw;
    }

    pMK->Release();

    if (FAILED(hr))
        return -1;

    return 0;
}
//---------------------------------------------------------------------------
void PSS_HtmlDialog::Init()
{
    m_hMSHTML = ::LoadLibrary(TEXT(_T("MSHTML.DLL")));
}
//---------------------------------------------------------------------------
