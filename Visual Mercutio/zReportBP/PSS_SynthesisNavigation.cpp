/****************************************************************************
 * ==> PSS_SynthesisNavigation ---------------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will navigate through the       *
 *               processes and write the synthesis info to the report       *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SynthesisNavigation.h"

// processsoft
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_ProcessGraphModelMdl.h"
#include "zModel\PSS_ProcessGraphPage.h"
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
#include "zReportBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_SynthesisNavigation
//---------------------------------------------------------------------------
PSS_SynthesisNavigation::PSS_SynthesisNavigation(PSS_ProcessGraphModelMdl* pModel,
                                                 void*                     pClass,
                                                 PSS_ProcessGraphModelMdl* pRootModel,
                                                 const CString&            domainName,
                                                 const CString&            unitName) :
    PSS_ProcessNavigation(pModel, pClass),
    m_pOStream(NULL),
    m_pRootModel(pRootModel),
    m_DomainName(domainName),
    m_UnitName(unitName)
{}
//---------------------------------------------------------------------------
PSS_SynthesisNavigation::~PSS_SynthesisNavigation()
{}
//---------------------------------------------------------------------------
bool PSS_SynthesisNavigation::OnStart()
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

    m_BlueStyle.SetTextColor(defCOLOR_BLACK).SetInterior(RGB(0, 128, 255));

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SynthesisNavigation::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_SynthesisNavigation::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
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
        m_pOStream->GetGridCore()->SetRowCount(rowCount + 30);

    CGXStyle wrapStyle;
    wrapStyle.SetWrapText(TRUE);

    bool error;

    // only for the specific unit
    const CString unitName = pSymbol->RetrieveUnitName(pSymbol->GetUnitGUID(), error);

    // check if for the same unit
    if (m_UnitName == unitName)
    {
        // add the symbol line
        *m_pOStream << m_DomainName;
        *m_pOStream << m_BlueStyle;
        *m_pOStream << _T("\t");

        *m_pOStream << m_CurrentProcessName;
        *m_pOStream << m_BlueStyle;
        *m_pOStream << wrapStyle;
        *m_pOStream << _T("\t");

        *m_pOStream << pSymbol->GetSymbolName();
        *m_pOStream << wrapStyle;
        *m_pOStream << _T("\n");
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SynthesisNavigation::OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol)
{
    m_CurrentProcessName = pSymbol->GetSymbolName();

    PSS_ProcessGraphModelMdl* pOwnerModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(pSymbol->GetOwnerModel());

    if (pOwnerModel)
    {
        PSS_ProcessGraphPage* pPage = m_pRootModel->FindModelPage(pOwnerModel, true);

        if (pPage)
            m_DomainName = pPage->GetPageName();
        else
            m_DomainName.LoadString(IDS_SYNTHESYS_NOT_FOUND);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_SynthesisNavigation::OnSymbol(PSS_Symbol* pSymbol)
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_SynthesisNavigation::OnLink(PSS_LinkSymbol* pLink)
{
    return true;
}
//---------------------------------------------------------------------------
