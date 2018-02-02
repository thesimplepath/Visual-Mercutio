// ZAModelGlobal.cpp: implementation of the ZAModelGlobal class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZAModelGlobal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 25 décembre 2006 - Ajout des décorations unicode _T(), nettoyage du code inutile. (En commentaires)

ZBPropertyAttributesSet	ZAModelGlobal::m_Set;
CString					ZAModelGlobal::m_Filename;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZAModelGlobal::ZAModelGlobal()
{
}

ZAModelGlobal::~ZAModelGlobal()
{
	// JMR-MODIF - Le 31 août 2005 - Destructeur remplaçé par la fonction Release.
	Release();
}

// JMR-MODIF - Le 31 août 2005 - Ajout de la fonction Release, pour permettre le nettoyage des ressources.
void ZAModelGlobal::Release()
{
	int Count = m_Set.GetSize();

	for ( int i = 0; i < Count; ++i )
	{
		ZBPropertyAttributes* pPropAtt = m_Set.GetAt( i );

		if ( pPropAtt )
		{
			delete pPropAtt;
		}
	}

	m_Set.RemoveAll();

	m_Filename.Empty();
}

bool ZAModelGlobal::SaveStateGlobalPropertyAttributes( const CString Filename )
{
	// Run through our sets of global attributes
	int Count = m_Set.GetSize();

	for ( int i = 0; i < Count; ++i )
	{
		ZBPropertyAttributes* pPropAtt = m_Set.GetAt( i );

		if ( pPropAtt )
		{
			pPropAtt->SaveStateToIniFile( m_Filename, i );
		}
	}

	return true;
}

ZBPropertyAttributes& ZAModelGlobal::GetGlobalPropertyAttributes( int ObjectID )
{
	ZBPropertyAttributes* pPropAtt = NULL;

	if ( ObjectID < m_Set.GetSize() && m_Set.GetAt( ObjectID ) != NULL )
	{
		pPropAtt = m_Set.GetAt( ObjectID );
	}
	else
	{
		pPropAtt = new ZBPropertyAttributes;
		ASSERT( pPropAtt );
		pPropAtt->LoadStateFromIniFile( m_Filename, ObjectID );
		m_Set.SetAtGrow( ObjectID, pPropAtt );
	}

	ASSERT( pPropAtt );
	return *pPropAtt;
}
