// ZBDynamicProperties.cpp: implementation of the ZBDynamicProperties class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBDynamicProperties.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 7 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(ZBDynamicProperties, CObject, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBDynamicProperties::ZBDynamicProperties()
{
}

ZBDynamicProperties::~ZBDynamicProperties()
{
    FreePropertiesSet();
}

ZBDynamicProperties::ZBDynamicProperties( const ZBDynamicProperties& src )
{
    *this = src;
}

ZBDynamicProperties& ZBDynamicProperties::operator=( const ZBDynamicProperties& src )
{
    ZBDynamicPropertiesIterator i(&src.m_Set);

    for ( ZBProperty* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        AddDynamicProperty( pProp->Dup() );
    }

    return *this;
}

ZBDynamicProperties* ZBDynamicProperties::Dup() const
{
    return ( new ZBDynamicProperties( *this ) );
}

void ZBDynamicProperties::FreePropertiesSet()
{
    ZBDynamicPropertiesIterator i( &m_Set );

    for ( ZBProperty* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        delete pProp;
    }

    m_Set.RemoveAll();
}

void ZBDynamicProperties::AddDynamicProperty( ZBProperty* pProperty )
{
    if ( !pProperty )
    {
        return;
    }

    if ( !Exist( pProperty ) )
    {
        m_Set.Add( pProperty );
    }
}

bool ZBDynamicProperties::Exist( ZBProperty* pProperty )
{
    ZBDynamicPropertiesIterator i( &m_Set );

    for ( ZBProperty* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->GetCategoryID() == pProperty->GetCategoryID() && pProp->GetItemID() == pProperty->GetItemID() )
        {
            return true;
        }
    }

    return false;
}

bool ZBDynamicProperties::DeleteProperty( ZBProperty* pProperty )
{
    ZBDynamicPropertiesIterator i( &m_Set );

    for ( ZBProperty* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->GetCategoryID() == pProperty->GetCategoryID() && pProp->GetItemID() == pProperty->GetItemID() )
        {
            delete pProp;
            i.Remove();
            return true;
        }
    }

    return false;
}

bool ZBDynamicProperties::FillProperties( ZBPropertySet&    PropSet,
                                          bool                NumericValue    /*= false*/,
                                          bool                GroupValue        /*= false*/ )
{
    ZBDynamicPropertiesIterator i( &m_Set );

    for ( ZBProperty* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        // Add the properties to the set.
        PropSet.Add( pProp->Dup() );
    }

    return true;
}

bool ZBDynamicProperties::SaveProperties( ZBPropertySet& PropSet )
{
    // Now run through the list of data and fill the property set
    ZBPropertyIterator s( &PropSet );

    for ( ZBProperty* pPropSrc = s.GetFirst(); pPropSrc; pPropSrc = s.GetNext() )
    {
        ZBDynamicPropertiesIterator d( &m_Set );

        for ( ZBProperty* pPropDst = d.GetFirst(); pPropDst; pPropDst = d.GetNext() )
        {        
            if ( pPropSrc->GetCategoryID() == pPropDst->GetCategoryID() &&
                 pPropSrc->GetItemID() == pPropDst->GetItemID() )
            {
                switch ( pPropSrc->GetPTValueType() )
                {
                    case ZBProperty::PT_STRING:
                    {
                        pPropDst->SetValueString( pPropSrc->GetValueString() );
                        break;
                    }

                    case ZBProperty::PT_DOUBLE:
                    {
                        pPropDst->SetValueDouble( pPropSrc->GetValueDouble() );
                        break;
                    }

                    case ZBProperty::PT_FLOAT:
                    {
                        pPropDst->SetValueFloat( pPropSrc->GetValueFloat() );
                        break;
                    }

                    case ZBProperty::PT_DATE:
                    {
                        pPropDst->SetValueDate( pPropSrc->GetValueDate() );
                        break;
                    }

                    case ZBProperty::PT_TIMESPAN:
                    {
                        pPropDst->SetValueTimeSpan( pPropSrc->GetValueTimeSpan() );
                        break;
                    }

                    case ZBProperty::PT_DURATION:
                    {
                        pPropDst->SetValueDuration( pPropSrc->GetValueDuration() );
                        break;
                    }
                }
            }
        }
    }

    return true;
}

bool ZBDynamicProperties::FillProperty( ZBProperty& Property )
{
    return true;
}

bool ZBDynamicProperties::SaveProperty( ZBProperty& Property )
{
    return true;
}

bool ZBDynamicProperties::CheckPropertyValue( ZBProperty& Property, CString& value, ZBPropertySet& Properties )
{
    return true;
}

bool ZBDynamicProperties::ProcessExtendedInput( ZBProperty&        Property,
                                                CString&        value,
                                                ZBPropertySet&    Properties,
                                                bool&            Refresh )
{
    return true;
}

bool ZBDynamicProperties::ProcessMenuCommand( int                MenuCommand,
                                              ZBProperty&        Property,
                                              CString&            value,
                                              ZBPropertySet&    Properties,
                                              bool&                Refresh )
{
    return true;
}

bool ZBDynamicProperties::OnPrePropertyChanged( CString NewValue, ZBProperty& Property, ZBPropertySet& Properties )
{
    return true;
}

bool ZBDynamicProperties::OnPostPropertyChanged( ZBProperty& Property, ZBPropertySet& Properties, bool& Refresh )
{
    return true;
}

bool ZBDynamicProperties::OnDropInternalPropertyItem( ZBProperty&        SrcProperty,
                                                      ZBProperty&        DstProperty,
                                                      bool                Top2Down,
                                                      ZBPropertySet&    Properties )
{
    return true;
}

bool ZBDynamicProperties::CreateSymbolProperties()
{
    return true;
}

void ZBDynamicProperties::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        // JMR-MODIF - Le 7 septembre 2005 - Ajout de la conversion explicite de SEC_INT en int.
        // Serialize the size
        ar << (int)m_Set.GetSize();

        ZBDynamicPropertiesIterator i( &m_Set );

        for ( ZBProperty* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
        {
            ar << pProp;
        }
    }
    else
    {
        int Size;
        ar >> Size;

        ZBProperty* pProp;

        for ( int i = 0; i < Size; ++i )
        {
            ar >> pProp;
            AddDynamicProperty( pProp );
        }
    }
}
