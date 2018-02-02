// ******************************************************************************************************************
// *											 Classe ZBPrestationsEntity											*
// ******************************************************************************************************************
// * JMR-MODIF - Le 7 octobre 2005 - Ajout de la classe ZBPrestationsEntity.										*
// ******************************************************************************************************************
// * Cette classe représente une entité de type prestation. Une entité peut être considérée comme un élément du		*
// * document.																										*
// ******************************************************************************************************************

#include "stdafx.h"
#include "ZBPrestationsEntity.h"

// BaseDoc
#include "zBaseLib\BaseDoc.h"
#include "zBaseLib\ZUGUID.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL( ZBPrestationsEntity, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBPrestationsEntity::ZBPrestationsEntity( const CString			Name		/*= _T( "" )*/, 
										  const CString			Description	/*= _T( "" )*/, 
										  ZBPrestationsEntity*	pParent		/*= NULL*/ )
	: m_EntityName			( Name ),
	  m_EntityDescription	( Description ),
	  m_pParent				( pParent )
{
	CreateGUID();
}

ZBPrestationsEntity::~ZBPrestationsEntity()
{
}

void ZBPrestationsEntity::CreateGUID()
{
	m_GUID = ZUGUID::CreateNewGUID();
}

/////////////////////////////////////////////////////////////////////////////
// ZBPrestationsEntity diagnostics
#ifdef _DEBUG
void ZBPrestationsEntity::AssertValid() const
{
	CObject::AssertValid();
}

void ZBPrestationsEntity::Dump( CDumpContext& dc ) const
{
	CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBPrestationsEntity serialization

void ZBPrestationsEntity::Serialize( CArchive& ar )
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
