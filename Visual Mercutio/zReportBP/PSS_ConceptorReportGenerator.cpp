/****************************************************************************
 * ==> PSS_ConceptorReportGenerator ----------------------------------------*
 ****************************************************************************
 * Description : Provides a Conceptor report generator                      *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ConceptorReportGenerator.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_ProcessGraphPage.h"
#include "zModel\PSS_UserGroupEntity.h"
#include "zModelBP\PSS_ProcessGraphModelMdlBP.h"
#include "zModelBP\PSS_StartSymbolBP.h"
#include "zModelBP\PSS_DeliverableLinkSymbolBP.h"
#include "zModelBP\PSS_ProcedureSymbolBP.h"
#include "zModelBP\PSS_ExtractProcessName.h"
#include "zReport\PSS_GridDocument.h"
#include "ZUSynthesisNavigation.h"
#include "PSS_ProcessConceptorNavigation.h"
#include "PSS_GridMercutioReportProcedureNavigation.h"
#include "PSS_GridMercutioReportDeliverableNavigation.h"

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
IMPLEMENT_SERIAL(PSS_ConceptorReportGenerator, PSS_ModelBPReportGenerator, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_ConceptorReportGenerator
//---------------------------------------------------------------------------
PSS_ConceptorReportGenerator::PSS_ConceptorReportGenerator(PSS_GridDocument*           pDoc,
                                                           PSS_ProcessGraphModelMdlBP* pModel,
                                                           PSS_ProcessGraphModelDoc*   pSourceDoc,
                                                           BOOL                        includeSynthesis,
                                                           BOOL                        includeDetail,
                                                           BOOL                        includeDeliverables) :
    PSS_ModelBPReportGenerator(pDoc, pModel, pSourceDoc),
    m_IncludeSynthesis(includeSynthesis),
    m_IncludeDetail(includeDetail),
    m_IncludeDeliverables(includeDeliverables)
{
    // fill the tab name array
    FillTabArray();
}
//---------------------------------------------------------------------------
PSS_ConceptorReportGenerator::~PSS_ConceptorReportGenerator()
{}
//---------------------------------------------------------------------------
void PSS_ConceptorReportGenerator::Initialize(PSS_GridDocument*           pDoc,
                                              PSS_ProcessGraphModelMdlBP* pModel,
                                              PSS_ProcessGraphModelDoc*   pSourceDoc,
                                              BOOL                        includeSynthesis,
                                              BOOL                        includeDetail,
                                              BOOL                        includeDeliverables)
{
    m_IncludeSynthesis    = includeSynthesis;
    m_IncludeDetail       = includeDetail;
    m_IncludeDeliverables = includeDeliverables;

    PSS_ModelBPReportGenerator::Initialize(pDoc, pModel, pSourceDoc);
}
//---------------------------------------------------------------------------
const CString PSS_ConceptorReportGenerator::GetReportTitle() const
{
    // build the model title function
    CString str;

    if (m_pDoc)
        str = m_pDoc->GetTitle();

    CString reportType;
    reportType.LoadString(IDS_CONCEPTOR_RPT_T);

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
bool PSS_ConceptorReportGenerator::FillGrid(CGXGridCore& gridCore, std::size_t index)
{
    // default size (60 rows * 15 columns)
    gridCore.SetRowCount(g_NbRows);
    gridCore.SetColCount(g_NbColumns);

    PSS_OStreamGrid ostream(&gridCore);

    CGXStyle style;
    style.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(11).SetBold(TRUE))
            .SetHorizontalAlignment(DT_CENTER)
            .SetInterior(defCOLOR_WHITE);

    // initialize the black border
    m_BlackBorderStyle.SetBorders          (gxBorderAll,    CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_LeftOnlyBlackBorderStyle.SetBorders  (gxBorderLeft,   CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_RightOnlyBlackBorderStyle.SetBorders (gxBorderRight,  CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_TopOnlyBlackBorderStyle.SetBorders   (gxBorderTop,    CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_BottomOnlyBlackBorderStyle.SetBorders(gxBorderBottom, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));

    // show the page header, unit name and description
    CString str;
    int     left, top;

    ostream.GetCurSel(left, top);
    ostream.GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 2);

    ostream << m_TabNameArray.GetAt(index);
    ostream << style;
    ostream << _T("\n");

    ostream << m_UnitCommentArray.GetAt(index);
    ostream << _T("\n\n");

    // if the synthesis is included
    if (m_IncludeSynthesis)
        FillSynthesis(ostream, index);

    if (!m_IncludeDetail)
        return true;

    return FillGridAllProcess(ostream, index);
}
//---------------------------------------------------------------------------
void PSS_ConceptorReportGenerator::OnPostRead(CArchive& ar)
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
                m_pModel                = pGraphModel;
                m_InChargeOfClosingFile = true;
            }
        }
    }
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ConceptorReportGenerator::AssertValid() const
    {
        PSS_ModelBPReportGenerator::AssertValid();
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void PSS_ConceptorReportGenerator::Dump(CDumpContext& dc) const
    {
        PSS_ModelBPReportGenerator::Dump(dc);
    }
#endif
//---------------------------------------------------------------------------
void PSS_ConceptorReportGenerator::FillTabArray()
{
    // if no doc or model defined, nothing to do
    if (!m_pDoc || !m_pModel)
        return;

    // remove all elements
    m_TabNameArray.RemoveAll();

    // load all process in the process name array. First, remove all elements
    RemoveAllData();

    FillTabUnitGroup(m_pModel->GetMainUserGroup());

    // fill the array with process name
    PSS_ExtractProcessName extractProcessName(m_pModel);

    // add all models to the model array
    extractProcessName.FillProcessNameArray(&m_ProcessNameArray);

    const int countProcess = m_ProcessNameArray.GetSize();

    for (int i = 0; i < countProcess; ++i)
    {
        // get the process matching with the model name, in case sensitive
        const CString             processName = m_ProcessNameArray.GetAt(i);
        PSS_ProcessGraphModelMdl* pModel      = m_pModel->FindModel(processName, true);

        // error?
        if (!pModel)
        {
            m_ModelArray.Add(NULL);
            continue;
        }

        m_ModelArray.Add(pModel);
    }

    m_GrayStyle.SetTextColor(defCOLOR_WHITE)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(9).SetBold(FALSE))
            .SetInterior(defCOLOR_GRAY);

    m_BlueStyle.SetTextColor(defCOLOR_BLACK).SetInterior(RGB(0, 128, 255));
    m_OrangeStyle.SetTextColor(defCOLOR_BLACK).SetInterior(RGB(250, 128, 64));
}
//---------------------------------------------------------------------------
void PSS_ConceptorReportGenerator::RemoveAllData()
{
    m_ProcessNameArray.RemoveAll();
    m_ModelArray.RemoveAll();
    m_UnitCommentArray.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_ConceptorReportGenerator::FillTabUnitGroup(PSS_UserGroupEntity* pGroup)
{
    if (!pGroup)
        return;

    m_TabNameArray.Add(pGroup->GetEntityName());
    m_UnitCommentArray.Add(pGroup->GetEntityDescription().IsEmpty() ? _T(" ") : pGroup->GetEntityDescription());

    if (pGroup->ContainEntity())
    {
        const int count = pGroup->GetEntityCount();

        for (int i = 0; i < count; ++i)
        {
            PSS_UserEntity* pEntity = pGroup->GetEntityAt(i);

            if (!pEntity)
                continue;

            PSS_UserGroupEntity* pUserGroup = dynamic_cast<PSS_UserGroupEntity*>(pEntity);

            if (pUserGroup)
                FillTabUnitGroup(pUserGroup);
        }
    }
}
//---------------------------------------------------------------------------
bool PSS_ConceptorReportGenerator::FillSynthesis(PSS_OStreamGrid& ostream, std::size_t index)
{
    CGXStyle style;

    // initialize the style for header cells
    style.SetTextColor(defCOLOR_WHITE)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(12).SetBold(TRUE))
            .SetInterior(RGB(250, 128, 64));

    CGXStyle normalStyle;

    normalStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(9).SetBold(FALSE))
            .SetInterior(defCOLOR_WHITE);

    // show header
    CString str;

    ostream << _T("\n\n");
    ostream << _T(" ");
    ostream << style;
    ostream << _T("\t");

    str.LoadString(IDS_CONCEPTOR_SYNTHESYS);
    ostream << str;
    ostream << CSize(150, 30);
    ostream << style;
    ostream << _T("\t");

    ostream << _T(" ");
    ostream << style;
    ostream << _T("\n");

    CGXStyle grayStyle;

    // initialize the style for header cells
    grayStyle.SetTextColor(defCOLOR_WHITE)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(12).SetBold(TRUE))
            .SetDraw3dFrame(gxFrameNormal)
            .SetInterior(defCOLOR_GRAY);

    // show header
    str.LoadString(IDS_CONCEPTOR_DOMAINTOPIC);
    ostream << str;
    ostream << CSize(150, 20);
    ostream << grayStyle;
    ostream << m_TopOnlyBlackBorderStyle;
    ostream << _T("\t");

    str.LoadString(IDS_CONCEPTOR_PROCESS);
    ostream << str;
    ostream << CSize(180, 0);
    ostream << grayStyle;
    ostream << m_TopOnlyBlackBorderStyle;
    ostream << _T("\t");

    str.LoadString(IDS_CONCEPTOR_PROCEDURE);
    ostream << str;
    ostream << CSize(200, 0);
    ostream << grayStyle;
    ostream << m_TopOnlyBlackBorderStyle;
    ostream << _T("\n");

    // build the synthesis for each page
    ZUSynthesisNavigation navigation(m_pModel,
                                     static_cast<void*>(&ostream),
                                     m_pModel,
                                     _T(""),
                                     m_TabNameArray.GetAt(index));

    // navigate through process symbols
    navigation.Navigate();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ConceptorReportGenerator::FillGridAllProcess(PSS_OStreamGrid& ostream, std::size_t index)
{
    // build the synthesis for each page
    PSS_ProcessConceptorNavigation navigation(m_pModel,
                                              static_cast<void*>(&ostream),
                                              m_pModel,
                                              _T(""),
                                              m_TabNameArray.GetAt(index),
                                              m_IncludeSynthesis,
                                              m_IncludeDetail,
                                              m_IncludeDeliverables);

    // navigate through process symbols
    navigation.Navigate();

    int left, top;

    // check the row count
    const ROWCOL rowCount = ostream.GetGridCore()->GetRowCount();
    ostream.GetCurSel(left, top);

    // if not enough, add the missing rows
    if ((top + 30) > int(rowCount))
        ostream.GetGridCore()->SetRowCount(rowCount + 30);

    return true;
}
//---------------------------------------------------------------------------
