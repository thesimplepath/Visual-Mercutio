/****************************************************************************
 * ==> PSS_ProcRisk --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides the procedures for risks                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcRiskH
#define PSS_ProcRiskH

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
#ifndef PSS_ProcRisk
    #define PSS_ProcRisk ZBProcRisk
#endif

// old class name mapping
#ifndef PSS_RiskPropertiesBP
    #define PSS_RiskPropertiesBP ZBBPRiskProperties
#endif

class PSS_RiskPropertiesBP;

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
* Procedures for risks
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcRisk : public CObject
{
    DECLARE_SERIAL(PSS_ProcRisk)

    public:
        typedef CCArray_T <PSS_RiskPropertiesBP*, PSS_RiskPropertiesBP*> IRiskPropertiesSet;
        typedef Iterator_T<PSS_RiskPropertiesBP*>                        IRiskPropertiesIterator;

        /**
        * Constructor
        *@param pParent - the parent component
        */
        PSS_ProcRisk(CODSymbolComponent* pParent = NULL);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ProcRisk(const PSS_ProcRisk& other);

        virtual ~PSS_ProcRisk();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_ProcRisk& operator = (const PSS_ProcRisk& other);

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual PSS_ProcRisk* Dup() const;

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
        * Adds a new empty risk
        *@return the new added risk index, -1 on error
        */
        virtual int AddNewRisk();

        /**
        * Adds a risk
        *@param pProperty - the risk property to add
        *@return the new added risk index, -1 on error
        */
        virtual int AddRisk(PSS_RiskPropertiesBP* pProperty);

        /**
        * Deletes a risk at index
        *@param index - the index
        *@return true on success, otherwise false
        */
        virtual bool DeleteRisk(std::size_t index);

        /**
        * Deletes a risk
        *@param pProperty - the risk property to delete
        *@return true on success, otherwise false
        */
        virtual bool DeleteRisk(PSS_RiskPropertiesBP* pProperty);

        /**
        * Checks if the risk name exists
        *@return true if the risk name exists, otherwise false
        */
        virtual bool RiskNameExist(const CString& name) const;

        /**
        * Gets the next valid risk name
        *@return the next valid risk name
        */
        virtual CString GetNextRiskValidName() const;

        /**
        * Gets the risk set
        *@return the risk set
        */
        virtual inline IRiskPropertiesSet& GetRiskSet();

        /**
        * Gets the risk count
        *@return the risk count
        */
        virtual inline std::size_t GetRiskCount() const;

        /**
        * Gets the property at index
        *@param index - the index
        *@return the property, NULL if not found or on error
        */
        virtual inline PSS_RiskPropertiesBP* GetProperty(std::size_t index) const;

        /**
        * Removes all the risks
        */
        virtual void RemoveAllRisks();

        /**
        * Gets the risk name at index
        *@param index - the index
        *@return the risk name, empty string if not found or on error
        */
        virtual CString GetRiskName(std::size_t index) const;

        /**
        * Sets the risk name at index
        *@param index - the index
        *@param value - the risk name
        */
        virtual void SetRiskName(std::size_t index, const CString& value);

        /**
        * Gets the risk description at index
        *@param index - the index
        *@return the risk description, empty string if not found or on error
        */
        virtual CString GetRiskDesc(std::size_t index) const;

        /**
        * Sets the risk description at index
        *@param index - the index
        *@param value - the risk description
        */
        virtual void SetRiskDesc(std::size_t index, const CString& value);

        /**
        * Gets the risk type at index
        *@param index - the index
        *@return the risk type, empty string if not found or on error
        */
        virtual CString GetRiskType(std::size_t index) const;

        /**
        * Sets the risk type at index
        *@param index - the index
        *@param value - the risk rype
        */
        virtual void SetRiskType(std::size_t index, const CString& value);

        /**
        * Gets the risk impact at index
        *@param index - the index
        *@return the risk impact, empty string if not found or on error
        */
        virtual int GetRiskImpact(std::size_t index) const;

        /**
        * Sets the risk impact at index
        *@param index - the index
        *@param value - the risk impact
        */
        virtual void SetRiskImpact(std::size_t index, int value);

        /**
        * Gets the risk probability at index
        *@param index - the index
        *@return the risk probability, empty string if not found or on error
        */
        virtual int GetRiskProbability(std::size_t index) const;

        /**
        * Sets the risk probability at index
        *@param index - the index
        *@param value - the risk probability
        */
        virtual void SetRiskProbability(std::size_t index, int value);

        /**
        * Gets the risk severity at index
        *@param index - the index
        *@return the risk severity, empty string if not found or on error
        */
        virtual int GetRiskSeverity(std::size_t index) const;

        /**
        * Sets the risk severity at index
        *@param index - the index
        *@param value - the risk severity
        */
        virtual void SetRiskSeverity(std::size_t index, int value);

        /**
        * Gets the risk unitary estimation at index
        *@param index - the index
        *@return the risk unitary estimation, empty string if not found or on error
        */
        virtual float GetRiskUE(std::size_t index) const;

        /**
        * Sets the risk unitary estimation at index
        *@param index - the index
        *@param value - the risk unitary estimation
        */
        virtual void SetRiskUE(std::size_t index, float Value);

        /**
        * Gets the risk annual operating loss (perte operationnelle annuelle in French) at index
        *@param index - the index
        *@return the risk annual operating loss, empty string if not found or on error
        */
        virtual float GetRiskPOA(std::size_t index) const;

        /**
        * Sets the risk annual operating loss (perte operationnelle annuelle in French) at index
        *@param index - the index
        *@param value - the risk annual operating loss
        */
        virtual void SetRiskPOA(std::size_t index, float value);

        /**
        * Gets the risk action at index
        *@param index - the index
        *@return the risk action, empty string if not found or on error
        */
        virtual bool GetRiskAction(std::size_t index) const;

        /**
        * Sets the risk action at index
        *@param index - the index
        *@param value - the risk action
        */
        virtual void SetRiskAction(std::size_t index, bool value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CODSymbolComponent* m_pParent;
        IRiskPropertiesSet  m_Set;
};

//---------------------------------------------------------------------------
// PSS_ProcRisk
//---------------------------------------------------------------------------
PSS_ProcRisk::IRiskPropertiesSet& PSS_ProcRisk::GetRiskSet()
{
    return m_Set;
}
//---------------------------------------------------------------------------
std::size_t PSS_ProcRisk::GetRiskCount() const
{
    return m_Set.GetSize();
}
//---------------------------------------------------------------------------
PSS_RiskPropertiesBP* PSS_ProcRisk::GetProperty(std::size_t index) const
{
    if (index < GetRiskCount())
        return m_Set.GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------

#endif
