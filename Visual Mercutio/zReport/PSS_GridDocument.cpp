/****************************************************************************
 * ==> PSS_GridDocument ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid document                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GridDocument.h"

// std
#include <memory>

// processsoft
#include "PSS_GridView.h"
#include "PSS_GridChildFrame.h"
#include "PSS_GridGroup.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
GXIMPLEMENT_DYNCREATE(PSS_GridDocument, CGXDocument)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_GridDocument, CGXDocument)
    //{{AFX_MSG_MAP(PSS_GridDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_GridDocument
//---------------------------------------------------------------------------
PSS_GridDocument::PSS_GridDocument() :
    CGXDocument(),
    m_pParam(NULL),
    m_FrozenRow(0),
    m_FrozenCol(0),
    m_FrozenHeaderRow(0),
    m_FrozenHeaderCol(0)
{}
//---------------------------------------------------------------------------
PSS_GridDocument::~PSS_GridDocument()
{
    // NOTE use the fully qualified name here to avoid to call a pure virtual function on destruction
    PSS_GridDocument::DeleteContents();
}
//---------------------------------------------------------------------------
bool PSS_GridDocument::SetNewGridParam(CGXGridParam* pParam)
{
    if (pParam)
    {
        DeleteContents();
        m_pParam = pParam;
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
CGXGridParam* PSS_GridDocument::GetGridParam(std::size_t index)
{
    PSS_GridDocument* pDoc = GetDocumentAt(index);
    return (pDoc ? pDoc->GetGridParam() : NULL);
}
//---------------------------------------------------------------------------
CGXTabCreateInfo* PSS_GridDocument::GetTabCreateInfo(std::size_t index)
{
    if (index >= GetGridTabCount())
        return NULL;

    CGXTabWndMgr* pMgr = GetPrimaryDocument()->GetTabManager();

    if (!pMgr)
        return NULL;

    CArray<CGXTabCreateInfo*, CGXTabCreateInfo*>* pTabInfoArray = pMgr->GetTabCreateInfoArray();

    return pTabInfoArray->GetAt(index);
}
//---------------------------------------------------------------------------
PSS_GridDocument* PSS_GridDocument::GetDocumentAt(std::size_t index)
{
    CGXTabCreateInfo* pTabInfo = GetTabCreateInfo(index);

    if (!pTabInfo)
        return NULL;

    return dynamic_cast<PSS_GridDocument*>(pTabInfo->GetDocument());
}
//---------------------------------------------------------------------------
CGXTabWnd* PSS_GridDocument::GetTabWnd(std::size_t index)
{
    PSS_GridDocument* pDoc = GetDocumentAt(index);

    if (pDoc)
        return (pDoc->GetFirstView() ? pDoc->GetFirstView()->GetTabWnd() : NULL);

    return NULL;
}
//---------------------------------------------------------------------------
PSS_GridView* PSS_GridDocument::GetTabView(std::size_t index)
{
    PSS_GridDocument* pDoc = GetDocumentAt(index);
    return (pDoc ? pDoc->GetFirstView() : NULL);
}
//---------------------------------------------------------------------------
CGXGridCore* PSS_GridDocument::GetTabGridCore(std::size_t index)
{
    return GetTabView(index);
}
//---------------------------------------------------------------------------
PSS_GridView* PSS_GridDocument::GetFirstView()
{
    POSITION pPos  = GetFirstViewPosition();
    CView*   pView = GetNextView(pPos);

    while (pView)
    {
        PSS_GridView* pGridView = dynamic_cast<PSS_GridView*>(pView);

        if (pGridView)
            return pGridView;

        pView = GetNextView(pPos);
    }

    return NULL;
}
//---------------------------------------------------------------------------
const CString PSS_GridDocument::GetTabName(std::size_t index)
{
    if (GetPrimaryDocument() == this)
    {
        CGXTabWnd* pTabWnd = GetTabWnd(index);

        if (!pTabWnd)
            return _T("");

        return pTabWnd->GetTabName(index);
    }

    PSS_GridDocument* pPrimaryDoc = dynamic_cast<PSS_GridDocument*>(GetPrimaryDocument());

    // call the function from the primary document
    return (pPrimaryDoc ? pPrimaryDoc->GetTabName(index) : _T(""));
}
//---------------------------------------------------------------------------
void PSS_GridDocument::SetTabName(const CString& name, std::size_t index)
{
    if (GetPrimaryDocument() == this)
    {
        CGXTabWnd* pTabWnd = GetTabWnd(index);

        if (!pTabWnd)
            return;

        pTabWnd->SetTabName(index, name);
        return;
    }

    PSS_GridDocument* pPrimaryDoc = dynamic_cast<PSS_GridDocument*>(GetPrimaryDocument());

    // call the function from the primary document
    if (pPrimaryDoc)
        pPrimaryDoc->SetTabName(name, index);
}
//---------------------------------------------------------------------------
void PSS_GridDocument::SetPathName(LPCTSTR pPathName, BOOL addToMRU)
{
    CGXTabWndMgr* pMgr = (GetPrimaryDocument() ? GetPrimaryDocument()->GetTabManager() : NULL);

    if (pMgr)
    {
        // get the tab create info array
        CArray<CGXTabCreateInfo*, CGXTabCreateInfo*>* pTabInfoArray = pMgr->GetTabCreateInfoArray();

        // get the size
        const int count = pTabInfoArray->GetSize();

        for (int i = 0; i < count; ++i)
        {
            CGXTabCreateInfo* pInfo = pTabInfoArray->GetAt(i);
            PSS_Assert(pInfo);

            PSS_GridDocument* pDoc = dynamic_cast<PSS_GridDocument*>(pInfo->GetDocument());

            if (pDoc)
                pDoc->BaseClassSetPathName(pPathName, addToMRU);
        }

        return;
    }

    CGXDocument::SetPathName(pPathName, addToMRU);
}
//---------------------------------------------------------------------------
std::size_t PSS_GridDocument::GetGridTabCount() const
{
    CGXDocument* pDoc = GetPrimaryDocument();
    PSS_Assert(pDoc);

    CGXTabWndMgr* pTabManager = pDoc->GetTabManager();
    return (pTabManager ? pTabManager->GetTabCount() : 0);
}
//---------------------------------------------------------------------------
bool PSS_GridDocument::DeleteGridTab(std::size_t index)
{
    CGXDocument* pDoc = GetPrimaryDocument();
    PSS_Assert(pDoc);

    CGXTabWndMgr* pTabManager = pDoc->GetTabManager();

    if (pTabManager)
        return pTabManager->DeleteWorkSheet(index);

    return false;
}
//---------------------------------------------------------------------------
void PSS_GridDocument::InitializeGroupControls(PSS_GridView* pView)
{
    IGridGroupIterator it(&m_GroupCtrlSet);

    for (PSS_GridGroup* pCtrl = it.GetFirst(); pCtrl; pCtrl = it.GetNext())
        if (!pCtrl->GetGridCore())
        {
            pCtrl->SetGridCore(pView);
            pCtrl->CreateControl();
        }
}
//---------------------------------------------------------------------------
void PSS_GridDocument::InsertGroupCtrl(ROWCOL         row,
                                       ROWCOL         col,
                                       int            coveringCells,
                                       bool           horizontal,
                                       bool           collapsed,
                                       const CString& label,
                                       const CString& tooltipText)
{
    PSS_GridView* pView = GetFirstView();

    std::unique_ptr<PSS_GridGroup> pCtrl(new PSS_GridGroup(pView,
                                                           row,
                                                           col,
                                                           coveringCells,
                                                           horizontal,
                                                           collapsed,
                                                           label,
                                                           tooltipText));

    m_GroupCtrlSet.Add(pCtrl.get());
    pCtrl.release();
}
//---------------------------------------------------------------------------
PSS_GridGroup* PSS_GridDocument::SearchGroupCtrl(ROWCOL row, ROWCOL col)
{
    IGridGroupIterator it(&m_GroupCtrlSet);

    for (PSS_GridGroup* pCtrl = it.GetFirst(); pCtrl; pCtrl = it.GetNext())
        if (pCtrl->GetRow() == row && pCtrl->GetCol() == col)
            return pCtrl;

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_GridDocument::RemoveAllGroupCtrl()
{
    // set the iterator to the right entity set
    IGridGroupIterator it(&m_GroupCtrlSet);

    for (PSS_GridGroup* pCtrl = it.GetFirst(); pCtrl; pCtrl = it.GetNext())
        delete pCtrl;

    m_GroupCtrlSet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_GridDocument::DeleteContents()
{
    RemoveAllGroupCtrl();

    if (m_pParam)
    {
        delete m_pParam;
        m_pParam = NULL;
    }
}
//---------------------------------------------------------------------------
BOOL PSS_GridDocument::SaveModified()
{
    POSITION pPos = GetFirstViewPosition();

    while (pPos)
    {
        CView* pView = GetNextView(pPos);
        ASSERT_VALID(pView);

        if (!CanExitGridView(pView))
        {
            CMDIChildWnd* pFrame = dynamic_cast<CMDIChildWnd*>(pView->GetParentFrame());

            if (pFrame)
                pFrame->MDIActivate();

            return FALSE;
        }
    }

    return CDocument::SaveModified();
}
//---------------------------------------------------------------------------
BOOL PSS_GridDocument::CanCloseFrame(CFrameWnd* pFrame)
{
    // certify that views can be deactivated
    CView* pView = pFrame->GetActiveView();

    if (pView && !CanExitGridView(pView))
        return FALSE;

    // check if view may be closed
    return CDocument::CanCloseFrame(pFrame);
}
//---------------------------------------------------------------------------
BOOL PSS_GridDocument::UpdateFrameTitle()
{
    CFrameWnd* pFrame = dynamic_cast<CFrameWnd*>(::AfxGetMainWnd());

    // force the active window title refresh
    if (pFrame && pFrame->GetActiveFrame())
    {
        pFrame->GetActiveFrame()->OnUpdateFrameTitle(TRUE);
        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_GridDocument::CanExitGridView(CView* pView)
{
    if (pView && pView->SendMessage(WM_GX_CANACTIVATE, 0, 0))
        return FALSE;

    // is it a grid?
    CGXGridCore* pGrid = NULL;

    CGXGridView* pGridView = dynamic_cast<CGXGridView*>(pView);

    if (pGridView)
        pGrid = pGridView;

    if (!pGrid)
    {
        CGXGridHandleView* pHandleView = dynamic_cast<CGXGridHandleView*>(pView);

        if (pHandleView)
            pGrid = pHandleView->GetGrid();
    }

    // certify that the current cell can be stored
    if (pGrid && !pGrid->TransferCurrentCell(TRUE, GX_UPDATENOW, FALSE))
        // grid state is invalid, don't close the frame
        return FALSE;

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_GridDocument::BaseClassSetPathName(LPCTSTR pPathName, BOOL addToMRU)
{
    CGXDocument::SetPathName(pPathName, addToMRU);
}
//---------------------------------------------------------------------------
BOOL PSS_GridDocument::OnOpenDocument(LPCTSTR pPathName)
{
    CGXGridParam* pParam = m_pParam;
    m_pParam             = NULL;

    try
    {
        if (!CGXDocument::OnOpenDocument(pPathName))
        {
            SetModifiedFlag(FALSE);
            m_pParam = pParam;
            return FALSE;
        }
    }
    catch (...)
    {
        m_pParam = pParam;
        throw;
    }

    delete pParam;

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL PSS_GridDocument::OnSaveDocument(LPCTSTR pPathName)
{
    // certify that each views current cell is stored
    CGXGridHint hint(gxHintTransferCurrentCell);
    hint.lParam = TRUE;

    UpdateAllViews(NULL, 0, &hint);

    // save the document
    if (!CGXDocument::OnSaveDocument(pPathName))
        return FALSE;

    SetModifiedFlag(FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GridDocument::AssertValid() const
    {
        CGXDocument::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GridDocument::Dump(CDumpContext& dc) const
    {
        CGXDocument::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
BOOL PSS_GridDocument::OnNewDocument()
{
    if (!CGXDocument::OnNewDocument())
        return FALSE;

    DeleteContents();
    SetModifiedFlag();

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_GridDocument::WorkBookSerialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        ar << m_pParam;
        ar << m_FrozenRow;
        ar << m_FrozenCol;
        ar << m_FrozenHeaderRow;
        ar << m_FrozenHeaderCol;
        ar << int(m_GroupCtrlSet.GetSize());

        IGridGroupIterator it(&m_GroupCtrlSet);

        for (PSS_GridGroup* pCtrl = it.GetFirst(); pCtrl; pCtrl = it.GetNext())
            ar << pCtrl;
    }
    else
    {
        ar >> m_pParam;
        ar >> m_FrozenRow;
        ar >> m_FrozenCol;
        ar >> m_FrozenHeaderRow;
        ar >> m_FrozenHeaderCol;

        // before reading elements, remove all the existing ones
        RemoveAllGroupCtrl();

        int            count;
        PSS_GridGroup* pCtrl;

        ar >> count;

        for (int i = 0; i < count; ++i)
        {
            ar >> pCtrl;
            m_GroupCtrlSet.Add(pCtrl);
        }
    }
}
//---------------------------------------------------------------------------
bool PSS_GridDocument::InsertNewGridTabAt(std::size_t index)
{
    PSS_GridView* pView = GetFirstView();
    PSS_Assert(pView);

    PSS_GridChildFrame* pFrame = dynamic_cast<PSS_GridChildFrame*>(pView->GetParentFrame());

    if (!pFrame)
        return false;

    pFrame->InsertWorkSheetHandler();

    return true;
}
//---------------------------------------------------------------------------
