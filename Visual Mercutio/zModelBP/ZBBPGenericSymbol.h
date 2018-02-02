// **********************************************************************************************************
// *									  Classe ZBBPGenericSymbol											*
// **********************************************************************************************************
// * JMR-MODIF - Le 19 octobre 2005 - Ajout de la classe ZBBPGenericSymbol.									*
// **********************************************************************************************************
// * Cette classe permet la gestion et l'affichage de n'importe quel type de symbole. On initialise la		*
// * classe avec un pointeur vers la ressource du symbole, et celui-ci est entièrement pris en charge.		*
// **********************************************************************************************************

#if !defined(AFX_ZBBPGenericSymbol_H__F5100AAD_5FFF_4817_BE12_0A6B0BA8A8D4__INCLUDED_)
#define AFX_ZBBPGenericSymbol_H__F5100AAD_5FFF_4817_BE12_0A6B0BA8A8D4__INCLUDED_

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

#include "zModel\ZBSymbol.h"
#include "zBaseSym\zBaseSymRes.h"

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZBBPGenericSymbol : public ZBSymbol
{
	DECLARE_SERIAL( ZBBPGenericSymbol )

public:

	ZBBPGenericSymbol( const CString Name = _T( "" ) );
	virtual ~ZBBPGenericSymbol();

// Opérations
public:

	/* Copy constructor. */
	ZBBPGenericSymbol( const ZBBPGenericSymbol& src );

	/* Assignment operator. */
	ZBBPGenericSymbol& operator=( const ZBBPGenericSymbol& src );

	/* Create a duplicate copy of this object. */
	virtual CODComponent* Dup() const;

// Méthodes basiques du symbole
public:

	// Le symbole n'accepte pas les attributs dynamiques
	virtual bool AcceptDynamicAttributes() const
	{
		return false;
	}

	// Les propriétés du symbole ne peuvent pas être éditées.
	virtual bool IsPropertiesReadOnly() const
	{
		return true;
	}

	// Le symbole ne peut pas contenir de modèles enfants.
	virtual bool CanContainChildModel() const
	{
		return false;
	}

	// Le modèle enfant ne peut pas être une référence.
	virtual bool IsChildModelRef() const
	{
		return false;
	}

	// Les lignes de commentaires ne peuvent pas être éditées.
	virtual bool CommentTextEditReadOnly() const
	{
		return true;
	}

	// Le nom du symbole peut être édité.
	virtual bool SymbolNameTextEditReadOnly() const
	{
		return false;
	}

	// JMR-MODIF - Le 20 mars 2006 - Fonction de contrôle des références, -1 signifie non pris en charge.
	virtual int GetSymbolReferenceNumber()
	{
		return -1;
	}

	// JMR-MODIF - Le 22 mars 2006 - Fonction permettant de définir si le symbole est générique.
	virtual BOOL IsGeneric()
	{
		return TRUE;
	}

// Fonctions
public:

	ULONG STDMETHODCALLTYPE AddRef()
	{
		return CODSymbolComponent::AddRef();
	}

	ULONG STDMETHODCALLTYPE Release()
	{
		return CODSymbolComponent::Release();
	}

	BOOL Create( UINT nID, const CString Name = _T( "" ) );

	virtual int GetRightSubMenu() const;

	virtual void Serialize( CArchive& ar );
};

inline int ZBBPGenericSymbol::GetRightSubMenu() const
{
	return 10;
}

#endif // !defined(AFX_ZBBPGenericSymbol_H__F5100AAD_5FFF_4817_BE12_0A6B0BA8A8D4__INCLUDED_)