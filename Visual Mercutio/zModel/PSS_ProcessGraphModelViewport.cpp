/****************************************************************************
 * ==> PSS_ProcessGraphModelViewport ---------------------------------------*
 ****************************************************************************
 * Description : Provides a graphic process model viewport                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessGraphModelViewport.h"

// processsoft
#include "zBaseLib\PSS_File.h"
#include "PSS_ProcessGraphModelController.h"
#include "PSS_ProcessGraphModelView.h"
#include "PSS_ProcessGraphModelMdl.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------------
// PSS_ProcessGraphModelViewport
//---------------------------------------------------------------------------
PSS_ProcessGraphModelViewport::PSS_ProcessGraphModelViewport()
{}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelViewport::~PSS_ProcessGraphModelViewport()
{
    m_pModel = NULL;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelViewport::SizeVp(PSS_DocumentPageSetup* pPageSetup)
{
    if (!pPageSetup)
        return;

    SetMapMode(MM_ANISOTROPIC);

    CODRuler* pRuler = GetRuler();
    ASSERT(pRuler);

    // set the right units for the ruler
    pRuler->SetUnitOfMeasure(OD_CENTIMETERS);

    CODMeasure gridSpacing(OD_CENTIMETERS, 0.2f);
    SetHorizontalGridSpacing(gridSpacing);
    SetVerticalGridSpacing(gridSpacing);

    // get the model
    CODModel* pModel = GetCanvasModel();

    if (pModel)
    {
        CODPageSettings& pageSettings = pModel->GetPageSettings();

        // set the model page settings to the paper size and orientation
        pageSettings.SetPaperOrientation(pPageSetup->GetOrientation());
        pageSettings.SetPaperSize(pPageSetup->GetStandardSize());

        UpdatePageLook(pPageSetup);

        OnUpdateMappingMode();
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelViewport::UpdatePageLook(PSS_DocumentPageSetup* PageSetup)
{
    // get the model
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (pModel)
    {
        // origin is initially [0, 0]
        SetOrigin(0, 0);
        SetLogOrigin(0, 0);

        CalcPageDimensions();

        CSize pageDim = GetPageDimensions();

        // if no printer installed, or if the paper size isn't recognized, configure the page dimensions
        // with the default values
        if (!PageSetup->CanPrint())
            pageDim = PageSetup->GetDefaultPageSize(CRect(11, 32, 11, 32));

        // set the model size according to the page dimension
        pModel->SetSize(pageDim.cx, pageDim.cy);

        // resize the viewport to the model size
        SizeToModel();

        SetExtents(pageDim.cx, pageDim.cy);
        SetLogExtents(pageDim.cx, pageDim.cy);

        SetVirtualOrigin(0, 0);
        SetVirtualSize(pageDim.cx, pageDim.cy);

        UpdateAll();
    }
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelMdl* PSS_ProcessGraphModelViewport::GetModel()
{
    return dynamic_cast<PSS_ProcessGraphModelMdl*>(GetCanvasModel());
}
//---------------------------------------------------------------------------
PSS_ProcessGraphModelController* PSS_ProcessGraphModelViewport::GetModelController()
{
    return dynamic_cast<PSS_ProcessGraphModelController*>(GetController());
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelViewport::SetRuler(const CODRuler& ruler)
{
    CODRuler* pRuler = GetRuler();

    if (pRuler)
    {
        pRuler->SetUnitOfMeasure(ruler.GetUnitOfMeasure());

        CODMeasure logXUnit;
        CODMeasure logYUnit;
        const_cast<CODRuler&>(ruler).GetLogicalUnitMeasure(logXUnit, logYUnit);

        if (float(logXUnit) || float(logYUnit))
            pRuler->SetLogicalUnitMeasure(logXUnit, logYUnit);

        CODMeasure scaleFrom;
        CODMeasure scaleTo;
        const_cast<CODRuler&>(ruler).GetMeasurementScale(scaleFrom, scaleTo);

        if (float(scaleFrom) || float(scaleTo))
            pRuler->SetMeasurementScale(scaleFrom, scaleTo);
    }
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelViewport::SetPageUnits(const ZBPageUnits& pageUnits)
{
    CODRuler* pRuler = GetRuler();

    if (pRuler)
    {
        pRuler->SetUnitOfMeasure(pageUnits.GetUnitOfMeasure());

        CODMeasure logXUnit;
        CODMeasure logYUnit;
        const_cast<ZBPageUnits&>(pageUnits).GetLogicalUnitMeasure(logXUnit, logYUnit);

        if (float(logXUnit) || float(logYUnit))
            pRuler->SetLogicalUnitMeasure(logXUnit, logYUnit);

        CODMeasure scaleFrom;
        CODMeasure scaleTo;
        const_cast<ZBPageUnits&>(pageUnits).GetMeasurementScale(scaleFrom, scaleTo);

        if (float(scaleFrom) || float(scaleTo))
            pRuler->SetMeasurementScale(scaleFrom, scaleTo);
    }
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelViewport::AssignNewController(PSS_ProcessGraphModelController* pCtlr,
                                                        PSS_ProcessGraphModelMdl*        pModel)
{
    if (pCtlr)
    {
        if (m_pCtlr && m_bAutoDelCtlr)
        {
            // remove the listener
            m_pCtlr->RemoveListener(this);
            delete m_pCtlr;
        }

        // assign the new controller to the viewport
        m_pCtlr = pCtlr;

        // assign the new model to the controller
        m_pCtlr->SetModel(pModel);

        // create the controler
        m_pCtlr->Create(m_pWnd, this);

        // add a listener to this viewport
        m_pCtlr->AddListener(this);

        // set the controller
        pModel->SetController(static_cast<CODController*>(m_pCtlr));

        m_bAutoDelCtlr = TRUE;

        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
bool PSS_ProcessGraphModelViewport::ExportModelToImageFile(const CString& fileName, CDC& dc)
{
    SECImage* pImage = CreateImageObjectFromFileExtension(fileName);

    if (pImage)
    {
        DrawImage(pImage, &dc);

        BOOL result;

        TRY
        {
            result = pImage->SaveImage(fileName);
        }
        CATCH (CFileException, e)
        {
            result = FALSE;
        }
        END_CATCH

        delete pImage;
        return result;
    }

    return false;
}
//---------------------------------------------------------------------------
SECImage* PSS_ProcessGraphModelViewport::CreateImageObjectFromFileExtension(const CString& fileName)
{
    PSS_File                  file(fileName);
    std::unique_ptr<SECImage> pImage;

    if (!file.GetFileExt().CompareNoCase(_T(".gif")))
        pImage.reset(new SECGif());
    else
    if (!file.GetFileExt().CompareNoCase(_T(".dib")))
        pImage.reset(new SECDib());
    else
    if (!file.GetFileExt().CompareNoCase(_T(".jpg")))
        pImage.reset(new SECJpeg());
    else
    if (!file.GetFileExt().CompareNoCase(_T(".pcx")))
        pImage.reset(new SECPcx());
    else
    if (!file.GetFileExt().CompareNoCase(_T(".tga")))
        pImage.reset(new SECTarga());
    else
    if (!file.GetFileExt().CompareNoCase(_T(".tif")))
        pImage.reset(new SECTiff());

    return pImage.release();
}
//---------------------------------------------------------------------------
SECImage* PSS_ProcessGraphModelViewport::LoadImageFromFile(const CString& fileName)
{
    PSS_File file(fileName);

    if (file.Exist())
    {
        std::unique_ptr<SECImage> pImage(CreateImageObjectFromFileExtension(fileName));

        if (pImage.get() && pImage->LoadImage(fileName))
            return pImage.release();
    }

    return NULL;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelViewport::OnInitialUpdate()
{
    CODViewport::OnInitialUpdate();

    PSS_ProcessGraphModelController* pModelCtrl = GetModelController();

    if (pModelCtrl)
        pModelCtrl->OnInitialUpdate();
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelViewport::OnUpdate(IMvcSubject* pSubject, IMvcMessage* pMsg)
{
    CODViewport::OnUpdate(pSubject, pMsg);
}
//---------------------------------------------------------------------------
BOOL PSS_ProcessGraphModelViewport::CreateController()
{
    PSS_ProcessGraphModelMdl* pModel = GetModel();

    if (pModel)
    {
        if (m_pCtlr && m_bAutoDelCtlr)
            delete m_pCtlr;

        m_pCtlr = pModel->CreateController(this);

        // set the controller
        pModel->SetController(static_cast<CODController*>(m_pCtlr));
        m_bAutoDelCtlr = TRUE;

        return TRUE;
    }

    return FALSE;
}
//---------------------------------------------------------------------------
void PSS_ProcessGraphModelViewport::CenterOrigin()
{
    const CSize logSize(GetLogSize());
    CPoint      logOrgPt;

    // assume the logical origin is within the bounds of the virtual space
    logOrgPt.x = 0 - logSize.cx / 2;
    logOrgPt.y = 0 - logSize.cy / 2;

    SetLogOrigin(logOrgPt.x, logOrgPt.y);

    Invalidate();
}
//---------------------------------------------------------------------------
