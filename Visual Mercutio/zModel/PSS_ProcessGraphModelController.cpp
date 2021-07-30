/****************************************************************************
 * ==> PSS_ProcessGraphModelController -------------------------------------*
 ****************************************************************************
 * Description : Provides a process graphic model controller                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessGraphModelController.h"

// processsoft
#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_DocumentObserverMsg.h"
#include "zBaseLib\PSS_ToolbarObserverMsg.h"
#include "zBaseLib\PSS_FileDialog.h"
#include "zProperty\PSS_PropertyObserverMsg.h"
#include "zProperty\PSS_DynamicProperties.h"
#include "zProperty\PSS_DynamicPropertiesManager.h"
#include "PSS_ProcessGraphModelDoc.h"
#include "PSS_ProcessGraphModelView.h"
#include "PSS_ProcessGraphModelViewport.h"
#include "PSS_ODSymbolManipulator.h"
#include "PSS_DocObserverMsg.h"
#include "PSS_UnitObserverMsg.h"
#include "PSS_ModelObserverMsg.h"
#include "PSS_SymbolObserverMsg.h"
#include "PSS_SymbolLogObserverMsg.h"
#include "PSS_LinkSymbol.h"
#include "PSS_TextZone.h"
#include "PSS_ProcessGraphPage.h"
#include "PSS_InsertModelNewPageDlg.h"
#include "PSS_RenameModelPageDlg.h"
#include "PSS_DeleteModelPageDlg.h"
#include "PSS_SelectSymbolAttributeDlg.h"
#include "PSS_FindSymbolExtDlg.h"
#include "PSS_BuildSymbolNewName.h"
#include "PSS_BuildGenericSymbolNewName.h"
#include "PSS_DynamicAttributesCreation.h"
#include "PSS_DynamicAttributesManipulator.h"
#include "PSS_ModelGlobal.h"

// resources
#include "zFormsRes\zFormsRes.h"
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define ANIMATE_TIMER 1123
//---------------------------------------------------------------------------
// Member variables
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_ProcessGraphModelController::m_pFormatPainterSymbol = NULL;
CODSymbolComponent* PSS_ProcessGraphModelController::m_LastSelectedElement  = NULL;
CODComponentSet     PSS_ProcessGraphModelController::m_CutSet;
CODComponentSet     PSS_ProcessGraphModelController::m_CopySet;
CODComponentSet     PSS_ProcessGraphModelController::m_SymbolAddedSet;
CPoint              PSS_ProcessGraphModelController::m_SavedEditPosition;
UINT                PSS_ProcessGraphModelController::m_CurrentCommandID     = 0;
bool                PSS_ProcessGraphModelController::m_CutCommand           = false;
bool                PSS_ProcessGraphModelController::m_IsInFormatPainter    = false;
CODNodeArray        PSS_ProcessGraphModelController::m_AnimatedNodes;
CODEdgeArray        PSS_ProcessGraphModelController::m_AnimatedEdges;
CODComponentSet     PSS_ProcessGraphModelController::m_AnimatedComponents;
COLORREF            PSS_ProcessGraphModelController::m_AnimatedColor        = -1;
PSS_Date            PSS_ProcessGraphModelController::m_TimerStartTime;
UINT                PSS_ProcessGraphModelController::m_Timer                = 0;
int                 PSS_ProcessGraphModelController::m_AnimateCounter       = 4;
int                 PSS_ProcessGraphModelController::m_AnimateSeconds       = 4;
bool                PSS_ProcessGraphModelController::m_SelectionChanged     = false;
bool                PSS_ProcessGraphModelController::m_AnimatedUseColor     = false;
bool                PSS_ProcessGraphModelController::m_TimerInitialized     = false;
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProcessGraphModelController, CODController)
    //{{AFX_MSG_MAP(PSS_ProcessGraphModelController)
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_RBUTTONUP()
    ON_WM_RBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDOWN()
    ON_COMMAND(ID_SELECT_ALL, OnSelectAll)
    ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
    ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
    ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
    ON_COMMAND(ID_EDIT_CUT, OnEditCut)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
    ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
    ON_COMMAND(ID_EDIT_DUPLICATE, OnEditDuplicate)
    ON_UPDATE_COMMAND_UI(ID_EDIT_DUPLICATE, OnUpdateEditDuplicate)
    ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
    ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
    ON_COMMAND(ID_EDIT_NAME, OnEditName)
    ON_UPDATE_COMMAND_UI(ID_EDIT_NAME, OnUpdateEditName)
    ON_COMMAND(ID_EDIT_COMMENT, OnEditComment)
    ON_UPDATE_COMMAND_UI(ID_EDIT_COMMENT, OnUpdateEditComment)
    ON_EN_CHANGE(IDC_OD_TEXTEDIT, OnChangeTextEdit)
    ON_COMMAND(ID_GO_PARENTMODEL, OnGoParentModel)
    ON_UPDATE_COMMAND_UI(ID_GO_PARENTMODEL, OnUpdateGoParentModel)
    ON_COMMAND(ID_BROWSE_SOURCESYMBOL, OnBrowseSourceSymbol)
    ON_UPDATE_COMMAND_UI(ID_BROWSE_SOURCESYMBOL, OnUpdateBrowseSourceSymbol)
    ON_COMMAND(ID_FIND_SYMBOL, OnFindSymbol)
    ON_COMMAND(ID_INSERT_MODELPAGE, OnInsertPage)
    ON_COMMAND(ID_RENAME_MODELPAGE, OnRenamePage)
    ON_COMMAND(ID_DELETE_MODELPAGE, OnDeletePage)
    ON_COMMAND(ID_RENAME_CURRENTMODELPAGE, OnRenameCurrentPage)
    ON_COMMAND(ID_DELETE_CURRENTMODELPAGE, OnDeleteCurrentPage)
    ON_COMMAND(ID_GOIN_SYMBOL, OnGoInSymbol)
    ON_COMMAND(ID_SELECT_SYMBOL, OnSelectSymbol)
    ON_COMMAND(ID_OD_MEASUREMENTS, OnOdMeasurements)
    ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomIn)
    ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomOut)
    ON_COMMAND(ID_ADD_NEWEXTAPP, OnAddNewExtApp)
    ON_UPDATE_COMMAND_UI(ID_ADD_NEWEXTAPP, OnUpdateAddNewExtApp)
    ON_COMMAND(ID_ADD_NEWEXTFILE, OnAddNewExtFile)
    ON_UPDATE_COMMAND_UI(ID_ADD_NEWEXTFILE, OnUpdateAddNewExtFile)
    ON_COMMAND(ID_SET_MODELBKIMAGE, OnSetBackgroundImage)
    ON_COMMAND(ID_CLEAR_MODELBKIMAGE, OnClearBackgroundImage)
    ON_UPDATE_COMMAND_UI(ID_SET_MODELBKIMAGE, OnUpdateSetBackgroundImage)
    ON_COMMAND(ID_SHOWMODELBORDER, OnShowModelBorder)
    ON_UPDATE_COMMAND_UI(ID_SHOWMODELBORDER, OnUpdateShowModelBorder)
    ON_COMMAND(ID_ADDWATERMARKLOGOMODEL, OnAddWatermarkModelLogo)
    ON_UPDATE_COMMAND_UI(ID_ADDWATERMARKLOGOMODEL, OnUpdateAddWatermarkModelLogo)
    ON_COMMAND(ID_CLEARWATERMARKLOGOMODEL, OnClearWatermarkModelLogo)
    ON_COMMAND(ID_SYM_SHOWNAMEAREA, OnSymbolShowNameArea)
    ON_UPDATE_COMMAND_UI(ID_SYM_SHOWNAMEAREA, OnUpdateSymbolShowNameArea)
    ON_COMMAND(ID_SYM_SHOWDESCRIPTIONAREA, OnSymbolShowDescriptionArea)
    ON_UPDATE_COMMAND_UI(ID_SYM_SHOWDESCRIPTIONAREA, OnUpdateSymbolShowDescriptionArea)
    ON_COMMAND(ID_SYM_SHOWATTRIBUTEAREA, OnSymbolShowAttributeArea)
    ON_UPDATE_COMMAND_UI(ID_SYM_SHOWATTRIBUTEAREA, OnUpdateSymbolShowAttributeArea)
    ON_COMMAND(ID_SYM_SHOWLABELATTRIBUTES, OnSymbolShowLabelAttributes)
    ON_UPDATE_COMMAND_UI(ID_SYM_SHOWLABELATTRIBUTES, OnUpdateSymbolShowLabelAttributes)
    ON_COMMAND(ID_SYM_SELECTATTRIBUTES, OnSymbolSelectAttributes)
    ON_UPDATE_COMMAND_UI(ID_SYM_SELECTATTRIBUTES, OnUpdateSymbolSelectAttributes)
    ON_COMMAND(ID_DYNATTR_ADD, OnDynamicAttributesAdd)
    ON_UPDATE_COMMAND_UI(ID_DYNATTR_ADD, OnUpdateDynamicAttributesAdd)
    ON_COMMAND(ID_DYNATTR_DUPLICATE, OnDynamicAttributesDuplicate)
    ON_UPDATE_COMMAND_UI(ID_DYNATTR_DUPLICATE, OnUpdateDynamicAttributesDuplicate)
    ON_COMMAND(ID_DYNATTR_DEL, OnDynamicAttributesDelete)
    ON_UPDATE_COMMAND_UI(ID_DYNATTR_DEL, OnUpdateDynamicAttributesDelete)
    ON_COMMAND(ID_REFRESH, OnRefresh)
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProcessGraphModelController
//---------------------------------------------------------------------------
PSS_ProcessGraphModelController::PSS_ProcessGraphModelController(PSS_ProcessGraphModelViewport* pViewport) :
    CODController(pViewport),
    m_pSymbolHit(NULL),
    m_pLabelHit(NULL),
    m_pRightSubMenu(NULL),
    m_CurrentCursor(0),
    m_IsEditingSymbolName(false),
    m_IsEditingSymbolComment(false),
    m_NewSymbolCreated(false)
{
    CODViewport* pCanvasVp = GetCanvasVp();

    if (pCanvasVp)
        pCanvasVp->Invalidate();
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelController::~PSS_ProcessGraphModelController()
{
    // when the controller is closed, reset the last selected element. Otherwise a pointer may be kept
    // on an unexisting symbol while the base class is deleted
    m_LastSelectedElement = NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelView* PSS_ProcessGraphModelController::GetView()
{
    if (m_pViewport)
    {
        PSS_ProcessGraphModelView* pView = dynamic_cast<PSS_ProcessGraphModelView*>(m_pViewport->GetWnd());

        if (pView)
            return pView;
    }

    return NULL;
}
//---------------------------------------------------------------------------
const PSS_ProcessGraphModelView* PSS_ProcessGraphModelController::GetView() const
{
    if (m_pViewport)
    {
        PSS_ProcessGraphModelView* pView = dynamic_cast<PSS_ProcessGraphModelView*>(m_pViewport->GetWnd());

        if (pView)
            return pView;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelViewport* PSS_ProcessGraphModelController::GetViewport()
{
    return dynamic_cast<PSS_ProcessGraphModelViewport*>(m_pViewport);
}
//---------------------------------------------------------------------------
CDocument* PSS_ProcessGraphModelController::GetDocument()
{
    PSS_ProcessGraphModelView* pView = GetView();

    if (pView)
        return pView->GetDocument();

    return NULL;
}
//---------------------------------------------------------------------------
const CDocument* PSS_ProcessGraphModelController::GetDocument() const
{
    const PSS_ProcessGraphModelView* pView = GetView();

    if (pView)
        return pView->GetDocument();

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessGraphModelController::GetModel()
{
    if (!m_pViewport)
        return NULL;

    return dynamic_cast<PSS_ProcessGraphModelMdl*>(m_pViewport->GetModel());
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessGraphModelController::GetRootModel()
{
    if (!m_pViewport)
        return NULL;

    PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(m_pViewport->GetModel());

    if (pModel)
        return pModel->GetRoot();

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::RefreshModelTree()
{
    CWnd* pMainWnd = ::AfxGetMainWnd();

    if (!pMainWnd)
        return;

    // send notification message to descendants
    pMainWnd->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED);
    pMainWnd->SendMessageToDescendants(UM_UNITMODELHASCHANGED);
}
//---------------------------------------------------------------------------
CMenu* PSS_ProcessGraphModelController::CreateContextMenu()
{
    if (m_pRightSubMenu)
        return m_pRightSubMenu;

    return CODController::CreateContextMenu();
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelViewport* PSS_ProcessGraphModelController::CreateViewFromModel(PSS_ProcessGraphModelMdl* pModel,
                                                                                    PSS_ProcessGraphModelMdl* pParentModel)
{
    PSS_ProcessGraphModelView* pView = GetView();

    if (!pView)
        return NULL;

    if (GetBrowseInSameWindow())
    {
        // clear the selection
        ClearSelection();

        // set the model
        pView->SetModel(pModel, true);

        CDocument* pDocument = pView->GetDocument();

        // refresh the views
        if (pDocument)
            pDocument->UpdateAllViews(pView);

        CFrameWnd* pFrameWnd = dynamic_cast<CFrameWnd*>(::AfxGetMainWnd());

        // force the refresh of the active window title
        if (pFrameWnd && pFrameWnd->GetActiveFrame())
            pFrameWnd->GetActiveFrame()->OnUpdateFrameTitle(TRUE);

        // set the right controller
        pModel->SetController(this);

        PSS_ProcessGraphModelViewport* pViewport = pView->GetViewport();

        // move to [0, 0]
        if (pViewport)
            pViewport->SetLogOrigin(0, 0);

        // return the viewport
        return pViewport;
    }

    CDocument* pDocument = dynamic_cast<CDocument*>(pView->GetDocument());

    if (!pDocument)
        return NULL;

    CFrameWnd* pFrame = pDocument->GetDocTemplate()->CreateNewFrame(pDocument, NULL);

    // call IntitialUpdateFrame after creating a new frame with CreateNewFrame. Calling this function causes
    // the views in that frame window to receive their OnInitialUpdate calls
    pDocument->GetDocTemplate()->InitialUpdateFrame(pFrame, pDocument);

    PSS_ProcessGraphModelView* pActiveView = dynamic_cast<PSS_ProcessGraphModelView*>(pFrame->GetActiveView());

    if (pActiveView)
    {
        // set the model
        pActiveView->SetModel(pModel);

        PSS_ProcessGraphModelViewport* pActiveViewport = pActiveView->GetViewport();

        // set the right controller
        if (pActiveViewport)
            pModel->SetController((CODController*)pActiveViewport->GetModelController());

        // move to [0, 0]
        pActiveViewport->SetLogOrigin(0, 0);

        pFrame->OnUpdateFrameTitle(TRUE);

        return pActiveViewport;
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelViewport* PSS_ProcessGraphModelController::BrowseModel(PSS_ProcessGraphModelMdl* pModel,
                                                                            PSS_ProcessGraphModelMdl* pParentModel)
{
    if (!pModel)
        return NULL;

    PSS_ProcessGraphModelDoc* pGraphModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    // if can't activate a view with model name, create a new view
    if (pGraphModelDoc)
    {
        CView* pView = pGraphModelDoc->ActivateView(pModel->GetAbsolutePath());

        if (!pView)
            // create a view from the model
            return CreateViewFromModel(pModel, pParentModel);

        PSS_ProcessGraphModelView* pGraphModelView = dynamic_cast<PSS_ProcessGraphModelView*>(pView);

        if (pGraphModelView)
            return pGraphModelView->GetViewport();
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelViewport* PSS_ProcessGraphModelController::OpenPage(PSS_ProcessGraphPage* pPage)
{
    if (!pPage)
        return NULL;

    PSS_ProcessGraphModelView* pView = GetView();

    if (pView)
    {
        PSS_ProcessGraphModelMdl* pModel = pPage->GetModel();

        // is there any child model?
        if (pModel)
        {
            PSS_ProcessGraphModelViewport* pVp = BrowseModel(pModel, pModel->GetParent());

            // when open a new model, unselect all symbols
            UnselectAllComponents();

            // return the viewport
            return pVp;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelViewport* PSS_ProcessGraphModelController::OpenSymbol(CODComponent* pComp)
{
    PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pComp);

    if (pSymbol)
    {
        PSS_ProcessGraphModelView* pView = GetView();

        if (pView)
        {
            PSS_ProcessGraphModelMdl* pModel = GetModel();

            // is there any child model?
            if (!pSymbol->GetChildModel())
                pSymbol->CreateEmptyChildModel(pModel);

            // end the text edit before going into the new model
            EndTextEdit(0, m_SavedEditPosition);

            PSS_ProcessGraphModelViewport* pVp =
                    BrowseModel((PSS_ProcessGraphModelMdl*)pSymbol->GetChildModel(), pModel);

            // when open a new model, unselect all symbols
            UnselectAllComponents();

            // return the viewport
            return pVp;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelViewport* PSS_ProcessGraphModelController::EnsureSymbolVisible(CODComponent* pComp)
{
    if (!pComp)
        return NULL;

    PSS_ProcessGraphModelViewport* pVp     = NULL;
    CODSymbolComponent*            pSymbol = NULL;
    PSS_Symbol*                    pSym    = dynamic_cast<PSS_Symbol*>(pComp);

    if (pSym)
    {
        pVp     = BrowseSymbolModel(pSym);
        pSymbol = pSym;
    }
    else
    {
        PSS_LinkSymbol* pLinkSym = dynamic_cast<PSS_LinkSymbol*>(pComp);

        if (pLinkSym)
        {
            pVp     = BrowseLinkSymbolModel(pLinkSym);
            pSymbol = pLinkSym;
        }
    }

    if (pVp)
    {
        PSS_ProcessGraphModelController* pModelCtrl = pVp->GetModelController();

        // when open a new model, unselect all symbols
        if (pModelCtrl)
            pModelCtrl->UnselectAllComponents();

        // animate the symbol
        if (pSymbol && pModelCtrl)
            pModelCtrl->AnimateSymbol(*pSymbol, true, defCOLOR_LTBLUE, 8);
    }

    // return the viewport
    return pVp;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelViewport* PSS_ProcessGraphModelController::BrowseLocalSymbol(CODComponent* pComp)
{
    if (!pComp)
        return NULL;

    PSS_ProcessGraphModelDoc* pDocument = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    if (!pDocument || !pDocument->GetModel())
        return NULL;

    CODSymbolComponent* pSymbol = NULL;
    PSS_Symbol*         pSym    = dynamic_cast<PSS_Symbol*>(pComp);

    if (pSym && !pSym->IsLocal())
        // find local symbol
        pSymbol = dynamic_cast<CODSymbolComponent*>(pSym->GetLocalSymbol());
    else
    {
        PSS_LinkSymbol* pLinkSym = dynamic_cast<PSS_LinkSymbol*>(pComp);

        if (pLinkSym && !pLinkSym->IsLocal())
            // find local symbol
            pSymbol = dynamic_cast<CODSymbolComponent*>(pLinkSym->GetLocalSymbol());
    }

    // if found, ensure that the symbol is visible
    if (pSymbol)
        return EnsureSymbolVisible(pSymbol);

    return NULL;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelController::AcceptDropItemToModel(CObject* pObj, const CPoint& point)
{
    if (!pObj)
        return false;

    // is a symbol?
    if (ISA(pObj, PSS_Symbol))
        return true;

    // is a link symbol?
    if (ISA(pObj, PSS_LinkSymbol))
        return true;

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelController::DropItemToModel(CObject* pObj, const CPoint& point)
{
    PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pObj);

    if (pSymbol)
    {
        m_pInsert = pSymbol->Dup();

        ClearSelectionToSet();
        m_CopySet.Add(m_pInsert);

        CPoint pt = point;

        VpLPtoDP(&pt);
        InsertSymbol(0, pt);

        return true;
    }

    PSS_LinkSymbol* pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pObj);

    if (pLinkSymbol)
    {
        m_pInsert = pLinkSymbol->Dup();

        ClearSelectionToSet();
        m_CopySet.Add(m_pInsert);

        CPoint pt = point;

        VpLPtoDP(&pt);
        InsertSymbol(0, pt);

        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelController::AcceptDropItem(CObject* pObj, const CPoint& point)
{
    // no object to drop?
    if (!pObj)
        return false;

    CPoint pt = point;
    VpDPtoLP(&pt);

    CODViewport*  pCanvasVp = GetCanvasVp();
    CODComponent* pCompHit  = NULL;

    if (pCanvasVp)
        pCompHit = pCanvasVp->ComponentHitTest(pt);

    // if no object hit, test the drop on the model
    if (!pCompHit)
        return AcceptDropItemToModel(pObj, pt);

    CODLabelComponent* pLabelHit = dynamic_cast<CODLabelComponent*>(pCompHit);

    // if it's a label, assign the right owner symbol
    if (pLabelHit)
        // select the symbol behind
        pCompHit = pLabelHit->GetOwner();

    PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pCompHit);

    if (pSymbol)
        return pSymbol->AcceptDropItem(pObj, pt);

    PSS_LinkSymbol* pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pCompHit);

    if (pLinkSymbol)
        return pLinkSymbol->AcceptDropItem(pObj, pt);

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelController::DropItem(CObject* pObj, const CPoint& point)
{
    // no object to drop?
    if (!pObj)
        return false;

    CPoint pt(point);
    CPoint ptInView(point);
    VpDPtoLP(&ptInView);

    CODViewport*  pCanvasVp = GetCanvasVp();
    CODComponent* pCompHit  = NULL;

    if (pCanvasVp)
        pCompHit = pCanvasVp->ComponentHitTest(ptInView);

    // if no object hit, drag symbol on the model
    if (!pCompHit)
        return DropItemToModel(pObj, pt);

    CODLabelComponent* pLabel = dynamic_cast<CODLabelComponent*>(pCompHit);

    // if it's a label, assign the right owner symbol
    if (pLabel)
        // select the symbol behind
        pCompHit = pLabel->GetOwner();

    UnselectAllComponents();

    PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pCompHit);
    bool        result  = false;

    if (pSymbol)
        result = pSymbol->DropItem(pObj, pt);
    else
    {
        PSS_LinkSymbol* pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pCompHit);

        if (pLinkSymbol)
            result = pLinkSymbol->DropItem(pObj, pt);
    }

    // select the drag&dropped symbol
    SelectComponent(*pCompHit);
    NotifySymbolSelected(pCompHit);

    // update the symbol
    CODComponentSet compSet;
    compSet.Add(pCompHit);
    GetVp()->DrawComponents(&compSet);

    return result;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::EditName(CODComponent* pCompToEdit)
{
    PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pCompToEdit);
    PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pCompToEdit);

    if (!pSymbol && !pLinkSymbol)
    {
        m_pSymbolHit = NULL;
        return;
    }

    m_pSymbolHit                       = static_cast<CODSymbolComponent*>(pCompToEdit);
    CODEditProperties* pEditProps      = static_cast<CODEditProperties*>(pCompToEdit->GetProperty(OD_PROP_EDIT));
    CODEditProperties* pModelEditProps = static_cast<CODEditProperties*>(GetCanvasModel()->GetProperty(OD_PROP_EDIT));

    // check if the symbol can be edited
    if ((pSymbol && pSymbol->SymbolNameTextEditReadOnly()) || (pLinkSymbol && pLinkSymbol->SymbolNameTextEditReadOnly()))
        return;

    if (GetCanvasModel()->GetDesignMode() || (!pEditProps->IsReadOnly() && !pModelEditProps->IsReadOnly()))
    {
        CODTextComponent* pTextComp = NULL;

        if (pSymbol)
            pTextComp = pSymbol->GetSymbolNameTextEdit();
        else
        if (pLinkSymbol)
            pTextComp = pLinkSymbol->GetSymbolNameTextEdit();

        // already editing?
        if (pTextComp && !pTextComp->IsEditing())
        {
            CODEditProperties* pEditProps = static_cast<CODEditProperties*>(pTextComp->GetProperty(OD_PROP_EDIT));
            ASSERT_VALID(pEditProps);

            if (pEditProps->IsReadOnly())
                return;

            CODComponentSet setUpdate;
            setUpdate.Add(pCompToEdit);

            if (pTextComp != m_pTextEdit)
            {
                EndTextEdit(0, m_SavedEditPosition);

                m_pTextEdit = pTextComp;
                m_pTextEdit->AddRef();

                // set the text edition flag
                m_IsEditingSymbolName = true;

                CODViewport* pCanvasVp = GetCanvasVp();

                if (pCanvasVp && m_pTextEdit->BeginEdit(pCanvasVp))
                    pCanvasVp->UpdateComponents(&setUpdate);
            }
        }

        CDocument* pDocument = GetDocument();

        // set the modification flag
        if (pDocument)
            pDocument->SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::EditComment(CODComponent* pCompToEdit)
{
    PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pCompToEdit);

    if (!pSymbol)
    {
        m_pSymbolHit = NULL;
        return;
    }

    m_pSymbolHit                       = pSymbol;
    CODEditProperties* pEditProps      = static_cast<CODEditProperties*>(m_pSymbolHit->GetProperty(OD_PROP_EDIT));
    CODEditProperties* pModelEditProps = static_cast<CODEditProperties*>(GetCanvasModel()->GetProperty(OD_PROP_EDIT));

    // Check if the symbol can be edited
    if (pSymbol->CommentTextEditReadOnly())
        return;

    if (GetCanvasModel()->GetDesignMode() || (!pEditProps->IsReadOnly() && !pModelEditProps->IsReadOnly()))
    {
        CODTextComponent* pTextComp = pSymbol->GetCommentTextEdit();

        // already editing?
        if (pTextComp && !pTextComp->IsEditing())
        {
            CODEditProperties* pEditProps = static_cast<CODEditProperties*>(pTextComp->GetProperty(OD_PROP_EDIT));
            ASSERT_VALID(pEditProps);

            if (pEditProps->IsReadOnly())
                return;

            CODComponentSet setUpdate;
            setUpdate.Add(m_pCompHit);

            if (pTextComp != m_pTextEdit)
            {
                EndTextEdit(0, m_SavedEditPosition);

                m_pTextEdit = pTextComp;
                m_pTextEdit->AddRef();

                // set the comment edition flag
                m_IsEditingSymbolComment = true;

                CODViewport* pCanvasVp = GetCanvasVp();

                if (pCanvasVp && m_pTextEdit->BeginEdit(pCanvasVp))
                    pCanvasVp->UpdateComponents(&setUpdate);
            }
        }

        CDocument* pDocument = GetDocument();

        // set the modification flag
        if (pDocument)
            pDocument->SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::ViewZoomIn()
{
    CODViewport* pCanvasVp = GetCanvasVp();

    if (!pCanvasVp)
        return;

    CSize magnification = pCanvasVp->GetMagnification();
    magnification.cx   += 25;
    magnification.cy   += 25;

    pCanvasVp->SetMagnification(magnification.cx, magnification.cy);

    UpdateTextEdit();

    pCanvasVp->Invalidate();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::ViewZoomOut()
{
    CODViewport* pCanvasVp = GetCanvasVp();

    if (!pCanvasVp)
        return;

    CSize magnification  = pCanvasVp->GetMagnification();
    magnification.cx    -= 25;
    magnification.cy    -= 25;

    pCanvasVp->SetMagnification(magnification.cx, magnification.cy);

    UpdateTextEdit();

    pCanvasVp->Invalidate();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::RedrawComponent(CODComponent& comp)
{
    // update symbols
    CODComponentSet compSet;
    compSet.Add(&comp);

    RedrawComponentSet(compSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::RedrawComponentSet(CODComponentSet& set)
{
    CODViewport* pCanvasVp = GetCanvasVp();

    if (!pCanvasVp)
        return;

    // update symbols
    pCanvasVp->UpdateComponents(&set);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::SelectAllComponents()
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    CODComponentSet* pSet = pModel->GetComponents();

    // iterate through all components and change the select all flag
    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // select the symbol
        CODEditProperties* pPropEdit = static_cast<CODEditProperties*>(pComp->GetProperty(OD_PROP_EDIT));

        if (pPropEdit)
        {
            std::unique_ptr<CODEditProperties> pEditProps(new CODEditProperties(*pPropEdit));
            pEditProps->SetCanSelect(TRUE);
            pComp->SetProperty(pEditProps.get());
            pEditProps.release();
        }
    }

    SelectAll();
    NotifySymbolSelected(NULL);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::UnselectAllComponents()
{
    // clear selection list
    ClearSelection();

    CODViewport* pCanvasVp = GetCanvasVp();

    // update the viewport
    if (pCanvasVp)
        pCanvasVp->UpdateAll();

    NotifySymbolSelected(NULL);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::SelectComponent(CODComponent& comp)
{
    m_setSelection.Add(&comp);
    RedrawComponent(comp);
    NotifySymbolSelected(&comp);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::SelectComponentSet(CODComponentSet& set)
{
    CODComponentIterator it(&set);

    for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext())
        m_setSelection.Add(pComp);

    RedrawComponentSet(set);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::UnselectComponent(CODComponent& comp)
{
    CODComponentSet set;
    set.Add(&comp);
    Deselect(&set);

    CODViewport* pCanvasVp = GetCanvasVp();

    // update the viewport
    if (pCanvasVp)
        pCanvasVp->UpdateAll();

    NotifySymbolSelected(NULL);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::UnselectComponentSet(CODComponentSet& set)
{
    Deselect(&set);
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelController::IsComponentSelected(CODComponent& comp)
{
    CODComponentIterator it(&m_setSelection);

    for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext())
        if (pComp == &comp)
            return true;

    return false;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelController::GetBrowseInSameWindow() const
{
    const PSS_ProcessGraphModelDoc* pDocument = dynamic_cast<const PSS_ProcessGraphModelDoc*>(GetDocument());

    if (pDocument)
        return pDocument->GetBrowseInSameWindow();

    return false;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::SetBrowseInSameWindow(bool value)
{
    PSS_ProcessGraphModelDoc* pDocument = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    if (pDocument)
        pDocument->SetBrowseInSameWindow(value);
}
//---------------------------------------------------------------------------
CODComponent* PSS_ProcessGraphModelController::InsertSymbol(CODComponent* pComp,
                                                            UINT          flags,
                                                            const CPoint& point,
                                                            bool          includePostCreation)
{
    CODController::InsertSymbol(flags, point);

    CDocument* pDocument = GetDocument();

    // set the modified flag
    if (pDocument)
        pDocument->SetModifiedFlag(TRUE);

    // reset the current command id
    m_CurrentCommandID = 0;

    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return NULL;

    PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pComp);

    if (pSymbol)
    {
        // assign the path
        pSymbol->SetAbsolutePath(pModel->GetAbsolutePath());

        // by default, assign the unique reference number
        if (GetRootModel())
        {
            const int refNumber = GetRootModel()->GetNextAvailableReferenceNumber();

            pSymbol->SetSymbolReferenceNumber(refNumber);

            // is the symbol generic?
            if (pSymbol->IsGeneric())
            {
                PSS_BuildGenericSymbolNewName buildNewName;

                // if the symbol is generic, set another name
                pSymbol->SetSymbolName(buildNewName.GetNextAvailableSymbolName(*GetRootModel()));
            }
            else
            {
                PSS_BuildSymbolNewName buildNewName;

                // get the next available name
                pSymbol->SetSymbolName(buildNewName.GetNextAvailableSymbolName(*GetRootModel(), refNumber));
            }
        }

        if (includePostCreation)
            // notify about the post-creation
            if (!pSymbol->OnPostCreation(pModel, this))
            {
                // delete the object
                DeleteComponent(pComp);

                // cancel the selection on the old object
                UnselectAllComponents();
                ClearSymbolAddedSet();
                ClearSelectionToSet();

                return NULL;
            }

        // refresh the attribute area and redraw the symbol
        pSymbol->RefreshAttributeTextArea(true);

        if (m_NewSymbolCreated && pSymbol->IsLocal())
        {
            // save the position first
            m_SavedEditPosition = point;

            // edit the name directly
            EditName(pComp);
        }

        // notify about the new selection
        NotifySymbolSelected(pComp);

        // call the virtual method on added symbol
        OnSymbolAdded(&m_SymbolAddedSet);

        // reset the creation flag
        m_NewSymbolCreated = false;

        return pComp;
    }

    PSS_TextZone* pTextZone = dynamic_cast<PSS_TextZone*>(pComp);

    if (pTextZone)
    {
        // initialize the text zone
        pTextZone->InitializeStyle();

        PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pTextZone->GetParent());

        // redraw the text zone
        if (pModel)
            pModel->RedrawComponent(*pTextZone);

        // notify about the new selection
        NotifySymbolSelected(pComp);

        // call the OnSymbolAdded function
        OnSymbolAdded(&m_SymbolAddedSet);

        m_NewSymbolCreated = false;
    }

    return pComp;
}
//---------------------------------------------------------------------------
CODComponent* PSS_ProcessGraphModelController::InsertSymbol(UINT flags, const CPoint& point, bool includePostCreation)
{
    return InsertSymbol(m_pInsert, flags, point, includePostCreation);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::DeleteComponent(CODComponent* pComp)
{
    if (!pComp)
        return;

    // add the component to the set
    CODComponentSet set;
    set.Add(pComp);

    // call the delete component function for a set
    DeleteComponents(&set);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::DeleteComponents(CODComponentSet* pCompSet)
{
    if (!pCompSet)
        return;

    CODComponentSet      setUpdate;
    CODComponentIterator it(pCompSet);

    for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext())
    {
        // get the owner model
        CODComponent* pParentComp = pComp->GetParent();
        CODModel*     pOwnerModel = NULL;

        while (pParentComp)
        {
            pOwnerModel = dynamic_cast<CODModel*>(pParentComp);

            // if a model, return it
            if (pOwnerModel)
                break;

            // otherwise get its parent
            pParentComp = pParentComp->GetParent();
        }

        // if no owner model, get the next component
        if (!pOwnerModel)
            continue;

        // remove the component
        CODComponentSet set;
        set.Add(pComp);
        RemoveReferenceSymbol(&set);

        // remove the child component
        pOwnerModel->RemoveChild(pComp);
    }

    // notify about the selection change
    if (setUpdate.GetSize() > 0)
        OnSelectionChange(&setUpdate);

    PSS_ProcessGraphModelViewport* pViewport = GetViewport();

    // update the whole viewport
    if (pViewport)
        pViewport->UpdateAll();
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelController::ValidateCutCopyOperations()
{
    CODComponentIterator it(GetSelection());

    for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext())
    {
        PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pComp);

        if (pSymbol)
        {
            if (!pSymbol->IsDoor() && !pSymbol->IsPackage() && !pSymbol->IsPage() && pSymbol->IsLocal())
                return TRUE;

            continue;
        }

        PSS_LinkSymbol* pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pComp);

        if (pLinkSymbol)
        {
            if (pLinkSymbol->IsLocal())
                return TRUE;

            continue;
        }

        PSS_TextZone* pTextZone = dynamic_cast<PSS_TextZone*>(pComp);

        // allows the copy if the element is a text zone
        if (pTextZone)
            return TRUE;

        CODComponent* pComponent = dynamic_cast<CODComponent*>(pComp);

        // allow the copy if the selected element is a kind of component. This includes all
        // the Mercutio symbols, however the sensitive elements were already filtered above,
        // and thus will be rejected before the application reaches this point
        if (pComponent)
            return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelController::FilterSelection(BOOL modifyFlag)
{
    CODComponentIterator it(GetSelection());
    BOOL                 selectionIsModified = modifyFlag;

    for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext())
    {
        PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pComp);

        if (pSymbol)
        {
            if (pSymbol->IsDoor() || pSymbol->IsPackage() || pSymbol->IsPage() || !pSymbol->IsLocal())
            {
                GetSelection()->Remove(it.Get());
                return FilterSelection(TRUE);
            }

            continue;
        }

        PSS_LinkSymbol* pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pComp);

        if (pLinkSymbol)
        {
            if (!pLinkSymbol->IsLocal())
            {
                GetSelection()->Remove(it.Get());
                return FilterSelection(TRUE);
            }

            continue;
        }

        CODLabelComponent* pLabel = dynamic_cast<CODLabelComponent*>(pComp);

        if (pLabel)
        {
            GetSelection()->Remove(it.Get());
            return FilterSelection(selectionIsModified);
        }
    }

    return selectionIsModified;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::RefreshSelectionProperties()
{
    // refresh only if one symbol is selected
    if (GetSelection()->GetSize() == 1)
        if (GetSelection()->GetAt(0))
            NotifySymbolSelected(GetSelection()->GetAt(0));
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::RefreshAllSymbols()
{
    PSS_ProcessGraphModelViewport* pViewport = GetViewport();

    PSS_Assert(pViewport);
    pViewport->UpdateAll();

    // refresh all symbol attributes
    PSS_ProcessGraphModelMdl* pRootModel = GetRootModel();
    PSS_Assert(pRootModel);
    pRootModel->RefreshSymbolAttributes(true);

    // refresh also the model tree
    RefreshModelTree();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::ReleaseClipboard()
{
    OpenClipboard();
    EmptyClipboard();
    CloseClipboard();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::SetImage(const CString& fileName, BOOL isLogo)
{
    PSS_ProcessGraphModelMdl* pModel = GetRootModel();
    PSS_Assert(pModel);

    std::unique_ptr<SECImage> pImage(PSS_ProcessGraphModelView::LoadImageFromFile(fileName));

    // allow the user to reset the file if it was modified, deleted or corrupted
    if (!pImage)
    {
        CString message = _T("");
        message.Format(IDS_WARN_IMGFILECORRUPTED, fileName);

        const int result = AfxMessageBox(message, MB_YESNO);

        if (result == 7)
        {
            pModel->SetBkGndFileName(_T(""));
            return;
        }
        else
        if (!isLogo)
            OnSetBackgroundImage();
        else
            OnAddWatermarkModelLogo();

        return;
    }

    std::unique_ptr<SECDib> pDibImage(new SECDib());
    pDibImage->ConvertImage(pImage.get());

    if (!isLogo)
    {
        // create the component
        CODImageComponent square;

        if (square.Load(*pDibImage, FALSE))
        {
            square.SetType(_T("Square"));
            square.SetSize(pDibImage->dwGetWidth(), pDibImage->dwGetHeight());

            pModel->SetBackgroundComponent(square, true, true);
            pModel->SetIsLogo(FALSE);
        }
    }
    else
    {
        // create the component
        CODImageComponent logo;

        if (logo.Load(*pDibImage, TRUE))
        {
            logo.SetType(_T("Logo"));
            logo.SetSize(pDibImage->dwGetWidth(), pDibImage->dwGetHeight());
            logo.MoveOrigin(10, 10);

            pModel->SetBackgroundComponent(logo, true, false);
            pModel->SetIsLogo(TRUE);
        }
    }

    pModel->SetBkGndFileName(fileName);

    // refresh the viewport
    PSS_ProcessGraphModelViewport* pViewport = GetViewport();
    PSS_Assert(pViewport);
    pViewport->UpdateAll();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::ClearImage()
{
    PSS_ProcessGraphModelMdl* pModel = GetRootModel();
    PSS_Assert(pModel);

    pModel->ClearBackgroundComponent(true);
    pModel->SetBkGndFileName(_T(""));

    // refresh the viewport
    PSS_ProcessGraphModelViewport* pViewport = GetViewport();
    PSS_Assert(pViewport);
    pViewport->UpdateAll();
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelController::GetImageFileName(CString& fileName)
{
    CString title;
    VERIFY(title.LoadString(IDS_IMAGEFILE_CHOOSETITLE));

    CString name;
    CString filter;

    // set the "*.jpg" files filter
    VERIFY(name.LoadString(IDS_EXPORTFILE_FILTERJPEG));
    filter += name;
    filter += char('\0');
    filter += _T("*.jpg");
    filter += char('\0');

    // append the "*.gif" files filter
    VERIFY(name.LoadString(IDS_EXPORTFILE_FILTERGIF));
    filter += name;
    filter += char('\0');
    filter += _T("*.gif");
    filter += char('\0');

    // append the "*.pcx" files filter
    VERIFY(name.LoadString(IDS_EXPORTFILE_FILTERPCX));
    filter += name;
    filter += char('\0');
    filter += _T("*.pcx");
    filter += char('\0');

    // append the "*.dib" files filter
    VERIFY(name.LoadString(IDS_EXPORTFILE_FILTERDIB));
    filter += name;
    filter += char('\0');
    filter += _T("*.dib");
    filter += char('\0');

    // append the "*.tga" files filter
    VERIFY(name.LoadString(IDS_EXPORTFILE_FILTERTGA));
    filter += name;
    filter += char('\0');
    filter += _T("*.tga");
    filter += char('\0');

    // append the "*.tif" files filter
    VERIFY(name.LoadString(IDS_EXPORTFILE_FILTERTIF));
    filter += name;
    filter += char('\0');
    filter += _T("*.tif");
    filter += char('\0');

    PSS_FileDialog fileDialog(title, filter, 6, _T(""));

    if (fileDialog.DoModal() == IDCANCEL)
    {
        fileName = _T("");
        return FALSE;
    }

    fileName = fileDialog.GetFileName();
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::AnimateNode(IODNode&    node,
                                                  bool        useColor,
                                                  COLORREF    color,
                                                  std::size_t animateCounter)
{
    if (useColor)
        m_AnimateSeconds = animateCounter;
    else
        m_AnimateCounter = animateCounter;

    m_AnimatedUseColor = useColor;
    m_AnimatedColor    = color;

    // kill the timer if necessary
    if (m_Timer)
        EndAnimateTimer();

    m_TimerStartTime = PSS_Date::GetCurrentTime();

    // add the component
    m_AnimatedNodes.Add(&node);

    // start the timer
    m_Timer = SetTimer(ANIMATE_TIMER, 50, NULL);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::AnimateNodes(CODNodeArray& nodes,
                                                   bool          useColor,
                                                   COLORREF      color,
                                                   std::size_t   animateCounter)
{
    if (useColor)
        m_AnimateSeconds = animateCounter;
    else
        m_AnimateCounter = animateCounter;

    m_AnimatedUseColor = useColor;
    m_AnimatedColor    = color;

    // kill the timer if necessary
    if (m_Timer)
        EndAnimateTimer();

    m_TimerStartTime = PSS_Date::GetCurrentTime();

    const int nodeCount = nodes.GetSize();

    // add the components
    for (int i = 0; i < nodeCount; ++i)
        m_AnimatedNodes.Add(nodes.GetAt(i));

    // start the timer
    m_Timer = SetTimer(ANIMATE_TIMER, 50, NULL);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::AnimateEdge(IODEdge&    edge,
                                                  bool        useColor,
                                                  COLORREF    color,
                                                  std::size_t animateCounter)
{
    if (useColor)
        m_AnimateSeconds = animateCounter;
    else
        m_AnimateCounter = animateCounter;

    m_AnimatedUseColor = useColor;
    m_AnimatedColor    = color;

    // kill the timer if necessary
    if (m_Timer)
        EndAnimateTimer();

    m_TimerStartTime = PSS_Date::GetCurrentTime();

    // add the component
    m_AnimatedEdges.Add(&edge);

    // start the timer
    m_Timer = SetTimer(ANIMATE_TIMER, 50, NULL);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::AnimateEdges(CODEdgeArray& edges,
                                                   bool          useColor,
                                                   COLORREF      color,
                                                   std::size_t   animateCounter)
{
    if (useColor)
        m_AnimateSeconds = animateCounter;
    else
        m_AnimateCounter = animateCounter;

    m_AnimatedUseColor = useColor;
    m_AnimatedColor    = color;

    // kill the timer if necessary
    if (m_Timer)
        EndAnimateTimer();

    m_TimerStartTime = PSS_Date::GetCurrentTime();

    const int edgeCount = edges.GetSize();

    // add the components
    for (int i = 0; i < edgeCount; ++i)
        m_AnimatedEdges.Add(edges.GetAt(i));

    // start the timer
    m_Timer = SetTimer(ANIMATE_TIMER, 50, NULL);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::AnimateSymbol(CODSymbolComponent& symbol,
                                                  bool                  useColor,
                                                  COLORREF              color,
                                                  size_t                animateCounter)
{
    if (useColor)
        m_AnimateSeconds = animateCounter;
    else
        m_AnimateCounter = animateCounter;

    m_AnimatedUseColor = useColor;
    m_AnimatedColor    = color;

    // kill the timer if necessary
    if (m_Timer)
        EndAnimateTimer();

    m_TimerStartTime = PSS_Date::GetCurrentTime();

    // add the component
    m_AnimatedComponents.Add(&symbol);

    // start the timer
    m_Timer = SetTimer(ANIMATE_TIMER, 50, NULL);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::AnimateSymbols(CODComponentSet& set,
                                                     bool             useColor,
                                                     COLORREF         color,
                                                     std::size_t      animateCounter)
{
    if (useColor)
        m_AnimateSeconds = animateCounter;
    else
        m_AnimateCounter = animateCounter;

    m_AnimatedUseColor = useColor;
    m_AnimatedColor    = color;

    // kill the timer if necessary
    if (m_Timer)
        EndAnimateTimer();

    m_TimerStartTime = PSS_Date::GetCurrentTime();

    // copy symbol to set
    CODComponentIterator it(&set);

    for (CODComponent* pSrcComp = it.GetFirst(); pSrcComp; pSrcComp = it.GetNext())
        m_AnimatedComponents.Add(pSrcComp);

    // start the timer
    m_Timer = SetTimer(ANIMATE_TIMER, 50, NULL);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::AnimateLink(CODLinkComponent& link,
                                                  bool              useColor,
                                                  COLORREF          color,
                                                  std::size_t       animateCounter)
{
    if (useColor)
        m_AnimateSeconds = animateCounter;
    else
        m_AnimateCounter = animateCounter;

    m_AnimatedUseColor = useColor;
    m_AnimatedColor    = color;

    // kill the timer if necessary
    if (m_Timer)
        EndAnimateTimer();

    m_TimerStartTime = PSS_Date::GetCurrentTime();

    // add the component
    m_AnimatedComponents.Add(&link);

    // start the timer
    m_Timer = SetTimer(ANIMATE_TIMER, 50, NULL);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::AnimateLinks(CODComponentSet& set,
                                                   bool             useColor,
                                                   COLORREF         color,
                                                   std::size_t      animateCounter)
{
    if (useColor)
        m_AnimateSeconds = animateCounter;
    else
        m_AnimateCounter = animateCounter;

    m_AnimatedUseColor = useColor;
    m_AnimatedColor    = color;

    // kill the timer if necessary
    if (m_Timer)
        EndAnimateTimer();

    m_TimerStartTime = PSS_Date::GetCurrentTime();

    // copy symbol to set
    CODComponentIterator it(&set);

    for (CODComponent* pSrcComp = it.GetFirst(); pSrcComp; pSrcComp = it.GetNext())
        m_AnimatedComponents.Add(pSrcComp);

    // start the timer
    m_Timer = SetTimer(ANIMATE_TIMER, 50, NULL);
}
//---------------------------------------------------------------------------
CODDeleteCommand* PSS_ProcessGraphModelController::ExecuteDeleteCommand(CODComponentSet* pCompSet)
{
    if (pCompSet && !m_CutCommand)
    {
        PSS_ProcessGraphModelMdl* pModel = GetModel();

        // iterate through all components and call the PreDelete method.
        // If return false, remove the component from the set
        for (int i = 0; i < pCompSet->GetSize(); ++i)
        {
            CODComponent* pComp   = pCompSet->GetAt(i);
            PSS_Symbol*   pSymbol = dynamic_cast<PSS_Symbol*>(pComp);

            // is a symbol?
            if (pSymbol)
            {
                // check if pre-delete returns ok
                if (!pSymbol->OnPreDelete(pModel, this))
                {
                    // remove component from the set
                    pCompSet->RemoveAt(i);
                    --i;
                }

                continue;
            }

            PSS_LinkSymbol* pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pComp);

            // is a link symbol?
            if (pLinkSymbol)
                // check if pre-delete returns ok
                if (!pLinkSymbol->OnPreDelete(pModel, this))
                {
                    // remove component from the set
                    pCompSet->RemoveAt(i);
                    --i;
                }
        }

        // delete the remaining symbols
        CODComponentSet* setCopy = GetSelection();
        RemoveReferenceSymbol(setCopy);
    }

    return CODController::ExecuteDeleteCommand(pCompSet);
}
//---------------------------------------------------------------------------
CODInsertCommand* PSS_ProcessGraphModelController::ExecuteInsertCommand(CODComponent* pComp, const BOOL allowDuplicates)
{
    // copy selected components
    if (m_setSelection.GetSize())
        CopySelectionToSet();

    CODInsertCommand* pCmd = CODController::ExecuteInsertCommand(pComp, allowDuplicates);

    ClearSymbolAddedSet();
    CopySymbolToSymbolAddedSet(pComp);

    return pCmd;
}
//---------------------------------------------------------------------------
CODInsertCommand* PSS_ProcessGraphModelController::ExecuteInsertCommand(CODComponentSet* pCompSet,
                                                                        const BOOL       allowDuplicates)
{
    // copy selected components
    if (m_setSelection.GetSize())
        CopySelectionToSet();

    CODInsertCommand* pCmd = CODController::ExecuteInsertCommand(pCompSet, allowDuplicates);

    ClearSymbolAddedSet();
    CopySymbolsToSymbolAddedSet(pCompSet);

    return pCmd;
}
//---------------------------------------------------------------------------
CODLinkCommand* PSS_ProcessGraphModelController::ExecuteLinkCommand(const CODPointArray& pointArray,
                                                                    CODPortComponent*    pSourcePort,
                                                                    CODPortComponent*    pTargetPort,
                                                                    CODEndpoint*         pSourceEndpoint,
                                                                    CODEndpoint*         pTargetEndpoint)
{
    CODLinkCommand* pCmd = CODController::ExecuteLinkCommand(pointArray,
                                                             pSourcePort,
                                                             pTargetPort,
                                                             pSourceEndpoint,
                                                             pTargetEndpoint);

    return pCmd;
}
//---------------------------------------------------------------------------
CODLinkCommand* PSS_ProcessGraphModelController::ExecuteLinkCommand(CODLinkComponent*    pLinkComp,
                                                                    const CODPointArray& pointArray,
                                                                    CODPortComponent*    pSourcePort,
                                                                    CODPortComponent*    pTargetPort)
{
    CODLinkCommand* pCmd = CODController::ExecuteLinkCommand(pLinkComp, pointArray, pSourcePort, pTargetPort);

    ClearSymbolAddedSet();
    CopySymbolToSymbolAddedSet(pLinkComp);

    return pCmd;
}
//---------------------------------------------------------------------------
CODLinkCommand* PSS_ProcessGraphModelController::ExecuteLinkCommand(CODLinkComponent* pLinkComp,
                                                                    CODPortComponent* pSourcePort,
                                                                    CODPortComponent* pTargetPort)
{
    CODLinkCommand* pCmd = CODController::ExecuteLinkCommand(pLinkComp, pSourcePort, pTargetPort);

    ClearSymbolAddedSet();
    CopySymbolToSymbolAddedSet(pLinkComp);

    return pCmd;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnInitialUpdate()
{
    ReleaseClipboard();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnModelDocumentHasChanged()
{
    // if an element is selected, do nothing
    if (GetSelection()->GetSize() > 0)
        return;

    // is the root model?
    if (GetModel() != GetRootModel())
        return;

    // unselect all components to avoid problems
    UnselectAllComponents();

    return;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnStartEditProperty()
{
    if (m_IsEditingSymbolName || m_IsEditingSymbolComment)
        EndTextEdit(0, m_SavedEditPosition);

    return;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnSelectionChange(CODComponentSet* pChangedSet)
{
    CODController::OnSelectionChange(pChangedSet);

    // indicate that the selection has changed
    m_SelectionChanged = true;

    // used to keep the last selected element. The user can therefore determine if he wants to edit the label
    if (GetSelection()->GetSize() == 1)
    {
        if (ISA(GetSelection()->GetAt(0), CODSymbolComponent))
            m_LastSelectedElement = static_cast<CODSymbolComponent*>(GetSelection()->GetAt(0));
        else
        if (ISA(GetSelection()->GetAt(0), CODLabelComponent))
            m_LastSelectedElement = static_cast<CODLabelComponent*>(GetSelection()->GetAt(0))->GetOwner();
        else
            m_LastSelectedElement = NULL;

        return;
    }

    m_LastSelectedElement = NULL;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    PSS_ProcessGraphModelMdl* pModel          = GetModel();
    PSS_SymbolLogObserverMsg* pLogObserverMsg = dynamic_cast<PSS_SymbolLogObserverMsg*>(pMsg);

    if (pLogObserverMsg)
    {
        if (pModel)
        {
            CODComponentSet* pSet = pModel->GetRoot()->FindSymbol(pLogObserverMsg->GetErrorLine().GetSymbolName(),
                                                                  pLogObserverMsg->GetErrorLine().GetSymbolPath(),
                                                                  true,
                                                                  true,
                                                                  true);

            if (pSet && pSet->GetSize() > 0)
            {
                COLORREF AnimatedColor;

                if (pLogObserverMsg->GetErrorLine().GetErrorType() == 1)
                    AnimatedColor = defCOLOR_RED;
                else
                    AnimatedColor = defCOLOR_GREEN;

                // certify that the first symbol is visible at least
                EnsureSymbolVisible(pSet->GetAt(0));
                AnimateSymbols(*pSet, true, AnimatedColor, 10);
            }
            else
            {
                PSS_MsgBox mBox;
                mBox.Show(IDS_SYMBOLNOTFOUND_USESEARCH, MB_OK);
            }
        }
    }
    else
    {
        PSS_DocumentObserverMsg* pDocObserverMsg = dynamic_cast<PSS_DocumentObserverMsg*>(pMsg);

        if (pDocObserverMsg)
        {
            PSS_ProcessGraphModelDoc* pObserverDocument =
                    dynamic_cast<PSS_ProcessGraphModelDoc*>(pDocObserverMsg->GetDocument());

            if (pObserverDocument && pObserverDocument == GetDocument())
                switch (pDocObserverMsg->GetMessageID())
                {
                    case UM_FRAMEHASBEENACTIVATED:
                        AssignSymbolHit();

                        // notify about the new selection
                        NotifySymbolSelected(m_pSymbolHit);
                        break;
                }
            else
                NotifyAllObservers(pMsg);
        }
    }

    // update the background image
    if (pModel)
    {
        PSS_ProcessGraphModelMdl* pRoot = pModel->GetRoot();

        if (pRoot && pRoot->IsBkGndMustBeRestored())
        {
            const CString fileName = pRoot->GetBkGndFileName();

            if (!fileName.IsEmpty())
                SetImage(fileName, pRoot->IsLogo());

            pRoot->ResetBkGndMustBeRestored();
        }
    }
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelController::OnToolTip(CString& toolTipText, const CPoint& point, PSS_Symbol::IEToolTipMode mode)
{
    CPoint pt(point);
    VpDPtoLP(&pt);

    CODComponent* pCompHit  = NULL;
    CODViewport*  pCanvasVp = GetCanvasVp();

    if (pCanvasVp)
        pCompHit = pCanvasVp->ComponentHitTest(pt);

    // if a label, reassign the hit symbol
    if (pCompHit && ISA(pCompHit, CODLabelComponent))
        pCompHit = static_cast<CODLabelComponent*>(pCompHit)->GetOwner();

    PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pCompHit);

    if (pSymbol)
        return pSymbol->OnToolTip(toolTipText, pt, mode);

    PSS_LinkSymbol* pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pCompHit);

    if (pLinkSymbol)
        return pLinkSymbol->OnToolTip(toolTipText, pt, mode);

    return false;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::NotifySymbolSelected(CODComponent* pComp)
{
    // if in format painter, forward the process to the ApplyFormatToSymbol function
    if (m_IsInFormatPainter)
    {
        ApplyFormatToSymbol(pComp);
        return;
    }

    PSS_ProcessGraphModelDoc* pDoc    = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());
    PSS_Symbol*               pSymbol = dynamic_cast<PSS_Symbol*>(pComp);

    if (pSymbol)
    {
        PSS_PropertyObserverMsg msg   (pSymbol);
        PSS_SymbolObserverMsg   symMsg(PSS_SymbolObserverMsg::IE_AT_ElementSelected, pSymbol);

        // notify direct observers
        NotifyAllObservers(&msg);
        NotifyAllObservers(&symMsg);

        // notify all document observers
        if (pDoc)
        {
            pDoc->NotifyAllObservers(&msg);
            pDoc->NotifyAllObservers(&symMsg);
        }

        return;
    }

    PSS_LinkSymbol* pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pComp);

    if (pLinkSymbol)
    {
        PSS_PropertyObserverMsg msg   (pLinkSymbol);
        PSS_SymbolObserverMsg   symMsg(PSS_SymbolObserverMsg::IE_AT_ElementSelected, pLinkSymbol);

        // notify direct observers
        NotifyAllObservers(&msg);
        NotifyAllObservers(&symMsg);

        // notify all document observers
        if (pDoc)
        {
            pDoc->NotifyAllObservers(&msg);
            pDoc->NotifyAllObservers(&symMsg);
        }

        return;
    }

    PSS_PropertyObserverMsg msg   (NULL);
    PSS_SymbolObserverMsg   symMsg(PSS_SymbolObserverMsg::IE_AT_ElementSelected, NULL);

    // Notify direct observers
    NotifyAllObservers(&msg);
    NotifyAllObservers(&symMsg);

    // notify all document observers
    if (pDoc)
    {
        pDoc->NotifyAllObservers(&msg);
        pDoc->NotifyAllObservers(&symMsg);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelController::StartTextEdit(UINT flags, CPoint point)
{
    CPoint ptLog = point;
    VpDPtoLP(&ptLog);

    CODViewport* pCanvasVp = GetCanvasVp();
    m_pCompHit             = NULL;

    if (pCanvasVp)
        m_pCompHit = GetCanvasVp()->ComponentHitTest(ptLog);

    PSS_Symbol*       pSymbol     =                  dynamic_cast<PSS_Symbol*>(m_pCompHit);
    PSS_LinkSymbol*   pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pCompHit);
    CODTextComponent* pTextComp   = NULL;

    if (pSymbol || pLinkSymbol)
    {
        CODEditProperties* pEditProps      = static_cast<CODEditProperties*>(m_pCompHit->GetProperty(OD_PROP_EDIT));
        CODEditProperties* pModelEditProps = static_cast<CODEditProperties*>(GetCanvasModel()->GetProperty(OD_PROP_EDIT));

        if (GetCanvasModel()->GetDesignMode() || (!pEditProps->IsReadOnly() && !pModelEditProps->IsReadOnly()))
        {
            m_pSymbolHit = static_cast<CODSymbolComponent*>(m_pCompHit);

            if (pSymbol)
            {
                // can the symbol name be edited?
                if (pSymbol->SymbolNameTextEditReadOnly())
                    return FALSE;

                // edit the symbol name
                pTextComp = pSymbol->GetSymbolNameTextEdit();
            }
            else
            if (pLinkSymbol)
            {
                // can the symbol name be edited?
                if (pLinkSymbol->SymbolNameTextEditReadOnly())
                    return FALSE;

                // edit the symbol name
                pTextComp = pLinkSymbol->GetSymbolNameTextEdit();
            }

            // is in the name region?
            if (pTextComp)
            {
                CODRgn rgn = pTextComp->GetRgn();

                // not in region, reset pTextComp
                if (!rgn.PtInRegion(point, 4))
                    pTextComp = NULL;
            }

            if (!pTextComp)
                if (pSymbol)
                {
                    // can the symbol comment be edited?
                    if (pSymbol->CommentTextEditReadOnly())
                        return FALSE;

                    // edit the symbol comment
                    pTextComp = pSymbol->GetCommentTextEdit();
                }
                else
                if (pLinkSymbol)
                {
                    // can the symbol comment be edited?
                    if (pLinkSymbol->CommentTextEditReadOnly())
                        return FALSE;

                    // edit the symbol comment
                    pTextComp = pLinkSymbol->GetCommentTextEdit();
                }

            // is in the comment region?
            if (pTextComp)
            {
                CODRgn rgn = pTextComp->GetRgn();

                // not in region, reset pTextComp
                if (!rgn.PtInRegion(point, 4))
                    pTextComp = NULL;
            }
        }
    }
    else
    {
        m_pSymbolHit = NULL;
        return CODController::StartTextEdit(flags, point);
    }

    BOOL editing = FALSE;

    // found a component to edit, and not already editing it?
    if (pTextComp && !pTextComp->IsEditing())
    {
        CODEditProperties* pEditProps = static_cast<CODEditProperties*>(pTextComp->GetProperty(OD_PROP_EDIT));
        ASSERT_VALID(pEditProps);

        if (pEditProps->IsReadOnly())
            return FALSE;

        CODComponentSet setUpdate;
        setUpdate.Add(m_pCompHit);

        if (pTextComp != m_pTextEdit)
        {
            EndTextEdit(0, m_SavedEditPosition);

            m_pTextEdit = pTextComp;
            m_pTextEdit->AddRef();

            CODViewport* pCanvasVp = GetCanvasVp();

            if (pCanvasVp)
            {
                editing = m_pTextEdit->BeginEdit(pCanvasVp);

                if (editing)
                    pCanvasVp->UpdateComponents(&setUpdate);
            }
        }
    }

    return editing;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::EndTextEdit(UINT nFlags, CPoint point)
{
    bool isNameValid = true;

    if (m_pTextEdit)
    {
        const CString value = m_pTextEdit->GetEditText();

        // get the label or edit text owner
        CODComponent* pOwner = NULL;

        // check label component, because it derives from text component
        if (ISA(m_pTextEdit, CODLabelComponent))
            pOwner = static_cast<CODLabelComponent*>(m_pTextEdit)->GetOwner();
        else
        if (ISA(m_pTextEdit, CODTextComponent))
            pOwner = static_cast<CODTextComponent*>(m_pTextEdit)->GetParent();

        PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pOwner);
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pOwner);

        if (pSymbol || pLinkSymbol)
        {
            if (m_IsEditingSymbolName)
            {
                if (value.IsEmpty())
                {
                    PSS_MsgBox mBox;
                    mBox.Show(IDS_SYMBOLNAME_EMPTY, MB_OK);
                    isNameValid = false;
                }

                PSS_ProcessGraphModelMdl* pModel = GetModel();
                PSS_ProcessGraphModelMdl* pRoot  = pModel ? pModel->GetRoot() : NULL;

                if (pRoot)
                    if (pSymbol && pSymbol->GetSymbolName() != value)
                    {
                        // check if new name is valid
                        if (pSymbol->IsNewNameValid(value))
                            pSymbol->SetSymbolName(value);
                        else
                            isNameValid = false;
                    }
                    else
                    if (pLinkSymbol && pLinkSymbol->GetSymbolName() != value)
                        // check if new name is valid
                        if (pLinkSymbol->IsNewNameValid(value))
                            pLinkSymbol->SetSymbolName(value);
                        else
                            isNameValid = false;
            }
            else
            if (m_IsEditingSymbolComment)
                if (pSymbol)
                    pSymbol->SetSymbolComment(value);
                else
                    pLinkSymbol->SetSymbolComment(value);

            // if the name is valid and the edition control will be left, close the editor
            if (isNameValid)
            {
                m_IsEditingSymbolName    = false;
                m_IsEditingSymbolComment = false;
            }
        }
    }

    // call the base class if the new name is valid
    if (isNameValid)
        CODController::EndTextEdit(nFlags, point);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::InsertSymbol(UINT flags, CPoint point)
{
    if (m_pInsert)
        InsertSymbol(m_pInsert, flags, point, true);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::EndLink(UINT flags, CPoint point)
{
    // save the inserted component pointer
    CODComponent* pComp = m_pInsert;

    CODController::EndLink(flags, point);

    // reset the current command identifier
    m_CurrentCommandID = 0;

    CDocument* pDocument = GetDocument();

    // set modified flag
    if (pDocument)
        pDocument->SetModifiedFlag(TRUE);

    PSS_LinkSymbol* pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pComp);

    if (pLinkSymbol)
    {
        PSS_ProcessGraphModelMdl* pModel = GetModel();

        // assign the path
        if (pModel)
            pLinkSymbol->SetAbsolutePath(pModel->GetAbsolutePath());

        // assign by default the unique reference number
        if (GetRootModel())
        {
            const int refNumber = GetRootModel()->GetNextAvailableReferenceNumber();
            pLinkSymbol->SetSymbolReferenceNumber(refNumber);

            PSS_BuildSymbolNewName buildNewName;

            // get the next available name
            pLinkSymbol->SetSymbolName(buildNewName.GetNextAvailableSymbolName(*GetRootModel(), refNumber));
        }

        // call for the post-creation
        if (!pLinkSymbol->OnPostCreation(pModel, this))
        {
            // delete the object
            CancelLink(flags, point);
            return;
        }

        // refresh the attribute area and redraw the symbol
        pLinkSymbol->RefreshAttributeTextArea(true);

        if (m_NewSymbolCreated && pLinkSymbol->IsLocal())
        {
            // save the position
            m_SavedEditPosition = point;

            // edit name directly
            EditName(pComp);
        }

        // notify new selection
        NotifySymbolSelected(pComp);

        // notify that a symbol was added
        OnSymbolAdded(&m_SymbolAddedSet);

        // reset the creation flag
        m_NewSymbolCreated = false;
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnSymbolAdded(CODComponentSet* pCompSet)
{
    DetermineReferencedSymbol(pCompSet);

    PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());
    PSS_Assert(pDoc);

    // notify observers for all added symbols
    CODComponentIterator it(pCompSet);

    for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext())
    {
        PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pComp);
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

        if (pSymbol || pLinkSymbol)
        {
            // build the message
            PSS_DocObserverMsg docMsg(PSS_DocObserverMsg::IE_AT_AddElement,
                                      NULL,
                                      GetModel(),
                                      static_cast<CODSymbolComponent*>(pComp));

            CWnd* pMainWnd = ::AfxGetMainWnd();

            if (pMainWnd)
                pMainWnd->SendMessageToDescendants(UM_ELEMENTADDEDDOCUMENTMODEL, 0, LPARAM(&docMsg));

            // call the utility class for manipulating dynamic attributes and
            // assign required dynamic properties on new symbol
            if (pDoc->HasDynamicPropertiesManager())
                if (pSymbol)
                    PSS_DynamicAttributesManipulator::AssignDynamicPropertyOnSymbol(pDoc->GetDynamicPropertiesManager(),
                                                                                    pSymbol);
                else
                    PSS_DynamicAttributesManipulator::AssignDynamicPropertyOnSymbol(pDoc->GetDynamicPropertiesManager(),
                                                                                    pLinkSymbol);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnSymbolDuplicated(CODComponentSet* pCompSet)
{
    int                  index        = 0;
    int                  copySetCount = m_CopySet.GetSize();
    CODComponentIterator it(pCompSet);

    // iterate through added elements and change their names. If symbols have child components,
    // asks the user to duplicate sub-components. Notify observers for all added symbols
    for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext(), ++index)
    {
        PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pComp);

        if (pSymbol)
        {
            if (copySetCount > index)
            {
                // get the matching source symbol
                PSS_Symbol* pSrcSymbol = dynamic_cast<PSS_Symbol*>(m_CopySet.GetAt(index));

                if (pSrcSymbol)
                    pSymbol->CopySymbolDefinitionFrom(*pSrcSymbol);
            }

            const int refNumber = GetRootModel()->GetNextAvailableReferenceNumber();
            pSymbol->SetSymbolReferenceNumber(refNumber);

            PSS_BuildSymbolNewName buildNewName(pSymbol->GetSymbolName());

            // get the next available name
            pSymbol->SetSymbolName(buildNewName.GetNextAvailableSymbolName(*GetRootModel(), refNumber));

            continue;
        }

        PSS_LinkSymbol* pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pComp);

        if (pLinkSymbol)
        {
            if (copySetCount > index)
            {
                // get the matching source symbol
                PSS_LinkSymbol* pSrcLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(m_CopySet.GetAt(index));

                if (pSrcLinkSymbol)
                    pLinkSymbol->CopySymbolDefinitionFrom(*pSrcLinkSymbol);
            }

            const int refNumber = GetRootModel()->GetNextAvailableReferenceNumber();
            pLinkSymbol->SetSymbolReferenceNumber(refNumber);

            PSS_BuildSymbolNewName buildNewName(pLinkSymbol->GetSymbolName());

            // get the next available name
            pLinkSymbol->SetSymbolName(buildNewName.GetNextAvailableSymbolName(*GetRootModel(), refNumber));
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnPostCutPasteOperation(CODComponentSet* pCompSet)
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::AssignSymbolHit()
{
    CODComponentSet* pSelection = GetSelection();

    if (!pSelection || pSelection->GetSize() != 1)
    {
        m_pSymbolHit = NULL;
        return;
    }

    if (ISA(pSelection->GetAt(0), PSS_Symbol) || ISA(pSelection->GetAt(0), PSS_LinkSymbol))
        m_pSymbolHit = dynamic_cast<CODSymbolComponent*>(pSelection->GetAt(0));
    else
    if (ISA(pSelection->GetAt(0), CODLabelComponent))
        // select the symbol behind
        m_pSymbolHit = dynamic_cast<CODLabelComponent*>(GetSelection()->GetAt(0))->GetOwner();
    else
        m_pSymbolHit = NULL;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::AssignLabelHit()
{
    CODComponentSet* pSelection = GetSelection();

    if (!pSelection || pSelection->GetSize() != 1)
    {
        m_pSymbolHit = NULL;
        return;
    }

    if (ISA(pSelection->GetAt(0), CODLabelComponent))
    {
        m_pLabelHit = static_cast<CODLabelComponent*>(GetSelection()->GetAt(0));

        // select the symbol behind
        m_pSymbolHit = m_pLabelHit->GetOwner();
    }
    else
        m_pLabelHit = NULL;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::DetermineReferencedSymbol(CODComponentSet* pCompSet)
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();
    PSS_ProcessGraphModelMdl* pRoot  = pModel ? pModel->GetRoot() : NULL;
    PSS_Assert(pRoot);

    CODComponentIterator it(&m_CopySet);

    // for each symbol coming from the copy source, locate the copied symbol
    for (CODComponent* pSrcComp = it.GetFirst(); pSrcComp; pSrcComp = it.GetNext())
    {
        PSS_Symbol* pSrcSymbol = dynamic_cast<PSS_Symbol*>(pSrcComp);

        if (pSrcSymbol)
        {
            CODComponentIterator itSym(pCompSet);

            for (CODComponent* pComp = itSym.GetFirst(); pComp; pComp = itSym.GetNext())
            {
                PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(pComp);

                if (pSymbol)
                    if (!pSrcSymbol->GetSymbolName().IsEmpty() &&
                         pSrcSymbol->GetSymbolName() == pSymbol->GetSymbolName())
                    {
                        pSymbol->CopySymbolDefinitionFrom(*pSrcSymbol);

                        // set a new reference number
                        pSymbol->SetSymbolReferenceNumber(pRoot->GetNextAvailableReferenceNumber());

                        // assign the reference
                        pSymbol->AssignReferenceSymbol(pSrcSymbol);

                        // set symbol as a copy
                        pSymbol->SetIsCopy();
                    }
            }

            continue;
        }

        PSS_LinkSymbol* pSrcLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pSrcComp);

        if (pSrcLinkSymbol)
        {
            CODComponentIterator itSym(pCompSet);

            for (CODComponent* pComp = itSym.GetFirst(); pComp; pComp = itSym.GetNext())
            {
                PSS_LinkSymbol* pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pComp);

                if (pLinkSymbol)
                    if (!pSrcLinkSymbol->GetSymbolName().IsEmpty() &&
                         pSrcLinkSymbol->GetSymbolName() == pLinkSymbol->GetSymbolName())
                    {
                        pLinkSymbol->CopySymbolDefinitionFrom(*pSrcLinkSymbol);

                        // set a new reference number
                        pLinkSymbol->SetSymbolReferenceNumber(pRoot->GetNextAvailableReferenceNumber());

                        // assign the reference
                        pLinkSymbol->AssignReferenceSymbol(pSrcLinkSymbol);

                        // set symbol as a copy
                        pLinkSymbol->SetIsCopy();
                    }
            }
        }
    }

    // update symbols
    GetVp()->DrawComponents(pCompSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::RemoveReferenceSymbol(CODComponentSet* pCompSet)
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();
    CODComponentIterator      it(pCompSet);

    // iterate through components and detach symbol observers
    for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext())
    {
        PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pComp);
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

        if (pSymbol || pLinkSymbol)
        {
            if (pSymbol)
                pSymbol->RemoveReferenceSymbol();
            else
            if (pLinkSymbol)
                pLinkSymbol->RemoveReferenceSymbol();

            CWnd* pMainWnd = ::AfxGetMainWnd();

            // build the message
            if (pMainWnd)
            {
                PSS_DocObserverMsg docMsg(PSS_DocObserverMsg::IE_AT_RemoveElement, NULL, pModel, static_cast<CODSymbolComponent*>(pComp));
                pMainWnd->SendMessageToDescendants(UM_ELEMENTREMOVEDDOCUMENTMODEL, 0, LPARAM(&docMsg));
            }
        }
    }
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelViewport* PSS_ProcessGraphModelController::BrowseSymbolModel(PSS_Symbol* pSymbol)
{
    PSS_ProcessGraphModelDoc* pDocument = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    if (pDocument)
    {
        PSS_ProcessGraphModelMdl* pModel       = pDocument->GetModel();
        PSS_ProcessGraphModelMdl* pSymbolModel = pModel ? pModel->GetSymbolModel(pSymbol) : NULL;

        // if can't activate a view with model name, create a new view
        if (pSymbolModel)
        {
            PSS_ProcessGraphModelViewport* pViewport = BrowseModel(pSymbolModel, pSymbolModel->GetParent());

            if (pViewport)
            {
                CODComponentSet compSet;
                compSet.Add(pSymbol);
                pViewport->CenterOnComponents(&compSet);
            }

            return pViewport;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelViewport* PSS_ProcessGraphModelController::BrowseLinkSymbolModel(PSS_LinkSymbol* pSymbol)
{
    PSS_ProcessGraphModelDoc* pDocument = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    if (pDocument)
    {
        PSS_ProcessGraphModelMdl* pModel       = pDocument->GetModel();
        PSS_ProcessGraphModelMdl* pSymbolModel = pModel ? pModel->GetLinkSymbolModel(pSymbol) : NULL;

        // if can't activate a view with model name, create a new view
        if (pSymbolModel)
        {
            PSS_ProcessGraphModelViewport* pViewport = BrowseModel(pSymbolModel, pSymbolModel->GetParent());

            if (pViewport)
            {
                CODComponentSet compSet;
                compSet.Add(pSymbol);
                pViewport->CenterOnComponents(&compSet);
            }

            return pViewport;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::CopySelectionToSet()
{
    ClearSelectionToSet();

    CODComponentIterator it(&m_setSelection);

    for (CODComponent* pSrcComp = it.GetFirst(); pSrcComp; pSrcComp = it.GetNext())
        m_CopySet.Add(pSrcComp);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::CopySymbolsToSymbolAddedSet(CODComponentSet* pCompSet)
{
    if (!pCompSet)
        return;

    CODComponentIterator it(pCompSet);

    // copy all pointers
    for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext())
        CopySymbolToSymbolAddedSet(pComp);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::CopyToClipboardSet(CODComponentSet* pCompSet)
{
    PSS_Assert(pCompSet);

    if (pCompSet && pCompSet->GetSize() > 0)
    {
        EmptyClipboardSet();

        // copy selected components to clipboard using custom clipboard format
        StoreComponentsToSet(*pCompSet);

        OpenClipboard();
        EmptyClipboard();

        CSharedFile file;
        CArchive    ar(&file, CArchive::store);

        StoreComponents(ar, *pCompSet);

        ar.Close();

        ::SetClipboardData(m_cfCanvas, file.Detach());

        // copy selected components to clipboard in enhanced metafile format
        if (ClipboardEnhMetafileEnabled())
        {
            CODViewport* pCanvasVp = GetCanvasVp();

            if (pCanvasVp)
            {
                std::unique_ptr<CMetaFileDC> pMetaDC(pCanvasVp->CreateMetafile(*pCompSet));

                if (pMetaDC.get())
                {
                    HENHMETAFILE hMetaFile = pMetaDC->CloseEnhanced();
                    ::SetClipboardData(CF_ENHMETAFILE, hMetaFile);
                }
            }
        }

        CloseClipboard();
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::EmptyClipboardSet()
{
    m_CutSet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::StoreComponentsToSet(const CODComponentSet& compSet)
{
    CODComponentSet primarySet;
    primarySet.Append(compSet);

    const int compCount = compSet.GetSize();

    // include labels and contained objects
    for (int i = 0; i < compCount; ++i)
    {
        CODComponent* pComp = compSet.GetAt(i);

        switch (m_state)
        {
            case OD_MOVE_START:
            case OD_MOVING:       pComp->GetTranslateSet(primarySet); break;
            case OD_ROTATE_START:
            case OD_ROTATING:     pComp->GetRotateSet(primarySet);    break;
            case OD_SCALE_START:
            case OD_SCALING:      pComp->GetScaleSet(primarySet);     break;
        }
    }

    CODConnectionSet movingConnectionSet;
    const int        primaryCount = primarySet.GetSize();

    // get all connections affected by symbols that are moving
    for (int i = 0; i < primaryCount; ++i)
    {
        CODSymbolComponent* pSymbol = dynamic_cast<CODSymbolComponent*>(primarySet.GetAt(i));

        if (pSymbol)
            pSymbol->GetMovingConnections(movingConnectionSet);
    }

    CODComponentSet dependentSet;
    const int       movingConnectionCount = movingConnectionSet.GetSize();

    // check moving connections and extract the symbols. Affected Symbols which
    // are not already included in the primary set are added to the dependent
    // symbol set
    for (int connectIndex = 0; connectIndex < movingConnectionCount; ++connectIndex)
    {
        CODConnection* pConnection = movingConnectionSet.GetAt(connectIndex);
        PSS_Assert(pConnection);

        ASSERT_VALID(pConnection->GetSourcePort());
        CODSymbolComponent* pSourceSymbol = pConnection->GetSourcePort()->GetOwner();

        ASSERT_VALID(pConnection->GetTargetPort());
        CODSymbolComponent* pTargetSymbol = pConnection->GetTargetPort()->GetOwner();

        BOOL sourceFound = FALSE;
        BOOL targetFound = FALSE;

        for (int i = 0; i < primaryCount && (!sourceFound || !targetFound); ++i)
        {
            CODComponent* pComp = primarySet.GetAt(i);

            if (pSourceSymbol == pComp || pComp->IsChild(pSourceSymbol))
                sourceFound = TRUE;

            if (pTargetSymbol == pComp || pComp->IsChild(pTargetSymbol))
                targetFound = TRUE;
        }

        const int dependentCount = dependentSet.GetSize();

        for (int j = 0; j < dependentCount && (!sourceFound || !targetFound); ++j)
        {
            CODComponent* pDepComp = dependentSet.GetAt(j);

            if (pSourceSymbol == pDepComp || pDepComp->IsChild(pSourceSymbol))
                sourceFound = TRUE;

            if (pTargetSymbol == pDepComp || pDepComp->IsChild(pTargetSymbol))
                targetFound = TRUE;
        }

        if (!sourceFound)
        {
            //dependentSet.Add(pSourceSymbol);
        }

        if (!targetFound)
        {
            //dependentSet.Add(pTargetSymbol);
        }
    }

    // iterate through the primary set and dependent set and serialize the components
    CODComponentSet* pCurSet = &dependentSet;

    for (int setCount = 1; setCount <= 2; ++setCount)
    {
        const int curSetCount = pCurSet->GetSize();

        for (int i = 0; i < curSetCount; ++i)
        {
            CODComponent*       pComp   = pCurSet->GetAt(i);
            CODSymbolComponent* pSymbol = dynamic_cast<CODSymbolComponent*>(pComp);
            CODConnectionSet    detachedSet;

            if (pSymbol)
            {
                CODConnectionSet connectionSet;

                // any connections to symbols that are not going to be serialized
                // must be detached. This eliminates dangling references
                pSymbol->GetAllConnections(connectionSet);

                const int connectionCount = connectionSet.GetSize();

                for (int connectIndex = 0; connectIndex < connectionCount; ++connectIndex)
                {
                    CODConnection* pConnection = connectionSet.GetAt(connectIndex);

                    if (movingConnectionSet.FindIndex(pConnection) == -1)
                    {
                        pSymbol->Detach(pConnection);
                        detachedSet.Add(pConnection);
                    }
                }
            }

            // keep the component
            m_CutSet.Add(pComp);

            // Concatenate all parent transformations and store them with the component.
            // This is necessary because the parent isn't being saved with the component,
            // but the component is still wanted to be rendered in the same place. When
            // read back in, the parent transform matrix is concatenated with the component
            // transform matrix
            CODTransform parentXform;

            pComp->ConcatParentTransforms(parentXform);

            if (pSymbol)
            {
                const int detachedCount = detachedSet.GetSize();

                // re-attach previously detached connections
                for (int connectIndex = 0; connectIndex < detachedCount; ++connectIndex)
                {
                    CODConnection* pConnection = detachedSet.GetAt(connectIndex);
                    pSymbol->Attach(pConnection);
                }
            }
        }

        pCurSet = &primarySet;
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::ApplyFormatToSymbol(CODComponent* pComp)
{
    // no object to format
    if (!pComp)
        return;

    // not to the same object
    if (pComp == m_pFormatPainterSymbol)
        return;

    PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pComp);
    PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

    if (pSymbol)
        pSymbol->ApplyFormatFromObject(*m_pFormatPainterSymbol);
    else
    if (pLinkSymbol)
        pLinkSymbol->ApplyFormatFromObject(*m_pFormatPainterSymbol);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnMouseMove(UINT flags, CPoint point)
{
    static HCURSOR oldCursor = NULL;
    static HCURSOR badCursor = NULL;
           HCURSOR curCursor = ::GetCursor();
           bool    handled   = false;

    if (m_pViewport)
    {
        // handle the tooltip
        CPoint pt(point);
        VpDPtoLP(&pt);

        CODComponent* pCompHit = m_pViewport->ComponentHitTest(pt);

        // if a label, reassign the hit symbol
        if (pCompHit && ISA(pCompHit, CODLabelComponent))
            pCompHit = static_cast<CODLabelComponent*>(pCompHit)->GetOwner();

        PSS_ProcessGraphModelView* pView       = GetView();
        PSS_Symbol*                pSymbol     =                  dynamic_cast<PSS_Symbol*>(pCompHit);
        PSS_LinkSymbol*            pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pCompHit);

        if (pSymbol || pLinkSymbol)
        {
            // call the symbol OnMouseMove function to check if it's necessary to do something
            if (pSymbol && pSymbol->AcceptMouseInteraction())
                handled = pSymbol->OnMouseMove(flags, pt, *this);
            else
            if (pLinkSymbol && pLinkSymbol->AcceptMouseInteraction())
                handled = pLinkSymbol->OnMouseMove(flags, pt, *this);

            if (pView)
                // show the tooltip
                if (::IsWindow(pView->GetToolTip().m_hWnd))
                    pView->GetToolTip().Activate(TRUE);
        }
        else
        if (pView)
            // hide the tooltip
            if (::IsWindow(pView->GetToolTip().m_hWnd))
                pView->GetToolTip().Activate(FALSE);
    }

    if (m_CurrentCursor)
        SetCustomCursor(m_CurrentCursor);
    else
    {
        if (curCursor != ::GetCursor())
            badCursor = ::GetCursor();

        if (!handled)
            if (::GetCursor() != badCursor)
                oldCursor = ::GetCursor();

            if (oldCursor)
                ::SetCursor(oldCursor);
    }

    if (!handled)
        CODController::OnMouseMove(flags, point);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnLButtonDblClk(UINT flags, CPoint point)
{
    bool handled = false;

    if (m_pViewport)
    {
        // handle the tooltip
        CPoint pt(point);
        VpDPtoLP(&pt);

        CODComponent* pCompHit = m_pViewport->ComponentHitTest(pt);

        // if a label, reassign the hit symbol
        if (pCompHit && ISA(pCompHit, CODLabelComponent))
            pCompHit = static_cast<CODLabelComponent*>(pCompHit)->GetOwner();

        PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pCompHit);
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pCompHit);

        // call the symbol OnLButtonDblClk function to check if it's necessary to do something
        if (pSymbol && pSymbol->AcceptMouseInteraction())
            handled = pSymbol->OnLButtonDblClk(flags, pt, *this);
        else
        if (pLinkSymbol && pLinkSymbol->AcceptMouseInteraction())
            handled = pLinkSymbol->OnLButtonDblClk(flags, pt, *this);
    }

    // don't continue if the double click was already handled
    if (handled)
        return;

    // if not handled, do the work
    CODComponent* pComp = NULL;

    AssignSymbolHit();

    PSS_ProcessGraphModelMdl* pModel         = GetModel();
    PSS_Symbol*               pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol*           pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);

    // If the symbol has a child model, open it
    if (pSymbolHit && (pSymbolHit->GetChildModel() || pSymbolHit->CanContainChildModel()))
    {
        OpenSymbol(m_pSymbolHit);

        if (m_pSymbolHit != pSymbolHit)
            pSymbolHit = dynamic_cast<PSS_Symbol*>(m_pSymbolHit);

        // call the OnPostDoubleClick function on the symbol
        if (pSymbolHit)
            pSymbolHit->OnPostDoubleClick(pModel, this);
    }
    else
    // if the symbol is a reference, browse the local symbol
    if ((pSymbolHit && !pSymbolHit->IsLocal()) || (pLinkSymbolHit && !pLinkSymbolHit->IsLocal()))
    {
        BrowseLocalSymbol(m_pSymbolHit);

        // select the local symbol
        SelectComponent(*m_pSymbolHit);

        if ((pSymbolHit && m_pSymbolHit != pSymbolHit) || (pLinkSymbolHit && m_pSymbolHit != pLinkSymbolHit))
        {
            pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
            pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);
        }

        // call the OnPostDoubleClick function on the symbol
        if (pSymbolHit)
            pSymbolHit->OnPostDoubleClick(pModel, this);
        else
            pLinkSymbolHit->OnPostDoubleClick(pModel, this);
    }
    else
        CODController::OnLButtonDblClk(flags, point);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnLButtonDown(UINT flags, CPoint point)
{
    bool handled = false;

    if (m_pViewport)
    {
        // handle the tooltip
        CPoint pt(point);
        VpDPtoLP(&pt);

        CODComponent* pCompHit = m_pViewport->ComponentHitTest(pt);

        SetStandardCursor(IDC_ARROW);
        m_CurrentCursor = 0;

        // process the style brush
        if (m_pFormatPainterSymbol && pCompHit && m_IsInFormatPainter)
        {
            PSS_Symbol*     pSrcSymbol     =                     dynamic_cast<PSS_Symbol*>(m_pFormatPainterSymbol);
            PSS_LinkSymbol* pSrcLinkSymbol = pSrcSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pFormatPainterSymbol);
            PSS_Symbol*     pDstSymbol     =                     dynamic_cast<PSS_Symbol*>(pCompHit);
            PSS_LinkSymbol* pDstLinkSymbol = pDstSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pCompHit);

            if (pSrcSymbol && pDstSymbol)
            {
                if ((pSrcSymbol->IsProcess()   && pDstSymbol->IsProcess())   ||
                    (pSrcSymbol->IsProcedure() && pDstSymbol->IsProcedure()) ||
                    (pSrcSymbol->IsStart()     && pDstSymbol->IsStart())     ||
                    (pSrcSymbol->IsStop()      && pDstSymbol->IsStop())      ||
                    (pSrcSymbol->IsDoor()      && pDstSymbol->IsDoor())      ||
                    (pSrcSymbol->IsPage()      && pDstSymbol->IsPage())      ||
                    (pSrcSymbol->IsPackage()   && pDstSymbol->IsPackage()))
                {
                    if (!PSS_ODSymbolManipulator::CopySymbolStyle(pSrcSymbol, pDstSymbol))
                        return;

                    pDstSymbol->RedrawSymbol();

                    // also copy the new style on the twin symbol
                    if (pDstSymbol->IsDoor() || pDstSymbol->IsPage())
                        pDstSymbol->DuplicateStyleOnTwinSymbol();

                    CDocument* pDocument = GetDocument();

                    if (pDocument)
                        pDocument->SetModifiedFlag(TRUE);
                }
            }
            else
            if (pSrcLinkSymbol && pDstLinkSymbol)
            {
                CODComponent* pSrcComp = PSS_ODSymbolManipulator::FindSymbol(pSrcLinkSymbol, M_SymbolNameComponentControlLabel);
                CODComponent* pDstComp = PSS_ODSymbolManipulator::FindSymbol(pDstLinkSymbol, M_SymbolNameComponentControlLabel);

                if (pSrcComp && pDstComp)
                {
                    PSS_ODSymbolManipulator::CopySymbolStyle(pSrcComp, pDstComp);
                    pDstLinkSymbol->RedrawSymbol();

                    CDocument* pDocument = GetDocument();

                    if (pDocument)
                        pDocument->SetModifiedFlag(TRUE);
                }
            }
            else
            if (pSrcLinkSymbol && ISA(pCompHit, CODLabelComponent))
            {
                CODComponent* pSrcComp = PSS_ODSymbolManipulator::FindSymbol(pSrcLinkSymbol, M_SymbolNameComponentControlLabel);

                if (pSrcComp && pCompHit)
                {
                    PSS_ODSymbolManipulator::CopySymbolStyle(pSrcComp, pCompHit);
                    RefreshAllSymbols();

                    CDocument* pDocument = GetDocument();

                    if (pDocument)
                        pDocument->SetModifiedFlag(TRUE);
                }
            }

            m_pFormatPainterSymbol = NULL;
        }

        m_IsInFormatPainter = false;

        // if a label, reassign the hit symbol
        if (pCompHit && ISA(pCompHit, CODLabelComponent))
            pCompHit = static_cast<CODLabelComponent*>(pCompHit)->GetOwner();

        PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pCompHit);
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pCompHit);

        // call the symbol OnLButtonDown function to check if it's necessary to do something
        if (pSymbol && pSymbol->AcceptMouseInteraction())
            handled = pSymbol->OnLButtonDown(flags, pt, *this);
        else
        if (pLinkSymbol && pLinkSymbol->AcceptMouseInteraction())
            handled = pLinkSymbol->OnLButtonDown(flags, pt, *this);
    }

    // don't continue if the left button down was already handled
    if (handled)
        return;

    // if not handle, do the work. Saves the previous element
    CODSymbolComponent* pOldSymbolClicked = m_LastSelectedElement;

    CODController::OnLButtonDown(flags, point);

    CDocument* pDoc = GetDocument();

    // notify about the component selection
    NotifySymbolSelected(m_LastSelectedElement);

    // check if selected symbol should be edited
    if (m_SelectionChanged && m_LastSelectedElement)
    {
        // if the user clicked a second time on the same symbol, assume he want to edit its name
        if (pOldSymbolClicked == m_LastSelectedElement)
        {
            bool isLocal = false;

            PSS_Symbol*     pLastSelSymbol     =                         dynamic_cast<PSS_Symbol*>(m_LastSelectedElement);
            PSS_LinkSymbol* pLastSelLinkSymbol = pLastSelSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_LastSelectedElement);

            if (pLastSelSymbol)
                isLocal = pLastSelSymbol->IsLocal();
            else
            if (pLastSelLinkSymbol)
                isLocal = pLastSelLinkSymbol->IsLocal();

            // save the position first
            m_SavedEditPosition = point;

            // edit the element only if the symbol is local
            if (isLocal)
                EditName(m_LastSelectedElement);
        }

        // set back the selection changed flag
        m_SelectionChanged = false;
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnLButtonUp(UINT flags, CPoint point)
{
    bool handled = false;

    if (m_pViewport)
    {
        // handle the tooltip
        CPoint pt(point);
        VpDPtoLP(&pt);

        CODComponent* pCompHit = m_pViewport->ComponentHitTest(pt);

        // if a label, reassign the hit symbol
        if (pCompHit && ISA(pCompHit, CODLabelComponent))
            pCompHit = static_cast<CODLabelComponent*>(pCompHit)->GetOwner();

        PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pCompHit);
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pCompHit);

        // call the symbol OnLButtonUp function to check if it's necessary to do something
        if (pSymbol && pSymbol->AcceptMouseInteraction())
            handled = pSymbol->OnLButtonUp(flags, pt, *this);
        else
        if (pLinkSymbol && pLinkSymbol->AcceptMouseInteraction())
            handled = pLinkSymbol->OnLButtonUp(flags, pt, *this);
    }

    // don't continue if the double click was handled
    if (handled)
        return;

    // if not handle, do the work
    CODController::OnLButtonUp(flags, point);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnRButtonUp(UINT flags, CPoint point)
{
    bool handled = false;

    if (m_pViewport)
    {
        // handle the tooltip
        CPoint pt(point);
        VpDPtoLP(&pt);

        CODComponent* pCompHit = m_pViewport->ComponentHitTest(pt);

        // if a label, reassign the hit symbol
        if (pCompHit && ISA(pCompHit, CODLabelComponent))
            pCompHit = static_cast<CODLabelComponent*>(pCompHit)->GetOwner();

        PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pCompHit);
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pCompHit);

        // call the symbol OnRButtonUp function to check if it's necessary to do something
        if (pSymbol && pSymbol->AcceptMouseInteraction())
            handled = pSymbol->OnRButtonUp(flags, pt, *this);
        else
        if (pLinkSymbol && pLinkSymbol->AcceptMouseInteraction())
            handled = pLinkSymbol->OnRButtonUp(flags, pt, *this);
    }

    // don't continue if the double click was handled
    if (handled)
        return;

    // if not handled, do the work
    AssignSymbolHit();

    if (m_pSymbolHit)
    {
        PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
        PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);

        if (pSymbolHit)
        {
            // no sub-menu defined, return
            if (pSymbolHit->GetRightSubMenu() == -1)
                return;

            if (pSymbolHit->IsLocal())
                m_pRightSubMenu = m_SymbolRightMainMenu.GetSubMenu(pSymbolHit->GetRightSubMenu());
            else
                m_pRightSubMenu = m_SymbolRefRightMainMenu.GetSubMenu(pSymbolHit->GetRightSubMenu());
        }
        else
        if (pLinkSymbolHit)
        {
            // no sub-menu defined, return
            if (pLinkSymbolHit->GetRightSubMenu() == -1)
                return;

            if (pLinkSymbolHit->IsLocal())
                m_pRightSubMenu = m_SymbolRightMainMenu.GetSubMenu(pLinkSymbolHit->GetRightSubMenu());
            else
                m_pRightSubMenu = m_SymbolRefRightMainMenu.GetSubMenu(pLinkSymbolHit->GetRightSubMenu());
        }
    }
    else
    if (GetSelection()->GetSize() >= 1)
    {
        m_pRightSubMenu = m_SymbolRightMainMenu.GetSubMenu(0);
        m_pSymbolHit    = NULL;
    }
    else
    {
        m_pRightSubMenu = NULL;
        m_pSymbolHit    = NULL;
    }

    CODController::OnRButtonUp(flags, point);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnTimer(SEC_UINT eventID)
{
    if (eventID == ANIMATE_TIMER)
        if (m_AnimatedUseColor)
        {
            // it's still time for animation
            if ((m_TimerStartTime + COleDateTimeSpan(0, 0, 0, m_AnimateCounter)) >= PSS_Date::GetCurrentTime())
            {
                if (!m_TimerInitialized)
                {
                    if (m_AnimatedNodes.GetSize() > 0)
                        ChangeColorNodes();

                    if (m_AnimatedEdges.GetSize() > 0)
                        ChangeColorEdges();

                    if (m_AnimatedComponents.GetSize() > 0)
                        ChangeColorSymbols();

                    m_TimerInitialized = true;
                }
            }
            else
                EndAnimateTimer();
        }
        else
        if (m_AnimateCounter > 0)
        {
            if (m_AnimatedNodes.GetSize() > 0)
                AnimateNodes();

            if (m_AnimatedEdges.GetSize() > 0)
                AnimateEdges();

            if (m_AnimatedComponents.GetSize() > 0)
                AnimateSymbols();

            --m_AnimateCounter;
        }
        else
            EndAnimateTimer();

    CODController::OnTimer(eventID);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnSelectAll()
{
    SelectAllComponents();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnEditClear()
{
    m_CutCommand = false;

    AssignSymbolHit();

    // call the base class
    CODController::OnEditClear();

    CDocument* pDocument = GetDocument();

    // set the modification flag
    if (pDocument)
        pDocument->SetModifiedFlag(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnEditCopy()
{
    // clear the clipboard before strating a new copy
    ReleaseClipboard();

    // filter the selection before starting to copy
    if (FilterSelection())
    {
        RefreshAllSymbols();

        PSS_MsgBox mBox;

        CString str = _T("");
        str.Format(IDS_WARNING_COPY_SELECTION);
        mBox.Show(str, MB_OK);
    }

    CopySelectionToSet();

    // call the base class
    CODController::OnEditCopy();

    CDocument* pDocument = GetDocument();

    // set the modification flag
    if (pDocument)
        pDocument->SetModifiedFlag(TRUE);

    m_CutCommand = false;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(ValidateCutCopyOperations());
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnEditCut()
{
    // empty the clipboard before beginning a new cut
    ReleaseClipboard();

    ClearSelectionToSet();
    RemoveReferenceSymbol(GetSelection());

    // filter the selection before allowing to cut
    if (FilterSelection())
    {
        RefreshAllSymbols();

        PSS_MsgBox mBox;

        CString s = _T("");
        s.Format(IDS_WARNING_CUT_SELECTION);
        mBox.Show(s, MB_OK);
    }

    if (m_pTextEdit && m_pTextEdit->IsEditing())
    {
        CEdit* pEdit = m_pTextEdit->GetEditControl();
        PSS_Assert(pEdit);
        pEdit->Cut();
        return;
    }

    PSS_ProcessGraphModelMdl* pRootModel = GetRootModel();
    PSS_Assert(pRootModel);
    pRootModel->SetInCutOperation(true);

    CODComponentSet* pSelection = GetSelection();

    // copy the selection to the clipboard set
    CopyToClipboardSet(pSelection);
    ExecuteDeleteCommand(pSelection);

    pRootModel->SetInCutOperation(false);

    CODViewport* pViewport = GetCanvasVp();

    // reset the paste insertion point
    if (pViewport)
        pViewport->SetPasteInsertionPoint(CPoint(0, 0));

    // refresh the tree
    RefreshModelTree();

    CDocument* pDocument = GetDocument();

    // set flag for modification
    if (pDocument)
        pDocument->SetModifiedFlag(TRUE);

    m_CutCommand = true;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateEditCut(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(ValidateCutCopyOperations());
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnEditPaste()
{
    if (m_CutCommand)
    {
        PSS_ProcessGraphModelMdl* pRootModel = GetRootModel();
        PSS_Assert(pRootModel);
        pRootModel->SetInCutOperation(true);

        CODComponent*        pComp = NULL;
        CODComponentIterator it(&m_CutSet);

        // remove labels from the set
        for (pComp = it.GetFirst(); pComp; pComp = it.GetNext())
        {
            CODLabelComponent* pLabel = dynamic_cast<CODLabelComponent*>(pComp);

            if (pLabel)
            {
                it.Remove();
                pComp->Release();
                it.GetPrev();
            }
        }

        CMap<CODComponent*, CODComponent*, int, int> translateSetMap;
        int                                          pos = 0;
        BOOL                                         added;

        for (pComp = it.GetFirst(); pComp; pComp = it.GetNext())
            if (!translateSetMap.Lookup(pComp, added))
            {
                translateSetMap.SetAt(pComp, pos);
                ++pos;
            }

        CODComponentSet translateSet;

        for (pComp = it.GetFirst(); pComp; pComp = it.GetNext())
        {
            pComp->GetTranslateSet(translateSet);

            if (translateSet.GetSize() > 0)
            {
                CODComponentIterator itTransSet(&translateSet);

                for (CODComponent* pTranslateComp = itTransSet.GetFirst(); pTranslateComp; pTranslateComp = itTransSet.GetNext())
                    if (!translateSetMap.Lookup(pTranslateComp, added))
                    {
                        ASSERT_VALID(pTranslateComp);
                        translateSetMap.SetAt(pTranslateComp, pos);
                        pTranslateComp->AddRef();
                        ++pos;
                    }
            }

            translateSet.SetSize(0);
        }

        translateSet.SetSize(translateSetMap.GetCount());

        for (POSITION pPos = translateSetMap.GetStartPosition(); pPos;)
        {
            translateSetMap.GetNextAssoc(pPos, pComp, pos);
            ASSERT_VALID(pComp);
            translateSet.SetAt(pos, pComp);
        }

        CODComponentIterator itTranslate(&translateSet);
        CRect                allCompRect;
        BOOL                 firstComp = TRUE;

        // find bounding rectangle for all components
        for (pComp = itTranslate.GetFirst(); pComp; pComp = itTranslate.GetNext())
        {
            const CPoint compOrigin = pComp->GetOrigin();
            const CSize  compSize   = pComp->GetSize();

            CRect compRect;
            compRect.SetRect(compOrigin.x, compOrigin.y, compOrigin.x + compSize.cx, compOrigin.y + compSize.cy);

            if (firstComp)
            {
                allCompRect = compRect;
                firstComp   = FALSE;
            }
            else
                allCompRect = CODGlobal::UnionRect(allCompRect, compRect);
        }

        CODViewport* pCanvasViewport = GetCanvasVp();

        if (!pCanvasViewport)
            THROW("The canvas viewport could not be found");

        // get the current paste insertion point
        CPoint insertPoint     = pCanvasViewport->GetPasteInsertionPoint();
        CPoint holdInsertPoint = insertPoint;

        int moveX = int(insertPoint.x - allCompRect.TopLeft().x);
        int moveY = int(insertPoint.y - allCompRect.TopLeft().y);

        if ((moveX < 5) && (moveY < 5) && (moveX > -5) && (moveY > -5))
        {
            moveX = 5;
            moveY = 5;
        }

        CODModel* pCanvasModel = GetCanvasModel();
        
        if (!pCanvasModel)
            THROW("The canvas model could not be found");

        // make sure components will be inserted inside the model
        pCanvasModel->FindValidMove(m_CutSet, moveX, moveY, &allCompRect);
        insertPoint.x = LONG(moveX);
        insertPoint.y = LONG(moveY);

        CODTransform translate;

        // translate the components
        translate.Translate(insertPoint.x, insertPoint.y);

        // translate the components to the new insertion point
        for (pComp = itTranslate.GetFirst(); pComp; pComp = itTranslate.GetNext())
        {
            CODTransform* pCompTransform = pComp->GetTransform();

            if (pCompTransform)
                *pCompTransform = translate * (*pCompTransform);
            else
                pComp->SetTransform(new CODTransform(translate));

            pComp->UpdateRgn();

            CODSymbolComponent* pSymbolComp = dynamic_cast< CODSymbolComponent*>(pComp);

            // hide the ports
            if (pSymbolComp)
                pSymbolComp->SetPortsVisible(FALSE);
        }

        // get current viewport visible region info
        allCompRect.OffsetRect(insertPoint);

        CPoint       vpOriginPoint    = pCanvasViewport->GetLogOrigin();
        const CPoint oldVpOriginPoint = vpOriginPoint;
        const CSize  vpSize           = pCanvasViewport->GetLogSize();

        // if new components bottom right corner extends beyond the visible area, pan the viewport so it is visible
        if (vpOriginPoint.x + vpSize.cx < allCompRect.right || vpOriginPoint.y + vpSize.cy < allCompRect.bottom)
        {
            if (vpOriginPoint.x + vpSize.cx < allCompRect.right)
                vpOriginPoint.x = allCompRect.right - vpSize.cx;

            if (vpOriginPoint.y + vpSize.cy < allCompRect.bottom)
                vpOriginPoint.y = allCompRect.bottom - vpSize.cy;

            pCanvasViewport->Pan(vpOriginPoint.x - oldVpOriginPoint.x, vpOriginPoint.y - oldVpOriginPoint.y);
            pCanvasViewport->Invalidate();
        }

        OnPostCutPasteOperation(&m_CutSet);

        // insert the components
        ExecuteInsertCommand(&m_CutSet);

        float gridSpacingLogX;
        float gridSpacingLogY;

        // find new viewport paste insertion point
        pCanvasViewport->GetRuler()->MeasureToLog(pCanvasViewport->GetHorizontalGridSpacing(),
                                                  gridSpacingLogX,
                                                  FALSE);
        pCanvasViewport->GetRuler()->MeasureToLog(pCanvasViewport->GetVerticalGridSpacing(),
                                                  gridSpacingLogY,
                                                  TRUE);

        insertPoint.x += LONG(gridSpacingLogX + 0.5f);
        insertPoint.y += LONG(gridSpacingLogY + 0.5f);

        // set the new viewport paste insertion point
        holdInsertPoint.x += LONG(gridSpacingLogX + 0.5f);
        holdInsertPoint.y += LONG(gridSpacingLogY + 0.5f);

        pCanvasViewport->SetPasteInsertionPoint(holdInsertPoint);

        pRootModel->SetInCutOperation(false);

        // recalculate all references
        pRootModel->RecalculateParent();
        pRootModel->RecalculateAbsolutePath();
    }
    else
    {
        // call the base class
        CODController::OnEditPaste();

        // call the virtual method on symbol added
        OnSymbolAdded(&m_setSelection);
    }

    CDocument* pDocument = GetDocument();

    // set the modification flag
    if (pDocument)
        pDocument->SetModifiedFlag(TRUE);

    RefreshAllSymbols();

    // cleanup the clipboard
    ReleaseClipboard();

    m_CutCommand = false;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnEditDuplicate()
{
    CWaitCursor cursor;

    // call the base class
    CODController::OnEditPaste();

    // call the virtual method on added symbol
    OnSymbolDuplicated(&m_setSelection);

    RefreshAllSymbols();

    CDocument* pDocument = GetDocument();

    // set the modification flag
    if (pDocument)
        pDocument->SetModifiedFlag(TRUE);

    // cleanup the clipboard
    ReleaseClipboard();

    m_CutCommand = false;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateEditDuplicate(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    // allow duplicates only if the selection set contains at least one object
    pCmdUI->Enable(m_CopySet.GetSize() > 0 && CanDuplicateObject(&m_CopySet));
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnEditRedo()
{
    // call the base class
    CODController::OnEditRedo();

    // refresh the tree
    RefreshModelTree();

    CDocument* pDocument = GetDocument();

    // set the modification flag
    if (pDocument)
        pDocument->SetModifiedFlag(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnEditUndo()
{
    // call the base class
    CODController::OnEditUndo();

    CODComponentSet* pSelection = GetSelection();

    if (pSelection)
    {
        const SEC_INT selectionCount = pSelection->GetSize();

        // if the last deleted item was a deliverable, refresh it. This allows the old model symbols
        // to be displayed correctly after an undo command
        for (SEC_INT i = 0; i < selectionCount; ++i)
        {
            PSS_LinkSymbol* pLinkSymbol = dynamic_cast<PSS_LinkSymbol*>(pSelection->GetAt(i));

            if (pLinkSymbol)
            {
                pLinkSymbol->UpdateRgn(TRUE);
                pLinkSymbol->RedrawSymbol();
            }
        }
    }

    // refresh the tree
    RefreshModelTree();

    CDocument* pDocument = GetDocument();

    // set the modification flag
    if (pDocument)
        pDocument->SetModifiedFlag(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnEditName()
{
    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);
    bool            isLocal        = false;

    // check if is local
    if (pSymbolHit)
        isLocal = pSymbolHit->IsLocal();
    else
    if (pLinkSymbolHit)
        isLocal = pLinkSymbolHit->IsLocal();

    if (isLocal)
        EditName(m_pSymbolHit);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateEditName(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);
    BOOL            enable         = FALSE;

    // get the enable flag
    if (pSymbolHit)
        enable = (pSymbolHit->IncludeNameArea() &&
                  pSymbolHit->UseDynamicArea() &&
                  pSymbolHit->IsNameAreaVisible());
    else
    if (pLinkSymbolHit)
        // todo -cBug -oJean: Added CanEditNonDynamicName() as a workaround, but check why a link symbol cannot be dynamic
        enable = (pLinkSymbolHit->IncludeNameArea()                                            &&
                 (pLinkSymbolHit->UseDynamicArea() || pLinkSymbolHit->CanEditNonDynamicName()) &&
                  pLinkSymbolHit->IsNameAreaVisible());

    pCmdUI->Enable(enable);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnEditComment()
{
    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);
    bool            isLocal        = false;

    // check if symbol is local
    if (pSymbolHit)
        isLocal = pSymbolHit->IsLocal();
    else
    if (pLinkSymbolHit)
        isLocal = pLinkSymbolHit->IsLocal();

    if (isLocal)
        EditComment(m_pSymbolHit);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateEditComment(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);
    BOOL            enable         = FALSE;

    // get the enable flag
    if (pSymbolHit)
        enable = (pSymbolHit->IncludeDescriptionArea() &&
                  pSymbolHit->UseDynamicArea()         &&
                  pSymbolHit->IsDescriptionsAreaVisible());
    else
    if (pLinkSymbolHit)
        enable = (pLinkSymbolHit->IncludeDescriptionArea() &&
                  pLinkSymbolHit->UseDynamicArea()         &&
                  pLinkSymbolHit->IsDescriptionsAreaVisible());

    pCmdUI->Enable(enable);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnChangeTextEdit()
{
    // if no symbol selected, call the base class
    if (!m_pSymbolHit)
        CODController::OnChangeTextEdit();

    if (!m_pTextEdit)
        return;

    CODViewport* pCanvasViewport = GetCanvasVp();

    if (!pCanvasViewport)
        return;

    sfl::MvcViewport::DC dc(pCanvasViewport, TRUE);

    CODComponentSet updateSet;
    updateSet.Add(m_pTextEdit);

    if (ISA(m_pTextEdit, CODLabelComponent))
    {
        CODSymbolComponent* pOwner = static_cast<CODLabelComponent*>(m_pTextEdit)->GetOwner();

        if (pOwner)
            updateSet.Add(pOwner);
    }

    pCanvasViewport->UpdateComponents(&updateSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnGoParentModel()
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (pModel)
    {
        PSS_ProcessGraphModelMdl* pParentModel = pModel->GetParent();

        if (pParentModel)
            BrowseModel(pParentModel, pParentModel->GetParent());
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateGoParentModel(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessGraphModelMdl* pModel = GetModel();
    pCmdUI->Enable(pModel && pModel->GetParent());
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnBrowseSourceSymbol()
{
    AssignSymbolHit();

    PSS_ProcessGraphModelDoc* pDocument = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    if (pDocument && pDocument->GetModel())
    {
        PSS_Symbol* pSymbolHit = dynamic_cast<PSS_Symbol*>(m_pSymbolHit);

        if (pSymbolHit && !pSymbolHit->IsLocal())
            BrowseLocalSymbol(pSymbolHit);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateBrowseSourceSymbol(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    AssignSymbolHit();

    PSS_Symbol* pSymbolHit = dynamic_cast<PSS_Symbol*>(m_pSymbolHit);

    pCmdUI->Enable(pSymbolHit && !pSymbolHit->IsLocal());
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnFindSymbol()
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    CWaitCursor waitCursor;

    PSS_Properties::IPropertySet propSet;
    PSS_DynamicAttributesManipulator::ExtractUniqueAttributes(pModel, propSet);

    PSS_PropertyAttributes propAttributes;
    PSS_FindSymbolExtDlg findSymbolDlg(&propAttributes, &propSet);

    if (findSymbolDlg.DoModal() == IDOK)
    {
        if (findSymbolDlg.GetInAllModels())
            pModel = pModel->GetRoot();

        // it's necessary to call Restore() here in order to change the cursor back to the wait cursor
        waitCursor.Restore();

        PSS_Log* pLog = NULL;

        PSS_ProcessGraphModelDoc* pModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pModel->GetDocument());

        if (pModelDoc)
        {
            pLog = pModelDoc->GetSearchOutputLog();

            // notify about the search log tab activation
            PSS_ToolbarObserverMsg msg(UM_ACTIVATE_LOGSEARCH_TAB);
            pModelDoc->NotifyAllObservers(&msg);
        }

        // start the search
        pModel->Find(findSymbolDlg.GetSearchArgument(),
                     pLog,
                     &propAttributes,
                     findSymbolDlg.GetInAllModels(),
                     findSymbolDlg.GetCaseSensitive(),
                     findSymbolDlg.GetPartialSearch());
    }

    PSS_Properties::IPropertyIterator it(&propSet);

    // remove all properties
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnInsertPage()
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    PSS_ProcessGraphModelMdl* pRoot = pModel->GetRoot();

    if (!pRoot)
        return;

    PSS_InsertModelNewPageDlg dlg(pRoot, pRoot->GetValidNextPageName(), pRoot->GetExistingPageNameArray());

    if (dlg.DoModal() == IDOK)
    {
        PSS_ProcessGraphModelMdl* pEmptyModel = pRoot->CreateEmptyModel(dlg.GetPageName(), dlg.GetParentModel());
        PSS_ProcessGraphPage*     pPage       = pRoot->CreateNewPage(pEmptyModel, dlg.GetPageName(), dlg.GetParentModel());

        BrowseModel(pEmptyModel, dlg.GetParentModel());

        CWnd* pMainWnd = ::AfxGetMainWnd();

        // build the message
        if (pMainWnd)
        {
            PSS_DocObserverMsg docMsg;
            pMainWnd->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, LPARAM(&docMsg));
        }

        CDocument* pDocument = GetDocument();
        PSS_Assert(pDocument);

        // set the modification flag
        pDocument->SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnRenamePage()
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    PSS_ProcessGraphModelMdl* pRoot = pModel->GetRoot();

    if (!pRoot)
        return;

    PSS_RenameModelPageDlg dlg(pRoot, pRoot->GetExistingPageNameArray());

    if (dlg.DoModal() == IDOK)
    {
        PSS_ProcessGraphPage* pPage = dlg.GetSelectedPage();

        if (pPage)
        {
            // keep the old page name
            const CString oldPageName = pPage->GetPageName();

            // Rename the page
            pPage->SetPageName(dlg.GetPageName());

            // notify the owner model about the page changes
            pRoot->OnPageNameChanged(pPage, oldPageName);
        }

        CWnd* pMainWnd = ::AfxGetMainWnd();

        // build the message
        if (pMainWnd)
        {
            PSS_DocObserverMsg docMsg;
            pMainWnd->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, LPARAM(&docMsg));
        }

        // set the modification flag
        GetDocument()->SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnDeletePage()
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    PSS_ProcessGraphModelMdl* pRoot = pModel->GetRoot();

    if (!pRoot)
        return;

    PSS_DeleteModelPageDlg dlg(GetModel()->GetRoot());

    if (dlg.DoModal() == IDOK)
    {
        PSS_ProcessGraphPage* pPage = dlg.GetSelectedPage();

        if (pPage)
        {
            // todo -cCheck -oJean: Not sure if the BrowseModel() function may change the current model and current
            //                      root model, but if it's the case the code below may not work as expected. This
            //                      should be well tested and validated
            // move to the root model
            BrowseModel(pRoot, pRoot->GetParent());

            // delete the page and its associated model
            pRoot->DeletePage(pPage->GetPageName(), true);

            CWnd* pMainWnd = ::AfxGetMainWnd();

            // build the message
            if (pMainWnd)
            {
                PSS_DocObserverMsg docMsg;
                pMainWnd->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, LPARAM(&docMsg));
            }

            CDocument* pDocument = GetDocument();

            // set the modification flag
            if (pDocument)
                pDocument->SetModifiedFlag(TRUE);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnRenameCurrentPage()
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    PSS_ProcessGraphModelMdl* pRoot = pModel->GetRoot();

    if (!pRoot)
        return;

    // get the current page
    PSS_ProcessGraphPage* pCurrentPage = pRoot->FindModelPage(pModel, true);

    // keep the old page name
    const CString oldPageName = pCurrentPage->GetPageName();

    PSS_RenameModelPageDlg dlg(pRoot, pRoot->GetExistingPageNameArray(), pCurrentPage);

    if (dlg.DoModal() == IDOK)
    {
        PSS_ProcessGraphPage* pPage = dlg.GetSelectedPage();

        if (pPage)
        {
            pPage->SetPageName(dlg.GetPageName());

            // notify the owner model about the page changes
            pRoot->OnPageNameChanged(pPage, oldPageName);
        }

        CWnd* pMainWnd = ::AfxGetMainWnd();

        // build the message
        if (pMainWnd)
        {
            PSS_DocObserverMsg docMsg;
            pMainWnd->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, LPARAM(&docMsg));
        }

        CDocument* pDocument = GetDocument();

        // set the modification flag
        if (pDocument)
            pDocument->SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnDeleteCurrentPage()
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
        return;

    PSS_ProcessGraphModelMdl* pRoot = pModel->GetRoot();

    if (!pRoot)
        return;

    // get the root page
    PSS_ProcessGraphPage* pRootPage = pRoot->FindModelPage(pRoot, true);

    // get the current page
    PSS_ProcessGraphPage* pCurrentPage = pRoot->FindModelPage(pModel, true);

    if (pModel->HasPageSet())
    {
        PSS_ProcessGraphModelMdl::IProcessGraphPageSet* pPageSet = pModel->GetPageSet();

        if (pPageSet && pPageSet->GetAt(0) == pCurrentPage)
        {
            // show warning message
            PSS_MsgBox mBox;
            mBox.Show(IDS_CANNOTDELETE_ROOTPAGE, MB_OK);
            return;
        }
    }

    // todo -cCheck -oJean: Not sure if the BrowseModel() function may change the current model and current
    //                      root model, but if it's the case the code below may not work as expected. This
    //                      should be well tested and validated
    // move to the root model
    BrowseModel(pRoot, pRoot->GetParent());

    if (pCurrentPage)
    {
        pRoot->NotifyDeletePage(pCurrentPage);

        // delete the page and its associated model
        pRoot->DeletePage(pCurrentPage->GetPageName(), true);

        CWnd* pMainWnd = ::AfxGetMainWnd();

        // build the message
        if (pMainWnd)
        {
            PSS_DocObserverMsg docMsg;
            pMainWnd->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, LPARAM(&docMsg));
        }

        CDocument* pDocument = GetDocument();

        // set the modification flag
        if (pDocument)
            pDocument->SetModifiedFlag(TRUE);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnGoInSymbol()
{
    AssignSymbolHit();

    PSS_Symbol* pSymbolHit = dynamic_cast<PSS_Symbol*>(m_pSymbolHit);

    if (pSymbolHit && (pSymbolHit->GetChildModel() || pSymbolHit->CanContainChildModel()))
        OpenSymbol(m_pSymbolHit);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnSelectSymbol()
{
    AssignSymbolHit();

    if (m_pSymbolHit)
    {
        EnsureSymbolVisible(m_pSymbolHit);
        SelectComponent(*m_pSymbolHit);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnOdMeasurements()
{
    // call the base class
    CODController::OnMeasurements();

    CDocument*   pDocument       = GetDocument();
    CODViewport* pCanvasViewport = GetCanvasVp();

    if (!pDocument || !pCanvasViewport)
        return;

    CODRuler* pRuler = pCanvasViewport->GetRuler();

    if (!pRuler)
        return;
        
    // set the modification flag
    pDocument->SetModifiedFlag(TRUE);

    PSS_ProcessGraphModelDoc* pGraphModelDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(pDocument);

    if (pGraphModelDoc)
        pGraphModelDoc->SetPageUnits(*pRuler);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnViewZoomIn()
{
    ViewZoomIn();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnViewZoomOut()
{
    ViewZoomOut();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnAddNewExtApp()
{
    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);

    if (pSymbolHit)
        pSymbolHit->DoInsertExtApp();
    else
    if (pLinkSymbolHit)
        pLinkSymbolHit->DoInsertExtApp();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateAddNewExtApp(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);
    bool            enable         = false;

    if (pSymbolHit)
        enable = pSymbolHit->AcceptExtApp();
    else
    if (pLinkSymbolHit)
        enable = pLinkSymbolHit->AcceptExtApp();

    pCmdUI->Enable(enable);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnAddNewExtFile()
{
    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);

    if (pSymbolHit)
        pSymbolHit->DoInsertExtFile();
    else
    if (pLinkSymbolHit)
        pLinkSymbolHit->DoInsertExtFile();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateAddNewExtFile(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);
    bool            enable         = false;

    if (pSymbolHit)
        enable = pSymbolHit->AcceptExtFile();
    else
    if (pLinkSymbolHit)
        enable = pLinkSymbolHit->AcceptExtFile();

    pCmdUI->Enable(enable);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnSetBackgroundImage()
{
    CString fileName;

    if (!GetImageFileName(fileName))
        return;

    SetImage(fileName, FALSE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateSetBackgroundImage(CCmdUI* pCmdUI)
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnClearBackgroundImage()
{
    ClearImage();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnShowModelBorder()
{
    PSS_ProcessGraphModelMdl* pModel = GetRootModel();
    PSS_Assert(pModel);

    pModel->SetShowPageBorder(!pModel->GetShowPageBorder());

    PSS_ProcessGraphModelViewport* pViewport = GetViewport();

    if (pViewport)
    {
        PSS_ProcessGraphModelView* pView = GetView();

        if (pView)
            pViewport->UpdatePageLook(pView->GetPrinterPageSize());
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateShowModelBorder(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    PSS_ProcessGraphModelMdl* pModel = GetRootModel();

    if (pModel)
        pCmdUI->SetCheck(pModel->GetShowPageBorder());
    else
        pCmdUI->SetCheck(FALSE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnAddWatermarkModelLogo()
{
    CString fileName;

    if (!GetImageFileName(fileName))
        return;

    SetImage(fileName, TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateAddWatermarkModelLogo(CCmdUI* pCmdUI)
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnClearWatermarkModelLogo()
{
    ClearImage();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnSymbolShowNameArea()
{
    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);

    // change the flag
    if (pSymbolHit)
    {
        pSymbolHit->ShowNameArea(!pSymbolHit->IsNameAreaVisible());

        // adjust the area element position
        pSymbolHit->AdjustAreaPosition();
    }
    else
    if (pLinkSymbolHit)
    {
        pLinkSymbolHit->ShowNameArea(!pLinkSymbolHit->IsNameAreaVisible());

        // adjust the area element position
        pLinkSymbolHit->AdjustAreaPosition();
    }

    CDocument* pDocument = GetDocument();

    // set the modification flag
    if (pDocument)
        pDocument->SetModifiedFlag(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateSymbolShowNameArea(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);
    BOOL            enable         = FALSE;

    // get the enable flag
    if (pSymbolHit)
        enable = pSymbolHit->IncludeNameArea() && pSymbolHit->UseDynamicArea();
    else
    if (pLinkSymbolHit)
        enable = pLinkSymbolHit->IncludeNameArea() && pLinkSymbolHit->UseDynamicArea();

    pCmdUI->Enable(enable);

    // if enabled, get the checked flag
    if (enable)
    {
        BOOL checked = FALSE;

        if (pSymbolHit)
            checked = pSymbolHit->IsNameAreaVisible();
        else
        if (pLinkSymbolHit)
            checked = pLinkSymbolHit->IsNameAreaVisible();

        pCmdUI->SetCheck(checked);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnSymbolShowDescriptionArea()
{
    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);

    // Change the flag
    if (pSymbolHit)
    {
        pSymbolHit->ShowDescriptionArea(!pSymbolHit->IsDescriptionsAreaVisible());

        // adjust the area element position
        pSymbolHit->AdjustAreaPosition();
    }
    else
    if (pLinkSymbolHit)
    {
        pLinkSymbolHit->ShowDescriptionArea(!pLinkSymbolHit->IsDescriptionsAreaVisible());

        // adjust the area element position
        pLinkSymbolHit->AdjustAreaPosition();
    }

    CDocument* pDocument = GetDocument();

    // set the modification flag
    if (pDocument)
        pDocument->SetModifiedFlag(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateSymbolShowDescriptionArea(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);
    BOOL            enable         = FALSE;

    // get the enable flag
    if (pSymbolHit)
        enable = (pSymbolHit->IncludeDescriptionArea() && pSymbolHit->UseDynamicArea());
    else
    if (pLinkSymbolHit)
        enable = (pLinkSymbolHit->IncludeDescriptionArea() && pLinkSymbolHit->UseDynamicArea());

    pCmdUI->Enable(enable);

    // if enabled, get the checked flag
    if (enable)
    {
        BOOL checked = FALSE;

        if (pSymbolHit)
            checked = pSymbolHit->IsDescriptionsAreaVisible();
        else
        if (pLinkSymbolHit)
            checked = pLinkSymbolHit->IsDescriptionsAreaVisible();

        pCmdUI->SetCheck(checked);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnSymbolShowAttributeArea()
{
    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);

    // change the flag
    if (pSymbolHit)
    {
        pSymbolHit->ShowAttributeArea(!pSymbolHit->IsAttributeAreaVisible());

        // if visible, refresh the attribute area
        if (pSymbolHit->IsAttributeAreaVisible())
            pSymbolHit->RefreshAttributeTextArea();

        // adjust the area element position
        pSymbolHit->AdjustAreaPosition();
    }
    else
    if (pLinkSymbolHit)
    {
        pLinkSymbolHit->ShowAttributeArea(!pLinkSymbolHit->IsAttributeAreaVisible());

        // if visible, refresh the attribute area
        if (pLinkSymbolHit->IsAttributeAreaVisible())
            pLinkSymbolHit->RefreshAttributeTextArea();

        // adjust the area element position
        pLinkSymbolHit->AdjustAreaPosition();
    }

    CDocument* pDocument = GetDocument();

    // set the modification flag
    if (pDocument)
        pDocument->SetModifiedFlag(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateSymbolShowAttributeArea(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);
    BOOL            enable         = FALSE;

    // get the enable flag
    if (pSymbolHit)
        enable = (pSymbolHit->IncludeAttributeArea() && pSymbolHit->UseDynamicArea());
    else
    if (pLinkSymbolHit)
        enable = (pLinkSymbolHit->IncludeAttributeArea() && pLinkSymbolHit->UseDynamicArea());

    pCmdUI->Enable(enable);

    // if enabled, get the checked flag
    if (enable)
    {
        BOOL checked = FALSE;

        if (pSymbolHit)
            checked = pSymbolHit->IsAttributeAreaVisible();
        else
        if (pLinkSymbolHit)
            checked = pLinkSymbolHit->IsAttributeAreaVisible();

        pCmdUI->SetCheck(checked);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnSymbolShowLabelAttributes()
{
    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);

    // change the flag
    if (pSymbolHit)
        pSymbolHit->SetShowTitleText(!pSymbolHit->GetShowTitleText());
    else
    if (pLinkSymbolHit)
        pLinkSymbolHit->SetShowTitleText(!pLinkSymbolHit->GetShowTitleText());

    CDocument* pDocument = GetDocument();

    // set the modification flag
    if (pDocument)
        pDocument->SetModifiedFlag(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateSymbolShowLabelAttributes(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);
    BOOL            enable         = FALSE;

    // get the enable flag
    if (pSymbolHit)
        enable = (pSymbolHit->IncludeAttributeArea()   &&
                  pSymbolHit->IsAttributeAreaVisible() &&
                  pSymbolHit->UseDynamicArea());
    else
    if (pLinkSymbolHit)
        enable = (pLinkSymbolHit->IncludeAttributeArea()   &&
                  pLinkSymbolHit->IsAttributeAreaVisible() &&
                  pLinkSymbolHit->UseDynamicArea());

    pCmdUI->Enable(enable);

    // if enabled, get the checked flag
    if (enable)
    {
        BOOL checked = FALSE;

        if (pSymbolHit)
            checked = pSymbolHit->GetShowTitleText();
        else
        if (pLinkSymbolHit)
            checked = pLinkSymbolHit->GetShowTitleText();

        pCmdUI->SetCheck(checked);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnSymbolSelectAttributes()
{
    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);

    if (!pSymbolHit && !pLinkSymbolHit)
        return;

    PSS_Properties::IPropertySet propSet;
    PSS_PropertyAttributes       propAttributes;

    // check what kind of symbol was clicked
    if (pSymbolHit)
    {
        // get the object property set
        pSymbolHit->FillProperties(propSet);

        // copy the symbol attributes
        propAttributes = pSymbolHit->GetAttributes();
    }
    else
    {
        // get the object property set
        pLinkSymbolHit->FillProperties(propSet);

        // copy the symbol attributes
        propAttributes = pLinkSymbolHit->GetAttributes();
    }

    // call the base dialog for attribute selection
    PSS_SelectSymbolAttributeDlg dlg(&propAttributes, &propSet);
    const UINT                   result = dlg.DoModal();

    // show the wait cursor for this operation
    CWaitCursor waitCursor;

    PSS_Properties::IPropertyIterator it(&propSet);

    // remove all properties
    for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
        delete pProp;

    propSet.RemoveAll();

    // check the return value
    switch (result)
    {
        case IDOK:
            if (pSymbolHit)
                pSymbolHit->OnChangeAttributes(&propAttributes);
            else
                pLinkSymbolHit->OnChangeAttributes(&propAttributes);

            break;

        case ID_APPLYTOALL:
        {
            PSS_ProcessGraphModelMdl* pRoot = GetRootModel();

            // iterate through all elements and sets the new attributes
            if (pRoot)
                if (pSymbolHit)
                    pRoot->PropagateNewSymbolAttributes(&propAttributes, pSymbolHit->GetObjectTypeID());
                else
                    pRoot->PropagateNewSymbolAttributes(&propAttributes, pLinkSymbolHit->GetObjectTypeID());

            break;
        }

        default:
            return;
    }

    // to set this attribute set as the default one, copy its content to the default properties
    if (dlg.MustSetAsDefaultToAll())
        if (pSymbolHit)
            PSS_ModelGlobal::GetGlobalPropertyAttributes(pSymbolHit->GetObjectTypeID()) = propAttributes;
        else
            PSS_ModelGlobal::GetGlobalPropertyAttributes(pLinkSymbolHit->GetObjectTypeID()) = propAttributes;

    CDocument* pDocument = GetDocument();

    // set the modification flag
    if (pDocument)
        pDocument->SetModifiedFlag(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateSymbolSelectAttributes(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);
    BOOL            enable         = FALSE;

    // get the enable flag
    if (pSymbolHit)
        enable = (pSymbolHit->IncludeAttributeArea()   &&
                  pSymbolHit->IsAttributeAreaVisible() &&
                  pSymbolHit->UseDynamicArea());
    else
    if (pLinkSymbolHit)
        enable = (pLinkSymbolHit->IncludeAttributeArea()   &&
                  pLinkSymbolHit->IsAttributeAreaVisible() &&
                  pLinkSymbolHit->UseDynamicArea());

    pCmdUI->Enable(enable);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnDynamicAttributesAdd()
{
    PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());
    PSS_Assert(pDoc);

    if (!pDoc->HasDynamicPropertiesManager())
        pDoc->AllocatePropertiesManager();

    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);

    PSS_DynamicAttributesCreation dlg(pDoc, (pSymbolHit || pLinkSymbolHit));

    if (dlg.DoModal() == IDCANCEL)
        return;

    // if a symbol is selected, assign the runtime class and the symbol name and reference
    CRuntimeClass* pRTClass  = NULL;
    CString        symbolName;
    int            symbolRef = -1;

    PSS_BasicSymbol* pBasicSymbol = dynamic_cast<PSS_BasicSymbol*>(m_pSymbolHit);

    if (pBasicSymbol)
    {
        pRTClass   = m_pSymbolHit->GetRuntimeClass();
        symbolName = pBasicSymbol->GetSymbolName();
        symbolRef  = pBasicSymbol->GetSymbolReferenceNumber();
    }

    PSS_DynamicPropertiesManager* pDynPropMgr = pDoc->GetDynamicPropertiesManager();
    PSS_Assert(pDynPropMgr);

    PSS_Property*    pProperty = NULL;
    PSS_StringFormat ft;

    switch (dlg.GetVisibility())
    {
        // local
        case 0:
            if (pBasicSymbol)
            {
                pProperty = pDynPropMgr->RegisterProperty(dlg.GetCategoryName(),
                                                          dlg.GetAttributeName(),
                                                          dlg.GetAttributeDescription(),
                                                          dlg.GetPropertyType(),
                                                          ft,
                                                          symbolName,
                                                          symbolRef);

                // add the property directly to the symbol
                pBasicSymbol->GetDynamicPropertiesManager()->AddDynamicProperty(pProperty->Dup());
            }

            break;

        // same class type
        case 1:
            pProperty = pDynPropMgr->RegisterProperty(dlg.GetCategoryName(),
                                                      dlg.GetAttributeName(),
                                                      dlg.GetAttributeDescription(),
                                                      dlg.GetPropertyType(),
                                                      ft,
                                                      pRTClass);

            // add the property to all symbols with the same class type
            PSS_DynamicAttributesManipulator::AssignProperty(GetRootModel(), pProperty, pRTClass);

            break;

        // all symbols
        case 2:
            pProperty = pDynPropMgr->RegisterProperty(dlg.GetCategoryName(),
                                                      dlg.GetAttributeName(),
                                                      dlg.GetAttributeDescription(),
                                                      dlg.GetPropertyType(),
                                                      ft);

            // add the property to all symbols
            PSS_DynamicAttributesManipulator::AssignProperty(GetRootModel(), pProperty);

            break;
    }

    NotifySymbolSelected(m_pSymbolHit);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateDynamicAttributesAdd(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    // no distinction
    pCmdUI->Enable(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnDynamicAttributesDuplicate()
{
    PSS_ProcessGraphModelDoc* pDoc = dynamic_cast<PSS_ProcessGraphModelDoc*>(GetDocument());

    // if the document doesn't contain a dynamic properties manager, creates a default one
    if (!pDoc->HasDynamicPropertiesManager())
        pDoc->AllocatePropertiesManager();

    PSS_DynamicPropertiesManager* pPropMgr = pDoc->GetDynamicPropertiesManager();
    PSS_Assert(pPropMgr);

    AssignSymbolHit();

    PSS_Symbol*     pSymbolHit     =                     dynamic_cast<PSS_Symbol*>(m_pSymbolHit);
    PSS_LinkSymbol* pLinkSymbolHit = pSymbolHit ? NULL : dynamic_cast<PSS_LinkSymbol*>(m_pSymbolHit);

    // create and show the duplicate dialog box
    PSS_DynamicAttributesDuplicationDlg dlg(pDoc, (pSymbolHit || pLinkSymbolHit));

    if (dlg.DoModal() == IDCANCEL)
        return;

    PSS_StringFormat             ft;
    PSS_Properties::IPropertySet propSet;
    CStringArray                 propList;
    CString                      symbolName;
    int                          symbolRef     = -1;
    PSS_Property*                pSrcProperty  =  NULL;
    PSS_Property*                pDestProperty =  NULL;
    PSS_BasicSymbol*             pBasicSymbol  =  dynamic_cast<PSS_BasicSymbol*>(m_pSymbolHit);

    // get the owning symbol name and reference
    if (pBasicSymbol)
    {
        symbolName = pBasicSymbol->GetSymbolName();
        symbolRef  = pBasicSymbol->GetSymbolReferenceNumber();
    }

    // get the dynamic properties contained in the symbol. They will be used to get the data
    if (pSymbolHit)
        pSymbolHit->FillProperties(propSet);
    else
    if (pLinkSymbolHit)
        pLinkSymbolHit->FillProperties(propSet);

    // get the properties matching with the selected category
    pPropMgr->CreatePropertyList(dlg.GetCategory(), propList);

    const INT_PTR propCount = propList.GetSize();

    // copy the properties. Here only the property containers are copied, i.e the properties with the same
    // name and description as in the source, however the values aren't copied, instead they will be copied later
    for (INT_PTR i = 0; i < propCount; ++i)
    {
        const CString propName = propList.GetAt(i);

        pSrcProperty  = pPropMgr->GetPropertyItem(dlg.GetCategory(), propName);
        pDestProperty = pPropMgr->RegisterProperty(dlg.GetName(),
                                                   pSrcProperty->GetLabel(),
                                                   pSrcProperty->GetDescription(),
                                                   pSrcProperty->GetType(),
                                                   ft,
                                                   symbolName,
                                                   symbolRef);

        // do copy the values?
        if (dlg.DupValuesIsChecked())
        {
            PSS_Properties::IPropertyIterator it(&propSet);

            for (PSS_Property* pProp = it.GetFirst(); pProp; pProp = it.GetNext())
                if (pProp->GetCategory() == dlg.GetCategory() && pProp->GetLabel() == pSrcProperty->GetLabel())
                {
                    pDestProperty->SetStringFormat(pProp->GetStringFormat());

                    switch (pSrcProperty->GetValueType())
                    {
                        case PSS_Property::IE_VT_Date:     pDestProperty->SetValueDate(pProp->GetValueDate());         break;
                        case PSS_Property::IE_VT_Double:   pDestProperty->SetValueDouble(pProp->GetValueDouble());     break;
                        case PSS_Property::IE_VT_Duration: pDestProperty->SetValueDuration(pProp->GetValueDuration()); break;
                        case PSS_Property::IE_VT_Float:    pDestProperty->SetValueFloat(pProp->GetValueFloat());       break;
                        case PSS_Property::IE_VT_String:   pDestProperty->SetValueString(pProp->GetValueString());     break;
                        case PSS_Property::IE_VT_TimeSpan: pDestProperty->SetValueTimeSpan(pProp->GetValueTimeSpan()); break;
                        case PSS_Property::IE_VT_Unknown:                                                              break;
                    }
                }
        }

        // copy the new property in the symbol
        if (pBasicSymbol)
            pBasicSymbol->GetDynamicPropertiesManager()->AddDynamicProperty(pDestProperty->Dup());
    }

    // refresh the symbol
    NotifySymbolSelected(m_pSymbolHit);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateDynamicAttributesDuplicate(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    pCmdUI->Enable(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnDynamicAttributesDelete()
{}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnUpdateDynamicAttributesDelete(CCmdUI* pCmdUI)
{
    if (!pCmdUI)
        return;

    // no distinction
    pCmdUI->Enable(TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::OnRefresh()
{
    PSS_ProcessGraphModelViewport* pViewport = GetViewport();
    PSS_Assert(pViewport);

    pViewport->UpdateAll();

    PSS_ProcessGraphModelMdl* pModel = GetModel();
    PSS_Assert(pModel);

    // refresh all symbol attributes
    pModel->RefreshSymbolAttributes(true);

    // also refresh the model tree
    RefreshModelTree();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::AnimateNodes()
{
    CODComponentSet updateSet;
    const int       nodeCount = m_AnimatedNodes.GetSize();

    for (int nodeIndex = 0; nodeIndex < nodeCount; ++nodeIndex)
    {
        IODNode*            pINode = m_AnimatedNodes.GetAt(nodeIndex);
        CODSymbolComponent* pComp  = static_cast<CODSymbolComponent*>(pINode);
        const BOOL          flag   = !(m_AnimateCounter % 2);

        pComp->SetTracking(flag);
        updateSet.Add(pComp);
    }

    CODViewport* pViewport = GetVp();

    if (pViewport)
        pViewport->DrawComponents(&updateSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::AnimateEdges()
{
    CODComponentSet updateSet;
    const int       nodeCount = m_AnimatedEdges.GetSize();

    for (int edgeIndex = 0; edgeIndex < nodeCount; ++edgeIndex)
    {
        IODEdge*          pIEdge = m_AnimatedEdges.GetAt(edgeIndex);
        CODLinkComponent* pComp  = static_cast<CODLinkComponent*>(pIEdge);
        const BOOL        flag   = !(m_AnimateCounter % 2);

        pComp->SetTracking(flag);
        updateSet.Add(pComp);
    }

    CODViewport* pViewport = GetVp();

    if (pViewport)
        pViewport->DrawComponents(&updateSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::AnimateSymbols()
{
    CODComponentSet      updateSet;
    CODComponentIterator it(&m_AnimatedComponents);

    for (CODComponent* pSrcComp = it.GetFirst(); pSrcComp; pSrcComp = it.GetNext())
    {
        pSrcComp->SetTracking(!(m_AnimateCounter % 2));
        updateSet.Add(pSrcComp);
    }

    CODViewport* pViewport = GetVp();

    if (pViewport)
        pViewport->DrawComponents(&updateSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::ChangeColorNodes()
{
    CODComponentSet updateSet;
    const int       nodeCount = m_AnimatedNodes.GetSize();

    for (int nodeIndex = 0; nodeIndex < nodeCount; ++nodeIndex)
    {
        IODNode*            pINode = m_AnimatedNodes.GetAt(nodeIndex);
        CODSymbolComponent* pComp  = static_cast<CODSymbolComponent*>(pINode);

        if (pComp)
        {
            PSS_ODSymbolManipulator::ChangeLineColor(pComp, m_AnimatedColor);
            PSS_ODSymbolManipulator::ChangeLabelLineColor(pComp, m_AnimatedColor);
        }

        updateSet.Add(pComp);
    }

    CODViewport* pViewport = GetVp();

    if (pViewport)
        pViewport->DrawComponents(&updateSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::ChangeColorEdges()
{
    CODComponentSet updateSet;
    const int       nodeCount = m_AnimatedEdges.GetSize();

    for (int edgeIndex = 0; edgeIndex < nodeCount; ++edgeIndex)
    {
        IODEdge*          pIEdge = m_AnimatedEdges.GetAt(edgeIndex);
        CODLinkComponent* pComp  = static_cast<CODLinkComponent*>(pIEdge);

        if (pComp)
        {
            PSS_ODSymbolManipulator::ChangeLineColor(pComp, m_AnimatedColor);
            PSS_ODSymbolManipulator::ChangeLabelLineColor(pComp, m_AnimatedColor);
        }

        updateSet.Add(pComp);
    }

    CODViewport* pViewport = GetVp();

    if (pViewport)
        pViewport->DrawComponents(&updateSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::ChangeColorSymbols()
{
    CODComponentSet      updateSet;
    CODComponentIterator it(&m_AnimatedComponents);

    for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext())
    {
        if (pComp)
        {
            PSS_ODSymbolManipulator::ChangeLineColor(pComp, m_AnimatedColor);
            PSS_ODSymbolManipulator::ChangeLabelLineColor(static_cast<CODSymbolComponent*>(pComp), m_AnimatedColor);
        }

        updateSet.Add(pComp);
    }

    CODViewport* pViewport = GetVp();

    if (pViewport)
        pViewport->DrawComponents(&updateSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::ChangeBackColorNodes()
{
    CODComponentSet updateSet;
    const int       nodeCount = m_AnimatedNodes.GetSize();

    for (int nodeIndex = 0; nodeIndex < nodeCount; ++nodeIndex)
    {
        IODNode*          pINode      = m_AnimatedNodes.GetAt(nodeIndex);
        CODLinkComponent* pComp       =                  static_cast<CODLinkComponent*>(pINode);
        PSS_Symbol*       pSymbol     =                  dynamic_cast<PSS_Symbol*>(pComp);
        PSS_LinkSymbol*   pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

        if (pSymbol)
        {
            PSS_ODSymbolManipulator::ChangeLineColor     (pSymbol, pSymbol->GetCurrentLineColor());
            PSS_ODSymbolManipulator::ChangeLabelLineColor(pSymbol, pSymbol->GetCurrentLabelColor());
        }
        else
        if (pLinkSymbol)
        {
            PSS_ODSymbolManipulator::ChangeLineColor     (pLinkSymbol, pLinkSymbol->GetCurrentLineColor());
            PSS_ODSymbolManipulator::ChangeLabelLineColor(pLinkSymbol, pLinkSymbol->GetCurrentLabelColor());
        }

        updateSet.Add(pComp);
    }

    CODViewport* pViewport = GetVp();

    if (pViewport)
        pViewport->DrawComponents(&updateSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::ChangeBackColorEdges()
{
    CODComponentSet updateSet;
    const int       nodeCount = m_AnimatedEdges.GetSize();

    for (int edgeIndex = 0; edgeIndex < nodeCount; ++edgeIndex)
    {
        IODEdge*          pIEdge      = m_AnimatedEdges.GetAt(edgeIndex);
        CODLinkComponent* pComp       =                  static_cast<CODLinkComponent*>(pIEdge);
        PSS_Symbol*       pSymbol     =                  dynamic_cast<PSS_Symbol*>(pComp);
        PSS_LinkSymbol*   pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

        if (pSymbol)
        {
            PSS_ODSymbolManipulator::ChangeLineColor     (pSymbol, pSymbol->GetCurrentLineColor());
            PSS_ODSymbolManipulator::ChangeLabelLineColor(pSymbol, pSymbol->GetCurrentLabelColor());
        }
        else
        if (pLinkSymbol)
        {
            PSS_ODSymbolManipulator::ChangeLineColor     (pLinkSymbol, pLinkSymbol->GetCurrentLineColor());
            PSS_ODSymbolManipulator::ChangeLabelLineColor(pLinkSymbol, pLinkSymbol->GetCurrentLabelColor());
        }

        updateSet.Add(pComp);
    }

    CODViewport* pViewport = GetVp();

    if (pViewport)
        pViewport->DrawComponents(&updateSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::ChangeBackColorSymbols()
{
    CODComponentSet      updateSet;
    CODComponentIterator it(&m_AnimatedComponents);

    for (CODComponent* pComp = it.GetFirst(); pComp; pComp = it.GetNext())
    {
        PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pComp);
        PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

        if (pSymbol)
        {
            PSS_ODSymbolManipulator::ChangeLineColor     (pSymbol, pSymbol->GetCurrentLineColor());
            PSS_ODSymbolManipulator::ChangeLabelLineColor(pSymbol, pSymbol->GetCurrentLabelColor());
        }
        else
        if (pLinkSymbol)
        {
            PSS_ODSymbolManipulator::ChangeLineColor     (pLinkSymbol, pLinkSymbol->GetCurrentLineColor());
            PSS_ODSymbolManipulator::ChangeLabelLineColor(pLinkSymbol, pLinkSymbol->GetCurrentLabelColor());
        }

        updateSet.Add(pComp);
    }

    CODViewport* pViewport = GetVp();

    if (pViewport)
        pViewport->DrawComponents(&updateSet);
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::EndAnimateTimer()
{
    KillTimer(m_Timer);
    m_Timer = 0;

    if (m_AnimatedUseColor)
    {
        if (m_AnimatedNodes.GetSize() > 0)
            ChangeBackColorNodes();

        if (m_AnimatedEdges.GetSize() > 0)
            ChangeBackColorEdges();

        if (m_AnimatedComponents.GetSize() > 0)
            ChangeBackColorSymbols();
    }

    m_AnimatedNodes.RemoveAll();
    m_AnimatedEdges.RemoveAll();
    m_AnimatedComponents.RemoveAll();

    m_AnimateCounter   = 0;
    m_TimerInitialized = false;
}
//---------------------------------------------------------------------------
