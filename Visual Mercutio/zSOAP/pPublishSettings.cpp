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

// JMR-MODIF - Le 15 septembre 2005 - Ajout des décorations Unicode _T(), nettoyage du code inutile.(En commentaires)

string pPublishSettings::url            = _T( "http://localhost:8080/soap/servlet/rpcrouter" );
string pPublishSettings::modelservice    = _T( "urn:emessenger" );
string pPublishSettings::serverservice    = _T( "urn:pssserver" );
string pPublishSettings::fileservice    = _T( "urn:pssfile" );
