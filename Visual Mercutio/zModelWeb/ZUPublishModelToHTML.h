/********************************************************************************************************
 *                                           Classe ZUPublishModelToHTML                                    *
 ********************************************************************************************************
 * Cette classe permet la gestion de l'exportation d'un projet au format HTML.                            *
 ********************************************************************************************************/

#if !defined(AFX_ZUPUBLISHMODELTOHTML_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_)
#define AFX_ZUPUBLISHMODELTOHTML_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_

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

#include "zReportWeb\ZUPublishReportInfo.h"

// Forward class declarations
class ZDProcessGraphModelDoc;
class ZIProcessGraphModelView;
class ZDGridReportDocument;

#ifdef _ZMODELWEBEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 3 juillet 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// ******************************************************************************************************
// *                                         Classe ZUPublishModelToHTML                                *
// ******************************************************************************************************

class AFX_EXT_CLASS ZUPublishModelToHTML
{
public:

    ZUPublishModelToHTML();
    virtual ~ZUPublishModelToHTML();

    static bool ExportModelToHTMLFile    ( ZDProcessGraphModelDoc*        pDoc,
                                          ZIProcessGraphModelView*        pView,
                                          ZUPublishReportInfo*            m_pReportInfo,
                                          const CString                    IniFilename = _T( "" ) );

    static void LaunchBrowser            ( CString Index );
};

#endif // !defined(AFX_ZUPUBLISHMODELTOHTML_H__2911BA6F_30D8_459C_9B9A_A644F79B704F__INCLUDED_)