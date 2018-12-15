// **************************************************************************************************************
// *                                       Classe pCheckUniverse                                                *
// **************************************************************************************************************
// * JMR-MODIF - Le 21 juin 2006 - Création de la classe pCheckUniverse.                                        *
// **************************************************************************************************************
// * Cette classe prend en charge la publication des univers vers Messenger.                                    *
// **************************************************************************************************************

#ifndef __PCHECKUNIVERSE_HDR_
#define __PCHECKUNIVERSE_HDR_

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zConversion\String16.h"

#include "puniverse.h"

#ifdef _ZSOAPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

string convertTo( String16 inStr );

/////////////////////////////////////////////
//Define serializers / soap mapping

// pproc soap mapping
BEGIN_EASYSOAP_NAMESPACE

template<>
class SOAPTypeTraits<puniverse>
{
public:

    static void GetType( SOAPQName& qname )
    {
        qname.Set( _T( "puniverse" ), _T( "urn:xml-soap-emessenger" ) );
    }

    static SOAPParameter& Serialize( SOAPParameter& param, const puniverse& val )
    {
        param.AddParameter( _T( "guidSystem" ) )        << val.guidSystem.c_str();
        param.AddParameter( _T( "guidPrestation" ) )    << val.guidPrestation.c_str();
        param.AddParameter( _T( "guidWorkgroup" ) )        << val.guidWorkgroup.c_str();

        return param;
    }

    static const SOAPParameter& Deserialize( const SOAPParameter& param, puniverse& val )
    {
        SOAPString tmp;

        param.GetParameter( _T( "guidSystem" ) )        >> tmp;
        val.guidSystem        = tmp.Str();

        param.GetParameter( _T( "guidPrestation" ) )    >> tmp;
        val.guidPrestation    = tmp.Str();

        param.GetParameter( _T( "guidWorkgroup" ) )        >> tmp;
        val.guidWorkgroup    = tmp.Str();

        return param;
    }
};

template<>
class SOAPTypeTraits< SOAPArray<puniverse> > : public SOAPArrayTypeTraits
{
};

class AFX_EXT_CLASS pCheckUniverse
{
public:

    pCheckUniverse();
    ~pCheckUniverse();

    void reset();
    void addUniverse( puniverse universe );
    void addAlias( CString Alias );

    bool check();

private:

    CString                m_Alias;

    list<puniverse>        m_universe;
};

END_EASYSOAP_NAMESPACE

#endif