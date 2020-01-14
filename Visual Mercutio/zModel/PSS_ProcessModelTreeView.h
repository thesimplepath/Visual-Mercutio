/****************************************************************************
 * ==> PSS_ProcessModelTreeView --------------------------------------------*
 ****************************************************************************
 * Description : Provides a process model tree view                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessModelTreeViewH
#define PSS_ProcessModelTreeViewH

#if _MSC_VER > 1000
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
#include "zBaseLib\PSS_TreeView.h"
#include "PSS_ModelTree.h"

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
* Process model tree view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessModelTreeView : public PSS_TreeView
{
    DECLARE_DYNCREATE(PSS_ProcessModelTreeView)

    public:
        PSS_ProcessModelTreeView();
        virtual ~PSS_ProcessModelTreeView();

        /**
        * Initializes the tree view
        *@param modelName - the model name
        *@param pModelSet - the model set
        *@param imageResID - the image resource identifier
        *@param pSet - the runime class set
        *@param enableMenuItems - if true, the menu items are enabled
        */
        virtual void Initialize(const CString&       modelName,
                                PSS_ModelSet*        pModelSet,
                                UINT                 imageResID,
                                PSS_RuntimeClassSet* pSet            = NULL,
                                bool                 enableMenuItems = true);

        /**
        * Refreshes the tree view
        */
        virtual void Refresh();

        /**
        * Empties the tree view
        */
        virtual void Empty();

        /**
        * Gets the selected model
        *@return the selected model, NULL if no selection or on error
        */
        virtual inline PSS_ProcessGraphModelMdl* GetSelectedModel();

        /**
        * Gets the selected symbol
        *@return the selected symbol, NULL if no selection or on error
        */
        virtual inline CODSymbolComponent* GetSelectedSymbol();

        /**
        * Gets the selected page
        *@return the selected page, NULL if no selection or on error
        */
        virtual inline PSS_ProcessGraphPage* GetSelectedPage();

        /**
        * Gets the selected owner model
        *@return the selected owner model, NULL if no selection or on error
        */
        virtual inline PSS_ProcessGraphModelMdl* GetSelectedOwnerModel();

        /**
        * Checks if the root is selected
        *@return true if the root is selected, otherwise false
        */
        virtual inline bool IsRootSelected() const;

        /**
        * Checks if the document is selected
        *@return true if the document is selected, otherwise false
        */
        virtual inline bool IsDocumentSelected() const;

        /**
        * Adds a model
        *@param pModel - the model to add
        */
        void AddModel(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Removes a model
        *@param pModel - the model to remove
        */
        void RemoveModel(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Adds a model set
        *@param pModelSet - the model set to add
        */
        void AddModelSet(PSS_ModelSet* pModelSet);

        /**
        * Removes a model set
        *@param pModel - the model set to remove
        */
        void RemoveModelSet(PSS_ModelSet* pModelSet);

        /**
        * Adds a symbol
        *@param pSymbol - the symbol to add
        *@param pModel - the model to add to, if NULL the symbol will be added to the root model
        *@param checkUnique - if true, the symbol will be added only if unique in the tree
        */
        void AddSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel = NULL, bool CheckUnique = true);

        /**
        * Removes a symbol
        *@param pSymbol - the symbol to remove
        *@param pModel - the model to remove from, if NULL the symbol will be removed from the root model
        */
        void RemoveSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel = NULL);

        /**
        * Modifies a symbol
        *@param pSymbol - the symbol to modify
        *@param pModel - the model
        */
        void ModifySymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel = NULL);

        /**
        * Checks if the tree contains a context menu
        *@param pWnd - the owner window to check
        *@param point - the mouse cursor position
        *@return the context menu identifier, -1 if no context menu
        */
        virtual int HasContextMenu(CWnd* pWnd, const CPoint& point);

        /**
        * Shows a context menu
        *@param pWnd - the owner window
        *@param point - the mouse cursor point
        *@return the context menu identifier, -1 if no context menu
        */
        virtual void ShowContextMenu(CWnd* pWnd, const CPoint& point);

    protected:
        PSS_ModelSet* m_pModelSet;
        PSS_ModelTree m_ModelTree;
        CMenu         m_SymbolPopupMainMenu;
        CMenu         m_SymbolRefPopupMainMenu;
        CMenu*        m_pPopupSubMenu;
        bool          m_EnableMenuItems;

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ProcessModelTreeView)
        virtual void OnDraw(CDC* pDC);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ProcessModelTreeView)
        afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
        afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
        afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
        afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
        afx_msg void OnModelBrowserEditName();
        afx_msg void OnModelBrowserGoInSymbol();
        afx_msg void OnModelBrowserEditCut();
        afx_msg void OnModelBrowserEditCopy();
        afx_msg void OnModelBrowserEditClear();
        afx_msg void OnModelBrowserProperties();
        afx_msg void OnModelBrowserBrowseSourceSymbol();
        afx_msg void OnModelBrowserSelectSymbol();
        afx_msg void OnInsertModelPage();
        afx_msg void OnRenameModelPage();
        afx_msg void OnDeleteModelPage();
        afx_msg void OnRefresh();
        afx_msg void OnCollapseBranch();
        afx_msg void OnExpandBranch();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Gets the no drop image index
        *@return the no drop image index
        */
        virtual inline int GetIndexOfNoDropImage() const;

        /**
        * Asserts the class validity
        */
        #ifdef _DEBUG
            virtual void AssertValid() const;
        #endif

        /**
        * Dumps the class content
        *@param dc - dump context
        */
        #ifdef _DEBUG
            virtual void Dump(CDumpContext& dc) const;
        #endif

    private:
        /**
        * Called when a double click is performed on the tree view
        */
        void OnDoubleClick();
};

//---------------------------------------------------------------------------
// PSS_ProcessModelTreeView
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessModelTreeView::GetSelectedModel()
{
    return m_ModelTree.GetSelectedModel();
}
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_ProcessModelTreeView::GetSelectedSymbol()
{
    return m_ModelTree.GetSelectedSymbol();
}
//---------------------------------------------------------------------------
PSS_ProcessGraphPage* PSS_ProcessModelTreeView::GetSelectedPage()
{
    return m_ModelTree.GetSelectedPage();
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessModelTreeView::GetSelectedOwnerModel()
{
    return m_ModelTree.GetSelectedOwnerModel();
}
//---------------------------------------------------------------------------
bool PSS_ProcessModelTreeView::IsRootSelected() const
{
    return m_ModelTree.IsRootSelected();
}
//---------------------------------------------------------------------------
bool PSS_ProcessModelTreeView::IsDocumentSelected() const
{
    return m_ModelTree.IsDocumentSelected();
}
//---------------------------------------------------------------------------
int PSS_ProcessModelTreeView::GetIndexOfNoDropImage() const
{
    return 12;
}
//---------------------------------------------------------------------------

#endif
