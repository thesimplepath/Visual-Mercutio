// ProcGraphModelView.h : interface of the ZIProcessGraphModelView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECTIVVIEW_H__BA14FA99_F1F8_4526_8B0F_A212865D7399__INCLUDED_)
#define AFX_OBJECTIVVIEW_H__BA14FA99_F1F8_4526_8B0F_A212865D7399__INCLUDED_

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
#include <Foundation\MVC\MvcWrapper.h>

// processsoft
#include "zBaseLib\PSS_DropScrollView.h"
#include "zBaseLib\PSS_DocumentPageSetup.h"
#include "ProcGraphModelVp.h"

// forward class declarations
class ZDProcessGraphModelMdl;
class PSS_ProcessGraphModelController;

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
* Wrapper class that derives from both a viewport and the ZIDropScrollView class. The resulting class can be used
* like a ZIDropScrollView, except all of the drawing will  automatically be delegated to the viewport class
*@note See the MvcForm sample for a demonstration of this class
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_MvcScrollView : public PSS_DropScrollView, public MvcWrapper_T<ZIProcessGraphModelViewport>
{
public:

    ////////////////////////////////////////////////////////
    // Construction/Destruction

    /* Constructor */
    PSS_MvcScrollView();

    /* Destructeur */
    virtual ~PSS_MvcScrollView();

    virtual BOOL Create(LPCTSTR         lpszClassName,
                        LPCTSTR         lpszWindowName,
                        DWORD           dwStyle,
                        const RECT&     rect,
                        CWnd*           pParentWnd,
                        UINT            nID,
                        CCreateContext* pContext = NULL);

    ////////////////////////////////////////////////////////
    // Operations

    //@cmember
    /* Casts this object to the base viewport class*/
    virtual ZIProcessGraphModelViewport* GetViewport();

    //@cmember
    /* Sets up default viewport initialization */
    virtual void OnInitialUpdate();

    //@cmember
    /* Forwards commands to the embedded viewport*/
    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

    //@cmember
    /* Forwards messages to the embedded viewport*/
    virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

    //@cmember
    /* Prepares the device context for drawing*/
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);

    //@cmember
    /* Called by MFC framework to scroll the view. */
    virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll = TRUE);

    ////////////////////////////////////////////////////////
    // Overrides which may change scroll bar size and position
    virtual CPoint SetOrigin(int x, int y);
    virtual CPoint SetLogOrigin(int x, int y);
    virtual CSize SetExtents(int cx, int cy);
    virtual CSize SetLogExtents(int cx, int cy);
    virtual CSize SetSize(int cx, int cy);
    virtual CSize SetLogSize(int cx, int cy);
    virtual CSize SetLogScaling(float fScaleWidth, float fScaleHeight);
    virtual void SetVirtualSize(int cx, int cy);
    virtual void SetVirtualOrigin(int x, int y);

protected:

    //@cmember
    /* Draws the viewport*/
    virtual void OnDraw(CDC* pDC);

    ////////////////////////////////////////////////////////
    // Implementation

    //@cmember
    /* Scrolls the embedded viewport in response to WM_xSCROLL or WM_SIZE messages*/
    virtual void DoScrollViewport(CPoint ptScrollPos);
    virtual void UpdateScrollBarPos();
    virtual void UpdateScrollBarSize();

    // Attributes
protected:

    CSize    m_szLineScroll;
    BOOL    m_bUpdateScrollBars;
};

class AFX_EXT_CLASS ZIProcessGraphModelView : public PSS_MvcScrollView
{
protected: // create from serialization only

    DECLARE_DYNCREATE(ZIProcessGraphModelView)

    ZIProcessGraphModelView();

    // Attributes
public:

    virtual PSS_ProcessGraphModelController* GetModelController();

    void    SetModel(ZDProcessGraphModelMdl* pModel, bool SizeViewport = true);
    virtual ZDProcessGraphModelMdl* GetModel();

    // Size the viewport to model
    void    SizeVpToModel();

    // Implement the drop of a symbol
    virtual bool AcceptDrop() const
    {
        return true;
    };
    virtual bool DropItem(CObject* pObj, const CPoint& pt);
    virtual bool AcceptDropItem(CObject* pObj, const CPoint& pt);

    virtual const CString GetViewName();

    // Image utility methods
    bool ChooseExportModelToImageFile();

    //    The tooltip class member. Used to display tooltip for
    //    fields.
    CToolTipCtrl& GetToolTip();

    // Operations
public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZIProcessGraphModelView)
public:
    virtual void OnDrawPan(CDC* pDC);    // overridden to draw this view in the pan window
    virtual void OnInitialUpdate();        // called first time after construct
    virtual void OnDraw(CDC* pDC);        // overridden to draw this view
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
    //}}AFX_VIRTUAL

// Implementation
public:

    virtual ~ZIProcessGraphModelView();

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    // Generated message map functions
protected:

    //{{AFX_MSG(ZIProcessGraphModelView)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg BOOL OnEraseBkgnd(CDC *pDC);
    afx_msg void OnExportModelToImageFile();
    afx_msg LRESULT OnRefreshSymbol(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnRefreshSymbolSet(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnBrowseSymbol(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnOpenModelPage(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnEnsureVisibleSymbol(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnModelDocumentHasChanged(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnAdviseStartPropertyEdition(WPARAM wParam, LPARAM lParam);
    afx_msg BOOL OnToolTipNeedText(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    // Pre translates key message.
    virtual BOOL PreTranslateMessage(MSG* pMsg);

    // ZVSpanView virtual functions
    virtual void UpdateOverviewRect();
    virtual void PreOverview();
    virtual void PostOverview();

    void InitializePanViewport();
    void SetRatio();

    // Attributes
protected:

    CString                                            m_StrToolTip;
    CToolTipCtrl                                    m_ToolTip;

    // Used in conjonction with the pan window
    CPoint                                            m_orig_ptVirtualOrigin;
    CSize                                            m_orig_szVirtualSize;
    CSize                                            m_orig_szMag;
    double                                            m_CurrentRatio;

    bool                                            m_PanInitialized;

    MvcScrollWrapper_T<ZIProcessGraphModelViewport>    m_vpPan;

private:

    ZDProcessGraphModelMdl*                            m_pModelOfView;
};

inline CToolTipCtrl& ZIProcessGraphModelView::GetToolTip()
{
    return m_ToolTip;
}

#endif
