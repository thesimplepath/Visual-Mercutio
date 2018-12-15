#ifndef __ZPREVIEWFILEDIALOG__
#define __ZPREVIEWFILEDIALOG__
// ZPreviewFileDialog.h : header file
//


//change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT


#include "zBaseLib\ZDib.h"


class ZAbstractPreview
{
public:
    virtual void SetPreviewFile(const CString& csFileName)=0;
    virtual void DrawPreview(CDC *pDC,int x,int y,int width,int height)=0;
    virtual CRect Calc(int bmpWid,int bmpDep,int wndWid,int wndDep);
};



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

/////////////////////////////////////////////////////////////////////////////
// ZIPreviewFileDialog dialog

class AFX_EXT_CLASS ZIPreviewFileDialog : public CFileDialog
{
    DECLARE_DYNAMIC(ZIPreviewFileDialog)

public:
    ZIPreviewFileDialog(ZAbstractPreview *pPreview,BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
        CString Title = "", CString InitialDir = "", 
        LPCTSTR lpszDefExt = NULL,
        LPCTSTR lpszFileName = NULL,
        DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        LPCTSTR lpszFilter = NULL,
        CWnd* pParentWnd = NULL);

protected:
    //{{AFX_MSG(ZIPreviewFileDialog)
    virtual BOOL OnInitDialog();
    afx_msg void OnClickedPreview();
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    virtual void OnFileNameChange();
    virtual void OnFolderChange();
    virtual void OnInitDone();

    CButton m_CheckBox;
    CRect m_PreviewRect;
    BOOL m_bPreview;
    ZAbstractPreview *m_pPreview;
    CRgn m_Region;
    CString m_csFileName;
    BOOL m_bChanged;
    BOOL m_RegionHasBeenCreated;
    CString m_Title;
    CString m_InitialDir;
};

#endif    // __ZPREVIEWFILEDIALOG__
