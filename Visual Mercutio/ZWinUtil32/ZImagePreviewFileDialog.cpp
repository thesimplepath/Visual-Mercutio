// ZImagePreviewFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ZImagePreviewFileDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



void ZPreviewDIB::SetPreviewFile(const CString& csFileName)
{
	if (!m_Dib.OpenDIB(csFileName)) 
		m_Dib.DestroyDIB();
}

void ZPreviewDIB::DrawPreview(CDC *pDC,int X,int Y,int width,int height)
{
	if (!m_Dib.IsValid()) 
		return;
	CRect cr;
	cr = Calc(m_Dib.Width(),m_Dib.Height(),width,height);
	m_Dib.StretchBlt(pDC->m_hDC,cr.left+X,cr.top+Y,cr.Width(),cr.Height(),0,0,m_Dib.Width(),m_Dib.Height());
}


/////////////////////////////////////////////////////////////////////////////
// ZIImagePreviewFileDialog

IMPLEMENT_DYNAMIC(ZIImagePreviewFileDialog, ZIPreviewFileDialog)


ZIImagePreviewFileDialog::ZIImagePreviewFileDialog(BOOL bOpenFileDialog, CString Title, CString InitialDir, CWnd* pParentWnd) 
: ZIPreviewFileDialog(&m_Preview, bOpenFileDialog, 
					  Title, InitialDir,
					  "bmp","*.bmp",
					  OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR |OFN_PATHMUSTEXIST,
					  "Bitmap Files (*.bmp)|*.bmp|"
					  "All Files (*.*)|*.*||", 
					  pParentWnd)
{
}


BEGIN_MESSAGE_MAP(ZIImagePreviewFileDialog, ZIPreviewFileDialog)
	//{{AFX_MSG_MAP(ZIImagePreviewFileDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



