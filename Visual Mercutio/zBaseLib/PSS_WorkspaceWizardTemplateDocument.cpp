/****************************************************************************
 * ==> PSS_WorkspaceWizardTemplateDocument ---------------------------------*
 ****************************************************************************
 * Description : Provides a workspace wizard template environment document  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WorkspaceWizardTemplateDocument.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(PSS_WorkspaceWizardTemplateDocument, CDocument)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_WorkspaceWizardTemplateDocument, CDocument)
    //{{AFX_MSG_MAP(PSS_WorkspaceWizardTemplateDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_WorkspaceWizardTemplateDocument
//---------------------------------------------------------------------------
PSS_WorkspaceWizardTemplateDocument::PSS_WorkspaceWizardTemplateDocument() :
    CDocument(),
    m_IsLoaded(false)
{}
//---------------------------------------------------------------------------
PSS_WorkspaceWizardTemplateDocument::~PSS_WorkspaceWizardTemplateDocument()
{}
//---------------------------------------------------------------------------
bool PSS_WorkspaceWizardTemplateDocument::ReadFromFile(const CString& fileName)
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

    // If everything is ok, set the path name
    if (result)
        SetPathName(fileName, FALSE);

    m_IsLoaded = result;

    return result;
}
//---------------------------------------------------------------------------
bool PSS_WorkspaceWizardTemplateDocument::SaveToFile(const CString& fileName)
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

    return result;
}
//---------------------------------------------------------------------------
void PSS_WorkspaceWizardTemplateDocument::Serialize(CArchive& ar)
{
    // serialize the workspace template set
    m_WorkspaceTemplates.Serialize(ar);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_WorkspaceWizardTemplateDocument::AssertValid() const
    {
        CDocument::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_WorkspaceWizardTemplateDocument::Dump(CDumpContext& dc) const
    {
        CDocument::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
BOOL PSS_WorkspaceWizardTemplateDocument::OnNewDocument()
{
    return FALSE;
}
//---------------------------------------------------------------------------
