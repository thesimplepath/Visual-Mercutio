/****************************************************************************
 * ==> PSS_HoverButton -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a hover button                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_HoverButtonH
#define PSS_HoverButtonH

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
* Hover button states
*/
enum class EHoverButtonState
{
    E_HB_OFF,
    E_HB_ON,
    E_HB_Over,
    E_HB_Greyed
};

/**
* Hover button
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_HoverButton : public CBitmapButton
{
    public:
        PSS_HoverButton();
        virtual ~PSS_HoverButton();

        /**
        * Gets the button state
        *@return the button state
        */
        virtual inline EHoverButtonState GetButtonState() const;

        /**
        * Sets the button state
        *@param state - new button state
        *@return previous button state
        */
        virtual EHoverButtonState SetButtonState(EHoverButtonState state);

        /**
        * Loads the bitmaps
        *@param bitmapUp - bitmap up
        *@param bitmapDown - bitmap down
        *@param bitmapFocus - bitmap focus
        *@param bitmapDisabled - bitmap disabled
        *@param pBitmapUp - bitmap up file name
        *@param pBitmapDown - bitmap down file name
        *@param pBitmapFocus - bitmap focus file name
        *@param pBitmapDisabled - bitmap disabled file name
        *@return TRUE on success, otherwise FALSE
        */
        BOOL LoadBitmaps(UINT   bitmapUp,  UINT   bitmapDown,  UINT   bitmapFocus,  UINT   bitmapDisabled);
        BOOL LoadBitmaps(LPCSTR pBitmapUp, LPCSTR pBitmapDown, LPCSTR pBitmapFocus, LPCSTR pBitmapDisabled);

        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ZUHoverButton)
        virtual void DrawItem(LPDRAWITEMSTRUCT pDrawItemStruct);
        //}}AFX_VIRTUAL

    protected:
        /// Generated message map functions
        //{{AFX_MSG(PSS_HoverButton)
        afx_msg void OnMouseMove(UINT flags, CPoint point);
        afx_msg void OnLButtonUp(UINT flags, CPoint point);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        HWND              m_hWndOld;
        CBitmap           m_BmpButtonDown;
        CBitmap           m_BmpButtonFocussed;
        CBitmap           m_BmpButtonUp;
        CBitmap           m_BmpButtonDisabled;
        EHoverButtonState m_ButtonState;
        BOOL              m_MouseTracking;

        /**
        * Called when mouse cursor enters inside the button
        */
        void OnMouseEnter();

        /**
        * Called when mouse cursor leaves the button
        */
        void OnMouseLeave();
};

//---------------------------------------------------------------------------
// PSS_HoverButton
//---------------------------------------------------------------------------
EHoverButtonState PSS_HoverButton::GetButtonState() const
{
    return m_ButtonState;
};
//---------------------------------------------------------------------------

#endif
