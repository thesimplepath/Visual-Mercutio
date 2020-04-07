/****************************************************************************
 * ==> PSS_PublishReportToHTML ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a report generator which will publish its content *
 *               to html files                                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_PublishReportToHTML.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_PublishReportToHTML
//---------------------------------------------------------------------------
PSS_PublishReportToHTML::PSS_PublishReportToHTML()
{}
//---------------------------------------------------------------------------
PSS_PublishReportToHTML::~PSS_PublishReportToHTML()
{}
//---------------------------------------------------------------------------
bool PSS_PublishReportToHTML::ExportReportToHTMLFile(PSS_ProcessGraphModelDoc* pDoc, PSS_PublishReportInfo* pReportInfo)
{
    if (!pDoc)
        return false;

    if (!pReportInfo)
        return false;

    PSS_ProcessGraphModelMdlBP* pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pDoc->GetModel());

    // export the Conceptor report content
    if (pReportInfo->m_DoExportConceptorReport)
    {
        std::unique_ptr<PSS_PublishConceptorReport> pConceptorReportGenerator
                (new PSS_PublishConceptorReport(pModel, pReportInfo->m_DoIncludeDetails, pReportInfo->m_DoIncludeDeliverables));

        pConceptorReportGenerator->Publish(pReportInfo->m_Directory + _T("\\"));
    }

    // export the process report content
    if (pReportInfo->m_DoExportProcessReport)
    {
        std::unique_ptr<PSS_PublishProcessReport> pProcessReportGenerator
                (new PSS_PublishProcessReport(pModel, &pReportInfo->m_Attributes));

        pProcessReportGenerator->Publish(pReportInfo->m_Directory + _T("\\"));
    }

    // export the prestations report content
    if (pReportInfo->m_DoExportPrestationsReport)
    {
        std::unique_ptr<PSS_PublishPrestationsReport> pPrestationsReportGenerator(new PSS_PublishPrestationsReport(pModel));
        pPrestationsReportGenerator->Publish(pReportInfo->m_Directory + _T("\\"));
    }

    // export the rule report content
    if (pReportInfo->m_DoExportRuleBook)
    {
        std::unique_ptr<PSS_PublishRuleBook> pRuleBookGenerator(new PSS_PublishRuleBook(pModel));
        pRuleBookGenerator->Publish(pReportInfo->m_Directory + _T("\\"));

        // publish the publication details
        std::unique_ptr<PSS_PublishRuleBookDetails> pRuleBookDetailsGenerator(new PSS_PublishRuleBookDetails(pModel));
        pRuleBookDetailsGenerator->Publish(pReportInfo->m_Directory + _T("\\"));
    }

    return true;
}
//---------------------------------------------------------------------------
