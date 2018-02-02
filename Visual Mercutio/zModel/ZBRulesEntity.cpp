// ******************************************************************************************************************
// *										Classe ZBRulesEntity													*
// ******************************************************************************************************************
// * JMR-MODIF - Le 14 novembre 2006 - Ajout de la classe ZBRulesEntity.											*
// ******************************************************************************************************************
// * Cette classe représente une entité de type règle. Une entité peut être considérée comme un élément du document.*
// ******************************************************************************************************************

#include "stdafx.h"
#include "ZBRulesEntity.h"

// BaseDoc
#include "zBaseLib\BaseDoc.h"
#include "zBaseLib\ZUGUID.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL( ZBRulesEntity, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBRulesEntity::ZBRulesEntity( const CString		Name		/*= _T( "" )*/, 
							  const CString		Description	/*= _T( "" )*/, 
							  ZBRulesEntity*	pParent		/*= NULL*/ )
	: m_EntityName			( Name ),
	  m_EntityDescription	( Description ),
	  m_pParent				( pParent )
{
	CreateGUID();
}

ZBRulesEntity::~ZBRulesEntity()
{
}

void ZBRulesEntity::CreateGUID()
{
	m_GUID = ZUGUID::CreateNewGUID();
}

/////////////////////////////////////////////////////////////////////////////
// ZBRulesEntity diagnostics
#ifdef _DEBUG
void ZBRulesEntity::AssertValid() const
{
	CObject::AssertValid();
}

void ZBRulesEntity::Dump( CDumpContext& dc ) const
{
	CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBRulesEntity serialization

void ZBRulesEntity::Serialize( CArchive& ar )
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
		ar >> m_GUID;
		ar >> m_EntityName;
		ar >> m_EntityDescription;
	}
}
