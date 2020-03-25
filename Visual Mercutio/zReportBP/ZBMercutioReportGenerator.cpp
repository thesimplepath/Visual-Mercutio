// ZBMercutioReportGenerator.cpp: implementation of the ZBMercutioReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBMercutioReportGenerator.h"

#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModelBP\PSS_ProcessGraphModelMdlBP.h"
#include "zReport\PSS_GridDocument.h"

#include "ZUGridMercutioRepProcedureNavigation.h"
#include "ZUGridMercutioRepDeliverableNavigation.h"

#include "zBaseLib\PSS_Global.h"

#include "zReport\zReportRes.h"
#include "zReportBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 29 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(ZBMercutioReportGenerator, ZBModelBPReportGenerator, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBMercutioReportGenerator::ZBMercutioReportGenerator(PSS_GridDocument*            pDoc        /*= NULL*/,
                                                     PSS_ProcessGraphModelMdlBP*    pModel        /*= NULL*/,
                                                     PSS_ProcessGraphModelDoc*    pSourceDoc    /*= NULL*/)
    : ZBModelBPReportGenerator(pDoc, pModel, pSourceDoc)
{
    // Store the model name
    if (m_pModel)
    {
        m_SubModelName = m_pModel->GetAbsolutePath();
    }

    // Fill the tab name array
    FillTabArray();
}

ZBMercutioReportGenerator::~ZBMercutioReportGenerator()
{}

void ZBMercutioReportGenerator::Initialize(PSS_GridDocument*                pDoc,
                                           PSS_ProcessGraphModelMdlBP*    pModel,
                                           PSS_ProcessGraphModelDoc*        pSourceDoc)
{
    // Store the model name
    if (m_pModel)
    {
        m_SubModelName = m_pModel->GetAbsolutePath();
    }

    // Call the base class
    ZBModelBPReportGenerator::Initialize(pDoc, pModel, pSourceDoc);
}

// To fill the tab array, use a visitor class 
void ZBMercutioReportGenerator::FillTabArray()
{
    // if no doc nor model defined. nothing to do.
    if (!m_pDoc || !m_pModel)
    {
        return;
    }

    // First, remove all elements
    m_TabNameArray.RemoveAll();

    // First tab is for the procedures
    CString s;
    s.LoadString(IDS_PROCEDURES_TAB);
    m_TabNameArray.Add(s);

    // Second tab is for the deliverables
    s.LoadString(IDS_DELIVERABLES_TAB);
    m_TabNameArray.Add(s);
}

bool ZBMercutioReportGenerator::FillGrid(CGXGridCore& GridCore, size_t Index)
{
    // Default size
    GridCore.SetRowCount(60);        // 60 rows
    GridCore.SetColCount(15);        // 15 columns

    switch (Index)
    {
        case 0:
        {
            return FillGridProcedures(GridCore, Index);
        }

        case 1:
        {
            return FillGridDeliverables(GridCore, Index);
        }
    }

    return false;
}

bool ZBMercutioReportGenerator::FillGridProcedures(CGXGridCore& GridCore, size_t Index)
{
    // Check the index validity
    if (Index >= (size_t)m_TabNameArray.GetSize())
    {
        return false;
    }

    if (!m_pModel)
    {
        return false;
    }

    // Construct the output stream grid object
    PSS_OStreamGrid ostream(&GridCore);

    // Construct the navigation grid for procedure
    ZUGridMercutioRepProcedureNavigation Navigation(m_pModel, static_cast<void*>(&ostream));

    // Now navigate through process symbols
    return Navigation.Navigate();
}

bool ZBMercutioReportGenerator::FillGridDeliverables(CGXGridCore& GridCore, size_t Index)
{
    // Check the index validity
    if (Index >= (size_t)m_TabNameArray.GetSize())
    {
        return false;
    }

    if (!m_pModel)
    {
        return false;
    }

    // Construct the output stream grid object
    PSS_OStreamGrid ostream(&GridCore);

    // Construct the navigation grid for deliverables
    ZUGridMercutioRepDeliverableNavigation Navigation(m_pModel, static_cast<void*>(&ostream));

    // Now navigate through process symbols
    return Navigation.Navigate();
}

const CString ZBMercutioReportGenerator::GetReportTitle() const
{
    // Build the title function of the model
    CString s;

    if (m_pDoc)
    {
        s = m_pDoc->GetTitle();
    }

    CString ReportType;
    ReportType.LoadString(IDS_MERCUTIO_RPT_T);

    s += _T(" [");
    s += ReportType;
    s += _T(" : ");

    if (m_pModel)
    {
        s += m_pModel->GetModelName();
    }
    else
    {
        s += _T("???");
    }

    s += _T(" ]");

    return s;
}

/////////////////////////////////////////////////////////////////////////////
// ZBMercutioReportGenerator diagnostics

#ifdef _DEBUG
void ZBMercutioReportGenerator::AssertValid() const
{
    ZBModelBPReportGenerator::AssertValid();
}

void ZBMercutioReportGenerator::Dump(CDumpContext& dc) const
{
    ZBModelBPReportGenerator::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBMercutioReportGenerator serialization

void ZBMercutioReportGenerator::OnPostRead(CArchive& ar)
{
    if (m_pSourceDoc == NULL && !m_FileName.IsEmpty())
    {
        m_pSourceDoc = new PSS_ProcessGraphModelDoc();

        // If the document is valid, assign the right model pointer
        if (m_pSourceDoc                                &&
            m_pSourceDoc->ReadFromFile(m_FileName) &&
            m_pSourceDoc->GetModel() &&
            ISA(m_pSourceDoc->GetModel(), PSS_ProcessGraphModelMdlBP))
        {
            m_pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pSourceDoc->GetModel());

            if (m_SubModelName)
            {
                m_pModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(m_pModel->FindModelFromPath(m_SubModelName));
            }

            m_InChargeOfClosingFile = true;
        }
    }
}

void ZBMercutioReportGenerator::Serialize(CArchive& ar)
{
    ZBModelBPReportGenerator::Serialize(ar);

    // Serialize the sub model name
    if (ar.IsStoring())
    {
        ar << m_SubModelName;
    }
    else
    {
        ar >> m_SubModelName;
    }
}
