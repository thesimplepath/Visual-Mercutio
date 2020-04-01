/****************************************************************************
 * ==> PSS_SesterceReportGenerator -----------------------------------------*
 ****************************************************************************
 * Description : Provides a Sesterce report generator                       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SesterceReportGenerator.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_UserGroupEntity.h"
#include "zModel\PSS_UserRoleEntity.h"
#include "zModelBP\PSS_ProcessGraphModelMdlBP.h"
#include "zModelBP\PSS_ProcessSymbolBP.h"
#include "zModelBP\PSS_ExtractProcessName.h"
#include "zModelBP\PSS_ProcedureCalculateTotals.h"
#include "zReport\PSS_GridDocument.h"
#include "PSS_GridSesterceProcessNavigation.h"
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
IMPLEMENT_SERIAL(PSS_SesterceReportGenerator, PSS_ModelBPReportGenerator, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_SesterceReportGenerator
//---------------------------------------------------------------------------
PSS_SesterceReportGenerator::PSS_SesterceReportGenerator(PSS_GridDocument*           pDoc,
                                                         PSS_ProcessGraphModelMdlBP* pModel,
                                                         PSS_ProcessGraphModelDoc*   pSourceDoc) :
    PSS_ModelBPReportGenerator(pDoc, pModel, pSourceDoc)
{
    // initialize the style for header cells
    m_HeaderStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(12).SetBold(TRUE))
            .SetInterior(M_Color_RoseSesterce);

    // initialize the style for cells
    m_NormalStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(10).SetBold(FALSE))
            .SetInterior(defCOLOR_WHITE);
}
//---------------------------------------------------------------------------
PSS_SesterceReportGenerator::~PSS_SesterceReportGenerator()
{}
//---------------------------------------------------------------------------
const CString PSS_SesterceReportGenerator::GetReportTitle() const
{
    // build the title function of the model
    CString str;

    if (m_pDoc)
        str = m_pDoc->GetTitle();

    CString reportType;
    reportType.LoadString(IDS_SESTERCE_RPT_T);

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
bool PSS_SesterceReportGenerator::FillGrid(CGXGridCore& gridCore, std::size_t index)
{
    if (!index)
        return FillGridUnit(gridCore);

    return FillGridProcess(gridCore, index);
}
//---------------------------------------------------------------------------
void PSS_SesterceReportGenerator::FillTabArray()
{
    // if no doc or model defined, nothing to do
    if (!m_pDoc || !m_pModel)
        return;

    // remove all elements
    m_TabNameArray.RemoveAll();

    PSS_ExtractProcessName extractProcessName(m_pModel);

    // first tab is for the model name
    m_TabNameArray.Add(m_pModel->GetModelName());

    // sort the list from the 1st tab
    extractProcessName.FillProcessNameArray(&m_TabNameArray, 1);
}
//---------------------------------------------------------------------------
bool PSS_SesterceReportGenerator::FillGridUnit(CGXGridCore& gridCore)
{
    PSS_OStreamGrid ostream(&gridCore);

    // default size, 60 rows x 15 columns
    gridCore.SetRowCount(60);
    gridCore.SetColCount(15);

    // show header
    ostream << _T("\n\n");

    CString str;
    str.LoadString(IDS_UNITNAME_H);

    ostream << str;
    ostream << CSize(150, 60);
    ostream << m_HeaderStyle;
    ostream << _T("\t");

    str.LoadString(IDS_UNITDES_H);
    ostream << str;
    ostream << CSize(200, 0);
    ostream << m_HeaderStyle;
    ostream << _T("\t");

    str.LoadString(IDS_UNITCOST_H);
    ostream << str;
    ostream << m_HeaderStyle;
    ostream << _T("\t");

    str.LoadString(IDS_UNITOWNER_H);
    ostream << str;
    ostream << CSize(200, 0);
    ostream << m_HeaderStyle;
    ostream << _T("\t");

    // process the group
    FillGridUnitGroup(m_pModel->GetMainUserGroup(), ostream);

    // the next following lines are for the all processes summary
    ostream << _T("\n\n\n");

    str.LoadString(IDS_SYMBOLREF_H);
    ostream << str;
    ostream << m_HeaderStyle;
    ostream << _T("\t");

    str.LoadString(IDS_SYMBOLNAME_H);
    ostream << str;
    ostream << m_HeaderStyle;
    ostream << _T("\t");

    str.LoadString(IDS_SYMBOLDES_H);
    ostream << str;
    ostream << m_HeaderStyle;

    std::size_t count = m_TabNameArray.GetSize();

    // iterate through all tabs and show their content. Start with the second tab, the first tab is this one
    for (std::size_t i = 1; i < count; ++i)
    {
        // find the process matching with the model name. Case sensitive, and only local symbol
        CODComponentSet* pSet = m_pModel->FindSymbol(m_TabNameArray.GetAt(i), _T(""), true, true, true);

        if (!pSet || pSet->GetSize() <= 0)
            continue;

        PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pSet->GetAt(0));

        if (!pProcess)
            continue;

        ostream << _T("\n");

        ostream << pProcess->GetSymbolReferenceNumberStr();
        ostream << m_NormalStyle;
        ostream << _T("\t");

        ostream << pProcess->GetSymbolName();
        ostream << m_NormalStyle;
        ostream << _T("\t");

        ostream << pProcess->GetSymbolComment();

        // check the row count
        const ROWCOL rowCount = ostream.GetGridCore()->GetRowCount();

        int left;
        int top;

        ostream.GetCurSel(left, top);

        // If not enough, add 5 rows
        if ((top + 5) > int(rowCount))
            ostream.GetGridCore()->SetRowCount(rowCount + 5);
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_SesterceReportGenerator::FillGridUnitGroup(PSS_UserGroupEntity* pGroup, PSS_OStreamGrid& ostream)
{
    if (!pGroup)
        return;

    CGXStyle numericCellStyle;
    numericCellStyle.SetValueType(GX_VT_NUMERIC);

    CGXStyle amountFormatStyle;
    amountFormatStyle.SetFormat(GX_FMT_COMMA).SetPlaces(0);

    // check the row count
    const ROWCOL rowCount = ostream.GetGridCore()->GetRowCount();

    int left;
    int top;

    ostream.GetCurSel(left, top);

    // If not enough, add 10 rows
    if ((top + 10) > int(rowCount))
        ostream.GetGridCore()->SetRowCount(rowCount + 10);

    // add the group line
    ostream << _T("\n");

    ostream << pGroup->GetEntityName();
    ostream << m_NormalStyle;
    ostream << _T("\t");

    ostream << pGroup->GetEntityDescription();
    ostream << m_NormalStyle;
    ostream << _T("\t");

    ostream << pGroup->GetEntityCost();
    ostream << m_NormalStyle;
    ostream << numericCellStyle;
    ostream << amountFormatStyle;
    ostream << _T("\t");

    if (pGroup->GetParent())
        ostream << pGroup->GetParent()->GetEntityName();
    else
        ostream << _T("");

    ostream << _T("\t");

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
            {
                FillGridUnitGroup(pUserGroup, ostream);
                continue;
            }

            PSS_UserRoleEntity* pUserRole = dynamic_cast<PSS_UserRoleEntity*>(pEntity);

            if (pUserRole)
                FillGridUnitRole(pUserRole, ostream);
        }
    }
}
//---------------------------------------------------------------------------
void PSS_SesterceReportGenerator::FillGridUnitRole(PSS_UserRoleEntity* pRole, PSS_OStreamGrid& ostream)
{
    // add the role line
    ostream << _T("\n");

    ostream << pRole->GetEntityName();
    ostream << m_NormalStyle;
    ostream << _T("\t");

    ostream << pRole->GetEntityDescription();
    ostream << m_NormalStyle;
    ostream << _T("\t");

    // no cost for a role
    ostream << _T("");
    ostream << _T("\t");

    if (pRole->GetParent())
        ostream << pRole->GetParent()->GetEntityName();
    else
        ostream << _T("");

    ostream << m_NormalStyle;
}
//---------------------------------------------------------------------------
bool PSS_SesterceReportGenerator::FillGridProcess(CGXGridCore& gridCore, std::size_t index)
{
    // check the index validity
    if (index >= std::size_t(m_TabNameArray.GetSize()))
        return false;

    PSS_ProcessGraphModelMdl* pModel          = NULL;
    PSS_ProcessGraphModelMdl* pProcGraphModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(m_pModel);

    // find the process matching with the model name, case sensitive
    if (pProcGraphModel)
        pModel = pProcGraphModel->FindModel(m_TabNameArray.GetAt(index), true);

    if (!pModel)
        return false;

    // build the output stream grid object
    PSS_OStreamGrid ostream(&gridCore);

    // default size, 60 rows x 15 columns
    gridCore.SetRowCount(60);
    gridCore.SetColCount(15);

    // build the navigation grid process
    PSS_GridSesterceProcessNavigation processNavigation(pModel, static_cast<void*>(&ostream));

    // navigate through the process symbols
    return processNavigation.Navigate();
}
//---------------------------------------------------------------------------
