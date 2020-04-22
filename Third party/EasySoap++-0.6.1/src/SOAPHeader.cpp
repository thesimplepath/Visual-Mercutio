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
 * $Id: SOAPHeader.cpp,v 1.14 2001/12/20 22:38:19 dcrowley Exp $
 */


#ifdef _MSC_VER
#pragma warning (disable: 4786)
#endif // _MSC_VER

#include <easysoap/SOAP.h>
#include <easysoap/SOAPHeader.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

USING_EASYSOAP_NAMESPACE

const char *SOAPHeader::actorNext = "http://schemas.xmlsoap.org/soap/actor/next";

SOAPHeader::SOAPHeader()
: m_outtasync(false)
{
}

SOAPHeader::~SOAPHeader()
{
	Reset();
}

SOAPParameter&
SOAPHeader::AddHeader()
{
	m_outtasync = true;
	return *m_headers.Add(m_pool.Get());
}

SOAPParameter&
SOAPHeader::AddHeader(const SOAPQName& name)
{
	SOAPParameter *p = m_pool.Get();
	p->SetName(name);
	m_headermap[name] = p;
	return *m_headers.Add(p);
}

void
SOAPHeader::Reset()
{
	for (Headers::Iterator i = m_headers.Begin(); i != m_headers.End(); ++i)
	{
		(*i)->Reset();
		m_pool.Return(*i);
	}
	m_headers.Resize(0);

	m_headermap.Clear();
	m_outtasync = false;
}

const SOAPParameter&
SOAPHeader::GetHeader(const SOAPQName& name) const
{
	if (m_outtasync)
		Sync();

	HeaderMap::Iterator found = m_headermap.Find(name);
	if (!found)
		throw SOAPException("Could not find header {%s}:%s",
			(const char *)name.GetNamespace(),
			(const char *)name.GetName());
	return **found;
}

SOAPParameter&
SOAPHeader::GetHeader(const SOAPQName& name)
{
	if (m_outtasync)
		Sync();

	HeaderMap::Iterator found = m_headermap.Find(name);
	if (!found)
		throw SOAPException("Could not find header {%s}:%s",
			(const char *)name.GetNamespace(),
			(const char *)name.GetName());
	return **found;
}

void
SOAPHeader::Sync() const
{
	m_headermap.Clear();
	for (Headers::ConstIterator i = m_headers.Begin(); i != m_headers.End(); ++i)
		m_headermap[(*i)->GetName()] = (*i);
	m_outtasync = false;
}

bool
SOAPHeader::WriteSOAPPacket(XMLComposer& packet) const
{
	if (m_headers.Size() > 0)
	{
		packet.StartTag(SOAPEnv::Header);

		for (Headers::ConstIterator i = m_headers.Begin(); i != m_headers.End(); ++i)
			(*i)->WriteSOAPPacket(packet);

		packet.EndTag(SOAPEnv::Header);
	}
	return true;
}

