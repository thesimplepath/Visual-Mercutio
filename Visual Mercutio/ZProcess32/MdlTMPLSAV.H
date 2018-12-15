// MdlTmplSav.h : header file

#include "Resource.h"

#include "zWinUtil32\ZSearchEdit.h"
#include "zBaseLib\ZIDialog.h"

#include "zBaseLib\FldStamp.h"

// JMR-MODIF - Le 9 décembre 2007 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

/////////////////////////////////////////////////////////////////////////////
// ZIModelTemplateCopyDlg dialog

class ZIModelTemplateCopyDlg : public ZIDialog
{
// Construction
public:

    // Standard constructor
    ZIModelTemplateCopyDlg( CString            FileExtension,
                            const CString    Directory,
                            ZDFolderStamp*    pFolderStamp    = NULL,
                            BOOL            AllowReplace    = FALSE,
                            CWnd*            pParent            = NULL );

public:

    CString GetDirectory() const
    {
        return m_Directory;
    }

    CString GetDescription()
    {
        return m_sDescription;
    }

    CString GetFilename()
    {
        return m_sFilename;
    }

    CString GetTitle()
    {
        return m_sTitle;
    }

    bool FileChooseExists() const
    {
        return m_FileExist;
    }

// Dialog Data
private:

    //{{AFX_DATA(ZIModelTemplateCopyDlg)
    enum { IDD = IDD_MODELTEMPLATESAVE };
    ZCSearchEdit m_ModelDirectory;
    CString m_sDescription;
    CString m_sFilename;
    CString m_sTitle;
    //}}AFX_DATA

// Implementation
protected:

    // DDX/DDV support
    virtual void DoDataExchange( CDataExchange* pDX );

    // Generated message map functions
    //{{AFX_MSG(ZIModelTemplateCopyDlg)
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnChangeTitle();
    afx_msg void OnDontSave();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:

    ZDFolderStamp*    m_pFolderStamp;

    CString            m_FileExtension;
    CString            m_Directory;

    BOOL            m_AllowReplace;

    bool            m_FileExist;
};
