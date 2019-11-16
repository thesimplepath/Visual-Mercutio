/****************************************************************************
 * ==> PSS_WorkspaceWizardTemplateDocument ---------------------------------*
 ****************************************************************************
 * Description : Provides a workspace wizard template environment document  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WorkspaceWizardTemplateDocumentH
#define PSS_WorkspaceWizardTemplateDocumentH

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
#include "PSS_WorkspaceWizardTemplateManager.h"

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
* Workspace wizard template environment document
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WorkspaceWizardTemplateDocument : public CDocument
{
    DECLARE_DYNCREATE(PSS_WorkspaceWizardTemplateDocument)

    public:
        PSS_WorkspaceWizardTemplateDocument();
        virtual ~PSS_WorkspaceWizardTemplateDocument();

        /**
        * Reads the document from a file
        *@param fileName - file name
        *@return true on success, otherwise false
        */
        virtual bool ReadFromFile(const CString& fileName);

        /**
        * Saves the document to a file
        *@param fileName - file name
        *@return true on success, otherwise false
        */
        virtual bool SaveToFile(const CString& fileName);

        /**
        * Gets the workspace environment
        *@return the workspace environment
        */
        virtual inline PSS_WorkspaceWizardTemplateManager& GetWorkspaceTemplates();

        /**
        * Checks if the document is loaded
        *@return true if the document is loaded, otherwise false
        */
        virtual inline bool IsLoaded() const;

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
        //{{AFX_VIRTUAL(PSS_WorkspaceWizardTemplateDocument)
        virtual BOOL OnNewDocument();
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_WorkspaceWizardTemplateDocument)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_WorkspaceWizardTemplateManager m_WorkspaceTemplates;
        bool                               m_IsLoaded;
};

//---------------------------------------------------------------------------
// PSS_WorkspaceWizardTemplateDocument
//---------------------------------------------------------------------------
PSS_WorkspaceWizardTemplateManager& PSS_WorkspaceWizardTemplateDocument::GetWorkspaceTemplates()
{
    return m_WorkspaceTemplates;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceWizardTemplateDocument::IsLoaded() const
{
    return m_IsLoaded;
}
//---------------------------------------------------------------------------

#endif
