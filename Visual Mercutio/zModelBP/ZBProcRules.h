// **************************************************************************************************************
// *										Classe ZBProcRules													*
// **************************************************************************************************************
// * JMR-MODIF - Le 21 novembre 2006 - Ajout de la classe ZBProcRules.											*
// **************************************************************************************************************
// * Cette classe est un gestionnaire pour l'ensemble des propriétés de type règles.							*
// **************************************************************************************************************

#if !defined(AFX_ZBProcRules_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_)
#define AFX_ZBProcRules_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_

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

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class ZBBPRulesProperties;

using namespace sfl;

typedef CCArray_T<ZBBPRulesProperties*, ZBBPRulesProperties*> ZBBPRulesPropertiesSet;
typedef Iterator_T<ZBBPRulesProperties*> ZBBPRulesPropertiesIterator;

class AFX_EXT_CLASS ZBProcRules : public CObject
{
	DECLARE_SERIAL( ZBProcRules )

public:

	ZBProcRules( CODSymbolComponent* pParent = NULL );
	virtual ~ZBProcRules();

	ZBProcRules( const ZBProcRules& src );

	ZBProcRules& operator=( const ZBProcRules& src );

	virtual ZBProcRules* Dup() const;

	void SetParent( CODSymbolComponent* pParent );

	int AddNewRule();
	int AddRule( ZBBPRulesProperties* pProperty );

	bool DeleteRule( size_t Index );
	bool DeleteRule( ZBBPRulesProperties* pProperty );
	bool RuleNameExist( const CString Name ) const;

	CString GetNextRuleValidName() const;

	ZBBPRulesProperties* LocateRuleByDescription( const CString Description ) const;
	int LocateRuleIndexByDescription( const CString Description ) const;

	// Obtient le pointeur du groupe des propriétés.
	ZBBPRulesPropertiesSet& GetRuleSet()
	{
		return m_Set;
	}

	// Obtient le nombre de propriétés contenues dans l'ensemble.
	size_t GetRulesCount() const
	{
		return m_Set.GetSize();
	}

	// Obtient la propriété contenue à l'index spécifié.
	ZBBPRulesProperties* GetProperty( size_t Index ) const
	{
		if ( Index < GetRulesCount() )
		{
			return m_Set.GetAt( Index );
		}

		return NULL;
	}

	void RemoveAllRules();

	CString GetRuleName( size_t Index ) const;
	void SetRuleName( size_t Index, CString Value );

	CString GetRuleDescription( size_t Index ) const;
	void SetRuleDescription( size_t Index, CString Value );

	CString GetRuleGUID( size_t Index ) const;
	void SetRuleGUID( size_t Index, CString Value );

	virtual void Serialize( CArchive& ar );

private:

	CODSymbolComponent*		m_pParent;
	ZBBPRulesPropertiesSet	m_Set;
};

#endif // !defined(AFX_ZBProcRules_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_)