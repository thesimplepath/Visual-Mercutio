/****************************************************************************
 * ==> PSS_TextAlignButton -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a text button with alignement style               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_TextAlignButtonH
#define PSS_TextAlignButtonH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#include "Mfc.h"

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
* Text button with alignement style
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_TextAlignButton : public CBitmapButton
{
    DECLARE_DYNCREATE(PSS_TextAlignButton)

    public:
        typedef CBitmapButton inherited;

    public:
        /**
        * Constructor
        *@param text - text
        *@param style - style
        *@param check - if TRUE, the button will be checked
        *@param pParentWnd, parent window, can be NULL
        *@param resID - resource identifier
        */
        PSS_TextAlignButton(const CString& text       = "",
                            UINT           style      = DT_SINGLELINE | DT_BOTTOM | DT_LEFT,
                            BOOL           check      = FALSE,
                            CWnd*          pParentWnd = NULL,
                            UINT           resID      = 0);

        virtual ~PSS_TextAlignButton();

        /**
        * Creates the button
        *@param text - text
        *@param style - style
        *@param check - if TRUE, the button will be checked
        *@param pParentWnd, parent window, can be NULL
        *@param resID - resource identifier
        */
        virtual void Create(const CString& text, UINT style, BOOL check, CWnd* pParentWnd, UINT resID);

        /**
        * Sets if button is checked
        *@param value - if TRUE, button is checked
        */
        virtual inline void SetCheck(BOOL value = TRUE);

        /**
        * Gets if button is checked
        *@return TRUE if button is checked, otherwise FALSE
        */
        virtual inline BOOL GetCheck() const;

    protected:
        /**
        * Draws the button
        *@param pDrawItemStructure - draw item structure
        */
        virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

        /// Generated message map functions
        //{{AFX_MSG(ZITextAlignButton)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CWnd*   m_pParentWnd;
        CString m_Text;
        UINT    m_Style;
        UINT    m_ResID;
        BOOL    m_Check;

        /**
        * Copy constructor
        *@param other - other object to copy from
        */
        PSS_TextAlignButton(const PSS_TextAlignButton& other);

        /**
        * Copy operator
        *@param other - other object to copy from
        *@return copy of itself
        */
        const PSS_TextAlignButton & operator = (const PSS_TextAlignButton& other);
};

//---------------------------------------------------------------------------
// PSS_TextAlignButton
//---------------------------------------------------------------------------
void PSS_TextAlignButton::SetCheck(BOOL value)
{
    m_Check = value;
    Invalidate();
}
//---------------------------------------------------------------------------
BOOL PSS_TextAlignButton::GetCheck() const
{
    return m_Check;
}
//---------------------------------------------------------------------------

#endif
