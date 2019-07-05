/****************************************************************************
 * ==> PSS_FilePreviewDlg --------------------------------------------------*
 ****************************************************************************
 * Description : File preview dialog                                        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_FilePreviewDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_FilePreviewDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_FilePreviewDlg)
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_FilePreviewDlg
//---------------------------------------------------------------------------
PSS_FilePreviewDlg::PSS_FilePreviewDlg(UINT resID, CWnd* pParent) :
    CDialog(PSS_FilePreviewDlg::IDD, pParent),
    m_pBrowser(NULL)
{
    CString strTemp;
    strTemp.Format(_T("%d"), resID);
    
    m_URL = PSS_WebBrowser::BuildResourceToURL(strTemp);
}
//---------------------------------------------------------------------------
PSS_FilePreviewDlg::PSS_FilePreviewDlg(LPCTSTR pURL, BOOL isRes, CWnd* pParent) :
    CDialog(PSS_FilePreviewDlg::IDD, pParent),
    m_pBrowser(NULL)
{
    if (isRes)
        m_URL = PSS_WebBrowser::BuildResourceToURL(pURL);
    else
        m_URL = pURL;
}
//---------------------------------------------------------------------------
PSS_FilePreviewDlg::~PSS_FilePreviewDlg()
{
    if (m_pBrowser)
        delete m_pBrowser;
}
//---------------------------------------------------------------------------
void PSS_FilePreviewDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}
//---------------------------------------------------------------------------
BOOL PSS_FilePreviewDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (GetDlgItem(IDC_WEBBROWSER_CONTROL))
    {
        CRect rect;
        GetDlgItem(IDC_WEBBROWSER_CONTROL)->GetClientRect(&rect);
        GetDlgItem(IDC_WEBBROWSER_CONTROL)->MapWindowPoints(this, &rect);

        // create the control
        m_pBrowser = new PSS_WebBrowser;
        ASSERT(m_pBrowser);

        if (!m_pBrowser->Create(NULL, NULL, WS_VISIBLE, rect, this, NULL))
        {
            TRACE(_T("failed to create browser\n"));
            delete m_pBrowser;
            m_pBrowser = NULL;

            return FALSE;
        }

        // initialize the first URL
        m_pBrowser->Navigate(m_URL);

        CString title;
        GetWindowText(title);
        title += _T(" ") + m_URL;
        SetWindowText(title);

        // resize all controls
        ResizeControl();
    }

    // activate the application window
    SetActiveWindow();
    SetForegroundWindow();

    // return TRUE unless a control is focused. NOTE exception for OCX property pages, which should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_FilePreviewDlg::OnSize(UINT type, int cx, int cy)
{
    CDialog::OnSize(type, cx, cy);

    ResizeControl();
}
//---------------------------------------------------------------------------
void PSS_FilePreviewDlg::ResizeControl()
{
    if (GetDlgItem(IDC_WEBBROWSER_CONTROL) && ::IsWindow(GetDlgItem(IDC_WEBBROWSER_CONTROL)->GetSafeHwnd()))
    {
        CRect rect;
        GetClientRect(&rect);

        if (GetDlgItem(IDOK))
        {
            CRect buttonRect;
            GetDlgItem(IDOK)->GetClientRect(&buttonRect);

            const int cx = buttonRect.Width();
            const int cy = buttonRect.Height();

            buttonRect.bottom = rect.bottom       - 5;
            buttonRect.right  = rect.right        - 5;
            buttonRect.top    = buttonRect.bottom - cy;
            buttonRect.left   = buttonRect.right  - cx;

            GetDlgItem(IDOK)->MoveWindow(&buttonRect);
        }

        if (m_pBrowser)
        {
            CRect browserRect;
            m_pBrowser->GetClientRect(&browserRect);

            const int cx = browserRect.Width();
            const int cy = browserRect.Height();

            browserRect.bottom = rect.bottom - 23;
            browserRect.right  = rect.right  - 5;
            browserRect.top    = 5;
            browserRect.left   = 5;

            m_pBrowser->MoveWindow(&browserRect);
        }
    }
}
//---------------------------------------------------------------------------
