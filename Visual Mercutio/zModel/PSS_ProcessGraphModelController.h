/****************************************************************************
 * ==> PSS_ProcessGraphModelController -------------------------------------*
 ****************************************************************************
 * Description : Provides a process graphic model controller                *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessGraphModelControllerH
#define PSS_ProcessGraphModelControllerH

#if _MSC_VER >= 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
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
#include "PSS_LinkSymbol.h"
#include "ZVDynamicAttributesDuplication.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class definition
class PSS_ProcessGraphModelViewport;
class PSS_ProcessGraphModelView;
class PSS_ProcessGraphModelDoc;
class PSS_ProcessGraphModelMdl;
class ZDProcessGraphPage;

#ifdef _ZMODELEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Process graphic model controller. This class processes global operations on model,
* like e.g the cut/copy/paste operations, the background image management, the page
* management (addig a new page, ...), the zoom/pan effects, ...
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessGraphModelController : public CODController,
                                                      public PSS_Subject,
                                                      public PSS_Observer
{
    public:
        /**
        * Constructor
        *@param pViewport - viewport
        */
        PSS_ProcessGraphModelController(PSS_ProcessGraphModelViewport* pViewport);

        /**
        * Gets the view
        *@return the view
        */
        virtual       PSS_ProcessGraphModelView* GetView();
        virtual const PSS_ProcessGraphModelView* GetView() const;

        /**
        * Gets the viewport
        *@return the viewport
        */
        virtual PSS_ProcessGraphModelViewport* GetViewport();

        /**
        * Gets the document
        *@return the document
        */
        virtual       CDocument* GetDocument();
        virtual const CDocument* GetDocument() const;

        /**
        * Gets the model
        *@return the model
        */
        virtual PSS_ProcessGraphModelMdl* GetModel();

        /**
        * Gets the root model
        *@return the root model
        */
        virtual PSS_ProcessGraphModelMdl* GetRootModel();

        /**
        * Refreshes the model tree
        */
        virtual void RefreshModelTree();

        /**
        * Creates the context menu
        *@return the newly created context menu
        */
        virtual CMenu* CreateContextMenu();

        /**
        * Creates a view from the model
        *@param pModel - the model
        *@param pParentModel - the parent model
        *@return the newly created viewport, NULL on error
        */
        virtual PSS_ProcessGraphModelViewport* CreateViewFromModel(PSS_ProcessGraphModelMdl* pModel,
                                                                   PSS_ProcessGraphModelMdl* pParentModel);

        /**
        * Browses the model
        *@param pModel - the model
        *@param pParentModel - the parent model
        *@return the viewport, NULL on error
        */
        virtual PSS_ProcessGraphModelViewport* BrowseModel(PSS_ProcessGraphModelMdl* pModel,
                                                           PSS_ProcessGraphModelMdl* pParentModel);

        /**
        * Opens a page
        *@param pPage - the page to open
        *@return the viewport, NULL on error
        */
        virtual PSS_ProcessGraphModelViewport* OpenPage(ZDProcessGraphPage* pPage);

        /**
        * Opens a symbol
        *@param pComp - the component
        *@return the viewport, NULL on error
        */
        virtual PSS_ProcessGraphModelViewport* OpenSymbol(CODComponent* pComp);

        /**
        * Ensures a symbol is visible
        *@param pComp - the component
        *@return the viewport, NULL on error
        */
        virtual PSS_ProcessGraphModelViewport* EnsureSymbolVisible(CODComponent* pComp);

        /**
        * Browses the local symbol
        *@param pComp - the component
        *@return the viewport, NULL on error
        */
        virtual PSS_ProcessGraphModelViewport* BrowseLocalSymbol(CODComponent* pComp);

        /**
        * Checks if the item to drop is accepted by the model
        *@param pObj - the dropped object
        *@param point - the drop point
        *@return true if the model accepts the item to drop, otherwise false
        */
        virtual bool AcceptDropItemToModel(CObject* pObj, const CPoint& point);

        /**
        * Drops an item in the model
        *@param pObj - the dropped object
        *@param point - the drop point
        *@return true on success, otherwise false
        */
        virtual bool DropItemToModel(CObject* pObj, const CPoint& point);

        /**
        * Checks if the item to drop is accepted
        *@param pObj - the dropped object
        *@param point - the drop point
        *@return true if the item to drop is accepted, otherwise false
        */
        virtual bool AcceptDropItem(CObject* pObj, const CPoint& point);

        /**
        * Drops an item
        *@param pObj - the dropped object
        *@param point - the drop point
        *@return true on success, otherwise false
        */
        virtual bool DropItem(CObject* pObj, const CPoint& point);

        /**
        * Edits the name
        *@param pCompToEdit - component to edit
        */
        virtual void EditName(CODComponent* pCompToEdit);

        /**
        * Edits the comment
        *@param pCompToEdit - component to edit
        */
        virtual void EditComment(CODComponent* pCompToEdit);

        /**
        * Called when a zoom in is performed on the view
        */
        virtual void ViewZoomIn();

        /**
        * Called when a zoom out is performed on the view
        */
        virtual void ViewZoomOut();

        /**
        * Redraws the component
        *@param comp - the component to redraw
        */
        virtual void RedrawComponent(CODComponent& comp);

        /**
        * Redraws all the components in the component set
        *@param set - the set containing the components to redraw
        */
        virtual void RedrawComponentSet(CODComponentSet& set);

        /**
        * Selects all the components
        */
        virtual void SelectAllComponents();

        /**
        * Unselects all the components
        */
        virtual void UnselectAllComponents();

        /**
        * Selects a component
        *@param comp - the component to select
        */
        virtual void SelectComponent(CODComponent& comp);

        /**
        * Selects all the components in the component set
        *@param comp - the set containing the components to select
        */
        virtual void SelectComponentSet(CODComponentSet& set);

        /**
        * Unselects the component
        *@param comp - the component to unselect
        */
        virtual void UnselectComponent(CODComponent& comp);

        /**
        * Unselects the component
        *@param set - the set containing the components to unselect
        */
        virtual void UnselectComponentSet(CODComponentSet& set);

        /**
        * Checks if a component is selected
        *@param comp - the component to check
        *@return true if the component is selcted, otherwise false
        */
        virtual bool IsComponentSelected(CODComponent& comp);

        /**
        * Checks if do browses in the same window
        *@return if do browses in the same window, otherwise false
        */
        virtual bool GetBrowseInSameWindow() const;

        /**
        * Sets if do browse in the same window
        *@param value - if true, the browse should be done in the same window
        */
        virtual void SetBrowseInSameWindow(bool value);

        /**
        * Inserts a new symbol in the model
        *@param pComp - symbol component
        *@param flags - flags
        *@param point - insertion point
        *@param includePostCreation - if true, the post-creation will be included
        *@return the newly inserted symbol
        */
        virtual CODComponent* InsertSymbol(CODComponent* pComp, UINT flags, const CPoint& point, bool includePostCreation);

        /**
        * Inserts a new symbol in the model
        *@param flags - flags
        *@param point - insertion point
        *@param includePostCreation - if true, the post-creation will be included
        *@return the newly inserted symbol
        */
        virtual CODComponent* InsertSymbol(UINT flags, const CPoint& point, bool includePostCreation);

        /**
        * Deletes a symbol from the model
        *@param pComp - component to delete
        */
        virtual void DeleteComponent(CODComponent* pComp);

        /**
        * Deletes all symbol contained in the set from the model
        *@param pCompSet - set containing the components to delete
        */
        virtual void DeleteComponents(CODComponentSet* pCompSet);

        /**
        * Validates the cut and copy operations
        *@return TRUE if cut and copy operations are validated, otherwise FALSE
        */
        virtual BOOL ValidateCutCopyOperations();

        /**
        * Filters the selection
        *@param modifyFlag - if TRUE, the modifiy flag will be set
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL FilterSelection(BOOL modifyFlag = FALSE);

        /**
        * Refreshes the selection properties
        */
        virtual void RefreshSelectionProperties();

        /**
        * Refreshes all the symbols
        */
        virtual void RefreshAllSymbols();

        /**
        * Releases the clipboard
        */
        virtual void ReleaseClipboard();

        /**
        * Sets the background image
        *@param fileName - image file name
        *@param isLogo - if true, the image is a logo
        */
        virtual void SetImage(const CString& fileName, BOOL isLogo);

        /**
        * Clears the background image
        */
        virtual void ClearImage();

        /**
        * Gets the current background image file name
        *@param[out] fileName - the image file name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL GetImageFileName(CString& fileName);

        /**
        * Animates the node
        *@param node - the node to animate
        *@param useColor - if true, the color should be used
        *@param color - the color, ignored if -1
        *@param animateCounter - the animate counter
        */
        virtual void AnimateNode(IODNode&    node,
                                 bool        useColor       =  false,
                                 COLORREF    color          = -1,
                                 std::size_t animateCounter =  4);

        /**
        * Animates all the nodes in the array
        *@param nodes - the array containing the nodes to animate
        *@param useColor - if true, the color should be used
        *@param color - the color, ignored if -1
        *@param animateCounter - the animate counter
        */
        virtual void AnimateNodes(CODNodeArray& nodes,
                                  bool          useColor       =  false,
                                  COLORREF      color          = -1,
                                  std::size_t   animateCounter =  4);

        /**
        * Animates the edge
        *@param edge - the edge to animate
        *@param useColor - if true, the color should be used
        *@param color - the color, ignored if -1
        *@param animateCounter - the animate counter
        */
        virtual void AnimateEdge(IODEdge&    edge,
                                 bool        useColor       =  false,
                                 COLORREF    color          = -1,
                                 std::size_t animateCounter =  4);

        /**
        * Animates all the edges in the array
        *@param edges - the array containing the edges to animate
        *@param useColor - if true, the color should be used
        *@param color - the color, ignored if -1
        *@param animateCounter - the animate counter
        */
        virtual void AnimateEdges(CODEdgeArray& edges,
                                  bool          useColor       =  false,
                                  COLORREF      color          = -1,
                                  std::size_t   animateCounter =  4);

        /**
        * Animates the symbol
        *@param symbol - the symbol to animate
        *@param useColor - if true, the color should be used
        *@param color - the color, ignored if -1
        *@param animateCounter - the animate counter
        */
        virtual void AnimateSymbol(CODSymbolComponent& symbol,
                              bool                     useColor       =  false,
                              COLORREF                 color          = -1,
                              std::size_t              animateCounter =  4);

        /**
        * Animates all the symbols contained in the set
        *@param symbols - the set containing the symbols to animate
        *@param useColor - if true, the color should be used
        *@param color - the color, ignored if -1
        *@param animateCounter - the animate counter
        */
        virtual void AnimateSymbols(CODComponentSet& symbols,
                                    bool             useColor       =  false,
                                    COLORREF         color          = -1,
                                    std::size_t      animateCounter =  4);

        /**
        * Animates the link
        *@param link - the link to animate
        *@param useColor - if true, the color should be used
        *@param color - the color, ignored if -1
        *@param animateCounter - the animate counter
        */
        virtual void AnimateLink(CODLinkComponent& link,
                                 bool              useColor       =  false,
                                 COLORREF          color          = -1,
                                 std::size_t       animateCounter =  4);

        /**
        * Animates all the links in the set
        *@param links - the set containing the links to animate
        *@param useColor - if true, the color should be used
        *@param color - the color, ignored if -1
        *@param animateCounter - the animate counter
        */
        virtual void AnimateLinks(CODComponentSet& set,
                                  bool             useColor       =  false,
                                  COLORREF         color          = -1,
                                  std::size_t      animateCounter =  4);

        /**
        * Creates and executes a delete command
        *@param pCompSet - the set containing the target components
        *@return the delete command, NULL on error
        */
        virtual CODDeleteCommand* ExecuteDeleteCommand(CODComponentSet* pCompSet);

        /**
        * Creates and executes an insert command for a single component
        *@param pComp - the target component
        *@param allowDuplicates - if TRUE, the duplicates are allowed
        *@return the insert command, NULL on error
        */
        virtual CODInsertCommand* ExecuteInsertCommand(CODComponent* pComp, const BOOL allowDuplicates = TRUE);

        /**
        * Creates and executes an insert command for a set of components
        *@param pCompSet - the set containing the target components
        *@param allowDuplicates - if TRUE, the duplicates are allowed
        *@return the insert command, NULL on error
        */
        virtual CODInsertCommand* ExecuteInsertCommand(CODComponentSet* pCompSet, const BOOL allowDuplicates = TRUE);

        /**
        * Creates and executes a link command
        *@param pointArray - the link point array
        *@param pSourcePort - the source port
        *@param pTargetPort - the target port
        *@param pSourceEndPoint - the source end point
        *@param pTargetEndPoint - the target end point
        *@return the link command, NULL on error
        */
        virtual CODLinkCommand* ExecuteLinkCommand(const CODPointArray& pointArray,
                                                   CODPortComponent*    pSourcePort,
                                                   CODPortComponent*    pTargetPort,
                                                   CODEndpoint*         pSourceEndPoint = NULL,
                                                   CODEndpoint*         pTargetEndPoint = NULL);

        /**
        * Creates and executes a link command
        *@param pLinkComp - the link component
        *@param pointArray - the link point array
        *@param pSourcePort - the source port
        *@param pTargetPort - the target port
        *@return the link command, NULL on error
        */
        virtual CODLinkCommand* ExecuteLinkCommand(CODLinkComponent*    pLinkComp,
                                                   const CODPointArray& pointArray,
                                                   CODPortComponent*    pSourcePort,
                                                   CODPortComponent*    pTargetPort);

        /**
        * Creates and executes a link command
        *@param pLinkComp - the link component
        *@param pSourcePort - the source port
        *@param pTargetPort - the target port
        *@return the link command, NULL on error
        */
        virtual CODLinkCommand* ExecuteLinkCommand(CODLinkComponent* pLinkComp,
                                                   CODPortComponent* pSourcePort,
                                                   CODPortComponent* pTargetPort);

        /**
        * Checks if the object can be duplicated
        *@param pCompSet - the component set at which the component belongs
        *@return true if the object can be duplicated, otherwise false
        */
        virtual inline bool CanDuplicateObject(CODComponentSet* pCompSet);

        /**
        * Called when the controller is initializing
        */
        virtual void OnInitialUpdate();

        /**
        * Called when the model document has changed
        */
        virtual void OnModelDocumentHasChanged();

        /**
        * Called when the property edition is starting
        */
        virtual void OnStartEditProperty();

        /**
        * Called when the selection changes
        *@param pChangedSet - the set containing the changed selection
        */
        virtual void OnSelectionChange(CODComponentSet* pChangedSet);

        /**
        * Called when the subject sent a message to this observer
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

        /**
        * Called when a tooltip is required
        *@param[in, out] toolTipText - tooltip text, formatted tooltip text on function ends
        *@param point - hit point
        *@param mode - tooltip mode
        *@return true if tooltip can be shown, otherwise false
        */
        virtual bool OnToolTip(CString&                toolTipText,
                               const CPoint&           point,
                               ZBSymbol::IEToolTipMode mode = ZBSymbol::IE_TT_Normal);

    protected:
        static CODSymbolComponent* m_pFormatPainterSymbol;
        static CODSymbolComponent* m_LastSelectedElement;
        static CODComponentSet     m_CutSet;
        static CODComponentSet     m_CopySet;
        static CODComponentSet     m_SymbolAddedSet;
        static CPoint              m_SavedEditPosition;
        static UINT                m_CurrentCommandID;
        static bool                m_CutCommand;
        static bool                m_IsInFormatPainter;
               CODSymbolComponent* m_pSymbolHit;
               CODLabelComponent*  m_pLabelHit;
               CMenu               m_SymbolRightMainMenu;
               CMenu               m_SymbolRefRightMainMenu;
               CMenu*              m_pRightSubMenu;
               int                 m_CurrentCursor;
               bool                m_IsEditingSymbolName;
               bool                m_IsEditingSymbolComment;
               bool                m_NewSymbolCreated;

        virtual ~PSS_ProcessGraphModelController();

        /**
        * Notifies the observers about the symbol selection
        *@param pComp - the selected symbol
        */
        virtual void NotifySymbolSelected(CODComponent* pComp);

        /**
        * Begins the text component edition at the point
        *@param flags - the flags
        *@param point - the edition point
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL StartTextEdit(UINT flags, CPoint point);

        /**
        * Ends the text component edition
        *@param flags - the flags
        *@param point - the edition point
        */
        virtual void EndTextEdit(UINT flags, CPoint point);

        /**
        * Inserts a symbol
        *@param flags - the flags
        *@param point - the insertion point
        */
        virtual void InsertSymbol(UINT flags, CPoint point);

        /**
        * Ends the link
        *@param flags - the flags
        *@param point - the insertion point
        */
        virtual void EndLink(UINT flags, CPoint point);

        /**
        * Called by the controller, once the symbol has been completely added and the name edited
        *@param pCompSet - the component set
        */
        virtual void OnSymbolAdded(CODComponentSet* pCompSet);

        /**
        * Called by the controller, once the symbol has been completely duplicated
        *@param pCompSet - the component set
        */
        virtual void OnSymbolDuplicated(CODComponentSet* pCompSet);

        /**
        * Called after a cut and paste operation
        *@param pCompSet - the component set
        */
        virtual void OnPostCutPasteOperation(CODComponentSet* pCompSet);

        /**
        * Assigns the symbol hit
        */
        virtual void AssignSymbolHit();

        /**
        * Assigns the label hit
        */
        virtual void AssignLabelHit();

        /**
        * Determines the referenced symbol
        *@param pCompSet - the component set
        */
        virtual void DetermineReferencedSymbol(CODComponentSet* pCompSet);

        /**
        * Removes the reference symbol
        *@param pCompSet - the component set
        */
        virtual void RemoveReferenceSymbol(CODComponentSet* pCompSet);

        /**
        * Browses the symbol model
        *@param pSymbol - the symbol
        *@return the viewport, NULL on error
        */
        virtual PSS_ProcessGraphModelViewport* BrowseSymbolModel(ZBSymbol* pSymbol);

        /**
        * Browses the link symbol model
        *@param pSymbol - the symbol
        *@return the viewport, NULL on error
        */
        virtual PSS_ProcessGraphModelViewport* BrowseLinkSymbolModel(PSS_LinkSymbol* pSymbol);

        /**
        * Clears the selection to set
        */
        virtual inline void ClearSelectionToSet();

        /**
        * Copies the selection to set
        */
        virtual void CopySelectionToSet();

        /**
        * Clears the symbol added set
        */
        virtual inline void ClearSymbolAddedSet();

        /**
        * Copies the symbol to the symbol added set
        *@param pComp - the symbol component to copy
        */
        virtual inline void CopySymbolToSymbolAddedSet(CODComponent* pComp);

        /**
        * Copies all the symbols to the symbol added set
        *@param pCompSet - the set containing the symbol components to copy
        */
        virtual void CopySymbolsToSymbolAddedSet(CODComponentSet* pCompSet);

        /**
        * Copies all the symbols to the clipboard
        *@param pCompSet - the set containing the symbol components to copy
        */
        virtual void CopyToClipboardSet(CODComponentSet* pCompSet);

        /**
        * Empties the clipboard set
        */
        virtual void EmptyClipboardSet();

        /**
        * Stores the components to the set
        *@param compSet - the set containing the components to store
        */
        virtual void StoreComponentsToSet(const CODComponentSet& compSet);

        /**
        * Applies the format to the symbol
        *@param pComp - the symbol component on which the format should be applied
        */
        virtual void ApplyFormatToSymbol(CODComponent* pComp);

        /// Generated message map functions
        //{{AFX_MSG(PSS_ProcessGraphModelController)
        afx_msg void OnMouseMove(UINT flags, CPoint point);
        afx_msg void OnLButtonDblClk(UINT flags, CPoint point);
        afx_msg void OnLButtonDown(UINT flags, CPoint point);
        afx_msg void OnLButtonUp(UINT flags, CPoint point);
        afx_msg void OnRButtonUp(UINT flags, CPoint point);
        afx_msg void OnTimer(SEC_UINT eventID);
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
        afx_msg void OnGoInSymbol();
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

    private:
        static CODNodeArray    m_AnimatedNodes;
        static CODEdgeArray    m_AnimatedEdges;
        static CODComponentSet m_AnimatedComponents;
        static COLORREF        m_AnimatedColor;
        static PSS_Date        m_TimerStartTime;
        static UINT            m_Timer;
        static int             m_AnimateCounter;
        static int             m_AnimateSeconds;
        static bool            m_SelectionChanged;
        static bool            m_AnimatedUseColor;
        static bool            m_TimerInitialized;

        /**
        * Animates the node
        */
        void AnimateNodes();

        /**
        * Animates the edges
        */
        void AnimateEdges();

        /**
        * Animates the symbols
        */
        void AnimateSymbols();

        /**
        * Changes the color on the nodes
        */
        void ChangeColorNodes();

        /**
        * Changes the color on the edges
        */
        void ChangeColorEdges();

        /**
        * Changes the color on the symbols
        */
        void ChangeColorSymbols();

        /**
        * Changes the back color on the nodes
        */
        void ChangeBackColorNodes();

        /**
        * Changes the back color on the edges
        */
        void ChangeBackColorEdges();

        /**
        * Changes the back color on the symbols
        */
        void ChangeBackColorSymbols();

        /**
        * Ends the animate timer
        */
        void EndAnimateTimer();
};

//---------------------------------------------------------------------------
// PSS_ProcessGraphModelController
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelController::CanDuplicateObject(CODComponentSet* pCompSet)
{
    return true;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::ClearSelectionToSet()
{
    m_CopySet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::ClearSymbolAddedSet()
{
    m_SymbolAddedSet.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelController::CopySymbolToSymbolAddedSet(CODComponent* pComp)
{
    m_SymbolAddedSet.Add(pComp);
}
//---------------------------------------------------------------------------

#endif
