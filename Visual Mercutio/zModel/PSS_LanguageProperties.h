/****************************************************************************
 * ==> PSS_LanguageProperties ----------------------------------------------*
 ****************************************************************************
 * Description : Provides the language properties                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_LanguagePropertiesH
#define PSS_LanguagePropertiesH

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
#ifndef PSS_LanguageProperties
    #define PSS_LanguageProperties ZBLanguageProp
#endif

// resources
#include "PSS_PropIDs.h"
#include "PSS_LanguageDefs.h"

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
#define M_Language_ID 1
//---------------------------------------------------------------------------

/**
* Language properties
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_LanguageProperties : public CODIntProperty,
                                             public sfl::CPropertyContainer< IODPropertyContainer,
                                                                             CODPropertyAccessor<PSS_LanguageProperties> >
{
    DECLARE_SERIAL(PSS_LanguageProperties)

    BEGIN_GUID_MAP(PSS_LanguageProperties)
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
            IE_CT_Language = 0x0001,
            IE_CT_All      = OD_CHANGE_ALL
        };

        /**
        * Constructor
        *@param id - property identifier
        */
        PSS_LanguageProperties(int nId = ZS_BP_PROP_LANGUAGE);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_LanguageProperties(const PSS_LanguageProperties& other);

        virtual ~PSS_LanguageProperties();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_LanguageProperties& operator = (const PSS_LanguageProperties& other);

        /**
        * Compares two basic model properties
        *@param other - other object to compare with
        *@return TRUE if the objects are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_LanguageProperties& other) const;

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
        virtual void Merge(CODProperty* pProp, DWORD changeFlags = (DWORD)IEChangeType::IE_CT_All);

        /**
        * Gets the language
        *@return the language
        */
        virtual inline ELanguage GetLanguage() const;

        /**
        * Gets the language as an integer value
        *@return the language as an integer value
        */
        virtual inline int GetLanguageInt() const;

        /**
        * Sets the language
        *@param value - the language
        */
        virtual inline void SetLanguage(ELanguage value);

        /**
        * Sets the language from an integer value
        *@param value - the language from an integer value
        */
        virtual inline void SetLanguageInt(const int value);

        /**
        * Checks if the identifier is in the property identifier range
        *@param id - the identifier to check
        *@return TRUE if the identifier is in the range, otherwise FALSE
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
        ELanguage m_Language;

    private:
        /**
        * Registers the basic properties meta-data
        *@return true on success, otherwise false
        */
        bool RegisterProperties();
};

//---------------------------------------------------------------------------
// PSS_LanguageProperties
//---------------------------------------------------------------------------
ULONG PSS_LanguageProperties::AddRef()
{
    return CODIntProperty::AddRef();
}
//---------------------------------------------------------------------------
ULONG PSS_LanguageProperties::Release()
{
    return CODIntProperty::Release();
}
//---------------------------------------------------------------------------
CODProperty* PSS_LanguageProperties::Dup()
{
    return new PSS_LanguageProperties(*this);
}
//---------------------------------------------------------------------------
ELanguage PSS_LanguageProperties::GetLanguage() const
{
    return m_Language;
}
//---------------------------------------------------------------------------
int PSS_LanguageProperties::GetLanguageInt() const
{
    return static_cast<int>(m_Language);
}
//---------------------------------------------------------------------------
void PSS_LanguageProperties::SetLanguage(ELanguage value)
{
    m_Language = value;
}
//---------------------------------------------------------------------------
void PSS_LanguageProperties::SetLanguageInt(const int value)
{
    m_Language = static_cast<ELanguage>(value);
}
//---------------------------------------------------------------------------

#endif
