/****************************************************************************
 * ==> PSS_ExtractModelUnitGroupAssigned -----------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which navigates through the model and *
 *               determines which unit group is attributed to which symbol. *
 *               From this list it's possible to rebuild the existing link  *
 *               hierarchy between the symbols and the unit groups          *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_ExtractModelUnitGroupAssigned.h"

// processsoft
#include "PSS_ProcessGraphModelMdl.h"
#include "PSS_UserEntity.h"
#include "PSS_Symbol.h"
#include "PSS_LinkSymbol.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_ExtractModelUnitGroupAssigned
//---------------------------------------------------------------------------
PSS_ExtractModelUnitGroupAssigned::PSS_ExtractModelUnitGroupAssigned(PSS_ProcessGraphModelMdl* pModel,
                                                                     void*                     pClass) :
    PSS_ModelNavigation(pModel, pClass),
    m_pUserEntity(NULL)
{}
//---------------------------------------------------------------------------
PSS_ExtractModelUnitGroupAssigned::~PSS_ExtractModelUnitGroupAssigned()
{}
//---------------------------------------------------------------------------
bool PSS_ExtractModelUnitGroupAssigned::OnStart()
{
    m_pUserEntity = static_cast<PSS_UserEntity*>(m_pClass);

    if (!m_pUserEntity)
        return false;

    // remove all elements from the set
    m_Set.RemoveAll();

    // nothing else to do
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractModelUnitGroupAssigned::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractModelUnitGroupAssigned::OnSymbol(PSS_Symbol* pSymbol)
{
    if (pSymbol->HasUnit() && pSymbol->GetUnitName() == m_pUserEntity->GetEntityName())
        m_Set.Add(pSymbol);

    return true;
}
//---------------------------------------------------------------------------
bool PSS_ExtractModelUnitGroupAssigned::OnLink(PSS_LinkSymbol* pLink)
{
    if (pLink->HasUnit() && pLink->GetUnitName() == m_pUserEntity->GetEntityName())
        m_Set.Add(pLink);

    return true;
}
//---------------------------------------------------------------------------
