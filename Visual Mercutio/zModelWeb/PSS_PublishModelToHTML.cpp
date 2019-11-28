/****************************************************************************
 * ==> PSS_PublishModelToHTML ----------------------------------------------*
 ****************************************************************************
 * Description : Publishes a model to html file                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_PublishModelToHTML.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zBaseLib\PSS_FileLauncher.h"
#include "zResMgr\PSS_ResourceManager.h"
#include "zProperty\ZBPropertyAttributes.h"
#include "zModel\ProcGraphModelMdl.h"
#include "zModel\PSS_ProcessGraphModelController.h"
#define _ZMODELEXPORT
#include "zModel\ProcGraphModelDoc.h"
#include "zModel\ProcGraphModelView.h"
#undef _ZMODELEXPORT
#include "zModel\ZUDynamicAttributesManipulator.h"
#include "zModel\ZBInfoModelGraphicGeneration.h"
#include "PSS_ModelGenerateImageFiles.h"
#include "PSS_PublishModel.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_PublishModelToHTML
//---------------------------------------------------------------------------
PSS_PublishModelToHTML::PSS_PublishModelToHTML()
{}
//---------------------------------------------------------------------------
PSS_PublishModelToHTML::~PSS_PublishModelToHTML()
{}
//---------------------------------------------------------------------------
bool PSS_PublishModelToHTML::ExportModelToHTMLFile(ZDProcessGraphModelDoc*  pDoc,
                                                   ZIProcessGraphModelView* pView,
                                                   ZUPublishReportInfo*     pReportInfo,
                                                   const CString&           iniFileName)
{
    if (!pDoc || !pView)
        return false;

    ZBPropertySet propSet;
    ZUDynamicAttributesManipulator::ExtractUniqueAttributes(pDoc->GetModel(), propSet);

    ZBPropertyAttributes propAttributes;

    // start with the wizard to choose the directory to export the model
    PSS_PublishModel publishModel(&propAttributes, &propSet, iniFileName);

    if (!publishModel.SelectDir())
        return false;

    if (publishModel.GetDir().IsEmpty())
        return false;

    CWaitCursor cursor;
    CDC*        pDC = NULL;

    try
    {
        pDC = pView->GetDC();

        ZBInfoModelGraphicGeneration modelInfo(pDoc->GetModel(),
                                               pView->GetModelController(),
                                               publishModel.GetDir(),
                                               false,
                                               publishModel.GetPublishConceptor(),
                                               publishModel.GetPublishProcess(),
                                               publishModel.GetPublishRuleBook(),
                                               publishModel.GetImageFileName(),
                                               publishModel.GetHyperLink(),
                                               pDC,
                                               PSS_Global::GetServer());

        // set the new language for generation
        PSS_ResourceManager::ChangeLanguage(publishModel.GetLanguage());

        PSS_ModelGenerateImageFiles modelGen(pDoc->GetModel(), &modelInfo, &propAttributes);

        modelGen.Navigate();

        // don't forget to release the dc
        pView->ReleaseDC(pDC);
        pDC = NULL;

        if (pReportInfo)
        {
            pReportInfo->Directory = publishModel.GetDir();

            if (publishModel.GetPublishConceptor())
            {
                pReportInfo->DoExportConceptorReport = TRUE;
                pReportInfo->DoIncludeDetails        = publishModel.GetPublishConceptorDetails()      ? TRUE : FALSE;
                pReportInfo->DoIncludeDeliverables   = publishModel.GetPublishConceptorDeliverables() ? TRUE : FALSE;
            }
            else
            {
                pReportInfo->DoExportConceptorReport = FALSE;
                pReportInfo->DoIncludeDetails        = FALSE;
                pReportInfo->DoIncludeDeliverables   = FALSE;
            }

            if (publishModel.GetPublishProcess())
            {
                pReportInfo->DoExportProcessReport = TRUE;
                pReportInfo->Attributes            = propAttributes;
            }
            else
                pReportInfo->DoExportProcessReport = FALSE;

            pReportInfo->DoExportPrestationsReport = TRUE;
            pReportInfo->DoExportRuleBook          = publishModel.GetPublishRuleBook() ? TRUE : FALSE;

            // if the visualization is required
            if (publishModel.GetVisualizeResult())
            {
                pReportInfo->IndexName       = modelGen.GetIndexHtmlFileName();
                pReportInfo->DoLaunchBrowser = TRUE;
            }
            else
            {
                pReportInfo->IndexName       = _T("");
                pReportInfo->DoLaunchBrowser = FALSE;
            }
        }
    }
    catch (...)
    {
        if (pDC)
            pView->ReleaseDC(pDC);

        throw;
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_PublishModelToHTML::LaunchBrowser(const CString& index)
{
    PSS_FileLauncher fileLauncher(index, PSS_FileLauncher::IE_FM_Open);
    fileLauncher.Launch();
}
//---------------------------------------------------------------------------
