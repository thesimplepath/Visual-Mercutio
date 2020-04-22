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
 */

//
//  The struct used for interop tests and is shared by
//  the interopclient and interopserver programs.
//

USING_EASYSOAP_NAMESPACE

struct SOAPStruct
{
	SOAPString	varString;
	int			varInt;
	float		varFloat;

	bool operator==(const SOAPStruct& other) const
	{
		return varInt == other.varInt &&
			varFloat == other.varFloat &&
			varString == other.varString;
	}

	bool operator!=(const SOAPStruct& other) const
	{
		return varInt != other.varInt ||
			varFloat != other.varFloat ||
			varString != other.varString;
	}
};

struct SOAPStructStruct
{
	SOAPString	varString;
	int			varInt;
	float		varFloat;
	SOAPStruct	varStruct;

	bool operator==(const SOAPStructStruct& other) const
	{
		return varString == other.varString &&
			varInt == other.varInt &&
			varFloat == other.varFloat &&
			varStruct == other.varStruct;
	}

	bool operator!=(const SOAPStructStruct& other) const
	{
		return varString != other.varString ||
			varInt != other.varInt ||
			varFloat != other.varFloat ||
			varStruct != other.varStruct;
	}
};

struct SOAPArrayStruct
{
	SOAPString				varString;
	int						varInt;
	float					varFloat;
	SOAPArray<SOAPString>	varArray;

	bool operator==(const SOAPArrayStruct& other) const
	{
		return varString == other.varString &&
			varInt == other.varInt &&
			varFloat == other.varFloat &&
			varArray == other.varArray;
	}

	bool operator!=(const SOAPArrayStruct& other) const
	{
		return !(*this == other);
	}
};

BEGIN_EASYSOAP_NAMESPACE

template<>
class SOAPTypeTraits<SOAPStruct>
{
public:
	static void GetType(SOAPQName& qname)
	{
		qname.Set("SOAPStruct", "http://soapinterop.org/xsd");
	}

	static SOAPParameter&
	Serialize(SOAPParameter& param, const SOAPStruct& val)
	{
		param.AddParameter("varString") << val.varString;
		param.AddParameter("varInt") << val.varInt;
		param.AddParameter("varFloat") << val.varFloat;
		return param;
	}

	static const SOAPParameter&
	Deserialize(const SOAPParameter& param, SOAPStruct& val)
	{
		param.GetParameter("varString") >> val.varString;
		param.GetParameter("varInt") >> val.varInt;
		param.GetParameter("varFloat") >> val.varFloat;
		return param;
	}
};

template<>
class SOAPTypeTraits< SOAPArray<SOAPStruct> > : public SOAPArrayTypeTraits
{
};

template<>
class SOAPTypeTraits<SOAPStructStruct>
{
public:
	static void GetType(SOAPQName& qname)
	{
		qname.Set("SOAPStructStruct", "http://soapinterop.org/xsd");
	}

	static SOAPParameter&
	Serialize(SOAPParameter& param, const SOAPStructStruct& val)
	{
		param.AddParameter("varString") << val.varString;
		param.AddParameter("varInt") << val.varInt;
		param.AddParameter("varFloat") << val.varFloat;
		param.AddParameter("varStruct") << val.varStruct;
		return param;
	}

	static const SOAPParameter&
	Deserialize(const SOAPParameter& param, SOAPStructStruct& val)
	{
		param.GetParameter("varString") >> val.varString;
		param.GetParameter("varInt") >> val.varInt;
		param.GetParameter("varFloat") >> val.varFloat;
		param.GetParameter("varStruct") >> val.varStruct;
		return param;
	}
};


template<>
class SOAPTypeTraits<SOAPArrayStruct>
{
public:
	static void GetType(SOAPQName& qname)
	{
		qname.Set("SOAPArrayStruct", "http://soapinterop.org/xsd");
	}

	static SOAPParameter&
	Serialize(SOAPParameter& param, const SOAPArrayStruct& val)
	{
		param.AddParameter("varString") << val.varString;
		param.AddParameter("varInt") << val.varInt;
		param.AddParameter("varFloat") << val.varFloat;
		param.AddParameter("varArray") << val.varArray;
		return param;
	}

	static const SOAPParameter&
	Deserialize(const SOAPParameter& param, SOAPArrayStruct& val)
	{
		param.GetParameter("varString") >> val.varString;
		param.GetParameter("varInt") >> val.varInt;
		param.GetParameter("varFloat") >> val.varFloat;
		param.GetParameter("varArray") >> val.varArray;
		return param;
	}
};

END_EASYSOAP_NAMESPACE



