// foldinfo.h : header file
//

#ifndef FoldInfo_h
#define FoldInfo_h 1

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zBaseLib\ZIDialog.h"
#include "zBaseLib\FldStamp.h"
#include "FldInfoC.h"

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
// ZIFolderInformation dialog

class AFX_EXT_CLASS ZIFolderInformation : public ZIDialog
{
// Construction
public:
    ZIFolderInformation(ZDFolderStamp* pFolderStamp = NULL, BOOL ReadOnly = FALSE, CWnd* pParent = NULL);    // standard constructor
    CString    GetFolderDescription() { return m_FolderDescription; };
    CString    GetFolderName() { return m_FolderName; };
    

// Dialog Data
    //{{AFX_DATA(ZIFolderInformation)
    enum { IDD = IDD_FOLDER_INFORMATION };
    CString    m_FolderDescription;
    CString    m_FolderName;
    //}}AFX_DATA
#ifdef _WIN32
    ZCFolderInformation    m_ListInformation;
#endif

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(ZIFolderInformation)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
    
private:
    ZDFolderStamp*     m_pFolderStamp;
    BOOL            m_ReadOnly;
};


#endif    // FoldInfo_h
