#if !defined(AFX_ZCProcessModelTreeView_H__BF391ECD_8805_4220_A368_C992B623A66E__INCLUDED_)
#define AFX_ZCProcessModelTreeView_H__BF391ECD_8805_4220_A368_C992B623A66E__INCLUDED_

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

/////////////////////////////////////////////////////////////////////////////
// ZCProcessModelTreeView view

class AFX_EXT_CLASS ZCProcessModelTreeView : public PSS_TreeView
{
public:
    ZCProcessModelTreeView();           // protected constructor used by dynamic creation
    virtual ~ZCProcessModelTreeView();
    DECLARE_DYNCREATE(ZCProcessModelTreeView)


    // Operations
public:
    void Initialize(const CString ModelName, PSS_ModelSet* pModelSet, UINT nIDImageRes, PSS_RuntimeClassSet* pSet = NULL, bool EnableMenuItems = true);
    void Refresh();
    void Empty();
    PSS_ProcessGraphModelMdl* GetSelectedModel()
    {
        return m_ModelTree.GetSelectedModel();
    };
    CODSymbolComponent* GetSelectedSymbol()
    {
        return m_ModelTree.GetSelectedSymbol();
    };
    ZDProcessGraphPage* GetSelectedPage()
    {
        return m_ModelTree.GetSelectedPage();
    };
    PSS_ProcessGraphModelMdl* GetSelectedOwnerModel()
    {
        return m_ModelTree.GetSelectedOwnerModel();
    };
    bool IsRootSelected() const
    {
        return m_ModelTree.IsRootSelected();
    };
    bool IsDocumentSelected() const
    {
        return m_ModelTree.IsDocumentSelected();
    };


    void AddModel(PSS_ProcessGraphModelMdl* pModel);
    void RemoveModel(PSS_ProcessGraphModelMdl* pModel);

    void AddModelSet(PSS_ModelSet* pModelSet);
    void RemoveModelSet(PSS_ModelSet* pModelSet);

    void AddSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel = NULL, bool CheckUnique = true);
    void RemoveSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel = NULL);
    void ModifySymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel = NULL);

    ////////////////////////////////////////////////////////////////////
    // Context menu function
    virtual int HasContextMenu(CWnd* pWnd, CPoint point);
    virtual void DisplayContextMenu(CWnd* pWnd, CPoint point);

protected:
    virtual int GetIndexOfNoDropImage() const;

    // Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ZCProcessModelTreeView)
protected:
    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
    //}}AFX_VIRTUAL

// Implementation
protected:
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
protected:
    //{{AFX_MSG(ZCProcessModelTreeView)
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

protected:
    PSS_ModelSet* m_pModelSet;
    PSS_ModelTree m_ModelTree;

private:
    void OnDoubleClick();

protected:
    CMenu                m_SymbolPopupMainMenu;
    CMenu                m_SymbolRefPopupMainMenu;
    CMenu*                m_pPopupSubMenu;
    bool                m_EnableMenuItems;
};


inline int ZCProcessModelTreeView::GetIndexOfNoDropImage() const
{
    return 12;
}

#endif
