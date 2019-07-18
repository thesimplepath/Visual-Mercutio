// rejact.h : header file
//

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#ifdef _WIN32
    // mfc
    #include <afxwin.h>
    #include <afxext.h>
    #include <afxcmn.h>
    #include <afxdtctl.h>
    #include <afxcmn.h>

    // CodeJoke components library
    #include <CJ60Lib.h>
#endif

// processsoft
#include "zBaseLib\ZIDialog.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "ZWinUtil32Res.h"
#endif

#ifdef _ZWINUTIL32EXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIRejectActivityInput dialog

class AFX_EXT_CLASS ZIRejectActivityInput : public ZIDialog
{
// Construction
public:
    ZIRejectActivityInput(CStringArray* pArray = NULL, CWnd* pParent = NULL);    // standard constructor
    CString    GetRejectText() { return m_RejectText; }
    
private:

// Dialog Data
    //{{AFX_DATA(ZIRejectActivityInput)
    enum { IDD = IDD_REJECTACTIVITYINFO };
#ifdef _WIN32 // In 32bit
    CCJFlatComboBox    m_RejectCategory;
#endif
#ifndef _WIN32 // In 16bit
    CComboBox    m_RejectCategory;
#endif
    CString    m_RejectText;
    //}}AFX_DATA

    CStringArray*    m_pArray;
    CString            m_OwnerText;
private:
    void CheckControlStates();

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(ZIRejectActivityInput)
    afx_msg void OnSelChangeRejectCategory();
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//#undef  AFX_DATA
//#define AFX_DATA
