// **************************************************************************************************************
// *                        Classes ZBBPPrestationNode et ZBBPPrestationsProperties                                *
// **************************************************************************************************************
// * JMR-MODIF - Le 31 janvier 2006 - Ajout des classes ZBBPPrestationNode et ZBBPPrestationsProperties.        *
// **************************************************************************************************************
// * Ces classes permettent la gestion des propriétés liées aux prestations. Lorsque l'utilisateur ajoute une    *
// * nouvelle prestation au processus, la liste d'objets de la classe ZBBPPrestationsProperties prend en charge    *
// * une nouvelle instance de la classe ZBBPPrestationNode.    Cette dernière représente la prestation.            *
// **************************************************************************************************************

#if !defined(AFX_ZBBPPrestationsProperties_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)
#define AFX_ZBBPPrestationsProperties_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zPropertyIds.h"

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//@flag Z_PRESTATION_NAME | Identifier for the name of the prestation.
#define Z_PRESTATION_NAME            1

//@flag Z_PRESTATION_PERCENTAGE | Identifier for the percentage of activity of the prestation.
#define Z_PRESTATION_PERCENTAGE        2

//@flag Z_PRESTATION_PRESTPROCESS | Identifier for the prestation value in the process.
#define Z_PRESTATION_PRESTPROCESS    3

// JMR-MODIF - Le 19 juin 2006 - Ajout de l'identifieur Z_PRESTATION_IDENTIFIER.
//@flag Z_PRESTATION_IDENTIFIER | Identifier for the prestation identifier in the process.
#define Z_PRESTATION_IDENTIFIER        4

// **************************************************************************************************************
// *                    Classe ZBBPPrestationNode : Représente une prestation particulière.                        *
// **************************************************************************************************************
class AFX_EXT_CLASS ZBBPPrestationNode : public CObject
{
    DECLARE_SERIAL( ZBBPPrestationNode )

public:

    ZBBPPrestationNode();
    ZBBPPrestationNode( const ZBBPPrestationNode& src );
    ~ZBBPPrestationNode();

    CString GetPrestationName() const;
    void    SetPrestationName( LPCTSTR lpszValue );

    CString GetPrestationGUID() const;
    void    SetPrestationGUID( LPCTSTR lpszValue );

    BOOL    GetValue( int nPropID, float &fValue ) const;
    void    SetValue( int nPropID, float  fValue );

    virtual void Serialize( CArchive& ar );

private:

    CString m_PrestationName;
    CString m_PrestationGUID;

    float    m_PercentageActivity;
};

// **************************************************************************************************************
// * Classe ZBBPPrestationsProperties : Représente et gère la liste des prestations ajoutées par l'utilisateur. *
// **************************************************************************************************************
class AFX_EXT_CLASS ZBBPPrestationsProperties
{
public:

    ZBBPPrestationsProperties();
    ~ZBBPPrestationsProperties();

    ZBBPPrestationsProperties& operator=( const ZBBPPrestationsProperties& src );

    void AddPrestation( ZBBPPrestationNode* Prestation );
    // JMR-MODIF - Le 20 mars 2006 - Ajout de la fonction RemovePrestation.
    void RemovePrestation( POSITION Pos );
    void RemoveAll();

    ZBBPPrestationNode* GetAt ( POSITION Pos );

    POSITION GetHeadPosition();
    POSITION GetTailPosition();
    POSITION GetPrevPosition();
    POSITION GetNextPosition();

    virtual void Serialize( CArchive& ar );

private:

    CObList        m_PrestationsList;
    POSITION    m_Pos;
};

#endif // !defined(AFX_ZBBPPrestationsProperties_H__D6010BE6_7C2A_47FF_857B_0C64A020F48F__INCLUDED_)