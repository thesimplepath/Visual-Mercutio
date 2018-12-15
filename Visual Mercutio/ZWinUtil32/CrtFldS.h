#if !defined(AFX_CRTFLDS_H__B6801F53_4E39_11D3_9604_0000B45D7C6F__INCLUDED_)
#define AFX_CRTFLDS_H__B6801F53_4E39_11D3_9604_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CrtFldS.h : header file
//

/*
//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT
*/
#include "zBaseLib\ZWizard.h"
#include "ZSearchEdit.h"

#include "zWinUtil32\ZWinUtil32.h"

/*
#ifdef _ZWINUTIL32EXPORT
//put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

//#undef  AFX_DATA
//#define AFX_DATA AFX_EXT_CLASS
*/


/////////////////////////////////////////////////////////////////////////////
// ZICreateFolderWizardStart dialog

class ZICreateFolderWizardStart : public ZIWizardDialog
{
// Construction
public:
    ZICreateFolderWizardStart(BOOL UseFolderNameAsFilename = FALSE, CString FolderDirectory = "", CString FolderName = "", CString FolderDescription = "", CString InitialFilename = "", CString FileExtension = "", CWnd* pParent = NULL);   // standard constructor

    // Get information, if successful
    CString    GetFolderName()  const { return m_FolderName; };
    CString    GetFolderDescription() const { return m_FolderComment; };
    CString    GetFilename()  const { return m_Filename; };


private:
// Dialog Data
    //{{AFX_DATA(ZICreateFolderWizardStart)
    enum { IDD = IDD_WZCREATEFOLDERFILE_ST };
    ZCSearchEdit    m_CompleteFilename;
    CString    m_FolderComment;
    CString    m_FolderName;
    //}}AFX_DATA
    BOOL    m_UseFolderNameAsFilename;
    CString    m_FolderDirectory;
    CString    m_Filename;
    CString    m_InitialFilename;
    CString m_FileExtension;
    char    m_szDir[_MAX_DIR];

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZICreateFolderWizardStart)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZICreateFolderWizardStart)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnChangeFolderName();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRTFLDS_H__B6801F53_4E39_11D3_9604_0000B45D7C6F__INCLUDED_)
