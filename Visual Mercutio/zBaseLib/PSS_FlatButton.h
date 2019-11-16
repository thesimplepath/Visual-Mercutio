/****************************************************************************
 * ==> PSS_FlatButton ------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a flat button                                     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FlatButtonH
#define PSS_FlatButtonH

#if _MSC_VER >= 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// comment the line below to deactivate the button auto-highlight (as it happens in Internet Explorer)
//#define ST_LIKEIE

// comment the line below to disable the ZMemoryDC class usage
//#define ST_USE_MEMDC

#ifdef ST_USE_MEMDC
    /**
    * Memory device context
    *@author Dominique Aigroz, Jean-Milost Reymond
    */
    class PSS_MemoryDC : public CDC
    {
    public:
        /**
        * Constructor
        *@param pDC - source device context
        */
        PSS_MemoryDC(CDC* pDC);

        virtual ~PSS_MemoryDC();

        /**
        * Pointer operator
        *@return this
        */
        inline PSS_MemoryDC* operator->();

        /**
        * Pointer operator
        *@return this
        */
        inline PSS_MemoryDC* operator*();

    private:
        CBitmap  m_Bitmap;
        CBitmap* m_pOldBitmap;
        CDC*     m_pDC;
        CRect    m_Rect;
        BOOL     m_MemDC;
        BOOL     m_Printing;
    };

    //---------------------------------------------------------------------------
    // PSS_MemoryDC
    //---------------------------------------------------------------------------
    PSS_MemoryDC* PSS_MemoryDC::operator->()
    {
        return this;
    }
    //---------------------------------------------------------------------------
    PSS_MemoryDC* PSS_MemoryDC::operator*()
    {
        return this;
    }
    //---------------------------------------------------------------------------
#endif

/**
* Flat button
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FlatButton : public CButton
{
    public:
        /**
        * Button alignments
        */
        enum
        {
            IE_ST_ALIGN_HORZ,
            IE_ST_ALIGN_VERT,
            IE_ST_ALIGN_HORZ_RIGHT
        };

        PSS_FlatButton();
        virtual ~PSS_FlatButton();

        /**
        * Gets if button is the default one
        *@return TRUE if button is the default one, otherwise FALSE
        */
        virtual BOOL GetDefault() const;

        /**
        * Sets the tooltip text
        *@param id - text identifier
        *@param activate - if TRUE, the button will be activated
        */
        virtual void SetTooltipText(int id, BOOL activate = TRUE);

        /**
        * Sets the tooltip text
        *@param pText - text
        *@param activate - if TRUE, the button will be activated
        */
        virtual void SetTooltipText(CString* pText, BOOL activate = TRUE);

        /**
        * Activates the tooltip button
        *@param enable - if TRUE, the button will be activated
        */
        virtual void ActivateTooltip(BOOL enable = TRUE);

        /**
        * Sets the button cursor
        *@param cursorID - cursor identifier
        */
        virtual BOOL SetBtnCursor(int cursorId = -1);

        /**
        * Gets if the flat button has the focus
        *@return TRUE if the flat button has the focus, otherwise FALSE
        */
        virtual BOOL GetFlatFocus() const;

        /**
        * Sets the focus on the flat button
        *@param drawFlatFocus - if TRUE, the focus will be drawn above the button
        *@param repaint - if TRUE, the button will be repainted
        */
        virtual void SetFlatFocus(BOOL drawFlatFocus, BOOL repaint = FALSE);

        /**
        * Gets the active foreground color
        *@return the active foreground color
        */
        virtual const COLORREF GetActiveFgColor() const;

        /**
        * Sets the active foreground color
        *@param color - color
        *@param repaint - if TRUE, the button will be repainted
        */
        virtual void SetActiveFgColor(COLORREF color, BOOL repaint = FALSE);

        /**
        * Sets the default active foreground color
        *@param repaint - if TRUE, the button will be repainted
        */
        virtual void SetDefaultActiveFgColor(BOOL repaint = FALSE);

        /**
        * Gets the active background color
        *@return the active background color
        */
        virtual const COLORREF GetActiveBgColor() const;

        /**
        * Sets the active background color
        *@param color - color
        *@param repaint - if TRUE, the button will be repainted
        */
        virtual void SetActiveBgColor(COLORREF color, BOOL repaint = FALSE);

        /**
        * Sets the default active foreground color
        *@param repaint - if TRUE, the button will be repainted
        */
        virtual void SetDefaultActiveBgColor(BOOL repaint = FALSE);

        /**
        * Gets the inactive foreground color
        *@return the inactive foreground color
        */
        virtual const COLORREF GetInactiveFgColor() const;

        /**
        * Sets the inactive foreground color
        *@param color - color
        *@param repaint - if TRUE, the button will be repainted
        */
        virtual void SetInactiveFgColor(COLORREF color, BOOL repaint = FALSE);

        /**
        * Sets the default inactive foreground color
        *@param repaint - if TRUE, the button will be repainted
        */
        virtual void SetDefaultInactiveFgColor(BOOL repaint = FALSE);

        /**
        * Gets the inactive background color
        *@return the inactive background color
        */
        virtual const COLORREF GetInactiveBgColor() const;

        /**
        * Sets the inactive background color
        *@param color - color
        *@param repaint - if TRUE, the button will be repainted
        */
        virtual void SetInactiveBgColor(COLORREF color, BOOL repaint = FALSE);

        /**
        * Sets the default inactive background color
        *@param repaint - if TRUE, the button will be repainted
        */
        virtual void SetDefaultInactiveBgColor(BOOL repaint = FALSE);

        /**
        * Gets if the text is shown
        *@return TRUE if the text is shown, otherwise FALSE
        */
        virtual BOOL GetShowText() const;

        /**
        * Sets if the text is shown
        *@param show - if TRUE, the text will be shown
        */
        virtual void SetShowText(BOOL show = TRUE);

        /**
        * Gets the text alignment
        *@return the text alignment
        */
        virtual int GetAlign() const;

        /**
        * Sets the text alignment
        *@param align - the text alignment
        */
        virtual void SetAlign(int align);

        /**
        * Gets if the button is flat
        *@return TRUE if the button is flat, otherwise FALSE
        */
        virtual BOOL GetFlat() const;

        /**
        * Sets if the button is flat
        *@param state - if TRUE, the button is flat
        */
        virtual void SetFlat(BOOL state = TRUE);

        /**
        * Sets the button icon
        *@param iconInID - icon identifier to show when the mouse is inside the button
        *@param iconOutID - icon identifier to show when the mouse is outside the button
        */
        virtual void SetIcon(int iconInId, int iconOutId = NULL);

        /**
        * Sets the button icon
        *@param hIconIn - icon handle to show when the mouse is inside the button
        *@param hIconOut - icon handle to show when the mouse is outside the button
        */
        virtual void SetIcon(HICON hIconIn, HICON hIconOut = NULL);

        /**
        * Sets if the border should be drawn
        *@param value - if TRUE, the border will be drawn
        */
        virtual void SetDrawBorder(BOOL value = TRUE);

        /**
        * Draws a transparent button
        *@param repaint - if TRUE, the button will be repainted
        */
        virtual void DrawTransparent(BOOL repaint = FALSE);

        /**
        * Gets the version as integer
        *@return the version as integer
        */
        static const short GetVersionI();

        /**
        * Gets the version as text
        *@return the version as text
        */
        static const char* GetVersionC();

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_FlatButton)
        virtual void PreSubclassWindow();
        virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
        //}}AFX_VIRTUAL

        /// generated message map functions
        //{{AFX_MSG(PSS_FlatButton)
        afx_msg void OnCaptureChanged(CWnd *pWnd);
        afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
        afx_msg void OnKillFocus(CWnd* pNewWnd);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg void OnSysColorChange();
        afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CToolTipCtrl m_ToolTip;
        CDC          m_DcBk;
        CBitmap      m_BmpBk;
        CBitmap*     m_pBmpOldBk;
        COLORREF     m_InactiveBg;
        COLORREF     m_InactiveFg;
        COLORREF     m_ActiveBg;
        COLORREF     m_ActiveFg;
        HCURSOR      m_hCursor;
        HICON        m_hIconIn;
        HICON        m_hIconOut;
        int          m_Align;
        BYTE         m_CxIcon;
        BYTE         m_CyIcon;
        BOOL         m_ShowText;
        BOOL         m_DrawBorder;
        BOOL         m_IsFlat;
        BOOL         m_MouseOnButton;
        BOOL         m_DrawFlatFocus;
        BOOL         m_DrawTransparent;
        BOOL         m_IsDefault;

        /**
        * Initializes the tooltip
        */
        void InitToolTip();

        /**
        * Draws the icon
        *@param pDC - device context to draw to
        *@param pTitle - button title
        *@param pItemRect - item rect
        *@param pCaptionRect - caption rect
        *@param isPressed - if TRUE, the button is in pressed state
        *@param isDisabled - if TRUE, the button is in disabled state
        */
        void DrawIcon(CDC* pDC, CString* pTitle, RECT* pItemRect, CRect* pCaptionRect, BOOL isPressed, BOOL isDisabled);

        /**
        * Paints the background
        *@param pDC - device context to draw to
        */
        void PaintBk(CDC* pDC);
};

#endif
