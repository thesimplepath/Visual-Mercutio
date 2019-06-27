/****************************************************************************
 * ==> PSS_SplashContainer -------------------------------------------------*
 ****************************************************************************
 * Description : Splash screen container                                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SplashContainerH
#define PSS_SplashContainerH

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
* Splash screen container
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SplashContainer
{
    public:
        /**
        * Constructor
        *@param pFileName - splash screen image file name to show
        *@param info - info text to show
        *@param pParent - splash screen parent form
        */
        PSS_SplashContainer(LPCTSTR pFileName, const CString& info = "", CWnd* pParent = NULL);

        /**
        * Constructor
        *@param resID - splash screen image resource identifier to use
        *@param info - info text to show
        *@param pParent - splash screen parent form
        */
        PSS_SplashContainer(UINT resID = 0, const CString& info = "", CWnd* pParent = NULL);

        virtual ~PSS_SplashContainer();

        /**
        * Shows the splash screen
        *@param pFileName - splash screen image file name to show
        *@param info - info text to show
        *@param pParent - splash screen parent form
        */
        bool Show(LPCTSTR pFileName, const CString& info = "", CWnd* pParent = NULL);

        /**
        * Shows the splash screen
        *@param resID - splash screen image resource identifier to use
        *@param info - info text to show
        *@param pParent - splash screen parent form
        */
        bool Show(UINT nResID, const CString& info = "", CWnd* pParent = NULL);

        /**
        * Shows the splash screen
        *@param info - info text to show
        */
        bool Show(const CString& info = "");

    private:
        CWnd*   m_pParentWnd;
        CString m_BitmapFileName;
        CString m_Info;
        UINT    m_BitmapResID;

        /**
        * Shows the splash screen in modal mode
        */
        bool ShowModal() const;
};

#endif
