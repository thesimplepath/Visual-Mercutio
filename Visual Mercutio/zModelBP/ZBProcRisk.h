// **************************************************************************************************************
// *											   Classe ZBProcRisk											*
// **************************************************************************************************************
// * JMR-MODIF - Le 3 juin 2007 - Ajout de la classe ZBProcRisk.												*
// **************************************************************************************************************
// * Cette classe est un gestionnaire pour l'ensemble des propriétés de type risques.							*
// **************************************************************************************************************

#if !defined(AFX_ZBProcRisk_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_)
#define AFX_ZBProcRisk_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_

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

class ZBBPRiskProperties;

using namespace sfl;

typedef CCArray_T<ZBBPRiskProperties*, ZBBPRiskProperties*> ZBBPRiskPropertiesSet;
typedef Iterator_T<ZBBPRiskProperties*> ZBBPRiskPropertiesIterator;

class AFX_EXT_CLASS ZBProcRisk : public CObject
{
	DECLARE_SERIAL( ZBProcRisk )

public:

	ZBProcRisk( CODSymbolComponent* pParent = NULL );
	virtual ~ZBProcRisk();

	ZBProcRisk( const ZBProcRisk& src );

	ZBProcRisk& operator=( const ZBProcRisk& src );

	virtual ZBProcRisk* Dup() const;

	void SetParent( CODSymbolComponent* pParent );

	int AddNewRisk();
	int AddRisk( ZBBPRiskProperties* pProperty );

	bool CreateInitialProperties();
	bool DeleteRisk( size_t Index );
	bool DeleteRisk( ZBBPRiskProperties* pProperty );
	bool RiskNameExist( const CString Name ) const;

	CString GetNextRiskValidName() const;

	// Obtient le pointeur du groupe des propriétés.
	ZBBPRiskPropertiesSet& GetRiskSet()
	{
		return m_Set;
	};

	// Obtient le nombre de propriétés contenues dans l'ensemble.
	size_t GetRiskCount() const
	{
		return m_Set.GetSize();
	};

	// Obtient la propriété contenue à l'index spécifié.
	ZBBPRiskProperties* GetProperty( size_t Index ) const
	{
		if ( Index < GetRiskCount() )
		{
			return m_Set.GetAt( Index );
		}

		return NULL;
	};

	void RemoveAllRisks();

	CString GetRiskName( size_t Index ) const;
	void SetRiskName( size_t Index, CString Value );

	CString GetRiskDesc( size_t Index ) const;
	void SetRiskDesc( size_t Index, CString Value );

	CString GetRiskType( size_t Index ) const;
	void SetRiskType( size_t Index, CString Value );

	int GetRiskImpact( size_t Index ) const;
	void SetRiskImpact( size_t Index, int Value );

	int GetRiskProbability( size_t Index ) const;
	void SetRiskProbability( size_t Index, int Value );

	int GetRiskSeverity( size_t Index ) const;
	void SetRiskSeverity( size_t Index, int Value );

	float GetRiskUE( size_t Index ) const;
	void SetRiskUE( size_t Index, float Value );

	float GetRiskPOA( size_t Index ) const;
	void SetRiskPOA( size_t Index, float Value );

	bool GetRiskAction( size_t Index ) const;
	void SetRiskAction( size_t Index, bool Value );

	virtual void Serialize( CArchive& ar );

private:

	CODSymbolComponent*			m_pParent;
	ZBBPRiskPropertiesSet		m_Set;
};

#endif // !defined(AFX_ZBProcRisk_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_)