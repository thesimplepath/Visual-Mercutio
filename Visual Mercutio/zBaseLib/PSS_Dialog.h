/****************************************************************************
 * ==> PSS_Dialog ----------------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic dialog box                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_DialogH
#define PSS_DialogH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#include "Mfc.h"

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
* Generic dialog box
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_Dialog : public CDialog
{
    public:
        /**
        * Constructor
        *@param templateID - dialog template identifier
        *@param autoCenter - if TRUE, the dialog will be auto-centered
        *@param pParentWnd - parent window, can be NULL
        */
        PSS_Dialog(UINT templateID = -1, BOOL autoCenter = TRUE, CWnd* pParentWnd = NULL);

        /**
        * Constructor
        *@param pTemplateName - dialog template name
        *@param autoCenter - if TRUE, the dialog will be auto-centered
        *@param pParentWnd - parent window, can be NULL
        */
        PSS_Dialog(LPCSTR pTemplateName, BOOL autoCenter = TRUE, CWnd* pParentWnd = NULL);

        /**
        * Constructor
        *@param templateID - dialog template identifier
        *@param autoCenter - if TRUE, the dialog will be auto-centered
        *@param bgCol - background color
        *@param staticCol - static label color
        *@param editCol - edit color
        *@param pParentWnd - parent window, can be NULL
        */
        PSS_Dialog(UINT     templateID,
                   BOOL     autoCenter,
                   COLORREF bgCol,
                   COLORREF staticCol,
                   COLORREF editCol,
                   CWnd*    pParentWnd = NULL);

        /**
        * Constructor
        *@param pTemplateName - dialog template name
        *@param autoCenter - if TRUE, the dialog will be auto-centered
        *@param bgCol - background color
        *@param staticCol - static label color
        *@param editCol - edit color
        *@param pParentWnd - parent window, can be NULL
        */
        PSS_Dialog(LPCSTR   pTemplateName,
                   BOOL     autoCenter,
                   COLORREF bgCol,
                   COLORREF staticCol,
                   COLORREF editCol,
                   CWnd*    pParentWnd = NULL);

        virtual ~PSS_Dialog();

        /**
        * Creates the dialog
        *@param templateID - dialog template identifier
        *@param autoCenter - if TRUE, the dialog will be auto-centered
        *@param pParentWnd - parent window, can be NULL
        */
        virtual void Create(UINT templateID, BOOL autoCenter = TRUE, CWnd* pParentWnd = NULL);

        /**
        * Creates the dialog
        *@param pTemplateName - dialog template name
        *@param autoCenter - if TRUE, the dialog will be auto-centered
        *@param pParentWnd - parent window, can be NULL
        */
        virtual void Create(LPCSTR pTemplateName, BOOL autoCenter = TRUE, CWnd* pParentWnd = NULL);

        /**
        * Creates the dialog
        *@param templateID - dialog template identifier
        *@param autoCenter - if TRUE, the dialog will be auto-centered
        *@param bgCol - background color
        *@param staticCol - static label color
        *@param editCol - edit color
        *@param pParentWnd - parent window, can be NULL
        */
        virtual void Create(UINT     templateID,
                            BOOL     autoCenter,
                            COLORREF bgCol,
                            COLORREF staticCol,
                            COLORREF editCol,
                            CWnd*    pParentWnd = NULL);

        /**
        * Creates the dialog
        *@param pTemplateName - dialog template name
        *@param autoCenter - if TRUE, the dialog will be auto-centered
        *@param bgCol - background color
        *@param staticCol - static label color
        *@param editCol - edit color
        *@param pParentWnd - parent window, can be NULL
        */
        void Create(LPCSTR   pTemplateName,
                    BOOL     autoCenter,
                    COLORREF bgCol,
                    COLORREF staticCol,
                    COLORREF editCol,
                    CWnd*    pParentWnd = NULL);

        /**
        * Sets the background color
        *@param value - the background color
        */
        void SetBackgroundColor(COLORREF col);

        /**
        * Sets the edit color
        *@param value - the edit color
        */
        void SetEditControlColor(COLORREF col);

        /**
        * Sets the static label color
        *@param value - the static label color
        */
        void SetStaticControlColor(COLORREF col);

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_Dialog)
        virtual BOOL OnInitDialog();
        afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        HBRUSH   m_hBgBrush;
        CBrush   m_Brush;
        COLORREF m_BgCol;
        COLORREF m_StaticCol;
        COLORREF m_EditCol;
        COLORREF m_CtlBgCol;
        COLORREF m_CtlTextCol;
        BOOL     m_AutoCenter;
        bool     m_ColorHasBeenSuperseed;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_Dialog(const PSS_Dialog& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_Dialog& operator = (const PSS_Dialog& other);

        /**
        * Gets if the dialog is auto-centered on opening
        *@return TRUE if the dialog is auto-centered on opening, otherwise FALSE
        */
        inline const BOOL GetAutoCenter() const;

        /**
        * Sets if the dialog is auto-centered on opening
        *@param value - if TRUE, the dialog is auto-centered
        */
        inline void SetAutoCenter(BOOL value);

        /**
        * Sets the dialog background and text color
        *@param bgColor - background color
        *@param textColor - text color
        */
        void SetDialogColors(COLORREF bgColor = RGB(192, 192, 192), COLORREF textColor = RGB(0, 0, 0));
};

//---------------------------------------------------------------------------
// PSS_Dialog
//---------------------------------------------------------------------------
const BOOL PSS_Dialog::GetAutoCenter() const
{
    return m_AutoCenter;
}
//---------------------------------------------------------------------------
void PSS_Dialog::SetAutoCenter(BOOL value)
{
    m_AutoCenter = value;
}
//---------------------------------------------------------------------------

#endif
