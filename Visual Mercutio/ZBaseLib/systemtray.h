/////////////////////////////////////////////////////////////////////////////
// SystemTray.h : header file
//

#ifndef _INCLUDED_SYSTEMTRAY_H_
#define _INCLUDED_SYSTEMTRAY_H_

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// ZISystemTray window

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 4 janvier 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile (En commentaires).

class AFX_EXT_CLASS ZISystemTray : public CWnd
{
// Construction/destruction
public:

    DECLARE_DYNAMIC( ZISystemTray )

    ZISystemTray();
    ZISystemTray( CWnd* pWnd, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID );
    virtual ~ZISystemTray();

// Operations
public:

    BOOL Enabled()
    {
        return m_bEnabled;
    }

    BOOL Visible()
    {
        return !m_bHidden;
    }

    // Create the tray icon
    BOOL Create( CWnd* pParent, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID );

    // Change or retrieve the Tooltip text
    BOOL    SetTooltipText( LPCTSTR pszTooltipText );
    BOOL    SetTooltipText( UINT nID );
    CString GetTooltipText() const;

    // Change or retrieve the icon displayed
    BOOL  SetIcon( HICON hIcon );
    BOOL  SetIcon( LPCTSTR lpszIconName );
    BOOL  SetIcon( UINT nIDResource );
    BOOL  SetStandardIcon( LPCTSTR lpIconName );
    BOOL  SetStandardIcon( UINT nIDResource );

    HICON GetIcon() const;

    void  HideIcon();
    void  ShowIcon();
    void  RemoveIcon();
    void  MoveToRight();

    // For icon animation
    BOOL  SetIconList( UINT uFirstIconID, UINT uLastIconID );
    BOOL  SetIconList( HICON* pHIconList, UINT nNumIcons );
    BOOL  Animate( UINT nDelayMilliSeconds, int nNumSeconds = -1 );
    BOOL  StepAnimation();
    BOOL  StopAnimation();

    // Change menu default item
    void GetMenuDefaultItem( UINT& uItem, BOOL& bByPos );
    BOOL SetMenuDefaultItem( UINT uItem, BOOL bByPos );

    BOOL CheckMenuItem( UINT uItem, BOOL bStatus );
    BOOL EnableMenuItem( UINT uItem, BOOL bStatus );
    BOOL SetMenuTextItem( UINT uItem, CString Text );

    // Change or retrieve the window to send notification messages to
    BOOL  SetNotificationWnd( CWnd* pNotifyWnd );
    CWnd* GetNotificationWnd() const;

    // Default handler for tray notification message
    virtual LRESULT OnTrayNotification( WPARAM uID, LPARAM lEvent );

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZISystemTray)
    protected:
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    //}}AFX_VIRTUAL

// Generated message map functions
protected:

    //{{AFX_MSG(ZISystemTray)
    afx_msg void OnTimer(UINT nIDEvent);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

// Implementation
protected:

    void Initialise();

    int                        m_nCurrentIcon;
    int                        m_nAnimationPeriod;

    static UINT                m_nIDEvent;

    UINT                    m_DefaultMenuItemID;
    UINT                    m_uIDTimer;

    BOOL                    m_bEnabled;                // does O/S support tray icon?
    BOOL                    m_bHidden;                // Has the icon been hidden?
    BOOL                    m_DefaultMenuItemByPos;

    CArray<HICON, HICON>    m_IconList;

    NOTIFYICONDATA            m_tnd;

    HICON                    m_hSavedIcon;

    CMenu                    m_Menu;
    CMenu*                    m_pSubMenu;

    COleDateTime            m_StartTime;
};

#endif
/////////////////////////////////////////////////////////////////////////////