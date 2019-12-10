/****************************************************************************
 * ==> PSS_ProcessGraphModelView -------------------------------------------*
 ****************************************************************************
 * Description : Provides a graphic process model view                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ProcessGraphModelViewH
#define PSS_ProcessGraphModelViewH

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

// class name mapping
#ifndef PSS_ProcessGraphModelMdl
    #define PSS_ProcessGraphModelMdl ZDProcessGraphModelMdl
#endif

// forward class declarations
class PSS_ProcessGraphModelMdl;
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
        PSS_MvcScrollView();
        virtual ~PSS_MvcScrollView();

        /**
        * Creates the view
        *@param pClassName - the class name
        *@param pWindowName - the window name
        *@param style - the view style
        *@param rect - the rect surrounding the view
        *@param pParentWnd - the parent window
        *@param id - the view identifier
        *@param pContext - the view context
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(LPCTSTR         pClassName,
                            LPCTSTR         pWindowName,
                            DWORD           style,
                            const RECT&     rect,
                            CWnd*           pParentWnd,
                            UINT            id,
                            CCreateContext* pContext = NULL);

        /**
        * Gets the viewport
        *@return the viewport
        */
        virtual ZIProcessGraphModelViewport* GetViewport();

        /**
        * Sets the view origin
        *@param x - x position in device units
        *@param y - y position in device units
        *@return the previous origin
        */
        virtual CPoint SetOrigin(int x, int y);

        /**
        * Sets the log origin
        *@param x - x position in device units
        *@param y - y position in device units
        *@return the previous log origin
        */
        virtual CPoint SetLogOrigin(int x, int y);

        /**
        * Sets the view extents
        *@param cx - extent width in device units
        *@param cy - extent height in device units
        *@return the previous extents
        */
        virtual CSize SetExtents(int cx, int cy);

        /**
        * Sets the log extents
        *@param cx - extent width in device units
        *@param cy - extent height in device units
        *@return the previous log extents
        */
        virtual CSize SetLogExtents(int cx, int cy);

        /**
        * Sets the view size
        *@param cx - view width in device units
        *@param cy - view height in device units
        *@return the previous size
        */
        virtual CSize SetSize(int cx, int cy);

        /**
        * Sets the log size
        *@param cx - log width in device units
        *@param cy - log height in device units
        *@return the previous log size
        */
        virtual CSize SetLogSize(int cx, int cy);

        /**
        * Sets the log scaling
        *@param scaleWidth - log scale width factor
        *@param scaleHeight - log scale height factor
        *@return the previous size extents
        */
        virtual CSize SetLogScaling(float scaleWidth, float scaleHeight);

        /**
        * Sets the view virtual origin
        *@param x - x position in device units
        *@param y - y position in device units
        */
        virtual void SetVirtualOrigin(int x, int y);

        /**
        * Sets the view virtual size
        *@param cx - view virtual width in device units
        *@param cy - view virtual height in device units
        */
        virtual void SetVirtualSize(int cx, int cy);

        /**
        * Called when the view is initialized for the first time
        */
        virtual void OnInitialUpdate();

        /**
        * Called when the device context is prepared for drawing
        *@param pDC - the device context
        *@param pInfo - the print info, ignored if NULL
        */
        virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);

        /**
        * Called when a scrolling is performed on the view
        *@param scrollSize - the scroll size
        *@param doScroll - if TRUE, the srolling should be performed
        *@return TRUE if the view was scrolled, otherwise FALSE
        */
        virtual BOOL OnScrollBy(CSize scrollSize, BOOL doScroll = TRUE);

        /**
        * Called when a Windows message is received in the view
        *@param message - the received Windows message
        *@param wParam - the message word parameter (16 bit value on old systems, now 32 bit long)
        *@param lParam - the message long parameter (32 bit value)
        *@param pResult - the message result
        *@return TRUE if the message was handled and should no longer be processed, otherwise FALSE
        */
        virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

        /**
        * Called when a command message is received in the view
        *@param id - the message identifier
        *@param code - the message code
        *@param pExtra - the message extra info
        *@param pHandlerInfo - the message handler info
        *@return TRUE if the message was handled and should no longer be processed, otherwise FALSE
        */
        virtual BOOL OnCmdMsg(UINT id, int code, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

    protected:
        CSize m_LineScroll;
        BOOL  m_UpdateScrollBars;

        /**
        * Scrolls the embedded viewport in response to WM_xSCROLL or WM_SIZE messages
        *@param scrollPos - the scroll position in device units
        */
        virtual void DoScrollViewport(const CPoint& scrollPos);

        /**
        * Updates the scrollbar position
        */
        virtual void UpdateScrollBarPos();

        /**
        * Updates the scrollbar size
        */
        virtual void UpdateScrollBarSize();

        /**
        * Called while the viewport is drawn
        *@param pDC - the device context to draw on
        */
        virtual void OnDraw(CDC* pDC);
};

/**
* Graphic process model view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ProcessGraphModelView : public PSS_MvcScrollView
{
    DECLARE_DYNCREATE(PSS_ProcessGraphModelView)

    public:
        virtual ~PSS_ProcessGraphModelView();

        /**
        * Gets the model controller
        *@return the model controller
        */
        virtual PSS_ProcessGraphModelController* GetModelController();

        /**
        * Gets the view model
        *@return the view model
        */
        virtual PSS_ProcessGraphModelMdl* GetModel();

        /**
        * Sets the view model
        *@param pModel - the view model
        *@param doSizeVp - if true, the viewport will also be sized
        */
        virtual void SetModel(PSS_ProcessGraphModelMdl* pModel, bool doSizeVp = true);

        /**
        * Sizes the viewport to model
        */
        virtual void SizeVpToModel();

        /**
        * Checks if the view supports the drop
        *@return true if the view supports the drop, otherwise false
        */
        virtual bool AcceptDrop() const;

        /**
        * Checks if a symbol may be dropped on this view
        *@param pObj - the symbol object to drop
        *@param point - the drop point
        *@return true if the symbol may be dropped on this view, otherwise false
        */
        virtual bool AcceptDropItem(CObject* pObj, const CPoint& point);

        /**
        * Drops a symbol on the view
        *@param pObj - the symbol object to drop
        *@param point - the drop point
        *@return true on success, otherwise false
        */
        virtual bool DropItem(CObject* pObj, const CPoint& point);

        /**
        * Gets the view name
        *@return the view name
        */
        virtual const CString GetViewName();

        /**
        * Selects the export model to image file
        *@return true on success, otherwise false
        */
        virtual bool SelectExportModelToImageFile();

        /**
        * Gets the tooltip
        *@return the tooltip
        */
        virtual inline CToolTipCtrl& GetToolTip();

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

    protected:
        MvcScrollWrapper_T<ZIProcessGraphModelViewport> m_PanVp;
        CToolTipCtrl                                    m_ToolTip;
        CString                                         m_StrToolTip;
        CPoint                                          m_VirtualOrigin;
        CSize                                           m_VirtualSize;
        CSize                                           m_MagOrigin;
        double                                          m_CurrentRatio;
        bool                                            m_PanInitialized;

        PSS_ProcessGraphModelView();

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ProcessGraphModelView)
        virtual void OnDrawPan(CDC* pDC);
        virtual void OnInitialUpdate();
        virtual void OnDraw(CDC* pDC);
        virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
        virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
        virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
        virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
        virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
        virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ProcessGraphModelView)
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

        /**
        * Pre-translates the key message
        *@param pMsg - the message
        *@return TRUE if the message was handled, otherwise FALSE
        */
        virtual BOOL PreTranslateMessage(MSG* pMsg);

        /**
        * Initializes the pan viewport
        */
        virtual void InitializePanViewport();

        /**
        * Updates the overview rectangle
        */
        virtual void UpdateOverviewRect();

        /**
        * Called before the overview is shown
        */
        virtual void PreOverview();

        /**
        * Called after the overview is shown
        */
        virtual void PostOverview();

        /**
        * Sets the view ratio
        */
        virtual void SetRatio();

    private:
        PSS_ProcessGraphModelMdl* m_pViewModel;
};

//---------------------------------------------------------------------------
// PSS_ProcessGraphModelView
//---------------------------------------------------------------------------
CToolTipCtrl& PSS_ProcessGraphModelView::GetToolTip()
{
    return m_ToolTip;
}
//---------------------------------------------------------------------------

#endif
