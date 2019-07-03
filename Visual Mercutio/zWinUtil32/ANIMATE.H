// animate.h : header file
//

//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#ifndef _WIN32
    extern "C" extern void WINAPI InitZWinUtilDLL();
    extern AFX_EXTENSION_MODULE NEAR extensionZWinUtilDLL;
    #define    AFX_EXT_CLASS
#else // Only in 16bit
    extern AFX_EXTENSION_MODULE extensionZWinUtil32DLL;
#endif // Only in 32bit


#ifdef _ZWINUTIL32EXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS

/////////////////////////////////////////////////////////////////////////////
// ZIAnimateDlg dialog

class AFX_EXT_CLASS ZIAnimateDlg : public CDialog
{
// Construction
public:
    ZIAnimateDlg( CWnd* pParent = NULL);    // standard constructor
    BOOL DisplayNext();
    void CloseAnimation();

// Dialog Data
    //{{AFX_DATA(ZIAnimateDlg)
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

// Data
private:
    UINT    m_uID;
    BOOL    m_bStop;
    CRect    m_ImageRect;
// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(ZIAnimateDlg)
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    virtual void OnCancel();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};



#undef AFX_DATA
#define AFX_DATA
