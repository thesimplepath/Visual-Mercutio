/************************************************************************************************************
 *                                          Classe ZDProcessGraphModelController                                *
 ************************************************************************************************************
 * Cette classe s'occupe de la gestion des modèles. Son rôle est d'effectuer les opérations globales sur    *
 * les modèles, tels que la gestion des couper-copier-coller, la gestion des trames de fond, l'introduction    *
 * de nouvelles pages, ou la gestion des zooms.                                                                *
 ************************************************************************************************************/

#if !defined(AFX_ProcGraphModelCtlr_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_)
#define AFX_ProcGraphModelCtlr_H__80924751_0CFB_414E_B0E6_5F13173E43F9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

 // Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\PSS_Date.h"
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "ZBSymbol.h"
#include "ZBLinkSymbol.h"
#include "ZVDynamicAttributesDuplication.h"

class ZIProcessGraphModelViewport;
class ZIProcessGraphModelView;
class ZDProcessGraphModelDoc;
class ZDProcessGraphModelMdl;
class ZDProcessGraphPage;

#ifdef _ZMODELEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 16 mai 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

class AFX_EXT_CLASS ZDProcessGraphModelController : public CODController, public PSS_Subject, public PSS_Observer
{
public:

    ZDProcessGraphModelController(ZIProcessGraphModelViewport* pViewport);

    virtual void OnInitialUpdate();

    ZIProcessGraphModelView*                GetView();
    ZIProcessGraphModelView*                GetViewConstPtr() const;
    ZIProcessGraphModelViewport*            GetViewport();
    ZIProcessGraphModelViewport*            GetViewportConstPtr() const;
    CDocument*                                GetDocument();
    CDocument*                                GetDocumentConstPtr() const;
    ZDProcessGraphModelMdl*                    GetModel();
    ZDProcessGraphModelMdl*                    GetRootModel();
    void                                    RefreshModelTree();

    virtual CMenu*                            CreateContextMenu();

    virtual ZIProcessGraphModelViewport*    BrowseModel(ZDProcessGraphModelMdl* pModel,
                                                        ZDProcessGraphModelMdl* pParentModel);

    virtual ZIProcessGraphModelViewport*    CreateViewFromModel(ZDProcessGraphModelMdl* pModel,
                                                                ZDProcessGraphModelMdl* pParentModel);

    virtual ZIProcessGraphModelViewport*    OpenSymbol(CODComponent* pComp);
    virtual ZIProcessGraphModelViewport*    EnsureSymbolVisible(CODComponent* pComp);
    virtual ZIProcessGraphModelViewport*    BrowseLocalSymbol(CODComponent* pComp);

    virtual ZIProcessGraphModelViewport*    OpenPage(ZDProcessGraphPage* pPage);

    virtual bool                            DropItemToModel(CObject* pObj, CPoint pt);
    virtual bool                            AcceptDropItemToModel(CObject* pObj, CPoint pt);

    virtual bool                            DropItem(CObject* pObj, CPoint pt);
    virtual bool                            AcceptDropItem(CObject* pObj, CPoint pt);

    void                                    EditName(CODComponent* pCompToEdit);
    void                                    EditComment(CODComponent* pCompToEdit);

    // Call back for Zoom In&Out
    virtual void                            ViewZoomIn();
    virtual void                            ViewZoomOut();

    /**
    * Called when a tooltip is required
    *@param[in, out] toolTipText - tooltip text, formatted tooltip text on function ends
    *@param point - hit point
    *@param mode - tooltip mode
    *@return true if tooltip can be shown, otherwise false
    */
    virtual bool OnToolTip(CString& toolTipText, const CPoint& point, ZBSymbol::IEToolTipMode mode = ZBSymbol::IE_TT_Normal);

    // Drawing functions
    void                                    ReDrawComponent(CODComponent& Comp);
    void                                    ReDrawComponentSet(CODComponentSet& Set);

    // Selection functions
    void                                    SelectAllComponents();
    void                                    UnselectAllComponents();
    void                                    SelectComponent(CODComponent& Comp);
    void                                    SelectComponentSet(CODComponentSet& Set);
    void                                    UnselectComponent(CODComponent& Comp);
    void                                    UnselectComponentSet(CODComponentSet& Set);
    bool                                    IsComponentSelected(CODComponent& Comp);

    bool                                    BrowseInSameWindow() const;
    void                                    SetBrowseInSameWindow(bool value);

    // Insert a new symbol on the model
    CODComponent*                            InsertSymbol(CODComponent* pComp,
                                                          UINT nFlags,
                                                          CPoint ptDev,
                                                          bool IncludePostCreation);

    CODComponent*                            InsertSymbol(UINT nFlags, CPoint ptDev, bool IncludePostCreation);

    // Delete a symbol or symbol sets from the model
    void                                    DeleteComponents(CODComponentSet* pCompSet);
    void                                    DeleteComponent(CODComponent* pComp);

    // JMR-MODIF - Le 17 septembre 2006 - Ajout de la fonction ValidateCutCopyOperations.
    BOOL                                    ValidateCutCopyOperations();

    // JMR-MODIF - Le 17 septembre 2006 - Ajout de la fonction FilterSelection.
    BOOL                                    FilterSelection(BOOL ModifyFlag = FALSE);

    // JMR-MODIF - Le 24 décembre 2006 - Ajout de la fonction RefreshSelectionProperties.
    void                                    RefreshSelectionProperties();

    // JMR-MODIF - Le 7 juin 2005 - Ajout de la fonction RefreshAllSymbols
    void                                    RefreshAllSymbols();

    // JMR-MODIF - Le 27 septembre 2006 - Ajout de la fonction ReleaseClipboard
    void                                    ReleaseClipboard();

    // JMR-MODIF - Le 20 juillet 2005 - Ajout de la fonction SetImage et ClearImage.
    void                                    SetImage(CString Filename, BOOL IsLogo);
    void                                    ClearImage();

    // JMR-MODIF - Le 7 octobre 2005 - Ajout de la fonction AskImageFilename.
    BOOL                                    AskImageFilename(CString& Filename);

    // Animation functions
    void    AnimateNode(IODNode& Node, bool UseColor = false, COLORREF col = -1, size_t AnimateCounter = 4);
    void    AnimateNodes(CODNodeArray& Nodes, bool UseColor = false, COLORREF col = -1, size_t AnimateCounter = 4);
    void    AnimateEdge(IODEdge& Edge, bool UseColor = false, COLORREF col = -1, size_t AnimateCounter = 4);
    void    AnimateEdges(CODEdgeArray& Edges, bool UseColor = false, COLORREF col = -1, size_t AnimateCounter = 4);

    void    AnimateSymbol(CODSymbolComponent&    Symbol,
                          bool                    UseColor = false,
                          COLORREF                col = -1,
                          size_t                AnimateCounter = 4);

    void    AnimateSymbols(CODComponentSet&    Set,
                           bool                UseColor = false,
                           COLORREF            col = -1,
                           size_t                AnimateCounter = 4);

    void    AnimateLink(CODLinkComponent&    Link,
                        bool                UseColor = false,
                        COLORREF            col = -1,
                        size_t                AnimateCounter = 4);

    void    AnimateLinks(CODComponentSet&    Set,
                         bool                UseColor = false,
                         COLORREF            col = -1,
                         size_t            AnimateCounter = 4);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZDProcessGraphModelController)
    //}}AFX_VIRTUAL

    virtual void                            OnModelDocumentHasChanged();

    virtual void                            OnAdviseStartPropertyEdition();

    // Observer call back
    virtual void                            OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    /* Called whenever the selection changes. */
    virtual void                            OnSelectionChange(CODComponentSet* pChangedSet);

    //@cmember
    /* Creates and executes a delete command. */
    virtual CODDeleteCommand*                ExecuteDeleteCommand(CODComponentSet* pCompSet);

    /* Creates and executes an insert command for a single component. */
    virtual CODInsertCommand*                ExecuteInsertCommand(CODComponent*    pComp,
                                                                  const BOOL    bAllowDuplicates = TRUE);

    //@cmember
    /* Creates and executes an insert command for a set of components. */
    virtual CODInsertCommand*                ExecuteInsertCommand(CODComponentSet*    pCompSet,
                                                                  const BOOL        bAllowDuplicates = TRUE);

    //@cmember
    /* Creates and executes a link command. */
    virtual CODLinkCommand*                    ExecuteLinkCommand(const CODPointArray&    pointArray,
                                                                  CODPortComponent*        pSourcePort,
                                                                  CODPortComponent*        pTargetPort,
                                                                  CODEndpoint*            pSourceEndpoint = NULL,
                                                                  CODEndpoint*            pTargetEndpoint = NULL);

    //@cmember
    /* Creates and executes a link command. */
    virtual CODLinkCommand*                    ExecuteLinkCommand(CODLinkComponent*        pLinkComp,
                                                                  const CODPointArray&    pointArray,
                                                                  CODPortComponent*        pSourcePort,
                                                                  CODPortComponent*        pTargetPort);

    //@cmember
    /* Creates and executes a link command. */
    virtual CODLinkCommand*                    ExecuteLinkCommand(CODLinkComponent* pLinkComp,
                                                                  CODPortComponent* pSourcePort,
                                                                  CODPortComponent* pTargetPort);

    // Return true if the objects contained in the pCompSet can be duplicated
    virtual bool CanDuplicateObject(CODComponentSet* pCompSet)
    {
        return true;
    }

    // Implementation
protected:

    virtual ~ZDProcessGraphModelController();

    // Generated message map functions
    //{{AFX_MSG(ZDProcessGraphModelController)
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnTimer(SEC_UINT nIDEvent);
    afx_msg void OnSelectAll();
    afx_msg void OnEditClear();
    afx_msg void OnEditCopy();
    afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
    afx_msg void OnEditCut();
    afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
    afx_msg void OnEditPaste();
    afx_msg void OnEditDuplicate();
    afx_msg void OnUpdateEditDuplicate(CCmdUI* pCmdUI);
    afx_msg void OnEditRedo();
    afx_msg void OnEditUndo();
    afx_msg void OnEditName();
    afx_msg void OnUpdateEditName(CCmdUI* pCmdUI);
    afx_msg void OnEditComment();
    afx_msg void OnUpdateEditComment(CCmdUI* pCmdUI);
    afx_msg void OnChangeTextEdit();
    afx_msg void OnGoParentModel();
    afx_msg void OnUpdateGoParentModel(CCmdUI* pCmdUI);
    afx_msg void OnBrowseSourceSymbol();
    afx_msg void OnUpdateBrowseSourceSymbol(CCmdUI* pCmdUI);
    afx_msg void OnFindSymbol();
    afx_msg void OnInsertPage();
    afx_msg void OnRenamePage();
    afx_msg void OnDeletePage();
    afx_msg void OnRenameCurrentPage();
    afx_msg void OnDeleteCurrentPage();
    afx_msg void OnGoinSymbol();
    afx_msg void OnSelectSymbol();
    afx_msg void OnOdMeasurements();
    afx_msg void OnViewZoomIn();
    afx_msg void OnViewZoomOut();
    afx_msg void OnAddNewExtApp();
    afx_msg void OnUpdateAddNewExtApp(CCmdUI* pCmdUI);
    afx_msg void OnAddNewExtFile();
    afx_msg void OnUpdateAddNewExtFile(CCmdUI* pCmdUI);
    afx_msg void OnSetBackgroundImage();
    afx_msg void OnUpdateSetBackgroundImage(CCmdUI* pCmdUI);
    afx_msg void OnClearBackgroundImage();
    afx_msg void OnShowModelBorder();
    afx_msg void OnUpdateShowModelBorder(CCmdUI* pCmdUI);
    afx_msg void OnAddWatermarkModelLogo();
    afx_msg void OnUpdateAddWatermarkModelLogo(CCmdUI* pCmdUI);
    afx_msg void OnClearWatermarkModelLogo();
    afx_msg void OnSymbolShowNameArea();
    afx_msg void OnUpdateSymbolShowNameArea(CCmdUI* pCmdUI);
    afx_msg void OnSymbolShowDescriptionArea();
    afx_msg void OnUpdateSymbolShowDescriptionArea(CCmdUI* pCmdUI);
    afx_msg void OnSymbolShowAttributeArea();
    afx_msg void OnUpdateSymbolShowAttributeArea(CCmdUI* pCmdUI);
    afx_msg void OnSymbolShowLabelAttributes();
    afx_msg void OnUpdateSymbolShowLabelAttributes(CCmdUI* pCmdUI);
    afx_msg void OnSymbolSelectAttributes();
    afx_msg void OnUpdateSymbolSelectAttributes(CCmdUI* pCmdUI);
    afx_msg void OnDynamicAttributesAdd();
    afx_msg void OnUpdateDynamicAttributesAdd(CCmdUI* pCmdUI);
    afx_msg void OnDynamicAttributesDuplicate();
    afx_msg void OnUpdateDynamicAttributesDuplicate(CCmdUI* pCmdUI);
    afx_msg void OnDynamicAttributesDelete();
    afx_msg void OnUpdateDynamicAttributesDelete(CCmdUI* pCmdUI);
    afx_msg void OnRefresh();
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

    // Advise observers on symbol selection
    void                                    NotifySymbolSelected(CODComponent* pComp);

    /* Begin editing the text component at the given point. */
    virtual BOOL                            StartTextEdit(UINT nFlags, CPoint ptDev);

    /* Finish text component editing. */
    virtual void                            EndTextEdit(UINT nFlags, CPoint ptDev);

    /* Called to insert a symbol. */
    virtual void                            InsertSymbol(UINT nFlags, CPoint ptDev);

    /* Called when the link is complete. */
    virtual void                            EndLink(UINT nFlags, CPoint ptDev);

    /* Called by the controller, once the symbol has been completely
       added and the name edited. */
    virtual void                            OnSymbolAdded(CODComponentSet* pCompSet);

    /* Called by the controller, once the symbol has been completely
       duplicated. */
    virtual void                            OnSymbolDuplicated(CODComponentSet* pCompSet);


    virtual void                            OnPostCutPasteOperation(CODComponentSet* pCompSet)
    {};

    void                                    AssignSymbolHit();
    void                                    AssignLabelHit();

    void                                    DetermineReferencedSymbol(CODComponentSet* pCompSet);

    void                                    RemoveReferenceSymbol(CODComponentSet* pCompSet);

    ZIProcessGraphModelViewport*            BrowseSymbolModel(ZBSymbol* pSymbol);
    ZIProcessGraphModelViewport*            BrowseLinkSymbolModel(ZBLinkSymbol* pSymbol);

protected:

    CString                                    AskProcessName();
    void                                    ClearSelectionToSet();
    void                                    CopySelectionToSet();
    void                                    ClearSymbolAddedSet();
    void                                    CopySymbolToSymbolAddedSet(CODComponent* pComp);
    void                                    CopySymbolsToSymbolAddedSet(CODComponentSet* pCompSet);

    void                                    CopyToClipboardSet(CODComponentSet* pCompSet);
    void                                    EmptyClipboardSet();
    void                                    StoreComponentsToSet(const CODComponentSet& setComponents);

    virtual void                            ApplyFormatToSymbol(CODComponent* pComp);

private:

    // Animation functions
    void                                    _AnimateNodes();
    void                                    _AnimateEdges();
    void                                    _AnimateSymbols();
    void                                    _ChangeColorNodes();
    void                                    _ChangeColorEdges();
    void                                    _ChangeColorSymbols();
    void                                    _ChangeBackColorNodes();
    void                                    _ChangeBackColorEdges();
    void                                    _ChangeBackColorSymbols();
    void                                    _EndAnimateTimer();

protected:

    CMenu                                    m_SymbolRightMainMenu;
    CMenu                                    m_SymbolRefRightMainMenu;
    CMenu*                                    m_pRightSubMenu;

    CODSymbolComponent*                        m_pSymbolHit;

    CODLabelComponent*                        m_pLabelHit;

    bool                                    m_IsEditingSymbolName;
    bool                                    m_IsEditingSymbolComment;
    bool                                    m_NewSymbolCreated;

    // JMR-MODIF - Le 5 mai 2006 - Ajout de la variable m_CurrentCursor, afin de sauvegarder les curseurs courants.
    int                                        m_CurrentCursor;

    // Current command ID used to save the last command 
    // when insert a new component
    static UINT                                m_CurrentCommandID;

    // this set is used during symbol copy
    // copy and paste and drag and drop operations
    static CODComponentSet                    m_setCopy;

    // this set is used when symbols are added
    static CODComponentSet                    m_setSymbolAddedSet;

    // This cpoint is used when start editname to keep the position
    static CPoint                            m_savedEditPosition;

    // Flag for knowing if the controler is in format painter process
    static bool                                m_IsInFormatPainter;
    static CODSymbolComponent*                m_pFormatPainterSymbol;

    // JMR-MODIF - Le 29 août 2006 - m_LastSelectedElement : Membre privé devient protected
    static CODSymbolComponent*                m_LastSelectedElement;

private:

    static bool                                m_SelectionChanged;

    // Used for animation
    static CODNodeArray                        m_animateNodes;
    static CODEdgeArray                        m_animateEdges;

    static CODComponentSet                    m_animateComponents;

    static int                                m_nAnimateCounter;
    static int                                m_nAnimateSeconds;

    static bool                                m_AnimatedUseColor;
    static bool                                m_TimerInitialized;

    static COLORREF                            m_AnimatedColor;

    static PSS_Date                            m_StartTimeOfTimer;

    static UINT                                m_nTimer;
};

inline void ZDProcessGraphModelController::ClearSelectionToSet()
{
    m_setCopy.RemoveAll();
}

inline void ZDProcessGraphModelController::ClearSymbolAddedSet()
{
    m_setSymbolAddedSet.RemoveAll();
}

inline void ZDProcessGraphModelController::CopySymbolToSymbolAddedSet(CODComponent* pComp)
{
    m_setSymbolAddedSet.Add(pComp);
}

inline void ZDProcessGraphModelController::CopySymbolsToSymbolAddedSet(CODComponentSet* pCompSet)
{
    if (pCompSet)
    {
        // Copy all pointers
        CODComponentIterator i(pCompSet);

        for (CODComponent* pComp = i.GetFirst(); pComp != NULL; pComp = i.GetNext())
        {
            CopySymbolToSymbolAddedSet(pComp);
        }
    }
}

#endif
