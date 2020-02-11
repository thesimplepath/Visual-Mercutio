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

#define Z_CHANGE_RULE_LIST 0x0001

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define Z_RULE_LIST 1
//---------------------------------------------------------------------------

/**
* Rule list properties for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS ZBBPRuleListProperties : public CODIntProperty,
                                             public sfl::CPropertyContainer< IODPropertyContainer,
                                                                             CODPropertyAccessor<ZBBPRuleListProperties> >
{
    DECLARE_SERIAL(ZBBPRuleListProperties)

public:
    /**
    * Constructor
    *@param propID - property identifier
    */
    ZBBPRuleListProperties(int propID = ZS_BP_PROP_RULELIST);

    /**
    * Copy constructor
    *@param other - other object to copy from
    */
    ZBBPRuleListProperties(const ZBBPRuleListProperties& other);

    virtual ~ZBBPRuleListProperties();

    /**
    * Copy operator
    *@param other - other object to copy from
    *@return copy of itself
    */
    ZBBPRuleListProperties& operator = (const ZBBPRuleListProperties& other);

    /**
    * Checks if another set of properties is equal to this one
    *@param other - the other properties to compare with
    *@return TRUE if the properties are equals, otherwise FALSE
    */
    BOOL operator == (const ZBBPRuleListProperties other) const;

    //@cmember
    /* Makes a copy of this properties object. */
    virtual CODProperty* Dup();

    //@cmember
    /* Merges another set of properties with this one. */
    virtual void Merge(CODProperty* pProperty, DWORD dwChangeFlags = OD_CHANGE_ALL);

    //@cmember
    /* Determines if another set of properties is equal to this one. */
    virtual BOOL IsEqual(CODProperty* pProp);

    // The GUID map implements the QueryGuid function
    BEGIN_GUID_MAP(ZBBPRuleListProperties)
        GUID_ENTRY(IODPropertyContainer)
        GUID_ENTRY(sfl::IPropertyContainer)
        GUID_CHAIN_ENTRY(CODIntProperty)
    END_GUID_MAP

    //@cmember
    /* Add a reference to this object. */
    ULONG STDMETHODCALLTYPE AddRef();
    //@cmember
    /* Release a reference to this object. */
    ULONG STDMETHODCALLTYPE Release();

    /////////////////////////////////////////////////////////////////////////
    // IODPropertyContainer interface

    /**
    * Checks if the identifier is in the property identifier range
    *@param id - the identifier to check
    *@return TRUE if the identifier is in the range, otherwise FALSE
    */
    virtual BOOL CompareId(const int nId) const;

    //@cmember
    /* Gets the task list. */
    CString GetRuleList() const;

    //@cmember
    /* Sets the task list. */
    void SetRuleList(LPCTSTR lpszValue);

    //@cmember
    /* Gets the value of the given string property. */
    virtual BOOL GetValue(const int nPropId, CString& strValue) const;

    //@cmember
    /* Gets the value of the given integer property. */
    virtual BOOL GetValue(const int nPropId, int& nValue) const;

    //@cmember
    /* Gets the value of the given unsigned integer property. */
    virtual BOOL GetValue(const int nPropId, UINT& nValue) const;

    //@cmember
    /* Gets the value of the given DWORD property. */
    virtual BOOL GetValue(const int nPropId, DWORD& dwValue) const;

    //@cmember
    /* Gets the value of the given float property. */
    virtual BOOL GetValue(const int nPropId, float& fValue) const;

    //@cmember
    /* Sets the value of the given string property. */
    virtual BOOL SetValue(const int nPropId, LPCTSTR lpszValue);

    //@cmember
    /* Sets the value of the given integer property. */
    virtual BOOL SetValue(const int nPropId, const int nValue);

    //@cmember
    /* Sets the value of the given unsigned integer property. */
    virtual BOOL SetValue(const int nPropId, const UINT nValue);

    //@cmember
    /* Sets the value of the given unsigned DWORD property. */
    virtual BOOL SetValue(const int nPropId, const DWORD dwValue);

    //@cmember
    /* Sets the value of the given float property. */
    virtual BOOL SetValue(const int nPropId, const float fValue);

    //@cmember
    /* Serializes the line properties. */
    virtual void Serialize(CArchive& ar);

    // Implementation
public:

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

private:

    /* Additional mutators for use with CODIntPropertyAccessor */
    void SetRuleListEx(const CString value);

    /* Registers the fill property meta-data. */
    bool RegisterProperties();

    // Attributes
protected:

    //@cmember
    /* The task list. */
    CString m_RuleList;
};

/////////////////////////////////////////////////////////////////////////////
// ZBBPRuleListProperties inline methods

//@mfunc Add a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBPRuleListProperties::AddRef()
{
    return CODIntProperty::AddRef();
}

//@mfunc Release a reference to this object.
//@rdesc New reference count value.
inline ULONG ZBBPRuleListProperties::Release()
{
    return CODIntProperty::Release();
}

//@mfunc Gets the task list.
//@rdesc The task list.
inline CString ZBBPRuleListProperties::GetRuleList() const
{
    return m_RuleList;
}

//@mfunc Creates a copy of this property.
//@rdesc A pointer to the new copy of the property. The caller is responsible
// for cleaning up this object.
inline CODProperty* ZBBPRuleListProperties::Dup()
{
    return new ZBBPRuleListProperties(*this);
}

#endif
