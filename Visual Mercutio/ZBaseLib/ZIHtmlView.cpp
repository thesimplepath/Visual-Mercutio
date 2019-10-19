/****************************************************************************
 * ==> PSS_HtmlView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides an html view                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "ZIHtmlView.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_HtmlView, CHtmlView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_HtmlView, CHtmlView)
    //{{AFX_MSG_MAP(PSS_HtmlView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_HtmlView
//---------------------------------------------------------------------------
PSS_HtmlView::PSS_HtmlView() :
    CHtmlView()
{}
//---------------------------------------------------------------------------
PSS_HtmlView::~PSS_HtmlView()
{}
//---------------------------------------------------------------------------
void PSS_HtmlView::Navigate(UINT resID, DWORD flags, LPCTSTR pTargetFrameName)
{
    CString strTemp;
    strTemp.Format("%d", resID);
    ResourceToURL(strTemp);

    // show the html or other file
    Navigate2(m_URL, flags, pTargetFrameName);
}
//---------------------------------------------------------------------------
void PSS_HtmlView::Navigate(LPCTSTR pURL, BOOL res, DWORD flags, LPCTSTR pTargetFrameName)
{
    if (res)
        ResourceToURL(pURL);
    else
        m_URL = pURL;

    // show the html or other file
    Navigate2(m_URL, flags, pTargetFrameName);
}
//---------------------------------------------------------------------------
void PSS_HtmlView::DoDataExchange(CDataExchange* pDX)
{
    CHtmlView::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_HtmlView)
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
void PSS_HtmlView::ResourceToURL(LPCTSTR pUrl)
{
    HINSTANCE hInstance = AfxGetResourceHandle();
    ASSERT(hInstance != NULL);

    LPTSTR pModule = new TCHAR[_MAX_PATH];

    try
    {
        if (::GetModuleFileName(hInstance, pModule, _MAX_PATH))
            m_URL.Format(_T("res://%s/%s"), pModule, pUrl);
    }
    catch (...)
    {
        delete[] pModule;
        throw;
    }

    delete[] pModule;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HtmlView::AssertValid() const
    {
        CHtmlView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_HtmlView::Dump(CDumpContext& dc) const
    {
        CHtmlView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
