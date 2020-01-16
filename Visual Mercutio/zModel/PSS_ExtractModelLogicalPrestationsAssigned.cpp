/****************************************************************************
 * ==> PSS_ExtractModelLogicalPrestationsAssigned --------------------------*
 ****************************************************************************
 * Description : Provides a navigator which navigates through the model and *
 *               determines which prestation is attributed to which symbol. *
 *               From this list it's possible to rebuild the existing link  *
 *               hierarchy between the symbols and the prestations          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ExtractModelLogicalPrestationsAssigned.h"

// processsoft
#include "zBaseLib\PSS_Tokenizer.h"
#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_PrestationsEntity.h"
#include "PSS_Symbol.h"
#include "PSS_LinkSymbol.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ExtractModelLogicalPrestationsAssigned
//---------------------------------------------------------------------------
PSS_ExtractModelLogicalPrestationsAssigned::PSS_ExtractModelLogicalPrestationsAssigned(PSS_ProcessGraphModelMdl* pModel,
                                                                                       void*                     pClass) :
    PSS_ModelNavigation(pModel, pClass),
    m_pPrestationsEntity(NULL)
{}
//---------------------------------------------------------------------------
PSS_ExtractModelLogicalPrestationsAssigned::~PSS_ExtractModelLogicalPrestationsAssigned()
{}
//---------------------------------------------------------------------------
bool PSS_ExtractModelLogicalPrestationsAssigned::OnStart()
{
    m_pPrestationsEntity = static_cast<PSS_PrestationsEntity*>(m_pClass);

    if (!m_pPrestationsEntity)
        return false;

    // remove all elements from the set
    m_Set.RemoveAll();

    // nothing else to do
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractModelLogicalPrestationsAssigned::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractModelLogicalPrestationsAssigned::OnSymbol(PSS_Symbol* pSymbol)
{
    // no prestations, nothing to do
    if (!pSymbol->HasPrestations())
        return true;

    PSS_Tokenizer     tokens     = pSymbol->GetPrestationsList();
    const std::size_t tokenCount = tokens.GetTokenCount();

    // iterate through prestation tokens and find the matching symbols
    for (std::size_t i = 0; i < tokenCount; ++i)
    {
        CString src;
        tokens.GetTokenAt(i, src);

        if (src == m_pPrestationsEntity->GetEntityName())
            m_Set.Add(pSymbol);
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractModelLogicalPrestationsAssigned::OnLink(PSS_LinkSymbol* pLink)
{
    return true;
}
//---------------------------------------------------------------------------
