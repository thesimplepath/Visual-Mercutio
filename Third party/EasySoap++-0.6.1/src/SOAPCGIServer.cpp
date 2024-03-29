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
 * $Id: SOAPCGIServer.cpp,v 1.11 2001/12/20 22:38:19 dcrowley Exp $
 */

#include <easysoap/SOAPCGIServer.h>
#include <easysoap/SOAPCGITransport.h>

USING_EASYSOAP_NAMESPACE

bool
SOAPCGIServer::Handle(const char *infile)
{
	SOAPCGITransport	cgi;
	if (infile)
		cgi.SetInFile(infile);
	return m_dispatch.Handle(cgi);
}


