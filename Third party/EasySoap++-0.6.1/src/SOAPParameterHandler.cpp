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
 * $Id: SOAPParameterHandler.cpp,v 1.27 2002/03/07 08:04:38 dcrowley Exp $
 */

#ifdef _MSC_VER
#pragma warning (disable: 4786)
#endif // _MSC_VER

#include "SOAPParameterHandler.h"
#include "SOAPStructHandler.h"

#include <easysoap/SOAPNamespaces.h>
#include <easysoap/SOAPParameter.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

USING_EASYSOAP_NAMESPACE

SOAPParameterHandler::SOAPParameterHandler()
: m_param(0)
, m_structHandler(0)
, m_setvalue(false)
{
}

SOAPParameterHandler::~SOAPParameterHandler()
{
	delete m_structHandler;
}

SOAPParseEventHandler *
SOAPParameterHandler::start(SOAPParser& parser, const XML_Char *name, const XML_Char **attrs)
{
	m_param->Reset();

	const char *ns = sp_strchr(name, PARSER_NS_SEP[0]);
	if (ns)
	{
		m_param->GetName().GetNamespace() = "";
		m_param->GetName().GetNamespace().Append(name, ns - name);
		m_param->GetName().GetName() = ++ns;
	}
	else
	{
		m_param->SetName(name);
	}

	m_setvalue = true;
	m_str.Resize(0);

	const XML_Char **cattrs = attrs;
	while (*cattrs)
	{
		const XML_Char *tag = *cattrs++;
		const XML_Char *val = *cattrs++;

		const char *tsep = sp_strchr(tag, PARSER_NS_SEP[0]);
		if (tsep)
		{
				m_attrName.GetNamespace() = "";
				m_attrName.GetNamespace().Append(tag, tsep - tag);
				m_attrName.GetName() = ++tsep;

				SOAPQName& attr = m_param->AddAttribute(m_attrName);

				const char *vsep = sp_strchr(val, ':');
				if (vsep)
				{
					const char *vns = parser.ExpandNamespace(val, vsep);
					if (vns)
						attr.Set(++vsep, vns);
					else
						attr = val;
				}
				else
				{
					attr = val;
				}
		}
		else
		{
			tsep = sp_strchr(tag, ':');
			if (tsep)
			{
				throw SOAPException("Could not expand attribute namespace: %s", tag);
			}
			else
			{
				m_attrName = tag;
				m_param->AddAttribute(m_attrName) = val;
			}
		}
	}

	return this;
}

SOAPParseEventHandler *
SOAPParameterHandler::startElement(SOAPParser& parser, const XML_Char *name, const XML_Char **attrs)
{
	//
	// If a parameter has an element, then it must
	// be a struct!
	m_setvalue = false;
	if (!m_structHandler)
		m_structHandler = new SOAPStructHandler();
	m_structHandler->SetParameter(m_param);
	return m_structHandler->start(parser, 0, 0)->startElement(parser, name, attrs);
}

void
SOAPParameterHandler::characterData(const XML_Char *str, int len)
{
	if (m_setvalue)
		m_str.Add(str, len);
}

void
SOAPParameterHandler::endElement(const XML_Char *)
{
	if (m_setvalue)
	{
		m_param->SetNull(false);
		m_str.Add(0); // null terminate
		m_param->GetStringRef() = m_str.Ptr();
	}
}
