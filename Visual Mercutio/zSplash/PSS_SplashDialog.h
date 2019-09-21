/****************************************************************************
 * ==> PSS_SplashDialog ----------------------------------------------------*
 ****************************************************************************
 * Description : Splash screen dialog                                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SplashDialogH
#define PSS_SplashDialogH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "zBaseLib\PSS_Bitmap.h"

// resources
#include "zSplashRes.h"

/**
* Splash screen dialog
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_SplashDialog : public CDialog
{
    public:
        /**
        * Splash screen resources enumeration
        */
        enum
        {
            IDD = IDD_SPLASH_IMAGE
        };

        /**
        * Constructor
        *@param pFileName - splash screen image file name to show
        *@param info - info text to show
        *@param pParent - splash screen parent form
        */
        PSS_SplashDialog(LPCTSTR pFileName, const CString& info = "", CWnd* pParent = NULL);

        /**
        * Constructor
        *@param resID - splash screen image resource identifier to use
        *@param info - info text to show
        *@param pParent - splash screen parent form
        */
        PSS_SplashDialog(UINT resID = 0, const CString& info = "", CWnd* pParent = NULL);

        virtual ~PSS_SplashDialog();

    protected:
        /**
        * Called when dialog is initialized
        *@return true if dialog was successfully initialized, otherwise false
        */
        virtual BOOL OnInitDialog();

        /// generated message map functions
        //{{AFX_MSG(PSS_SplashDialog)
        afx_msg void OnLButtonUp(UINT flags, CPoint point);
        afx_msg void OnLButtonDblClk(UINT flags, CPoint point);
        afx_msg void OnPaint();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /**
        * DDX/DDV support
        *@param pDX - data to exchange
        */
        virtual void DoDataExchange(CDataExchange* pDX);

    private:
        PSS_Bitmap m_Bitmap;
        CString    m_BitmapFileName;
        CString    m_Info;
        CFont      m_Font;
        CRect      m_InfoRect;
        COLORREF   m_FontColor;
        COLORREF   m_BackgroundColor;
        UINT       m_BitmapResID;
};

#endif
