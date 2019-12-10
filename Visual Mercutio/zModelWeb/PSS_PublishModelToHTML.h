/****************************************************************************
 * ==> PSS_PublishModelToHTML ----------------------------------------------*
 ****************************************************************************
 * Description : Publishes a model to html file                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#ifndef PSS_PublishModelToHTMLH
#define PSS_PublishModelToHTMLH

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
#include "zReportWeb\ZUPublishReportInfo.h"

// class name mapping
#ifndef PSS_ProcessGraphModelDoc
    #define PSS_ProcessGraphModelDoc ZDProcessGraphModelDoc
#endif

// forward class declarations
class PSS_ProcessGraphModelDoc;
class PSS_ProcessGraphModelView;
class ZDGridReportDocument;

#ifdef _ZMODELWEBEXPORT
    // put the values back to make AFX_EXT_CLASS export again
    #undef AFX_EXT_CLASS
    #undef AFX_EXT_API
    #undef AFX_EXT_DATA
    #define AFX_EXT_CLASS AFX_CLASS_EXPORT
    #define AFX_EXT_API AFX_API_EXPORT
    #define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

/**
* Publishes a model in html format
*@author Dominique Aigroz, Jean-Milost Reymond
*/
class AFX_EXT_CLASS PSS_PublishModelToHTML
{
    public:
        PSS_PublishModelToHTML();
        virtual ~PSS_PublishModelToHTML();

        /**
        * Publishes a model to a html file
        *@param pDoc - document owning the model
        *@param pView - document view
        *@param pReportInfo - report info
        *@param iniFileName - ini file name
        *@return true on success, otherwise false
        */
        static bool ExportModelToHTMLFile(PSS_ProcessGraphModelDoc*  pDoc,
                                          PSS_ProcessGraphModelView* pView,
                                          ZUPublishReportInfo*       pReportInfo,
                                          const CString&             iniFileName = _T(""));

        /**
        * Launches the browser
        *@param index - index
        */
        static void LaunchBrowser(const CString& index);
};

#endif
