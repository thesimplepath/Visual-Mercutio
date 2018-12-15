// ZProcPreviewFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ZProcPreviewFileDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



void ZPreviewProcess::SetPreviewFile(const CString& csFileName)
{
}

void ZPreviewProcess::DrawPreview(CDC *pDC,int X,int Y,int width,int height)
{
}


/////////////////////////////////////////////////////////////////////////////
// ZIProcessPreviewFileDialog

IMPLEMENT_DYNAMIC(ZIProcessPreviewFileDialog, ZIPreviewFileDialog)


ZIProcessPreviewFileDialog::ZIProcessPreviewFileDialog(BOOL bOpenFileDialog, CString Title, CString InitialDir, CWnd* pParentWnd) 
: ZIPreviewFileDialog(&m_Preview, bOpenFileDialog, 
                      Title, InitialDir,
                      "wlf","*.wlf",
                      OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR |OFN_PATHMUSTEXIST,
                      "Fichier Processus (*.wlf)|*.wlf|"
                      "Tous fichiers (*.*)|*.*||", 
                      pParentWnd)
{
}


BEGIN_MESSAGE_MAP(ZIProcessPreviewFileDialog, ZIPreviewFileDialog)
    //{{AFX_MSG_MAP(ZIProcessPreviewFileDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()



