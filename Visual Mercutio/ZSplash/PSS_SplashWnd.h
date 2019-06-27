/****************************************************************************
 * ==> PSS_SplashWnd -------------------------------------------------------*
 ****************************************************************************
 * Description : Splash screen window                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SplashWndH
#define PSS_SplashWndH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "zBaseLib\ZBitmap.h"

/**
* Splash screen window
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_SplashWnd : public CWnd
{
    public:
        PSS_SplashWnd();
        virtual ~PSS_SplashWnd();

        /**
        * Creates splash screen window
        *@param includeProgress - if true, progress bar will be shown
        *@param pParent - splash screen parent window
        *@return true on success, otherwise false
        */
        bool CreateSplashWindow(bool includeProgress, CWnd* pParent);

        /**
        * Shows the splash screen
        *@return true on success, otherwise false
        */
        bool Show();

        /**
        * Hides the splash screen
        *@return true on success, otherwise false
        */
        bool Hide();

        /**
        * Updates the splash screen
        */
        void Update();

        /**
        * Sets the splash screen parent window
        *@param pParent - splash screen parent window
        */
        void SetParent(CWnd* pParent);

        /**
        * Sets the splash screen text
        *@param value - splash screen text to show
        */
        void SetText(const CString& value);

        /**
        * Sets the splash screen text
        *@param value - splash screen text resource identifier to show
        */
        void SetText(UINT resID);

        /**
        * Sets the splash screen progress
        *@param value - progress value
        */
        void SetProgress(std::size_t value);

        /**
        * Loads the splash screen image
        *@param pFileName - splash screen image file name
        */
        bool LoadBitmapImage(LPCTSTR pFileName);

        /**
        * Loads the splash screen image
        *@param pFileName - splash screen image resource identifier
        */
        bool LoadBitmapImage(UINT resID);

    protected:
        /// generated message map functions
        //{{AFX_MSG(ZSplashWnd)
        afx_msg void OnPaint();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        CProgressCtrl m_ProgressControl;
        ZBitmap       m_Bitmap;
        CFont         m_Font;
        COLORREF      m_FontColor;
        COLORREF      m_BackgroundColor;
        CRect         m_ProgressRect;
        CRect         m_TextRect;
        CString       m_Text;
        bool          m_IncludeProgress;
};

#endif
