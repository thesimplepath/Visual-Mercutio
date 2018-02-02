// ZVFindSymbolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVFindSymbolDlg.h"
#include "ProcGraphModelMdl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVFindSymbolDlg dialog


ZVFindSymbolDlg::ZVFindSymbolDlg(ZDProcessGraphModelMdl& Mdl, UINT nIDRes, CWnd* pParent /*=NULL*/)
	: ZIDialog(ZVFindSymbolDlg::IDD, TRUE, pParent),
	  m_Model(Mdl),
	  m_pSymbol(NULL),
	  m_nIDRes(nIDRes)
{
	//{{AFX_DATA_INIT(ZVFindSymbolDlg)
	m_SymbolName = _T("");
	m_InAllModels = TRUE;
	m_PartialSearch = TRUE;
	m_CaseSensitive = FALSE;
	//}}AFX_DATA_INIT
}


void ZVFindSymbolDlg::CheckControlState()
{
	UpdateData();
	if (GetDlgItem(IDC_FIND))
		GetDlgItem(IDC_FIND)->EnableWindow( !m_SymbolName.IsEmpty() );

	if (GetDlgItem(IDC_BROWSE))
		GetDlgItem(IDC_BROWSE)->EnableWindow( m_ResultList.GetSelectedSymbol() != NULL );
}

void ZVFindSymbolDlg::DoDataExchange(CDataExchange* pDX)
{
	ZIDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZVFindSymbolDlg)
	DDX_Control(pDX, IDC_FINDRESULT_LIST, m_ResultList);
	DDX_Text(pDX, IDC_SYMBOLNAME, m_SymbolName);
	DDX_Check(pDX, IDC_INALLMODELS, m_InAllModels);
	DDX_Check(pDX, IDC_CASESENSITIVE, m_CaseSensitive);
	DDX_Check(pDX, IDC_PARTIAL, m_PartialSearch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVFindSymbolDlg, ZIDialog)
	//{{AFX_MSG_MAP(ZVFindSymbolDlg)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_EN_CHANGE(IDC_SYMBOLNAME, OnChangeSymbolName)
	ON_NOTIFY(NM_CLICK, IDC_FINDRESULT_LIST, OnClickFindResultList)
	ON_NOTIFY(NM_DBLCLK, IDC_FINDRESULT_LIST, OnDblclkFindResultList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVFindSymbolDlg message handlers

BOOL ZVFindSymbolDlg::OnInitDialog() 
{
	ZIDialog::OnInitDialog();
	
	m_ResultList.Initialize( NULL, m_nIDRes );
	CheckControlState();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVFindSymbolDlg::OnFind() 
{
	UpdateData();
	
	ZDProcessGraphModelMdl* pModel = &m_Model;
	if (m_InAllModels)
		pModel = m_Model.GetRoot();

	CODComponentSet* pSet = NULL;
	if (m_PartialSearch)
		pSet = pModel->FindSymbolPartialName( m_SymbolName, m_InAllModels, m_CaseSensitive, false );
	else
		pSet = pModel->FindSymbol( m_SymbolName, "", m_InAllModels, m_CaseSensitive, false );

	m_ResultList.Initialize( pSet, m_nIDRes );

}

void ZVFindSymbolDlg::OnBrowse() 
{
	if (m_ResultList.GetSelectedSymbol())
		m_pSymbol = m_ResultList.GetSelectedSymbol();
	EndDialog( IDC_BROWSE ); 
}


void ZVFindSymbolDlg::OnChangeSymbolName() 
{
	// If this is a RICHEDIT control, the control will not
	// send this notification unless you override the ZIDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	CheckControlState();

	// Set default to search button
	if (GetDlgItem(IDC_FIND))
		SetDefID( IDC_FIND );
}

void ZVFindSymbolDlg::OnClickFindResultList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CheckControlState();

	// Set default to browse button
	if (GetDlgItem(IDC_BROWSE))
		SetDefID( IDC_BROWSE );
	
	*pResult = 0;
}

void ZVFindSymbolDlg::OnDblclkFindResultList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CheckControlState();
	OnBrowse();
	*pResult = 0;
}
