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
 * $Id: SOAPServer.h,v 1.3 2002/05/20 16:56:11 jgorlick Exp $
 */


#if !defined(AFX_SOAPSERVER_H__E392FAB3_3022_11D5_B3F3_000000000000__INCLUDED_)
#define AFX_SOAPSERVER_H__E392FAB3_3022_11D5_B3F3_000000000000__INCLUDED_

#include <easysoap/SOAP.h>
#include <easysoap/SOAPServerDispatch.h>
#include <easysoap/SOAPDispatchHandler.h>

BEGIN_EASYSOAP_NAMESPACE

/**
*
*/
template <typename T>
class SOAPServer
{
protected:
	SOAPServer() {}
	~SOAPServer() {}

	SOAPServerDispatch	m_dispatch;

public:
	T& DispatchTo(SOAPDispatchHandlerInterface* disp)
	{
		m_dispatch.DispatchTo(disp);
		return *(T*)this; // Is there a better way to do this?
	}

	T& DispatchTo(SOAPHeaderHandlerInterface* disp)
	{
		m_dispatch.DispatchTo(disp);
		return *(T*)this; // Is there a better way to do this?
	}
};

END_EASYSOAP_NAMESPACE

#endif // AFX_SOAPSERVER_H__E392FAB3_3022_11D5_B3F3_000000000000__INCLUDED_

