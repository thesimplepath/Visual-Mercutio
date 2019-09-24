#include <StdAfx.h>

// ZBPropertyAttributes
#include "ZBPropertyAttributes.h"

// ZBTokenizer
#include "zBaseLib\ZBTokenizer.h"

// ZUStringFormater
#include "zBaseLib\ZUStringFormater.h"

// ZUSystemOption
#include "zBaseLib\ZUSystemOption.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 2 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// constant definition
const CString _PropertyAttributeStateSectionName    = _T( "_PropertyDefaultAttributeSaveState" );
const CString _PropertyAttributeStateEntityName        = _T( "_PropertyDefaultAttributeState" );

_ZBPropertyAttribute::_ZBPropertyAttribute( int CategoryID /*= -1*/, int ItemID /*= -1*/ )
{
    m_CategoryID    = CategoryID;
    m_ItemID        = ItemID;
}

_ZBPropertyAttribute::_ZBPropertyAttribute( _ZBPropertyAttribute& src )
{
    *this = src;
}

const _ZBPropertyAttribute & _ZBPropertyAttribute::operator= ( const _ZBPropertyAttribute &right )
{
    m_CategoryID    = right.m_CategoryID;
    m_ItemID        = right.m_ItemID;

    return *this;
}

_ZBPropertyAttribute* _ZBPropertyAttribute::Clone()
{
    return new _ZBPropertyAttribute( *this );
}

CArchive& operator >> ( CArchive& ar, _ZBPropertyAttribute& src )
{
    ar >> src.m_CategoryID;
    ar >> src.m_ItemID;

    return ar;
}

CArchive& operator << ( CArchive& ar, const _ZBPropertyAttribute& src )
{
    ar << src.m_CategoryID;
    ar << src.m_ItemID;

    return ar;
}

// Class ZBPropertyAttributes 

ZBPropertyAttributes::ZBPropertyAttributes()
    : m_DisplayTitleText( true )
{
}

ZBPropertyAttributes::~ZBPropertyAttributes()
{
    RemoveAllAttributes();
}

ZBPropertyAttributes::ZBPropertyAttributes( ZBPropertyAttributes& src )
{
    *this = src;
}

const ZBPropertyAttributes & ZBPropertyAttributes::operator= ( const ZBPropertyAttributes &right )
{
    m_DisplayTitleText = right.m_DisplayTitleText;

    // Remove all existing attributes first.
    RemoveAllAttributes();

    // Copy all attribute elements
    _ZBPropertyAttributeIterator i( &right.GetAttributeSetConst() );

    for ( _ZBPropertyAttribute* pAtt = i.GetFirst(); pAtt != NULL; pAtt = i.GetNext() )
    {
        AddAttribute( pAtt->Clone() );
    }

    return *this;
}

ZBPropertyAttributes* ZBPropertyAttributes::Clone()
{
    return new ZBPropertyAttributes( *this );
}

void ZBPropertyAttributes::RemoveAllAttributes()
{
    _ZBPropertyAttributeIterator i( &m_AttributeSet );

    for ( _ZBPropertyAttribute* pAtt = i.GetFirst(); pAtt != NULL; pAtt = i.GetNext() )
    {
        delete pAtt;
    }

    m_AttributeSet.RemoveAll();
}

_ZBPropertyAttribute* ZBPropertyAttributes::FindAttribute( int CategoryID, int ItemID )
{
    _ZBPropertyAttributeIterator i( &m_AttributeSet );

    for ( _ZBPropertyAttribute* pAtt = i.GetFirst(); pAtt != NULL; pAtt = i.GetNext() )
    {
        if ( pAtt->GetCategoryID() == CategoryID && pAtt->GetItemID() == ItemID )
        {
            return pAtt;
        }
    }

    return NULL;
}

void ZBPropertyAttributes::AddAttribute( _ZBPropertyAttribute* pAttribute )
{
    if ( pAttribute )
    {
        if ( !FindAttribute( pAttribute->GetCategoryID(), pAttribute->GetItemID() ) )
        {
            m_AttributeSet.Add( pAttribute );
        }
        else
        {
            // Otherwise, delete the attribute
            delete pAttribute;
        }
    }
}

void ZBPropertyAttributes::AddAttributeAt( size_t Index, _ZBPropertyAttribute* pAttribute )
{
    if ( pAttribute && Index < GetAttributeCount() )
    {
        if ( !FindAttribute( pAttribute->GetCategoryID(), pAttribute->GetItemID() ) )
        {
            m_AttributeSet.InsertAt( Index, pAttribute );
        }
        else
        {
            delete pAttribute;
        }
    }
    else
    {
        AddAttribute( pAttribute );
    }
}

bool ZBPropertyAttributes::DeleteAttributeAt( size_t Index )
{
    _ZBPropertyAttribute* pAtt = GetAttributeAt( Index );

    if ( pAtt )
    {
        delete pAtt;
        m_AttributeSet.RemoveAt( Index );
        return true;
    }

    return false;
}

bool ZBPropertyAttributes::DeleteAttribute( int CategoryID, int ItemID )
{
    _ZBPropertyAttributeIterator i( &m_AttributeSet );

    for ( _ZBPropertyAttribute* pAtt = i.GetFirst(); pAtt != NULL; pAtt = i.GetNext() )
    {
        if ( pAtt->GetCategoryID() == CategoryID && pAtt->GetItemID() == ItemID )
        {
            delete pAtt;
            i.Remove();
            return true;
        }
    }

    return false;
}

void ZBPropertyAttributes::DeleteCategoryAttribute( int CategoryID )
{
    size_t nCount = GetAttributeCount();

    for ( size_t i = 0; i < nCount; ++i )
    {
        _ZBPropertyAttribute* pAtt = GetAttributeAt( i );

        if ( pAtt && pAtt->GetCategoryID() == CategoryID )
        {
            delete pAtt;
            m_AttributeSet.RemoveAt(i);
            --i;;
        }
    }
}

bool ZBPropertyAttributes::Match( ZBPropertySet&    PropSet,
                                  const CString        What,
                                  bool                CaseSensitive /*= false*/,
                                  bool                PartialSearch /*= false*/ )
{
    ZBPropertyIterator i( &PropSet );
    ZBProperty* pProp;

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( !FindAttribute( pProp->GetCategoryID(), pProp->GetItemID() ) )
        {
            continue;
        }

        CString Value;

        // Retreive the formatted value
        switch ( pProp->GetPTValueType() )
        {
            case ZBProperty::PT_DOUBLE:
            {
                Value = ZUStringFormatter::GetFormattedBuffer( pProp->GetValueDouble(), pProp->GetStringFormat() );
                break;
            }

            case ZBProperty::PT_FLOAT:
            {
                Value = ZUStringFormatter::GetFormattedBuffer( pProp->GetValueFloat(), pProp->GetStringFormat() );
                break;
            }

            case ZBProperty::PT_DATE:
            {
                // RS-MODIF 15.08.05 cast implicite pour obtenir le bon lien objet
                //Value = ZUStringFormatter::GetFormattedBuffer( pProp->GetValueDate(), pProp->GetStringFormat() );
                Value = ZUStringFormatter::GetFormattedBuffer( (PSS_Date&)pProp->GetValueDate(),
                                                               pProp->GetStringFormat() );
                break;
            }

            case ZBProperty::PT_TIMESPAN:
            {
                // RS-MODIF 15.08.05 cast implicite pour obtenir le bon lien objet
                //Value = ZUStringFormatter::GetFormattedBuffer( pProp->GetValueTimeSpan(), pProp->GetStringFormat() );
                Value = ZUStringFormatter::GetFormattedBuffer( (ZBTimeSpan&)pProp->GetValueTimeSpan(),
                                                               pProp->GetStringFormat() );
                break;
            }

            case ZBProperty::PT_DURATION:
            {
                // RS-MODIF 15.08.05 cast implicite pour obtenir le bon lien objet
                //Value = ZUStringFormatter::GetFormattedBuffer( pProp->GetValueDuration(), pProp->GetStringFormat() );
                Value = ZUStringFormatter::GetFormattedBuffer( (PSS_Duration&)pProp->GetValueDuration(),
                                                               pProp->GetStringFormat() );
                break;
            }

            case ZBProperty::PT_STRING:
            {
                Value = pProp->GetValueString();
                break;
            }

            default:
                break;
        }

        if ( Value.IsEmpty() )
        {
            continue;
        }

        // Now check if the value string match with the what string
        if ( PartialSearch )
        {
            // For non case sensitive search, transform the string to lowercase
            CString LowerWhat = What;
            LowerWhat.MakeLower();

            CString LowerValue = Value;
            LowerValue.MakeLower();

            // In case sensitive, use Find function
            if ( (  CaseSensitive && Value.Find( What ) != -1 ) ||
                 ( !CaseSensitive && LowerValue.Find( LowerWhat ) != -1 ) )
            {
                return true;
            }
        }
        else
        {
            if ( (  CaseSensitive && What == Value ) ||
                 ( !CaseSensitive && Value.CompareNoCase( What ) == 0 ) )
            {
                return true;
            }
        }
    }

    // Does not match
    return false;
}

CString ZBPropertyAttributes::GetString( ZBPropertySet* pPropSet, bool KeepOnlyNotEmpty /*= true*/ )
{
    if ( !pPropSet )
    {
        return _T( "" );
    }

    ZBTokenizer token( '\n' );

    ZBPropertyIterator i(pPropSet);
    ZBProperty* pProp;

    for ( pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( !FindAttribute( pProp->GetCategoryID(), pProp->GetItemID() ) )
        {
            continue;
        }

        CString Value;
        CString Format;

        if ( GetDisplayTitleText() )
        {
            Format = pProp->GetLabel();
            Format += _T( ": " );
        }

        // Retreive the formatted value
        switch ( pProp->GetPTValueType() )
        {
            case ZBProperty::PT_DOUBLE:
            {
                Value += ZUStringFormatter::GetFormattedBuffer( pProp->GetValueDouble(), pProp->GetStringFormat() );
                break;
            }

            case ZBProperty::PT_FLOAT:
            {
                Value += ZUStringFormatter::GetFormattedBuffer( pProp->GetValueFloat(), pProp->GetStringFormat() );
                break;
            }

            case ZBProperty::PT_DATE:
            {
                // RS-MODIF 15.08.05 cast implicite pour obtenir le bon lien objet
                //Value += ZUStringFormatter::GetFormattedBuffer( pProp->GetValueDate(), pProp->GetStringFormat() );
                Value += ZUStringFormatter::GetFormattedBuffer( (PSS_Date&)pProp->GetValueDate(),
                                                                pProp->GetStringFormat() );
                break;
            }

            case ZBProperty::PT_TIMESPAN:
            {
                // RS-MODIF 15.08.05 cast implicite pour obtenir le bon lien objet
                //Value += ZUStringFormatter::GetFormattedBuffer( pProp->GetValueTimeSpan(), pProp->GetStringFormat() );
                Value += ZUStringFormatter::GetFormattedBuffer( (ZBTimeSpan&)pProp->GetValueTimeSpan(),
                                                                pProp->GetStringFormat() );
                break;
            }

            case ZBProperty::PT_DURATION:
            {
                // RS-MODIF 15.08.05 cast implicite pour obtenir le bon lien objet
                //Value += ZUStringFormatter::GetFormattedBuffer( pProp->GetValueDuration(), pProp->GetStringFormat() );
                Value += ZUStringFormatter::GetFormattedBuffer( (PSS_Duration&)pProp->GetValueDuration(),
                                                                pProp->GetStringFormat() );
                break;
            }

            case ZBProperty::PT_STRING:
            {
                Value += pProp->GetValueString();
                break;
            }

            default:
                break;
        }

        if ( Value.IsEmpty() && KeepOnlyNotEmpty )
        {
            continue;
        }

        token.AddToken( Format + Value );
    }

    return token.GetString();
}

CArchive& operator >> ( CArchive& ar, ZBPropertyAttributes& src )
{
    WORD wValue;
    ar >> wValue;
    src.SetDisplayTitleText( ( wValue == 1 ) ? true : false );
    int nCount;
    _ZBPropertyAttribute Attribute;

    ar >> nCount;

    for ( int i=0; i < nCount; i++ )
    {
        ar >> Attribute;
        src.AddAttribute( Attribute.Clone() );
    }

    return ar;
}

CArchive& operator << ( CArchive& ar, const ZBPropertyAttributes& src )
{
    ar << (WORD)src.GetDisplayTitleText();
    ar << (int)src.GetAttributeCount();

    _ZBPropertyAttributeIterator i( &src.GetAttributeSetConst() );

    for ( _ZBPropertyAttribute* pAtt = i.GetFirst(); pAtt != NULL; pAtt = i.GetNext() )
    {
        ar << *pAtt;
    }

    return ar;
}

bool ZBPropertyAttributes::LoadStateFromIniFile( const CString IniFile, int ObjectID )
{
    // First, delete all attributes
    RemoveAllAttributes();

    CString EntityName;
    EntityName.Format( _T( "%s%d" ), (const char*)_PropertyAttributeStateSectionName, ObjectID );

    ZUSystemOption SystemOption( IniFile, EntityName );

    CString KeyName;
    CString Line;
    size_t Idx = 0;

    do
    {
        // Format the key
        KeyName.Format( _T( "%s%d" ), (const char*)_PropertyAttributeStateEntityName, Idx );
        Line = SystemOption.ReadOption( KeyName, _T( "" ) );

        if ( Line.IsEmpty() )
        {
            break;
        }

        ++Idx;

        CString str;
        ZBTokenizer token;

        // Extract the category ID
        str = token.GetFirstToken( Line );

        if ( str.IsEmpty() )
        {
            continue;
        }

        int CategoryID = atoi( (const char*)str );

        // Extract the item ID
        str = token.GetNextToken();

        if ( str.IsEmpty() )
        {
            continue;
        }

        int ItemID = atoi( (const char*)str );

        // If we are here, all objects have been extracted
        // Create the object state
        _ZBPropertyAttribute* pAtt = new _ZBPropertyAttribute( CategoryID, ItemID );

        // Add it to the array of value
        AddAttribute( pAtt );
    }
    while (Idx < 1000000);    // Sets the maximum loop at 1 million objects
                            // which is big already

    return true;
}

bool ZBPropertyAttributes::SaveStateToIniFile( const CString IniFile, int ObjectID )
{
    CString EntityName;
    EntityName.Format( _T( "%s%d" ), (const char*)_PropertyAttributeStateSectionName, ObjectID );

    ZUSystemOption SystemOption( IniFile, EntityName );

    // RS-MODIF 12.12.04 we need to delete all records before saving
    DeleteAttributesFromIniFile( IniFile, ObjectID );

    size_t Idx = 0;
    CString KeyName;

    _ZBPropertyAttributeIterator i( &GetAttributeSetConst() );

    for ( _ZBPropertyAttribute* pAtt = i.GetFirst(); pAtt != NULL; pAtt = i.GetNext(), ++Idx )
    {
        // Format the key
        KeyName.Format( _T( "%s%d" ), (const char*)_PropertyAttributeStateEntityName, Idx );
        ZBTokenizer token;

        // Build the string
        token.AddToken( pAtt->GetCategoryID() );
        token.AddToken( pAtt->GetItemID() );

        // Write the string to the ini file
        SystemOption.WriteOption( KeyName, token.GetString() );
    }

    return true;
}

// RS-MODIF 12.12.04 delete attributes
bool ZBPropertyAttributes::DeleteAttributesFromIniFile( const CString IniFile, int ObjectID )
{
    CString EntityName;
    EntityName.Format( _T( "%s%d" ), (const char*)_PropertyAttributeStateSectionName, ObjectID );

    ZUSystemOption    SystemOption( IniFile, EntityName );

    CString KeyName;
    CString Line;
    size_t Idx = 0;

    do
    {
        // Format the key
        KeyName.Format( _T( "%s%d" ), (const char*)_PropertyAttributeStateEntityName, Idx );
        Line = SystemOption.ReadOption( KeyName, _T( "" ) );

        if ( Line.IsEmpty() )
        {
            break;
        }

        ++Idx;

        SystemOption.WriteOption( KeyName, _T( "0;0" ) );
    }
    while (Idx < 1000000);    // Sets the maximum loop at 1 million objects
                            // which is big already

    return true;
}
