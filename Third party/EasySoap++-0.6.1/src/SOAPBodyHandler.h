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
 * $Id: SOAPBodyHandler.h,v 1.8 2001/11/30 06:19:54 dcrowley Exp $
 */


#if !defined(AFX_SOAPBODYHANDLER_H__F011566F_10D2_4391_B8C2_C19BA6AFA822__INCLUDED_)
#define AFX_SOAPBODYHANDLER_H__F011566F_10D2_4391_B8C2_C19BA6AFA822__INCLUDED_

#include "SOAPMethodHandler.h"
#include "SOAPParameterHandler.h"

BEGIN_EASYSOAP_NAMESPACE

class SOAPBody;

class SOAPBodyHandler : public SOAPParseEventHandler  
{
public:
	SOAPBodyHandler();
	virtual ~SOAPBodyHandler();

	void SetBody(SOAPBody&);

	virtual SOAPParseEventHandler* start(SOAPParser& parser, const XML_Char *name, const XML_Char **attrs);
	virtual SOAPParseEventHandler* startElement(SOAPParser& parser, const XML_Char *name, const XML_Char **attrs);

private:

	SOAPBody				*m_body;
	bool					m_gotMethod;
	SOAPMethodHandler		m_methodHandler;
	SOAPParameterHandler	m_paramHandler;
};

END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPBODYHANDLER_H__F011566F_10D2_4391_B8C2_C19BA6AFA822__INCLUDED_)

