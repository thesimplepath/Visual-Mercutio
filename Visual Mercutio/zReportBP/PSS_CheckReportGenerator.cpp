/****************************************************************************
 * ==> PSS_CheckReportGenerator --------------------------------------------*
 ****************************************************************************
 * Description : Provides a check report generator                          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CheckReportGenerator.h"

// processsoft
#include "zBaseLib\PSS_Global.h"
#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModel\PSS_UserGroupEntity.h"
#include "zModel\PSS_UserRoleEntity.h"
#include "zModelBP\PSS_ProcessGraphModelMdlBP.h"
#include "zModelBP\PSS_ExtractProcessName.h"
#include "zModelBP\PSS_ProcessSymbolBP.h"
#include "zReport\PSS_GridDocument.h"
#include "ZUGridProcessNavigation.h"

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
IMPLEMENT_SERIAL(PSS_CheckReportGenerator, PSS_ModelBPReportGenerator, g_DefVersion)
//---------------------------------------------------------------------------
// PSS_CheckReportGenerator
//---------------------------------------------------------------------------
PSS_CheckReportGenerator::PSS_CheckReportGenerator(PSS_GridDocument*           pDoc,
                                                   PSS_ProcessGraphModelMdlBP* pModel,
                                                   PSS_ProcessGraphModelDoc*   pSourceDoc) :
    PSS_ModelBPReportGenerator(pDoc, pModel, pSourceDoc)
{}
//---------------------------------------------------------------------------
PSS_CheckReportGenerator::~PSS_CheckReportGenerator()
{}
//---------------------------------------------------------------------------
bool PSS_CheckReportGenerator::FillGrid(CGXGridCore& gridCore, std::size_t index)
{
    if (!index)
        return FillGridUnit(gridCore);

    return FillGridProcess(gridCore, index);
}
//---------------------------------------------------------------------------
const CString PSS_CheckReportGenerator::GetReportTitle() const
{
    // build the model title function
    CString str;

    if (m_pDoc)
        str = m_pDoc->GetTitle();

    CString reportType;
    reportType.LoadString(IDS_CHECK_RPT_T);

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
void PSS_CheckReportGenerator::FillTabArray()
{
    // if no doc or model defined, nothing to do
    if (!m_pDoc || !m_pModel)
        return;

    // remove all elements
    m_TabNameArray.RemoveAll();

    PSS_ExtractProcessName extractProcessName(m_pModel);

    // first tab is for the units
    CString str;
    str.LoadString(IDS_UNITNAME_TAB);
    m_TabNameArray.Add(str);

    // sort the list since the 1st tab
    extractProcessName.FillProcessNameArray(&m_TabNameArray, 1);
}
//---------------------------------------------------------------------------
bool PSS_CheckReportGenerator::FillGridUnit(CGXGridCore& gridCore)
{
    PSS_OStreamGrid ostream(&gridCore);

    // default size, 60 rows x 15 columns
    gridCore.SetRowCount(60);
    gridCore.SetColCount(15);

    // initialize the header cells style
    CGXStyle style;
    style.SetTextColor(defCOLOR_WHITE)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(12).SetBold(TRUE))
            .SetInterior(defCOLOR_GRAY);

    CGXStyle normalStyle;
    normalStyle.SetTextColor(defCOLOR_BLACK)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(9).SetBold(FALSE))
            .SetInterior(defCOLOR_WHITE);

    // show the header
    ostream << _T("\n\n");

    CString str;
    str.LoadString(IDS_UNITNAME_H);
    ostream << str;
    ostream << CSize(150, 40); // set the cell size
    ostream << style;
    ostream << _T("\t");

    str.LoadString(IDS_UNITDES_H);
    ostream << str;
    ostream << CSize(200, 0); // set the cell width only
    ostream << style;
    ostream << _T("\t");

    str.LoadString(IDS_UNITCOST_H);
    ostream << str;
    ostream << style;
    ostream << _T("\t");

    str.LoadString(IDS_UNITOWNER_H);
    ostream << str;
    ostream << CSize(200, 0); // set the cell width only
    ostream << style;

    // process the group
    FillGridUnitGroup(m_pModel->GetMainUserGroup(), ostream);

    // the next following lines are for the all processes summary
    ostream << _T("\n\n\n");

    str.LoadString(IDS_SYMBOLREF_H);
    ostream << str;
    ostream << style;
    ostream << _T("\t");

    str.LoadString(IDS_SYMBOLNAME_H);
    ostream << str;
    ostream << style;
    ostream << _T("\t");

    str.LoadString(IDS_SYMBOLDES_H);
    ostream << str;
    ostream << style;

    const std::size_t count = m_TabNameArray.GetSize();

    // iterate through all tabs and show the info. Start with the second tab, the first tab is this one
    for (std::size_t i = 1; i < count; ++i)
    {
        // get the process matching with the model name, in case sensitive and only in local symbols
        CODComponentSet* pSet = m_pModel->FindSymbol(m_TabNameArray.GetAt(i), _T(""), true, true, true);

        if (!pSet || pSet->GetSize() <= 0)
            continue;

        PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pSet->GetAt(0));

        if (!pProcess)
            continue;

        ostream << _T("\n");

        ostream << pProcess->GetSymbolReferenceNumberStr();
        ostream << normalStyle;
        ostream << _T("\t");

        ostream << pProcess->GetSymbolName();
        ostream << normalStyle;
        ostream << _T("\t");

        ostream << pProcess->GetSymbolComment();

        int left;
        int top;

        // check the row count
        const ROWCOL rowCount = ostream.GetGridCore()->GetRowCount();
        ostream.GetCurSel(left, top);

        // if not enough, add 5 rows
        if ((top + 5) > int(rowCount))
            ostream.GetGridCore()->SetRowCount(rowCount + 5);
    }

    return true;
}
//---------------------------------------------------------------------------
void PSS_CheckReportGenerator::FillGridUnitGroup(PSS_UserGroupEntity* pGroup, PSS_OStreamGrid& ostream)
{
    if (!pGroup)
        return;

    // add the group line
    ostream << _T("\n");

    ostream << pGroup->GetEntityName();
    ostream << _T("\t");

    ostream << pGroup->GetEntityDescription();
    ostream << _T("\t");

    ostream << pGroup->GetEntityCost();
    ostream << _T("\t");

    if (pGroup->GetParent())
        ostream << pGroup->GetParent()->GetEntityName();
    else
        ostream << _T("");

    if (pGroup->ContainEntity())
    {
        const int count = pGroup->GetEntityCount();
        int       left;
        int       top;

        // check the row count
        const ROWCOL rowCount = ostream.GetGridCore()->GetRowCount();
        ostream.GetCurSel(left, top);

        // if not enough, add rows
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
void PSS_CheckReportGenerator::FillGridUnitRole(PSS_UserRoleEntity* pRole, PSS_OStreamGrid& ostream)
{
    // add the role line
    ostream << _T("\n");

    ostream << pRole->GetEntityName();
    ostream << _T("\t");

    ostream << pRole->GetEntityDescription();
    ostream << _T("\t");

    // no cost for a role
    ostream << _T("");
    ostream << _T("\t");

    if (pRole->GetParent())
        ostream << pRole->GetParent()->GetEntityName();
    else
        ostream << _T("");
}
//---------------------------------------------------------------------------
bool PSS_CheckReportGenerator::FillGridProcess(CGXGridCore& gridCore, std::size_t index)
{
    // is index out of bounds?
    if (index >= std::size_t(m_TabNameArray.GetSize()))
        return false;

    // get the process matching with the model name, in case sensitive
    PSS_ProcessGraphModelMdl* pModel = m_pModel->FindModel(m_TabNameArray.GetAt(index), true);

    if (!pModel)
        return false;

    // build the output stream grid object
    PSS_OStreamGrid ostream(&gridCore);

    // default size, 60 rows x 15 columns
    gridCore.SetRowCount(60);
    gridCore.SetColCount(15);

    // build the navigation grid process
    ZUGridProcessNavigation processNavigation(pModel, static_cast<void*>(&ostream));

    // navigate through the process symbols
    return processNavigation.Navigate();
}
//---------------------------------------------------------------------------
