/****************************************************************************
 * ==> PSS_DocumentReadWrite -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a document reader and writer                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_DocumentReadWrite.h"

// std
#include <Io.h>

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_DocumentExport.h"
#include "zBaseLib\PSS_DocumentData.h"
#include "zBaseLib\PSS_Edit.h"
#include "zBaseLib\PSS_GlobalFieldManager.h"
#include "zBaseLib\PSS_FileDialog.h"
#include "zWinUtil32\PSS_NewFormDialog.h"
#include "zWinUtil32\PSS_FolderInfoDialog.h"
#include "zWinUtil32\PSS_DocOptionDialog.h"
#if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
    #include "formasc.h"
    #include "shcpydlg.h"
    #include "schcrtdl.h"
    #include "schname.h"
    #include "SelStyle.h"
    #include "styledef.h"
    #include "wzattach.h"
    #include "FrmMng.h"
#endif
#include "PSS_App.h"

// resources
#include "Resources.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_DocumentReadWrite, PSS_Document, g_DefVersion)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DocumentReadWrite, PSS_Document)
    //{{AFX_MSG_MAP(PSS_DocumentReadWrite)
    ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
    ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
    ON_COMMAND(ID_FILE_SAVE, OnFileSave)
    ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
    ON_COMMAND(ID_IMPORT, OnImport)
    ON_COMMAND(ID_EXPORT, OnExport)
    ON_COMMAND(ID_FILE_OPTIONS, OnFileOptions)
    ON_COMMAND(ID_FILE_PROPERTY, OnFileProperty)
    ON_COMMAND(ID_FORMULA_SCENARIO_ASSOCIATE, OnFormulaScenarioAssociate)
    ON_COMMAND(ID_FORMULA_SCHEMA_COPY, OnFormulaScenarioCopy)
    ON_COMMAND(ID_FORMULA_SCHEMA_CREATION, OnFormulaScenarioCreation)
    ON_COMMAND(ID_FORMULA_SCHEMA_DELETE, OnFormulaScenarioDelete)
    ON_COMMAND(ID_PAGE_DELETE, OnPageDelete)
    ON_COMMAND(ID_FORM_ATTACH, OnFormAttach)
    ON_COMMAND(ID_FORM_MANAGE, OnFormManage)
    ON_COMMAND(ID_DEFINE_STYLE, OnDefineStyle)
    ON_COMMAND(ID_CHANGE_STYLE, OnChangeStyle)
    ON_COMMAND(ID_INSERTNEWPAGE, OnInsertNewPage)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
PSS_DocumentReadWrite::PSS_DocumentReadWrite() :
    PSS_Document()
{}
//---------------------------------------------------------------------------
PSS_DocumentReadWrite::PSS_DocumentReadWrite(const PSS_DocumentReadWrite& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_DocumentReadWrite::~PSS_DocumentReadWrite()
{}
//---------------------------------------------------------------------------
const PSS_DocumentReadWrite& PSS_DocumentReadWrite::operator = (const PSS_DocumentReadWrite& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentReadWrite::CopyPage(PSS_DocumentReadWrite* pTargetDoc,
                                     int                    pageIndex,
                                     int                    sourceDocIndex,
                                     int                    destDocIndex)
{
    if (!pTargetDoc)
        return FALSE;

    if (sourceDocIndex == -1)
    {
        PSS_DocumentData* pSrcDocData = GetActiveDocumentData();
        
        if (!pSrcDocData)
            return FALSE;

        PSS_DocumentData* pDestDocData = pTargetDoc->GetDocumentDataAt(destDocIndex);

        if (!pDestDocData)
            return false;

        return pSrcDocData->CopyPage(pDestDocData, pageIndex);
    }

    PSS_DocumentData* pSrcDocDataAt = GetDocumentDataAt(sourceDocIndex);

    if (!pSrcDocDataAt)
        return FALSE;

    PSS_DocumentData* pDestDocDataAt = pTargetDoc->GetDocumentDataAt(destDocIndex);

    if (!pDestDocDataAt)
        return FALSE;

    return pSrcDocDataAt->CopyPage(pDestDocDataAt, pageIndex);
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentReadWrite::CopyPageOnlyObjects(PSS_DocumentReadWrite* pTargetDoc,
                                                int                    pageIndex,
                                                int                    sourceDocIndex,
                                                int                    destDocIndex)
{
    if (!pTargetDoc)
        return FALSE;

    if (sourceDocIndex == -1)
    {
        PSS_DocumentData* pSrcDocData = GetActiveDocumentData();

        if (!pSrcDocData)
            return FALSE;

        PSS_DocumentData* pDestDocData = pTargetDoc->GetDocumentDataAt(destDocIndex);

        if (!pDestDocData)
            return false;

        return pSrcDocData->CopyPageOnlyObjects(pDestDocData, pageIndex);
    }

    PSS_DocumentData* pSrcDocDataAt = GetDocumentDataAt(sourceDocIndex);

    if (!pSrcDocDataAt)
        return FALSE;

    PSS_DocumentData* pDestDocDataAt = pTargetDoc->GetDocumentDataAt(destDocIndex);

    if (!pDestDocDataAt)
        return FALSE;

    return pSrcDocDataAt->CopyPageOnlyObjects(pDestDocDataAt, pageIndex);
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentReadWrite::CopyPageOnlyFormula(PSS_DocumentReadWrite* pTargetDoc,
                                                int                    pageIndex,
                                                int                    sourceDocIndex,
                                                int                    destDocIndex)
{
    if (!pTargetDoc)
        return FALSE;

    if (sourceDocIndex == -1)
    {
        PSS_DocumentData* pSrcDocData = GetActiveDocumentData();

        if (!pSrcDocData)
            return FALSE;

        PSS_DocumentData* pDestDocData = pTargetDoc->GetDocumentDataAt(destDocIndex);

        if (!pDestDocData)
            return false;

        return pSrcDocData->CopyPageOnlyFormula(pDestDocData, pageIndex);
    }

    PSS_DocumentData* pSrcDocDataAt = GetDocumentDataAt(sourceDocIndex);

    if (!pSrcDocDataAt)
        return FALSE;

    PSS_DocumentData* pDestDocDataAt = pTargetDoc->GetDocumentDataAt(destDocIndex);

    if (!pDestDocDataAt)
        return FALSE;

    return pSrcDocDataAt->CopyPageOnlyFormula(pDestDocDataAt, pageIndex);
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentReadWrite::DeletePage(int pageIndex, int docIndex)
{
    if (docIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (!pDocData)
            return FALSE;

        return pDocData->DeletePage(pageIndex);
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(docIndex);

    if (!pDocDataAt)
        return FALSE;

    return pDocDataAt->DeletePage(pageIndex);
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::MoveContents(PSS_DocumentReadWrite* pDocument,
                                         BOOL                   copyFormat,
                                         int                    sourceDocIndex,
                                         int                    destDocIndex)
{
    if (!pDocument)
        return;

    if (sourceDocIndex == -1)
    {
        PSS_DocumentData* pDocData       = GetActiveDocumentData();
        PSS_DocumentData* pTargetDocData = pDocument->GetActiveDocumentData();

        if (pDocData && pTargetDocData)
            pDocData->MoveContents(pTargetDocData, copyFormat);

        return;
    }

    PSS_DocumentData* pDocDataAt       = GetDocumentDataAt(sourceDocIndex);
    PSS_DocumentData* pTargetDocDataAt = pDocument->GetDocumentDataAt(destDocIndex);

    if (pDocDataAt && pTargetDocDataAt)
        pDocDataAt->MoveContents(pTargetDocDataAt, copyFormat);
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::SetCurrentStyle(const CString& name, int docIndex)
{
    if (docIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (!pDocData)
            return;

        pDocData->SetCurrentStyle(name);
        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(docIndex);

    if (!pDocDataAt)
        return;

    pDocDataAt->SetCurrentStyle(name);
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::StyleHasBeenDeleted(PSS_Style::Handle hStyle, int docIndex)
{
    if (docIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (!pDocData)
            return;

        pDocData->StyleHasBeenDeleted(hStyle);
        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(docIndex);

    if (!pDocDataAt)
        return;

    pDocDataAt->StyleHasBeenDeleted(hStyle);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_DocumentReadWrite::AssertValid() const
    {
        PSS_Document::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_DocumentReadWrite::Dump(CDumpContext& dc) const
    {
        PSS_Document::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnUpdateFileSave(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(IsModified());
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnUpdateFileSaveAs(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!GetKeepOnlyFLF());
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnImport()
{
    PSS_App* pApp = PSS_App::GetApp();

    if (!pApp)
        return;

    CString title;
    VERIFY(title.LoadString(IDS_IMPORTFILE_CHOOSETITLE));

    // set the "*.txt" files filter
    CString filter;
    VERIFY(filter.LoadString(IDS_EXPORTFILE_FILTER));

    filter += (char)'\0';
    filter += _T("*.txt");
    filter += (char)'\0';

    // append the "*.*" all files filter
    CString allFilter;
    VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));

    filter += allFilter;
    filter += (char)'\0';
    filter += _T("*.*");
    filter += (char)'\0';

    PSS_FileDialog fileDialog(title, filter, 2, pApp->GetFileDirectory());

    if (fileDialog.DoModal() == IDOK)
    {
        PSS_DocumentExport exportText(fileDialog.GetFileName(),
                                      this,
                                      GetDocOptions().GetSynchronizationHeader(),
                                      GetDocOptions().GetSynchronizationSeparator(),
                                      pApp->GetExportSchemaName(),
                                      pApp->GetExportPropagationMode(),
                                      pApp->GetEmptyWhenZero());

        exportText.Import();

        // recalculate formulas
        CalculateAllFormula(GetMainView(), TRUE);

        // refresh the view
        UpdateAllViews(NULL);

        // has been modified
        SetModifiedFlag();
    }
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnExport()
{
    PSS_App* pApp = PSS_App::GetApp();

    if (!pApp)
        return;

    CString title;
    VERIFY(title.LoadString(IDS_EXPORTFILE_CHOOSETITLE));

    // set the "*.txt" files filter
    CString filter;
    VERIFY(filter.LoadString(IDS_EXPORTFILE_FILTER));

    filter += (char)'\0';
    filter += _T("*.txt");
    filter += (char)'\0';

    // append the "*.*" all files filter
    CString allFilter;
    VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));

    filter += allFilter;
    filter += (char)'\0';
    filter += _T("*.*");
    filter += (char)'\0';

    PSS_FileDialog fileDialog(title, filter, 2, pApp->GetFileDirectory());

    if (fileDialog.DoModal() == IDOK)
    {
        PSS_DocumentExport exportText(fileDialog.GetFileName(),
                                      this,
                                      GetDocOptions().GetSynchronizationHeader(),
                                      GetDocOptions().GetSynchronizationSeparator(),
                                      pApp->GetExportSchemaName(),
                                      pApp->GetExportPropagationMode(),
                                      pApp->GetEmptyWhenZero());

        exportText.Export();
    }
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnFileOptions()
{
    #if defined(_ZDESIGNER)
        PSS_DocOptionDlg docOptionDlg(&GetDocOptions());

        // if option must be changed
        if (docOptionDlg.DoModal() == IDOK)
        {
            SetModifiedFlag(TRUE);
            UpdateAllViews(NULL);
        }
    #endif
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnFileProperty()
{
    PSS_FolderInfoDialog folderInfoDialog(&GetDocumentStamp(), TRUE);
    folderInfoDialog.DoModal();
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnFileSave()
{
    if (GetKeepOnlyFLF())
    {
        // export values
        if (!StartRealTimeExport(TRUE))
        {
            // in write mode no chance, file corruption
            PSS_MsgBox mBox;
            mBox.Show(IDS_RTEXPORT_CREATIONFAILED);
        }

        return;
    }

    CDocument::OnFileSave();

    // initialize the file list
    FileListHasChanged();
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnFileSaveAs()
{
    if (!GetKeepOnlyFLF())
        CDocument::OnFileSaveAs();

    // initialize the file list
    FileListHasChanged();
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnFormulaScenarioAssociate()
{
    #if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
        PSS_PlanFinObject*   pObj = GetSelectedObject();
        PSS_FormulaAssociate formulaAssociate(pObj);
        formulaAssociate.DoModal();

        CWnd* pWnd = ::AfxGetMainWnd();

        // deselect all objects
        if (pWnd)
            pWnd->SendMessageToDescendants(ID_FIELD_DESELECTALLOBJECT);
    #endif
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnFormulaScenarioCopy()
{
    #if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
        PSS_SchemaCopyDlg schemaCopyDlg;
        BOOL              doContinue;
        BOOL              hasChanged = FALSE;

        schemaCopyDlg.m_sCurrentSchema = GetCurrentSchema();

        do
        {
            doContinue = FALSE;

            if (schemaCopyDlg.DoModal() == IDOK)
            {
                PSS_DocumentData* pDocData = GetActiveDocumentData();

                if (pDocData)
                {
                    // check if the schema already exist
                    if (pDocData->GetSchema().GetFormulaList(schemaCopyDlg.m_sNewSchemaName))
                    {
                        PSS_MsgBox mBox;
                        CString    prompt;

                        ::AfxFormatString1(prompt, IDS_ALREADYEXIST_SCENARIO, GetCurrentSchema());

                        if (mBox.Show(prompt) == IDYES)
                            doContinue = TRUE;
                    }
                    else
                    if (!pDocData->GetSchema().CopySchema(pDocData->GetCurrentSchema(), schemaCopyDlg.m_sNewSchemaName))
                    {
                        PSS_MsgBox mBox;
                        CString    prompt;

                        ::AfxFormatString1(prompt, IDS_UNABLETOCOPY_CURRENTSCENARIO, GetCurrentSchema());

                        if (mBox.Show(prompt) == IDYES)
                            doContinue = TRUE;
                    }

                    // set the type and the description
                    PSS_FormulaSchema* pSource;
                    pSource = static_cast<PSS_FormulaSchema*>(pDocData->GetSchema().GetFormulaSchema(schemaCopyDlg.m_sNewSchemaName));
                    pSource->SetDescription(schemaCopyDlg.m_sDescription);

                    hasChanged = TRUE;
                }
            }
        }
        while (doContinue);

        if (hasChanged)
        {
            ChangeCurrentSchema(schemaCopyDlg.m_sNewSchemaName);
            SchemaListHasChanged();
        }
    #endif
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnFormulaScenarioCreation()
{
    #if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
        PSS_SchemaCreateDlg schemaCreateDlg;

        if (schemaCreateDlg.DoModal() == IDOK)
        {
            // create an empty schema
            PSS_EnterSchemaName enterSchemaName;
            BOOL                doContinue;

            do
            {
                doContinue = FALSE;

                if (enterSchemaName.DoModal() == IDOK)
                {
                    PSS_DocumentData* pDocData = GetActiveDocumentData();

                    if (pDocData)
                    {
                        // check if the schema already exist
                        if (pDocData->GetSchema().GetFormulaList(enterSchemaName.m_sSchemaName) ||
                            enterSchemaName.m_sSchemaName.IsEmpty())
                        {
                            PSS_MsgBox mBox;
                            CString    prompt;

                            ::AfxFormatString1(prompt, IDS_ALREADYEXIST_SCENARIO, GetCurrentSchema());

                            if (mBox.Show(prompt) == IDYES)
                                doContinue = TRUE;
                        }
                        else
                        {
                            pDocData->GetSchema().Create(enterSchemaName.m_sSchemaName);

                            PSS_FormulaSchema* pSource;
                            pSource = static_cast<PSS_FormulaSchema*>(pDocData->GetSchema().GetFormulaSchema(enterSchemaName.m_sSchemaName));
                            pSource->SetDescription(enterSchemaName.m_sDescription);
                        }
                    }
                }
                else
                    return;
            }
            while (doContinue);

            ChangeCurrentSchema(enterSchemaName.m_sSchemaName);
            SchemaListHasChanged();
        }
        else
            // copy before a schema
            OnFormulaScenarioCopy();
    #endif
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnFormulaScenarioDelete()
{
    const CString schema = GetCurrentSchema();

    if (schema == g_OriginalSchema)
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_CANNOTDELETE_ORIGINALSCENARIO, MB_OK);
    }
    else
    {
        PSS_MsgBox mBox;
        CString    prompt;

        ::AfxFormatString1(prompt, IDS_CONFIRMDELETION_CURRENTSCENARIO, schema);

        if (mBox.Show(prompt) == IDYES)
        {
            PSS_DocumentData* pDocData = GetActiveDocumentData();

            if (pDocData)
                pDocData->GetSchema().DeleteFormulaList(pDocData->GetCurrentSchema());

            // Set the new current schema. By default, the original
            ChangeCurrentSchema(g_OriginalSchema);
            SchemaListHasChanged();
        }
    }
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnDefineStyle()
{
    #if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
        PSS_StyleDefDlg styleDefDlg;
        styleDefDlg.DoModal();

        // notify the combo to be changed
        StyleListHasChanged();

        UpdateAllViews(NULL);
        SetModifiedFlag();
    #endif
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnChangeStyle()
{
    #if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
        PSS_PlanFinObject* pObj = GetSelectedObject();

        if (!pObj)
        {
            PSS_View* pMainView = GetMainView();

            if (!pMainView)
                return;

            // call the selector tool
            pObj = pMainView->SelectObject();

            if (!pObj)
                return;
        }

        PSS_SelectStyleDlg selectStyleDlg;

        if (selectStyleDlg.DoModal() == IDOK)
        {
            pObj->SetStyle(selectStyleDlg.GetSelectedStyle());
            UpdateAllViews(NULL);
            SetModifiedFlag();
        }
    #endif
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnInsertNewPage()
{
    SetPageCount(GetPageCount() + 1);
    UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnFormAttach()
{
    #if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
        // before starting to attach, check if the document was modified. If yes, ask to save it
        if (IsModified())
        {
            CString  format;
            format.LoadString(IDS_DOCUMENTMODIFIED_ASKCONFIRMATION_FORMATTACH);

            char buffer[500];
            wsprintf(buffer, (const char*)format, (const char*)m_strPathName);

            PSS_MsgBox mBox;

            switch (mBox.Show(buffer))
            {
                case IDYES:
                    if (!DoSave(m_strPathName))
                        // don't continue
                        return;

                    break;

                case IDNO:
                    SetModifiedFlag(FALSE);
                    break;

                case IDCANCEL:
                    // don't continue
                    return;

                default:
                    ASSERT(FALSE);
                    break;
            }
        }

        PSS_WizardAttachForm wizardAttachForm(this);

        if (wizardAttachForm.DoModal() != IDOK)
            return;
    #endif
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnPageDelete()
{
    PSS_MsgBox mBox;

    switch (mBox.Show(IDS_CONFIRMCURRENTPAGEDELETION, MB_YESNO))
    {
        case IDYES:
            // continue and delete page
            break;

        case IDNO:
            // don't continue
            return;

        default:
            ASSERT(FALSE);
            break;
    }

    if (!DeletePage(GetCurrentPage()))
        mBox.Show(IDS_DELETEPAGE_ERROR);
}
//---------------------------------------------------------------------------
void PSS_DocumentReadWrite::OnFormManage()
{
    #if defined(_ZDESIGNER) || defined(_ZSCRIPTOR)
        PSS_ManageForms manageForms;
        manageForms.DoModal();
    #endif
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentReadWrite::BuildTemplateName(CString& str)
{
    PSS_App* pApp = PSS_App::GetApp();

    if (!pApp)
        return FALSE;

    PSS_DocumentData* pDocData = GetActiveDocumentData();

    if (!pDocData)
        return FALSE;

    return pApp->BuildTemplateName(str, pDocData->GetStamp());
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentReadWrite::SaveModified()
{
    if (!IsModified())
        return TRUE;

    if (DocumentIsTemplate())
        return FALSE;

    PSS_App* pApp = PSS_App::GetApp();

    if (!pApp)
        return FALSE;

    // get document name/title
    CString name = m_strPathName;

    if (name.IsEmpty())
    {
        name = m_strTitle;

        if (name.IsEmpty())
            VERIFY(name.LoadString(AFX_IDS_UNTITLED));
    }

    // if it's the normal template, cannot be changed
    if (!m_strPathName.CompareNoCase(pApp->GetNormalTemplate()))
        return TRUE;

    CString prompt;

    if (DocumentIsTemplate())
        ::AfxFormatString1(prompt, IDP_ASK_TO_SAVE_TEMPLATE, name);
    else
        ::AfxFormatString1(prompt, IDP_ASK_TO_SAVE, name);

    PSS_MsgBox mBox;

    switch (mBox.Show(prompt))
    {
        case IDYES:
            // either save or update, as appropriate
            if (_access(m_strPathName, 6) && !GetKeepOnlyFLF())
            {
                // if no access to the file in read/write
                if (!DoSave(NULL))
                    return FALSE;
            }
            else
            if (!DoSave(m_strPathName))
                return FALSE;

            break;

        case IDNO:
            // if not saving changes, revert the document
            break;

        case IDCANCEL:
            return FALSE;

        default:
            ASSERT(FALSE);
            break;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentReadWrite::OnNewDocument()
{
    PSS_Global::SetCurrentDocumentForSerialization(this);
    PSS_NewFormDialog newFormDialog(&PSS_Global::GetTemplateManager(),
                                    PSS_NewFormDialog::IE_T_StartForm,
                                    PSS_NewFormDialog::IE_ET_Form);

    if (newFormDialog.DoModal() == IDCANCEL)
        return FALSE;

    if (!OpenDocument((const char*)newFormDialog.GetFileName(), FALSE))
        return FALSE;

    // set the document type
    GetDocumentStamp().SetFileType(PSS_Stamp::IE_FD_DocumentType);
    AssignPredefinedField();

    // empty the path name
    m_strPathName.Empty();
    ChangeCurrentSchema(GetStandardSchema(), TRUE);

    // initialize the style list
    StyleListHasChanged();

    // initialize the file list
    FileListHasChanged();

    // set to the previous file directory
    PSS_Global::SetToFileDirectory();

    if (!StartRealTimeExport())
    {
        // in write mode no chance, file corruption
        PSS_MsgBox mBox;
        mBox.Show(IDS_RTEXPORT_CREATIONFAILED);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentReadWrite::OnOpenDocument(const char* pPathName)
{
    return PSS_Document::OnOpenDocument(pPathName);
}
//---------------------------------------------------------------------------
BOOL PSS_DocumentReadWrite::OnSaveDocument(const char* pPathName)
{
    BOOL result = TRUE;

    if (!GetKeepOnlyFLF())
    {
        // set the last opened file name
        if (!DocumentIsTemplate())
        {
            PSS_App* pApp = PSS_App::GetApp();

            if (pApp)
                pApp->SetLastLoadedFileName(pPathName);
        }

        result = CDocument::OnSaveDocument(pPathName);

        // change the document name
        SetPathName(pPathName);
    }

    if (!StartRealTimeExport(TRUE))
    {
        // in write mode no chance, file corruption
        PSS_MsgBox mBox;
        mBox.Show(IDS_RTEXPORT_CREATIONFAILED);
    }

    return result;
}
//---------------------------------------------------------------------------
