/****************************************************************************
 * ==> PSS_CheckMessengerValidUnit -----------------------------------------*
 ****************************************************************************
 * Description : Provides a navigator which will navigates through the      *
 *               process and write the process information to a grid        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_CheckMessengerValidUnit.h"

// processsoft
#include "zBaseLib\PSS_Log.h"
#include "zModel\PSS_ProcessGraphModelMdl.h"
#include "zModel\PSS_Symbol.h"
#include "zModel\PSS_LinkSymbol.h"
#include "zModel\PSS_UserGroupEntity.h"
#include "zModel\PSS_GenericSymbolErrorLine.h"
#include "PSS_ProcedureSymbolBP.h"
#include "PSS_StartSymbolBP.h"
#include "PSS_StopSymbolBP.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_CheckMessengerValidUnit
//---------------------------------------------------------------------------
PSS_CheckMessengerValidUnit::PSS_CheckMessengerValidUnit(PSS_ProcessGraphModelMdl* pModel, void* pClass) :
    ZUProcessNavigation(pModel, pClass)
{}
//---------------------------------------------------------------------------
PSS_CheckMessengerValidUnit::~PSS_CheckMessengerValidUnit()
{}
//---------------------------------------------------------------------------
bool PSS_CheckMessengerValidUnit::OnStart()
{
    if (!m_pModel)
        return false;

    // is main user group valid?
    if (!m_pModel->MainUserGroupIsValid())
    {
        if (m_pLog)
        {
            CString message;
            message.LoadString(IDS_ERR_USERGROUP_DIFFMODEL);
            PSS_GenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    // is main logical system valid?
    if (!m_pModel->MainLogicalSystemIsValid())
    {
        if (m_pLog)
        {
            CString message;
            message.LoadString(IDS_ERR_SYSTEMDEFXML_DIFFMODEL);
            PSS_GenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    // is main logical prestation valid?
    if (!m_pModel->MainLogicalPrestationsIsValid())
    {
        if (m_pLog)
        {
            CString message;
            message.LoadString(IDS_ERR_PRESTATIONSDEFXML_DIFFMODEL);
            PSS_GenericSymbolErrorLine e(message);
            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckMessengerValidUnit::OnFinish()
{
    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckMessengerValidUnit::OnProcedureSymbol(PSS_ProcedureSymbolBP* pSymbol)
{
    // check if it's a local symbol
    if (!pSymbol || !pSymbol->IsLocal())
        return true;

    // check if an unit is defined for the procedure
    if (pSymbol->GetUnitGUID().IsEmpty())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_PROCEDURE_INC_17,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);

            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckMessengerValidUnit::OnStartSymbol(PSS_StartSymbolBP* pSymbol)
{
    // check if it's a local symbol
    if (!pSymbol || !pSymbol->IsLocal())
        return true;

    // check if an unit is defined for the procedure
    if (pSymbol->GetUnitGUID().IsEmpty())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_START_INC_14,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);

            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    return true;
}
//---------------------------------------------------------------------------
bool PSS_CheckMessengerValidUnit::OnStopSymbol(PSS_StopSymbolBP* pSymbol)
{
    // check if it's a local symbol
    if (!pSymbol || !pSymbol->IsLocal())
        return true;

    // check if an unit is defined for the procedure
    if (pSymbol->GetUnitGUID().IsEmpty())
    {
        if (m_pLog)
        {
            PSS_GenericSymbolErrorLine e(IDS_AL_STOP_INC_7,
                                         pSymbol->GetSymbolName(),
                                         pSymbol->GetAbsolutePath(),
                                        -1,
                                         1);

            m_pLog->AddLine(e);
        }

        // increment the error counter
        ++m_ErrorCounter;
    }

    return true;
}
//---------------------------------------------------------------------------
