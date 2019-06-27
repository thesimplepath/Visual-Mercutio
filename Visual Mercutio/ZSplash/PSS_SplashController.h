/****************************************************************************
 * ==> PSS_SplashController ------------------------------------------------*
 ****************************************************************************
 * Description : Splash screen controller, allows to run a splash screen    *
 *               inside a thread, and to show and hide it                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SplashControllerH
#define PSS_SplashControllerH

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

// processsoft
#include "PSS_SplashWndThread.h"

#ifdef _ZSPLASHEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Splash screen controller
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SplashController
{
    public:
        PSS_SplashController();
        virtual ~PSS_SplashController();

        /**
        * Shows the splash screen
        *@param pFileName - splash screen image file name
        *@param maxTime - maximum time the splash screen can be shown in seconds
        *@param includeProgress - if true, progress bar will be shown
        *@param pParent - parent window owning the splash screen, can be NULL
        *@return true on success, otherwise false
        */
        bool Show(LPCTSTR pFileName, std::size_t maxTime = 20, bool includeProgress = true, CWnd* pParent = NULL);

        /**
        * Shows the splash screen
        *@param resID - splash screen image resource identifier to show
        *@param maxTime - maximum time the splash screen can be shown in seconds
        *@param includeProgress - if true, progress bar will be shown
        *@param pParent - parent window owning the splash screen, can be NULL
        *@return true on success, otherwise false
        */
        bool Show(UINT resID, std::size_t MaxTime = 20, bool IncludeProgress = true, CWnd* pParent = NULL);

        /**
        * Hides the splash screen
        *@return true on success, otherwise false
        */
        bool Hide();

        /**
        * Sets progress position
        *@param value - progress value
        */
        void SetProgress(std::size_t value);

        /**
        * Sets text
        *@param value - text to show
        */
        void SetText(const CString& value);

        /**
        * Sets text
        *@param resID - text resource identifier to show
        */
        void SetText(UINT resID);

        /**
        * Assigns parent window
        *@param pParent - parent window owning the splash screen
        */
        void SetParent(CWnd* pParent);

    private:
        PSS_SplashWndThread* m_pThread;
};

#endif
