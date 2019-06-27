/****************************************************************************
 * ==> PSS_SplashWndThread -------------------------------------------------*
 ****************************************************************************
 * Description : Threaded splash screen window                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SplashWndThreadH
#define PSS_SplashWndThreadH

#if _MSC_VER > 1000
    #pragma once
#endif

// processsoft
#include "PSS_SplashWnd.h"

/**
* Threaded splash screen window
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class PSS_SplashWndThread : public CWinThread
{
    DECLARE_DYNCREATE(PSS_SplashWndThread)

    public:
        /**
        * Constructor
        *@param pFileName - splash screen image file name
        *@param maxTime - maximum time the splash screen can be shown in seconds
        *@param includeProgress - if true, progress bar will be shown
        *@param pParent - parent window owning the splash screen, can be NULL
        */
        PSS_SplashWndThread(LPCTSTR pFileName, std::size_t maxTime = 20, bool includeProgress = true, CWnd* pParent = NULL);

        /**
        * Constructor
        *@param resID - splash screen image resource identifier to show
        *@param maxTime - maximum time the splash screen can be shown in seconds
        *@param includeProgress - if true, progress bar will be shown
        *@param pParent - parent window owning the splash screen, can be NULL
        */
        PSS_SplashWndThread(UINT resID, std::size_t maxTime = 20, bool includeProgress = true, CWnd* pParent = NULL);

        /**
        * Constructor
        *@param maxTime - maximum time the splash screen can be shown in seconds
        *@param includeProgress - if true, progress bar will be shown
        *@param pParent - parent window owning the splash screen, can be NULL
        */
        PSS_SplashWndThread(std::size_t maxTime = 20, bool includeProgress = true, CWnd* pParent = NULL);

        virtual ~PSS_SplashWndThread();

        /**
        * Initializes the splash screen instance
        *@return true on success, otherwise false
        */
        virtual BOOL InitInstance();

        /**
        * Exits the splash screen instance
        *@return result code
        */
        virtual int ExitInstance();

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

        /**
        * Kills the thread
        *@note This function is called in the context of other threads, not the thread itself
        */
        void KillThread();

    protected:
        /// Generated message map functions
        //{{AFX_MSG(ZSplashWinThread)
            // NOTE the ClassWizard will add and remove member functions here
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        virtual int Run();

    private:
        CWnd*         m_pParent;
        PSS_SplashWnd m_SplashWnd;
        HANDLE        m_hEventKill;
        HANDLE        m_hEventDead;
        CString       m_BitmapFile;
        COleDateTime  m_StartTime;
        std::size_t   m_MaxTime;
        UINT          m_ResID;
        bool          m_IncludeProgress;

        /**
        * Deletes the thread
        */
        void Delete();
};

#endif
