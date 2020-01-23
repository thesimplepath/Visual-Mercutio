/****************************************************************************
 * ==> PSS_BasicModelProperties --------------------------------------------*
 ****************************************************************************
 * Description : Provides the basic model properties                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BasicModelPropertiesH
#define PSS_BasicModelPropertiesH

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
#ifndef PSS_BasicModelProperties
    #define PSS_BasicModelProperties ZBBasicModelProperties
#endif

// processsoft
#include "PSS_PropIDs.h"

#ifdef _ZMODELEXPORT
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
#define M_Model_Name_ID        1
#define M_Model_Description_ID 2
//---------------------------------------------------------------------------

/**
* Basic model properties (i.e its name and description)
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BasicModelProperties : public CODIntProperty,
                                               public sfl::CPropertyContainer< IODPropertyContainer,
                                                                               CODPropertyAccessor<PSS_BasicModelProperties> >
{
    DECLARE_SERIAL(PSS_BasicModelProperties)

    /// Generated guid map
    BEGIN_GUID_MAP(PSS_BasicModelProperties)
        GUID_ENTRY(IODPropertyContainer)
        GUID_ENTRY(sfl::IPropertyContainer)
        GUID_CHAIN_ENTRY(CODIntProperty)
    END_GUID_MAP

    public:
        /**
        * Change type
        *@note These items may be combinated
        */
        enum IEChangeType
        {
            IE_CT_Model_Name        = 0x0001,
            IE_CT_Model_Description = 0x0002,
            IE_CT_All               = OD_CHANGE_ALL
        };

        /**
        * Constructor
        *@param id - property identifier
        */
        PSS_BasicModelProperties(int id = ZS_BP_PROP_MODEL_BASIC);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_BasicModelProperties(const PSS_BasicModelProperties& other);

        virtual ~PSS_BasicModelProperties();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_BasicModelProperties& operator = (const PSS_BasicModelProperties& other);

        /**
        * Compares two basic model properties
        *@param other - other object to compare with
        *@return TRUE if the objects are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_BasicModelProperties& propBasic) const;

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
        *@return the duplicated object, NULL on error
        */
        virtual inline CODProperty* Dup();

        /**
        * Merges another set of properties with this one
        *@param pProp - the property set to merge with
        *@param changeFlags - the change flags to apply
        */
        virtual void Merge(CODProperty* pProp, DWORD changeType = IE_CT_All);

        /**
        * Gets the model name
        *@return the model name
        */
        virtual inline CString GetModelName() const;

        /**
        * Sets the model name
        *@param value - the model name
        */
        virtual inline void SetModelName(const CString value);

        /**
        * Gets the model description
        *@return the model description
        */
        virtual inline CString GetModelDescription() const;

        /**
        * Sets the model description
        *@param value - the model description
        */
        virtual inline void SetModelDescription(const CString value);

        /**
        * Compares the property identifier with another identifier
        *@param id - the property identifier to compare with
        *@return TRUE if the property identifiers are equals, otherwise FALSE
        */
        virtual BOOL CompareId(const int id) const;

        /**
        * Determines if another set of properties is equal to this one
        *@param pProp - the property set to compare with
        */
        virtual BOOL IsEqual(CODProperty* pProp);

        /**
        * Gets the property value
        *@param propID - the property identifier for which the value should be get
        *@param[out] value - the property value, in case the function success
        *@return TRUE on success, otherwise FASLE
        */
        virtual BOOL GetValue(const int propID, int&     value) const;
        virtual BOOL GetValue(const int propID, UINT&    value) const;
        virtual BOOL GetValue(const int propID, DWORD&   value) const;
        virtual BOOL GetValue(const int propID, float&   value) const;
        virtual BOOL GetValue(const int propID, CString& value) const;

        /**
        * Sets the property value
        *@param propID - the property identifier for which the value should be set
        *@param value/pValue - the property value to set
        *@return TRUE on success, otherwise FASLE
        */
        virtual BOOL SetValue(const int propID, const int   value);
        virtual BOOL SetValue(const int propID, const UINT  value);
        virtual BOOL SetValue(const int propID, const DWORD value);
        virtual BOOL SetValue(const int propID, const float value);
        virtual BOOL SetValue(const int propID, LPCTSTR     pValue);

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
        CString m_ModelName;
        CString m_ModelDescription;

    private:
        /**
        * Registers the basic property meta-data
        *@return true on success, otherwise false
        */
        bool RegisterProperties();
};

//---------------------------------------------------------------------------
// PSS_BasicModelProperties
//---------------------------------------------------------------------------
ULONG PSS_BasicModelProperties::AddRef()
{
    return CODIntProperty::AddRef();
}
//---------------------------------------------------------------------------
ULONG PSS_BasicModelProperties::Release()
{
    return CODIntProperty::Release();
}
//---------------------------------------------------------------------------
CODProperty* PSS_BasicModelProperties::Dup()
{
    return new PSS_BasicModelProperties(*this);
}
//---------------------------------------------------------------------------
CString PSS_BasicModelProperties::GetModelName() const
{
    return m_ModelName;
}
//---------------------------------------------------------------------------
void PSS_BasicModelProperties::SetModelName(const CString value)
{
    m_ModelName = value;
}
//---------------------------------------------------------------------------
CString PSS_BasicModelProperties::GetModelDescription() const
{
    return m_ModelDescription;
}
//---------------------------------------------------------------------------
void PSS_BasicModelProperties::SetModelDescription(const CString value)
{
    m_ModelDescription = value;
}
//---------------------------------------------------------------------------

#endif
