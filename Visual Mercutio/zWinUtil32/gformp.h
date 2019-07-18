// gformp.h : header file
//
#if !defined(__GFORMP_H)
#define __GFORMP_H

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\TmplMng.h"

// resources
#ifndef _WIN32
    #include "zWinUtilRes.h"
#else
    #include "zWinUtil32Res.h"
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
// ZIGenericFormPage dialog

class AFX_EXT_CLASS ZIGenericFormPage : public CPropertyPage
{
// Construction
public:
    ZIGenericFormPage();    // standard constructor
    ZIGenericFormPage( CWnd *pMain, CString sTitle, ZDTemplateManager* pTemplateManager );
    ~ZIGenericFormPage();
    CString    GetCaption() const { return m_strCaption; };
    
    virtual BOOL OnSetActive();     // called when this page gets the focus
// Dialog Data
    //{{AFX_DATA(ZIGenericFormPage)
    enum { IDD = IDD_GENERICFORM };
    CListBox    m_ctlListOfPlan;
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(ZIGenericFormPage)
    afx_msg void OnSelChangeList();
    afx_msg void OnDblclkListOfForms();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    ZDTemplateManager*    m_pTemplateManager;
};

//#undef  AFX_DATA
//#define AFX_DATA

#endif // __GFORMP_H
