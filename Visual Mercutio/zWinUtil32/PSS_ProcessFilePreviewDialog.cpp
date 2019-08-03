/****************************************************************************
 * ==> PSS_ProcessFilePreviewDialog ----------------------------------------*
 ****************************************************************************
 * Description : Provides a process preview file dialog box                 *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessFilePreviewDialog.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_ProcessPreviewForm
//---------------------------------------------------------------------------
void PSS_ProcessPreviewForm::SetPreviewFile(const CString& fileName)
{}
//---------------------------------------------------------------------------
void PSS_ProcessPreviewForm::DrawPreview(CDC* pDC, int x, int y, int width, int height)
{}
//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_ProcessFilePreviewDialog, PSS_FilePreviewDialog)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_ProcessFilePreviewDialog, PSS_FilePreviewDialog)
    //{{AFX_MSG_MAP(PSS_ProcessFilePreviewDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_ProcessFilePreviewDialog
//---------------------------------------------------------------------------
PSS_ProcessFilePreviewDialog::PSS_ProcessFilePreviewDialog(BOOL           openFileDialog,
                                                           const CString& title,
                                                           const CString& initialDir,
                                                           CWnd*          pParentWnd) :
    PSS_FilePreviewDialog(&m_Preview,
                          openFileDialog,
                          title,
                          initialDir,
                          "wlf","*.wlf",
                          OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR |OFN_PATHMUSTEXIST,
                          "Fichier Processus (*.wlf)|*.wlf|Tous fichiers (*.*)|*.*||",
                          pParentWnd)
{}
//---------------------------------------------------------------------------
