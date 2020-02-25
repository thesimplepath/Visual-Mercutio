/****************************************************************************
 * ==> PSS_CombinationPropertiesBP -----------------------------------------*
 ****************************************************************************
 * Description : Provides the combination properties for banking process    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_CombinationPropertiesBPH
#define PSS_CombinationPropertiesBPH

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
#ifndef PSS_CombinationPropertiesBP
    #define PSS_CombinationPropertiesBP ZBBPCombinationProperties
#endif

// resources
#include "PSS_PropIDs.h"

#ifdef _ZMODELBPEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define M_Combination_Name_ID            1
#define M_Combination_Deliverables_ID    2
#define M_Combination_Activation_Perc_ID 3
#define M_Combination_Master_ID          4
//---------------------------------------------------------------------------

/**
* Combination properties for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_CombinationPropertiesBP : public CObject
{
    DECLARE_SERIAL(PSS_CombinationPropertiesBP)

    public:
        /**
        * Change type
        *@note These items may be combinated
        */
        enum IEChangeType
        {
            IE_CT_Change_Combination_Name            = 0x0001,
            IE_CT_Change_Combination_Deliverables    = 0x0002,
            IE_CT_Change_Combination_Activation_Perc = 0x0004,
            IE_CT_Change_Combination_Master          = 0x0008,
            IE_CT_All                                = OD_CHANGE_ALL
        };

        PSS_CombinationPropertiesBP();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_CombinationPropertiesBP(const PSS_CombinationPropertiesBP& other);

        virtual ~PSS_CombinationPropertiesBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_CombinationPropertiesBP& operator = (const PSS_CombinationPropertiesBP& other);

        /**
        * Checks if another set of properties is equal to this one
        *@param other - the other properties to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_CombinationPropertiesBP& other) const;

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual inline PSS_CombinationPropertiesBP* Dup() const;

        /**
        * Merges another property set with this one
        *@param pProp - other property set to merge with
        *@param changeFlags - the change flags
        */
        virtual void Merge(PSS_CombinationPropertiesBP* pProp, DWORD changeFlags = IE_CT_All);

        /**
        * Checks if another set of properties is equal to this one
        *@param pProp - other property set to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        virtual BOOL IsEqual(PSS_CombinationPropertiesBP* pProp);

        /**
        * Gets the combination name
        *@return the combination name
        */
        virtual inline CString GetCombinationName() const;

        /**
        * Sets the combination name
        *@param pValue - the combination name
        */
        virtual void SetCombinationName(LPCTSTR pValue);

        /**
        * Gets the deliberable list
        *@return the deliberable list
        */
        virtual inline CString GetCombinationDeliverables() const;

        /**
        * Sets the deliberable list
        *@param pValue - the deliberable list
        */
        virtual void SetCombinationDeliverables(LPCTSTR pValue);

        /**
        * Gets the combination activation percentage
        *@return the combination activation percentage
        */
        virtual inline float GetCombinationActivationPerc() const;

        /**
        * Sets the combination activation percentage
        *@param value - the combination activation percentage
        */
        virtual inline void SetCombinationActivationPerc(const float value);

        /**
        * Checks if the combination contains deliverables
        *@return true if combination contains deliverables, otherwise false
        */
        virtual bool IsDeliverableInCombination(LPCTSTR pValue);

        /**
        * Gets the combination master name
        *@return the combination master name
        */
        virtual inline CString GetCombinationMaster() const;

        /**
        * Sets the combination master name
        *@param pValue - the combination master name
        */
        virtual void SetCombinationMaster(LPCTSTR pValue);

        /**
        * Gets the property value
        *@param propId - the property identifier
        *@param[out] value - the property value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL GetValue(const int propId, int&     value) const;
        virtual BOOL GetValue(const int propId, UINT&    value) const;
        virtual BOOL GetValue(const int propId, DWORD&   value) const;
        virtual BOOL GetValue(const int propId, float&   value) const;
        virtual BOOL GetValue(const int propId, CString& value) const;

        /**
        * Sets the property value
        *@param propId - the property identifier
        *@param value/pValue - the property value
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetValue(const int propId, const int   value);
        virtual BOOL SetValue(const int propId, const UINT  value);
        virtual BOOL SetValue(const int propId, const DWORD value);
        virtual BOOL SetValue(const int propId, const float value);
        virtual BOOL SetValue(const int propId, LPCTSTR     pValue);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        CString m_CombinationName;
        CString m_CombinationDeliverables;
        CString m_CombinationMaster;
        float   m_CombinationActivationPerc;

    private:
        /**
        * Sets the combination name (advanced)
        *@param pValue - the combination name
        */
        void SetCombinationNameEx(const CString& value);

        /**
        * Sets the deliberable list (advanced)
        *@param pValue - the deliberable list
        */
        void SetCombinationDeliverablesEx(const CString& value);

        /**
        * Sets the combination master name (advanced)
        *@param pValue - the combination master name
        */
        void SetCombinationMasterEx(const CString& value);
};

//---------------------------------------------------------------------------
// PSS_CombinationPropertiesBP
//---------------------------------------------------------------------------
PSS_CombinationPropertiesBP* PSS_CombinationPropertiesBP::Dup() const
{
    return new PSS_CombinationPropertiesBP(*this);
}
//---------------------------------------------------------------------------
CString PSS_CombinationPropertiesBP::GetCombinationName() const
{
    return m_CombinationName;
}
//---------------------------------------------------------------------------
CString PSS_CombinationPropertiesBP::GetCombinationDeliverables() const
{
    return m_CombinationDeliverables;
}
//---------------------------------------------------------------------------
float PSS_CombinationPropertiesBP::GetCombinationActivationPerc() const
{
    return m_CombinationActivationPerc;
}
//---------------------------------------------------------------------------
void PSS_CombinationPropertiesBP::SetCombinationActivationPerc(const float value)
{
    m_CombinationActivationPerc = value;
}
//---------------------------------------------------------------------------
CString PSS_CombinationPropertiesBP::GetCombinationMaster() const
{
    return m_CombinationMaster;
}
//---------------------------------------------------------------------------

#endif
