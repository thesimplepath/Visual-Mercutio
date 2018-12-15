// ZUExtractModelAttributes.cpp: implementation of the ZUExtractModelAttributes class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProcGraphModelMdl.h"
#include "ZUExtractModelAttributes.h"

#include "ZBSymbol.h"
#include "ZBLinkSymbol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 1er mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUExtractModelAttributes::ZUExtractModelAttributes( ZDProcessGraphModelMdl*    pModel    /*= NULL*/,
                                                    void*                    pClass    /*= NULL*/ )
    : ZUModelNavigation( pModel, pClass )
{
}

ZUExtractModelAttributes::~ZUExtractModelAttributes()
{
}

bool ZUExtractModelAttributes::OnStart()
{
    m_pPropertySet = static_cast<ZBPropertySet*>( m_pClass );

    if ( !m_pPropertySet )
    {
        return false;
    }

    // Reset the array of ids
    memset( m_IDArray, 0, sizeof( m_IDArray ) );

    // Nothing more to do
    return true;
}

bool ZUExtractModelAttributes::OnFinish()
{
    return true;
}

bool ZUExtractModelAttributes::OnSymbol( ZBSymbol* pSymbol )
{
    ZBPropertySet PropSet;

    // Retrieve the property set from object
    pSymbol->FillProperties( PropSet, true );

    // Add the attributes to the pPublishAttribDef class
    ProcessAttrib( PropSet );

    // Remove all properties
    ZBPropertyIterator i( &PropSet );
    ZBProperty* pProp;

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        delete pProp;
    }

    PropSet.RemoveAll();

    return true;
}

bool ZUExtractModelAttributes::OnLink( ZBLinkSymbol* pLink )
{
    ZBPropertySet PropSet;

    // Retrieve the property set from object
    pLink->FillProperties( PropSet, true );

    // Add the attributes to the pPublishAttribDef class
    ProcessAttrib( PropSet );

    // Remove all properties
    ZBPropertyIterator i( &PropSet );
    ZBProperty* pProp;

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        delete pProp;
    }

    PropSet.RemoveAll();

    return true;
}

void ZUExtractModelAttributes::ProcessAttrib( ZBPropertySet& PropSet )
{
    ASSERT( m_pPropertySet );

    // Remove all properties
    ZBPropertyIterator i( &PropSet );
    ZBProperty* pProp;

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        short left    = pProp->GetCategoryID() & 0x0000FFFF;
        short right    = pProp->GetItemID() & 0x0000FFFF;
        int Key        = ( left << 16 ) | right;

        // If the key doesn't exist yet,
        // add it to the final property set
        if ( !KeyExist( Key ) )
        {
            m_pPropertySet->Add( pProp->Dup() );
        }
    }
}

bool ZUExtractModelAttributes::KeyExist( int key )
{
    for ( int i = 0; i < sizeof( m_IDArray ) && m_IDArray[i] != 0; ++i )
    {
        if ( m_IDArray[i] == key )
        {
            return true;
        }
    }

    // doesn't exist

    // Check the array size before inserting the element
    if ( i < sizeof( m_IDArray ) / sizeof( int ) )
    {
        // add it for the next time
        m_IDArray[i] = key;
    }

    return false;
}
