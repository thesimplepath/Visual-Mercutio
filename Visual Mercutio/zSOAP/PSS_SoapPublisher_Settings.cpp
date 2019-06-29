/****************************************************************************
 * ==> PSS_SoapPublisher_Settings ------------------------------------------*
 ****************************************************************************
 * Description : Settings for the SOAP protocol                             *
 * Developer   : Processsoft                                                *
 ****************************************************************************/

#include "stdafx.h"
#include "PSS_SoapPublisher_Settings.h"

std::string PSS_SoapPublisher_Settings::m_Url           = _T("http://localhost:8080/soap/servlet/rpcrouter");
std::string PSS_SoapPublisher_Settings::m_ModelService  = _T("urn:emessenger");
std::string PSS_SoapPublisher_Settings::m_ServerService = _T("urn:pssserver");
std::string PSS_SoapPublisher_Settings::m_FileService   = _T("urn:pssfile");
