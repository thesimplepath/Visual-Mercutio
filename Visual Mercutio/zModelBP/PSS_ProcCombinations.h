/****************************************************************************
 * ==> PSS_ProcCombinations ------------------------------------------------*
 ****************************************************************************
 * Description : Provides the procedures for combinations                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcCombinationsH
#define PSS_ProcCombinationsH

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
#ifndef PSS_ProcCombinations
    #define PSS_ProcCombinations ZBProcCombinations
#endif

// old class name mapping
#ifndef PSS_CombinationPropertiesBP
    #define PSS_CombinationPropertiesBP ZBBPCombinationProperties
#endif

// forward class declarations
class PSS_CombinationPropertiesBP;

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
* Procedures for combinations
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcCombinations : public CObject
{
    DECLARE_SERIAL(PSS_ProcCombinations)

    public:
        typedef CCArray_T <PSS_CombinationPropertiesBP*, PSS_CombinationPropertiesBP*> ICombinationPropertiesSet;
        typedef Iterator_T<PSS_CombinationPropertiesBP*>                               ICombinationPropertiesIterator;

        PSS_ProcCombinations(CODSymbolComponent* pParent = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ProcCombinations(const PSS_ProcCombinations& other);

        virtual ~PSS_ProcCombinations();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_ProcCombinations& operator = (const PSS_ProcCombinations& other);

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual PSS_ProcCombinations* Dup() const;

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
        * Adds a new empty combination
        *@return the new added combination index, -1 on error
        */
        virtual int AddNewCombination();

        /**
        * Adds a combination
        *@param pProperty - the combination property to add
        *@return the new added combination index, -1 on error
        */
        virtual int AddCombination(PSS_CombinationPropertiesBP* pProperty);

        /**
        * Deletes a combination at index
        *@param index - the index
        *@return true on success, otherwise false
        */
        virtual bool DeleteCombination(std::size_t index);

        /**
        * Deletes a combination
        *@param pProperty - the combination property to delete
        *@return true on success, otherwise false
        */
        virtual bool DeleteCombination(PSS_CombinationPropertiesBP* pProperty);

        /**
        * Checks if the combination name exists
        *@return true if the combination name exists, otherwise false
        */
        virtual bool CombinationNameExist(const CString& name) const;

        /**
        * Gets the next valid combination name
        *@return the next valid combination name
        */
        virtual CString GetNextCombinationValidName() const;

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
        * Gets the combination properties containing a deliverable
        *@param deliverableName - the deliverable name to search
        *@return the combination properties containing the deliverable, NULL if not found or on error
        */
        virtual PSS_CombinationPropertiesBP* LocateCombinationOfDeliverable(const CString& deliverableName) const;

        /**
        * Gets the combination properties index containing a deliverable
        *@param deliverableName - the deliverable name to search
        *@return the combination properties index containing the deliverable, -1 if not found or on error
        */
        virtual int LocateCombinationIndexOfDeliverable(const CString& deliverableName) const;

        /**
        * Gets the combination properties containing a specific master
        *@param master - the master to search
        *@return the combination properties containing the specific master, NULL if not found or on error
        */
        virtual PSS_CombinationPropertiesBP* LocateCombinationOfMaster(const CString& master) const;

        /**
        * Gets the combination properties index containing a specific master
        *@param master - the master to search
        *@return the combination properties index containing the specific master, -1 if not found or on error
        */
        virtual int LocateCombinationIndexOfMaster(const CString& master) const;

        /**
        * Replaces an old deliverable by a new one
        *@param oldDeliverableName - the old deliverable name
        *@param newDeliverableName - the new deliverable name
        *@return true on success, otherwise false
        */
        virtual bool ReplaceDeliverable(const CString& oldDeliverableName, const CString& newDeliverableName);

        /**
        * Deletes a deliverable from all combinations, including the master
        *@param deliverableName - the deliverable name to search
        *@return true on success, otherwise false
        */
        virtual bool DeleteDeliverableFromAllCombinations(const CString& deliverableName);

        /**
        * Gets the combination set
        *@return the combination set
        */
        virtual inline ICombinationPropertiesSet& GetCombinationSet();

        /**
        * Gets the combination count
        *@return the combination count
        */
        virtual inline std::size_t GetCombinationCount() const;

        /**
        * Gets the property at index
        *@param index - the index
        *@return the property, NULL if not found or on error
        */
        virtual inline PSS_CombinationPropertiesBP* GetProperty(std::size_t index) const;

        /**
        * Removes all the combinations
        */
        virtual void RemoveAllCombinations();

        /**
        * Gets the combination name at index
        *@param index - the index
        *@return the combination name, empty string if not found or on error
        */
        virtual CString GetCombinationName(std::size_t index) const;

        /**
        * Sets the combination name at index
        *@param index - the index
        *@param value - the combination name
        */
        virtual void SetCombinationName(std::size_t index, const CString& value);

        /**
        * Gets the deliberable list at index
        *@param index - the index
        *@return the deliberable list, empty string if not found or on error
        */
        virtual CString GetCombinationDeliverables(std::size_t index) const;

        /**
        * Sets the deliberable list at index
        *@param index - the index
        *@param value - the deliberable list
        */
        virtual void SetCombinationDeliverables(std::size_t index, const CString& value);

        /**
        * Adds a deliverable to the deliberables at index
        *@param index - the index
        *@param value - the deliberable list
        *@return true on success, otherwise false
        */
        virtual bool AddCombinationDeliverable(std::size_t index, const CString& value);

        /**
        * Removes a deliverable from the deliberables at index
        *@param index - the index
        *@param value - the deliberable list
        *@return true on success, otherwise false
        */
        virtual bool RemoveCombinationDeliverable(std::size_t index, const CString& value);

        /**
        * Removes all the deliverables from the deliberable list at index
        *@param index - the index
        *@return true on success, otherwise false
        */
        virtual bool RemoveAllCombinationDeliverable(std::size_t index);

        /**
        * Gets the combination percentage at index
        *@param index - the index
        *@return the combination percentage
        */
        virtual float GetCombinationActivationPerc(std::size_t index) const;

        /**
        * Sets the combination percentage at index
        *@param index - the index
        *@param value - the combination percentage
        */
        virtual void SetCombinationActivationPerc(std::size_t index, const float value);

        /**
        * Gets the combination master name at index
        *@param index - the index
        *@return the combination master name at index, empty string of not found or on error
        */
        virtual CString GetCombinationMaster(std::size_t index) const;

        /**
        * Sets the combination master name at index
        *@param index - the index
        *@param value - the combination master name
        */
        virtual void SetCombinationMaster(std::size_t index, const CString& value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CODSymbolComponent*       m_pParent;
        ICombinationPropertiesSet m_Set;
};

//---------------------------------------------------------------------------
// PSS_ProcCombinations
//---------------------------------------------------------------------------
PSS_ProcCombinations::ICombinationPropertiesSet& PSS_ProcCombinations::GetCombinationSet()
{
    return m_Set;
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcCombinations::GetCombinationCount() const
{
    return m_Set.GetSize();
}
//---------------------------------------------------------------------------
PSS_CombinationPropertiesBP* PSS_ProcCombinations::GetProperty(std::size_t index) const
{
    if (index < GetCombinationCount())
        return m_Set.GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------

#endif
