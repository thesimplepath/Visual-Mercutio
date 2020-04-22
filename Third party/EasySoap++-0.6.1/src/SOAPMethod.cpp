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
 * $Id: SOAPMethod.cpp,v 1.16 2002/04/18 05:28:06 dcrowley Exp $
 */


#ifdef _MSC_VER
#pragma warning (disable: 4786)
#endif // _MSC_VER

#include <easysoap/SOAP.h>
#include <easysoap/SOAPMethod.h>
#include <easysoap/XMLComposer.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

USING_EASYSOAP_NAMESPACE

SOAPMethod::SOAPMethod(const char *name, const char *ns)
{
	SetName(name, ns);
}

SOAPMethod::SOAPMethod(const char *name, const char *ns, const char *sa)
{
	SetName(name, ns);
	SetSoapAction(sa);
}

SOAPMethod::~SOAPMethod()
{
}

void
SOAPMethod::SetSoapAction(const char *sa)
{
	m_action = sa;
}

bool
SOAPMethod::WriteSOAPPacket(XMLComposer& packet) const
{
	packet.StartTag(GetName(), "m");

	for (size_t i = 0; i < GetArray().Size(); ++i)
		GetArray()[i]->WriteSOAPPacket(packet);

	packet.EndTag(GetName());

	return true;
}

