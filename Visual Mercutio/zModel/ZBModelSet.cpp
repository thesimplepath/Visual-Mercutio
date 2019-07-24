// ZBModelSet.cpp: implementation of the ZBModelSet class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBModelSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 28 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(ZBModelSet, CObject, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBModelSet::ZBModelSet()
{
}

ZBModelSet::~ZBModelSet()
{
}

ZBModelSet* ZBModelSet::Clone()
{
    ZBModelSet* pNewSet = new ZBModelSet;

    for ( size_t i = 0; i < GetModelCount(); ++i )
    {
        ZDProcessGraphModelMdl* pMdl = GetModelAt( i );

        if ( pMdl )
        {
            pNewSet->AddModel( pMdl );
        }
    }

    return pNewSet;
}

ZDProcessGraphModelMdl* ZBModelSet::GetModelAt( size_t Index )
{
    if ( Index < GetModelCount() )
    {
        return (ZDProcessGraphModelMdl*)m_Set.GetAt( Index );
    }

    return NULL;
}

bool ZBModelSet::AddModel( ZDProcessGraphModelMdl* pModel )
{
    size_t PreviousCount = GetModelCount();
    m_Set.Add( pModel );

    return GetModelCount() > PreviousCount;
}

void ZBModelSet::RemoveAllModel()
{
    m_Set.RemoveAll();
}

void ZBModelSet::DeleteAllModel()
{
    for ( size_t i = 0; i < GetModelCount(); ++i )
    {
        ZDProcessGraphModelMdl* pMdl = GetModelAt( i );

        if ( pMdl )
        {
            delete pMdl;
        }
    }

    m_Set.RemoveAll();
}

bool ZBModelSet::RemoveModelAt( size_t Index )
{
    if ( Index < GetModelCount() )
    {
        m_Set.RemoveAt( Index );
        return true;
    }

    return false;
}

bool ZBModelSet::RemoveModel( ZDProcessGraphModelMdl* pModel )
{
    for ( size_t i = 0; i < GetModelCount(); ++i )
    {
        ZDProcessGraphModelMdl* pMdl = GetModelAt( i );

        if ( pMdl == pModel )
        {
            RemoveModelAt( i );
            return true;
        }
    }

    return false;
}

ZDProcessGraphModelMdl* ZBModelSet::FindModel( const CString Name )
{
    for ( size_t i = 0; i < GetModelCount(); ++i )
    {
        ZDProcessGraphModelMdl* pMdl = GetModelAt( i );

        if ( pMdl->GetModelName() == Name )
        {
            return pMdl;
        }
    }

    return NULL;
}

int ZBModelSet::FindModelIndex( ZDProcessGraphModelMdl* pModel )
{
    for ( size_t i = 0; i < GetModelCount(); ++i )
    {
        ZDProcessGraphModelMdl*    pMdl = GetModelAt( i );

        if ( pMdl == pModel )
        {
            return i;
        }
    }

    return -1;
}

// Serializes the set
void ZBModelSet::Serialize( CArchive& ar )
{
    m_Set.Serialize( ar );
}
