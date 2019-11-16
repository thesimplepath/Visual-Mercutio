/****************************************************************************
 * ==> PSS_ColorBtn --------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a color picker button and its associated dialog   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_ColorBtnH
#define PSS_ColorBtnH

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

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
// In order to ease use, these values have been hardcoded in colorbtn.rc
// This avoids the need for another header file
#define IDD_COLORBTN     5100
#define IDC_COLOR1       5101
#define IDC_COLOR20      5120
#define IDC_OTHER        5121
#define WM_COLOR_CHANGED WM_USER + 33
//---------------------------------------------------------------------------

/**
* Color picker dialog
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_ColorBtnDialog : public CDialog
{
    friend class PSS_ColorBtn;

    public:
        /**
        * Dialog resources
        */
        enum
        {
            IDD = IDD_COLORBTN
        };

        /**
        * Constructor
        *@param pParent - parent window, can be NULL
        */
        PSS_ColorBtnDialog(CWnd* pParent = NULL);

    protected:
        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_ColorBtnDialog)
        virtual void DoDataExchange(CDataExchange* pDX);
        //}}AFX_VIRTUAL

        /// Generated message map functions
        //{{AFX_MSG(PSS_ColorBtnDialog)
        virtual BOOL OnInitDialog();
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
        afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
        afx_msg void OnOther();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Called when a color is selected
        *@param id - identifier
        */
        virtual void OnColor(UINT id);

        /**
        * Ends the dialog
        *@param result - dialog modal result
        */
        virtual void EndDialog(int result);

    private:
        static COLORREF m_Colors[20];
        static BYTE     m_Used[20];
        int             m_ColorIndex;
};

/**
* Color picker button
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_ColorBtn : public CButton
{
    public:
        PSS_ColorBtn();
        virtual ~PSS_ColorBtn();

        /**
        * Gets the selected color
        *@return the selected color
        */
        virtual inline COLORREF GetColor();

        /**
        * Sets the selected color
        *@param color - color to set
        */
        virtual inline void SetColor(COLORREF color);

        /**
        * Resets the color table to its default value (may be used during serialization)
        */
        static void Reset();

        /**
        * Loads the color table from the registry
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL Load();

        /**
        * Stores the color table to the registry
        *@return TRUE on success, otherwise FALSE
        */
        static BOOL Store();

        /**
        * Serializes the class content to an archive
        *@param ar - archive
        */
        void Serialize(CArchive& ar);

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_ColorBtn)
        afx_msg void OnClicked();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * Draws an item
        *@param pDrawStruct - draw structure
        */
        void DrawItem(LPDRAWITEMSTRUCT pDrawStruct);

    private:
        PSS_ColorBtnDialog* m_pColorDlg;
        CBrush              m_BackBrush;
        CBrush              m_NullBrush;
        CBrush*             m_pOldBrush;
        CPen                m_BlackPen;
        CPen                m_DkGray;
        CPen                m_WhitePen;
        CPen                m_NullPen;
        CPen*               m_pOldPen;
        COLORREF            m_CurrentColor;
};

//---------------------------------------------------------------------------
// PSS_ColorBtn
//---------------------------------------------------------------------------
COLORREF PSS_ColorBtn::GetColor()
{
    return m_CurrentColor;
}
//---------------------------------------------------------------------------
void PSS_ColorBtn::SetColor(COLORREF color)
{
    m_CurrentColor = color;
}
//---------------------------------------------------------------------------

#endif
