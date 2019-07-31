/****************************************************************************
 * ==> PSS_SystemOptionSheet -----------------------------------------------*
 ****************************************************************************
 * Description : Provides a system option sheet                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_SystemOptionSheet.h"

// processsoft
#include "zBaseLib\Export.h"
#include "zWinUtil32\PSS_GeneralPage.h"
#include "PSS_ViewPage.h"
#include "PSS_ReducedViewPage.h"
#include "PSS_CalculationPage.h"
#include "PSS_NavigationPage.h"
#include "PSS_ExportPage.h"

// resources
#include "zWinUtil32\zWinUtil32Res.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// Message map
//---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(PSS_SystemOptionSheet, CPropertySheet)
    //{{AFX_MSG_MAP(PSS_SystemOptionSheet)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
//---------------------------------------------------------------------------
// PSS_SystemOptionSheet
//---------------------------------------------------------------------------
PSS_SystemOptionSheet::PSS_SystemOptionSheet(ZAApplicationOption* pAppOptions, IEOptionPage optionPages) :
    PSS_BasePropSheet(static_cast<UINT>(IDS_SYSTEMOPTION_TITLE)),
    m_pAppOptions(pAppOptions),
    m_OptionPages(optionPages)
{
    // add the general page
    if (optionPages & IE_OP_General)
    {
        std::unique_ptr<PSS_GeneralPage> pGeneralPage(new PSS_GeneralPage(pAppOptions));
        GetPageArray().Add(pGeneralPage.get());
        AddPage(pGeneralPage.get());
        pGeneralPage.release();
    }

    // add the view page
    if (optionPages & IE_OP_View)
    {
        std::unique_ptr<PSS_ViewPage> pViewPage(new PSS_ViewPage(pAppOptions));
        GetPageArray().Add(pViewPage.get());
        AddPage(pViewPage.get());
        pViewPage.release();
    }

    // add the view page (reduced version)
    if (optionPages & IE_OP_ViewReduced)
    {
        std::unique_ptr<PSS_ReducedViewPage> pViewPageReduced(new PSS_ReducedViewPage(pAppOptions));
        GetPageArray().Add(pViewPageReduced.get());
        AddPage(pViewPageReduced.get());
        pViewPageReduced.release();
    }
    
    // add the calculation page
    if (optionPages & IE_OP_Calculation)
    {
        std::unique_ptr<PSS_CalculationPage> pCalculationPage(new PSS_CalculationPage(pAppOptions));
        GetPageArray().Add(pCalculationPage.get());
        AddPage(pCalculationPage.get());
        pCalculationPage.release();
    }

    // add the navigation page
    if (optionPages & IE_OP_Navigation)
    {
        std::unique_ptr<PSS_NavigationPage> pNavigationPage(new PSS_NavigationPage(pAppOptions));
        GetPageArray().Add(pNavigationPage.get());
        AddPage(pNavigationPage.get());
        pNavigationPage.release();
    }

    // add the export page
    if (optionPages & IE_OP_Export)
    {
        std::unique_ptr<PSS_ExportPage> pExportPage(new PSS_ExportPage(pAppOptions));
        GetPageArray().Add(pExportPage.get());
        AddPage(pExportPage.get());
        pExportPage.release();
    }
}
//---------------------------------------------------------------------------
PSS_SystemOptionSheet::PSS_SystemOptionSheet(const PSS_SystemOptionSheet& other)
{
    THROW("Copy constructor isn't allowed for this class");
}
//---------------------------------------------------------------------------
PSS_SystemOptionSheet::~PSS_SystemOptionSheet()
{}
//---------------------------------------------------------------------------
const PSS_SystemOptionSheet& PSS_SystemOptionSheet::operator = (const PSS_SystemOptionSheet& other)
{
    THROW("Copy operator isn't allowed for this class");
}
//---------------------------------------------------------------------------
int PSS_SystemOptionSheet::DoModal()
{
    if (PSS_BasePropSheet::DoModal() == IDOK)
    {
              CObArray&   pageArray = GetPageArray();
        const std::size_t pageCount = pageArray.GetSize();

        // iterate through all pages and test if the page has been initialized, save it if it's the case
        for (int i = 0; i < pageCount; ++i)
        {
            PSS_GenericPropPage* pPage = (PSS_GenericPropPage*)pageArray[i];
            ASSERT(pPage);

            if (pPage->Initialized())
                pPage->SaveValuesToObject();
        }

        return IDOK;
    }

    return IDCANCEL;
}
//---------------------------------------------------------------------------
BOOL PSS_SystemOptionSheet::OnInitDialog()
{
    const BOOL result = PSS_BasePropSheet::OnInitDialog();

    CenterWindow();

    return result;
}
//---------------------------------------------------------------------------
