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
 * $Id: SOAPWinInetTransport.cpp,v 1.7 2002/05/02 16:35:41 dcrowley Exp $
 */

#ifdef _MSC_VER
#pragma warning (disable: 4786)
#endif // _MSC_VER

#include <easysoap/SOAP.h>
#include <easysoap/SOAPonHTTP.h>
#include <easysoap/SOAPWinInetTransport.h>

#define DEFAULT_USERAGENT EASYSOAP_STRING "/" EASYSOAP_VERSION_STRING

USING_EASYSOAP_NAMESPACE

SOAPWinInetTransport::SOAPWinInetTransport()
: m_keepAlive(true)
, m_hInternet(NULL)
, m_hConnect(NULL)
, m_hRequest(NULL)
, m_canRead(0)
{
}

SOAPWinInetTransport::SOAPWinInetTransport(const SOAPUrl& endpoint)
: m_keepAlive(true)
, m_hInternet(NULL)
, m_hConnect(NULL)
, m_hRequest(NULL)
, m_canRead(0)
{
	ConnectTo(endpoint);
}

SOAPWinInetTransport::SOAPWinInetTransport(const SOAPUrl& endpoint, const SOAPUrl& proxy)
: m_keepAlive(true)
, m_hInternet(NULL)
, m_hConnect(NULL)
, m_hRequest(NULL)
, m_canRead(0)
{
	ConnectTo(endpoint, proxy);
}

SOAPWinInetTransport::~SOAPWinInetTransport()
{
	Close();
}

void
SOAPWinInetTransport::Close()
{
	if (m_hRequest != NULL)
		InternetCloseHandle(m_hRequest);

	if (m_hConnect != NULL)
		InternetCloseHandle(m_hConnect);

	if (m_hInternet != NULL)
		InternetCloseHandle(m_hInternet);
}

void
SOAPWinInetTransport::ConnectTo(const SOAPUrl& endpoint)
{
	Close();
	m_endpoint = endpoint;

	if (m_endpoint.Protocol() != SOAPUrl::http_proto && m_endpoint.Protocol() != SOAPUrl::https_proto)
		throw SOAPSocketException("Invalid protocol specified.  Only http and https are supported.");

	m_hInternet = InternetOpenA(
		m_userAgent.IsEmpty() ? DEFAULT_USERAGENT : (const char *)m_userAgent,
		INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	if (m_hInternet == NULL)
		throw SOAPSocketException("Could not initialize internet connection: %s", GetErrorInfo());
}

void
SOAPWinInetTransport::ConnectTo(const SOAPUrl& endpoint, const SOAPUrl& proxy)
{
	Close();
	m_endpoint = endpoint;

	if (m_endpoint.Protocol() != SOAPUrl::http_proto && m_endpoint.Protocol() != SOAPUrl::https_proto)
		throw SOAPSocketException("Invalid protocol specified.  Only http and https are supported.");

	DWORD ptype = INTERNET_OPEN_TYPE_PRECONFIG;

	char proxystr[256];
	snprintf(proxystr, sizeof(proxystr), "%s:%u",
		(const char *)proxy.Hostname(), proxy.Port());

	m_hInternet = InternetOpenA(
		m_userAgent.IsEmpty() ? DEFAULT_USERAGENT : (const char *)m_userAgent,
		INTERNET_OPEN_TYPE_PROXY,
		proxystr, NULL, 0);

	if (m_hInternet == NULL)
		throw SOAPSocketException("Could not initialize internet connection: %s", GetErrorInfo());

	m_hConnect = InternetConnectA(m_hInternet,
		m_endpoint.Hostname(), m_endpoint.Port(),
		m_endpoint.User(), m_endpoint.Password(),
		INTERNET_SERVICE_HTTP, 0, 0);

	if (m_hConnect == NULL)
		throw SOAPSocketException("Failed to create connection to %s: %s", endpoint, GetErrorInfo());
}

const char *
SOAPWinInetTransport::GetContentType() const
{
	return m_contentType;
}

const char *
SOAPWinInetTransport::GetCharset() const
{
	return m_charset;
}

size_t
SOAPWinInetTransport::Read(char *buffer, size_t bufflen)
{
	DWORD read = 0;

	if (m_canRead != -1 && m_canRead < bufflen)
		bufflen = m_canRead;

	if (!InternetReadFile(m_hRequest, buffer, bufflen, &read))
		throw SOAPSocketException("Failed to read request: %s", GetErrorInfo());

	if (m_canRead != -1)
	{
		if (read > m_canRead)
			throw SOAPException("read > m_canRead");
		m_canRead -= read;
	}

	return read;
}

size_t
SOAPWinInetTransport::Write(const SOAPMethod& method, const char *packet, size_t packetlen)
{
	DWORD cflags = 0;

	if (!m_hConnect)
	{
		m_hConnect = InternetConnectA(m_hInternet,
			m_endpoint.Hostname(), m_endpoint.Port(),
			m_endpoint.User(), m_endpoint.Password(),
			INTERNET_SERVICE_HTTP, 0, 0);
	}

	if (m_hConnect == NULL)
		throw SOAPSocketException("Failed to create connection to %s: %s",
			(const char *)m_endpoint.GetString(), GetErrorInfo());

	if (m_keepAlive)
		cflags |= INTERNET_FLAG_KEEP_CONNECTION;

	if (m_endpoint.Protocol() == SOAPUrl::https_proto)
		cflags |= INTERNET_FLAG_SECURE;

	if (m_hRequest)
		InternetCloseHandle(m_hRequest);

	m_hRequest = HttpOpenRequestA(m_hConnect, "POST",
		m_endpoint.Path(), NULL, NULL, NULL, cflags, 0);
	if (m_hRequest == NULL)
		throw SOAPSocketException("Failed to open request: %s", GetErrorInfo());

	if (m_canRead != -1 && m_canRead > 0)
		throw SOAPException("Didn't finish reading request!");

	bool sentCert = false;
	DWORD dwCode = 0;
	DWORD dwSize = sizeof(dwCode);
	char headers[256];
	if (method.GetSoapAction())
	{
		snprintf(headers, sizeof(headers), "Content-Type: text/xml; charset=\"UTF-8\"\r\n"
			"SOAPAction: \"%s\"\r\n", (const char *)method.GetSoapAction());
	}
	else
	{
		snprintf(headers, sizeof(headers), "Content-Type: text/xml; charset=\"UTF-8\"\r\n"
			"SOAPAction:\r\n");
	}

	BOOL sendSuccess = FALSE;
	do
	{
		sendSuccess = HttpSendRequestA(m_hRequest, headers, -1,
			(void *)packet, packetlen);

		if ( !HttpQueryInfoA(m_hRequest,
			HTTP_QUERY_STATUS_CODE |
			HTTP_QUERY_FLAG_NUMBER, &dwCode, &dwSize, NULL))
		{
			throw SOAPException("Failed to get back server status code.");
		}

		if (!sendSuccess)
		{
			if (sentCert)
			{
				if (dwCode == 403)
				{
					//
					// Okay, we tried once already to send a certificate
					// and it failed.  This means the user hit "cancel"
					throw SOAPException("Endpoint requires a client certificate.");
				}
			}

			DWORD dwError = GetLastError();
			if (dwError == ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED)
			{
				if (InternetErrorDlg(	GetDesktopWindow(),
										m_hRequest,
										ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED,
										FLAGS_ERROR_UI_FILTER_FOR_ERRORS		|
										FLAGS_ERROR_UI_FLAGS_GENERATE_DATA		|
										FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS,
										NULL) != ERROR_SUCCESS )
				{
					throw SOAPException("Failed to select client authentication certificate.");
				}
				sentCert = true;
			}
			else
			{
				throw SOAPSocketException("Failed to send request: %s", GetErrorInfo());
			}
		}
		else
		{
			if (dwCode == HTTP_STATUS_PROXY_AUTH_REQ)
			{
				sendSuccess = FALSE;
				if ( InternetErrorDlg(GetDesktopWindow(),
						m_hRequest, ERROR_INTERNET_INCORRECT_PASSWORD,
						FLAGS_ERROR_UI_FILTER_FOR_ERRORS |
						FLAGS_ERROR_UI_FLAGS_GENERATE_DATA |
						FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS,
						NULL) == ERROR_SUCCESS )
						// this looks wrong but ERROR_SUCCESS is returned if the user cancels
				{
					throw SOAPException("Failed to authenticate with the proxy.");
				}
			}
		}
	} while (!sendSuccess);

	if (dwCode != 500 && dwCode != 200)
	{
		throw SOAPException("Unexpected server response code: %d", dwCode);
	}

	DWORD qsize = sizeof(m_canRead);

	if (!HttpQueryInfo (m_hRequest,
			HTTP_QUERY_CONTENT_LENGTH |
			HTTP_QUERY_FLAG_NUMBER, &m_canRead, &qsize, NULL))
		m_canRead = -1;

	char contenttype[256];
	qsize = sizeof(contenttype);
	if (!HttpQueryInfoA(m_hRequest, HTTP_QUERY_CONTENT_TYPE, contenttype, &qsize, NULL))
		contenttype[0] = 0;
	SOAPHTTPProtocol::ParseContentType(m_contentType, m_charset, contenttype);

	return packetlen;
}

void
SOAPWinInetTransport::SetKeepAlive(bool keepAlive)
{
	m_keepAlive = keepAlive;
}

const char *
SOAPWinInetTransport::GetErrorInfo()
{
	DWORD dwError = GetLastError();
	char errMessage[256]="";

	if (!FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE,
		GetModuleHandleA("wininet.dll"), dwError, 0,
		(LPSTR)errMessage, sizeof(errMessage) - 1, NULL))
	{
		snprintf(errMessage, sizeof(errMessage), "Unspecified error 0x%08x", dwError);
	}

	return m_errorString = errMessage;
}

