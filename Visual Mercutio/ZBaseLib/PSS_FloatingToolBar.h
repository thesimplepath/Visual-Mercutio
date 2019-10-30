/****************************************************************************
 * ==> PSS_FloatingToolBar -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a generic floating toolbar                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_FloatingToolBarH
#define PSS_FloatingToolBarH

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

// forward class declarations
class PSS_WindowConfiguration;

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

using namespace sfl;

/**
* Generic floating toolbar
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_FloatingToolBar
{
    public:
        PSS_FloatingToolBar();
        virtual ~PSS_FloatingToolBar();

        /**
        * Initializes the toolbar
        *@param pWndConf - window configuration
        *@param pToolBarManager - toolbar manager
        *@param pMenuBarManager - menu bar manager
        */
        static void Initialize(PSS_WindowConfiguration* pWndConf,
                               SECToolBarManager*       pToolBarManager,
                               SECMenuBar*              pMenuBarManager);

        /**
        * Releases the toolbar resources
        */
        static void Release();

        /**
        * Gets the toolbar manager
        *@return the toolbar manager
        */
        static inline SECToolBarManager* GetToolBarManager();

        /**
        * Gets the menu bar manager
        *@return the menu bar manager
        */
        static inline SECMenuBar* GetMenuBarManager();

        /**
        * Registers the toolbar
        *@param name - toolbar name
        *@param pBar - toolbar to register
        *@param pFrame - frame window
        *@param notation - model notation
        *@return true on success, otherwise false
        */
        static bool RegisterToolBar(const CString& name, CControlBar* pBar, CFrameWnd* pFrame, EModelNotation notation);

        /**
        * Registers the toolbar
        *@param name - toolbar name
        *@param toolBarID - toolbar identifier in resources
        *@param pFrame - frame window
        *@param notation - model notation
        *@return true on success, otherwise false
        */
        static bool RegisterToolBar(const CString& name, UINT toolBarID, CFrameWnd* pFrame, EModelNotation notation);

        /**
        * Unregisters the toolbar
        *@param pBar - toolbar to unregister
        *@return true on success, otherwise false
        */
        static bool UnregisterToolBar(CControlBar* pBar);

        /**
        * Unregisters the toolbar
        *@param toolBarID - toolbar identifier in resources
        *@return true on success, otherwise false
        */
        static bool UnregisterToolBar(UINT toolBarID);

        /**
        * Registers the menu bar
        *@param name - menu bar name
        *@param pMenu - menu bar to register
        *@param pFrame - frame window
        *@param notation - model notation
        *@return true on success, otherwise false
        */
        static bool RegisterMenuBar(const CString& name, CMenu* pMenu, CFrameWnd* pFrame, EModelNotation notation);

        /**
        * Registers the menu bar
        *@param name - menu bar name
        *@param menuBarID - menu bar identifier in resources
        *@param pFrame - frame window
        *@param notation - model notation
        *@return true on success, otherwise false
        */
        static bool RegisterMenuBar(const CString& name, UINT menuBarID, CFrameWnd* pFrame, EModelNotation notation);

        /**
        * Registers and loads the menu bar
        *@param name - menu bar name
        *@param menuBarID - menu bar identifier in resources
        *@param pFrame - frame window
        *@param notation - model notation
        *@return true on success, otherwise false
        */
        static bool RegisterAndLoadMenuBar(const CString& name, UINT menuBarID, CFrameWnd* pFrame, EModelNotation notation);

        /**
        * Unregisters the menu bar
        *@param pBar - menu bar to unregister
        *@return true on success, otherwise false
        */
        static bool UnregisterMenuBar(CMenu* pMenu);

        /**
        * Unregisters the menu bar
        *@param menuBarID - menu bar identifier in resources
        *@return true on success, otherwise false
        */
        static bool UnregisterMenuBar(UINT menuBarID);

        /**
        * Switches the context
        *@param notation - model notation
        */
        static bool SwitchContext(EModelNotation notation);

        /**
        * Reloads the bar state
        *@param name - bar name
        */
        static void ReloadBarState();
        static void ReloadBarState(const CString& name);

        /**
        * Saves the bar state
        */
        static void SaveBarState();

    private:
        /**
        * Shows the toolbar
        *@param notation - model notation
        *@return true on success, otherwise false
        */
        static bool ShowToolBars(EModelNotation notation);

        /**
        * Hides the toolbar
        *@param notation - model notation
        *@return true on success, otherwise false
        */
        static bool HideToolBars(EModelNotation notation);

        /**
        * Checks if the toolbar exists
        *@param name - toolbar name
        *@return true if the toolbar exists, otherwise false
        */
        static bool ToolBarExist(const CString& name);

        /**
        * Checks if the toolbar exists
        *@param toolbarID - toolbar identifier in resources
        *@return true if the toolbar exists, otherwise false
        */
        static bool ToolBarExist(UINT toolbarID);

        /**
        * Checks if the toolbar exists
        *@param pBar - toolbar
        *@return true if the toolbar exists, otherwise false
        */
        static bool ToolBarExist(CControlBar* pBar);

        /**
        * Shows the menu bars
        *@param notation - model notation
        *@return true on success, otherwise false
        */
        static bool ShowMenuBars(EModelNotation notation);

        /**
        * Hides the menu bars
        *@param notation - model notation
        *@return true on success, otherwise false
        */
        static bool HideMenuBars(EModelNotation notation);

        /**
        * Checks if the menu bar exists
        *@param pBar - menu bar name
        *@return true if the menu bar exists, otherwise false
        */
        static bool MenuBarExist(const CString& name);

        /**
        * Checks if the menu bar exists
        *@param menuBarID - menu bar identifier in resources
        *@return true if the menu bar exists, otherwise false
        */
        static bool MenuBarExist(UINT menuBarID);

        /**
        * Checks if the menu bar exists
        *@param pBar - menu bar
        *@return true if the menu bar exists, otherwise false
        */
        static bool MenuBarExist(CMenu* pMenu);

    protected:
        /**
        * Toolbar data
        */
        class IToolBarData
        {
            public:
                CString        m_Name;
                UINT           m_ToolBarID;
                CControlBar*   m_pBar;
                CFrameWnd*     m_pFrame;
                EModelNotation m_Notation;
                bool           m_Reloaded;

                /**
                * Constructor
                *@param name - toolbar name
                *@param pBar - toolbar
                *@param pFrame - frame window
                *@param notation - model notation
                */
                IToolBarData(const CString& name, CControlBar* pBar, CFrameWnd* pFrame, EModelNotation notation);

                /**
                * Constructor
                *@param name - toolbar name
                *@param toolBarID - toolbar identifier in resources
                *@param pFrame - frame window
                *@param notation - model notation
                */
                IToolBarData(const CString& name, UINT toolBarID, CFrameWnd* pFrame, EModelNotation notation);

                virtual ~IToolBarData();
        };

        /**
        * Menu bar data
        */
        class IMenuBarData
        {
            public:
                CString        m_Name;
                UINT           m_MenuID;
                CMenu*         m_pMenu;
                CFrameWnd*     m_pFrame;
                EModelNotation m_Notation;
                bool           m_Reloaded;

                /**
                * Constructor
                *@param name - menu bar name
                *@param pBar - menu bar
                *@param pFrame - frame window
                *@param notation - model notation
                */
                IMenuBarData(const CString& name, CMenu* pMenu, CFrameWnd* pFrame, EModelNotation notation);

                /**
                * Constructor
                *@param name - menu bar name
                *@param menuBarID - menu bar identifier in resources
                *@param pFrame - frame window
                *@param notation - model notation
                */
                IMenuBarData(const CString& name, UINT menuBarID, CFrameWnd* pFrame, EModelNotation notation);

                virtual ~IMenuBarData();
        };

        typedef CCArray_T<IToolBarData*, IToolBarData*> IToolBarSet;
        typedef Iterator_T<IToolBarData*>               IToolBarIterator;
        typedef CCArray_T<IMenuBarData*, IMenuBarData*> IMenuBarSet;
        typedef Iterator_T<IMenuBarData*>               IMenuBarIterator;

    private:
        static IToolBarSet              m_ToolBarSet;
        static IMenuBarSet              m_MenuBarSet;
        static PSS_WindowConfiguration* m_pWndConf;
        static SECToolBarManager*       m_pToolBarManager;
        static SECMenuBar*              m_pMenuBarManager;
        static EModelNotation           m_CurrentNotation;
};

//---------------------------------------------------------------------------
// PSS_FloatingToolBar
//---------------------------------------------------------------------------
SECToolBarManager* PSS_FloatingToolBar::GetToolBarManager()
{
    return m_pToolBarManager;
}
//---------------------------------------------------------------------------
SECMenuBar* PSS_FloatingToolBar::GetMenuBarManager()
{
    return m_pMenuBarManager;
}
//---------------------------------------------------------------------------

#endif
