/* 
 * EasySoap++ - A C++ library for SOAP (Simple Object Access Protocol)
 * Copyright (C) 2001 David Crowley; SciTegic, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * $Id: SOAPProxy.h,v 1.6 2002/05/20 16:56:11 jgorlick Exp $
 */


#if !defined(AFX_SOAPPROXY_H__D489F911_F39E_4C38_A5C0_95CD3D0A9459__INCLUDED_)
#define AFX_SOAPPROXY_H__D489F911_F39E_4C38_A5C0_95CD3D0A9459__INCLUDED_

#include <easysoap\SOAP.h>

#include <easysoap\SOAPMethod.h>
#include <easysoap\SOAPEnvelope.h>
#include <easysoap\SOAPResponse.h>
#include <easysoap\SOAPParse.h>
#include <easysoap\SOAPUrl.h>
#include <easysoap\XMLComposer.h>

BEGIN_EASYSOAP_NAMESPACE

class SOAPTransport;

/**
*
*/
class EASYSOAP_EXPORT SOAPProxy  
{
public:
	SOAPProxy() :
		m_transport(0),
		m_deltrans(false)
	{
	}

	SOAPProxy(const SOAPUrl& endpoint) :
		m_transport(0),
		m_deltrans(false)
	{
		SetEndpoint(endpoint);
	}

	SOAPProxy(const SOAPUrl& endpoint, const SOAPUrl& proxy) :
		m_transport(0),
		m_deltrans(false)
	{
		SetEndpoint(endpoint, proxy);
	}

	SOAPProxy(SOAPTransport *transport, bool deltrans = false) :
		m_transport(transport),
		m_deltrans(deltrans)
	{
	}

	SOAPProxy(SOAPTransport& transport) :
		m_transport(&transport),
		m_deltrans(false)
	{
	}

	virtual ~SOAPProxy()
	{
		if (m_deltrans)
			delete m_transport;
	}

	void SetEndpoint(const SOAPUrl& endpoint);

	void SetEndpoint(const SOAPUrl& endpoint, const SOAPUrl& proxy);

	void SetEndpoint(SOAPTransport *transport, bool deltrans = false)
	{
		if (m_deltrans)
			delete m_transport;
		m_transport = transport;
		m_deltrans = deltrans;
	}

	SOAPMethod& SetMethod(const char *name, const char *ns)
	{
		SOAPMethod& method = m_message.GetBody().GetMethod();
		method.SetName(name, ns);
		return method;
	}

	const SOAPResponse& Execute()
	{
		return Execute(m_message);
	}

	const SOAPResponse& Execute(const SOAPMethod& method);
	const SOAPResponse& Execute(const SOAPEnvelope& envelope);

	void SendRequest(const SOAPEnvelope& envelope);
	const SOAPResponse& GetResponse();

private:

	SOAPProxy(const SOAPProxy& proxy);
	SOAPProxy& operator=(const SOAPProxy& proxy);

	SOAPEnvelope		m_message;
	SOAPResponse		m_response;
	XMLComposer			m_packet;
	SOAPParser			m_parser;
	SOAPTransport		*m_transport;
	bool				m_deltrans;
};

END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPPROXY_H__D489F911_F39E_4C38_A5C0_95CD3D0A9459__INCLUDED_)

