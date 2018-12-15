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
#include "pPublishFile.h"

#include "zSoapException.h"

// JMR-MODIF - Le 15 septembre 2005 - Ajout des décorations Unicode _T(), nettoyage du code inutile.(En commentaires)

/////////////////////////////////////////////////////////////////////////////////
// Default constructor
pPublishFile::pPublishFile()
{
}

/////////////////////////////////////////////////////////////////////////////////
// Default destructor
pPublishFile::~pPublishFile()
{
}

/////////////////////////////////////////////////////////////////////////////////
// send data to urn:pssfile , method: pubFile
// out:returns true on success
bool pPublishFile::pubFile( pfile mfile )
{
    SOAPDebugger::SetFile( _T( "c:\\psssoap_pufile.log" ) );

    bool RetValue = true;

    try
    {
        // Defs
        string wdsl_urn = pPublishSettings::fileservice;

        // Initialize objects
        string url = pPublishSettings::url;
        SOAPProxy proxy( url.c_str() );

        // Proc
        SOAPMethod pubFile( _T( "pubFile" ), wdsl_urn.c_str(), _T( "http://" ) );
        SOAPParameter& ref = pubFile.AddParameter( _T( "mfile" ) );
        ref << mfile;

        if ( (int)proxy.Execute( pubFile ).GetReturnValue() < 0 )
        {
            TRACE( _T( "Pub file failed\n" ) );
            RetValue = false;
        }

        // Everything was fine...
    }
    catch ( SOAPException& ex )
    {
        TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
        RetValue = false;
    }

    SOAPDebugger::Close();
    return RetValue;
}

/////////////////////////////////////////////////////////////////////////////////
// check if the file has changed on the server recently - 0=no , 1=a recent file is available, -1=old file available
int pPublishFile::pubHasChanged( int    mfolder,
                                 string    mfilename,
                                 int    mday,
                                 int    mmonth,
                                 int    myear,
                                 int    mhour,
                                 int    mmin,
                                 int    msec )
{
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////
// download the file from the server
pfile pPublishFile::pubGetFile( int mfolder, string mfilename )
{
    SOAPDebugger::SetFile( _T( "c:\\psssoap.log" ) );
    pfile rstr;

    try
    {
        // Defs
        string wdsl_urn = _T( "urn:pssfile" );    //not from config engine at time....pPublishSettings::service;

        // Initialize objects
        string url = pPublishSettings::url;
        SOAPProxy proxy( url.c_str() );

        // Proc
        SOAPMethod pubGetFile( _T( "pubGetFile" ), wdsl_urn.c_str(), _T( "http://" ) );
        pubGetFile.AddParameter( _T( "mfolder" ) ).SetValue( mfolder );
        pubGetFile.AddParameter( _T( "mfilename" ) ).SetValue( mfilename.c_str() );

        const SOAPResponse& resp = proxy.Execute( pubGetFile );
        resp.GetReturnValue() >> rstr;
    }
    catch ( SOAPException& ex )
    {
        TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
        // JMR-MODIF - Le 16 mai 2006 - Ne pas lancer une nouvelle exception après capture de la précédente,
        // car cette nouvelle exception n'est pas traitée, et interrompt le programme.
//        throw ZBSoapException( IDS_SOAPEXCEPTION, ex.What().Str(), __FILE__, __LINE__ );
        return pfile();
    }

    return rstr;
}
