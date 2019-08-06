// msgbox.h : header file

#ifndef MsgBox_h
#define MsgBox_h 1

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _ZBASELIBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 12 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

extern AFX_EXTENSION_MODULE g_zBaseLibDLL;

#define ID_TIMERABOUT                15
#define NUMBER_OF_ICON                7
#define ANIMATION2_NUMBER_OF_ICON    9

/////////////////////////////////////////////////////////////////////////////
// MsgBox dialog
class AFX_EXT_CLASS MsgBox : public CDialog
{
    DECLARE_DYNCREATE( MsgBox )

// Construction
public:

    // Standard constructor
    MsgBox( CWnd* pParent = NULL );

    // Standard destructor
    ~MsgBox();

    // Dialog Data
    //{{AFX_DATA(MsgBox)
    enum { IDD = IDD_DIALOG_FORSAVE };
    CStatic m_icnApp;
    //}}AFX_DATA

    int DisplayMsgBox( LPCSTR prompt, UINT fuStyle = MB_YESNOCANCEL );
    int DisplayMsgBox( UINT uIDRes, UINT fuStyle = MB_YESNOCANCEL, HINSTANCE hInst = NULL );

    // JMR-MODIF - Le 7 novembre 2006 - Ajout de la fonction DoChangeCancelToUnlock.
    void DoChangeCancelBtnToUnlockBtn( BOOL Value = TRUE );

// Implementation
protected:

    // DDX/DDV support
    virtual void DoDataExchange( CDataExchange* pDX );

    // Generated message map functions
    //{{AFX_MSG(MsgBox)
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnPaint();
    afx_msg void OnYes();
    afx_msg void OnNo();
    afx_msg void OnCancelBtn();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    // JMR-MODIF - Le 6 novembre 2006 - Ajout de la fonction ReleaseDialog.
    void ReleaseDialog();
    void AdjustSize();

private:

    int        m_iIcon;

    UINT    m_uTimerID;

    HICON    m_pIcon[NUMBER_OF_ICON];
    HICON    m_pIconAnimation2[ANIMATION2_NUMBER_OF_ICON];

    CString m_strText;

    UINT    m_fuStyle;

    // JMR-MODIF - Le 7 novembre 2006 - Ajout de la variable bDoShowUnlockButton.
    BOOL    bDoShowUnlockButton;
};

#endif    // MsgBox_h
