/****************************************************************************
 * ==> PSS_FilePreviewDialog -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a file preview dialog box                         *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FilePreviewDialog.h"

// Windows
#include <dlgs.h>

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Global defines
//---------------------------------------------------------------------------
#define IDC_STATIC_RECT   6000
#define IDC_CHECK_PREVIEW 6001
//---------------------------------------------------------------------------
// PSS_AbstractPreviewForm
//---------------------------------------------------------------------------
CRect PSS_AbstractPreviewForm::Calc(int bmpWidth, int bmpHeight, int wndWidth, int wndHeight)
{
    CRect cr;
    int d, w;

    if (bmpHeight > bmpWidth)
    {
        d = __min(bmpHeight, wndHeight);
        w = (bmpWidth * d) / bmpHeight;
    }
    else
    {
        w = __min(bmpWidth, wndWidth);
        d = (bmpHeight * w) / bmpWidth;
    }

    const int x = (wndWidth  - w) / 2;
    const int y = (wndHeight - d) / 2;

    return CRect(x, y, x + w, y + d);
}
//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_FilePreviewDialog, CFileDialog)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FilePreviewDialog, CFileDialog)
    //{{AFX_MSG_MAP(PSS_FilePreviewDialog)
    ON_BN_CLICKED(IDC_CHECK_PREVIEW, OnClickedPreview)
    ON_WM_PAINT()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FilePreviewDialog
//---------------------------------------------------------------------------
PSS_FilePreviewDialog::PSS_FilePreviewDialog(PSS_AbstractPreviewForm* pPreview,
                                             BOOL                     openFileDialog,
                                             const CString&           title,
                                             const CString&           initialDir,
                                             LPCTSTR                  pDefExt,
                                             LPCTSTR                  pFileName,
                                             DWORD                    flags,
                                             LPCTSTR                  pFilters,
                                             CWnd*                    pParentWnd) :
    CFileDialog(openFileDialog, pDefExt, pFileName, flags, pFilters, pParentWnd),
    m_pPreview(pPreview),
    m_Title(title),
    m_InitialDir(initialDir),
    m_Preview(TRUE),
    m_Changed(FALSE),
    m_RegionHasBeenCreated(FALSE)
{
    m_ofn.Flags          |= OFN_ENABLETEMPLATE;
    m_ofn.hInstance       = AfxGetInstanceHandle();
    m_ofn.lpTemplateName  = "PREVIEWFILEOPEN_TEMPLATE";

    if (!m_InitialDir.IsEmpty())
        m_ofn.lpstrInitialDir = (const char*)m_InitialDir;

    if (!m_Title.IsEmpty())
        m_ofn.lpstrTitle = (const char*)m_Title;
}
//---------------------------------------------------------------------------
BOOL PSS_FilePreviewDialog::OnInitDialog()
{
    CFileDialog::OnInitDialog();

    // return TRUE unless the focus is set to a control. NOTE OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_FilePreviewDialog::OnInitDone()
{
    CWnd* pWnd = GetDlgItem(IDC_STATIC_RECT);

    if (pWnd)
    {
        CRect cr;
        pWnd->GetWindowRect(&cr);
        ScreenToClient(&cr);
        cr.top     = cr.bottom + 15;
        cr.bottom  = cr.top    + 20;
        cr.left   += 40;
        m_CheckBox.Create("&Preview", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTOCHECKBOX, cr, this, IDC_CHECK_PREVIEW);
        m_CheckBox.SetFont(GetFont());
        m_CheckBox.SetCheck(m_Preview);

        pWnd->GetWindowRect(&cr);
        ScreenToClient(&cr);
        cr.top         = cr.bottom + 45;
        cr.bottom      = cr.top    + 102;
        cr.left       += 15;
        cr.right       = cr.left   + 102;
        m_PreviewRect  = cr;

        m_Region.CreateRectRgn(m_PreviewRect.left   + 1,
                               m_PreviewRect.top    + 1,
                               m_PreviewRect.right  - 1,
                               m_PreviewRect.bottom - 1);

        m_RegionHasBeenCreated = TRUE;
    }
}
//---------------------------------------------------------------------------
void PSS_FilePreviewDialog::OnClickedPreview()
{
    m_Preview = m_CheckBox.GetCheck() == 1 ? TRUE : FALSE;
    InvalidateRect(&m_PreviewRect);
}
//---------------------------------------------------------------------------
void PSS_FilePreviewDialog::OnPaint()
{
    // device context for painting
    CPaintDC dc(this);

    dc.Draw3dRect(&m_PreviewRect, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHILIGHT));

    if (m_Preview)
    {
        dc.SelectClipRgn(&m_Region);
        m_pPreview->DrawPreview(&dc,
                                m_PreviewRect.left     + 1,
                                m_PreviewRect.top      + 1,
                                m_PreviewRect.Width()  - 2,
                                m_PreviewRect.Height() - 2);
        dc.SelectClipRgn(NULL);
    }
}
//---------------------------------------------------------------------------
void PSS_FilePreviewDialog::OnSize(UINT nType, int cx, int cy)
{
    CFileDialog::OnSize(nType, cx, cy);

    CWnd* pWnd = GetDlgItem(IDC_STATIC_RECT);

    if (pWnd && m_RegionHasBeenCreated)
    {
        CRect cr;
        pWnd->GetWindowRect(&cr);
        ScreenToClient(&cr);
        cr.top         = cr.bottom + 45;
        cr.bottom      = cr.top    + 102;
        cr.left       += 15;
        cr.right       = cr.left   + 102;
        m_PreviewRect  = cr;

        m_Region.SetRectRgn(m_PreviewRect.left   + 1,
                            m_PreviewRect.top    + 1,
                            m_PreviewRect.right  - 1,
                            m_PreviewRect.bottom - 1);

        cr.InflateRect(20, 5);
        InvalidateRect(&cr);
    }
}
//---------------------------------------------------------------------------
void PSS_FilePreviewDialog::OnFileNameChange()
{
    if (!m_Changed && m_Preview)
    {
        m_pPreview->SetPreviewFile(GetPathName());
        InvalidateRect(&m_PreviewRect);
    }

    m_Changed = FALSE;
}
//---------------------------------------------------------------------------
void PSS_FilePreviewDialog::OnFolderChange()
{
    m_Changed = TRUE;
    m_pPreview->SetPreviewFile(CString(""));
    InvalidateRect(&m_PreviewRect);
}
//---------------------------------------------------------------------------
BOOL PSS_FilePreviewDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    ASSERT(pResult);

    // allow message map to override
    OFNOTIFY* pNotify = (OFNOTIFY*)lParam;

    switch (pNotify->hdr.code)
    {
        case CDN_SELCHANGE:    OnFileNameChange(); return TRUE;
        case CDN_FOLDERCHANGE: OnFolderChange();   return TRUE;
        case CDN_INITDONE:     OnInitDone();       return TRUE;
    }

    return CFileDialog::OnNotify(wParam, lParam, pResult);
}
//---------------------------------------------------------------------------
