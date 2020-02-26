/****************************************************************************
 * ==> PSS_ProcDeliveries --------------------------------------------------*
 ****************************************************************************
 * Description : Provides the procedures for deliveries                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcDeliveriesH
#define PSS_ProcDeliveriesH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_ProcDeliveries
    #define PSS_ProcDeliveries ZBProcDeliveries
#endif

// old class name mapping
#ifndef PSS_DeliveriesPropertiesBP
    #define PSS_DeliveriesPropertiesBP ZBBPDeliveriesProperties
#endif

class PSS_DeliveriesPropertiesBP;

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// scope symbols in stingray foundation library
using namespace sfl;

/**
* Procedures for deliveries
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcDeliveries : public CObject
{
    DECLARE_SERIAL(PSS_ProcDeliveries)

    public:
        typedef CCArray_T <PSS_DeliveriesPropertiesBP*, PSS_DeliveriesPropertiesBP*> IDeliveriesPropertiesSet;
        typedef Iterator_T<PSS_DeliveriesPropertiesBP*>                              IDeliveriesPropertiesIterator;

        /**
        * Constructor
        *@param pParent - the parent component
        */
        PSS_ProcDeliveries(CODSymbolComponent* pParent = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ProcDeliveries(const PSS_ProcDeliveries& other);

        virtual ~PSS_ProcDeliveries();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_ProcDeliveries& operator = (const PSS_ProcDeliveries& other);

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual PSS_ProcDeliveries* Dup() const;

        /**
        * Creates the initial properties
        *@return true on success, otherwise false
        */
        virtual bool CreateInitialProperties();

        /**
        * Sets the parent symbol object
        *@param pParent - the parent symbol object
        */
        virtual void SetParent(CODSymbolComponent* pParent);

        /**
        * Adds a new empty delivery
        *@return the new added delivery index, -1 on error
        */
        virtual int AddNewDelivery();

        /**
        * Adds a delivery
        *@param pProperty - the delivery property to add
        *@return the new added delivery index, -1 on error
        */
        virtual int AddDelivery(PSS_DeliveriesPropertiesBP* pProperty);

        /**
        * Deletes a delivery at index
        *@param index - the index
        *@return true on success, otherwise false
        */
        virtual bool DeleteDelivery(std::size_t index);

        /**
        * Deletes a delivery
        *@param pProperty - the delivery property to delete
        *@return true on success, otherwise false
        */
        virtual bool DeleteDelivery(PSS_DeliveriesPropertiesBP* pProperty);

        /**
        * Checks if the delivery name exists
        *@return true if the delivery name exists, otherwise false
        */
        virtual bool DeliveryNameExist(const CString& name) const;

        /**
        * Gets the next valid delivery name
        *@return the next valid delivery name
        */
        virtual CString GetNextDeliveryValidName() const;

        /**
        * Builds a string containing all the available deliverables
        *@param allDeliverables - all the deliverables to build
        *@return the string containing all the available deliverables
        */
        virtual CString GetAvailableDeliverables(const CString& allDeliverables) const;

        /**
        * Builds a string with all allocated deliverables
        *@return the string with all allocated deliverables
        */
        virtual CString GetAllocatedDeliverables() const;

        /**
        * Checks if a deliverable can be found in a string containing deliverables
        *@param deliverables - the deliverables to search in
        *@param value - the deliverable value to search
        *@return true if the deliverable can be found in the string containing deliverables, otherwise false
        */
        virtual bool IsDeliverableInString(const CString& deliverables, const CString& value) const;

        /**
        * Gets the delivery properties containing a deliverable
        *@param deliverableName - the deliverable name to search
        *@return the delivery properties containing the deliverable, NULL if not found or on error
        */
        virtual PSS_DeliveriesPropertiesBP* LocateDeliveryOfDeliverable(const CString& deliverableName) const;

        /**
        * Gets the delivery properties index containing a deliverable
        *@param deliverableName - the deliverable name to search
        *@return the delivery properties index containing the deliverable, -1 if not found or on error
        */
        virtual int LocateDeliveryIndexOfDeliverable(const CString& deliverableName) const;

        /**
        * Gets the delivery properties containing a specific main delivery
        *@param master - the master to search
        *@return the delivery properties containing the specific main delivery, NULL if not found or on error
        */
        virtual PSS_DeliveriesPropertiesBP* LocateDeliveryOfMain(const CString& main) const;

        /**
        * Gets the delivery properties index containing a specific main delivery
        *@param master - the main delivery to search
        *@return the delivery properties index containing the specific main delivery, -1 if not found or on error
        */
        virtual int LocateDeliveryIndexOfMain(const CString& main) const;

        /**
        * Replaces an old deliverable by a new one
        *@param oldDeliverableName - the old deliverable name
        *@param newDeliverableName - the new deliverable name
        *@return true on success, otherwise false
        */
        virtual bool ReplaceDeliverable(const CString& oldDeliverableName, const CString& newDeliverableName);

        /**
        * Deletes a deliverable from all deliveries, including the master
        *@param deliverableName - the deliverable name to search
        *@return true on success, otherwise false
        */
        virtual bool DeleteDeliverableFromAllDeliveries(const CString& deliverableName);

        /**
        * Gets the delivery set
        *@return the delivery set
        */
        virtual inline IDeliveriesPropertiesSet& GetDeliverySet();

        /**
        * Gets the deliveries count
        *@return the deliveries count
        */
        virtual inline std::size_t GetDeliveriesCount() const;

        /**
        * Gets the property at index
        *@param index - the index
        *@return the property, NULL if not found or on error
        */
        virtual inline PSS_DeliveriesPropertiesBP* GetProperty(std::size_t index) const;

        /**
        * Removes all the deliveries
        */
        virtual void RemoveAllDeliveries();

        /**
        * Gets the delivery name at index
        *@param index - the index
        *@return the delivery name, empty string if not found or on error
        */
        virtual CString GetDeliveryName(std::size_t index) const;

        /**
        * Sets the delivery name at index
        *@param index - the index
        *@param value - the delivery name
        */
        virtual void SetDeliveryName(std::size_t index, const CString& value);

        /**
        * Gets the delivery deliverables list at index
        *@param index - the index
        *@return the delivery deliberables list, empty string if not found or on error
        */
        virtual CString GetDeliveryDeliverables(std::size_t index) const;

        /**
        * Sets the delivery deliberables list at index
        *@param index - the index
        *@param value - the delivery deliberables list
        */
        virtual void SetDeliveryDeliverables(std::size_t index, const CString& value);

        /**
        * Adds a delivery deliverable to the deliberables at index
        *@param index - the index
        *@param value - the delivery deliberable list
        *@return true on success, otherwise false
        */
        virtual bool AddDeliveryDeliverable(std::size_t index, const CString& value);

        /**
        * Removes a delivery deliverable from the deliberables at index
        *@param index - the index
        *@param value - the delivery deliberable list
        *@return true on success, otherwise false
        */
        virtual bool RemoveDeliveryDeliverable(std::size_t index, const CString& value);

        /**
        * Removes all the deliveries deliverables from the deliberable list at index
        *@param index - the index
        *@return true on success, otherwise false
        */
        virtual bool RemoveAllDeliveryDeliverable(std::size_t index);

        /**
        * Gets the delivery quantity at index
        *@param index - the index
        *@return the delivery quantity
        */
        virtual float GetDeliveryQuantity(std::size_t index) const;

        /**
        * Sets the delivery quantity at index
        *@param index - the index
        *@param value - the delivery quantity
        */
        virtual void SetDeliveryQuantity(std::size_t index, const float value);

        /**
        * Gets the delivery percentage at index
        *@param index - the index
        *@return the delivery percentage
        */
        virtual float GetDeliveryPercentage(std::size_t index) const;

        /**
        * Sets the delivery percentage at index
        *@param index - the index
        *@param value - the delivery percentage
        */
        virtual void SetDeliveryPercentage(std::size_t index, const float value);

        /**
        * Gets the delivery main name at index
        *@param index - the index
        *@return the delivery main name at index, empty string of not found or on error
        */
        virtual CString GetDeliveryMain(std::size_t index) const;

        /**
        * Sets the delivery main name at index
        *@param index - the index
        *@param value - the delivery main name
        */
        virtual void SetDeliveryMain(std::size_t index, const CString& value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CODSymbolComponent*      m_pParent;
        IDeliveriesPropertiesSet m_Set;
};

//---------------------------------------------------------------------------
// PSS_ProcDeliveries
//---------------------------------------------------------------------------
PSS_ProcDeliveries::IDeliveriesPropertiesSet& PSS_ProcDeliveries::GetDeliverySet()
{
    return m_Set;
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcDeliveries::GetDeliveriesCount() const
{
    return m_Set.GetSize();
}
//---------------------------------------------------------------------------
PSS_DeliveriesPropertiesBP* PSS_ProcDeliveries::GetProperty(std::size_t index) const
{
    if (index < GetDeliveriesCount())
        return m_Set.GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------

#endif
