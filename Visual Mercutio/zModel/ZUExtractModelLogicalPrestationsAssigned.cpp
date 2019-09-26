// **************************************************************************************************************
// *                            Classe ZUExtractModelLogicalPrestationsAssigned                                    *
// **************************************************************************************************************
// * JMR-MODIF - Le 20 février 2006 - Ajout de la classe ZUExtractModelLogicalPrestationsAssigned.                *
// **************************************************************************************************************
// * Cette classe permet de déterminer quelle prestation est attibuée à quel symbole. A partir de cette liste,    *
// * il est possible de reconstruire la hiérarchie des liens existants entre symboles et prestations.            *
// **************************************************************************************************************

#include "stdafx.h"
#include "ProcGraphModelMdl.h"
#include "ZUExtractModelLogicalPrestationsAssigned.h"

#include "ZBPrestationsEntity.h"

#include "ZBSymbol.h"
#include "ZBLinkSymbol.h"

#include "zBaseLib\PSS_Tokenizer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUExtractModelLogicalPrestationsAssigned::ZUExtractModelLogicalPrestationsAssigned( ZDProcessGraphModelMdl*    pModel    /*= NULL*/,
                                                                                    void*                    pClass    /*= NULL*/ )
    : ZUModelNavigation( pModel, pClass )
{
}

ZUExtractModelLogicalPrestationsAssigned::~ZUExtractModelLogicalPrestationsAssigned()
{
}

bool ZUExtractModelLogicalPrestationsAssigned::OnStart()
{
    m_pPrestationsEntity = static_cast<ZBPrestationsEntity*>( m_pClass );

    if ( !m_pPrestationsEntity )
    {
        return false;
    }

    // Remove all elements from the set
    m_Set.RemoveAll();

    // Nothing more to do
    return true;
}

bool ZUExtractModelLogicalPrestationsAssigned::OnFinish()
{
    return true;
}

bool ZUExtractModelLogicalPrestationsAssigned::OnSymbol( ZBSymbol* pSymbol )
{
    if ( pSymbol->HasPrestations() )
    {
        PSS_Tokenizer aToken = pSymbol->GetPrestationsList();

        for ( size_t i = 0; i < aToken.GetTokenCount(); i++ )
        {
            CString m_Src = _T( "" );
            aToken.GetTokenAt( i, m_Src );

            if ( m_Src == m_pPrestationsEntity->GetEntityName() )
            {
                m_Set.Add( pSymbol );
            }
        }
    }

    return true;
}

bool ZUExtractModelLogicalPrestationsAssigned::OnLink( ZBLinkSymbol* pLink )
{
    return true;
}
