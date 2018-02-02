// HtmlDlg.h: interface for the ZHtmlDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZDLGHTML_H__00C54337_702E_11D2_ABF7_CCFAF0973072__INCLUDED_)
#define AFX_ZDLGHTML_H__00C54337_702E_11D2_ABF7_CCFAF0973072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZWEBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 26 janvier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZHtmlDialog
{
public:

	ZHtmlDialog( LPCTSTR lpszURL, BOOL bRes = FALSE, CWnd* pParent = NULL );
	ZHtmlDialog( UINT nResID, CWnd* pParent = NULL );
	ZHtmlDialog();

	virtual ~ZHtmlDialog();

public:

	void SetDlgOptions( LPCTSTR lpszOptions );
	void SetSize( int x, int y );
	void SetParam( LPCTSTR lpszArgs );
	void SetParam( VARIANT* pvarArgs );

	LPCVARIANT GetReturnVariant();

	CString GetReturnString();

	virtual int DoModal();

private:

	inline void ResourceToURL( LPCTSTR lpszURL );
	void CommonConstruct();

protected:

	HWND		m_hWndParent;
	CString		m_strOptions;
	COleVariant	m_varArgs;
	COleVariant	m_varReturn;
	CString		m_strURL;
	HINSTANCE	m_hInstMSHTML;
};

#endif // !defined(AFX_ZDLGHTML_H__00C54337_702E_11D2_ABF7_CCFAF0973072__INCLUDED_)