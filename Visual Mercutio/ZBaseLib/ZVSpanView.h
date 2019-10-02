#if !defined(AFX_ZVSPANVIEW_H__49684074_0FA6_4142_B4F8_F0E878FEDB38__INCLUDED_)
#define AFX_ZVSPANVIEW_H__49684074_0FA6_4142_B4F8_F0E878FEDB38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


//CR MSW: move this into the class.
typedef enum
{
    ZVP_PANDELAY, ZVP_PANINSTANT
} ZVPanMode;

// forward class declaration
class PSS_SpanWnd;

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS



/////////////////////////////////////////////////////////////////////////////
// ZVSpanView view

class AFX_EXT_CLASS ZVSpanView : public CScrollView
{
    friend class PSS_SpanWnd;
    DECLARE_DYNAMIC(ZVSpanView)

protected:
    ZVSpanView();           // protected constructor used by dynamic creation

// Operations
public:
    void AssignSpanWnd(PSS_SpanWnd *pWnd);

    //@Access Public Members
    //Panning Operations
    //@cmember
    /* Sets the pan mode to one of ZVP_PANDELAY or ZVP_PANINSTANT.*/
    void SetPanMode(ZVPanMode panMode);

    //@cmember
    /* Retrieves the current pan mode.*/
    ZVPanMode GetPanMode()
    {
        return m_panMode;
    };

    //Are we in a pan mode? 
    //@cmember
    /* Is the view currently panning?*/
    BOOL IsPanning()
    {
        return m_bPanning;
    };

    // Operations - virtual so you can change behavior or enhance it.
public:
    //Panning operations
    //@cmember
    /* Put the ZVSpanView into panning mode.*/
    virtual void StartPan(CPoint * ptPan,
                          UINT nCursorID = 0);

    //@cmember
    /* Continues the pan, causes the view to be updated if in SEC_PANINSTANT mode.*/
    virtual void ContinuePan(CPoint *ptPan);

    //@cmember
    /* Stops the pan, causes the view to be updated if in SEC_PANDELAY mode.*/
    virtual void EndPan(CPoint *ptPan);

    //@Access Overview Window Operations
    //@cmember
    /* Is the overview window being displayed?*/
    BOOL IsOverviewShown()
    {
        return m_pOverview != NULL;
    };

    //@cmember
    /* Call to update the overview window.*/
    virtual void UpdateOverviewWnd(CView * pSender,
                                   LPARAM lHint = 0L,
                                   CObject * pHint = NULL);

    //@cmember
    /* When overview window is updated, invalidates all of the window or, using hints, only some regions for repainting.*/
    virtual void OnUpdateOverview(CView * pSender,
                                  LPARAM lHint, CObject * pHint,
                                  CDC * pOverviewDC, CWnd * pWndOverview);

    void   CenterOnLogicalPoint(CPoint ptCenter);
    CPoint GetLogicalCenterPoint(void);

    void   ViewDPtoLP(LPPOINT lpPoints, int nCount = 1);
    void   ViewLPtoDP(LPPOINT lpPoints, int nCount = 1);
    void   ClientToDevice(CPoint &point);


    // Overrideables - OverRide this to get notifications of zoom level change
protected:
    void      PersistRatio(const CSize &orig, CSize &dest, CPoint &remainder);
    virtual void ZoomLevelChanged(void); //From CScrollView


// Implementation
protected:
    virtual ~ZVSpanView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    virtual void OnDrawPan(CDC* pDC)
    {}; // Used to draw the view in the pan window

    virtual void OnDraw(CDC* pDC) = 0; // Pass on Pure Virtual from CScrollView
    //Internal functions
    virtual void PerformPan(CPoint *ptEndPan, BOOL bReversePan = FALSE);
    virtual void UpdateOverviewRect();
    virtual void PreOverview();
    virtual void PostOverview();
    virtual void OverviewDestroyed();
    virtual void UpdatePanViewport(CPoint * lpPtNewLog);

protected:
    // Member variables
    UINT         m_nCursorID;
    ZVPanMode    m_panMode;
    BOOL         m_bPanning;
    HCURSOR      m_hOrigCursor;
    HCURSOR      m_hDragCursor;
    CPoint       m_ptLogStartDrag; //Logical coords of pan start
    PSS_SpanWnd* m_pOverview;    //The overview window.
    CPtrList     m_listAllocOverview;
    BOOL         m_InVirtualDraw;

    //These member store state needed for the overview window.
    CSize         m_orig_szTotalDev;
    BOOL          m_orig_bCenter;
    UINT          m_orig_zoomMode;

    BOOL DoScroll(CSize sizeScroll, BOOL bDoScroll);

public:
    // Generated message map functions
    //{{AFX_MSG(ZVSpanView)
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnHScroll(UINT, UINT, CScrollBar*);
    afx_msg void OnVScroll(UINT, UINT, CScrollBar*);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP();
};

#endif
