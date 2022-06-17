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
#include "zProperty\PSS_PropertyAttributes.h"
#include "zModel\PSS_ProcessGraphModelMdl.h"
#include "zModel\PSS_ProcessGraphModelController.h"
#define _ZMODELEXPORT
    #include "zModel\PSS_ProcessGraphModelDoc.h"
    #include "zModel\PSS_ProcessGraphModelView.h"
#undef _ZMODELEXPORT
#include "zModel\PSS_DynamicAttributesManipulator.h"
#include "zModel\PSS_InfoModelGraphicGeneration.h"
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
bool PSS_PublishModelToHTML::ExportModelToHTMLFile(PSS_ProcessGraphModelDoc*  pDoc,
                                                   PSS_ProcessGraphModelView* pView,
                                                   PSS_PublishReportInfo*     pReportInfo,
                                                   const CString&             iniFileName)
{
    if (!pDoc || !pView)
        return false;

    PSS_Properties::IPropertySet propSet;
    PSS_DynamicAttributesManipulator::ExtractUniqueAttributes(pDoc->GetModel(), propSet);

    PSS_PropertyAttributes propAttributes;

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

        PSS_InfoModelGraphicGeneration modelInfo(pDoc->GetModel(),
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
            pReportInfo->m_Directory = publishModel.GetDir();

            if (publishModel.GetPublishConceptor())
            {
                pReportInfo->m_DoExportConceptorReport = TRUE;
                pReportInfo->m_DoIncludeDetails        = publishModel.GetPublishConceptorDetails();
                pReportInfo->m_DoIncludeDeliverables   = publishModel.GetPublishConceptorDeliverables();
            }
            else
            {
                pReportInfo->m_DoExportConceptorReport = FALSE;
                pReportInfo->m_DoIncludeDetails        = FALSE;
                pReportInfo->m_DoIncludeDeliverables   = FALSE;
            }

            if (publishModel.GetPublishProcess())
            {
                pReportInfo->m_DoExportProcessReport = TRUE;
                pReportInfo->m_Attributes            = propAttributes;
            }
            else
                pReportInfo->m_DoExportProcessReport = FALSE;

            pReportInfo->m_DoExportPrestationsReport = TRUE;
            pReportInfo->m_DoExportRuleBook          = publishModel.GetPublishRuleBook();

            // if the visualization is required
            if (publishModel.GetVisualizeResult())
            {
                pReportInfo->m_IndexName       = modelGen.GetIndexHtmlFileName();
                pReportInfo->m_DoLaunchBrowser = TRUE;
            }
            else
            {
                pReportInfo->m_IndexName       = _T("");
                pReportInfo->m_DoLaunchBrowser = FALSE;
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
    PSS_FileLauncher fileLauncher(index, PSS_FileLauncher::IEMode::IE_FM_Open);
    fileLauncher.Launch();
}
//---------------------------------------------------------------------------
