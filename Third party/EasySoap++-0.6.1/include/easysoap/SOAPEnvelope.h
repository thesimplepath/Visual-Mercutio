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
 * $Id: SOAPEnvelope.h,v 1.4 2002/05/20 16:56:11 jgorlick Exp $
 */


#if !defined(AFX_SOAPENVELOPE_H__E0A24A39_4139_4A48_9C59_1DF34800189D__INCLUDED_)
#define AFX_SOAPENVELOPE_H__E0A24A39_4139_4A48_9C59_1DF34800189D__INCLUDED_

#include <easysoap\SOAP.h>

#include <easysoap\SOAPBody.h>
#include <easysoap\SOAPHeader.h>

BEGIN_EASYSOAP_NAMESPACE

/**
*
*/
class EASYSOAP_EXPORT SOAPEnvelope
{
public:
	SOAPEnvelope();
	virtual ~SOAPEnvelope();

	SOAPHeader&			GetHeader()			{return m_header;}
	const SOAPHeader&	GetHeader() const	{return m_header;}

	SOAPBody&			GetBody()			{return m_body;}
	const SOAPBody&		GetBody() const		{return m_body;}

	bool WriteSOAPPacket(XMLComposer& packet) const;

	void Reset()
	{
		m_header.Reset();
		m_body.Reset();
	}

private:

	SOAPHeader	m_header;
	SOAPBody	m_body;
};

END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPENVELOPE_H__E0A24A39_4139_4A48_9C59_1DF34800189D__INCLUDED_)

