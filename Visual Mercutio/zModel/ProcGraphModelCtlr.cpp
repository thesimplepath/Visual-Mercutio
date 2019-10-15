/************************************************************************************************************
 *                                          Classe ZDProcessGraphModelController                                *
 ************************************************************************************************************
 * Cette classe s'occupe de la gestion des modèles. Son rôle est d'effectuer les opérations globales sur    *
 * les modèles, tels que la gestion des couper-copier-coller, la gestion des trames de fond, l'introduction    *
 * de nouvelles pages, ou la gestion des zooms.                                                                *
 ************************************************************************************************************/

#include "stdafx.h"
#include "ProcGraphModelCtlr.h"

 // JMR-MODIF - Le 1er septembre 2005 - Pourquoi qu'en debug ?
 //#ifdef _DEBUG
#include "zFormsRes\zFormsRes.h"
//#endif

#include "zRes32\zRes.h"

#include "zBaseLib\PSS_MsgBox.h"
#include "zBaseLib\PSS_DocumentObserverMsg.h"
#include "zBaseLib\PSS_ToolbarObserverMsg.h"

// FileDlg
#include "zBaseLib\PSS_FileDialog.h"

#include "zProperty\ZBPropertyObserverMsg.h"
#include "zProperty\ZBDynamicProperties.h"
#include "zProperty\ZBDynamicPropertiesManager.h"

#include "ProcGraphModelVp.h"
#include "ProcGraphModelDoc.h"
#include "ProcGraphModelView.h"

#include "ZUODSymbolManipulator.h"

#include "ZBDocObserverMsg.h"
#include "ZBUnitObserverMsg.h"
#include "ZBModelObserverMsg.h"
#include "ZBSymbolObserverMsg.h"
#include "ZBSymbolLogObserverMsg.h"

#include "ZBLinkSymbol.h"

// JMR-MODIF - LE 5 avril 2006 - Ajout de la classe ZBTextZone
#include "ZBTextZone.h"

#include "ZDProcessGraphPage.h"

#include "ZVInsertModelNewPageDlg.h"
#include "ZVRenameModelPageDlg.h"
#include "ZVDeleteModelPageDlg.h"
#include "ZVSelectSymbolAttributeDlg.h"

// Find a symbol dialog
#include "ZVFindSymbolExtDlg.h"

// Utility class to found the next available symbol name
#include "ZUBuildSymbolNewName.h"

// JMR-MODIF - Le 4 avril 2006 - Ajout de l'en-tête ZUBuildGenericSymbolNewName.h
#include "ZUBuildGenericSymbolNewName.h"

#include "ZVDynamicAttributesCreation.h"
#include "ZUDynamicAttributesManipulator.h"

// Global for model
#include "ZAModelGlobal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// JMR-MODIF - Le 21 octobre 2007 - Ajout des décorations unicode _T( ), nettoyage du code nutile. (En commentaires)

#define ANIMATE_TIMER 1123

// **********************************************************************************************************
// *                                             Static class variables                                        *
// **********************************************************************************************************
static bool                CutCommand = false;
static CODComponentSet    m_setCut;

CODSymbolComponent*        ZDProcessGraphModelController::m_LastSelectedElement = NULL;
CODSymbolComponent*        ZDProcessGraphModelController::m_pFormatPainterSymbol = NULL;

CODComponentSet            ZDProcessGraphModelController::m_setCopy;
CODComponentSet            ZDProcessGraphModelController::m_setSymbolAddedSet;
CODComponentSet            ZDProcessGraphModelController::m_animateComponents;

CODNodeArray            ZDProcessGraphModelController::m_animateNodes;
CODEdgeArray            ZDProcessGraphModelController::m_animateEdges;

int                        ZDProcessGraphModelController::m_nAnimateCounter = 4;
int                        ZDProcessGraphModelController::m_nAnimateSeconds = 4;

bool                    ZDProcessGraphModelController::m_SelectionChanged = false;
bool                    ZDProcessGraphModelController::m_AnimatedUseColor = false;
bool                    ZDProcessGraphModelController::m_TimerInitialized = false;
bool                    ZDProcessGraphModelController::m_IsInFormatPainter = false;

UINT                    ZDProcessGraphModelController::m_nTimer = 0;
UINT                    ZDProcessGraphModelController::m_CurrentCommandID = 0;

CPoint                    ZDProcessGraphModelController::m_savedEditPosition;

COLORREF                ZDProcessGraphModelController::m_AnimatedColor = -1;

PSS_Date                    ZDProcessGraphModelController::m_StartTimeOfTimer;

// **********************************************************************************************************
// *                                     Message map for call back functions                                *
// **********************************************************************************************************

BEGIN_MESSAGE_MAP(ZDProcessGraphModelController, CODController)
    //{{AFX_MSG_MAP(ZDProcessGraphModelController)
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
    ON_COMMAND(ID_GOIN_SYMBOL, OnGoinSymbol)
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

// **********************************************************************************************************
// *                                        ZDProcessGraphModelController                                    *
// **********************************************************************************************************

ZDProcessGraphModelController::ZDProcessGraphModelController(ZIProcessGraphModelViewport* pViewport)
    : CODController(pViewport),
    m_pRightSubMenu(NULL),
    m_pSymbolHit(NULL),
    m_pLabelHit(NULL),
    m_CurrentCursor(0),        // JMR-MODIF - Le 5 mai 2006 - Initialisation de la variable m_OldCursor.
    m_IsEditingSymbolName(false),
    m_IsEditingSymbolComment(false),
    m_NewSymbolCreated(false)
{
    GetCanvasVp()->Invalidate();
}

ZDProcessGraphModelController::~ZDProcessGraphModelController()
{
    // When the controller is closed, reset the last selected element.
    // Otherwise, we have the risk to keep a pointer on an unexisting symbol
    m_LastSelectedElement = NULL;
}

ZIProcessGraphModelViewport* ZDProcessGraphModelController::GetViewport()
{
    return dynamic_cast<ZIProcessGraphModelViewport*>(m_pViewport);
}

ZIProcessGraphModelViewport* ZDProcessGraphModelController::GetViewportConstPtr() const
{
    return dynamic_cast<ZIProcessGraphModelViewport*>(m_pViewport);
}

ZIProcessGraphModelView* ZDProcessGraphModelController::GetView()
{
    if (m_pViewport)
    {
        CWnd* pWnd = m_pViewport->GetWnd();

        if (pWnd && ISA(pWnd, ZIProcessGraphModelView))
        {
            return (ZIProcessGraphModelView*)pWnd;
        }
    }

    return NULL;
}

ZIProcessGraphModelView* ZDProcessGraphModelController::GetViewConstPtr() const
{
    if (m_pViewport)
    {
        CWnd* pWnd = m_pViewport->GetWnd();

        if (pWnd && ISA(pWnd, ZIProcessGraphModelView))
        {
            return (ZIProcessGraphModelView*)pWnd;
        }
    }

    return NULL;
}

CDocument* ZDProcessGraphModelController::GetDocument()
{
    if (GetView())
    {
        return GetView()->GetDocument();
    }

    return NULL;
}

CDocument* ZDProcessGraphModelController::GetDocumentConstPtr() const
{
    if (GetViewConstPtr())
    {
        return GetViewConstPtr()->GetDocument();
    }

    return NULL;
}

ZDProcessGraphModelMdl* ZDProcessGraphModelController::GetModel()
{
    if (m_pViewport && m_pViewport->GetModel() && ISA(m_pViewport->GetModel(), ZDProcessGraphModelMdl))
    {
        return (ZDProcessGraphModelMdl*)m_pViewport->GetModel();
    }

    return NULL;
}

ZDProcessGraphModelMdl* ZDProcessGraphModelController::GetRootModel()
{
    if (m_pViewport && m_pViewport->GetModel() && ISA(m_pViewport->GetModel(), ZDProcessGraphModelMdl))
    {
        return dynamic_cast<ZDProcessGraphModelMdl*>(m_pViewport->GetModel())->GetRoot();
    }

    return NULL;
}

void ZDProcessGraphModelController::OnInitialUpdate()
{
    // JMR-MODIF - Le 27 septembre 2006 - Vide le presse-papier pour commencer avec un presse-papier propre.
    ReleaseClipboard();
}

bool ZDProcessGraphModelController::BrowseInSameWindow() const
{
    if (GetDocumentConstPtr() && ISA(GetDocumentConstPtr(), ZDProcessGraphModelDoc))
    {
        return dynamic_cast<ZDProcessGraphModelDoc*>(GetDocumentConstPtr())->BrowseInSameWindow();
    }

    return false;
}

void ZDProcessGraphModelController::SetBrowseInSameWindow(bool value)
{
    if (GetDocument() && ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        dynamic_cast<ZDProcessGraphModelDoc*>(GetDocument())->SetBrowseInSameWindow(value);
    }
}

void ZDProcessGraphModelController::AssignSymbolHit()
{
    if (GetSelection()->GetSize() == 1 &&
        (ISA(GetSelection()->GetAt(0), ZBSymbol) || ISA(GetSelection()->GetAt(0), ZBLinkSymbol)))
    {
        m_pSymbolHit = (CODSymbolComponent*)GetSelection()->GetAt(0);
    }
    else
    {
        if (GetSelection()->GetSize() == 1 && ISA(GetSelection()->GetAt(0), CODLabelComponent))
        {
            // Select the symbol behind
            // JMR-MODIF - Le 31 mai 2005 - Conversion explicite remplace le cast. La conversion explicite
            // donne un résultat identique sur l'objet casté en classe de base, tandis que l'ancienne
            // implémentation (dynamic_cast) provoque une exception dans le compilateur VC.NET
            CODLabelComponent* m_pTmpSymbolHit = (CODLabelComponent*)GetSelection()->GetAt(0);
            m_pSymbolHit = m_pTmpSymbolHit->GetOwner();
            //            m_pSymbolHit = dynamic_cast<CODLabelComponent*>(GetSelection()->GetAt(0))->GetOwner();
        }
        else
        {
            m_pSymbolHit = NULL;
        }
    }
}

void ZDProcessGraphModelController::AssignLabelHit()
{
    if (GetSelection()->GetSize() == 1 && ISA(GetSelection()->GetAt(0), CODLabelComponent))
    {
        m_pLabelHit = (CODLabelComponent*)GetSelection()->GetAt(0);

        // Select the symbol behind
        m_pSymbolHit = m_pLabelHit->GetOwner();
    }
    else
    {
        m_pLabelHit = NULL;
    }
}

void ZDProcessGraphModelController::AnimateNode(IODNode&    Node,
                                                bool        UseColor        /*= false*/,
                                                COLORREF    col                /*= -1*/,
                                                size_t        AnimateCounter    /*= 4*/)
{
    if (UseColor)
    {
        m_nAnimateSeconds = AnimateCounter;
    }
    else
    {
        m_nAnimateCounter = AnimateCounter;
    }

    m_AnimatedUseColor = UseColor;
    m_AnimatedColor = col;

    // Kill the timer if necessary
    if (m_nTimer != 0)
    {
        _EndAnimateTimer();
    }

    m_StartTimeOfTimer = PSS_Date::GetCurrentTime();

    // Add the component
    m_animateNodes.Add(&Node);

    // Start the timer
    m_nTimer = SetTimer(ANIMATE_TIMER, 50, NULL);
}

void ZDProcessGraphModelController::AnimateNodes(CODNodeArray&    Nodes,
                                                 bool            UseColor        /*= false*/,
                                                 COLORREF        col                /*= -1*/,
                                                 size_t        AnimateCounter    /*= 4*/)
{
    if (UseColor)
    {
        m_nAnimateSeconds = AnimateCounter;
    }
    else
    {
        m_nAnimateCounter = AnimateCounter;
    }

    m_AnimatedUseColor = UseColor;
    m_AnimatedColor = col;

    // Kill the timer if necessary
    if (m_nTimer != 0)
    {
        _EndAnimateTimer();
    }

    m_StartTimeOfTimer = PSS_Date::GetCurrentTime();

    // Add the components
    for (int nNodeIdx = 0; nNodeIdx < Nodes.GetSize(); ++nNodeIdx)
    {
        m_animateNodes.Add(Nodes.GetAt(nNodeIdx));
    }

    // Start the timer
    m_nTimer = SetTimer(ANIMATE_TIMER, 50, NULL);
}

void ZDProcessGraphModelController::AnimateEdge(IODEdge&    Edge,
                                                bool        UseColor        /*= false*/,
                                                COLORREF    col                /*= -1*/,
                                                size_t        AnimateCounter    /*= 4*/)
{
    if (UseColor)
    {
        m_nAnimateSeconds = AnimateCounter;
    }
    else
    {
        m_nAnimateCounter = AnimateCounter;
    }

    m_AnimatedUseColor = UseColor;
    m_AnimatedColor = col;

    // Kill the timer if necessary
    if (m_nTimer != 0)
    {
        _EndAnimateTimer();
    }

    m_StartTimeOfTimer = PSS_Date::GetCurrentTime();

    // Add the component
    m_animateEdges.Add(&Edge);

    // Start the timer
    m_nTimer = SetTimer(ANIMATE_TIMER, 50, NULL);
}

void ZDProcessGraphModelController::AnimateEdges(CODEdgeArray&    Edges,
                                                 bool            UseColor        /*= false*/,
                                                 COLORREF        col                /*= -1*/,
                                                 size_t        AnimateCounter    /*= 4*/)
{
    if (UseColor)
    {
        m_nAnimateSeconds = AnimateCounter;
    }
    else
    {
        m_nAnimateCounter = AnimateCounter;
    }

    m_AnimatedUseColor = UseColor;
    m_AnimatedColor = col;

    // Kill the timer if necessary
    if (m_nTimer != 0)
    {
        _EndAnimateTimer();
    }

    m_StartTimeOfTimer = PSS_Date::GetCurrentTime();

    // Add the components
    for (int nNodeIdx = 0; nNodeIdx < Edges.GetSize(); ++nNodeIdx)
    {
        m_animateEdges.Add(Edges.GetAt(nNodeIdx));
    }

    // Start the timer
    m_nTimer = SetTimer(ANIMATE_TIMER, 50, NULL);
}

void ZDProcessGraphModelController::AnimateSymbol(CODSymbolComponent&    Symbol,
                                                  bool                    UseColor        /*= false*/,
                                                  COLORREF                col                /*= -1*/,
                                                  size_t                AnimateCounter    /*= 4*/)
{
    if (UseColor)
    {
        m_nAnimateSeconds = AnimateCounter;
    }
    else
    {
        m_nAnimateCounter = AnimateCounter;
    }

    m_AnimatedUseColor = UseColor;
    m_AnimatedColor = col;

    // Kill the timer if necessary
    if (m_nTimer != 0)
    {
        _EndAnimateTimer();
    }

    m_StartTimeOfTimer = PSS_Date::GetCurrentTime();

    // Add the component
    m_animateComponents.Add(&Symbol);

    // Start the timer
    m_nTimer = SetTimer(ANIMATE_TIMER, 50, NULL);
}

void ZDProcessGraphModelController::AnimateSymbols(CODComponentSet&    Set,
                                                   bool                UseColor        /*= false*/,
                                                   COLORREF            col                /*= -1*/,
                                                   size_t                AnimateCounter    /*= 4*/)
{
    if (UseColor)
    {
        m_nAnimateSeconds = AnimateCounter;
    }
    else
    {
        m_nAnimateCounter = AnimateCounter;
    }

    m_AnimatedUseColor = UseColor;
    m_AnimatedColor = col;

    // Kill the timer if necessary
    if (m_nTimer != 0)
    {
        _EndAnimateTimer();
    }

    m_StartTimeOfTimer = PSS_Date::GetCurrentTime();

    // Copy symbol to set
    CODComponentIterator    IterSelection(&Set);
    CODComponent*            pSrcComp;

    for (pSrcComp = IterSelection.GetFirst(); pSrcComp != NULL; pSrcComp = IterSelection.GetNext())
    {
        m_animateComponents.Add(pSrcComp);
    }

    // Start the timer
    m_nTimer = SetTimer(ANIMATE_TIMER, 50, NULL);
}

void ZDProcessGraphModelController::AnimateLink(CODLinkComponent&    Link,
                                                bool                UseColor        /*= false*/,
                                                COLORREF            col                /*= -1*/,
                                                size_t                AnimateCounter    /*= 4*/)
{
    if (UseColor)
    {
        m_nAnimateSeconds = AnimateCounter;
    }
    else
    {
        m_nAnimateCounter = AnimateCounter;
    }

    m_AnimatedUseColor = UseColor;
    m_AnimatedColor = col;

    // Kill the timer if necessary
    if (m_nTimer != 0)
    {
        _EndAnimateTimer();
    }

    m_StartTimeOfTimer = PSS_Date::GetCurrentTime();

    // Add the component
    m_animateComponents.Add(&Link);

    // Start the timer
    m_nTimer = SetTimer(ANIMATE_TIMER, 50, NULL);
}

void ZDProcessGraphModelController::AnimateLinks(CODComponentSet&    Set,
                                                 bool                UseColor        /*= false*/,
                                                 COLORREF            col                /*= -1*/,
                                                 size_t            AnimateCounter    /*= 4*/)
{
    if (UseColor)
    {
        m_nAnimateSeconds = AnimateCounter;
    }
    else
    {
        m_nAnimateCounter = AnimateCounter;
    }

    m_AnimatedUseColor = UseColor;
    m_AnimatedColor = col;

    // Kill the timer if necessary
    if (m_nTimer != 0)
    {
        _EndAnimateTimer();
    }

    m_StartTimeOfTimer = PSS_Date::GetCurrentTime();

    // Copy symbol to set
    CODComponentIterator    IterSelection(&Set);
    CODComponent*            pSrcComp;

    for (pSrcComp = IterSelection.GetFirst(); pSrcComp != NULL; pSrcComp = IterSelection.GetNext())
    {
        m_animateComponents.Add(pSrcComp);
    }

    // Start the timer
    m_nTimer = SetTimer(ANIMATE_TIMER, 50, NULL);
}

void ZDProcessGraphModelController::_AnimateNodes()
{
    CODComponentSet setUpdate;

    for (int nNodeIdx = 0; nNodeIdx < m_animateNodes.GetSize(); nNodeIdx++)
    {
        IODNode*            pINode = m_animateNodes.GetAt(nNodeIdx);
        CODSymbolComponent*    pComp = static_cast<CODSymbolComponent*>(pINode);

        BOOL bFlag = !(m_nAnimateCounter % 2);

        pComp->SetTracking(bFlag);

        setUpdate.Add(pComp);
    }

    GetVp()->DrawComponents(&setUpdate);
}

void ZDProcessGraphModelController::_AnimateEdges()
{
    CODComponentSet setUpdate;

    for (int nEdgeIdx = 0; nEdgeIdx < m_animateEdges.GetSize(); nEdgeIdx++)
    {
        IODEdge*            pIEdge = m_animateEdges.GetAt(nEdgeIdx);
        CODLinkComponent*    pComp = static_cast<CODLinkComponent*>(pIEdge);

        BOOL bFlag = !(m_nAnimateCounter % 2);

        pComp->SetTracking(bFlag);

        setUpdate.Add(pComp);
    }

    GetVp()->DrawComponents(&setUpdate);
}

void ZDProcessGraphModelController::_AnimateSymbols()
{
    CODComponentSet setUpdate;

    CODComponentIterator    IterSelection(&m_animateComponents);
    CODComponent*            pSrcComp;

    for (pSrcComp = IterSelection.GetFirst(); pSrcComp != NULL; pSrcComp = IterSelection.GetNext())
    {
        BOOL bFlag = !(m_nAnimateCounter % 2);

        pSrcComp->SetTracking(bFlag);

        setUpdate.Add(pSrcComp);
    }

    GetVp()->DrawComponents(&setUpdate);
}

void ZDProcessGraphModelController::_ChangeColorNodes()
{
    CODComponentSet setUpdate;

    for (int nNodeIdx = 0; nNodeIdx < m_animateNodes.GetSize(); nNodeIdx++)
    {
        IODNode*            pINode = m_animateNodes.GetAt(nNodeIdx);
        CODSymbolComponent*    pComp = static_cast<CODSymbolComponent*>(pINode);

        if (pComp != NULL)
        {
            ZUODSymbolManipulator::ChangeLineColor(pComp, m_AnimatedColor);
            ZUODSymbolManipulator::ChangeLabelLineColor(pComp, m_AnimatedColor);
        }

        setUpdate.Add(pComp);
    }

    GetVp()->DrawComponents(&setUpdate);
}

void ZDProcessGraphModelController::_ChangeColorEdges()
{
    CODComponentSet setUpdate;

    for (int nEdgeIdx = 0; nEdgeIdx < m_animateEdges.GetSize(); nEdgeIdx++)
    {
        IODEdge*            pIEdge = m_animateEdges.GetAt(nEdgeIdx);
        CODLinkComponent*    pComp = static_cast<CODLinkComponent*>(pIEdge);

        if (pComp != NULL)
        {
            ZUODSymbolManipulator::ChangeLineColor(pComp, m_AnimatedColor);
            ZUODSymbolManipulator::ChangeLabelLineColor(pComp, m_AnimatedColor);
        }

        setUpdate.Add(pComp);
    }

    GetVp()->DrawComponents(&setUpdate);
}

void ZDProcessGraphModelController::_ChangeColorSymbols()
{
    CODComponentSet setUpdate;

    CODComponentIterator    IterSelection(&m_animateComponents);
    CODComponent*            pComp;

    for (pComp = IterSelection.GetFirst(); pComp != NULL; pComp = IterSelection.GetNext())
    {
        if (pComp != NULL)
        {
            ZUODSymbolManipulator::ChangeLineColor(pComp, m_AnimatedColor);
            ZUODSymbolManipulator::ChangeLabelLineColor(dynamic_cast<CODSymbolComponent*>(pComp),
                                                        m_AnimatedColor);
        }

        setUpdate.Add(pComp);
    }

    GetVp()->DrawComponents(&setUpdate);
}

void ZDProcessGraphModelController::_ChangeBackColorNodes()
{
    CODComponentSet setUpdate;

    for (int nNodeIdx = 0; nNodeIdx < m_animateNodes.GetSize(); nNodeIdx++)
    {
        IODNode*            pINode = m_animateNodes.GetAt(nNodeIdx);
        CODSymbolComponent*    pComp = static_cast<CODSymbolComponent*>(pINode);

        if (pComp != NULL && ISA(pComp, ZBSymbol))
        {
            ZUODSymbolManipulator::ChangeLineColor(pComp,
                                                   dynamic_cast<ZBSymbol*>(pComp)->GetCurrentLineColor());

            ZUODSymbolManipulator::ChangeLabelLineColor(pComp,
                                                        dynamic_cast<ZBSymbol*>(pComp)->GetCurrentLabelColor());
        }
        else if (pComp != NULL && ISA(pComp, ZBLinkSymbol))
        {
            ZUODSymbolManipulator::ChangeLineColor(pComp,
                                                   dynamic_cast<ZBLinkSymbol*>(pComp)->GetCurrentLineColor());

            ZUODSymbolManipulator::ChangeLabelLineColor(pComp,
                                                        dynamic_cast<ZBLinkSymbol*>(pComp)->GetCurrentLabelColor());
        }

        setUpdate.Add(pComp);
    }

    GetVp()->DrawComponents(&setUpdate);
}

void ZDProcessGraphModelController::_ChangeBackColorEdges()
{
    CODComponentSet setUpdate;

    for (int nEdgeIdx = 0; nEdgeIdx < m_animateEdges.GetSize(); nEdgeIdx++)
    {
        IODEdge*            pIEdge = m_animateEdges.GetAt(nEdgeIdx);
        CODLinkComponent*    pComp = static_cast<CODLinkComponent*>(pIEdge);

        if (pComp != NULL && ISA(pComp, ZBSymbol))
        {
            ZUODSymbolManipulator::ChangeLineColor(pComp,
                                                   dynamic_cast<ZBSymbol*>(pComp)->GetCurrentLineColor());

            ZUODSymbolManipulator::ChangeLabelLineColor(pComp,
                                                        dynamic_cast<ZBSymbol*>(pComp)->GetCurrentLabelColor());
        }
        else if (pComp != NULL && ISA(pComp, ZBLinkSymbol))
        {
            ZUODSymbolManipulator::ChangeLineColor(pComp,
                                                   dynamic_cast<ZBLinkSymbol*>(pComp)->GetCurrentLineColor());

            ZUODSymbolManipulator::ChangeLabelLineColor(pComp,
                                                        dynamic_cast<ZBLinkSymbol*>(pComp)->GetCurrentLabelColor());
        }

        setUpdate.Add(pComp);
    }

    GetVp()->DrawComponents(&setUpdate);
}

void ZDProcessGraphModelController::_ChangeBackColorSymbols()
{
    CODComponentSet setUpdate;

    CODComponentIterator    IterSelection(&m_animateComponents);
    CODComponent*            pComp;

    for (pComp = IterSelection.GetFirst(); pComp != NULL; pComp = IterSelection.GetNext())
    {
        if (pComp != NULL && ISA(pComp, ZBSymbol))
        {
            ZUODSymbolManipulator::ChangeLineColor(pComp,
                                                   dynamic_cast<ZBSymbol*>(pComp)->GetCurrentLineColor());

            ZUODSymbolManipulator::ChangeLabelLineColor(dynamic_cast<CODSymbolComponent*>(pComp),
                                                        dynamic_cast<ZBSymbol*>(pComp)->GetCurrentLabelColor());
        }
        else if (pComp != NULL && ISA(pComp, ZBLinkSymbol))
        {
            ZUODSymbolManipulator::ChangeLineColor(pComp,
                                                   dynamic_cast<ZBLinkSymbol*>(pComp)->GetCurrentLineColor());

            ZUODSymbolManipulator::ChangeLabelLineColor(dynamic_cast<CODSymbolComponent*>(pComp),
                                                        dynamic_cast<ZBLinkSymbol*>(pComp)->GetCurrentLabelColor());
        }

        setUpdate.Add(pComp);
    }

    GetVp()->DrawComponents(&setUpdate);
}

// JMR-MODIF - Le 17 septembre 2006 - Supprime de la sélection les objets interdits à la copie. (Portes, pages, ...)
BOOL ZDProcessGraphModelController::FilterSelection(BOOL ModifyFlag /*= FALSE*/)
{
    CODComponentIterator    IterSelection(GetSelection());
    CODComponent*            pComp;
    BOOL                    SelectionIsModified = ModifyFlag;

    for (pComp = IterSelection.GetFirst(); pComp != NULL; pComp = IterSelection.GetNext())
    {
        if (ISA(pComp, ZBSymbol))
        {
            ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pComp);

            if (pSymbol != NULL)
            {
                if (pSymbol->IsDoor() ||
                    pSymbol->IsPackage() ||
                    pSymbol->IsPage() ||
                    !pSymbol->IsLocal())
                {
                    GetSelection()->Remove(IterSelection.Get());
                    return FilterSelection(TRUE);
                }
            }
        }
        else if (ISA(pComp, ZBLinkSymbol))
        {
            ZBLinkSymbol* pLinkSymbol = dynamic_cast<ZBLinkSymbol*>(pComp);

            if (pLinkSymbol != NULL)
            {
                if (!pLinkSymbol->IsLocal())
                {
                    GetSelection()->Remove(IterSelection.Get());
                    return FilterSelection(TRUE);
                }
            }
        }
        else if (ISA(pComp, CODLabelComponent))
        {
            GetSelection()->Remove(IterSelection.Get());
            return FilterSelection(SelectionIsModified);
        }
    }

    return SelectionIsModified;
}

// JMR-MODIF - Le 17 septembre 2006 - Contrôle la validité des objets avant de valider la commande couper/copier.
BOOL ZDProcessGraphModelController::ValidateCutCopyOperations()
{
    CODComponentIterator    IterSelection(GetSelection());
    CODComponent*            pComp;

    for (pComp = IterSelection.GetFirst(); pComp != NULL; pComp = IterSelection.GetNext())
    {
        if (ISA(pComp, ZBSymbol))
        {
            ZBSymbol* pSymbol = dynamic_cast<ZBSymbol*>(pComp);

            if (pSymbol != NULL)
            {
                if (!pSymbol->IsDoor() &&
                    !pSymbol->IsPackage() &&
                    !pSymbol->IsPage() &&
                    pSymbol->IsLocal())
                {
                    return TRUE;
                }
            }
        }
        else if (ISA(pComp, ZBLinkSymbol))
        {
            ZBLinkSymbol* pLinkSymbol = dynamic_cast<ZBLinkSymbol*>(pComp);

            if (pLinkSymbol != NULL)
            {
                if (pLinkSymbol->IsLocal())
                {
                    return TRUE;
                }
            }
        }
        // JMR-MODIF - Le 8 mai 2007 - Autorise la copie si l'élément sélectionné est une zone de texte.
        else if (ISA(pComp, ZBTextZone))
        {
            return TRUE;
        }
        // JMR-MODIF - Le 8 mai 2007 - Autorise la copie si l'élément sélectionné est une entité de type composant. Ceci
        // inclut tous les symboles de Mercutio, mais les éléments sensibles ont déjà été filtrés dans les lignes de code
        // ci-dessus, et donc seront rejetés avant que le programme atteigne ce point
        else if (ISA(pComp, CODComponent))
        {
            return TRUE;
        }
    }

    return FALSE;
}

// JMR-MODIF - Le 27 septembre 2006 - Cette fonction permet de vider le presse-papiers.
void ZDProcessGraphModelController::ReleaseClipboard()
{
    OpenClipboard();
    EmptyClipboard();
    CloseClipboard();
}

// Cette fonction effectue la fonction "Copier" dans le document.
void ZDProcessGraphModelController::OnEditCopy()
{
    // JMR-MODIF - Le 27 septembre 2006 - Vide le presse-papier avant la nouvelle opération.
    ReleaseClipboard();

    // JMR-MODIF - Le 17 septembre 2006 - Filtre la sélection avant d'autoriser l'opération "copier".
    if (FilterSelection() == TRUE)
    {
        RefreshAllSymbols();

        PSS_MsgBox mBox;

        CString s = _T("");
        s.Format(IDS_WARNING_COPY_SELECTION);
        mBox.Show(s, MB_OK);
    }

    CopySelectionToSet();

    // Call the base class
    CODController::OnEditCopy();

    // Set flag for modification
    if (GetDocument())
    {
        GetDocument()->SetModifiedFlag(TRUE);
    }

    CutCommand = false;
}

// JMR-MODIF - Le 17 septembre 2006 - Ajout de la fonction OnUpdateEditCopy.
void ZDProcessGraphModelController::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(ValidateCutCopyOperations());
}

// Cette fonction effectue la fonction "Couper" dans le document.
void ZDProcessGraphModelController::OnEditCut()
{
    // JMR-MODIF - Le 27 septembre 2006 - Vide le presse-papier avant la nouvelle opération.
    ReleaseClipboard();

    ClearSelectionToSet();
    RemoveReferenceSymbol(GetSelection());

    // JMR-MODIF - Le 17 septembre 2006 - Filtre la sélection avant d'autoriser l'opération "couper".
    if (FilterSelection() == TRUE)
    {
        RefreshAllSymbols();

        PSS_MsgBox mBox;

        CString s = _T("");
        s.Format(IDS_WARNING_CUT_SELECTION);
        mBox.Show(s, MB_OK);
    }

    if (m_pTextEdit != NULL && m_pTextEdit->IsEditing())
    {
        CEdit* pEdit = m_pTextEdit->GetEditControl();

        ASSERT(pEdit != NULL);

        pEdit->Cut();

        return;
    }

    ASSERT(GetRootModel());
    GetRootModel()->SetInCutOperation(true);

    // In our clipboard set
    CopyToClipboardSet(GetSelection());
    ExecuteDeleteCommand(GetSelection());

    GetRootModel()->SetInCutOperation(false);

    // Reset the paste insertion point.
    GetCanvasVp()->SetPasteInsertionPoint(CPoint(0, 0));

    // Refresh the tree
    RefreshModelTree();

    // Set flag for modification
    if (GetDocument())
    {
        GetDocument()->SetModifiedFlag(TRUE);
    }

    CutCommand = true;
}

// JMR-MODIF - Le 17 septembre 2006 - Ajout de la fonction OnUpdateEditCut.
void ZDProcessGraphModelController::OnUpdateEditCut(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(ValidateCutCopyOperations());
}

// Cette fonction permet la copie vers le presse-papier.
void ZDProcessGraphModelController::CopyToClipboardSet(CODComponentSet* pCompSet)
{
    ASSERT(pCompSet != NULL);

    if (pCompSet && pCompSet->GetSize() > 0)
    {
        EmptyClipboardSet();

        // Copy selected components to clipboard using custom clipboard format.
        StoreComponentsToSet(*pCompSet);

        OpenClipboard();
        EmptyClipboard();

        // Copy selected components to clipboard using custom clipboard format.
        CSharedFile file;

        CArchive ar(&file, CArchive::store);

        StoreComponents(ar, *pCompSet);

        ar.Close();

        ::SetClipboardData(m_cfCanvas, file.Detach());

        // Copy selected components to clipboard in enhanced metafile format.
        if (ClipboardEnhMetafileEnabled())
        {
            CMetaFileDC* pMetaDC = GetCanvasVp()->CreateMetafile(*pCompSet);

            if (pMetaDC != NULL)
            {
                HENHMETAFILE hMetaFile = pMetaDC->CloseEnhanced();
                ::SetClipboardData(CF_ENHMETAFILE, hMetaFile);

                delete pMetaDC;
            }
        }

        CloseClipboard();
    }
}

// JMR-MODIF - Le 17 septembre 2006 - Cette fonction vide l'ensemble des données à couper.
void ZDProcessGraphModelController::EmptyClipboardSet()
{
    m_setCut.RemoveAll();
}

// Cette fonction permet l'enregistrement d'un composant dans le presse-papier.
void ZDProcessGraphModelController::StoreComponentsToSet(const CODComponentSet& setComponents)
{
    CODComponentSet        setPrimary;
    CODComponentSet        setDependents;
    CODConnectionSet    setMovingConnections;
    int                    i;

    setPrimary.Append(setComponents);

    // Include labels and contained objects.
    for (i = 0; i < setComponents.GetSize(); i++)
    {
        CODComponent* pComp = setComponents.GetAt(i);

        switch (m_state)
        {
            case OD_MOVE_START:
            case OD_MOVING:
            {
                // Get labels and contained objects
                pComp->GetTranslateSet(setPrimary);
                break;
            }

            case OD_ROTATE_START:
            case OD_ROTATING:
            {
                pComp->GetRotateSet(setPrimary);
                break;
            }

            case OD_SCALE_START:
            case OD_SCALING:
            {
                pComp->GetScaleSet(setPrimary);
                break;
            }
        }
    }

    // Get all connections affected by symbols that are moving.
    for (i = 0; i < setPrimary.GetSize(); i++)
    {
        CODComponent* pComp = setPrimary.GetAt(i);

        if (ISA(pComp, CODSymbolComponent))
        {
            CODSymbolComponent* pSymbol = static_cast<CODSymbolComponent*>(pComp);
            pSymbol->GetMovingConnections(setMovingConnections);
        }
    }

    // Examine moving connections and extract the symbols. Symbols affected that
    // are not already included in the primary set are added to the dependent
    // symbol set.
    for (int nConnectIdx = 0; nConnectIdx < setMovingConnections.GetSize(); nConnectIdx++)
    {
        CODConnection* pConnection = setMovingConnections.GetAt(nConnectIdx);

        ASSERT_VALID(pConnection->GetSourcePort());
        CODSymbolComponent* pSourceSymbol = pConnection->GetSourcePort()->GetOwner();

        ASSERT_VALID(pConnection->GetTargetPort());
        CODSymbolComponent* pTargetSymbol = pConnection->GetTargetPort()->GetOwner();

        BOOL bSourceFound = FALSE;
        BOOL bTargetFound = FALSE;

        for (int i = 0; i < setPrimary.GetSize() && (!bSourceFound || !bTargetFound); i++)
        {
            CODComponent* pComp = setPrimary.GetAt(i);

            if (pSourceSymbol == pComp || pComp->IsChild(pSourceSymbol))
            {
                bSourceFound = TRUE;
            }

            if (pTargetSymbol == pComp || pComp->IsChild(pTargetSymbol))
            {
                bTargetFound = TRUE;
            }
        }

        for (int j = 0; j < setDependents.GetSize() && (!bSourceFound || !bTargetFound); j++)
        {
            CODComponent* pDepComp = setDependents.GetAt(j);

            if (pSourceSymbol == pDepComp || pDepComp->IsChild(pSourceSymbol))
            {
                bSourceFound = TRUE;
            }

            if (pTargetSymbol == pDepComp || pDepComp->IsChild(pTargetSymbol))
            {
                bTargetFound = TRUE;
            }
        }

        if (!bSourceFound)
        {
            //            setDependents.Add( pSourceSymbol );
        }

        if (!bTargetFound)
        {
            //            setDependents.Add( pTargetSymbol );
        }
    }

    // Loop through the primary set and dependent set and serialize the components.
    CODComponentSet* pCurSet = &setDependents;

    for (int nSetCount = 1; nSetCount <= 2; nSetCount++)
    {
        for (i = 0; i < pCurSet->GetSize(); i++)
        {
            CODComponent*        pComp = pCurSet->GetAt(i);
            CODSymbolComponent*    pSymbol = NULL;
            CODConnectionSet    setConnections;
            CODConnectionSet    setDetached;
            int                    nConnectIdx;

            if (ISA(pComp, CODSymbolComponent))
            {
                pSymbol = static_cast<CODSymbolComponent*>(pComp);

                // Any connections to symbols that are not going to be serialized
                // must be detached. This eliminates dangling references.
                pSymbol->GetAllConnections(setConnections);

                for (nConnectIdx = 0; nConnectIdx < setConnections.GetSize(); nConnectIdx++)
                {
                    CODConnection* pConnection = setConnections.GetAt(nConnectIdx);

                    if (setMovingConnections.FindIndex(pConnection) == -1)
                    {
                        pSymbol->Detach(pConnection);
                        setDetached.Add(pConnection);
                    }
                }
            }

            // Store the component
            m_setCut.Add(pComp);

            // Concatonate all parent transformations and store those
            // with the component. This is necessary because the parent
            // isn't being saved with the component, but we still want
            // the component to be rendered in the same place. When
            // read back in, the parent transform matrix is concatonated
            // with the component transform matrix.
            CODTransform parentXform;

            pComp->ConcatParentTransforms(parentXform);

            if (pSymbol != NULL)
            {
                // Re-attach connections that were detached.
                for (nConnectIdx = 0; nConnectIdx < setDetached.GetSize(); nConnectIdx++)
                {
                    CODConnection* pConnection = setDetached.GetAt(nConnectIdx);
                    pSymbol->Attach(pConnection);
                }
            }
        }

        pCurSet = &setPrimary;
    }
}

// Cette fonction effectue la fonction "Coller" dans le document.
void ZDProcessGraphModelController::OnEditPaste()
{
    if (CutCommand == true)
    {
        ASSERT(GetRootModel());
        GetRootModel()->SetInCutOperation(true);

        CODComponent*                                    pComp;
        CODComponentSet                                    setTranslate;
        CMap<CODComponent*, CODComponent*, int, int>    mapTranslateSet;
        BOOL                                            bAdded;

        int nPos = 0;

        CODComponentIterator i(&m_setCut);

        // Remove labels from the set
        for (pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext())
        {
            if (ISA(pComp, CODLabelComponent))
            {
                i.Remove();
                pComp->Release();
                i.GetPrev();
            }
        }

        for (pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext())
        {
            if (!mapTranslateSet.Lookup(pComp, bAdded))
            {
                mapTranslateSet.SetAt(pComp, nPos++);
            }
        }

        for (pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext())
        {
            pComp->GetTranslateSet(setTranslate);

            if (setTranslate.GetSize() > 0)
            {
                CODComponent* pTranslateComp;
                CODComponentIterator iTransSet(&setTranslate);

                for (pTranslateComp = iTransSet.GetFirst(); pTranslateComp != NULL; pTranslateComp = iTransSet.GetNext())
                {
                    if (!mapTranslateSet.Lookup(pTranslateComp, bAdded))
                    {
                        ASSERT_VALID(pTranslateComp);
                        mapTranslateSet.SetAt(pTranslateComp, nPos++);
                        pTranslateComp->AddRef();
                    }
                }
            }

            setTranslate.SetSize(0);
        }

        CPoint    ptComp;
        CSize    szComp;
        CRect    rcAllComps;
        CRect    rcComp;

        setTranslate.SetSize(mapTranslateSet.GetCount());

        POSITION pos;

        for (pos = mapTranslateSet.GetStartPosition(); pos != NULL; )
        {
            mapTranslateSet.GetNextAssoc(pos, pComp, nPos);
            ASSERT_VALID(pComp);
            setTranslate.SetAt(nPos, pComp);
        }

        BOOL bFirstComp = TRUE;
        CODComponentIterator iTranslate(&setTranslate);

        // Find bounding rectangle for all components
        for (pComp = iTranslate.GetFirst(); pComp != NULL; pComp = iTranslate.GetNext())
        {
            ptComp = pComp->GetOrigin();
            szComp = pComp->GetSize();

            rcComp.SetRect(ptComp.x, ptComp.y, ptComp.x + szComp.cx, ptComp.y + szComp.cy);

            if (bFirstComp)
            {
                rcAllComps = rcComp;
                bFirstComp = FALSE;
            }
            else
            {
                rcAllComps = CODGlobal::UnionRect(rcAllComps, rcComp);
            }
        }

        // Get current paste insertion point.
        CPoint ptInsert = GetCanvasVp()->GetPasteInsertionPoint();
        CPoint ptHoldInsert = ptInsert;

        CODTransform xform;
        CODTransform *pCompXForm;

        int nMoveX = (int)(ptInsert.x - rcAllComps.TopLeft().x);
        int nMoveY = (int)(ptInsert.y - rcAllComps.TopLeft().y);

        if ((nMoveX < 5) && (nMoveY < 5) && (nMoveX > -5) && (nMoveY > -5))
        {
            nMoveX = 5;
            nMoveY = 5;
        }

        // Make sure components will be inserted inside the model.
        GetCanvasModel()->FindValidMove(m_setCut, nMoveX, nMoveY, &rcAllComps);
        ptInsert.x = (LONG)nMoveX;
        ptInsert.y = (LONG)nMoveY;

        // Translate the components.
        xform.Translate(ptInsert.x, ptInsert.y);

        // Translate the components to the new insertion point.
        for (pComp = iTranslate.GetFirst(); pComp != NULL; pComp = iTranslate.GetNext())
        {
            pCompXForm = pComp->GetTransform();

            if (pCompXForm)
            {
                *pCompXForm = xform * (*pCompXForm);
            }
            else
            {
                pComp->SetTransform(new CODTransform(xform));
            }

            pComp->UpdateRgn();

            if (ISA(pComp, CODSymbolComponent))
            {
                // Hide the ports
                ((CODSymbolComponent*)(pComp))->SetPortsVisible(FALSE);
            }
        }

        // Get current viewport visible region info.
        rcAllComps.OffsetRect(ptInsert);

        CPoint ptVpOrigin = GetCanvasVp()->GetLogOrigin();
        CPoint ptOldVpOrigin = ptVpOrigin;

        CSize szVpSize = GetCanvasVp()->GetLogSize();

        // If new components bottom right corner extends beyond the visible area,
        // pan the viewport so it is visible.
        if (ptVpOrigin.x + szVpSize.cx < rcAllComps.right ||
            ptVpOrigin.y + szVpSize.cy < rcAllComps.bottom)
        {
            if (ptVpOrigin.x + szVpSize.cx < rcAllComps.right)
            {
                ptVpOrigin.x = rcAllComps.right - szVpSize.cx;
            }

            if (ptVpOrigin.y + szVpSize.cy < rcAllComps.bottom)
            {
                ptVpOrigin.y = rcAllComps.bottom - szVpSize.cy;
            }

            GetCanvasVp()->Pan(ptVpOrigin.x - ptOldVpOrigin.x, ptVpOrigin.y - ptOldVpOrigin.y);
            GetCanvasVp()->Invalidate();
        }

        OnPostCutPasteOperation(&m_setCut);

        // Insert the components.
        ExecuteInsertCommand(&m_setCut);

        /***********************************************************************************************************
        // JMR-MODIF - Le 16 mars 2006 - Supprimé destruction du lien, car utilisé lors de la fermeture du document.
        // Sans ce lien, la fermeture du document envoie un message "Debug assertion failed."

        // Release the components (they were AddRef'd once on CopyFromClipboard()
        // and a second time when inserted into the model).
        for( pComp = iTranslate.GetFirst(); pComp != NULL; pComp = iTranslate.GetNext() )
        {
            pComp->Release();
        }
        ***********************************************************************************************************/

        // Find new viewport paste insertion point.
        float fGridSpacingLogX;
        float fGridSpacingLogY;

        GetCanvasVp()->GetRuler()->MeasureToLog(GetCanvasVp()->GetHorizontalGridSpacing(),
                                                fGridSpacingLogX,
                                                FALSE);

        GetCanvasVp()->GetRuler()->MeasureToLog(GetCanvasVp()->GetVerticalGridSpacing(),
                                                fGridSpacingLogY,
                                                TRUE);

        ptInsert.x += (LONG)(fGridSpacingLogX + 0.5);
        ptInsert.y += (LONG)(fGridSpacingLogY + 0.5);

        // Set new viewport paste insertion point.
        ptHoldInsert.x += (LONG)(fGridSpacingLogX + 0.5);
        ptHoldInsert.y += (LONG)(fGridSpacingLogY + 0.5);

        GetCanvasVp()->SetPasteInsertionPoint(ptHoldInsert);

        ASSERT(GetRootModel());
        GetRootModel()->SetInCutOperation(false);

        // Recalculate all references
        GetRootModel()->RecalculateParentPtr();
        GetRootModel()->ReCalculateAbsolutePath();
    }
    else
    {
        // Call the base class
        CODController::OnEditPaste();

        // Call the virtual method on symbol added
        OnSymbolAdded(&m_setSelection);
    }

    // Set flag for modification
    if (GetDocument())
    {
        GetDocument()->SetModifiedFlag(TRUE);
    }

    // ***********************************************************************************************************
    // JMR-MODIF - Le 27 septembre 2006 - Remplace la fonction RefreshModelTree par la fonction RefreshAllSymbols.

    // Refresh the tree
//    RefreshModelTree();

    RefreshAllSymbols();
    // ***********************************************************************************************************

    // JMR-MODIF - Le 27 septembre 2006 - Vide le presse-papier à la fin de l'opération.
    ReleaseClipboard();

    CutCommand = false;
}

void ZDProcessGraphModelController::OnEditDuplicate()
{
    CWaitCursor cursor;

    // Call the base class
    CODController::OnEditPaste();

    // Call the virtual method on symbol added
    OnSymbolDuplicated(&m_setSelection);

    // ***********************************************************************************************************
    // JMR-MODIF - Le 27 septembre 2006 - Remplace la fonction RefreshModelTree par la fonction RefreshAllSymbols.

    // Refresh the tree
//    RefreshModelTree();

    RefreshAllSymbols();
    // ***********************************************************************************************************

    // Set flag for modification
    if (GetDocument())
    {
        GetDocument()->SetModifiedFlag(TRUE);
    }

    // JMR-MODIF - Le 27 septembre 2006 - Vide le presse-papier à la fin de l'opération.
    ReleaseClipboard();

    CutCommand = false;
}

void ZDProcessGraphModelController::OnUpdateEditDuplicate(CCmdUI* pCmdUI)
{
    // Allow duplicates only if at least one object in the selection set
    pCmdUI->Enable(m_setCopy.GetSize() > 0 && CanDuplicateObject(&m_setCopy));
}

void ZDProcessGraphModelController::OnEditRedo()
{
    // Call the base class
    CODController::OnEditRedo();

    // Refresh the tree
    RefreshModelTree();

    // Set flag for modification
    if (GetDocument())
    {
        GetDocument()->SetModifiedFlag(TRUE);
    }
}

void ZDProcessGraphModelController::OnEditUndo()
{
    // Call the base class
    CODController::OnEditUndo();

    // ***********************************************************************************************************
    // JMR-MODIF - Le 21 mars 2006 - Si le dernier élément effacé était un livrable, ordonne son rafraîchissement.
    // Ceci permet d'éviter que les symboles des anciens modèles ne s'affichent pas correctement après une
    // commande Undo.
    for (SEC_INT i = 0; i < GetSelection()->GetSize(); i++)
    {
        if (GetSelection()->GetAt(i) != NULL && ISA(GetSelection()->GetAt(i), ZBLinkSymbol))
        {
            ZBLinkSymbol* m_TmpSym = reinterpret_cast<ZBLinkSymbol*>(GetSelection()->GetAt(i));

            if (m_TmpSym != NULL)
            {
                m_TmpSym->UpdateRgn(TRUE);
                m_TmpSym->RedrawSymbol();
            }
        }
    }
    // ***********************************************************************************************************

    // Refresh the tree
    RefreshModelTree();

    // Set flag for modification
    if (GetDocument())
    {
        GetDocument()->SetModifiedFlag(TRUE);
    }
}

// Select all objects
void ZDProcessGraphModelController::OnSelectAll()
{
    SelectAllComponents();
}

// Delete a symbol
void ZDProcessGraphModelController::OnEditClear()
{
    CutCommand = false;

    AssignSymbolHit();

    // Call the base class
    CODController::OnEditClear();

    // Set flag for modification
    if (GetDocument())
    {
        GetDocument()->SetModifiedFlag(TRUE);
    }
}

void ZDProcessGraphModelController::OnEditName()
{
    AssignSymbolHit();

    // Check if is local
    bool IsLocal = false;

    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        IsLocal = dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IsLocal();
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        IsLocal = dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IsLocal();
    }

    if (IsLocal)
    {
        EditName(m_pSymbolHit);
    }
}

void ZDProcessGraphModelController::OnUpdateEditName(CCmdUI* pCmdUI)
{
    AssignSymbolHit();

    // Retreive the enable flag
    BOOL bEnable = FALSE;

    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        bEnable = dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IncludeNameArea() &&
            dynamic_cast<ZBSymbol*>(m_pSymbolHit)->UseDynamicArea() &&
            dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IsNameAreaVisible();
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        bEnable = dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IncludeNameArea() &&
            dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->UseDynamicArea() &&
            dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IsNameAreaVisible();
    }

    pCmdUI->Enable(bEnable);
}

void ZDProcessGraphModelController::OnEditComment()
{
    AssignSymbolHit();

    // Check if is local
    bool IsLocal = false;

    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        IsLocal = dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IsLocal();
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        IsLocal = dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IsLocal();
    }

    if (IsLocal)
    {
        EditComment(m_pSymbolHit);
    }
}

void ZDProcessGraphModelController::OnUpdateEditComment(CCmdUI* pCmdUI)
{
    AssignSymbolHit();

    // Retreive the enable flag
    BOOL bEnable = FALSE;

    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        bEnable = dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IncludeDescriptionArea() &&
            dynamic_cast<ZBSymbol*>(m_pSymbolHit)->UseDynamicArea() &&
            dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IsDescriptionsAreaVisible();
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        bEnable = dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IncludeDescriptionArea() &&
            dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->UseDynamicArea() &&
            dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IsDescriptionsAreaVisible();
    }

    pCmdUI->Enable(bEnable);
}

void ZDProcessGraphModelController::OnSymbolShowNameArea()
{
    AssignSymbolHit();

    // Change the flag
    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        dynamic_cast<ZBSymbol*>(m_pSymbolHit)->DisplayNameArea(!dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IsNameAreaVisible());

        // Adjust the element position for areas
        dynamic_cast<ZBSymbol*>(m_pSymbolHit)->AdjustAreaPosition();
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->DisplayNameArea(!dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IsNameAreaVisible());

        // Adjust the element position for areas
        dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->AdjustAreaPosition();
    }

    // Set flag for modification
    if (GetDocument())
    {
        GetDocument()->SetModifiedFlag(TRUE);
    }
}

void ZDProcessGraphModelController::OnUpdateSymbolShowNameArea(CCmdUI* pCmdUI)
{
    AssignSymbolHit();

    // Retreive the enable flag
    BOOL bEnable = FALSE;

    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        bEnable = dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IncludeNameArea() &&
            dynamic_cast<ZBSymbol*>(m_pSymbolHit)->UseDynamicArea();
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        bEnable = dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IncludeNameArea() &&
            dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->UseDynamicArea();
    }

    pCmdUI->Enable(bEnable);

    // If enable, retreive the checked flag
    if (bEnable)
    {
        BOOL bChecked = FALSE;

        if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
        {
            bChecked = dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IsNameAreaVisible();
        }
        else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
        {
            bChecked = dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IsNameAreaVisible();
        }

        pCmdUI->SetCheck(bChecked);
    }
}

void ZDProcessGraphModelController::OnSymbolShowDescriptionArea()
{
    AssignSymbolHit();

    // Change the flag
    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        dynamic_cast<ZBSymbol*>(m_pSymbolHit)->
            DisplayDescriptionArea(!dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IsDescriptionsAreaVisible());

        // Adjust the element position for areas
        dynamic_cast<ZBSymbol*>(m_pSymbolHit)->AdjustAreaPosition();
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->
            DisplayDescriptionArea(!dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IsDescriptionsAreaVisible());

        // Adjust the element position for areas
        dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->AdjustAreaPosition();
    }

    // Set flag for modification
    if (GetDocument())
    {
        GetDocument()->SetModifiedFlag(TRUE);
    }
}

void ZDProcessGraphModelController::OnUpdateSymbolShowDescriptionArea(CCmdUI* pCmdUI)
{
    AssignSymbolHit();

    // Retreive the enable flag
    BOOL bEnable = FALSE;

    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        bEnable = dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IncludeDescriptionArea() &&
            dynamic_cast<ZBSymbol*>(m_pSymbolHit)->UseDynamicArea();
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        bEnable = dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IncludeDescriptionArea() &&
            dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->UseDynamicArea();
    }

    pCmdUI->Enable(bEnable);

    // If enable, retreive the checked flag
    if (bEnable)
    {
        BOOL bChecked = FALSE;

        if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
        {
            bChecked = dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IsDescriptionsAreaVisible();
        }
        else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
        {
            bChecked = dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IsDescriptionsAreaVisible();
        }

        pCmdUI->SetCheck(bChecked);
    }
}

void ZDProcessGraphModelController::OnSymbolShowAttributeArea()
{
    AssignSymbolHit();

    // Change the flag
    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        dynamic_cast<ZBSymbol*>(m_pSymbolHit)->
            DisplayAttributeArea(!dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IsAttributeAreaVisible());

        // If it is visible, then refresh the attribute area
        if (dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IsAttributeAreaVisible())
        {
            dynamic_cast<ZBSymbol*>(m_pSymbolHit)->RefreshAttributeAreaText();
        }

        // Adjust the element position for areas
        dynamic_cast<ZBSymbol*>(m_pSymbolHit)->AdjustAreaPosition();
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->
            DisplayAttributeArea(!dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IsAttributeAreaVisible());

        // If it is visible, then refresh the attribute area
        if (dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IsAttributeAreaVisible())
        {
            dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->RefreshAttributeAreaText();
        }

        // Adjust the element position for areas
        dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->AdjustAreaPosition();
    }

    // Set flag for modification
    if (GetDocument())
    {
        GetDocument()->SetModifiedFlag(TRUE);
    }
}

void ZDProcessGraphModelController::OnUpdateSymbolShowAttributeArea(CCmdUI* pCmdUI)
{
    AssignSymbolHit();

    // Retreive the enable flag
    BOOL bEnable = FALSE;

    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        bEnable = dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IncludeAttributeArea() &&
            dynamic_cast<ZBSymbol*>(m_pSymbolHit)->UseDynamicArea();
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        bEnable = dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IncludeAttributeArea() &&
            dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->UseDynamicArea();
    }

    pCmdUI->Enable(bEnable);

    // If enable, retreive the checked flag
    if (bEnable)
    {
        BOOL bChecked = FALSE;

        if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
        {
            bChecked = dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IsAttributeAreaVisible();
        }
        else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
        {
            bChecked = dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IsAttributeAreaVisible();
        }

        pCmdUI->SetCheck(bChecked);
    }
}

void ZDProcessGraphModelController::OnSymbolShowLabelAttributes()
{
    AssignSymbolHit();

    // Change the flag
    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        dynamic_cast<ZBSymbol*>(m_pSymbolHit)->
            SetDisplayTitleText(!dynamic_cast<ZBSymbol*>(m_pSymbolHit)->GetDisplayTitleText());
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->
            SetDisplayTitleText(!dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->GetDisplayTitleText());
    }

    // Set flag for modification
    if (GetDocument())
    {
        GetDocument()->SetModifiedFlag(TRUE);
    }
}

void ZDProcessGraphModelController::OnUpdateSymbolShowLabelAttributes(CCmdUI* pCmdUI)
{
    AssignSymbolHit();

    // Retreive the enable flag
    BOOL bEnable = FALSE;

    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        bEnable = dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IncludeAttributeArea() &&
            dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IsAttributeAreaVisible() &&
            dynamic_cast<ZBSymbol*>(m_pSymbolHit)->UseDynamicArea();
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        bEnable = dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IncludeAttributeArea() &&
            dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IsAttributeAreaVisible() &&
            dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->UseDynamicArea();
    }

    pCmdUI->Enable(bEnable);

    // If enable, retreive the checked flag
    if (bEnable)
    {
        BOOL bChecked = FALSE;

        if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
        {
            bChecked = dynamic_cast<ZBSymbol*>(m_pSymbolHit)->GetDisplayTitleText();
        }
        else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
        {
            bChecked = dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->GetDisplayTitleText();
        }

        pCmdUI->SetCheck(bChecked);
    }
}

void ZDProcessGraphModelController::OnSymbolSelectAttributes()
{
    AssignSymbolHit();

    // Check if symbol clicked allow the
    if (m_pSymbolHit == NULL || (!ISA(m_pSymbolHit, ZBSymbol) && !ISA(m_pSymbolHit, ZBLinkSymbol)))
    {
        return;
    }

    // Retrieve the property set from object
    ZBPropertySet            PropSet;
    ZBPropertyAttributes    PropAttributes;

    // Check what symbol clicked
    if (ISA(m_pSymbolHit, ZBSymbol))
    {
        // Retrieve the property set from object
        dynamic_cast<ZBSymbol*>(m_pSymbolHit)->FillProperties(PropSet);

        // Copy symbol attributes
        PropAttributes = dynamic_cast<ZBSymbol*>(m_pSymbolHit)->GetAttributes();
    }
    else
    {
        // Retrieve the property set from object
        dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->FillProperties(PropSet);

        // Copy symbol attributes
        PropAttributes = dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->GetAttributes();
    }

    // Call the base dialog for attribute selection
    ZVSelectSymbolAttributeDlg dlg(&PropAttributes, &PropSet);
    UINT RetValue = dlg.DoModal();

    // Display the wait cursor for this operation.
    CWaitCursor Cursor;

    // Remove all properties
    ZBPropertyIterator    i(&PropSet);
    ZBProperty*            pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        delete pProp;
    }

    PropSet.RemoveAll();

    // Test the return value
    switch (RetValue)
    {
        case IDOK:
        {
            if (ISA(m_pSymbolHit, ZBSymbol))
            {
                dynamic_cast<ZBSymbol*>(m_pSymbolHit)->OnChangeAttributes(&PropAttributes);
            }
            else
            {
                dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->OnChangeAttributes(&PropAttributes);
            }

            break;
        }

        case ID_APPLYTOALL:
        {
            // Run through all elements and sets the new attributes
            if (GetRootModel())
            {
                if (ISA(m_pSymbolHit, ZBSymbol))
                {
                    GetRootModel()->PropagateNewSymbolAttributes(&PropAttributes,
                                                                 dynamic_cast<ZBSymbol*>(m_pSymbolHit)->GetObjectTypeID());
                }
                else
                {
                    GetRootModel()->PropagateNewSymbolAttributes(&PropAttributes,
                                                                 dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->GetObjectTypeID());
                }
            }

            break;
        }

        default:
        {
            return;
        }
    }

    // If we would like to have these attributes set as the default,
    // Then copy them to the default properties
    if (dlg.MustSetAsDefaultToAll())
    {
        if (ISA(m_pSymbolHit, ZBSymbol))
        {
            ZAModelGlobal::GetGlobalPropertyAttributes(dynamic_cast<ZBSymbol*>(m_pSymbolHit)->GetObjectTypeID()) = PropAttributes;
        }
        else
        {
            ZAModelGlobal::GetGlobalPropertyAttributes(dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->GetObjectTypeID()) = PropAttributes;
        }
    }

    // Set flag for modification
    if (GetDocument())
    {
        GetDocument()->SetModifiedFlag(TRUE);
    }
}

void ZDProcessGraphModelController::OnUpdateSymbolSelectAttributes(CCmdUI* pCmdUI)
{
    AssignSymbolHit();

    // Retreive the enable flag
    BOOL bEnable = FALSE;

    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        bEnable = dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IncludeAttributeArea() &&
            dynamic_cast<ZBSymbol*>(m_pSymbolHit)->IsAttributeAreaVisible() &&
            dynamic_cast<ZBSymbol*>(m_pSymbolHit)->UseDynamicArea();
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        bEnable = dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IncludeAttributeArea() &&
            dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->IsAttributeAreaVisible() &&
            dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->UseDynamicArea();
    }

    pCmdUI->Enable(bEnable);
}

void ZDProcessGraphModelController::OnDynamicAttributesAdd()
{
    ASSERT(GetDocument());
    ASSERT(ISA(GetDocument(), ZDProcessGraphModelDoc));

    ZDProcessGraphModelDoc* pDoc = dynamic_cast<ZDProcessGraphModelDoc*>(GetDocument());

    if (!pDoc->HasDynamicPropertiesManager())
    {
        pDoc->AllocatePropertiesManager();
    }

    ASSERT(pDoc->GetDynamicPropertiesManager());

    AssignSymbolHit();

    ZVDynamicAttributesCreation dlg(pDoc, (m_pSymbolHit != NULL && (ISA(m_pSymbolHit, ZBSymbol) ||
                                                                    ISA(m_pSymbolHit, ZBLinkSymbol))) ? true : false);

    if (dlg.DoModal() == IDCANCEL)
    {
        return;
    }

    // Assigns the runtime class and the symbol name and reference if a symbol is selected
    CRuntimeClass* pRTClass = NULL;

    CString SymbolName;

    int SymbolRef = -1;

    if (m_pSymbolHit != NULL && (ISA(m_pSymbolHit, ZBSymbol) || ISA(m_pSymbolHit, ZBLinkSymbol)))
    {
        pRTClass = m_pSymbolHit->GetRuntimeClass();
        SymbolName = dynamic_cast<ZIBasicSymbol*>(m_pSymbolHit)->GetSymbolName();
        SymbolRef = dynamic_cast<ZIBasicSymbol*>(m_pSymbolHit)->GetSymbolReferenceNumber();
    }

    ZBProperty*        pProperty = NULL;
    PSS_StringFormat    ft;

    switch (dlg.GetVisibility())
    {
        // Local
        case 0:
        {
            if (m_pSymbolHit)
            {
                pProperty = pDoc->GetDynamicPropertiesManager()->RegisterProperty(dlg.GetCategoryName(),
                                                                                  dlg.GetAttributeName(),
                                                                                  dlg.GetAttributeDescription(),
                                                                                  dlg.GetPropertyType(),
                                                                                  ft,
                                                                                  SymbolName,
                                                                                  SymbolRef);

                // Add the property directly to the symbol
                dynamic_cast<ZIBasicSymbol*>(m_pSymbolHit)->
                    GetDynamicPropertiesManager()->AddDynamicProperty(pProperty->Dup());
            }

            break;
        }

        // Same class type
        case 1:
        {
            pProperty = pDoc->GetDynamicPropertiesManager()->RegisterProperty(dlg.GetCategoryName(),
                                                                              dlg.GetAttributeName(),
                                                                              dlg.GetAttributeDescription(),
                                                                              dlg.GetPropertyType(),
                                                                              ft,
                                                                              pRTClass);

            // Add the property to all symbols with the same class type
            ZUDynamicAttributesManipulator::AssignProperty(GetRootModel(), pProperty, pRTClass);

            break;
        }

        // All symbols
        case 2:
        {
            pProperty = pDoc->GetDynamicPropertiesManager()->RegisterProperty(dlg.GetCategoryName(),
                                                                              dlg.GetAttributeName(),
                                                                              dlg.GetAttributeDescription(),
                                                                              dlg.GetPropertyType(),
                                                                              ft);

            // Add the property to all symbols
            ZUDynamicAttributesManipulator::AssignProperty(GetRootModel(), pProperty);

            break;
        }
    }

    // JMR-MODIF - Le 22 août 2005 - Ordonne le rafraîchissement de l'affichage après l'ajout d'une propriété.
    NotifySymbolSelected(m_pSymbolHit);
}

void ZDProcessGraphModelController::OnUpdateDynamicAttributesAdd(CCmdUI* pCmdUI)
{
    // No distinction
    pCmdUI->Enable(TRUE);
}

// JMR-MODIF - Le 18 août 2005 - Ajout de la fonction OnDynamicAttributesDuplicate.
void ZDProcessGraphModelController::OnDynamicAttributesDuplicate()
{
    // Teste la validité du document.
    ASSERT(GetDocument());
    ASSERT(ISA(GetDocument(), ZDProcessGraphModelDoc));

    // Obtient le pointeur sur le document.
    ZDProcessGraphModelDoc* pDoc = dynamic_cast<ZDProcessGraphModelDoc*>(GetDocument());

    // Si le document n'a pas de gestionnaire de propriétés dynamiques, on en crée un par défaut.
    if (!pDoc->HasDynamicPropertiesManager())
    {
        pDoc->AllocatePropertiesManager();
    }

    // Teste la validité du gestionnaire de propriétés dynamiques.
    ASSERT(pDoc->GetDynamicPropertiesManager());

    AssignSymbolHit();

    // Crée et affiche la boîte de dialogue pour la duplication.
    ZVDynamicAttributesDuplication m_Dlg(pDoc, (m_pSymbolHit != NULL && (ISA(m_pSymbolHit, ZBSymbol) ||
                                                                         ISA(m_pSymbolHit, ZBLinkSymbol))) ? true : false);

    if (m_Dlg.DoModal() == IDCANCEL)
    {
        return;
    }

    CString            SymbolName;
    int                SymbolRef = -1;
    ZBProperty*        pSrcProperty = NULL;
    ZBProperty*        pDestProperty = NULL;
    PSS_StringFormat    ft;
    ZBPropertySet    PropSet;
    CStringArray    m_PropList;

    // Retrouve le nom et la référence du symbole propriétaire.
    if (m_pSymbolHit != NULL && (ISA(m_pSymbolHit, ZBSymbol) || ISA(m_pSymbolHit, ZBLinkSymbol)))
    {
        SymbolName = dynamic_cast<ZIBasicSymbol*>(m_pSymbolHit)->GetSymbolName();
        SymbolRef = dynamic_cast<ZIBasicSymbol*>(m_pSymbolHit)->GetSymbolReferenceNumber();
    }

    // Obtient les propriétés dynamiques contenues dans le symbole. Cela servira pour obtenir les données.
    if (m_pSymbolHit != NULL)
    {
        if (ISA(m_pSymbolHit, ZBSymbol))
        {
            dynamic_cast<ZBSymbol*>(m_pSymbolHit)->FillProperties(PropSet);
        }

        if (ISA(m_pSymbolHit, ZBLinkSymbol))
        {
            dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->FillProperties(PropSet);
        }
    }

    // Obtient la liste des propriétés contenues dans la catégorie choisie.
    pDoc->GetDynamicPropertiesManager()->CreatePropertyList(m_Dlg.m_Category, m_PropList);

    // Copie les propriétés. A ce stade, seuls les "conteneurs" de propriétés sont copiés, c'est à dire que l'on
    // obtient des propriétés portant les mêmes noms et descriptions que dans la source de données, mais les
    // valeurs ne sont pas copiées. La copie des valeurs se fera un peu plus bas dans le code.
    for (INT_PTR i = 0; i < m_PropList.GetSize(); i++)
    {
        CString sProperty = m_PropList.GetAt(i);

        pSrcProperty = pDoc->GetDynamicPropertiesManager()->GetPropertyItem(m_Dlg.m_Category, sProperty);
        pDestProperty = pDoc->GetDynamicPropertiesManager()->RegisterProperty(m_Dlg.m_Name,
                                                                              pSrcProperty->GetLabel(),
                                                                              pSrcProperty->GetDescription(),
                                                                              pSrcProperty->GetPTType(),
                                                                              ft,
                                                                              SymbolName,
                                                                              SymbolRef);

        // Si l'option "Copier les valeurs" est cochée dans la boîte de dialogue, on copie les valeurs.
        if (m_Dlg.m_bDupValuesIsChecked == TRUE)
        {
            ZBPropertyIterator    j(&PropSet);
            ZBProperty*            pProp;

            for (pProp = j.GetFirst(); pProp; pProp = j.GetNext())
            {
                if (pProp->GetCategory() == m_Dlg.m_Category &&
                    pProp->GetLabel() == pSrcProperty->GetLabel())
                {
                    pDestProperty->SetStringFormat(pProp->GetStringFormat());

                    switch (pSrcProperty->GetPTValueType())
                    {
                        case ZBProperty::PT_DATE:
                        {
                            pDestProperty->SetValueDate(pProp->GetValueDate());
                            break;
                        }

                        case ZBProperty::PT_DOUBLE:
                        {
                            pDestProperty->SetValueDouble(pProp->GetValueDouble());
                            break;
                        }

                        case ZBProperty::PT_DURATION:
                        {
                            pDestProperty->SetValueDuration(pProp->GetValueDuration());
                            break;
                        }

                        case ZBProperty::PT_FLOAT:
                        {
                            pDestProperty->SetValueFloat(pProp->GetValueFloat());
                            break;
                        }

                        case ZBProperty::PT_STRING:
                        {
                            pDestProperty->SetValueString(pProp->GetValueString());
                            break;
                        }

                        case ZBProperty::PT_TIMESPAN:
                        {
                            pDestProperty->SetValueTimeSpan(pProp->GetValueTimeSpan());
                            break;
                        }

                        case ZBProperty::PT_UNKNOWN:
                        {
                            break;
                        }
                    }
                }
            }
        }

        // Copie la nouvelle propriété directement dans le symbole.
        dynamic_cast<ZIBasicSymbol*>(m_pSymbolHit)->
            GetDynamicPropertiesManager()->AddDynamicProperty(pDestProperty->Dup());
    }

    // Rafraîchit l'affichage.
    NotifySymbolSelected(m_pSymbolHit);
}

// JMR-MODIF - Le 18 août 2005 - Ajout de la fonction OnUpdateDynamicAttributesDuplicate.
void ZDProcessGraphModelController::OnUpdateDynamicAttributesDuplicate(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(TRUE);
}

void ZDProcessGraphModelController::OnDynamicAttributesDelete()
{}

void ZDProcessGraphModelController::OnUpdateDynamicAttributesDelete(CCmdUI* pCmdUI)
{
    // No distinction
    pCmdUI->Enable(TRUE);
}

void ZDProcessGraphModelController::OnRefresh()
{
    ASSERT(GetViewport());
    GetViewport()->UpdateAll();

    // Refresh all symbol attributes
    ASSERT(GetModel());
    GetModel()->RefreshSymbolAttributes(true);

    // Refresh also the model tree
    RefreshModelTree();
}

// JMR-MODIF - Le 7 juin 2005 - Ajout de la fonction RefreshAllSymbols()
// Cette fonction permet de rafraîchir tous les symboles présents dans le document courant.
void ZDProcessGraphModelController::RefreshAllSymbols()
{
    ASSERT(GetViewport());
    GetViewport()->UpdateAll();

    // Refresh all symbol attributes
    ASSERT(GetRootModel());
    GetRootModel()->RefreshSymbolAttributes(true);

    // Refresh also the model tree
    RefreshModelTree();
}

ZIProcessGraphModelViewport* ZDProcessGraphModelController::EnsureSymbolVisible(CODComponent* pComp)
{
    if (pComp == NULL)
    {
        return NULL;
    }

    ZIProcessGraphModelViewport*    pVp = NULL;
    CODSymbolComponent*                pSymbol = NULL;

    if (ISA(pComp, ZBSymbol))
    {
        pVp = BrowseSymbolModel(reinterpret_cast<ZBSymbol*>(pComp));
        pSymbol = reinterpret_cast<CODSymbolComponent*>(pComp);
    }
    else if (ISA(pComp, ZBLinkSymbol))
    {
        pVp = BrowseLinkSymbolModel(reinterpret_cast<ZBLinkSymbol*>(pComp));
        pSymbol = reinterpret_cast<CODSymbolComponent*>(pComp);
    }

    // When open a new model, unselect all symbols
    if (pVp && pVp->GetModelController())
    {
        pVp->GetModelController()->UnselectAllComponents();
    }

    // And then animate the symbol
    if (pSymbol && pVp && pVp->GetModelController())
    {
        pVp->GetModelController()->AnimateSymbol(*pSymbol, true, defCOLOR_LTBLUE, 8);
    }

    // Returns the viewport
    return pVp;
}

ZIProcessGraphModelViewport* ZDProcessGraphModelController::BrowseLocalSymbol(CODComponent* pComp)
{
    if (!GetDocument() || !ISA(GetDocument(), ZDProcessGraphModelDoc) ||
        !((ZDProcessGraphModelDoc*)GetDocument())->GetModel() || !pComp)
    {
        return NULL;
    }

    CODSymbolComponent* pSymbol = NULL;

    if (ISA(pComp, ZBSymbol) && !((ZBSymbol*)pComp)->IsLocal())
    {
        // Find local symbol
        pSymbol = reinterpret_cast<CODSymbolComponent*>(((ZBSymbol*)pComp)->GetLocalSymbol());
    }
    else if (ISA(pComp, ZBLinkSymbol) && !((ZBLinkSymbol*)pComp)->IsLocal())
    {
        // Find local symbol
        pSymbol = reinterpret_cast<CODSymbolComponent*>(((ZBLinkSymbol*)pComp)->GetLocalSymbol());
    }

    // If found, ensure the symbol visible
    if (pSymbol)
    {
        return EnsureSymbolVisible(pSymbol);
    }

    return NULL;
}

ZIProcessGraphModelViewport* ZDProcessGraphModelController::BrowseSymbolModel(ZBSymbol* pSymbol)
{
    if (GetDocument())
    {
        ZDProcessGraphModelMdl* pSymbolModel = NULL;

        // If can't activate a view with model's name, create a new view
        if (ISA(GetDocument(), ZDProcessGraphModelDoc))
        {
            pSymbolModel = ((ZDProcessGraphModelDoc*)GetDocument())->GetModel()->GetSymbolModel(pSymbol);
        }

        if (pSymbolModel)
        {
            ZIProcessGraphModelViewport* pViewport = BrowseModel(pSymbolModel, pSymbolModel->GetParent());

            if (pViewport)
            {
                CODComponentSet CompSet;
                CompSet.Add(pSymbol);
                pViewport->CenterOnComponents(&CompSet);
            }

            return reinterpret_cast<ZIProcessGraphModelViewport*>(pViewport);
        }
    }

    return NULL;
}

ZIProcessGraphModelViewport* ZDProcessGraphModelController::BrowseLinkSymbolModel(ZBLinkSymbol* pSymbol)
{
    if (GetDocument())
    {
        ZDProcessGraphModelMdl* pSymbolModel = NULL;

        // If can't activate a view with model's name, create a new view
        if (ISA(GetDocument(), ZDProcessGraphModelDoc))
        {
            pSymbolModel = ((ZDProcessGraphModelDoc*)GetDocument())->GetModel()->GetLinkSymbolModel(pSymbol);
        }

        if (pSymbolModel)
        {
            ZIProcessGraphModelViewport* pViewport = BrowseModel(pSymbolModel, pSymbolModel->GetParent());

            if (pViewport)
            {
                CODComponentSet CompSet;
                CompSet.Add(pSymbol);
                pViewport->CenterOnComponents(&CompSet);
            }

            return reinterpret_cast<ZIProcessGraphModelViewport*>(pViewport);
        }
    }

    return NULL;
}

ZIProcessGraphModelViewport* ZDProcessGraphModelController::OpenSymbol(CODComponent* pComp)
{
    if (pComp != NULL && ISA(pComp, ZBSymbol))
    {
        ZBSymbol*                    pSymbol = (ZBSymbol*)pComp;
        ZIProcessGraphModelView*    pView = GetView();

        if (pView)
        {
            // Is there any child model
            if (pSymbol->GetChildModel() == NULL)
            {
                pSymbol->CreateEmptyChildModel(GetModel());
            }

            // End the text edit before going into the new model
            EndTextEdit(0, m_savedEditPosition);

            ZIProcessGraphModelViewport* pVp =
                BrowseModel((ZDProcessGraphModelMdl*)pSymbol->GetChildModel(), GetModel());

            // When open a new model, unselect all symbols    
            UnselectAllComponents();

            // Returns the viewport
            return pVp;
        }
    }

    return NULL;
}

ZIProcessGraphModelViewport* ZDProcessGraphModelController::OpenPage(ZDProcessGraphPage* pPage)
{
    if (pPage)
    {
        ZIProcessGraphModelView* pView = GetView();

        if (pView)
        {
            // Is there any child model
            if (pPage->GetpModel() != NULL)
            {
                ZIProcessGraphModelViewport* pVp =
                    BrowseModel((ZDProcessGraphModelMdl*)pPage->GetpModel(),
                                reinterpret_cast<ZDProcessGraphModelMdl*>(pPage->GetpModel())->GetParent());

                // When open a new model, unselect all symbols    
                UnselectAllComponents();

                // Returns the viewport
                return pVp;
            }
        }
    }

    return NULL;
}

ZIProcessGraphModelViewport* ZDProcessGraphModelController::BrowseModel(ZDProcessGraphModelMdl* pModel,
                                                                        ZDProcessGraphModelMdl* pParentModel)
{
    if (!GetDocument() || !pModel)
    {
        return NULL;
    }

    // If can't activate a view with model's name, create a new view
    if (ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        CView *pView = ((ZDProcessGraphModelDoc*)GetDocument())->ActivateView(pModel->GetAbsolutePath());

        if (!pView)
        {
            // From the model, create a view
            return CreateViewFromModel(pModel, pParentModel);
        }
        else
        {
            if (ISA(pView, ZIProcessGraphModelView))
            {
                return reinterpret_cast<ZIProcessGraphModelView*>(pView)->GetViewport();
            }
        }
    }

    return NULL;
}

ZIProcessGraphModelViewport* ZDProcessGraphModelController::CreateViewFromModel(ZDProcessGraphModelMdl* pModel,
                                                                                ZDProcessGraphModelMdl* pParentModel)
{
    ZIProcessGraphModelView* pView = GetView();

    if (pView)
    {
        if (BrowseInSameWindow())
        {
            // Clear the selection
            ClearSelection();

            // Set the model
            pView->SetModel(pModel, true);

            // Refresh the views
            pView->GetDocument()->UpdateAllViews(pView);

            // Force the refresh of the active window title
            if (AfxGetMainWnd() && ISA(AfxGetMainWnd(), CFrameWnd) &&
                dynamic_cast<CFrameWnd*>(AfxGetMainWnd())->GetActiveFrame())
            {
                dynamic_cast<CFrameWnd*>(AfxGetMainWnd())->GetActiveFrame()->OnUpdateFrameTitle(TRUE);
            }

            // Sets the right controller
            pModel->SetController(this);

            // Move to 0,0
            pView->GetViewport()->SetLogOrigin(0, 0);

            // Return the viewport
            return pView->GetViewport();
        }
        else
        {
            CFrameWnd* pFrame =
                pView->GetDocument()->GetDocTemplate()->CreateNewFrame((CDocument*)pView->GetDocument(), NULL);

            // Call IntitialUpdateFrame after creating a new frame with CreateNewFrame. 
            // Calling this function causes the views in that frame window to receive 
            // their OnInitialUpdate calls. 
            pView->GetDocument()->GetDocTemplate()->InitialUpdateFrame(pFrame, (CDocument*)pView->GetDocument());

            if (pFrame->GetActiveView() && ISA(pFrame->GetActiveView(), ZIProcessGraphModelView))
            {
                // Set the model
                ((ZIProcessGraphModelView*)pFrame->GetActiveView())->SetModel(pModel);

                // Sets the right controller
                if (reinterpret_cast<ZIProcessGraphModelView*>(pFrame->GetActiveView())->GetViewport())
                {
                    pModel->SetController(reinterpret_cast<ZIProcessGraphModelView*>(pFrame->GetActiveView())->GetViewport()->GetModelController());
                }

                // Move to 0,0
                pView->GetViewport()->SetLogOrigin(0, 0);

                pFrame->OnUpdateFrameTitle(TRUE);

                return reinterpret_cast<ZIProcessGraphModelView*>(pFrame->GetActiveView())->GetViewport();
            }
        }
    }

    return NULL;
}

void ZDProcessGraphModelController::RefreshModelTree()
{
    // Send notification message
    AfxGetMainWnd()->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED);
    AfxGetMainWnd()->SendMessageToDescendants(UM_UNITMODELHASCHANGED);
}

void ZDProcessGraphModelController::ReDrawComponent(CODComponent& Comp)
{
    // Update symbols
    CODComponentSet CompSet;
    CompSet.Add(&Comp);
    GetCanvasVp()->UpdateComponents(&CompSet);
}

void ZDProcessGraphModelController::ReDrawComponentSet(CODComponentSet& Set)
{
    // Update symbols
    GetCanvasVp()->UpdateComponents(&Set);
}

void ZDProcessGraphModelController::SelectAllComponents()
{
    // Run trough all components and change the select all flag
    // Process the model components
    CODComponentSet* pSet = GetModel()->GetComponents();

    for (int i = 0; i < pSet->GetSize(); ++i)
    {
        CODComponent* pComp = pSet->GetAt(i);

        // Let select the symbol
        CODEditProperties* pPropEdit = (CODEditProperties*)pComp->GetProperty(OD_PROP_EDIT);

        if (pPropEdit)
        {
            CODEditProperties PropEdit(*pPropEdit);
            PropEdit.SetCanSelect(TRUE);
            pComp->SetProperty(&PropEdit);
        }
    }

    // Just call the select all function
    SelectAll();
    NotifySymbolSelected(NULL);
}

void ZDProcessGraphModelController::UnselectAllComponents()
{
    /* Clear selection list. */
    ClearSelection();

    // Update the viewport
    ASSERT(GetCanvasVp());
    GetCanvasVp()->UpdateAll();

    NotifySymbolSelected(NULL);
}

void ZDProcessGraphModelController::SelectComponent(CODComponent& Comp)
{
    m_setSelection.Add(&Comp);
    ReDrawComponent(Comp);
    NotifySymbolSelected(&Comp);
}

void ZDProcessGraphModelController::SelectComponentSet(CODComponentSet& Set)
{
    CODComponentIterator    i(&Set);
    CODComponent*            pComp;

    for (pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext())
    {
        m_setSelection.Add(pComp);
    }

    ReDrawComponentSet(Set);
}

void ZDProcessGraphModelController::UnselectComponent(CODComponent& Comp)
{
    CODComponentSet Set;
    Set.Add(&Comp);
    Deselect(&Set);

    // Update the viewport
    ASSERT(GetCanvasVp());
    GetCanvasVp()->UpdateAll();

    NotifySymbolSelected(NULL);
}

void ZDProcessGraphModelController::UnselectComponentSet(CODComponentSet& Set)
{
    Deselect(&Set);
}

bool ZDProcessGraphModelController::IsComponentSelected(CODComponent& Comp)
{
    CODComponentIterator    i(&m_setSelection);
    CODComponent*            pComp;

    for (pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext())
    {
        if (pComp == &Comp)
        {
            return true;
        }
    }

    return false;
}

void ZDProcessGraphModelController::CopySelectionToSet()
{
    ClearSelectionToSet();

    CODComponentIterator    IterSelection(&m_setSelection);
    CODComponent*            pSrcComp;

    for (pSrcComp = IterSelection.GetFirst(); pSrcComp != NULL; pSrcComp = IterSelection.GetNext())
    {
        m_setCopy.Add(pSrcComp);
    }
}

// Proceed the drop of an object to the model
bool ZDProcessGraphModelController::DropItemToModel(CObject* pObj, CPoint pt)
{
    if (pObj && ISA(pObj, ZBSymbol))
    {
        // Set the insert symbol to a duplicate of the
        m_pInsert = ((ZBSymbol*)pObj)->Dup();

        ClearSelectionToSet();
        m_setCopy.Add(m_pInsert);

        VpLPtoDP(&pt);
        InsertSymbol(0, pt);

        return true;
    }
    else if (pObj && ISA(pObj, ZBLinkSymbol))
    {
        // Set the insert symbol to a duplicate of the
        m_pInsert = ((ZBLinkSymbol*)pObj)->Dup();

        ClearSelectionToSet();
        m_setCopy.Add(m_pInsert);

        VpLPtoDP(&pt);
        InsertSymbol(0, pt);

        return true;
    }

    return false;
}

// Check if the drop can be done successfuly on the model
bool ZDProcessGraphModelController::AcceptDropItemToModel(CObject* pObj, CPoint pt)
{
    // If it is a symbol
    if (pObj && ISA(pObj, ZBSymbol))
    {
        return true;
    }

    // If it is a link symbol
    if (pObj && ISA(pObj, ZBLinkSymbol))
    {
        return true;
    }

    return false;
}

// Proceed the drop of an object
bool ZDProcessGraphModelController::DropItem(CObject* pObj, CPoint pt)
{
    // If an object to drop
    if (pObj)
    {
        CPoint point(pt);
        VpDPtoLP(&point);

        CODComponent* pCompHit = GetCanvasVp()->ComponentHitTest(point);

        // If no object hit, drag symbol on the model
        if (!pCompHit)
        {
            return DropItemToModel(pObj, pt);
        }

        // If it is a label, assign the right owner symbol
        if (ISA(pCompHit, CODLabelComponent))
        {
            // Select the symbol behind
            // JMR-MODIF - Le 2 juin 2005 - Conversion explicite remplace le cast. La conversion explicite
            // donne un résultat identique sur l'objet casté en classe de base, tandis que l'ancienne
            // implémentation (dynamic_cast) provoque une exception dans le compilateur VC.NET
            CODLabelComponent* m_pTmpCompHit = (CODLabelComponent*)pCompHit;
            pCompHit = m_pTmpCompHit->GetOwner();
            //            pCompHit = dynamic_cast<CODLabelComponent*>(pCompHit)->GetOwner();
        }

        bool Result = false;

        // ***************************************************************************************************
        // JMR-MODIF - Le 29 novembre 2006 - Désélectionne tous les symboles plutôt que le symbole unique.

/*        // First, unselect the symbol if selected
        bool UnselectSymbol = false;

        if ( IsComponentSelected( *pCompHit ) )
        {
            UnselectSymbol = true;
            UnselectComponent( *pCompHit );
        }*/

        UnselectAllComponents();
        // ***************************************************************************************************

        if (ISA(pCompHit, ZBSymbol))
        {
            Result = ((ZBSymbol*)pCompHit)->DropItem(pObj, pt);
        }
        else if (ISA(pCompHit, ZBLinkSymbol))
        {
            Result = ((ZBLinkSymbol*)pCompHit)->DropItem(pObj, pt);
        }

        // ***************************************************************************************************
        // JMR-MODIF - Le 29 novembre 2006 - Sélectionne uniquement le symbole concerné par le glisser-coller.

/*        // Second, reselect the same symbol if necessary
        if ( UnselectSymbol )
        {
            SelectComponent( *pCompHit );
        }*/

        SelectComponent(*pCompHit);
        NotifySymbolSelected(pCompHit);
        // ***************************************************************************************************

        // Update the symbol
        CODComponentSet CompSet;
        CompSet.Add(pCompHit);
        GetVp()->DrawComponents(&CompSet);

        return Result;
    }

    return false;
}

// Check if the drop can be done successfuly
bool ZDProcessGraphModelController::AcceptDropItem(CObject* pObj, CPoint pt)
{
    // If an object to drop
    if (pObj)
    {
        VpDPtoLP(&pt);
        CODComponent* pCompHit = GetCanvasVp()->ComponentHitTest(pt);

        // If no object hit, test the drop on the model
        if (!pCompHit)
        {
            return AcceptDropItemToModel(pObj, pt);
        }

        // If it is a label, assign the right owner symbol
        if (ISA(pCompHit, CODLabelComponent))
        {
            // Select the symbol behind
            // JMR-MODIF - Le 2 juin 2005 - Conversion explicite remplace le cast. La conversion explicite
            // donne un résultat identique sur l'objet casté en classe de base, tandis que l'ancienne
            // implémentation (dynamic_cast) provoque une exception dans le compilateur VC.NET
            CODLabelComponent* m_pTmpCompHit = (CODLabelComponent*)pCompHit;
            pCompHit = m_pTmpCompHit->GetOwner();
            //            pCompHit = dynamic_cast<CODLabelComponent*>(pCompHit)->GetOwner();
        }

        if (pCompHit && ISA(pCompHit, ZBSymbol))
        {
            return ((ZBSymbol*)pCompHit)->AcceptDropItem(pObj, pt);
        }
        else if (pCompHit && ISA(pCompHit, ZBLinkSymbol))
        {
            return ((ZBLinkSymbol*)pCompHit)->AcceptDropItem(pObj, pt);
        }
    }

    return false;
}

void ZDProcessGraphModelController::DeleteComponents(CODComponentSet* pCompSet)
{
    if (pCompSet)
    {
        CODComponentSet            setUpdate;
        CODComponentIterator    i(pCompSet);
        CODComponent            *pComp;

        for (pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext())
        {
            // Retrieve the owner model
            CODComponent* pParentComp = pComp->GetParent();
            CODModel* pOwnerModel = NULL;

            while (pParentComp)
            {
                // If a model, return it
                if (pParentComp && ISA(pParentComp, CODModel))
                {
                    pOwnerModel = dynamic_cast<CODModel*>(pParentComp);
                    break;
                }

                // Otherwise retreive its parent
                pParentComp = pParentComp->GetParent();
            }

            // If no owner model, next component
            if (!pOwnerModel)
            {
                continue;
            }

            // Process the remove of a component
            CODComponentSet set;
            set.Add(pComp);
            RemoveReferenceSymbol(&set);

            // Remove the child first
            pOwnerModel->RemoveChild(pComp);
        }

        // Advise on the selection change
        if (setUpdate.GetSize() > 0)
        {
            OnSelectionChange(&setUpdate);
        }

        // Update the entire viewport
        GetViewport()->UpdateAll();
    }
}

void ZDProcessGraphModelController::DeleteComponent(CODComponent* pComp)
{
    if (pComp)
    {
        // Add it to the set
        CODComponentSet set;
        set.Add(pComp);

        // Call the delete component function for a set
        DeleteComponents(&set);
    }
}

void ZDProcessGraphModelController::EndLink(UINT nFlags, CPoint ptDev)
{
    // Save the inserted component pointer
    CODComponent* pComp = m_pInsert;

    CODController::EndLink(nFlags, ptDev);

    // Reset the current command id
    m_CurrentCommandID = 0;

    // Set flag for modification
    if (GetDocument())
    {
        GetDocument()->SetModifiedFlag(TRUE);
    }

    if (pComp && ISA(pComp, ZBLinkSymbol))
    {
        // Assign the path
        ((ZBLinkSymbol*)pComp)->SetAbsolutePath(GetModel()->GetAbsolutePath());

        // Assign by default the unique reference number
        if (GetRootModel())
        {
            // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
            int RefNumber = GetRootModel()->GetNextAvailableReferenceNumber();

            // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
//            ( (ZBLinkSymbol*)pComp )->SetSymbolReferenceNumber( GetRootModel()->GetNextAvailableReferenceNumber() );
            ((ZBLinkSymbol*)pComp)->SetSymbolReferenceNumber(RefNumber);

            // Retreive the next available name
            ZUBuildSymbolNewName BuildNewName;

            // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
            ((ZBLinkSymbol*)pComp)->SetSymbolName(BuildNewName.GetNextAvailableSymbolName(*GetRootModel(),
                                                                                          RefNumber));
        }

        // Call for the PostCreation
        if (!((ZBLinkSymbol*)pComp)->OnPostCreation(GetModel(), this))
        {
            // Destroy the object
            CancelLink(nFlags, ptDev);
            return;
        }

        // Refresh the attribute area and redraw the symbol
        ((ZBLinkSymbol*)pComp)->RefreshAttributeAreaText(true);

        if (m_NewSymbolCreated && ((ZBLinkSymbol*)pComp)->IsLocal())
        {
            // Save the position first
            m_savedEditPosition = ptDev;

            // Edit name directly
            EditName(pComp);
        }

        // Notify new selection
        NotifySymbolSelected(pComp);

        // Call the virtual method on symbol added
        OnSymbolAdded(&m_setSymbolAddedSet);

        // Reset the creation flag
        m_NewSymbolCreated = false;
    }
}

// Insert a new symbol
void ZDProcessGraphModelController::InsertSymbol(UINT nFlags, CPoint ptDev)
{
    if (m_pInsert)
    {
        ZDProcessGraphModelController::InsertSymbol(m_pInsert, nFlags, ptDev, true);
    }
}

// Insert a new symbol
CODComponent* ZDProcessGraphModelController::InsertSymbol(UINT nFlags, CPoint ptDev, bool IncludePostCreation)
{
    return ZDProcessGraphModelController::InsertSymbol(m_pInsert, nFlags, ptDev, IncludePostCreation);
}

// Insert a new symbol
CODComponent* ZDProcessGraphModelController::InsertSymbol(CODComponent*    pComp,
                                                          UINT                nFlags,
                                                          CPoint            ptDev,
                                                          bool                IncludePostCreation)
{
    CODController::InsertSymbol(nFlags, ptDev);

    // Set flag for modification
    if (GetDocument())
    {
        GetDocument()->SetModifiedFlag(TRUE);
    }

    // Reset the current command id
    m_CurrentCommandID = 0;

    if (pComp && ISA(pComp, ZBSymbol))
    {
        // Assign the path
        ((ZBSymbol*)pComp)->SetAbsolutePath(GetModel()->GetAbsolutePath());

        // Assign by default the unique reference number
        if (GetRootModel())
        {
            // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
            int RefNumber = GetRootModel()->GetNextAvailableReferenceNumber();

            // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
//            ( (ZBSymbol*)pComp )->SetSymbolReferenceNumber( GetRootModel()->GetNextAvailableReferenceNumber() );
            ((ZBSymbol*)pComp)->SetSymbolReferenceNumber(RefNumber);

            // JMR-MODIF - Le 22 mars 2006 - Teste si le symbole est un symbole générique.
            if (((ZBSymbol*)pComp)->IsGeneric() == TRUE)
            {
                // JMR-MODIF - Le 22 mars 2006 - Si le symbole est générique, attribue un autre type de nom.
                ZUBuildGenericSymbolNewName BuildNewName;
                ((ZBSymbol*)pComp)->SetSymbolName(BuildNewName.GetNextAvailableSymbolName(*GetRootModel()));
            }
            else
            {
                // Retreive the next available name
                ZUBuildSymbolNewName BuildNewName;

                // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
                ((ZBSymbol*)pComp)->SetSymbolName(BuildNewName.GetNextAvailableSymbolName(*GetRootModel(),
                                                                                          RefNumber));
            }
        }

        if (IncludePostCreation)
        {
            // Call for the PostCreation
            if (!((ZBSymbol*)pComp)->OnPostCreation(GetModel(), this))
            {
                // Remove the object
                DeleteComponent(pComp);

                // Cancel the selection on the old object
                UnselectAllComponents();
                ClearSymbolAddedSet();
                ClearSelectionToSet();

                return NULL;
            }
        }

        // Refresh the attribute area and redraw the symbol
        ((ZBSymbol*)pComp)->RefreshAttributeAreaText(true);

        if (m_NewSymbolCreated && ((ZBSymbol*)pComp)->IsLocal())
        {
            // Save the position first
            m_savedEditPosition = ptDev;

            // Edit name directly
            EditName(pComp);
        }

        // Notify new selection
        NotifySymbolSelected(pComp);

        // Call the virtual method on symbol added
        OnSymbolAdded(&m_setSymbolAddedSet);

        // Reset the creation flag
        m_NewSymbolCreated = false;
    }
    // JMR-MODIF - Le 4 avril 2006 - Code de gestion des zones de textes.
    else if (pComp && ISA(pComp, ZBTextZone))
    {
        // Initialise le style de la zone de texte.
        ((ZBTextZone*)pComp)->InitializeStyle();

        // Redessine la zone de texte.
        CODComponent* pMdlComp = ((ZBTextZone*)pComp)->GetParent();

        if (pMdlComp && ISA(pMdlComp, ZDProcessGraphModelMdl))
        {
            dynamic_cast<ZDProcessGraphModelMdl*>(pMdlComp)->ReDrawComponent(*((ZBTextZone*)pComp));
        }

        // Notifie la nouvelle sélection.
        NotifySymbolSelected(pComp);

        // Appelle la méthode virtuelle OnSymbolAdded.
        OnSymbolAdded(&m_setSymbolAddedSet);

        m_NewSymbolCreated = false;
    }

    return pComp;
}

CODDeleteCommand* ZDProcessGraphModelController::ExecuteDeleteCommand(CODComponentSet* pCompSet)
{
    if (pCompSet && CutCommand == false)
    {
        // First, run through all components and call the PreDelete method
        // If return false, remove the component from the set
        for (int i = 0; i < pCompSet->GetSize(); ++i)
        {
            CODComponent* pComp = pCompSet->GetAt(i);

            // Test if a symbol
            if (pComp && ISA(pComp, ZBSymbol))
            {
                // Test if predelete returns nok
                if (!dynamic_cast<ZBSymbol*>(pComp)->OnPreDelete(GetModel(), this))
                {
                    // Remove component from the set
                    pCompSet->RemoveAt(i);
                    --i;
                }
            }
            // Test if a linksymbol
            else if (pComp && ISA(pComp, ZBLinkSymbol))
            {
                // Test if predelete returns nok
                if (!dynamic_cast<ZBLinkSymbol*>(pComp)->OnPreDelete(GetModel(), this))
                {
                    // Remove component from the set
                    pCompSet->RemoveAt(i);
                    --i;
                }
            }
        }

        // Now, we have only the symbol we really want to delete
        CODComponentSet* setCopy = GetSelection();
        RemoveReferenceSymbol(setCopy);
    }

    return CODController::ExecuteDeleteCommand(pCompSet);
}

CODInsertCommand* ZDProcessGraphModelController::ExecuteInsertCommand(CODComponent*    pComp,
                                                                      const BOOL        bAllowDuplicates /*= TRUE*/)
{
    // Copy selected components first if something
    if (m_setSelection.GetSize() != 0)
    {
        CopySelectionToSet();
    }

    CODInsertCommand* pCmd = CODController::ExecuteInsertCommand(pComp, bAllowDuplicates);

    ClearSymbolAddedSet();
    CopySymbolToSymbolAddedSet(pComp);

    return pCmd;
}

CODInsertCommand* ZDProcessGraphModelController::ExecuteInsertCommand(CODComponentSet*    pCompSet,
                                                                      const BOOL        bAllowDuplicates /*= TRUE*/)
{
    // Copy selected components first if something
    if (m_setSelection.GetSize() != 0)
    {
        CopySelectionToSet();
    }

    CODInsertCommand* pCmd = CODController::ExecuteInsertCommand(pCompSet, bAllowDuplicates);

    ClearSymbolAddedSet();
    CopySymbolsToSymbolAddedSet(pCompSet);

    return pCmd;
}

CODLinkCommand* ZDProcessGraphModelController::ExecuteLinkCommand(const CODPointArray&    pointArray,
                                                                  CODPortComponent*    pSourcePort,
                                                                  CODPortComponent*    pTargetPort,
                                                                  CODEndpoint*            pSourceEndpoint /*= NULL*/,
                                                                  CODEndpoint*            pTargetEndpoint /*= NULL*/)
{
    CODLinkCommand* pCmd = CODController::ExecuteLinkCommand(pointArray,
                                                             pSourcePort,
                                                             pTargetPort,
                                                             pSourceEndpoint,
                                                             pTargetEndpoint);

    return pCmd;
}

CODLinkCommand* ZDProcessGraphModelController::ExecuteLinkCommand(CODLinkComponent*    pLinkComp,
                                                                  const CODPointArray&    pointArray,
                                                                  CODPortComponent*    pSourcePort,
                                                                  CODPortComponent*    pTargetPort)
{
    CODLinkCommand* pCmd = CODController::ExecuteLinkCommand(pLinkComp, pointArray, pSourcePort, pTargetPort);

    ClearSymbolAddedSet();
    CopySymbolToSymbolAddedSet(pLinkComp);

    return pCmd;
}

CODLinkCommand* ZDProcessGraphModelController::ExecuteLinkCommand(CODLinkComponent* pLinkComp,
                                                                  CODPortComponent* pSourcePort,
                                                                  CODPortComponent* pTargetPort)
{
    CODLinkCommand* pCmd = CODController::ExecuteLinkCommand(pLinkComp, pSourcePort, pTargetPort);

    ClearSymbolAddedSet();
    CopySymbolToSymbolAddedSet(pLinkComp);

    return pCmd;
}

void ZDProcessGraphModelController::DetermineReferencedSymbol(CODComponentSet* pCompSet)
{
    ASSERT(GetModel()->GetRoot());

    // For each symbol coming from the source of copy
    // Locate the symbol copied
    CODComponentIterator srcSymbolIter(&m_setCopy);
    CODComponent* pSrcComp;

    for (pSrcComp = srcSymbolIter.GetFirst(); pSrcComp != NULL; pSrcComp = srcSymbolIter.GetNext())
    {
        if (pSrcComp && ISA(pSrcComp, ZBSymbol))
        {
            CODComponentIterator i(pCompSet);
            CODComponent* pComp;

            for (pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext())
            {
                if (pComp && ISA(pComp, ZBSymbol))
                {
                    if (!((ZBSymbol*)pSrcComp)->GetSymbolName().IsEmpty() &&
                        ((ZBSymbol*)pSrcComp)->GetSymbolName() == ((ZBSymbol*)pComp)->GetSymbolName())
                    {
                        ((ZBSymbol*)pComp)->CopySymbolDefinitionFrom((ZBSymbol&)*pSrcComp);

                        // Sets a new reference number
                        ((ZBSymbol*)pComp)->SetSymbolReferenceNumber(GetModel()->GetRoot()->GetNextAvailableReferenceNumber());

                        // Assign the reference
                        ((ZBSymbol*)pComp)->AssignReferenceSymbol((ZBSymbol*)pSrcComp);

                        // JMR-MODIF - Le 7 février 2006 - Ajout du code de marquage des copies.
                        ((ZBSymbol*)pComp)->SetIsCopy();
                    }
                }
            }
        }
        else if (pSrcComp && ISA(pSrcComp, ZBLinkSymbol))
        {
            CODComponentIterator i(pCompSet);
            CODComponent* pComp;

            for (pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext())
            {
                if (pComp && ISA(pComp, ZBLinkSymbol))
                {
                    if (!((ZBLinkSymbol*)pSrcComp)->GetSymbolName().IsEmpty() &&
                        ((ZBLinkSymbol*)pSrcComp)->GetSymbolName() == ((ZBLinkSymbol*)pComp)->GetSymbolName())
                    {
                        ((ZBLinkSymbol*)pComp)->CopySymbolDefinitionFrom((ZBLinkSymbol&)*pSrcComp);

                        // Sets a new reference number
                        ((ZBLinkSymbol*)pComp)->SetSymbolReferenceNumber(GetModel()->GetRoot()->GetNextAvailableReferenceNumber());

                        // Assign the reference
                        ((ZBLinkSymbol*)pComp)->AssignReferenceSymbol((ZBLinkSymbol*)pSrcComp);

                        // JMR-MODIF - Le 7 février 2006 - Ajout du code de marquage des copies.
                        ((ZBLinkSymbol*)pComp)->SetIsCopy();
                    }
                }
            }
        }
    }

    // Update symbols
    GetVp()->DrawComponents(pCompSet);
}

void ZDProcessGraphModelController::RemoveReferenceSymbol(CODComponentSet* pCompSet)
{
    // Call RemoveReferenceSymbol to detach observers
    CODComponentIterator i(pCompSet);
    CODComponent* pComp;

    for (pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext())
    {
        if (pComp && (ISA(pComp, ZBSymbol) || ISA(pComp, ZBLinkSymbol)))
        {
            if (ISA(pComp, ZBSymbol))
            {
                ((ZBSymbol*)pComp)->RemoveReferenceSymbol();
            }
            else if (ISA(pComp, ZBLinkSymbol))
            {
                ((ZBLinkSymbol*)pComp)->RemoveReferenceSymbol();
            }

            // Build the message
            ZBDocObserverMsg DocMsg(ZBDocObserverMsg::RemoveElement, NULL, GetModel(), (ZBSymbol*)pComp);
            AfxGetMainWnd()->SendMessageToDescendants(UM_ELEMENTREMOVEDDOCUMENTMODEL, 0, (LPARAM)&DocMsg);
        }
    }
}

void ZDProcessGraphModelController::OnSymbolAdded(CODComponentSet* pCompSet)
{
    DetermineReferencedSymbol(pCompSet);

    ASSERT(GetDocument());
    ASSERT(ISA(GetDocument(), ZDProcessGraphModelDoc));

    ZDProcessGraphModelDoc* pDoc = dynamic_cast<ZDProcessGraphModelDoc*>(GetDocument());

    // Notify observers for all added symbols
    CODComponentIterator i(pCompSet);
    CODComponent* pComp;

    for (pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext())
    {
        if (pComp && (ISA(pComp, ZBSymbol) || ISA(pComp, ZBLinkSymbol)))
        {
            // Build the message
            ZBDocObserverMsg DocMsg(ZBDocObserverMsg::AddElement,
                                    NULL,
                                    GetModel(),
                                    reinterpret_cast<CODSymbolComponent*>(pComp));

            AfxGetMainWnd()->SendMessageToDescendants(UM_ELEMENTADDEDDOCUMENTMODEL, 0, (LPARAM)&DocMsg);

            // Call the utility class for manipulating dynamic attributes
            // and assign required dynamic properties on new symbol
            if (pDoc->HasDynamicPropertiesManager())
            {
                if (ISA(pComp, ZBSymbol))
                {
                    ZUDynamicAttributesManipulator::AssignDynamicPropertyOnSymbol(pDoc->GetDynamicPropertiesManager(), dynamic_cast<ZBSymbol*>(pComp));
                }
                else
                {
                    ZUDynamicAttributesManipulator::AssignDynamicPropertyOnSymbol(pDoc->GetDynamicPropertiesManager(), dynamic_cast<ZBLinkSymbol*>(pComp));
                }
            }
        }
    }
}

void ZDProcessGraphModelController::OnSymbolDuplicated(CODComponentSet* pCompSet)
{
    // Run through added elements and change their names.
    // If symbols have child components, then asks the user to duplicate sub-components
    // Notify observers for all added symbols
    CODComponentIterator    i(pCompSet);
    CODComponent*            pComp;

    int iPos = 0;
    int CountCopySet = m_setCopy.GetSize();

    for (pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext(), ++iPos)
    {
        if (pComp && (ISA(pComp, ZBSymbol) || ISA(pComp, ZBLinkSymbol)))
        {
            if (ISA(pComp, ZBSymbol))
            {
                if (CountCopySet > iPos)
                {
                    // Retreive the corresponding source symbol
                    CODComponent* pSrcComp = m_setCopy.GetAt(iPos);

                    if (pSrcComp && ISA(pSrcComp, ZBSymbol))
                    {
                        ((ZBSymbol*)pComp)->CopySymbolDefinitionFrom(*((ZBSymbol*)pSrcComp));
                    }
                }

                // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
                int RefNumber = GetRootModel()->GetNextAvailableReferenceNumber();

                // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
//                ( (ZBSymbol*)pComp )->SetSymbolReferenceNumber( GetRootModel()->GetNextAvailableReferenceNumber() );
                ((ZBSymbol*)pComp)->SetSymbolReferenceNumber(RefNumber);

                // Retreive the next available name
                ZUBuildSymbolNewName BuildNewName(((ZBSymbol*)pComp)->GetSymbolName());

                // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
                ((ZBSymbol*)pComp)->SetSymbolName(BuildNewName.GetNextAvailableSymbolName(*GetRootModel(),
                                                                                          RefNumber));
            }
            else if (ISA(pComp, ZBLinkSymbol))
            {
                if (CountCopySet > iPos)
                {
                    // Retreive the corresponding source symbol
                    CODComponent* pSrcComp = m_setCopy.GetAt(iPos);

                    if (pSrcComp && ISA(pSrcComp, ZBLinkSymbol))
                    {
                        ((ZBLinkSymbol*)pComp)->CopySymbolDefinitionFrom(*((ZBLinkSymbol*)pSrcComp));
                    }
                }

                // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
                int RefNumber = GetRootModel()->GetNextAvailableReferenceNumber();

                // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
//                ( (ZBLinkSymbol*)pComp )->SetSymbolReferenceNumber( GetRootModel()->GetNextAvailableReferenceNumber() );
                ((ZBLinkSymbol*)pComp)->SetSymbolReferenceNumber(RefNumber);

                // Retreive the next available name
                ZUBuildSymbolNewName BuildNewName(((ZBLinkSymbol*)pComp)->GetSymbolName());

                // JMR-MODIF - Le 23 mai 2006 - La génération du nom et la ref. interne utilisent le même paramètre.
                ((ZBLinkSymbol*)pComp)->SetSymbolName(BuildNewName.GetNextAvailableSymbolName(*GetRootModel(),
                                                                                              RefNumber));
            }
        }
    }
}

// **********************************************************************************************************
// *                                 ZDProcessGraphModelController message handlers                            *
// **********************************************************************************************************

void ZDProcessGraphModelController::ApplyFormatToSymbol(CODComponent* pComp)
{
    // No object to format
    if (!pComp)
    {
        return;
    }

    // Not to the same object
    if (pComp == m_pFormatPainterSymbol)
    {
        return;
    }

    if (pComp && ISA(pComp, ZBSymbol))
    {
        dynamic_cast<ZBSymbol*>(pComp)->ApplyFormatFromObject(*m_pFormatPainterSymbol);
    }
    else if (pComp && ISA(pComp, ZBLinkSymbol))
    {
        dynamic_cast<ZBLinkSymbol*>(pComp)->ApplyFormatFromObject(*m_pFormatPainterSymbol);
    }
}

CMenu* ZDProcessGraphModelController::CreateContextMenu()
{
    if (m_pRightSubMenu)
    {
        return m_pRightSubMenu;
    }

    return CODController::CreateContextMenu();
}

// JMR-MODIF - Le 24 décembre 2006 - Permet de rafraîchir l'affichage des propriétés des éléments sélectionnés.
void ZDProcessGraphModelController::RefreshSelectionProperties()
{
    // L'opération n'est possible que si un seul symbole est sélectionné.
    if (GetSelection()->GetSize() == 1)
    {
        if (GetSelection()->GetAt(0) != NULL)
        {
            NotifySymbolSelected(GetSelection()->GetAt(0));
        }
    }
}

void ZDProcessGraphModelController::NotifySymbolSelected(CODComponent* pComp)
{
    // If we are in FormatPainter, then forward the process to the ApplyFormatToSymbol function
    if (m_IsInFormatPainter)
    {
        ApplyFormatToSymbol(pComp);

        return;
    }

    CDocument* pDoc = GetDocument();

    if (pComp && ISA(pComp, ZBSymbol))
    {
        ZBSymbolObserverMsg        SymMsg(ZBSymbolObserverMsg::ElementSelected, dynamic_cast<ZBSymbol*>(pComp));
        ZBPropertyObserverMsg    Msg(dynamic_cast<ZBSymbol*>(pComp));

        // Notify direct observers first
        NotifyAllObservers(&Msg);
        NotifyAllObservers(&SymMsg);

        // And then document notify all observers
        if (ISA(pDoc, ZDProcessGraphModelDoc))
        {
            reinterpret_cast<ZDProcessGraphModelDoc*>(pDoc)->NotifyAllObservers(&Msg);
            reinterpret_cast<ZDProcessGraphModelDoc*>(pDoc)->NotifyAllObservers(&SymMsg);
        }
    }
    else if (pComp && ISA(pComp, ZBLinkSymbol))
    {
        ZBSymbolObserverMsg        SymMsg(ZBSymbolObserverMsg::ElementSelected, dynamic_cast<ZBLinkSymbol*>(pComp));
        ZBPropertyObserverMsg    Msg(dynamic_cast<ZBLinkSymbol*>(pComp));

        // Notify direct observers first
        NotifyAllObservers(&Msg);
        NotifyAllObservers(&SymMsg);

        // And then document notify all observers
        if (ISA(pDoc, ZDProcessGraphModelDoc))
        {
            reinterpret_cast<ZDProcessGraphModelDoc*>(pDoc)->NotifyAllObservers(&Msg);
            reinterpret_cast<ZDProcessGraphModelDoc*>(pDoc)->NotifyAllObservers(&SymMsg);
        }
    }
    else
    {
        ZBSymbolObserverMsg        SymMsg(ZBSymbolObserverMsg::ElementSelected, NULL);
        ZBPropertyObserverMsg    Msg(NULL);

        // Notify direct observers first
        NotifyAllObservers(&Msg);
        NotifyAllObservers(&SymMsg);

        // And then document notify all observers
        if (ISA(pDoc, ZDProcessGraphModelDoc))
        {
            reinterpret_cast<ZDProcessGraphModelDoc*>(pDoc)->NotifyAllObservers(&Msg);
            reinterpret_cast<ZDProcessGraphModelDoc*>(pDoc)->NotifyAllObservers(&SymMsg);
        }
    }
}

void ZDProcessGraphModelController::OnSelectionChange(CODComponentSet* pChangedSet)
{
    CODController::OnSelectionChange(pChangedSet);

    // Flag to indicate that the selection has changed
    m_SelectionChanged = true;

    // Used to keep the last selected element
    // We can therefore determine if the user wants to edit the label
    if (GetSelection()->GetSize() == 1)
    {
        if (ISA(GetSelection()->GetAt(0), CODSymbolComponent))
        {
            m_LastSelectedElement = reinterpret_cast<CODSymbolComponent*>(GetSelection()->GetAt(0));
        }
        else if (ISA(GetSelection()->GetAt(0), CODLabelComponent))
        {
            m_LastSelectedElement =
                reinterpret_cast<CODSymbolComponent*>(reinterpret_cast<CODLabelComponent*>(GetSelection()->GetAt(0))->GetOwner());
        }
        else
        {
            m_LastSelectedElement = NULL;
        }
    }
    else
    {
        m_LastSelectedElement = NULL;
    }
}

void ZDProcessGraphModelController::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    bool bHandle = false;

    if (m_pViewport)
    {
        // Handle the tooltip
        CPoint pt(point);
        VpDPtoLP(&pt);
        CODComponent* pCompHit = m_pViewport->ComponentHitTest(pt);

        // If a label, reassign the hit symbol
        if (pCompHit && ISA(pCompHit, CODLabelComponent))
        {
            pCompHit =
                reinterpret_cast<CODSymbolComponent*>(reinterpret_cast<CODLabelComponent*>(pCompHit)->GetOwner());
        }

        if (pCompHit && (ISA(pCompHit, ZBSymbol) || ISA(pCompHit, ZBLinkSymbol)))
        {
            // Call the symbol OnMouseMove function to check if necessary do something
            if (ISA(pCompHit, ZBSymbol))
            {
                if (dynamic_cast<ZBSymbol*>(pCompHit)->AcceptMouseInteraction())
                {
                    bHandle = dynamic_cast<ZBSymbol*>(pCompHit)->OnLButtonDblClk(nFlags, pt, *this);
                }
            }
            else
            {
                if (dynamic_cast<ZBLinkSymbol*>(pCompHit)->AcceptMouseInteraction())
                {
                    bHandle = dynamic_cast<ZBLinkSymbol*>(pCompHit)->OnLButtonDblClk(nFlags, pt, *this);
                }
            }
        }
    }

    // If the double click has been handle, don't continue
    if (bHandle)
    {
        return;
    }

    // If not handle, do the work
    CODComponent* pComp = NULL;

    AssignSymbolHit();

    // If the symbol has a child model, open it
    if (m_pSymbolHit != NULL && (ISA(m_pSymbolHit, ZBSymbol) &&
        (reinterpret_cast<ZBSymbol*>(m_pSymbolHit)->GetChildModel() ||
         reinterpret_cast<ZBSymbol*>(m_pSymbolHit)->CanContainChildModel())))
    {
        OpenSymbol(m_pSymbolHit);

        // Call the symbol OnPostDoubleClick function 
        if (ISA(m_pSymbolHit, ZBSymbol))
        {
            dynamic_cast<ZBSymbol*>(m_pSymbolHit)->OnPostDoubleClick(GetModel(), this);
        }
    }
    // If the symbol is a reference, browse the local symbol
    else if (m_pSymbolHit != NULL &&
        ((ISA(m_pSymbolHit, ZBSymbol) &&
          reinterpret_cast<ZBSymbol*>(m_pSymbolHit)->IsLocal() == false) ||
          (ISA(m_pSymbolHit, ZBLinkSymbol) &&
           reinterpret_cast<ZBLinkSymbol*>(m_pSymbolHit)->IsLocal() == false)))
    {
        BrowseLocalSymbol(m_pSymbolHit);

        // Select local symbol
        SelectComponent(*m_pSymbolHit);

        // Call the symbol OnPostDoubleClick function
        if (ISA(m_pSymbolHit, ZBSymbol))
        {
            dynamic_cast<ZBSymbol*>(m_pSymbolHit)->OnPostDoubleClick(GetModel(), this);
        }
        else
        {
            dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->OnPostDoubleClick(GetModel(), this);
        }
    }
    else
    {
        CODController::OnLButtonDblClk(nFlags, point);
    }
}

void ZDProcessGraphModelController::OnLButtonDown(UINT nFlags, CPoint point)
{
    bool bHandle = false;

    if (m_pViewport)
    {
        // Handle the tooltip
        CPoint pt(point);
        VpDPtoLP(&pt);
        CODComponent* pCompHit = m_pViewport->ComponentHitTest(pt);

        // JMR-MODIF - Le 5 mai 2006 - Réinitialise le curseur.
        SetStandardCursor(IDC_ARROW);
        m_CurrentCursor = 0;

        // *******************************************************************************************************
        // JMR-MODIF - Le 3 mai 2006 - Ajout du code pour la prise en charge du pinceau de style.
        if (m_pFormatPainterSymbol != NULL && pCompHit != NULL && m_IsInFormatPainter == true)
        {
            if (ISA(m_pFormatPainterSymbol, ZBSymbol) && ISA(pCompHit, ZBSymbol))
            {
                ZBSymbol* m_SrcSymbol = reinterpret_cast<ZBSymbol*>(m_pFormatPainterSymbol);
                ZBSymbol* m_DstSymbol = reinterpret_cast<ZBSymbol*>(pCompHit);

                if (m_SrcSymbol != NULL && m_DstSymbol != NULL)
                {
                    if ((m_SrcSymbol->IsProcess() && m_DstSymbol->IsProcess()) ||
                        (m_SrcSymbol->IsProcedure() && m_DstSymbol->IsProcedure()) ||
                        (m_SrcSymbol->IsStart() && m_DstSymbol->IsStart()) ||
                        (m_SrcSymbol->IsStop() && m_DstSymbol->IsStop()) ||
                        (m_SrcSymbol->IsDoor() && m_DstSymbol->IsDoor()) ||
                        (m_SrcSymbol->IsPage() && m_DstSymbol->IsPage()) ||
                        (m_SrcSymbol->IsPackage() && m_DstSymbol->IsPackage()))
                    {
                        if (ZUODSymbolManipulator::CopySymbolStyle(m_SrcSymbol, m_DstSymbol) == FALSE)
                        {
                            return;
                        }

                        m_DstSymbol->RedrawSymbol();

                        // JMR-MODIF - Le 3 septembre 2006 - Copie aussi le nouveau style sur le symbole jumeau.
                        if (m_DstSymbol->IsDoor() || m_DstSymbol->IsPage())
                        {
                            m_DstSymbol->DuplicateStyleOnTwinSymbol();
                        }

                        if (GetDocument() != NULL)
                        {
                            GetDocument()->SetModifiedFlag(TRUE);
                        }
                    }
                }
            }
            else if (ISA(m_pFormatPainterSymbol, ZBLinkSymbol) && ISA(pCompHit, ZBLinkSymbol))
            {
                CODComponent* m_SrcSymbol =
                    ZUODSymbolManipulator::FindSymbol(dynamic_cast<ZBLinkSymbol*>(m_pFormatPainterSymbol),
                                                      SymbolNameComponentControlLabel);

                CODComponent* m_DstSymbol =
                    ZUODSymbolManipulator::FindSymbol(dynamic_cast<ZBLinkSymbol*>(pCompHit),
                                                      SymbolNameComponentControlLabel);

                if (m_SrcSymbol != NULL && m_DstSymbol != NULL)
                {
                    ZUODSymbolManipulator::CopySymbolStyle(m_SrcSymbol, m_DstSymbol);
                    reinterpret_cast<ZBLinkSymbol*>(pCompHit)->RedrawSymbol();

                    if (GetDocument() != NULL)
                    {
                        GetDocument()->SetModifiedFlag(TRUE);
                    }
                }
            }
            else if (ISA(m_pFormatPainterSymbol, ZBLinkSymbol) && ISA(pCompHit, CODLabelComponent))
            {
                CODComponent* m_SrcSymbol =
                    ZUODSymbolManipulator::FindSymbol(dynamic_cast<ZBLinkSymbol*>(m_pFormatPainterSymbol),
                                                      SymbolNameComponentControlLabel);

                if (m_SrcSymbol != NULL && pCompHit != NULL)
                {
                    ZUODSymbolManipulator::CopySymbolStyle(m_SrcSymbol, pCompHit);
                    RefreshAllSymbols();

                    if (GetDocument() != NULL)
                    {
                        GetDocument()->SetModifiedFlag(TRUE);
                    }
                }
            }

            m_pFormatPainterSymbol = NULL;
        }

        m_IsInFormatPainter = false;
        // *******************************************************************************************************

        // If a label, reassign the hit symbol
        if (pCompHit && ISA(pCompHit, CODLabelComponent))
        {
            pCompHit =
                reinterpret_cast<CODSymbolComponent*>(reinterpret_cast<CODLabelComponent*>(pCompHit)->GetOwner());
        }

        if (pCompHit && (ISA(pCompHit, ZBSymbol) || ISA(pCompHit, ZBLinkSymbol)))
        {
            // Call the symbol OnMouseMove function to check if necessary do something
            if (ISA(pCompHit, ZBSymbol))
            {
                if (dynamic_cast<ZBSymbol*>(pCompHit)->AcceptMouseInteraction())
                {
                    bHandle = dynamic_cast<ZBSymbol*>(pCompHit)->OnLButtonDown(nFlags, pt, *this);
                }
            }
            else
            {
                if (dynamic_cast<ZBLinkSymbol*>(pCompHit)->AcceptMouseInteraction())
                {
                    bHandle = dynamic_cast<ZBLinkSymbol*>(pCompHit)->OnLButtonDown(nFlags, pt, *this);
                }
            }
        }
    }

    // If the double click has been handle, don't continue
    if (bHandle)
    {
        return;
    }

    // If not handle, do the work
    // Saves the previous element
    CODSymbolComponent* OldSymbolClicked = m_LastSelectedElement;

    CODController::OnLButtonDown(nFlags, point);

    CDocument* pDoc = GetDocument();

    // Notify selection of component
    NotifySymbolSelected(m_LastSelectedElement);

    // Check if necessary to edit the symbol selected
    if (m_SelectionChanged == true && m_LastSelectedElement)
    {
        // If the user click a second time on the same symbol,
        // assume he'd like edit its name
        if (OldSymbolClicked == m_LastSelectedElement)
        {
            bool IsLocal = false;

            if (m_LastSelectedElement != NULL && ISA(m_LastSelectedElement, ZBSymbol))
            {
                IsLocal = dynamic_cast<ZBSymbol*>(m_LastSelectedElement)->IsLocal();
            }
            else if (m_LastSelectedElement != NULL && ISA(m_LastSelectedElement, ZBLinkSymbol))
            {
                IsLocal = dynamic_cast<ZBLinkSymbol*>(m_LastSelectedElement)->IsLocal();
            }

            // Save the position first
            m_savedEditPosition = point;

            // Edit the element only if the symbol is local
            if (IsLocal)
            {
                EditName(m_LastSelectedElement);
            }
        }

        // Set back the selection changed flag
        m_SelectionChanged = false;
    }
}

void ZDProcessGraphModelController::OnLButtonUp(UINT nFlags, CPoint point)
{
    bool bHandle = false;

    if (m_pViewport)
    {
        // Handle the tooltip
        CPoint pt(point);
        VpDPtoLP(&pt);
        CODComponent* pCompHit = m_pViewport->ComponentHitTest(pt);

        // If a label, reassign the hit symbol
        if (pCompHit && ISA(pCompHit, CODLabelComponent))
        {
            pCompHit =
                reinterpret_cast<CODSymbolComponent*>(reinterpret_cast<CODLabelComponent*>(pCompHit)->GetOwner());
        }

        if (pCompHit && (ISA(pCompHit, ZBSymbol) || ISA(pCompHit, ZBLinkSymbol)))
        {
            // Call the symbol OnMouseMove function to check if necessary do something
            if (ISA(pCompHit, ZBSymbol))
            {
                if (dynamic_cast<ZBSymbol*>(pCompHit)->AcceptMouseInteraction())
                {
                    bHandle = dynamic_cast<ZBSymbol*>(pCompHit)->OnLButtonUp(nFlags, pt, *this);
                }
            }
            else
            {
                if (dynamic_cast<ZBLinkSymbol*>(pCompHit)->AcceptMouseInteraction())
                {
                    bHandle = dynamic_cast<ZBLinkSymbol*>(pCompHit)->OnLButtonUp(nFlags, pt, *this);
                }
            }
        }
    }

    // If the double click has been handle, don't continue
    if (bHandle)
    {
        return;
    }

    // If not handle, do the work
    CODController::OnLButtonUp(nFlags, point);
}

void ZDProcessGraphModelController::OnRButtonUp(UINT nFlags, CPoint point)
{
    bool bHandle = false;

    if (m_pViewport)
    {
        // Handle the tooltip
        CPoint pt(point);
        VpDPtoLP(&pt);
        CODComponent* pCompHit = m_pViewport->ComponentHitTest(pt);

        // If a label, reassign the hit symbol
        if (pCompHit && ISA(pCompHit, CODLabelComponent))
        {
            pCompHit =
                reinterpret_cast<CODSymbolComponent*>(reinterpret_cast<CODLabelComponent*>(pCompHit)->GetOwner());
        }

        if (pCompHit && (ISA(pCompHit, ZBSymbol) || ISA(pCompHit, ZBLinkSymbol)))
        {
            // Call the symbol OnMouseMove function to check if necessary do something
            if (ISA(pCompHit, ZBSymbol))
            {
                if (dynamic_cast<ZBSymbol*>(pCompHit)->AcceptMouseInteraction())
                {
                    bHandle = dynamic_cast<ZBSymbol*>(pCompHit)->OnRButtonUp(nFlags, pt, *this);
                }
            }
            else
            {
                if (dynamic_cast<ZBLinkSymbol*>(pCompHit)->AcceptMouseInteraction())
                {
                    bHandle = dynamic_cast<ZBLinkSymbol*>(pCompHit)->OnRButtonUp(nFlags, pt, *this);
                }
            }
        }
    }

    // If the double click has been handle, don't continue
    if (bHandle)
    {
        return;
    }

    // If not handle, do the work
    AssignSymbolHit();

    if (m_pSymbolHit != NULL)
    {
        if (ISA(m_pSymbolHit, ZBSymbol))
        {
            // No sub-menu defined, return
            if (reinterpret_cast<ZBSymbol*>(m_pSymbolHit)->GetRightSubMenu() == -1)
            {
                return;
            }

            if (reinterpret_cast<ZBSymbol*>(m_pSymbolHit)->IsLocal())
            {
                m_pRightSubMenu =
                    m_SymbolRightMainMenu.GetSubMenu(reinterpret_cast<ZBSymbol*>(m_pSymbolHit)->GetRightSubMenu());
            }
            else
            {
                m_pRightSubMenu =
                    m_SymbolRefRightMainMenu.GetSubMenu(reinterpret_cast<ZBSymbol*>(m_pSymbolHit)->GetRightSubMenu());
            }
        }
        else
        {
            // No sub-menu defined, return
            if (reinterpret_cast<ZBLinkSymbol*>(m_pSymbolHit)->GetRightSubMenu() == -1)
            {
                return;
            }

            if (reinterpret_cast<ZBLinkSymbol*>(m_pSymbolHit)->IsLocal())
            {
                m_pRightSubMenu =
                    m_SymbolRightMainMenu.GetSubMenu(reinterpret_cast<ZBLinkSymbol*>(m_pSymbolHit)->GetRightSubMenu());
            }
            else
            {
                m_pRightSubMenu =
                    m_SymbolRefRightMainMenu.GetSubMenu(reinterpret_cast<ZBLinkSymbol*>(m_pSymbolHit)->GetRightSubMenu());
            }
        }
    }
    else if (GetSelection()->GetSize() >= 1)
    {
        m_pRightSubMenu = m_SymbolRightMainMenu.GetSubMenu(0);
        m_pSymbolHit = NULL;
    }
    else
    {
        m_pRightSubMenu = NULL;
        m_pSymbolHit = NULL;
    }

    CODController::OnRButtonUp(nFlags, point);
}

void ZDProcessGraphModelController::OnMouseMove(UINT nFlags, CPoint point)
{
    // JMR-MODIF - Le 17 mai 2006 - Ajout des variables m_OldCursor, m_BadCursor, m_CurCursor.
    static HCURSOR    m_OldCursor = NULL;
    static HCURSOR    m_BadCursor = NULL;

    HCURSOR            m_CurCursor = GetCursor();

    bool            bHandle = false;

    if (m_pViewport)
    {
        // Handle the tooltip
        CPoint pt(point);
        VpDPtoLP(&pt);
        CODComponent* pCompHit = m_pViewport->ComponentHitTest(pt);

        // If a label, reassign the hit symbol
        if (pCompHit && ISA(pCompHit, CODLabelComponent))
        {
            pCompHit =
                reinterpret_cast<CODSymbolComponent*>(reinterpret_cast<CODLabelComponent*>(pCompHit)->GetOwner());
        }

        if (pCompHit && (ISA(pCompHit, ZBSymbol) || ISA(pCompHit, ZBLinkSymbol)))
        {
            // Call the symbol OnMouseMove function to check if necessary do something
            if (ISA(pCompHit, ZBSymbol))
            {
                if (dynamic_cast<ZBSymbol*>(pCompHit)->AcceptMouseInteraction())
                {
                    bHandle = dynamic_cast<ZBSymbol*>(pCompHit)->OnMouseMove(nFlags, pt, *this);
                }
            }
            else
            {
                if (dynamic_cast<ZBLinkSymbol*>(pCompHit)->AcceptMouseInteraction())
                {
                    bHandle = dynamic_cast<ZBLinkSymbol*>(pCompHit)->OnMouseMove(nFlags, pt, *this);
                }
            }

            // Use Activate() to show the tooltip.
            if (::IsWindow(GetView()->GetToolTip().m_hWnd))
            {
                GetView()->GetToolTip().Activate(TRUE);
            }

            // JMR-MODIF - Le 17 mai 2006 - La gestion des curseurs se fait maintenant ci-dessous.
/*            if ( !bHandle )
            {
                // Change the cursor shape
                SetStandardCursor( IDC_ARROW );
            }
*/
        }
        else
        {
            if (::IsWindow(GetView()->GetToolTip().m_hWnd))
            {
                // Use Activate() to hide the tooltip.
                GetView()->GetToolTip().Activate(FALSE);
            }

            // JMR-MODIF - Le 17 mai 2006 - La gestion des curseurs se fait maintenant ci-dessous.
            // JMR-MODIF - Le 5 mai 2006 - Ajout du code pour remettre en place le curseur précédent.
/*            if ( m_CurrentCursor != 0 )
            {
                SetCustomCursor( m_CurrentCursor );
            }
*/
        }
    }

    // JMR-MODIF - Le 17 mai 2006 - Nouvelle gestion du curseur.
    if (m_CurrentCursor != 0)
    {
        SetCustomCursor(m_CurrentCursor);
    }
    else
    {
        if (m_CurCursor != GetCursor())
        {
            m_BadCursor = GetCursor();
        }

        if (!bHandle)
        {
            if (GetCursor() != m_BadCursor)
            {
                m_OldCursor = GetCursor();
            }

            if (m_OldCursor != NULL)
            {
                SetCursor(m_OldCursor);
            }
        }
    }

    if (!bHandle)
    {
        CODController::OnMouseMove(nFlags, point);
    }
}

void ZDProcessGraphModelController::EditName(CODComponent* pCompToEdit)
{
    BOOL                bEditing = FALSE;
    CODTextComponent*    pTextComp = NULL;

    if (pCompToEdit != NULL && (ISA(pCompToEdit, ZBSymbol) || ISA(pCompToEdit, ZBLinkSymbol)))
    {
        m_pSymbolHit = static_cast<CODSymbolComponent*>(pCompToEdit);

        CODEditProperties*    pEditProps = (CODEditProperties*)pCompToEdit->GetProperty(OD_PROP_EDIT);
        CODEditProperties*    pModelEditProps = (CODEditProperties*)GetCanvasModel()->GetProperty(OD_PROP_EDIT);
        BOOL                bDesignMode = GetCanvasModel()->GetDesignMode();

        // Check if the symbol can be edited
        if (ISA(m_pSymbolHit, ZBSymbol) && reinterpret_cast<ZBSymbol*>(m_pSymbolHit)->SymbolNameTextEditReadOnly())
        {
            return;
        }

        if (ISA(m_pSymbolHit, ZBLinkSymbol) && reinterpret_cast<ZBLinkSymbol*>(m_pSymbolHit)->SymbolNameTextEditReadOnly())
        {
            return;
        }

        if (bDesignMode || (!pEditProps->IsReadOnly() && !pModelEditProps->IsReadOnly()))
        {
            if (ISA(pCompToEdit, ZBSymbol))
            {
                pTextComp = ((ZBSymbol*)pCompToEdit)->GetSymbolNameTextEdit();
            }
            else if (ISA(pCompToEdit, ZBLinkSymbol))
            {
                pTextComp = ((ZBLinkSymbol*)pCompToEdit)->GetSymbolNameTextEdit();
            }

            if (pTextComp != NULL && pTextComp->IsEditing() != TRUE)
            {
                CODEditProperties* pEditProps = (CODEditProperties*)pTextComp->GetProperty(OD_PROP_EDIT);
                ASSERT_VALID(pEditProps);

                if (pEditProps->IsReadOnly())
                {
                    return;
                }

                CODComponentSet setUpdate;
                setUpdate.Add(pCompToEdit);

                if (pTextComp != m_pTextEdit)
                {
                    EndTextEdit(0, m_savedEditPosition);

                    m_pTextEdit = pTextComp;
                    m_pTextEdit->AddRef();

                    bEditing = m_pTextEdit->BeginEdit(GetCanvasVp());

                    // Set the flag for text edition
                    m_IsEditingSymbolName = true;

                    if (bEditing)
                    {
                        GetCanvasVp()->UpdateComponents(&setUpdate);
                    }
                }
            }

            // Set flag for modification
            if (GetDocument())
            {
                GetDocument()->SetModifiedFlag(TRUE);
            }
        }
    }
    else
    {
        m_pSymbolHit = NULL;
    }
}

void ZDProcessGraphModelController::EditComment(CODComponent* pCompToEdit)
{
    BOOL                bEditing = FALSE;
    CODTextComponent*    pTextComp = NULL;

    if (pCompToEdit != NULL && ISA(pCompToEdit, ZBSymbol))
    {
        // If it is not our symbol type, call the base class
        m_pSymbolHit = static_cast<ZBSymbol*>(pCompToEdit);

        CODEditProperties*    pEditProps = (CODEditProperties*)m_pSymbolHit->GetProperty(OD_PROP_EDIT);
        CODEditProperties*    pModelEditProps = (CODEditProperties*)GetCanvasModel()->GetProperty(OD_PROP_EDIT);
        BOOL                bDesignMode = GetCanvasModel()->GetDesignMode();

        // Check if the symbol can be edited
        if (ISA(m_pSymbolHit, ZBSymbol) && reinterpret_cast<ZBSymbol*>(m_pSymbolHit)->CommentTextEditReadOnly())
        {
            return;
        }

        if (ISA(m_pSymbolHit, ZBLinkSymbol) && reinterpret_cast<ZBLinkSymbol*>(m_pSymbolHit)->CommentTextEditReadOnly())
        {
            return;
        }

        if (bDesignMode || (!pEditProps->IsReadOnly() && !pModelEditProps->IsReadOnly()))
        {
            if (ISA(pCompToEdit, ZBSymbol))
            {
                pTextComp = ((ZBSymbol*)pCompToEdit)->GetCommentTextEdit();
            }
            else if (ISA(pCompToEdit, ZBLinkSymbol))
            {
                pTextComp = ((ZBLinkSymbol*)pCompToEdit)->GetCommentTextEdit();
            }

            if (pTextComp != NULL && pTextComp->IsEditing() != TRUE)
            {
                CODEditProperties* pEditProps = (CODEditProperties*)pTextComp->GetProperty(OD_PROP_EDIT);
                ASSERT_VALID(pEditProps);

                if (pEditProps->IsReadOnly())
                {
                    return;
                }

                CODComponentSet setUpdate;
                setUpdate.Add(m_pCompHit);

                if (pTextComp != m_pTextEdit)
                {
                    EndTextEdit(0, m_savedEditPosition);

                    m_pTextEdit = pTextComp;
                    m_pTextEdit->AddRef();

                    bEditing = m_pTextEdit->BeginEdit(GetCanvasVp());

                    // Set the flag for comment edition
                    m_IsEditingSymbolComment = true;

                    if (bEditing)
                    {
                        GetCanvasVp()->UpdateComponents(&setUpdate);
                    }
                }
            }

            // Set flag for modification
            if (GetDocument())
            {
                GetDocument()->SetModifiedFlag(TRUE);
            }
        }
    }
    else m_pSymbolHit = NULL;
}

BOOL ZDProcessGraphModelController::StartTextEdit(UINT nFlags, CPoint ptDev)
{
    nFlags; // unused

    BOOL                bEditing = FALSE;
    CODTextComponent*    pTextComp = NULL;

    CPoint ptLog = ptDev;
    VpDPtoLP(&ptLog);

    m_pCompHit = GetCanvasVp()->ComponentHitTest(ptLog);

    if (m_pCompHit != NULL && (ISA(m_pCompHit, ZBSymbol) || ISA(m_pCompHit, ZBLinkSymbol)))
    {
        CODEditProperties*    pEditProps = (CODEditProperties*)m_pCompHit->GetProperty(OD_PROP_EDIT);
        CODEditProperties*    pModelEditProps = (CODEditProperties*)GetCanvasModel()->GetProperty(OD_PROP_EDIT);
        BOOL                bDesignMode = GetCanvasModel()->GetDesignMode();

        if (bDesignMode || (!pEditProps->IsReadOnly() && !pModelEditProps->IsReadOnly()))
        {
            // If it is not our symbol type, call the base class
            m_pSymbolHit = static_cast<CODSymbolComponent*>(m_pCompHit);

            // Check if the symbol can be edited
            if (ISA(m_pSymbolHit, ZBSymbol) && reinterpret_cast<ZBSymbol*>(m_pSymbolHit)->SymbolNameTextEditReadOnly())
            {
                return bEditing;
            }

            if (ISA(m_pSymbolHit, ZBLinkSymbol) && reinterpret_cast<ZBLinkSymbol*>(m_pSymbolHit)->SymbolNameTextEditReadOnly())
            {
                return bEditing;
            }

            // Can be edited
            if (ISA(m_pSymbolHit, ZBSymbol))
            {
                pTextComp = ((ZBSymbol*)m_pSymbolHit)->GetSymbolNameTextEdit();
            }
            else if (ISA(m_pSymbolHit, ZBLinkSymbol))
            {
                pTextComp = ((ZBLinkSymbol*)m_pSymbolHit)->GetSymbolNameTextEdit();
            }

            // Test if in region
            if (pTextComp)
            {
                CODRgn rgn;
                rgn = pTextComp->GetRgn();

                // Not in region, reset pTextComp
                if (!rgn.PtInRegion(ptDev, 4))
                {
                    pTextComp = NULL;
                }
            }

            if (!pTextComp)
            {
                // Check if the symbol can be edited
                if (ISA(m_pSymbolHit, ZBSymbol) &&
                    reinterpret_cast<ZBSymbol*>(m_pSymbolHit)->CommentTextEditReadOnly())
                {
                    return bEditing;
                }

                if (ISA(m_pSymbolHit, ZBLinkSymbol) &&
                    reinterpret_cast<ZBLinkSymbol*>(m_pSymbolHit)->CommentTextEditReadOnly())
                {
                    return bEditing;
                }

                // Can be edited
                if (ISA(m_pSymbolHit, ZBSymbol))
                {
                    pTextComp = ((ZBSymbol*)m_pSymbolHit)->GetCommentTextEdit();
                }
                else if (ISA(m_pSymbolHit, ZBLinkSymbol))
                {
                    pTextComp = ((ZBLinkSymbol*)m_pSymbolHit)->GetCommentTextEdit();
                }
            }

            // Test if in region
            if (pTextComp)
            {
                CODRgn rgn;
                rgn = pTextComp->GetRgn();

                // Not in region, reset pTextComp
                if (!rgn.PtInRegion(ptDev, 4))
                {
                    pTextComp = NULL;
                }
            }
        }
    }
    else
    {
        m_pSymbolHit = NULL;
        return CODController::StartTextEdit(nFlags, ptDev);
    }

    if (pTextComp != NULL && pTextComp->IsEditing() != TRUE)
    {
        CODEditProperties* pEditProps = (CODEditProperties*)pTextComp->GetProperty(OD_PROP_EDIT);
        ASSERT_VALID(pEditProps);

        if (pEditProps->IsReadOnly())
        {
            return FALSE;
        }

        CODComponentSet setUpdate;
        setUpdate.Add(m_pCompHit);

        if (pTextComp != m_pTextEdit)
        {
            EndTextEdit(0, m_savedEditPosition);

            m_pTextEdit = pTextComp;
            m_pTextEdit->AddRef();

            bEditing = m_pTextEdit->BeginEdit(GetCanvasVp());

            if (bEditing)
            {
                GetCanvasVp()->UpdateComponents(&setUpdate);
            }
        }
    }

    return bEditing;
}


void ZDProcessGraphModelController::EndTextEdit(UINT nFlags, CPoint ptDev)
{
    CString value;
    bool IsNameValid = true;

    if (m_pTextEdit)
    {
        value = m_pTextEdit->GetEditText();

        // Retreive the label or edit text owner
        CODComponent* pOwner = NULL;

        // first check label component, because he derives from text component
        if (ISA(m_pTextEdit, CODLabelComponent))
        {
            pOwner = reinterpret_cast<CODLabelComponent*>(m_pTextEdit)->GetOwner();
        }
        else if (ISA(m_pTextEdit, CODTextComponent))
        {
            pOwner = reinterpret_cast<CODTextComponent*>(m_pTextEdit)->GetParent();
        }

        if (pOwner && (ISA(pOwner, ZBSymbol) || ISA(pOwner, ZBLinkSymbol)))
        {
            if (m_IsEditingSymbolName)
            {
                if (value.IsEmpty())
                {
                    PSS_MsgBox mBox;
                    mBox.Show(IDS_SYMBOLNAME_EMPTY, MB_OK);
                    IsNameValid = false;
                }

                ZDProcessGraphModelMdl* pRoot = GetModel()->GetRoot();

                if (pRoot)
                {
                    if (ISA(pOwner, ZBSymbol) && ((ZBSymbol*)pOwner)->GetSymbolName() != value)
                    {
                        // Check if new name is valid
                        if (!((ZBSymbol*)pOwner)->IsNewNameValid(value))
                        {
                            IsNameValid = false;
                        }
                        else ((ZBSymbol*)pOwner)->SetSymbolName(value);
                    }
                    else if (ISA(pOwner, ZBLinkSymbol) && ((ZBLinkSymbol*)pOwner)->GetSymbolName() != value)
                    {
                        // Check if new name is valid
                        if (!((ZBLinkSymbol*)pOwner)->IsNewNameValid(value))
                        {
                            IsNameValid = false;
                        }
                        else ((ZBLinkSymbol*)pOwner)->SetSymbolName(value);
                    }
                }
            }
            else if (m_IsEditingSymbolComment)
            {
                if (ISA(pOwner, ZBSymbol))
                {
                    ((ZBSymbol*)pOwner)->SetSymbolComment(value);
                }
                else
                {
                    ((ZBLinkSymbol*)pOwner)->SetSymbolComment(value);
                }
            }

            // Reset edition flag only if the name is valid
            // and we know that we will leave the edition control
            if (IsNameValid)
            {
                // Reset edition flag
                m_IsEditingSymbolName = false;
                m_IsEditingSymbolComment = false;
            }
        }
    }

    // Call the base class if the new name is valid
    if (IsNameValid)
    {
        CODController::EndTextEdit(nFlags, ptDev);
    }
}

void ZDProcessGraphModelController::OnTimer(SEC_UINT nIDEvent)
{
    if (nIDEvent == ANIMATE_TIMER)
    {
        if (m_AnimatedUseColor)
        {
            // It still time for animation
            if ((m_StartTimeOfTimer + COleDateTimeSpan(0, 0, 0, m_nAnimateCounter)) >= PSS_Date::GetCurrentTime())
            {
                if (!m_TimerInitialized)
                {
                    if (m_animateNodes.GetSize() > 0)
                    {
                        _ChangeColorNodes();
                    }

                    if (m_animateEdges.GetSize() > 0)
                    {
                        _ChangeColorEdges();
                    }

                    if (m_animateComponents.GetSize() > 0)
                    {
                        _ChangeColorSymbols();
                    }

                    m_TimerInitialized = true;
                }
            }
            else _EndAnimateTimer();
        }
        else
        {
            if (m_nAnimateCounter > 0)
            {
                if (m_animateNodes.GetSize() > 0)
                {
                    _AnimateNodes();
                }

                if (m_animateEdges.GetSize() > 0)
                {
                    _AnimateEdges();
                }

                if (m_animateComponents.GetSize() > 0)
                {
                    _AnimateSymbols();
                }

                --m_nAnimateCounter;
            }
            else _EndAnimateTimer();
        }
    }

    CODController::OnTimer(nIDEvent);
}

void ZDProcessGraphModelController::_EndAnimateTimer()
{
    KillTimer(m_nTimer);
    m_nTimer = 0;

    if (m_AnimatedUseColor)
    {
        if (m_animateNodes.GetSize() > 0)
        {
            _ChangeBackColorNodes();
        }

        if (m_animateEdges.GetSize() > 0)
        {
            _ChangeBackColorEdges();
        }

        if (m_animateComponents.GetSize() > 0)
        {
            _ChangeBackColorSymbols();
        }
    }

    m_animateNodes.RemoveAll();
    m_animateEdges.RemoveAll();
    m_animateComponents.RemoveAll();
    m_nAnimateCounter = 0;
    m_TimerInitialized = false;
}

void ZDProcessGraphModelController::OnChangeTextEdit()
{
    // If not a symbol selected, call the base class
    if (m_pSymbolHit == NULL)
    {
        CODController::OnChangeTextEdit();
    }

    if (m_pTextEdit == NULL)
    {
        return;
    }

    sfl::MvcViewport::DC dc(GetCanvasVp(), TRUE);

    CODComponentSet setUpdate;

    setUpdate.Add(m_pTextEdit);

    if (ISA(m_pTextEdit, CODLabelComponent))
    {
        CODLabelComponent*    pLabel = static_cast<CODLabelComponent*>(m_pTextEdit);
        CODSymbolComponent*    pOwner = pLabel->GetOwner();

        if (pOwner != NULL)
        {
            setUpdate.Add(pOwner);
        }
    }

    GetCanvasVp()->UpdateComponents(&setUpdate);
}

void ZDProcessGraphModelController::OnGoinSymbol()
{
    AssignSymbolHit();

    if (m_pSymbolHit != NULL && (ISA(m_pSymbolHit, ZBSymbol) &&
        (reinterpret_cast<ZBSymbol*>(m_pSymbolHit)->GetChildModel() ||
         reinterpret_cast<ZBSymbol*>(m_pSymbolHit)->CanContainChildModel())))
    {
        OpenSymbol(m_pSymbolHit);
    }
}

void ZDProcessGraphModelController::OnSelectSymbol()
{
    AssignSymbolHit();

    if (m_pSymbolHit)
    {
        EnsureSymbolVisible(m_pSymbolHit);
        SelectComponent(*m_pSymbolHit);
    }
}

void ZDProcessGraphModelController::OnGoParentModel()
{
    ZDProcessGraphModelMdl* pModel = GetModel();

    if (pModel && pModel->GetParent())
    {
        BrowseModel(pModel->GetParent(), pModel->GetParent()->GetParent());
    }
}

void ZDProcessGraphModelController::OnUpdateGoParentModel(CCmdUI* pCmdUI)
{
    ZDProcessGraphModelMdl* pModel = GetModel();
    pCmdUI->Enable(pModel && pModel->GetParent());
}

void ZDProcessGraphModelController::OnBrowseSourceSymbol()
{
    AssignSymbolHit();

    if (GetDocument() && ISA(GetDocument(), ZDProcessGraphModelDoc) &&
        ((ZDProcessGraphModelDoc*)GetDocument())->GetModel() && m_pSymbolHit    &&
        ISA(m_pSymbolHit, ZBSymbol) && !((ZBSymbol*)m_pSymbolHit)->IsLocal())
    {
        BrowseLocalSymbol((ZBSymbol*)m_pSymbolHit);
    }
}

void ZDProcessGraphModelController::OnUpdateBrowseSourceSymbol(CCmdUI* pCmdUI)
{
    AssignSymbolHit();

    pCmdUI->Enable(m_pSymbolHit && ISA(m_pSymbolHit, ZBSymbol) && !((ZBSymbol*)m_pSymbolHit)->IsLocal());
}

void ZDProcessGraphModelController::OnFindSymbol()
{
    ZDProcessGraphModelMdl* pModel = GetModel();

    if (!pModel)
    {
        return;
    }

    CWaitCursor wait;

    ZBPropertySet Set;
    ZUDynamicAttributesManipulator::ExtractUniqueAttributes(GetModel(), Set);

    ZBPropertyAttributes PropAttributes;

    ZVFindSymbolExtDlg FindSymbolDlg(&PropAttributes, &Set);

    if (FindSymbolDlg.DoModal() == IDOK)
    {
        if (FindSymbolDlg.GetInAllModels())
        {
            pModel = pModel->GetRoot();
        }

        // It is necessary to call Restore here in order
        // to change the cursor back to the wait cursor.
        wait.Restore();

        ZILog* pLog = NULL;

        if (pModel->GetDocument() && ISA(pModel->GetDocument(), ZDProcessGraphModelDoc))
        {
            pLog = dynamic_cast<ZDProcessGraphModelDoc*>(pModel->GetDocument())->GetSearchOutputLog();

            // Asks to activate the search log tab
            PSS_ToolbarObserverMsg Msg(UM_ACTIVATE_LOGSEARCH_TAB);
            dynamic_cast<ZDProcessGraphModelDoc*>(pModel->GetDocument())->NotifyAllObservers(&Msg);
        }

        // Now launch the find 
        pModel->Find(FindSymbolDlg.GetWhat(),
                     pLog,
                     &PropAttributes,
                     FindSymbolDlg.GetInAllModels(),
                     FindSymbolDlg.GetCaseSensitive(),
                     FindSymbolDlg.GetPartialSearch());
    }

    // Remove all properties
    ZBPropertyIterator i(&Set);
    ZBProperty* pProp;

    for (pProp = i.GetFirst(); pProp; pProp = i.GetNext())
    {
        delete pProp;
    }

    Set.RemoveAll();
}

void ZDProcessGraphModelController::OnInsertPage()
{
    ZDProcessGraphModelMdl* pRoot = GetModel()->GetRoot();

    if (!pRoot)
    {
        return;
    }

    ZVInsertModelNewPageDlg Dlg(pRoot, pRoot->GetValidNextPageName(), pRoot->GetExistingPageNameArray());

    if (Dlg.DoModal() == IDOK)
    {
        ZDProcessGraphModelMdl*    pModel = pRoot->CreateEmptyModel(Dlg.GetPageName(), Dlg.GetParentModel());
        ZDProcessGraphPage*        pPage = pRoot->CreateNewPage(pModel, Dlg.GetPageName(), Dlg.GetParentModel());

        BrowseModel(pModel, Dlg.GetParentModel());

        // Build the message
        ZBDocObserverMsg DocMsg;
        AfxGetMainWnd()->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, (LPARAM)&DocMsg);

        // Set flag for modification
        GetDocument()->SetModifiedFlag(TRUE);
    }
}

void ZDProcessGraphModelController::OnRenamePage()
{
    ZDProcessGraphModelMdl* pRoot = GetModel()->GetRoot();

    if (!pRoot)
    {
        return;
    }

    CString NewPage = pRoot->GetValidNextPageName();

    ZVRenameModelPageDlg Dlg(pRoot, pRoot->GetExistingPageNameArray());

    if (Dlg.DoModal() == IDOK)
    {
        ZDProcessGraphPage* pPage = Dlg.GetSelectedPage();

        if (pPage)
        {
            // Keeps the old page name
            CString OldPageName = pPage->GetPageName();

            // Rename the page
            pPage->SetPageName(Dlg.GetPageName());

            // Advise the owner model of page changes
            pRoot->OnPageNameChanged(pPage, OldPageName);
        }

        // Build the message
        ZBDocObserverMsg DocMsg;
        AfxGetMainWnd()->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, (LPARAM)&DocMsg);

        // Set flag for modification
        GetDocument()->SetModifiedFlag(TRUE);
    }
}

void ZDProcessGraphModelController::OnRenameCurrentPage()
{
    ZDProcessGraphModelMdl* pRoot = GetModel()->GetRoot();

    if (!pRoot)
    {
        return;
    }

    CString NewPage = pRoot->GetValidNextPageName();

    // Find the current page
    ZDProcessGraphPage* pCurrentPage = pRoot->FindModelPage(GetModel(), true);

    // Keeps the old page name
    CString OldPageName = pCurrentPage->GetPageName();

    ZVRenameModelPageDlg Dlg(pRoot, pRoot->GetExistingPageNameArray(), pCurrentPage);

    if (Dlg.DoModal() == IDOK)
    {
        ZDProcessGraphPage* pPage = Dlg.GetSelectedPage();

        if (pPage)
        {
            pPage->SetPageName(Dlg.GetPageName());

            // Advise the owner model of page changes
            pRoot->OnPageNameChanged(pPage, OldPageName);
        }

        // Build the message
        ZBDocObserverMsg DocMsg;
        AfxGetMainWnd()->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, (LPARAM)&DocMsg);

        // Set flag for modification
        GetDocument()->SetModifiedFlag(TRUE);
    }
}

void ZDProcessGraphModelController::OnDeletePage()
{
    if (!GetModel()->GetRoot())
    {
        return;
    }

    ZVDeleteModelPageDlg Dlg(GetModel()->GetRoot());

    if (Dlg.DoModal() == IDOK)
    {
        ZDProcessGraphPage* pPage = Dlg.GetSelectedPage();

        if (pPage)
        {
            // First, move to the root model
            BrowseModel(GetModel()->GetRoot(), GetModel()->GetRoot()->GetParent());

            // Delete the page and its associated model
            GetModel()->GetRoot()->DeletePage(pPage->GetPageName(), true);

            // Build the message
            ZBDocObserverMsg DocMsg;
            AfxGetMainWnd()->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, (LPARAM)&DocMsg);

            // Set flag for modification
            GetDocument()->SetModifiedFlag(TRUE);
        }
    }
}

void ZDProcessGraphModelController::OnDeleteCurrentPage()
{
    if (!GetModel()->GetRoot())
    {
        return;
    }

    // Retreive the root page
    ZDProcessGraphPage* pRootPage = GetModel()->GetRoot()->FindModelPage(GetModel()->GetRoot(), true);

    // Find the current page
    ZDProcessGraphPage* pCurrentPage = GetModel()->GetRoot()->FindModelPage(GetModel(), true);

    if (GetModel()->HasPageSet() &&
        GetModel()->GetPageSet() &&
        GetModel()->GetPageSet()->GetAt(0) == pCurrentPage)
    {
        // Display warning message
        PSS_MsgBox mBox;
        mBox.Show(IDS_CANNOTDELETE_ROOTPAGE, MB_OK);

        return;
    }

    // First, move to the root model
    BrowseModel(GetModel()->GetRoot(), GetModel()->GetRoot()->GetParent());

    if (pCurrentPage)
    {
        GetModel()->GetRoot()->NotifyDeletePage(pCurrentPage);

        // Delete the page and its associated model
        GetModel()->GetRoot()->DeletePage(pCurrentPage->GetPageName(), true);

        // Build the message
        ZBDocObserverMsg DocMsg;
        AfxGetMainWnd()->SendMessageToDescendants(UM_DOCUMENTMODELHASCHANGED, 0, (LPARAM)&DocMsg);

        // Set flag for modification
        GetDocument()->SetModifiedFlag(TRUE);
    }
}

void ZDProcessGraphModelController::OnOdMeasurements()
{
    // Call the base class
    CODController::OnMeasurements();

    if (!GetDocument() || !GetCanvasVp()->GetRuler())
    {
        return;
    }

    // Set flag for modification
    GetDocument()->SetModifiedFlag(TRUE);

    if (ISA(GetDocument(), ZDProcessGraphModelDoc))
    {
        ((ZDProcessGraphModelDoc*)GetDocument())->SetPageUnits(*(GetCanvasVp()->GetRuler()));
    }
}

void ZDProcessGraphModelController::ViewZoomIn()
{
    BOOL    bDesignMode = GetCanvasModel()->GetDesignMode();
    CSize    szMag = GetCanvasVp()->GetMagnification();

    szMag.cx += 25;
    szMag.cy += 25;

    GetCanvasVp()->SetMagnification(szMag.cx, szMag.cy);

    UpdateTextEdit();

    GetCanvasVp()->Invalidate();
}

void ZDProcessGraphModelController::ViewZoomOut()
{
    BOOL    bDesignMode = GetCanvasModel()->GetDesignMode();
    CSize    szMag = GetCanvasVp()->GetMagnification();

    szMag.cx -= 25;
    szMag.cy -= 25;

    GetCanvasVp()->SetMagnification(szMag.cx, szMag.cy);

    UpdateTextEdit();

    GetCanvasVp()->Invalidate();
}

void ZDProcessGraphModelController::OnViewZoomIn()
{
    ViewZoomIn();
}

void ZDProcessGraphModelController::OnViewZoomOut()
{
    ViewZoomOut();
}

void ZDProcessGraphModelController::OnAddNewExtApp()
{
    AssignSymbolHit();

    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        dynamic_cast<ZBSymbol*>(m_pSymbolHit)->DoInsertExtApp();
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->DoInsertExtApp();
    }
}

void ZDProcessGraphModelController::OnUpdateAddNewExtApp(CCmdUI* pCmdUI)
{
    bool Enable = false;

    AssignSymbolHit();

    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        Enable = dynamic_cast<ZBSymbol*>(m_pSymbolHit)->AcceptExtApp();
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        Enable = dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->AcceptExtApp();
    }

    pCmdUI->Enable(Enable);
}

void ZDProcessGraphModelController::OnAddNewExtFile()
{
    AssignSymbolHit();

    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        dynamic_cast<ZBSymbol*>(m_pSymbolHit)->DoInsertExtFile();
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->DoInsertExtFile();
    }
}

void ZDProcessGraphModelController::OnUpdateAddNewExtFile(CCmdUI* pCmdUI)
{
    bool Enable = false;

    AssignSymbolHit();

    if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBSymbol))
    {
        Enable = dynamic_cast<ZBSymbol*>(m_pSymbolHit)->AcceptExtFile();
    }
    else if (m_pSymbolHit != NULL && ISA(m_pSymbolHit, ZBLinkSymbol))
    {
        Enable = dynamic_cast<ZBLinkSymbol*>(m_pSymbolHit)->AcceptExtFile();
    }

    pCmdUI->Enable(Enable);
}

void ZDProcessGraphModelController::OnShowModelBorder()
{
    ZDProcessGraphModelMdl* pModel = GetRootModel();
    ASSERT(pModel);

    pModel->SetShowPageBorder(!pModel->GetShowPageBorder());

    // JMR-MODIF - Le 14 juillet 2005 - Modifié l'appel à UpdatePageLook
    // pour tenir compte de la nouvelle implémentation.
    if (GetViewport())
    {
        if (GetView())
        {
            GetViewport()->UpdatePageLook(GetView()->GetPrinterPageSize());
        }
    }
}

void ZDProcessGraphModelController::OnUpdateShowModelBorder(CCmdUI* pCmdUI)
{
    ZDProcessGraphModelMdl* pModel = GetRootModel();
    ASSERT(pModel);

    pCmdUI->SetCheck(pModel->GetShowPageBorder());
}

void ZDProcessGraphModelController::OnModelDocumentHasChanged()
{
    // Check if we have one element selected
    // If it is the case, do nothing
    if (GetSelection()->GetSize() > 0)
    {
        return;
    }

    // Otherwise, check if we are at the root of the model
    if (GetModel() != GetRootModel())
    {
        return;
    }

    // Unselect all components to avoid problems
    UnselectAllComponents();

    return;
}

void ZDProcessGraphModelController::OnAdviseStartPropertyEdition()
{
    if (m_IsEditingSymbolName || m_IsEditingSymbolComment)
    {
        EndTextEdit(0, m_savedEditPosition);
    }

    return;
}

void ZDProcessGraphModelController::OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg)
{
    if (pMsg && ISA(pMsg, ZBSymbolLogObserverMsg))
    {
        CODComponentSet* pSet = GetModel()->GetRoot()->FindSymbol(dynamic_cast<ZBSymbolLogObserverMsg*>(pMsg)->GetErrorLine().GetSymbolName(),
                                                                  dynamic_cast<ZBSymbolLogObserverMsg*>(pMsg)->GetErrorLine().GetSymbolPath(),
                                                                  true,
                                                                  true,
                                                                  true);
        if (pSet && pSet->GetSize() > 0)
        {
            COLORREF AnimatedColor;

            if (dynamic_cast<ZBSymbolLogObserverMsg*>(pMsg)->GetErrorLine().GetErrorType() == 1)
            {
                AnimatedColor = defCOLOR_RED;
            }
            else
            {
                AnimatedColor = defCOLOR_GREEN;
            }

            // Ensure the first symbol visible at least
            EnsureSymbolVisible(pSet->GetAt(0));
            AnimateSymbols(*pSet, true, AnimatedColor, 10);
        }
        else
        {
            PSS_MsgBox mBox;
            mBox.Show(IDS_SYMBOLNOTFOUND_USESEARCH, MB_OK);
        }
    }
    else if (pMsg && ISA(pMsg, PSS_DocumentObserverMsg) &&
             dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetDocument() == GetDocument() &&
             ISA(dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetDocument(), ZDProcessGraphModelDoc))
    {
        // Check about document close, detach observer
        switch (dynamic_cast<PSS_DocumentObserverMsg*>(pMsg)->GetMessageID())
        {
            case UM_FRAMEHASBEENACTIVATED:
            {
                AssignSymbolHit();

                // Notify new selection
                NotifySymbolSelected(m_pSymbolHit);
                break;
            }
        }
    }
    else NotifyAllObservers(pMsg);

    // JMR-MODIF - Le 5 août 2005 - Ajout du code de mise à jour de la trame de fond.
    if (GetModel() != NULL)
    {
        if (GetModel()->GetRoot()->IsBkGndMustBeRestored() == TRUE)
        {
            CString BkGndFilename = GetModel()->GetRoot()->GetBkGndFilename();

            if (BkGndFilename != _T(""))
            {
                SetImage(BkGndFilename, GetModel()->GetRoot()->IsLogo());
            }

            GetModel()->GetRoot()->ResetBkGndMustBeRestored();
        }
    }
}

bool ZDProcessGraphModelController::OnToolTip(CString& toolTipText, const CPoint& point, ZBSymbol::IEToolTipMode mode)
{
    CPoint pt(point);
    VpDPtoLP(&pt);
    CODComponent* pCompHit = GetCanvasVp()->ComponentHitTest(pt);

    // If a label, reassign the hit symbol
    if (pCompHit && ISA(pCompHit, CODLabelComponent))
        pCompHit = reinterpret_cast<CODSymbolComponent*>(reinterpret_cast<CODLabelComponent*>(pCompHit)->GetOwner());

    if (pCompHit && ISA(pCompHit, ZBSymbol))
        return ((ZBSymbol*)pCompHit)->OnToolTip(toolTipText, pt, mode);
    else
    if (pCompHit && ISA(pCompHit, ZBLinkSymbol))
        return ((ZBLinkSymbol*)pCompHit)->OnToolTip(toolTipText, pt, mode);

    return false;
}

// ******************************************************************************************************************
// *                                Fonctions de gestion des logos et trames de fond                                *
// ******************************************************************************************************************

// **************************************** Fonctions de gestion des événements *************************************

// Cette fonction est appelée lorsque l'utilisateur désire ajouter un logo a ses pages.
void ZDProcessGraphModelController::OnAddWatermarkModelLogo()
{
    CString Filename;

    // JMR-MODIF - Le 7 octobre 2005 - Le corps de la fonction est déplaçé dans la fonction AskImageFilename.
    if (AskImageFilename(Filename) != TRUE)
    {
        return;
    }

    // JMR-MODIF - Le 6 octobre 2005 - Dorénavant, la suite de la fonction se trouve dans SetImage.
    SetImage(Filename, TRUE);
}

// Cette fonction est appelée lorsque l'entrée "Ajouter un logo" du menu doit être mise à jour.
void ZDProcessGraphModelController::OnUpdateAddWatermarkModelLogo(CCmdUI* pCmdUI)
{}

// Cette fonction est appelée lorsque l'utilisateur désire ajouter une trame de fond a ses pages.
void ZDProcessGraphModelController::OnSetBackgroundImage()
{
    CString Filename;

    // JMR-MODIF - Le 7 octobre 2005 - Le corps de la fonction est déplaçé dans la fonction AskImageFilename.
    if (AskImageFilename(Filename) != TRUE)
    {
        return;
    }

    // JMR-MODIF - Le 20 juillet 2005 - Dorénavant, la suite de la fonction se trouve dans SetImage.
    SetImage(Filename, FALSE);
}

// Cette fonction est appelée lorsque l'entrée "Ajouter une trame de fond" du menu doit être mise à jour.
void ZDProcessGraphModelController::OnUpdateSetBackgroundImage(CCmdUI* pCmdUI)
{}

// Cette fonction est appelée lorsque l'utilisateur désire supprimer le logo dans ses pages.
void ZDProcessGraphModelController::OnClearWatermarkModelLogo()
{
    // JMR-MODIF - Le 7 octobre 2005 - Le corps de la fonction est déplaçé dans la fonction ClearImage.
    ClearImage();
}

// Cette fonction est appelée lorsque l'utilisateur désire supprimer le logo dans ses pages.
void ZDProcessGraphModelController::OnClearBackgroundImage()
{
    // JMR-MODIF - Le 7 octobre 2005 - Le corps de la fonction est déplaçé dans la fonction ClearImage.
    ClearImage();
}

// ***************************************** Fonctions de gestion des fichiers **************************************

// JMR-MODIF - Le 7 octobre 2005 -
// Cette fonction permet à l'utilisateur de choisir le fichier d'image à travers une boîte de dialogue.
BOOL ZDProcessGraphModelController::AskImageFilename(CString& Filename)
{
    CString title;
    VERIFY(title.LoadString(IDS_IMAGEFILE_CHOOSETITLE));

    CString strRes;
    CString strFilter;

    // append the "*.jpg" files filter
    VERIFY(strRes.LoadString(IDS_EXPORTFILE_FILTERJPEG));
    strFilter += strRes;
    strFilter += (char)'\0';        // next string please
    strFilter += _T("*.jpg");
    strFilter += (char)'\0';        // last string

    // set the "*.gif" files filter
    VERIFY(strRes.LoadString(IDS_EXPORTFILE_FILTERGIF));
    strFilter += strRes;
    strFilter += (char)'\0';        // next string please
    strFilter += _T("*.gif");
    strFilter += (char)'\0';        // last string

    // append the "*.pcx" files filter
    VERIFY(strRes.LoadString(IDS_EXPORTFILE_FILTERPCX));
    strFilter += strRes;
    strFilter += (char)'\0';        // next string please
    strFilter += _T("*.pcx");
    strFilter += (char)'\0';        // last string

    // append the "*.dib" files filter
    VERIFY(strRes.LoadString(IDS_EXPORTFILE_FILTERDIB));
    strFilter += strRes;
    strFilter += (char)'\0';        // next string please
    strFilter += _T("*.dib");
    strFilter += (char)'\0';        // last string

    // append the "*.tga" files filter
    VERIFY(strRes.LoadString(IDS_EXPORTFILE_FILTERTGA));
    strFilter += strRes;
    strFilter += (char)'\0';        // next string please
    strFilter += _T("*.tga");
    strFilter += (char)'\0';        // last string

    // append the "*.tif" files filter
    VERIFY(strRes.LoadString(IDS_EXPORTFILE_FILTERTIF));
    strFilter += strRes;
    strFilter += (char)'\0';        // next string please
    strFilter += _T("*.tif");
    strFilter += (char)'\0';        // last string

    PSS_FileDialog fileDialog(title, strFilter, 6, _T(""));

    if (fileDialog.DoModal() == IDCANCEL)
    {
        Filename = _T("");
        return FALSE;
    }

    Filename = fileDialog.GetFileName();
    return TRUE;
}

// ******************************************* Fonctions de gestion des images **************************************

// JMR-MODIF - Le 20 juillet 2005 - Ajout de la fonction SetImage, afin de pouvoir inclure la trame de fond.
void ZDProcessGraphModelController::SetImage(CString Filename, BOOL IsLogo)
{
    ZDProcessGraphModelMdl* pModel = GetRootModel();
    ASSERT(pModel);

    SECImage* pImage = ZIProcessGraphModelView::LoadImageFromFile(Filename);

    // JMR-MODIF - Le 5 août 2005 - Ajout du code pour permettre à l'utilisateur de réattribuer le fichier si celui-ci
    // a été déplaçé, supprimé ou endommagé.
    if (!pImage)
    {
        CString m_StrMsg = _T("");
        m_StrMsg.Format(IDS_WARN_IMGFILECORRUPTED, Filename);

        int myResult = AfxMessageBox(m_StrMsg, MB_YESNO);

        if (myResult == 7)
        {
            pModel->SetBkGndFilename(_T(""));
            return;
        }
        else
        {
            if (!IsLogo)
            {
                OnSetBackgroundImage();
            }
            else
            {
                OnAddWatermarkModelLogo();
            }
        }

        return;
    }

    SECDib* pDibImage = new SECDib();
    ASSERT(pDibImage);

    pDibImage->ConvertImage(pImage);

    if (!IsLogo)
    {
        //Create the component
        CODImageComponent Square;

        if (Square.Load(*pDibImage, FALSE))
        {
            Square.SetType(_T("Square"));
            Square.SetSize(pDibImage->dwGetWidth(), pDibImage->dwGetHeight());

            pModel->SetBackgroundComponent(Square, true, true);
            pModel->SetIsLogo(FALSE);
        }
    }
    else
    {
        //Create the component
        CODImageComponent Logo;

        if (Logo.Load(*pDibImage, TRUE))
        {
            Logo.SetType(_T("Logo"));
            Logo.SetSize(pDibImage->dwGetWidth(), pDibImage->dwGetHeight());
            Logo.MoveOrigin(10, 10);

            pModel->SetBackgroundComponent(Logo, true, false);
            pModel->SetIsLogo(TRUE);
        }
    }

    delete pDibImage;
    delete pImage;

    // JMR-MODIF - Le 5 août 2005 - Ajout du code d'initialisation du nom du fichier de tramage.
    pModel->SetBkGndFilename(Filename);

    // Refresh the viewport
    ASSERT(GetViewport());
    GetViewport()->UpdateAll();
}

// JMR-MODIF - Le 7 octobre 2005 - Cette fonction permet de nettoyer l'arrière plan.
void ZDProcessGraphModelController::ClearImage()
{
    ZDProcessGraphModelMdl* pModel = GetRootModel();
    ASSERT(pModel);
    pModel->ClearBackgroundComponent(true);

    // JMR-MODIF - Le 5 août 2005 - Ajout du code de réinitialisation du nom du fichier de tramage.
    pModel->SetBkGndFilename(_T(""));

    // Refresh the viewport
    ASSERT(GetViewport());
    GetViewport()->UpdateAll();
}
