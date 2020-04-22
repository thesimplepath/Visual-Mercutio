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
 * $Id: SOAPParameter.cpp,v 1.47 2001/12/20 22:38:19 dcrowley Exp $
 */


#ifdef _MSC_VER
#pragma warning (disable: 4786)
#endif // _MSC_VER

#include <easysoap/SOAP.h>
#include <easysoap/SOAPParameter.h>
#include <easysoap/SOAPNamespaces.h>
#include <easysoap/XMLComposer.h>

USING_EASYSOAP_NAMESPACE

SOAPParameter::SOAPParameter()
: m_parent(0)
, m_dataPtr(&m_x_data)
{
	Reset();
}

SOAPParameter::SOAPParameter(const SOAPParameter& param)
: m_parent(0)
, m_dataPtr(&m_x_data)
{
	Assign(param);
}

SOAPParameter::~SOAPParameter()
{
	for (Array::Iterator i = m_dataPtr->m_array.Begin(); i != m_dataPtr->m_array.End(); ++i)
	{
		(*i)->SetParent(0);
	}
	Reset();
}

void
SOAPParameter::Assign(const SOAPParameter& param)
{
	Reset();
	m_name = param.m_name;
	m_x_data.Assign(this, *param.m_dataPtr);
}


void
SOAPParameter::Data::Assign(SOAPParameter *parent, const Data& d)
{
	m_strval = d.m_strval;
	m_isstruct = d.m_isstruct;
	m_attrs = d.m_attrs;

	const Array& params = d.m_array;
	m_array.Resize(params.Size());
	for (size_t i = 0; i < params.Size(); ++i)
	{
		m_array[i] = parent->m_pool.Get(*params[i]);
		m_array[i]->SetParent(parent);
	}

	m_outtasync = true;
	m_struct.Clear();
}


SOAPParameter&
SOAPParameter::operator=(const SOAPParameter& param)
{
	Reset();
	Assign(param);
	return *this;
}

void
SOAPParameter::ClearValue()
{
	m_dataPtr->Clear(m_pool);
}

void
SOAPParameter::Data::Clear(Pool& pool)
{
	for (Array::Iterator i = m_array.Begin(); i != m_array.End(); ++i)
	{
		(*i)->Reset();
		(*i)->SetParent(0);
		pool.Return(*i);
	}

	m_attrs.Clear();
	m_array.Resize(0);
	m_struct.Clear();
	m_isstruct = false;
	m_outtasync = false;
	m_strval = "";
}

void
SOAPParameter::Reset()
{
	if (m_parent && m_parent->m_dataPtr)
		m_parent->m_dataPtr->m_outtasync = true;
	m_name.GetName().Empty();
	m_name.GetNamespace().Empty();

	m_x_data.Clear(m_pool);
	m_dataPtr = &m_x_data;
}

void
SOAPParameter::SetName(const char *name, const char *ns)
{
	if (!ns)
		m_name = name;
	else
		m_name.Set(name, ns);

	if (m_parent)
		m_parent->m_dataPtr->m_outtasync = true;
}

void
SOAPParameter::SetType(const char *name, const char *ns)
{
	AddAttribute(XMLSchema2001::type).Set(name, ns);
}

bool
SOAPParameter::IsNull() const
{
	Attrs::Iterator null = m_dataPtr->m_attrs.Find(XMLSchema2001::nil);

	if (!null)
		null = m_dataPtr->m_attrs.Find(XMLSchema1999::null);

	if (null && (*null == "true" || *null == "1"))
		return true;

	return false;
}

bool
SOAPParameter::IsStruct() const
{
	return m_dataPtr->m_isstruct;
}

void
SOAPParameter::SetNull(bool isnull)
{
	if (isnull)
		m_dataPtr->m_attrs[XMLSchema2001::nil] = "true";
	else
		m_dataPtr->m_attrs.Remove(XMLSchema2001::nil);
}

void
SOAPParameter::SetIsStruct()
{
	m_dataPtr->m_isstruct = true;
}

SOAPQName&
SOAPParameter::AddAttribute(const SOAPQName& name)
{
	return m_dataPtr->m_attrs[name];
}

void
SOAPParameter::SetValue(const char *val)
{
	SOAPTypeTraits<const char *>::GetType(AddAttribute(XMLSchema2001::type));
	SOAPTypeTraits<const char *>::Serialize(*this, val);
}

#ifdef HAVE_WCHART
void
SOAPParameter::SetValue(const wchar_t *val)
{
	SOAPTypeTraits<const wchar_t *>::GetType(AddAttribute(XMLSchema2001::type));
	SOAPTypeTraits<const wchar_t *>::Serialize(*this, val);
}
#endif

void
SOAPParameter::SetInt(const char *val)
{
	SOAPTypeTraits<int>::GetType(AddAttribute(XMLSchema2001::type));
	SOAPTypeTraits<int>::Serialize(*this, val);
}

void
SOAPParameter::SetFloat(const char *val)
{
	SOAPTypeTraits<float>::GetType(AddAttribute(XMLSchema2001::type));
	SOAPTypeTraits<float>::Serialize(*this, val);
}

void
SOAPParameter::SetDouble(const char *val)
{
	SOAPTypeTraits<double>::GetType(AddAttribute(XMLSchema2001::type));
	SOAPTypeTraits<double>::Serialize(*this, val);
}

void
SOAPParameter::SetValue(int val)
{
	SOAPTypeTraits<int>::GetType(AddAttribute(XMLSchema2001::type));
	SOAPTypeTraits<int>::Serialize(*this, val);
}

void
SOAPParameter::SetValue(float val)
{
	SOAPTypeTraits<float>::GetType(AddAttribute(XMLSchema2001::type));
	SOAPTypeTraits<float>::Serialize(*this, val);
}

void
SOAPParameter::SetValue(double val)
{
	SOAPTypeTraits<double>::GetType(AddAttribute(XMLSchema2001::type));
	SOAPTypeTraits<double>::Serialize(*this, val);
}

void
SOAPParameter::SetBoolean(const char *val)
{
	SOAPTypeTraits<bool>::GetType(AddAttribute(XMLSchema2001::type));
	SOAPTypeTraits<bool>::Serialize(*this, val);
}

void
SOAPParameter::SetValue(bool val)
{
	SOAPTypeTraits<bool>::GetType(AddAttribute(XMLSchema2001::type));
	SOAPTypeTraits<bool>::Serialize(*this, val);
}

const SOAPString&
SOAPParameter::GetString() const
{
	if (IsStruct())
		throw SOAPException("Cannot convert a struct to a string.");

	return m_dataPtr->m_strval;
}

int
SOAPParameter::GetInt() const
{
	int ret;
	SOAPTypeTraits<int>::Deserialize(*this, ret);
	return ret;
}

bool
SOAPParameter::GetBoolean() const
{
	bool ret;
	SOAPTypeTraits<bool>::Deserialize(*this, ret);
	return ret;
}

float
SOAPParameter::GetFloat() const
{
	float ret;
	SOAPTypeTraits<float>::Deserialize(*this, ret);
	return ret;
}

double
SOAPParameter::GetDouble() const
{
	double ret;
	SOAPTypeTraits<double>::Deserialize(*this, ret);
	return ret;
}

const SOAPParameter&
SOAPParameter::GetParameter(const char *name) const
{
	CheckStructSync();
	Struct::Iterator i = m_dataPtr->m_struct.Find(name);
	if (!i)
		throw SOAPException("Could not find element by name: %s", name);
	return **i;
}


SOAPParameter&
SOAPParameter::AddParameter(const char *name)
{
	SOAPParameter *ret = m_pool.Get();
	ret->SetParent(this);
	ret->SetName(name);
	m_dataPtr->m_array.Add(ret);
	m_dataPtr->m_outtasync = true;
	SetIsStruct();

	return *ret;
}

SOAPParameter&
SOAPParameter::AddParameter(const SOAPParameter& p)
{
	SOAPParameter *ret = m_pool.Get(p);
	ret->SetParent(this);
	m_dataPtr->m_array.Add(ret);
	m_dataPtr->m_outtasync = true;
	SetIsStruct();

	return *ret;
}

SOAPParameter::Struct&
SOAPParameter::GetStruct()
{
	CheckStructSync();
	return m_dataPtr->m_struct;
}

const SOAPParameter::Struct&
SOAPParameter::GetStruct() const
{
	CheckStructSync();
	return m_dataPtr->m_struct;
}

void
SOAPParameter::CheckStructSync() const
{
	if (m_dataPtr->m_outtasync)
	{
		m_dataPtr->m_struct.Clear();
		for (Array::ConstIterator i = m_dataPtr->m_array.Begin(); i != m_dataPtr->m_array.End(); ++i)
		{
			m_dataPtr->m_struct[(*i)->GetName().GetName()] = (SOAPParameter *)*i;
		}
		m_dataPtr->m_outtasync = false;
	}
}

bool
SOAPParameter::WriteSOAPPacket(XMLComposer& packet) const
{
	packet.StartTag(m_name);

	for (Attrs::Iterator i = m_dataPtr->m_attrs.Begin(); i != m_dataPtr->m_attrs.End(); ++i)
		packet.AddAttr(i.Key(), i.Item());

	if (IsStruct())
	{
		for (size_t i = 0; i < GetArray().Size(); ++i)
			GetArray()[i]->WriteSOAPPacket(packet);
	}
	else
	{
		packet.WriteValue(m_dataPtr->m_strval);
	}

	packet.EndTag(m_name);

	return true;
}

