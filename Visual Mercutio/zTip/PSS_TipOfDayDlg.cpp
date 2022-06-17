/****************************************************************************
 * ==> PSS_TipOfDayDlg -----------------------------------------------------*
 ****************************************************************************
 * Description : Tip of the day dialog                                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_TipOfDayDlg.h"

// processsoft
#include "zWeb\PSS_WebBrowser.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_TipOfDayDlg, CDialog)
    //{{AFX_MSG_MAP(PSS_TipOfDayDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_TipOfDayDlg
//---------------------------------------------------------------------------
PSS_TipOfDayDlg::PSS_TipOfDayDlg(CWnd* pParent) :
    CDialog(PSS_TipOfDayDlg::IDD, pParent),
    m_DontShowOnStartup(FALSE),
    m_pBrowser(NULL)
{}
//---------------------------------------------------------------------------
PSS_TipOfDayDlg::PSS_TipOfDayDlg(UINT resID, CWnd* pParent) :
    CDialog(PSS_TipOfDayDlg::IDD, pParent),
    m_DontShowOnStartup(FALSE),
    m_pBrowser(NULL)
{
    CString strTemp;
    strTemp.Format(_T("%d"), resID);

    m_strURL = PSS_WebBrowser::BuildResourceToURL(strTemp);
}
//---------------------------------------------------------------------------
PSS_TipOfDayDlg::PSS_TipOfDayDlg(LPCTSTR pURL, BOOL isRes, CWnd* pParent) :
    CDialog(PSS_TipOfDayDlg::IDD, pParent),
    m_DontShowOnStartup(FALSE),
    m_pBrowser(NULL)
{
    if (isRes)
        m_strURL = PSS_WebBrowser::BuildResourceToURL(pURL);
    else
        m_strURL = pURL;
}
//---------------------------------------------------------------------------
PSS_TipOfDayDlg::~PSS_TipOfDayDlg()
{
    if (m_pBrowser)
        delete m_pBrowser;
}
//---------------------------------------------------------------------------
void PSS_TipOfDayDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    DDX_Check(pDX, IDC_STARTUP, m_DontShowOnStartup);
}
//---------------------------------------------------------------------------
BOOL PSS_TipOfDayDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (GetDlgItem(IDC_WEBCTRL))
    {
        CRect rect;
        GetDlgItem(IDC_WEBCTRL)->GetClientRect (&rect);
        GetDlgItem(IDC_WEBCTRL)->MapWindowPoints( this, &rect );

        // create the control
        m_pBrowser = new PSS_WebBrowser;
        ASSERT (m_pBrowser);

        if (!m_pBrowser->Create(NULL, NULL, WS_VISIBLE, rect, this, NULL))
        {
            TRACE("failed to create browser\n");
            delete m_pBrowser;
            m_pBrowser = NULL;
            return FALSE;
        }

        // initialize the first url
        COleVariant noArg;
        m_pBrowser->Navigate(m_strURL);
    }

    // activate the application window
    SetActiveWindow();
    SetForegroundWindow();

    // return TRUE unless the focus is set to a control. NOTE as an exception, OCX Property Pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
