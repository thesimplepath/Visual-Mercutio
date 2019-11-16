// ZIUnitInfo.cpp : implementation file
//

#include "stdafx.h"
#include "ZIUnitInfo.h"
#include "zBaseLib\PSS_Directory.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZIUnitInfo dialog


ZIUnitInfo::ZIUnitInfo(const CString Name /*= ""*/, 
                       const CString Directory /*= ""*/, 
                       bool DisplayOnly /*= false*/, 
                       CWnd* pParent /*=NULL*/)
    : CDialog(ZIUnitInfo::IDD, pParent),
      m_Directory(Directory),
      m_DisplayOnly(DisplayOnly)
{
    //{{AFX_DATA_INIT(ZIUnitInfo)
    m_UnitName = Name;
    //}}AFX_DATA_INIT
    m_UnitDirectory.SetSearchType(PSS_SearchEditButton::IE_T_Directory, "", m_Directory);

    // If the directory is empty, use the current directory
    if (m_Directory.IsEmpty())
    {
        GetCurrentDirectory( 500, m_Directory.GetBuffer( 500 ) );
    }

}


void ZIUnitInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZIUnitInfo)
    DDX_Control(pDX, IDC_UNITDIR, m_UnitDirectory);
    DDX_Text(pDX, IDC_UNITNAME, m_UnitName);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZIUnitInfo, CDialog)
    //{{AFX_MSG_MAP(ZIUnitInfo)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZIUnitInfo message handlers

void ZIUnitInfo::OnOK() 
{
    UpdateData( TRUE );
    if (!m_DisplayOnly)
    {
        if (m_UnitName.IsEmpty())
            return;
        m_UnitDirectory.GetWindowText( m_Directory );
        m_Directory = PSS_Directory::NormalizeDirectory( m_Directory );
    }    
    CDialog::OnOK();
}

BOOL ZIUnitInfo::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    if (m_DisplayOnly)
    {
        if (GetDlgItem(IDC_UNITNAME))
            GetDlgItem(IDC_UNITNAME)->EnableWindow(FALSE);

        if (GetDlgItem(IDC_UNITDIR))
            GetDlgItem(IDC_UNITDIR)->EnableWindow(FALSE);

        CString    Text;
        Text.LoadString( IDS_CLOSE_TEXT );
        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->SetWindowText( Text );

    }
    m_UnitDirectory.SetWindowText( m_Directory );

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
