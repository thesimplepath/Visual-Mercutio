// ZIWelcomeDialog.h : header file
//

#ifndef ZIWelcomeDialog_h
#define ZIWelcomeDialog_h 1

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZIDialog.h"
#include "zBaseLib\AppOpt.h"
#include "PSS_HoverButton.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"
#include "zRes32\ZRes.h"

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 20 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutuile. (En commentaires)

class AFX_EXT_CLASS ZIWelcomeDialog : public ZIDialog
{
// Construction
public:

    // standard constructor
    ZIWelcomeDialog( UINT                    nID,
                     UINT                    nIDBitmap,
                     ZAApplicationOption*    pApplicationOptions,
                     BOOL                    EnableMoveToGeneral    = FALSE,
                     CWnd*                    pParent                = NULL );

    // Dialog Data
    //{{AFX_DATA(ZIWelcomeDialog)
    enum { IDD = IDD_WELCOME };
    CHyperLink      m_HyperLink;
    PSS_HoverButton m_LastFile;
    PSS_HoverButton m_Cancel;
    BOOL            m_DoNotStart;
    //}}AFX_DATA

// Implementation
protected:

    virtual void DoDataExchange( CDataExchange* pDX );    // DDX/DDV support
    virtual void OnCancel();

    // Generated message map functions
    //{{AFX_MSG(ZIWelcomeDialog)
    afx_msg void OnWelcomeLastFile();
    afx_msg void OnPaint();
    virtual BOOL OnInitDialog();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    BOOL                    m_EnableMoveToGeneral;
    ZAApplicationOption*     m_pApplicationOptions;
    UINT m_nIDBitmap;

protected:

    void    SaveState();
};

#endif