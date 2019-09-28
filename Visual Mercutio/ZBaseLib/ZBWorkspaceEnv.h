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
class AFX_EXT_CLASS ZBWorkspaceEnv : public ZBWorkspaceGroupEntity
{
    DECLARE_SERIAL(ZBWorkspaceEnv)

public:
    // Can have a parent in case of multiple workspace environements
    ZBWorkspaceEnv(const CString Name = "", PSS_WorkspaceEntity* pParent = NULL);
    virtual ~ZBWorkspaceEnv();

    // Operations
public:
    virtual BOOL IsModified()
    {
        return m_bModified;
    };
    virtual void SetModifiedFlag(BOOL bModified = TRUE)
    {
        m_bModified = bModified;
    };
    void SetOpenedFiles(CStringArray& OpenedFiles);

    // Serialization mechanism
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

private:
    void OpenLastFiles();

private:
    CStringArray    m_OpenedFileArray;
    BOOL            m_bModified;

};

#endif
