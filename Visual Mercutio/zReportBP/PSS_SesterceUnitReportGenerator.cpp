/****************************************************************************
 * ==> PSS_SesterceUnitReportGenerator -------------------------------------*
 ****************************************************************************
 * Description : Provides a Sesterce unit report generator                  *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SesterceUnitReportGenerator.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_UserGroupEntity.h"
#include "zModel\PSS_UserRoleEntity.h"
#include "zModelBP\PSS_ProcessGraphModelMdlBP.h"
#include "zModelBP\PSS_ExtractProcessName.h"
#include "zModelBP\PSS_ProcedureCalculateTotals.h"
#include "zModelBP\PSS_UserGroupCalculateTotals.h"
#include "zModelBP\PSS_ProcessSymbolBP.h"
#include "zReport\PSS_GridDocument.h"
#include "zReport\PSS_GridView.h"
#include "zReport\PSS_GridGroup.h"
#include "PSS_GridProcessNavigation.h"
#include "PSS_ColorRefDefinition.h"

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
IMPLEMENT_SERIAL(PSS_SesterceUnitReportGenerator, PSS_ModelBPReportGenerator, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_SesterceUnitReportGenerator
//---------------------------------------------------------------------------
PSS_SesterceUnitReportGenerator::PSS_SesterceUnitReportGenerator(PSS_GridDocument*           pDoc,
                                                                 PSS_ProcessGraphModelMdlBP* pModel,
                                                                 PSS_ProcessGraphModelDoc*   pSourceDoc,
                                                                 bool                        includeMonthDetail) :
    PSS_ModelBPReportGenerator(pDoc, pModel, pSourceDoc),
    m_IncludeMonthDetail(includeMonthDetail)
{
    // initialize the normal style for cells
    m_NormalStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(9)
            .SetBold(FALSE))
            .SetInterior(defCOLOR_WHITE);

    // initialize the bold style for cells
    m_BoldStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(9)
            .SetBold(TRUE))
            .SetInterior(defCOLOR_WHITE);

    // initialize the rose style for header cells
    m_RoseStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(10)
            .SetBold(FALSE))
            .SetInterior(M_Color_RoseSesterce);

    // initialize the bold rose style for header cells
    m_BoldRoseStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(10)
            .SetBold(TRUE))
            .SetInterior(M_Color_RoseSesterce);

    // initialize the blue style
    m_BlueStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(9)
            .SetBold(FALSE))
            .SetInterior(M_Color_BlueMercutio);

    // initialize the green style
    m_GreenStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(9)
            .SetBold(FALSE))
            .SetInterior(M_Color_StartGreen);

    // initialize the red style
    m_RedStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(9)
            .SetBold(FALSE))
            .SetInterior(M_Color_EndRed);

    // initialize the gray style for header cells
    m_GrayStyle.SetTextColor(defCOLOR_WHITE)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(10)
            .SetBold(TRUE))
            .SetInterior(defCOLOR_GRAY);

    // initialize the light gray style for header cells
    m_LightGrayStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(9)
            .SetBold(FALSE))
            .SetInterior(defCOLOR_LTGRAY);

    // initialize the black border
    m_BlackBorderStyle.SetBorders(gxBorderAll, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));
    m_LeftOnlyBlackBorderStyle.SetBorders(gxBorderLeft, CGXPen().SetWidth(1).SetColor(defCOLOR_BLACK));

    // initialize the miscellaneous cell formats
    m_PercentFormatStyle.SetFormat(GX_FMT_PERCENT).SetPlaces(0);
    m_AmountFormatStyle.SetFormat(GX_FMT_COMMA).SetPlaces(0);
    m_NumberTwoDecFormatStyle.SetFormat(GX_FMT_FIXED).SetPlaces(2);
    m_NumericCellStyle.SetValueType(GX_VT_NUMERIC).SetPlaces(0);
}
//---------------------------------------------------------------------------
PSS_SesterceUnitReportGenerator::~PSS_SesterceUnitReportGenerator()
{
    // NOTE use fully qualified name here to avoid to call a pure virtual function on destruction
    PSS_SesterceUnitReportGenerator::RemoveAllData();
}
//---------------------------------------------------------------------------
const CString PSS_SesterceUnitReportGenerator::GetReportTitle() const
{
    CString str;

    // build the model title
    if (m_pDoc)
        str = m_pDoc->GetTitle();

    CString reportType;
    reportType.LoadString(IDS_SESTERCE_UNIT_RPT_T);

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
bool PSS_SesterceUnitReportGenerator::FillGrid(CGXGridCore& gridCore, std::size_t index)
{
    PSS_OStreamGrid ostream(&gridCore);

    // default size, 60 rows x 15 columns
    gridCore.SetRowCount(60);
    gridCore.SetColCount(15);

    // get the grid view
    PSS_GridView* pGridView = dynamic_cast<PSS_GridView*>(gridCore.GridWnd());

    // show header
    ostream << _T("\n\n");

    int       left;
    int       top;
    const int count = m_ProcessNameArray.GetSize() + 1;

    if (m_IncludeMonthDetail)
    {
        // if a grid view exists, insert a group control for all sub-processes
        if (pGridView)
        {
            ostream << _T("\t");

            for (int i = 0; i < count; ++i)
            {
                // get the current position
                ostream.GetCurSel(left, top);

                // check the number of column
                const ROWCOL colCount = ostream.GetGridCore()->GetColCount();

                // if not enough, add the missing columns
                if ((left + 20) > int(colCount))
                    ostream.GetGridCore()->SetColCount(colCount + 20);

                CString label;
                label.LoadString(IDS_CHKBOX_LABEL);

                CString tooltipText;
                tooltipText.LoadString(IDS_CHKBOX_TTP);

                pGridView->InsertGroupCtrl(top,
                                           left,
                                           (i + 1 < count) ? 12 : 13,
                                           true,
                                           true,
                                           label,
                                           tooltipText);

                // move right for the next control
                ostream.Right(13);
            }
        }
    }

    // check the report width
    ostream << _T("\t");

    // get the current position
    ostream.GetCurSel(left, top);

    // check the column count
    const ROWCOL colCount = ostream.GetGridCore()->GetColCount();

    if (m_IncludeMonthDetail)
    {
        // if not enough, add the missing columns
        if ((left + (count * 13)) > int(colCount))
            ostream.GetGridCore()->SetColCount(colCount + (count * 13));
    }
    else
    if ((left + count) > int(colCount))
        // if not enough, add the missing columns
        ostream.GetGridCore()->SetColCount(colCount + count);

    ostream << _T("\n");

    CString str;

    switch (index)
    {
        case 0: str.LoadString(IDS_WORKLOAD_LBLRPT);    break;
        case 1: str.LoadString(IDS_COSTUNIT_LBLRPT);    break;
        case 2: str.LoadString(IDS_COSTHMOUNIT_LBLRPT); break;
    }

    ostream << str;
    ostream << CSize(200, 40);
    ostream << m_RoseStyle;
    ostream << _T("\t");

    // the model name
    ostream << m_pModel->GetModelName();
    ostream << CSize(150, 0);
    ostream << m_RoseStyle;

    if (m_IncludeMonthDetail)
    {
        // process each month
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT1);
        ostream << str;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT2);
        ostream << str;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT3);
        ostream << str;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT4);
        ostream << str;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT5);
        ostream << str;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT6);
        ostream << str;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT7);
        ostream << str;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT8);
        ostream << str;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT9);
        ostream << str;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT10);
        ostream << str;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT11);
        ostream << str;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
        ostream << _T("\t");

        str.LoadString(IDS_MONTH_LBLRPT12);
        ostream << str;
        ostream << CSize(80, 0);
        ostream << m_RoseStyle;
        ostream << m_BlackBorderStyle;
    }

    const int processCount = m_ProcessNameArray.GetSize();

    // for each sub-process, write the header
    for (int i = 0; i < processCount; ++i)
    {
        ostream << _T("\t");

        ostream << m_ProcessNameArray.GetAt(i);
        ostream << CSize(150, 0);
        ostream << m_RoseStyle;

        if (m_IncludeMonthDetail)
        {
            ostream << _T("\t");

            // process each month
            str.LoadString(IDS_MONTH_LBLRPT1);
            ostream << str;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT2);
            ostream << str;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT3);
            ostream << str;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT4);
            ostream << str;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT5);
            ostream << str;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT6);
            ostream << str;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT7);
            ostream << str;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT8);
            ostream << str;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT9);
            ostream << str;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT10);
            ostream << str;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT11);
            ostream << str;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
            ostream << _T("\t");

            str.LoadString(IDS_MONTH_LBLRPT12);
            ostream << str;
            ostream << CSize(80, 0);
            ostream << m_RoseStyle;
            ostream << m_BlackBorderStyle;
        }
    }

    // process all user groups
    FillGridUnitGroup(m_pModel->GetMainUserGroup(), index, ostream);

    if (pGridView)
    {
        // freeze the first column
        PSS_GridDocument* pDoc = pGridView->GetDocument();

        if (pDoc)
        {
            pDoc->SetFrozenRow(4);
            pDoc->SetFrozenCol(1);
            pDoc->SetFrozenHeaderRow(4);
            pDoc->SetFrozenHeaderCol(1);

            pGridView->FreezeSplitter();
        }
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_SesterceUnitReportGenerator::FillTabArray()
{
    // if no doc or model defined, nothing to do
    if (!m_pDoc || !m_pModel)
        return;

    // load all process in the process name array. First, remove all elements
    RemoveAllData();

    // fill the array with process name
    PSS_ExtractProcessName extractProcessName(m_pModel);
    extractProcessName.FillProcessNameArray(&m_ProcessNameArray);

    // add all models to the model array
    m_ModelArray.Add(m_pModel);
    
    const int countProcess = m_ProcessNameArray.GetSize();

    for (int i = 0; i < countProcess; ++i)
    {
        // find the process matching with the model name, case sensitive
        PSS_ProcessGraphModelMdl* pModel = m_pModel->FindModel(m_ProcessNameArray.GetAt(i), true);

        // error
        if (!pModel)
            return;

        m_ModelArray.Add(pModel);
    }

    PSS_UserGroupCalculateTotals::IInfo info(false, m_pModel->GetMainUserGroup());

    for (int i = 0; i < m_ModelArray.GetSize(); ++i)
    {
        PSS_ProcessGraphModelMdl* pGraphModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(m_ModelArray.GetAt(i));

        if (!pGraphModel)
            continue;

        std::unique_ptr<PSS_UserGroupCalculateTotals> pUserGroupTotals(new PSS_UserGroupCalculateTotals());

        if (!pUserGroupTotals->Navigate(pGraphModel, (void*)(static_cast<PSS_UserGroupCalculateTotals::IInfo*>(&info))))
            return;

        m_NavigationTotalArray.Add(pUserGroupTotals.get());
        pUserGroupTotals.release();
    }

    CString str;

    // fill tabs, the first one is the workload
    str.LoadString(IDS_WORKLOAD_TAB);
    m_TabNameArray.Add(str);

    // second tab is the cost
    str.LoadString(IDS_COST_TAB);
    m_TabNameArray.Add(str);

    // third tab is the HMO cost
    str.LoadString(IDS_COSTHMO_TAB);
    m_TabNameArray.Add(str);
}
//---------------------------------------------------------------------------
void PSS_SesterceUnitReportGenerator::RemoveAllData()
{
    m_ProcessNameArray.RemoveAll();
    m_ModelArray.RemoveAll();

    const int count = m_NavigationTotalArray.GetSize();

    for (int i = 0; i < count; ++i)
        delete m_NavigationTotalArray.GetAt(i);

    m_NavigationTotalArray.RemoveAll();
}
//---------------------------------------------------------------------------
void PSS_SesterceUnitReportGenerator::FillGridUnitGroup(PSS_UserGroupEntity* pGroup,
                                                        std::size_t          index,
                                                        PSS_OStreamGrid&     ostream)
{
    if (!pGroup)
        return;

    // add the group line
    ostream << _T("\n");
    ostream << pGroup->GetEntityName();
    ostream << m_NormalStyle;
    ostream << _T("\t");

    const int modelCount  = m_ModelArray.GetSize();
    const int totalsCount = m_NavigationTotalArray.GetSize();

    for (int i = 0; i < modelCount && i < totalsCount; ++i)
    {
        PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(m_ModelArray.GetAt(i));

        if (!pModel)
            continue;

        PSS_UserGroupCalculateTotals* pTotals = dynamic_cast<PSS_UserGroupCalculateTotals*>(m_NavigationTotalArray.GetAt(i));

        if (!pTotals)
            continue;

        FillProcessFigures(pModel, pTotals, pGroup, index, ostream);
    }

    if (pGroup->ContainEntity())
    {
        // check the row count
        const ROWCOL rowCount = ostream.GetGridCore()->GetRowCount();

        int left;
        int top;

        ostream.GetCurSel(left, top);

        const int count = pGroup->GetEntityCount();

        // if not enough, add the missing rows
        if ((top + count + 5) > int(rowCount))
            ostream.GetGridCore()->SetRowCount(rowCount + count + 5);

        for (int i = 0; i < count; ++i)
        {
            PSS_UserEntity* pEntity = pGroup->GetEntityAt(i);

            if (!pEntity)
                continue;

            PSS_UserGroupEntity* pUserGroup = dynamic_cast<PSS_UserGroupEntity*>(pEntity);

            if (pUserGroup)
            {
                FillGridUnitGroup(pUserGroup, index, ostream);
                continue;
            }

            PSS_UserRoleEntity* pUserRole = dynamic_cast<PSS_UserRoleEntity*>(pEntity);

            if (pUserRole)
                FillGridUnitRole(pUserRole, index, ostream);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_SesterceUnitReportGenerator::FillGridUnitRole(PSS_UserRoleEntity* pRole,
                                                       std::size_t         index,
                                                       PSS_OStreamGrid&    ostream)
{
    // do nothing for role
}
//---------------------------------------------------------------------------
void PSS_SesterceUnitReportGenerator::FillProcessFigures(PSS_ProcessGraphModelMdl*     pModel,
                                                         PSS_UserGroupCalculateTotals* pTotal,
                                                         PSS_UserGroupEntity*          pGroup,
                                                         std::size_t                   index,
                                                         PSS_OStreamGrid&              ostream)
{
    if (pTotal)
        return;

    if (!pGroup)
        return;

    PSS_AnnualNumberPropertiesBP* pAnnualNumber;

    switch (index)
    {
        case 0:
            // the total unit procedure workload
            pAnnualNumber = pTotal->GetProcedureWorkloadForecast(pGroup->GetEntityName());

            if (pAnnualNumber)
                ostream << pAnnualNumber->GetNumberYear();
            else
                ostream << 0.0;

            break;

        case 1:
            // the total unit procedure cost
            pAnnualNumber = pTotal->GetProcedureCostForecast(pGroup->GetEntityName());

            if (pAnnualNumber)
                ostream << pAnnualNumber->GetNumberYear();
            else
                ostream << 0.0;

            break;

        case 2:
            // the total unit procedure HMO cost
            pAnnualNumber = pTotal->GetProcedureCost(pGroup->GetEntityName());

            if (pAnnualNumber)
                ostream << pAnnualNumber->GetNumberYear();
            else
                ostream << 0.0;

            break;
    }

    ostream << m_NormalStyle;
    ostream << m_NumericCellStyle;
    ostream << m_AmountFormatStyle;
    ostream << _T("\t");

    if (m_IncludeMonthDetail)
        // the total unit procedure workload forecast
        for (int i = 0; i < 12; ++i)
        {
            switch (index)
            {
                case 0:
                    // the total unit procedure workload
                    pAnnualNumber = pTotal->GetProcedureWorkloadForecast(pGroup->GetEntityName());

                    if (pAnnualNumber)
                        ostream << pAnnualNumber->GetNumberAt(i);
                    else
                        ostream << 0.0;

                    break;

                case 1:
                    // the total unit procedure cost
                    pAnnualNumber = pTotal->GetProcedureCostForecast(pGroup->GetEntityName());

                    if (pAnnualNumber)
                        ostream << pAnnualNumber->GetNumberAt(i);
                    else
                        ostream << 0.0;

                    break;

                case 2:
                    // the total unit procedure cost hmo
                    pAnnualNumber = pTotal->GetProcedureCost(pGroup->GetEntityName());

                    if (pAnnualNumber)
                        ostream << pAnnualNumber->GetNumberAt(i);
                    else
                        ostream << 0.0;

                    break;
            }

            ostream << m_NormalStyle;
            ostream << m_NumericCellStyle;
            ostream << m_AmountFormatStyle;
            ostream << _T("\t");
        }
}
//---------------------------------------------------------------------------
