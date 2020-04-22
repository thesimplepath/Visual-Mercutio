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
 * $Id: SOAPonHTTP.cpp,v 1.54 2002/06/25 16:42:55 dcrowley Exp $
 */

/* Modified 20-aug-2001 Tor Molnes ConsultIT AS
 * Added simple patch to support HTTP Chunked Transfer Encoding
 */

#ifdef _MSC_VER
#pragma warning (disable: 4786)
#endif // _MSC_VER

#include <easysoap/SOAP.h>
#include <easysoap/SOAPonHTTP.h>
#include <easysoap/SOAPEnvelope.h>
#include <easysoap/SOAPDebugger.h>

#include "SOAPSecureSocketImp.h"

#define DEFAULT_USERAGENT EASYSOAP_STRING "/" EASYSOAP_VERSION_STRING

USING_EASYSOAP_NAMESPACE

SOAPonHTTP::SOAPonHTTP(const SOAPUrl& endpoint)
: m_ctx(0)
{
	ConnectTo(endpoint);
}

SOAPonHTTP::SOAPonHTTP(const SOAPUrl& endpoint, const SOAPUrl& proxy)
: m_ctx(0)
{
	ConnectTo(endpoint, proxy);
}


// read the payload into the buffer.
// can be called multiple times.
// returns 0 if entire payload has been read.

size_t
SOAPonHTTP::Read(char *buffer, size_t buffsize)
{
	return m_http.Read(buffer, buffsize);
}

// send the payload.  can only be called ONCE per
// payload. 
//
size_t
SOAPonHTTP::Write(const SOAPMethod& method, const char *payload, size_t payloadsize)
{
	int retry = 5;
	int ret = 0;
	while (retry--)
	{
		m_http.BeginPost(m_endpoint.Path());
		m_http.WriteHeader("User-Agent", m_userAgent.IsEmpty() ?
				DEFAULT_USERAGENT : (const char *)m_userAgent);

		m_http.WriteHeader("Content-Type", "text/xml; charset=\"UTF-8\"");
		if (!m_endpoint.User().IsEmpty() || !m_endpoint.Password().IsEmpty())
		{
			SOAPString up = m_endpoint.User();
			up.Append(":");
			up.Append(m_endpoint.Password());
			SOAPString enc;
			SOAPBase64Base::Encode(up, up.Length(), enc);

			up = "Basic ";
			up.Append(enc);
			m_http.WriteHeader("Authorization", (const char *)up);
		}

		m_http.Write("SOAPAction:");
		if (method.GetSoapAction())
		{
			m_http.Write(" \"");
			m_http.Write(method.GetSoapAction());
			m_http.Write("\"");
		}
		m_http.WriteLine();

		ret = m_http.PostData(payload, payloadsize);

		//
		// If resource moved (temporarily or permanently)
		if (ret == 301 || ret == 302)
		{
			const char *location = m_http.GetHeader("Location");
			if (!location)
				throw SOAPException("HTTP code %d did not return a Location header.", ret);

			SOAPUrl newendpoint = location;

			// If only the path changed, we don't
			// need to re-connect.
			if (newendpoint.Hostname() != m_endpoint.Hostname() ||
				newendpoint.Port() != m_endpoint.Port())
				m_http.ConnectTo(newendpoint);

			m_endpoint = newendpoint;
		}
		else
			break;
	}

	// Only valid return codes  we know of.  200 is success,
	// 500 could be a soap fault.
	if (ret != 200 && ret != 500)
		throw SOAPException("Unexpected return code: %s",
			(const char *)m_http.GetRequestMessage());

	bool isxml = true;
	const char *contype = m_http.GetHeader("Content-Type");
	if (contype)
		isxml = (sp_strstr(contype, "text/xml") != 0);

	if (!isxml)
		throw SOAPException("Unexpected return Content-Type: %s", contype);

	return ret;
}

const char *
SOAPonHTTP::GetCharset() const
{
	return m_http.GetCharset();
}

const char *
SOAPonHTTP::GetContentType() const
{
	return m_http.GetContentType();
}

void
SOAPonHTTP::ConnectTo(const SOAPUrl& endpoint)
{
	m_endpoint = endpoint;
	if (m_ctx)
			m_http.SetContext(*m_ctx);

	const char *proxy_str = getenv("http_proxy");
	if (proxy_str)
	{
		SOAPUrl proxy = proxy_str;
		m_http.ConnectTo(endpoint, proxy);
	}
	else
		m_http.ConnectTo(endpoint);
}

void
SOAPonHTTP::ConnectTo(const SOAPUrl& endpoint, const SOAPUrl& proxy)
{
	m_endpoint = endpoint;
	if (m_ctx)
			m_http.SetContext(*m_ctx);
	m_http.ConnectTo(endpoint, proxy);
}

void
SOAPHTTPProtocol::ConnectTo(const SOAPUrl& endpoint, const SOAPUrl& proxy)
{
	Close();
	m_endpoint = endpoint;
	m_proxy = proxy;
}

void
SOAPHTTPProtocol::ConnectTo(const SOAPUrl& endpoint)
{
	Close();
	m_endpoint = endpoint;
	m_proxy = SOAPUrl();
}

void
SOAPHTTPProtocol::WriteHostHeader(const SOAPUrl& url)
{
	if (url.PortIsDefault())
		WriteHeader("Host", (const char *)url.Hostname());
	else
	{
		char buffer[256];
		snprintf(buffer, sizeof(buffer), "%s:%d",
				(const char *)url.Hostname(),
				url.Port());
		WriteHeader("Host", buffer);
	}
}

int
SOAPHTTPProtocol::Get(const char *path)
{
	StartVerb("GET", path);
	WriteLine("");
	int ret = GetReply();
	if (ret == 100)
		ret = GetReply();
	return ret;
}

void
SOAPHTTPProtocol::FlushInput()
{
	char buffer[256];
	while (CanRead())
	{
		size_t read = Read(buffer, sizeof(buffer));
		if (read == 0)
		{
			Close();
		}
	}

	if (m_doclose)
		Close();
}

void
SOAPHTTPProtocol::StartVerb(const char *verb, const char *path)
{
	if (!path)
		throw SOAPException("Invalid NULL path");

	FlushInput();
	SOAPDebugger::Print(1, "\n\nREQUEST:\n");

	if (!Connect())
		throw SOAPSocketException("Unable to make socket connection");
	Write(verb);
	Write(" ");

	if (m_httpproxy)
	{
		Write(m_endpoint.GetBaseString());
		if (*path == '/')
			++path;
		Write(path);
	}
	else
		Write(path);

	WriteLine(" HTTP/1.1");
	WriteHostHeader(m_endpoint);

	if (m_keepAlive)
		WriteHeader("Connection", "Keep-Alive");
}

void
SOAPHTTPProtocol::BeginPost(const char *path)
{

	StartVerb("POST", path);
}

int
SOAPHTTPProtocol::PostData(const char *bytes, int len)
{
	WriteHeader("Content-Length", len);
	WriteLine("");
	Write(bytes, len);

	int ret = GetReply();

	if (ret == 100)
		ret = GetReply();

	return ret;
}

void
SOAPHTTPProtocol::WriteHeader(const char *header, const char *value)
{
	Write(header);
	Write(": ");
	WriteLine(value);
}

void
SOAPHTTPProtocol::WriteHeader(const char *header, int value)
{
	char buffer[64];
	snprintf(buffer, sizeof(buffer), "%d", value);
	WriteHeader(header, buffer);
}

int
SOAPHTTPProtocol::GetReply()
{
	Flush();
	SOAPDebugger::Print(1, "\n\nRESPONSE:\n");
	char buff[2048];
	m_headers.Clear();

	int httpreturn = 500;
	int respver = 0;

	// This should read a line that is something like:
	// HTTP/1.1 200 OK
	if (ReadLine(buff, sizeof(buff)) == 0)
	{
		throw SOAPSocketException("Couldn't read response.");
	}

	const char *vers = sp_strchr(buff, '/');
	if (vers)
	{
		respver += atoi(++vers) * 10;
		if ((vers = sp_strchr(vers, '.')))
			respver += atoi(++vers);
	}

	const char *httpretcode = sp_strchr(buff, ' ');
	if (httpretcode)
	{
		m_httpmsg = ++httpretcode;
		httpreturn = atoi(httpretcode);
		if (httpreturn == 0)
			httpreturn = 500;
	}
	else
		m_httpmsg = buff;

	while (1)
	{
		if (ReadLine(buff, sizeof(buff)) == 0)
			break;

		if (buff[0] == 0)
			break;
		char *c = sp_strchr(buff, ':');
		if (c)
		{
			*c++ = 0;
			while (*c == ' ')
				*c++ = 0;
			m_headers[buff] = c;
		}
		else
		{
			// I don't think we should get here...
		}
	}

	//
	// Get charset/content-type info
	//
	// Per some RFC, encoding is us-ascii if it's not
	// specifief in HTTP header.
	m_charset = "US-ASCII";
	const char *contype = GetHeader("Content-Type");
	if (contype)
	{
		const char *charset = charset = sp_strstr(contype, "charset=");
		if (charset)
		{
			charset += 8;
			if (*charset == '\"')
				++charset;
			const char *end = charset;

			while (*end && *end != '\"' && *end != ';' && *end != ' ')
				++end;

			m_charset = "";
			m_charset.Append(charset, end - charset);
		}
	}

	//
	// Get some information so we can close the
	// the connection gracefully if we need to..
	//
	m_canread = GetContentLength();
	m_doclose = false;
	const char *keepalive = GetHeader("Connection");
	if (respver > 10)
	{
		if (keepalive && sp_strcasecmp(keepalive, "Keep-Alive") != 0)
			m_doclose = true;
	}
	else
	{
		if (!keepalive || sp_strcasecmp(keepalive, "Keep-Alive") != 0)
			m_doclose = true;
	}

	if (!m_keepAlive)
		m_doclose = true;
	//
	// Check if HTTP is Transfer Endoded: Chunked
	//
	const char *chunked = GetHeader("Transfer-Encoding");
	m_chunked = false;
	if (chunked && sp_strcasecmp(chunked, "Chunked") == 0)
	{
		m_chunked = true;
		m_canread = 0;
		SOAPDebugger::Print(2, "\nTransfer is Chunked!\n");
	}

	return httpreturn;
}

const char *
SOAPHTTPProtocol::GetHeader(const char *header) const
{
	HeaderMap::Iterator i = m_headers.Find(header);
	if (i != m_headers.End())
	{
		return (const char *)(*i);
	}
	return 0;
}

int
SOAPHTTPProtocol::GetContentLength() const
{
	const char *header = GetHeader("Content-Length");
	int len = -1;
	if (header)
		len = atoi(header);
	return len;
}

size_t
SOAPHTTPProtocol::GetChunkLength()
{
	char hexStg[10];	// hex buffer
	int  n = 0;         // position in string
	int  m = 0;         // hex value of character (0-15)
	size_t intValue = 0;  // integer value of hex string

	// skip blank lines
	while ((super::ReadLine(hexStg, sizeof(hexStg))) == 0)
		;

	while (n < 8)
	{
		if (hexStg[n]=='\0')
			break;
		if (hexStg[n] >= '0' && hexStg[n] <= '9')	//if 0 to 9
			m = hexStg[n] & 0x0f;            //convert to int
		else if (hexStg[n] >='a' && hexStg[n] <= 'f') //if a to f
			m = (hexStg[n] & 0x0f) + 9;      //convert to int
		else if (hexStg[n] >='A' && hexStg[n] <= 'F') //if A to F
			m = (hexStg[n] & 0x0f) + 9;      //convert to int
		else
			break;
		++n;
		intValue = intValue * 16 + m;
	}

	SOAPDebugger::Print(1, "\nGetChunkLength: %s = %d\n", hexStg, intValue);
	return intValue;
}

void
SOAPHTTPProtocol::Close()
{
	SOAPDebugger::Print(5, "SOAPHTTPProtocol::Close()");
	m_canread = 0;
	m_doclose = false;
	super::Close();
	SOAPDebugger::Print(2, "CLOSED\n");
}

bool
SOAPHTTPProtocol::CanRead()
{
	return m_canread > 0 || super::CanRead();
	//return (m_canread == -1 && super::CanRead()) || m_canread > 0;
}

size_t
SOAPHTTPProtocol::ReadChunk(char *buffer, size_t len)
{
	// get chunk size, abort on empty chunk
	if (m_canread == 0&& (m_canread = GetChunkLength()) == 0)
	{
		if (m_doclose)
			Close();
		return 0;
	}

	if (len > m_canread)
		len = m_canread;

	size_t ret = super::Read(buffer, len);
	m_canread -= ret;
	return ret;
}

size_t
SOAPHTTPProtocol::ReadBytes(char *buffer, size_t len)
{
	size_t ret = 0;
	if (m_canread != 0)
	{
		ret = super::Read(buffer, len);
		if (m_canread > 0)
		{
			m_canread -= ret;
			if (m_canread == 0 && m_doclose)
			{
				Close();
			}
		}
	}
	return ret;
}

size_t
SOAPHTTPProtocol::Read(char *buffer, size_t len)
{
	if (m_chunked)
		return ReadChunk(buffer, len);

	return ReadBytes(buffer, len);
}

bool
SOAPHTTPProtocol::Connect()
{
	SOAPDebugger::Print(5, "SOAPHTTPProtocol::Connect()\r\n");
	if (!IsOpen())
	{
		// See if we have to talk through an HTTP proxy
		m_httpproxy = (m_proxy.Protocol() == SOAPUrl::http_proto);

		int port					= m_httpproxy ? m_proxy.Port()		: m_endpoint.Port();
		const char *host			= m_httpproxy ? m_proxy.Hostname()	: m_endpoint.Hostname();
		SOAPUrl::UrlProtocol proto	= m_endpoint.Protocol();

		switch (proto)
		{
		case SOAPUrl::http_proto:
			SOAPProtocolBase::Connect(host, port);
			break;
		case SOAPUrl::https_proto:
			{
				SOAPSecureSocketImp * socket;
				if (m_ctx)
					socket = new SOAPSecureSocketImp(*m_ctx);
				else
					socket = new SOAPSecureSocketImp();

				if (!socket)
					throw SOAPMemoryException();

				socket->Connect(host, port);

				SOAPProtocolBase::SetSocket(socket);
				if (m_httpproxy)
				{
					char buffer[1024];
					snprintf(buffer, 1024, "CONNECT %s:%d HTTP/1.0",
							(const char *)m_endpoint.Hostname(),
							m_endpoint.Port());
					WriteLine(buffer);
					WriteHostHeader(m_endpoint);
					WriteLine("");

					if (GetReply() != 200)
						throw SOAPException("Error setting up tunnel through proxy: %s",
							(const char *)m_httpmsg);
					//
					// we turn the proxy flag off because at this point
					// we have a connection which looks like a direct
					// connection.  So we don't have to do anything
					// fancy with the GET/POST commands.
					m_httpproxy = false;
				}
			}
			break;
		default:
			throw SOAPSocketException("Can only handle HTTP protocols");
		}
		return IsOpen();
	}

	return true;
}

void
SOAPHTTPProtocol::ParseContentType(SOAPString& contentType, SOAPString& charset, const char *ctype)
{
	//
	// Per some RFC, encoding is us-ascii if it's not
	// specified in HTTP header.
	//
	charset = "US-ASCII";
	contentType = "text/xml";

	if (ctype)
	{
		const char *ct = ctype;
		while (*ct)
		{
			int c = *ct++;
			if (c == ' ' || c == ';' || c == 0)
			{
				contentType = "";
				contentType.Append(ctype, ct - ctype - 1);
				break;
			}
		}


		const char *cs = sp_strstr(ctype, "charset=");
		if (cs)
		{
			cs += 8;
			if (*cs == '\"')
				++cs;
			const char *end = cs;

			while (*end && *end != '\"' && *end != ';' && *end != ' ')
				++end;

			charset = "";
			charset.Append(cs, end - cs);
		}
	}
}

