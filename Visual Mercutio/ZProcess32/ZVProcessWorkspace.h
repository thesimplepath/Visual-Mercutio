// ZVProcessWorkspace.h: interface for the ZVProcessWorkspace class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZVPROCESSWORKSPACE_H__8CD08B10_53ED_438C_82AD_1E04FE3C6282__INCLUDED_)
#define AFX_ZVPROCESSWORKSPACE_H__8CD08B10_53ED_438C_82AD_1E04FE3C6282__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zBaseLib\ZISubject.h"
#include "zBaseLib\ZIObserver.h"
#include "zBaseLib\ZCWorkspaceTreeCtrl.h"
#include "zWinUtil32\PSS_FormTemplateTreeCtrl.h"
#include "zWinUtil32\PSS_FileWnd.h"
#include "zWinUtil32\PSS_UrlWnd.h"
#include "ZCProcessModelDocument.h"
#include "ZVLogicalSystem.h"
#include "ZVUserGroup.h"
#include "ZVPrestations.h"
#include "ZVRules.h"

// JMR-MODIF - Le 11 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

////////////////////////////////////////////////////////////////
// Tab Index constant definition
// La liste ci-dessous représente l'ordre d'affichage des formulaires. On peut tout à fait réorganiser cette liste,
// à condition que la valeur des index reste logique et consécutive. Par exemple, si on définit un ordre illogique
// comme : 0-1-2-3-5-6-7-8, le programme va se planter.
const int def_WorkspaceTabIndex        = 0;
const int def_ModelDocumentTabIndex    = 1;
const int def_UserTabIndex            = 2;
const int def_LogicalSystemTabIndex    = 3;
const int def_PrestationsTabIndex    = 4;        // JMR-MODIF - Le 11 octobre 2005 - Ajout de la constante de formulaire.
const int def_RulesTabIndex            = 5;        // JMR-MODIF - Le 13 novembre 2006 - Ajout de la constante de formulaire.
const int def_FileTabIndex            = 6;

// JMR-MODIF - Le 13 novembre 2006 - Ces deux formulaires ne sont pas inclus dans cette version. Pour les utiliser,
// il faut leur attribuer une valeur valide (par exemple, le dernier numéro attribué ci-dessus incrémenté de 1), et
// décommenter la variable de définition des variables _DISPLAY_SCRIPTOR et / ou _DISPLAY_WEBVIEW dans le fichier
// ZVProcessWorkspace.cpp.
const int def_FormTemplateTabIndex    = -1;
const int def_WebTabIndex            = -1;

class ZVProcessWorkspace : public SECControlBar,
                           public ZISubject,
                           public ZIObserver
{
    DECLARE_DYNAMIC( ZVProcessWorkspace )

public:

    ZVProcessWorkspace();
    virtual ~ZVProcessWorkspace();

    void Initialize();

    // JMR-MODIF - Le 30 août 2005 - Ajout de la fonction Release.
    void Release();

    void InitializeModelDocumentTree( ZBModelSet* pModelSet );
    void InitializeModelUnitTree( ZBModelSet* pModelSet );

    void RefreshModelDocumentTree();
    void RefreshModelUnitTree();

    void EmptyModelDocumentTree();
    void EmptyModelUnitTree();

    void AddModelDocument( ZDProcessGraphModelMdl* pModel );
    void RemoveModelDocument( ZDProcessGraphModelMdl* pModel );

    void AddModelDocumentSet( ZBModelSet* pModelSet );
    void RemoveModelDocumentSet( ZBModelSet* pModelSet );

    void AddModelDocumentSymbol( CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel = NULL );
    void RemoveModelDocumentSymbol( CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel = NULL );
    void ModifyModelDocumentSymbol( CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel = NULL );

    void AddModelUnit( ZDProcessGraphModelMdl* pModel );
    void RemoveModelUnit( ZDProcessGraphModelMdl* pModel );

    void AddModelUnitSet( ZBModelSet* pModelSet );
    void RemoveModelUnitSet( ZBModelSet* pModelSet );

    void AddModelUnitSymbol( CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel = NULL );
    void RemoveModelUnitSymbol( CODSymbolComponent* pSymbol, ZDProcessGraphModelMdl* pModel = NULL );

    ///////////////////////////////////////////////////////////
    // Workspace methods
    ZCWorkspaceTreeCtrl* GetWorkspaceView();

    void ActivateWorkspaceTab()
    {
        m_wndTab.ActivateTab( def_WorkspaceTabIndex );
    };

    void ShowWorkspaceTab()
    {
        m_wndTab.EnableTab( def_WorkspaceTabIndex, TRUE );
    };

    void HideWorkspaceTab()
    {
        m_wndTab.EnableTab( def_WorkspaceTabIndex, FALSE );
    };

    ///////////////////////////////////////////////////////////
    // Model document methods
    ZCProcessModelDocument* GetModelDocumentTree();

    void ActivateModelDocumentTab()
    {
        m_wndTab.ActivateTab( def_ModelDocumentTabIndex );
    };

    void ShowModelDocumentTab()
    {
        m_wndTab.EnableTab( def_ModelDocumentTabIndex, TRUE );
    };

    void HideModelDocumentTab()
    {
        m_wndTab.EnableTab( def_ModelDocumentTabIndex, FALSE );
    };

    ///////////////////////////////////////////////////////////
    // Form template methods
    PSS_FormTemplateTreeCtrl* GetFormTemplateView();

    void ActivateFormTemplateTab()
    {
        m_wndTab.ActivateTab( def_FormTemplateTabIndex );
    };

    void ShowFormTemplateTab()
    {
        m_wndTab.EnableTab( def_FormTemplateTabIndex, TRUE );
    };

    void HideFormTemplateTab()
    {
        m_wndTab.EnableTab( def_FormTemplateTabIndex, FALSE );
    };

    ///////////////////////////////////////////////////////////
    // User Group template methods
    ZVUserGroup* GetUserView();

    void ActivateUserTab()
    {
        m_wndTab.ActivateTab( def_UserTabIndex );
    };

    void ShowUserTab()
    {
        m_wndTab.EnableTab( def_UserTabIndex, TRUE );
    };

    void HideUserTab()
    {
        m_wndTab.EnableTab( def_UserTabIndex, FALSE );
    };

    ///////////////////////////////////////////////////////////
    // Logical System methods
    ZVLogicalSystem* GetLogicalSystemView();

    void ActivateLogicalSystemTab()
    {
        m_wndTab.ActivateTab( def_LogicalSystemTabIndex );
    };

    void ShowLogicalSystemTab()
    {
        m_wndTab.EnableTab( def_LogicalSystemTabIndex, TRUE );
    };

    void HideLogicalSystemTab()
    {
        m_wndTab.EnableTab( def_LogicalSystemTabIndex, FALSE );
    };

    ///////////////////////////////////////////////////////////
    // File methods
    PSS_FileWnd* GetFileView();

    void ActivateFileTab()
    {
        m_wndTab.ActivateTab( def_FileTabIndex );
    };

    void ShowFileTab()
    {
        m_wndTab.EnableTab( def_FileTabIndex, TRUE );
    };

    void HideFileTab()
    {
        m_wndTab.EnableTab( def_FileTabIndex, FALSE );
    };

    ///////////////////////////////////////////////////////////
    // Web view methods
    PSS_UrlWnd* GetWebView();

    void ActivateWebTab()
    {
        m_wndTab.ActivateTab( def_WebTabIndex );
    };

    void ShowWebTab()
    {
        m_wndTab.EnableTab( def_WebTabIndex, TRUE );
    };

    void HideWebTab()
    {
        m_wndTab.EnableTab( def_WebTabIndex, FALSE );
    };

    ///////////////////////////////////////////////////////////////////////////
    // JMR-MODIF - Le 11 octobre 2005 - Ajout des méthodes pour les prestations
    ZVPrestations* GetPrestationsView();

    void ActivatePrestationsTab()
    {
        m_wndTab.ActivateTab( def_PrestationsTabIndex );
    };

    void ShowPrestationsTab()
    {
        m_wndTab.EnableTab( def_PrestationsTabIndex, TRUE );
    };

    void HidePrestationsTab()
    {
        m_wndTab.EnableTab( def_PrestationsTabIndex, FALSE );
    };

    ///////////////////////////////////////////////////////////////////////////
    // JMR-MODIF - Le 15 novembre 2006 - Ajout des méthodes pour les règles.
    ZVRules* GetRulesView();

    void ActivateRulesTab()
    {
        m_wndTab.ActivateTab( def_RulesTabIndex );
    };

    void ShowRulesTab()
    {
        m_wndTab.EnableTab( def_RulesTabIndex, TRUE );
    };

    void HideRulesTab()
    {
        m_wndTab.EnableTab( def_RulesTabIndex, FALSE );
    };

    ///////////////////////////////////////////////////////////
    // ZIObserver call-back method
    virtual void OnUpdate( ZISubject* pSubject, ZIObserverMsg* pMsg );

public:

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVProcessWorkspace)
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
    virtual void OnExtendContextMenu(CMenu* pMenu);
    //}}AFX_VIRTUAL

// Generated message map functions
protected:

    //{{AFX_MSG(ZVProcessWorkspace)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnListGetDispInfoModelView(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnListGetDispInfoFormView(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnListGetDispInfoFileView(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnListGetDispInfoUserView(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnListGetDispInfoWebView(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg LRESULT OnInitializeModelDocument( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnModelDocumentHasChanged( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnInitializeModelUnit( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnModelUnitHasChanged( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnAddModelDocument( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnRemoveModelDocument( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnAddModelUnit( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnRemoveModelUnit( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnAddModelDocumentSymbol( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnRemoveModelDocumentSymbol( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnModifyModelDocumentSymbol( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnAddModelUnitSymbol( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnRemoveModelUnitSymbol( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnModifyModelUnitSymbol( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnCloseDocumentModelTree( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnCloseUnitModelTree( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnDocumentHasBeenSelected( WPARAM wParam, LPARAM lParam );
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    CDocument*                m_pActiveDocument;

    SEC3DTabWnd                m_wndTab;

    ZCWorkspaceTreeCtrl        m_WorkspaceView;
    ZCProcessModelDocument    m_ProcessModelView;
    PSS_FormTemplateTreeCtrl  m_FormTemplateView;
    ZVUserGroup                m_UserView;
    ZVLogicalSystem            m_LogicalSystemView;
    ZVPrestations            m_PrestationsView;    // JMR-MODIF - Le 11 octobre 2005 - Ajout variable m_PrestationsView.
    ZVRules                    m_RulesView;        // JMR-MODIF - Le 13 novembre 2006 - Ajout de la variable m_RulesView.
    PSS_FileWnd                m_FileView;
    PSS_UrlWnd                m_URLView;
};

inline ZCProcessModelDocument* ZVProcessWorkspace::GetModelDocumentTree()
{
    return &m_ProcessModelView;
}

inline PSS_FormTemplateTreeCtrl* ZVProcessWorkspace::GetFormTemplateView()
{
    return &m_FormTemplateView;
}

inline ZCWorkspaceTreeCtrl* ZVProcessWorkspace::GetWorkspaceView()
{
    return &m_WorkspaceView;
}

inline ZVUserGroup* ZVProcessWorkspace::GetUserView()
{
    return &m_UserView;
}

inline ZVLogicalSystem* ZVProcessWorkspace::GetLogicalSystemView()
{
    return &m_LogicalSystemView;
}

inline PSS_FileWnd* ZVProcessWorkspace::GetFileView()
{
    return &m_FileView;
}

inline PSS_UrlWnd* ZVProcessWorkspace::GetWebView()
{
    return &m_URLView;
}

// JMR-MODIF - Le 11 octobre 2005 - Ajout de la fonction inline GetPrestationsView()
inline ZVPrestations* ZVProcessWorkspace::GetPrestationsView()
{
    return &m_PrestationsView;
}

// JMR-MODIF - Le 15 novembre 2006 - Ajout de la fonction inline GetRulesView()
inline ZVRules* ZVProcessWorkspace::GetRulesView()
{
    return &m_RulesView;
}

#endif // !defined(AFX_ZVPROCESSWORKSPACE_H__8CD08B10_53ED_438C_82AD_1E04FE3C6282__INCLUDED_)