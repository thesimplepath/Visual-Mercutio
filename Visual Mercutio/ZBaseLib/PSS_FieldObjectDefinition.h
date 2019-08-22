/****************************************************************************
 * ==> PSS_FieldObjectDefinition -------------------------------------------*
 ****************************************************************************
 * Description : Provides a field object definition                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FieldObjectDefinitionH
#define PSS_FieldObjectDefinitionH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_FieldObjectDefinition
    #define PSS_FieldObjectDefinition ZAObjectDefinition
#endif

// mfc
#include "mfc.h"

// processsoft
#include "ZAObject.h"

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
* Object definition
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FieldObjectDefinition : public CObject
{
    DECLARE_SERIAL(PSS_FieldObjectDefinition)

    public:
        typedef CObject inherited;

        PSS_FieldObjectDefinition();

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_FieldObjectDefinition(const PSS_FieldObjectDefinition& other);

        virtual ~PSS_FieldObjectDefinition();

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        virtual const PSS_FieldObjectDefinition& operator = (const PSS_FieldObjectDefinition& other);

        /**
        * Clones the object definition
        *@return the cloned object definition, NULL on error
        */
        virtual PSS_FieldObjectDefinition* Clone() const;

        /**
        * Gets the field description
        *@return the field description
        */
        virtual inline const CString GetDescription() const;

        /**
        * Sets the field description
        *@param value - the field description
        */
        virtual inline void SetDescription(const CString& value);

        /**
        * Gets the class name
        *@return the class nae
        */
        virtual inline const CString GetClassName() const;

        /**
        * Sets the class name
        *@param value - the class nae
        */
        virtual inline void SetClassName(const CString& value);

        /**
        * Gets the object
        *@return the object
        */
        virtual inline PlanFinObject* GetObject();

        /**
        * Sets the object
        *@param pObject - the object
        */
        virtual inline void SetObject(PlanFinObject* pObject);

        /**
        * Gets the field name
        *@return the field name
        */
        virtual inline const CString GetFieldName() const;

        /**
        * Sets the field name
        *@param value - the field name
        */
        virtual inline void SetFieldName(const CString& value);

        /**
        * Gets the field description used for wizard. Destinated to users
        *@return the field description used for wizard
        */
        virtual inline const CString GetHelpUserDescription() const;

        /**
        * Sets the field description used for wizard. Destinated to users
        *@param value - the field description used for wizard
        */
        virtual inline void SetHelpUserDescription(const CString& value);

        /**
        * Gets if field is sorted
        *@return TRUE if field is sorted, otherwise FALSE
        */
        virtual inline const BOOL IsSorted() const;

        /**
        * Sets if field is sorted
        *@param value - if TRUE, field is sorted
        */
        virtual inline void SetSorted(BOOL value = TRUE);

        /**
        * Serializes the object content
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

    private:
        PlanFinObject* m_pObject;
        CString        m_Description;
        CString        m_ClassName;
        CString        m_FieldName;
        CString        m_HelpUserDescription;
        BOOL           m_Sorted;
};

//---------------------------------------------------------------------------
// PSS_BaseDocument
//---------------------------------------------------------------------------
const CString PSS_FieldObjectDefinition::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------
void PSS_FieldObjectDefinition::SetDescription(const CString& value)
{
    m_Description = value;
}
//---------------------------------------------------------------------------
const CString PSS_FieldObjectDefinition::GetClassName() const
{
    return m_ClassName;
}
//---------------------------------------------------------------------------
void PSS_FieldObjectDefinition::SetClassName(const CString& value)
{
    m_ClassName = value;
}
//---------------------------------------------------------------------------
PlanFinObject* PSS_FieldObjectDefinition::GetObject()
{
    return m_pObject;
}
//---------------------------------------------------------------------------
void PSS_FieldObjectDefinition::SetObject(PlanFinObject* value)
{
    m_pObject = value;
}
//---------------------------------------------------------------------------
const CString PSS_FieldObjectDefinition::GetFieldName() const
{
    return m_FieldName;
}
//---------------------------------------------------------------------------
void PSS_FieldObjectDefinition::SetFieldName(const CString& value)
{
    m_FieldName = value;
}
//---------------------------------------------------------------------------
const CString PSS_FieldObjectDefinition::GetHelpUserDescription() const
{
    return m_HelpUserDescription;
}
//---------------------------------------------------------------------------
void PSS_FieldObjectDefinition::SetHelpUserDescription(const CString& value)
{
    m_HelpUserDescription = value;
}
//---------------------------------------------------------------------------
const BOOL PSS_FieldObjectDefinition::IsSorted() const
{
    return m_Sorted;
}
//---------------------------------------------------------------------------
void PSS_FieldObjectDefinition::SetSorted(BOOL value)
{
    m_Sorted = value;
}
//---------------------------------------------------------------------------

#endif
