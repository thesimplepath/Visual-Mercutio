
#include "StdAfx.h"
#include "zBaseLib\Export.h"
// SysOpt
#include "SysOpt32.h"


// GenPage
#include "zWinUtil32\GenPage.h"
// ViewPgR
#include "ViewPgR.h"
// ViewPage
#include "ViewPage.h"
// CalcPage
#include "CalcPage.h"
// ExpPage
#include "ExpPage.h"
// NavPage
#include "NavPage.h"

#include "zWinUtil32\ZWinUtil32.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//IMPLEMENT_DYNAMIC(ZISystemOption, ZIBasePropSheet)

BEGIN_MESSAGE_MAP(ZISystemOption, CPropertySheet)
	//{{AFX_MSG_MAP(ZISystemOption)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()





// Class ZISystemOption 


ZISystemOption::ZISystemOption(ZAApplicationOption* pApplicationOptions, unsigned int PageOptions)
  : ZIBasePropSheet(static_cast<UINT>(IDS_SYSTEMOPTION_TITLE)),
	m_pApplicationOptions(pApplicationOptions), m_PageOptions(PageOptions)
{
	// Add the general page
	if (PageOptions & GeneralOptionPage)
	{
		ZIGeneralPage*	pGeneralPage = new ZIGeneralPage( pApplicationOptions );
		GetPageArray().Add( pGeneralPage );
		AddPage( pGeneralPage );
	}
	// Add the view page
	if (PageOptions & ViewOptionPage)
	{
		ZIViewPage*	pViewPage = new ZIViewPage( pApplicationOptions );
		GetPageArray().Add( pViewPage );
		AddPage( pViewPage );
	}
	// Add the view page (reduced version)
	if (PageOptions & ViewReducedOptionPage)
	{
		ZIViewPageReduced*	pViewPageReduced = new ZIViewPageReduced( pApplicationOptions );
		GetPageArray().Add( pViewPageReduced );
		AddPage( pViewPageReduced );
	}
	
	// Add the calculation page
	if (PageOptions & CalculationOptionPage)
	{
		ZICalculationPage*	pCalculationPage = new ZICalculationPage( pApplicationOptions );
		GetPageArray().Add( pCalculationPage );
		AddPage( pCalculationPage );
	}
	// Add the navigation page
	if (PageOptions & NavigationOptionPage)
	{
		ZINavigationPage*	pNavigationPage = new ZINavigationPage( pApplicationOptions );
		GetPageArray().Add( pNavigationPage );
		AddPage( pNavigationPage );
	}
	// Add the export page
	if (PageOptions & ExportOptionPage)
	{
		ZIExportPage*	pExportPage = new ZIExportPage( pApplicationOptions );
		GetPageArray().Add( pExportPage );
		AddPage( pExportPage );
	}
/*
	// Add the global page
	if (PageOptions & GlobalOptionPage)
	{
		ZIGeneralPage*	pGlobalPage = new ZIGeneralPage( pApplicationOptions );
		GetPageArray().Add( pGlobalPage );
		AddPage( pGlobalPage );
	}
*/	
}


ZISystemOption::~ZISystemOption()
{
}




BOOL ZISystemOption::OnInitDialog()
{
	BOOL bResult = ZIBasePropSheet::OnInitDialog();

	CenterWindow();
	return bResult;
}


int ZISystemOption::DoModal()
{
	if (ZIBasePropSheet::DoModal() == IDOK)
	{
		// Run throughout all pages and test if the page
		// has been initialized. If it is the case,
		// requests to save
		CObArray&	PageArray = GetPageArray();
  		for (int i = 0; i < PageArray.GetSize(); ++i)
  			if (((ZIGenericPropPage*)(PageArray[i]))->HasBeenInitialized())
  				((ZIGenericPropPage*)(PageArray[i]))->SaveValuesToObject();
		return IDOK;
	}
	return IDCANCEL;
}
