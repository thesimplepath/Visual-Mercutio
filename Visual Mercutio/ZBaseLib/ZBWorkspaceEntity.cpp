// ZBWorkspaceEntity.cpp: implementation of the ZBWorkspaceEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBWorkspaceEntity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 18 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL( ZBWorkspaceEntity, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBWorkspaceEntity::ZBWorkspaceEntity( const CString Name /*= ""*/, ZBWorkspaceEntity* pParent /*= NULL*/ )
    : m_EntityName    ( Name ),
      m_pParent        ( pParent )
{
}

ZBWorkspaceEntity::~ZBWorkspaceEntity()
{
}

/////////////////////////////////////////////////////////////////////////////
// ZBWorkspaceEntity diagnostics
#ifdef _DEBUG
void ZBWorkspaceEntity::AssertValid() const
{
    CObject::AssertValid();
}

void ZBWorkspaceEntity::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBWorkspaceEntity serialization

void ZBWorkspaceEntity::Serialize ( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        // Write the elements
        ar << m_EntityName;
        ar << m_EntityDescription;
    }
    else
    {
        // Read the elements
        ar >> m_EntityName;
        ar >> m_EntityDescription;
    }
}
