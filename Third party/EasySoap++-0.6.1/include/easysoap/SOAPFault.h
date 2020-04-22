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
 * $Id: SOAPFault.h,v 1.4 2002/05/20 16:56:11 jgorlick Exp $
 */


#if !defined(AFX_SOAPFAULT_H__290FC204_F572_4249_8E5E_D52E987FFAD0__INCLUDED_)
#define AFX_SOAPFAULT_H__290FC204_F572_4249_8E5E_D52E987FFAD0__INCLUDED_

#include <easysoap\SOAP.h>
#include <easysoap\SOAPParameter.h>

BEGIN_EASYSOAP_NAMESPACE

class SOAPFaultHandler;

/**
*
*/
class EASYSOAP_EXPORT SOAPFault : public SOAPParameter
{
public:
	friend class SOAPFaultHandler;

	SOAPFault();
	virtual ~SOAPFault();

	void SetFaultCode(const char *faultcode)
	{
		AddFaultCode().SetValue(faultcode);
	}

	void SetFaultString(const char *faultstring)
	{
		AddFaultString().SetValue(faultstring);
	}

	void SetFaultActor(const char *faultactor)
	{
		AddFaultActor().SetValue(faultactor);
	}

	SOAPParameter& AddFaultCode()
	{
		return AddParameter(faultcode_attr);
	}

	SOAPParameter& AddFaultString()
	{
		return AddParameter(faultstring_attr);
	}

	SOAPParameter& AddFaultActor()
	{
		return AddParameter(faultactor_attr);
	}

	SOAPParameter& AddFaultDetail()
	{
		return AddParameter(faultdetail_attr);
	}

	const SOAPParameter* GetFaultString() const;
	const SOAPParameter* GetFaultActor() const;
	const SOAPParameter* GetFaultCode() const;
	const SOAPParameter* GetDetail() const;

private:
	static const SOAPString faultcode_attr;
	static const SOAPString faultstring_attr;
	static const SOAPString faultactor_attr;
	static const SOAPString faultdetail_attr;
};

/**
*
*/
class SOAPFaultException : public SOAPException
{
private:
	SOAPFault	m_fault;

public:
	SOAPFaultException(const SOAPFault&);
	const SOAPFault& GetFault() const {return m_fault;}
};

END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPFAULT_H__290FC204_F572_4249_8E5E_D52E987FFAD0__INCLUDED_)

