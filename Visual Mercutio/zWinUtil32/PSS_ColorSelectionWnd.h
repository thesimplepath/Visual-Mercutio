/****************************************************************************
 * ==> PSS_ColorSelectionWnd -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a color selection window                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ColorSelectionWndH
#define PSS_ColorSelectionWndH

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

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Color selection window
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ColorSelectionWnd : public CWnd
{
    DECLARE_DYNAMIC(PSS_ColorSelectionWnd);

    public:
        /**
        * Constructor
        *@param color - default color
        */
        PSS_ColorSelectionWnd(COLORREF color = defCOLOR_BLACK);

        virtual ~PSS_ColorSelectionWnd();

        /**
        * Creates the color window
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create();

        /**
        * Chooses the color
        */
        virtual void ChooseColor();

        /**
        * Checks if color has changed
        *@return TRUE if color has changed, otherwise FALSE
        */
        virtual inline BOOL ColorHasChanged() const;

        /**
        * Gets the selected color
        *@return the selected color
        */
        virtual inline COLORREF GetColor() const;

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_ColorSelectionWnd)
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        afx_msg void OnPaint();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        static CString  near m_ClassName;
        static CFont    near m_Font;
        static COLORREF      m_ColorTable[24];
        COLORREF             m_Col;
        COLORREF             m_OldCol;
        CPen                 m_BlackPen;
        CPen                 m_WhitePen;
        CPen                 m_GrayPen;
        std::size_t          m_CurrentX;
        std::size_t          m_CurrentY;
        BOOL                 m_Selected;

        /**
        * Draws a color
        *@param dc - device context
        *@param x - x position in pixels
        *@param y - y position in pixels
        *@param color - color
        *@param highlight - if TRUE, color is highlighted
        */
        void DrawColor(CDC& dc, int x, int y, COLORREF col, BOOL highLight = FALSE);

        /**
        * Finds the color
        *@param point - point
        *@param[in, out] rect - rectangle
        *@return selection error or success code
        */
        int FindColor(const CPoint& point, CRect& rect);

        /**
        * Finds the color rect
        *@param[in, out] rect - color rect
        *@return selection error or success code
        */
        int FindColorRect(CRect& rect);

        /**
        * Shows the highlight
        *@param dc - device context
        *@param[in, out] rect - highlight rectangle
        *@param show - if TRUE, highlight is shown, hidden otherwise
        */
        void ShowHighlight(CDC& dc, CRect& rect, BOOL show);
};

//---------------------------------------------------------------------------
// PSS_ColorSelectionWnd
//---------------------------------------------------------------------------
BOOL PSS_ColorSelectionWnd::ColorHasChanged() const
{
    return m_Col != m_OldCol;
}
//---------------------------------------------------------------------------
COLORREF PSS_ColorSelectionWnd::GetColor() const
{
    return m_Col;
}
//---------------------------------------------------------------------------

#endif
