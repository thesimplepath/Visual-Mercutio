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
 * $Id: SOAPEnvelope.cpp,v 1.16 2001/12/20 22:38:19 dcrowley Exp $
 */


#ifdef _MSC_VER
#pragma warning (disable: 4786)
#endif // _MSC_VER

#include <easysoap/SOAP.h>
#include <easysoap/SOAPEnvelope.h>
#include <easysoap/SOAPNamespaces.h>
#include <easysoap/XMLComposer.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

USING_EASYSOAP_NAMESPACE

SOAPEnvelope::SOAPEnvelope()
{

}

SOAPEnvelope::~SOAPEnvelope()
{

}

bool
SOAPEnvelope::WriteSOAPPacket(XMLComposer& packet) const
{
	packet.Reset();
	packet.StartTag(SOAPEnv::Envelope, "E");

	// TODO: automagically add only the tags we need...
	packet.AddXMLNS("A", SOAPEnc::base);
	packet.AddXMLNS("s", XMLSchema2001::xsi);
	packet.AddXMLNS("y", XMLSchema2001::xsd);

	// TODO: allow user to set custom encoding style
	packet.AddAttr(SOAPEnv::encodingStyle, SOAPEnc::base);

	m_header.WriteSOAPPacket(packet);
	m_body.WriteSOAPPacket(packet);

	packet.EndTag(SOAPEnv::Envelope);

	return true;
}




