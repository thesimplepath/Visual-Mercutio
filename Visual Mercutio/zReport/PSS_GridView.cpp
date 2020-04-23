/****************************************************************************
 * ==> PSS_GridView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a grid view                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GridView.h"

// std
#include <memory>

// processsoft
#include "zBaseLib\PSS_FileDialog.h"
#include "zBaseLib\PSS_MsgBox.h"
#include "PSS_GridCheckBox.h"
#include "PSS_GridGroup.h"

// resources
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Static variables
//---------------------------------------------------------------------------
CMenu PSS_GridView::m_PopupMenu;
//---------------------------------------------------------------------------
// Dynamic creation
//---------------------------------------------------------------------------
GXIMPLEMENT_DYNCREATE(PSS_GridView, CGXGridView)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_GridView, CGXGridView)
    //{{AFX_MSG_MAP(PSS_GridView)
    ON_WM_CREATE()
    ON_COMMAND(ID_FILE_EXPORTTEXTFILE, OnExportToTextFile)
    ON_UPDATE_COMMAND_UI(ID_FILE_EXPORTTEXTFILE, OnUpdateExportToTextFile)
    ON_COMMAND(ID_FILE_IMPORTTEXTFILE, OnImportFromTextFile)
    ON_UPDATE_COMMAND_UI(ID_FILE_IMPORTTEXTFILE, OnUpdateImportFromTextFile)
    ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomIn)
    ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMIN, OnUpdateViewZoomIn)
    ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomOut)
    ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMOUT, OnUpdateViewZoomOut)
    ON_COMMAND(ID_FREEZE_SPLITTER, OnFreezeSplitter)
    ON_UPDATE_COMMAND_UI(ID_FREEZE_SPLITTER, OnUpdateFreezeSplitter)
    ON_COMMAND(ID_UNFREEZE_SPLITTER, OnUnfreezeSplitter)
    ON_UPDATE_COMMAND_UI(ID_UNFREEZE_SPLITTER, OnUpdateUnfreezeSplitter)
    ON_COMMAND(ID_GRID_UNHIDEALL, OnUnhideAll)
    ON_UPDATE_COMMAND_UI(ID_GRID_UNHIDEALL, OnUpdateUnhideAll)
    ON_COMMAND(ID_FILE_PRINT, CGXGridView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, CGXGridView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CGXGridView::OnFilePrintPreview)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_GridView
//---------------------------------------------------------------------------
PSS_GridView::PSS_GridView() :
    CGXGridView()
{}
//---------------------------------------------------------------------------
PSS_GridView::~PSS_GridView()
{}
//---------------------------------------------------------------------------
void PSS_GridView::SetupUserAttributes()
{
    CGXGridParam* pParam = GetParam();

    if (!pParam)
        return;

    CGXStylesMap* pStylesMap = pParam->GetStylesMap();

    // register user attributes for the CGXStyleSheet-User Attributes page. Control objects
    // will be created on demand in CGXControlFactory
    pStylesMap->RegisterDefaultUserAttributes();
}
//---------------------------------------------------------------------------
void PSS_GridView::SetupControls()
{
    // owner drawn checkbox
    RegisterControl(GX_IDS_CTRL_CHECKBOX, new PSS_GridCheckBox(this));
}
//---------------------------------------------------------------------------
void PSS_GridView::InsertGroupCtrl(ROWCOL         row,
                                   ROWCOL         col,
                                   int            coveringCells,
                                   bool           horizontal,
                                   bool           collapsed,
                                   const CString& label,
                                   const CString& tooltipText)
{
    PSS_GridDocument* pDoc = GetDocument();

    if (!pDoc)
        return;

    pDoc->InsertGroupCtrl(row,
                          col,
                          coveringCells,
                          horizontal,
                          collapsed,
                          label,
                          tooltipText);
}
//---------------------------------------------------------------------------
PSS_GridGroup* PSS_GridView::SearchGroupCtrl(ROWCOL row, ROWCOL col)
{
    PSS_GridDocument* pDoc = GetDocument();

    if (!pDoc)
        return NULL;

    return pDoc->SearchGroupCtrl(row, col);
}
//---------------------------------------------------------------------------
void PSS_GridView::SetPopupMenu(UINT resID)
{
    // release the previous menu
    if (m_PopupMenu.GetSafeHmenu())
        m_PopupMenu.DestroyMenu();

    m_PopupMenu.LoadMenu(resID);
}
//---------------------------------------------------------------------------
void PSS_GridView::ExportToTextFile()
{
    CString title;
    VERIFY(title.LoadString(IDS_EXPORTFILE_CHOOSETITLE));

    // set the "*.txt" filter
    CString filter;
    VERIFY(filter.LoadString(IDS_EXPORTFILE_FILTER));
    filter += (char)'\0';
    filter += _T("*.txt");
    filter += (char)'\0';

    // append the "*.*" filter
    CString allFilter;
    VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
    filter += allFilter;
    filter += (char)'\0';
    filter += _T("*.*");
    filter += (char)'\0';

    PSS_FileDialog fileDialog(title, filter, 2, _T(""));

    if (fileDialog.DoModal() == IDCANCEL)
        return;

    if (!ExportToTextFile(fileDialog.GetFileName()))
    {
        // in write mode, no chance, file corruption
        PSS_MsgBox mBox;
        mBox.Show(IDS_EXPORTFILE_FAIL);
        return;
    }
}
//---------------------------------------------------------------------------
bool PSS_GridView::ExportToTextFile(const CString& fileName)
{
    CFile textFile;

    if (!textFile.Open(fileName, CFile::modeCreate | CFile::modeWrite))
        return false;

    CopyTextToFile(textFile, CGXRange(0, 1, GetRowCount(), GetColCount()));

    textFile.Close();

    return true;
}
//---------------------------------------------------------------------------
void PSS_GridView::ImportTextFile()
{
    CString title;
    VERIFY(title.LoadString(IDS_IMPORTFILE_CHOOSETITLE));

    // set the "*.txt" filter
    CString filter;
    VERIFY(filter.LoadString(IDS_EXPORTFILE_FILTER));
    filter += (char)'\0';
    filter += _T("*.txt");
    filter += (char)'\0';

    // append the "*.*" filter
    CString allFilter;
    VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
    filter += allFilter;
    filter += (char)'\0';
    filter += _T("*.*");
    filter += (char)'\0';

    PSS_FileDialog fileDialog(title, filter, 2, _T(""));

    if (fileDialog.DoModal() == IDCANCEL)
        return;

    if (!ImportTextFile(fileDialog.GetFileName()))
    {
        PSS_MsgBox mBox;
        mBox.Show(IDS_IMPORTFILE_FAIL);
        return;
    }
}
//---------------------------------------------------------------------------
bool PSS_GridView::ImportTextFile(const CString& fileName)
{
    CFile textFile;

    if (!textFile.Open(fileName, CFile::modeRead))
        return false;

    LPTSTR pszBuffer;
    DWORD  dwSize = (DWORD)textFile.GetLength();
    pszBuffer     = new TCHAR[dwSize];

    try
    {
        textFile.Read(pszBuffer, dwSize);
        PasteTextFromBuffer(pszBuffer, dwSize, CGXRange(0, 1));
        textFile.Close();
    }
    catch (...)
    {
        delete[] pszBuffer;
        throw;
    }

    delete[] pszBuffer;
    return true;
}
//---------------------------------------------------------------------------
void PSS_GridView::FreezeSplitter()
{
    PSS_GridDocument* pDoc = GetDocument();

    if (pDoc && (pDoc->GetFrozenRow() || pDoc->GetFrozenHeaderRow()))
        SetFrozenRows(pDoc->GetFrozenRow(), pDoc->GetFrozenHeaderRow());

    if (pDoc && (pDoc->GetFrozenCol() || pDoc->GetFrozenHeaderCol()))
        SetFrozenCols(pDoc->GetFrozenCol(), pDoc->GetFrozenHeaderCol());
}
//---------------------------------------------------------------------------
void PSS_GridView::UnfreezeSplitter()
{
    SetFrozenRows(0, 0);
    SetFrozenCols(0, 0);
}
//---------------------------------------------------------------------------
void PSS_GridView::UnhideAll()
{
    HideRows(0, GetRowCount(), FALSE);
    HideCols(0, GetColCount(), FALSE);
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GridView::AssertValid() const
    {
        CGXGridView::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_GridView::Dump(CDumpContext& dc) const
    {
        CGXGridView::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
BOOL PSS_GridView::PreCreateWindow(CREATESTRUCT& cs)
{
    return CGXGridView::PreCreateWindow(cs);
}
//---------------------------------------------------------------------------
void PSS_GridView::OnInitialUpdate()
{
    PSS_GridDocument* pDoc = GetDocument();

    if (!pDoc)
        return;

    // is a grid param?
    if (!pDoc->GetGridParam())
    {

        // asks for the grid param creation
        if (!pDoc->CreateGridParam())
            return;

        // set the document to the grid view. FALSE indicates that document is responsible
        // for deleting the object
        SetParam(pDoc->GetGridParam(), FALSE);

        // 60 rows and 15 columns
        SetRowCount(60);
        SetColCount(15);
    }
    else
        // set the document to the grid view. FALSE indicates that document is responsible
        // for deleting the object
        SetParam(pDoc->GetGridParam(), FALSE);

    CGXGridParam* pParam = GetParam();

    if (pParam)
    {
        // custom styles map initialization
        if (!pParam->GetStylesMap())
        {
            // create a styles map and connect it with the parameter object
            std::unique_ptr<CGXStylesMap> pStylesMap(new CGXStylesMap());

            pParam->SetStylesMap(pStylesMap.get());

            // add standard styles
            pStylesMap->CreateStandardStyles();

            SetupUserAttributes();

            pStylesMap->ReadProfile();

            pStylesMap.release();
        }

        // custom initialization of property object
        if (!pParam->GetProperties())
        {
            // create a styles map and connect it with the parameter object
            std::unique_ptr<CGXProperties> pProperties(new CGXProperties());

            pProperties->AddDefaultUserProperties();

            // set the standard properties
            pProperties->SetDisplayHorzLines(TRUE);
            pProperties->SetDisplayVertLines(TRUE);
            pProperties->SetPrintHorzLines  (FALSE);
            pProperties->SetPrintVertLines  (FALSE);

            pProperties->SetPrintColHeaders(FALSE);
            pProperties->SetPrintRowHeaders(FALSE);

            pProperties->ReadProfile();

            pParam->SetProperties(pProperties.get());

            pProperties.release();
        }

        // printer settings custom initialization
        if (!pParam->GetPrintDevice())
        {
            // initialize printer object if some default settings is required
            // for the grid printing, e.g print landscape
        }

        CGXGridView::OnInitialUpdate();

        // register all the view controls
        SetupControls();

        EnableHints(FALSE);

        // lock any drawing
        const BOOL old = LockUpdate();

        // initialize the grid data. Disable undo mechanism for the following commands
        pParam->EnableUndo(FALSE);

        // floating cells mode. The other possible mode for floating cells is gxnFloatEvalOnDisplay 
        SetFloatCellsMode(gxnFloatDelayEval);

        // re-enable the undo mechanism
        pParam->EnableUndo(TRUE);

        // unlock drawing
        LockUpdate(old);
    }

    // certify that everything is redrawn
    Invalidate();

    // enable Objective Grid internal update-hint mechanism. The below line should be written
    // as a last command in the OnInitialUpdate() function, because as long as EnableHints() is
    // not called, the document modified flag will not be updated
    EnableHints();
}
//---------------------------------------------------------------------------
BOOL PSS_GridView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}
//---------------------------------------------------------------------------
void PSS_GridView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    CGXGridView::OnBeginPrinting(pDC, pInfo);
}
//---------------------------------------------------------------------------
void PSS_GridView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    CGXGridView::OnEndPrinting(pDC, pInfo);
}
//---------------------------------------------------------------------------
void PSS_GridView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
    // print the canvas
    CGXGridView::OnPrint(pDC, pInfo);
}
//---------------------------------------------------------------------------
void PSS_GridView::OnClickedButtonRowCol(ROWCOL row, ROWCOL col)
{
    PSS_GridGroup* pCtrl = SearchGroupCtrl(row, col);

    // toggle the group control
    if (pCtrl)
        pCtrl->SetCollapsed(!pCtrl->GetCollapsed());
}
//---------------------------------------------------------------------------
void PSS_GridView::OnViewZoomIn()
{
    if (GetZoom() < 300)
        SetZoom(GetZoom() * 11 / 10);
}
//---------------------------------------------------------------------------
void PSS_GridView::OnViewZoomOut()
{
    if (GetZoom() > 40)
        SetZoom(GetZoom() * 10 / 11);
}
//---------------------------------------------------------------------------
void PSS_GridView::OnUpdateViewZoomIn(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetParam() && GetZoom() < 300);
}
//---------------------------------------------------------------------------
void PSS_GridView::OnUpdateViewZoomOut(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetParam() && GetZoom() > 40);
}
//---------------------------------------------------------------------------
void PSS_GridView::OnFreezeSplitter()
{
    FreezeSplitter();
}
//---------------------------------------------------------------------------
void PSS_GridView::OnUpdateFreezeSplitter(CCmdUI* pCmdUI)
{
    const ROWCOL frozenRow       = GetFrozenRows();
    const ROWCOL frozenCol       = GetFrozenCols();
    const ROWCOL frozenHeaderRow = GetHeaderRows();
    const ROWCOL frozenHeaderCol = GetHeaderCols();

    PSS_GridDocument* pDoc = GetDocument();

    if (pDoc)
        pCmdUI->Enable(!frozenRow                  &&
                       !frozenCol                  &&
                       !frozenHeaderRow            &&
                       !frozenHeaderCol            &&
                       (pDoc->GetFrozenRow()       ||
                        pDoc->GetFrozenCol()       ||
                        pDoc->GetFrozenHeaderRow() ||
                        pDoc->GetFrozenHeaderCol() ));
    else
        pCmdUI->Enable(FALSE);
}
//---------------------------------------------------------------------------
void PSS_GridView::OnUnfreezeSplitter()
{
    UnfreezeSplitter();
}
//---------------------------------------------------------------------------
void PSS_GridView::OnUpdateUnfreezeSplitter(CCmdUI* pCmdUI)
{
    const ROWCOL frozenRow       = GetFrozenRows();
    const ROWCOL frozenCol       = GetFrozenCols();
    const ROWCOL frozenHeaderRow = GetHeaderRows();
    const ROWCOL frozenHeaderCol = GetHeaderCols();

    PSS_GridDocument* pDoc = GetDocument();

    if (pDoc)
        pCmdUI->Enable(frozenRow || frozenCol || frozenHeaderRow || frozenHeaderCol);
    else
        pCmdUI->Enable(FALSE);
}
//---------------------------------------------------------------------------
void PSS_GridView::OnUnhideAll()
{
    UnhideAll();
}
//---------------------------------------------------------------------------
void PSS_GridView::OnUpdateUnhideAll(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}
//---------------------------------------------------------------------------
void PSS_GridView::OnDraw(CDC* pDC)
{
    #ifdef _DEBUG
        PSS_GridDocument* pDoc = GetDocument();
        ASSERT_VALID(pDoc);
    #endif

    CGXGridView::OnDraw(pDC);
}
//---------------------------------------------------------------------------
int PSS_GridView::OnCreate(LPCREATESTRUCT pCreateStruct)
{
    EnableIntelliMouse();

    #if _MFC_VER >= 0x0400
        // enable grid to be used as data source
        EnableGridToolTips();
        EnableOleDropTarget();
        EnableOleDataSource();
    #endif

    EnableFormulaEngine();

    if (CGXGridView::OnCreate(pCreateStruct) == -1)
        return -1;

    m_dwDndDropTargetFlags = GX_DNDEGDESCROLL | GX_DNDAUTOSCROLL | GX_DNDTEXT | GX_DNDSTYLES;

    return 0;
}
//---------------------------------------------------------------------------
void PSS_GridView::OnExportToTextFile()
{
    ExportToTextFile();
}
//---------------------------------------------------------------------------
void PSS_GridView::OnUpdateExportToTextFile(CCmdUI* pCmdUI)
{}
//---------------------------------------------------------------------------
void PSS_GridView::OnImportFromTextFile()
{
    ImportTextFile();
}
//---------------------------------------------------------------------------
void PSS_GridView::OnUpdateImportFromTextFile(CCmdUI* pCmdUI)
{}
//---------------------------------------------------------------------------
BOOL PSS_GridView::OnRButtonClickedRowCol(ROWCOL row, ROWCOL col, UINT flags, CPoint point)
{
    CMenu* pPopup = (m_PopupMenu.GetSafeHmenu() ? m_PopupMenu.GetSubMenu(0) : NULL);

    // cannot proceed with the right button click
    if (!pPopup)
        return FALSE;

    // show the menu
    ClientToScreen(&point);
    pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, ::AfxGetMainWnd());

    // the message was processed
    return TRUE;
}
//---------------------------------------------------------------------------
