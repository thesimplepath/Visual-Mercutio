/****************************************************************************
 * ==> PSS_PublishReportToHTML ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a report generator which will publish its content *
 *               to html files                                              *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PublishReportToHTMLH
#define PSS_PublishReportToHTMLH

#if _MSC_VER > 1000
    #pragma once
#endif

// change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

// processsoft
#include "zReport\PSS_GridReportDocument.h"
#include "PSS_PublishReportInfo.h"
#include "PSS_PublishConceptorReport.h"
#include "PSS_PublishProcessReport.h"
#include "PSS_PublishPrestationsReport.h"
#include "PSS_PublishRuleBook.h"
#include "PSS_PublishRuleBookDetails.h"

#ifdef _ZREPORTWEBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Publishes a report to html files
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PublishReportToHTML
{
    public:
        PSS_PublishReportToHTML();
        virtual ~PSS_PublishReportToHTML();

        /**
        * Exports the report to HTML files
        *@param pDoc - the document from which the report should be generated
        *@param pReportInfo - the report info
        */
        static bool ExportReportToHTMLFile(PSS_ProcessGraphModelDoc* pDoc, PSS_PublishReportInfo* pReportInfo);
};

#endif
