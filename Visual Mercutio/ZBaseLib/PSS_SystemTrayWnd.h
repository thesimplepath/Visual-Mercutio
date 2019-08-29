/****************************************************************************
 * ==> PSS_SystemTrayWnd ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a system tray window                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_SystemTrayWndH
#define PSS_SystemTrayWndH

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// mfc
#include <afxtempl.h>

#ifdef _ZBASELIBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* System tray window
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_SystemTrayWnd : public CWnd
{
    DECLARE_DYNAMIC(PSS_SystemTrayWnd)

    public:
        PSS_SystemTrayWnd();

        /**
        * Constructor
        *@param pWnd - parent window
        *@param callbackMessage - callback message
        *@param pTooltip - tooltip text
        *@param hIcon - icon handle
        *@param id - identifier
        */
        PSS_SystemTrayWnd(CWnd* pWnd, UINT callbackMessage, LPCTSTR pTooltip, HICON hIcon, UINT id);

        virtual ~PSS_SystemTrayWnd();

        /**
        * Checks if the tray is enabled
        *@return TRUE if the tray is enabled, otherwise FALSE
        */
        virtual inline BOOL Enabled();

        /**
        * Checks if the tray is visible
        *@return TRUE if the tray is visible, otherwise FALSE
        */
        virtual inline BOOL Visible();

        /**
        * Creates the tray icon
        *@param pParent - parent window
        *@param callbackMessage - callback message
        *@param pTip - tooltip text
        *@param hIcon - icon handle
        *@param id - identifier
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Create(CWnd* pParent, UINT callbackMessage, LPCTSTR pTip, HICON hIcon, UINT id);

        /**
        * Sets the tooltip text
        *@param pTooltipText - tooltip text
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetTooltipText(LPCTSTR pTooltipText);

        /**
        * Sets the tooltip text
        *@param id - tooltip text identifier
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetTooltipText(UINT id);

        /**
        * Gets the tooltip text
        *@return the tooltip text
        */
        virtual CString GetTooltipText() const;

        /**
        * Sets the displayed icon
        *@param hIcon - icon handle
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetIcon(HICON hIcon);

        /**
        * Sets the displayed icon
        *@param pIconName - icon name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetIcon(LPCTSTR pIconName);

        /**
        * Sets the displayed icon
        *@param iconID - icon resource identifier
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetIcon(UINT iconID);

        /**
        * Sets the standard icon
        *@param pIconName - icon name
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetStandardIcon(LPCTSTR lpIconName);

        /**
        * Sets the standard icon
        *@param iconID - icon resource identifier
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetStandardIcon(UINT iconID);

        /**
        * Gets the icon
        *@return the icon handle, NULL if no icon or on error
        */
        virtual HICON GetIcon() const;

        /**
        * Hides the icon
        */
        virtual void HideIcon();

        /**
        * Shows the icon
        */
        virtual void ShowIcon();

        /**
        * Removes the icon
        */
        virtual void RemoveIcon();

        /**
        * Moves the splash screen to the right
        */
        virtual void MoveToRight();

        /**
        * Sets the animated icon list
        *@param firstIconID - first icon identifier in the resources
        *@param lastIconID - last icon identifier in the resources
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetIconList(UINT firstIconID, UINT lastIconID);

        /**
        * Sets the animated icon list
        *@param pIconList - animated icon frame list
        *@param iconCount - icon count in the list
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetIconList(HICON* pIconList, UINT iconCount);

        /**
        * Animates the icon
        *@param delay - delay in milliseconds
        *@param duration - duration in seconds, -1 for infinite
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL Animate(UINT delay, int duration = -1);

        /**
        * Steps into the animation
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL StepAnimation();

        /**
        * Stops the animation
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL StopAnimation();

        /**
        * Gets the menu default item
        *@param[out] item - item
        *@param[out] byPos - if TRUE, the item is get by position
        */
        virtual void GetMenuDefaultItem(UINT& item, BOOL& byPos) const;

        /**
        * Gets the menu default item
        *@param item - item
        *@param byPos - if TRUE, the item will be get by position
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetMenuDefaultItem(UINT item, BOOL byPos);

        /**
        * Checks the menu item
        *@param item - item
        *@param status - if TRUE, the item will be enabled
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL CheckMenuItem(UINT item, BOOL status);

        /**
        * Enables the menu item
        *@param item - item to enable
        *@param status - if TRUE, the item will be enabled
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL EnableMenuItem(UINT item, BOOL status);

        /**
        * Sets the menu item text
        *@param item - item to enable
        *@param text - item text
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetMenuTextItem(UINT item, const CString& text);

        /**
        * Gets the window to send notification messages to
        *@return the window to send notification messages to, NULL if no window defined or on error
        */
        virtual CWnd* GetNotificationWnd() const;

        /**
        * Sets the window to send notification messages to
        *@param pNotifyWnd - the window to send notification messages to
        *@return TRUE on success, otherwise FALSE
        */
        virtual BOOL SetNotificationWnd(CWnd* pNotifyWnd);

        /**
        * Called when tray receives notification message
        *@param wParam - word parameter
        *@param lParam - long parameter
        *@return result
        */
        virtual LRESULT OnTrayNotification(UINT wParam, LONG lParam);

    protected:
        static UINT          m_EventID;
        CArray<HICON, HICON> m_IconList;
        NOTIFYICONDATA       m_NotifyIconData;
        HICON                m_hSavedIcon;
        CMenu                m_Menu;
        CMenu*               m_pSubMenu;
        COleDateTime         m_StartTime;
        UINT                 m_DefaultMenuItemID;
        UINT                 m_TimerID;
        int                  m_CurrentIcon;
        int                  m_AnimationPeriod;
        BOOL                 m_Enabled;
        BOOL                 m_Hidden;
        BOOL                 m_DefaultMenuItemByPos;

        /**
        * Initializes the tray panel
        */
        void Initialise();

        //{{AFX_MSG(PSS_SystemTrayWnd)
        afx_msg void OnTimer(UINT nIDEvent);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

        /// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(PSS_SystemTrayWnd)
        virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
        //}}AFX_VIRTUAL
};

//---------------------------------------------------------------------------
// PSS_SystemTrayWnd
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::Enabled()
{
    return m_Enabled;
}
//---------------------------------------------------------------------------
BOOL PSS_SystemTrayWnd::Visible()
{
    return !m_Hidden;
}
//---------------------------------------------------------------------------

#endif
