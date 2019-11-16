/****************************************************************************
 * ==> PSS_WorkspaceFileEntity ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace file entity                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WorkspaceFileEntityH
#define PSS_WorkspaceFileEntityH

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
#ifndef PSS_WorkspaceFileEntity
    #define PSS_WorkspaceFileEntity ZBWorkspaceFileEntity
#endif

// processsoft
#include "PSS_File.h"
#include "PSS_WorkspaceEntity.h"

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
* Workspace file entity
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WorkspaceFileEntity : public PSS_WorkspaceEntity
{
    DECLARE_SERIAL(PSS_WorkspaceFileEntity)

    public:
        /**
        * Constructor
        *@param name - name
        *@param pParent - parent entity, NULL if root
        */
        PSS_WorkspaceFileEntity(const CString& name = "", PSS_WorkspaceEntity* pParent = NULL);

        virtual ~PSS_WorkspaceFileEntity();

        /**
        * Checks if a file name is defined
        *@return true if a file name is defined, otherwise false
        */
        virtual bool HasFileName() const;

        /**
        * Gets the file name
        *@return the file name
        */
        virtual CString GetFileName() const;

        /**
        * Sets the file name
        *@param value - the file name
        */
        virtual void SetFileName(const CString& value);

        /**
        * Gets the file title
        *@return the file title
        */
        virtual CString GetFileTitle() const;

        /**
        * Gets the file path
        *@return the file path
        */
        virtual CString GetFilePath() const;

        /**
        * Gets the file extension
        *@return the file extension
        */
        virtual CString GetFileExt() const;

        /**
        * Gets the file name icon
        *@return the file name icon
        */
        virtual HICON GetFileNameIcon() const;

        /**
        * Opens the file
        *@return true on success, otherwise false
        */
        virtual bool OpenFile();

        /**
        * Checks if properties are visible
        *@return true if properties are visible, otherwise false
        */
        virtual bool PropertiesVisible();

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
        PSS_File m_File;
};

#endif
