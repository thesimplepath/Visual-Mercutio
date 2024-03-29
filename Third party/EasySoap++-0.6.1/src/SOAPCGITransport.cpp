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
 * $Id: SOAPCGITransport.cpp,v 1.13 2002/03/14 22:33:19 dcrowley Exp $
 */


#include <easysoap/SOAPCGIServer.h>
#include <easysoap/SOAPCGITransport.h>
#include <easysoap/SOAPonHTTP.h>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif // _WIN32

USING_EASYSOAP_NAMESPACE

SOAPCGITransport::SOAPCGITransport()
: m_logfile(0)
, m_infile(0)
, m_canread(-1)
{
#ifdef __BORLANDC__
	setmode(fileno(stdin), O_BINARY);
	setmode(fileno(stdout), O_BINARY);
#else
#ifdef _WIN32
	_setmode(_fileno(stdin), _O_BINARY);
	_setmode(_fileno(stdout), _O_BINARY);
#endif // _WIN32
#endif //__BORLANDC__

	const char *contentlen = getenv("CONTENT_LENGTH");
	if (contentlen)
		m_canread = atoi(contentlen);

	SOAPHTTPProtocol::ParseContentType(m_contentType, m_charset, getenv("CONTENT_TYPE"));

	const char *sa = getenv("HTTP_SOAPACTION");

	if (sa && *sa == '\"')
		++sa;
	m_soapaction = sa;
	size_t len = m_soapaction.Length();
	if (len > 0 && m_soapaction[len - 1] == '\"')
		m_soapaction.Str()[len - 1] = 0;
}

SOAPCGITransport::~SOAPCGITransport()
{
	SetLogFile(0);
	SetInFile(0);
}

//
// Log requests to this file.  Used for debugging
// (copies stdin to this file)
void
SOAPCGITransport::SetLogFile(const char *logfile)
{
	if (m_logfile)
	{
		fclose(m_logfile);
		m_logfile = 0;
	}
	if (logfile)
		m_logfile = fopen(logfile, "ab");
}

//
// Read input from this file.  Used for debugging.
// (reads this file instead of stdin)
void
SOAPCGITransport::SetInFile(const char *infile)
{
	if (m_infile)
	{
		fclose(m_infile);
		m_infile = 0;
	}
	if (infile)
		m_infile = fopen(infile, "rb");
}

void
SOAPCGITransport::SetError()
{
	fprintf(stdout, "Status: 500 Internal Server Error\r\n");
}

const char *
SOAPCGITransport::GetCharset() const
{
	return m_charset;
}

const char *
SOAPCGITransport::GetContentType() const
{
	return m_contentType;
}

const char *
SOAPCGITransport::GetSoapAction() const
{
	return m_soapaction;
}

size_t
SOAPCGITransport::Read(char *buffer, size_t buffsize)
{
	int read = 0;

	if (m_canread == -1 || m_canread > 0)
	{
		if (m_canread != -1 && buffsize > (size_t)m_canread)
			buffsize = m_canread;

		if (m_infile)
			read = fread(buffer, 1, buffsize, m_infile);
		else
			read = fread(buffer, 1, buffsize, stdin);

		if (m_canread != -1)
			m_canread -= read;

		if (read > 0 && m_logfile)
			fwrite(buffer, 1, read, m_logfile);
	}

	return read;
}

size_t
SOAPCGITransport::Write(const SOAPMethod&, const char *payload, size_t payloadsize)
{
	fprintf(stdout, "SOAPServer: %s/%s\r\n", EASYSOAP_STRING, EASYSOAP_VERSION_STRING);
	fprintf(stdout, "Content-Length: %d\r\n", payloadsize);
	fprintf(stdout, "Content-Type: text/xml; charset=\"UTF-8\"\r\n\r\n");

	fwrite(payload, 1, payloadsize, stdout);

	return payloadsize;
}


