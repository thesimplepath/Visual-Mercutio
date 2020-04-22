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
 * $Id: SOAPClientSocketImp.h,v 1.10 2002/06/07 19:31:13 kingmob Exp $
 */


#if !defined(AFX_SOAPCLIENTSOCKETIMP_H__7D357522_E8B1_45A2_8CE1_A472A7D58C13__INCLUDED_)
#define AFX_SOAPCLIENTSOCKETIMP_H__7D357522_E8B1_45A2_8CE1_A472A7D58C13__INCLUDED_

#include <easysoap/SOAPSocket.h>

BEGIN_EASYSOAP_NAMESPACE

class SOAPClientSocketImp : public SOAPSocketInterface
{
protected:
//	friend class SOAPSecureSocketImp;
	unsigned int	m_socket;

public:
	SOAPClientSocketImp();
	virtual ~SOAPClientSocketImp();

	unsigned int GetRawSocketHandle() { return m_socket; } ;
	void			Wait(int sec, int usec);
	virtual bool WaitRead(int sec = -1, int usec = 0);
	virtual bool WaitWrite(int sec = -1, int usec = 0);
	virtual bool IsOpen();
	virtual void Close();
	virtual bool Connect(const char *host, unsigned int port);
	virtual size_t Read(char *buffer, size_t len);
	virtual size_t Write(const char *buffer, size_t len);

};

END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPCLIENTSOCKETIMP_H__7D357522_E8B1_45A2_8CE1_A472A7D58C13__INCLUDED_)

