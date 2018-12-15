// ZPreviewFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ZPreviewFileDialog.h"
#include <dlgs.h>

#define IDC_STATIC_RECT            6000
#define IDC_CHECK_PREVIEW        6001

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// ZIPreviewFileDialog

IMPLEMENT_DYNAMIC(ZIPreviewFileDialog, CFileDialog)


ZIPreviewFileDialog::ZIPreviewFileDialog(ZAbstractPreview *pPreview, BOOL bOpenFileDialog, CString Title, CString InitialDir, 
        LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
        DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
        CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
    m_Title = Title;
    m_InitialDir = InitialDir;

    m_ofn.Flags |= OFN_ENABLETEMPLATE;
    m_ofn.hInstance = AfxGetInstanceHandle();
    m_ofn.lpTemplateName = "PREVIEWFILEOPEN_TEMPLATE";
    if (!m_InitialDir.IsEmpty())
        m_ofn.lpstrInitialDir = (const char*)m_InitialDir;
    if (!m_Title.IsEmpty())
        m_ofn.lpstrTitle = (const char*)m_Title;

    m_pPreview = pPreview;
    m_bChanged = FALSE;
    m_bPreview = TRUE;
    m_RegionHasBeenCreated = FALSE;
}


BEGIN_MESSAGE_MAP(ZIPreviewFileDialog, CFileDialog)
    //{{AFX_MSG_MAP(ZIPreviewFileDialog)
    ON_BN_CLICKED(IDC_CHECK_PREVIEW,OnClickedPreview)
    ON_WM_PAINT()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL ZIPreviewFileDialog::OnInitDialog() 
{
    CFileDialog::OnInitDialog();
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL ZIPreviewFileDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    ASSERT(pResult != NULL);

    // allow message map to override

    OFNOTIFY* pNotify = (OFNOTIFY*)lParam;
    switch(pNotify->hdr.code)
    {
    case CDN_SELCHANGE:
        OnFileNameChange();
        return TRUE;
    case CDN_FOLDERCHANGE:
        OnFolderChange();
        return TRUE;
    case CDN_INITDONE:
        OnInitDone();
        return TRUE;
    }
    return CFileDialog::OnNotify(wParam, lParam, pResult);
}

void ZIPreviewFileDialog::OnInitDone()
{
    CWnd*    pWnd = GetDlgItem(IDC_STATIC_RECT);
    if(pWnd) 
    {
        CRect cr ;
        pWnd->GetWindowRect(&cr);
        ScreenToClient(&cr);
        cr.top = cr.bottom+15;
        cr.bottom = cr.top+20;
        cr.left += 40;
        m_CheckBox.Create("&Preview",WS_CHILD|WS_VISIBLE|WS_TABSTOP|BS_AUTOCHECKBOX,cr,this,IDC_CHECK_PREVIEW);
        m_CheckBox.SetFont(GetFont());
        m_CheckBox.SetCheck(m_bPreview);

        pWnd->GetWindowRect(&cr);
        ScreenToClient(&cr);
        cr.top = cr.bottom + 45;
        cr.bottom = cr.top + 102;
        cr.left += 15;
        cr.right = cr.left + 102;
        m_PreviewRect = cr;

        m_Region.CreateRectRgn(m_PreviewRect.left+1,m_PreviewRect.top+1,m_PreviewRect.right-1,m_PreviewRect.bottom-1);
        m_RegionHasBeenCreated = TRUE;
    }
}

void ZIPreviewFileDialog::OnFileNameChange()
{
    if(!m_bChanged && m_bPreview)
    {
        m_pPreview->SetPreviewFile(GetPathName());
        InvalidateRect(&m_PreviewRect);
    }
    m_bChanged = FALSE;
}


void ZIPreviewFileDialog::OnFolderChange()
{
    m_bChanged = TRUE;
    m_pPreview->SetPreviewFile(CString(""));
    InvalidateRect(&m_PreviewRect);
}

void ZIPreviewFileDialog::OnClickedPreview()
{
    m_bPreview = m_CheckBox.GetCheck() == 1 ? TRUE : FALSE;
    InvalidateRect(&m_PreviewRect);
}

void ZIPreviewFileDialog::OnPaint() 
{
    CPaintDC dc(this); // device context for painting

    dc.Draw3dRect(&m_PreviewRect,::GetSysColor(COLOR_BTNSHADOW),::GetSysColor(COLOR_BTNHILIGHT));
    if (m_bPreview)
    {
        dc.SelectClipRgn(&m_Region);
        m_pPreview->DrawPreview(&dc,m_PreviewRect.left+1,m_PreviewRect.top+1,m_PreviewRect.Width()-2,m_PreviewRect.Height()-2);
        dc.SelectClipRgn(NULL);
    }
}


CRect ZAbstractPreview::Calc(int bmpWid,int bmpDep,int wndWid,int wndDep)
{
    CRect cr;
    int d,w,x,y;
    if (bmpDep > bmpWid)
    {
        d = __min(bmpDep,wndDep);
        w = (bmpWid*d)/bmpDep;
    }
    else
    {
        w = __min(bmpWid,wndWid);
        d = (bmpDep*w)/bmpWid;
    }
    x = (wndWid- w)/2;
    y = (wndDep - d)/2;
    return CRect(x,y,x+w,y+d);
}


void ZIPreviewFileDialog::OnSize(UINT nType, int cx, int cy) 
{
    CFileDialog::OnSize(nType, cx, cy);
    
    CWnd*    pWnd = GetDlgItem(IDC_STATIC_RECT);
    if (pWnd && m_RegionHasBeenCreated) 
    {
        CRect cr ;

        pWnd->GetWindowRect(&cr);
        ScreenToClient(&cr);
        cr.top = cr.bottom + 45;
        cr.bottom = cr.top + 102;
        cr.left += 15;
        cr.right = cr.left + 102;
        m_PreviewRect = cr;

        m_Region.SetRectRgn(m_PreviewRect.left+1,m_PreviewRect.top+1,m_PreviewRect.right-1,m_PreviewRect.bottom-1);
        cr.InflateRect(20,5);
        InvalidateRect( &cr );
    }
    
}

