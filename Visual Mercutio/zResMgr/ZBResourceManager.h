/////////////////////////////////////////////////////////////////////////////
//@doc ZBResourceManager
//@module ZBResourceManager.h | Interface of the <c ZBResourceManager> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Dom
// <nl>Created:		 10/2002
// <nl>Description:  ZBResourceManager resource support
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBRESOURCEMANAGER_H__CC419699_D4EE_4511_A8B2_DBF927A86F36__INCLUDED_)
#define AFX_ZBRESOURCEMANAGER_H__CC419699_D4EE_4511_A8B2_DBF927A86F36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zLanguageDef.h"

/////////////////////////////////////////////////////////////////////////////
// Forward class declaration

#ifdef _ZRESMGREXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 28 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (en commentaires)

///////////////////////////////////////////////////////////////////////////
// _ZBResourceInfo class

class _ZBResourceInfo
{
public:

	_ZBResourceInfo( const CString Filename = _T( "" ), Language Lang = UnknownLang )
	{
		m_Filename	= Filename;
		m_Language	= Lang;
		m_Module	= NULL;
	};

	virtual ~_ZBResourceInfo()
	{
	};

	CString GetFilename() const;
	void	SetFilename( CString value );

	Language GetLanguage() const;
	void	 SetLanguage( Language value );

	HMODULE	GetModule() const;
	void	SetModule( HMODULE	value );

private:

	CString		m_Filename;
	Language	m_Language;
	HMODULE		m_Module;
};

inline CString _ZBResourceInfo::GetFilename() const 
{
	return m_Filename;
}

inline void _ZBResourceInfo::SetFilename( CString value )
{
	m_Filename = value;
}

inline Language _ZBResourceInfo::GetLanguage() const 
{
	return m_Language;
}

inline void _ZBResourceInfo::SetLanguage( Language value )
{
	m_Language = value;
}

inline HMODULE _ZBResourceInfo::GetModule() const 
{
	return m_Module;
}

inline void _ZBResourceInfo::SetModule( HMODULE value )
{
	m_Module = value;
}

/////////////////////////////////////////////////////////////////////////////
// scope symbols in stingray foundation library
using namespace sfl;

///////////////////////////////////////////////////////////////////////////
// Collection definitions

//@type ZBResourceInfoSet | An array of _ZBResourceInfo pointers.
//@iex typedef CCArray_T<_ZBResourceInfo*,_ZBResourceInfo*> ZBResourceInfoSet;
typedef CCArray_T<_ZBResourceInfo*, _ZBResourceInfo*> ZBResourceInfoSet;

//@type ZBResourceIterator | An iterator for ZBResourceInfoSet collections.
//@iex typedef Iterator_T<_ZBResourceInfo*> ZBResourceIterator;
typedef Iterator_T<_ZBResourceInfo*> ZBResourceIterator;

///////////////////////////////////////////////////////////////////////////
// ZBResourceManager class

class AFX_EXT_CLASS ZBResourceManager
{
public:

	ZBResourceManager();
	virtual ~ZBResourceManager();

	// JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release.
	static void Release();

	static bool LoadFromDirectory( const CString Dir );
	static bool ChangeLanguage( Language Lang );

private:

	static void Unload();

private:

	static ZBResourceInfoSet	m_TableResources;
	static ZBResourceInfoSet	m_TableResourcesLoaded;
	static Language				m_CurrentLanguage;
};

#endif // !defined(AFX_ZBRESOURCEMANAGER_H__CC419699_D4EE_4511_A8B2_DBF927A86F36__INCLUDED_)