#include "StdAfx.h"
#include "ZUPublishReportToHTML.h"

ZUPublishReportToHTML::ZUPublishReportToHTML()
{
}

ZUPublishReportToHTML::~ZUPublishReportToHTML()
{
}

// Cette fonction permet l'exportation du rapport Conceptor vers un système de fichiers HTML.
bool ZUPublishReportToHTML::ExportReportToHTMLFile(PSS_ProcessGraphModelDoc*    pDoc,
                                                    ZUPublishReportInfo*    ReportInfo )
{
    if ( ReportInfo != NULL )
    {
        if ( ReportInfo->DoExportConceptorReport == TRUE )
        {
            ZVPublishConceptorReport* m_pConceptorReportGenerator =
                new ZVPublishConceptorReport( dynamic_cast<PSS_ProcessGraphModelMdlBP*>( pDoc->GetModel() ),
                                              ReportInfo->DoIncludeDetails,
                                              ReportInfo->DoIncludeDeliverables );

            if ( !m_pConceptorReportGenerator )
            {
                return false;
            }

            m_pConceptorReportGenerator->Publish( ReportInfo->Directory + _T( "\\" ) );

            delete m_pConceptorReportGenerator;
        }

        // JMR-MODIF - Le 6 mars 2006 - Ajout de l'exportation du rapport Processus.
        if ( ReportInfo->DoExportProcessReport == TRUE )
        {
            ZVPublishProcessReport* m_pProcessReportGenerator =
                new ZVPublishProcessReport( dynamic_cast<PSS_ProcessGraphModelMdlBP*>( pDoc->GetModel() ),
                                            &ReportInfo->Attributes );

            if ( !m_pProcessReportGenerator )
            {
                return false;
            }

            m_pProcessReportGenerator->Publish( ReportInfo->Directory + _T( "\\" ) );

            delete m_pProcessReportGenerator;
        }

        // JMR-MODIF - Le 15 mars 2006 - Ajout de l'exportation du rapport Prestations.
        if ( ReportInfo->DoExportPrestationsReport == TRUE )
        {
            ZVPublishPrestationsReport* m_pPrestationsReportGenerator =
                new ZVPublishPrestationsReport( dynamic_cast<PSS_ProcessGraphModelMdlBP*>( pDoc->GetModel() ) );

            if ( !m_pPrestationsReportGenerator )
            {
                return false;
            }

            m_pPrestationsReportGenerator->Publish( ReportInfo->Directory + _T( "\\" ) );

            delete m_pPrestationsReportGenerator;
        }

        // JMR-MODIF - Le 14 janvier 2007 - Ajout de l'exportation du livre des règles.
        if ( ReportInfo->DoExportRuleBook == TRUE )
        {
            ZVPublishRuleBook* m_pRuleBookGenerator =
                new ZVPublishRuleBook( dynamic_cast<PSS_ProcessGraphModelMdlBP*>( pDoc->GetModel() ) );

            if ( !m_pRuleBookGenerator )
            {
                return false;
            }

            m_pRuleBookGenerator->Publish( ReportInfo->Directory + _T( "\\" ) );

            delete m_pRuleBookGenerator;

            // JMR-MODIF - Le 25 avril 2007 - Ajout de l'infrastructure pour la publication des détails.
            ZVPublishRuleBookDetails* m_pRuleBookDetailsGenerator =
                new ZVPublishRuleBookDetails( dynamic_cast<PSS_ProcessGraphModelMdlBP*>( pDoc->GetModel() ) );

            if ( !m_pRuleBookDetailsGenerator )
            {
                return false;
            }

            m_pRuleBookDetailsGenerator->Publish( ReportInfo->Directory + _T( "\\" ) );

            delete m_pRuleBookDetailsGenerator;
        }
    }

    return true;
}
