/****************************************************************************
 * ==> PSS_RuleListPropertiesBP --------------------------------------------*
 ****************************************************************************
 * Description : Provides the rule list properties for banking process      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_RuleListPropertiesBPH
#define PSS_RuleListPropertiesBPH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_RuleListPropertiesBP
    #define PSS_RuleListPropertiesBP ZBBPRuleListProperties
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
#define M_Rule_List_ID 1
//---------------------------------------------------------------------------

/**
* Rule list properties for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_RuleListPropertiesBP : public CODIntProperty,
                                               public sfl::CPropertyContainer< IODPropertyContainer,
                                                                               CODPropertyAccessor<PSS_RuleListPropertiesBP> >
{
    DECLARE_SERIAL(PSS_RuleListPropertiesBP)

    /// generated guid map
    BEGIN_GUID_MAP(PSS_RuleListPropertiesBP)
        GUID_ENTRY(IODPropertyContainer)
        GUID_ENTRY(sfl::IPropertyContainer)
        GUID_CHAIN_ENTRY(CODIntProperty)
    END_GUID_MAP

    public:
        /**
        * Change type
        *@note These items may be combined
        */
        enum class IEChangeType
        {
            IE_CT_Change_Rule_List = 0x0001,
            IE_CT_All              = OD_CHANGE_ALL
        };

        /**
        * Constructor
        *@param propID - property identifier
        */
        PSS_RuleListPropertiesBP(int propID = ZS_BP_PROP_RULELIST);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_RuleListPropertiesBP(const PSS_RuleListPropertiesBP& other);

        virtual ~PSS_RuleListPropertiesBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_RuleListPropertiesBP& operator = (const PSS_RuleListPropertiesBP& other);

        /**
        * Checks if another set of properties is equal to this one
        *@param other - the other properties to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_RuleListPropertiesBP& other) const;

        /**
        * Adds a reference to this object
        *@return the updated reference count
        */
        virtual inline ULONG STDMETHODCALLTYPE AddRef();

        /**
        * Releases a reference from this object
        *@return the updated reference count
        */
        virtual inline ULONG STDMETHODCALLTYPE Release();

        /**
        * Makes a copy of this object
        *@return a copy of this object, NULL on error
        */
        virtual inline CODProperty* Dup();

        /**
        * Merges another property set with this one
        *@param pProp - other property set to merge with
        *@param changeFlags - the change flags
        */
        virtual void Merge(CODProperty* pProp, DWORD changeFlags = (DWORD)IEChangeType::IE_CT_All);

        /**
        * Checks if the identifier is in the property identifier range
        *@param id - the identifier to check
        *@return TRUE if the identifier is in the range, otherwise FALSE
        */
        virtual BOOL CompareId(const int id) const;

        /**
        * Checks if another set of properties is equal to this one
        *@param pProp - other property set to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        virtual BOOL IsEqual(CODProperty* pProp);

        /**
        * Gets the rule list
        *@return the rule list
        */
        virtual inline CString GetRuleList() const;

        /**
        * Sets the rule list
        *@param pValue - the rule list
        */
        virtual void SetRuleList(LPCTSTR pValue);

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
        CString m_RuleList;

    private:
        /**
        * Sets the rule list (advanced)
        *@param value - the rule list
        */
        void SetRuleListEx(const CString value);

        /**
        * Registers the basic property meta-data
        *@return true on success, otherwise false
        */
        bool RegisterProperties();
};

//---------------------------------------------------------------------------
// PSS_RuleListPropertiesBP
//---------------------------------------------------------------------------
ULONG PSS_RuleListPropertiesBP::AddRef()
{
    return CODIntProperty::AddRef();
}
//---------------------------------------------------------------------------
ULONG PSS_RuleListPropertiesBP::Release()
{
    return CODIntProperty::Release();
}
//---------------------------------------------------------------------------
CODProperty* PSS_RuleListPropertiesBP::Dup()
{
    return new PSS_RuleListPropertiesBP(*this);
}
//---------------------------------------------------------------------------
CString PSS_RuleListPropertiesBP::GetRuleList() const
{
    return m_RuleList;
}
//---------------------------------------------------------------------------

#endif
