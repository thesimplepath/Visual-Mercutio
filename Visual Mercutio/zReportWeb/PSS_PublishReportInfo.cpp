/****************************************************************************
 * ==> PSS_PublishReportInfo -----------------------------------------------*
 ****************************************************************************
 * Description : Provides the publish report info                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_PublishReportInfo.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_PublishReportInfo
//---------------------------------------------------------------------------
PSS_PublishReportInfo::PSS_PublishReportInfo() :
    m_DoExportProcessReport(FALSE),
    m_DoExportConceptorReport(FALSE),
    m_DoExportPrestationsReport(FALSE),
    m_DoExportRuleBook(FALSE),
    m_DoLaunchBrowser(FALSE),
    m_DoIncludeDeliverables(FALSE),
    m_DoIncludeDetails(FALSE)
{}
//---------------------------------------------------------------------------
PSS_PublishReportInfo::~PSS_PublishReportInfo()
{}
//---------------------------------------------------------------------------
