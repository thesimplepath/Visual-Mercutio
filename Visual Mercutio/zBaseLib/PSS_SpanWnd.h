/****************************************************************************
 * ==> PSS_SpanWnd ---------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a span window                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SpanWndH
#define PSS_SpanWndH

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
class PSS_SpanView;

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
* Span window
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SpanWnd : public CWnd
{
    friend class PSS_SpanView;

    public:
        /**
        * Constructor
        *@param pPanView - parent pan view, can be NULL
        */
        PSS_SpanWnd(PSS_SpanView* pPanView = NULL);

        virtual ~PSS_SpanWnd();

        /**
        * Creates the overview window and specifies its initial position and size
        *@param rectCreate - the rectangle surrounding the overview window, in screen coordinates
        *@param pParent - parent window
        *@param id - identifier
        *@param pTitle - title
        */
        virtual BOOL Create(const CRect& rectCreate, CWnd* pParent, UINT id, LPCTSTR pTitle = NULL);

        /**
        * Assigns the pan view
        *@param pView - the pan view to assign
        */
        virtual void AssignPanView(PSS_SpanView* pView);

        /**
        * Implements the overview window style settings at creation
        *@param cs - create structure
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

        /**
        * Sets the rectangle surrounding the overview window
        *@param rectNewPan - the rectangle surrounding the overview window, in screen coordinates
        */
        virtual void SetPanRect(CRect& rectNewPan);

        /**
        * Draws the rectangle representing the overview window
        *@param pDC - device context to paint to
        */
        virtual void DrawPanRect(CDC* pDC);

        /**
        * Updates the overview window when the user scrolls or updates the panning view
        *@param pSender - event sender
        *@param lHint - low hint parameter
        *@param pHint - hint
        */
        virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

        /**
        * Clips the overview cursor
        */
        virtual void ClipOverviewCursor();

        /**
        * Converts the overview desktop point from device coordinates to logical coordinates
        *@param pPoint - point to convert
        */
        virtual void OverviewDPtoLP(CPoint* pPoint);

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
        PSS_SpanView* m_pPanView;
        HCURSOR       m_hOverviewCursor;
        HCURSOR       m_hCurrentOverviewCursor;
        HCURSOR       m_hOverviewOnMoveCursor;
        CRect         m_RectLogPan;
        CSize         m_LogDrag;
        BOOL          m_Captured;
        BOOL          m_ClipVerified;

        /// Generated message map functions
        //{{AFX_MSG(PSS_SpanWnd)
        afx_msg void OnClose();
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
        afx_msg void OnPaint();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP();

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SpanWnd)
        //}}AFX_VIRTUAL
};

#endif
