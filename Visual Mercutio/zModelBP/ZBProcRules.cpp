// **************************************************************************************************************
// *                                        Classe ZBProcRules                                                    *
// **************************************************************************************************************
// * JMR-MODIF - Le 21 novembre 2006 - Ajout de la classe ZBProcRules.                                            *
// **************************************************************************************************************
// * Cette classe est un gestionnaire pour l'ensemble des propriétés de type règles.                            *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZBProcRules.h"

#include "ZBBPRulesProp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// constant definition
const int LastRuleIDProperties = ZS_BP_PROP_RULES + 39;

IMPLEMENT_SERIAL(ZBProcRules, CObject, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Constructeur par défaut de la classe ZBProcRules.
ZBProcRules::ZBProcRules( CODSymbolComponent* pParent /*= NULL*/ )
    : m_pParent( pParent )
{
}

// Constructeur par copie de la classe ZBProcRules.
ZBProcRules::ZBProcRules( const ZBProcRules& src )
{
    *this = src;
}

// Destructeur de la classe ZBProcRules.
ZBProcRules::~ZBProcRules()
{
    RemoveAllRules();
}

// Surcharge de l'opérateur = pour la classe ZBProcRules.
ZBProcRules& ZBProcRules::operator=( const ZBProcRules& src )
{
    // Copy the members.
    ZBBPRulesPropertiesIterator i( &const_cast<ZBProcRules&>( src ).GetRuleSet() );

    for ( ZBBPRulesProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        AddRule( pProp->Dup() );
    }

    m_pParent = src.m_pParent;

    return *this;
}

// Cette fonction permet d'effectuer un duplicata de l'objet instancié.
ZBProcRules* ZBProcRules::Dup() const
{
    return ( new ZBProcRules( *this ) );
}

// Cette fonction permet l'attribution du composant parent.
void ZBProcRules::SetParent( CODSymbolComponent* pParent )
{
    m_pParent = pParent;
}

// Cette fonction permet l'ajout d'une nouvelle propriété vide, de type règle, dans la liste.
int ZBProcRules::AddNewRule()
{
    ZBBPRulesProperties* pProps = new ZBBPRulesProperties;

    return AddRule( pProps );
}

// Cette fonction permet l'ajout d'une propriété de type règle dans la liste.
int ZBProcRules::AddRule( ZBBPRulesProperties* pProperty )
{
    if ( pProperty )
    {
        // If no rule name specified, set it by default
        if ( pProperty->GetRuleName().IsEmpty() )
        {
            pProperty->SetRuleName( GetNextRuleValidName() );
        }

        m_Set.Add( pProperty );

        // Returns the index
        return GetRulesCount() - 1;
    }

    return -1;
}

// Cette fonction permet la suppression d'une propriété dans la liste.
bool ZBProcRules::DeleteRule( size_t Index )
{
    if ( Index < GetRulesCount() )
    {
        ZBBPRulesProperties* pProperty = GetProperty( Index );

        if ( pProperty )
        {
            m_Set.RemoveAt( Index );
            delete pProperty;
            return true;
        }
    }

    return false;
}

// Cette fonction permet la suppression d'une propriété dans la liste.
bool ZBProcRules::DeleteRule( ZBBPRulesProperties* pProperty )
{
    ZBBPRulesPropertiesIterator i( &m_Set );

    for ( ZBBPRulesProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProperty == pProp )
        {
            i.Remove();
            delete pProp;
            return true;
        }
    }

    return false;
}

// Cette fonction permet la suppression de toutes les propriétés dans la liste.
void ZBProcRules::RemoveAllRules()
{
    ZBBPRulesPropertiesIterator i( &m_Set );

    for ( ZBBPRulesProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        delete pProp;
    }

    // Then, remove all elements
    m_Set.RemoveAll();
}

// Obtient le nom de la règle.
CString ZBProcRules::GetRuleName( size_t Index ) const
{
    if ( Index < GetRulesCount() )
    {
        return m_Set.GetAt( Index )->GetRuleName();
    }

    return _T( "" );
}

// Inscrit le nom de la règle.
void ZBProcRules::SetRuleName( size_t Index, CString Value )
{
    if ( Index < GetRulesCount() )
    {
        m_Set.GetAt( Index )->SetRuleName( Value );
    }
}

// Obtient la description associée à cette règle.
CString ZBProcRules::GetRuleDescription( size_t Index ) const
{
    if ( Index < GetRulesCount() )
    {
        return m_Set.GetAt( Index )->GetRuleDescription();
    }

    return _T( "" );
}

// Inscrit la description associée à cette règle.
void ZBProcRules::SetRuleDescription( size_t Index, CString Value )
{
    if ( Index < GetRulesCount() )
    {
        m_Set.GetAt( Index )->SetRuleDescription( Value );
    }
}

// Obtient la description associée à cette règle.
CString ZBProcRules::GetRuleGUID( size_t Index ) const
{
    if ( Index < GetRulesCount() )
    {
        return m_Set.GetAt( Index )->GetRuleGUID();
    }

    return _T( "" );
}

// Inscrit la description associée à cette règle.
void ZBProcRules::SetRuleGUID( size_t Index, CString Value )
{
    if ( Index < GetRulesCount() )
    {
        m_Set.GetAt( Index )->SetRuleGUID( Value );
    }
}

// Permet de savoir si le nom de la règle spécifiée existe déjà.
bool ZBProcRules::RuleNameExist( const CString Name ) const
{
    // Run through the set and build the string
    ZBBPRulesPropertiesIterator i( &m_Set );

    for ( ZBBPRulesProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
    {
        if ( pProp->GetRuleName() == Name )
        {
            return true;
        }
    }

    return false;
}

// Obtient le prochain nom valide pour une règle.
CString ZBProcRules::GetNextRuleValidName() const
{
    CString str;
    int i = 1;

    do
    {
        str.Format( _T( "Règle %d" ), i++ );
    }
    while ( RuleNameExist( str ) == true );

    return str;
}

// Cette fonction permet de retrouver la propriété contenant la description souhaitée.
ZBBPRulesProperties* ZBProcRules::LocateRuleByDescription( const CString Description ) const
{
    int Index = LocateRuleIndexByDescription( Description );

    if ( Index == -1 )
    {
        return NULL;
    }

    return GetProperty( Index );
}

// Cette fonction permet de retrouver l'index de la propriété contenant la description souhaitée.
int ZBProcRules::LocateRuleIndexByDescription( const CString Description ) const
{
    // Run through the set of rules and check if found
    ZBBPRulesPropertiesIterator i( &m_Set );
    int Index = 0;

    for ( ZBBPRulesProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext(), ++Index )
    {
        if ( !pProp->GetRuleDescription().IsEmpty() && pProp->GetRuleDescription() == Description )
        {
            return Index;
        }
    }

    return -1;
}

// Fonction de sérialisation de l'objet.
void ZBProcRules::Serialize( CArchive& ar )
{
    // Only if the object is serialize from and to a document
    if ( ar.m_pDocument )
    {
        if ( ar.IsStoring() )
        {
            TRACE( _T( "ZBProcRules::Serialize : Start Save\n" ) );
    
            // Serialize the size of the set
            ar << (int)m_Set.GetSize();

            ZBBPRulesPropertiesIterator i( &m_Set );

            for ( ZBBPRulesProperties* pProp = i.GetFirst(); pProp; pProp = i.GetNext() )
            {
                ar << pProp;
            }

            TRACE( _T( "ZBProcRules::Serialize : End Save\n" ) );
        }
        else
        {
            TRACE( _T( "ZBProcRules::Serialize : Start Read\n" ) );

            RemoveAllRules();

            // Read the size of the set
            int Count;
            ar >> Count;

            ZBBPRulesProperties* pProp;

            for ( int i = 0; i < (int)Count; ++i )
            {
                ar >> pProp;
                AddRule( pProp );
            }
        
            TRACE( _T( "ZBProcRules::Serialize : End Read\n" ) );
        }
    }
}
