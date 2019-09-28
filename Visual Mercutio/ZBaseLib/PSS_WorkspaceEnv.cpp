/****************************************************************************
 * ==> PSS_WorkspaceEnv ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace environment                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WorkspaceEnv.h"

// processsoft
#include "PSS_File.h"
#include "ZUFileLauncher.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_WorkspaceEnv, ZBWorkspaceGroupEntity, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_WorkspaceEnv
//---------------------------------------------------------------------------
PSS_WorkspaceEnv::PSS_WorkspaceEnv(const CString& name, PSS_WorkspaceEntity* pParent) :
    ZBWorkspaceGroupEntity(name, pParent),
    m_Modified(FALSE)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceEnv::~PSS_WorkspaceEnv()
{}
//---------------------------------------------------------------------------
void PSS_WorkspaceEnv::SetOpenedFiles(CStringArray& openedFiles)
{
    // clear the array
    m_OpenedFileArray.RemoveAll();

    // copy files
    int Count = openedFiles.GetSize();

    for (int i = 0; i < Count; ++i)
        m_OpenedFileArray.Add(openedFiles.GetAt(i));
}
//---------------------------------------------------------------------------
void PSS_WorkspaceEnv::Serialize(CArchive& ar)
{
    ZBWorkspaceGroupEntity::Serialize(ar);

    // serialize the opened file array
    m_OpenedFileArray.Serialize(ar);

    if (ar.IsStoring())
        // todo -cFeature -oJean: add storing code here
        // after a save, clear the modified flag
        m_Modified = FALSE;
    else
    {
        // todo -cFeature -oJean: add loading code here

        // recalculate all parent pointers
        RecalculateParent();

        // open files
        OpenLastFiles();
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_WorkspaceEnv::AssertValid() const
    {
        ZBWorkspaceGroupEntity::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_WorkspaceEnv::Dump(CDumpContext& dc) const
    {
        ZBWorkspaceGroupEntity::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_WorkspaceEnv::OpenLastFiles()
{
    // copy files
    const int count = m_OpenedFileArray.GetSize();

    for (int i = 0; i < count; ++i)
        // check if the file exists
        if (PSS_File::Exist(m_OpenedFileArray.GetAt(i)))
        {
            ZUFileLauncher fl;

            if (fl.Launch(m_OpenedFileArray.GetAt(i)))
            {
                // todo -cFeature -oJean: show error message
            }
        }
        else
        {
            // todo -cFeature -oJean: show warning message
        }
}
//---------------------------------------------------------------------------
