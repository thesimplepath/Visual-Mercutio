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
 * $Id: SOAPSTL.h,v 1.6 2002/05/20 16:56:11 jgorlick Exp $
 */

#ifndef _SOAPSTL_H_
#define _SOAPSTL_H_

//
//
//  This file provides serialization mechanisms
//  for some of the common STL classes
//
//
//  Because many compilers (MSVC 6 included) do not
//  support partial template specialization, you
//  will have to make some simple class declarations
//  so the compiler can figure out how to serialze
//  and deserialize your arrays and maps.
//
//  Example for a std::vector of MyStruct:
//
//  class SOAPTypeTraits<std::vector<MyStruct> >
//   : public SOAPArrayTypeTrais
//   {
//   };
//
//  Example for a std::map:
//
//  class SOAPTypeTraits<std::map<std::string,MyStruct> >
//   : public SOAPSTLMapTypeTrais
//   {
//   };
//

#include <string>
#include <vector>
#include <map>

BEGIN_EASYSOAP_NAMESPACE

/**
*
*/
template<>

class SOAPTypeTraits<std::string>
{
public:
	static void GetType(SOAPQName& type)
	{
		type = XMLSchema2001::string;
	}

	static SOAPParameter& Serialize(SOAPParameter& param, const std::string& val)
	{
		param.SetValue(val.c_str());
		return param;
	}

	static const SOAPParameter& Deserialize(const SOAPParameter& param, std::string& val)
	{
		val = (const char *)param.GetString();
		return param;
	}
};

#ifdef HAVE_PARTIAL_SPECIALIZATION
/**
*
*/
template <typename T>
class SOAPTypeTraits< std::vector<T> > : public SOAPArrayTypeTraits
{
};
#else // DONT HAVE_PARTIAL_SPECIALIZATION
/**
*
*/
template<>

class SOAPTypeTraits< std::vector<bool> > : public SOAPArrayTypeTraits
{
};

/**
*
*/
template<>

class SOAPTypeTraits< std::vector<short> > : public SOAPArrayTypeTraits
{
};

/**
*
*/
template<>

class SOAPTypeTraits< std::vector<int> > : public SOAPArrayTypeTraits
{
};

/**
*
*/
template<>

class SOAPTypeTraits< std::vector<long> > : public SOAPArrayTypeTraits
{
};

/**
*
*/
template<>

class SOAPTypeTraits< std::vector<float> > : public SOAPArrayTypeTraits
{
};

/**
*
*/
template<>

class SOAPTypeTraits< std::vector<double> > : public SOAPArrayTypeTraits
{
};

/**
*
*/
template<>

class SOAPTypeTraits< std::vector<std::string> > : public SOAPArrayTypeTraits
{
};
#endif // HAVE_PARTIAL_SPECIALIZATION


//
// Traits for base64 encoded byte arrays
/**
*
*/
class SOAPSTLBase64 : public SOAPBase64Base
{
public:
	const std::vector<char>*	m_carr;
	std::vector<char>*			m_arr;

	SOAPSTLBase64(const std::vector<char>& carr)
		: m_carr(&carr), m_arr(0)
	{
	}

	SOAPSTLBase64(std::vector<char>& arr)
		: m_carr(0), m_arr(&arr)
	{
	}
private:
	SOAPSTLBase64();
	SOAPSTLBase64(const SOAPSTLBase64&);
	SOAPSTLBase64& operator=(const SOAPSTLBase64&);
};

/**
*
*/
template<>

class SOAPTypeTraits< SOAPSTLBase64 > : public SOAPBase64Traits
{
};


//
// Traits for hex encoded byte arrays
/**
*
*/
class SOAPSTLHex : public SOAPHexBase
{
public:
	const std::vector<char>*	m_carr;
	std::vector<char>*			m_arr;

	SOAPSTLHex(const std::vector<char>& carr) : m_carr(&carr), m_arr(0)
	{
	}

	SOAPSTLHex(std::vector<char>& arr) : m_carr(0), m_arr(&arr)
	{
	}
private:
	SOAPSTLHex();
	SOAPSTLHex(const SOAPSTLHex&);
	SOAPSTLHex& operator=(const SOAPSTLHex&);
};

/**
*
*/
template<>

class SOAPTypeTraits< SOAPSTLHex > : public SOAPHexTraits
{
};

/**
*
*/
class SOAPSTLMapTypeTraits
{
public:
	static void GetType(SOAPQName& type)
	{
		type.Set("Map", "http://xml.apache.org/xml-soap");
	}

	template <typename V>
	static SOAPParameter& Serialize(SOAPParameter& param, const V& val)
	{
		param.SetIsStruct();
		for (MEMBER_TYPE(V::const_iterator) i = val.begin(); i != val.end(); ++i)
		{
			SOAPParameter& p = param.AddParameter();
			p.SetIsStruct();
			p.AddParameter("key") << i->first;
			p.AddParameter("value") << i->second;
		}
		return param;
	}

	template <typename V>
	static const SOAPParameter& Deserialize(const SOAPParameter& param, V& val)
	{
		MEMBER_TYPE(V::key_type) key;
		const SOAPParameter::Array& arr = param.GetArray();
		for (SOAPParameter::Array::ConstIterator i = arr.Begin(); i != arr.End(); ++i)
		{
			(*i)->GetParameter("key") >> key;
			(*i)->GetParameter("value") >> val[key];
		}
		return param;
	}
};

#ifdef HAVE_PARTIAL_SPECIALIZATION
/**
*
*/
template <typename K, typename V>
class SOAPTypeTraits< std::map<K, V> > : public SOAPSTLMapTypeTraits
{
};
#endif // HAVE_PARTIAL_SPECIALIZATION

END_EASYSOAP_NAMESPACE

#endif // _SOAPSTL_H_

