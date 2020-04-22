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
 * $Id: SOAPParameter.h,v 1.9 2002/06/26 20:09:45 dcrowley Exp $
 */


#if !defined(AFX_SOAPPARAMETER_H__30811BAD_D6A1_4535_B256_9EEB56A84026__INCLUDED_)
#define AFX_SOAPPARAMETER_H__30811BAD_D6A1_4535_B256_9EEB56A84026__INCLUDED_

#ifdef _MSC_VER
#pragma warning (disable: 4786)
#endif // _MSC_VER

#include <easysoap\SOAP.h>
#include <easysoap\SOAPNamespaces.h>
#include <easysoap\SOAPPool.h>

BEGIN_EASYSOAP_NAMESPACE

class SOAPParameterHandler;

/**
*
*/
class EASYSOAP_EXPORT SOAPParameter
{
public:

	typedef SOAPArray<SOAPParameter*>				Array;
	typedef SOAPHashMap<SOAPString, SOAPParameter*>	Struct;
	typedef SOAPHashMap<SOAPQName, SOAPQName>		Attrs;
	typedef SOAPPool<SOAPParameter> 				Pool;

	SOAPParameter();
	SOAPParameter(const SOAPParameter& param);
	virtual ~SOAPParameter();

	SOAPParameter& operator=(const SOAPParameter& param);


	void Reset();		// clears value and name
	void ClearValue();	// clears just the value

	SOAPQName& GetName()					{return m_name;}
	const SOAPQName& GetName() const		{return m_name;}

	void SetName(const SOAPQName& name)		{m_name = name;}
	void SetName(const char *name, const char *ns = 0);

	void SetType(const char *name, const char *ns = 0);

	void SetValue(bool val);
	void SetBoolean(const char *val);
	void SetValue(int val);
	void SetInt(const char *val);
	void SetValue(float val);
	void SetFloat(const char *val);
	void SetValue(double val);
	void SetDouble(const char *val);

	void SetValue(const char *val);
#ifdef HAVE_WCHART
	void SetValue(const wchar_t *val);
#endif // HAVE_WCHART


	bool GetBoolean() const;

	int GetInt() const;
	operator int() const					{return GetInt();}

	float GetFloat() const;
	operator float() const					{return GetFloat();}

	double GetDouble() const;
	operator double() const					{return GetDouble();}

	const SOAPString& GetString() const;
	operator const SOAPString&() const		{return GetString();}

	Array& GetArray()
	{
		return m_dataPtr->m_array;
	}

	const Array& GetArray() const
	{
		return m_dataPtr->m_array;
	}

	Struct& GetStruct();
	const Struct& GetStruct() const;

	SOAPParameter& AddParameter(const char *name = "item");
	SOAPParameter& AddParameter(const SOAPParameter& p);

	const SOAPParameter& GetParameter(const char *) const;
	const SOAPParameter& GetParameter(size_t i) const
	{
		if (i >= m_dataPtr->m_array.Size())
			throw SOAPException("Array index out of bounds while trying to access  element %u (out of %u) on parameter %s.",
				i, m_dataPtr->m_array.Size(), (const char *)GetName().GetName());
		return *m_dataPtr->m_array[i];
	}

	void SetNull(bool isnull = true);
	void SetIsStruct();

	bool IsNull() const;
	bool IsStruct() const;

	Attrs& GetAttributes() {return m_dataPtr->m_attrs;}
	const Attrs& GetAttributes() const {return m_dataPtr->m_attrs;}
	const Attrs& GetAccessorAttributes() const {return m_x_data.m_attrs;}
	SOAPQName& AddAttribute(const SOAPQName& name);

	//
	// Use this to get access to the underlying string.
	SOAPString& GetStringRef()					{return m_dataPtr->m_strval;}
	const SOAPString& GetStringRef() const		{return m_dataPtr->m_strval;}

	bool WriteSOAPPacket(XMLComposer& packet) const;

	void LinkTo(SOAPParameter& param)
	{
		m_dataPtr = param.m_dataPtr;
	}

private:
	void SetParent(SOAPParameter *parent) {m_parent = parent;}
	void Assign(const SOAPParameter&);
	void CheckStructSync() const;

	class Data
	{
	public:
		Data() : m_isstruct(false), m_outtasync(false) {}
		~Data() {}

		void Clear(Pool&);
		void Assign(SOAPParameter *parent, const Data&);

		bool			m_isstruct;	// true for array, struct types
		SOAPString		m_strval;	// value legal only if m_isstruct == false

		Array			m_array;
		Attrs			m_attrs;
		mutable Struct	m_struct;
		mutable bool	m_outtasync;// true if we need to resynch the hashmap to the array
	private:
		Data& operator=(const Data&);
		Data(const Data&);
	};

	friend class EASYSOAP_NAMESPACE(SOAPParameter::Data);

	Pool			m_pool;
	SOAPParameter	*m_parent;
	SOAPQName		m_name;
	Data			m_x_data;	// Don't use this directly!
	Data			*m_dataPtr;
};

END_EASYSOAP_NAMESPACE

#include <easysoap\SOAPTypeTraits.h>

BEGIN_EASYSOAP_NAMESPACE

template<typename T>
inline SOAPParameter&
operator<<(SOAPParameter& param, const T& val)
{
	//
	// If SOAPTypeTraits<> is undefined for your
	// class then you will have to implement it.
	// Look in SOAPTypeTraits.h for examples.
	//
	param.ClearValue();
	// Add xsi:type attribute
	SOAPTypeTraits<T>::GetType(param.AddAttribute(XMLSchema2001::type));
	// serialize
	return SOAPTypeTraits<T>::Serialize(param, val);
}

template<typename T>
inline const SOAPParameter&
operator>>(const SOAPParameter& param, T& val)
{
	//
	// If SOAPTypeTraits<> is undefined for your
	// class then you will have to implement it.
	// Look in SOAPTypeTraits.h for examples.
	//
	return SOAPTypeTraits<T>::Deserialize(param, val);
}

//
// specialize const char * and const wchar_t * so the
// compiler doesn't get confused thinking it's "char[5]"
// or something like that...
inline SOAPParameter&
operator<<(SOAPParameter& param, const char *val)
{
	param.ClearValue();
	SOAPTypeTraits<const char *>::GetType(param.AddAttribute(XMLSchema2001::type));
	return SOAPTypeTraits<const char *>::Serialize(param, val);
}

#ifdef HAVE_WCHART
inline SOAPParameter&
operator<<(SOAPParameter& param, const wchar_t *val)
{
	param.ClearValue();
	SOAPTypeTraits<const wchar_t *>::GetType(param.AddAttribute(XMLSchema2001::type));
	return SOAPTypeTraits<const wchar_t *>::Serialize(param, val);
}
#endif

END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPPARAMETER_H__30811BAD_D6A1_4535_B256_9EEB56A84026__INCLUDED_)

