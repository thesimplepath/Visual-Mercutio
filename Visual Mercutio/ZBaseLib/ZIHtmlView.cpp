// ZIHtmlView.cpp : implementation file
//

#include "stdafx.h"
#include "ZIHtmlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIHtmlView

IMPLEMENT_DYNCREATE(ZIHtmlView, CHtmlView)

ZIHtmlView::ZIHtmlView()
{
	//{{AFX_DATA_INIT(ZIHtmlView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

ZIHtmlView::~ZIHtmlView()
{
}

void ZIHtmlView::Navigate(UINT nResID, DWORD dwFlags /*= 0*/, LPCTSTR lpszTargetFrameName /*= NULL*/)
{
	CString strTemp;
	strTemp.Format("%d", nResID);
	
	ResourceToURL(strTemp);
	// And now display the html or other file
	Navigate2( m_strURL, dwFlags, lpszTargetFrameName );
}

void ZIHtmlView::Navigate(LPCTSTR lpszURL, BOOL bRes, DWORD dwFlags /*= 0*/, LPCTSTR lpszTargetFrameName /*= NULL*/)
{
	if (bRes)
	{
		ResourceToURL(lpszURL);
	}
	else
		m_strURL = lpszURL;
	// And now display the html or other file
	Navigate2( m_strURL, dwFlags, lpszTargetFrameName );
}


void ZIHtmlView::ResourceToURL(LPCTSTR lpszURL)
{
	HINSTANCE hInstance = AfxGetResourceHandle();
	ASSERT(hInstance != NULL);
	
	LPTSTR lpszModule = new TCHAR[_MAX_PATH];
	
	if (GetModuleFileName(hInstance, lpszModule, _MAX_PATH))
	{
		m_strURL.Format(_T("res://%s/%s"), lpszModule, lpszURL);
	}
	
	delete []lpszModule;
}


void ZIHtmlView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZIHtmlView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZIHtmlView, CHtmlView)
	//{{AFX_MSG_MAP(ZIHtmlView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIHtmlView diagnostics

#ifdef _DEBUG
void ZIHtmlView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void ZIHtmlView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZIHtmlView message handlers
