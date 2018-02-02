// ZWebBrowser.h: interface for the ZWebBrowser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZWEBBROWSER_H__A90C7280_27E7_428A_BA4C_ED1969E92153__INCLUDED_)
#define AFX_ZWEBBROWSER_H__A90C7280_27E7_428A_BA4C_ED1969E92153__INCLUDED_

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

#include "webbrowser.h"

#ifdef _ZWEBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 26 janvier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commenatires)

class AFX_EXT_CLASS ZWebBrowser : public CWebBrowser
{
public:

	ZWebBrowser();
	virtual ~ZWebBrowser();

	void SetOptions( LPCTSTR lpszOptions );

	void SetParam( LPCTSTR lpszArgs );
	void SetParam( VARIANT* pvarArgs );

	void SetURL( UINT nResID, HINSTANCE hInstance = NULL );
	void SetURL( LPCTSTR lpszURL, BOOL bRes, HINSTANCE hInstance = NULL );
	void SetURL( UINT nResID, LPCTSTR lpszParam, HINSTANCE hInstance = NULL );
	void SetURL( LPCTSTR lpszURL, BOOL bRes, LPCTSTR lpszParam, HINSTANCE hInstance = NULL );

	void Navigate();
	void Navigate( const CString strURL );
	void Navigate( UINT nResID, HINSTANCE hInstance = NULL );
	void Navigate( LPCTSTR lpszURL, BOOL bRes, HINSTANCE hInstance = NULL );
	void Navigate( UINT nResID, LPCTSTR lpszParam, HINSTANCE hInstance = NULL );
	void Navigate( LPCTSTR lpszURL, BOOL bRes, LPCTSTR lpszParam, HINSTANCE hInstance = NULL );

	// Helper function
	static CString BuildResourceToURL(LPCTSTR lpszURL, HINSTANCE hInstance = NULL );

private:

	void ResourceToURL( LPCTSTR lpszURL, HINSTANCE hInstance = NULL );

private:
	CString			m_strURL;
	CString			m_strOptions;
	COleVariant		m_varArgs;
	COleVariant		m_varReturn;
};

#endif // !defined(AFX_ZWEBBROWSER_H__A90C7280_27E7_428A_BA4C_ED1969E92153__INCLUDED_)