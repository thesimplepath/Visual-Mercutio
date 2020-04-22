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
 * $Id: SOAPISAPIServer.h,v 1.6 2002/05/20 16:56:11 jgorlick Exp $
 */


#if !defined(AFX_SOAPISAPIHANDLER_H__E392FAB3_3022_11D5_B3F3_000000000000__INCLUDED_)
#define AFX_SOAPISAPIHANDLER_H__E392FAB3_3022_11D5_B3F3_000000000000__INCLUDED_

#include <httpext.h>
#include <easysoap/SOAPServer.h>

BEGIN_EASYSOAP_NAMESPACE

/**
*
*/
class EASYSOAP_EXPORT SOAPISAPIImpersonateUser
{
public:
	SOAPISAPIImpersonateUser(EXTENSION_CONTROL_BLOCK *);
	~SOAPISAPIImpersonateUser();

private:
	SOAPISAPIImpersonateUser(const SOAPISAPIImpersonateUser&);
	SOAPISAPIImpersonateUser& operator=(const SOAPISAPIImpersonateUser&);

	EXTENSION_CONTROL_BLOCK	*m_ecb;
};

/**
*
*/
class EASYSOAP_EXPORT SOAPISAPITransport : public SOAPServerTransport
{
public:
	SOAPISAPITransport();
	~SOAPISAPITransport();

	void Initialize(EXTENSION_CONTROL_BLOCK* pECB);
	const char *GetServerInfo(const char *property);
	void NoContentType() {m_doContentType = false;}
	void AddHeader(const char *name, const char *value);
	size_t Write(const char *payload, size_t payloadsize);

	void SetError();
	const char *GetCharset() const;
	const char *GetContentType() const;
	const char *GetSoapAction() const;
	size_t Read(char *buffer, size_t buffsize);
	size_t Write(const SOAPMethod& method, const char *payload, size_t payloadsize);

private:
	SOAPISAPITransport(const SOAPISAPITransport&);
	SOAPISAPITransport& operator=(const SOAPISAPITransport&);

	EXTENSION_CONTROL_BLOCK*	m_ecb;
	const unsigned char *		m_ecbData;
	bool						m_error;
	size_t						m_leftRead;
	SOAPString					m_charset;
	SOAPString					m_contentType;
	SOAPString					m_soapaction;
	SOAPArray<char>				m_buffer;
	SOAPArray<char>				m_headers;
	bool						m_doContentType;
};

/**
*
*/
class EASYSOAP_EXPORT SOAPISAPIServer : public SOAPServer<SOAPISAPIServer>
{
public:
	SOAPISAPIServer() : m_ioport(NULL) {}
	SOAPISAPIServer(HANDLE ioport) : m_ioport(ioport) {}

	//
	// returns false if an error occurred
	bool Handle(SOAPISAPITransport& trans);
	int Handle();

private:

	SOAPISAPIServer(const SOAPISAPIServer&);
	SOAPISAPIServer& operator=(const SOAPISAPIServer&);

	HANDLE				m_ioport;
};

END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPISAPIHANDLER_H__E392FAB3_3022_11D5_B3F3_000000000000__INCLUDED_)

