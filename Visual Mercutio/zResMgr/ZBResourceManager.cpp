/////////////////////////////////////////////////////////////////////////////
//@doc ZBResourceManager
//@module ZBResourceManager.cpp | Implementation of the <c ZBResourceManager> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Dom
// <nl>Created: 10/2002
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBResourceManager.h"
#include "ZBModuleVersion.h"

#include "zBaseLib\zDirectory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 28 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (en commentaires)

//////////////////////////////////////////////////////////////////////
// Static variables
ZBResourceInfoSet	ZBResourceManager::m_TableResources;
ZBResourceInfoSet	ZBResourceManager::m_TableResourcesLoaded;
Language			ZBResourceManager::m_CurrentLanguage		= UnknownLang;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBResourceManager::ZBResourceManager()
{
}

ZBResourceManager::~ZBResourceManager()
{
	// JMR-MODIF - Le 30 août 2005 - Destructeur statique jamais appelé, remplaçé par la fonction Release.
	Release();
}

// JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release pour permettre le nettoyage des ressources.
void ZBResourceManager::Release()
{
	// Décharge les librairies utilisées pour le language courant.
	Unload();

	// Détruit la table des ressources.
	ZBResourceIterator i( &m_TableResources );

	for ( _ZBResourceInfo* pInfo = i.GetFirst(); pInfo != NULL; pInfo = i.GetNext() )
	{
		if ( pInfo != NULL )
		{
			delete pInfo;
			pInfo = NULL;
		}
	}

	m_TableResources.RemoveAll();
}

// Cette fonction permet d'initialiser la table des ressources.
bool ZBResourceManager::LoadFromDirectory( const CString Dir )
{
	CStringArray FileArray;

	if ( ZDirectory::FindFile( _T( "*.dll" ), Dir, FileArray, false ) <= 0 )
	{
		return true;
	}

	// Run through the file array and process each file
	for ( int i = 0; i < FileArray.GetSize() ;++i )
	{
		HMODULE hModule = LoadLibrary( FileArray.GetAt( i ) );

		ZBModuleVersion ver;

		if ( ver.GetFileVersionInfo( FileArray.GetAt( i ) ) )
		{
			Language lang = UnknownLang;

			switch ( ver.GetLangID() )
			{
				case 0x040C: // French
				{
					lang = FrenchLang;
					break;
				}

				case 0x0409: // English
				{
					lang = EnglishLang;
					break;
				}

				case 0x0407: // German
				{
					lang = GermanLang;
					break;
				}
			}

			// Add the resource dll to the table
			_ZBResourceInfo* pResInfo = new _ZBResourceInfo( FileArray.GetAt( i ), lang );
			m_TableResources.Add( pResInfo );
		}

		if ( hModule )
		{
			FreeLibrary( hModule );
		}
	}

	return true;
}

// Cette fonction permet de charger une nouvelle bibliothèque pour le language.
bool ZBResourceManager::ChangeLanguage( Language Lang )
{
	if ( Lang == m_CurrentLanguage )
	{
		return true;
	}

	// Unload the loaded resource dlls first
	Unload();

	bool Found = false;

	// Run through the set of resource dlls
	ZBResourceIterator i( &m_TableResources );

	for ( _ZBResourceInfo* pInfo = i.GetFirst(); pInfo != NULL; pInfo = i.GetNext() )
	{
		// If the right language
		if ( pInfo->GetLanguage() == Lang )
		{
			// Load the library and keep the module handle 
			// returned by the LoadLibrary function
			pInfo->SetModule( LoadLibrary( pInfo->GetFilename() ) );

			// Add the pointer to the loaded array
			m_TableResourcesLoaded.Add( pInfo );
		}
	}

	m_CurrentLanguage = Lang;

	return true;
}

// Cette fonction permet de décharger la bibliothèque actuellement utilisée pour le language.
void ZBResourceManager::Unload()
{
	// Run through the set of loaded resource
	ZBResourceIterator i( &m_TableResourcesLoaded );

	for ( _ZBResourceInfo* pInfo = i.GetFirst(); pInfo != NULL; pInfo = i.GetNext() )
	{
		if ( pInfo->GetModule() )
		{
			FreeLibrary( pInfo->GetModule() );
		}

		pInfo->SetModule( NULL );
	}

	// Finally remove all element pointers from the table.
	// but not delete the element itself
	m_TableResourcesLoaded.RemoveAll();
}
