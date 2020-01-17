/****************************************************************************
 * ==> PSS_LogicalRulesDocument --------------------------------------------*
 ****************************************************************************
 * Description : Provides a logical rules document                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_LogicalRulesDocumentH
#define PSS_LogicalRulesDocumentH

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
#include "zBaseLib\PSS_BaseDocument.h"
#include "PSS_LogicalRulesEntity.h"

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Logical rules document
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_LogicalRulesDocument : public PSS_BaseDocument
{
    DECLARE_DYNCREATE(PSS_LogicalRulesDocument)

    public:
        typedef PSS_BaseDocument inherited;

        PSS_LogicalRulesDocument();
        virtual ~PSS_LogicalRulesDocument();

        /**
        * Gets the logical rules environment
        *@return the logical rules environment
        */
        virtual inline PSS_LogicalRulesEntity& GetRulesEnvironment();

        /**
        * Checks if the document is loaded
        *@return true if the document is loaded, otherwise false
        */
        virtual inline bool IsLoaded() const;

        /**
        * Sets the document as loaded
        *@param value - if true, the document is loaded
        */
        virtual inline void SetLoaded(bool value = true);

        /**
        * Checks if the document is modified
        *@return TRUE if the document is modified, otherwise FALSE
        */
        virtual inline BOOL IsModified();

        /**
        * Sets the document as modified
        *@param value - if TRUE, the document is modified
        */
        virtual inline void SetModifiedFlag(BOOL value = TRUE);

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        virtual void Serialize(CArchive& ar);

        /**
        * Reads the document from a file
        *@param fileName - the file name
        *@return true on success, otherwise false
        */
        virtual bool ReadFromFile(const CString& fileName);

        /**
        * Saves the document to a file
        *@param fileName - the file name
        *@return true on success, otherwise false
        */
        virtual bool SaveToFile(const CString& fileName);

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
        /// Generated message map functions
        //{{AFX_MSG(PSS_LogicalRulesDocument)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Called when a new document is created
        */
        virtual BOOL OnNewDocument();

    private:
        PSS_LogicalRulesEntity m_RulesEnvironment;
        CString                m_GUID;
        bool                   m_IsLoaded;
};

//---------------------------------------------------------------------------
// PSS_LogicalRulesDocument
//---------------------------------------------------------------------------
PSS_LogicalRulesEntity& PSS_LogicalRulesDocument::GetRulesEnvironment()
{
    return m_RulesEnvironment;
}
//---------------------------------------------------------------------------
bool PSS_LogicalRulesDocument::IsLoaded() const
{
    return m_IsLoaded;
}
//---------------------------------------------------------------------------
void PSS_LogicalRulesDocument::SetLoaded(bool value)
{
    m_IsLoaded = value;
}
//---------------------------------------------------------------------------
BOOL PSS_LogicalRulesDocument::IsModified()
{
    return (CDocument::IsModified() || m_RulesEnvironment.IsModified());
}
//---------------------------------------------------------------------------
void PSS_LogicalRulesDocument::SetModifiedFlag(BOOL value)
{
    CDocument::SetModifiedFlag(value);
    m_RulesEnvironment.SetModifiedFlag(value);
}
//---------------------------------------------------------------------------

#endif
