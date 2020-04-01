/****************************************************************************
 * ==> PSS_GridMercutioReportDeliverableNavigation -------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will navigate through the       *
 *               deliverables and write the Mercutio info to the report     *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GridMercutioReportDeliverableNavigation.h"

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
// PSS_GridMercutioReportDeliverableNavigation
//---------------------------------------------------------------------------
PSS_GridMercutioReportDeliverableNavigation::PSS_GridMercutioReportDeliverableNavigation(PSS_ProcessGraphModelMdl* pModel,
                                                                                         void*                     pClass) :
    PSS_ProcessNavigation(pModel, pClass),
    m_pOStream(NULL)
{}
//---------------------------------------------------------------------------
PSS_GridMercutioReportDeliverableNavigation::~PSS_GridMercutioReportDeliverableNavigation()
{}
//---------------------------------------------------------------------------
bool PSS_GridMercutioReportDeliverableNavigation::OnStart()
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

    // load string resources
    m_DescriptionLabel.LoadString(IDS_DESC_LBLRPT);
    m_RuleListLabel.LoadString(IDS_RULELIST_LBLRPT);
    m_KeyInfoLabel.LoadString(IDS_KEYINFO_LBLRPT);
    m_FormListLabel.LoadString(IDS_FORMLST_LBLRPT);
    m_InputProcedureLabel.LoadString(IDS_INPUTPROC_LBLRPT);
    m_OutputProcedureLabel.LoadString(IDS_OUTPUTPROC_LBLRPT);
    m_ComingFromProcedureLabel.LoadString(IDS_COMINGFROMPROC_LBLRPT);
    m_GoingToProcedureLabel.LoadString(IDS_GOINGTOPROC_LBLRPT);
    m_InitialProcedureLabel.LoadString(IDS_INITIALPROC_LBLRPT);
    m_FinalProcedureLabel.LoadString(IDS_FINALPROC_LBLRPT);

    // size all cells width one time
    *m_pOStream << CSize(70, 0);
    *m_pOStream << _T("\t");
    *m_pOStream << CSize(100, 0);
    *m_pOStream << _T("\t");
    *m_pOStream << CSize(100, 0);
    *m_pOStream << _T("\t");
    *m_pOStream << CSize(100, 0);
    *m_pOStream << _T("\t");
    *m_pOStream << CSize(100, 0);
    *m_pOStream << _T("\t");
    *m_pOStream << CSize(100, 0);

    // set the default row height for all cells
    m_pOStream->GetGridCore()->SetDefaultRowHeight(20);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridMercutioReportDeliverableNavigation::OnFinish()
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

    int top;
    int left;

    m_pOStream->GetCurSel(left, top);

    // set the grid as read-only
    m_pOStream->GetGridCore()->SetReadOnly(TRUE);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridMercutioReportDeliverableNavigation::OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol)
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
    const ROWCOL rowCount = m_pOStream->GetGridCore()->GetRowCount();

    int left;
    int top;

    m_pOStream->GetCurSel(left, top);

    // if not enough, add the missing rows
    if ((top + 30) > int(rowCount))
        m_pOStream->GetGridCore()->SetRowCount(rowCount + 60);

    // build the first line with the deliverable reference number and the deliverable name.
    m_pOStream->HomeLeft();

    *m_pOStream << pSymbol->GetSymbolReferenceNumberStr();
    *m_pOStream << m_BlueStyle;
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

    // build the second line with the deliverable description
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

    // build the third line with the key info label
    *m_pOStream << _T("\n");
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 5);
    *m_pOStream << m_KeyInfoLabel;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << m_BlackBorderStyle;

    // build the next lines with the key info itself, at least one empty line
    std::size_t count = max(pSymbol->GetTextItemCount(), 1);

    for (std::size_t i = 0; i < count; ++i)
    {
        *m_pOStream << _T("\n");
        *m_pOStream << m_BlueStyle;
        *m_pOStream << m_LeftOnlyBlackBorderStyle;
        *m_pOStream << _T("\t");

         m_pOStream->GetCurSel(left, top);
         m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 4);
        *m_pOStream << pSymbol->GetTextItemAt(i);
        *m_pOStream << m_NormalStyle;
        *m_pOStream << m_BlackBorderStyle;
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

    // build the third line with the forms, document label
    *m_pOStream << _T("\n");
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 5);
    *m_pOStream << m_FormListLabel;
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

    // build the third line with the input procedure name
    *m_pOStream << _T("\n");
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 3);
    *m_pOStream << m_InputProcedureLabel;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t\t\t\t");

     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 1);
    *m_pOStream << m_GoingToProcedureLabel;
    *m_pOStream << m_LightGrayStyle;
    *m_pOStream << m_BlackBorderStyle;

    CString procedureNumber;
    CString procedureName;
    CString processName;

    // get the output procedure name
    PSS_ProcedureSymbolBP* pProcedure = pSymbol->GetTargetProcedure();
    PSS_ProcessSymbolBP*   pProcess   = pSymbol->GetComingFromProcess();

    if (pProcess)
    {
        procedureNumber = pProcess->GetSymbolReferenceNumberStr();
        processName     = pProcess->GetSymbolName();
    }

    if (pProcedure)
    {
        procedureNumber = pProcedure->GetSymbolReferenceNumberStr();
        procedureName   = pProcedure->GetSymbolName();
    }
    else
    if (pSymbol->IsFinal())
    {
        procedureNumber = m_FinalProcedureLabel;
        processName.Empty();
    }

    *m_pOStream << _T("\n");
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top + 1, left);
    *m_pOStream << procedureNumber;
    *m_pOStream << m_BlueStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top + 1, left + 2);
    *m_pOStream << procedureName;
    *m_pOStream << m_BoldStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t\t\t");

     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top + 1, left + 1);
    *m_pOStream << processName;
    *m_pOStream << m_NormalStyle;
    *m_pOStream << m_BlackBorderStyle;

    // build the next line with the output procedure name. NOTE two newline, since we have written information on two lines
    *m_pOStream << _T("\n\n");
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 3);
    *m_pOStream << m_OutputProcedureLabel;
    *m_pOStream << m_GrayStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t\t\t\t");

     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 1);
    *m_pOStream << m_ComingFromProcedureLabel;
    *m_pOStream << m_LightGrayStyle;
    *m_pOStream << m_BlackBorderStyle;

    // empty the process name
    processName.Empty();

    // get the input procedure name
    pProcedure = pSymbol->GetSourceProcedure();
    pProcess   = pSymbol->GetComingFromProcess();

    if (pProcess)
    {
        procedureNumber = pProcess->GetSymbolReferenceNumberStr();
        processName     = pProcess->GetSymbolName();
    }

    if (pProcedure)
    {
        procedureNumber = pProcedure->GetSymbolReferenceNumberStr();
        procedureName   = pProcedure->GetSymbolName();
    }
    else
    if (pSymbol->IsInitial())
    {
        // search if an inter-process deliverable exists
        procedureNumber = m_InitialProcedureLabel;
        processName     = _T("");
    }

    *m_pOStream << _T("\n");
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top + 1, left);
    *m_pOStream << procedureNumber;
    *m_pOStream << m_BlueStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top + 1, left + 2);
    *m_pOStream << procedureName;
    *m_pOStream << m_BoldStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t\t\t");

     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top + 1, left + 1);
    *m_pOStream << processName;
    *m_pOStream << m_NormalStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\n\n");

    *m_pOStream << _T("\n");
    *m_pOStream << _T("\n");

    return true;
}
//---------------------------------------------------------------------------
