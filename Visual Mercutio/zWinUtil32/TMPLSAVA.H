// tmplsava.h : header file
//

#ifndef TmplSavA_h
#define TmplSavA_h 1

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\TmplMng.h"
#include "zBaseLib\ZIDialog.h"
#include "TmplTree.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"

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
// ZITemplateCopyDlg dialog

class AFX_EXT_CLASS ZITemplateCopyDlg : public ZIDialog
{
// Construction
public:
    ZITemplateCopyDlg(ZDTemplateManager* pTemplateManager, CString FileExtension, ZDFolderStamp* pFolderStamp = NULL, BOOL AllowReplace = FALSE, CWnd* pParent = NULL);    // standard constructor
    CString        GetDescription(){ return m_sDescription; };
    CString        GetFilename(){ return m_sFilename; };
    CString        GetTitle(){ return m_sTitle; };
    bool        FileChooseExists() const { return m_FileExist; };

private:
// Dialog Data
    //{{AFX_DATA(ZITemplateCopyDlg)
    enum { IDD = IDD_TEMPLATESAVE };
    CString    m_sDescription;
    CString    m_sFilename;
    CString    m_sTitle;
    //}}AFX_DATA
#ifdef _WIN32
    ZCTemplateTreeCtrl    m_TemplateDirList;
#endif
#ifndef _WIN32
    CListBox            m_TemplateDirList;
#endif

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(ZITemplateCopyDlg)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnChangeTitle();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
    
private:
    ZDTemplateManager*     m_pTemplateManager;
    ZDFolderStamp*        m_pFolderStamp;
    CString                m_FileExtension;
    BOOL                m_AllowReplace;
    bool                m_FileExist;
};



#endif // TmplSavA_h