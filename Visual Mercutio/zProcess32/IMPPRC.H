/****************************************************************************
 * ==> PSS_ImportProcessDlg ------------------------------------------------*
 ****************************************************************************
 * Description : Provides an import process dialog                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

// processsoft
#include "zBaseLib\PSS_Dialog.h"

// resources
#include "resource.h"

class ZIImportProcess : public PSS_Dialog
{
// Construction
public:
    ZIImportProcess(CString File = "", BOOL Import = TRUE, CWnd* pParent = NULL);    // standard constructor
    CString    GetFile() { return m_File; };
        
private:
// Dialog Data
    //{{AFX_DATA(ZIImportProcess)
    enum { IDD = IDD_IMPORTPROCESS_DEFINITION };
    CString    m_File;
    //}}AFX_DATA
    BOOL    m_Import;
    CString    m_InitialFile;

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    // Generated message map functions
    //{{AFX_MSG(ZIImportProcess)
    afx_msg void OnSelect();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
