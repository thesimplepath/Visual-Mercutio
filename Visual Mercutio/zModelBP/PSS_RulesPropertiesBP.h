/****************************************************************************
 * ==> PSS_RulesPropertiesBP -----------------------------------------------*
 ****************************************************************************
 * Description : Provides the rule properties for banking process           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RulesPropertiesBPH
#define PSS_RulesPropertiesBPH

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
#ifndef PSS_RulesPropertiesBP
    #define PSS_RulesPropertiesBP ZBBPRulesProperties
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
#define M_Rule_Name_ID        1
#define M_Rule_Description_ID 2
#define M_Rule_Identifier_ID  3
//---------------------------------------------------------------------------

/**
* Rule properties for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_RulesPropertiesBP : public CObject
{
    DECLARE_SERIAL(PSS_RulesPropertiesBP)

    public:
        /**
        * Change type
        *@note These items may be combined
        */
        enum class IEChangeType
        {
            IE_CT_Change_Rule_Name        = 0x0001,
            IE_CT_Change_Rule_Description = 0x0002,
            IE_CT_Change_Rule_GUID        = 0x0004,
            IE_CT_All                     = OD_CHANGE_ALL
        };

        PSS_RulesPropertiesBP();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_RulesPropertiesBP(const PSS_RulesPropertiesBP& other);

        virtual ~PSS_RulesPropertiesBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_RulesPropertiesBP& operator = (const PSS_RulesPropertiesBP& other);

        /**
        * Checks if another set of properties is equal to this one
        *@param other - the other properties to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_RulesPropertiesBP& other) const;

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual inline PSS_RulesPropertiesBP* Dup() const;

        /**
        * Merges another property set with this one
        *@param pProp - other property set to merge with
        *@param changeFlags - the change flags
        */
        virtual void Merge(PSS_RulesPropertiesBP* pProp, DWORD changeFlags = (DWORD)IEChangeType::IE_CT_All);

        /**
        * Checks if another set of properties is equal to this one
        *@param pProp - other property set to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        virtual BOOL IsEqual(PSS_RulesPropertiesBP* pProp);

        /**
        * Gets the rule name
        *@return the rule name
        */
        virtual inline CString GetRuleName() const;

        /**
        * Sets the rule name
        *@param pValue - the rule name
        */
        virtual void SetRuleName(LPCTSTR pValue);

        /**
        * Gets the rule description
        *@return the rule description
        */
        virtual inline CString GetRuleDescription() const;

        /**
        * Sets the rule description
        *@param pValue - the rule description
        */
        virtual void SetRuleDescription(LPCTSTR pValue);

        /**
        * Gets the rule GUID
        *@return the rule GUID
        */
        virtual inline CString GetRuleGUID() const;

        /**
        * Sets the rule GUID
        *@param pValue - the rule GUID
        */
        virtual void SetRuleGUID(LPCTSTR pValue);

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
        CString m_RuleName;
        CString m_RuleDescription;
        CString m_RuleGUID;

    private:
        /**
        * Sets the rule name (extended)
        *@param value - the rule name
        */
        void SetRuleNameEx(const CString value);

        /**
        * Sets the rule description (extended)
        *@param value - the rule description
        */
        void SetRuleDescriptionEx(const CString value);

        /**
        * Sets the rule GUID (extended)
        *@param value - the rule GUID
        */
        void SetRuleGUIDEx(const CString value);
};

//---------------------------------------------------------------------------
// PSS_RulesPropertiesBP
//---------------------------------------------------------------------------
PSS_RulesPropertiesBP* PSS_RulesPropertiesBP::Dup() const
{
    return new PSS_RulesPropertiesBP(*this);
}
//---------------------------------------------------------------------------
CString PSS_RulesPropertiesBP::GetRuleName() const
{
    return m_RuleName;
}
//---------------------------------------------------------------------------
CString PSS_RulesPropertiesBP::GetRuleDescription() const
{
    return m_RuleDescription;
}
//---------------------------------------------------------------------------
CString PSS_RulesPropertiesBP::GetRuleGUID() const
{
    return m_RuleGUID;
}
//---------------------------------------------------------------------------

#endif
