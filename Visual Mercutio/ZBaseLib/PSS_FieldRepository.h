/****************************************************************************
 * ==> PSS_FieldRepository -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a repository field                                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FieldRepositoryH
#define PSS_FieldRepositoryH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "GFldDoc.h"

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
* Repository field
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FieldRepository
{
    public:
        PSS_FieldRepository();
        virtual ~PSS_FieldRepository();

        /**
        * Initializes an empty repository
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL InitializeEmpty();

        /**
        * Opens and initializes the field repository
        *@param fileName - file name
        *@param readOnly - if TRUE repository is opened in read-only mode
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL OpenRepository(const CString& fileName, BOOL readOnly = TRUE);

        /**
        * Closes the repository and if necessary, save changes
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CloseRepository();

        /**
        * Saves the repository to a file
        *@param fileName - file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SaveRepositoryToFile(const CString& fileName);

        /**
        * Reloads the repository
        *@param saveBefore - if TRUE, repository content will be saved before reloaded
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL ReloadRepository(BOOL saveBefore = FALSE);

        /**
        * Adds a new historic value into the field history array
        *@param fieldName - field name
        *@param value - value
        */
        virtual inline void AddFieldHistoryValue(const CString& fieldName, const CString& value);

        /**
        * Removes a specific historic value from the manager
        *@param fieldName - field name
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL RemoveFieldHistory(const CString& fieldName);

        /**
        * Removes a specific historic value from the manager
        *@param fieldName - field name
        *@param value - value
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL RemoveFieldHistoryValue(const CString& fieldName, const CString& value);

        /**
        * Searches if a specific fields exists
        *@param fieldName - field name
        *@return history field, NULL if not found or on error
        */
        virtual inline ZAHistoryField* FindFieldHistory(const CString& fieldName);

        /**
        * Gets the field history
        *@param fieldName - field name for which the history should be get
        *@return the field history
        */
        virtual inline CStringArray* GetFieldHistory(const CString& fieldName);

        /**
        * Gets the history manager element count
        *@return the history manager element count
        */
        virtual inline std::size_t GetFieldHistoryCount();

        /**
        * Gets the global field manager element count
        *@return the global field manager element count
        */
        virtual inline std::size_t GetFieldCount();

        /**
        * Adds a new field
        *@param pField - field to add
        *@return the index of the added field
        */
        virtual inline int AddField(PSS_FieldObjectDefinition* pField);

        /**
        * Deletes a field
        *@param name - field name to delete
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL DeleteField(const CString& name);

        /**
        * Deletes all the fields
        *@return TRUE on success, otherwise FALSE
        */
        virtual inline BOOL DeleteAllField();

        /**
        * Finds if a field exists
        *@param name - field name
        *@return found field, NULL if not found or on error
        */
        virtual inline PSS_FieldObjectDefinition* FindField(const CString& name);

        /**
        * Gets the object at a specific location
        *@param index - field index
        *@return the object at the specific location, NULL if not found or on error
        */
        virtual inline PSS_FieldObjectDefinition* GetFieldAt(int index);

        /**
        * Gets the field description
        *@param name - field name
        *@return field description
        */
        virtual inline CString GetDescription(const CString& name);

        /**
        * Gets the field class name
        *@param name - field name for which the class name should be get
        *@return the field class name, empty string if not found or on error
        */
        virtual inline CString GetClassName(const CString& name);

        /**
        * Gets the field name array
        *@return the field name array of all fields contained in the manager
        */
        virtual inline const CStringArray& GetFieldNameArray();

        /**
        * Copies the object field definition to the Planfin object
        *@param name - field name
        *@param pObj - object
        *@param pDoc - document
        */
        virtual inline void CopyFieldDefinition(const CString& name, PlanFinObject* pObj, ZDDocument* pDoc);

        /**
        * Checks if field repository is valid
        *@return TRUE is valid, otherwise FALSE
        */
        virtual inline BOOL IsValid() const;

        /**
        * Imports a field repository and merge fields with the source
        *@param fieldRepository - field repository
        *@param replaceExisting - if TRUE, existing content will be replaced by the merged one
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Import(PSS_FieldRepository& fieldRepository, BOOL replaceExisting = FALSE);

    private:
        PSS_GlobalFieldManager* m_GlobalFieldManager;
        ZAHistoryFieldManager*  m_HistoryValueManager;
        ZDGlobalFieldDocument*  m_Document;
        CString                 m_FileName;
        BOOL                    m_ReadOnly;
        BOOL                    m_IsValid;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_FieldRepository(const PSS_FieldRepository& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_FieldRepository& operator = (const PSS_FieldRepository& other);
};

//---------------------------------------------------------------------------
// PSS_FieldRepository
//---------------------------------------------------------------------------
void PSS_FieldRepository::AddFieldHistoryValue(const CString& fieldName, const CString& value)
{
    if (m_HistoryValueManager)
        m_HistoryValueManager->AddFieldHistoryValue(fieldName, value);
}
//---------------------------------------------------------------------------
BOOL PSS_FieldRepository::RemoveFieldHistory(const CString& fieldName)
{
    if (m_HistoryValueManager)
        return m_HistoryValueManager->RemoveFieldHistory(fieldName);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_FieldRepository::RemoveFieldHistoryValue(const CString& fieldName, const CString& value)
{
    if (m_HistoryValueManager)
        return m_HistoryValueManager->RemoveFieldHistoryValue(fieldName, value);

    return FALSE;
}
//---------------------------------------------------------------------------
ZAHistoryField* PSS_FieldRepository::FindFieldHistory(const CString& fieldName)
{
    if (m_HistoryValueManager)
        return m_HistoryValueManager->FindField(fieldName);

    return NULL;
}
//---------------------------------------------------------------------------
CStringArray* PSS_FieldRepository::GetFieldHistory(const CString& fieldName)
{
    if (m_HistoryValueManager)
        return m_HistoryValueManager->GetFieldHistory(fieldName);

    return NULL;
}
//---------------------------------------------------------------------------
std::size_t PSS_FieldRepository::GetFieldHistoryCount()
{
    if (m_HistoryValueManager)
        return m_HistoryValueManager->GetCount();

    return 0;
}
//---------------------------------------------------------------------------
std::size_t PSS_FieldRepository::GetFieldCount()
{
    if (m_GlobalFieldManager)
        return m_GlobalFieldManager->GetCount();

    return 0;
}
//---------------------------------------------------------------------------
int PSS_FieldRepository::AddField(PSS_FieldObjectDefinition* pField)
{
    if (m_GlobalFieldManager)
        return m_GlobalFieldManager->AddField(pField);

    return 0;
}
//---------------------------------------------------------------------------
BOOL PSS_FieldRepository::DeleteField(const CString& name)
{
    if (m_GlobalFieldManager)
        return m_GlobalFieldManager->DeleteField(name);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_FieldRepository::DeleteAllField()
{
    if (m_GlobalFieldManager)
        return m_GlobalFieldManager->DeleteAllField();

    return FALSE;
}
//---------------------------------------------------------------------------
PSS_FieldObjectDefinition* PSS_FieldRepository::FindField(const CString& name)
{
    if (m_GlobalFieldManager)
        return m_GlobalFieldManager->FindField(name);

    return NULL;
}
//---------------------------------------------------------------------------
PSS_FieldObjectDefinition* PSS_FieldRepository::GetFieldAt(int index)
{
    if (m_GlobalFieldManager)
        return m_GlobalFieldManager->GetAt(index);

    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_FieldRepository::GetDescription(const CString& name)
{
    if (m_GlobalFieldManager)
        return m_GlobalFieldManager->GetDescription(name);

    return "";
}
//---------------------------------------------------------------------------
CString PSS_FieldRepository::GetClassName(const CString& name)
{
    if (m_GlobalFieldManager)
        return m_GlobalFieldManager->GetClassName(name);

    return "";
}
//---------------------------------------------------------------------------
const CStringArray& PSS_FieldRepository::GetFieldNameArray()
{
    return m_GlobalFieldManager->GetFieldNameArray();
}
//---------------------------------------------------------------------------
void PSS_FieldRepository::CopyFieldDefinition(const CString& name, PlanFinObject* pObj, ZDDocument* pDoc)
{
    if (m_GlobalFieldManager)
        m_GlobalFieldManager->CopyFieldDefinition(name, pObj, pDoc);
}
//---------------------------------------------------------------------------
BOOL PSS_FieldRepository::IsValid() const
{
    return m_IsValid;
}
//---------------------------------------------------------------------------

#endif
