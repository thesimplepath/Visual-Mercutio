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
 * $Id: SOAPTransport.h,v 1.5 2002/05/20 16:56:11 jgorlick Exp $
 */


#if !defined(AFX_SOAPTRANSPORT_H__7D357522_E8B1_45A2_8CE1_A472A7D58C13__INCLUDED_)
#define AFX_SOAPTRANSPORT_H__7D357522_E8B1_45A2_8CE1_A472A7D58C13__INCLUDED_

#include <easysoap/SOAP.h>

BEGIN_EASYSOAP_NAMESPACE

class SOAPMethod;

/**
*
*/
class EASYSOAP_EXPORT SOAPTransport
{
private:
	SOAPTransport(const SOAPTransport&);
	SOAPTransport& operator=(const SOAPTransport&);

protected:
	SOAPTransport() {}

public:
	virtual ~SOAPTransport() {}
	//
	//  Return charset if known otherwise null
	virtual const char *GetCharset() const = 0;

	//
	//  Return charset if known otherwise null
	virtual const char *GetContentType() const = 0;

	// read the payload into the buffer.
	// can be called multiple times.
	// returns 0 if entire payload has been read.
	virtual size_t Read(char *buffer, size_t buffsize) = 0;

	// send the payload.  can only be called ONCE per
	// payload. 
	virtual size_t Write(const SOAPMethod& method, const char *payload, size_t payloadsize) = 0;
};

/**
*
*/
class EASYSOAP_EXPORT SOAPServerTransport : public SOAPTransport
{
private:
	SOAPServerTransport(const SOAPServerTransport&);
	SOAPServerTransport& operator=(const SOAPServerTransport&);

protected:
	SOAPServerTransport() {}

public:
	virtual ~SOAPServerTransport() {}

	virtual const char *GetSoapAction() const = 0;

	virtual void SetError() = 0;
};

END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPTRANSPORT_H__7D357522_E8B1_45A2_8CE1_A472A7D58C13__INCLUDED_)

