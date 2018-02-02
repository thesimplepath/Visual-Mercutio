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
#include "pPublishModel.h"

#include "zSoapException.h"

// JMR-MODIF - Le 14 septembre 2005 - Ajout des décorations Unicode _T(), nettoyage du code inutile.(En cimmentaires)

/////////////////////////////////////////////////////////////////////////////////
// Default constructor
pPublishModel::pPublishModel()
{
	// JMR-MODIF - Le 21 juin 2006 - Ajout de l'initialisation de la variable m_Alias.
	m_Alias = _T( "" );
}

/////////////////////////////////////////////////////////////////////////////////
// Default destructor
pPublishModel::~pPublishModel()
{
}

/////////////////////////////////////////////////////////////////////////////////
// reset data (empty lists)
void pPublishModel::reset()
{
	m_procs.clear();
	m_delivs.clear();
	m_pdattrs.clear();
	m_distribs.clear();
	m_distribmaps.clear();
	m_inputs.clear();
}

/////////////////////////////////////////////////////////////////////////////////
// set model information
void pPublishModel::setModel( pmodel model )
{
	m_model = model;
}

/////////////////////////////////////////////////////////////////////////////////
// add new procedure
void pPublishModel::addProc( pproc proc )
{
	m_procs.insert( m_procs.end(), proc );
}

/////////////////////////////////////////////////////////////////////////////////
// add new deliverable
void pPublishModel::addDeliv( pdeliv deliv )
{
	m_delivs.insert( m_delivs.end(), deliv );
}

/////////////////////////////////////////////////////////////////////////////////
// add new attribute
void pPublishModel::addAttr( ppdattr pdattr )
{
	m_pdattrs.insert( m_pdattrs.end(), pdattr );
}

/////////////////////////////////////////////////////////////////////////////////
// add new distrib
void pPublishModel::addDistrib( pdistrib distrib )
{
	m_distribs.insert( m_distribs.end(), distrib );
}

/////////////////////////////////////////////////////////////////////////////////
// add new distribmap
void pPublishModel::addDistribmap( pdistribmap distribmap )
{
	m_distribmaps.insert( m_distribmaps.end(), distribmap );
}

/////////////////////////////////////////////////////////////////////////////////
// add new input
void pPublishModel::addInput( pinput inputs )
{
	m_inputs.insert( m_inputs.end(), inputs );
}

// JMR-MODIF - Le 21 juin 2006 - Cette fonction permet d'ajouter l'alias, nécessaire pour la publication.
void pPublishModel::addAlias( CString Alias )
{
	m_Alias = Alias;
}

/////////////////////////////////////////////////////////////////////////////////
// send data to urn:emessenger , method: sndModel
// out:returns true on success
bool pPublishModel::send()
{
	SOAPDebugger::SetFile( _T( "c:\\psssoap.log" ) );

	TRACE( _T( "pPublishModel::send()\n" ) );
	TRACE( _T( "pPublishModel::send().init\n" ) );

	// defs
	string wdsl_urn = pPublishSettings::modelservice;

	// initialize objects
	string url = pPublishSettings::url;
	SOAPProxy proxy( url.c_str() );

	int modelid = -1;

	try
	{
		TRACE( _T( "pPublishModel::send().pubInit\n" ) );

		// pubInit
		//RS-MODIF 04.08.05 erreur publication messenger sous XP
		//SOAPMethod pubInit("pubInit",wdsl_urn.c_str());
		SOAPMethod pubInit( _T( "pubInit" ), wdsl_urn.c_str(), _T( "http://" ) );

		// JMR-MODIF - Le 21 juin 2006 - Ajout du paramètre Alias dans l'envoi.
		pubInit.AddParameter( _T( "alias" ) ).SetValue( m_Alias );

		if ( (int)proxy.Execute( pubInit ).GetReturnValue() < 0 )
		{
			throw ZBSoapException( IDS_PUBINITSERVERFAIL, NULL, __FILE__, __LINE__ );
		}
	}
	catch ( SOAPException& ex )
	{
		TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
		// JMR-MODIF - Le 16 mai 2006 - Ne pas lancer une nouvelle exception après capture de la précédente,
		// car cette nouvelle exception n'est pas traitée, et interrompt le programme.
//		throw ZBSoapException( IDS_SOAPEXCEPTION, ex.What().Str(), __FILE__, __LINE__ );
		return false;
	}

	try
	{
		TRACE( _T( "pPublishModel::send().pubModel\n" ) );

		// pubModel
		SOAPMethod pubModel( _T( "pubModel" ), wdsl_urn.c_str(), _T( "http://" ) );

		SOAPParameter& mdl = pubModel.AddParameter();
		mdl << m_model;

		// JMR-MODIF - Le 21 juin 2006 - Ajout du paramètre Alias dans l'envoi.
		pubModel.AddParameter( _T( "alias" ) ).SetValue( m_Alias );

		modelid = proxy.Execute( pubModel ).GetReturnValue();

		if ( modelid < 0 )
		{
			throw ZBSoapException( IDS_PUBMODELSERVERFAIL, m_model.modelname.c_str(), __FILE__, __LINE__ );
		}
	}
	catch ( SOAPException& ex )
	{
		TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
		// JMR-MODIF - Le 16 mai 2006 - Ne pas lancer une nouvelle exception après capture de la précédente,
		// car cette nouvelle exception n'est pas traitée, et interrompt le programme.
//		throw ZBSoapException( IDS_SOAPEXCEPTION, ex.What().Str(), __FILE__, __LINE__ );
		return false;
	}

	try
	{
		TRACE( _T( "pPublishModel::send().pubProc\n" ) );

		// proc
		if ( m_procs.size() > 0 )
		{
			SOAPMethod pubProc( _T( "pubProc" ), wdsl_urn.c_str(), _T( "http://" ) );
			pubProc.AddParameter( _T( "modelid" ) ).SetValue( (int)modelid );
			pubProc.AddParameter( _T( "procnbr" ) ).SetValue( (int)m_procs.size() );

			SOAPArray<pproc> procs;
			list<pproc>::iterator proci;

			for ( proci =  m_procs.begin(); proci != m_procs.end(); ++proci )
			{
				procs.Add( *proci );
			}

			SOAPParameter& p = pubProc.AddParameter( _T( "proc" ) );
			p << procs;

			// JMR-MODIF - Le 21 juin 2006 - Ajout du paramètre Alias dans l'envoi.
			pubProc.AddParameter( _T( "alias" ) ).SetValue( m_Alias );

			if ( (int)proxy.Execute( pubProc ).GetReturnValue() < 0 )
			{
				throw ZBSoapException( IDS_PUBPROCSERVERFAIL, m_model.modelname.c_str(), __FILE__, __LINE__ );
			}
		}
	}
	catch ( SOAPException& ex )
	{
		TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
		// JMR-MODIF - Le 16 mai 2006 - Ne pas lancer une nouvelle exception après capture de la précédente,
		// car cette nouvelle exception n'est pas traitée, et interrompt le programme.
//		throw ZBSoapException( IDS_SOAPEXCEPTION, ex.What().Str(), __FILE__, __LINE__ );
		return false;
	}

	try
	{
		TRACE( _T( "pPublishModel::send().pubDeliv\n" ) );

		// pubDeliv
		if ( m_delivs.size() > 0 )
		{
			SOAPMethod pubDeliv( _T( "pubDeliv" ), wdsl_urn.c_str(), _T( "http://" ) );
			pubDeliv.AddParameter( _T( "modelid" ) ).SetValue( (int)modelid );
			pubDeliv.AddParameter( _T( "delivnbr" ) ).SetValue( (int)m_delivs.size() );
			
			SOAPArray<pdeliv> delivs;
			list<pdeliv>::iterator delivi;

			for ( delivi =  m_delivs.begin(); delivi != m_delivs.end(); ++delivi )
			{
				delivs.Add( *delivi );
			}

			SOAPParameter& q = pubDeliv.AddParameter( _T( "deliv" ) );
			q << delivs;

			// JMR-MODIF - Le 21 juin 2006 - Ajout du paramètre Alias dans l'envoi.
			pubDeliv.AddParameter( _T( "alias" ) ).SetValue( m_Alias );

			if ( (int)proxy.Execute( pubDeliv ).GetReturnValue() < 0 )
			{
				throw ZBSoapException( IDS_PUBDELIVSERVERFAIL, m_model.modelname.c_str(), __FILE__, __LINE__ );
			}
		}
	}
	catch ( SOAPException& ex )
	{
		TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
		// JMR-MODIF - Le 16 mai 2006 - Ne pas lancer une nouvelle exception après capture de la précédente,
		// car cette nouvelle exception n'est pas traitée, et interrompt le programme.
//		throw ZBSoapException( IDS_SOAPEXCEPTION, ex.What().Str(), __FILE__, __LINE__ );
		return false;
	}

	try
	{
		TRACE( _T( "pPublishModel::send().pubPdattr\n" ) );

		// pubPdattr
		if ( m_pdattrs.size() > 0 )
		{
			SOAPMethod pubPdattr( _T( "pubPdattr" ), wdsl_urn.c_str(), _T( "http://" ) );
			pubPdattr.AddParameter( _T( "modelid" ) ).SetValue( (int)modelid );

			SOAPArray<ppdattr> pdattrs;
			list<ppdattr>::iterator pdattri;

			//RS-MODIF 17.11.2005 correction du dépassement mémoire
			// création de boucles de max 10'000 entrées à publier à la fois

			pdattri				= m_pdattrs.begin();
			SOAPParameter& size	= pubPdattr.AddParameter( "pdattrnbr" );
			SOAPParameter& r	= pubPdattr.AddParameter( "pdattr" );

			// JMR-MODIF - Le 17 octobre 2006 - Ajout du paramètre Alias dans l'envoi.
			pubPdattr.AddParameter( _T( "alias" ) ).SetValue( m_Alias );

			do
			{
				pdattrs.Empty();

				int x = 0;

				do
				{
					pdattrs.Add(*pdattri);
					++pdattri;
					x++;
				}
				while ( ( pdattri != m_pdattrs.end() ) && ( x < 10000 ) );

				size.SetValue( x );

				// RS-MODIF 17.11.2005 ancienne boucle
				/*for ( pdattri =  m_pdattrs.begin(); pdattri != m_pdattrs.end(); ++pdattri )
				{
					pdattrs.Add( *pdattri );
				}*/

				r.SetNull();
				r << pdattrs;

				// JMR-MODIF - Le 17 octobre 2006 - L'alias doit être ajouté au paquet avant la boucle do.
				// JMR-MODIF - Le 21 juin 2006 - Ajout du paramètre Alias dans l'envoi.
//				pubPdattr.AddParameter( _T( "alias" ) ).SetValue( m_Alias );

				if ( (int)proxy.Execute( pubPdattr ).GetReturnValue() < 0 )
				{
					throw ZBSoapException( IDS_PUBPDATTRSERVERFAIL, m_model.modelname.c_str(), __FILE__, __LINE__ );
				}
			}
			while ( pdattri != m_pdattrs.end() );
		}
	}
	catch ( SOAPException& ex )
	{
		TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
		// JMR-MODIF - Le 16 mai 2006 - Ne pas lancer une nouvelle exception après capture de la précédente,
		// car cette nouvelle exception n'est pas traitée, et interrompt le programme.
//		throw ZBSoapException( IDS_SOAPEXCEPTION, ex.What().Str(), __FILE__, __LINE__ );
		return false;
	}

	try
	{
		TRACE( _T( "pPublishModel::send().pubDistrib\n" ) );

		// pubDistrib
		if ( m_distribs.size() > 0 )
		{
			SOAPMethod pubDistrib( _T( "pubDistrib" ), wdsl_urn.c_str(), _T( "http://" ) );
			pubDistrib.AddParameter( _T( "modelid" ) ).SetValue( (int)modelid );
			pubDistrib.AddParameter( _T( "distribnbr" ) ).SetValue( (int)m_distribs.size() );
			
			SOAPArray<pdistrib> distribs;
			list<pdistrib>::iterator distribi;

			for ( distribi =  m_distribs.begin(); distribi != m_distribs.end(); ++distribi )
			{
				distribs.Add( *distribi );
			}

			SOAPParameter& s = pubDistrib.AddParameter( _T( "distrib" ) );
			s << distribs;

			// JMR-MODIF - Le 21 juin 2006 - Ajout du paramètre Alias dans l'envoi.
			pubDistrib.AddParameter( _T( "alias" ) ).SetValue( m_Alias );

			if ( (int)proxy.Execute( pubDistrib ).GetReturnValue() < 0 )
			{
				throw ZBSoapException( IDS_PUBDISTRIBSERVERFAIL, m_model.modelname.c_str(), __FILE__, __LINE__ );
			}
		}
	}
	catch ( SOAPException& ex )
	{
		TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
		// JMR-MODIF - Le 16 mai 2006 - Ne pas lancer une nouvelle exception après capture de la précédente,
		// car cette nouvelle exception n'est pas traitée, et interrompt le programme.
//		throw ZBSoapException( IDS_SOAPEXCEPTION, ex.What().Str(), __FILE__, __LINE__ );
		return false;
	}

	try
	{
		TRACE( _T( "pPublishModel::send().pubDistribmap\n" ) );

		// pubDistribmap
		if ( m_distribmaps.size() > 0 )
		{
			SOAPMethod pubDistribmap( _T( "pubDistribmap" ), wdsl_urn.c_str(), _T( "http://" ) );
			pubDistribmap.AddParameter( _T( "modelid" ) ).SetValue( (int)modelid );
			pubDistribmap.AddParameter( _T( "distribmapnbr" ) ).SetValue( (int)m_distribmaps.size() );

			SOAPArray<pdistribmap> distribmaps;
			list<pdistribmap>::iterator distribmapi;

			for ( distribmapi =  m_distribmaps.begin(); distribmapi != m_distribmaps.end(); ++distribmapi )
			{
				distribmaps.Add( *distribmapi );
			}

			SOAPParameter& u = pubDistribmap.AddParameter( _T( "distribmap" ) );
			u << distribmaps;

			// JMR-MODIF - Le 21 juin 2006 - Ajout du paramètre Alias dans l'envoi.
			pubDistribmap.AddParameter( _T( "alias" ) ).SetValue( m_Alias );

			if ( (int)proxy.Execute( pubDistribmap ).GetReturnValue() < 0 )
			{
				throw ZBSoapException( IDS_PUBDISTRIBMAPSERVERFAIL, m_model.modelname.c_str(), __FILE__, __LINE__ );
			}
		}
	}
	catch ( SOAPException& ex )
	{
		TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
		// JMR-MODIF - Le 16 mai 2006 - Ne pas lancer une nouvelle exception après capture de la précédente,
		// car cette nouvelle exception n'est pas traitée, et interrompt le programme.
//		throw ZBSoapException( IDS_SOAPEXCEPTION, ex.What().Str(), __FILE__, __LINE__ );
		return false;
	}

	try
	{
		TRACE( _T( "pPublishModel::send().pubInput\n" ) );

		// pubInput
		if ( m_inputs.size() > 0 )
		{
			SOAPMethod pubInput( _T( "pubInput" ), wdsl_urn.c_str(), _T( "http://" ) );
			pubInput.AddParameter( _T( "modelid" ) ).SetValue( (int)modelid );
			pubInput.AddParameter( _T( "inputnbr" ) ).SetValue( (int)m_inputs.size() );
			
			SOAPArray<pinput> inputs;
			list<pinput>::iterator inputi;

			for ( inputi =  m_inputs.begin(); inputi != m_inputs.end(); ++inputi )
			{
				inputs.Add( *inputi );
			}

			SOAPParameter& t = pubInput.AddParameter( _T( "input" ) );
			t << inputs;

			// JMR-MODIF - Le 21 juin 2006 - Ajout du paramètre Alias dans l'envoi.
			pubInput.AddParameter( _T( "alias" ) ).SetValue( m_Alias );

			if ( (int)proxy.Execute( pubInput ).GetReturnValue() < 0 )
			{
				throw ZBSoapException( IDS_PUBINPUTSERVERFAIL, m_model.modelname.c_str(), __FILE__, __LINE__ );
			}
		}
	}
	catch ( SOAPException& ex )
	{
		TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
		// JMR-MODIF - Le 16 mai 2006 - Ne pas lancer une nouvelle exception après capture de la précédente,
		// car cette nouvelle exception n'est pas traitée, et interrompt le programme.
//		throw ZBSoapException( IDS_SOAPEXCEPTION, ex.What().Str(), __FILE__, __LINE__ );
		return false;
	}

	try
	{
		TRACE( _T( "pPublishModel::send().pubDone\n" ) );

		// pubDone
		SOAPMethod pubDone( _T( "pubDone" ), wdsl_urn.c_str(), _T( "http://" ) );

		if ( (int)proxy.Execute( pubDone ).GetReturnValue() < 0 )
		{
			throw ZBSoapException( IDS_PUBDONESERVERFAIL, m_model.modelname.c_str(), __FILE__, __LINE__ );
		}
	}
	catch ( SOAPException& ex )
	{
		TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
		// JMR-MODIF - Le 16 mai 2006 - Ne pas lancer une nouvelle exception après capture de la précédente,
		// car cette nouvelle exception n'est pas traitée, et interrompt le programme.
//		throw ZBSoapException( IDS_SOAPEXCEPTION, ex.What().Str(), __FILE__, __LINE__ );
		return false;
	}

	TRACE( _T( "pPublishModel::send().complete\n" ) );
	return true;
}

int pPublishModel::getModelVersion( string modelref )
{
	SOAPDebugger::SetFile( _T( "c:\\psssoap.log" ) );

	try
	{
		TRACE( _T( "pPublishModel::getModelVersion %s\n" ), modelref.c_str() );

		// defs
		string wdsl_urn = pPublishSettings::modelservice;

		// initialize objects
		string url = pPublishSettings::url;
		SOAPProxy proxy( url.c_str() );

		// pubInit
		SOAPMethod pubGetModelVersion( _T( "pubGetModelVersion" ), wdsl_urn.c_str(), _T( "http://" ) );
		pubGetModelVersion.AddParameter( _T( "modelref" ) ).SetValue( modelref.c_str() );

		// JMR-MODIF - Le 21 juin 2006 - Ajout du paramètre Alias dans l'envoi.
		pubGetModelVersion.AddParameter( _T( "alias" ) ).SetValue( m_Alias );

		return proxy.Execute( pubGetModelVersion ).GetReturnValue();
	}
	catch ( SOAPException& ex )
	{
		TRACE( _T( "Caught SOAP exception:%s\n" ), ex.What().Str() );
		// JMR-MODIF - Le 16 mai 2006 - Ne pas lancer une nouvelle exception après capture de la précédente,
		// car cette nouvelle exception n'est pas traitée, et interrompt le programme.
//		throw ZBSoapException( IDS_SOAPEXCEPTION, ex.What().Str(), __FILE__, __LINE__ );
		return -1;
	}

	return -1;
}
