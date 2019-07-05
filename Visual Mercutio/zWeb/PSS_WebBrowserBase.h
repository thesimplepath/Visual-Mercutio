/****************************************************************************
 * ==> PSS_WebBrowserBase --------------------------------------------------*
 ****************************************************************************
 * Description : Basic web browser MFC dialog                               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_WebBrowserBaseH
#define PSS_WebBrowserBaseH

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

#ifdef _ZWEBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Basic web browser MFC dialog
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_WebBrowserBase : public CWnd
{
    public:
        /**
        * Gets the class identifier
        *@return class identifier
        */
        CLSID const& GetClsID();

        /**
        * Creates the dialog
        *@param pClassName - class name
        *@param pWindowName - Windows name
        *@param style - dialog style
        *@param rect - rect surrounding the dialog in pixels
        *@param pParentWnd - parent window
        *@param id - dialog identifier
        *@param pContext - dialog create context, can be NULL
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(LPCTSTR         pClassName,
                            LPCTSTR         pWindowName,
                            DWORD           style,
                            const RECT&     rect,
                            CWnd*           pParentWnd,
                            UINT            id,
                            CCreateContext* pContext = NULL);

        /**
        * Creates the dialog
        *@param pWindowName - Windows name
        *@param style - dialog style
        *@param rect - rect surrounding the dialog in pixels
        *@param pParentWnd - parent window
        *@param id - dialog identifier
        *@param pPersist - dialog persistent file, can be NULL
        *@param storage - if TRUE, storage system will be enabled
        *@param licKey - license key, can be NULL
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(LPCTSTR     pWindowName,
                            DWORD       style,
                            const RECT& rect,
                            CWnd*       pParentWnd,
                            UINT        id,
                            CFile*      pPersist = NULL,
                            BOOL        storage  = FALSE,
                            BSTR        licKey   = NULL);

        /**
        * Goes back
        */
        virtual void GoBack();

        /**
        * Goes forward
        */
        virtual void GoForward();

        /**
        * Goes home
        */
        virtual void GoHome();

        /**
        * Goes search
        */
        virtual void GoSearch();

        /**
        * Stops the search
        */
        virtual void Stop();

        /**
        * Quits the browser
        */
        virtual void Quit();

        /**
        * Navigates to url
        *@param pURL - url to navigate to
        *@param flags - flags
        *@param pTargetFrameName - target frame name
        *@param pPostData - post data
        *@param pHeaders - headers
        */
        virtual void Navigate(LPCTSTR  pURL, VARIANT* pFlags, VARIANT* pTargetFrameName, VARIANT* pPostData, VARIANT* pHeaders);
        virtual void Navigate(VARIANT* pURL, VARIANT* pFlags, VARIANT* pTargetFrameName, VARIANT* pPostData, VARIANT* pHeaders);

        /**
        * Refreshes the dialog content
        *@param pLevel - refresh level
        */
        virtual void Refresh();
        virtual void Refresh(VARIANT* pLevel);

        /**
        * Gets application
        *@return application
        */
        virtual LPDISPATCH GetApplication();

        /**
        * Gets parent
        *@return parent
        */
        virtual LPDISPATCH GetParent();

        /**
        * Gets container
        *@return container
        */
        virtual LPDISPATCH GetContainer();

        /**
        * Gets document
        *@return document
        */
        virtual LPDISPATCH GetDocument();

        /**
        * Gets if is a top level container
        *@return TRUE if is a top level container, otherwise FALSE
        */
        virtual BOOL GetTopLevelContainer();

        /**
        * Gets type
        *@return type
        */
        virtual CString GetType();

        /**
        * Gets left position
        *@return left position in pixels
        */
        virtual long GetLeft();

        /**
        * Sets left position
        *@param value - new left position in pixels
        */
        virtual void SetLeft(long value);

        /**
        * Gets top position
        *@return top position in pixels
        */
        virtual long GetTop();

        /**
        * Sets top position
        *@param value - new top position in pixels
        */
        virtual void SetTop(long value);

        /**
        * Gets width
        *@return width in pixels
        */
        virtual long GetWidth();

        /**
        * Sets height
        *@param value - new width in pixels
        */
        virtual void SetWidth(long value);

        /**
        * Gets height
        *@return height in pixels
        */
        virtual long GetHeight();

        /**
        * Sets height
        *@param value - new height in pixels
        */
        virtual void SetHeight(long value);

        /**
        * Gets the location name
        *@return the location name
        */
        virtual CString GetLocationName();

        /**
        * Gets the location url
        *@return the location url
        */
        virtual CString GetLocationURL();

        /**
        * Gets if browser is busy
        *@return TRUE if browser is busy, otherwise FALSE
        */
        virtual BOOL GetBusy();

        /**
        * Converts a position from browser client rect to Windows screen rect
        *@param pCX - x value to convert, converted value on function ends
        *@param pCY - y value to convert, converted value on function ends
        */
        virtual void ClientToWindow(long* pCX, long* pCY);

        /**
        * Gets a property
        *@param pProperty - property name
        *@return property value
        */
        virtual VARIANT GetProperty(LPCTSTR pProperty);

        /**
        * Sets a property
        *@param pProperty - property name
        *@param value - property value
        */
        virtual void SetProperty(LPCTSTR pProperty, const VARIANT& value);

        /**
        * Gets the name
        *@return the name
        */
        virtual CString GetName();

        /**
        * Gets the dialog handle
        *@return the dialog handle
        */
        virtual long GetHwnd();

        /**
        * Gets the full name
        *@return the full name
        */
        virtual CString GetFullName();

        /**
        * Gets the path
        *@return the path
        */
        virtual CString GetPath();

        /**
        * Gets if dialog is visible
        *@return TRUE if dialog is visible, otherwise FALSE
        */
        virtual BOOL GetVisible();

        /**
        * Sets the dialog visible
        *@param value - if TRUE, dialog is visible
        */
        virtual void SetVisible(BOOL bNewValue);

        /**
        * Gets if status bar is visible
        *@return TRUE if status bar is visible, otherwise FALSE
        */
        virtual BOOL GetStatusBar();

        /**
        * Sets the status bar visible
        *@param value - if TRUE, status bar is visible
        */
        virtual void SetStatusBar(BOOL value);

        /**
        * Gets the status text
        *@return the status text
        */
        virtual CString GetStatusText();

        /**
        * Sets the status text
        *@param pValue - status text
        */
        virtual void SetStatusText(LPCTSTR pValue);

        /**
        * Gets the toolbar
        *@return the toolbar index
        */
        virtual long GetToolBar();

        /**
        * Sets the toolbar
        *@param value - toolbar index
        */
        virtual void SetToolBar(long value);

        /**
        * Gets if the menu bar is visible
        *@return TRUE if the menu bar is visible, otherwise FALSE
        */
        virtual BOOL GetMenuBar();

        /**
        * Sets the menu bar visibility
        *@param value - if TRUE, the menu bar is visible
        */
        virtual void SetMenuBar(BOOL value);

        /**
        * Gets if the browser is in full screen mode
        *@return TRUE if the menu bar is in full screen mode, otherwise FALSE
        */
        virtual BOOL GetFullScreen();

        /**
        * Sets the browser in full screen mode
        *@param value - if TRUE, the browser will be set in full screen mode
        */
        virtual void SetFullScreen(BOOL value);

        /**
        * Queries the web status
        *@param cmdID - command identifier
        *@return the web status
        */
        virtual long QueryStatusWB(long cmdID);

        /**
        * Executes a web command
        *@param cmdID - command identifier
        *@param cmdExecOpt - command to execute options
        *@param pIn - input data
        *@param pOut - output data
        *@return the web status
        */
        virtual void ExecWB(long cmdID, long cmdExecOpt, VARIANT* pIn, VARIANT* pOut);

        /**
        * Shows the browser bar
        *@param pClsID - identifier
        *@param pShow - show state
        *@param pSize - size
        */
        virtual void ShowBrowserBar(VARIANT* pClsID, VARIANT* pShow, VARIANT* pSize);

        /**
        * Gets the ready state
        *@return the ready state
        */
        virtual long GetReadyState();

        /**
        * Gets the offline mode state
        *@return TRUE if in offline mode, otherwise FALSE
        */
        virtual BOOL GetOffline();

        /**
        * Sets the offline mode state
        *@param value - if TRUE, browser is in offline mode
        */
        virtual void SetOffline(BOOL value);

        /**
        * Gets the silent mode state
        *@return TRUE if in silent mode, otherwise FALSE
        */
        virtual BOOL GetSilent();

        /**
        * Sets the silent mode state
        *@param value - if TRUE, browser is in silent mode
        */
        virtual void SetSilent(BOOL value);

        /**
        * Gets if registered as browser
        *@return TRUE if registered as browser, otherwise FALSE
        */
        virtual BOOL GetRegisterAsBrowser();

        /**
        * Sets if registered as browser
        *@param value - if TRUE, browser will be registered
        */
        virtual void SetRegisterAsBrowser(BOOL value);

        /**
        * Gets if registered as drop target
        *@return TRUE if registered as drop target, otherwise FALSE
        */
        virtual BOOL GetRegisterAsDropTarget();

        /**
        * Sets if registered as drop target
        *@param value - if TRUE, drop target will be registered
        */
        virtual void SetRegisterAsDropTarget(BOOL value);

        /**
        * Gets the theater mode state
        *@return TRUE if in theater mode, otherwise FALSE
        */
        virtual BOOL GetTheaterMode();

        /**
        * Sets the theater mode state
        *@param value - if TRUE, browser is in theater mode
        */
        virtual void SetTheaterMode(BOOL value);

        /**
        * Gets if the address bar is visible
        *@return TRUE if the address bar is visible, otherwise FALSE
        */
        virtual BOOL GetAddressBar();

        /**
        * Sets the address bar visibility
        *@param value - if TRUE, the address bar will be visible
        */
        virtual void SetAddressBar(BOOL value);

        /**
        * Gets if the browser is resizeable
        *@return TRUE if the browser is resizeable, otherwise FALSE
        */
        virtual BOOL GetResizable();

        /**
        * Sets if the browser is resizeable
        *@param value - if TRUE, the browser will be resizeable
        */
        virtual void SetResizable(BOOL value);

    protected:
        DECLARE_DYNCREATE(PSS_WebBrowserBase)
};

#endif
