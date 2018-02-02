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
// <nl>Created:		 03/2002
// <nl>Description:  XXXClass frame window support
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __PPUBLISHMODEL_HDR_
#define __PPUBLISHMODEL_HDR_

// Change the definition of AFX_EXT... to make it import
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_IMPORT
#define AFX_EXT_API AFX_API_IMPORT
#define AFX_EXT_DATA AFX_DATA_IMPORT

#include "pmodel.h"
#include "pproc.h"
#include "pdeliv.h"
#include "ppdattr.h"
#include "pinput.h"
#include "pdistrib.h"
#include "pdistribmap.h"

#ifdef _ZSOAPEXPORT
// Put the values back to make AFX_EXT_CLASS export again
#undef AFX_EXT_CLASS
#undef AFX_EXT_API
#undef AFX_EXT_DATA
#define AFX_EXT_CLASS AFX_CLASS_EXPORT
#define AFX_EXT_API AFX_API_EXPORT
#define AFX_EXT_DATA AFX_DATA_EXPORT
#endif

// JMR-MODIF - Le 15 septembre 2005 - Ajout de la décoration Unicode _T( ) pour les chaînes de caractères de cette classe.

//Define serializers / soap mapping

/////////////////////////////////////////////
// pproc soap mapping
BEGIN_EASYSOAP_NAMESPACE

template<>
class SOAPTypeTraits<pproc>
{
public:

	static void GetType( SOAPQName& qname )
	{
		qname.Set( _T( "pproc" ), _T( "urn:xml-soap-emessenger" ) );
	}

	// JMR-MODIF - Le 23 mai 2006 - Ajout du code pour la prise en charge du nouveau champ procidprocessus.
	static SOAPParameter& Serialize( SOAPParameter& param, const pproc& val )
	{
		param.AddParameter( _T( "procid" ) )			<< val.procid;
		param.AddParameter( _T( "wkgid" ) )				<< val.wkgid.c_str();
		param.AddParameter( _T( "proctype" ) )			<< val.proctype;
		param.AddParameter( _T( "doublesign" ) )		<< val.doublesign;
		param.AddParameter( _T( "procidprocessus" ) )	<< val.procidprocessus;

		return param;
	}

	// JMR-MODIF - Le 23 mai 2006 - Ajout du code pour la prise en charge du nouveau champ procidprocessus.
	static const SOAPParameter& Deserialize( const SOAPParameter& param, pproc& val )
	{
		SOAPString tmp;

		param.GetParameter( _T( "procid" ) )			>> val.procid;
		param.GetParameter( _T( "wkgid" ) )				>> tmp;
		val.wkgid = tmp.Str();
		param.GetParameter( _T( "proctype" ) )			>> val.proctype;
		param.GetParameter( _T( "doublesign" ) )		>> val.doublesign;
		param.GetParameter( _T( "procidprocessus" ) )	>> val.procidprocessus;

		return param;
	}
};

template<>
class SOAPTypeTraits< SOAPArray<pproc> > : public SOAPArrayTypeTraits
{
};

/////////////////////////////////////////////
// pdeliv soap mapping
template<>
class SOAPTypeTraits<pdeliv>
{
public:

	static void GetType( SOAPQName& qname )
	{
		qname.Set( _T( "pdeliv" ), _T( "urn:xml-soap-emessenger" ) );
	}

	static SOAPParameter& Serialize( SOAPParameter& param, const pdeliv& val )
	{
		param.AddParameter( _T( "delivid" ) )			<< val.delivid;
		param.AddParameter( _T( "procidsrc" ) )			<< val.procidsrc;
		param.AddParameter( _T( "procidtrg" ) )			<< val.procidtrg;
		param.AddParameter( _T( "delivname" ) )			<< val.delivname.c_str();
		param.AddParameter( _T( "lateral" ) )			<< val.lateral;
		param.AddParameter( _T( "lateraldirection" ) )	<< val.lateraldirection;
		param.AddParameter( _T( "doublesign" ) )		<< val.doublesign;

		return param;
	}

	static const SOAPParameter& Deserialize( const SOAPParameter& param, pdeliv& val )
	{
		SOAPString tmp;

		param.GetParameter( _T( "delivid" ) )			>> val.delivid;
		param.GetParameter( _T( "procidsrc" ) )			>> val.procidsrc;
		param.GetParameter( _T( "procidtrg" ) )			>> val.procidtrg;
		param.GetParameter( _T( "delivname" ) )			>> tmp;
		val.delivname = tmp.Str();
		param.GetParameter( _T( "lateral" ) )			>> val.lateral;
		param.GetParameter( _T( "lateraldirection" ) )	>> val.lateraldirection;
		param.GetParameter( _T( "doublesign" ) )		>> val.doublesign;

		return param;
	}
};

template<>
class SOAPTypeTraits< SOAPArray<pdeliv> > : public SOAPArrayTypeTraits
{
};

/////////////////////////////////////////////
// pmodel soap mapping
template<>
class SOAPTypeTraits<pmodel>
{
public:

	static void GetType( SOAPQName& qname )
	{
		qname.Set( _T( "pmodel" ), _T( "urn:xml-soap-emessenger" ) );
	}

	static SOAPParameter& Serialize( SOAPParameter& param, const pmodel& val )
	{
		param.AddParameter( _T( "modelname" ) )	<< val.modelname.c_str();
		param.AddParameter( _T( "modelref" ) )	<< val.modelref.c_str();

		// JMR-MODIF - Le 21 juin 2006 - Ajout de la sérialisation des dates de validité.
		param.AddParameter( _T( "startdate" ) )	<< val.startdate.c_str();
		param.AddParameter( _T( "enddate" ) )	<< val.enddate.c_str();

		return param;
	}

	static const SOAPParameter& Deserialize( const SOAPParameter& param, pmodel& val )
	{
		SOAPString tmp;

		param.GetParameter( _T( "modelname" ) )	>>tmp;
		val.modelname = tmp.Str();
		param.GetParameter( _T( "modelref" ) )	>>tmp;
		val.modelref = tmp.Str();

		// JMR-MODIF - Le 21 juin 2006 - Ajout de la désérialisation des dates de validité.
		param.GetParameter( _T( "startdate" ) )	>>tmp;
		val.startdate = tmp.Str();
		param.GetParameter( _T( "enddate" ) )	>>tmp;
		val.enddate = tmp.Str();

		return param;
	}
};

template<>
class SOAPTypeTraits< SOAPArray<pmodel> > : public SOAPArrayTypeTraits
{
};

/////////////////////////////////////////////
// ppdattr soap mapping
template<>
class SOAPTypeTraits<ppdattr>
{
public:

	static void GetType( SOAPQName& qname )
	{
		qname.Set( _T( "ppdattr" ), _T( "urn:xml-soap-emessenger" ) );
	}

	static SOAPParameter& Serialize( SOAPParameter& param, const ppdattr& val )
	{
		param.AddParameter( _T( "pdattribid" ) )	<< val.pdattribid;
		param.AddParameter( _T( "prow" ) )			<< val.prow;
		param.AddParameter( _T( "attribdefid" ) )	<< val.attribdefid;
		param.AddParameter( _T( "mvalue" ) )		<< val.mvalue.c_str();

		return param;
	}

	static const SOAPParameter& Deserialize( const SOAPParameter& param, ppdattr& val )
	{
		SOAPString tmp;

		param.GetParameter( _T( "pdattribid" ) )	>> val.pdattribid;
		param.GetParameter( _T( "prow" ) )			>> val.prow;
		param.GetParameter( _T( "attribdefid" ) )	>> val.attribdefid;
		param.GetParameter( _T( "mvalue" ) )		>>tmp;
		val.mvalue = tmp.Str();

		return param;
	}
};

template<>
class SOAPTypeTraits< SOAPArray<ppdattr> > : public SOAPArrayTypeTraits
{
};

/////////////////////////////////////////////
// pdistrib soap mapping
template<>
class SOAPTypeTraits<pdistrib>
{
public:

	static void GetType( SOAPQName& qname )
	{
		qname.Set( _T( "pdistrib" ), _T( "urn:xml-soap-emessenger" ) );
	}

	static SOAPParameter& Serialize( SOAPParameter& param, const pdistrib& val )
	{
		param.AddParameter( _T( "wkgid" ) )			<< val.wkgid.c_str();
		param.AddParameter( _T( "attribdefid" ) )	<< val.attribdefid;
		param.AddParameter( _T( "mop" ) )			<< val.mop;
		param.AddParameter( _T( "mdata" ) )			<< val.mdata.c_str();

		return param;
	}

	static const SOAPParameter& Deserialize( const SOAPParameter& param, pdistrib& val )
	{
		SOAPString tmp;

		param.GetParameter( _T( "wkgid" ) )			>> tmp;
		val.wkgid = tmp.Str();
		param.GetParameter( _T( "attribdefid" ) )	>> val.attribdefid;
		param.GetParameter( _T( "mop" ) )			>> val.mop;
		param.GetParameter( _T( "mdata" ) )			>> tmp;
		val.mdata = tmp.Str();

		return param;
	}
};

template<>
class SOAPTypeTraits< SOAPArray<pdistrib> > : public SOAPArrayTypeTraits
{
};

/////////////////////////////////////////////
// pdistribmap soap mapping
template<>
class SOAPTypeTraits<pdistribmap>
{
public:

	static void GetType( SOAPQName& qname )
	{
		qname.Set( _T( "pdistribmap" ), _T( "urn:xml-soap-emessenger" ) );
	}

	static SOAPParameter& Serialize( SOAPParameter& param, const pdistribmap& val )
	{	
		param.AddParameter( _T( "pdattribid" ) )	<< val.pdattribid;
		param.AddParameter( _T( "attribdefid" ) )	<< val.attribdefid;
		param.AddParameter( _T( "mdata" ) )			<< val.mdata.c_str();
		param.AddParameter( _T( "mlop" ) )			<< val.mlop;

		return param;
	}

	static const SOAPParameter& Deserialize( const SOAPParameter& param, pdistribmap& val )
	{
		SOAPString tmp;

		param.GetParameter( _T( "pdattribid" ) )	>> val.pdattribid;
		param.GetParameter( _T( "attribdefid" ) )	>> val.attribdefid;
		param.GetParameter( _T( "mdata" ) )			>> tmp;
		val.mdata = tmp.Str();
		param.GetParameter( _T( "mlop" ) )			>> val.mlop;

		return param;
	}
};

template<>
class SOAPTypeTraits< SOAPArray<pdistribmap> > : public SOAPArrayTypeTraits
{
};

/////////////////////////////////////////////
// pinput soap mapping
template<>
class SOAPTypeTraits<pinput>
{
public:

	static void GetType( SOAPQName& qname )
	{
		qname.Set( _T( "pinput" ), _T( "urn:xml-soap-emessenger" ) );
	}

	static SOAPParameter& Serialize( SOAPParameter& param, const pinput& val )
	{	
		//param.AddParameter( _T( "modelid" ) )		<< val.modelid;
		param.AddParameter( _T( "pdattribid" ) )	<< val.pdattribid;
		param.AddParameter( _T( "attribdefid" ) )	<< val.attribdefid;
		param.AddParameter( _T( "mdefval" ) )		<< val.mdefval.c_str();
		param.AddParameter( _T( "mflag" ) )			<< val.mflag;
		param.AddParameter( _T( "constraintid" ) )	<< val.constraintid;

		return param;
	}

	static const SOAPParameter& Deserialize( const SOAPParameter& param, pinput& val )
	{
		SOAPString tmp;

		//param.GetParameter( _T( "modelid" ) )		>> val.modelid;
		param.GetParameter( _T( "pdattribid" ) )	>> val.pdattribid;
		param.GetParameter( _T( "attribdefid" ) )	>> val.attribdefid;
		param.GetParameter( _T( "mdefval" ) )		>> tmp;
		val.mdefval = tmp.Str();
		param.GetParameter( _T( "mflag" ) )			>> val.mflag;
		param.GetParameter( _T( "constraintid" ) )	>> val.constraintid;

		return param;
	}
};

template<>
class SOAPTypeTraits< SOAPArray<pinput> > : public SOAPArrayTypeTraits
{
};

class AFX_EXT_CLASS pPublishModel
{
public:

	pPublishModel();
	~pPublishModel();

	void reset();
	
	void setModel		( pmodel model );
	void addProc		( pproc proc );
	void addDeliv		( pdeliv deliv );
	void addAttr		( ppdattr pdattr );
	void addDistrib		( pdistrib distrib );
	void addDistribmap	( pdistribmap distribmap );
	void addInput		( pinput inputs );

	// JMR-MODIF - Le 21 juin 2006 - Ajout de la fonction addAlias.
	void addAlias( CString Alias );

	bool send();

	int getModelVersion(string model);

private:

	// JMR-MODIF - Le 21 juin 2006 - Ajout de la variable m_Alias.
	CString				m_Alias;

	pmodel				m_model;
	list<pproc>			m_procs;
	list<pdeliv>		m_delivs;
	list<ppdattr>		m_pdattrs;
	list<pdistrib>		m_distribs;
	list<pdistribmap>	m_distribmaps;
	list<pinput>		m_inputs;
};

END_EASYSOAP_NAMESPACE

#endif