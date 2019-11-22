#if !defined(AFX_ZVSelectSymbolFromGraphModel_H__5D8F8DB9_0C53_488F_98D1_D117F87B7601__INCLUDED_)
#define AFX_ZVSelectSymbolFromGraphModel_H__5D8F8DB9_0C53_488F_98D1_D117F87B7601__INCLUDED_

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

// stingray studio
#include "Views\OdRulerWrapper.h"

// processsoft
#include "zBaseLib\PSS_Dialog.h"
#include "zBaseLib\PSS_Observer.h"
#include "zBaseLib\PSS_Subject.h"
#include "zBaseLib\PSS_ObserverMsg.h"
#include "ZDefinitionSelectable.h"

// forward class declaration
class ZDProcessGraphModelMdl;

#ifdef _ZMODELEXPORT
// put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 11 mai 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// _ZVGraphModelViewport viewport

class _ZVGraphModelViewport : public CODBufferedRulerViewport, public PSS_Observer
{
public:

    _ZVGraphModelViewport();

    void ReSizeToWnd(CWnd& Wnd);

    //////////////////////////////////////////////////////////////////////
    // ZIObserver method
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(_ZVGraphModelViewport)
    //}}AFX_VIRTUAL

// Implementation
public:

    virtual ~_ZVGraphModelViewport();
    virtual BOOL CreateController();
};

/////////////////////////////////////////////////////////////////////////////
// _ZVGraphModelController controller

class _ZVGraphModelController : public CODController, public PSS_Observer
{
public:

    _ZVGraphModelController(CODViewport* pViewport);

    CODSymbolComponent* GetSelectedSymbol()
    {
        return m_pSelectedSymbol;
    };

    //////////////////////////////////////////////////////////////////////
    // ZIObserver method
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    // Implementation
public:

    virtual ~_ZVGraphModelController();

    /* Called whenever the selection changes. */
    virtual void OnSelectionChange(CODComponentSet* pChangedSet);

    // Generated message map functions
protected:

    //{{AFX_MSG(_ZVGraphModelController)
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    void OnRefresh();
    void OnGoUp();

private:

    CODSymbolComponent* GetSymbolSelected();

private:

    CODSymbolComponent* m_pSelectedSymbol;
};

/////////////////////////////////////////////////////////////////////////////
// _ZVGraphModelWnd window

class _ZVGraphModelWnd : public CWnd, public PSS_Subject, public PSS_Observer
{
    // Construction
public:

    _ZVGraphModelWnd();

    bool    GetEnableNavigate() const;
    void    SetEnableNavigate(bool value);

    //////////////////////////////////////////////////////////////////////
    // ZIObserver method
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

public:

    virtual CWnd* GetWnd() const;
    CODModel* GetModel();
    void SetModel(CODModel* pModel);
    void SetCurrentSymbol(CODSymbolComponent* pComp);
    void Initialize();

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(_ZVGraphModelWnd)
    //}}AFX_VIRTUAL

// Implementation
public:

    virtual ~_ZVGraphModelWnd();

    // Generated message map functions
protected:

    //{{AFX_MSG(_ZVGraphModelWnd)
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected:

    stingray::foundation::MvcScrollWrapper_T<_ZVGraphModelViewport> m_vpDialog;
    CODModel*    m_pModel;

private:

    bool        m_EnableNavigate;
};

inline bool _ZVGraphModelWnd::GetEnableNavigate() const
{
    return m_EnableNavigate;
}

inline void _ZVGraphModelWnd::SetEnableNavigate(bool value)
{
    m_EnableNavigate = value;
}

/////////////////////////////////////////////////////////////////////////////
// _ZBSelectSymbolObserverMsg observer message

class _ZBSelectSymbolObserverMsg : public PSS_ObserverMsg
{
    DECLARE_DYNAMIC(_ZBSelectSymbolObserverMsg)

public:

    _ZBSelectSymbolObserverMsg(CODSymbolComponent* pComp = NULL);
    virtual ~_ZBSelectSymbolObserverMsg();

    CODSymbolComponent* GetComponent() const
    {
        return m_pComp;
    };

    void SetComponent(CODSymbolComponent* value)
    {
        m_pComp = value;
    };

private:

    CODSymbolComponent* m_pComp;
};

/////////////////////////////////////////////////////////////////////////////
// _ZVSelectSymbolFlatToolBar window

class _ZVSelectSymbolFlatToolBar : public CStatic, public PSS_Subject
{
public:

    // Construction
    _ZVSelectSymbolFlatToolBar();
    virtual ~_ZVSelectSymbolFlatToolBar();

    void EnableNavigate(bool EnableNavigate = true);

    // Operations
public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(_ZVSelectSymbolFlatToolBar)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Generated message map functions
protected:

    //{{AFX_MSG(_ZVSelectSymbolFlatToolBar)
    afx_msg void OnRefreshButton();
    afx_msg void OnGoUpButton();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    // Attributes
private:

    CCJFlatButton    m_RefreshButton;
    CCJFlatButton    m_GoUpButton;

    CImageList        m_ImageList;
    CToolTipCtrl    m_tooltip;

    bool            m_EnableNavigate;
};

/////////////////////////////////////////////////////////////////////////////
// ZVSelectSymbolFromGraphModel dialog

class AFX_EXT_CLASS ZVSelectSymbolFromGraphModel : public PSS_Dialog, public PSS_Observer
{
    // Construction
public:

    ZVSelectSymbolFromGraphModel(ZDProcessGraphModelMdl*    pModel,
                                 const CString                Title = _T(""),
                                 int                        SelectableItem = Selectable_All,
                                 bool                        EnableNavigate = true,
                                 CWnd*                        pParent = NULL);

    ZVSelectSymbolFromGraphModel(ZDProcessGraphModelMdl*    pModel,
                                 const CString                Title,
                                 CRuntimeClass*            pSelectableClass,
                                 bool                        EnableNavigate = true,
                                 CWnd*                        pParent = NULL);

    ZVSelectSymbolFromGraphModel(ZDProcessGraphModelMdl*    pModel,
                                 UINT                        nIDResTitle,
                                 int                        SelectableItem = Selectable_All,
                                 bool                        EnableNavigate = true,
                                 CWnd*                        pParent = NULL);

    ZVSelectSymbolFromGraphModel(ZDProcessGraphModelMdl*    pModel,
                                 UINT                        nIDResTitle,
                                 CRuntimeClass*            pSelectableClass,
                                 bool                        EnableNavigate = true,
                                 CWnd*                        pParent = NULL);

    virtual ~ZVSelectSymbolFromGraphModel();

    CODSymbolComponent* GetSelectedSymbol()
    {
        return m_pSelectedSymbol;
    };

    CString GetSymbolPath() const
    {
        return m_SymbolPath;
    };

    CString GetSymbolName() const
    {
        return m_SymbolName;
    };

    //////////////////////////////////////////////////////////////////////
    // ZIObserver method
    virtual void OnUpdate(PSS_Subject* pSubject, PSS_ObserverMsg* pMsg);

    // Dialog Data
    //{{AFX_DATA(ZVSelectSymbolFromGraphModel)
//    enum { IDD = IDD_SELECTSYMBOL_GRAPH };
    CString    m_SymbolPath;
    CString    m_SymbolName;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVSelectSymbolFromGraphModel)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVSelectSymbolFromGraphModel)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    void MoveControls(int cx, int cy);
    void CheckSymbol(CODSymbolComponent* pComp);

private:

    ZDProcessGraphModelMdl*        m_pModel;
    _ZVSelectSymbolFlatToolBar    m_FlatToolBar;
    _ZVGraphModelWnd            m_wndModelGraph;
    CString                        m_Title;
    CODSymbolComponent*            m_pSelectedSymbol;
    CRuntimeClass*                m_pSelectableClass;
    int                            m_SelectableItem;
    bool                        m_EnableNavigate;
};

#endif
