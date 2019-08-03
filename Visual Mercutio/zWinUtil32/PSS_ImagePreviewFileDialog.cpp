/****************************************************************************
 * ==> PSS_ImagePreviewFileDialog ------------------------------------------*
 ****************************************************************************
 * Description : Provides an image preview file dialog box                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ImagePreviewFileDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_PreviewBitmapForm
//---------------------------------------------------------------------------
void PSS_PreviewBitmapForm::SetPreviewFile(const CString& fileName)
{
    if (!m_Dib.OpenDIB(fileName)) 
        m_Dib.DestroyDIB();
}
//---------------------------------------------------------------------------
void PSS_PreviewBitmapForm::DrawPreview(CDC* pDC, int X, int Y, int width, int height)
{
    if (!m_Dib.IsValid()) 
        return;

    const CRect cr = Calc(m_Dib.Width(), m_Dib.Height(), width, height);

    m_Dib.StretchBlt(pDC->m_hDC, cr.left + X, cr.top + Y, cr.Width(), cr.Height(), 0, 0, m_Dib.Width(), m_Dib.Height());
}
//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_ImagePreviewFileDialog, PSS_FilePreviewDialog)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ImagePreviewFileDialog, PSS_FilePreviewDialog)
    //{{AFX_MSG_MAP(PSS_ImagePreviewFileDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ImagePreviewFileDialog
//---------------------------------------------------------------------------
PSS_ImagePreviewFileDialog::PSS_ImagePreviewFileDialog(BOOL           openFileDialog, 
                                                       const CString& title,
                                                       const CString& initialDir,
                                                       CWnd*          pParentWnd) :
    PSS_FilePreviewDialog(&m_Preview,
                          openFileDialog,
                          title,
                          initialDir,
                          "bmp",
                          "*.bmp",
                          OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR |OFN_PATHMUSTEXIST,
                          "Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||",
                          pParentWnd)
{}
//---------------------------------------------------------------------------
