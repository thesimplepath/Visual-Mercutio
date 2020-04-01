/****************************************************************************
 * ==> PSS_GridSesterceProcessNavigation -----------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will navigate through the       *
 *               processes and write the Sesterce info to the report        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GridSesterceProcessNavigation.h"

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
#include "zReport\PSS_GridDocument.h"
#include "zReport\PSS_OStreamGrid.h"
#include "zReport\PSS_GridView.h"
#include "zReport\PSS_GridGroup.h"
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
// PSS_GridSesterceProcessNavigation
//---------------------------------------------------------------------------
PSS_GridSesterceProcessNavigation::PSS_GridSesterceProcessNavigation(PSS_ProcessGraphModelMdl* pModel,
                                                                     void*                     pClass) :
    PSS_ProcessNavigation(pModel, pClass),
    m_pOStream(NULL)
{}
//---------------------------------------------------------------------------
PSS_GridSesterceProcessNavigation::~PSS_GridSesterceProcessNavigation()
{}
//---------------------------------------------------------------------------
bool PSS_GridSesterceProcessNavigation::OnStart()
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

    if (!m_pModel)
        return false;

    // find the process matching with the model name, case sensitive and only local symbols
    PSS_ProcessSymbolBP* pProcess = NULL;
    CODComponentSet*     pSet     = m_pModel->GetRoot()->FindSymbol(m_pModel->GetModelName(), _T(""), true, true, true);

    if (pSet && pSet->GetSize() > 0)
        pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pSet->GetAt(0));

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

    // initialize the rose style for header cells
    m_RoseStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(10).SetBold(FALSE))
            .SetInterior(M_Color_RoseSesterce);

    // initialize the bold rose style for header cells
    m_BoldRoseStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(10).SetBold(TRUE))
            .SetInterior(M_Color_RoseSesterce);

    // initialize the blue style
    m_BlueStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(9).SetBold(FALSE))
            .SetInterior(M_Color_BlueMercutio);

    // initialize the green style
    m_GreenStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(9).SetBold(FALSE))
            .SetInterior(M_Color_StartGreen);

    // initialize the red style
    m_RedStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(9).SetBold(FALSE))
            .SetInterior(M_Color_EndRed);

    // Initialize the gray style for header cells
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
    m_AmountFormatStyle.SetFormat(GX_FMT_COMMA).SetPlaces(0);
    m_NumberTwoDecFormatStyle.SetFormat(GX_FMT_FIXED).SetPlaces(2);
    m_NumericCellStyle.SetValueType(GX_VT_NUMERIC).SetPlaces(0);

    // set the default row height and column width for all cells
    m_pOStream->GetGridCore()->SetDefaultRowHeight(20);
    m_pOStream->GetGridCore()->SetDefaultColWidth(80);

    // show the header, check the number of row
    const ROWCOL rowCount = m_pOStream->GetGridCore()->GetRowCount();

    int left;
    int top;

    m_pOStream->GetCurSel(left, top);

    // if not enough, add the missing rows
    if ((top + 5) > int(rowCount))
        m_pOStream->GetGridCore()->SetRowCount(rowCount + 5);

    // check the column count
    const ROWCOL colCount = m_pOStream->GetGridCore()->GetColCount();

    // if not enough, add the missing columns
    if ((left + 120) > int(colCount))
        m_pOStream->GetGridCore()->SetColCount(colCount + 120);

    // first row is for control and for monthly label to process information
    m_pOStream->Right(77);

    // get the grid view
    PSS_GridView* pGridView = dynamic_cast<PSS_GridView*>(m_pOStream->GetGridCore()->GridWnd());

    // insert a group control for months
    if (pGridView)
    {
        // get the current position
        m_pOStream->GetCurSel(left, top);

        CString label;
        label.LoadString(IDS_CHKBOX_LABEL);

        CString tooltipText;
        tooltipText.LoadString(IDS_CHKBOX_TTP);

        pGridView->InsertGroupCtrl(top,
                                   left,
                                   13,
                                   true,
                                   true,
                                   label,
                                   tooltipText);
    }

    *m_pOStream << m_NormalStyle;
    *m_pOStream << _T("\t");

    CString str;

    // inserts all the month labels
    str.LoadString(IDS_MONTH_LBLRPT1);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT2);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT3);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT4);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT5);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT6);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT7);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT8);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT9);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT10);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT11);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT12);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\n");

    // cell A1
    *m_pOStream << CSize(200, 80);
    *m_pOStream << m_RoseStyle;
    *m_pOStream << _T("\t");

    // next cells
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 7);
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
     m_pOStream->Right(8);

    // next cells
     m_pOStream->GetCurSel(left, top);
     m_pOStream->GetGridCore()->SetCoveredCellsRowCol(top, left, top, left + 66);
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
     m_pOStream->Right(67);

    // next cell is the forecasted process workload
    str.LoadString(IDS_FORECWORKLOADPROCESS_LBLRPT);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // next cell is the forecasted process workload itself
    if (pProcess)
    {
        *m_pOStream << pProcess->GetProcessWorkloadForecast().GetNumberYear();
        *m_pOStream << m_LightGrayStyle;
        *m_pOStream << m_BlackBorderStyle;
        *m_pOStream << m_NumericCellStyle;
        *m_pOStream << m_AmountFormatStyle;
        *m_pOStream << _T("\t");

        // the forecasted process cost for each month
        for (int i = 0; i < 12; ++i)
        {
            *m_pOStream << pProcess->GetProcessWorkloadForecast().GetNumberAt(i);
            *m_pOStream << m_LightGrayStyle;
            *m_pOStream << m_NumericCellStyle;
            *m_pOStream << m_AmountFormatStyle;
            *m_pOStream << _T("\t");
        }
    }

    // build the second header line
    *m_pOStream << _T("\n");
    *m_pOStream << CSize(200, 80);
    *m_pOStream << m_RoseStyle;
    *m_pOStream << _T("\t");

    // next cell is the output percent
    str.LoadString(IDS_PERCOUT_LBLRPT);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // next cell is the unit name
    str.LoadString(IDS_UNIT_LBLRPT);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // next cell is the unitary cost
    str.LoadString(IDS_UNITARYCOST_LBLRPT);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // next cell is the combination name
    str.LoadString(IDS_COMBINATIONNAME_LBLRPT);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // next cell is the percent combination activation
    str.LoadString(IDS_COMBPERC_LBLRPT);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // next cell is the multiplicator
    str.LoadString(IDS_MULTIPLICATOR_LBLRPT);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // next cell is the standard time
    str.LoadString(IDS_STANDARDTIME_LBLRPT);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // next cell is the quantity
    str.LoadString(IDS_QUANTITY_LBLRPT);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;

    // insert a group control for months
    if (pGridView)
    {
        // get the current position
        m_pOStream->GetCurSel(left, top);

        CString label;
        label.LoadString(IDS_CHKBOX_LABEL);

        CString tooltipText;
        tooltipText.LoadString(IDS_CHKBOX_TTP);

        pGridView->InsertGroupCtrl(top - 2,
                                   left,
                                   12,
                                   true,
                                   true,
                                   label,
                                   tooltipText);
    }

    // insert the tab
    *m_pOStream << _T("\t");

    // next cells are the quantity for each month
    str.LoadString(IDS_MONTH_LBLRPT1);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT2);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT3);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT4);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT5);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT6);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT7);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT8);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT9);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT10);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT11);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT12);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // next cell is the procedure activation percent 
    str.LoadString(IDS_PERCACTPROCEDURE_LBLRPT);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;

    // insert a group control for months
    if (pGridView)
    {
        // get the current position
        m_pOStream->GetCurSel(left, top);

        CString label;
        label.LoadString(IDS_CHKBOX_LABEL);

        CString tooltipText;
        tooltipText.LoadString(IDS_CHKBOX_TTP);

        pGridView->InsertGroupCtrl(top - 2,
                                   left,
                                   12,
                                   true,
                                   true,
                                   label,
                                   tooltipText);
    }

    // insert the tab
    *m_pOStream << _T("\t");

    // next cells are the quantity for each month
    str.LoadString(IDS_MONTH_LBLRPT1);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT2);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT3);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT4);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT5);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT6);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT7);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT8);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT9);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT10);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT11);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT12);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // next cell is the procedure cost
    str.LoadString(IDS_PROCEDURECOST_LBLRPT);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;

    // insert a group control for months
    if (pGridView)
    {
        // get the current position
        m_pOStream->GetCurSel(left, top);

        CString label;
        label.LoadString(IDS_CHKBOX_LABEL);

        CString tooltipText;
        tooltipText.LoadString(IDS_CHKBOX_TTP);

        pGridView->InsertGroupCtrl(top - 2,
                                   left,
                                   12,
                                   true,
                                   true,
                                   label,
                                   tooltipText);
    }

    // insert the tab
    *m_pOStream << _T("\t");

    // next cell is the quantity for each month
    str.LoadString(IDS_MONTH_LBLRPT1);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT2);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT3);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT4);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT5);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT6);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT7);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT8);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT9);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT10);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT11);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT12);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // next cell is the forecasted procedure workload
    str.LoadString(IDS_FORCPROCWORKLOAD_LBLRPT);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;

    // insert a group control for months
    if (pGridView)
    {
        // get the current position
        m_pOStream->GetCurSel(left, top);

        CString label;
        label.LoadString(IDS_CHKBOX_LABEL);

        CString tooltipText;
        tooltipText.LoadString(IDS_CHKBOX_TTP);

        pGridView->InsertGroupCtrl(top - 2,
                                   left,
                                   12,
                                   true,
                                   true,
                                   label,
                                   tooltipText);
    }

    // insert the tab
    *m_pOStream << "\t";

    // next cells are the quantity for each month
    str.LoadString(IDS_MONTH_LBLRPT1);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT2);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT3);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT4);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT5);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT6);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT7);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT8);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT9);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT10);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT11);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT12);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // next cell is the forecasted procedure cost
    str.LoadString(IDS_FORCPROCCOST_LBLRPT);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;

    // insert a group control for months
    if (pGridView)
    {
        // get the current position
        m_pOStream->GetCurSel(left, top);

        CString label;
        label.LoadString(IDS_CHKBOX_LABEL);

        CString tooltipText;
        tooltipText.LoadString(IDS_CHKBOX_TTP);

        pGridView->InsertGroupCtrl(top - 2,
                                   left,
                                   12,
                                   true,
                                   true,
                                   label,
                                   tooltipText);
    }

    // insert the tab
    *m_pOStream << _T("\t");

    // next cells are the quantity for each month
    str.LoadString(IDS_MONTH_LBLRPT1);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT2);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT3);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT4);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT5);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT6);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT7);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT8);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT9);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT10);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT11);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_MONTH_LBLRPT12);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // next cell is the procedure cost per activation
    str.LoadString(IDS_PROCCOSTPERACT_LBLRPT);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // next cell is the procedure workload per activation
    str.LoadString(IDS_PROCWORKLOADPERACT_LBLRPT);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // next cell is the forecasted process cost
    str.LoadString(IDS_FORCPROCESSCOST_LBLRPT);
    *m_pOStream << str;
    *m_pOStream << m_RoseStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    if (pProcess)
    {
        // next cell is the forecasted process cost itself
        *m_pOStream << pProcess->GetProcessCostForecast().GetNumberYear();
        *m_pOStream << m_LightGrayStyle;
        *m_pOStream << m_BlackBorderStyle;
        *m_pOStream << m_NumericCellStyle;
        *m_pOStream << m_AmountFormatStyle;
        *m_pOStream << _T("\t");

        // the forecasted process cost for each month
        for (int i = 0; i < 12; ++i)
        {
            *m_pOStream << pProcess->GetProcessCostForecast().GetNumberAt(i);
            *m_pOStream << m_LightGrayStyle;
            *m_pOStream << m_NumericCellStyle;
            *m_pOStream << m_AmountFormatStyle;
            *m_pOStream << _T("\t");
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridSesterceProcessNavigation::OnFinish()
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

    // get the grid view and the document
    PSS_GridView*     pView = dynamic_cast<PSS_GridView*>(m_pOStream->GetGridCore()->GridWnd());
    PSS_GridDocument* pDoc  = pView->GetDocument();

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
//---------------------------------------------------------------------------
bool PSS_GridSesterceProcessNavigation::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
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
    if ((top + 5) > int(rowCount))
        m_pOStream->GetGridCore()->SetRowCount(rowCount + 5);

    // check the column count
    const ROWCOL colCount = m_pOStream->GetGridCore()->GetColCount();

    // if not enough, add the missing columns
    if ((left + 30) > int(colCount))
        m_pOStream->GetGridCore()->SetColCount(colCount + 30);

    *m_pOStream << _T("\n");

    // the procedure name
    *m_pOStream << pSymbol->GetSymbolName();
    *m_pOStream << m_NormalStyle;
    *m_pOStream << _T("\t");

    // right three times
    *m_pOStream << m_RoseStyle;
    *m_pOStream << _T("\t");

    // the unit name
    *m_pOStream << pSymbol->GetUnitName();
    *m_pOStream << m_NormalStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // the unitary cost
    *m_pOStream << pSymbol->GetUnitaryCost();
    *m_pOStream << m_NormalStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << m_NumericCellStyle;
    *m_pOStream << m_AmountFormatStyle;
    *m_pOStream << _T("\t");

    // right two times
    *m_pOStream << m_RoseStyle;
    *m_pOStream << _T("\t");
    *m_pOStream << m_RoseStyle;
    *m_pOStream << _T("\t");

    // the multiplier
    *m_pOStream << pSymbol->GetMultiplier();
    *m_pOStream << m_NormalStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << m_NumericCellStyle;
    *m_pOStream << m_AmountFormatStyle;
    *m_pOStream << _T("\t");

    // the standard time
    *m_pOStream << pSymbol->GetProcessingTime();
    *m_pOStream << m_LightGrayStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << m_NumericCellStyle;
    *m_pOStream << m_NumberTwoDecFormatStyle;
    *m_pOStream << _T("\t");

    // right 13 times
    for (int i = 0; i < 13; ++i)
    {
        *m_pOStream << m_GrayStyle;
        *m_pOStream << _T("\t");
    }

    // the procedure activation
    *m_pOStream << pSymbol->GetProcedureActivation().GetNumberYear();
    *m_pOStream << m_LightGrayStyle;
    *m_pOStream << m_NumericCellStyle;
    *m_pOStream << m_AmountFormatStyle;
    *m_pOStream << _T("\t");

    // the procedure activation for each month
    for (int i = 0; i < 12; ++i)
    {
        *m_pOStream << pSymbol->GetProcedureActivation().GetNumberAt(i);
        *m_pOStream << m_LightGrayStyle;
        *m_pOStream << m_NumericCellStyle;
        *m_pOStream << m_AmountFormatStyle;
        *m_pOStream << _T("\t");
    }

    // the procedure cost
    *m_pOStream << pSymbol->GetProcedureCost().GetNumberYear();
    *m_pOStream << m_LightGrayStyle;
    *m_pOStream << m_NumericCellStyle;
    *m_pOStream << m_AmountFormatStyle;
    *m_pOStream << _T("\t");

    // the procedure cost for each month
    for (int i = 0; i < 12; ++i)
    {
        *m_pOStream << pSymbol->GetProcedureCost().GetNumberAt(i);
        *m_pOStream << m_LightGrayStyle;
        *m_pOStream << m_NumericCellStyle;
        *m_pOStream << m_AmountFormatStyle;
        *m_pOStream << _T("\t");
    }

    // the procedure workload forecast
    *m_pOStream << pSymbol->GetProcedureWorkloadForecast().GetNumberYear();
    *m_pOStream << m_LightGrayStyle;
    *m_pOStream << m_NumericCellStyle;
    *m_pOStream << m_AmountFormatStyle;
    *m_pOStream << _T("\t");

    // the procedure workload for each month
    for (int i = 0; i < 12; ++i)
    {
        *m_pOStream << pSymbol->GetProcedureWorkloadForecast().GetNumberAt(i);
        *m_pOStream << m_LightGrayStyle;
        *m_pOStream << m_NumericCellStyle;
        *m_pOStream << m_AmountFormatStyle;
        *m_pOStream << _T("\t");
    }

    // the procedure cost forecast
    *m_pOStream << pSymbol->GetProcedureCostForecast().GetNumberYear();
    *m_pOStream << m_LightGrayStyle;
    *m_pOStream << m_NumericCellStyle;
    *m_pOStream << m_AmountFormatStyle;
    *m_pOStream << _T("\t");

    // the procedure cost for each month
    for (int i = 0; i < 12; ++i)
    {
        *m_pOStream << pSymbol->GetProcedureCostForecast().GetNumberAt(i);
        *m_pOStream << m_LightGrayStyle;
        *m_pOStream << m_NumericCellStyle;
        *m_pOStream << m_AmountFormatStyle;
        *m_pOStream << _T("\t");
    }

    // the procedure cost per activation
    *m_pOStream << pSymbol->GetProcedureCostPerActivity();
    *m_pOStream << m_LightGrayStyle;
    *m_pOStream << m_NumericCellStyle;
    *m_pOStream << m_AmountFormatStyle;
    *m_pOStream << _T("\t");

    // the procedure workload per activation
    *m_pOStream << pSymbol->GetProcedureWorkloadPerActivity();
    *m_pOStream << m_LightGrayStyle;
    *m_pOStream << m_NumericCellStyle;
    *m_pOStream << m_AmountFormatStyle;
    *m_pOStream << _T("\t");

    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridSesterceProcessNavigation::OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol)
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
    if ((top + 5) > int(rowCount))
        m_pOStream->GetGridCore()->SetRowCount(rowCount + 5);

    // check the column count
    const ROWCOL colCount = m_pOStream->GetGridCore()->GetColCount();

    // if not enough, add 30 columns
    if ((left + 30) > int(colCount))
        m_pOStream->GetGridCore()->SetColCount(colCount + 30);

    *m_pOStream << _T("\n");

    // the deliverable name
    *m_pOStream << pSymbol->GetSymbolName();

    if (pSymbol->IsInitial())
        *m_pOStream << m_GreenStyle;
    else
    if (pSymbol->IsFinal())
        *m_pOStream << m_RedStyle;
    else
    if (pSymbol->IsInterProcess())
        *m_pOStream << m_BlueStyle;
    else
        *m_pOStream << m_LightGrayStyle;

    *m_pOStream << _T("\t");

    // the deliverable output percent
    *m_pOStream << pSymbol->GetOutWorkloadPercent();
    *m_pOStream << m_NormalStyle;
    *m_pOStream << m_NumericCellStyle;
    *m_pOStream << m_PercentFormatStyle;
    *m_pOStream << _T("\t");

    // right one time
    *m_pOStream << m_RoseStyle;
    *m_pOStream << _T("\t");

    // the unitary cost
    *m_pOStream << pSymbol->GetUnitaryCost();
    *m_pOStream << m_NormalStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << m_NumericCellStyle;
    *m_pOStream << m_AmountFormatStyle;
    *m_pOStream << _T("\t");

    // the combination name
    if (pSymbol->IsFinal())
        *m_pOStream << _T("");
    else
        *m_pOStream << pSymbol->GetCombinationName();

    *m_pOStream << m_NormalStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << _T("\t");

    // not for final deliverables
    if (pSymbol->IsFinal())
    {
        *m_pOStream << _T("");
        *m_pOStream << m_NormalStyle;
        *m_pOStream << m_BlackBorderStyle;
    }
    else
    {
        const float value = pSymbol->GetCombinationMaxPercentage();

        if (value != float(INT_MAX))
        {
            *m_pOStream << value;
            *m_pOStream << m_NormalStyle;
            *m_pOStream << m_NumericCellStyle;
            *m_pOStream << m_PercentFormatStyle;
        }
        else
        {
            *m_pOStream << _T("#ERR");
            *m_pOStream << m_NormalStyle;
            *m_pOStream << m_BlackBorderStyle;
        }
    }

    *m_pOStream << _T("\t");

    // right one time
    *m_pOStream << m_GrayStyle;
    *m_pOStream << _T("\t");

    // the standard time
    *m_pOStream << pSymbol->GetProcessingTime();
    *m_pOStream << m_NormalStyle;
    *m_pOStream << m_BlackBorderStyle;
    *m_pOStream << m_NumericCellStyle;
    *m_pOStream << m_AmountFormatStyle;
    *m_pOStream << _T("\t");

    // the quantity
    *m_pOStream << pSymbol->GetQuantityYear();
    *m_pOStream << m_LightGrayStyle;
    *m_pOStream << m_NumericCellStyle;
    *m_pOStream << m_AmountFormatStyle;
    *m_pOStream << _T("\t");

    // the quantity for each month
    for (int i = 0; i < 12; ++i)
    {
        *m_pOStream << pSymbol->GetQuantity().GetNumberAt(i);
        *m_pOStream << m_LightGrayStyle;
        *m_pOStream << m_NumericCellStyle;
        *m_pOStream << m_AmountFormatStyle;
        *m_pOStream << _T("\t");
    }

    // right 13 times
    for (int i = 0; i < 13; ++i)
    {
        *m_pOStream << m_GrayStyle;
        *m_pOStream << _T("\t");
    }

    // the deliverable cost
    *m_pOStream << pSymbol->GetCost().GetNumberYear();
    *m_pOStream << m_LightGrayStyle;
    *m_pOStream << m_NumericCellStyle;
    *m_pOStream << m_AmountFormatStyle;
    *m_pOStream << _T("\t");

    // the deliverable cost for each month
    for (int i = 0; i < 12; ++i)
    {
        *m_pOStream << pSymbol->GetCost().GetNumberAt(i);
        *m_pOStream << m_LightGrayStyle;
        *m_pOStream << m_NumericCellStyle;
        *m_pOStream << m_AmountFormatStyle;
        *m_pOStream << _T("\t");
    }

    // the deliverable cost
    *m_pOStream << pSymbol->GetWorkloadForecast().GetNumberYear();
    *m_pOStream << m_LightGrayStyle;
    *m_pOStream << m_NumericCellStyle;
    *m_pOStream << m_AmountFormatStyle;
    *m_pOStream << _T("\t");

    // the deliverable cost for each month
    for (int i = 0; i < 12; ++i)
    {
        *m_pOStream << pSymbol->GetWorkloadForecast().GetNumberAt(i);
        *m_pOStream << m_LightGrayStyle;
        *m_pOStream << m_NumericCellStyle;
        *m_pOStream << m_AmountFormatStyle;
        *m_pOStream << _T("\t");
    }

    // right 13 times
    for (int i = 0; i < 13; ++i)
    {
        *m_pOStream << m_GrayStyle;
        *m_pOStream << _T("\t");
    }

    // right two times
    *m_pOStream << m_GrayStyle;
    *m_pOStream << _T("\t");
    *m_pOStream << m_GrayStyle;
    *m_pOStream << _T("\t");

    return true;
}
//---------------------------------------------------------------------------
