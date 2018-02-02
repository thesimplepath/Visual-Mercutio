// ZVManageValueIntelliEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ZVManageValueIntelliEdit.h"

#include "InpVal.h"

#include "zBaseLib\zBaseLibRes.h"
#include "zRes32\zRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVManageValueIntelliEdit dialog


ZVManageValueIntelliEdit::ZVManageValueIntelliEdit(CStringArray* pArrayOfValues, CWnd* pParent /*=NULL*/)
: CDialog(IDD_MGVALUE_INTELLI, pParent), // ZVManageValueIntelliEdit::IDD, pParent), 
  m_pArrayOfValues(pArrayOfValues)
{
	//{{AFX_DATA_INIT(ZVManageValueIntelliEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ZVManageValueIntelliEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZVManageValueIntelliEdit)
	DDX_Control(pDX, IDC_VALUES, m_Values);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVManageValueIntelliEdit, CDialog)
	//{{AFX_MSG_MAP(ZVManageValueIntelliEdit)
	ON_BN_CLICKED(IDC_ADDVALUE, OnAddvalue)
	ON_BN_CLICKED(IDC_DELVALUE, OnDelvalue)
	ON_LBN_SELCHANGE(IDC_VALUES, OnSelchangeValues)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVManageValueIntelliEdit message handlers

void ZVManageValueIntelliEdit::OnAddvalue() 
{
	ZIInputValue	Dlg(IDS_INSERTVALUE_INTELLI);

	if (Dlg.DoModal() == IDOK)
	{
		m_Values.AddString( Dlg.GetValue() );
	}

	OnSelchangeValues();
	
}

void ZVManageValueIntelliEdit::OnDelvalue() 
{
	int CurSel = m_Values.GetCurSel();
	ASSERT( CurSel != LB_ERR );
	m_Values.DeleteString( CurSel );
}

void ZVManageValueIntelliEdit::OnSelchangeValues() 
{
	if (GetDlgItem(IDC_DELVALUE))
		GetDlgItem(IDC_DELVALUE)->EnableWindow( m_Values.GetCurSel() != LB_ERR );
}

BOOL ZVManageValueIntelliEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	// Fill the list box
	if (!m_pArrayOfValues)
		return TRUE;
	m_Values.ResetContent();
	for (size_t i = 0; i < (size_t)m_pArrayOfValues->GetSize(); ++i)
		m_Values.AddString( m_pArrayOfValues->GetAt(i) );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVManageValueIntelliEdit::OnOK() 
{
	if (m_pArrayOfValues)
	{
		CString s;
		// Remove all elements
		m_pArrayOfValues->RemoveAll();
		// Copy listbox elements to array
		int Count = m_Values.GetCount();
		for (int i=0; i < Count; ++i)
		{
			m_Values.GetText( i, s );
			m_pArrayOfValues->Add( s );
		}
	}
	
	CDialog::OnOK();
}
