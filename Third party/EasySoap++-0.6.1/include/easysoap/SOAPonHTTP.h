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
 * $Id: SOAPonHTTP.h,v 1.13 2002/06/12 08:32:25 dcrowley Exp $
 */

/* Modified 20-aug-2001 Tor Molnes ConsultIT AS
 * Added simple patch to support HTTP Chunked Transfer Encoding
 */

#if !defined(AFX_SOAPONHTTP_H__7D357522_E8B1_45A2_8CE1_A472A7D58C13__INCLUDED_)
#define AFX_SOAPONHTTP_H__7D357522_E8B1_45A2_8CE1_A472A7D58C13__INCLUDED_

#include <easysoap/SOAPUrl.h>
#include <easysoap/SOAPSocket.h>
#include <easysoap/SOAPTransport.h>
#include <easysoap/SOAPSSLContext.h>
#include <easysoap/SOAPDebugger.h>

BEGIN_EASYSOAP_NAMESPACE

/**
*
*/
class EASYSOAP_EXPORT SOAPHTTPProtocol : public SOAPProtocolBase
{
private:
	typedef	SOAPProtocolBase super;
	typedef SOAPHashMapNoCase<SOAPString, SOAPString>	HeaderMap;

	HeaderMap	m_headers;
	SOAPUrl		m_endpoint;
	SOAPUrl		m_proxy;
	SOAPString	m_httpmsg;
	SOAPString	m_charset;
	SOAPString	m_contentType;
	size_t		m_canread;
	bool		m_httpproxy;
	bool		m_doclose;
	bool		m_keepAlive;
	bool		m_chunked;
	SOAPSSLContext	*m_ctx;

	int		GetReply();
	size_t	GetChunkLength();
	bool	Connect();
	void	WriteHostHeader(const SOAPUrl&);
	void	FlushInput();
	void	StartVerb(const char *verb, const char *path);
	size_t  ReadChunk(char *buffer, size_t len);
	size_t  ReadBytes(char *buffer, size_t len);

public:
	SOAPHTTPProtocol()
		: m_canread(0)
		, m_httpproxy(false)
		, m_doclose(false)
		, m_keepAlive(true)
		, m_chunked(false)
		, m_ctx(0)
	{}

	SOAPHTTPProtocol(const SOAPUrl& endpoint)
		: m_canread(0)
		, m_httpproxy(false)
		, m_doclose(false)
		, m_keepAlive(true)
		, m_chunked(false)
		, m_ctx(0)
	{
		ConnectTo(endpoint);
	}

	SOAPHTTPProtocol(const SOAPUrl& endpoint, const SOAPUrl& proxy)
		: m_canread(0)
		, m_httpproxy(false)
		, m_doclose(false)
		, m_keepAlive(true)
		, m_chunked(false)
		, m_ctx(0)
	{
		ConnectTo(endpoint, proxy);
	}

	~SOAPHTTPProtocol()
	{}

	void	SetKeepAlive(bool keepAlive = true)	{m_keepAlive = keepAlive;}
	void 	SetContext(SOAPSSLContext& context) { m_ctx = &context; }
	void	ConnectTo(const SOAPUrl& endpoint);
	void	ConnectTo(const SOAPUrl& endpoint, const SOAPUrl& proxy);
	int		Get(const char *path);
	void	BeginPost(const char *path);
	int		PostData(const char *bytes, int len);
	void	WriteHeader(const char *header, const char *value);
	void	WriteHeader(const char *header, int value);

	const char *GetCharset() const {return m_charset;}
	const char *GetContentType() const {return m_contentType;}
	const char *GetHeader(const char *header) const;
	int		GetContentLength() const;
	bool	IsChunked() const {return m_chunked;}

	virtual size_t Read(char *buffer, size_t len);
	virtual void Close();
	virtual bool CanRead();
	const SOAPString& GetRequestMessage()	{return m_httpmsg;}

	static void ParseContentType(SOAPString& contentType, SOAPString& charset, const char *contenttype);
};

/**
*
*/
class EASYSOAP_EXPORT SOAPonHTTP : public SOAPTransport
{
private:
	SOAPonHTTP(const SOAPonHTTP&);
	SOAPonHTTP& operator=(const SOAPonHTTP&);

	SOAPHTTPProtocol	m_http;
	SOAPString			m_userAgent;
	SOAPUrl				m_endpoint;
	SOAPSSLContext 		*m_ctx;

public:
	SOAPonHTTP() : m_ctx(0){}
	SOAPonHTTP(const SOAPUrl& endpoint);
	SOAPonHTTP(const SOAPUrl& endpoint, const SOAPUrl& proxy);

	virtual ~SOAPonHTTP() {}

	void ConnectTo(const SOAPUrl& endpoint);
	void ConnectTo(const SOAPUrl& endpoint, const SOAPUrl& proxy);

	void SetUserAgent(const char *userAgent);
	void SetTimeout(size_t secs) {m_http.SetTimeout(secs);}
	void SetKeepAlive(bool keepAlive = true)	{m_http.SetKeepAlive(keepAlive);}
	void SetContext(SOAPSSLContext& context) 
	{
			m_ctx = &context;
			m_http.SetContext(context);
	}
	//
	//  Return charset if we know it
	virtual const char *GetCharset() const;
	virtual const char *GetContentType() const;

	// read the payload into the buffer.
	// can be called multiple times.
	// returns 0 if entire payload has been read.
	virtual size_t Read(char *buffer, size_t buffsize);

	// send the payload.  can only be called ONCE per
	// payload.
	virtual size_t Write(const SOAPMethod& method, const char *payload, size_t payloadsize);
};

END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPONHTTP_H__7D357522_E8B1_45A2_8CE1_A472A7D58C13__INCLUDED_)

