/****************************************************************************
 * ==> PSS_ProcessWorkspace ------------------------------------------------*
 ****************************************************************************
 * Description : Provides the process workspace                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessWorkspaceH
#define PSS_ProcessWorkspaceH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_WorkspaceTreeCtrl.h"
#include "zWinUtil32\PSS_FormTemplateTreeCtrl.h"
#include "zWinUtil32\PSS_FileWnd.h"
#include "zWinUtil32\PSS_UrlWnd.h"
#include "PSS_ProcessModelDocument.h"
#include "PSS_LogicalSystemView.h"
#include "PSS_UserGroupView.h"
#include "PSS_PrestationsView.h"
#include "PSS_RulesView.h"

//---------------------------------------------------------------------------
// Tab index constant definition
//---------------------------------------------------------------------------
// NOTE the sorting is important. It may be reordered, however the numbers should
// remain consecutive. Any non-consecutive number list (e.g 0-1-2-3-5-6-7-8) may
// cause the application to crash
const int g_WorkspaceTabIndex     = 0;
const int g_ModelDocumentTabIndex = 1;
const int g_UserTabIndex          = 2;
const int g_LogicalSystemTabIndex = 3;
const int g_PrestationsTabIndex   = 4;
const int g_RulesTabIndex         = 5;
const int g_FileTabIndex          = 6;

// NOTE the forms below aren't included in this version. Set a valid number to use
// them, e.g the last number above incremented by 1. Also the SHOW_SCRIPTOR/SHOW_WEBVIEW
// defines should be enabled in the cpp file
const int g_FormTemplateTabIndex  = -1;
const int g_WebTabIndex           = -1;
//---------------------------------------------------------------------------

/**
* Process workspace
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ProcessWorkspace : public SECControlBar,
                             public PSS_Subject,
                             public PSS_Observer
{
    DECLARE_DYNAMIC(PSS_ProcessWorkspace)

    public:
        PSS_ProcessWorkspace();
        virtual ~PSS_ProcessWorkspace();

        /**
        * Initializes the workspace
        */
        virtual void Initialize();

        /**
        * Releases the workspace
        */
        virtual void Release();

        /**
        * Initializes the model document tree
        *@param pModelSet - the model set
        */
        virtual void InitializeModelDocumentTree(PSS_ModelSet* pModelSet);

        /**
        * Adds the documents contained in the model to the tree
        *@param pModel - the model containing the documents to add
        */
        virtual void AddModelDocument(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Adds the documents contained in the models to the tree
        *@param pModel - the model set containing the documents to add
        */
        virtual void AddModelDocumentSet(PSS_ModelSet* pModelSet);

        /**
        * Removes the documents contained in the model from the tree
        *@param pModel - the model containing the documents to remove
        */
        virtual void RemoveModelDocument(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Removes the documents contained in the models to the tree
        *@param pModel - the model set containing the documents to remove
        */
        virtual void RemoveModelDocumentSet(PSS_ModelSet* pModelSet);

        /**
        * Adds the model document symbol to the tree
        *@param pSymbol - the symbol containing the document to add
        *@param pModel - the model owning the symbol
        */
        virtual void AddModelDocumentSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel = NULL);

        /**
        * Modifies the model document symbol on the tree
        *@param pSymbol - the symbol containing the document to modify
        *@param pModel - the model owning the symbol
        */
        virtual void ModifyModelDocumentSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel = NULL);

        /**
        * Removes the model symbol document from the tree
        *@param pSymbol - the symbol containing the document to remove
        *@param pModel - the model owning the symbol
        */
        virtual void RemoveModelDocumentSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel = NULL);

        /**
        * Empties the model document tree
        */
        virtual void EmptyModelDocumentTree();

        /**
        * Refreshes the model document tree
        */
        virtual void RefreshModelDocumentTree();

        /**
        * Initializes the model unit tree
        *@param pModelSet - the model set
        */
        virtual void InitializeModelUnitTree(PSS_ModelSet* pModelSet);

        /**
        * Empties the model unit tree
        */
        virtual void EmptyModelUnitTree();

        /**
        * Refreshes the model unit tree
        */
        virtual void RefreshModelUnitTree();

        /**
        * Adds the units contained in the model to the tree
        *@param pModel - the model containing the units to add
        */
        virtual void AddModelUnit(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Adds the units contained in the models to the tree
        *@param pModelSet - the model set containing the units to add
        */
        virtual void AddModelUnitSet(PSS_ModelSet* pModelSet);

        /**
        * Removes the units contained in the model from the tree
        *@param pModel - the model containing the units to remove
        */
        virtual void RemoveModelUnit(PSS_ProcessGraphModelMdl* pModel);

        /**
        * Removes the units contained in the models from the tree
        *@param pModelSet - the model set containing the units to remove
        */
        virtual void RemoveModelUnitSet(PSS_ModelSet* pModelSet);

        /**
        * Adds the model unit symbol to the tree
        *@param pSymbol - the symbol containing the unit to add
        *@param pModel - the model owning the symbol
        */
        virtual void AddModelUnitSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel = NULL);

        /**
        * Removes the model unit symbol from the tree
        *@param pSymbol - the symbol containing the unit to add
        *@param pModel - the model owning the symbol
        */
        virtual void RemoveModelUnitSymbol(CODSymbolComponent* pSymbol, PSS_ProcessGraphModelMdl* pModel = NULL);

        /**
        * Gets the workspace view
        *@return the workspace view
        */
        virtual inline PSS_WorkspaceTreeCtrl* GetWorkspaceView();

        /**
        * Activates the workspace tab
        */
        virtual inline void ActivateWorkspaceTab();

        /**
        * Shows the workspace tab
        */
        virtual inline void ShowWorkspaceTab();

        /**
        * Hides the workspace tab
        */
        virtual inline void HideWorkspaceTab();

        /**
        * Gets the model document tree
        *@return the model document tree
        */
        virtual inline PSS_ProcessModelDocument* GetModelDocumentTree();

        /**
        * Activates the model document tab
        */
        virtual inline void ActivateModelDocumentTab();

        /**
        * Shows the model document tab
        */
        virtual inline void ShowModelDocumentTab();

        /**
        * Hides the model document tab
        */
        virtual inline void HideModelDocumentTab();

        /**
        * Gets the form template view
        *@return the form template view
        */
        virtual inline PSS_FormTemplateTreeCtrl* GetFormTemplateView();

        /**
        * Activates the form template tab
        */
        virtual inline void ActivateFormTemplateTab();

        /**
        * Shows the form template tab
        */
        virtual inline void ShowFormTemplateTab();

        /**
        * Hides the form template tab
        */
        virtual inline void HideFormTemplateTab();

        /**
        * Gets the user view
        *@return the user view
        */
        virtual inline PSS_UserGroupView* GetUserView();

        /**
        * Activates the user tab
        */
        virtual inline void ActivateUserTab();

        /**
        * Shows the user tab
        */
        virtual inline void ShowUserTab();

        /**
        * Hides the user tab
        */
        virtual inline void HideUserTab();

        /**
        * Gets the logical system view
        *@return the logical system view
        */
        virtual inline PSS_LogicalSystemView* GetLogicalSystemView();

        /**
        * Activates the logical system tab
        */
        virtual inline void ActivateLogicalSystemTab();

        /**
        * Shows the logical system tab
        */
        virtual inline void ShowLogicalSystemTab();

        /**
        * Hides the logical system tab
        */
        virtual inline void HideLogicalSystemTab();

        /**
        * Gets the file view
        *@return the file view
        */
        virtual inline PSS_FileWnd* GetFileView();

        /**
        * Activates the file tab
        */
        virtual inline void ActivateFileTab();

        /**
        * Shows the file tab
        */
        virtual inline void ShowFileTab();

        /**
        * Hides the file tab
        */
        virtual inline void HideFileTab();

        /**
        * Gets the web view
        *@return the web view
        */
        virtual inline PSS_UrlWnd* GetWebView();

        /**
        * Activates the web tab
        */
        virtual inline void ActivateWebTab();

        /**
        * Shows the web tab
        */
        virtual inline void ShowWebTab();

        /**
        * Hides the web tab
        */
        virtual inline void HideWebTab();

        /**
        * Gets the prestations view
        *@return the prestations view
        */
        virtual inline PSS_PrestationsView* GetPrestationsView();

        /**
        * Activates the prestations tab
        */
        virtual inline void ActivatePrestationsTab();

        /**
        * Shows the prestations tab
        */
        virtual inline void ShowPrestationsTab();

        /**
        * Hides the prestations tab
        */
        virtual inline void HidePrestationsTab();

        /**
        * Gets the rules view
        *@return the rules view
        */
        virtual inline PSS_RulesView* GetRulesView();

        /**
        * Activates the rules tab
        */
        virtual inline void ActivateRulesTab();

        /**
        * Shows the rules tab
        */
        virtual inline void ShowRulesTab();

        /**
        * Hides the rules tab
        */
        virtual inline void HideRulesTab();

        /**
        * Called when the observer receives a message from the subject
        *@param pSubject - subject which sent the message
        *@param pMsg - the message
        */
        virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ProcessWorkspace)
        virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
        virtual void OnExtendContextMenu(CMenu* pMenu);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ProcessWorkspace)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
        afx_msg void OnListGetDispInfoModelView(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnListGetDispInfoFormView(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnListGetDispInfoFileView(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnListGetDispInfoUserView(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void OnListGetDispInfoWebView(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg LRESULT OnInitializeModelDocument(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnModelDocumentHasChanged(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnInitializeModelUnit(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnModelUnitHasChanged(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnAddModelDocument(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnRemoveModelDocument(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnAddModelUnit(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnRemoveModelUnit(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnAddModelDocumentSymbol(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnRemoveModelDocumentSymbol(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnModifyModelDocumentSymbol(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnAddModelUnitSymbol(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnRemoveModelUnitSymbol(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnModifyModelUnitSymbol(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnCloseDocumentModelTree(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnCloseUnitModelTree(WPARAM wParam, LPARAM lParam);
        afx_msg LRESULT OnDocumentHasBeenSelected(WPARAM wParam, LPARAM lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CDocument*               m_pActiveDocument;
        SEC3DTabWnd              m_WndTab;
        PSS_WorkspaceTreeCtrl    m_WorkspaceView;
        PSS_ProcessModelDocument m_ProcessModelView;
        PSS_FormTemplateTreeCtrl m_FormTemplateView;
        PSS_UserGroupView        m_UserView;
        PSS_LogicalSystemView    m_LogicalSystemView;
        PSS_PrestationsView      m_PrestationsView;
        PSS_RulesView            m_RulesView;
        PSS_FileWnd              m_FileView;
        PSS_UrlWnd               m_URLView;
};

//---------------------------------------------------------------------------
// PSS_ProcessWorkspace
//---------------------------------------------------------------------------
PSS_WorkspaceTreeCtrl* PSS_ProcessWorkspace::GetWorkspaceView()
{
    return &m_WorkspaceView;
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ActivateWorkspaceTab()
{
    m_WndTab.ActivateTab(g_WorkspaceTabIndex);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ShowWorkspaceTab()
{
    m_WndTab.EnableTab(g_WorkspaceTabIndex, TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::HideWorkspaceTab()
{
    m_WndTab.EnableTab(g_WorkspaceTabIndex, FALSE);
}
//---------------------------------------------------------------------------
PSS_ProcessModelDocument* PSS_ProcessWorkspace::GetModelDocumentTree()
{
    return &m_ProcessModelView;
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ActivateModelDocumentTab()
{
    m_WndTab.ActivateTab(g_ModelDocumentTabIndex);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ShowModelDocumentTab()
{
    m_WndTab.EnableTab(g_ModelDocumentTabIndex, TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::HideModelDocumentTab()
{
    m_WndTab.EnableTab(g_ModelDocumentTabIndex, FALSE);
}
//---------------------------------------------------------------------------
PSS_FormTemplateTreeCtrl* PSS_ProcessWorkspace::GetFormTemplateView()
{
    return &m_FormTemplateView;
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ActivateFormTemplateTab()
{
    m_WndTab.ActivateTab(g_FormTemplateTabIndex);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ShowFormTemplateTab()
{
    m_WndTab.EnableTab(g_FormTemplateTabIndex, TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::HideFormTemplateTab()
{
    m_WndTab.EnableTab(g_FormTemplateTabIndex, FALSE);
}
//---------------------------------------------------------------------------
PSS_UserGroupView* PSS_ProcessWorkspace::GetUserView()
{
    return &m_UserView;
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ActivateUserTab()
{
    m_WndTab.ActivateTab(g_UserTabIndex);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ShowUserTab()
{
    m_WndTab.EnableTab(g_UserTabIndex, TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::HideUserTab()
{
    m_WndTab.EnableTab(g_UserTabIndex, FALSE);
}
//---------------------------------------------------------------------------
PSS_LogicalSystemView* PSS_ProcessWorkspace::GetLogicalSystemView()
{
    return &m_LogicalSystemView;
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ActivateLogicalSystemTab()
{
    m_WndTab.ActivateTab(g_LogicalSystemTabIndex);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ShowLogicalSystemTab()
{
    m_WndTab.EnableTab(g_LogicalSystemTabIndex, TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::HideLogicalSystemTab()
{
    m_WndTab.EnableTab(g_LogicalSystemTabIndex, FALSE);
}
//---------------------------------------------------------------------------
PSS_FileWnd* PSS_ProcessWorkspace::GetFileView()
{
    return &m_FileView;
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ActivateFileTab()
{
    m_WndTab.ActivateTab(g_FileTabIndex);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ShowFileTab()
{
    m_WndTab.EnableTab(g_FileTabIndex, TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::HideFileTab()
{
    m_WndTab.EnableTab(g_FileTabIndex, FALSE);
}
//---------------------------------------------------------------------------
PSS_UrlWnd* PSS_ProcessWorkspace::GetWebView()
{
    return &m_URLView;
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ActivateWebTab()
{
    m_WndTab.ActivateTab(g_WebTabIndex);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ShowWebTab()
{
    m_WndTab.EnableTab(g_WebTabIndex, TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::HideWebTab()
{
    m_WndTab.EnableTab(g_WebTabIndex, FALSE);
}
//---------------------------------------------------------------------------
PSS_PrestationsView* PSS_ProcessWorkspace::GetPrestationsView()
{
    return &m_PrestationsView;
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ActivatePrestationsTab()
{
    m_WndTab.ActivateTab(g_PrestationsTabIndex);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ShowPrestationsTab()
{
    m_WndTab.EnableTab(g_PrestationsTabIndex, TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::HidePrestationsTab()
{
    m_WndTab.EnableTab(g_PrestationsTabIndex, FALSE);
}
//---------------------------------------------------------------------------
PSS_RulesView* PSS_ProcessWorkspace::GetRulesView()
{
    return &m_RulesView;
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ActivateRulesTab()
{
    m_WndTab.ActivateTab(g_RulesTabIndex);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::ShowRulesTab()
{
    m_WndTab.EnableTab(g_RulesTabIndex, TRUE);
}
//---------------------------------------------------------------------------
void PSS_ProcessWorkspace::HideRulesTab()
{
    m_WndTab.EnableTab(g_RulesTabIndex, FALSE);
}
//---------------------------------------------------------------------------

#endif
