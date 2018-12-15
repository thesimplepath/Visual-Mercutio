#if !defined(AFX_ZVPUBLISHREPORTTOHTML_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_)
#define AFX_ZVPUBLISHREPORTTOHTML_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zReport\ZDGridReportDoc.h"

#include "ZUPublishReportInfo.h"
#include "ZVPublishConceptorReport.h"
#include "ZVPublishProcessReport.h"
#include "ZVPublishPrestationsReport.h"
// JMR-MODIF - Le 14 janvier 2007 - Ajout de l'en-tête ZVPublishRuleBook.h
#include "ZVPublishRuleBook.h"
// JMR-MODIF - Le 25 avril 2007 - Ajout de l'en-tête ZVPublishRuleBook.h
#include "ZVPublishRuleBookDetails.h"

#ifdef _ZREPORTWEBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

class AFX_EXT_CLASS ZUPublishReportToHTML
{
public:

    ZUPublishReportToHTML                ();
    ~ZUPublishReportToHTML                ();

    static bool ExportReportToHTMLFile    ( ZDProcessGraphModelDoc*    pDoc,
                                          ZUPublishReportInfo*        ReportInfo );
};

#endif // !defined(AFX_ZVPUBLISHREPORTTOHTML_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_)