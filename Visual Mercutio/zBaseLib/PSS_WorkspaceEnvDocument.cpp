/****************************************************************************
 * ==> PSS_WorkspaceEnvDocument --------------------------------------------*
 ****************************************************************************
 * Description : Provides a workspace environment document                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WorkspaceEnvDocument.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_WorkspaceEnvDocument, CDocument)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_WorkspaceEnvDocument, CDocument)
    //{{AFX_MSG_MAP(PSS_WorkspaceEnvDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_WorkspaceEnvDocument
//---------------------------------------------------------------------------
PSS_WorkspaceEnvDocument::PSS_WorkspaceEnvDocument() :
    CDocument(),
    m_IsLoaded(false)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceEnvDocument::~PSS_WorkspaceEnvDocument()
{}
//---------------------------------------------------------------------------
bool PSS_WorkspaceEnvDocument::ReadFromFile(const CString& fileName)
{
    CFile          file;
    CFileException fe;

    if (!file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe))
        return FALSE;

    CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);

    loadArchive.m_pDocument  = this;
    loadArchive.m_bForceFlat = FALSE;

    bool result = false;

    TRY
    {
        Serialize(loadArchive);
        result = TRUE;
    }
    CATCH(CArchiveException, e)
    {
        result = FALSE;
    }
    END_CATCH

    loadArchive.Close();
    file.Close();

    // if everything is ok, set the path name
    if (result)
        SetPathName(fileName, FALSE);

    m_IsLoaded = result;

    return result;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceEnvDocument::SaveToFile(const CString& fileName)
{
    CFile          file;
    CFileException fe;

    if (!file.Open(fileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite, &fe))
        return FALSE;

    CArchive saveArchive(&file, CArchive::store | CArchive::bNoFlushOnDelete);

    saveArchive.m_pDocument  = this;
    saveArchive.m_bForceFlat = FALSE;

    bool result = false;

    TRY
    {
        Serialize(saveArchive);
        result = TRUE;
    }
    CATCH(CArchiveException, e)
    {
        result = FALSE;
    }
    END_CATCH

    saveArchive.Close();
    file.Close();

    // once saved, clear the modified flag
    SetModifiedFlag(FALSE);

    return result;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceEnvDocument::Serialize(CArchive& ar)
{
    // serialize the environement
    m_WorkspaceEnvironment.Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_WorkspaceEnvDocument::AssertValid() const
    {
        CDocument::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_WorkspaceEnvDocument::Dump(CDumpContext& dc) const
    {
        CDocument::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
BOOL PSS_WorkspaceEnvDocument::OnNewDocument()
{
    ASSERT(FALSE);
    return FALSE;
}
//---------------------------------------------------------------------------
