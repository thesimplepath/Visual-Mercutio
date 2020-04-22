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
 * $Id: SOAPException.h,v 1.4 2002/05/20 16:56:11 jgorlick Exp $
 */


#if !defined(AFX_SOAPEXCEPTION_H__18828772_7674_41DA_A39A_14D5CCB77E75__INCLUDED_)
#define AFX_SOAPEXCEPTION_H__18828772_7674_41DA_A39A_14D5CCB77E75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include <stdarg.h>

#include <easysoap\SOAPString.h>

BEGIN_EASYSOAP_NAMESPACE

/**
* SOAP exception
*/
class EASYSOAP_EXPORT SOAPException
{
protected:
	SOAPString	 m_what;

	SOAPException() {}

	void FormattedMessage(const char *fmt, va_list args)
	{
		char buffer[2048];
		vsnprintf_s(buffer, sizeof(buffer), 1, fmt, args);
		m_what = buffer;
	}

public:
	SOAPException(const SOAPString& what)
		: m_what(what) {}
	SOAPException(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		FormattedMessage(fmt, args);
		va_end(args);
	}

	virtual ~SOAPException() {}

	const SOAPString& What() const {return m_what;}
};

/**
*
*/
class EASYSOAP_EXPORT SOAPMemoryException : public SOAPException
{
public:
	SOAPMemoryException() {}
	~SOAPMemoryException() {}
};

/**
*
*/
class EASYSOAP_EXPORT SOAPSocketException : public SOAPException
{
public:
	SOAPSocketException(const SOAPString& what)
		: SOAPException(what) {}
	SOAPSocketException(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		FormattedMessage(fmt, args);
		va_end(args);
	}
	~SOAPSocketException() {}
};




END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPEXCEPTION_H__18828772_7674_41DA_A39A_14D5CCB77E75__INCLUDED_)

