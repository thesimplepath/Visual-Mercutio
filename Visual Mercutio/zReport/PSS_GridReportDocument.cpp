/****************************************************************************
 * ==> PSS_GridReportDocument ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid report document                            *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GridReportDocument.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "PSS_GridView.h"
#include "PSS_GenericGridReportGenerator.h"

// resources
#include "zReportRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
static PSS_GenericGridReportGenerator* g_pGenerator = NULL;
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
GXIMPLEMENT_DYNCREATE(PSS_GridReportDocument, PSS_GridDocument)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_GridReportDocument, PSS_GridDocument)
    //{{AFX_MSG_MAP(PSS_GridReportDocument)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_GridReportDocument
//---------------------------------------------------------------------------
PSS_GridReportDocument::PSS_GridReportDocument() :
    PSS_GridDocument(),
    PSS_GridReportGenerator(),
    m_pGenerator(NULL),
    m_ViewRequireDataRefresh(false)
{}
//---------------------------------------------------------------------------
PSS_GridReportDocument::~PSS_GridReportDocument()
{
    if (m_pGenerator)
        delete m_pGenerator;
}
//---------------------------------------------------------------------------
bool PSS_GridReportDocument::SetNewReportGridGenerator(PSS_GenericGridReportGenerator* pGenerator)
{
    if (GetPrimaryDocument() == this)
        if (pGenerator)
        {
            if (m_pGenerator)
                delete m_pGenerator;

            m_pGenerator = pGenerator;

            // after the the new generator assignement, the frame title may change
            UpdateFrameTitle();

            // initialize the grid
            return InitializeGrid();
        }

    PSS_GridReportDocument* pReportDoc = dynamic_cast<PSS_GridReportDocument*>(GetPrimaryDocument());

    return (pReportDoc ? pReportDoc->SetNewReportGridGenerator(pGenerator) : false);
}
//---------------------------------------------------------------------------
std::size_t PSS_GridReportDocument::GetGeneratorTabCount() const
{
    if (GetPrimaryDocument() == this)
        return (m_pGenerator ? m_pGenerator->GetGeneratorTabCount() : 0);

    PSS_GridReportDocument* pReportDoc = dynamic_cast<PSS_GridReportDocument*>(GetPrimaryDocument());

    // call the function from the primary document
    return (pReportDoc ? pReportDoc->GetGeneratorTabCount() : 0);
}
//---------------------------------------------------------------------------
const CString PSS_GridReportDocument::GetGeneratorTabName(std::size_t index)
{
    if (GetPrimaryDocument() == this)
        return (m_pGenerator ? m_pGenerator->GetGeneratorTabName(index) : _T(""));

    PSS_GridReportDocument* pReportDoc = dynamic_cast<PSS_GridReportDocument*>(GetPrimaryDocument());

    // call the function from the primary document
    return (pReportDoc ? pReportDoc->GetGeneratorTabName(index) : _T(""));
}
//---------------------------------------------------------------------------
bool PSS_GridReportDocument::FillGrid(CGXGridCore& gridCore, std::size_t index)
{
    if (GetPrimaryDocument() == this)
        return (m_pGenerator ? m_pGenerator->FillGrid(gridCore, index) : true);

    PSS_GridReportDocument* pReportDoc = dynamic_cast<PSS_GridReportDocument*>(GetPrimaryDocument());

    // call the function from the primary document
    return (pReportDoc ? pReportDoc->FillGrid(gridCore, index) : true);
}
//---------------------------------------------------------------------------
int PSS_GridReportDocument::GetReportTypeID() const
{
    if (GetPrimaryDocument() == this)
        return (m_pGenerator ? m_pGenerator->GetReportTypeID() : -1);

    PSS_GridReportDocument* pReportDoc = dynamic_cast<PSS_GridReportDocument*>(GetPrimaryDocument());

    // call the function from the primary document
    return (pReportDoc ? pReportDoc->GetReportTypeID() : -1);
}
//---------------------------------------------------------------------------
void PSS_GridReportDocument::SetReportTypeID(int typeID)
{
    if (GetPrimaryDocument() == this)
        if (m_pGenerator)
            m_pGenerator->SetReportTypeID(typeID);

    PSS_GridReportDocument* pReportDoc = dynamic_cast<PSS_GridReportDocument*>(GetPrimaryDocument());

    // call the function from the primary document
    if (pReportDoc)
        pReportDoc->SetReportTypeID(typeID);
}
//---------------------------------------------------------------------------
const CString PSS_GridReportDocument::GetReportTitle() const
{
    if (GetPrimaryDocument() == this)
        return (m_pGenerator ? m_pGenerator->GetReportTitle() : _T(""));

    PSS_GridReportDocument* pReportDoc = dynamic_cast<PSS_GridReportDocument*>(GetPrimaryDocument());

    // Call the function from the primary document
    return (pReportDoc ? pReportDoc->GetReportTitle() : _T(""));
}
//---------------------------------------------------------------------------
bool PSS_GridReportDocument::IsReportDataExternal() const
{
    if (GetPrimaryDocument() == this)
        return (m_pGenerator ? m_pGenerator->IsReportDataExternal() : false);

    PSS_GridReportDocument* pReportDoc = dynamic_cast<PSS_GridReportDocument*>(GetPrimaryDocument());

    // call the function from the primary document
    return (pReportDoc ? pReportDoc->IsReportDataExternal() : false);
}
//---------------------------------------------------------------------------
bool PSS_GridReportDocument::ReportDataMustBeReloaded() const
{
    if (GetPrimaryDocument() == this)
        return (m_pGenerator ? m_pGenerator->ReportDataMustBeReloaded() : false);

    PSS_GridReportDocument* pReportDoc = dynamic_cast<PSS_GridReportDocument*>(GetPrimaryDocument());

    // Call the function from the primary document
    return (pReportDoc ? pReportDoc->ReportDataMustBeReloaded() : false);
}
//---------------------------------------------------------------------------
bool PSS_GridReportDocument::UseAutomaticReload() const
{
    if (GetPrimaryDocument() == this)
        return (m_pGenerator ? m_pGenerator->UseAutomaticReload() : false);

    PSS_GridReportDocument* pReportDoc = dynamic_cast<PSS_GridReportDocument*>(GetPrimaryDocument());

    // call the function from the primary document
    return (pReportDoc ? pReportDoc->UseAutomaticReload() : false);
}
//---------------------------------------------------------------------------
bool PSS_GridReportDocument::SetAllTabNameToGrid()
{
    const std::size_t completeTabCount = GetGeneratorTabCount();

    // fill all tabs
    for (std::size_t i = 0; i < completeTabCount; ++i)
        // set the tab name
        SetTabName(GetGeneratorTabName(i), i);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridReportDocument::OnPostInitialized(CGXTabWndMgr* pMgr, CGXAppAdapter* pAppAdapt, bool newFile)
{
    if (!newFile)
    {
        // required since don't know why objective grid sets the primary document as
        // the last document, and not on this document, which is the master document
        // after the read. In CreateTabs function, the manager changes the primary document
        // to the last document. This generates a situation where the last document has
        // a primary document pointer to itself and all the others have the primary
        // document pointer set to this document
        ASSERT(pMgr);
        ASSERT(pAppAdapt);

        // get the tab create info array
        CArray<CGXTabCreateInfo*, CGXTabCreateInfo*>* pTabInfoArray = pMgr->GetTabCreateInfoArray();

        // get the size
        const int count = pTabInfoArray->GetSize();

        for (int i = 0; i < count; ++i)
        {
            CGXTabCreateInfo* pInfo = pTabInfoArray->GetAt(i);
            ASSERT(pInfo);

            if (pInfo->GetDocument())
                pInfo->GetDocument()->SetPrimaryDocument(this);
        }

        if (IsReportDataExternal() && ReportDataMustBeReloaded())
        {
            // set the m_ViewRequireDataRefresh to true. This will force the view to
            // fill the grid again when the OnInitialUpdate() function will be called
            m_ViewRequireDataRefresh = true;

            // if don't use automatic reload, ask the question before
            if (!UseAutomaticReload())
            {
                PSS_MsgBox mBox;

                if (mBox.Show(IDS_MASTERDATA_CHANGE_RELOAD, MB_YESNO) == IDNO)
                    // set the m_ViewRequireDataRefresh to false. This will not allow the
                    // view to fill the grid again when the OnInitialUpdate() function will
                    // be called
                    m_ViewRequireDataRefresh = false;
            }

            InitializeGrid();
        }
        else
            // reload all tab names from the generator
            SetAllTabNameToGrid();

        // reset the flag
        m_ViewRequireDataRefresh = false;
    }

    // get the first document view
    PSS_GridView* pView = GetFirstView();

    // set the popup submenu
    if (pView)
        pView->SetPopupMenu(IDR_GRIDREPORT_SUBMENU);

    return true;
}
//---------------------------------------------------------------------------
BOOL PSS_GridReportDocument::OnOpenDocument(LPCTSTR pPathName)
{
    // reset the generator
    g_pGenerator = NULL;

    // set to false. If necessary, will be set to true later
    m_ViewRequireDataRefresh = false;

    if (!PSS_GridDocument::OnOpenDocument(pPathName))
        return FALSE;

    // if a valid generator is defined, sssign it to the primary document
    if (g_pGenerator)
    {
        PSS_GridReportDocument* pReportDoc = dynamic_cast<PSS_GridReportDocument*>(GetPrimaryDocument());

        if (pReportDoc)
        {
            pReportDoc->AssignGenerator(g_pGenerator);
            g_pGenerator->SetDocument(pReportDoc);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_GridReportDocument::OnPreDataFilled(std::size_t index)
{
    if (GetPrimaryDocument() == this)
    {
        if (m_pGenerator)
            m_pGenerator->OnPreDataFilled(index);

        return;
    }

    PSS_GridReportDocument* pReportDoc = dynamic_cast<PSS_GridReportDocument*>(GetPrimaryDocument());

    // call the function from the primary document
    if (pReportDoc)
        pReportDoc->OnPreDataFilled(index);
}
//---------------------------------------------------------------------------
void PSS_GridReportDocument::OnPostDataFilled(std::size_t index)
{
    if (GetPrimaryDocument() == this)
    {
        if (m_pGenerator)
        {
            m_pGenerator->OnPostDataFilled(index);

            // change the modified flag
            SetModifiedFlag();
        }

        return;
    }

    PSS_GridReportDocument* pReportDoc = dynamic_cast<PSS_GridReportDocument*>(GetPrimaryDocument());

    // call the function from the primary document
    if (pReportDoc)
        pReportDoc->OnPostDataFilled(index);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GridReportDocument::AssertValid() const
    {
        PSS_GridDocument::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GridReportDocument::Dump(CDumpContext& dc) const
    {
        PSS_GridDocument::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_GridReportDocument::WorkBookSerialize(CArchive& ar)
{
    PSS_GridDocument::WorkBookSerialize(ar);

    if (ar.IsStoring())
        ar << m_pGenerator;
    else
    {
        ar >> m_pGenerator;

        // if a generator is defined and not the primary document
        if (m_pGenerator)
        {
            // save the generator for further assignement. Cannot assign through
            // the GetPrimaryDocument() function, since it isn't yet assigned
            g_pGenerator = m_pGenerator;

            // reset the generator
            m_pGenerator = NULL;
        }
    }
}
//---------------------------------------------------------------------------
bool PSS_GridReportDocument::InitializeGenerator()
{
    if (GetPrimaryDocument() == this)
        return (m_pGenerator ? m_pGenerator->Initialize() : false);

    PSS_GridReportDocument* pReportDoc = dynamic_cast<PSS_GridReportDocument*>(GetPrimaryDocument());

    // call the function from the primary document
    return (pReportDoc ? pReportDoc->InitializeGenerator() : false);
}
//---------------------------------------------------------------------------
bool PSS_GridReportDocument::InitializeGrid()
{
    if (!InitializeGenerator())
        return false;

    // at least one tab is required
    if (!GetGeneratorTabCount())
        return false;

    // check if needed to remove tabs. Don't remove all tabs, just the difference if positive
    if (GetGeneratorTabCount() < GetGridTabCount())
        for (int i = GetGridTabCount() - GetGeneratorTabCount(); i > 0; --i)
            DeleteGridTab();

    // for each tab, fill the grid param
    const std::size_t existingGridTabCount = GetGridTabCount();

    // if needed, create additional tabs
    const std::size_t completeTabCount = GetGeneratorTabCount();

    for (std::size_t i = existingGridTabCount; i < completeTabCount; ++i)
        // by inserting new tab, a new view is created and the OnInitialUpdate() function
        // is called, which fill the grid by calling the FillGrid() function for the right
        // index view
        InsertNewGridTab();

    // change the tab name
    for (std::size_t i = 0; i < completeTabCount; ++i)
        SetTabName(GetGeneratorTabName(i), i);

    // need to fill all tabs
    for (std::size_t i = 0; i < completeTabCount; ++i)
    {
        // get the adequate grid param pointer
        CGXGridCore* pGridCore = GetTabGridCore(i);

        if (!pGridCore)
            continue;

        // lock any drawing
        const BOOL old = pGridCore->LockUpdate();

        // disable undo mechanism for the following commands
        pGridCore->GetParam()->EnableUndo(FALSE);

        // Call the call-back function
        OnPreDataFilled(i);

        // fill the grid parameter
        FillGrid(*pGridCore, i);

        // call the callback function
        OnPostDataFilled(i);

        // reenable undo mechanism
        pGridCore->GetParam()->EnableUndo(TRUE);

        // unlock drawing
        pGridCore->LockUpdate(old);

        // just to certify that everything is redrawn
        pGridCore->Redraw();
    }

    // set the modified flag to true
    SetModifiedFlag();

    return true;
}
//---------------------------------------------------------------------------
