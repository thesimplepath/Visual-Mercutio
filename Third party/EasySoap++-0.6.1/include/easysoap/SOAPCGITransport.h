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
 * $Id: SOAPCGITransport.h,v 1.5 2002/05/20 16:56:11 jgorlick Exp $
 */

#if !defined(AFX_SOAPCGITRANSPORT_H__E392FAB3_3022_11D5_B3F3_000000000000__INCLUDED_)
#define AFX_SOAPCGITRANSPORT_H__E392FAB3_3022_11D5_B3F3_000000000000__INCLUDED_

#include <stdio.h>
#include <easysoap/SOAPCGIServer.h>

BEGIN_EASYSOAP_NAMESPACE

//
//
//  A simple Transport class for CGI
//
/**
*
*/
class SOAPCGITransport : public SOAPServerTransport
{
public:
	SOAPCGITransport();
	~SOAPCGITransport();

	void SetError();
	const char *GetCharset() const;
	const char *GetContentType() const;
	const char *GetSoapAction() const;
	size_t Read(char *buffer, size_t buffsize);
	size_t Write(const SOAPMethod& method, const char *payload, size_t payloadsize);

	// Log requests to this file.  Used for debugging
	// (copies stdin to this file)
	void SetLogFile(const char *logfile);
	// Read input from this file.  Used for debugging.
	// (reads this file instead of stdin)
	void SetInFile(const char *infile);

private:

	SOAPCGITransport(const SOAPCGITransport&);
	SOAPCGITransport& operator=(const SOAPCGITransport&);

	FILE		*m_logfile;
	FILE		*m_infile;
	int			m_canread;
	SOAPString	m_charset;
	SOAPString	m_contentType;
	SOAPString	m_soapaction;
};

END_EASYSOAP_NAMESPACE

#endif // AFX_SOAPCGITRANSPORT_H__E392FAB3_3022_11D5_B3F3_000000000000__INCLUDED_

