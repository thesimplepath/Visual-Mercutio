// ZBCheckReportGenerator.cpp: implementation of the ZBCheckReportGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZBCheckReportGenerator.h"

#include "zModel\PSS_ProcessGraphModelDoc.h"
#include "zModelBP\PSS_ProcessGraphModelMdlBP.h"
#include "zReport\ZDGridDoc.h"

#include "zModelBP\PSS_ExtractProcessName.h"
#include "ZUGridProcessNavigation.h"

#include "zModelBP\PSS_ProcessSymbolBP.h"

#include "zModel\PSS_UserGroupEntity.h"
#include "zModel\PSS_UserRoleEntity.h"

#include "zBaseLib\PSS_Global.h"

#include "zReport\zReportRes.h"
#include "zReportBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 29 mars 2006 - Ajout des déclarations unicode _T( ), nettoyage du code inutile. (En commentaires)

IMPLEMENT_SERIAL(ZBCheckReportGenerator, ZBModelBPReportGenerator, g_DefVersion)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZBCheckReportGenerator::ZBCheckReportGenerator(ZDGridDocument*                pDoc        /*= NULL*/,
                                               PSS_ProcessGraphModelMdlBP*    pModel        /*= NULL*/,
                                               PSS_ProcessGraphModelDoc*        pSourceDoc    /*= NULL*/)
    : ZBModelBPReportGenerator(pDoc, pModel, pSourceDoc)
{}

ZBCheckReportGenerator::~ZBCheckReportGenerator()
{}

bool ZBCheckReportGenerator::FillGrid(CGXGridCore& GridCore, size_t Index)
{
    if (Index == 0)
    {
        return FillGridUnit(GridCore);
    }

    return FillGridProcess(GridCore, Index);
}

bool ZBCheckReportGenerator::FillGridUnit(CGXGridCore& GridCore)
{
    ZBOStreamGrid ostream(&GridCore);

    // Default size
    GridCore.SetRowCount(60);        // 60 rows
    GridCore.SetColCount(15);        // 15 columns

    // Initialize the style for header cells
    CGXStyle Style;

    Style.SetTextColor(defCOLOR_WHITE)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(12).SetBold(TRUE))
        .SetInterior(defCOLOR_GRAY);

    CGXStyle NormalStyle;

    NormalStyle.SetTextColor(defCOLOR_BLACK)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(9).SetBold(FALSE))
        .SetInterior(defCOLOR_WHITE);

    // Display header
    CString s;

    ostream << _T("\n\n");

    s.LoadString(IDS_UNITNAME_H);
    ostream << s;
    ostream << CSize(150, 40);    // Set the cell size
    ostream << Style;
    ostream << _T("\t");

    s.LoadString(IDS_UNITDES_H);
    ostream << s;
    ostream << CSize(200, 0);        // Set the cell width only
    ostream << Style;
    ostream << _T("\t");

    s.LoadString(IDS_UNITCOST_H);
    ostream << s;
    ostream << Style;
    ostream << _T("\t");

    s.LoadString(IDS_UNITOWNER_H);
    ostream << s;
    ostream << CSize(200, 0);        // Set the cell width only
    ostream << Style;

    // Then process the group
    FillGridUnitGroup(m_pModel->GetMainUserGroup(), ostream);

    // The next following lines are for the resumé of all processes
    ostream << _T("\n\n\n");

    s.LoadString(IDS_SYMBOLREF_H);
    ostream << s;
    ostream << Style;
    ostream << _T("\t");

    s.LoadString(IDS_SYMBOLNAME_H);
    ostream << s;
    ostream << Style;
    ostream << _T("\t");

    s.LoadString(IDS_SYMBOLDES_H);
    ostream << s;
    ostream << Style;

    // Now, run through all tabs and display the correct information
    size_t Count = m_TabNameArray.GetSize();

    // Start with the second tab. First tab is this one.
    for (size_t i = 1; i < Count; ++i)
    {
        // Find the right process, function of the model name
        CODComponentSet* pSet = m_pModel->FindSymbol(m_TabNameArray.GetAt(i),
                                                     _T(""),
                                                     true,
                                                     true,        // In case sensitive,
                                                     true);    // and only local symbol

        if (!pSet ||
            pSet->GetSize() <= 0 ||
            pSet->GetAt(0) == NULL ||
            !ISA(pSet->GetAt(0), PSS_ProcessSymbolBP))
        {
            continue;
        }

        PSS_ProcessSymbolBP* pProcess = dynamic_cast<PSS_ProcessSymbolBP*>(pSet->GetAt(0));

        ostream << _T("\n");

        ostream << pProcess->GetSymbolReferenceNumberStr();
        ostream << NormalStyle;
        ostream << _T("\t");

        ostream << pProcess->GetSymbolName();
        ostream << NormalStyle;
        ostream << _T("\t");

        ostream << pProcess->GetSymbolComment();

        int top;
        int left;

        // Check the number of row
        ROWCOL RowCount = ostream.GetGridCore()->GetRowCount();
        ostream.GetCurSel(left, top);

        // If not enough, add 5 rows
        if ((top + 5) > (int)RowCount)
        {
            ostream.GetGridCore()->SetRowCount(RowCount + 5);
        }
    }

    return true;
}

void ZBCheckReportGenerator::FillGridUnitGroup(PSS_UserGroupEntity* pGroup, ZBOStreamGrid &ostream)
{
    if (!pGroup)
    {
        return;
    }

    // add the group line
    ostream << _T("\n");

    ostream << pGroup->GetEntityName();
    ostream << _T("\t");

    ostream << pGroup->GetEntityDescription();
    ostream << _T("\t");

    ostream << pGroup->GetEntityCost();
    ostream << _T("\t");

    if (pGroup->GetParent())
    {
        ostream << pGroup->GetParent()->GetEntityName();
    }
    else
    {
        ostream << _T("");
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
                FillGridUnitGroup(dynamic_cast<PSS_UserGroupEntity*>(pEntity), ostream);
            }

            if (ISA(pEntity, PSS_UserRoleEntity))
            {
                FillGridUnitRole(dynamic_cast<PSS_UserRoleEntity*>(pEntity), ostream);
            }
        }
    }
}

void ZBCheckReportGenerator::FillGridUnitRole(PSS_UserRoleEntity* pRole, ZBOStreamGrid &ostream)
{
    // add the role line
    ostream << _T("\n");

    ostream << pRole->GetEntityName();
    ostream << _T("\t");

    ostream << pRole->GetEntityDescription();
    ostream << _T("\t");

    ostream << _T("");    // No cost for a role
    ostream << _T("\t");

    if (pRole->GetParent())
    {
        ostream << pRole->GetParent()->GetEntityName();
    }
    else
    {
        ostream << _T("");
    }
}

bool ZBCheckReportGenerator::FillGridProcess(CGXGridCore& GridCore, size_t Index)
{
    // Check the index validity
    if (Index >= (size_t)m_TabNameArray.GetSize())
    {
        return false;
    }

    // Find the right process, function of the model name
    PSS_ProcessGraphModelMdl* pModel = m_pModel->FindModel(m_TabNameArray.GetAt(Index), true); // In case sensitive

    if (!pModel)
    {
        return false;
    }

    // Construct the output stream grid object
    ZBOStreamGrid ostream(&GridCore);

    // Default size
    GridCore.SetRowCount(60);        // 60 rows
    GridCore.SetColCount(15);        // 15 columns

    // Construct the navigation grid process
    ZUGridProcessNavigation ProcessNavigation(pModel, static_cast<void*>(&ostream));

    // Now navigate through process symbols
    return ProcessNavigation.Navigate();
}

// To fill the tab array, use a visitor class 
void ZBCheckReportGenerator::FillTabArray()
{
    // if no doc nor model defined. nothing to do.
    if (!m_pDoc || !m_pModel)
    {
        return;
    }

    // First, remove all elements
    m_TabNameArray.RemoveAll();

    PSS_ExtractProcessName extractProcessName(m_pModel);

    // First tab is for the units 
    CString s;
    s.LoadString(IDS_UNITNAME_TAB);
    m_TabNameArray.Add(s);

    // JMR-MODIF - Le 29 mars 2006 - Ajout de l'index de tri : On trie la liste depuis l'onglet 1.
    extractProcessName.FillProcessNameArray(&m_TabNameArray, 1);
}

const CString ZBCheckReportGenerator::GetReportTitle() const
{
    // Build the title function of the model
    CString s;

    if (m_pDoc)
    {
        s = m_pDoc->GetTitle();
    }

    CString ReportType;
    ReportType.LoadString(IDS_CHECK_RPT_T);

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
