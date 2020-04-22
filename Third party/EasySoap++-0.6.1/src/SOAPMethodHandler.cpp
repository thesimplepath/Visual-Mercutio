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
 * $Id: SOAPMethodHandler.cpp,v 1.20 2001/11/21 06:00:47 dcrowley Exp $
 */


#ifdef _MSC_VER
#pragma warning (disable: 4786)
#endif // _MSC_VER

#include "SOAPMethodHandler.h"
#include <easysoap/SOAPMethod.h>
#include <easysoap/SOAPNamespaces.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

USING_EASYSOAP_NAMESPACE

SOAPMethodHandler::SOAPMethodHandler()
: m_method(0)
{

}

SOAPMethodHandler::~SOAPMethodHandler()
{

}

void
SOAPMethodHandler::SetMethod(SOAPMethod& method)
{
	m_method = &method;
}

SOAPParseEventHandler *
SOAPMethodHandler::start(SOAPParser&, const XML_Char *name, const XML_Char **)
{
	m_method->Reset();

	const char *ns = sp_strchr(name, PARSER_NS_SEP[0]);
	if (ns)
	{
		m_method->GetName().GetNamespace() = "";
		m_method->GetName().GetNamespace().Append(name, ns - name);
		m_method->GetName().GetName() = ++ns;
	}
	else
	{
		m_method->SetName(name);
	}

	return this;
}

SOAPParseEventHandler *
SOAPMethodHandler::startElement(SOAPParser& parser, const XML_Char *name, const XML_Char **attrs)
{
	const char *id = 0;
	const char *href = 0;

	const char **cattrs = attrs;
	while (*cattrs)
	{
		const char *tag = *cattrs++;
		const char *val = *cattrs++;

		if (sp_strcmp(tag, "id") == 0)
		{
			id = val;
			break;
		}
		else if (sp_strcmp(tag, "href") == 0)
		{
			href = val;
			break;
		}
	}

	SOAPParameter *param = &m_method->AddParameter(name);

	if (href)
		parser.SetHRefParam(param);
	if (id)
		parser.SetIdParam(id, param);

	m_paramHandler.SetParameter(param);
	return m_paramHandler.start(parser, name, attrs);
}


