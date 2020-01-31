// **************************************************************************************************************
// *                                  Classe ZBBPDeliveriesProperties                                            *
// **************************************************************************************************************
// * JMR-MODIF - Le 6 février 2006 - Ajout de la classe ZBBPDeliveriesProperties.                                *
// **************************************************************************************************************
// * Cette classe représente une propriété de type livraison.                                                    *
// **************************************************************************************************************

#ifndef __ZBBPDeliveriesProp_H__
#define __ZBBPDeliveriesProp_H__

#if _MSC_VER > 1000
    #pragma once
#endif

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_DeliveriesPropertiesBP
    #define PSS_DeliveriesPropertiesBP ZBBPDeliveriesProperties
#endif

#include "PSS_PropIDs.h"

#ifdef _ZMODELBPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// Process change flags

//@topic Deliveries Properties Change Flags | Different aspects of the Deliveries
// properties that can be changed individually.
//@flag Z_CHANGE_DELIVERY_NAME | Change the name of this delivery.
#define Z_CHANGE_DELIVERY_NAME            0x0001
//@flag Z_CHANGE_DELIVERY_DELIVERABLES | Change the deliverables list for this delivery.
#define Z_CHANGE_DELIVERY_DELIVERABLES    0x0002
//@flag Z_CHANGE_DELIVERY_QUANTITY | Change the quantity for this delivery.
#define Z_CHANGE_DELIVERY_QUANTITY        0x0004
//@flag Z_CHANGE_DELIVERY_PRECENTAGE | Change the percentage for this delivery.
#define Z_CHANGE_DELIVERY_PRECENTAGE    0x0008
//@flag Z_CHANGE_DELIVERY_MAIN | Change the master deliverable for this delivery.
#define Z_CHANGE_DELIVERY_MAIN            0x0016

/////////////////////////////////////////////////////////////////////////////
// Fill property IDs

//@topic Fill Property Identifiers | Identify the properties contained by
// <ZBBPDeliveriesProperties> objects. The ZBBPDeliveriesProperties class is a property
// container for these sub-properties. These property identifiers are
// unique within a process properties container. These identifiers are used
// in conjunction with the <IODPropertyContainer> interface implemented
// by the process property container.
//@flag Z_DELIVERIES_NAME | Identifier for the name of this delivery.
#define Z_DELIVERY_NAME                    1
//@flag Z_DELIVERIES_DELIVERABLES | Identifier for the list of deliverables for this delivery.
#define Z_DELIVERY_DELIVERABLES            2
//@flag Z_DELIVERIES_QUANTITY | Identifier for the quantity for this delivery.
#define Z_DELIVERY_QUANTITY                3
//@flag Z_DELIVERY_PERCENTAGE | Identifier for the percentage for this delivery.
#define Z_DELIVERY_PERCENTAGE            4
//@flag Z_DELIVERIES_MAIN | Identifier for the main deliverable for this delivery.
#define Z_DELIVERY_MAIN                    5

class AFX_EXT_CLASS ZBBPDeliveriesProperties : public CObject
{
    DECLARE_SERIAL(ZBBPDeliveriesProperties)

public:

    ZBBPDeliveriesProperties();
    ZBBPDeliveriesProperties(const ZBBPDeliveriesProperties& propProcess);

    virtual ~ZBBPDeliveriesProperties();

public:

    ZBBPDeliveriesProperties& operator=(const ZBBPDeliveriesProperties& propProcess);

    BOOL operator==(const ZBBPDeliveriesProperties propProcess) const;

    virtual ZBBPDeliveriesProperties* Dup() const;

    virtual void Merge(ZBBPDeliveriesProperties* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL);

    virtual BOOL IsEqual(ZBBPDeliveriesProperties* pProp);

public:

    CString GetDeliveryName() const;
    void SetDeliveryName(LPCTSTR lpszValue);

    CString GetDeliveryDeliverables() const;
    void SetDeliveryDeliverables(LPCTSTR lpszValue);
    bool IsDeliverableInDelivery(LPCTSTR lpszValue);

    float GetDeliveryQuantity() const;
    void SetDeliveryQuantity(const float value);

    float GetDeliveryPercentage() const;
    void SetDeliveryPercentage(const float value);

    CString GetDeliveryMain() const;
    void SetDeliveryMain(LPCTSTR lpszValue);

    /////////////////////////////////////////////////////////////////////////
    // GetValue and SetValue functions

    virtual BOOL GetValue(const int nPropId, int& nValue) const;
    virtual BOOL GetValue(const int nPropId, UINT& nValue) const;
    virtual BOOL GetValue(const int nPropId, DWORD& dwValue) const;
    virtual BOOL GetValue(const int nPropId, float& fValue) const;
    virtual BOOL GetValue(const int nPropId, CString& strValue) const;

    virtual BOOL SetValue(const int nPropId, const int nValue);
    virtual BOOL SetValue(const int nPropId, const UINT nValue);
    virtual BOOL SetValue(const int nPropId, const DWORD dwValue);
    virtual BOOL SetValue(const int nPropId, const float fValue);
    virtual BOOL SetValue(const int nPropId, LPCTSTR lpszValue);

    virtual void Serialize(CArchive& ar);

private:

    void SetDeliveryNameEx(const CString value);
    void SetDeliveryDeliverablesEx(const CString value);
    void SetDeliveryMainEx(const CString value);

public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    CString    m_DeliveryName;
    CString    m_DeliveryDeliverables;
    CString    m_DeliveryMain;

    float    m_DeliveryQuantity;
    float    m_DeliveryPercentage;
};

// Cette fonction permet d'effectuer un duplicata de l'objet instancié.
inline ZBBPDeliveriesProperties* ZBBPDeliveriesProperties::Dup() const
{
    return new ZBBPDeliveriesProperties(*this);
}

// Obtient le nom de la livraison
inline CString ZBBPDeliveriesProperties::GetDeliveryName() const
{
    return m_DeliveryName;
}

// Obtient la liste des livrables de la livraison
inline CString ZBBPDeliveriesProperties::GetDeliveryDeliverables() const
{
    return m_DeliveryDeliverables;
}

// Obtient la quantité de la livraison
inline float ZBBPDeliveriesProperties::GetDeliveryQuantity() const
{
    return m_DeliveryQuantity;
}

// Indique la quantité de la livraison.
inline void ZBBPDeliveriesProperties::SetDeliveryQuantity(const float value)
{
    m_DeliveryQuantity = value;
}

// Obtient le pourcentage de la livraison
inline float ZBBPDeliveriesProperties::GetDeliveryPercentage() const
{
    return m_DeliveryPercentage;
}

// Indique le pourcentage de la livraison.
inline void ZBBPDeliveriesProperties::SetDeliveryPercentage(const float value)
{
    m_DeliveryPercentage = value;
}

// Obtient le nom du livrable principal de la livraison
inline CString ZBBPDeliveriesProperties::GetDeliveryMain() const
{
    return m_DeliveryMain;
}

#endif
