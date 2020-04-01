/****************************************************************************
 * ==> PSS_ProcessConceptorNavigation --------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will navigate through the       *
 *               processes and write the Conceptor info to the report       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ProcessConceptorNavigation.h"

// processsoft
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_ProcessGraphPage.h"
#include "zModelBP\PSS_ProcessGraphModelMdlBP.h"
#include "zModelBP\PSS_DoorSymbolBP.h"
#include "zModelBP\PSS_PageSymbolBP.h"
#include "zModelBP\PSS_ProcedureSymbolBP.h"
#include "zModelBP\PSS_ProcessSymbolBP.h"
#include "zModelBP\PSS_StartSymbolBP.h"
#include "zModelBP\PSS_StopSymbolBP.h"
#include "zModelBP\PSS_DeliverableLinkSymbolBP.h"
#include "zReport\PSS_OStreamGrid.h"

// resources
#include "zModelBP\zModelBPRes.h"
#include "zReportBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ProcessConceptorNavigation
//---------------------------------------------------------------------------
PSS_ProcessConceptorNavigation::PSS_ProcessConceptorNavigation(PSS_ProcessGraphModelMdl* pModel,
                                                               void*                     pClass,
                                                               PSS_ProcessGraphModelMdl* pRootModel,
                                                               const CString&            domainName,
                                                               const CString&            unitName,
                                                               BOOL                      includeSynthesis,
                                                               BOOL                      includeDetail,
                                                               BOOL                      includeDeliverables) :
    PSS_ProcessNavigation(pModel, pClass),
    m_pOStream(NULL),
    m_pPreviousProcess(NULL),
    m_pRootModel(pRootModel),
    m_DomainName(domainName),
    m_UnitName(unitName),
    m_IncludeSynthesis(includeSynthesis),
    m_IncludeDetail(includeDetail),
    m_IncludeDeliverables(includeDeliverables),
    m_First(false)
{}
//---------------------------------------------------------------------------
PSS_ProcessConceptorNavigation::~PSS_ProcessConceptorNavigation()
{}
//---------------------------------------------------------------------------
bool PSS_ProcessConceptorNavigation::OnStart()
{
    // get the stream class
    if (!m_pOStream)
    {
        m_pOStream = static_cast<PSS_OStreamGrid*>(m_pClass);

        if (!m_pOStream)
            return false;
    }

    m_GrayStyle.SetTextColor(defCOLOR_WHITE)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(9).SetBold(FALSE))
            .SetInterior(defCOLOR_GRAY);

    m_BlueStyle.SetTextColor(defCOLOR_BLACK).SetInterior(RGB(0, 128, 255));
    m_OrangeStyle.SetTextColor(defCOLOR_BLACK).SetInterior(RGB(250, 128, 64));

    // initialize the black border
    m_BlackBorderStyle.SetBorders(gxBorderAll, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_LeftOnlyBlackBorderStyle.SetBorders(gxBorderLeft, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_RightOnlyBlackBorderStyle.SetBorders(gxBorderRight, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_TopOnlyBlackBorderStyle.SetBorders(gxBorderTop, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_BottomOnlyBlackBorderStyle.SetBorders(gxBorderBottom, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessConceptorNavigation::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessConceptorNavigation::OnProcedureSymbol(PSS_ProcedureSymbolBP* pProcedure)
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

    // check the row count
    ROWCOL rowCount = m_pOStream->GetGridCore()->GetRowCount();

    int left, top;
    m_pOStream->GetCurSel(left, top);

    // if not enough, add the missing rows
    if ((top + 30) > int(rowCount))
        m_pOStream->GetGridCore()->SetRowCount(rowCount + 30);

    bool          error;
    const CString unitName = pProcedure->RetrieveUnitName(pProcedure->GetUnitGUID(), error);

    // check if for the same unit
    if (unitName != m_UnitName)
        return true;

    // if not yet visible, show the process section
    if (m_First == false)
        ShowProcess();

    CGXStyle wrapStyle;
    wrapStyle.SetWrapText(TRUE);

    CString str = _T("");

    // show the section
    *m_pOStream << _T("\n");
    *m_pOStream << pProcedure->GetSymbolReferenceNumberStr();
    *m_pOStream << m_BlueStyle;
    *m_pOStream << m_TopOnlyBlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_CONCEPTOR_PROCEDURE);
    *m_pOStream << str;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << m_TopOnlyBlackBorderStyle;
    *m_pOStream << _T("\t");

    *m_pOStream << pProcedure->GetSymbolName();
    *m_pOStream << wrapStyle;
    *m_pOStream << m_TopOnlyBlackBorderStyle;
    *m_pOStream << _T("\n");

    str.LoadString(IDS_CONCEPTOR_DESCRIPTION);
    *m_pOStream << str;
    *m_pOStream << m_BlueStyle;
    *m_pOStream << _T("\t");

    *m_pOStream << pProcedure->GetSymbolComment();
    *m_pOStream << wrapStyle;
    *m_pOStream << _T("\n");

    if (m_IncludeDeliverables)
    {
        str.LoadString(IDS_CONCEPTOR_DELIVERABLE_ENTRY);
        *m_pOStream << str;
        *m_pOStream << m_GrayStyle;
        *m_pOStream << _T("\t");
        *m_pOStream << m_GrayStyle;
        *m_pOStream << _T("\t");
        *m_pOStream << m_GrayStyle;
        *m_pOStream << _T("\n");

        // get all the entering up deliverables
        CODEdgeArray edges;

        if (pProcedure->GetEnteringUpDeliverable(edges) > 0)
            for (int i = 0; i < edges.GetSize(); ++i)
            {
                IODEdge*                     pIEdge = edges.GetAt(i);
                PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                if (!pComp)
                    continue;

                // show the reference number
                *m_pOStream << pComp->GetSymbolReferenceNumberStr();
                *m_pOStream << m_BlueStyle;
                *m_pOStream << _T("\t");

                // show the deliverable name
                *m_pOStream << pComp->GetSymbolName();
                *m_pOStream << _T("\n");

                // check the row count
                const ROWCOL rowCount = m_pOStream->GetGridCore()->GetRowCount();

                int left, top;
                m_pOStream->GetCurSel(left, top);

                // if not enough, add the missing rows
                if ((top + 5) > int(rowCount))
                    m_pOStream->GetGridCore()->SetRowCount(rowCount + 5);
            }

        str.LoadString(IDS_CONCEPTOR_DELIVERABLE_LATERAL_OUTPUT);
        *m_pOStream << str;
        *m_pOStream << m_GrayStyle;
        *m_pOStream << _T("\t");
        *m_pOStream << m_GrayStyle;
        *m_pOStream << _T("\t");
        *m_pOStream << m_GrayStyle;
        *m_pOStream << _T("\n");

        // get all leaving right deliverables
        if (pProcedure->GetEdgesLeaving_Right(edges) > 0)
            for (int i = 0; i < edges.GetSize(); ++i)
            {
                IODEdge*                     pIEdge = edges.GetAt(i);
                PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                if (!pComp)
                    continue;

                // show the reference number
                *m_pOStream << pComp->GetSymbolReferenceNumberStr();
                *m_pOStream << m_BlueStyle;
                *m_pOStream << _T("\t");

                // show the deliverable name
                *m_pOStream << pComp->GetSymbolName();
                *m_pOStream << wrapStyle;
                *m_pOStream << _T("\n");

                // check the row count
                const ROWCOL rowCount = m_pOStream->GetGridCore()->GetRowCount();

                int left, top;
                m_pOStream->GetCurSel(left, top);

                // if not enough, add the missing rows
                if ((top + 5) > int(rowCount))
                    m_pOStream->GetGridCore()->SetRowCount(rowCount + 5);
            }

        // get all leaving left deliverables
        if (pProcedure->GetEdgesLeaving_Left(edges) > 0)
            for (int i = 0; i < edges.GetSize(); ++i)
            {
                IODEdge*                     pIEdge = edges.GetAt(i);
                PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                if (!pComp)
                    continue;

                // show the reference number
                *m_pOStream << pComp->GetSymbolReferenceNumberStr();
                *m_pOStream << m_BlueStyle;
                *m_pOStream << _T("\t");

                // show the deliverable name
                *m_pOStream << pComp->GetSymbolName();
                *m_pOStream << wrapStyle;
                *m_pOStream << _T("\n");

                // check the row count
                const ROWCOL rowCount = m_pOStream->GetGridCore()->GetRowCount();

                int left, top;
                m_pOStream->GetCurSel(left, top);

                // if not enough, add the missing rows
                if ((top + 5) > int(rowCount))
                    m_pOStream->GetGridCore()->SetRowCount(rowCount + 5);
            }

        str.LoadString(IDS_CONCEPTOR_DELIVERABLE_LATERAL_ENTRY);
        *m_pOStream << str;
        *m_pOStream << m_GrayStyle;
        *m_pOStream << _T("\t");
        *m_pOStream << m_GrayStyle;
        *m_pOStream << _T("\t");
        *m_pOStream << m_GrayStyle;
        *m_pOStream << _T("\n");

        // get all entering right deliverables
        if (pProcedure->GetEdgesEntering_Right(edges) > 0)
            for (int i = 0; i < edges.GetSize(); ++i)
            {
                IODEdge*                     pIEdge = edges.GetAt(i);
                PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                if (!pComp)
                    continue;

                // show the reference number
                *m_pOStream << pComp->GetSymbolReferenceNumberStr();
                *m_pOStream << m_BlueStyle;
                *m_pOStream << _T("\t");

                // show the deliverable name
                *m_pOStream << pComp->GetSymbolName();
                *m_pOStream << wrapStyle;
                *m_pOStream << _T("\n");

                // check the row count
                const ROWCOL rowCount = m_pOStream->GetGridCore()->GetRowCount();

                int left, top;
                m_pOStream->GetCurSel(left, top);

                // if not enough, add the missing rows
                if ((top + 5) > int(rowCount))
                    m_pOStream->GetGridCore()->SetRowCount(rowCount + 5);
            }

        // get all entering left deliverables
        if (pProcedure->GetEdgesEntering_Left(edges) > 0)
            for (int i = 0; i < edges.GetSize(); ++i)
            {
                IODEdge*                     pIEdge = edges.GetAt(i);
                PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                if (!pComp)
                    continue;

                // show the reference number
                *m_pOStream << pComp->GetSymbolReferenceNumberStr();
                *m_pOStream << m_BlueStyle;
                *m_pOStream << _T("\t");

                // show the deliverable name
                *m_pOStream << pComp->GetSymbolName();
                *m_pOStream << wrapStyle;
                *m_pOStream << _T("\n");

                // check the row count
                const ROWCOL rowCount = m_pOStream->GetGridCore()->GetRowCount();

                int left, top;
                m_pOStream->GetCurSel(left, top);

                // if not enough, add the missing rows
                if ((top + 5) > int(rowCount))
                    m_pOStream->GetGridCore()->SetRowCount(rowCount + 5);
            }
    }

    rowCount = m_pOStream->GetGridCore()->GetRowCount();
    m_pOStream->GetCurSel(left, top);

    // If not enough, add the missing rows
    if ((top + 20) > int(rowCount))
        m_pOStream->GetGridCore()->SetRowCount(rowCount + 20);

    // rules, decisions, tasks, etc.
    str.LoadString(IDS_CONCEPTOR_RULESLIST);
    *m_pOStream << str;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << _T("\t");
    *m_pOStream << m_GrayStyle;
    *m_pOStream << _T("\t");
    *m_pOStream << m_GrayStyle;
    *m_pOStream << _T("\n");

    // build the next lines with the rules, at least one empty line
    int count = max(pProcedure->GetRuleCount(), 1);

    for (int i = 0; i < count; ++i)
    {
        str.Format(IDS_CONCEPTOR_RULE_NB, i + 1);
        *m_pOStream << str;
        *m_pOStream << m_BlueStyle;
        *m_pOStream << _T("\t");
        *m_pOStream << pProcedure->GetRuleAt(i);
        *m_pOStream << wrapStyle;
        *m_pOStream << _T("\n");

        // check the row count
        const ROWCOL rowCount = m_pOStream->GetGridCore()->GetRowCount();

        int left, top;
        m_pOStream->GetCurSel(left, top);

        // if not enough, add the missing rows
        if ((top + 5) > int(rowCount))
            m_pOStream->GetGridCore()->SetRowCount(rowCount + 5);
    }

    str.LoadString(IDS_CONCEPTOR_TASKSLIST);
    *m_pOStream << str;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << _T("\t");
    *m_pOStream << m_GrayStyle;
    *m_pOStream << _T("\t");
    *m_pOStream << m_GrayStyle;
    *m_pOStream << _T("\n");

    // build the next lines with the tasks, at least one empty line
    count = max(pProcedure->GetTaskCount(), 1);

    for (int i = 0; i < count; ++i)
    {
        str.Format(IDS_CONCEPTOR_TASK_NB, i + 1);
        *m_pOStream << str;
        *m_pOStream << m_BlueStyle;
        *m_pOStream << _T("\t");
        *m_pOStream << pProcedure->GetTaskAt(i);
        *m_pOStream << wrapStyle;
        *m_pOStream << _T("\n");

        // check the row count
        const ROWCOL rowCount = m_pOStream->GetGridCore()->GetRowCount();

        int left, top;
        m_pOStream->GetCurSel(left, top);

        // if not enough, add the missing rows
        if ((top + 5) > int(rowCount))
            m_pOStream->GetGridCore()->SetRowCount(rowCount + 5);
    }

    str.LoadString(IDS_CONCEPTOR_DECISIONSLIST);
    *m_pOStream << str;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << _T("\t");
    *m_pOStream << m_GrayStyle;
    *m_pOStream << _T("\t");
    *m_pOStream << m_GrayStyle;
    *m_pOStream << _T("\n");

    // build the next lines with the decisions, at least one empty line
    count = max(pProcedure->GetDecisionCount(), 1);

    for (int i = 0; i < count; ++i)
    {
        str.Format(IDS_CONCEPTOR_DECISION_NB, i + 1);
        *m_pOStream << str;
        *m_pOStream << m_BlueStyle;
        *m_pOStream << _T("\t");
        *m_pOStream << pProcedure->GetDecisionAt(i);
        *m_pOStream << wrapStyle;
        *m_pOStream << _T("\n");

        // check the row count
        const ROWCOL rowCount = m_pOStream->GetGridCore()->GetRowCount();

        int left, top;
        m_pOStream->GetCurSel(left, top);

        // if not enough, add the missing rows
        if ((top + 5) > int(rowCount))
            m_pOStream->GetGridCore()->SetRowCount(rowCount + 5);
    }

    if (m_IncludeDeliverables)
    {
        str.LoadString(IDS_CONCEPTOR_DELIVERABLE_OUTPUT);
        *m_pOStream << str;
        *m_pOStream << m_GrayStyle;
        *m_pOStream << _T("\t");
        *m_pOStream << m_GrayStyle;
        *m_pOStream << _T("\t");
        *m_pOStream << m_GrayStyle;
        *m_pOStream << _T("\n");

        // get all leaving down deliverables
        CODEdgeArray edges;

        if (pProcedure->GetEdgesLeaving_Down(edges) > 0)
            for (int i = 0; i < edges.GetSize(); ++i)
            {
                IODEdge*                     pIEdge = edges.GetAt(i);
                PSS_DeliverableLinkSymbolBP* pComp  = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                if (!pComp)
                    continue;

                // show the reference number
                *m_pOStream << pComp->GetSymbolReferenceNumberStr();
                *m_pOStream << m_BlueStyle;
                *m_pOStream << _T("\t");

                // show the deliverable name
                *m_pOStream << pComp->GetSymbolName();
                *m_pOStream << wrapStyle;
                *m_pOStream << _T("\n");

                // check the row count
                const ROWCOL rowCount = m_pOStream->GetGridCore()->GetRowCount();

                int left, top;
                m_pOStream->GetCurSel(left, top);

                // if not enough, add the missing rows
                if ((top + 5) > int(rowCount))
                    m_pOStream->GetGridCore()->SetRowCount(rowCount + 5);
            }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessConceptorNavigation::OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol)
{
    m_pPreviousProcess   = pSymbol;
    m_CurrentProcessName = pSymbol->GetSymbolName();

    PSS_ProcessGraphModelMdl* pOwnerModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetOwnerModel());

    if (pOwnerModel)
    {
        PSS_ProcessGraphPage* pPage = m_pRootModel->FindModelPage(pOwnerModel, true);

        if (pPage)
            m_DomainName = pPage->GetPageName();
        else
            m_DomainName.LoadString(IDS_CONCEPTOR_NOT_FOUND);
    }

    m_First = false;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessConceptorNavigation::OnSymbol(PSS_Symbol* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessConceptorNavigation::OnLink(PSS_LinkSymbol* pLink)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessConceptorNavigation::ShowProcess()
{
    if (!m_pPreviousProcess)
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

    m_First = true;

    CGXStyle style;
    style.SetTextColor(defCOLOR_BLACK).SetInterior(RGB(250, 128, 64));

    CGXStyle wrapStyle;
    wrapStyle.SetWrapText(TRUE);

    // check the row count
    const ROWCOL rowCount = m_pOStream->GetGridCore()->GetRowCount();

    int left, top;
    m_pOStream->GetCurSel(left, top);

    // if not enough, add the missing rows
    if ((top + 30) > int(rowCount))
        m_pOStream->GetGridCore()->SetRowCount(rowCount + 30);

    CString str;

    // title
    *m_pOStream << _T("\n\n");
    *m_pOStream << style;
    *m_pOStream << m_TopOnlyBlackBorderStyle;
    *m_pOStream << m_BottomOnlyBlackBorderStyle;
    *m_pOStream << m_DomainName;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_CONCEPTOR_PROCESS);
    *m_pOStream << str;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << m_TopOnlyBlackBorderStyle;
    *m_pOStream << m_BottomOnlyBlackBorderStyle;
    *m_pOStream << _T("\t");

    *m_pOStream << style;
    *m_pOStream << m_CurrentProcessName;
    *m_pOStream << style;
    *m_pOStream << wrapStyle;
    *m_pOStream << m_TopOnlyBlackBorderStyle;
    *m_pOStream << m_BottomOnlyBlackBorderStyle;
    *m_pOStream << m_RightOnlyBlackBorderStyle;
    *m_pOStream << _T("\t\n");

    PSS_Symbol* pSymbol = dynamic_cast<PSS_Symbol*>(m_pPreviousProcess);

    if (pSymbol)
    {
        PSS_ProcessGraphModelMdlBP* pGraphModel = dynamic_cast<PSS_ProcessGraphModelMdlBP*>(pSymbol->GetChildModel());

        if (pGraphModel)
        {
            CODNodeArray nodes;

            if (pGraphModel->GetBPStartSymbols(nodes, false) > 0)
                StartSection(nodes);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ProcessConceptorNavigation::StartSection(CODNodeArray& nodes)
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

    CGXStyle wrapStyle;
    wrapStyle.SetWrapText(TRUE);

    const std::size_t nodeSize = nodes.GetSize();

    for (std::size_t i = 0; i < nodeSize; ++i)
    {
        IODNode*            pINode = nodes.GetAt(i);
        PSS_StartSymbolBP*  pStart = static_cast<PSS_StartSymbolBP*>(pINode);

        if (!pStart)
            continue;

        // check the row count
        ROWCOL rowCount = m_pOStream->GetGridCore()->GetRowCount();

        int left, top;
        m_pOStream->GetCurSel(left, top);

        // if not enough, add the missing rows
        if ((top + 5) > int(rowCount))
            m_pOStream->GetGridCore()->SetRowCount(rowCount + 5);

        // check if for the same unit
        if (pStart->GetUnitName() != m_UnitName)
            continue;

        CString str;

        // show the section
        *m_pOStream << _T("\n");
        *m_pOStream << pStart->GetSymbolReferenceNumberStr();
        *m_pOStream << m_BlueStyle;
        *m_pOStream << _T("\t");

        str.LoadString(IDS_CONCEPTOR_STARTPOINT);
        *m_pOStream << str;
        *m_pOStream << m_GrayStyle;
        *m_pOStream << _T("\t");

        *m_pOStream << pStart->GetSymbolName();
        *m_pOStream << _T("\n");

        str.LoadString(IDS_CONCEPTOR_DESCRIPTION);
        *m_pOStream << str;
        *m_pOStream << m_BlueStyle;
        *m_pOStream << _T("\t");

        *m_pOStream << pStart->GetSymbolComment();
        *m_pOStream << wrapStyle;
        *m_pOStream << _T("\n");

        if (m_IncludeDeliverables)
        {
            CODEdgeArray edges;

            // get all leaving down deliverables
            if (pStart->GetEdgesLeaving(edges) > 0)
            {
                PSS_DeliverableLinkSymbolBP* pDeliverable = NULL;

                const int edgeCount = edges.GetSize();

                for (int j = 0; j < edgeCount; ++j)
                {
                    IODEdge* pIEdge = edges.GetAt(j);
                    pDeliverable    = static_cast<PSS_DeliverableLinkSymbolBP*>(pIEdge);

                    if (!pDeliverable)
                        continue;
                }

                if (pDeliverable)
                {
                    str.LoadString(IDS_CONCEPTOR_DELIVERABLE);
                    *m_pOStream << str + _T(" ");
                    *m_pOStream << pDeliverable->GetSymbolReferenceNumberStr();
                    *m_pOStream << m_BlueStyle;
                    *m_pOStream << _T("\t");
                    *m_pOStream << pDeliverable->GetSymbolName();
                    *m_pOStream << _T("\n");
                }
            }
        }

        // check the row count
        rowCount = m_pOStream->GetGridCore()->GetRowCount();
        m_pOStream->GetCurSel(left, top);

        // if not enough, add the missing rows
        if ((top + 5) > int(rowCount))
            m_pOStream->GetGridCore()->SetRowCount(rowCount + 5);
    }

    return true;
}
//---------------------------------------------------------------------------
