// TipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TipDlg.h"
#include "zWeb\ZWebBrowser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZTipOfDayDlg dialog


ZTipOfDayDlg::ZTipOfDayDlg(CWnd* pParent /*=NULL*/)
    : CDialog(ZTipOfDayDlg::IDD, pParent),
    m_pBrowser(NULL)
{
    //{{AFX_DATA_INIT(ZTipOfDayDlg)
    m_DontShowOnStartup = FALSE;
    //}}AFX_DATA_INIT
}


ZTipOfDayDlg::ZTipOfDayDlg(UINT nResID, CWnd* pParent /*=NULL*/)
    : CDialog(ZTipOfDayDlg::IDD, pParent),
    m_pBrowser(NULL)
{
    //{{AFX_DATA_INIT(ZTipOfDayDlg)
    m_DontShowOnStartup = FALSE;
    //}}AFX_DATA_INIT
    CString strTemp;
    strTemp.Format("%d", nResID);
    
    m_strURL = ZWebBrowser::BuildResourceToURL(strTemp);
}

ZTipOfDayDlg::ZTipOfDayDlg(LPCTSTR lpszURL, BOOL bRes, CWnd* pParent /*=NULL*/)
    : CDialog(ZTipOfDayDlg::IDD, pParent),
    m_pBrowser(NULL)
{
    //{{AFX_DATA_INIT(ZTipOfDayDlg)
    m_DontShowOnStartup = FALSE;
    //}}AFX_DATA_INIT
    if (bRes)
    {
        m_strURL = ZWebBrowser::BuildResourceToURL(lpszURL);
    }
    else
        m_strURL = lpszURL;
}


ZTipOfDayDlg::~ZTipOfDayDlg()
{
    if (m_pBrowser)
        delete m_pBrowser;
    m_pBrowser = NULL;
}

void ZTipOfDayDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZTipOfDayDlg)
    DDX_Check(pDX, IDC_STARTUP, m_DontShowOnStartup);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZTipOfDayDlg, CDialog)
    //{{AFX_MSG_MAP(ZTipOfDayDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZTipOfDayDlg message handlers

BOOL ZTipOfDayDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();

    if (GetDlgItem(IDC_WEBCTRL))
    {
        CRect rect;
        GetDlgItem(IDC_WEBCTRL)->GetClientRect (&rect);
        GetDlgItem(IDC_WEBCTRL)->MapWindowPoints( this, &rect );

        // Create the control.
        m_pBrowser = new ZWebBrowser;
        ASSERT (m_pBrowser);
        if (!m_pBrowser->Create(NULL,NULL,WS_VISIBLE,rect,this,NULL))
        {
            TRACE("failed to create browser\n");
            delete m_pBrowser;
            m_pBrowser = NULL;
            return FALSE;
        }

        // Initialize the first URL.
        COleVariant noArg;
        m_pBrowser->Navigate( m_strURL );

    }
    // Activate the application window
    SetActiveWindow();
    SetForegroundWindow();
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}




