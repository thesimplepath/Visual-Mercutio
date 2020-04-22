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
 * $Id: SOAPISAPIServer.cpp,v 1.18 2002/02/13 23:05:49 dcrowley Exp $
 */


#include <easysoap/SOAPISAPIServer.h>
#include <easysoap/SOAPonHTTP.h>

USING_EASYSOAP_NAMESPACE

SOAPISAPITransport::SOAPISAPITransport()
: m_ecb(0), m_ecbData(0), m_error(false), m_leftRead(0), m_doContentType(true)
{	
}

void
SOAPISAPITransport::Initialize(EXTENSION_CONTROL_BLOCK *pECB)
{
	m_ecb = pECB;
	m_ecbData = 0;
	m_error = false;
	m_leftRead = 0;
	m_doContentType = true;
	m_headers.Resize(0);

	if (!m_ecb)
		throw SOAPException("Got null EXTENSION_CONTROL_BLOCK pointer");

	SOAPHTTPProtocol::ParseContentType(m_contentType, m_charset, m_ecb->lpszContentType);
	m_leftRead = m_ecb->cbTotalBytes;

	const char *sa = GetServerInfo("HTTP_SOAPACTION");
	if (sa)
	{
		if (*sa == '\"')
			++sa;
		m_soapaction = sa;
		size_t len = m_soapaction.Length();
		if (len > 0 && m_soapaction[len - 1] == '\"')
			m_soapaction.Str()[len - 1] = 0;
	}
	else
		m_soapaction.Empty();
}

void
SOAPISAPITransport::AddHeader(const char *name, const char *value)
{
	m_headers.Add(name, sp_strlen(name));
	m_headers.Add(": ", 2);
	m_headers.Add(value, sp_strlen(value));
	m_headers.Add("\r\n", 2);
}

const char *
SOAPISAPITransport::GetServerInfo(const char *property)
{
	DWORD bsize = m_buffer.Size();
	if (!m_ecb->GetServerVariable(m_ecb->ConnID, (char *)property, m_buffer, &bsize))
	{
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			m_buffer.Resize(bsize);
			if (!m_ecb->GetServerVariable(m_ecb->ConnID, (char *)property, m_buffer, &bsize))
				return 0;
		}
		else
			return 0;
	}

	return m_buffer;
}

SOAPISAPITransport::~SOAPISAPITransport()
{
}

void
SOAPISAPITransport::SetError()
{
	m_error = true;
}

const char *
SOAPISAPITransport::GetCharset() const
{
	return m_charset;
}

const char *
SOAPISAPITransport::GetContentType() const
{
	return m_contentType;
}

const char *
SOAPISAPITransport::GetSoapAction() const
{
	return m_soapaction;
}

size_t
SOAPISAPITransport::Read(char *buffer, size_t buffsize)
{
	if (sp_strcmp(m_ecb->lpszMethod, "POST"))
	{
		m_error = true;
		throw SOAPException("Invalid HTTP method '%s', only POST is supported.", m_ecb->lpszMethod);
	}

	if (!m_ecb)
		throw SOAPException("Invalid EXTENSION_CONTROL_BLOCK");

	DWORD dwSize = buffsize > m_leftRead ? m_leftRead : buffsize;

	if (m_leftRead > 0)
	{
		if (!m_ecbData)
			m_ecbData = m_ecb->lpbData;

		if (m_ecbData == m_ecb->lpbData + m_ecb->cbAvailable)
		{
			if (m_ecb->cbTotalBytes > m_ecb->cbAvailable)
			{
				if (!m_ecb->ReadClient(m_ecb->ConnID, (void *)buffer, &dwSize))
					throw SOAPException("ReadClient() failed, err=0x%08x",
							GetLastError());
				if (dwSize == 0)
					m_leftRead = 0;
			}
			else
			{
				dwSize = 0;
			}
		}
		else
		{
			if (!m_ecbData)
				m_ecbData = m_ecb->lpbData;
			DWORD remain = m_ecb->lpbData + m_ecb->cbAvailable - m_ecbData;
			if (dwSize > remain)
				dwSize = remain;
			const unsigned char *end = m_ecbData + dwSize;
			while (m_ecbData != end)
				*buffer++ = *m_ecbData++;
		}

		m_leftRead -= dwSize;
	}
	return dwSize;
}

size_t
SOAPISAPITransport::Write(const SOAPMethod&, const char *payload, size_t payloadsize)
{
	return Write(payload, payloadsize);
}

size_t
SOAPISAPITransport::Write(const char *payload, size_t payloadsize)
{
	if (!m_ecb)
		throw SOAPException("Invalid EXTENSION_CONTROL_BLOCK");

	HSE_SEND_HEADER_EX_INFO header;
	DWORD dwSize = payloadsize;
	const char *httpstatus = 0;

	int httpstatuscode = 0;

	if (m_error)
	{
		httpstatus = "500 Internal Server Error";
		httpstatuscode = 500;
	}
	else
	{
		httpstatus = "200 OK";
		httpstatuscode = 200;
	}

	char contentLength[20];
	snprintf(contentLength, sizeof(contentLength), "%u", payloadsize);

	if (m_doContentType)
		AddHeader("Content-Type", "text/xml; charset=\"UTF-8\"");
	AddHeader("Content-Length", contentLength);
	m_headers.Add("\r\n", 3); // terminating null!

	header.pszStatus = httpstatus;
	header.pszHeader = (const char *)m_headers;
	header.cchStatus = sp_strlen(httpstatus);
	header.cchHeader = m_headers.Size();
	header.fKeepConn = TRUE;

	m_ecb->dwHttpStatusCode = httpstatuscode;
	m_ecb->ServerSupportFunction(m_ecb->ConnID, HSE_REQ_SEND_RESPONSE_HEADER_EX, &header, NULL, 0);
	m_ecb->WriteClient(m_ecb->ConnID,
		(void *)payload,
		&dwSize,
// Disable Nagling for IIS >= 5.0
#if HSE_VERSION_MAJOR < 5
		HSE_IO_SYNC | 0x00001000
#else
		HSE_IO_SYNC | HSE_IO_NODELAY
#endif
		);

	return dwSize;
}

bool
SOAPISAPIServer::Handle(SOAPISAPITransport& trans)
{
	return m_dispatch.Handle(trans);
}

int
SOAPISAPIServer::Handle()
{
	unsigned long	pN1, pN2; 
	OVERLAPPED*		pOverLapped;

	SOAPISAPITransport trans;
	while(GetQueuedCompletionStatus(m_ioport, &pN1, &pN2, 
			&pOverLapped, INFINITE))
	{
		if (pOverLapped == (OVERLAPPED*)0xFFFFFFFF)
			break;

		EXTENSION_CONTROL_BLOCK *pECB = (EXTENSION_CONTROL_BLOCK*)pN1;
		DWORD dwState = HSE_STATUS_ERROR;

		if (pECB)
		{
			try
			{
				SOAPISAPIImpersonateUser impersonate(pECB);
				trans.Initialize(pECB);

				if (pN2 == 0)
				{
					if (Handle(trans))
						dwState = HSE_STATUS_SUCCESS;
				}
				else
				{
					// Huh?!?!?
				}
			}
			catch (SOAPException&)
			{
			}
			catch (...)
			{
			}
			//
			// We do this here to ensure that this step is
			// *always* taken care of...
			pECB->ServerSupportFunction(pECB->ConnID, HSE_REQ_DONE_WITH_SESSION, &dwState, NULL, 0);
		}
	}

	return 0;
}

SOAPISAPIImpersonateUser::SOAPISAPIImpersonateUser(EXTENSION_CONTROL_BLOCK *pECB)
: m_ecb(pECB)
{
	if (m_ecb)
	{
		//
		//  Set thread to impersonate
		HANDLE impersonateToken = 0;
		if (m_ecb->ServerSupportFunction(m_ecb->ConnID,
			HSE_REQ_GET_IMPERSONATION_TOKEN,
			&impersonateToken, 0, 0))
		{
			if (!SetThreadToken(NULL, impersonateToken))
			{
				throw SOAPException("Failed to impersonate user.");
			}
		}
	}
}

SOAPISAPIImpersonateUser::~SOAPISAPIImpersonateUser()
{
	if (m_ecb)
	{
		//
		// Clear the thread of any impersonatings it
		// may be doing...
		SetThreadToken(NULL, NULL);
	}
}
