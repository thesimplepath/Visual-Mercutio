/****************************************************************************
 * ==> Toolbarx ------------------------------------------------------------*
 ****************************************************************************
 * Description : Interface of the CToolBarEx, CBubble, and CFrame classes   *
 * Developer   : Processsoft                                                *
 ****************************************************************************
 * NOTE: MFC Undocumented feature usage                                     *
 *                                                                          *
 *  This code relies on internal knowledge of the class and structures      *
 *  used to implement the MFC 2.0/2.5 CToolBar, and CFrame classes.         *
 *                                                                          *
 *  It relies on the following undocumented member functions from CToolBar  *
 *    CToolBar::HitTest()                                                   *
 *                                                                          *
 *  It uses the following undocumented messages and defines from afxpriv.h  *
 *    WM_SETMESSAGESTRING                                                   *
 *    AFX_IDS_IDLEMESSAGE                                                   *
 *                                                                          *
 *  This code is compatible with:                                           *
 *    - MFC verions 2.0 and 2.5 for Win16 and Win32                         *
 ****************************************************************************/

#ifndef _WIN32

#ifndef ToolbarxH
#define ToolbarxH

#if !defined(TBX_FRAME) && !defined(TBX_MDIFRAME) && !defined(TBX_OLEIPFRAME)
    #error Either TBX_FRAME, TBX_MDIFRAME, or TBX_OLEIPFRAME must be globally defined to include the proper CFrame class
#endif

// mfc
#include <afxwin.h>
#include <afxext.h>

// visual mercutio
#include "ZAConst.h"

// control defines
#define TBX_TIMER_OFF     -1
#define TBX_TIMER_PENDING  1
#define TBX_TIMER_ID       2010
#define TBX_TIMER_TIME     1000
#define TBX_FONT_SIZE     -8
#define TBX_BUBBLE_DELAY   100

/**
* CBubble window
*/
class CBubble : public CWnd
{
    DECLARE_DYNAMIC(CBubble);

    public:
        CBubble();
        virtual ~CBubble();

        /**
        * Check if bubble window was created
        *@return true if created, otherwise false
        */
        BOOL IsCreated()
        {
            return m_bCreated;
        }

        /**
        * Creates the bubble window
        *@return true on success, otherwise false
        */
        BOOL Create();

        /**
        * Destroys the bubble window
        *@return true on success, otherwise false
        */
        virtual BOOL DestroyWindow();

        /**
        * Turns the bubble off
        */
        void OffBubble();

        /**
        * Requests the bubble window to track with the specified text and string resource ID
        *@param pt - track point
        *@param string - text to show
        *@param nID - resource ID
        */
        void Track(const CPoint& pt, const CString& string, int nID);

        /**
        * Hides the bubble window
        */
        void Hide();

        // add GetOwner() and SetOwner() for MFC < 2.5. GetOwner() and SetOwner() are provided in
        // MFC >= 2.5 only. They are used for OLE 2.0 in-place activation support. Since OLE 2.0
        // is only in MFC 2.5 and higher, these functions are required to allow the code to still
        // work in MFC < 2.5
        #if (_MFC_VER < 0x0250)
            // use HWND because the CWnd might be temporary
            HWND hwndOwner;

            /**
            * Sets the bubble window owner
            *@param pOwner - owner
            */
            void SetOwner(CWnd* pOwner)
            {
                hwndOwner = pOwner->GetSafeHwnd();
            }

            /**
            * Gets the bubble window owner
            *@return owner
            */
            CWnd* GetOwner() const
            {
                return (hwndOwner ? FromHandle(hwndOwner) : GetParent());
            }
        #endif

    protected:
        // generated message map functions
        //{{AFX_MSG(CBubble)
        afx_msg void OnPaint();
        afx_msg LONG OnSetText(UINT, LONG lParam);
        afx_msg void OnTimer(UINT nIDEvent);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Starts the timer
        */
        void StartTimer();

        /**
        * Stops the timer
        */
        void StopTimer();

    private:
        static CString near m_strClassName;  // bubble window class name
        static CFont   near m_fntFont;       // bubble window font
        static int     near m_nBubbleHeight; // bubble window height
        static int     near m_nTextHeight;   // Text height
               BOOL         m_bCreated;      // bubble window creation flag
               BOOL         m_bBubbleOn;     // bubble window ON/OFF status flag
               int          m_nTimerMode;    // current timer mode
               int          m_nID;           // ID of the item we're tracking
};

/**
* CToolBar
*/
class CToolBarEx : public CToolBar
{
    DECLARE_DYNAMIC(CToolBarEx);

    public:
        CToolBarEx();
        virtual ~CToolBarEx();

        /**
        * Creates the toolbar
        *@param pParentWnd - parent window
        *@param dwStyle - toolbar style
        *@return true on success, otherwise false
        */
        BOOL Create(CWnd* pParentWnd, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP, UINT nID = AFX_IDW_TOOLBAR);

        /**
        * Pre-translates messages
        *@param msg - message
        *@return true on success, otherwise false
        */
        BOOL PreTranslateMessage(MSG* msg);

    protected:
        /**
        * Shows and tracks the bubble window
        *@param bTrackingButton - 
        */
        // todo -cFeature -oJean: complete the documentation
        void TrackBubble(BOOL bTrackingButton = TRUE);

        /**
        * Cancels the bubble window
        *@note Static, so the hook can use it
        */
        static void CancelBubble();

        /**
        * Determines if the hovered window is a candidate for tranfering the bubble window to
        *@param pcwndOver - window to check
        *@return true if the hovered window is a valid candidate, otherwise false
        */
        BOOL IsTransferable(CWnd* pcwndOver);

    protected:
        // generated message map functions
        //{{AFX_MSG(CToolBarEx)
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnCancelMode();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

    private:
        /**
        * Passes the bubble control to another window
        *@param bMode - 
        */
        // todo -cFeature -oJean: complete the documentation
        void TransferBubble(BOOL bMode = TRUE);

        /**
        * Gets the first descendent window for the CToolBarEx from a child window
        *@param pcwndChild - child window to start from
        *@return descendent window, NULL if not found
        */
        // todo -cFeature -oJean: fix the name spelling
        CWnd* GetFirstDescendantWindow(CWnd* pcwndChild);

        /**
        * Installs a keyboard hook
        */
        void InstallKeyboardHook();

        /**
        * Removes a keyboard hook
        */
        void RemoveKeyboardHook();

        /**
        * Keyboard hook procedure (used to disable bubble when a key is pressed)
        *@note Static, so the callback can be a member of this class
        *@param code - message code
        *@param wParam - additional message information. The contents of this parameter depend on the value of the code parameter
        *@param lParam - additional message information. The contents of this parameter depend on the value of the code parameter
        *@return the result of the message processing, depends on the message sent
        */
        static LRESULT CALLBACK AFX_EXPORT KeyboardHookCallback(int code, WPARAM wParam, LPARAM lParam);

        // add GetOwner() and SetOwner() for MFC < 2.5. GetOwner() and SetOwner() are provided in
        // MFC >= 2.5 only. They are used for OLE 2.0 in-place activation support. Since OLE 2.0
        // is only in MFC 2.5 and higher, these functions are required to allow the code to still
        // work in MFC < 2.5
        #if (_MFC_VER < 0x0250)
            // use HWND because the CWnd might be temporary
            HWND hwndOwner;

            /**
            * Sets the toolbar owner
            *@param pOwner - owner
            */
            void SetOwner(CWnd* pOwner)
            {
                hwndOwner = pOwner->GetSafeHwnd();
            }

            /**
            * Gets the toolbar owner
            *@return owner
            */
            CWnd* GetOwner() const
            {
                return (hwndOwner ? FromHandle(hwndOwner) : GetParent());
            }
        #endif

    protected:
        static CBubble near m_Bubble; // CBubble window. NOTE one bubble window is shared by all CToolBarEx's

    private:
        // NOTE these are static so the hook can get to them
        static BOOL  near m_bCaptured;    // we mouse captured flag
        static int   near m_nButtonIndex; // current index of button we're over
        static int   near m_nChildID;     // current ID of the child window we're tracking
        static HHOOK near m_hHook;        // handle to the keyboard hook installed
        static int   near m_nToolBars;    // number of toolbar we have created
        static BOOL  near m_bWin31;       // window version flag
};

/**
* CFrameWndEx
*@note Only used for MFC 2.5 and higher
*/
#if defined(TBX_FRAME) && (_MFC_VER >= 0x0250)
    class CFrameWndEx : public CFrameWnd
    {
        DECLARE_DYNCREATE(CFrameWndEx)

        public:
            CFrameWndEx();
            virtual ~CFrameWndEx();

        protected:
            // generated message map functions
            //{{AFX_MSG(CFrameWndEx)
            afx_msg LONG OnSetMessageString(UINT wParam, LONG lParam);
            //}}AFX_MSG
            DECLARE_MESSAGE_MAP()
    };

    // automatic class substitution
    #define CFrameWnd CFrameWndEx
#endif

/**
* CMDIFrameWndEx
*@note Only used for MFC 2.5 and higher
*/
#if defined(TBX_MDIFRAME) && (_MFC_VER >= 0x0250)
    class CMDIFrameWndEx : public CMDIFrameWnd
    {
        DECLARE_DYNCREATE(CMDIFrameWndEx)

        public:
            CMDIFrameWndEx();
            virtual ~CMDIFrameWndEx();

        protected:
            // generated message map functions
            //{{AFX_MSG(CMDIFrameWndEx)
            afx_msg LONG OnSetMessageString(UINT wParam, LONG lParam);
            //}}AFX_MSG
            DECLARE_MESSAGE_MAP()
    };

    // automatic class substitution
    #define CMDIFrameWnd CMDIFrameWndEx
#endif

/**
* COleIPFrameWndEx
*@note Only used for MFC 2.5 and higher
*/
#if defined(TBX_OLEIPFRAME) && (_MFC_VER >= 0x0250)
class COleIPFrameWndEx : public COleIPFrameWnd
{
    DECLARE_DYNCREATE(COleIPFrameWndEx)

    public:
        COleIPFrameWndEx();
        virtual ~COleIPFrameWndEx();

    protected:
        // generated message map functions
        //{{AFX_MSG(COleIPFrameWndEx)
        afx_msg LONG OnSetMessageString(UINT wParam, LONG lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

    // automatic class substitution
    #define COleIPFrameWnd COleIPFrameWndEx
#endif

/**
* CStatusBarEx window
*@note Only used for MFC 2.0 and earlier
*/
#if (_MFC_VER < 0x0250)
    class CStatusBarEx : public CStatusBar
    {
        DECLARE_DYNCREATE(CStatusBarEx)

    public:
        CStatusBarEx();
        virtual ~CStatusBarEx();

    protected:
        // generated message map functions
        //{{AFX_MSG(CStatusBarEx)
        afx_msg LONG OnSetText(UINT, LONG lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
    };

    // automatic class substitution
    #define CStatusBar CStatusBarEx
#endif

// automatic class substitution
#define CToolBar CToolBarEx

#endif

#endif