/****************************************************************************
 * ==> PSS_BuildSymbolNewName ----------------------------------------------*
 ****************************************************************************
 * Description : Provides a helper which creates an unique and valid name   *
 *               for each symbols                                           *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_BuildSymbolNewName.h"

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
// PSS_BuildSymbolNewName
//---------------------------------------------------------------------------
PSS_BuildSymbolNewName::PSS_BuildSymbolNewName(const CString& baseName) :
    PSS_BasicSymbolVisitor(),
    m_BaseName(baseName),
    m_Found(false)
{}
//---------------------------------------------------------------------------
PSS_BuildSymbolNewName::~PSS_BuildSymbolNewName()
{}
//---------------------------------------------------------------------------
CString PSS_BuildSymbolNewName::GetNextAvailableSymbolName(CODModel& model, int refNumber)
{
    if (m_BaseName.IsEmpty())
        m_SymbolName.Format(_T("sym%d"), refNumber);
    else
        m_SymbolName.Format(_T("%s%d"), (const char*)m_BaseName, refNumber);

    m_Found = false;

    // generate the name
    GetNextAvailableSymbolNamePvt(model);

    // if the new name is valid, return it
    if (!m_Found)
        return m_SymbolName;

    // if no page available, return empty string
    return _T("");
}
//---------------------------------------------------------------------------
bool PSS_BuildSymbolNewName::Visit(CODComponent& symbol)
{
    CODComponent*   pComp       = &symbol;
    PSS_Symbol*     pSymbol     =                  dynamic_cast<PSS_Symbol*>(pComp);
    PSS_LinkSymbol* pLinkSymbol = pSymbol ? NULL : dynamic_cast<PSS_LinkSymbol*>(pComp);

    m_Found = ((pSymbol     && pSymbol->GetSymbolName()     == m_SymbolName) ||
               (pLinkSymbol && pLinkSymbol->GetSymbolName() == m_SymbolName));

    return false;
}
//---------------------------------------------------------------------------
void PSS_BuildSymbolNewName::GetNextAvailableSymbolNamePvt(CODModel& model)
{
    PSS_ProcessGraphModelMdl* pModel = dynamic_cast<PSS_ProcessGraphModelMdl*>(&model);

    if (pModel)
        pModel->AcceptVisitor(*this);
}
//---------------------------------------------------------------------------
