/****************************************************************************
 * ==> PSS_WorkspaceEnv ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace environment                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WorkspaceEnvH
#define PSS_WorkspaceEnvH

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
#ifndef PSS_WorkspaceEnv
    #define PSS_WorkspaceEnv ZBWorkspaceEnv
#endif

// processsoft
#include "ZBWorkspaceGroupEntity.h"

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
* Workspace environment
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WorkspaceEnv : public ZBWorkspaceGroupEntity
{
    DECLARE_SERIAL(PSS_WorkspaceEnv)

    public:
        /**
        * Constructor
        *@param name - name
        *@param pPArent - parent, can be NULL
        *@note Can have a parent in case of multiple workspace environments
        */
        PSS_WorkspaceEnv(const CString& name = "", PSS_WorkspaceEntity* pParent = NULL);

        virtual ~PSS_WorkspaceEnv();

        /**
        * Checks if environment was modified
        *@return TRUE if environment was modified, otherwise FALSE
        */
        virtual inline BOOL IsModified() const;

        /**
        * Sets the environment as modified
        *@param modified - if TRUE, the environment will be tagged as modified
        */
        virtual inline void SetModifiedFlag(BOOL modified = TRUE);

        /**
        * Sets the opened files
        *@param openedFiles - opened files
        */
        void SetOpenedFiles(CStringArray& openedFiles);

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
        CStringArray m_OpenedFileArray;
        BOOL         m_Modified;

        /**
        * Opens the last files
        */
        void OpenLastFiles();
};

//---------------------------------------------------------------------------
// PSS_WorkspaceEnv
//---------------------------------------------------------------------------
BOOL PSS_WorkspaceEnv::IsModified() const
{
    return m_Modified;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceEnv::SetModifiedFlag(BOOL modified)
{
    m_Modified = modified;
}
//---------------------------------------------------------------------------

#endif
