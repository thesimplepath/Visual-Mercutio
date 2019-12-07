// ZUGridProcessNavigation.cpp: implementation of the ZUGridProcessNavigation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUGridProcessNavigation.h"

#include "zModel\ProcGraphModelMdl.h"
#include "zModel\ZBSymbol.h"
#include "zModel\PSS_LinkSymbol.h"

#include "zModelBP\ZBBPDoorSymbol.h"
#include "zModelBP\ZBBPPageSymbol.h"
#include "zModelBP\ZBBPProcedureSymbol.h"
#include "zModelBP\ZBBPProcessSymbol.h"
#include "zModelBP\ZBBPStartSymbol.h"
#include "zModelBP\ZBBPStopSymbol.h"
#include "zModelBP\ZBDeliverableLinkSymbol.h"

#include "zReport\ZBOStreamGrid.h"

#include "zModelBP\zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 7 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUGridProcessNavigation::ZUGridProcessNavigation(PSS_ProcessGraphModelMdl*    pModel    /*= NULL*/,
                                                 void*                        pClass    /*= NULL*/)
    : ZUProcessNavigation(pModel, pClass)
{}

ZUGridProcessNavigation::~ZUGridProcessNavigation()
{}

bool ZUGridProcessNavigation::OnStart()
{
    // Start by casting the stream class
    m_postream = static_cast<ZBOStreamGrid*>(m_pClass);

    // Initialize the style for header cells
    CGXStyle Style;
    Style.SetTextColor(defCOLOR_WHITE)
        .SetFont(CGXFont().SetFaceName(_T("Verdana"))
                 .SetSize(12).SetBold(TRUE))
        .SetDraw3dFrame(gxFrameNormal)
        .SetInterior(defCOLOR_GRAY);

    // Display header
    CString s;
    *m_postream << _T("\n\n");
    s.LoadString(IDS_SYMBOLREF_H);
    *m_postream << s;
    *m_postream << CSize(100, 40);    // Set the cell size
    *m_postream << Style;
    *m_postream << "\t";

    s.LoadString(IDS_SYMBOLNAME_H);
    *m_postream << s;
    *m_postream << CSize(150, 0);        // Set the cell width only
    *m_postream << Style;
    *m_postream << _T("\t");

    s.LoadString(IDS_SYMBOLDES_H);
    *m_postream << s;
    *m_postream << CSize(200, 0);        // Set the cell width only
    *m_postream << Style;
    *m_postream << _T("\t");

    s.LoadString(IDS_SYMBOLUNIT_H);
    *m_postream << s;
    *m_postream << CSize(150, 0);        // Set the cell width only
    *m_postream << Style;

    return (m_postream) ? true : false;
}

bool ZUGridProcessNavigation::OnFinish()
{
    return true;
}

bool ZUGridProcessNavigation::OnDoorSymbol(ZBBPDoorSymbol* pSymbol)
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

    // add the symbol line
    *m_postream << _T("\n");
    *m_postream << pSymbol->GetSymbolReferenceNumberStr();
    *m_postream << _T("\t");
    *m_postream << pSymbol->GetSymbolName();
    *m_postream << _T("\t");
    *m_postream << pSymbol->GetSymbolComment();

    return true;
}

bool ZUGridProcessNavigation::OnPageSymbol(ZBBPPageSymbol* pSymbol)
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

    // add the symbol line
    *m_postream << _T("\n");
    *m_postream << pSymbol->GetSymbolReferenceNumberStr();
    *m_postream << _T("\t");
    *m_postream << pSymbol->GetSymbolName();
    *m_postream << _T("\t");
    *m_postream << pSymbol->GetSymbolComment();

    return true;
}

bool ZUGridProcessNavigation::OnProcedureSymbol(ZBBPProcedureSymbol* pSymbol)
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

    // add the symbol line
    *m_postream << _T("\n");
    *m_postream << pSymbol->GetSymbolReferenceNumberStr();
    *m_postream << _T("\t");
    *m_postream << pSymbol->GetSymbolName();
    *m_postream << _T("\t");
    *m_postream << pSymbol->GetSymbolComment();
    *m_postream << _T("\t");
    *m_postream << pSymbol->GetUnitName();

    return true;
}

bool ZUGridProcessNavigation::OnProcessSymbol(ZBBPProcessSymbol* pSymbol)
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

    // add the symbol line
    *m_postream << _T("\n");
    *m_postream << pSymbol->GetSymbolReferenceNumberStr();
    *m_postream << _T("\t");
    *m_postream << pSymbol->GetSymbolName();
    *m_postream << _T("\t");
    *m_postream << pSymbol->GetSymbolComment();

    return true;
}

bool ZUGridProcessNavigation::OnStartSymbol(ZBBPStartSymbol* pSymbol)
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

    // add the symbol line
    *m_postream << _T("\n");
    *m_postream << pSymbol->GetSymbolReferenceNumberStr();
    *m_postream << _T("\t");
    *m_postream << pSymbol->GetSymbolName();
    *m_postream << _T("\t");
    *m_postream << pSymbol->GetSymbolComment();
    *m_postream << _T("\t");
    *m_postream << pSymbol->GetUnitName();

    return true;
}

bool ZUGridProcessNavigation::OnStopSymbol(ZBBPStopSymbol* pSymbol)
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

    // add the symbol line
    *m_postream << _T("\n");
    *m_postream << pSymbol->GetSymbolReferenceNumberStr();
    *m_postream << _T("\t");
    *m_postream << pSymbol->GetSymbolName();
    *m_postream << _T("\t");
    *m_postream << pSymbol->GetSymbolComment();

    return true;
}

bool ZUGridProcessNavigation::OnDeliverableLinkSymbol(ZBDeliverableLinkSymbol* pSymbol)
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

    // add the symbol line
    *m_postream << _T("\n");
    *m_postream << pSymbol->GetSymbolReferenceNumberStr();
    *m_postream << _T("\t");
    *m_postream << pSymbol->GetSymbolName();
    *m_postream << _T("\t");
    *m_postream << pSymbol->GetSymbolComment();

    return true;
}

bool ZUGridProcessNavigation::OnSymbol(ZBSymbol* pSymbol)
{
    return true;
}

bool ZUGridProcessNavigation::OnLink(PSS_LinkSymbol* pLink)
{
    return true;
}
