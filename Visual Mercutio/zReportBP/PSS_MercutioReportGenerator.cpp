/****************************************************************************
 * ==> PSS_MercutioReportGenerator -----------------------------------------*
 ****************************************************************************
 * Description : Provides a Mercutio report generator                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_MercutioReportGenerator.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModelBP\PSS_ProcessGraphModelMdlBP.h"
#include "zReport\PSS_GridDocument.h"
#include "ZUGridMercutioRepProcedureNavigation.h"
#include "ZUGridMercutioRepDeliverableNavigation.h"

// resources
#include "zReport\zReportRes.h"
#include "zReportBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// Serialization
//---------------------------------------------------------------------------
IMPLEMENT_SERIAL(PSS_MercutioReportGenerator, PSS_ModelBPReportGenerator, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_MercutioReportGenerator
//---------------------------------------------------------------------------
PSS_MercutioReportGenerator::PSS_MercutioReportGenerator(PSS_GridDocument*           pDoc,
                                                         PSS_ProcessGraphModelMdlBP* pModel,
                                                         PSS_ProcessGraphModelDoc*   pSourceDoc) :
    PSS_ModelBPReportGenerator(pDoc, pModel, pSourceDoc)
{
    // keep the model name
    if (m_pModel)
        m_SubModelName = m_pModel->GetAbsolutePath();

    // fill the tab name array
    FillTabArray();
}
//---------------------------------------------------------------------------
PSS_MercutioReportGenerator::~PSS_MercutioReportGenerator()
{}
//---------------------------------------------------------------------------
void PSS_MercutioReportGenerator::Initialize(PSS_GridDocument*           pDoc,
                                             PSS_ProcessGraphModelMdlBP* pModel,
                                             PSS_ProcessGraphModelDoc*   pSourceDoc)
{
    // store the model name
    if (m_pModel)
        m_SubModelName = m_pModel->GetAbsolutePath();

    PSS_ModelBPReportGenerator::Initialize(pDoc, pModel, pSourceDoc);
}
//---------------------------------------------------------------------------
const CString PSS_MercutioReportGenerator::GetReportTitle() const
{
    // build the model title function
    CString str;

    if (m_pDoc)
        str = m_pDoc->GetTitle();

    CString reportType;
    reportType.LoadString(IDS_MERCUTIO_RPT_T);

    str += _T(" [");
    str += reportType;
    str += _T(" : ");

    if (m_pModel)
        str += m_pModel->GetModelName();
    else
        str += _T("???");

    str += _T(" ]");

    return str;
}
//---------------------------------------------------------------------------
bool PSS_MercutioReportGenerator::FillGrid(CGXGridCore& gridCore, std::size_t index)
{
    // default size, 60 rows * 15 columns
    gridCore.SetRowCount(60);
    gridCore.SetColCount(15);

    switch (index)
    {
        case 0: return FillGridProcedures  (gridCore, index);
        case 1: return FillGridDeliverables(gridCore, index);
    }

    return false;
}
//---------------------------------------------------------------------------
void PSS_MercutioReportGenerator::Serialize(CArchive& ar)
{
    PSS_ModelBPReportGenerator::Serialize(ar);

    // serialize the sub model name
    if (ar.IsStoring())
        ar << m_SubModelName;
    else
        ar >> m_SubModelName;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_MercutioReportGenerator::AssertValid() const
    {
        PSS_ModelBPReportGenerator::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_MercutioReportGenerator::Dump(CDumpContext& dc) const
    {
        PSS_ModelBPReportGenerator::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_MercutioReportGenerator::OnPostRead(CArchive& ar)
{
    if (!m_pSourceDoc && !m_FileName.IsEmpty())
    {
        m_pSourceDoc = new PSS_ProcessGraphModelDoc();

        // if the document is valid, assign the model
        if (m_pSourceDoc && m_pSourceDoc->ReadFromFile(m_FileName))
        {
            PSS_ProcessGraphModelMdlBP* pGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pSourceDoc->GetModel());

            if (pGraphModel)
            {
                if (m_SubModelName)
                    m_pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pGraphModel->FindModelFromPath(m_SubModelName));
                else
                    m_pModel = pGraphModel;

                m_InChargeOfClosingFile = true;
            }
        }
    }
}
//---------------------------------------------------------------------------
void PSS_MercutioReportGenerator::FillTabArray()
{
    // if no doc or model defined, nothing to do
    if (!m_pDoc || !m_pModel)
        return;

    // remove all elements
    m_TabNameArray.RemoveAll();

    CString str;

    // first tab is for the procedures
    str.LoadString(IDS_PROCEDURES_TAB);
    m_TabNameArray.Add(str);

    // second tab is for the deliverables
    str.LoadString(IDS_DELIVERABLES_TAB);
    m_TabNameArray.Add(str);
}
//---------------------------------------------------------------------------
bool PSS_MercutioReportGenerator::FillGridProcedures(CGXGridCore& gridCore, std::size_t index)
{
    // check the index validity
    if (index >= std::size_t(m_TabNameArray.GetSize()))
        return false;

    if (!m_pModel)
        return false;

    // build the output stream grid object
    PSS_OStreamGrid ostream(&gridCore);

    // build the navigation grid for procedure
    ZUGridMercutioRepProcedureNavigation navigation(m_pModel, static_cast<void*>(&ostream));

    // navigate through the process symbols
    return navigation.Navigate();
}
//---------------------------------------------------------------------------
bool PSS_MercutioReportGenerator::FillGridDeliverables(CGXGridCore& gridCore, std::size_t index)
{
    // check the index validity
    if (index >= std::size_t(m_TabNameArray.GetSize()))
        return false;

    if (!m_pModel)
        return false;

    // build the output stream grid object
    PSS_OStreamGrid ostream(&gridCore);

    // build the navigation grid for deliverables
    ZUGridMercutioRepDeliverableNavigation navigation(m_pModel, static_cast<void*>(&ostream));

    // navigate through the process symbols
    return navigation.Navigate();
}
//---------------------------------------------------------------------------
