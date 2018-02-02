// ZBSystemEntity.cpp: implementation of the ZBSystemEntity class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBSystemEntity.h"

// BaseDoc
#include "zBaseLib\BaseDoc.h"
#include "zBaseLib\ZUGUID.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 10 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZBSystemEntity, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBSystemEntity::ZBSystemEntity( const CString	Name		/*= _T( "" )*/, 
								const CString	Description	/*= _T( "" )*/, 
								ZBSystemEntity*	pParent		/*= NULL*/ )
	: m_EntityName			( Name ),
	  m_EntityDescription	( Description ),
	  m_pParent				( pParent )
{
	CreateGUID();
}

ZBSystemEntity::~ZBSystemEntity()
{
}

void ZBSystemEntity::CreateGUID()
{
	m_GUID = ZUGUID::CreateNewGUID();
}

/////////////////////////////////////////////////////////////////////////////
// ZBSystemEntity diagnostics
#ifdef _DEBUG
void ZBSystemEntity::AssertValid() const
{
	CObject::AssertValid();
}

void ZBSystemEntity::Dump( CDumpContext& dc ) const
{
	CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBSystemEntity serialization

void ZBSystemEntity::Serialize ( CArchive& ar )
{
	if ( ar.IsStoring() )
	{
		// Write the elements
		ar << m_GUID;
		ar << m_EntityName;
		ar << m_EntityDescription;
	}
	else
	{
		// Read the elements
		// JMR-MODIF - Le 2 septembre 2005 - La variable locale s ne semble pas être utilisée.
//		CString s;
		ar >> m_GUID;
		ar >> m_EntityName;
		ar >> m_EntityDescription;
	}
}
