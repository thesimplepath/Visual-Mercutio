// ZUGridSesterceProcessNavigation.cpp: implementation of the ZUGridSesterceProcessNavigation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUGridSesterceProcessNavigation.h"

#include "zModel\PSS_ProcessGraphModelMdl.h"
#include "zReport\ZDGridDoc.h"

#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModelBP\PSS_DoorSymbolBP.h"
#include "zModelBP\PSS_PageSymbolBP.h"
#include "zModelBP\PSS_ProcedureSymbolBP.h"
#include "zModelBP\ZBBPProcessSymbol.h"
#include "zModelBP\ZBBPStartSymbol.h"
#include "zModelBP\ZBBPStopSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"

#include "zReport\ZBOStreamGrid.h"
#include "zReport\ZVGridView.h"
#include "zReport\ZCGridGroup.h"

#include "ColorRefDefinition.h"

#include "zModelBP\zModelBPRes.h"
#include "zReportBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 28 mars 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUGridSesterceProcessNavigation::ZUGridSesterceProcessNavigation(PSS_ProcessGraphModelMdl*    pModel    /*= NULL*/,
                                                                 void*                        pClass    /*= NULL*/)
    : ZUProcessNavigation(pModel, pClass)
{}

ZUGridSesterceProcessNavigation::~ZUGridSesterceProcessNavigation()
{}

bool ZUGridSesterceProcessNavigation::OnStart()
{
    // Start by casting the stream class
    m_postream = static_cast<ZBOStreamGrid*>(m_pClass);

    ASSERT(m_postream->GetGridCore() != NULL);
    ASSERT(m_pModel != NULL);

    // Retrieve the grid view
    ZVGridView*    pView = NULL;
    CWnd*        pWnd = m_postream->GetGridCore()->GridWnd();

    if (pWnd && ISA(pWnd, ZVGridView))
    {
        pView = dynamic_cast<ZVGridView*>(pWnd);
    }

    // Find the right process, function of the model name
    ZBBPProcessSymbol*    pProcess = NULL;
    CODComponentSet*    pSet = m_pModel->GetRoot()->FindSymbol(m_pModel->GetModelName(),
                                                               _T(""),
                                                               true,
                                                               true,    // In case sensitive,
                                                               true);    // and only local symbol

    if (pSet && pSet->GetSize() > 0 && pSet->GetAt(0) != NULL && ISA(pSet->GetAt(0), ZBBPProcessSymbol))
    {
        pProcess = dynamic_cast<ZBBPProcessSymbol*>(pSet->GetAt(0));
    }

    // Initialize the normal style for cells
    m_NormalStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(9).SetBold(FALSE))
        .SetInterior(defCOLOR_WHITE);

    // Initialize the normal style for cells
    m_BoldStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(9).SetBold(TRUE))
        .SetInterior(defCOLOR_WHITE);

    // Initialize the rose style for header cells
    m_RoseStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(10).SetBold(FALSE))
        .SetInterior(defCOLOR_ROSESESTERCE);

    // Initialize the bold rose style for header cells
    m_BoldRoseStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(10).SetBold(TRUE))
        .SetInterior(defCOLOR_ROSESESTERCE);

    // Initialize the blue style
    m_BlueStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(9).SetBold(FALSE))
        .SetInterior(defCOLOR_BLUEMERCUTIO);

    // Initialize the blue style
    m_GreenStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(9).SetBold(FALSE))
        .SetInterior(defCOLOR_STARTGREEN);

    // Initialize the blue style
    m_RedStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(9).SetBold(FALSE))
        .SetInterior(defCOLOR_ENDRED);

    // Initialize the blue style for header cells
    m_GrayStyle.SetTextColor(defCOLOR_WHITE)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(10).SetBold(TRUE))
        .SetInterior(defCOLOR_GRAY);

    // Initialize the blue style for header cells
    m_LightGrayStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(9).SetBold(FALSE))
        .SetInterior(defCOLOR_LTGRAY);

    // Initialize the black border
    m_BlackBorderStyle.SetBorders(gxBorderAll, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_LeftOnlyBlackBorderStyle.SetBorders(gxBorderLeft, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));

    // Initialize the different cell formats
    m_PercentFormatStyle.SetFormat(GX_FMT_PERCENT).SetPlaces(0);
    m_AmountFormatStyle.SetFormat(GX_FMT_COMMA).SetPlaces(0);
    m_NumberTwoDecFormatStyle.SetFormat(GX_FMT_FIXED).SetPlaces(2);
    m_NumericCellStyle.SetValueType(GX_VT_NUMERIC).SetPlaces(0);

    // Sets the default row height and column width for all cells
    m_postream->GetGridCore()->SetDefaultRowHeight(20);
    m_postream->GetGridCore()->SetDefaultColWidth(80);

    // Display header
    CString s;
    int top;
    int left;

    // Check the number of row
    ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
    m_postream->GetCurSel(left, top);

    // If not enough, add 5 rows
    if ((top + 5) > (int)RowCount)
    {
        m_postream->GetGridCore()->SetRowCount(RowCount + 5);
    }

    // Check the number of column
    ROWCOL ColCount = m_postream->GetGridCore()->GetColCount();

    // If not enough, add 120 columns
    if ((left + 120) > (int)ColCount)
    {
        m_postream->GetGridCore()->SetColCount(ColCount + 120);
    }

    // First row is for control
    // and for monthly label for process information
    m_postream->Right(77); // Move right

    // If a grid view, insert a group control for months
    if (pView)
    {
        // Retrieve the current position
        m_postream->GetCurSel(left, top);

        CString Label;
        Label.LoadString(IDS_CHKBOX_LABEL);

        CString ToolTipText;
        ToolTipText.LoadString(IDS_CHKBOX_TTP);

        pView->InsertGroupCtrl(top,
                               left,            // row col
                               13,                // covering cells
                               true,            // horizontal
                               true,            // collapsed
                               Label,
                               ToolTipText);
    }

    *m_postream << m_NormalStyle;
    *m_postream << _T("\t");

    // Then inserts all labels for months
    s.LoadString(IDS_MONTH_LBLRPT1);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT2);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT3);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT4);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT5);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT6);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT7);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT8);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT9);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT10);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT11);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT12);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\n");

    // Cell A1
    *m_postream << CSize(200, 80);    // Set the cell size
    *m_postream << m_RoseStyle;
    *m_postream << _T("\t");

    // Next cells
    m_postream->GetCurSel(left, top);
    m_postream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 7);
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    m_postream->Right(8); // Move right

    // Next cells
    m_postream->GetCurSel(left, top);
    m_postream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 66);
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    m_postream->Right(67); // Move right

    // Next cell is the forecasted process workload
    s.LoadString(IDS_FORECWORKLOADPROCESS_LBLRPT);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // Next cell is the forecasted process workload itself
    if (pProcess)
    {
        *m_postream << pProcess->GetProcessWorkloadForecast().GetNumberYear();
        *m_postream << m_LightGrayStyle;
        *m_postream << m_BlackBorderStyle;
        *m_postream << m_NumericCellStyle;
        *m_postream << m_AmountFormatStyle;
        *m_postream << _T("\t");

        // The forecasted process cost for each month
        for (int i = 0; i < 12; ++i)
        {
            *m_postream << pProcess->GetProcessWorkloadForecast().GetNumberAt(i);
            *m_postream << m_LightGrayStyle;
            *m_postream << m_NumericCellStyle;
            *m_postream << m_AmountFormatStyle;
            *m_postream << _T("\t");
        }
    }

    // Build the second header line
    *m_postream << _T("\n");
    *m_postream << CSize(200, 80);    // Set the cell size
    *m_postream << m_RoseStyle;
    *m_postream << _T("\t");

    // Next cell is the output percent
    s.LoadString(IDS_PERCOUT_LBLRPT);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // Next cell is the unit name
    s.LoadString(IDS_UNIT_LBLRPT);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // Next cell is the unitary cost
    s.LoadString(IDS_UNITARYCOST_LBLRPT);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // Next cell is the combination name
    s.LoadString(IDS_COMBINATIONNAME_LBLRPT);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // Next cell is the percent combination activation
    s.LoadString(IDS_COMBPERC_LBLRPT);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // Next cell is the multiplicator
    s.LoadString(IDS_MULTIPLICATOR_LBLRPT);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // Next cell is the standard time
    s.LoadString(IDS_STANDARDTIME_LBLRPT);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // Next cell is the quantity
    s.LoadString(IDS_QUANTITY_LBLRPT);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;

    // If a grid view, insert a group control for months
    if (pView)
    {
        // Retrieve the current position
        m_postream->GetCurSel(left, top);

        CString Label;
        Label.LoadString(IDS_CHKBOX_LABEL);

        CString ToolTipText;
        ToolTipText.LoadString(IDS_CHKBOX_TTP);

        pView->InsertGroupCtrl(top - 2,
                               left,            // row col
                               12,                // covering cells
                               true,            // horizontal
                               true,            // collapsed
                               Label,
                               ToolTipText);
    }

    // Insert the tab
    *m_postream << _T("\t");

    // Next cell is the quantity for each month
    s.LoadString(IDS_MONTH_LBLRPT1);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT2);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT3);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT4);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT5);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT6);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT7);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT8);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT9);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT10);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT11);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT12);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // Next cell is the procedure activation percent 
    s.LoadString(IDS_PERCACTPROCEDURE_LBLRPT);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;

    // If a grid view, insert a group control for months
    if (pView)
    {
        // Retrieve the current position
        m_postream->GetCurSel(left, top);

        CString Label;
        Label.LoadString(IDS_CHKBOX_LABEL);

        CString ToolTipText;
        ToolTipText.LoadString(IDS_CHKBOX_TTP);

        pView->InsertGroupCtrl(top - 2,
                               left,            // row col
                               12,                // covering cells
                               true,            // horizontal
                               true,            // collapsed
                               Label,
                               ToolTipText);
    }

    // Insert the tab
    *m_postream << _T("\t");

    // Next cell is the quantity for each month
    s.LoadString(IDS_MONTH_LBLRPT1);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT2);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT3);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT4);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT5);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT6);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT7);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT8);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT9);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT10);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT11);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT12);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // Next cell is the procedure cost
    s.LoadString(IDS_PROCEDURECOST_LBLRPT);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;

    // If a grid view, insert a group control for months
    if (pView)
    {
        // Retrieve the current position
        m_postream->GetCurSel(left, top);

        CString Label;
        Label.LoadString(IDS_CHKBOX_LABEL);

        CString ToolTipText;
        ToolTipText.LoadString(IDS_CHKBOX_TTP);

        pView->InsertGroupCtrl(top - 2,
                               left,            // row col
                               12,                // covering cells
                               true,            // horizontal
                               true,            // collapsed
                               Label,
                               ToolTipText);
    }

    // Insert the tab
    *m_postream << _T("\t");

    // Next cell is the quantity for each month
    s.LoadString(IDS_MONTH_LBLRPT1);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT2);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT3);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT4);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT5);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT6);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT7);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT8);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT9);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT10);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT11);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT12);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // Next cell is the forecasted procedure workload
    s.LoadString(IDS_FORCPROCWORKLOAD_LBLRPT);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;

    // If a grid view, insert a group control for months
    if (pView)
    {
        // Retrieve the current position
        m_postream->GetCurSel(left, top);

        CString Label;
        Label.LoadString(IDS_CHKBOX_LABEL);

        CString ToolTipText;
        ToolTipText.LoadString(IDS_CHKBOX_TTP);

        pView->InsertGroupCtrl(top - 2,
                               left,            // row col
                               12,                // covering cells
                               true,            // horizontal
                               true,            // collapsed
                               Label,
                               ToolTipText);
    }

    // Insert the tab
    *m_postream << "\t";

    // Next cell is the quantity for each month
    s.LoadString(IDS_MONTH_LBLRPT1);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT2);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT3);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT4);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT5);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT6);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT7);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT8);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT9);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT10);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT11);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT12);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // Next cell is the forecasted procedure cost
    s.LoadString(IDS_FORCPROCCOST_LBLRPT);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;

    // If a grid view, insert a group control for months
    if (pView)
    {
        // Retrieve the current position
        m_postream->GetCurSel(left, top);

        CString Label;
        Label.LoadString(IDS_CHKBOX_LABEL);

        CString ToolTipText;
        ToolTipText.LoadString(IDS_CHKBOX_TTP);

        pView->InsertGroupCtrl(top - 2,
                               left,            // row col
                               12,                // covering cells
                               true,            // horizontal
                               true,            // collapsed
                               Label,
                               ToolTipText);
    }

    // Insert the tab
    *m_postream << _T("\t");

    // Next cell is the quantity for each month
    s.LoadString(IDS_MONTH_LBLRPT1);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT2);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT3);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT4);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT5);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT6);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT7);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT8);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT9);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT10);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT11);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    s.LoadString(IDS_MONTH_LBLRPT12);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // Next cell is the procedure cost per activation
    s.LoadString(IDS_PROCCOSTPERACT_LBLRPT);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // Next cell is the procedure workload per activation
    s.LoadString(IDS_PROCWORKLOADPERACT_LBLRPT);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // Next cell is the forecasted process cost
    s.LoadString(IDS_FORCPROCESSCOST_LBLRPT);
    *m_postream << s;
    *m_postream << m_RoseStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    if (pProcess)
    {
        // Next cell is the forecasted process cost itself
        *m_postream << pProcess->GetProcessCostForecast().GetNumberYear();
        *m_postream << m_LightGrayStyle;
        *m_postream << m_BlackBorderStyle;
        *m_postream << m_NumericCellStyle;
        *m_postream << m_AmountFormatStyle;
        *m_postream << _T("\t");

        // The forecasted process cost for each month
        for (int i = 0; i < 12; ++i)
        {
            *m_postream << pProcess->GetProcessCostForecast().GetNumberAt(i);
            *m_postream << m_LightGrayStyle;
            *m_postream << m_NumericCellStyle;
            *m_postream << m_AmountFormatStyle;
            *m_postream << _T("\t");
        }
    }

    /*
        // JMR-MODIF - Le 29 mars 2006 - Suppression du code ci-dessous, car inutile.
        // Change the default properties
        CGXProperties* pProperties = m_postream->GetGridCore()->GetParam()->GetProperties();

        if ( pProperties )
        {
        }
    */

    return (m_postream) ? true : false;
}

bool ZUGridSesterceProcessNavigation::OnFinish()
{
    int top;
    int left;
    m_postream->GetCurSel(left, top);

    // Retrieve the grid view
    ZVGridView*    pView = NULL;
    CWnd*        pWnd = m_postream->GetGridCore()->GridWnd();

    if (pWnd && ISA(pWnd, ZVGridView))
    {
        pView = dynamic_cast<ZVGridView*>(pWnd);
    }

    ZDGridDocument* pDoc = pView->GetDocument();

    if (pDoc)
    {
        pDoc->SetFrozenRow(3);
        pDoc->SetFrozenCol(1);

        pDoc->SetFrozenHeaderRow(3);
        pDoc->SetFrozenHeaderCol(1);
        pView->FreezeSplitter();
    }

    return true;
}

bool ZUGridSesterceProcessNavigation::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    int top;
    int left;

    // Check the number of row
    ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
    m_postream->GetCurSel(left, top);

    // If not enough, add 5 rows
    if ((top + 5) > (int)RowCount)
    {
        m_postream->GetGridCore()->SetRowCount(RowCount + 5);
    }

    // Check the number of column
    ROWCOL ColCount = m_postream->GetGridCore()->GetColCount();

    // If not enough, add 30 columns
    if ((left + 30) > (int)ColCount)
    {
        m_postream->GetGridCore()->SetColCount(ColCount + 30);
    }

    *m_postream << _T("\n");

    // The procedure name
    *m_postream << pSymbol->GetSymbolName();
    *m_postream << m_NormalStyle;
    *m_postream << _T("\t");

    // Right three times
    *m_postream << m_RoseStyle;
    *m_postream << _T("\t");

    // The unit name
    *m_postream << pSymbol->GetUnitName();
    *m_postream << m_NormalStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // The unitary cost
    *m_postream << pSymbol->GetUnitaryCost();
    *m_postream << m_NormalStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << m_NumericCellStyle;
    *m_postream << m_AmountFormatStyle;
    *m_postream << _T("\t");

    // Right two times
    *m_postream << m_RoseStyle;
    *m_postream << _T("\t");
    *m_postream << m_RoseStyle;
    *m_postream << _T("\t");

    // The multiplier
    *m_postream << pSymbol->GetMultiplier();
    *m_postream << m_NormalStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << m_NumericCellStyle;
    *m_postream << m_AmountFormatStyle;
    *m_postream << _T("\t");

    // The standard time
    *m_postream << pSymbol->GetProcessingTime();
    *m_postream << m_LightGrayStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << m_NumericCellStyle;
    *m_postream << m_NumberTwoDecFormatStyle;
    *m_postream << _T("\t");

    // Right 13 times
    for (int i = 0; i < 13; ++i)
    {
        *m_postream << m_GrayStyle;
        *m_postream << _T("\t");
    }

    // The procedure activation
    *m_postream << pSymbol->GetProcedureActivation().GetNumberYear();
    *m_postream << m_LightGrayStyle;
    *m_postream << m_NumericCellStyle;
    *m_postream << m_AmountFormatStyle;
    *m_postream << _T("\t");

    // The procedure activation for each month
    for (int i = 0; i < 12; ++i)
    {
        *m_postream << pSymbol->GetProcedureActivation().GetNumberAt(i);
        *m_postream << m_LightGrayStyle;
        *m_postream << m_NumericCellStyle;
        *m_postream << m_AmountFormatStyle;
        *m_postream << _T("\t");
    }

    // The procedure cost
    *m_postream << pSymbol->GetProcedureCost().GetNumberYear();
    *m_postream << m_LightGrayStyle;
    *m_postream << m_NumericCellStyle;
    *m_postream << m_AmountFormatStyle;
    *m_postream << _T("\t");

    // The procedure cost for each month
    for (int i = 0; i < 12; ++i)
    {
        *m_postream << pSymbol->GetProcedureCost().GetNumberAt(i);
        *m_postream << m_LightGrayStyle;
        *m_postream << m_NumericCellStyle;
        *m_postream << m_AmountFormatStyle;
        *m_postream << _T("\t");
    }

    // The procedure workload forecast
    *m_postream << pSymbol->GetProcedureWorkloadForecast().GetNumberYear();
    *m_postream << m_LightGrayStyle;
    *m_postream << m_NumericCellStyle;
    *m_postream << m_AmountFormatStyle;
    *m_postream << _T("\t");

    // The procedure workload for each month
    for (int i = 0; i < 12; ++i)
    {
        *m_postream << pSymbol->GetProcedureWorkloadForecast().GetNumberAt(i);
        *m_postream << m_LightGrayStyle;
        *m_postream << m_NumericCellStyle;
        *m_postream << m_AmountFormatStyle;
        *m_postream << _T("\t");
    }

    // The procedure cost forecast
    *m_postream << pSymbol->GetProcedureCostForecast().GetNumberYear();
    *m_postream << m_LightGrayStyle;
    *m_postream << m_NumericCellStyle;
    *m_postream << m_AmountFormatStyle;
    *m_postream << _T("\t");

    // The procedure cost for each month
    for (int i = 0; i < 12; ++i)
    {
        *m_postream << pSymbol->GetProcedureCostForecast().GetNumberAt(i);
        *m_postream << m_LightGrayStyle;
        *m_postream << m_NumericCellStyle;
        *m_postream << m_AmountFormatStyle;
        *m_postream << _T("\t");
    }

    // The procedure cost per activation
    *m_postream << pSymbol->GetProcedureCostPerActivity();
    *m_postream << m_LightGrayStyle;
    *m_postream << m_NumericCellStyle;
    *m_postream << m_AmountFormatStyle;
    *m_postream << _T("\t");

    // The procedure workload per activation
    *m_postream << pSymbol->GetProcedureWorkloadPerActivity();
    *m_postream << m_LightGrayStyle;
    *m_postream << m_NumericCellStyle;
    *m_postream << m_AmountFormatStyle;
    *m_postream << _T("\t");

    return true;
}

bool ZUGridSesterceProcessNavigation::OnDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol)
{
    int top;
    int left;

    // Check the number of row
    ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
    m_postream->GetCurSel(left, top);

    // If not enough, add 5 rows
    if ((top + 5) > (int)RowCount)
    {
        m_postream->GetGridCore()->SetRowCount(RowCount + 5);
    }

    // Check the number of column
    ROWCOL ColCount = m_postream->GetGridCore()->GetColCount();

    // If not enough, add 30 columns
    if ((left + 30) > (int)ColCount)
    {
        m_postream->GetGridCore()->SetColCount(ColCount + 30);
    }

    *m_postream << _T("\n");

    // The deliverable name
    *m_postream << pSymbol->GetSymbolName();

    if (pSymbol->IsInitial())
    {
        *m_postream << m_GreenStyle;
    }
    else if (pSymbol->IsFinal())
    {
        *m_postream << m_RedStyle;
    }
    else if (pSymbol->IsInterProcess())
    {
        *m_postream << m_BlueStyle;
    }
    else
    {
        *m_postream << m_LightGrayStyle;
    }

    *m_postream << _T("\t");

    // The deliverable output percent
    *m_postream << pSymbol->GetOutWorkloadPercent();
    *m_postream << m_NormalStyle;
    *m_postream << m_NumericCellStyle;
    *m_postream << m_PercentFormatStyle;
    *m_postream << _T("\t");

    // Right one time
    *m_postream << m_RoseStyle;
    *m_postream << _T("\t");

    // The unitary cost
    *m_postream << pSymbol->GetUnitaryCost();
    *m_postream << m_NormalStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << m_NumericCellStyle;
    *m_postream << m_AmountFormatStyle;
    *m_postream << _T("\t");

    // The combination name
    if (pSymbol->IsFinal())
    {
        *m_postream << _T("");
    }
    else
    {
        *m_postream << pSymbol->GetCombinationName();
    }

    *m_postream << m_NormalStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << _T("\t");

    // Not for final deliverables
    if (pSymbol->IsFinal())
    {
        *m_postream << _T("");
        *m_postream << m_NormalStyle;
        *m_postream << m_BlackBorderStyle;
    }
    else
    {
        float value = pSymbol->GetCombinationMaxPercentage();

        if (value != (float)INT_MAX)
        {
            *m_postream << value;
            *m_postream << m_NormalStyle;
            *m_postream << m_NumericCellStyle;
            *m_postream << m_PercentFormatStyle;
        }
        else
        {
            *m_postream << _T("#ERR");
            *m_postream << m_NormalStyle;
            *m_postream << m_BlackBorderStyle;
        }
    }

    *m_postream << _T("\t");

    // Right one time
    *m_postream << m_GrayStyle;
    *m_postream << _T("\t");

    // The standard time
    *m_postream << pSymbol->GetProcessingTime();
    *m_postream << m_NormalStyle;
    *m_postream << m_BlackBorderStyle;
    *m_postream << m_NumericCellStyle;
    *m_postream << m_AmountFormatStyle;
    *m_postream << _T("\t");

    // The quantity
    *m_postream << pSymbol->GetQuantityYear();
    *m_postream << m_LightGrayStyle;
    *m_postream << m_NumericCellStyle;
    *m_postream << m_AmountFormatStyle;
    *m_postream << _T("\t");

    // The quantity for each month
    for (int i = 0; i < 12; ++i)
    {
        *m_postream << pSymbol->GetQuantity().GetNumberAt(i);
        *m_postream << m_LightGrayStyle;
        *m_postream << m_NumericCellStyle;
        *m_postream << m_AmountFormatStyle;
        *m_postream << _T("\t");
    }

    // Right 13 times
    for (int i = 0; i < 13; ++i)
    {
        *m_postream << m_GrayStyle;
        *m_postream << _T("\t");
    }

    // The deliverable cost
    *m_postream << pSymbol->GetCost().GetNumberYear();
    *m_postream << m_LightGrayStyle;
    *m_postream << m_NumericCellStyle;
    *m_postream << m_AmountFormatStyle;
    *m_postream << _T("\t");

    // The deliverable cost for each month
    for (int i = 0; i < 12; ++i)
    {
        *m_postream << pSymbol->GetCost().GetNumberAt(i);
        *m_postream << m_LightGrayStyle;
        *m_postream << m_NumericCellStyle;
        *m_postream << m_AmountFormatStyle;
        *m_postream << _T("\t");
    }

    // The deliverable cost
    *m_postream << pSymbol->GetWorkloadForecast().GetNumberYear();
    *m_postream << m_LightGrayStyle;
    *m_postream << m_NumericCellStyle;
    *m_postream << m_AmountFormatStyle;
    *m_postream << _T("\t");

    // The deliverable cost for each month
    for (int i = 0; i < 12; ++i)
    {
        *m_postream << pSymbol->GetWorkloadForecast().GetNumberAt(i);
        *m_postream << m_LightGrayStyle;
        *m_postream << m_NumericCellStyle;
        *m_postream << m_AmountFormatStyle;
        *m_postream << _T("\t");
    }

    // Right 13 times
    for (int i = 0; i < 13; ++i)
    {
        *m_postream << m_GrayStyle;
        *m_postream << _T("\t");
    }

    // Right two times
    *m_postream << m_GrayStyle;
    *m_postream << _T("\t");
    *m_postream << m_GrayStyle;
    *m_postream << _T("\t");

    return true;
}
//---------------------------------------------------------------------------
