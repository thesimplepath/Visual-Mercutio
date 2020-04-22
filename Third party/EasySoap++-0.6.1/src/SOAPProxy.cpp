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
 * $Id: SOAPProxy.cpp,v 1.15 2002/05/02 17:51:58 dcrowley Exp $
 */

#ifdef _MSC_VER
#pragma warning (disable: 4786)
#endif // _MSC_VER

#include <easysoap/SOAPProxy.h>

#ifdef EASYSOAP_USE_WININET
#include <easysoap/SOAPWinInetTransport.h>
#else
#include <easysoap/SOAPonHTTP.h>
#endif

USING_EASYSOAP_NAMESPACE

const SOAPResponse&
SOAPProxy::Execute(const SOAPMethod& method)
{
	if (!m_transport)
		throw SOAPException("No transport!");

	m_message.GetBody().SetMethod(method);
	return Execute(m_message);
}

const SOAPResponse&
SOAPProxy::Execute(const SOAPEnvelope& envelope)
{
	SendRequest(envelope);
	return GetResponse();
}

void
SOAPProxy::SendRequest(const SOAPEnvelope& envelope)
{
	if (!m_transport)
		throw SOAPException("No transport!");

	envelope.WriteSOAPPacket(m_packet);
	m_transport->Write(envelope.GetBody().GetMethod(), m_packet.GetBytes(), m_packet.GetLength());
}

const SOAPResponse&
SOAPProxy::GetResponse()
{
	if (!m_transport)
		throw SOAPException("No transport!");

	m_parser.Parse(m_response, *m_transport);

	if (m_response.IsFault())
		throw SOAPFaultException(m_response.GetBody().GetFault());

	return m_response;
}

void
SOAPProxy::SetEndpoint(const SOAPUrl& endpoint)
{
	// Assume it's an HTTP protocol.
	// TODO: What we need here is a factory.
#ifdef EASYSOAP_USE_WININET
	SOAPWinInetTransport *transport = new SOAPWinInetTransport();
#else
	SOAPonHTTP *transport = new SOAPonHTTP();
#endif
	SetEndpoint(transport, true);
	transport->ConnectTo(endpoint);
}

void
SOAPProxy::SetEndpoint(const SOAPUrl& endpoint, const SOAPUrl& proxy)
{
	// Assume it's an HTTP protocol.
	// TODO: What we need here is a factory.
#ifdef EASYSOAP_USE_WININET
	SOAPWinInetTransport *transport = new SOAPWinInetTransport();
#else
	SOAPonHTTP *transport = new SOAPonHTTP();
#endif
	SetEndpoint(transport, true);
	transport->ConnectTo(endpoint, proxy);
}
