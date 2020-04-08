/****************************************************************************
 * ==> PSS_BuildGenericSymbolNewName ---------------------------------------*
 ****************************************************************************
 * Description : Provides a helper which creates an unique and valid name   *
 *               for each generic symbols                                   *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_BuildGenericSymbolNewName.h"

// processsoft
#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_Symbol.h"
#include "PSS_LinkSymbol.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_BuildGenericSymbolNewName
//---------------------------------------------------------------------------
PSS_BuildGenericSymbolNewName::PSS_BuildGenericSymbolNewName(const CString& baseName) :
    PSS_BasicSymbolVisitor(),
    m_BaseName(baseName),
    m_Found(false)
{}
//---------------------------------------------------------------------------
PSS_BuildGenericSymbolNewName::~PSS_BuildGenericSymbolNewName()
{}
//---------------------------------------------------------------------------
CString PSS_BuildGenericSymbolNewName::GetNextAvailableSymbolName(CODModel& model)
{
    for (int p = 1; p < 10000000; ++p)
    {
        if (m_BaseName.IsEmpty())
            m_GenericSymbolName.Format(_T("Generic%d"), p);
        else
            m_GenericSymbolName.Format(_T("%s%d"), (const char*)m_BaseName, p);

        m_Found = false;

        // generate the name
        GetNextAvailableSymbolNamePvt(model);

        // if the new name is valid, return it
        if (!m_Found)
            return m_GenericSymbolName;
    }

    // if no page available, return empty string
    return _T("");
}
//---------------------------------------------------------------------------
bool PSS_BuildGenericSymbolNewName::Visit(CODComponent& symbol)
{
    CODComponent*   pComp       = &symbol;
    PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pComp);
    PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

    m_Found = ((pSymbol     && pSymbol->GetSymbolName()     == m_GenericSymbolName) ||
               (pLinkSymbol && pLinkSymbol->GetSymbolName() == m_GenericSymbolName));

    return false;
}
//---------------------------------------------------------------------------
void PSS_BuildGenericSymbolNewName::GetNextAvailableSymbolNamePvt(CODModel& model)
{
    PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(&model);

    if (pModel)
        pModel->AcceptVisitor(*this);
}
//---------------------------------------------------------------------------
