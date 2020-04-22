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
 * $Id: SOAPMethodHandler.h,v 1.7 2001/11/21 06:00:47 dcrowley Exp $
 */


#if !defined(AFX_SOAPMETHODHANDLER_H__986E8F0F_4214_4C89_A3E6_FA2BD4444667__INCLUDED_)
#define AFX_SOAPMETHODHANDLER_H__986E8F0F_4214_4C89_A3E6_FA2BD4444667__INCLUDED_

#include "SOAPParameterHandler.h"

BEGIN_EASYSOAP_NAMESPACE

class SOAPMethod;

class SOAPMethodHandler   : public SOAPParseEventHandler
{
public:
	SOAPMethodHandler();
	virtual ~SOAPMethodHandler();

	void SetMethod(SOAPMethod&);

	virtual SOAPParseEventHandler* start(SOAPParser& parser, const XML_Char *name, const XML_Char **attrs);
	virtual SOAPParseEventHandler* startElement(SOAPParser& parser, const XML_Char *name, const XML_Char **attrs);

private:
	SOAPMethod				*m_method;
	SOAPParameterHandler	m_paramHandler;
};

END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPMETHODHANDLER_H__986E8F0F_4214_4C89_A3E6_FA2BD4444667__INCLUDED_)

