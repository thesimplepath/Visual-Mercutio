/****************************************************************************
 * ==> PSS_GridProcessNavigation -------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will navigate through a process *
 *               and write the information to the report grid               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_GridProcessNavigation.h"

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

// resources
#include "zModelBP\zModelBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_GridProcessNavigation
//---------------------------------------------------------------------------
PSS_GridProcessNavigation::PSS_GridProcessNavigation(PSS_ProcessGraphModelMdl* pModel,
                                                     void*                     pClass) :
    PSS_ProcessNavigation(pModel, pClass),
    m_pOStream(NULL)
{}
//---------------------------------------------------------------------------
PSS_GridProcessNavigation::~PSS_GridProcessNavigation()
{}
//---------------------------------------------------------------------------
bool PSS_GridProcessNavigation::OnStart()
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

    CGXStyle style;

    // initialize the style for header cells
    style.SetTextColor(defCOLOR_WHITE)
            .SetFont(CGXFont().SetFaceName(_T("Verdana"))
            .SetSize(12).SetBold(TRUE))
            .SetDraw3dFrame(gxFrameNormal)
            .SetInterior(defCOLOR_GRAY);

    CString str;

    // show the header
    str.LoadString(IDS_SYMBOLREF_H);
    *m_pOStream << _T("\n\n");
    *m_pOStream << str;
    *m_pOStream << CSize(100, 40);
    *m_pOStream << style;
    *m_pOStream << "\t";

    str.LoadString(IDS_SYMBOLNAME_H);
    *m_pOStream << str;
    *m_pOStream << CSize(150, 0);
    *m_pOStream << style;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_SYMBOLDES_H);
    *m_pOStream << str;
    *m_pOStream << CSize(200, 0);
    *m_pOStream << style;
    *m_pOStream << _T("\t");

    str.LoadString(IDS_SYMBOLUNIT_H);
    *m_pOStream << str;
    *m_pOStream << CSize(150, 0);
    *m_pOStream << style;

    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridProcessNavigation::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridProcessNavigation::OnDoorSymbol(PSS_DoorSymbolBP* pSymbol)
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

    // add the symbol line
    *m_pOStream << _T("\n");
    *m_pOStream << pSymbol->GetSymbolReferenceNumberStr();
    *m_pOStream << _T("\t");
    *m_pOStream << pSymbol->GetSymbolName();
    *m_pOStream << _T("\t");
    *m_pOStream << pSymbol->GetSymbolComment();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridProcessNavigation::OnPageSymbol(PSS_PageSymbolBP* pSymbol)
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

    // add the symbol line
    *m_pOStream << _T("\n");
    *m_pOStream << pSymbol->GetSymbolReferenceNumberStr();
    *m_pOStream << _T("\t");
    *m_pOStream << pSymbol->GetSymbolName();
    *m_pOStream << _T("\t");
    *m_pOStream << pSymbol->GetSymbolComment();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridProcessNavigation::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
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

    // add the symbol line
    *m_pOStream << _T("\n");
    *m_pOStream << pSymbol->GetSymbolReferenceNumberStr();
    *m_pOStream << _T("\t");
    *m_pOStream << pSymbol->GetSymbolName();
    *m_pOStream << _T("\t");
    *m_pOStream << pSymbol->GetSymbolComment();
    *m_pOStream << _T("\t");
    *m_pOStream << pSymbol->GetUnitName();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridProcessNavigation::OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol)
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

    // Check the row count
    const ROWCOL rowCount = m_pOStream->GetGridCore()->GetRowCount();

    int left;
    int top;

    m_pOStream->GetCurSel(left, top);

    // if not enough, add the missing rows
    if ((top + 5) > int(rowCount))
        m_pOStream->GetGridCore()->SetRowCount(rowCount + 5);

    // add the symbol line
    *m_pOStream << _T("\n");
    *m_pOStream << pSymbol->GetSymbolReferenceNumberStr();
    *m_pOStream << _T("\t");
    *m_pOStream << pSymbol->GetSymbolName();
    *m_pOStream << _T("\t");
    *m_pOStream << pSymbol->GetSymbolComment();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridProcessNavigation::OnStartSymbol(PSS_StartSymbolBP* pSymbol)
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

    // add the symbol line
    *m_pOStream << _T("\n");
    *m_pOStream << pSymbol->GetSymbolReferenceNumberStr();
    *m_pOStream << _T("\t");
    *m_pOStream << pSymbol->GetSymbolName();
    *m_pOStream << _T("\t");
    *m_pOStream << pSymbol->GetSymbolComment();
    *m_pOStream << _T("\t");
    *m_pOStream << pSymbol->GetUnitName();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridProcessNavigation::OnStopSymbol(PSS_StopSymbolBP* pSymbol)
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

    // add the symbol line
    *m_pOStream << _T("\n");
    *m_pOStream << pSymbol->GetSymbolReferenceNumberStr();
    *m_pOStream << _T("\t");
    *m_pOStream << pSymbol->GetSymbolName();
    *m_pOStream << _T("\t");
    *m_pOStream << pSymbol->GetSymbolComment();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridProcessNavigation::OnDeliverableLinkSymbol(PSS_DeliverableLinkSymbolBP* pSymbol)
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

    // add the symbol line
    *m_pOStream << _T("\n");
    *m_pOStream << pSymbol->GetSymbolReferenceNumberStr();
    *m_pOStream << _T("\t");
    *m_pOStream << pSymbol->GetSymbolName();
    *m_pOStream << _T("\t");
    *m_pOStream << pSymbol->GetSymbolComment();

    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridProcessNavigation::OnSymbol(PSS_Symbol* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_GridProcessNavigation::OnLink(PSS_LinkSymbol* pLink)
{
    return true;
}
//---------------------------------------------------------------------------
