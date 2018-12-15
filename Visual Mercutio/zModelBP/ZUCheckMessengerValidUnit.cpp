// ZUCheckMessengerValidUnit.cpp: implementation of the ZUCheckMessengerValidUnit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ZUCheckMessengerValidUnit.h"
#include "ZBBPProcedureSymbol.h"
#include "ZBBPStartSymbol.h"
#include "ZBBPStopSymbol.h"

#include "zModel\ProcGraphModelMdl.h"
#include "zModel\ZBSymbol.h"
#include "zModel\ZBLinkSymbol.h"
#include "zModel\ZBUserGroupEntity.h"

// Include files for log
#include "zBaseLib\ZILog.h"
#include "zModel\ZBGenericSymbolErrorLine.h"

#include "zModelBPRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// JMR-MODIF - Le 20 avril 2006 - Ajout des décorations unicode _T( ), nettoyage du code inutile. (En commentaires)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ZUCheckMessengerValidUnit::ZUCheckMessengerValidUnit( ZDProcessGraphModelMdl*    pModel /*= NULL*/,
                                                      void*                        pClass /*= NULL*/ )
    : ZUProcessNavigation( pModel, pClass )
{
}

ZUCheckMessengerValidUnit::~ZUCheckMessengerValidUnit()
{
}

bool ZUCheckMessengerValidUnit::OnStart()
{
    if ( !m_pModel )
    {
        return false;
    }

    // Main user group is not valid
    if ( !m_pModel->MainUserGroupIsValid() )
    {
        if ( m_pLog )
        {
            CString message;
            message.LoadString( IDS_ERR_USERGROUP_DIFFMODEL );
            ZBGenericSymbolErrorLine e( message );
            m_pLog->AddLine( e );
        }

        // Increment error counter
        ++m_ErrorCounter;
    }

    // Main logical system is not valid
    if ( !m_pModel->MainLogicalSystemIsValid() )
    {
        if ( m_pLog )
        {
            CString message;
            message.LoadString( IDS_ERR_SYSTEMDEFXML_DIFFMODEL );
            ZBGenericSymbolErrorLine e( message );
            m_pLog->AddLine( e );
        }

        // Increment error counter
        ++m_ErrorCounter;
    }

    // JMR-MODIF - Le 20 avril 2006 - Ajout du code de test pour le fichier des prestations.
    if ( !m_pModel->MainLogicalPrestationsIsValid() )
    {
        if ( m_pLog )
        {
            CString message;
            message.LoadString( IDS_ERR_PRESTATIONSDEFXML_DIFFMODEL );
            ZBGenericSymbolErrorLine e( message );
            m_pLog->AddLine( e );
        }

        // Increment error counter
        ++m_ErrorCounter;
    }

    return true;
}

bool ZUCheckMessengerValidUnit::OnFinish()
{
    return true;
}

bool ZUCheckMessengerValidUnit::OnProcedureSymbol( ZBBPProcedureSymbol* pSymbol )
{
    // Test if it is a local symbol
    if ( !pSymbol || !pSymbol->IsLocal() )
    {
        return true;
    }

    // Check if unit defined for procedure
    if ( pSymbol->GetUnitGUID().IsEmpty() )
    {
        if ( m_pLog )
        {
            ZBGenericSymbolErrorLine e( IDS_AL_PROCEDURE_INC_17,
                                        pSymbol->GetSymbolName(),
                                        pSymbol->GetAbsolutePath(),
                                        -1,
                                        1 );

            m_pLog->AddLine( e );
        }

        // Increment error counter
        ++m_ErrorCounter;
    }

    return true;
}

bool ZUCheckMessengerValidUnit::OnStartSymbol( ZBBPStartSymbol* pSymbol )
{
    // Test if it is a local symbol
    if ( !pSymbol || !pSymbol->IsLocal() )
    {
        return true;
    }

    // Check if unit defined for procedure
    if ( pSymbol->GetUnitGUID().IsEmpty() )
    {
        if ( m_pLog )
        {
            ZBGenericSymbolErrorLine e( IDS_AL_START_INC_14,
                                        pSymbol->GetSymbolName(),
                                        pSymbol->GetAbsolutePath(),
                                        -1,
                                        1 );

            m_pLog->AddLine( e );
        }

        // Increment error counter
        ++m_ErrorCounter;
    }

    return true;
}

bool ZUCheckMessengerValidUnit::OnStopSymbol( ZBBPStopSymbol* pSymbol )
{
    // Test if it is a local symbol
    if ( !pSymbol || !pSymbol->IsLocal() )
    {
        return true;
    }

    // Check if unit defined for procedure
    if ( pSymbol->GetUnitGUID().IsEmpty() )
    {
        if ( m_pLog )
        {
            ZBGenericSymbolErrorLine e( IDS_AL_STOP_INC_7,
                                        pSymbol->GetSymbolName(),
                                        pSymbol->GetAbsolutePath(),
                                        -1,
                                        1 );

            m_pLog->AddLine( e );
        }

        // Increment error counter
        ++m_ErrorCounter;
    }

    return true;
}
