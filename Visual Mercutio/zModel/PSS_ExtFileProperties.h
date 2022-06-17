/****************************************************************************
 * ==> PSS_ExtFileProperties -----------------------------------------------*
 ****************************************************************************
 * Description : Provides external file properties                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ExtFilePropertiesH
#define PSS_ExtFilePropertiesH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_ExtFileProperties
    #define PSS_ExtFileProperties ZBExtFileProperties
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
#define M_File_Title_ID      1
#define M_File_Name_ID       2
#define M_Insertion_Type_ID  3
#define M_Activation_Type_ID 4
//---------------------------------------------------------------------------

/**
* External file properties
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ExtFileProperties : public CObject
{
    DECLARE_SERIAL(PSS_ExtFileProperties)

    public:
        /**
        * Change type
        *@note These items may be combined
        */
        enum class IEChangeType
        {
            IE_CT_File_Title      = 0x0001,
            IE_CT_File_Name       = 0x0002,
            IE_CT_Insertion_Type  = 0x0004,
            IE_CT_Activation_Type = 0x0008,
            IE_CT_All             = OD_CHANGE_ALL
        };

        PSS_ExtFileProperties();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_ExtFileProperties(const PSS_ExtFileProperties& other);

        virtual ~PSS_ExtFileProperties();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        PSS_ExtFileProperties& operator = (const PSS_ExtFileProperties& other);

        /**
        * Checks if another set of properties is equal to this one
        *@param other - the other properties to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        BOOL operator == (const PSS_ExtFileProperties& other) const;

        /**
        * Makes a copy of this properties object
        *@return a copy of this properties object, NULL on error
        */
        virtual inline PSS_ExtFileProperties* Dup() const;

        /**
        * Merges another property set with this one
        *@param pProp - other property set to merge with
        *@param changeFlags - the change flags
        */
        virtual void Merge(PSS_ExtFileProperties* pProp, DWORD changeFlags = (DWORD)IEChangeType::IE_CT_All);

        /**
        * Checks if another set of properties is equal to this one
        *@param pProp - other property set to compare with
        *@return TRUE if the properties are equals, otherwise FALSE
        */
        virtual BOOL IsEqual(PSS_ExtFileProperties* pProp);

        /**
        * Checks if the object is empty
        *@return TRUE if the object is empty, otherwise FALSE
        */
        virtual inline BOOL IsEmpty() const;

        /**
        * Gets the file title
        *@return the file title
        */
        virtual inline CString GetFileTitle() const;

        /**
        * Sets the file title
        *@param pValue - the file title
        */
        virtual void SetFileTitle(LPCTSTR pValue);

        /**
        * Gets the file name
        *@return the file name
        */
        virtual inline CString GetFileName() const;

        /**
        * Sets the file name
        *@param pValue - the file name
        */
        virtual void SetFileName(LPCTSTR pValue);

        /**
        * Gets the insertion type
        *@return the insertion type
        */
        virtual inline int GetInsertionType() const;

        /**
        * Sets the insertion type
        *@param value - the insertion type
        */
        virtual inline void SetInsertionType(const int value);

        /**
        * Gets the activation type
        *@return the activation type
        */
        virtual inline int GetActivationType() const;

        /**
        * Sets the activation type
        *@param value - the activation type
        */
        virtual inline void SetActivationType(const int value);

        /**
        * Gets the property value
        *@param propId - the property identifier
        *@param[out] value - the property value, in case the function success
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
        CString m_FileTitle;
        CString m_FileName;
        int     m_InsertionType;
        int     m_ActivationType;

    private:
        /**
        * Sets the file title (extended)
        *@param value - the value
        */
        void SetFileTitleEx(const CString& value);

        /**
        * Sets the file name (extended)
        *@param value - the value
        */
        void SetFileNameEx(const CString& value);
};

//---------------------------------------------------------------------------
// PSS_ExtFileProperties
//---------------------------------------------------------------------------
PSS_ExtFileProperties* PSS_ExtFileProperties::Dup() const
{
    return new PSS_ExtFileProperties(*this);
}
//---------------------------------------------------------------------------
BOOL PSS_ExtFileProperties::IsEmpty() const
{
    return m_FileTitle.IsEmpty() && m_FileName.IsEmpty();
}
//---------------------------------------------------------------------------
CString PSS_ExtFileProperties::GetFileTitle() const
{
    return m_FileTitle;
}
//---------------------------------------------------------------------------
CString PSS_ExtFileProperties::GetFileName() const
{
    return m_FileName;
}
//---------------------------------------------------------------------------
int PSS_ExtFileProperties::GetInsertionType() const
{
    return m_InsertionType;
}
//---------------------------------------------------------------------------
void PSS_ExtFileProperties::SetInsertionType(const int value)
{
    m_InsertionType = value;
}
//---------------------------------------------------------------------------
int PSS_ExtFileProperties::GetActivationType() const
{
    return m_ActivationType;
}
//---------------------------------------------------------------------------
void PSS_ExtFileProperties::SetActivationType(const int value)
{
    m_ActivationType = value;
}
//---------------------------------------------------------------------------

#endif
