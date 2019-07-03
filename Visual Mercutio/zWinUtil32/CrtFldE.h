#if !defined(AFX_CRTFLDE_H__B6801F54_4E39_11D3_9604_0000B45D7C6F__INCLUDED_)
#define AFX_CRTFLDE_H__B6801F54_4E39_11D3_9604_0000B45D7C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CrtFldE.h : header file
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
// ZICreateFolderWizardExist dialog

class ZICreateFolderWizardExist : public ZIWizardDialog
{
// Construction
public:
    enum    FldExistInitialChoice { FolderNameChoice, DirectoryChoice, FilenameChoice, KeepChoice };

    ZICreateFolderWizardExist(CString FolderName, CString FileDirectory, CString InitialFilename, FldExistInitialChoice InitialChoice = FolderNameChoice, CWnd* pParent = NULL);   // standard constructor

    // Get information, if successful
    CString    GetFilename() const { return m_CompleteFilename; };
    CString    GetFileDirectory() const { return m_FileDirectory; };
    CString    GetFolderName() const { return m_Folder; };
    BOOL    IsFolderNameChoosed() const { return m_Choice == 0; };
    BOOL    IsDirectoryChoosed() const { return m_Choice == 1; };
    BOOL    IsFilenameChoosed() const { return m_Choice == 2; };
    BOOL    IsReWriteChoosed() const { return m_Choice == 3; };


private:
// Dialog Data
    //{{AFX_DATA(ZICreateFolderWizardExist)
    enum { IDD = IDD_WZCREATEFOLDERFILE_EXIST };
    ZCSearchEdit    m_Filename;
    ZCSearchEdit    m_Directory;
    int        m_Choice;
    CString    m_Folder;
    //}}AFX_DATA
    CString m_FileDirectory;
    CString m_CompleteFilename;
    CString m_InitialFilename;

    FldExistInitialChoice m_InitialChoice;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(ZICreateFolderWizardExist)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

private:
    void CheckControlStates();

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(ZICreateFolderWizardExist)
    virtual void OnOK();
    afx_msg void OnFolderChoice();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRTFLDE_H__B6801F54_4E39_11D3_9604_0000B45D7C6F__INCLUDED_)
