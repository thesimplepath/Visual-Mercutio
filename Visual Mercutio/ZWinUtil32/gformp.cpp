// gformp.cpp : implementation file
//

#include "stdafx.h"
#include "gformp.h"
#include "zBaseLib\msgbox.h"
#include "planfin.hdf"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(ZIGenericFormPage, CPropertyPage)
	//{{AFX_MSG_MAP(ZIGenericFormPage)
	ON_LBN_SELCHANGE(IDC_LISTPLANFIN, OnSelChangeList)
	ON_LBN_DBLCLK(IDC_LISTPLANFIN, OnDblclkListOfForms)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZIGenericFormPage generic property page

ZIGenericFormPage::ZIGenericFormPage()
: CPropertyPage(ZIGenericFormPage::IDD), m_pTemplateManager(NULL)
{
}


ZIGenericFormPage::ZIGenericFormPage( CWnd *pMain, CString sTitle, ZDTemplateManager* pTemplateManager )
: CPropertyPage(ZIGenericFormPage::IDD), m_pTemplateManager(pTemplateManager)
{
	ASSERT( m_pTemplateManager );
	m_strCaption = sTitle;
#ifdef _WIN32
    m_psp.dwFlags |= PSP_USETITLE;
    m_psp.pszTitle = sTitle;
#endif
}


ZIGenericFormPage::~ZIGenericFormPage()
{
}


void ZIGenericFormPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZIGenericFormPage)
	DDX_Control(pDX, IDC_LISTPLANFIN, m_ctlListOfPlan);
	//}}AFX_DATA_MAP
}

void ZIGenericFormPage::OnSelChangeList()
{
	// Set the commentary
	int iCurrentSelection = m_ctlListOfPlan.GetCurSel();
	if (iCurrentSelection != LB_ERR && GetParent() && GetParent()->GetParent())
		GetParent()->GetParent()->PostMessage( UM_SETCOMMENT, iCurrentSelection );
}

void ZIGenericFormPage::OnDblclkListOfForms()
{
	if (GetParent() && GetParent()->GetParent())
		GetParent()->GetParent()->PostMessage( UM_FORMS_SELECTED );
}

 
BOOL ZIGenericFormPage::OnSetActive()
{
	ASSERT( m_pTemplateManager );

	BOOL	bRetValue = CPropertyPage::OnSetActive();
	// Run throughout all template directory	
  	ZDTemplateDir* pTemplateDir = m_pTemplateManager->FindTemplateDir( m_strCaption );

	// Copy values to the CListBox
	m_ctlListOfPlan.ResetContent();
	// Run throughout all template directory	
	ZDTemplateFile* pTemplateFile;
	for (size_t i = 0; i < pTemplateDir->GetSize(); ++i)
  	{
	  	pTemplateFile = pTemplateDir->GetTemplateFileAt( i );
	  	if (pTemplateFile)
	  		m_ctlListOfPlan.AddString( pTemplateFile->GetTitle() );
  	}
	GetParent()->GetParent()->PostMessage( UM_FORMACTIVATE );
  	return bRetValue;
}

