/****************************************************************************
 * ==> PSS_HistoricValueDocument -------------------------------------------*
 ****************************************************************************
 * Description : Provides an historic value document                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_HistoricValueDocumentH
#define PSS_HistoricValueDocumentH

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
#include "PSS_HistoricValueManager.h"

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
* Historic value document
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_HistoricValueDocument : public CDocument
{
    DECLARE_DYNCREATE(PSS_HistoricValueDocument)

    public:
        PSS_HistoricValueDocument();
        virtual ~PSS_HistoricValueDocument();

        /**
        * Reads from file
        *@param fileName - file name
        *@return true on success, otherwise false
        */
        virtual bool ReadFromFile(const CString& fileName);

        /**
        * Writes to file
        *@param fileName - file name
        *@return true on success, otherwise false
        */
        virtual bool SaveToFile(const CString& fileName);

        /**
        * Gets the historic value manager
        *@return the historic value manager
        */
        virtual inline PSS_HistoricValueManager& GetHistoricValueManager();

        /**
        * Checks if document is loaded
        *@return true if document is loaded, otherwise false
        */
        virtual inline bool IsLoaded() const;

        /**
        * Sets the document as loaded
        *@param value - if true, the document is loaded
        */
        virtual inline void SetLoaded(bool value = true);

        /**
        * Checks if document is modified
        *@return true if the document is modified, otherwise false
        */
        virtual inline BOOL IsModified();

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
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_HistoricValueDocument)
        virtual BOOL OnNewDocument();
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_HistoricValueDocument)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_HistoricValueManager m_HistoricValueManager;
        bool                     m_IsLoaded;
};

//---------------------------------------------------------------------------
// PSS_HistoricValueDocument
//---------------------------------------------------------------------------
PSS_HistoricValueManager& PSS_HistoricValueDocument::GetHistoricValueManager()
{
    return m_HistoricValueManager;
}
//---------------------------------------------------------------------------
bool PSS_HistoricValueDocument::IsLoaded() const
{
    return m_IsLoaded;
}
//---------------------------------------------------------------------------
void PSS_HistoricValueDocument::SetLoaded(bool value)
{
    m_IsLoaded = value;
}
//---------------------------------------------------------------------------
BOOL PSS_HistoricValueDocument::IsModified()
{
    return CDocument::IsModified();
}
//---------------------------------------------------------------------------

#endif
