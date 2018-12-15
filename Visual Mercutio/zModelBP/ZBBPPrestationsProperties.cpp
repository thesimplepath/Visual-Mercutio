// **************************************************************************************************************
// *                        Classes ZBBPPrestationNode et ZBBPPrestationsProperties                                *
// **************************************************************************************************************
// * JMR-MODIF - Le 31 janvier 2006 - Ajout des classes ZBBPPrestationNode et ZBBPPrestationsProperties.        *
// **************************************************************************************************************
// * Ces classes permettent la gestion des propriétés liées aux prestations. Lorsque l'utilisateur ajoute une    *
// * nouvelle prestation au processus, la liste d'objets de la classe ZBBPPrestationsProperties prend en charge    *
// * une nouvelle instance de la classe ZBBPPrestationNode.    Cette dernière représente la prestation.            *
// **************************************************************************************************************

#include "stdafx.h"
#include "ZBBPPrestationsProperties.h"

// **************************************************************************************************************
// *                    Classe ZBBPPrestationNode : Représente une prestation particulière.                        *
// **************************************************************************************************************

IMPLEMENT_SERIAL( ZBBPPrestationNode, CObject, def_Version )

// Constructeur par défaut de la classe ZBBPPrestationNode.
ZBBPPrestationNode::ZBBPPrestationNode()
{
    m_PrestationName        = _T( "" );
    m_PrestationGUID        = _T( "" );
    m_PercentageActivity    = 0.0f;
}

// Constructeur par copie de la classe ZBBPPrestationNode.
ZBBPPrestationNode::ZBBPPrestationNode( const ZBBPPrestationNode& src )
{
    m_PrestationName        = src.GetPrestationName();
    m_PrestationGUID        = src.GetPrestationGUID();

    src.GetValue( Z_PRESTATION_PERCENTAGE, m_PercentageActivity );
}

// Destructeur de la classe ZBBPPrestationNode.
ZBBPPrestationNode::~ZBBPPrestationNode()
{
}

// Cette fonction permet d'obtenir le nom attribué à la propriété de prestation.
CString ZBBPPrestationNode::GetPrestationName() const
{
    return m_PrestationName;
}

// Cette fonction permet d'attribuer un nom à la propriété de prestation.
void ZBBPPrestationNode::SetPrestationName( LPCTSTR lpszValue )
{
    if ( lpszValue != NULL )
    {
        m_PrestationName = lpszValue;
    }
    else
    {
        TRACE0( _T( "ZBBPPrestationNode -> Invalid Task List pointer!\n" ) );
        ASSERT( FALSE );
    }
}

// Cette fonction permet d'obtenir le GUID attribué à la propriété de prestation.
CString ZBBPPrestationNode::GetPrestationGUID() const
{
    return m_PrestationGUID;
}

// Cette fonction permet d'attribuer un GUID à la propriété de prestation.
void ZBBPPrestationNode::SetPrestationGUID( LPCTSTR lpszValue )
{
    if ( lpszValue != NULL )
    {
        m_PrestationGUID = lpszValue;
    }
    else
    {
        TRACE0( _T( "ZBBPPrestationNode -> Invalid prestation GUID pointer!\n" ) );
        ASSERT( FALSE );
    }
}

// Cette fonction permet d'obtenir une valeur représentée dans la propriété de prestation.
// Entrées :    - nPropID    ->    Permet de définir quelle valeur de type float doit être obtenue. Seul le
//                                pourcentage d'activité de la prestation est implémenté pour le moment.
//                - fValue    ->    Pointeur vers une valeur externe, de type float.
// Retour :        Un booléen indiquant si la valeur a pu être obtenue.
BOOL ZBBPPrestationNode::GetValue( int nPropID, float &fValue ) const
{
    switch ( nPropID )
    {
        // Valeur de pourcentage attribué à cette prestation.
        case Z_PRESTATION_PERCENTAGE:
        {
            fValue = m_PercentageActivity;
            return TRUE;
        }

        default:
        {
            return FALSE;
        }
    }
}

// Cette fonction permet d'attribuer une valeur de type float dans la propriété de prestation.
// Entrées :    - nPropID    ->    Permet de définir quelle valeur de type float doit être attribuée. Seul le
//                                pourcentage d'activité de la prestation est implémenté pour le moment.
//                - fValue    ->    La nouvelle valeur, de type float.
// Retour :        Aucun.
void ZBBPPrestationNode::SetValue( int nPropID, float Value )
{
    switch ( nPropID )
    {
        case Z_PRESTATION_PERCENTAGE:
        {
            m_PercentageActivity = Value;
            break;
        }

        default:
        {
            break;
        }
    }
}

// Permet de sérialiser le contenu de l'objet.
void ZBBPPrestationNode::Serialize( CArchive& ar )
{
    CObject::Serialize( ar );

    if ( ar.IsStoring() )
    {
        TRACE( _T( "ZBBPPrestationNode::Serialize : Start Save\n" ) );

        PUT_SCHEMA( ar, ZBBPPrestationNode );

        ar << m_PrestationName;
        ar << m_PrestationGUID;
        ar << m_PercentageActivity;

        TRACE( _T( "ZBBPPrestationNode::Serialize : End Save\n" ) );
    }
    else
    {
        TRACE( _T( "ZBBPPrestationNode::Serialize : Start Read\n" ) );

        UINT nSchema;
        GET_SCHEMA( ar, nSchema );

        ar >> m_PrestationName;
        ar >> m_PrestationGUID;
        ar >> m_PercentageActivity;

        TRACE( _T( "ZBBPPrestationNode::Serialize : End Read\n" ) );
    }
}

// **************************************************************************************************************
// * Classe ZBBPPrestationsProperties : Représente et gère la liste des prestations ajoutées par l'utilisateur. *
// **************************************************************************************************************

// Constructeur par défaut de la classe ZBBPPrestationsProperties.
ZBBPPrestationsProperties::ZBBPPrestationsProperties()
{
    m_Pos = NULL;
}

// Destructeur de la classe ZBBPPrestationsProperties.
ZBBPPrestationsProperties::~ZBBPPrestationsProperties()
{
}

// Cette fonction permet de libérer la ressource mémoire utilisée par cet objet.
void ZBBPPrestationsProperties::RemoveAll()
{
    POSITION Pos = GetHeadPosition();

    while ( Pos != NULL )
    {
        ZBBPPrestationNode* m_TmpPrestation = dynamic_cast<ZBBPPrestationNode*>( m_PrestationsList.GetAt( Pos ) );

        if ( m_TmpPrestation != NULL )
        {
            delete m_TmpPrestation;
            m_TmpPrestation = NULL;
        }

        GetNextPosition();

        m_PrestationsList.RemoveAt( Pos );

        Pos = m_Pos;
    }
}

// Cette fonction surcharge l'opérateur = pour permettre la coipe directe d'une prestation.
ZBBPPrestationsProperties& ZBBPPrestationsProperties::operator=( const ZBBPPrestationsProperties& src )
{
    POSITION Pos = src.m_PrestationsList.GetHeadPosition();

    while ( Pos != NULL )
    {
        CObject* m_TmpObject                    = const_cast<CObject*>( src.m_PrestationsList.GetAt( Pos ) );
        ZBBPPrestationNode* m_TmpSrcPrestation    = dynamic_cast<ZBBPPrestationNode*>( m_TmpObject );

        ZBBPPrestationNode* m_TmpPrestation = new ZBBPPrestationNode( *m_TmpSrcPrestation );

        m_PrestationsList.AddTail( m_TmpPrestation );

        src.m_PrestationsList.GetNext( Pos );
    }

    m_Pos = src.m_Pos;

    return *this;
}

// Cette fonction permet d'ajouter une nouvelle prestation dans la liste.
void ZBBPPrestationsProperties::AddPrestation( ZBBPPrestationNode* Prestation )
{
    m_Pos = m_PrestationsList.AddTail( Prestation );
}

// JMR-MODIF - Le 20 mars 2006 - Cette fonction permet de supprimer une prestation de la liste.
void ZBBPPrestationsProperties::RemovePrestation( POSITION Pos )
{
    if ( Pos != NULL )
    {
        ZBBPPrestationNode* m_TmpNode = GetAt( Pos );

        if ( m_TmpNode != NULL )
        {
            delete m_TmpNode;
            m_TmpNode = NULL;
        }

        m_PrestationsList.RemoveAt( Pos );
    }
}

// Cette fonction permet d'obtenir une prestation en fonction de sa position.
ZBBPPrestationNode* ZBBPPrestationsProperties::GetAt( POSITION Pos )
{
    if ( Pos != NULL )
    {
        return dynamic_cast<ZBBPPrestationNode*>( m_PrestationsList.GetAt( Pos ) );
    }

    return NULL;
}

// Cette fonction permet d'obtenir la position de la première prestation de la liste.
POSITION ZBBPPrestationsProperties::GetHeadPosition()
{
    m_Pos = m_PrestationsList.GetHeadPosition();

    return m_Pos;
}

// Cette fonction permet d'obtenir la position de la dernière prestation de la liste.
POSITION ZBBPPrestationsProperties::GetTailPosition()
{
    m_Pos = m_PrestationsList.GetTailPosition();

    return m_Pos;
}

// Cette fonction permet d'obtenir la position de la prestation précédant la prestation courante. NULL si inexistante.
POSITION ZBBPPrestationsProperties::GetPrevPosition()
{
    if ( m_Pos != NULL )
    {
        m_PrestationsList.GetPrev( m_Pos );
    }

    return m_Pos;
}

// Cette fonction permet d'obtenir la position de la prestation suivant la prestation courante. NULL si inexistante.
POSITION ZBBPPrestationsProperties::GetNextPosition()
{
    if ( m_Pos != NULL )
    {
        m_PrestationsList.GetNext( m_Pos );
    }

    return m_Pos;
}

// Permet de sérialiser le contenu de l'objet.
void ZBBPPrestationsProperties::Serialize( CArchive& ar )
{
    if ( ar.IsStoring() )
    {
        TRACE( _T( "ZBBPPrestationsProperties::Serialize : Start Save\n" ) );

        ar << m_PrestationsList.GetCount();

        GetHeadPosition();

        while ( m_Pos != NULL )
        {
            ZBBPPrestationNode* m_TmpPrestation = dynamic_cast<ZBBPPrestationNode*>( m_PrestationsList.GetAt( m_Pos ) );

            if ( m_TmpPrestation != NULL )
            {
                m_TmpPrestation->Serialize( ar );
            }

            GetNextPosition();
        }

        GetHeadPosition();

        TRACE( _T( "ZBBPPrestationsProperties::Serialize : End Save\n" ) );
    }
    else
    {
        TRACE( _T( "ZBBPPrestationsProperties::Serialize : Start Read\n" ) );

        INT_PTR nbPrestations;

        ar >> nbPrestations;

        for ( INT_PTR i = 0; i < nbPrestations; i++ )
        {
            ZBBPPrestationNode* m_TmpPrestation = new ZBBPPrestationNode();

            m_TmpPrestation->Serialize( ar );

            AddPrestation( m_TmpPrestation );
        }

        GetHeadPosition();

        TRACE( _T( "ZBBPPrestationsProperties::Serialize : End Read\n" ) );
    }
}
