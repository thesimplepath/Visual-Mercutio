/****************************************************************************
 * ==> PSS_ProcessModelTree ------------------------------------------------*
 ****************************************************************************
 * Description : Provides a process model tree                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessModelTreeH
#define PSS_ProcessModelTreeH

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
#include "zBaseLib\PSS_TreeCtrl.h"
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
* Process model tree
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessModelTree : public PSS_TreeCtrl
{
    DECLARE_DYNCREATE(PSS_ProcessModelTree)

    public:
        PSS_ProcessModelTree();
        virtual ~PSS_ProcessModelTree();

        /**
        * Initializes the tree
        *@param modelName - the model name
        *@param pModelSet - the model set
        *@param imageResID - the image resource identifier
        *@param pSet - the runime class set
        *@param enableMenuItems - if true, the menu items are enabled
        */
        virtual void Initialize(const CString&       modelName,
                                PSS_ModelSet*        pModelSet,
                                UINT                 imageResID,
                                PSS_RuntimeClassSet* pSet = NULL,
                                bool                 enableMenuItems = true);

        /**
        * Refreshes the tree
        */
        virtual void Refresh();

        /**
        * Empties the tree
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
        virtual void AddModel(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Removes a model
        *@param pModel - the model to remove
        */
        virtual void RemoveModel(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Adds a model set
        *@param pModelSet - the model set to add
        */
        virtual void AddModelSet(PSS_ModelSet* pModelSet);

        /**
        * Removes a model set
        *@param pModel - the model set to remove
        */
        virtual void RemoveModelSet(PSS_ModelSet* pModelSet);

        /**
        * Adds a symbol
        *@param pSymbol - the symbol to add
        *@param pModel - the model to add to, if NULL the symbol will be added to the root model
        *@param checkUnique - if true, the symbol will be added only if unique in the tree
        */
        virtual void AddSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel = NULL, bool checkUnique = true);

        /**
        * Removes a symbol
        *@param pSymbol - the symbol to remove
        *@param pModel - the model to remove from, if NULL the symbol will be removed from the root model
        */
        virtual void RemoveSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel = NULL);

        /**
        * Modifies a symbol
        *@param pSymbol - the symbol to modify
        *@param pModel - the model
        */
        virtual void ModifySymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel = NULL);

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

        // todo FIXME -cBug -oJean: On the right symbol list, several popup menu entries, like "Add an external app...",
        //                          doesn't work. Please check and fix
        /// Generated message map functions
        //{{AFX_MSG(PSS_ProcessModelTree)
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

    private:
        /**
        * Called when a double click is performed on the tree
        */
        void OnDoubleClick();
};

//---------------------------------------------------------------------------
// PSS_ProcessModelTree
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessModelTree::GetSelectedModel()
{
    return m_ModelTree.GetSelectedModel();
}
//---------------------------------------------------------------------------
CODSymbolComponent* PSS_ProcessModelTree::GetSelectedSymbol()
{
    return m_ModelTree.GetSelectedSymbol();
}
//---------------------------------------------------------------------------
PSS_ProcessGraphPage* PSS_ProcessModelTree::GetSelectedPage()
{
    return m_ModelTree.GetSelectedPage();
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessModelTree::GetSelectedOwnerModel()
{
    return m_ModelTree.GetSelectedOwnerModel();
}
//---------------------------------------------------------------------------
bool PSS_ProcessModelTree::IsRootSelected() const
{
    return m_ModelTree.IsRootSelected();
}
//---------------------------------------------------------------------------
bool PSS_ProcessModelTree::IsDocumentSelected() const
{
    return m_ModelTree.IsDocumentSelected();
}
//---------------------------------------------------------------------------
int PSS_ProcessModelTree::GetIndexOfNoDropImage() const
{
    return 12;
}
//---------------------------------------------------------------------------

#endif
