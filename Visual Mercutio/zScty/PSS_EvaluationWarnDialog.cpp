/****************************************************************************
 * ==> PSS_EvaluationWarnDialog --------------------------------------------*
 ****************************************************************************
 * Description : Provides an evaluation warning dialog box                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_EvaluationWarnDialog.h"

// resources
#include "zRes32\zRes.h"

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_EvaluationWarnDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_EvaluationWarnDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
PSS_EvaluationWarnDialog::PSS_EvaluationWarnDialog(CWnd* pParent) :
    CDialog(IDD_EVALUATIONWARNING, pParent)
{}
//---------------------------------------------------------------------------
void PSS_EvaluationWarnDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}
//---------------------------------------------------------------------------
BOOL PSS_EvaluationWarnDialog::OnInitDialog()
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
