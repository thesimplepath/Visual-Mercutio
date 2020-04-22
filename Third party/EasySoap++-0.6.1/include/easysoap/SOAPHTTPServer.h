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
 * $Id: SOAPHTTPServer.h,v 1.3 2002/05/20 16:56:11 jgorlick Exp $
 */


#if !defined(AFX_SOAPHTTPSERVERTRANSPORT_H__0A80D352_B75C_411D_9096_7F1CACB82BD1__INCLUDED_)
#define AFX_SOAPHTTPSERVERTRANSPORT_H__0A80D352_B75C_411D_9096_7F1CACB82BD1__INCLUDED_

#include <easysoap/SOAPServer.h>

struct _TServer;
struct _TSession;

BEGIN_EASYSOAP_NAMESPACE

/**
*
*/
class EASYSOAP_EXPORT SOAPHTTPServer : public SOAPServer<SOAPHTTPServer>
{
public:
	SOAPHTTPServer(int port=80);
	~SOAPHTTPServer();

	int Handle();

	void Stop();
	void ResetFlag();
	int IsStopped();

private:

	static int _RequestHandler(struct _TSession *);
	void RequestHandler(struct _TSession *);

	struct _TServer		*m_server;
};

END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPHTTPSERVERTRANSPORT_H__0A80D352_B75C_411D_9096_7F1CACB82BD1__INCLUDED_)

