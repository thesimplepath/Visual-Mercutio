/****************************************************************************
 * ==> PSS_CodeInputDialog -------------------------------------------------*
 ****************************************************************************
 * Description : Provides an code input dialog box                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_CodeInputDialog.h"

// processsoft
#include "zBaseLib\File.h"
#include "ZBKeyFile.h"

// resources
#include "zRes32\zRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_CodeInputDialog, CDialog)
    //{{AFX_MSG_MAP(PSS_CodeInputDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_CodeInputDialog
//---------------------------------------------------------------------------
PSS_CodeInputDialog::PSS_CodeInputDialog(CWnd* pParent) :
    CDialog(IDD_CODE2INSTALL, pParent),
    m_Code(""),
    m_Counter(0)
{}
//---------------------------------------------------------------------------
void PSS_CodeInputDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_CodeInputDialog)
    DDX_Text(pDX, IDC_CODEINSTALL, m_Code);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_CodeInputDialog::OnInitDialog()
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
void PSS_CodeInputDialog::OnOK()
{
    UpdateData(TRUE);

    ++m_Counter;

    CString text;
    CString caption;
    CString wndDir;

    // check if the key file exists
    GetWindowsDirectory(wndDir.GetBuffer(MAX_PATH), MAX_PATH);
    wndDir.ReleaseBuffer();

    wndDir += _T("\\winkeys.key");

    if (!ZFile::Exist(wndDir))
    {
        text.LoadString(IDS_PASSWORDFAILED2);
        caption.LoadString(IDS_PASSWORDCAPTION);
        MessageBox(text, caption, MB_ICONSTOP);
        CDialog::OnCancel();
        return;
    }

    ZBKeyFile file(wndDir);

    // check the password
    if (!file.IsKeyValid(m_Code))
    {
        // out of retries?
        if (m_Counter > 3)
        {
            text.LoadString(IDS_PASSWORDFAILED);
            caption.LoadString(IDS_PASSWORDCAPTION);
            MessageBox(text, caption, MB_ICONSTOP);

            CDialog::OnCancel();
            return;
        }

        text.LoadString(IDS_PASSWORDRETRY);
        caption.LoadString(IDS_PASSWORDRETRYCAPTION);
        MessageBox(text, caption, MB_ICONEXCLAMATION);

        // clear the old code
        m_Code = "";
        UpdateData(FALSE);
        return;
    }

    CDialog::OnOK();
}
//---------------------------------------------------------------------------
