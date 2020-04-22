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
 * $Id: SOAPHeaderHandler.cpp,v 1.14 2001/11/21 06:00:47 dcrowley Exp $
 */


#ifdef _MSC_VER
#pragma warning (disable: 4786)
#endif // _MSC_VER

#include <easysoap/SOAP.h>
#include <easysoap/SOAPNamespaces.h>

#include "SOAPHeaderHandler.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

USING_EASYSOAP_NAMESPACE

SOAPHeaderHandler::SOAPHeaderHandler()
: m_header(0)
{

}

SOAPHeaderHandler::~SOAPHeaderHandler()
{

}

void
SOAPHeaderHandler::SetHeader(SOAPHeader& header)
{
	m_header = &header;
}

SOAPParseEventHandler *
SOAPHeaderHandler::start(SOAPParser&, const XML_Char *, const XML_Char **)
{
	return this;
}

SOAPParseEventHandler *
SOAPHeaderHandler::startElement(SOAPParser& parser, const XML_Char *name, const XML_Char **attrs)
{
	m_paramHandler.SetParameter(&m_header->AddHeader());
	return m_paramHandler.start(parser, name, attrs);
}

