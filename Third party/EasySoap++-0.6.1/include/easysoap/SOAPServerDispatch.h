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
 * $Id: SOAPServerDispatch.h,v 1.5 2002/05/20 16:56:11 jgorlick Exp $
 */


#if !defined(AFX_SOAPSERVERDISPATCH_H__F7015C4A_8459_4090_ABD1_FB3EAB144B39__INCLUDED_)
#define AFX_SOAPSERVERDISPATCH_H__F7015C4A_8459_4090_ABD1_FB3EAB144B39__INCLUDED_

#include <easysoap/SOAP.h>

BEGIN_EASYSOAP_NAMESPACE

class SOAPDispatchHandlerInterface;
class SOAPHeaderHandlerInterface;

/**
*
*/
class EASYSOAP_EXPORT SOAPServerDispatch
{
public:
	SOAPServerDispatch();
	virtual ~SOAPServerDispatch();

	SOAPServerDispatch& DispatchTo(SOAPDispatchHandlerInterface *disp);
	SOAPServerDispatch& DispatchTo(SOAPHeaderHandlerInterface *disp);

	//
	// returns false if an error occurred
	bool Handle(SOAPServerTransport& transport);

protected:
	virtual bool	HandleRequest(SOAPEnvelope& request, SOAPResponse& response);
	virtual void	HandleHeaders(SOAPEnvelope& request, SOAPResponse& response);
	virtual void	HandleFault(SOAPFault&) {}

private:

	SOAPServerDispatch(const SOAPServerDispatch&);
	SOAPServerDispatch& operator=(const SOAPServerDispatch&);
	void WriteFault(const SOAPFault& fault);

	typedef SOAPArray<SOAPDispatchHandlerInterface*> Handlers;
	typedef SOAPArray<SOAPHeaderHandlerInterface*> HeaderHandlers;

	Handlers			m_handlers;
	HeaderHandlers		m_headerHandlers;
	SOAPServerTransport	*m_transport;
	SOAPResponse		m_response;
	SOAPEnvelope		m_request;
	XMLComposer			m_writer;
	SOAPParser			m_parser;
	SOAPString			m_respname;
};

END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPSERVERDISPATCH_H__F7015C4A_8459_4090_ABD1_FB3EAB144B39__INCLUDED_)

