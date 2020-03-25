// ZUSynthesisNavigation.cpp: implementation of the ZUSynthesisNavigation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZUSynthesisNavigation.h"

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

#include "zModelBP\zModelBPRes.h"
#include "zReportBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 7 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUSynthesisNavigation::ZUSynthesisNavigation(PSS_ProcessGraphModelMdl*    pModel        /*= NULL*/,
                                             void*                        pClass        /*= NULL*/,
                                             PSS_ProcessGraphModelMdl*    pRootModel    /*= NULL*/,
                                             const CString                domainName    /*= ""*/,
                                             const CString                unitName    /*= ""*/)
    : PSS_ProcessNavigation(pModel, pClass),
    m_pRootModel(pRootModel),
    m_DomainName(domainName),
    m_UnitName(unitName)
{}

ZUSynthesisNavigation::~ZUSynthesisNavigation()
{}

// Cette fonction est appelée lorsque la navigation démarre.
bool ZUSynthesisNavigation::OnStart()
{
    // Start by casting the stream class
    m_postream = static_cast<PSS_OStreamGrid*>(m_pClass);

    m_BlueStyle.SetTextColor(defCOLOR_BLACK)
        .SetInterior(RGB(0, 128, 255));

    return (m_postream) ? true : false;
}

// Cette fonction est appelée lorsque la navigation se termine.
bool ZUSynthesisNavigation::OnFinish()
{
    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type PSS_ProcedureSymbolBP dans le modèle.
bool ZUSynthesisNavigation::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    int top;
    int left;

    // Check the number of row
    ROWCOL RowCount = m_postream->GetGridCore()->GetRowCount();
    m_postream->GetCurSel(left, top);

    // If not enough, add 30 rows
    if ((top + 30) > (int)RowCount)
    {
        m_postream->GetGridCore()->SetRowCount(RowCount + 30);
    }

    CGXStyle WrapStyle;
    WrapStyle.SetWrapText(TRUE);

    // Only for the specific unit
    // Check if for the same unit
    bool Error;

    CString UnitName = pSymbol->RetrieveUnitName(pSymbol->GetUnitGUID(), Error);

    if (m_UnitName == UnitName)
    {
        // Add the symbol line
        *m_postream << m_DomainName;
        *m_postream << m_BlueStyle;
        *m_postream << _T("\t");

        *m_postream << m_CurrentProcessName;
        *m_postream << m_BlueStyle;
        *m_postream << WrapStyle;
        *m_postream << _T("\t");

        *m_postream << pSymbol->GetSymbolName();
        *m_postream << WrapStyle;
        *m_postream << _T("\n");
    }

    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type PSS_ProcessSymbolBP dans le modèle.
bool ZUSynthesisNavigation::OnProcessSymbol(PSS_ProcessSymbolBP* pSymbol)
{
    m_CurrentProcessName = pSymbol->GetSymbolName();

    PSS_ProcessGraphModelMdl* pOwnerModel = (PSS_ProcessGraphModelMdl*)pSymbol->GetOwnerModel();

    if (pOwnerModel)
    {
        PSS_ProcessGraphPage* pPage = m_pRootModel->FindModelPage(pOwnerModel, true);

        if (pPage)
        {
            m_DomainName = pPage->GetPageName();
        }
        else
        {
            m_DomainName.LoadString(IDS_SYNTHESYS_NOT_FOUND);
        }
    }

    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type PSS_Symbol dans le modèle.
bool ZUSynthesisNavigation::OnSymbol(PSS_Symbol* pSymbol)
{
    return true;
}

// Cette fonction est appelée lorsque la navigation visite un symbole de type PSS_LinkSymbol dans le modèle.
bool ZUSynthesisNavigation::OnLink(PSS_LinkSymbol* pLink)
{
    return true;
}
