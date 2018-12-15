/////////////////////////////////////////////////////////////////////////////
//@doc ZIEvalWarning
//@module Eval.cpp | Implementation of the <c ZIEvalWarning> class.
// 
// zADS<tm>
// <nl>Copyright <cp> 1993-2000 Advanced Dedicated Software, Inc. 
// All rights reserved.
// Contact:
// mailto:devzone@adsoft-form.com
// http://www.adsoft-form.com
// 
// 
// <nl>Created: 03/2001
// 
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Eval.h"

#include "zRes32\zRes.h"

/////////////////////////////////////////////////////////////////////////////
// ZIEvalWarning dialog


ZIEvalWarning::ZIEvalWarning(CWnd* pParent /*=NULL*/)
    : CDialog(IDD_EVALUATIONWARNING, pParent)
{
    //{{AFX_DATA_INIT(ZIEvalWarning)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

void ZIEvalWarning::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIEvalWarning)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZIEvalWarning, CDialog)
    //{{AFX_MSG_MAP(ZIEvalWarning)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZIEvalWarning message handlers

BOOL ZIEvalWarning::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    // Put the window in the right of the screen    
    CRect    rect;
    GetClientRect( &rect );
    CRect    ClientRect;
    UINT    uiX, uiY;
    uiX = GetSystemMetrics( SM_CXFULLSCREEN );
    uiY = GetSystemMetrics( SM_CYFULLSCREEN );
    SetWindowPos( NULL, (uiX - rect.right) / 2, (uiY - rect.bottom) / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE );
    
    
    return TRUE;  // return TRUE  unless you set the focus to a control
}
