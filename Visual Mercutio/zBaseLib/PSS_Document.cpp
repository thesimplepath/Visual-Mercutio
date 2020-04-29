/****************************************************************************
 * ==> PSS_Document --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a document                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include <StdAfx.h>
#include "PSS_Document.h"

// processsoft
#include "PSS_PlanFinObjects.h"
#include "PSS_PlanFinObsoleteObjects.h"
#include "PSS_PLFNBoundText.h"
#include "PSS_PLFNRadioBtn.h"
#include "PSS_PLFNCheckBtn.h"
#include "PSS_PLFNBitmap.h"
#include "PSS_PLFNSquare.h"
#include "PSS_PLFNMaskString.h"
#include "PSS_PLFNMultiColumn.h"
#include "PSS_PLFNAutoNumbered.h"
#include "PSS_MsgBox.h"
#include "PSS_View.h"
#include "PSS_HtmlView.h"
#include "PSS_Edit.h"
#include "PSS_DocumentExport.h"
#include "PSS_Global.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_Document, PSS_BaseDocument, g_DefVersion)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_Document, PSS_BaseDocument)
    //{{AFX_MSG_MAP(PSS_Document)
    ON_COMMAND(ID_PAGE_RECALCULATE, OnPageRecalculate)
    ON_COMMAND(ID_PAGE_NEXT, OnPageNext)
    ON_COMMAND(ID_PAGE_PREV, OnPagePrev)
    ON_UPDATE_COMMAND_UI(ID_PAGE_PREV, OnUpdatePagePrev)
    ON_UPDATE_COMMAND_UI(ID_PAGE_NEXT, OnUpdatePageNext)
    ON_COMMAND(ID_PAGE_REFRESH, OnPageRefresh)
    ON_COMMAND(ID_FILE_NEXT, OnFileNext)
    ON_UPDATE_COMMAND_UI(ID_FILE_NEXT, OnUpdateFileNext)
    ON_COMMAND(ID_FILE_PREV, OnFilePrev)
    ON_UPDATE_COMMAND_UI(ID_FILE_PREV, OnUpdateFilePrev)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_Document
//---------------------------------------------------------------------------
PSS_Document::PSS_Document() :
    PSS_BaseDocument(),
    m_pClipBoardObject(NULL),
    m_pEdit(NULL),
    m_pRealTimeExport(NULL),
    m_VersionNumber(0),
    m_ObjectCounter(0),
    m_ActiveDocumentIndex(-1),
    m_VisibleDocumentDataCount(0),
    m_CurrentElement(0),
    m_CurrentTabOrder(0.0),
    m_KeepOnlyFLF(FALSE),
    m_ShowHiddenField(FALSE),
    m_PrintLine(TRUE)
{}
//---------------------------------------------------------------------------
PSS_Document::PSS_Document(const PSS_Document& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_Document::~PSS_Document()
{
    if (m_pRealTimeExport)
    {
        m_pRealTimeExport->EndSynchronization();
        delete m_pRealTimeExport;
    }

    // delete all created temporary files
    PSS_Document::DeleteAllTemporaryFiles();

    // delete all document data
    PSS_Document::RemoveAllDocumentData();

    // Destroy the clipboard
    if (m_pClipBoardObject)
        delete m_pClipBoardObject;

    // delete the edit control
    if (m_pEdit)
        delete m_pEdit;
}
//---------------------------------------------------------------------------
const PSS_Document& PSS_Document::operator = (const PSS_Document& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
void PSS_Document::GetStyleArrayName(CStringArray& styleArray)
{
    PSS_StyleManager& styles     = GetStyleManager();
    const std::size_t styleCount = styles.GetCount();

    for (std::size_t i = 0; i < styleCount; ++i)
    {
        PSS_Style* pStyle = styles.GetStyle(i);

        if (pStyle)
            styleArray.Add(pStyle->GetStyleName());
    }
}
//---------------------------------------------------------------------------
int PSS_Document::PreviousVisibleDocumentAvailable(std::size_t documentIndex) const
{
    int i = documentIndex;

    while (--i >= 0)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);

        if (pDocData && pDocData->DocumentDataIsVisible())
            return i;
    }

    return -1;
}
//---------------------------------------------------------------------------
int PSS_Document::NextVisibleDocumentAvailable(std::size_t documentIndex) const
{
    const std::size_t count = GetDocumentDataCount();

    for (std::size_t i = documentIndex + 1; i < count; ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);

        if (pDocData && pDocData->DocumentDataIsVisible())
            return i;
    }

    return -1;
}
//---------------------------------------------------------------------------
PSS_HtmlView* PSS_Document::GetHtmlView()
{
    POSITION pPos  = GetFirstViewPosition();
    CView*   pView = GetNextView(pPos);

    while (pView)
    {
        PSS_HtmlView* pHtmlView = dynamic_cast<PSS_HtmlView*>(pView);

        if (pHtmlView)
            return pHtmlView;

        pView = GetNextView(pPos);
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_Document::InitializeAllAssociations(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->InitializeAllAssociations();

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    pDocDataAt->InitializeAllAssociations();
}
//---------------------------------------------------------------------------
void PSS_Document::CalculateAllFormula(CView* pView, BOOL allPages, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->CalculateAllFormula(pView, allPages);

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    pDocDataAt->CalculateAllFormula(pView, allPages);
}
//---------------------------------------------------------------------------
void PSS_Document::CheckForClearCalcField(CView* pView, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->CheckForClearCalcField(pView);

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    pDocDataAt->CheckForClearCalcField(pView);
}
//---------------------------------------------------------------------------
void PSS_Document::ClearCurrentAssociation(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->ClearCurrentAssociation();

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    pDocDataAt->ClearCurrentAssociation();
}
//---------------------------------------------------------------------------
void PSS_Document::ChangeFieldForCalculation(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->ChangeFieldForCalculation();

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    pDocDataAt->ChangeFieldForCalculation();
}
//---------------------------------------------------------------------------
void PSS_Document::SchemaListHasChanged(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->SchemaListHasChanged();

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->SchemaListHasChanged();
}
//---------------------------------------------------------------------------
BOOL PSS_Document::IsCalculatedFieldInSchema(PSS_PlanFinObject* pObj, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (!pDocData)
            return FALSE;

        return pDocData->IsCalculatedFieldInSchema(pObj);
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    return pDocDataAt->IsCalculatedFieldInSchema(pObj);
}
//---------------------------------------------------------------------------
void PSS_Document::RefreshCurrentSchema(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->RefreshCurrentSchema();

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    pDocDataAt->RefreshCurrentSchema();
}
//---------------------------------------------------------------------------
void PSS_Document::InitializeAllObjects()
{
    const std::size_t count = GetDocumentDataCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);

        if (pDocData)
            pDocData->InitializeAllObjectPointers();
    }
}
//---------------------------------------------------------------------------
void PSS_Document::ChangeCurrentFile(const CString& name, BOOL notify)
{
    const std::size_t count = GetDocumentDataCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);

        if (pDocData && pDocData->GetStamp().GetTitle() == name)
            ChangeCurrentFile(i, notify);
    }
}
//---------------------------------------------------------------------------
void PSS_Document::ChangeCurrentFile(std::size_t fileIndex, BOOL notify)
{
    CWnd* pWnd = ::AfxGetMainWnd();

    if (!pWnd)
        return;

    PSS_DocumentData* pDocData = GetDocumentDataAt(fileIndex);

    if (!pDocData)
        return;

    if (pDocData->IsExternalBinaryData())
    {}
    else
    if (pDocData->IsURLData())
    {
        if (notify)
            pWnd->SendMessageToDescendants(UM_SETDEFAULTFILE,
                                            0,
                                            LPARAM((const char*)pDocData->GetStamp().GetTemplate()));

        pWnd->SendMessageToDescendants(UM_SHOWHTMLVIEW, 0, LPARAM(this));

        if (!pDocData->GetStamp().GetTemplate().IsEmpty() && GetHtmlView())
            pWnd->SendMessageToDescendants(UM_NAVIGATEURL,
                                            0,
                                            LPARAM((const char*)pDocData->GetStamp().GetTemplate()));
    }
    else
    if (pDocData->IsBinaryDataValid())
    {
        if (notify)
            pWnd->SendMessageToDescendants(UM_SETDEFAULTFILE,
                                            0,
                                            LPARAM((const char*)pDocData->GetStamp().GetTemplate()));

        pWnd->SendMessageToDescendants(UM_SHOWHTMLVIEW, 0, LPARAM(this));

        if (!pDocData->GetFileBufferTemporaryFile().IsEmpty() && GetHtmlView())
            pWnd->SendMessageToDescendants(UM_NAVIGATEURL,
                                            0,
                                            LPARAM((const char*)pDocData->GetFileBufferTemporaryFile()));
    }
    else
    {
        pWnd->SendMessageToDescendants(UM_HIDEHTMLVIEW, 0, LPARAM(this));

        if (notify)
            pWnd->SendMessageToDescendants(UM_SETDEFAULTFILE,
                                            0,
                                            LPARAM((const char*)pDocData->GetStamp().GetTitle()));
    }

    SetActiveDocumentIndex(fileIndex);
}
//---------------------------------------------------------------------------
void PSS_Document::ChangeCurrentFileOpen(const CString& name, BOOL notify)
{
    const std::size_t count = GetDocumentDataCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);

        if (pDocData && pDocData->GetStamp().GetTitle() == name)
            ChangeCurrentFileOpen(i, notify);
    }
}
//---------------------------------------------------------------------------
void PSS_Document::ChangeCurrentFileOpen(std::size_t fileIndex, BOOL notify)
{
    CWnd* pWnd = ::AfxGetMainWnd();

    if (!pWnd)
        return;

    PSS_DocumentData* pDocData = GetDocumentDataAt(fileIndex);

    if (!pDocData)
        return;

    if (pDocData->IsExternalBinaryData())
    {}
    else
    if (pDocData->IsURLData())
    {
        if (notify)
            pWnd->SendMessageToDescendants(UM_SETDEFAULTFILE,
                                           0,
                                           LPARAM((const char*)pDocData->GetStamp().GetTemplate()));

        pWnd->SendMessageToDescendants(UM_SHOWHTMLVIEW, 0, LPARAM(this));

        if (!pDocData->GetStamp().GetTemplate().IsEmpty() && GetHtmlView())
            pWnd->SendMessageToDescendants(UM_NAVIGATEURL,
                                           0,
                                           LPARAM((const char*)pDocData->GetStamp().GetTemplate()));
    }
    else
    if (pDocData->IsBinaryDataValid())
    {
        if (notify)
            pWnd->SendMessageToDescendants(UM_SETDEFAULTFILE,
                                           0,
                                           LPARAM((const char*)pDocData->GetStamp().GetTemplate()));

        pWnd->SendMessageToDescendants(UM_SHOWHTMLVIEW, 0, LPARAM(this));

        if (!pDocData->GetFileBufferTemporaryFile().IsEmpty() && GetHtmlView())
            pWnd->SendMessageToDescendants(UM_NAVIGATEURL,
                                           0,
                                           LPARAM((const char*)pDocData->GetFileBufferTemporaryFile()));
    }
    else
    {
        pWnd->SendMessageToDescendants(UM_HIDEHTMLVIEW, 0, LPARAM(this));

        if (notify)
            pWnd->SendMessageToDescendants(UM_SETDEFAULTFILE,
                                           0,
                                           LPARAM((const char*)pDocData->GetStamp().GetTitle()));
    }

    SetActiveDocumentIndex(fileIndex);
}
//---------------------------------------------------------------------------
CObList& PSS_Document::GetObjectList(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();
        PSS_Assert(pDocData);
        return pDocData->GetObjectList();
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    return pDocDataAt->GetObjectList();
}
//---------------------------------------------------------------------------
int PSS_Document::GetObjectCount(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (!pDocData)
            return 0;

        return pDocData->GetObjectCount();
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        return pDocDataAt->GetObjectCount();

    return 0;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_Document::GetHead(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (!pDocData)
            return NULL;

        return pDocData->GetHead();
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        return pDocDataAt->GetHead();

    return NULL;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_Document::GetNext(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (!pDocData)
            return NULL;

        return pDocData->GetNext();
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        return pDocDataAt->GetNext();

    return NULL;
}
//---------------------------------------------------------------------------
CString PSS_Document::GetStandardSchema() const
{
    return g_OriginalSchema;
}
//---------------------------------------------------------------------------
CString PSS_Document::GetCurrentSchema(int documentIndex) const
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (!pDocData)
            return _T("");

        return pDocData->GetCurrentSchema();
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        return pDocDataAt->GetCurrentSchema();

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_Document::SetCurrentSchema(const CString& name, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->SetCurrentSchema(name);

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->SetCurrentSchema(name);
}
//---------------------------------------------------------------------------
PSS_Formula* PSS_Document::GetFormula(const CString& name, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();
        PSS_Assert(pDocData);
        return pDocData->GetFormula(name);
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    return pDocDataAt->GetFormula(name);
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_Document::GetObject(CString& name, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();
        PSS_Assert(pDocData);
        return pDocData->GetObject(name);
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    return pDocDataAt->GetObject(name);
}
//---------------------------------------------------------------------------
int PSS_Document::GetPageCount(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (!pDocData)
            return 0;

        return pDocData->GetMaxPage();
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        return pDocDataAt->GetMaxPage();

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_Document::SetPageCount(int page, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->SetMaxPage(page);

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->SetMaxPage(page);
}
//---------------------------------------------------------------------------
CString PSS_Document::GetDefaultAssociationString() const
{
    return g_DefaultAssociationString;
}
//---------------------------------------------------------------------------
int PSS_Document::GetCurrentPage(int documentIndex) const
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (!pDocData)
            return -1;

        return pDocData->GetCurrentPage();
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        return pDocDataAt->GetCurrentPage();

    return -1;
}
//---------------------------------------------------------------------------
void PSS_Document::SetCurrentPage(int page, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->SetCurrentPage(page);

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->SetCurrentPage(page);
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_Document::GetSelectedObject(BOOL checkPage, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            return pDocData->GetSelectedObject(checkPage);

        return NULL;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        return pDocDataAt->GetSelectedObject(checkPage);

    return NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::ObjectExist(const CString& name, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            return pDocData->ObjectExist(name);

        return FALSE;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        return pDocDataAt->ObjectExist(name);

    return FALSE;
}
//---------------------------------------------------------------------------
PSS_View* PSS_Document::GetMainView()
{
    POSITION pPos  = GetFirstViewPosition();
    CView*   pView = GetNextView(pPos);

    while (pView)
    {
        PSS_View* pCurView = dynamic_cast<PSS_View*>(pView);

        if (pCurView)
            return pCurView;

        pView = GetNextView(pPos);
    }

    return NULL;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::StartRealTimeExport(BOOL doExport, BOOL doImport)
{
    // check if it's necessary to create a real time synchro. No templates, ExchangeFeedFile required
    if (!DocumentIsTemplate() && GetDocOptions().GetIsSynchronizeExchangeFeedFile())
    {
        if (!IsRealTimeExported())
            // create the real time export process
            if (!CreateRealTimeExport())
                return FALSE;

        if (doExport)
        {
            PSS_DocumentExport* pDocExport = GetRealTimeExport();

            if (pDocExport)
                pDocExport->Export();
        }

        if (doImport)
        {
            PSS_DocumentExport* pDocExport = GetRealTimeExport();

            if (pDocExport)
                pDocExport->Import();
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_Document::DocumentHasBeenModified()
{}
//---------------------------------------------------------------------------
void PSS_Document::FieldHasBeenModified()
{
    if (IsRealTimeExported())
    {
        PSS_DocumentExport* pDocExport = GetRealTimeExport();

        if (pDocExport)
            pDocExport->SourceHasBeenModified();
    }
}
//---------------------------------------------------------------------------
void PSS_Document::RemoveAllDocumentData()
{
    const std::size_t count = GetDocumentDataCount();

    for (std::size_t i = 0; i < count; ++i)
        delete GetDocumentDataAt(i);

    m_DocumentDataArray.RemoveAll();

    // notify the frame that the file list has changed
    FileListHasChanged();
}
//---------------------------------------------------------------------------
PSS_Stamp& PSS_Document::GetStamp(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();
        PSS_Assert(pDocData);
        return pDocData->GetStamp();
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    return pDocDataAt->GetStamp();
}
//---------------------------------------------------------------------------
PSS_SchemaManager& PSS_Document::GetSchema(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();
        PSS_Assert(pDocData);
        return pDocData->GetSchema();
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    return pDocDataAt->GetSchema();
}
//---------------------------------------------------------------------------
void PSS_Document::CalculateForecastedObjectCount()
{
    m_ObjectCounter = 0;

    const std::size_t count = GetDocumentDataCount();

    for (std::size_t i = 0; i < count; ++i)
        m_ObjectCounter += GetDocumentDataAt(i)->GetObjectCount();
}
//---------------------------------------------------------------------------
void PSS_Document::ShowDocumentData(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->ShowDocumentData();

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->ShowDocumentData();
}
//---------------------------------------------------------------------------
void PSS_Document::HideDocumentData(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->HideDocumentData();

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->HideDocumentData();
}
//---------------------------------------------------------------------------
void PSS_Document::ShowAllDocumentData()
{
    const std::size_t count = GetDocumentDataCount();

    for (std::size_t i = 0; i < count; ++i)
        GetDocumentDataAt(i)->ShowDocumentData();
}
//---------------------------------------------------------------------------
void PSS_Document::HideAllDocumentData()
{
    const std::size_t count = GetDocumentDataCount();

    for (std::size_t i = 0; i < count; ++i)
        GetDocumentDataAt(i)->HideDocumentData();
}
//---------------------------------------------------------------------------
BOOL PSS_Document::DocumentDataIsVisible(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            return pDocData->DocumentDataIsVisible();

        return FALSE;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        return pDocDataAt->DocumentDataIsVisible();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::CopyDocumentDataArray(PSS_Document* pDocSrc, BOOL insertAsReadOnly)
{
    return CopyDocumentDataArray(pDocSrc->GetDocumentDataArray(), insertAsReadOnly);
}
//---------------------------------------------------------------------------
BOOL PSS_Document::CopyDocumentDataArray(CObArray& arraySrc, BOOL insertAsReadOnly)
{
    PSS_DocumentData* pDocData;
    const int         arrayCount = arraySrc.GetSize();
    BOOL              error      = FALSE;

    for (int i = 0; i < arrayCount; ++i)
    {
        PSS_DocumentData* pSrcDocData = dynamic_cast<PSS_DocumentData*>(arraySrc.GetAt(i));
        PSS_Assert(pSrcDocData);

        pDocData = pSrcDocData->Clone();
        PSS_Assert(pDocData);
        pDocData->SetDocument(this);

        // set the read-only flag
        pDocData->SetAsReadOnly(insertAsReadOnly);
        error |= !AddDocumentData(pDocData);
    }

    return !error;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::CopyDocumentDataArrayAfter(PSS_Document* pDocSrc, int index, BOOL insertAsReadOnly)
{
    return CopyDocumentDataArrayAfter(pDocSrc->GetDocumentDataArray(), index, insertAsReadOnly);
}
//---------------------------------------------------------------------------
BOOL PSS_Document::CopyDocumentDataArrayAfter(CObArray& arraySrc, int index, BOOL insertAsReadOnly)
{
    BOOL              error = FALSE;
    PSS_DocumentData* pDocData;
    const int         arrayCount = arraySrc.GetSize();

    for (int i = 0; i < arrayCount; ++i)
    {
        PSS_DocumentData* pSrcDocData = dynamic_cast<PSS_DocumentData*>(arraySrc.GetAt(i));
        PSS_Assert(pSrcDocData);

        pDocData = ((PSS_DocumentData*)arraySrc.GetAt(i))->Clone();
        PSS_Assert(pDocData);
        pDocData->SetDocument(this);

        // Set the read-only flag
        pDocData->SetAsReadOnly(insertAsReadOnly);
        error |= !AddDocumentDataAfter(pDocData, index + i);
    }

    return !error;
}
//---------------------------------------------------------------------------
PSS_FontManager& PSS_Document::GetFontManager(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();
        PSS_Assert(pDocData);
        return pDocData->GetFontManager();
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    return pDocDataAt->GetFontManager();
}
//---------------------------------------------------------------------------
PSS_StyleManager& PSS_Document::GetStyleManager(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();
        PSS_Assert(pDocData);
        return pDocData->GetStyleManager();
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    return pDocDataAt->GetStyleManager();
}
//---------------------------------------------------------------------------
void PSS_Document::PropagateFieldValue(PSS_PlanFinObject* pObj, int documentIndex)
{
    switch (documentIndex)
    {
        case -2:
        {
            const std::size_t count = GetDocumentDataCount();

            for (std::size_t i = 0; i < count; ++i)
            {
                PSS_DocumentData* pDocData = GetDocumentDataAt(i);

                if (pDocData)
                    pDocData->PropagateFieldValue(pObj);
            }

            return;
        }

        case -1:
        {
            PSS_DocumentData* pDocData = GetActiveDocumentData();

            if (pDocData)
                pDocData->PropagateFieldValue(pObj);

            return;
        }

        default:
        {
            PSS_DocumentData* pDocData = GetDocumentDataAt(documentIndex);

            if (pDocData)
                pDocData->PropagateFieldValue(pObj);

            return;
        }
    }
}
//---------------------------------------------------------------------------
void PSS_Document::GetDocumentDataName(CStringArray& stringArray, BOOL onlyVisible)
{
    stringArray.RemoveAll();

    const std::size_t count = GetDocumentDataCount();

    for (std::size_t i = 0; i < GetDocumentDataCount(); ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);
        PSS_Assert(pDocData);

        if (!onlyVisible || (onlyVisible && pDocData->DocumentDataIsVisible()))
            stringArray.Add(pDocData->GetStamp().GetTitle());
    }
}
//---------------------------------------------------------------------------
int PSS_Document::FindDocumentData(const CString& name)
{
    for (size_t i = 0; i < GetDocumentDataCount(); ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);
        PSS_Assert(pDocData);

        if (pDocData->GetStamp().GetTitle() == name)
            return i;
    }

    return -1;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::DocumentDataIsReadOnly(int documentIndex) const
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            return pDocData->IsReadOnly();

        return TRUE;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        return pDocDataAt->IsReadOnly();

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_Document::SetDocumentDataAsReadOnly(BOOL value, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->SetAsReadOnly(value);

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->SetAsReadOnly(value);
}
//---------------------------------------------------------------------------
BOOL PSS_Document::DocumentDataIsStandardForm(int documentIndex) const
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            return pDocData->IsStandardForm();

        return FALSE;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        return pDocDataAt->IsStandardForm();

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::DocumentDataIsInternalKeyEqualTo(const CString& key, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            return pDocData->IsInternalKeyEqualTo(key);

        return FALSE;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        return pDocDataAt->IsInternalKeyEqualTo(key);

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::IsReadOnlyAtRuntime(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            return pDocData->IsReadOnlyAtRuntime();

        return NULL;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        return pDocDataAt->IsReadOnlyAtRuntime();

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_Document::SetReadOnlyAtRuntime(BOOL value, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->SetReadOnlyAtRuntime(value);

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->SetReadOnlyAtRuntime(value);
}
//---------------------------------------------------------------------------
void PSS_Document::SetAllDocReadOnlyAtRuntime(BOOL value)
{
    std::size_t count = GetDocumentDataCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);

        if (pDocData)
            pDocData->SetReadOnlyAtRuntime(value);
    }
}
//---------------------------------------------------------------------------
void PSS_Document::ChangeCurrentSchema(const CString& name, BOOL notify, int documentIndex)
{
    switch (documentIndex)
    {
        case -1:
        {
            PSS_DocumentData* pDocData = GetActiveDocumentData();

            if (pDocData)
                pDocData->ChangeCurrentSchema(name, notify);

            return;
        }

        case -2:
        {
            const std::size_t count = GetDocumentDataCount();

            for (std::size_t i = 0; i < count; ++i)
            {
                PSS_DocumentData* pDocData = GetDocumentDataAt(i);

                if (pDocData)
                    pDocData->ChangeCurrentSchema(name, notify);
            }

            return;
        }
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    pDocDataAt->ChangeCurrentSchema(name, notify);
}
//---------------------------------------------------------------------------
void PSS_Document::StartCalcTimer(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->StartCalcTimer();

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->StartCalcTimer();
}
//---------------------------------------------------------------------------
void PSS_Document::ResetCalcTimer(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->ResetCalcTimer();

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->ResetCalcTimer();
}
//---------------------------------------------------------------------------
BOOL PSS_Document::CreateAllTemporaryFileFromBuffer()
{
    const std::size_t count = GetDocumentDataCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);

        if (pDocData)
            pDocData->CreateTemporaryFileFromBuffer();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::DeleteAllTemporaryFiles()
{
    const std::size_t count = GetDocumentDataCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);

        if (pDocData)
            pDocData->DeleteTemporaryFile();
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::ReadDocument(const CString& fileName)
{
    BOOL           result = FALSE;
    CFile          file;
    CFileException fe;

    if (!file.Open(fileName, CFile::modeRead | CFile::shareDenyWrite, &fe))
        return FALSE;

    CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);

    loadArchive.m_pDocument  = this;
    loadArchive.m_bForceFlat = FALSE;

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

    return result;
}
//---------------------------------------------------------------------------
void PSS_Document::OnDraw(CDC* pDC, PSS_View* pView, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->OnDraw(pDC, pView);

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->OnDraw(pDC, pView);
}
//---------------------------------------------------------------------------
void PSS_Document::SwitchTabOrder(PSS_PlanFinObject* pObject, double tabOrder, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->SwitchTabOrder(pObject, tabOrder);

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->SwitchTabOrder(pObject, tabOrder);
}
//---------------------------------------------------------------------------
void PSS_Document::AssignMultiColumnMemberFields(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->AssignMultiColumnMemberFields();

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->AssignMultiColumnMemberFields();
}
//---------------------------------------------------------------------------
void PSS_Document::AssignAllMultiColumnMemberFields()
{
    const std::size_t count = GetDocumentDataCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);

        if (pDocData)
            pDocData->AssignMultiColumnMemberFields();
    }
}
//---------------------------------------------------------------------------
CStringArray* PSS_Document::GetObjectFieldNameArrayOfDocument(int documentIndex) const
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            return pDocData->GetObjectFieldNameArray();

        return NULL;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        return pDocDataAt->GetObjectFieldNameArray();

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_Document::AddFieldNameInObectArray(const CString& fieldName, int documentIndex)
{
    PSS_DocumentData* pDocData = NULL;

    if (documentIndex == -1)
        pDocData = GetActiveDocumentData();
    else
        pDocData = GetDocumentDataAt(documentIndex);

    // if valid document data
    if (pDocData)
    {
        // add new field name in the specific document data
        if (!pDocData->AddFieldNameInObectArray(fieldName))
            return false;

        // add also the fieldname in the global fieldname array
        if (!FieldNameExistInObectArray(fieldName))
            m_FieldNameArray.Add(fieldName);

        // no error
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_Document::BuildObjectFieldNameArray()
{
    // free the object fieldname array
    m_FieldNameArray.RemoveAll();

    const std::size_t docDataCount = GetDocumentDataCount();

    // iterate through all documents
    for (std::size_t i = 0; i < docDataCount; ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);

        if (!pDocData)
            continue;

        // if elements have been built
        if (pDocData->BuildObjectFieldNameArray())
        {
            CStringArray* pFieldNameArrayOfDocData = pDocData->GetObjectFieldNameArray();

            if (!pFieldNameArrayOfDocData)
                continue;

            const std::size_t elementCount = pFieldNameArrayOfDocData->GetSize();

            // iterate through all elements, check if exists, and insert it in the list
            for (std::size_t elementIndex = 0; elementIndex < elementCount; ++elementIndex)
                if (!FieldNameExistInObectArray(pFieldNameArrayOfDocData->GetAt(elementIndex)))
                    m_FieldNameArray.Add(pFieldNameArrayOfDocData->GetAt(elementIndex));
        }
    }

    return m_FieldNameArray.GetSize() > 0;
}
//---------------------------------------------------------------------------
bool PSS_Document::BuildObjectFieldNameArrayOfDocument(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            return pDocData->BuildObjectFieldNameArray();

        return false;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        return pDocDataAt->BuildObjectFieldNameArray();

    return false;
}
//---------------------------------------------------------------------------
PSS_PlanFinObject* PSS_Document::GetEditedObject(BOOL checkPage, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (!pDocData)
            return NULL;

        return pDocData->GetEditedObject(checkPage);
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    return pDocDataAt->GetEditedObject(checkPage);
}
//---------------------------------------------------------------------------
void PSS_Document::SetEditedObject(PSS_PlanFinObject* pObj, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->SetEditedObject(pObj);

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    pDocDataAt->SetEditedObject(pObj);
}
//---------------------------------------------------------------------------
void PSS_Document::CreateAutomaticNewName(PSS_PlanFinObject* pObj)
{
    pObj->SetObjectName(GetAutomaticNewName(pObj));
}
//---------------------------------------------------------------------------
void PSS_Document::CopyObjectToClipBoard(PSS_PlanFinObject* pObj)
{
    if (pObj)
        m_pClipBoardObject = pObj->Clone();
}
//---------------------------------------------------------------------------
void PSS_Document::AssignPredefinedField(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->AssignPredefinedField();

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->AssignPredefinedField();
}
//---------------------------------------------------------------------------
BOOL PSS_Document::ChangeObjectType(PSS_PlanFinObject* pObj,
                                    const CString&     name,
                                    const CString&     finalValue,
                                    BOOL               propagate,
                                    int                documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
        {
            SetModifiedFlag();
            return pDocData->ChangeObjectType(pObj, name, finalValue, propagate);
        }

        return FALSE;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
    {
        SetModifiedFlag();
        return pDocDataAt->ChangeObjectType(pObj, name, finalValue, propagate);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::InsertObject(PSS_PlanFinObject*   pObj,
                                PSS_FieldRepository* pFieldRepository,
                                BOOL                 insertInGlobalRepository,
                                int                  documentIndex,
                                BOOL                 refresh)
{
    if (!pObj)
        return FALSE;

    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
        {
            SetModifiedFlag();
            AddFieldNameInObectArray(pObj->GetObjectName());
            return pDocData->InsertObject(pObj, pFieldRepository, insertInGlobalRepository, refresh);
        }

        return FALSE;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
    {
        SetModifiedFlag();
        AddFieldNameInObectArray(pObj->GetObjectName(), documentIndex);
        return pDocDataAt->InsertObject(pObj, pFieldRepository, insertInGlobalRepository, refresh);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::InsertObjectAtHead(PSS_PlanFinObject*   pObj,
                                      PSS_FieldRepository* pFieldRepository,
                                      BOOL                 insertInGlobalRepository,
                                      int                  documentIndex,
                                      BOOL                 refresh)
{
    if (!pObj)
        return FALSE;

    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
        {
            SetModifiedFlag();
            AddFieldNameInObectArray(pObj->GetObjectName());
            return pDocData->InsertObjectAtHead(pObj, pFieldRepository, insertInGlobalRepository, refresh);
        }

        return FALSE;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
    {
        SetModifiedFlag();
        AddFieldNameInObectArray(pObj->GetObjectName(), documentIndex);
        return pDocDataAt->InsertObjectAtHead(pObj, pFieldRepository, insertInGlobalRepository, refresh);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::DeleteObject(PSS_PlanFinObject* pObj,
                              BOOL                 deleteFromMemory,
                              int                  documentIndex,
                              BOOL                 refresh)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
        {
            SetModifiedFlag();
            return pDocData->DeleteObject(pObj, deleteFromMemory, refresh);
        }

        return FALSE;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
    {
        SetModifiedFlag();
        return pDocDataAt->DeleteObject(pObj, deleteFromMemory, refresh);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::MoveObjectInOrder(PSS_PlanFinObject* pObj, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
        {
            SetModifiedFlag();
            return pDocData->MoveObjectInOrder(pObj);
        }

        return FALSE;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
    {
        SetModifiedFlag();
        return pDocDataAt->MoveObjectInOrder(pObj);
    }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_Document::AssignObjectValue(const CString& name,
                                     const CString& value,
                                     int            page,
                                     int            propagationMode,
                                     BOOL           emptyWhenZero,
                                     int            documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
        {
            SetModifiedFlag();
            pDocData->AssignObjectValue(name, value, page, propagationMode, emptyWhenZero);
        }

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
    {
        SetModifiedFlag();
        pDocDataAt->AssignObjectValue(name, value, page, propagationMode, emptyWhenZero);
    }
}
//---------------------------------------------------------------------------
void PSS_Document::SetCurrentPageToObject(PSS_PlanFinObject* pObj, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->SetCurrentPageToObject(pObj);

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->SetCurrentPageToObject(pObj);
}
//---------------------------------------------------------------------------
BOOL PSS_Document::InsertDocument(const CString& fileName, BOOL insertAsReadOnly, int propagateValue)
{
    return InsertDocumentAfter(fileName, -1, insertAsReadOnly);
}
//---------------------------------------------------------------------------
BOOL PSS_Document::InsertDocumentAfter(const CString& fileName,
                                       int            indexAfter,
                                       BOOL           insertAsReadOnly,
                                       int            propagateValue)
{
    // set silent mode before opening the file
    PSS_Global::SetOpenFileInSilentMode();

    PSS_Document* pNewDocument =
            dynamic_cast<PSS_Document*>(PSS_Global::GetDocTemplate()->OpenDocumentFile((const char*)fileName));

    if (!pNewDocument)
        return FALSE;

    // set the document type, only if the document is correct
    pNewDocument->GetStamp().SetFileType(PSS_Stamp::IE_FD_DocumentType);

    // check if all fonts still available
    CheckDocumentFontAndStyle();

    // before inserting the document, propagate the source document value
    PropagateExternDocumentAllValues(pNewDocument, g_LocateAllDocumentsEmptyOnly, FALSE);

    // propagate the document value to the document
    pNewDocument->PropagateExternDocumentAllValues(this, g_LocateAllDocumentsEmptyOnly, FALSE);

    if (indexAfter == -1)
        CopyDocumentDataArray(pNewDocument, insertAsReadOnly);
    else
        CopyDocumentDataArrayAfter(pNewDocument, indexAfter, insertAsReadOnly);

    pNewDocument->OnCloseDocument();

    // set back silent mode after having opened the file
    PSS_Global::SetOpenFileInSilentMode(FALSE);

    // it's important to initialize all object again
    InitializeAllObjects();

    // count all pages for all document data
    DocumentCountAndSetPages();

    SetModifiedFlag(TRUE);

    // set to the previous file directory
    PSS_Global::SetToFileDirectory();

    // advise the frame that the file list has changed
    FileListHasChanged();

    // set the current file list
    if (GetActiveDocumentIndex() == -1)
        SetActiveDocumentIndex(0);

    ChangeCurrentFile(GetActiveDocumentIndex(), TRUE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::InsertExternalDocument(const CString& fileName, BOOL insertAsReadOnly, int propagateValue)
{
    return InsertExternalDocumentAfter(fileName, -1, insertAsReadOnly);
}
//---------------------------------------------------------------------------
BOOL PSS_Document::InsertExternalDocumentAfter(const CString& fileName,
                                               int            indexAfter,
                                               BOOL           insertAsReadOnly,
                                               int            propagateValue)
{
    PSS_File file(fileName);

    // check if file exists
    if (!file.Exist())
        return FALSE;

    std::unique_ptr<PSS_DocumentData> pNewDocData(new PSS_DocumentData());

    // set the type for Document
    pNewDocData->GetStamp().SetFileType(PSS_Stamp::IE_FD_DocumentType);

    // set the right type for the document
    pNewDocData->GetStamp().SetDocumentDataType(PSS_Stamp::IE_DT_ExternalForm);
    pNewDocData->GetStamp().SetTemplate(fileName);

    int newIndex = 0;

    if (indexAfter == -1)
    {
        AddDocumentData(pNewDocData.get());
        newIndex = GetDocumentDataCount() - 1;
    }
    else
    {
        AddDocumentDataAfter(pNewDocData.get(), indexAfter);
        newIndex = indexAfter + 1;
    }

    pNewDocData.release();

    SetModifiedFlag(TRUE);

    // set to the previous file directory
    PSS_Global::SetToFileDirectory();

    // notify the frame that the file list has changed
    FileListHasChanged();

    // set the current file list
    if (newIndex == -1)
        SetActiveDocumentIndex(0);
    else
        SetActiveDocumentIndex(newIndex);

    // change the current file displayed
    ChangeCurrentFile(GetActiveDocumentIndex(), TRUE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::InsertBinaryDocument(const CString& fileName,
                                        const CString& infoName,
                                        const CString& infoDescription)
{
    return InsertBinaryDocumentAfter(fileName, -1, infoName, infoDescription);
}
//---------------------------------------------------------------------------
BOOL PSS_Document::InsertBinaryDocumentAfter(const CString& fileName,
                                             int            indexAfter,
                                             const CString& infoName,
                                             const CString& infoDescription)
{
    std::unique_ptr<PSS_DocumentData> pNewDocData(new PSS_DocumentData());

    // set the type for Document
    pNewDocData->GetStamp().SetFileType(PSS_Stamp::IE_FD_DocumentType);

    // set the document name
    pNewDocData->GetStamp().SetTitle(infoName);

    // set the document description
    pNewDocData->GetStamp().SetDescription(infoDescription);

    // create the binary buffer from file
    if (!pNewDocData->CreateBufferFromFile(fileName))
        return FALSE;

    int newIndex = 0;

    if (indexAfter == -1)
    {
        AddDocumentData(pNewDocData.get());
        newIndex = GetDocumentDataCount() - 1;
    }
    else
    {
        AddDocumentDataAfter(pNewDocData.get(), indexAfter);
        newIndex = indexAfter + 1;
    }

    pNewDocData.release();

    // count all pages for all document data
    DocumentCountAndSetPages();

    SetModifiedFlag(TRUE);

    // set to the previous file directory
    PSS_Global::SetToFileDirectory();

    // create all file for all file buffered
    CreateAllTemporaryFileFromBuffer();

    // notify the frame that the file list has changed
    FileListHasChanged();

    // set the current file list
    if (newIndex == -1)
        SetActiveDocumentIndex(0);
    else
        SetActiveDocumentIndex(newIndex);

    // change the current file displayed
    ChangeCurrentFile(GetActiveDocumentIndex(), TRUE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::InsertExternalBinaryDocument(const CString& fileName,
                                                const CString& infoName,
                                                const CString& infoDescription)
{
    return InsertExternalBinaryDocumentAfter(fileName, -1, infoName, infoDescription);
}
//---------------------------------------------------------------------------
BOOL PSS_Document::InsertExternalBinaryDocumentAfter(const CString& fileName,
                                                     int            indexAfter,
                                                     const CString& infoName,
                                                     const CString& infoDescription)
{
    PSS_File file(fileName);

    // check if file exists
    if (!file.Exist())
        return FALSE;

    std::unique_ptr<PSS_DocumentData> pNewDocData(new PSS_DocumentData());

    // set the type for Document
    pNewDocData->GetStamp().SetFileType(PSS_Stamp::IE_FD_DocumentType);

    // set the document name
    pNewDocData->GetStamp().SetTitle(infoName);

    // set the document description
    pNewDocData->GetStamp().SetDescription(infoDescription);

    // set the right type for the document
    pNewDocData->GetStamp().SetDocumentDataType(PSS_Stamp::IE_DT_ExternalBinary);
    pNewDocData->GetStamp().SetTemplate(fileName);

    int newIndex = 0;

    if (indexAfter == -1)
    {
        AddDocumentData(pNewDocData.get());
        newIndex = GetDocumentDataCount() - 1;
    }
    else
    {
        AddDocumentDataAfter(pNewDocData.get(), indexAfter);
        newIndex = indexAfter + 1;
    }

    pNewDocData.release();

    SetModifiedFlag(TRUE);

    // set to the previous file directory
    PSS_Global::SetToFileDirectory();

    // notify the frame that the file list has changed
    FileListHasChanged();

    // set the current file list
    if (newIndex == -1)
        SetActiveDocumentIndex(0);
    else
        SetActiveDocumentIndex(newIndex);

    // change the current file displayed
    ChangeCurrentFile(GetActiveDocumentIndex(), TRUE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::InsertURL(const CString& url)
{
    return InsertURLAfter(url, -1);
}
//---------------------------------------------------------------------------
BOOL PSS_Document::InsertURLAfter(const CString& url, int indexAfter)
{
    std::unique_ptr<PSS_DocumentData> pNewDocData(new PSS_DocumentData());

    // set the type for Document
    pNewDocData->GetStamp().SetFileType(PSS_Stamp::IE_FD_DocumentType);

    // set the document name
    pNewDocData->GetStamp().SetTitle(url);

    // set the right type for the document
    pNewDocData->GetStamp().SetDocumentDataType(PSS_Stamp::IE_DT_URL);
    pNewDocData->GetStamp().SetTemplate(url);

    int newIndex = 0;

    if (indexAfter == -1)
    {
        AddDocumentData(pNewDocData.get());
        newIndex = GetDocumentDataCount() - 1;
    }
    else
    {
        AddDocumentDataAfter(pNewDocData.get(), indexAfter);
        newIndex = indexAfter + 1;
    }

    pNewDocData.release();

    SetModifiedFlag(TRUE);

    // set to the previous file directory
    PSS_Global::SetToFileDirectory();

    // Advise the frame that the file list has changed
    FileListHasChanged();

    // set the current file list
    if (newIndex == -1)
        SetActiveDocumentIndex(0);
    else
        SetActiveDocumentIndex(newIndex);

    // change the current file displayed
    ChangeCurrentFile(GetActiveDocumentIndex(), TRUE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::DeleteDocumentAt(int index)
{
    if (index < GetDocumentDataCount())
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(index);

        if (pDocData)
        {
            delete pDocData;
            m_DocumentDataArray.RemoveAt(index);

            // notify the frame that the file list has changed
            FileListHasChanged();

            // if the active document is the deleted document, change it
            if (GetActiveDocumentIndex() == index)
                ChangeCurrentFile(0, TRUE);

            // document has changed
            SetModifiedFlag();
            return TRUE;
        }
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::DeleteDocumentData(PSS_DocumentData* pDocData)
{
    const int index = GetDocumentDataIndex(pDocData);
    return (index != -1 ? DeleteDocumentAt(index) : FALSE);
}
//---------------------------------------------------------------------------
BOOL PSS_Document::PropagateDocumentValue(const CString& name,
                                          const CString& value,
                                          int            propagationMode,
                                          BOOL           emptyWhenZero,
                                          int            documentIndex,
                                          int            page)
{
    PSS_DocumentData* pData = NULL;

    // if does not concern all documents
    if (propagationMode != g_LocateAllDocumentsEmptyOnly && propagationMode != g_LocateAllDocuments)
    {
        // get the document data pointer
        pData = (documentIndex == -1 ? GetActiveDocumentData() : GetDocumentDataAt(documentIndex));

        // if not valid, error
        if (!pData)
            return FALSE;
    }

    // set modification flag
    SetModifiedFlag();

    switch (propagationMode)
    {
        case g_LocateAllDocumentsEmptyOnly:
            // for each document data, call the document function to change the object value
            for (std::size_t i = 0; i < GetDocumentDataCount(); ++i)
            {
                PSS_DocumentData* pDocData = GetDocumentDataAt(i);
                PSS_Assert(pDocData);
                pDocData->AssignObjectValue(name, value, 0, g_LocateAllPagesEmptyOnly, emptyWhenZero);
            }

            break;

        case g_LocateAllDocuments:
            // for each document data, call the document function to change the object value
            for (std::size_t i = 0; i < GetDocumentDataCount(); ++i)
            {
                PSS_DocumentData* pDocData = GetDocumentDataAt(i);
                PSS_Assert(pDocData);
                pDocData->AssignObjectValue(name, value, 0, g_LocateAllPages, emptyWhenZero);
            }

            break;

        case g_LocatePageOnlyEmptyOnly:
        case g_LocateForwardPageEmptyOnly:
        case g_LocateAllPagesEmptyOnly:
        case g_LocatePageOnly:
        case g_LocateForwardPage:
        case g_LocateAllPages:
            PSS_Assert(pData);
            return pData->AssignObjectValue(name, value, page, propagationMode, emptyWhenZero);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::PropagateDocumentValueFromTo(const CString& name,
                                                const CString& value,
                                                int            propagationMode,
                                                BOOL           emptyWhenZero,
                                                int            documentIndexFrom,
                                                int            documentIndexTo,
                                                int            page)
{
    PSS_DocumentData* pData = NULL;

    if (documentIndexTo == -1)
        documentIndexTo = GetDocumentDataCount() - 1;

    // the index should be right
    if (documentIndexFrom > documentIndexTo)
        return FALSE;

    // for each document data, call the document function to change the object value
    for (std::size_t i = documentIndexFrom; i <= documentIndexTo; ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);
        PSS_Assert(pDocData);
        pDocData->AssignObjectValue(name, value, 0, propagationMode, emptyWhenZero);
    }

    // set modification flag
    SetModifiedFlag();
    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::PropagateExternDocumentAllValues(PSS_Document* pDoc,
                                                    int           propagationMode,
                                                    BOOL          emptyWhenZero,
                                                    int           documentIndex,
                                                    int           page)
{
    PSS_Assert(pDoc);

    PSS_PlanFinObject* pObj;
    const std::size_t  docDataCount = pDoc->GetDocumentDataCount();

    // for all fields coming from the extern document, propagate all values. Process only one time per field name.
    // For each object, assign the new value
    for (std::size_t i = 0; i < docDataCount; ++i)
    {
        PSS_DocumentData* pDocData = pDoc->GetDocumentDataAt(i);
        PSS_Assert(pDocData);

        if ((pObj = pDocData->GetHead()) != NULL)
            do
            {
                // if the object is exportable
                if (!pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNAscii))        &&
                    !pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNAutoNumbered)) &&
                    !pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNTwoStates)))
                    continue;

                PSS_PLFNText* pTextObj = dynamic_cast<PSS_PLFNText*>(pObj);

                if (pTextObj && pTextObj->GetIsStatic())
                    continue;

                if (!PropagateDocumentValue(pObj->GetObjectName(),
                                            pObj->GetUnformattedObject(),
                                            propagationMode,
                                            emptyWhenZero,
                                            documentIndex,
                                            page))
                    return FALSE;
            }
            while ((pObj = pDocData->GetNext()) != NULL);
    }

    // set modification flag
    SetModifiedFlag();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::PropagateInternalDocumentAllValues(int  indexFrom,
                                                      int  indexTo,
                                                      int  propagationMode,
                                                      BOOL emptyWhenZero,
                                                      int  documentIndex,
                                                      int  page)
{
    PSS_PlanFinObject *pObj;

    if (indexTo == -1)
        indexTo = GetDocumentDataCount() - 1;

    // the index should be right
    if (indexFrom > indexTo)
        return FALSE;

    // for each object, assign the new value
    for (std::size_t i = indexFrom; i <= indexTo; ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);
        PSS_Assert(pDocData);

        if ((pObj = pDocData->GetHead()) != NULL)
            do
            {
                // if the object is exportable
                if (!pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNAscii))        &&
                    !pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNAutoNumbered)) &&
                    !pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNTwoStates)))
                    continue;

                PSS_PLFNText* pTextObj = dynamic_cast<PSS_PLFNText*>(pObj);

                if (pTextObj && pTextObj->GetIsStatic())
                    continue;

                if (!PropagateDocumentValue(pObj->GetObjectName(),
                                            pObj->GetUnformattedObject(),
                                            propagationMode,
                                            emptyWhenZero,
                                            documentIndex,
                                            page))
                    return FALSE;
            }
            while ((pObj = pDocData->GetNext()) != NULL);
    }

    // set modification flag
    SetModifiedFlag();

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_Document::PropagateInternalDocumentOnDocumentValues(int  inIndexFrom,
                                                             int  inIndexTo,
                                                             int  toIndexFrom,
                                                             int  toIndexTo,
                                                             int  propagationMode,
                                                             BOOL emptyWhenZero)
{
    // for each object, assign the new value
    PSS_PlanFinObject  *pObj;

    if (inIndexTo == -1)
        inIndexTo = GetDocumentDataCount() - 1;

    // the index should be right
    if (inIndexFrom > inIndexTo)
        return FALSE;

    for (std::size_t i = inIndexFrom; i <= inIndexTo; ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);
        PSS_Assert(pDocData);

        if ((pObj = pDocData->GetHead()) != NULL)
            do
            {
                // if the object is exportable
                if (!pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNAscii)) &&
                    !pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNAutoNumbered)) &&
                    !pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNTwoStates)))
                    continue;

                PSS_PLFNText* pTextObj = dynamic_cast<PSS_PLFNText*>(pObj);

                if (pTextObj && pTextObj->GetIsStatic())
                    continue;

                if (!PropagateDocumentValueFromTo(pObj->GetObjectName(),
                                                  pObj->GetUnformattedObject(),
                                                  propagationMode,
                                                  emptyWhenZero,
                                                  toIndexFrom,
                                                  toIndexTo))
                    return FALSE;
            }
            while ((pObj = pDocData->GetNext()) != NULL);
    }

    // set modification flag
    SetModifiedFlag();

    return TRUE;
}
//---------------------------------------------------------------------------
CString PSS_Document::GetAutomaticNewName(PSS_PlanFinObject* pObj, int documentIndex)
{
    PSS_Assert(pObj);

    PSS_DocumentData* pDocData = NULL;

    if (documentIndex == -1)
        pDocData = GetActiveDocumentData();
    else
        pDocData = GetDocumentDataAt(documentIndex);

    PSS_Assert(pDocData);

    // check the class type
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNAutoNumbered)))
        return pDocData->BuildAutomaticNewName(_T("ANumbered"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNLine)))
        return pDocData->BuildAutomaticNewName(_T("Ln"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNRect)))
        return pDocData->BuildAutomaticNewName(_T("Rct"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNNumbered)))
        return pDocData->BuildAutomaticNewName(_T("Numb"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNStatic)))
        return pDocData->BuildAutomaticNewName(_T("Stc"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNTime)))
        return pDocData->BuildAutomaticNewName(_T("Tm"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNNumbEdit)))
        return pDocData->BuildAutomaticNewName(_T("NumbEdt"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNMaskString)))
    {
        if (static_cast<PSS_PLFNString*>(pObj)->GetKeepHistory())
            return pDocData->BuildAutomaticNewName(_T("MskTxt"));

        return pDocData->BuildAutomaticNewName(_T("MskTxtHist"));
    }
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNBoundText)))
        return pDocData->BuildAutomaticNewName(_T("BndTxt"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNStringHistory)))
        return pDocData->BuildAutomaticNewName(_T("StrHist"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNString)))
        return pDocData->BuildAutomaticNewName(_T("Str"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNNumHistory)))
        return pDocData->BuildAutomaticNewName(_T("$NumHist"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNNumbNumEdit)))
        return pDocData->BuildAutomaticNewName(_T("$NumbNumEdt"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNLong)))
        return pDocData->BuildAutomaticNewName(_T("$Number"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNSquare)))
        return pDocData->BuildAutomaticNewName(_T("Squ"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNText)))
        return pDocData->BuildAutomaticNewName(_T("Text"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNAscii)))
        return pDocData->BuildAutomaticNewName(_T("Ascii"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNRadioBtn)))
        return pDocData->BuildAutomaticNewName(_T("Radio"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNCheckBtn)))
        return pDocData->BuildAutomaticNewName(_T("Chk"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNBitmap)))
        return pDocData->BuildAutomaticNewName(_T("Bmp"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNGraphic)))
        return pDocData->BuildAutomaticNewName(_T("Ascii"));
    else
    if (pObj->IsKindOf(RUNTIME_CLASS(PSS_PLFNMultiColumn)))
        return pDocData->BuildAutomaticNewName(_T("MultiC"));

    return _T("");
}
//---------------------------------------------------------------------------
void PSS_Document::OnCloseDocument()
{
    PSS_BaseDocument::OnCloseDocument();

    if (!PSS_Global::OpenFileInSilentMode())
    {
        CWnd* pWnd = ::AfxGetMainWnd();

        // notify the framework, that this file is closed
        if (pWnd)
            pWnd->SendMessageToDescendants(UM_DOCUMENTHASBEENSELECTED, 0, LPARAM(NULL));
    }
}
//---------------------------------------------------------------------------
void PSS_Document::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
        SerializeWrite(ar);
    else
        SerializeRead(ar);
}
//---------------------------------------------------------------------------
void PSS_Document::SerializeRead(CArchive& ar)
{
    // read informations. Check if the stamp has been set for next generation of files
    WORD    stamp = 0xFFFF;
    CString schemaName;
    long    internalVersion;
    WORD    wValue;

    TRY
    {
        PSS_BaseDocument::Serialize(ar);

        ar >> wValue;
        m_ObjectCounter = int(wValue);
        internalVersion = GetDocumentStamp().GetInternalVersion();

        if (internalVersion < 11)
            ar >> schemaName;
    }
    CATCH(CArchiveException, e)
    {
        // set for more recent file
        if (e->m_cause == CArchiveException::badSchema)
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_FILEGENERATEDNEWERVER, MB_OK);
            THROW_LAST();
        }

        stamp           = 0;
        m_ObjectCounter = int(stamp);

        // put the default schema name
        schemaName = g_OriginalSchema;
    }
    END_CATCH

    PSS_DocumentData* pNewDocument = NULL;

    if (internalVersion < 11)
    {
        std::unique_ptr<PSS_DocumentData> pNewDoc(new PSS_DocumentData(this));

        // copy the file stamp
        pNewDoc->GetStamp() = (PSS_Stamp&)GetDocumentStamp();
        pNewDoc->SetCurrentSchema(schemaName);

        // add the document data pointer
        if (!AddDocumentData(pNewDoc.get()))
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_FILECORRUPTED, MB_OK);
        }

        pNewDocument = pNewDoc.release();

        SetActiveDocumentIndex(0);
    }

    if (internalVersion >= 11)
    {
        if (internalVersion < 17)
        {
            // serialize the active document index
            ar >> wValue;

            if (wValue == 0xFFFF)
                m_ActiveDocumentIndex = -1;
            else
                m_ActiveDocumentIndex = int(wValue);
        }
        else
            ar >> m_ActiveDocumentIndex;

        // serialize the document data array
        SerializeDocumentDataArray(ar);
    }

    if (internalVersion < 11 && pNewDocument)
        if (internalVersion >= 4)
        {
            // serialize the font manager
            pNewDocument->GetFontManager().Serialize(ar);

            // serialize the style manager
            pNewDocument->GetStyleManager().Serialize(ar);
        }

    if (internalVersion < 11 && pNewDocument)
        TRY
        {
            // serialize the list
            pNewDocument->GetObjectList().Serialize(ar);
        }
        CATCH(CArchiveException, e)
        {
            if (stamp == 0xFFFF)
            {
                PSS_MsgBox mBox;
                mBox.Show(IDS_FILECORRUPTED, MB_OK);
                THROW_LAST();
            }
        }
        END_CATCH

    if (internalVersion < 11 && pNewDocument)
    {
        TRY
        {
            if (stamp == 0xFFFF)
            {
                pNewDocument->GetSchema().Serialize(ar);
            }
            else
            {
                pNewDocument->GetSchema().ReadSerializeOldFormat(ar);
            }
        }
        CATCH(CArchiveException, e)
        {
            if (stamp == 0xFFFF)
            {
                PSS_MsgBox mBox;
                mBox.Show(IDS_FILECORRUPTED);
                THROW_LAST();
            }

            // not found, initialize the variable by searching certain information in the file
            // to differentiate the type
            m_VersionNumber = g_DefVersion;
        }
        END_CATCH
    }

    // serialize document options, read information
    if (internalVersion >= 5)
        ar >> m_DocOptions;

    // serialize the history manager
    if (internalVersion >= 9)
        GetHistoryValueManager().Serialize(ar);

    // serialize the synchronization file name
    if (internalVersion >= 10)
        ar >> m_SynchronizationFileName;

    if (internalVersion < 11 && pNewDocument)
    {
        // if the counter does not match with the counter list, notify the user that the formulary
        // should be attached to a new template
        if (GetForecastedObjectCount() != pNewDocument->GetObjectList().GetCount())
        {
            // assign the counter list
            SetForecastedObjectCount(pNewDocument->GetObjectCount());

            PSS_MsgBox mBox;
            mBox.Show(IDS_FILEPROBLEM, MB_OK);
        }

        if (pNewDocument->GetStamp().GetTemplate().IsEmpty())
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_TEMPLATEPROBLEM, MB_OK);
        }
    }

    // after all elements were read, initialize the associations
    InitializeAllObjects();

    // create all buffered files
    CreateAllTemporaryFileFromBuffer();

    // initialize all multi-column field members
    AssignAllMultiColumnMemberFields();
}
//---------------------------------------------------------------------------
void PSS_Document::SerializeWrite(CArchive& ar)
{
    // it is important to initialize all object pointers again
    InitializeAllObjects();

    // check if all fonts still available
    CheckDocumentFontAndStyle();

    // call the base class for serialization
    PSS_BaseDocument::Serialize(ar);

    CalculateForecastedObjectCount();

    ar << WORD(m_ObjectCounter);

    // serialize the active document index, since version 17 directly as int and not WORD
    ar << m_ActiveDocumentIndex;

    // serialize the document data array
    SerializeDocumentDataArray(ar);

    // serialize document options
    ar << GetDocOptions();

    // serialize the history manager
    GetHistoryValueManager().Serialize(ar);

    // serialize the synchronization file name
    ar << m_SynchronizationFileName;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_Document::AssertValid() const
    {
        CDocument::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_Document::Dump(CDumpContext& dc) const
    {
        CDocument::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_Document::OnPageRecalculate()
{
    // check read-only mode
    if (IsReadOnlyAtRuntime())
        return;

    CWnd* pWnd = ::AfxGetMainWnd();

    if (pWnd)
        pWnd->SendMessageToDescendants(ID_CALCULATE_MESSAGE, 0, 0);
}
//---------------------------------------------------------------------------
void PSS_Document::OnPagePrev()
{
    if (GetCurrentPage() - 1 >= 1)
    {
        SetCurrentPage(GetCurrentPage() - 1);
        CalculateAllFormula(GetMainView());

        // kill the current focus if on edit mode
        ::SetFocus(NULL);
        UpdateAllViews(NULL);
    }
}
//---------------------------------------------------------------------------
void PSS_Document::OnPageNext()
{
    if (GetCurrentPage() + 1 <= GetPageCount())
    {
        SetCurrentPage(GetCurrentPage() + 1);
        CalculateAllFormula(GetMainView());

        // kill the current focus if on edit mode
        ::SetFocus(NULL);
        UpdateAllViews(NULL);
    }
}
//---------------------------------------------------------------------------
void PSS_Document::OnUpdatePagePrev(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(GetCurrentPage() > 1);
}
//---------------------------------------------------------------------------
void PSS_Document::OnUpdatePageNext(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(GetCurrentPage() < GetPageCount());
}
//---------------------------------------------------------------------------
void PSS_Document::OnFilePrev()
{
    const int previousIndex = PreviousVisibleDocumentAvailable(GetActiveDocumentIndex());

    if (previousIndex != -1)
    {
        ChangeCurrentFile(previousIndex, TRUE);
        CalculateAllFormula(GetMainView());

        // kill the current focus on edit mode
        ::SetFocus(NULL);
        UpdateAllViews(NULL);
    }
}
//---------------------------------------------------------------------------
void PSS_Document::OnFileNext()
{
    const int nextIndex = NextVisibleDocumentAvailable(GetActiveDocumentIndex());

    if (nextIndex != -1)
    {
        ChangeCurrentFile(nextIndex, TRUE);
        CalculateAllFormula(GetMainView());

        // kill the current focus on edit mode
        ::SetFocus(NULL);
        UpdateAllViews(NULL);
    }
}
//---------------------------------------------------------------------------
void PSS_Document::OnUpdateFilePrev(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(PreviousVisibleDocumentAvailable(GetActiveDocumentIndex()) != -1);
}
//---------------------------------------------------------------------------
void PSS_Document::OnUpdateFileNext(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(NextVisibleDocumentAvailable(GetActiveDocumentIndex()) != -1);
}
//---------------------------------------------------------------------------
void PSS_Document::OnPageRefresh()
{
    UpdateAllViews(NULL);
}
//---------------------------------------------------------------------------
BOOL PSS_Document::OpenDocument(const char* pPathName, BOOL setLastLoaded)
{
    PSS_Global::SetCurrentDocumentForSerialization(this);

    CWaitCursor cursor;

    if (!CDocument::OnOpenDocument(pPathName))
        return FALSE;

    SetPathName(pPathName);

    PSS_DocumentData* pDocData = GetActiveDocumentData();

    if (pDocData)
    {
        // if the formula list is empty, load the standard list instead
        if (pDocData->IsFormData() && pDocData->GetSchema().GetFormulaList(GetCurrentSchema()))
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_FILECORRUPTED, MB_OK);
            return FALSE;
        }

        // because in the previous versions, the calculated fields and the number have different classes,
        // it is necessary to replace calculated fields with number fields with a flag
        if (pDocData->GetStamp().GetInternalVersion() < 1)
            ReplaceCalculatedFields();
    }

    if (!PSS_Global::OpenFileInSilentMode())
    {
        CalculateAllFormula(GetMainView(), TRUE);

        // start the timer for the first time
        StartCalcTimer();

        // count all pages for all document data
        DocumentCountAndSetPages();
        SchemaListHasChanged();

        // initialize the style list
        StyleListHasChanged();

        // initialize the file list
        FileListHasChanged();

        // set the current file list
        ChangeCurrentFile(GetActiveDocumentIndex(), TRUE);

        // go to the first page
        SetCurrentPage(1);

        if (!StartRealTimeExport())
        {
            // in write mode, no chance, file corruption
            PSS_MsgBox mBox;
            mBox.Show(IDS_RTEXPORT_CREATIONFAILED);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_Document::CheckFormulaObject(PSS_PlanFinObject* pOld, PSS_PlanFinObject* pNew, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->CheckFormulaObject(pOld, pNew);

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->CheckFormulaObject(pOld, pNew);
}
//---------------------------------------------------------------------------
BOOL PSS_Document::CreateRealTimeExport()
{
    // check if it's necessary to create a real time synchro. No templates, exchange feed file required
    if (DocumentIsTemplate() || !GetDocOptions().GetIsSynchronizeExchangeFeedFile())
        return TRUE;

    // build the synchronization file name
    const CString file = GetDocOptions().BuildSynchronizationFileName(GetPathName());

    // If the file is empty, out
    if (file.IsEmpty())
        return TRUE;

    if (m_pRealTimeExport)
        delete m_pRealTimeExport;

    // create the object
    m_pRealTimeExport = new PSS_DocumentExport(file,
                                               this,
                                               GetDocOptions().GetSynchronizationHeader(),
                                               GetDocOptions().GetSynchronizationSeparator(),
                                               _T(""),
                                               g_LocateAllPages);

    m_pRealTimeExport->StartSynchronization(GetDocOptions().GetSynchronizeTimeSequence());

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_Document::DeleteAllObjects(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();
        PSS_Assert(pDocData);
        pDocData->DeleteAllObjects();
        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    pDocDataAt->DeleteAllObjects();
}
//---------------------------------------------------------------------------
int PSS_Document::CountAndSetPages(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();
        PSS_Assert(pDocData);
        return pDocData->CountAndSetPages();
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);
    PSS_Assert(pDocDataAt);
    return pDocDataAt->CountAndSetPages();
}
//---------------------------------------------------------------------------
int PSS_Document::DocumentCountAndSetPages()
{
    int pages = 0;

    for (std::size_t i = 0; i < GetDocumentDataCount(); ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);
        PSS_Assert(pDocData);
        pages += pDocData->CountAndSetPages();
    }

    return pages;
}
//---------------------------------------------------------------------------
bool PSS_Document::FieldNameExistInObectArray(const CString& fieldName)
{
    const std::size_t arrayCount = m_FieldNameArray.GetSize();

    for (std::size_t i = 0; i < arrayCount; ++i)
        if (fieldName == m_FieldNameArray.GetAt(i))
            return true;

    return false;
}
//---------------------------------------------------------------------------
void PSS_Document::ReplaceCalculatedFields(int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            pDocData->ReplaceCalculatedFields();

        return;
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        pDocDataAt->ReplaceCalculatedFields();
}
//---------------------------------------------------------------------------
void PSS_Document::CheckDocumentFontAndStyle()
{
    // iterate through the document data array and check the font validity
    for (std::size_t i = 0; i < GetDocumentDataCount(); ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);
        PSS_Assert(pDocData);
        pDocData->CheckFontValidity();
    }
}
//---------------------------------------------------------------------------
CString PSS_Document::BuildAutomaticNewName(const CString& prefix, int documentIndex)
{
    if (documentIndex == -1)
    {
        PSS_DocumentData* pDocData = GetActiveDocumentData();

        if (pDocData)
            return pDocData->BuildAutomaticNewName(prefix);

        return _T("");
    }

    PSS_DocumentData* pDocDataAt = GetDocumentDataAt(documentIndex);

    if (pDocDataAt)
        return pDocDataAt->BuildAutomaticNewName(prefix);

    return _T("");
}
//---------------------------------------------------------------------------
int PSS_Document::GetDocumentDataIndex(PSS_DocumentData* pDocData)
{
    if (!pDocData)
        return -1;

    const int docCount = GetDocumentDataCount();

    for (int i = 0; i < docCount; ++i)
    {
        PSS_DocumentData* pData = GetDocumentDataAt(i);

        if (pData && pData == pDocData)
            return i;
    }

    return -1;
}
//---------------------------------------------------------------------------
std::size_t PSS_Document::CalculateVisibleDocumentDataCount()
{
    // initialize the counter
    m_VisibleDocumentDataCount = 0;

    const std::size_t docCount = GetDocumentDataCount();

    for (std::size_t i = 0; i < docCount; ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);
        PSS_Assert(pDocData);

        if (pDocData->DocumentDataIsVisible())
            ++m_VisibleDocumentDataCount;
    }

    return m_VisibleDocumentDataCount;
}
//---------------------------------------------------------------------------
void PSS_Document::SerializeDocumentDataArray(CArchive& ar)
{
    if (ar.IsStoring())
        SerializeDocumentDataArrayWrite(ar);
    else
        SerializeDocumentDataArrayRead(ar);
}
//---------------------------------------------------------------------------
void PSS_Document::SerializeDocumentDataArrayRead(CArchive& ar)
{
    m_DocumentDataArray.Serialize(ar);

    for (size_t i = 0; i < GetDocumentDataCount(); ++i)
    {
        PSS_DocumentData* pDocData = GetDocumentDataAt(i);
        PSS_Assert(pDocData);
        pDocData->SetDocument(this);
    }
}
//---------------------------------------------------------------------------
void PSS_Document::SerializeDocumentDataArrayWrite(CArchive& ar)
{
    // do nothing else than serializing the array
    m_DocumentDataArray.Serialize(ar);
}
//---------------------------------------------------------------------------
