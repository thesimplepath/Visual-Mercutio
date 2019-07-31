/****************************************************************************
 * ==> PSS_FormPreviewFileDialog -------------------------------------------*
 ****************************************************************************
 * Description : Provides a form preview file dialog box                    *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_FormPreviewFileDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_PreviewForm
//---------------------------------------------------------------------------
void PSS_PreviewForm::SetPreviewFile(const CString& fileName)
{}
//---------------------------------------------------------------------------
void PSS_PreviewForm::DrawPreview(CDC* pDC, int x, int y, int width, int height)
{}
//---------------------------------------------------------------------------
// Dynamic construction
//---------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(PSS_FormPreviewFileDialog, ZIPreviewFileDialog)
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FormPreviewFileDialog, ZIPreviewFileDialog)
    //{{AFX_MSG_MAP(PSS_FormPreviewFileDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FormPreviewFileDialog
//---------------------------------------------------------------------------
PSS_FormPreviewFileDialog::PSS_FormPreviewFileDialog(BOOL           openFileDialog,
                                                     const CString& title,
                                                     const CString& initialDir,
                                                     CWnd*          pParentWnd) :
    ZIPreviewFileDialog(&m_Preview,
                        openFileDialog,
                        title,
                        initialDir,
                        "flf",
                        "*.flf",
                        OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR |OFN_PATHMUSTEXIST,
                        "Fichier Formulaire (*.flf)|*.flf|Tous fichiers (*.*)|*.*||",
                        pParentWnd)
{}
//---------------------------------------------------------------------------
