// ZVDeleteModelPageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVDeleteModelPageDlg.h"

#include "ProcGraphModelMdl.h"
#include "ZDProcessGraphPage.h"
#include "ZBModelSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
  
/////////////////////////////////////////////////////////////////////////////
// ZVDeleteModelPageDlg dialog


ZVDeleteModelPageDlg::ZVDeleteModelPageDlg(ZDProcessGraphModelMdl* pModel, ZBRuntimeClassSet* pSet /*= NULL*/, CWnd* pParent /*=NULL*/)
    : ZIDialog(ZVDeleteModelPageDlg::IDD, TRUE, pParent),
      m_pModel(pModel),
      m_pSelectedPage(NULL),
      m_pRootPage(NULL),
      m_pSet(pSet)
{
    //{{AFX_DATA_INIT(ZVDeleteModelPageDlg)
    m_PageName = _T("");
    //}}AFX_DATA_INIT
}


void ZVDeleteModelPageDlg::DoDataExchange(CDataExchange* pDX)
{
    ZIDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(ZVDeleteModelPageDlg)
    DDX_Control(pDX, IDC_EXISTINGPROCESS, m_SymbolTree);
    DDX_Text(pDX, IDC_PAGENAME, m_PageName);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVDeleteModelPageDlg, ZIDialog)
    //{{AFX_MSG_MAP(ZVDeleteModelPageDlg)
    ON_NOTIFY(TVN_SELCHANGED, IDC_EXISTINGPROCESS, OnSelchangedSymboltree)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVDeleteModelPageDlg message handlers

void ZVDeleteModelPageDlg::OnOK() 
{
    // TODO: Add extra validation here
    
    ZIDialog::OnOK();
}

void ZVDeleteModelPageDlg::OnSelchangedSymboltree(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

    if (m_SymbolTree.GetSelectedPage() != NULL && 
        m_pRootPage != m_SymbolTree.GetSelectedPage())
    {
        m_pSelectedPage = m_SymbolTree.GetSelectedPage ();
        m_PageName = m_pSelectedPage->GetPageName();
        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->EnableWindow(TRUE);

    }
    else
    {
        m_pSelectedPage = NULL;
        m_PageName = _T("");
        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->EnableWindow(FALSE);
    }
    UpdateData(FALSE);
    
    *pResult = 0;
}

BOOL ZVDeleteModelPageDlg::OnInitDialog() 
{
    ZIDialog::OnInitDialog();
    
    if (m_pModel)
    {
        ZBModelSet    DocumentModelSet;
        DocumentModelSet.AddModel( m_pModel );
        m_SymbolTree.Initialize( "Document", &DocumentModelSet, IDB_IL_BP_SYMBOLS, m_pSet );
        // Retreive the root page
        m_pRootPage = m_pModel->GetRoot()->FindModelPage( m_pModel->GetRoot(), true );
        // Set the OK disabled at startup
        if (GetDlgItem(IDOK))
            GetDlgItem(IDOK)->EnableWindow(FALSE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
