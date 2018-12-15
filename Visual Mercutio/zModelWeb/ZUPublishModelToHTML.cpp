/********************************************************************************************************
 *                                           Classe ZUPublishModelToHTML                                    *
 ********************************************************************************************************
 * Cette classe permet la gestion de l'exportation d'un projet au format HTML.                            *
 ********************************************************************************************************/

#include "stdafx.h"
#include "ZUPublishModelToHTML.h"

#include "zModel\ProcGraphModelMdl.h"
#include "zModel\ProcGraphModelCtlr.h"

// JMR-MODIF - Le 25 mai 2005 - Ajout de #define _ZMODELEXPORT et #undef _ZMODELEXPORT pour supprimer une erreur.
#define _ZMODELEXPORT
#include "zModel\ProcGraphModelDoc.h"
#include "zModel\ProcGraphModelView.h"
#undef _ZMODELEXPORT

#include "zModel\ZUDynamicAttributesManipulator.h"

// ZBPropertyAttributes
#include "zProperty\ZBPropertyAttributes.h"

// Resource manager helper class
#include "zResMgr\ZBResourceManager.h"

#include "ZUModelGenerateImageFiles.h"
#include "zModel\ZBInfoModelGraphicGeneration.h"

// ZVPublishModel
#include "ZVPublishModel.h"

#include "zBaseLib\ZAGlobal.h"

#include "zBaseLib\ZUFileLauncher.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 28 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

// ******************************************************************************************************
// *                                           Construction et destruction                                *
// ******************************************************************************************************

// Constructeur par défaut de la classe ZUPublishModelToHTML.
ZUPublishModelToHTML::ZUPublishModelToHTML()
{
}

// Destructeur de la classe ZUPublishModelToHTML.
ZUPublishModelToHTML::~ZUPublishModelToHTML()
{
}

// ******************************************************************************************************
// *                                             Fonctions d'exportation                                *
// ******************************************************************************************************

// Cette fonction permet l'exportation du projet au format HTML.
bool ZUPublishModelToHTML::ExportModelToHTMLFile( ZDProcessGraphModelDoc*    pDoc,
                                                  ZIProcessGraphModelView*    pView,
                                                  ZUPublishReportInfo*        m_pReportInfo,
                                                  const CString                IniFilename /*= ""*/ )
{
    if ( !pDoc || !pView )
    {
        return false;
    }

    ZBPropertySet Set;
    ZUDynamicAttributesManipulator::ExtractUniqueAttributes( pDoc->GetModel(), Set );

    ZBPropertyAttributes PropAttributes;

    // Starts with the wizard to choose the directory to export the model
    ZVPublishModel PublishModel( &PropAttributes, &Set, IniFilename );

    if ( PublishModel.Choose() == FALSE )
    {
        return false;
    }

    if ( PublishModel.GetDirectory().IsEmpty() )
    {
        return false;
    }

    CWaitCursor cursor;
    CDC* pDC = pView->GetDC();

    // JMR-MODIF - Le 1er juillet 2005 - Supprimé l'option permettant de choisir un chemin relatif ou absolu pour la
    // génération des pages HTML. Dorénavant, toutes les pages sont relatives (Système Web), donc on force le 4ème
    // paramètre de ModelInfo à false.
    // JMR-MODIF - Le 4 juillet 2005 - Ajouté le paramètre 5 pour la prise en charge du rapport Conceptor.
    // JMR-MODIF - Le 6 mars 2006 - Ajouté le paramètre 6 pour la prise en charge du rapport processus.
    // JMR-MODIF - Le 16 janvier 2007 - Ajouté le paramètre 7 pour la prise en charge du livre des règles.
    ZBInfoModelGraphicGeneration ModelInfo( pDoc->GetModel(),
                                            pView->GetModelController(),
                                            PublishModel.GetDirectory(),
                                            false,
                                            PublishModel.GetPublishConceptor(),
                                            PublishModel.GetPublishProcess(),
                                            PublishModel.GetPublishRuleBook(),
                                            PublishModel.GetImageFilename(),
                                            PublishModel.GetHyperLink(),
                                            pDC,
                                            ZAGlobal::GetServer() );

    // Sets the new language for generation
    ZBResourceManager::ChangeLanguage( PublishModel.GetLanguage() );

    ZUModelGenerateImageFiles ModelGen( pDoc->GetModel(),
                                        &ModelInfo,
                                        &PropAttributes );

    ModelGen.Navigate();

    // Dom: 04/2002
    // Don't forget to release the dc
    pView->ReleaseDC( pDC );

    // JMR-MODIF - Le 28 février 2006 - La réattribution du langage d'origine ne se fait plus ici.
    // Change back the resource language
//    ZBResourceManager::ChangeLanguage( pDoc->GetLanguage() );

    // JMR-MODIF - Le 4 juillet 2005 - Mise à jour des données concernant la publication des rapports.
    // JMR-MODIF - Le 6 mars 2006 - Modification de l'infrastructure pour la gestion des rapports processus.
    if ( m_pReportInfo != NULL )
    {
        m_pReportInfo->Directory                = PublishModel.GetDirectory();

        if ( PublishModel.GetPublishConceptor() == true )
        {
            m_pReportInfo->DoExportConceptorReport    = TRUE;
            m_pReportInfo->DoIncludeDetails            = ( PublishModel.GetPublishConceptorDetails() )         ? TRUE : FALSE;
            m_pReportInfo->DoIncludeDeliverables    = ( PublishModel.GetPublishConceptorDeliverables() ) ? TRUE : FALSE;
        }
        else
        {
            m_pReportInfo->DoExportConceptorReport    = FALSE;
            m_pReportInfo->DoIncludeDetails            = FALSE;
            m_pReportInfo->DoIncludeDeliverables    = FALSE;
        }

        if ( PublishModel.GetPublishProcess() == true )
        {
            m_pReportInfo->DoExportProcessReport    = TRUE;
            m_pReportInfo->Attributes                = PropAttributes;
        }
        else
        {
            m_pReportInfo->DoExportProcessReport    = FALSE;
        }

        // JMR-MODIF - Le 14 mars 2006 - Force la génération du rapport Prestations.
        m_pReportInfo->DoExportPrestationsReport = TRUE;

        // JMR-MODIF - Le 14 janvier 2006 - Ajout du code de gestion pour le livre des règles.
        if ( PublishModel.GetPublishRuleBook() == true )
        {
            m_pReportInfo->DoExportRuleBook = TRUE;
        }
        else
        {
            m_pReportInfo->DoExportRuleBook = FALSE;
        }

        // If the visualization is required
        if ( PublishModel.GetVisualizeResult() )
        {
            m_pReportInfo->IndexName        = ModelGen.GetIndexHtmlFilename();
            m_pReportInfo->DoLaunchBrowser    = TRUE;
        }
        else
        {
            m_pReportInfo->IndexName        = _T( "" );
            m_pReportInfo->DoLaunchBrowser    = FALSE;
        }
    }

    return true;
}

// Cette fonction Initialise l'exécuteur de fichiers avec le nom de fichier HTML, puis démarre le browser.
void ZUPublishModelToHTML::LaunchBrowser( CString Index )
{
    ZUFileLauncher FileLauncher( Index, FLMopen );
    FileLauncher.Launch();
}
