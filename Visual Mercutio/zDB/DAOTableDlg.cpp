// DAOTableDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DAOTableDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZDAOTableDlg dialog


ZDAOTableDlg::ZDAOTableDlg(CWnd* pParent /*=NULL*/)
    : ZIDialog(ZDAOTableDlg::IDD, TRUE, pParent)
{
    m_TableName = _T("");
}

ZDAOTableDlg::ZDAOTableDlg(CDaoDatabase* pDB, CWnd* pParent /*=NULL*/)
    : ZIDialog(ZDAOTableDlg::IDD, TRUE, pParent)
{
    m_pDB = pDB;
    m_TableName = _T("");
    //{{AFX_DATA_INIT(ZDAOTableDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

void ZDAOTableDlg::DoDataExchange(CDataExchange* pDX)
{
    ZIDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZDAOTableDlg)
    DDX_Control(pDX, IDC_LISTBOX, m_ListBox);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZDAOTableDlg, ZIDialog)
    //{{AFX_MSG_MAP(ZDAOTableDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZDAOTableDlg message handlers


BOOL ZDAOTableDlg::OnInitDialog() 
{
    ZIDialog::OnInitDialog();
    
    m_ListBox.Initialize( m_pDB );
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void ZDAOTableDlg::OnOK() 
{
    m_TableName = m_ListBox.GetSelectedTable();
    ZIDialog::OnOK();

}

