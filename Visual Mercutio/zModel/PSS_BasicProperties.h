/****************************************************************************
 * ==> PSS_BasicProperties -------------------------------------------------*
 ****************************************************************************
 * Description : Provides the basic properties                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_BasicPropertiesH
#define PSS_BasicPropertiesH

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
#ifndef PSS_BasicProperties
    #define PSS_BasicProperties ZBBasicProperties
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
#define M_Symbol_Name_ID        1
#define M_Symbol_Description_ID 2
#define M_Symbol_Number_ID      3
#define M_Symbol_Risk_Level_ID  4
//---------------------------------------------------------------------------

/**
* Basic properties (i.e the symbol name, description, number and risk level)
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_BasicProperties : public CODIntProperty,
                                          public sfl::CPropertyContainer< IODPropertyContainer,
                                                                          CODPropertyAccessor<PSS_BasicProperties> >
{
    DECLARE_SERIAL(PSS_BasicProperties)

    /// Generated guid map
    BEGIN_GUID_MAP(PSS_BasicProperties)
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
            IE_CT_Symbol_Name        = 0x0001,
            IE_CT_Symbol_Description = 0x0002,
            IE_CT_Symbol_Number      = 0x0004,
            IE_CT_Symbol_Risk_Level  = 0x0008,
            IE_CT_Symbol_All         = OD_CHANGE_ALL
        };

        /**
        * Constructor
        *@param id - property identifier
        */
        PSS_BasicProperties(int id = ZS_BP_PROP_BASIC);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_BasicProperties(const PSS_BasicProperties& propBasic);

        virtual ~PSS_BasicProperties();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_BasicProperties& operator = (const PSS_BasicProperties& other);

        /**
        * Compares two basic model properties
        *@param other - other object to compare with
        *@return TRUE if the objects are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_BasicProperties& other) const;

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
        virtual void Merge(CODProperty* pProp, DWORD changeFlags = (DWORD)IEChangeType::IE_CT_Symbol_All);

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
        * Gets the symbol name
        *@return the symbol name
        */
        virtual inline CString GetSymbolName() const;

        /**
        * Sets the symbol name
        *@param value - the symbol name
        */
        virtual inline void SetSymbolName(const CString value);

        /**
        * Gets the symbol description
        *@return the symbol description
        */
        virtual inline CString GetSymbolDescription() const;

        /**
        * Sets the symbol description
        *@param value - the symbol description
        */
        virtual inline void SetSymbolDescription(const CString value);

        /**
        * Gets the symbol number
        *@return the symbol number
        */
        virtual inline int GetSymbolNumber() const;

        /**
        * Gets the symbol number as a string
        *@return the symbol number as a string
        */
        virtual CString GetSymbolNumberStr() const;

        /**
        * Sets the symbol number
        *@param value - the symbol number
        */
        virtual inline void SetSymbolNumber(const int value);

        /**
        * Sets the symbol number as a string
        *@param value - the symbol number as a string
        */
        virtual void SetSymbolNumber(const CString value);

        /**
        * Gets the symbol risk level
        *@return the symbol risk level
        */
        virtual inline CString GetSymbolRiskLevel() const;

        /**
        * Sets the symbol risk level
        *@param value - the symbol risk level
        */
        virtual inline void SetSymbolRiskLevel(const CString value);

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
        CString m_SymbolName;
        CString m_SymbolDescription;
        CString m_SymbolRiskLevel;
        int     m_SymbolNumber;

    private:
        /**
        * Registers the basic property meta-data
        *@return true on success, otherwise false
        */
        bool RegisterProperties();
};

//---------------------------------------------------------------------------
// PSS_BasicProperties
//---------------------------------------------------------------------------
ULONG PSS_BasicProperties::AddRef()
{
    return CODIntProperty::AddRef();
}
//---------------------------------------------------------------------------
ULONG PSS_BasicProperties::Release()
{
    return CODIntProperty::Release();
}
//---------------------------------------------------------------------------
CODProperty* PSS_BasicProperties::Dup()
{
    return new PSS_BasicProperties(*this);
}
//---------------------------------------------------------------------------
CString PSS_BasicProperties::GetSymbolName() const
{
    return m_SymbolName;
}
//---------------------------------------------------------------------------
void PSS_BasicProperties::SetSymbolName(const CString value)
{
    m_SymbolName = value;
}
//---------------------------------------------------------------------------
CString PSS_BasicProperties::GetSymbolDescription() const
{
    return m_SymbolDescription;
}
//---------------------------------------------------------------------------
void PSS_BasicProperties::SetSymbolDescription(const CString value)
{
    m_SymbolDescription = value;
}
//---------------------------------------------------------------------------
int PSS_BasicProperties::GetSymbolNumber() const
{
    return m_SymbolNumber;
}
//---------------------------------------------------------------------------
void PSS_BasicProperties::SetSymbolNumber(const int value)
{
    m_SymbolNumber = value;
}
//---------------------------------------------------------------------------
CString PSS_BasicProperties::GetSymbolRiskLevel() const
{
    return m_SymbolRiskLevel;
}
//---------------------------------------------------------------------------
void PSS_BasicProperties::SetSymbolRiskLevel(const CString riskLevel)
{
    m_SymbolRiskLevel = riskLevel;
}
//---------------------------------------------------------------------------

#endif
