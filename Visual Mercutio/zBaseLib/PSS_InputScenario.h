/****************************************************************************
 * ==> PSS_InputScenario ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides an input scenario                                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_InputScenarioH
#define PSS_InputScenarioH

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

// processsoft
#include "PSS_FieldInputScenario.h"

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Input scenario
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_InputScenario : public CObject
{
    DECLARE_SERIAL(PSS_InputScenario)

    public:
        typedef CObject inherited;

        /**
        * Constructor
        *@param name - name
        */
        PSS_InputScenario(const CString& name = "");

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_InputScenario(const PSS_InputScenario& other);

        virtual ~PSS_InputScenario();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_InputScenario& operator = (const PSS_InputScenario& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_InputScenario* Clone() const;

        /**
        * Initializes the class
        *@param name - name
        */
        virtual void Initialize(const CString& name);

        /**
        * Gets the name
        *@return the name
        */
        virtual inline CString GetName() const;

        /**
        * Sets the name
        *@param value - the name
        */
        virtual inline void SetName(const CString& value);

        /**
        * Removes all the fields
        */
        virtual void RemoveAllField();

        /**
        * Gets the field count
        *@return the field count
        */
        virtual inline std::size_t GetFieldCount() const;

        /**
        * Gets the field at index
        *@param index - index
        *@return the field, NULL on error or if not found
        */
        virtual inline PSS_FieldInputScenario* GetFieldAt(std::size_t index) const;

        /**
        * Searches a field
        *@param fieldName - field name
        *@return the field, NULL if not found or on error
        */
        virtual PSS_FieldInputScenario* SearchFieldName(const CString& fieldName) const;

        /**
        * Searches the field name index
        *@param fieldName - field name
        *@return the field name index, -1 if not found or on error
        */
        virtual int SearchFieldNameIndex(const CString& fieldName) const;

        /**
        * Adds a field
        *@param pField - field to add
        *@return true on successm otherwise false
        */
        virtual inline bool AddField(PSS_FieldInputScenario* pField);

        /**
        * Adds a field
        *@param fieldName - field name
        *@param userName - user name
        *@param order - order
        *@return true on successm otherwise false
        */
        virtual bool AddField(const CString& fieldName, const CString& userName = "", int order = -1);

        /**
        * Deletes a field
        *@param fieldName - field name
        *@return true on success, otherwise false
        */
        virtual bool DeleteFieldName(const CString& fieldName);

        /**
        * Deletes a field name at index
        *@param index - index
        *@return true on success, otherwise false
        */
        virtual bool DeleteFieldNameAt(std::size_t index);

        /**
        * Removes a field name at index
        *@param index - index
        *@return true on success, otherwise false
        */
        virtual inline bool RemoveFieldNameAt(std::size_t index);

        /**
        * Gets the scenario for user
        *@param userName - user name
        *@param[out] scenario - scenario
        *@return the scenario index
        */
        virtual std::size_t GetScenarioForUser(const CString& userName, PSS_InputScenario& scenario);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CObArray m_InputFieldSet;
        CString  m_Name;
};

//---------------------------------------------------------------------------
// PSS_InputScenario
//---------------------------------------------------------------------------
CString PSS_InputScenario::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
void PSS_InputScenario::SetName(const CString& value)
{
    m_Name = value;
}
//---------------------------------------------------------------------------
std::size_t PSS_InputScenario::GetFieldCount() const
{
    return m_InputFieldSet.GetSize();
}
//---------------------------------------------------------------------------
PSS_FieldInputScenario* PSS_InputScenario::GetFieldAt(std::size_t index)    const
{
    if (index < GetFieldCount())
        return static_cast<PSS_FieldInputScenario*>(m_InputFieldSet.GetAt(index));

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_InputScenario::AddField(PSS_FieldInputScenario* pField)
{
    try
    {
        m_InputFieldSet.Add(pField);
    }
    catch (CMemoryException&)
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_InputScenario::RemoveFieldNameAt(std::size_t index)
{
    if (index < GetFieldCount())
        m_InputFieldSet.RemoveAt(index);

    return false;
}
//---------------------------------------------------------------------------

#endif
