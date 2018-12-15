// ZBUserEntity.cpp: implementation of the ZBUserEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBUserEntity.h"

// BaseDoc
#include "zBaseLib\BaseDoc.h"

#include "zBaseLib\ZUGUID.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 27 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (en commentaires)

IMPLEMENT_SERIAL( ZBUserEntity, CObject, def_Version )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBUserEntity::ZBUserEntity( const CString    Name        /*= ""*/,
                            const CString    Description    /*= ""*/,
                            const float        Cost        /*= 0*/,
                            ZBUserEntity*    pParent        /*= NULL*/ )
    : m_EntityName            ( Name ),
      m_EntityDescription    ( Description ),
      m_EntityCost            ( Cost ),
      m_pParent                ( pParent )
{
    CreateGUID();
}

ZBUserEntity::~ZBUserEntity()
{
}

ZBUserEntity::ZBUserEntity( const ZBUserEntity& src )
{
    *this = src;
}

ZBUserEntity& ZBUserEntity::operator=( const ZBUserEntity& src )
{
    m_GUID                = src.m_GUID;
    m_EntityName        = src.m_EntityName;
    m_EntityDescription    = src.m_EntityDescription;
    m_EntityCost        = src.m_EntityCost;

    return *this;
}

ZBUserEntity* ZBUserEntity::Clone() const
{
    return ( new ZBUserEntity( *this ) );
}

void ZBUserEntity::CreateGUID()
{
    m_GUID = ZUGUID::CreateNewGUID();
}

/////////////////////////////////////////////////////////////////////////////
// ZBUserEntity diagnostics
#ifdef _DEBUG
void ZBUserEntity::AssertValid() const
{
    CObject::AssertValid();
}

void ZBUserEntity::Dump( CDumpContext& dc ) const
{
    CObject::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBUserEntity serialization

void ZBUserEntity::Serialize ( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        // Write the elements
        ar << m_GUID;
        ar << m_EntityName;
        ar << m_EntityDescription;
        ar << m_EntityCost;
    }
    else
    {
        // Read the elements
        CString s;
        ar >> s;

        if ( ar.m_pDocument &&
             dynamic_cast<ZDBaseDocument*>(ar.m_pDocument)->GetDocumentStamp().GetInternalVersion() >= 19 )
        {
            m_GUID = s;
            ar >> m_EntityName;
        }
        else
        {
            CreateGUID();
            m_EntityName = s;
        }

        ar >> m_EntityDescription;
        ar >> m_EntityCost;
    }
}
