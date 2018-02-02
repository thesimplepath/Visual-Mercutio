// ZBSmartString.cpp : implementation file
//

#include "stdafx.h"
#include "ZBSmartString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZBSmartString

ZBSmartString::ZBSmartString(UINT nIdText)
{
	m_bCString = true;
	m_pStrText = new CString;

	#ifdef _DEBUG
	if(!m_pStrText->LoadString(nIdText))
		TRACE("\nError loading string %d", nIdText);
	#else
	m_pStrText->LoadString(nIdText);
	#endif
}

void ZBSmartString::SetCString(const CString& strText)
{
	m_bCString = true;
	m_pStrText = new CString(strText);
}

void ZBSmartString::SetLPCTSTR(LPCTSTR pText)
{
	m_bCString = false;
	m_pText = pText;
}

void ZBSmartString::Clear()
{
	if(m_bCString && m_pStrText)
		delete m_pStrText;
	m_pStrText = NULL;
}

ZBSmartString::ZBSmartString(const ZBSmartString& d)
{
	if(d.m_bCString)
		SetCString(*d.m_pStrText);
	else
		SetLPCTSTR(d.m_pText);
}

ZBSmartString::~ZBSmartString()
{
	if(m_bCString)
		delete m_pStrText;
}

ZBSmartString& ZBSmartString::operator=(const ZBSmartString& data)
{
	Clear();

	if(data.m_bCString)
		SetCString(*data.m_pStrText);
	else
		SetLPCTSTR(data.m_pText);

	return *this;
}

/*
ZBSmartString& ZBSmartString::operator=(const CString& strText)
{
	Clear();
	SetCString(strText);

	return *this;
}
*/

ZBSmartString& ZBSmartString::operator=(LPCTSTR pData)
{
	Clear();
	SetLPCTSTR(pData);

	return *this;
}

ZBSmartString::operator LPCTSTR() const
{
	return m_bCString ? m_pStrText->operator LPCTSTR() : m_pText;
}
