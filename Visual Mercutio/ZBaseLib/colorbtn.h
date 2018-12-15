
/*************************************************************************

ColorBtn.h header file

ZCColorBtn: A control panel like color picker
           by The Gremlin

Compatibility: Visual C++ 4.0 and up.

**************************************************************************/

#ifndef _COLORBTN_H_
#define _COLORBTN_H_

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// In order to ease use, these values have been hard coded in colorbtn.rc
// This avoids the need for another header file.
#define IDD_COLORBTN                    ( 5100 )
#define IDC_COLOR1                      ( 5101 )
#define IDC_COLOR20                     ( 5120 )
#define IDC_OTHER                       ( 5121 )

#define MESSAGE_COLOR_CHANGED           WM_USER + 33

#ifdef _ZBASELIBEXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 21 octobre 2005 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// _ZVColorBtnDlg class

class _ZVColorBtnDlg : public CDialog
{
// Construction
public:

    // standard constructor
    _ZVColorBtnDlg( CWnd* pParent = NULL );

    // Dialog Data
    //{{AFX_DATA(ZVColorBtnDlg)
    enum { IDD = IDD_COLORBTN };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZVColorBtnDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZVColorBtnDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnOther();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    void OnColor( UINT id );
    void EndDialog( int nResult );

public:

    static COLORREF colors[20];
    static BYTE        used[20];

    CButton*        parent;
    int                colorindex;
};

/////////////////////////////////////////////////////////////////////////////
// ZCColorBtn class

class AFX_EXT_CLASS ZCColorBtn : public CButton
{
public:

    // Construction / Destruction
    ZCColorBtn();
    virtual ~ZCColorBtn();

    // The selected color,set this variable to initialize the
    // button's color and read to see the results
    COLORREF GetColor()
    {
        return currentcolor;
    }

    void SetColor( COLORREF color )
    {
        currentcolor = color;
    }

    // If using Serialize, call Reset to reinitialize the color table at OnNewDocument()
    static void Reset();

    // Use Load and Store to save/restore the color table to/from the registry
    static BOOL Load();
    static BOOL Store();

    // JMR-MODIF - Le 21 octobre 2005 - Supprimé la déclaration static pour la fonction Serialize.
    // Use Serialize to store the color table in a file. Call at the document's Serialize()
    void Serialize( CArchive& ar );

// Implementation
public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZCColorBtn)
    //}}AFX_VIRTUAL

// Generated message map functions
protected:

    //{{AFX_MSG(ZCColorBtn)
    afx_msg void OnClicked();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    void DrawItem( LPDRAWITEMSTRUCT );

private:

    // A number of pens and brushes needed to paint the button
    CBrush            backbrush;
    CBrush            nullbrush;

    CBrush*            oldbrush;

    CPen            blackpen;
    CPen            dkgray;
    CPen            whitepen;
    CPen            nullpen;

    CPen*            oldpen;

    COLORREF        currentcolor;

    _ZVColorBtnDlg    dlg;
};

#endif