/****************************************************************************
 * ==> PSS_DAOTableDlg -----------------------------------------------------*
 ****************************************************************************
 * Description : Provides a data access object (DAO) table dialog box       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_DAOTableDlg.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_DAOTableDlg, PSS_Dialog)
    //{{AFX_MSG_MAP(PSS_DAOTableDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_DAOTableDlg
//---------------------------------------------------------------------------
PSS_DAOTableDlg::PSS_DAOTableDlg(CWnd* pParent) :
    PSS_Dialog(PSS_DAOTableDlg::IDD, TRUE, pParent),
    m_pDB(NULL)
{}
//---------------------------------------------------------------------------
PSS_DAOTableDlg::PSS_DAOTableDlg(CDaoDatabase* pDB, CWnd* pParent) :
    PSS_Dialog(PSS_DAOTableDlg::IDD, TRUE, pParent),
    m_pDB(pDB)
{}
//---------------------------------------------------------------------------
void PSS_DAOTableDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(PSS_DAOTableDlg)
    DDX_Control(pDX, IDC_LISTBOX, m_ListBox);
    //}}AFX_DATA_MAP
}
//---------------------------------------------------------------------------
BOOL PSS_DAOTableDlg::OnInitDialog()
{
    PSS_Dialog::OnInitDialog();

    m_ListBox.Initialize(m_pDB);

    // return TRUE unless the focus is set to a control. NOTE as an exception, OCX property pages should return FALSE
    return TRUE;
}
//---------------------------------------------------------------------------
void PSS_DAOTableDlg::OnOK()
{
    m_TableName = m_ListBox.GetSelectedTable();
    PSS_Dialog::OnOK();
}
//---------------------------------------------------------------------------
