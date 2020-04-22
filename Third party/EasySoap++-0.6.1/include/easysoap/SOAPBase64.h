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
 * $Id: SOAPBase64.h,v 1.3 2002/05/20 16:56:11 jgorlick Exp $
 */


#if !defined(AFX_SOAPBASE64_H__8831A358_2EA1_11D5_B3F3_000000000000__INCLUDED_)
#define AFX_SOAPBASE64_H__8831A358_2EA1_11D5_B3F3_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

BEGIN_EASYSOAP_NAMESPACE

//
// These classes are used to wrap arrays
// so we know how to encode/decode.

//
// Encode/Decode as base64
/**
*
*/
class EASYSOAP_EXPORT SOAPBase64Base
{
public:
	static size_t EstimateSize(const SOAPString& str);
	static void Encode(const char *bytes, size_t byteslen, SOAPString& str);
	static void Decode(const SOAPString& str, char *bytes, size_t& byteslen);

protected:
	SOAPBase64Base() {}

private:
	SOAPBase64Base(const SOAPBase64Base&);
	SOAPBase64Base& operator=(const SOAPBase64Base&);
};

//
// Encode/Decode as hex
/**
*
*/
class EASYSOAP_EXPORT SOAPHexBase
{
public:
	static size_t EstimateSize(const SOAPString& str);
	static void Encode(const char *bytes, size_t byteslen, SOAPString& str);
	static void Decode(const SOAPString& str, char *bytes, size_t& byteslen);

protected:
	SOAPHexBase() {}

private:
	SOAPHexBase(const SOAPHexBase&);
	SOAPHexBase& operator=(const SOAPHexBase&);
};

END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPBASE64_H__8831A358_2EA1_11D5_B3F3_000000000000__INCLUDED_)

