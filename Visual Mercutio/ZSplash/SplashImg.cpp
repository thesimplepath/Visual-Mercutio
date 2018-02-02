// SplashImg.cpp : implementation file
//

#include "stdafx.h"
#include "SplashImg.h"

#include "ZSplashRes.h"
#include "SplashDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZSplashImage

ZSplashImage::ZSplashImage(UINT nResID /*= 0*/, const CString Info /*= ""*/, CWnd* pParentWnd /*= NULL*/)
: m_BitmapResID(nResID), m_Info(Info), m_pParentWnd(pParentWnd)
{
}

ZSplashImage::ZSplashImage(LPCTSTR szFilename, const CString Info /*= ""*/, CWnd* pParentWnd /*= NULL*/)
: m_BitmapFilename(szFilename), m_BitmapResID(0), m_Info(Info), m_pParentWnd(pParentWnd)
{
}

ZSplashImage::~ZSplashImage()
{
}


bool ZSplashImage::Display( LPCTSTR szFilename, const CString Info /*= ""*/, CWnd* pParentWnd /*= NULL*/ ) 
{
	m_pParentWnd = pParentWnd;
	m_BitmapFilename = szFilename;
	m_Info = Info;

	return ProcessDisplay();
}

bool ZSplashImage::Display( UINT nResID, const CString Info /*= ""*/, CWnd* pParentWnd /*= NULL*/ ) 
{
	m_pParentWnd = pParentWnd;
	m_BitmapResID = nResID;
	m_Info = Info;

	return ProcessDisplay();
}

bool ZSplashImage::Display(const CString Info /*= ""*/)
{
	// Check if the constructor has been called correctly
	if (m_BitmapFilename.IsEmpty() && m_BitmapResID == 0)
		return false;

	// If the info is not empty, assigns the its new value
	if (!Info.IsEmpty())
		m_Info = Info;

	return ProcessDisplay();
}


bool ZSplashImage::ProcessDisplay()
{
	ZSplashDialog*	pSplash;
	if (m_BitmapFilename.IsEmpty())
		pSplash = new ZSplashDialog( m_BitmapResID, m_Info, m_pParentWnd );
	else
		pSplash = new ZSplashDialog( m_BitmapFilename, m_Info, m_pParentWnd );

	if (!pSplash)
		return false;

	pSplash->DoModal();
	delete pSplash;
	return true;
}

