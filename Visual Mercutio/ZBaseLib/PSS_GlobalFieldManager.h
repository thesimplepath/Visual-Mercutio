/****************************************************************************
 * ==> PSS_GlobalFieldManager ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a global field container for the document         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_GlobalFieldManagerH
#define PSS_GlobalFieldManagerH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_GlobalFieldManager
    #define PSS_GlobalFieldManager ZAGlobalFieldManager
#endif

// mfc
#include "mfc.h"

// processsoft
#include "PSS_FieldObjectDefinition.h"
#include "PSS_HistoryField.h"

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
* Global field manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_GlobalFieldManager : public CObject
{
    DECLARE_SERIAL(PSS_GlobalFieldManager)

    public:
        typedef CObject inherited;

        PSS_GlobalFieldManager();
        virtual ~PSS_GlobalFieldManager();

        /**
        * Gets the field count
        *@return the field count
        */
        virtual inline std::size_t GetCount() const;

        /**
        * Adds a new field
        *@param pField - field to add
        *@return the added field index
        */
        virtual int AddField(PSS_FieldObjectDefinition* pField);

        /**
        * Deletes a field
        *@param name - field name to delete
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DeleteField(const CString& name);

        /**
        * Delete all the fields
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL DeleteAllField();

        /**
        * Searches a field
        *@param name - field name to search for
        *@return found field, NULL if not found or on error
        */
        virtual PSS_FieldObjectDefinition* FindField(const CString& name);

        /**
        * Gets the field object at index
        *@param index - index
        *@return the field object, NULL if not found or on error
        */
        virtual PSS_FieldObjectDefinition* GetAt(int index);

        /**
        * Gets a field description
        *@param name - field name for which the description should be get
        *@return  the field description, empty string if not found or on error
        */
        virtual CString GetDescription(const CString& name);

        /**
        * Gets the field class name
        *@param name - field name for which the class name should be get
        *@return the field class name, empty string if not found or on error
        */
        virtual CString GetClassName(const CString& name);

        /**
        * Gets the manager field name array
        *@return the manager field name array
        */
        virtual const CStringArray& GetFieldNameArray();

        /**
        * Copies the field definition
        *@param name -field name to copy to
        *@param pObj - field object to copy from
        *@param pDoc - document
        */
        virtual void CopyFieldDefinition(const CString& name, PlanFinObject* pObj, ZDDocument* pDoc);

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
        CObArray     m_GlobalFieldArray;
        CStringArray m_FieldNameArray;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_GlobalFieldManager(const PSS_GlobalFieldManager& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_GlobalFieldManager& operator = (const PSS_GlobalFieldManager& other);

        /**
        * Removes all the fields
        */
        void FreeList();
};

//---------------------------------------------------------------------------
// PSS_GlobalFieldManager
//---------------------------------------------------------------------------
std::size_t PSS_GlobalFieldManager::GetCount() const
{
    return m_GlobalFieldArray.GetSize();
}
//---------------------------------------------------------------------------

#endif
