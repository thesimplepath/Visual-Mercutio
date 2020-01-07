// ZBConceptorReportGenerator.cpp: implementation of the ZBConceptorReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBConceptorReportGenerator.h"

#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModelBP\ProcGraphModelMdlBP.h"
#include "zModel\ZDProcessGraphPage.h"
#include "zReport\ZDGridDoc.h"
#include "zModel\PSS_UserGroupEntity.h"

#include "zModelBP\ZBBPStartSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"
#include "zModelBP\ZBBPProcedureSymbol.h"

#include "zModelBP\ZUExtractProcessName.h"
#include "ZUSynthesisNavigation.h"
#include "ZUProcessConceptorNavigation.h"

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

IMPLEMENT_SERIAL(ZBConceptorReportGenerator, ZBModelBPReportGenerator, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBConceptorReportGenerator::ZBConceptorReportGenerator(ZDGridDocument*                pDoc                    /*= NULL*/,
                                                       ZDProcessGraphModelMdlBP*    pModel                    /*= NULL*/,
                                                       PSS_ProcessGraphModelDoc*        pSourceDoc                /*= NULL*/,
                                                       BOOL                        bIncludeSynthesis        /*= TRUE*/,
                                                       BOOL                        bIncludeDetail            /*= TRUE*/,
                                                       BOOL                        bIncludeDeliverables    /*= TRUE*/)
    : ZBModelBPReportGenerator(pDoc, pModel, pSourceDoc)
{
    m_IncludeSynthesis = bIncludeSynthesis;
    m_IncludeDetail = bIncludeDetail;
    m_IncludeDeliverables = bIncludeDeliverables;

    // Fill the tab name array
    FillTabArray();
}

ZBConceptorReportGenerator::~ZBConceptorReportGenerator()
{}

void ZBConceptorReportGenerator::Initialize(ZDGridDocument*            pDoc,
                                            ZDProcessGraphModelMdlBP*    pModel,
                                            PSS_ProcessGraphModelDoc*    pSourceDoc,
                                            BOOL                        bIncludeSynthesis        /*= TRUE*/,
                                            BOOL                        bIncludeDetail            /*= TRUE*/,
                                            BOOL                        bIncludeDeliverables    /*= TRUE*/)
{
    m_IncludeSynthesis = bIncludeSynthesis;
    m_IncludeDetail = bIncludeDetail;
    m_IncludeDeliverables = bIncludeDeliverables;

    // Call the base class
    ZBModelBPReportGenerator::Initialize(pDoc, pModel, pSourceDoc);
}

void ZBConceptorReportGenerator::RemoveAllData()
{
    m_ProcessNameArray.RemoveAll();
    m_ModelArray.RemoveAll();
    m_UnitCommentArray.RemoveAll();
}

// To fill the tab array, use a visitor class 
void ZBConceptorReportGenerator::FillTabArray()
{
    // if no doc nor model defined. nothing to do.
    if (!m_pDoc || !m_pModel)
    {
        return;
    }

    // First, remove all elements
    m_TabNameArray.RemoveAll();

    // Load all process in the process name array
    // First, remove all elements
    RemoveAllData();

    FillTabUnitGroup(m_pModel->GetMainUserGroup());

    // Fill the array with process name
    ZUExtractProcessName ExtractProcessName(m_pModel);

    // Add all models to the model array
    ExtractProcessName.FillProcessNameArray(&m_ProcessNameArray);

    int CountProcess = m_ProcessNameArray.GetSize();

    for (int Idx = 0; Idx < CountProcess; ++Idx)
    {
        // Find the right process, function of the model name
        CString                      processName = m_ProcessNameArray.GetAt(Idx);
        PSS_ProcessGraphModelMdl*    pModel = m_pModel->FindModel(processName, true); // In case sensitive

        if (!pModel)
        {
            // Error 
            m_ModelArray.Add(NULL);
            continue;
        }

        m_ModelArray.Add(pModel);
    }

    m_GrayStyle.SetTextColor(defCOLOR_WHITE)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(9).SetBold(FALSE))
        .SetInterior(defCOLOR_GRAY);

    m_BlueStyle.SetTextColor(defCOLOR_BLACK)
        .SetInterior(RGB(0, 128, 255));

    m_OrangeStyle.SetTextColor(defCOLOR_BLACK)
        .SetInterior(RGB(250, 128, 64));
}

void ZBConceptorReportGenerator::FillTabUnitGroup(PSS_UserGroupEntity* pGroup)
{
    m_TabNameArray.Add(pGroup->GetEntityName());
    m_UnitCommentArray.Add((pGroup->GetEntityDescription().IsEmpty()) ? _T(" ") : pGroup->GetEntityDescription());

    if (pGroup->ContainEntity())
    {
        int Count = pGroup->GetEntityCount();

        for (int i = 0; i < Count; ++i)
        {
            PSS_UserEntity* pEntity = pGroup->GetEntityAt(i);

            if (!pEntity)
            {
                continue;
            }

            if (ISA(pEntity, PSS_UserGroupEntity))
            {
                FillTabUnitGroup(dynamic_cast<PSS_UserGroupEntity*>(pEntity));
            }
        }
    }
}

// Cette fonction sert à remplir les données d'une feuille, représentée par la variable Index, du rapport.
bool ZBConceptorReportGenerator::FillGrid(CGXGridCore& GridCore, size_t Index)
{
    // Default size (60 rows * 15 columns)
    GridCore.SetRowCount(g_NbRows);
    GridCore.SetColCount(g_NbColumns);

    ZBOStreamGrid ostream(&GridCore);

    CGXStyle Style;

    Style.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(11).SetBold(TRUE))
        .SetHorizontalAlignment(DT_CENTER)
        .SetInterior(defCOLOR_WHITE);

    // Initialize the black border
    m_BlackBorderStyle.SetBorders(gxBorderAll, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_LeftOnlyBlackBorderStyle.SetBorders(gxBorderLeft, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_RightOnlyBlackBorderStyle.SetBorders(gxBorderRight, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_TopOnlyBlackBorderStyle.SetBorders(gxBorderTop, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_BottomOnlyBlackBorderStyle.SetBorders(gxBorderBottom, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));

    // Display the page header, unit name and description
    CString s;
    int left, top;

    ostream.GetCurSel(left, top);
    ostream.GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 2);

    ostream << m_TabNameArray.GetAt(Index);
    ostream << Style;
    ostream << _T("\n");

    ostream << m_UnitCommentArray.GetAt(Index);
    ostream << _T("\n\n");

    // If the synthesis is included
    if (m_IncludeSynthesis)
    {
        FillSynthesis(ostream, Index);
    }

    if (m_IncludeDetail == false)
    {
        return true;
    }

    return FillGridAllProcess(ostream, Index);
}

// Cette fonction permet de générér les en-têtes des cellules.
bool ZBConceptorReportGenerator::FillSynthesis(ZBOStreamGrid& ostream, size_t Index)
{
    // Initialize the style for header cells
    CGXStyle Style;

    Style.SetTextColor(defCOLOR_WHITE)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(12).SetBold(TRUE))
        .SetInterior(RGB(250, 128, 64));

    CGXStyle NormalStyle;

    NormalStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(9).SetBold(FALSE))
        .SetInterior(defCOLOR_WHITE);

    // Display header
    CString s = _T("");

    ostream << _T("\n\n");
    ostream << _T(" ");
    ostream << Style;
    ostream << _T("\t");

    s.LoadString(IDS_CONCEPTOR_SYNTHESYS);
    ostream << s;
    ostream << CSize(150, 30);        // Set the cell size
    ostream << Style;
    ostream << _T("\t");

    ostream << _T(" ");
    ostream << Style;
    ostream << _T("\n");

    // Initialize the style for header cells
    CGXStyle GrayStyle;

    GrayStyle.SetTextColor(defCOLOR_WHITE)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(12).SetBold(TRUE))
        .SetDraw3dFrame(gxFrameNormal)
        .SetInterior(defCOLOR_GRAY);

    // Display header
    s.LoadString(IDS_CONCEPTOR_DOMAINTOPIC);
    ostream << s;
    ostream << CSize(150, 20);        // Set the cell size
    ostream << GrayStyle;
    ostream << m_TopOnlyBlackBorderStyle;
    ostream << _T("\t");

    s.LoadString(IDS_CONCEPTOR_PROCESS);
    ostream << s;
    ostream << CSize(180, 0);        // Set the cell width only
    ostream << GrayStyle;
    ostream << m_TopOnlyBlackBorderStyle;
    ostream << _T("\t");

    s.LoadString(IDS_CONCEPTOR_PROCEDURE);
    ostream << s;
    ostream << CSize(200, 0);        // Set the cell width only
    ostream << GrayStyle;
    ostream << m_TopOnlyBlackBorderStyle;
    ostream << _T("\n");

    // Construct the synthesis for each page
    ZUSynthesisNavigation Navigation(m_pModel,
                                     static_cast<void*>(&ostream),
                                     m_pModel,
                                     _T(""),
                                     m_TabNameArray.GetAt(Index));

    // Now navigate through process symbols
    Navigation.Navigate();

    return true;
}

bool ZBConceptorReportGenerator::FillGridAllProcess(ZBOStreamGrid& ostream, size_t Index)
{
    // Construct the synthesis for each page
    ZUProcessConceptorNavigation Navigation(m_pModel,
                                            static_cast<void*>(&ostream),
                                            m_pModel,
                                            _T(""),
                                            m_TabNameArray.GetAt(Index),
                                            m_IncludeSynthesis,
                                            m_IncludeDetail,
                                            m_IncludeDeliverables);

    // Now navigate through process symbols
    Navigation.Navigate();

    // Check the number of row
    int left, top;
    ROWCOL RowCount = ostream.GetGridCore()->GetRowCount();
    ostream.GetCurSel(left, top);

    // If not enough, add 30 rows
    if ((top + 30) > (int)RowCount)
    {
        ostream.GetGridCore()->SetRowCount(RowCount + 30);
    }

    return true;
}

const CString ZBConceptorReportGenerator::GetReportTitle() const
{
    // Build the title function of the model
    CString s;

    if (m_pDoc)
    {
        s = m_pDoc->GetTitle();
    }

    CString ReportType;
    ReportType.LoadString(IDS_CONCEPTOR_RPT_T);

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
// ZBConceptorReportGenerator diagnostics

#ifdef _DEBUG
void ZBConceptorReportGenerator::AssertValid() const
{
    ZBModelBPReportGenerator::AssertValid();
}

void ZBConceptorReportGenerator::Dump(CDumpContext& dc) const
{
    ZBModelBPReportGenerator::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ZBConceptorReportGenerator serialisation

void ZBConceptorReportGenerator::OnPostRead(CArchive& ar)
{
    if (m_pSourceDoc == NULL && !m_FileName.IsEmpty())
    {
        m_pSourceDoc = new PSS_ProcessGraphModelDoc();

        // If the document is valid, assign the right model pointer
        if (m_pSourceDoc                                &&
            m_pSourceDoc->ReadFromFile(m_FileName) &&
            m_pSourceDoc->GetModel() &&
            ISA(m_pSourceDoc->GetModel(), ZDProcessGraphModelMdlBP))
        {
            m_pModel = dynamic_cast<ZDProcessGraphModelMdlBP*>(m_pSourceDoc->GetModel());
            m_InChargeOfClosingFile = true;
        }
    }
}
