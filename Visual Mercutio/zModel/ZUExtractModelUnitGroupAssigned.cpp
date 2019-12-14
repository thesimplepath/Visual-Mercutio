// **************************************************************************************************************
// *                                 Classe ZUExtractModelUnitGroupAssigned                                        *
// **************************************************************************************************************
// * Cette classe permet de déterminer quelle système logique est attibuée à quel symbole. A partir de cette    *
// * liste, il est possible de reconstruire la hiérarchie des liens existants entre symboles et systèmes        *
// * externes.                                                                                                    *
// **************************************************************************************************************

#include "stdafx.h"
#include "PSS_ProcessGraphModelMdl.h"
#include "ZUExtractModelUnitGroupAssigned.h"

#include "ZBUserEntity.h"

#include "ZBSymbol.h"
#include "PSS_LinkSymbol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 20 février 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUExtractModelUnitGroupAssigned::ZUExtractModelUnitGroupAssigned(PSS_ProcessGraphModelMdl*    pModel    /*= NULL*/,
                                                                 void*                        pClass    /*= NULL*/)
    : ZUModelNavigation(pModel, pClass)
{}

ZUExtractModelUnitGroupAssigned::~ZUExtractModelUnitGroupAssigned()
{}

bool ZUExtractModelUnitGroupAssigned::OnStart()
{
    m_pUserEntity = static_cast<ZBUserEntity*>(m_pClass);

    if (!m_pUserEntity)
    {
        return false;
    }

    // Remove all elements from the set
    m_Set.RemoveAll();

    // Nothing more to do
    return true;
}

bool ZUExtractModelUnitGroupAssigned::OnFinish()
{
    return true;
}

bool ZUExtractModelUnitGroupAssigned::OnSymbol(PSS_Symbol* pSymbol)
{
    if (pSymbol->HasUnit() && pSymbol->GetUnitName() == m_pUserEntity->GetEntityName())
    {
        m_Set.Add(pSymbol);
    }

    return true;
}

bool ZUExtractModelUnitGroupAssigned::OnLink(PSS_LinkSymbol* pLink)
{
    if (pLink->HasUnit() && pLink->GetUnitName() == m_pUserEntity->GetEntityName())
    {
        m_Set.Add(pLink);
    }

    return true;
}
