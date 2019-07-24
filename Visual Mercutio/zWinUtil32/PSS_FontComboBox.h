/****************************************************************************
 * ==> PSS_FontComboBox ----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a font combo box                                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FontComboBoxH
#define PSS_FontComboBoxH

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
* Font style enumerator
*@author Dominique Aigroz, Jean-Milost Reymond
*/
typedef enum
{
    E_FS_Fonts
} EFontStyle;

/**
* Font combo box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FontComboBox : public CComboBox
{
    public:
        PSS_FontComboBox();

         /**
         * Constructor
         *@param fontStyle - font style
         */
        PSS_FontComboBox(EFontStyle fontStyle);

         virtual ~PSS_FontComboBox();

         /**
         * Sets the highlight colors
         *@param highlight - highlight background color
         *@param highlightText - highlight text color
         */
         virtual inline void SetHighlightColors(COLORREF highlight, COLORREF highlightText);

         /**
         * Sets the normal colors
         *@param bgColor - background color
         *@param textColor - text color
         */
         virtual inline void SetNormalColors(COLORREF bgColor, COLORREF textColor);

         /**
         * Sets the current font
         *@param pFont - font
         *@param pFontName - font name
         *@return TRUE on success, otherwise FALSE
         */
         virtual BOOL SetCurrentFont(LPLOGFONT pFont);
         virtual BOOL SetCurrentFont(LPCTSTR pFontName);

         /**
         * Fills the fonts in the combo box
         */
         virtual void FillFonts();

         /**
         * Gets the selected font
         *@param[out] font - selected font
         *@return selected font index
         */
         virtual int GetSelFont(LOGFONT& font);

         /**
         * Font enumerator callback
         *@param pFont - font
         *@param pTextMetric - text metric
         *@param type - font type
         *@param pData - custom data
         *@return TRUE if next callback should be called, otherwise FALSE
         */
         static BOOL CALLBACK EnumFontProc(LPLOGFONT pFont, LPTEXTMETRIC pTextMetric, DWORD type, LPARAM pData);

    protected:
        EFontStyle m_Style;
        COLORREF   m_ClrHighlight;
        COLORREF   m_ClrNormalText;
        COLORREF   m_ClrHighlightText;
        COLORREF   m_ClrBkgnd;
        BOOL       m_InitOver;

        /// Generated message map functions
        //{{AFX_MSG(PSS_FontComboBox)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnDestroy();
        afx_msg long OnInitFonts(WPARAM wParam, LPARAM lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_FontComboBox)
        virtual void PreSubclassWindow();
        virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
        virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
        //}}AFX_VIRTUAL

        /**
        * Draws the font
        *@param pDrawStruct - draw structure
        */
        virtual void DrawFont(LPDRAWITEMSTRUCT pDrawStruct);

        /**
        * Initialize fonts
        */
        virtual void InitFonts();
};

//---------------------------------------------------------------------------
// PSS_FontComboBox
//---------------------------------------------------------------------------
void PSS_FontComboBox::SetHighlightColors(COLORREF highlight, COLORREF highlightText)
{
    m_ClrHighlight     = highlight;
    m_ClrHighlightText = highlightText;
}
//---------------------------------------------------------------------------
void PSS_FontComboBox::SetNormalColors(COLORREF bgColor, COLORREF textColor)
{
    m_ClrBkgnd      = bgColor;
    m_ClrNormalText = textColor;
}
//---------------------------------------------------------------------------

#endif
