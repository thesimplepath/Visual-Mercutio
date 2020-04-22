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
 * $Id: SOAPBodyHandler.cpp,v 1.22 2001/11/30 07:07:42 dcrowley Exp $
 */


#ifdef _MSC_VER
#pragma warning (disable: 4786)
#endif // _MSC_VER

#include "SOAPBodyHandler.h"
#include "es_namespaces.h"

#include <easysoap/SOAPBody.h>
#include <easysoap/SOAPNamespaces.h>

USING_EASYSOAP_NAMESPACE

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SOAPBodyHandler::SOAPBodyHandler()
: m_body(0)
, m_gotMethod(false)
{
}

SOAPBodyHandler::~SOAPBodyHandler()
{

}

void
SOAPBodyHandler::SetBody(SOAPBody& body)
{
	m_body = &body;
	m_methodHandler.SetMethod(body.GetMethod());
}

SOAPParseEventHandler *
SOAPBodyHandler::start(SOAPParser&, const XML_Char *, const XML_Char **)
{
	m_gotMethod = false;
	return this;
}

SOAPParseEventHandler *
SOAPBodyHandler::startElement(SOAPParser& parser, const XML_Char *name, const XML_Char **attrs)
{
	const char *id = 0;
	const char *href = 0;
	bool notRoot = false;

	const XML_Char **cattrs = attrs;
	while (*cattrs)
	{
		const char *tag = *cattrs++;
		const char *val = *cattrs++;
		if (sp_strcmp(tag, "id") == 0)
		{
			id = val;
		}
		else if (sp_strcmp(tag, "href") == 0)
		{
			href = val;
		}
		else if (sp_strcmp(tag, SOAP_ENC PARSER_NS_SEP "root") == 0)
		{
			notRoot = (sp_strcmp(val, "0") == 0);
		}
	}

	if (m_gotMethod || notRoot)
	{
		SOAPParameter *p = &m_body->AddParameter();

		if (href)
			parser.SetHRefParam(p);
		if (id)
			parser.SetIdParam(id, p);

		m_paramHandler.SetParameter(p);
		return m_paramHandler.start(parser, name, attrs);
	}

	if (sp_strcmp(name, SOAP_ENV PARSER_NS_SEP "Fault") == 0)
	{
		SOAPParameter *p = &m_body->GetFault();
		m_paramHandler.SetParameter(p);
		m_body->SetIsFault(true);
		return m_paramHandler.start(parser, name, attrs);
	}

	m_gotMethod = true;
	m_body->SetIsFault(false);
	return m_methodHandler.start(parser, name, attrs);
}

