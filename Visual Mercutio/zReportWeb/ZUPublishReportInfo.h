#if !defined(AFX_ZVPUBLISHREPORTINFO_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_)
#define AFX_ZVPUBLISHREPORTINFO_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_

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

#include "zProperty\ZBPropertyAttributes.h"

#ifdef _ZREPORTWEBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

struct AFX_EXT_CLASS ZUPublishReportInfo
{
public:

    ZUPublishReportInfo()
    {
        DoExportProcessReport        = FALSE;
        DoExportConceptorReport        = FALSE;
        DoExportPrestationsReport    = FALSE;
        DoExportRuleBook            = FALSE;
        DoLaunchBrowser                = FALSE;

        Directory                    = _T( "" );
        IndexName                    = _T( "" );
    }

public:

    // JMR-MODIF - Le 6 mars 2006 - Ajout de la variable DoExportProcessReport.
    BOOL                    DoExportProcessReport;
    // JMR-MODIF - Le 6 mars 2006 - Modification de la variable DoExportReport en DoExportConceptorReport.
    BOOL                    DoExportConceptorReport;
    // JMR-MODIF - Le 15 mars 2006 - Ajout de la variable DoExportPrestationsReport.
    BOOL                    DoExportPrestationsReport;
    // JMR-MODIF - Le 14 janvier 2007 - Ajout de la variable DoExportRuleBook.
    BOOL                    DoExportRuleBook;
    BOOL                    DoLaunchBrowser;

    BOOL                    DoIncludeDeliverables;
    BOOL                    DoIncludeDetails;

    CString                    Directory;
    CString                    IndexName;

    // JMR-MODIF - Le 6 mars 2006 - Ajout de la variable Attributes.
    ZBPropertyAttributes    Attributes;
};

#endif // !defined(AFX_ZVPUBLISHREPORTINFO_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_)