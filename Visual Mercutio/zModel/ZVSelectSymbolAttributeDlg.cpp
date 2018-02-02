// ZVSelectSymbolAttributeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVSelectSymbolAttributeDlg.h"


// ZBPropertyAttributes
#include "zProperty\ZBPropertyAttributes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// ZVSelectSymbolAttributeDlg dialog


ZVSelectSymbolAttributeDlg::ZVSelectSymbolAttributeDlg(ZBPropertyAttributes* pPropAttributes /*= NULL*/, 
													   ZBPropertySet* pPropSet /*= NULL*/,
													   CWnd* pParent /*=NULL*/)
	: CDialog(ZVSelectSymbolAttributeDlg::IDD, pParent),
	m_pPropAttributes(pPropAttributes),
	m_pPropSet(pPropSet)
{
	//{{AFX_DATA_INIT(ZVSelectSymbolAttributeDlg)
	m_SetAsDefaultToAll = FALSE;
	m_ShowLabel = TRUE;
	//}}AFX_DATA_INIT
	if (m_pPropAttributes)
		m_ShowLabel = m_pPropAttributes->GetDisplayTitleText();
}


void ZVSelectSymbolAttributeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZVSelectSymbolAttributeDlg)
	DDX_Control(pDX, IDC_ATTRIBUTE_TREE, m_AttributeTree);
	DDX_Check(pDX, IDC_SETASDEFAULT_TOALL, m_SetAsDefaultToAll);
	DDX_Check(pDX, IDC_SHOWLABEL, m_ShowLabel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVSelectSymbolAttributeDlg, CDialog)
	//{{AFX_MSG_MAP(ZVSelectSymbolAttributeDlg)
	ON_BN_CLICKED(ID_APPLYTOALL, OnApplyToAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVSelectSymbolAttributeDlg message handlers

void ZVSelectSymbolAttributeDlg::OnApplyToAll() 
{
	UpdateData(TRUE);

	// Asks the control to fill the corresponding
	// checked items
	m_AttributeTree.FillCorrespondingCheckedItems();
	if (m_pPropAttributes)
		m_pPropAttributes->SetDisplayTitleText( m_ShowLabel );

	CDialog::EndDialog(ID_APPLYTOALL);
	
}

void ZVSelectSymbolAttributeDlg::OnOK() 
{
	UpdateData(TRUE);

	// Asks the control to fill the corresponding
	// checked items
	m_AttributeTree.FillCorrespondingCheckedItems();
	if (m_pPropAttributes)
		m_pPropAttributes->SetDisplayTitleText( m_ShowLabel );

	CDialog::OnOK();
}


BOOL ZVSelectSymbolAttributeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Initialize the attribute tree control
	m_AttributeTree.Initialize( m_pPropAttributes,m_pPropSet );

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
