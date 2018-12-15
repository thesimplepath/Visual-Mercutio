// ZWizard.h : header file

#ifndef ZWizard_h
#define ZWizard_h 1

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zWinUtil32\ZWinUtil32.h"

#include "ZIDialog.h"

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 6 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZIWizardDialog dialog

class AFX_EXT_CLASS ZIWizardDialog : public ZIDialog
{
// Construction
public:

    // Standard constructor
    ZIWizardDialog( UINT    nID                = 0,
                    UINT    nBitmapID        = 0,
                    UINT    nIconID            = 0,
                    CString    sTitleWindow    = _T( "" ),
                    CString    sTitleWizard    = _T( "" ),
                    CString    sTextWizard        = _T( "" ),
                    BOOL    bAutoCenter        = TRUE,
                    BOOL    bStandAlone        = FALSE,
                    CWnd*    pParent            = NULL );

    ZIWizardDialog( UINT    nID,
                    UINT    nBitmapID,
                    UINT    nIconID,
                    UINT    nTitleWindowID,
                    UINT    nTitleWizardID,
                    UINT    nTextWizardID,
                    BOOL    bAutoCenter        = TRUE,
                    BOOL    bStandAlone        = FALSE,
                    CWnd*    pParent            = NULL );

    ZIWizardDialog( UINT        nID,
                    UINT        nBitmapID,
                    UINT        nIconID,
                    CString        sTitleWindow,
                    CString        sTitleWizard,
                    CString        sTextWizard,
                    COLORREF    BackCol,
                    COLORREF    StaticCol,
                    COLORREF    EditCol,
                    BOOL        bAutoCenter    = TRUE,
                    BOOL        bStandAlone    = FALSE,
                    CWnd*        pParent        = NULL );

    ZIWizardDialog( UINT        nID,
                    UINT        nBitmapID,
                    UINT        nIconID,
                    UINT        nTitleWindowID,
                    UINT        nTitleWizardID,
                    UINT        nTextWizardID,
                    COLORREF    BackCol,
                    COLORREF    StaticCol,
                    COLORREF    EditCol,
                    BOOL        bAutoCenter    = TRUE,
                    BOOL        bStandAlone    = FALSE,
                    CWnd*        pParent        = NULL);

    BOOL Create( UINT        nID                = 0,
                 UINT        nBitmapID        = 0,
                 UINT        nIconID            = 0,
                 CString    sTitleWindow    = _T( "" ),
                 CString    sTitleWizard    = _T( "" ),
                 CString    sTextWizard        = _T( "" ),
                 BOOL        bAutoCenter        = TRUE,
                 BOOL        bStandAlone        = FALSE,
                 CWnd*        pParent            = NULL );

    BOOL Create( UINT        nID,
                 UINT        nBitmapID,
                 UINT        nIconID,
                 UINT        nTitleWindowID,
                 UINT        nTitleWizardID,
                 UINT        nTextWizardID,
                 BOOL        bAutoCenter        = TRUE,
                 BOOL        bStandAlone        = FALSE,
                 CWnd*        pParent            = NULL );

    BOOL Create( UINT        nID,
                 UINT        nBitmapID,
                 UINT        nIconID,
                 CString    sTitleWindow,
                 CString    sTitleWizard,
                 CString    sTextWizard,
                 COLORREF    BackCol,
                 COLORREF    StaticCol,
                 COLORREF    EditCol,
                 BOOL        bAutoCenter        = TRUE,
                 BOOL        bStandAlone        = FALSE,
                 CWnd*        pParent            = NULL );

    BOOL Create( UINT        nID,
                 UINT        nBitmapID,
                 UINT        nIconID,
                 UINT        nTitleWindowID,
                 UINT        nTitleWizardID,
                 UINT        nTextWizardID,
                 COLORREF    BackCol,
                 COLORREF    StaticCol,
                 COLORREF    EditCol,
                 BOOL        bAutoCenter        = TRUE,
                 BOOL        bStandAlone        = FALSE,
                 CWnd*        pParent            = NULL );

    // Dialog Data
    //{{AFX_DATA(ZIWizardDialog)
        CBitmapButton    m_btnHelp;
    //}}AFX_DATA

    void    SetWizardWindowTitle( UINT nID );
    void    SetWizardSubjectText( UINT nID );
    void    SetWizardBodyText( UINT nID );
    void    SetWizardWindowTitle( const CString value );
    void    SetWizardSubjectText( const CString value );
    void    SetWizardBodyText( const CString value );

// Implementation
protected:

    void Paint( CDC& dc );
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(ZIWizardDialog)
    afx_msg void OnNext();
    afx_msg void OnPaint();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    void CreateFont();

protected:

    UINT            m_nID;
    UINT            m_nBitmapID;
    UINT            m_nIconID;
    BOOL            m_bStandAlone;
    CString            m_sTitleWindow;
    CString            m_sTitleWizard;
    CString            m_sTextWizard;
    CRect            m_DialogRect;
    HINSTANCE        m_hInst;
    HICON            m_hIcon;

private:

    CFont            m_TextFont;
    CFont            m_TitleFont;
};

inline void ZIWizardDialog::SetWizardWindowTitle( const CString value )
{
    m_sTitleWindow = value;
    SetWindowText( m_sTitleWindow );
}

inline void ZIWizardDialog::SetWizardSubjectText( const CString value )
{
    m_sTitleWizard = value;
}

inline void ZIWizardDialog::SetWizardBodyText( const CString value )
{
    m_sTextWizard = value;
}

#endif    // ZIWizardDialog_h
