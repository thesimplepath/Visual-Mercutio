/****************************************************************************
 * ==> PSS_PublishReportInfo -----------------------------------------------*
 ****************************************************************************
 * Description : Provides the publish report info                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PublishReportInfoH
#define PSS_PublishReportInfoH

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
#include "zProperty\PSS_PropertyAttributes.h"

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
* Generic file
*@author Dominique Aigroz, Jean-Milost Reymond
*/
struct AFX_EXT_CLASS PSS_PublishReportInfo
{
    public:
        PSS_PropertyAttributes m_Attributes;
        CString                m_Directory;
        CString                m_IndexName;
        BOOL                   m_DoExportProcessReport;
        BOOL                   m_DoExportConceptorReport;
        BOOL                   m_DoExportPrestationsReport;
        BOOL                   m_DoExportRuleBook;
        BOOL                   m_DoLaunchBrowser;
        BOOL                   m_DoIncludeDeliverables;
        BOOL                   m_DoIncludeDetails;

        PSS_PublishReportInfo();
        virtual ~PSS_PublishReportInfo();
};

#endif
