/****************************************************************************
 * ==> PSS_ProcessPropertiesBP ---------------------------------------------*
 ****************************************************************************
 * Description : Provides the process properties for banking process        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessPropertiesBPH
#define PSS_ProcessPropertiesBPH

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
#ifndef PSS_ProcessPropertiesBP
    #define PSS_ProcessPropertiesBP ZBBPProcessProperties
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
#define M_Management_Case_ID 1
//---------------------------------------------------------------------------

/**
* Process properties for banking process
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessPropertiesBP : public CODIntProperty,
                                              public sfl::CPropertyContainer<IODPropertyContainer,
                                                                             CODPropertyAccessor<PSS_ProcessPropertiesBP> >
{
    DECLARE_SERIAL(PSS_ProcessPropertiesBP)

    /// generated guid map
    BEGIN_GUID_MAP(PSS_ProcessPropertiesBP)
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
            IE_CT_Change_Management_Case = 0x0001,
            IE_CT_All                    = OD_CHANGE_ALL
        };

        /**
        * Constructor
        *@param propID - property identifier
        */
        PSS_ProcessPropertiesBP(int propID = ZS_BP_PROP_PROCESS);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ProcessPropertiesBP(const PSS_ProcessPropertiesBP& other);

        virtual ~PSS_ProcessPropertiesBP();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_ProcessPropertiesBP& operator = (const PSS_ProcessPropertiesBP& other);

        /**
        * Checks if another set of properties is equal to this one
        *@param other - the other properties to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_ProcessPropertiesBP& other) const;

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
        * Makes a copy of this properties object
        *@return a copy of this properties object, NULL on error
        */
        virtual inline CODProperty* Dup();

        /**
        * Merges another property set with this one
        *@param pProp - other property set to merge with
        *@param changeFlags - the change flags
        */
        virtual void Merge(CODProperty* pProp, DWORD changeFlags = OD_CHANGE_ALL);

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
        * Gets the management case
        *@return the management case
        */
        virtual inline CString GetManagementCase() const;

        /**
        * Sets the management case
        *@param pValue - the management case
        */
        virtual void SetManagementCase(LPCTSTR pValue);

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
        CString m_ManagementCase;

    private:
        /**
        * Sets the management case (advanced)
        *@param pValue - the management case
        */
        void SetManagementCaseEx(const CString name);

        /**
        * Registers the basic property meta-data
        *@return true on success, otherwise false
        */
        bool RegisterProperties();
};

//---------------------------------------------------------------------------
// PSS_ProcessPropertiesBP
//---------------------------------------------------------------------------
ULONG PSS_ProcessPropertiesBP::AddRef()
{
    return CODIntProperty::AddRef();
}
//---------------------------------------------------------------------------
ULONG PSS_ProcessPropertiesBP::Release()
{
    return CODIntProperty::Release();
}
//---------------------------------------------------------------------------
CODProperty* PSS_ProcessPropertiesBP::Dup()
{
    return new PSS_ProcessPropertiesBP(*this);
}
//---------------------------------------------------------------------------
CString PSS_ProcessPropertiesBP::GetManagementCase() const
{
    return m_ManagementCase;
}
//---------------------------------------------------------------------------

#endif
