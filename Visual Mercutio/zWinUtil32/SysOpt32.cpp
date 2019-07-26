#include "StdAfx.h"
#include "SysOpt32.h"

// processsoft
#include "zBaseLib\Export.h"
#include "zWinUtil32\PSS_GeneralPage.h"
#include "ViewPgR.h"
#include "ViewPage.h"
#include "PSS_CalculationPage.h"
#include "PSS_ExportPage.h"
#include "PSS_NavigationPage.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"

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
  : PSS_BasePropSheet(static_cast<UINT>(IDS_SYSTEMOPTION_TITLE)),
    m_pApplicationOptions(pApplicationOptions), m_PageOptions(PageOptions)
{
    // Add the general page
    if (PageOptions & GeneralOptionPage)
    {
        PSS_GeneralPage* pGeneralPage = new PSS_GeneralPage(pApplicationOptions);
        GetPageArray().Add( pGeneralPage );
        AddPage( pGeneralPage );
    }
    // Add the view page
    if (PageOptions & ViewOptionPage)
    {
        ZIViewPage*    pViewPage = new ZIViewPage( pApplicationOptions );
        GetPageArray().Add( pViewPage );
        AddPage( pViewPage );
    }
    // Add the view page (reduced version)
    if (PageOptions & ViewReducedOptionPage)
    {
        ZIViewPageReduced*    pViewPageReduced = new ZIViewPageReduced( pApplicationOptions );
        GetPageArray().Add( pViewPageReduced );
        AddPage( pViewPageReduced );
    }
    
    // add the calculation page
    if (PageOptions & CalculationOptionPage)
    {
        std::unique_ptr<PSS_CalculationPage> pCalculationPage(new PSS_CalculationPage(pApplicationOptions));
        GetPageArray().Add(pCalculationPage.get());
        AddPage(pCalculationPage.get());
        pCalculationPage.release();
    }

    // Add the navigation page
    if (PageOptions & NavigationOptionPage)
    {
        std::unique_ptr<PSS_NavigationPage> pNavigationPage(new PSS_NavigationPage(pApplicationOptions));
        GetPageArray().Add(pNavigationPage.get());
        AddPage(pNavigationPage.get());
        pNavigationPage.release();
    }

    // Add the export page
    if (PageOptions & ExportOptionPage)
    {
        PSS_ExportPage* pExportPage = new PSS_ExportPage(pApplicationOptions);
        GetPageArray().Add( pExportPage );
        AddPage( pExportPage );
    }
/*
    // Add the global page
    if (PageOptions & GlobalOptionPage)
    {
        ZIGeneralPage*    pGlobalPage = new ZIGeneralPage( pApplicationOptions );
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
    BOOL bResult = PSS_BasePropSheet::OnInitDialog();

    CenterWindow();
    return bResult;
}


int ZISystemOption::DoModal()
{
    if (PSS_BasePropSheet::DoModal() == IDOK)
    {
        // Run throughout all pages and test if the page
        // has been initialized. If it is the case,
        // requests to save
        CObArray&    PageArray = GetPageArray();
          for (int i = 0; i < PageArray.GetSize(); ++i)
              if (((ZIGenericPropPage*)(PageArray[i]))->HasBeenInitialized())
                  ((ZIGenericPropPage*)(PageArray[i]))->SaveValuesToObject();
        return IDOK;
    }
    return IDCANCEL;
}
