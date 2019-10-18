/****************************************************************************
 * ==> PSS_WorkspaceEnvDocument --------------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace environment document                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WorkspaceEnvDocumentH
#define PSS_WorkspaceEnvDocumentH

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
#include "PSS_WorkspaceEnv.h"

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
* Workspace environment document
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WorkspaceEnvDocument : public CDocument
{
    DECLARE_DYNCREATE(PSS_WorkspaceEnvDocument)

    public:
        PSS_WorkspaceEnvDocument();
        virtual ~PSS_WorkspaceEnvDocument();

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
        virtual bool SaveToFile(const CString& Filename);

        /**
        * Gets the workspace environment
        *@return the workspace environment
        */
        virtual inline PSS_WorkspaceEnv& GetWorkspaceEnvironment();

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
        //{{AFX_VIRTUAL(PSS_WorkspaceEnvDocument)
        virtual BOOL OnNewDocument();
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_WorkspaceEnvDocument)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        PSS_WorkspaceEnv m_WorkspaceEnvironment;
        bool             m_IsLoaded;
};

//---------------------------------------------------------------------------
// PSS_WorkspaceEnvDocument
//---------------------------------------------------------------------------
PSS_WorkspaceEnv& PSS_WorkspaceEnvDocument::GetWorkspaceEnvironment()
{
    return m_WorkspaceEnvironment;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceEnvDocument::IsLoaded() const
{
    return m_IsLoaded;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceEnvDocument::SetLoaded(bool value)
{
    m_IsLoaded = value;
}
//---------------------------------------------------------------------------
BOOL PSS_WorkspaceEnvDocument::IsModified()
{
    return CDocument::IsModified() || m_WorkspaceEnvironment.IsModified();
}
//---------------------------------------------------------------------------

#endif
