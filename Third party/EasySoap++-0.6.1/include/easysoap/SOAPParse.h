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
 * $Id: SOAPParse.h,v 1.4 2002/05/20 16:56:11 jgorlick Exp $
 */


#if !defined(AFX_SOAPPARSE_H__751545FF_EF84_42BC_9622_A6CE624F1F14__INCLUDED_)
#define AFX_SOAPPARSE_H__751545FF_EF84_42BC_9622_A6CE624F1F14__INCLUDED_


#include <easysoap/SOAP.h>
#include <easysoap/XMLParser.h>

#include <easysoap/SOAPTransport.h>
#include <easysoap/SOAPStack.h>

BEGIN_EASYSOAP_NAMESPACE

class SOAPParserEventHandler;
class SOAPEnvelopeHandler;

/**
*
*/
class EASYSOAP_EXPORT SOAPParser : protected XMLParser
{
public:

	SOAPParser();
	virtual ~SOAPParser();

	SOAPEnvelope& Parse(SOAPEnvelope& env, SOAPTransport& trans);

	// Used by subscribers/handlers

	// Resolves a namespace like "xsi" into a fully qualified name
	// "http://www.w3.org/1999/XMLSchema-instance"
	const char *ExpandNamespace(const char *name, const char *nsend) const;

	//
	// Set the SOAPParameter which defines the
	// give id attribute.
	void SetIdParam(const char *name, SOAPParameter *);

	void SetHRefParam(SOAPParameter *);

protected:

	void startElement(const XML_Char *name, const XML_Char **attrs);
	void endElement(const XML_Char *name);
	void characterData(const XML_Char *str, int len);
	void startNamespace(const XML_Char *prefix, const XML_Char *uri);
	void endNamespace(const XML_Char *prefix);

private:

	typedef SOAPStack<SOAPParseEventHandler *>	HandlerStack;
	typedef SOAPHashMap<SOAPString, SOAPString> NamespaceMap;
	typedef SOAPHashMap<SOAPString, SOAPParameter*> IdMap;
	typedef SOAPArray<SOAPParameter *>				HRefArray;

	void HandleHRefs();

	SOAPEnvelopeHandler		*m_envelopeHandler;
	HandlerStack			m_handlerstack;
	mutable SOAPString		m_work;
	SOAPEnvelopeHandler		*m_handler;
	NamespaceMap			m_nsmap;
	IdMap					m_idmap;
	HRefArray				m_hrefs;
};

END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPPARSE_H__751545FF_EF84_42BC_9622_A6CE624F1F14__INCLUDED_)

