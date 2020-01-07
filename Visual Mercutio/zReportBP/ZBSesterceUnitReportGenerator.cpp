// ZBSesterceUnitReportGenerator.cpp: implementation of the ZBSesterceUnitReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBSesterceUnitReportGenerator.h"

#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModelBP\ProcGraphModelMdlBP.h"
#include "zReport\ZDGridDoc.h"

#include "zModelBP\ZUExtractProcessName.h"
#include "ZUGridProcessNavigation.h"

#include "zModelBP\ZUProcedureCalculateTotals.h"
#include "zModelBP\ZUUserGroupCalculateTotals.h"

#include "zModelBP\ZBBPProcessSymbol.h"

#include "zModel\PSS_UserGroupEntity.h"
#include "zModel\ZBUserRoleEntity.h"

#include "zReport\ZVGridView.h"
#include "zReport\ZCGridGroup.h"

#include "zBaseLib\PSS_Global.h"

#include "ColorRefDefinition.h"

#include "zReport\zReportRes.h"
#include "zReportBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 8 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(ZBSesterceUnitReportGenerator, ZBModelBPReportGenerator, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBSesterceUnitReportGenerator::ZBSesterceUnitReportGenerator(ZDGridDocument*            pDoc                /*= NULL*/,
                                                             ZDProcessGraphModelMdlBP*    pModel                /*= NULL*/,
                                                             PSS_ProcessGraphModelDoc*    pSourceDoc            /*= NULL*/,
                                                             bool                        IncludeMonthDetail    /*= true*/)
    : ZBModelBPReportGenerator(pDoc, pModel, pSourceDoc),
    m_IncludeMonthDetail(IncludeMonthDetail)
{
    // Initialize the normal style for cells
    m_NormalStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(9)
                 .SetBold(FALSE))
        .SetInterior(defCOLOR_WHITE);

    // Initialize the normal style for cells
    m_BoldStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(9)
                 .SetBold(TRUE))
        .SetInterior(defCOLOR_WHITE);

    // Initialize the rose style for header cells
    m_RoseStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(10)
                 .SetBold(FALSE))
        .SetInterior(defCOLOR_ROSESESTERCE);

    // Initialize the bold rose style for header cells
    m_BoldRoseStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(10)
                 .SetBold(TRUE))
        .SetInterior(defCOLOR_ROSESESTERCE);

    // Initialize the blue style 
    m_BlueStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(9)
                 .SetBold(FALSE))
        .SetInterior(defCOLOR_BLUEMERCUTIO);

    // Initialize the blue style 
    m_GreenStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(9)
                 .SetBold(FALSE))
        .SetInterior(defCOLOR_STARTGREEN);

    // Initialize the blue style 
    m_RedStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(9)
                 .SetBold(FALSE))
        .SetInterior(defCOLOR_ENDRED);

    // Initialize the blue style for header cells
    m_GrayStyle.SetTextColor(defCOLOR_WHITE)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(10)
                 .SetBold(TRUE))
        .SetInterior(defCOLOR_GRAY);

    // Initialize the blue style for header cells
    m_LightGrayStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(9)
                 .SetBold(FALSE))
        .SetInterior(defCOLOR_LTGRAY);

    // Initialize the black border
    m_BlackBorderStyle.SetBorders(gxBorderAll, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_LeftOnlyBlackBorderStyle.SetBorders(gxBorderLeft, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));

    // Initialize the different cell formats
    m_PercentFormatStyle.SetFormat(GX_FMT_PERCENT).SetPlaces(0);
    m_AmountFormatStyle.SetFormat(GX_FMT_COMMA).SetPlaces(0);
    m_NumberTwoDecFormatStyle.SetFormat(GX_FMT_FIXED).SetPlaces(2);
    m_NumericCellStyle.SetValueType(GX_VT_NUMERIC).SetPlaces(0);
}

ZBSesterceUnitReportGenerator::~ZBSesterceUnitReportGenerator()
{
    RemoveAllData();
}

void ZBSesterceUnitReportGenerator::RemoveAllData()
{
    m_ProcessNameArray.RemoveAll();
    m_ModelArray.RemoveAll();

    for (int i = 0; i < m_NavigationTotalArray.GetSize(); ++i)
    {
        delete ((ZUUserGroupCalculateTotals*)m_NavigationTotalArray.GetAt(i));
    }

    m_NavigationTotalArray.RemoveAll();
}

// To fill the tab array, use a visitor class 
// And fill also the internal process array
void ZBSesterceUnitReportGenerator::FillTabArray()
{
    // if no doc nor model defined. nothing to do.
    if (!m_pDoc || !m_pModel)
    {
        return;
    }

    // Load all process in the process name array
    // First, remove all elements
    RemoveAllData();

    // Fill the array with process name
    ZUExtractProcessName ExtractProcessName(m_pModel);
    ExtractProcessName.FillProcessNameArray(&m_ProcessNameArray);

    // Add all models to the model array
    m_ModelArray.Add(m_pModel);
    int CountProcess = m_ProcessNameArray.GetSize();

    for (int Idx = 0; Idx < CountProcess; ++Idx)
    {
        // Find the right process, function of the model name.
        // In case sensitive...
        PSS_ProcessGraphModelMdl* pModel = m_pModel->FindModel(m_ProcessNameArray.GetAt(Idx), true);

        if (!pModel)
        {
            // Error
            return;
        }

        m_ModelArray.Add(pModel);
    }

    ZBUserGroupCalculateTotalsInformation Info(false, m_pModel->GetMainUserGroup());

    for (int i = 0; i < m_ModelArray.GetSize(); ++i)
    {
        ZUUserGroupCalculateTotals* pUserGroupTotals = new ZUUserGroupCalculateTotals;

        if (!pUserGroupTotals->Navigate(((PSS_ProcessGraphModelMdl*)m_ModelArray.GetAt(i)),
            (void*)(static_cast<ZBUserGroupCalculateTotalsInformation*>(&Info))))
        {
            return;
        }

        m_NavigationTotalArray.Add((CObject*)pUserGroupTotals);
    }

    // Then, fill tabs
    // First tab is the workload
    CString s;
    s.LoadString(IDS_WORKLOAD_TAB);
    m_TabNameArray.Add(s);

    // Second tab is the cost
    s.LoadString(IDS_COST_TAB);
    m_TabNameArray.Add(s);

    // Third tab is the cost hmo
    s.LoadString(IDS_COSTHMO_TAB);
    m_TabNameArray.Add(s);
}

bool ZBSesterceUnitReportGenerator::FillGrid(CGXGridCore& GridCore, size_t Index)
{
    ZBOStreamGrid ostream(&GridCore);

    // Default size
    GridCore.SetRowCount(60);        // 60 rows
    GridCore.SetColCount(15);        // 15 columns

    // Retrieve the grid view
    ZVGridView* pView = NULL;
    CWnd* pWnd = GridCore.GridWnd();

    if (pWnd && ISA(pWnd, ZVGridView))
    {
        pView = dynamic_cast<ZVGridView*>(pWnd);
    }

    // Display header
    CString s;
    int top;
    int left;

    ostream << _T("\n\n");

    int Count = m_ProcessNameArray.GetSize() + 1;

    if (m_IncludeMonthDetail)
    {
        // If a grid view, insert a group control for all sub-processes
        if (pView)
        {
            ostream << _T("\t");

            for (int i = 0; i < Count; ++i)
            {
                // Retrieve the current position
                ostream.GetCurSel(left, top);

                // Check the number of column
                ROWCOL ColCount = ostream.GetGridCore()->GetColCount();

                // If not enough, add 20 columns
                if ((left + 20) > (int)ColCount)
                {
                    ostream.GetGridCore()->SetColCount(ColCount + 20);
                }

                CString Label;
                Label.LoadString(IDS_CHKBOX_LABEL);

                CString ToolTipText;
                ToolTipText.LoadString(IDS_CHKBOX_TTP);

                pView->InsertGroupCtrl(top,                            // Row col
                                       left,                            // Row col
                                       (i + 1 < Count) ? 12 : 13,    // Covering cells
                                       true,                            // Horizontal
                                       true,                            // Collapsed
                                       Label,
                                       ToolTipText);

                // Move right for the next control
                ostream.Right(13);
            }
        }
    }

    // Check the report width
    ostream << _T("\t");

    // Retrieve the current position
    ostream.GetCurSel(left, top);

    // Check the number of column
    ROWCOL ColCount = ostream.GetGridCore()->GetColCount();

    if (m_IncludeMonthDetail)
    {
        // If not enough, add 20 columns
        if ((left + (Count * 13)) > (int)ColCount)
        {
            ostream.GetGridCore()->SetColCount(ColCount + (Count * 13));
        }
    }
    else
    {
        // If not enough, add 20 columns
        if ((left + Count) > (int)ColCount)
        {
            ostream.GetGridCore()->SetColCount(ColCount + Count);
        }
    }

    ostream << _T("\n");

    switch (Index)
    {
        case 0:
        {
            s.LoadString(IDS_WORKLOAD_LBLRPT);
            break;
        }

        case 1:
        {
            s.LoadString(IDS_COSTUNIT_LBLRPT);
            break;
        }

        case 2:
        {
            s.LoadString(IDS_COSTHMOUNIT_LBLRPT);
            break;
        }
    }

    ostream << s;
    ostream << CSize(200, 40);    // Set the cell size
    ostream << m_RoseStyle;
    ostream << _T("\t");

    // The model name
    ostream << m_pModel->GetModelName();
    ostream << CSize(150, 0);        // Set the cell width only
    ostream << m_RoseStyle;

    if (m_IncludeMonthDetail)
    {
        // JMR-MODIF - Le 9 mars 2006 - Ajouté pour chaque mois la valeur CSize( 80, 0 ).

        // Then each month 
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT1);
        ostream << s;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT2);
        ostream << s;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT3);
        ostream << s;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT4);
        ostream << s;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT5);
        ostream << s;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT6);
        ostream << s;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT7);
        ostream << s;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT8);
        ostream << s;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT9);
        ostream << s;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT10);
        ostream << s;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT11);
        ostream << s;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        s.LoadString(IDS_MONTH_LBLRPT12);
        ostream << s;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
    }

    // Now, for each sub-process, write the header
    for (int i = 0; i < m_ProcessNameArray.GetSize(); ++i)
    {
        ostream << _T("\t");

        ostream << m_ProcessNameArray.GetAt(i);
        // JMR-MODIF - Le 9 mars 2006 - Changé la largeur de cellule de 100 à 150.
        ostream << CSize(150, 0);        // Set the cell width only
        ostream << m_RoseStyle;

        if (m_IncludeMonthDetail)
        {
            // JMR-MODIF - Le 9 mars 2006 - Ajouté pour chaque mois la valeur CSize( 80, 0 ).

            ostream << _T("\t");

            // Then each month
            s.LoadString(IDS_MONTH_LBLRPT1);
            ostream << s;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT2);
            ostream << s;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT3);
            ostream << s;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT4);
            ostream << s;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT5);
            ostream << s;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT6);
            ostream << s;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT7);
            ostream << s;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT8);
            ostream << s;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT9);
            ostream << s;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT10);
            ostream << s;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT11);
            ostream << s;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            s.LoadString(IDS_MONTH_LBLRPT12);
            ostream << s;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
        }
    }

    // Finally, process all user groups
    FillGridUnitGroup(m_pModel->GetMainUserGroup(), Index, ostream);

    // To finish, just freeze the first column
    ZDGridDocument* pDoc = pView->GetDocument();

    if (pDoc)
    {
        pDoc->SetFrozenRow(4);
        pDoc->SetFrozenCol(1);

        pDoc->SetFrozenHeaderRow(4);
        pDoc->SetFrozenHeaderCol(1);

        pView->FreezeSplitter();
    }

    return true;
}

void ZBSesterceUnitReportGenerator::FillGridUnitGroup(PSS_UserGroupEntity*    pGroup,
                                                      size_t                Index,
                                                      ZBOStreamGrid        &ostream)
{
    if (!pGroup)
    {
        return;
    }

    // add the group line
    ostream << _T("\n");
    ostream << pGroup->GetEntityName();
    ostream << m_NormalStyle;
    ostream << _T("\t");

    // Fill process figures for the main process
    FillProcessFigures(((PSS_ProcessGraphModelMdl*)m_ModelArray.GetAt(0)),
        ((ZUUserGroupCalculateTotals*)m_NavigationTotalArray.GetAt(0)),
                       pGroup,
                       Index,
                       ostream);

    for (int i = 1; i < m_ModelArray.GetSize() && i < m_NavigationTotalArray.GetSize(); ++i)
    {
        FillProcessFigures(((PSS_ProcessGraphModelMdl*)m_ModelArray.GetAt(i)),
            ((ZUUserGroupCalculateTotals*)m_NavigationTotalArray.GetAt(i)),
                           pGroup,
                           Index,
                           ostream);
    }

    if (pGroup->ContainEntity())
    {
        int Count = pGroup->GetEntityCount();
        int top;
        int left;

        // Check the number of row
        ROWCOL RowCount = ostream.GetGridCore()->GetRowCount();
        ostream.GetCurSel(left, top);

        // If not enough, add rows
        if ((top + Count + 5) > (int)RowCount)
        {
            ostream.GetGridCore()->SetRowCount(RowCount + Count + 5);
        }

        for (int i = 0; i < Count; ++i)
        {
            PSS_UserEntity* pEntity = pGroup->GetEntityAt(i);

            if (!pEntity)
            {
                continue;
            }

            if (ISA(pEntity, PSS_UserGroupEntity))
            {
                FillGridUnitGroup(dynamic_cast<PSS_UserGroupEntity*>(pEntity), Index, ostream);
            }

            if (ISA(pEntity, ZBUserRoleEntity))
            {
                FillGridUnitRole(dynamic_cast<ZBUserRoleEntity*>(pEntity), Index, ostream);
            }
        }
    }
}

void ZBSesterceUnitReportGenerator::FillProcessFigures(PSS_ProcessGraphModelMdl*        pModel,
                                                       ZUUserGroupCalculateTotals*    pTotal,
                                                       PSS_UserGroupEntity*            pGroup,
                                                       size_t                        Index,
                                                       ZBOStreamGrid                &ostream)
{
    ASSERT(pGroup);
    ASSERT(pTotal);
    ZBBPAnnualNumberProperties* pAnnualNumber;

    switch (Index)
    {
        case 0:
        {
            // The total unit procedure workload
            pAnnualNumber = pTotal->GetProcedureWorkloadForecast(pGroup->GetEntityName());

            if (pAnnualNumber)
            {
                ostream << pAnnualNumber->GetNumberYear();
            }
            else
            {
                ostream << (double)0;
            }

            break;
        }

        case 1:
        {
            // The total unit procedure cost
            pAnnualNumber = pTotal->GetProcedureCostForecast(pGroup->GetEntityName());

            if (pAnnualNumber)
            {
                ostream << pAnnualNumber->GetNumberYear();
            }
            else
            {
                ostream << (double)0;
            }

            break;
        }

        case 2:
        {
            // The total unit procedure cost hmo
            pAnnualNumber = pTotal->GetProcedureCost(pGroup->GetEntityName());

            if (pAnnualNumber)
            {
                ostream << pAnnualNumber->GetNumberYear();
            }
            else
            {
                ostream << (double)0;
            }

            break;
        }
    }

    ostream << m_NormalStyle;
    ostream << m_NumericCellStyle;
    ostream << m_AmountFormatStyle;
    ostream << _T("\t");

    if (m_IncludeMonthDetail)
    {
        // The total unit procedure workload forecast
        for (int i = 0; i < 12; ++i)
        {
            switch (Index)
            {
                case 0:
                {
                    // The total unit procedure workload
                    pAnnualNumber = pTotal->GetProcedureWorkloadForecast(pGroup->GetEntityName());

                    if (pAnnualNumber)
                    {
                        ostream << pAnnualNumber->GetNumberAt(i);
                    }
                    else
                    {
                        ostream << (double)0;
                    }

                    break;
                }

                case 1:
                {
                    // The total unit procedure cost
                    pAnnualNumber = pTotal->GetProcedureCostForecast(pGroup->GetEntityName());

                    if (pAnnualNumber)
                    {
                        ostream << pAnnualNumber->GetNumberAt(i);
                    }
                    else
                    {
                        ostream << (double)0;
                    }

                    break;
                }

                case 2:
                {
                    // The total unit procedure cost hmo
                    pAnnualNumber = pTotal->GetProcedureCost(pGroup->GetEntityName());

                    if (pAnnualNumber)
                    {
                        ostream << pAnnualNumber->GetNumberAt(i);
                    }
                    else
                    {
                        ostream << (double)0;
                    }

                    break;
                }
            }

            ostream << m_NormalStyle;
            ostream << m_NumericCellStyle;
            ostream << m_AmountFormatStyle;
            ostream << _T("\t");
        }
    }
}

void ZBSesterceUnitReportGenerator::FillGridUnitRole(ZBUserRoleEntity*    pRole,
                                                     size_t            Index,
                                                     ZBOStreamGrid        &ostream)
{
    // Do nothing for role
}

const CString ZBSesterceUnitReportGenerator::GetReportTitle() const
{
    // Build the title function of the model
    CString s;

    if (m_pDoc)
    {
        s = m_pDoc->GetTitle();
    }

    CString ReportType;
    ReportType.LoadString(IDS_SESTERCE_UNIT_RPT_T);

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
