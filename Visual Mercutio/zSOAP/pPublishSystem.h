/////////////////////////////////////////////////////////////////////////////
//@doc XXXClass
//@module XXXClass.h | Interface of the <c XXXClass> class.
//
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA,
// All rights reserved.
//
// This source code is only intended as a supplement to
// the ProcessSoft Class Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// ProcessSoft products.
//
// Author:       Gaya
// <nl>Created:         03/2002
// <nl>Description:  XXXClass frame window support
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __PPUBLISHSYSTEM_HDR_
#define __PPUBLISHSYSTEM_HDR_

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "zConversion\String16.h"

#include "psystem.h"

#ifdef _ZSOAPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 30 mars 2006 - Ajout des décorations Unicode _T( ), nettoyage du code inutile. (En commentaires)

string convertTo( String16 inStr );

/////////////////////////////////////////////
//Define serializers / soap mapping

// pproc soap mapping
BEGIN_EASYSOAP_NAMESPACE

template<>
class SOAPTypeTraits<psystem>
{
public:

    static void GetType( SOAPQName& qname )
    {
        qname.Set( _T( "psystem" ), _T( "urn:xml-soap-emessenger" ) );
    }

    static SOAPParameter& Serialize( SOAPParameter& param, const psystem& val )
    {
        param.AddParameter( _T( "systemid" ) )        << val.systemid.c_str();
        param.AddParameter( _T( "systemparent" ) )    << val.systemparent.c_str();
        param.AddParameter( _T( "systemtitle" ) )    << val.systemtitle.c_str();
        param.AddParameter( _T( "command" ) )        << val.command.c_str();
        param.AddParameter( _T( "parameters" ) )    << val.parameters.c_str();
        param.AddParameter( _T( "directory" ) )        << val.directory.c_str();
        param.AddParameter( _T( "priority" ) )        << val.priority;
        param.AddParameter( _T( "windowst" ) )        << val.windowst;

        return param;
    }

    static const SOAPParameter& Deserialize( const SOAPParameter& param, psystem& val )
    {
        SOAPString tmp;

        param.GetParameter( _T( "systemid" ) )        >> tmp;
        val.systemid        = tmp.Str();
        param.GetParameter( _T( "systemparent" ) )    >> tmp;
        val.systemparent    = tmp.Str();
        param.GetParameter( _T( "systemtitle" ) )    >> tmp;
        val.systemtitle        = tmp.Str();
        param.GetParameter( _T( "command" ) )        >> tmp;
        val.command            = tmp.Str();
        param.GetParameter( _T( "parameters" ) )    >> tmp;
        val.parameters        = tmp.Str();
        param.GetParameter( _T( "directory" ) )        >> tmp;
        val.directory        = tmp.Str();
        param.GetParameter( _T( "priority" ) )        >> val.priority;
        param.GetParameter( _T( "windowst" ) )        >> val.windowst;

        return param;
    }
};

template<>
class SOAPTypeTraits< SOAPArray<psystem> > : public SOAPArrayTypeTraits
{
};

class AFX_EXT_CLASS pPublishSystem
{
public:

    pPublishSystem();
    ~pPublishSystem();

    void reset();
    void addSystem( psystem syst );

    // JMR-MODIF - Le 21 juin 2006 - Ajout de la fonction addAlias.
    void addAlias( CString Alias );

    bool send();

private:

    // JMR-MODIF - Le 21 juin 2006 - Ajout de la variable m_Alias.
    CString            m_Alias;

    list<psystem>    m_systems;
};

END_EASYSOAP_NAMESPACE

#endif