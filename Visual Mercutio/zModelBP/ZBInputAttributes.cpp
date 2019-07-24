// ZBInputAttributes.cpp: implementation of the ZBInputAttribute class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBInputAttributes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// ZBInputAttribute class implementation

IMPLEMENT_SERIAL(ZBInputAttribute, CObject, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBInputAttribute::ZBInputAttribute()
{
}

ZBInputAttribute::~ZBInputAttribute()
{
}

ZBInputAttribute::ZBInputAttribute( const ZBInputAttribute& src )
{
    *this = src;
}

ZBInputAttribute& ZBInputAttribute::operator=( const ZBInputAttribute& src )
{
    m_CategoryID    = src.m_CategoryID;
    m_ItemID        = src.m_ItemID;
    m_SymbolRef        = src.m_SymbolRef;
    m_DefaultValue    = src.m_DefaultValue;
    m_Flag            = src.m_Flag;

    return *this;
}

ZBInputAttribute* ZBInputAttribute::Dup() const
{
    return ( new ZBInputAttribute( *this ) );
}

void ZBInputAttribute::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        TRACE( "ZBInputAttribute::Serialize : Start Save\n" );

        ar << m_CategoryID;
        ar << m_ItemID;
        ar << m_SymbolRef;
        ar << m_DefaultValue;
        ar << m_Flag;

        TRACE( "ZBInputAttribute::Serialize : End Save\n" );
    }
    else
    {
        TRACE( "ZBInputAttribute::Serialize : Start Read\n" );

        ar >> m_CategoryID;
        ar >> m_ItemID;
        ar >> m_SymbolRef;
        ar >> m_DefaultValue;
        ar >> m_Flag;
    
        TRACE( "ZBInputAttribute::Serialize : End Read\n" );
    }
}

//////////////////////////////////////////////////////////////////////
// ZBInputAttributeManager class implementation

IMPLEMENT_SERIAL(ZBInputAttributeManager, CObject, g_DefVersion)
  
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBInputAttributeManager::ZBInputAttributeManager()
{
}

ZBInputAttributeManager::~ZBInputAttributeManager()
{
    DeleteAllInputAttributes();
}

ZBInputAttributeManager::ZBInputAttributeManager( const ZBInputAttributeManager& src )
{
    *this = src;
}

ZBInputAttributeManager& ZBInputAttributeManager::operator=( const ZBInputAttributeManager& src )
{
    ZBInputAttributeIterator i( &src.m_Set );

    for ( ZBInputAttribute* pInputAttrib = i.GetFirst(); pInputAttrib; pInputAttrib = i.GetNext() )
    {
        AddInputAttribute( pInputAttrib->Dup() );
    }

    return *this;
}

ZBInputAttributeManager* ZBInputAttributeManager::Dup() const
{
    return ( new ZBInputAttributeManager( *this ) );
}

void ZBInputAttributeManager::DeleteAllInputAttributes()
{
    ZBInputAttributeIterator i( &m_Set );

    for ( ZBInputAttribute* pInputAttrib = i.GetFirst(); pInputAttrib; pInputAttrib = i.GetNext() )
        delete pInputAttrib;

    m_Set.RemoveAll();
}

void ZBInputAttributeManager::AddInputAttribute( ZBInputAttribute* pInputAttribute, bool ReplaceExisting /*= true*/ )
{
    if ( !pInputAttribute )
        return;

    if ( !Exist( pInputAttribute ) )
        m_Set.Add( pInputAttribute );
    else
    if ( ReplaceExisting )
    {
        ReplaceInputAttribute( pInputAttribute );

        ZBInputAttribute* pOldAttribute = pInputAttribute;

        // and don't forget to delete the object,
        // since he is not assigned to our set
        // and set the pointer to the existing object
        pInputAttribute = FindInputAttribute( pInputAttribute->GetCategoryID(),
                                              pInputAttribute->GetItemID(),
                                              pInputAttribute->GetSymbolRef() );

        delete pOldAttribute;
    }
}

bool ZBInputAttributeManager::DeleteInputAttribute( ZBInputAttribute* pInputAttribute )
{
    ZBInputAttributeIterator i( &m_Set );

    for ( ZBInputAttribute* pInputAttrib = i.GetFirst(); pInputAttrib; pInputAttrib = i.GetNext() )
    {
        if ( pInputAttrib == pInputAttribute )
        {
            delete pInputAttrib;
            i.Remove();
            return true;
        }
    }

    return false;
}

ZBInputAttribute* ZBInputAttributeManager::FindInputAttribute( int CategoryID, int ItemID, int SymbolRef )
{
    ZBInputAttributeIterator i( &m_Set );

    for ( ZBInputAttribute* pInputAttrib = i.GetFirst(); pInputAttrib; pInputAttrib = i.GetNext() )
    {
        if ( pInputAttrib->GetCategoryID() == CategoryID &&
             pInputAttrib->GetItemID() == ItemID &&
             pInputAttrib->GetSymbolRef() == SymbolRef )
            return pInputAttrib;
    }

    return NULL;
}

bool ZBInputAttributeManager::Exist( ZBInputAttribute* pInputAttribute )
{
    if ( !pInputAttribute )
        return false;

    return ( FindInputAttribute( pInputAttribute->GetCategoryID(),
                                 pInputAttribute->GetItemID(),
                                 pInputAttribute->GetSymbolRef()) != NULL ) ? true : false;
}

void ZBInputAttributeManager::ReplaceInputAttribute( ZBInputAttribute* pInputAttribute )
{
    ZBInputAttribute* pAttr = FindInputAttribute( pInputAttribute->GetCategoryID(),
                                                  pInputAttribute->GetItemID(),
                                                  pInputAttribute->GetSymbolRef() );

    if ( pAttr )
    {
        // Use assignment operator
        *pAttr = *pInputAttribute;
    }
}

void ZBInputAttributeManager::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        TRACE( "ZBInputAttributeManager::Serialize : Start Save\n" );

        // JMR-MODIF - Le 7 septembre 2005 - Ajout de la conversion explicite de SEC_INT en int.
        // Serialize the size
        ar << (int)m_Set.GetSize();

        ZBInputAttributeIterator i( &m_Set );

        for ( ZBInputAttribute* pInputAttrib = i.GetFirst(); pInputAttrib; pInputAttrib = i.GetNext() )
        {        
            ar << pInputAttrib;
        }

        TRACE( "ZBInputAttributeManager::Serialize : End Save\n" );
    }
    else
    {
        TRACE( "ZBInputAttributeManager::Serialize : Start Read\n" );

        int Size;
        ar >> Size;

        ZBInputAttribute* pInputAttrib;
        for ( int i = 0; i < (int)Size; ++i )
        {
            ar >> pInputAttrib;
            AddInputAttribute( pInputAttrib );
        }

        TRACE( "ZBInputAttributeManager::Serialize : End Read\n" );
    }
}
