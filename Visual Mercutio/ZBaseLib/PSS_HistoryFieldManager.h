/****************************************************************************
 * ==> PSS_HistoryFieldManager ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a history field manager for the document          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef HistFMng_h
#define HistFMng_h 1

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// old class name mapping. This is required to maintain the compatibility with the files serialized before the class renaming
#ifndef PSS_HistoryFieldManager
    //#define PSS_HistoryFieldManager ZAHistoryFieldManager
#endif

// mfc
#include "mfc.h"

// processsoft
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
* History field manager
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_HistoryFieldManager : public CObject
{
    DECLARE_SERIAL(PSS_HistoryFieldManager)

    public:
        typedef CObject inherited;

        PSS_HistoryFieldManager();
        virtual ~PSS_HistoryFieldManager();

        /**
        * Adds a new historic value in the field history array
        *@param fieldName - field name
        *@param value - value
        */
        void AddFieldHistoryValue(const CString& fieldName, const CString& value);

        /**
        * Removes a specific historic value from the manager
        *@param fieldName - field name
        *@param value - value
        *@return TRUE on success, otherwise FALSE
        */
        BOOL RemoveFieldHistoryValue(const CString& fieldName, const CString& value);

        /**
        * Removes a specific historic field from the manager
        *@param fieldName - field name
        *@return TRUE on success, otherwise FALSE
        */
        BOOL RemoveFieldHistory(const CString& fieldName);

        /**
        * Searches if a specific fields exists
        *@param fieldName - field name
        *@return TRUE if the specific fields exists, otherwise FALSE
        */
        PSS_HistoryField* FindField(const CString& fieldName);

        /**
        * Gets the field history
        *@param fieldName - field name
        *@return the field history, NULL if not found or on error
        */
        CStringArray* GetFieldHistory(const CString& fieldName);

        /**
        * Gets the history manager element count
        *@return the history manager element count
        */
        virtual inline std::size_t GetCount() const;

        /**
        * Removes the history
        */
        void FreeList();

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

    private:
        CObArray m_FieldHistoryArray;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_HistoryFieldManager(const PSS_HistoryFieldManager& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_HistoryFieldManager& operator = (const PSS_HistoryFieldManager& other);
};

//---------------------------------------------------------------------------
// PSS_HistoryFieldManager
//---------------------------------------------------------------------------
std::size_t PSS_HistoryFieldManager::GetCount() const
{
    return m_FieldHistoryArray.GetSize();
}
//---------------------------------------------------------------------------

#endif
