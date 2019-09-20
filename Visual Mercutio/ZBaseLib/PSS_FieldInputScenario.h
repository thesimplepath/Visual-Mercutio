/****************************************************************************
 * ==> PSS_FieldInputScenario ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a field input scenario                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FieldInputScenarioH
#define PSS_FieldInputScenarioH

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
#ifndef PSS_FieldInputScenario
    #define PSS_FieldInputScenario ZBFieldInputScenario
#endif

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
* Field input scenario
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_FieldInputScenario : public CObject
{
    DECLARE_SERIAL(PSS_FieldInputScenario)

    public:
        typedef CObject inherited;

        /**
        * Constructor
        *@param fieldName - field name
        *@param userName - user name
        *@param order - order
        */
        PSS_FieldInputScenario(const CString& fieldName = "", const CString& userName = "", int order = -1);

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_FieldInputScenario(const PSS_FieldInputScenario& other);

        virtual ~PSS_FieldInputScenario();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_FieldInputScenario& operator = (const PSS_FieldInputScenario& other);

        /**
        * Clones the object
        *@return the cloned object, NULL on error
        */
        virtual PSS_FieldInputScenario* Clone() const;

        /**
        * Initializes the class
        *@param fieldName - field name
        *@param userName - user name
        *@param order - order
        */
        virtual void Initialize(const CString& fieldName, const CString& userName = "", int order = -1);

        /**
        * Checks if scenario is ordered
        *@return true if the scenario is ordered, otherwise false
        */
        virtual inline bool IsOrdered() const;

        /**
        * Checks if everyone is allowed
        *@return true if everyone is allowed, otherwise false
        */
        virtual inline bool EveryoneAllowed() const;

        /**
        * Gets the order
        *@return the order
        */
        virtual inline int GetOrder() const;

        /**
        * Sets the order
        *@param value - the order
        */
        virtual inline void SetOrder(int value);

        /**
        * Gets the user name
        *@return the user name
        */
        virtual inline CString GetUserName() const;

        /**
        * Sets the user name
        *@param value - the user name
        */
        virtual inline void SetUserName(const CString& value);

        /**
        * Gets the field name
        *@return the field name
        */
        virtual inline CString GetFieldName() const;

        /**
        * Sets the field name
        *@param value - the field name
        */
        virtual inline void SetFieldName(const CString& value);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

    private:
        CString m_FieldName;
        CString m_UserName;
        int     m_Order;
};

//---------------------------------------------------------------------------
// PSS_FieldInputScenario
//---------------------------------------------------------------------------
bool PSS_FieldInputScenario::IsOrdered() const
{
    return m_Order != -1;
}
//---------------------------------------------------------------------------
bool PSS_FieldInputScenario::EveryoneAllowed() const
{
    return m_UserName.IsEmpty();
}
//---------------------------------------------------------------------------
int PSS_FieldInputScenario::GetOrder() const
{
    return m_Order;
}
//---------------------------------------------------------------------------
void PSS_FieldInputScenario::SetOrder(int value)
{
    m_Order = value;
}
//---------------------------------------------------------------------------
CString PSS_FieldInputScenario::GetUserName() const
{
    return m_UserName;
}
//---------------------------------------------------------------------------
void PSS_FieldInputScenario::SetUserName(const CString& value)
{
    m_UserName = value;
}
//---------------------------------------------------------------------------
CString PSS_FieldInputScenario::GetFieldName() const
{
    return m_FieldName;
}
//---------------------------------------------------------------------------
void PSS_FieldInputScenario::SetFieldName(const CString& value)
{
    m_FieldName = value;
}
//---------------------------------------------------------------------------

#endif
