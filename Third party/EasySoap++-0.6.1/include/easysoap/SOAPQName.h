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
 * $Id: SOAPQName.h,v 1.3 2002/05/20 16:56:11 jgorlick Exp $
 */


#if !defined(AFX_SOAPQNAME_H__E392FAB3_3022_11D5_B3F3_000000000000__INCLUDED_)
#define AFX_SOAPQNAME_H__E392FAB3_3022_11D5_B3F3_000000000000__INCLUDED_

#include <easysoap\SOAP.h>

BEGIN_EASYSOAP_NAMESPACE

/**
*
*/
class EASYSOAP_EXPORT SOAPQName  
{
public:
	SOAPQName()
	{
	}

	SOAPQName(const char *name, const char *ns = 0)
	{
		Set(name, ns);
	}

	SOAPQName(const SOAPQName& that)
	{
		m_name = that.m_name;
		m_namespace = that.m_namespace;
	}

	~SOAPQName()
	{
	}

	SOAPQName& operator=(const SOAPQName& that)
	{
		m_name = that.m_name;
		m_namespace = that.m_namespace;
		return *this;
	}

	SOAPQName& operator=(const char *name)
	{
		m_name = name;
		m_namespace = (const char *)0;
		return *this;
	}

	void Set(const char *name, const char *ns)
	{
		m_name = name;
		m_namespace = ns;
	}

	bool operator==(const SOAPQName& that) const
	{
		return (m_name.IsEmpty() && that.m_name.IsEmpty() || m_name == that.m_name)
			&& (m_namespace.IsEmpty() && that.m_namespace.IsEmpty() || m_namespace == that.m_namespace);
	}

	bool operator!=(const SOAPQName& that) const
	{
		return !(*this == that);
	}

	bool operator==(const char *name) const
	{
		return m_namespace.IsEmpty() && m_name == name;
	}

	SOAPString& GetName()
	{
		return m_name;
	}

	const SOAPString& GetName() const
	{
		return m_name;
	}

	SOAPString& GetNamespace()
	{
		return m_namespace;
	}

	const SOAPString& GetNamespace() const
	{
		return m_namespace;
	}

	void Clear()
	{
		m_name.Empty();
		m_namespace.Empty();
	}

	bool IsUndefined()
	{
		return m_name.IsEmpty() && m_namespace.IsEmpty();
	}

private:
	SOAPString	m_name;
	SOAPString	m_namespace;
};

/**
*
*/
template <>
struct SOAPHashCodeFunctor<SOAPQName>
{
	size_t operator()(const SOAPQName& val) const
	{
		return sp_hashcode(val.GetName()) ^ sp_hashcode(val.GetNamespace());
	}
};

END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPQNAME_H__E392FAB3_3022_11D5_B3F3_000000000000__INCLUDED_)

