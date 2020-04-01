/****************************************************************************
 * ==> PSS_GridMercutioReportProcedureNavigation ---------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will navigate through the       *
 *               procedures and write the Mercutio info to the report       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GridMercutioReportProcedureNavigation.h"

// processsoft
#include "zModel\PSS_ProcessGraphModelMdl.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModelBP\PSS_DoorSymbolBP.h"
#include "zModelBP\PSS_PageSymbolBP.h"
#include "zModelBP\PSS_ProcedureSymbolBP.h"
#include "zModelBP\PSS_ProcessSymbolBP.h"
#include "zModelBP\PSS_StartSymbolBP.h"
#include "zModelBP\PSS_StopSymbolBP.h"
#include "zModelBP\PSS_DeliverableLinkSymbolBP.h"
#include "zReport\PSS_OStreamGrid.h"
#include "PSS_ColorRefDefinition.h"

// resources
#include "zModelBP\zModelBPRes.h"
#include "zReportBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_GridMercutioReportProcedureNavigation
//---------------------------------------------------------------------------
PSS_GridMercutioReportProcedureNavigation::PSS_GridMercutioReportProcedureNavigation(PSS_ProcessGraphModelMdl* pModel,
                                                                                     void*                     pClass) :
    PSS_ProcessNavigation(pModel, pClass),
    m_pOStream(NULL)
{}
//---------------------------------------------------------------------------
PSS_GridMercutioReportProcedureNavigation::~PSS_GridMercutioReportProcedureNavigation()
{}
//---------------------------------------------------------------------------
bool PSS_GridMercutioReportProcedureNavigation::OnStart()
{
    // get the stream class
    if (!m_pOStream)
    {
        m_pOStream = static_cast<PSS_OStreamGrid*>(m_pClass);

        if (!m_pOStream)
            return false;
    }

    if (!m_pOStream->GetGridCore())
        return false;

    // initialize the normal style for cells
    m_NormalStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(9).SetBold(FALSE))
            .SetInterior(defCOLOR_WHITE);

    // initialize the bold style for cells
    m_BoldStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(9).SetBold(TRUE))
            .SetInterior(defCOLOR_WHITE);

    // initialize the blue style for header cells
    m_BlueStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(10).SetBold(FALSE))
            .SetInterior(M_Color_BlueMercutio);

    // initialize the bold blue style for header cells
    m_BoldBlueStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(10).SetBold(TRUE))
            .SetInterior(M_Color_BlueMercutio);

    // initialize the gray style for header cells
    m_GrayStyle.SetTextColor(defCOLOR_WHITE)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(10).SetBold(TRUE))
            .SetInterior(defCOLOR_GRAY);

    // initialize the light gray style for header cells
    m_LightGrayStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(9).SetBold(FALSE))
            .SetInterior(defCOLOR_LTGRAY);

    // initialize the black border
    m_BlackBorderStyle.SetBorders(gxBorderAll, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_LeftOnlyBlackBorderStyle.SetBorders(gxBorderLeft, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));

    // initialize the different cell formats
    m_PercentFormatStyle.SetFormat(GX_FMT_PERCENT).SetPlaces(0);
    m_NumericCellStyle.SetValueType(GX_VT_NUMERIC).SetPlaces(0);

    // load the strings from the resources
    m_DescriptionLabel.LoadString(IDS_DESC_LBLRPT);
    m_UnitLabel.LoadString(IDS_UNIT_LBLRPT);
    m_CombinationLabel.LoadString(IDS_COMBINATION_LBLRPT);
    m_RuleListLabel.LoadString(IDS_RULELIST_LBLRPT);
    m_TaskListLabel.LoadString(IDS_TASKLIST_LBLRPT);
    m_DecisionListLabel.LoadString(IDS_DECISIONLIST_LBLRPT);
    m_FormsLabel.LoadString(IDS_FORMS_LBLRPT);
    m_AppsLabel.LoadString(IDS_APP_LBLRPT);
    m_OutputDeliverableLabel.LoadString(IDS_OUTPUTDELIVERABLES_LBLRPT);
    m_LateralDeliverableLabel.LoadString(IDS_LATERALDELIVERABLES_LBLRPT);

    // size all cells width once
    *m_pOStream << CSize(70, 0);
    *m_pOStream << _T("\t");
    *m_pOStream << CSize(170, 0);
    *m_pOStream << _T("\t");
    *m_pOStream << CSize(90, 0);
    *m_pOStream << _T("\t");
    *m_pOStream << CSize(90, 0);
    *m_pOStream << _T("\t");
    *m_pOStream << CSize(90, 0);
    *m_pOStream << _T("\t");
    *m_pOStream << CSize(90, 0);

    // set the default row height for all cells
    m_pOStream->GetGridCore()->SetDefaultRowHeight(20);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridMercutioReportProcedureNavigation::OnFinish()
{
    // get the stream class
    if (!m_pOStream)
    {
        m_pOStream = static_cast<PSS_OStreamGrid*>(m_pClass);

        if (!m_pOStream)
            return false;
    }

    if (!m_pOStream->GetGridCore())
        return false;

    int left;
    int top;

    m_pOStream->GetCurSel(left, top);

    // set the grid as read-only
    m_pOStream->GetGridCore()->SetReadOnly(TRUE);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridMercutioReportProcedureNavigation::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    // not required for reference
    if (!pSymbol->IsLocal())
        return true;

    // get the stream class
    if (!m_pOStream)
    {
        m_pOStream = static_cast<PSS_OStreamGrid*>(m_pClass);

        if (!m_pOStream)
            return false;
    }

    if (!m_pOStream->GetGridCore())
        return false;

    // check the row count
    const ROWCOL rowCount = m_pOStream->GetGridCore()->GetRowCount();

    int left;
    int top;

    m_pOStream->GetCurSel(left, top);

    // if not enough, add the missing rows
    if ((top + 30) > int(rowCount))
        m_pOStream->GetGridCore()->SetRowCount(rowCount + 60);

    // build the first line with the deliverable reference number and the deliverable name
     m_pOStream->HomeLeft();
    *m_pOStream << pSymbol->GetSymbolReferenceNumberStr();
    *m_pOStream << m_BlueStyle;
     m_pOStream->SetCurSelRowHeight(40);
    *m_pOStream << _T("\t");

     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 4);
    *m_pOStream << pSymbol->GetSymbolName();
    *m_pOStream << m_BoldBlueStyle;

    // set the border
     m_pOStream->HomeLeft();
     m_pOStream->GetCurSel(left, top);
     m_pOStream->SetCurSel(left, top, left + 5, top);
    *m_pOStream << m_BlackBorderStyle;

    // build the second line with the unit name
    *m_pOStream << _T("\n");
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 1);
    *m_pOStream << m_UnitLabel;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t\t");

     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 3);
    *m_pOStream << pSymbol->GetUnitName();
    *m_pOStream << m_NormalStyle;
    *m_pOStream << m_BlackBorderStyle;

    // build the third line with the procedure description
    *m_pOStream << _T("\n");
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 1);
    *m_pOStream << m_DescriptionLabel;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t\t");

     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 3);
    *m_pOStream << pSymbol->GetSymbolComment();
    *m_pOStream << m_NormalStyle;
    *m_pOStream << m_BlackBorderStyle;

    // build the fourth line with the combination label
    *m_pOStream << _T("\n");
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 1);
    *m_pOStream << m_CombinationLabel;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t\t");

    // build the next columns with the combination name, maximum column is limited to 4
    std::size_t count = min(pSymbol->GetCombinationCount(), 4);

    for (std::size_t i = 0; i < count; ++i)
    {
        *m_pOStream << pSymbol->GetCombinationName(i);
        *m_pOStream << m_LightGrayStyle;
        *m_pOStream << m_LeftOnlyBlackBorderStyle;
        *m_pOStream << m_BlackBorderStyle;
        *m_pOStream << _T("\t");
    }

    CODEdgeArray edges;

    // for each deliverable, build the line. Get all entering up deliverables
    if (pSymbol->GetEnteringUpDeliverable(edges) > 0)
        for (int i = 0; i < edges.GetSize(); ++i)
        {
            IODEdge*                     pIEdge = edges.GetAt(i);
            PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

            if (!pComp)
                continue;

            // show the reference number
            *m_pOStream << _T("\n");
            *m_pOStream << pComp->GetSymbolReferenceNumberStr();
            *m_pOStream << m_BlueStyle;
            *m_pOStream << _T("\t");

            // show the deliverable name
            *m_pOStream << pComp->GetSymbolName();
            *m_pOStream << m_GrayStyle;
            *m_pOStream << _T("\t");

            bool found = false;

            // for each column, find if the deliverable belongs to the combination
            for (std::size_t j = 0; j < 4 && !found; ++j)
            {
                if (pSymbol->IsDeliverableInString(pSymbol->GetCombinationDeliverables(j), pComp->GetSymbolName()))
                {
                    found = true;

                    if (pSymbol->GetCombinationMaster(j) == pComp->GetSymbolName())
                    {
                        *m_pOStream << pComp->GetCombinationMaxPercentage();
                        *m_pOStream << m_PercentFormatStyle;
                        *m_pOStream << m_NumericCellStyle;
                    }
                    else
                        *m_pOStream << _T("x");

                    *m_pOStream << m_NormalStyle;
                }

                *m_pOStream << _T("\t");
            }
        }

    // build the next line with the rule list label
    *m_pOStream << _T("\n");
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 5);
    *m_pOStream << m_RuleListLabel;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << m_BlackBorderStyle;

    // build the next lines with the rules themselves, at least one empty line
    count = max(pSymbol->GetRuleCount(), 1);

    for (std::size_t i = 0; i < count; ++i)
    {
        *m_pOStream << _T("\n");
        *m_pOStream << m_BlueStyle;
        *m_pOStream << m_LeftOnlyBlackBorderStyle;
        *m_pOStream << _T("\t");

         m_pOStream->GetCurSel(left, top);
         m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 4);
        *m_pOStream << pSymbol->GetRuleAt(i);
        *m_pOStream << m_NormalStyle;
        *m_pOStream << m_BlackBorderStyle;
    }

    // build the next line with the task list label
    *m_pOStream << _T("\n");
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 5);
    *m_pOStream << m_TaskListLabel;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << m_BlackBorderStyle;

    // build the next lines with the tasks themselves, at least one empty line
    count = max(pSymbol->GetTaskCount(), 1);

    for (std::size_t i = 0; i < count; ++i)
    {
        *m_pOStream << _T("\n");
        *m_pOStream << m_BlueStyle;
        *m_pOStream << m_LeftOnlyBlackBorderStyle;
        *m_pOStream << _T("\t");

         m_pOStream->GetCurSel(left, top);
         m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 4);
        *m_pOStream << pSymbol->GetTaskAt(i);
        *m_pOStream << m_NormalStyle;
        *m_pOStream << m_BlackBorderStyle;
    }

    // build the next line with the decision list label
    *m_pOStream << _T("\n");
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 5);
    *m_pOStream << m_DecisionListLabel;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << m_BlackBorderStyle;

    // build the next lines with the decisions themselves, at least one empty line
    count = max(pSymbol->GetDecisionCount(), 1);

    for (std::size_t i = 0; i < count; ++i)
    {
        *m_pOStream << _T("\n");
        *m_pOStream << m_BlueStyle;
        *m_pOStream << m_LeftOnlyBlackBorderStyle;
        *m_pOStream << _T("\t");

         m_pOStream->GetCurSel(left, top);
         m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 4);
        *m_pOStream << pSymbol->GetDecisionAt(i);
        *m_pOStream << m_NormalStyle;
        *m_pOStream << m_BlackBorderStyle;
    }

    // build the line with the forms, document label
    *m_pOStream << _T("\n");
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 5);
    *m_pOStream << m_FormsLabel;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << m_BlackBorderStyle;

    // build the next lines with the forms, document and other
    count = pSymbol->GetExtFileCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        *m_pOStream << _T("\n");
        *m_pOStream << m_BlueStyle;
        *m_pOStream << m_LeftOnlyBlackBorderStyle;
        *m_pOStream << _T("\t");

         m_pOStream->GetCurSel(left, top);
         m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 4);
        *m_pOStream << pSymbol->GetFileTitle(i);
        *m_pOStream << m_NormalStyle;
        *m_pOStream << m_BlackBorderStyle;
    }

    // build the line with the external application label
    *m_pOStream << _T("\n");
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 5);
    *m_pOStream << m_AppsLabel;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << m_BlackBorderStyle;

    // build the next lines with the forms, document and other
    count = pSymbol->GetExtAppCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        *m_pOStream << _T("\n");
        *m_pOStream << m_BlueStyle;
        *m_pOStream << m_LeftOnlyBlackBorderStyle;
        *m_pOStream << _T("\t");

         m_pOStream->GetCurSel(left, top);
         m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 4);
        *m_pOStream << pSymbol->GetCommandTitle(i);
        *m_pOStream << m_NormalStyle;
        *m_pOStream << m_BlackBorderStyle;
    }

    // build the line with the output deliverables
    *m_pOStream << _T("\n");
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 5);
    *m_pOStream << m_OutputDeliverableLabel;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << m_BlackBorderStyle;

    // for each deliverables, build the line. Get all leaving down deliverables
    if (pSymbol->GetLeavingDownDeliverable(edges) > 0)
        for (int i = 0; i < edges.GetSize(); ++i)
        {
            IODEdge*                     pIEdge = edges.GetAt(i);
            PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

            if (!pComp)
                continue;

            // show the reference number
            *m_pOStream << _T("\n");
            *m_pOStream << pComp->GetSymbolReferenceNumberStr();
            *m_pOStream << m_BlueStyle;
            *m_pOStream << _T("\t");

            // show the deliverable name
             m_pOStream->GetCurSel(left, top);
             m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 3);
            *m_pOStream << pComp->GetSymbolName();
            *m_pOStream << m_NormalStyle;
            *m_pOStream << _T("\t\t\t\t");

            // show the output workload deliverable. Check if it's a local symbol
            if (!pComp->IsLocal())
                // get the local symbol
                pComp = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pComp->GetLocalSymbol());

            if (pComp)
                *m_pOStream << pComp->GetOutWorkloadPercent();
            else
                *m_pOStream << _T("#ERR");

            *m_pOStream << m_NormalStyle;
            *m_pOStream << m_PercentFormatStyle;
            *m_pOStream << m_NumericCellStyle;
        }

    // build the line with the lateral deliverables
    *m_pOStream << _T("\n");
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 5);
    *m_pOStream << m_LateralDeliverableLabel;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << m_BlackBorderStyle;

    // for each deliverables, build the line. Get all leaving right deliverables
    if (pSymbol->GetLeavingRightDeliverable(edges) > 0)
        for (int i = 0; i < edges.GetSize(); ++i)
        {
            IODEdge*                     pIEdge = edges.GetAt(i);
            PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

            if (!pComp)
                continue;

            // show the reference number
            *m_pOStream << _T("\n");
            *m_pOStream << pComp->GetSymbolReferenceNumberStr();
            *m_pOStream << m_BlueStyle;
            *m_pOStream << _T("\t");

            // show the deliverable name
             m_pOStream->GetCurSel(left, top);
             m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 3);
            *m_pOStream << pComp->GetSymbolName();
            *m_pOStream << m_NormalStyle;
            *m_pOStream << _T("\t\t\t\t");

            // show the output workload deliverable. Test if it is a local symbol
            if (!pComp->IsLocal())
                // get the local symbol
                pComp = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pComp->GetLocalSymbol());

            if (pComp)
                *m_pOStream << pComp->GetOutWorkloadPercent();
            else
                *m_pOStream << _T("#ERR");

            *m_pOStream << m_NormalStyle;
            *m_pOStream << m_PercentFormatStyle;
            *m_pOStream << m_NumericCellStyle;
        }

    // get all leaving left deliverables
    if (pSymbol->GetLeavingLeftDeliverable(edges) > 0)
        for (int i = 0; i < edges.GetSize(); ++i)
        {
            IODEdge*                     pIEdge = edges.GetAt(i);
            PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

            if (!pComp)
                continue;

            // show the reference number
            *m_pOStream << _T("\n");
            *m_pOStream << pComp->GetSymbolReferenceNumberStr();
            *m_pOStream << m_BlueStyle;
            *m_pOStream << _T("\t");

            // show the deliverable name
             m_pOStream->GetCurSel(left, top);
             m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 3);
            *m_pOStream << pComp->GetSymbolName();
            *m_pOStream << m_NormalStyle;
            *m_pOStream << _T("\t\t\t\t");

            // show the output workload deliverable. Test if it is a local symbol
            if (!pComp->IsLocal())
                // get the local symbol
                pComp = dynamic_cast<PSS_DeliverableLinkSymbolBP*>(pComp->GetLocalSymbol());

            if (pComp)
                *m_pOStream << pComp->GetOutWorkloadPercent();
            else
                *m_pOStream << _T("#ERR");

            *m_pOStream << m_NormalStyle;
            *m_pOStream << m_PercentFormatStyle;
            *m_pOStream << m_NumericCellStyle;
        }

    *m_pOStream << _T("\n");
    *m_pOStream << _T("\n");

    return true;
}
//---------------------------------------------------------------------------
