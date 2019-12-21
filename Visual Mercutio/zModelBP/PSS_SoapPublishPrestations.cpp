/****************************************************************************
 * ==> PSS_SoapPublishPrestations ------------------------------------------*
 ****************************************************************************
 * Description : Publish the prestations to Messenger through a SOAP        *
 *               protocol, and check the publication validity               *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_SoapPublishPrestations.h"

// processsoft
#include "zSOAP\PSS_SoapData_Settings.h"

// resources
#include "zModelBPRes.h"

#ifdef _DEBUG
    #undef THIS_FILE
    static char THIS_FILE[]=__FILE__;
    #define new DEBUG_NEW
#endif

//---------------------------------------------------------------------------
// PSS_SoapPublishPrestations
//---------------------------------------------------------------------------
PSS_SoapPublishPrestations::PSS_SoapPublishPrestations(ZBPublishMessengerModelInformation* pInfo, PSS_Log* pLog) :
    m_pInfo(pInfo),
    m_pLog(pLog)
{}
//---------------------------------------------------------------------------
PSS_SoapPublishPrestations::~PSS_SoapPublishPrestations()
{}
//---------------------------------------------------------------------------
bool PSS_SoapPublishPrestations::Publish()
{
    if (!m_pInfo || !m_pInfo->m_pDoc || !m_pInfo->m_pDoc->GetMainLogicalPrestations())
        return false;

    // copy the publication address from source info
    PSS_SoapData_Settings::m_Url = (const char*)m_pInfo->m_MessengerAddress;

    // publish all prestations from root one
    PublishPrestations(m_pInfo->m_pDoc->GetMainLogicalPrestations());

    return m_Prestations.Send();
}
//---------------------------------------------------------------------------
void PSS_SoapPublishPrestations::PublishPrestations(PSS_LogicalPrestationsEntity* pPrestations)
{
    if (!pPrestations)
        return;

    // log prestations content
    if (m_pLog && m_pLog->IsInDebugMode())
    {
        CString message;
        message.Format(IDS_AL_PUBLISHPRESTATION, (const char*)pPrestations->GetEntityName());
        PSS_GenericSymbolErrorLine e(message);
        m_pLog->AddLine(e);
    }

    // publish the prestations and their alias
    m_Prestations.Set(PSS_SoapData_Prestations(PSS_String16(pPrestations->GetGUID()),
                                               PSS_String16(pPrestations->GetParent() ? pPrestations->GetParent()->GetGUID() : _T("")),
                                               PSS_String16(pPrestations->GetEntityName())));

    m_Prestations.AddAlias(m_pInfo->m_MessengerAlias);

    #ifdef _DEBUG
        CString s;
        s.Format(_T(" Prestation = %s\n"), (const char*)pPrestations->GetEntityName());
        TRACE(s);
    #endif

    if (pPrestations->ContainEntity())
    {
        const int count = pPrestations->GetEntityCount();

        for (int i = 0; i < count; ++i)
        {
            ZBPrestationsEntity* pEntity = pPrestations->GetEntityAt(i);

            if (!pEntity)
                continue;

            PublishPrestations(dynamic_cast<PSS_LogicalPrestationsEntity*>(pEntity));
        }
    }
}
//---------------------------------------------------------------------------
