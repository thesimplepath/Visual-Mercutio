// **************************************************************************************************************
// *                                       Classe pCheckUniverse                                                *
// **************************************************************************************************************
// * JMR-MODIF - Le 21 juin 2006 - Création de la classe pCheckUniverse.                                        *
// **************************************************************************************************************
// * Cette classe prend en charge la publication des univers vers Messenger.                                    *
// **************************************************************************************************************

#include "stdafx.h"

#include "pPublishSettings.h"
#include "pCheckUniverse.h"

#include "zSoapException.h"

/////////////////////////////////////////////////////////////////////////////////
//Default constructor
pCheckUniverse::pCheckUniverse()
{
    m_Alias = _T("");
}

/////////////////////////////////////////////////////////////////////////////////
//Default destructor
pCheckUniverse::~pCheckUniverse()
{
}

/////////////////////////////////////////////////////////////////////////////////
//reset data (empty lists)
void pCheckUniverse::reset()
{
    m_universe.clear();
}

/////////////////////////////////////////////////////////////////////////////////
//add new procedure
void pCheckUniverse::addUniverse(puniverse universe)
{
    m_universe.insert(m_universe.end(), universe);
}

void pCheckUniverse::addAlias(const CString& alias)
{
    m_Alias = alias;
}

/////////////////////////////////////////////////////////////////////////////////
// Send data to urn:emessenger , method: pubCheckUniverse
//    out:returns true on success
bool pCheckUniverse::check()
{
    SOAPDebugger::SetFile(_T("c:\\psssoap_pubcheckuniverse.log"));

    bool retValue = true;

    try
    {
        TRACE(_T("pCheckUniverse.check()"));

        // defs
        std::string wdsl_urn = pPublishSettings::m_ModelService;

        // initialize objects
        std::string url = pPublishSettings::m_Url;
        SOAPProxy proxy(url.c_str());

        // send
        SOAPMethod checkUniverse(_T("pubCheckUniverse"), wdsl_urn.c_str(), _T("http://"));
        checkUniverse.AddParameter(_T("universenbr")).SetValue(int(m_universe.size()));

        SOAPArray<puniverse>      universea;
        list<puniverse>::iterator universei;

        for (universei = m_universe.begin(); universei != m_universe.end(); ++universei)
            universea.Add(*universei);

        SOAPParameter& p = checkUniverse.AddParameter(_T("universe"));
        p << universea;

        checkUniverse.AddParameter(_T("alias")).SetValue(m_Alias);

        if (int(proxy.Execute(checkUniverse).GetReturnValue()) < 0)
            retValue = false;
    }
    catch (SOAPException& ex)
    {
        TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
        retValue = false;
    }

    SOAPDebugger::Close();

    return retValue;
}
