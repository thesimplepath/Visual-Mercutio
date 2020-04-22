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
 */

#if !defined(AFX_WHICHTOOLKITHANDLER_H__54C64ECA_7D60_4DD8_B8B4_EEE5EAF4118A__INCLUDED_)
#define AFX_WHICHTOOLKITHANDLER_H__54C64ECA_7D60_4DD8_B8B4_EEE5EAF4118A__INCLUDED_

#include <easysoap/SOAP.h>
#include <easysoap/SOAPDispatchHandler.h>

USING_EASYSOAP_NAMESPACE

class WhichToolkitHandler :
	public SOAPDispatchHandler<WhichToolkitHandler>
{
public:
	WhichToolkitHandler()
	{
		DispatchMethod("whichToolkit", "http://www.soapware.org/", &WhichToolkitHandler::whichToolkit);
	}

	WhichToolkitHandler* GetTarget(const SOAPEnvelope& request)
	{
		return this;
	}

	void whichToolkit(const SOAPMethod& request, SOAPMethod& response);
};

#endif // !defined(AFX_WHICHTOOLKITHANDLER_H__54C64ECA_7D60_4DD8_B8B4_EEE5EAF4118A__INCLUDED_)


