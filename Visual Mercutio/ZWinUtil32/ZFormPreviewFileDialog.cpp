// ZFormPreviewFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ZFormPreviewFileDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



void ZPreviewForm::SetPreviewFile(const CString& csFileName)
{
}

void ZPreviewForm::DrawPreview(CDC *pDC,int X,int Y,int width,int height)
{
}


/////////////////////////////////////////////////////////////////////////////
// ZIFormPreviewFileDialog

IMPLEMENT_DYNAMIC(ZIFormPreviewFileDialog, ZIPreviewFileDialog)


ZIFormPreviewFileDialog::ZIFormPreviewFileDialog(BOOL bOpenFileDialog, CString Title, CString InitialDir, CWnd* pParentWnd) 
: ZIPreviewFileDialog(&m_Preview, bOpenFileDialog, 
					  Title, InitialDir,
					  "flf","*.flf",
					  OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR |OFN_PATHMUSTEXIST,
					  "Fichier Formulaire (*.flf)|*.flf|"
					  "Tous fichiers (*.*)|*.*||", 
					  pParentWnd)
{
}


BEGIN_MESSAGE_MAP(ZIFormPreviewFileDialog, ZIPreviewFileDialog)
	//{{AFX_MSG_MAP(ZIFormPreviewFileDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



