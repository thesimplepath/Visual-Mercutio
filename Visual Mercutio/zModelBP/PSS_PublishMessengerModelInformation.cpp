/****************************************************************************
 * ==> PSS_PublishMessengerModelInformation --------------------------------*
 ****************************************************************************
 * Description : Provides the publish to Messenger model information        *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "StdAfx.h"
#include "PSS_PublishMessengerModelInformation.h"

 //---------------------------------------------------------------------------
 // PSS_PublishMessengerModelInformation
 //---------------------------------------------------------------------------
PSS_PublishMessengerModelInformation::PSS_PublishMessengerModelInformation(PSS_ProcessGraphModelDoc* pDoc,
                                                                           const CString&            messengerAddress,
                                                                           const CString&            messengerAlias) :
    m_pDoc(pDoc),
    m_MessengerAddress(messengerAddress),
    m_MessengerAlias(messengerAlias)
{}
//---------------------------------------------------------------------------
PSS_PublishMessengerModelInformation::~PSS_PublishMessengerModelInformation()
{}
//---------------------------------------------------------------------------
