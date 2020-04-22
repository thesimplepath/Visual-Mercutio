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
 * SOAPParse.cpp,v 1.27 2001/12/11 01:53:44 dcrowley Exp
 */

#ifdef _MSC_VER
#pragma warning (disable: 4786)
#endif // _MSC_VER

#include <easysoap/SOAP.h>
#include <easysoap/SOAPParse.h>
#include <easysoap/SOAPNamespaces.h>

#include "SOAPEnvelopeHandler.h"
#include "es_namespaces.h"

#define BUFF_SIZE 1024

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

USING_EASYSOAP_NAMESPACE

SOAPParser::SOAPParser()
{
	m_envelopeHandler = new SOAPEnvelopeHandler();
}

SOAPParser::~SOAPParser()
{
	delete m_envelopeHandler;
}


SOAPEnvelope&
SOAPParser::Parse(SOAPEnvelope& env, SOAPTransport& trans)
{
	m_envelopeHandler->SetEnvelope(env);
	m_handler = m_envelopeHandler;

	// make sure our stack is empty
	m_handlerstack.Clear();
	m_nsmap.Clear();

	//
	// clear out any id/href info
	// we have hanging around...
	m_idmap.Clear();
	m_hrefs.Resize(0);

	const char *contentType = trans.GetContentType();
	if (contentType && sp_strcmp(contentType, "text/xml"))
		throw SOAPException("Unexpected content type, only support text/xml: %s", contentType);

	InitParser(trans.GetCharset());
	while (1)
	{
		//
		// create a buffer to read the HTTP payload into
		//
		void *buffer = GetParseBuffer(BUFF_SIZE);
		if (!buffer)
			throw SOAPMemoryException();

		//
		// read the HTTP payload
		//
		int read = trans.Read((char *)buffer, BUFF_SIZE);
		if (!ParseBuffer(read))
		{
			throw SOAPException(
				"Error while parsing SOAP XML payload: %s",
				GetErrorMessage());
		}

		if (read == 0)
			break;
	}

	HandleHRefs();

	return env;
}

void
SOAPParser::startElement(const XML_Char *name, const XML_Char **attrs)
{
	SOAPParseEventHandler* handler = 0;
	if (m_handlerstack.IsEmpty())
	{
		if (sp_strcmp(name, SOAP_ENV PARSER_NS_SEP "Envelope") == 0)
		{
			handler = m_handler;
		}
		else
		{
			//
			// FIXME:
			// Probably what we should do instead of throw is set
			// a flag that says the response is invalid.  We usually
			// get in here when the HTTP response code is 500 and it
			// gives us back some HTML instead of a SOAP Fault.
			throw SOAPException("Unknown SOAP response tag: %s", name);
		}
	}
	else
	{
		handler = m_handlerstack.Top();
	}

	if (handler)
	{
		m_handlerstack.Push(handler->startElement(*this, name, attrs));
	}
	else
	{
		m_handlerstack.Push(0);
	}
}

void
SOAPParser::characterData(const XML_Char *str, int len)
{
	SOAPParseEventHandler* handler = m_handlerstack.Top();
	if (handler)
		handler->characterData(str, len);
}

void
SOAPParser::endElement(const XML_Char *name)
{
	SOAPParseEventHandler* handler = m_handlerstack.Top();
	if (handler)
		handler->endElement(name);
	m_handlerstack.Pop();
}

void
SOAPParser::startNamespace(const XML_Char *prefix, const XML_Char *uri)
{
	if (prefix)
		m_work = prefix;
	else
		m_work = "";

	m_nsmap[m_work] = uri;
}

void
SOAPParser::endNamespace(const XML_Char *prefix)
{
	if (prefix)
		m_work = prefix;
	else
		m_work = "";

	m_nsmap.Remove(m_work);
}

void
SOAPParser::SetHRefParam(SOAPParameter *param)
{
	m_hrefs.Add(param);
}

void
SOAPParser::SetIdParam(const char *id, SOAPParameter *param)
{
	IdMap::Iterator i = m_idmap.Find(id);
	if (i)
		throw SOAPException("Found parameter with duplicate id='%s'", id);
	m_idmap[id] = param;
}

const char *
SOAPParser::ExpandNamespace(const char *ns, const char *nsend) const
{
	m_work = "";
	m_work.Append(ns, nsend - ns);
	NamespaceMap::Iterator i = m_nsmap.Find(m_work);
	if (i)
		return i->Str();
	return 0;
}

void
SOAPParser::HandleHRefs()
{
	//
	// For all of the parameters with href's
	// which were registerd, link them to
	// the param with the corresponding id.
	for (HRefArray::Iterator i = m_hrefs.Begin(); i != m_hrefs.End(); ++i)
	{
		SOAPParameter *p = *i;
		SOAPParameter::Attrs::Iterator href = p->GetAttributes().Find("href");
		if (!href)
			throw SOAPException("Somehow a parameter without an href got in the href map...");
		const char *h = href.Item().GetName();
		if (*h == '#')
		{
			IdMap::Iterator id = m_idmap.Find(++h);
			if (!id)
				throw SOAPException("Could not find parameter for href='%s'", --h);
			SOAPParameter *pid = *id;
			p->LinkTo(*pid);
		}
		else
			throw SOAPException("Could not resolve href='%s'", h);
	}
}
