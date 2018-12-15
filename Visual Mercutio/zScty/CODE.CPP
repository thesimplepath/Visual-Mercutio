// code.cpp : implementation file
//

#include "stdafx.h"
#include "code.h"

#include "zRes32\zRes.h"

#include "zBaseLib\File.h"
// ZBKeyFile
#include "ZBKeyFile.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZICode dialog


ZICode::ZICode(CWnd* pParent /*=NULL*/)
    :     CDialog(IDD_CODE2INSTALL, pParent),
        m_iCounter(0)
{
    //{{AFX_DATA_INIT(ZICode)
    m_sCode = "";
    //}}AFX_DATA_INIT
}

void ZICode::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZICode)
    DDX_Text(pDX, IDC_CODEINSTALL, m_sCode);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZICode, CDialog)
    //{{AFX_MSG_MAP(ZICode)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZICode message handlers

void ZICode::OnOK()
{
    UpdateData( TRUE );
    CString        sText;
    CString        sCaption;
    ++m_iCounter;
    // Check if the key file exists
    CString strWndDir;
    GetWindowsDirectory(strWndDir.GetBuffer(MAX_PATH), MAX_PATH);
    strWndDir.ReleaseBuffer();

    strWndDir += _T("\\winkeys.key");
    if (!ZFile::Exist( strWndDir ))
    {
        sText.LoadString( IDS_PASSWORDFAILED2 );
        sCaption.LoadString( IDS_PASSWORDCAPTION );
        MessageBox( sText, sCaption, MB_ICONSTOP );
        CDialog::OnCancel();
        return;
    }
    // Check the password
    ZBKeyFile File( strWndDir );
    if (!File.IsKeyValid( m_sCode ))
    {
        // When no retries left
        if (m_iCounter > 3)
        {
            sText.LoadString( IDS_PASSWORDFAILED );
            sCaption.LoadString( IDS_PASSWORDCAPTION );
            MessageBox( sText, sCaption, MB_ICONSTOP );
            CDialog::OnCancel();
            return;
        }
        sText.LoadString( IDS_PASSWORDRETRY );
        sCaption.LoadString( IDS_PASSWORDRETRYCAPTION );
        MessageBox( sText, sCaption, MB_ICONEXCLAMATION );
        // Clear the old code
        m_sCode = "";
        UpdateData( FALSE );
        return;
    }    
    CDialog::OnOK();
}

BOOL ZICode::OnInitDialog()
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
