/////////////////////////////////////////////////////////////////////////////
//@doc XXXClass
//@module XXXClass.cpp | Implementation of the <c XXXClass> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Gaya
// <nl>Created: 03/2002
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pPublishSettings.h"

std::string pPublishSettings::m_Url           = _T("http://localhost:8080/soap/servlet/rpcrouter");
std::string pPublishSettings::m_ModelService  = _T("urn:emessenger");
std::string pPublishSettings::m_ServerService = _T("urn:pssserver");
std::string pPublishSettings::m_FileService   = _T("urn:pssfile");
