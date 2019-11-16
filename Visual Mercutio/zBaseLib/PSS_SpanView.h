/****************************************************************************
 * ==> PSS_SpanView --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a span view                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SpanViewH
#define PSS_SpanViewH

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

// forward class declaration
class PSS_SpanWnd;

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Span view
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SpanView : public CScrollView
{
    friend class PSS_SpanWnd;
    DECLARE_DYNAMIC(PSS_SpanView)

    public:
        /**
        * Pan mode
        */
        typedef enum
        {
            IE_PM_Delay,
            IE_PM_Instant
        } IEPanMode;

        /**
        * Assigns the span window
        *@param pWnd - span window to assign
        */
        virtual void AssignSpanWnd(PSS_SpanWnd *pWnd);

        /**
        * Gets the pan mode
        *@return the pan mode
        */
        virtual inline IEPanMode GetPanMode() const;

        /**
        * Sets the pan mode
        *@param mode - pan mode
        */
        virtual void SetPanMode(IEPanMode mode);

        /**
        * Checks if the view is currently panning
        *@return TRUE the view is currently panning, otherwise FALSE
        */
        virtual inline BOOL IsPanning() const;

        /**
        * Starts the panning mode
        *@param pPanPoint - panning point
        *@param cursorID - cursor identifier to show while panning
        */
        virtual void StartPan(CPoint* pPanPoint, UINT cursorID = 0);

        /**
        * Continues the pan, causes the view to be updated if in instant mode
        *@param pPanPoint - panning point
        */
        virtual void ContinuePan(CPoint* pPanPoint);

        /**
        * Stops the pan, causes the view to be updated if in delayed mode
        *@param pPanPoint - panning point
        */
        virtual void EndPan(CPoint* pPanPoint);

        /**
        * Checks if the overview window is being shown
        */
        virtual inline BOOL IsOverviewShown() const;

        /**
        * Called when the overview window is updated
        *@param pSender - event sender
        *@param lHint - hint parameter
        *@param pHint - hint
        */
        virtual void UpdateOverviewWnd(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);

        /**
        * When overview window is updated, invalidates all of the window or, using hints, only some regions for repainting
        *@param pSender - event sender
        *@param lHint - hint parameter
        *@param pHint - hint
        *@param pOverviewDC - overview device context
        *@param pWndOverview - overview window
        */
        virtual void OnUpdateOverview(CView* pSender, LPARAM lHint, CObject* pHint, CDC* pOverviewDC, CWnd* pWndOverview);

        /**
        * Centers the view on a logical point
        *@param point - point
        */
        virtual void CenterOnLogicalPoint(CPoint& point);

        /**
        * Gets the logical center point
        *@return the logical center point
        */
        virtual CPoint GetLogicalCenterPoint();

        /**
        * Converts points from device coordinates to logical coordinates
        *@param pPoints - points to convert, converted points on function ends
        *@param count - point count
        */
        virtual void ViewDPtoLP(LPPOINT pPoints, int count = 1);

        /**
        * Converts points from logical coordinates to device coordinates
        *@param pPoints - points to convert, converted points on function ends
        *@param count - point count
        */
        virtual void ViewLPtoDP(LPPOINT pPoints, int count = 1);

        /**
        * Converts a point from client to device coordinates
        *@param[in, out] point - points to convert, converted points on function ends
        */
        virtual void ClientToDevice(CPoint& point);

    protected:
        PSS_SpanWnd* m_pOverview;
        IEPanMode    m_PanMode;
        HCURSOR      m_hOrigCursor;
        HCURSOR      m_hDragCursor;
        CPoint       m_LogStartDrag;
        CPtrList     m_ListAllocOverview;
        CSize        m_OriginalTotalDev;
        UINT         m_CursorID;
        UINT         m_OriginalZoomMode;
        BOOL         m_Panning;
        BOOL         m_InVirtualDraw;
        BOOL         m_OriginalCenter;

        PSS_SpanView();
        virtual ~PSS_SpanView();

        /// Generated message map functions
        //{{AFX_MSG(ZVSpanView)
        afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
        afx_msg void OnHScroll(UINT, UINT, CScrollBar*);
        afx_msg void OnVScroll(UINT, UINT, CScrollBar*);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP();

        /**
        * Called when zoom level changes
        *@param origin - origin
        *@param[out] dest - destination
        *@param[out] remainder - remainder
        */
        virtual void PersistRatio(const CSize& origin, CSize& dest, CPoint& remainder);

        /**
        * Called when the zoom level changed
        */
        virtual void ZoomLevelChanged();

        /**
        * Called when the view is drawn in the pan window
        *@param pDC - device context
        */
        virtual void OnDrawPan(CDC* pDC);

        /**
        * Called when the view is drawing
        *@param pDC - device context
        */
        virtual void OnDraw(CDC* pDC) = 0;

        /**
        * Performs the panning
        *@param pEndPan - end panning poinr
        *@param reversePan - if TRUE, panning will be reversed
        */
        virtual void PerformPan(CPoint* pEndPan, BOOL reversePan = FALSE);

        /**
        * Updates the overview rectangle
        */
        virtual void UpdateOverviewRect();

        /**
        * Called before overview
        */
        virtual void PreOverview();

        /**
        * Called after overview
        */
        virtual void PostOverview();

        /**
        * Called when overview is destroyed
        */
        virtual void OverviewDestroyed();

        /**
        * Called when pan viewport is updated
        *@param pNewLog - new log point
        */
        virtual void UpdatePanViewport(CPoint* pNewLog);

        /**
        * Checks if the view should be scrolled
        *@param sizeScroll - size scroll
        *@param doScroll - if TRUE, the view should be scrolled
        *@return TRUE if the view can be scrolled, otherwise FALSE
        */
        virtual BOOL DoScroll(CSize& sizeScroll, BOOL doScroll);

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
};

//---------------------------------------------------------------------------
// PSS_SpanView
//---------------------------------------------------------------------------
PSS_SpanView::IEPanMode PSS_SpanView::GetPanMode() const
{
    return m_PanMode;
}
//---------------------------------------------------------------------------
BOOL PSS_SpanView::IsPanning() const
{
    return m_Panning;
}
//---------------------------------------------------------------------------
BOOL PSS_SpanView::IsOverviewShown() const
{
    return (m_pOverview != NULL);
}
//---------------------------------------------------------------------------

#endif
