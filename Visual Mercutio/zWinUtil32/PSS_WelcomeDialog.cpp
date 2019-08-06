/****************************************************************************
 * ==> PSS_WelcomeDialog ---------------------------------------------------*
 ****************************************************************************
 * Description : Provides a welcome dialog box                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_WelcomeDialog.h"

// processsoft
#include "zBaseLib\Draw.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_WelcomeDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_WelcomeDialog)
    ON_BN_CLICKED(ID_WELCOME_LASTFILE, OnWelcomeLastFile)
    ON_WM_PAINT()
    ON_WM_CTLCOLOR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_WelcomeDialog
//---------------------------------------------------------------------------
PSS_WelcomeDialog::PSS_WelcomeDialog(UINT                   id,
                                     UINT                   bitmapID,
                                     PSS_ApplicationOption* pAppOptions,
                                     BOOL                   enableMoveToGeneral,
                                     CWnd*                  pParent) :
    ZIDialog(id, TRUE, pParent),
    m_BitmapID(bitmapID),
    m_pAppOptions(pAppOptions),
    m_EnableMoveToGeneral(enableMoveToGeneral)
{
    m_DoNotStart = !m_pAppOptions->GetShowWelcomeScreen();
}
//---------------------------------------------------------------------------
void PSS_WelcomeDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange( pDX );

    //{{AFX_DATA_MAP(PSS_WelcomeDialog)
    DDX_Control(pDX, ID_WELCOME_LASTFILE, m_LastFile);
    DDX_Control(pDX, IDCANCEL,            m_Cancel);
    DDX_Control(pDX, IDC_HYPERLINK_HTTP,  m_HyperLink);
    DDX_Check  (pDX, IDC_DONOTSTART,      m_DoNotStart);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_WelcomeDialog::OnInitDialog()
{
    ZIDialog::OnInitDialog();

    m_HyperLink.SetURL(_T("http://www.processsoft.com"));

    // return TRUE unless the focus is set to a control
    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_WelcomeDialog::OnWelcomeLastFile()
{
    SaveState();
    EndDialog(ID_WELCOME_LASTFILE);
}
//---------------------------------------------------------------------------
void PSS_WelcomeDialog::OnPaint()
{
    // device context for painting
    CPaintDC dc(this);

    HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(m_BitmapID), RT_BITMAP);

    DisplayBitmapFile(MAKEINTRESOURCE(m_BitmapID), dc.m_hDC, hInst, 3, 3);
}
//---------------------------------------------------------------------------
HBRUSH PSS_WelcomeDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    return ZIDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}
//---------------------------------------------------------------------------
void PSS_WelcomeDialog::OnCancel()
{
    SaveState();
    CDialog::OnCancel();
}
//---------------------------------------------------------------------------
void PSS_WelcomeDialog::SaveState()
{
    UpdateData();

    // save the flag
    m_pAppOptions->SetShowWelcomeScreen(!m_DoNotStart);
}
//---------------------------------------------------------------------------
