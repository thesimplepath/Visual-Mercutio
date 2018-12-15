// **************************************************************************************************************
// *                                        Classe ZBProcDeliveries                                                *
// **************************************************************************************************************
// * JMR-MODIF - Le 6 février 2006 - Ajout de la classe ZBProcDeliveries.                                        *
// **************************************************************************************************************
// * Cette classe est un gestionnaire pour l'ensemble des propriétés de type livraisons.                        *
// **************************************************************************************************************

#if !defined(AFX_ZBProcDeliveries_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_)
#define AFX_ZBProcDeliveries_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_

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

class ZBBPDeliveriesProperties;

using namespace sfl;

typedef CCArray_T<ZBBPDeliveriesProperties*, ZBBPDeliveriesProperties*> ZBBPDeliveriesPropertiesSet;
typedef Iterator_T<ZBBPDeliveriesProperties*> ZBBPDeliveriesPropertiesIterator;

class AFX_EXT_CLASS ZBProcDeliveries : public CObject
{
    DECLARE_SERIAL( ZBProcDeliveries )

public:

    ZBProcDeliveries( CODSymbolComponent* pParent = NULL );
    virtual ~ZBProcDeliveries();

    ZBProcDeliveries( const ZBProcDeliveries& src );

    ZBProcDeliveries& operator=( const ZBProcDeliveries& src );

    virtual ZBProcDeliveries* Dup() const;

    void SetParent( CODSymbolComponent* pParent );

    int AddNewDelivery();
    int AddDelivery( ZBBPDeliveriesProperties* pProperty );

    bool CreateInitialProperties();
    bool DeleteDelivery( size_t Index );
    bool DeleteDelivery( ZBBPDeliveriesProperties* pProperty );
    bool DeliveryNameExist( const CString Name ) const;
    bool ReplaceDeliverable( const CString OldDeliverableName, const CString NewDeliverableName );
    bool DeleteDeliverableFromAllDeliveries( const CString DeliverableName );
    bool IsDeliverableInString( const CString Deliverables, const CString Value ) const;

    CString GetNextDeliveryValidName() const;
    CString GetAvailableDeliverables( const CString AllDeliverables ) const;
    CString GetAllocatedDeliverables() const;

    ZBBPDeliveriesProperties* LocateDeliveryOfDeliverable( const CString DeliverableName ) const;
    int LocateDeliveryIndexOfDeliverable( const CString DeliverableName ) const;

    ZBBPDeliveriesProperties* LocateDeliveryOfMain( const CString Main ) const;
    int LocateDeliveryIndexOfMain( const CString Master ) const;

    // Obtient le pointeur du groupe des propriétés.
    ZBBPDeliveriesPropertiesSet& GetDeliverySet()
    {
        return m_Set;
    };

    // Obtient le nombre de propriétés contenues dans l'ensemble.
    size_t GetDeliveriesCount() const
    {
        return m_Set.GetSize();
    };

    // Obtient la propriété contenue à l'index spécifié.
    ZBBPDeliveriesProperties* GetProperty( size_t Index ) const
    {
        if ( Index < GetDeliveriesCount() )
        {
            return m_Set.GetAt( Index );
        }

        return NULL;
    };

    void RemoveAllDeliveries();

    CString GetDeliveryName( size_t Index ) const;
    void SetDeliveryName( size_t Index, CString Value );

    CString GetDeliveryDeliverables( size_t Index ) const;
    void SetDeliveryDeliverables( size_t Index, CString Value );

    bool AddDeliveryDeliverable( size_t Index, CString Value );
    bool RemoveDeliveryDeliverable( size_t Index, CString Value );
    bool RemoveAllDeliveryDeliverable( size_t Index );

    float GetDeliveryQuantity( size_t Index ) const;
    void SetDeliveryQuantity( size_t Index, const float value );

    float GetDeliveryPercentage( size_t Index ) const;
    void SetDeliveryPercentage( size_t Index, const float value );

    CString GetDeliveryMain( size_t Index ) const;
    void SetDeliveryMain( size_t Index, CString Value );

    virtual void Serialize( CArchive& ar );

private:

    CODSymbolComponent*            m_pParent;
    ZBBPDeliveriesPropertiesSet    m_Set;
};

#endif // !defined(AFX_ZBProcDeliveries_H__562EAAA5_9EC1_4359_9853_36C96DC6DD6A__INCLUDED_)