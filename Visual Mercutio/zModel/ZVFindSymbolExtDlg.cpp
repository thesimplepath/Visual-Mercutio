// ZVFindSymbolExtDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZVFindSymbolExtDlg.h"

// ZBPropertyAttributes
#include "zProperty\ZBPropertyAttributes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZVFindSymbolExtDlg dialog


ZVFindSymbolExtDlg::ZVFindSymbolExtDlg(ZBPropertyAttributes* pPropAttributes /*=NULL*/, 
                                       ZBPropertySet* pPropSet /*=NULL*/,
                                       CWnd* pParent /*=NULL*/)
: PSS_Dialog(ZVFindSymbolExtDlg::IDD, TRUE, pParent),
  m_pPropAttributes(pPropAttributes),
  m_pPropSet(pPropSet)
      
{
    //{{AFX_DATA_INIT(ZVFindSymbolExtDlg)
    m_InAllModels = TRUE;
    m_CaseSensitive = FALSE;
    m_PartialSearch = TRUE;
    m_What = _T("");
    //}}AFX_DATA_INIT
}


void ZVFindSymbolExtDlg::CheckControlState()
{
    UpdateData();
    if (GetDlgItem(IDC_FIND))
        GetDlgItem(IDC_FIND)->EnableWindow( !m_What.IsEmpty() );
}

void ZVFindSymbolExtDlg::DoDataExchange(CDataExchange* pDX)
{
    PSS_Dialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(ZVFindSymbolExtDlg)
    DDX_Control(pDX, IDC_ATTRIBUTE_TREE, m_AttributeText);
    DDX_Check(pDX, IDC_INALLMODELS, m_InAllModels);
    DDX_Check(pDX, IDC_CASESENSITIVE, m_CaseSensitive);
    DDX_Check(pDX, IDC_PARTIAL, m_PartialSearch);
    DDX_Text(pDX, IDC_WHAT, m_What);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZVFindSymbolExtDlg, PSS_Dialog)
    //{{AFX_MSG_MAP(ZVFindSymbolExtDlg)
    ON_EN_CHANGE(IDC_SYMBOLNAME, OnChangeSymbolName)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZVFindSymbolExtDlg message handlers

BOOL ZVFindSymbolExtDlg::OnInitDialog() 
{
    PSS_Dialog::OnInitDialog();

    // Initialize the attribute tree control
    m_AttributeText.Initialize( m_pPropAttributes,m_pPropSet );

    CheckControlState();
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void ZVFindSymbolExtDlg::OnChangeSymbolName() 
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


void ZVFindSymbolExtDlg::OnOK() 
{
    m_AttributeText.FillMatchingCheckedItems();

    PSS_Dialog::OnOK();
}
