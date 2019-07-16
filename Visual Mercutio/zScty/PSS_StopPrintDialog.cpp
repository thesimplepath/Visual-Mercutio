/****************************************************************************
 * ==> PSS_StopPrintDialog -------------------------------------------------*
 ****************************************************************************
 * Description : Provides a stop print dialog box                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_StopPrintDialog.h"

// processsoft
#include "PSS_CodeInputDialog.h"

// resources
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_StopPrintDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_StopPrintDialog)
    ON_BN_CLICKED(IDDELOCK, OnDelock)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_StopPrintDialog
//---------------------------------------------------------------------------
PSS_StopPrintDialog::PSS_StopPrintDialog(CWnd* pParent) :
    CDialog(IDD_CANTCONTINUE, pParent)
{}
//---------------------------------------------------------------------------
void PSS_StopPrintDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}
//---------------------------------------------------------------------------
BOOL PSS_StopPrintDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    CRect rect;
    GetClientRect(&rect);

    // put the window on the screen right
    const UINT screenX = ::GetSystemMetrics(SM_CXFULLSCREEN);
    const UINT screenY = ::GetSystemMetrics(SM_CYFULLSCREEN);
    SetWindowPos(NULL, (screenX - rect.right) / 2, (screenY - rect.bottom) / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

    // return TRUE unless the focus is set to a control
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_StopPrintDialog::OnDelock()
{
    PSS_CodeInputDialog dialog;

    // start the code entry
    if (dialog.DoModal() == IDOK)
    {
        m_Code = dialog.GetCode();
        EndDialog(IDCHANGE);
        return;
    }

    EndDialog(IDOK);
}
//---------------------------------------------------------------------------
