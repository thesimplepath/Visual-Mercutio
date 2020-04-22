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
// This is a test harness for running interop tests
// with EasySoap++.  For more information on interop
// testing, see:
//
//    http://www.xmethods.net/ilab/ilab.html
//

#ifdef _WIN32
#pragma warning (disable: 4786)
#endif // _WIN32

#include <iostream>
#include <algorithm>

#include <math.h>
#include <time.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

#include <easysoap/SOAP.h>
#include <easysoap/SOAPonHTTP.h>
#include <easysoap/SOAPDebugger.h>
#include <easysoap/SOAPSocket.h>

#include "interopstruct.h"

static const char *default_server = "http://easysoap.sourceforge.net/cgi-bin/interopserver";
static const char *default_server_name = "EasySoap++ at Sourceforge";
static const char *default_interop_namespace = "http://soapinterop.org/";
static const char *default_interop_soapaction = "urn:soapinterop";
static const char *round2_soapaction = "http://soapinterop.org/";


XMLComposer testresults;
bool cgimode = false;

//
// The main library doesn't include iostream,
// so we define an overload to write out
// a SOAPString here....
inline std::ostream&
operator<<(std::ostream& os, const SOAPString& str)
{
	const char *s = str;
	return os << (s ? s : "(null)");
}

inline std::ostream&
operator<<(std::ostream& os, const SOAPQName& name)
{
	return os << name.GetName();
}

double
randdouble()
{
	double f1 = rand();
	double f2 = rand();
	double f3 = (rand() % 40) - 20;
	if (f2 == 0.0)
		return 0.0;
	return f1/f2*pow(10.0, f3);
}

//
// Exception we throw when there is a problem
// with floating point accuracy.
class FPLossException : public SOAPException
{
public:
	FPLossException(float a, float b)
		: SOAPException("Floating point loss: expecting %.9G, got %.9G", a, b)
	{
	}

	FPLossException(double a, double b)
		: SOAPException("Floating point loss: expecting %.18G, got %.18G", a, b)
	{
	}
};

//
// Exception we throw when something passes that
// we're not expecting to...
class UnexpectedSuccessException : public SOAPException
{
public:
	UnexpectedSuccessException(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		FormattedMessage(fmt, args);
		va_end(args);
	}
};


inline bool
almostequal(float a, float b)
{
	if (a != b && fabs(a - b) <= fabs(a) * 0.0000005)
		throw FPLossException(a, b);
	return false;
}

inline bool
almostequal(double a, double b)
{
	if (a != b && fabs(a - b) <= fabs(a) * 0.0000005)
		throw FPLossException(a, b);
	return false;
}

inline bool
almostequal(const SOAPArray<float>& a, const SOAPArray<float>& b)
{
	if (a.Size() != b.Size())
		return false;
	bool retval = true;
	for (size_t i = 0; i < a.Size(); ++i)
	{
		if (!almostequal(a[i], b[i]))
		{
			retval = false;
		}
	}
	return retval;
}


inline bool
almostequal(const SOAPArray<double>& a, const SOAPArray<double>& b)
{
	if (a.Size() != b.Size())
		return false;
	bool retval = true;
	for (size_t i = 0; i < a.Size(); ++i)
	{
		if (!almostequal(a[i], b[i]))
		{
			retval = false;
		}
	}
	return retval;
}


inline bool
almostequal(const SOAPArray<SOAPStruct>& a, const SOAPArray<SOAPStruct>& b)
{
	if (a.Size() != b.Size())
		return false;
	bool retval = true;
	for (size_t i = 0; i < a.Size(); ++i)
	{
		if (a[i] != b[i] && !almostequal(a[i].varFloat, b[i].varFloat))
		{
			retval = false;
		}
	}
	return retval;
}


//
// The struct used to hold endpoint information
//

struct Endpoint
{
	Endpoint() {skip = false;}

	SOAPString name;
	SOAPString wsdl;
	SOAPUrl    endpoint;
	SOAPString soapaction;
	bool	   needsappend;
	SOAPString nspace;
	SOAPString dir;
	bool       skip;

	bool operator<(const Endpoint& p) const
	{
		return name < p.name;
	}
};

const SOAPParameter&
operator>>(const SOAPParameter& param, Endpoint& e)
{
	SOAPString endpoint;
	param.GetParameter("name") >> e.name;
	param.GetParameter("wsdl") >> e.wsdl;
	param.GetParameter("endpoint") >> endpoint; e.endpoint = endpoint;
	param.GetParameter("soapaction") >> e.soapaction;
	e.needsappend = (param.GetParameter("soapactionNeedsMethod").GetInt() != 0);
	param.GetParameter("methodNamespace") >> e.nspace;

	// Try to fix wrong values.
	if (e.nspace == "http://soapinterop.org")
		e.nspace = default_interop_namespace;

	return param;
}

void
GetRound1Endpoints(SOAPArray<Endpoint>& ea)
{
	SOAPProxy proxy("http://www.xmethods.net/perl/soaplite.cgi");
	SOAPMethod getAllEndpoints("getAllEndpoints",
		"http://soapinterop.org/ilab",
		"http://soapinterop.org/ilab#getAllEndpoints");

	//SOAPDebugger::SetFile("r1.log");
	const SOAPResponse& response = proxy.Execute(getAllEndpoints);
	const SOAPParameter& p = response.GetReturnValue();

	for (SOAPParameter::Array::ConstIterator i = p.GetArray().Begin();
			i != p.GetArray().End();
			++i)
	{
		Endpoint& e = ea.Add();
		*(*i) >> e;
		e.skip = false;
	}
}

void
GetRound2Endpoints(SOAPArray<Endpoint>& ea, const char *groupName)
{
	SOAPProxy proxy("http://www.whitemesa.net/interopInfo");
	SOAPMethod getEndpointInfo("GetEndpointInfo",
		"http://soapinterop.org/info/",
		"http://soapinterop.org/info/");

	//SOAPDebugger::SetFile("r2.log");
	getEndpointInfo.AddParameter("groupName") << groupName;

	const SOAPResponse& response = proxy.Execute(getEndpointInfo);
	const SOAPParameter& p = response.GetReturnValue();

	
	SOAPString endpoint;
	for (SOAPParameter::Array::ConstIterator i = p.GetArray().Begin();
			i != p.GetArray().End();
			++i)
	{
		Endpoint& e = ea.Add();
		(*i)->GetParameter("endpointName") >> e.name;
		(*i)->GetParameter("endpointURL") >> endpoint; e.endpoint = endpoint;
		(*i)->GetParameter("wsdlURL") >> e.wsdl;
		e.nspace = default_interop_namespace;
		e.soapaction = round2_soapaction;
		e.skip = false;

		if (e.name == "OpenLink")
			e.skip = true;
		if (e.name == "SilverStream")
			e.skip = true;
	}
}

typedef enum
{
	round1,
	round2a,
	round2b,
	round2c,
	misc
} TestType;


void
SetupMethod(SOAPMethod& method, const char *name, const Endpoint& e)
{
	SOAPString sa = e.soapaction;
	if (e.needsappend)
		sa.Append(name);
	method.SetName(name, e.nspace);
	method.SetSoapAction(sa);
}

/////////////////////////////////////////////////////////////////////////////////
//
// Round 1 + Round 2 base methods
//
////////////////////////////////////////////////////////////////////////////////

void
TestEchoVoid(SOAPProxy& proxy, const Endpoint& e)
{
	SOAPMethod method;
	SetupMethod(method, "echoVoid", e);

	const SOAPResponse& response = proxy.Execute(method);
	if (response.GetBody().GetMethod().GetNumParameters() != 0)
		throw SOAPException("Received unexpected return values.");
}

void
TestEchoString(SOAPProxy& proxy, const Endpoint& e, const char *value)
{
	SOAPString inputValue = value;

	SOAPMethod method;
	SetupMethod(method, "echoString", e);
	method.AddParameter("inputString") << inputValue;

	const SOAPResponse& response = proxy.Execute(method);
	SOAPString outputValue;
	response.GetReturnValue() >> outputValue;
	if (inputValue != outputValue)
		throw SOAPException("Values are not equal");
}

void
TestEchoInteger(SOAPProxy& proxy, const Endpoint& e, int value)
{
	int inputValue = value;

	SOAPMethod method;
	SetupMethod(method, "echoInteger", e);
	method.AddParameter("inputInteger") << inputValue;

	const SOAPResponse& response = proxy.Execute(method);
	int outputValue = 0;
	response.GetReturnValue() >> outputValue;
	if (inputValue != outputValue)
		throw SOAPException("Values are not equal");
}

const SOAPResponse&
TestEchoInteger(SOAPProxy& proxy, const Endpoint& e, const char *value)
{
	SOAPMethod method;
	SetupMethod(method, "echoInteger", e);
	method.AddParameter("inputInteger").SetInt(value);

	return proxy.Execute(method);
}

void
TestEchoIntegerForFail(SOAPProxy& proxy, const Endpoint& e, const char *value)
{
	const SOAPResponse& response = TestEchoInteger(proxy, e, value);
	throw UnexpectedSuccessException("Returned value: %s",
			(const char *)response.GetReturnValue().GetString());
}

void
TestEchoIntegerForPass(SOAPProxy& proxy, const Endpoint& e, const char *value)
{
	const SOAPResponse& response = TestEchoInteger(proxy, e, value);
	int returnValue;
	response.GetReturnValue() >> returnValue;
}

void
TestEchoFloat(SOAPProxy& proxy, const Endpoint& e, float value)
{
	float inputValue = value;

	SOAPMethod method;
	SetupMethod(method, "echoFloat", e);
	SOAPParameter& inputParam = method.AddParameter("inputFloat");
	inputParam << inputValue;

	const SOAPResponse& response = proxy.Execute(method);
	const SOAPParameter& outputParam = response.GetReturnValue();
	float outputValue = 0;
	outputParam >> outputValue;

	if (inputValue != outputValue && !almostequal(inputValue, outputValue))
		throw SOAPException("Values are not equal: %s != %s",
			(const char *)inputParam.GetString(),
			(const char *)outputParam.GetString());
}

void
TestEchoDouble(SOAPProxy& proxy, const Endpoint& e, double value)
{
	double inputValue = value;

	SOAPMethod method;
	SetupMethod(method, "echoDouble", e);
	SOAPParameter& inputParam = method.AddParameter("inputDouble");
	inputParam << inputValue;

	const SOAPResponse& response = proxy.Execute(method);
	const SOAPParameter& outputParam = response.GetReturnValue();
	double outputValue = 0;
	outputParam >> outputValue;

	if (inputValue != outputValue && !almostequal(inputValue, outputValue))
		throw SOAPException("Values are not equal: %s != %s",
			(const char *)inputParam.GetString(),
			(const char *)outputParam.GetString());
}

void
TestEchoDouble(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoDouble(proxy, e, 12445e63);
}

void
TestEchoFloatStringValue(SOAPProxy& proxy, const Endpoint& e, const char *value)
{
	SOAPMethod method;
	SetupMethod(method, "echoFloat", e);
	SOAPParameter& inputParam = method.AddParameter("inputFloat");
	inputParam.SetFloat(value);

	const SOAPResponse& response = proxy.Execute(method);
	if (response.GetReturnValue().GetString() != value)
		throw SOAPException("Wrong return value: %s",
			(const char *)response.GetReturnValue().GetString());
}

const SOAPResponse&
TestEchoFloat(SOAPProxy& proxy, const Endpoint& e, const char *value)
{
	SOAPMethod method;
	SetupMethod(method, "echoFloat", e);
	SOAPParameter& inputParam = method.AddParameter("inputFloat");
	inputParam.SetFloat(value);

	return proxy.Execute(method);
}

void
TestEchoFloatForFail(SOAPProxy& proxy, const Endpoint& e, const char *value)
{
	const SOAPResponse& response = TestEchoFloat(proxy, e, value);
	throw UnexpectedSuccessException("Returned value: %s",
		(const char *)response.GetReturnValue().GetString());
}

void
TestEchoFloatForPass(SOAPProxy& proxy, const Endpoint& e, const char *value)
{
	const SOAPResponse& response = TestEchoFloat(proxy, e, value);
	float result;
	response.GetReturnValue() >> result;
}

void
TestEchoStruct(SOAPProxy& proxy, const Endpoint& e)
{
	SOAPStruct inputValue;
	
	inputValue.varString = "This is a struct string.";
	inputValue.varInt = 68;
	inputValue.varFloat = (float)25.24345356;

	SOAPMethod method;
	SetupMethod(method, "echoStruct", e);
	method.AddParameter("inputStruct") << inputValue;

	const SOAPResponse& response = proxy.Execute(method);
	SOAPStruct outputValue;
	response.GetReturnValue() >> outputValue;
	if (inputValue != outputValue && !almostequal(inputValue.varFloat, outputValue.varFloat))
		throw SOAPException("Values are not equal");
}

void
TestEchoIntegerArray(SOAPProxy& proxy, const Endpoint& e, int numvals)
{
	SOAPArray<int> inputValue;
	SOAPArray<int> outputValue;

	for (int i = 0; i < numvals; ++i)
		inputValue.Add(rand());

	SOAPMethod method;
	SetupMethod(method, "echoIntegerArray", e);
	// Here I call SetArrayType() to make sure that for zero-length
	// arrays the array type is correct.  We have to set it manually
	// for zero length arrays because we can't determine the type from
	// elements in the array!
	SOAPParameter& param = method.AddParameter("inputIntegerArray");
	param << inputValue;

	const SOAPResponse& response = proxy.Execute(method);
	response.GetReturnValue() >> outputValue;
	if (inputValue != outputValue)
		throw SOAPException("Values are not equal");
}


void
TestEchoFloatArray(SOAPProxy& proxy, const Endpoint& e, int numvals)
{
	SOAPArray<float> inputValue;
	for (int i = 0; i < numvals; ++i)
		inputValue.Add((float)randdouble());

	SOAPMethod method;
	SetupMethod(method, "echoFloatArray", e);
	// Here I call SetArrayType() to make sure that for zero-length
	// arrays the array type is correct.  We have to set it manually
	// for zero length arrays because we can't determine the type from
	// elements in the array!
	SOAPParameter& param = method.AddParameter("inputFloatArray");
	param << inputValue;

	const SOAPResponse& response = proxy.Execute(method);

	SOAPArray<float> outputValue;
	response.GetReturnValue() >> outputValue;

	if (inputValue != outputValue && !almostequal(inputValue, outputValue))
		throw SOAPException("Values are not equal");
}


void
TestEchoDoubleArray(SOAPProxy& proxy, const Endpoint& e, int numvals)
{
	SOAPArray<double> inputValue;
	for (int i = 0; i < numvals; ++i)
		inputValue.Add(randdouble());

	SOAPMethod method;
	SetupMethod(method, "echoDoubleArray", e);
	// Here I call SetArrayType() to make sure that for zero-length
	// arrays the array type is correct.  We have to set it manually
	// for zero length arrays because we can't determine the type from
	// elements in the array!
	SOAPParameter& param = method.AddParameter("inputDoubleArray");
	param << inputValue;

	const SOAPResponse& response = proxy.Execute(method);

	SOAPArray<double> outputValue;
	response.GetReturnValue() >> outputValue;

	if (inputValue != outputValue && !almostequal(inputValue, outputValue))
		throw SOAPException("Values are not equal");
}


void
TestEchoStringArray(SOAPProxy& proxy, const Endpoint& e, int numvals)
{
	SOAPArray<SOAPString> inputValue;
	for (int i = 0; i < numvals; ++i)
	{
		char buffer[256];
		sprintf(buffer, "This is test string #%d, rn=%d", i, rand());
		inputValue.Add(buffer);
	}

	SOAPMethod method;
	SetupMethod(method, "echoStringArray", e);
	// Here I call SetArrayType() to make sure that for zero-length
	// arrays the array type is correct.  We have to set it manually
	// for zero length arrays because we can't determine the type from
	// elements in the array!
	SOAPParameter& param = method.AddParameter("inputStringArray");
	param << inputValue;

	const SOAPResponse& response = proxy.Execute(method);
	SOAPArray<SOAPString> outputValue;
	response.GetReturnValue() >> outputValue;
	if (inputValue != outputValue)
		throw SOAPException("Values are not equal");
}


void
TestEchoStructArray(SOAPProxy& proxy, const Endpoint& e, int numvals)
{
	SOAPArray<SOAPStruct> inputValue;
	for (int i = 0; i < numvals; ++i)
	{
		SOAPStruct& val = inputValue.Add();
		char buffer[256];
		sprintf(buffer, "This is struct string #%d, rn=%d", i, rand());
		val.varString = buffer;
		val.varFloat = (float)randdouble();
		val.varInt = rand();
	}

	SOAPMethod method;
	SetupMethod(method, "echoStructArray", e);
	// Here I call SetArrayType() to make sure that for zero-length
	// arrays the array type is correct.  We have to set it manually
	// for zero length arrays because we can't determine the type from
	// elements in the array!
	SOAPParameter& param = method.AddParameter("inputStructArray");
	param << inputValue;

	const SOAPResponse& response = proxy.Execute(method);
	SOAPArray<SOAPStruct> outputValue;
	response.GetReturnValue() >> outputValue;
	if (inputValue != outputValue && !almostequal(inputValue, outputValue))
		throw SOAPException("Values are not equal");
}

void
TestEchoInteger(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoInteger(proxy, e, rand());
}

void
TestEchoInteger_MostPositive(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoInteger(proxy, e, 2147483647);
}

void
TestEchoInteger_MostNegative(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoInteger(proxy, e, -2147483647 - 1);
}

void
TestEchoInteger_Overflow(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoIntegerForFail(proxy, e, "2147483648");
}

void
TestEchoInteger_Underflow(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoIntegerForFail(proxy, e, "-2147483649");
}

void
TestEchoInteger_Junk1(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoIntegerForFail(proxy, e, "1234junk");
}

void
TestEchoInteger_Junk2(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoIntegerForPass(proxy, e, "\r\n\t 1234 \r\n\t");
}

void
TestEchoFloat(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoFloat(proxy, e, 31391236.0);
}

void
TestEchoFloat_NaN(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoFloatStringValue(proxy, e, "NaN");
}

void
TestEchoFloat_INF(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoFloatStringValue(proxy, e, "INF");
}

void
TestEchoFloat_negINF(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoFloatStringValue(proxy, e, "-INF");
}

void
TestEchoFloat_DoubleOverflow(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoFloatForFail(proxy, e, "1.8e308");
}

void
TestEchoFloat_DoubleUnderflow(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoFloatForFail(proxy, e, "2.4e-360");
}

void
TestEchoFloat_SingleOverflow(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoFloatForFail(proxy, e, "3.5e38");
}

void
TestEchoFloat_SingleUnderflow(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoFloatForFail(proxy, e, "6.9e-46");
}

void
TestEchoFloat_Junk1(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoFloatForFail(proxy, e, "1234junk");
}

void
TestEchoFloat_Junk2(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoFloatForPass(proxy, e, "\r\n\t 1234 \r\n\t");
}

void
TestEchoString(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoString(proxy, e, "This is a test string from EasySoap++");
}

void
TestEchoString_newlines(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoString(proxy, e, "This\ris\na\r\ntest\tstring\n\rfrom EasySoap++");
}

void
TestEchoIntegerArray(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoIntegerArray(proxy, e, rand() % 10 + 5);
}

void
TestEchoFloatArray(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoFloatArray(proxy, e, rand() % 10 + 5);
}

void
TestEchoStringArray(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoStringArray(proxy, e, rand() % 10 + 5);
}

void
TestEchoStructArray(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoStructArray(proxy, e, rand() % 10 + 5);
}

void
TestEchoIntegerArrayZeroLen(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoIntegerArray(proxy, e, 0);
}

void
TestEchoFloatArrayZeroLen(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoFloatArray(proxy, e, 0);
}

void
TestEchoStringArrayZeroLen(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoStringArray(proxy, e, 0);
}

void
TestEchoStructArrayZeroLen(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoStructArray(proxy, e, 0);
}

void
TestEchoDoubleArray(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoDoubleArray(proxy, e, rand() % 10 + 5);
}

void
TestEchoDoubleArrayZeroLen(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoDoubleArray(proxy, e, 0);
}

/////////////////////////////////////////////////////////////////////////////////
//
// Additional Round 2 base methods
//
////////////////////////////////////////////////////////////////////////////////

void
TestEchoBooleanJunk(SOAPProxy& proxy, const Endpoint& e)
{
	SOAPMethod method;
	SetupMethod(method, "echoBoolean", e);
	(method.AddParameter("inputBoolean") << "junk").SetType("boolean", XMLSchema2001::xsd);

	const SOAPResponse& response = proxy.Execute(method);

	throw UnexpectedSuccessException("Returned value: %s",
		(const char *)response.GetReturnValue().GetString());
}

void
TestEchoBooleanTrue(SOAPProxy& proxy, const Endpoint& e)
{
	bool val = true;
	SOAPMethod method;
	SetupMethod(method, "echoBoolean", e);
	method.AddParameter("inputBoolean") << val;

	const SOAPResponse& response = proxy.Execute(method);
	response.GetReturnValue() >> val;
	if (!val)
		throw SOAPException("Values are not equal");
}

void
TestEchoBooleanFalse(SOAPProxy& proxy, const Endpoint& e)
{
	bool val = false;
	SOAPMethod method;
	SetupMethod(method, "echoBoolean", e);
	method.AddParameter("inputBoolean") << val;

	const SOAPResponse& response = proxy.Execute(method);
	response.GetReturnValue() >> val;
	if (val)
		throw SOAPException("Values are not equal");
}


/////////////////////////////////////////////////////////////////////////////////
//
// Round 2 Group B methods
//
////////////////////////////////////////////////////////////////////////////////


void
TestEchoNestedStruct(SOAPProxy& proxy, const Endpoint& e)
{
	SOAPStructStruct inputValue;
	
	inputValue.varString = "This is a struct string.";
	inputValue.varInt = 68;
	inputValue.varFloat = (float)25.24345356;
	inputValue.varStruct.varFloat = (float)12.5;
	inputValue.varStruct.varInt = 86;
	inputValue.varStruct.varString = "This is a nested struct.";

	SOAPMethod method;
	SetupMethod(method, "echoNestedStruct", e);
	method.AddParameter("inputStruct") << inputValue;

	const SOAPResponse& response = proxy.Execute(method);
	SOAPStructStruct outputValue;
	response.GetReturnValue() >> outputValue;
	if (inputValue != outputValue && !almostequal(inputValue.varFloat, outputValue.varFloat))
		throw SOAPException("Values are not equal");
}

void
TestEchoNestedArray(SOAPProxy& proxy, const Endpoint& e)
{
	SOAPArrayStruct inputValue;
	
	inputValue.varString = "This is a struct string.";
	inputValue.varInt = 68;
	inputValue.varFloat = 12.5;
	inputValue.varArray.Add() = "This is string 1";
	inputValue.varArray.Add() = "This is string 2";
	inputValue.varArray.Add() = "This is string 3";
	inputValue.varArray.Add() = "This is string 4";

	SOAPMethod method;
	SetupMethod(method, "echoNestedArray", e);
	method.AddParameter("inputStruct") << inputValue;

	const SOAPResponse& response = proxy.Execute(method);
	SOAPArrayStruct outputValue;
	response.GetReturnValue() >> outputValue;
	if (inputValue != outputValue && !almostequal(inputValue.varFloat, outputValue.varFloat))
		throw SOAPException("Values are not equal");
}

void
TestEcho2DStringArray(SOAPProxy& proxy, const Endpoint& e)
{
	SOAPMethod method;
	SetupMethod(method, "echo2DStringArray", e);

	SOAP2DArray<SOAPString> twod, result;

	size_t rows = rand() % 5 + 3;
	size_t cols = rand() % 5 + 3;

	char buff[64];
	twod.Resize(rows, cols);

	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j)
		{
			snprintf(buff, sizeof(buff), "%d,%d", i, j);
			twod[i][j] = buff;
		}

	method.AddParameter("input2DStringArray") << twod;

	const SOAPResponse& response = proxy.Execute(method);
	response.GetReturnValue() >> result;

	if (result != twod)
		throw SOAPException("2D Array values differ.");
}

void
TestEchoStructAsSimpleTypes(SOAPProxy& proxy, const Endpoint& e)
{
	SOAPMethod method;
	SetupMethod(method, "echoStructAsSimpleTypes", e);

	SOAPStruct s;
	s.varString = "This is a test";
	s.varInt = rand() % 10000;
	s.varFloat = (float)randdouble();

	method.AddParameter("inputStruct") << s;

	const SOAPResponse& response = proxy.Execute(method);

	if (response.GetReturnValue("outputString").GetString() != s.varString)
		throw SOAPException("String values are not equal.");

	if (response.GetReturnValue("outputInteger").GetInt() != s.varInt)
		throw SOAPException("Int values are not equal.");

	if (response.GetReturnValue("outputFloat").GetFloat() != s.varFloat)
		throw SOAPException("Float values are not equal.");
}

void
TestEchoSimpleTypesAsStruct(SOAPProxy& proxy, const Endpoint& e)
{
	SOAPMethod method;
	SetupMethod(method, "echoSimpleTypesAsStruct", e);

	SOAPStruct s;
	s.varString = "This is a test";
	s.varInt = rand() % 10000;
	s.varFloat = (float)randdouble();

	method.AddParameter("inputString") << s.varString;
	method.AddParameter("inputInteger") << s.varInt;
	method.AddParameter("inputFloat") << s.varFloat;

	const SOAPResponse& response = proxy.Execute(method);
	SOAPStruct out;
	response.GetReturnValue() >> out;

	if (s != out)
		throw SOAPException("Values are not equal.");
}

void
TestEchoBase64(SOAPProxy& proxy, const Endpoint& e)
{
	SOAPArray<char> inputBinary, outputBinary;

	int size = rand() % 501 + 500;
	inputBinary.Resize(size);
	for (int i = 0; i < size; ++i)
		inputBinary[i] = rand();

	SOAPMethod method;
	SetupMethod(method, "echoBase64", e);
	method.AddParameter("inputBase64") << SOAPBase64(inputBinary);
	const SOAPResponse& response = proxy.Execute(method);

	SOAPBase64 base64(outputBinary);
	response.GetReturnValue() >> base64;

	if (inputBinary != outputBinary)
		throw SOAPException("Values are not equal");
}

/////////////////////////////////////////////////////////////////////////////////
//
// Round 2 Group C methods
//
//
// echoHdrString
// echoHdrStruct
//
// Variations:
//  mustUnderstand = "1", "0"
//  namespace = "http://soapinterop.org/echoheader/", other
//  actor = none (default), next, other
//
/////////////////////////////////////////////////////////////////////////////////

void
TestEchoHdrString(SOAPProxy& proxy, const Endpoint& e,
				  bool mustUnderstand,
				  bool understandable,
				  int actor)
{
	static const char *headerNamespace = "http://soapinterop.org/echoheader/";
	static const char *otherNamespace = "http://other.soapinterop.org/echoheader/";

	SOAPQName headname("echoMeStringRequest", understandable ? headerNamespace : otherNamespace);

	SOAPEnvelope env;
	SOAPParameter& header = env.GetHeader().AddHeader(headname);
	SOAPMethod& method = env.GetBody().GetMethod();

	method.SetName("echoVoid", e.nspace);
	method.SetSoapAction(e.soapaction);

	SOAPString str = "This is a string in the header";
	header << str;


	header.AddAttribute(SOAPEnv::mustUnderstand) = mustUnderstand ? "1" : "0";
	if (actor == 1)
		header.AddAttribute(SOAPEnv::actor) = SOAPHeader::actorNext;
	else if (actor == 2)
		header.AddAttribute(SOAPEnv::actor) = "http://jackandjill.com/wentup/thehill";

	const SOAPResponse& response = proxy.Execute(env);

	if (understandable && actor != 2)
	{
		SOAPQName rheadname("echoMeStringResponse", understandable ? headerNamespace : otherNamespace);
		const SOAPParameter& rhead = response.GetHeader().GetHeader(rheadname);

		SOAPString rstr;
		rhead >> rstr;

		if (rstr != str)
			throw SOAPException("Values are not equal: '%s' and '%s'",
				(const char *)str,
				(const char *)rstr);
	}
}

void
TestEchoHdrStruct(SOAPProxy& proxy, const Endpoint& e,
				  bool mustUnderstand,
				  bool understandable,
				  int actor)
{
	static const char *headerNamespace = "http://soapinterop.org/echoheader/";
	static const char *otherNamespace = "http://other.soapinterop.org/echoheader/";

	SOAPQName headname("echoMeStructRequest", understandable ? headerNamespace : otherNamespace);

	SOAPEnvelope env;
	SOAPParameter& header = env.GetHeader().AddHeader(headname);
	SOAPMethod& method = env.GetBody().GetMethod();

	method.SetName("echoVoid", e.nspace);
	method.SetSoapAction(e.soapaction);

	SOAPStruct str;

	str.varString = "This is a string in the header";
	str.varFloat = (float)randdouble();
	str.varInt = rand();

	header << str;

	header.AddAttribute(SOAPEnv::mustUnderstand) = mustUnderstand ? "1" : "0";
	if (actor == 1)
		header.AddAttribute(SOAPEnv::actor) = SOAPHeader::actorNext;
	else if (actor == 2)
		header.AddAttribute(SOAPEnv::actor) = "http://jackandjill.com/wentup/thehill";

	const SOAPResponse& response = proxy.Execute(env);

	if (understandable && actor != 2)
	{
		SOAPQName rheadname("echoMeStructResponse", understandable ? headerNamespace : otherNamespace);
		const SOAPParameter& rhead = response.GetHeader().GetHeader(rheadname);

		SOAPStruct rstr;
		rhead >> rstr;

		if (rstr != str)
			throw SOAPException("Values are not equal");
	}
}

static bool HeaderMustUnderstand;
static bool HeaderUnderstandable;
static int HeaderActor;

void
TestEchoHdrString(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoHdrString(proxy, e, HeaderMustUnderstand, HeaderUnderstandable, HeaderActor);
}

void
TestEchoHdrStruct(SOAPProxy& proxy, const Endpoint& e)
{
	TestEchoHdrStruct(proxy, e, HeaderMustUnderstand, HeaderUnderstandable, HeaderActor);
}

/////////////////////////////////////////////////////////////////////////////////
//
// Miscellaneous methods
//
/////////////////////////////////////////////////////////////////////////////////

void
TestBogusMethod(SOAPProxy& proxy, const Endpoint& e)
{
	SOAPMethod method;
	SetupMethod(method, "BogusMethod", e);
	proxy.Execute(method);
}

void
TestBogusNamespace(SOAPProxy& proxy, const Endpoint& e)
{
	SOAPMethod method("echoVoid", "http://bogusns.com/", "http://bogusns.com/");
	proxy.Execute(method);
	throw UnexpectedSuccessException("Method executed with bogus namespace.");
}

void
TestMustUnderstand(SOAPProxy& proxy, const Endpoint& e, const char *mu)
{
	SOAPEnvelope mustUnderstand;
	SOAPParameter& header = mustUnderstand.GetHeader().AddHeader();

	header.SetName("Transaction", "uri:my-transaction");
	header.SetValue("5");
	header.AddAttribute(SOAPEnv::mustUnderstand) = mu;

	SOAPMethod& method = mustUnderstand.GetBody().GetMethod();
	method.SetName("echoVoid", e.nspace);
	method.SetSoapAction(e.soapaction);

	proxy.Execute(mustUnderstand);
}

void
TestMustUnderstand_1(SOAPProxy& proxy, const Endpoint& e)
{
	TestMustUnderstand(proxy, e, "1");
}

void
TestMustUnderstand_0(SOAPProxy& proxy, const Endpoint& e)
{
	TestMustUnderstand(proxy, e, "0");
}


BEGIN_EASYSOAP_NAMESPACE

//
// We have to declare the type traits for our map
template<>
class SOAPTypeTraits< SOAPHashMap<SOAPString, int> > : public SOAPMapTypeTraits
{
};

END_EASYSOAP_NAMESPACE

void
TestEchoMap(SOAPProxy& proxy, const Endpoint& e)
{
    SOAPMethod method;
	SetupMethod(method, "echoMap", e);

    SOAPHashMap<SOAPString, int> map, outmap;
    map["one"] = 1;
    map["two"] = 2;
    map["three"] = 3;

    method.AddParameter("inputMap") << map;
    const SOAPResponse& response = proxy.Execute(method);

    response.GetReturnValue() >> outmap;
    if (map.Size() != outmap.Size())
        throw SOAPException("Maps have differing number of values.");
}

void
TestEchoHexBinary(SOAPProxy& proxy, const Endpoint& e)
{
	SOAPArray<char> inputBinary, outputBinary;

	int size = rand() % 501 + 500;
	inputBinary.Resize(size);
	for (int i = 0; i < size; ++i)
		inputBinary[i] = rand();

	SOAPMethod method;
	SetupMethod(method, "echoHexBinary", e);
	method.AddParameter("inputHexBinary") << SOAPHex(inputBinary);
	const SOAPResponse& response = proxy.Execute(method);

	SOAPHex hex(outputBinary);
	response.GetReturnValue() >> hex;

	if (inputBinary != outputBinary)
		throw SOAPException("Values are not equal");
}


/////////////////////////////////////////////////////////////////////////////////



typedef void (*TestFunction)(SOAPProxy&, const Endpoint&);

void
BeginEndpointTesting(const Endpoint& e, TestType test)
{
	if (cgimode)
	{
		std::cout << "<html><head><title>"
			<< "EasySoap++ Interop tests"
			<< "</title></head><body>"
			<< "<h2>EasySoap++ Interop tests</h2>"
			<< "<h3>" << e.name;

		switch (test)
		{
			case round1:
				std::cout << ": Round 1";
				break;
			case round2a:
				std::cout << ": Round 2 Base";
				break;
			case round2b:
				std::cout << ": Round 2 Group B";
				break;
			case round2c:
				std::cout << ": Round 2 Group C";
				break;
			case misc:
				std::cout << ": Miscellaneous";
				break;
		}

		std::cout << "</h3>"
			<< "<table border='1'>"
			<< "<tr><th>Test</th><th>Result</th><th>Message</th></tr>";
	}
	else
	{
		std::cout	<< "      Name: " << e.name << std::endl
					<< "  Endpoint: " << e.endpoint.GetString() << std::endl
					<< " Namespace: " << e.nspace << std::endl
					<< "SOAPAction: " << e.soapaction
					<< (e.needsappend ? "(method)" : "") <<	std::endl
					<< std::endl;
	}
}

void
EndEndpointTesting(const Endpoint& e)
{
	if (cgimode)
	{
		std::cout << "</table></body></html>";
	}
	else
	{
		std::cout
			<< std::endl
			<< "--------------------------------------------------------------"
			<< std::endl
			<< std::endl;
	}
}

void
BeginTest(const Endpoint& e, const char *testname)
{
	char buffer[256];
	snprintf(buffer, sizeof(buffer), "%s/%s.txt",
			(const char *)e.dir, testname);
	bool created = SOAPDebugger::SetFile(buffer);

	if (cgimode)
	{
		std::cout << "<tr><td>";
		if (created)
			std::cout << "<a href='/interoptests/" << e.dir
				<< "/" << testname <<".txt'>" << testname << "</a>";
		else
			std::cout << testname;
		std::cout << "</td>";
	}
	else
	{
		std::cout << "Testing " << testname << ": ";
	}
}

void
EndTest(const Endpoint& e, const SOAPString& type, const SOAPString& msg)
{
	if (cgimode)
	{
		if (type == "PASS")
		{
			std::cout << "<td><font color='green'>" << type << "</font></td>";
			if (msg != "PASS")
				std::cout << "<td>" << msg << "</td></tr>";
			else
				std::cout << "<td></td></tr>";
		}
		else
		{
			std::cout << "<td><font color='red'>" << type << "</font></td>";
			if (msg != "FAIL")
				std::cout << "<td>" << msg << "</td></tr>";
			else
				std::cout << "<td></td></tr>";
		}
		std::cout << std::endl;
		std::cout.flush();
	}
	else
	{
		std::cout << type;
		if (!msg.IsEmpty() && msg != "PASS")
			std::cout << ": " << msg;
		std::cout << std::endl;
	}
}

void
TestForPass(SOAPProxy& proxy, const Endpoint& e, const SOAPString& testname, TestFunction func)
{
	SOAPString type;
	SOAPString msg;

	try
	{
		BeginTest(e, testname);
		func(proxy, e);
		type = "PASS";
		msg = "PASS";
	}
	catch (FPLossException& sex)
	{
		type = "FP LOSS";
		msg = sex.What();
	}
	catch (SOAPSocketException& sex)
	{
		type = "NETWORK ERROR";
		msg = sex.What();
	}
	catch (SOAPFaultException& sex)
	{
		type = "FAULT";
		msg = sex.What();
	}
	catch (SOAPException& sex)
	{
		type = "FAIL";
		msg = sex.What();
	}
	catch (...)
	{
		type = "UNKNOWN";
		msg = "Unknown error, problem with EasySoap++";
	}

	EndTest(e, type, msg);

	testresults.StartTag("Test");
	testresults.AddAttr("name", testname);

	testresults.StartTag("Result");
	testresults.WriteValue(type);
	testresults.EndTag("Result");

	testresults.StartTag("Message");
	testresults.WriteValue(msg);
	testresults.EndTag("Message");

	testresults.EndTag("Test");
}

void
TestForFault(SOAPProxy& proxy, const Endpoint& e, const SOAPString& testname, TestFunction func)
{
	SOAPString type;
	SOAPString msg;
	try
	{
		BeginTest(e, testname);
		func(proxy, e);
		type = "FAIL";
		msg = "FAIL";
	}
	catch (SOAPFaultException& sex)
	{
		type = "PASS";
		msg = sex.What();
	}
	catch (UnexpectedSuccessException& sex)
	{
		type = "FAIL";
		msg = sex.What();
	}
	catch (SOAPSocketException& sex)
	{
		type = "NETWORK ERROR";
		msg = sex.What();
	}
	catch (SOAPException& sex)
	{
		type = "FAIL";
		msg = sex.What();
	}
	catch (...)
	{
		type = "UNKNOWN";
		msg = "Unknown error, problem with EasySoap++";
	}

	EndTest(e, type, msg);

	testresults.StartTag("Test");
	testresults.AddAttr("name", testname);

	testresults.StartTag("Result");
	testresults.WriteValue(type);
	testresults.EndTag("Result");

	testresults.StartTag("Message");
	testresults.WriteValue(msg);
	testresults.EndTag("Message");

	testresults.EndTag("Test");
}

void
TestInterop(const Endpoint& e, TestType test)
{
	SOAPonHTTP transport(e.endpoint);
	transport.SetTimeout(30);
	SOAPProxy proxy(&transport);

	testresults.StartTag("Server");
	testresults.AddAttr("name", e.name);

	testresults.StartTag("Endpoint");
	testresults.WriteValue(e.endpoint.GetString());
	testresults.EndTag("Endpoint");

	testresults.StartTag("SoapAction");
	testresults.WriteValue(e.soapaction);
	testresults.EndTag("SoapAction");

	testresults.StartTag("NameSpace");
	testresults.WriteValue(e.nspace);
	testresults.EndTag("NameSpace");

	if (test == round1 || test == round2a)
	{
	//
	// Round 1
	TestForPass(proxy, e, "echoVoid",					TestEchoVoid);
	TestForPass(proxy, e, "echoInteger",				TestEchoInteger);
	TestForPass(proxy, e, "echoInteger_MostPositive",	TestEchoInteger_MostPositive);
	TestForPass(proxy, e, "echoInteger_MostNegative",	TestEchoInteger_MostNegative);
	TestForFault(proxy, e, "echoInteger_Overflow",		TestEchoInteger_Overflow);
	TestForFault(proxy, e, "echoInteger_Underflow",		TestEchoInteger_Underflow);
	TestForFault(proxy, e, "echoInteger_Junk1"	,		TestEchoInteger_Junk1);
	TestForPass(proxy, e, "echoInteger_Junk2"	,		TestEchoInteger_Junk2);
	TestForPass(proxy, e, "echoFloat",					TestEchoFloat);
	TestForPass(proxy, e, "echoFloat_NaN",				TestEchoFloat_NaN);
	TestForPass(proxy, e, "echoFloat_INF",				TestEchoFloat_INF);
	TestForPass(proxy, e, "echoFloat_negINF",			TestEchoFloat_negINF);
	TestForFault(proxy, e, "echoFloat_SingleOverflow",	TestEchoFloat_SingleOverflow);
	TestForFault(proxy, e, "echoFloat_SingleUnderflow",	TestEchoFloat_SingleUnderflow);
	TestForFault(proxy, e, "echoFloat_DoubleOverflow",	TestEchoFloat_DoubleOverflow);
	TestForFault(proxy, e, "echoFloat_DoubleUnderflow",	TestEchoFloat_DoubleUnderflow);
	TestForFault(proxy, e, "echoFloat_Junk1",			TestEchoFloat_Junk1);
	TestForPass(proxy, e, "echoFloat_Junk2",			TestEchoFloat_Junk2);
	TestForPass(proxy, e, "echoString",					TestEchoString);
	TestForPass(proxy, e, "echoString_newlines",		TestEchoString_newlines);
	TestForPass(proxy, e, "echoStruct",					TestEchoStruct);
	TestForPass(proxy, e, "echoIntegerArray",			TestEchoIntegerArray);
	TestForPass(proxy, e, "echoFloatArray",				TestEchoFloatArray);
	TestForPass(proxy, e, "echoStringArray",			TestEchoStringArray);
	TestForPass(proxy, e, "echoStructArray",			TestEchoStructArray);
	TestForPass(proxy, e, "echoIntegerArray_ZeroLen",	TestEchoIntegerArrayZeroLen);
	TestForPass(proxy, e, "echoFloatArray_ZeroLen",		TestEchoFloatArrayZeroLen);
	TestForPass(proxy, e, "echoStringArray_ZeroLen",	TestEchoStringArrayZeroLen);
	TestForPass(proxy, e, "echoStructArray_ZeroLen",	TestEchoStructArrayZeroLen);

	}

	if (test == round2a)
	{
	//
	// Additional Round 2 base methods
	TestForPass(proxy, e, "echoBase64",					TestEchoBase64);
	TestForPass(proxy, e, "echoBoolean_true",			TestEchoBooleanTrue);
	TestForPass(proxy, e, "echoBoolean_false",			TestEchoBooleanFalse);
	TestForFault(proxy, e, "echoBoolean_junk",			TestEchoBooleanJunk);
	// echoDate
	// echoDecimal
	}

	if (test == round2b)
	{
	//
	// Round 2/Group B methods
	TestForPass(proxy, e, "echoStructAsSimpleTypes",	TestEchoStructAsSimpleTypes);
	TestForPass(proxy, e, "echoSimpleTypesAsStruct",	TestEchoSimpleTypesAsStruct);
	TestForPass(proxy, e, "echo2DStringArray",			TestEcho2DStringArray);
	TestForPass(proxy, e, "echoNestedStruct",			TestEchoNestedStruct);
	TestForPass(proxy, e, "echoNestedArray",			TestEchoNestedArray);
	}

	if (test == round2c)
	{
		//
		// Round 2/Group C methods
		for (int actor = 0; actor < 3; ++actor)
			for (int mu = 0; mu < 2; ++mu)
				for (int und = 0; und < 2; ++und)
				{
					char stringbuff[64];
					char structbuff[64];

					snprintf(stringbuff, sizeof(stringbuff), "echoHdrString mu=%d understandable=%d actor=%s",
						mu, und, (actor == 0 ? "default" : (actor == 1 ? "next" : "other")));

					snprintf(structbuff, sizeof(structbuff), "echoHdrStruct mu=%d understandable=%d actor=%s",
						mu, und, (actor == 0 ? "default" : (actor == 1 ? "next" : "other")));

					HeaderMustUnderstand = (mu != 0);
					HeaderUnderstandable = (und != 0);
					HeaderActor = actor;

					if (!und && mu && actor != 2)
					{
						TestForFault(proxy, e, stringbuff,	TestEchoHdrString);
						TestForFault(proxy, e, structbuff,	TestEchoHdrStruct);
					}
					else
					{
						TestForPass(proxy, e, stringbuff,	TestEchoHdrString);
						TestForPass(proxy, e, structbuff,	TestEchoHdrStruct);
					}
				}

	}

	if (test == misc)
	{
	// Miscellaneous methods
	TestForFault(proxy, e, "BogusMethod",				TestBogusMethod);
	TestForFault(proxy, e, "BogusNamespace",			TestBogusNamespace);
	TestForFault(proxy, e, "MustUnderstand=1",			TestMustUnderstand_1);
	TestForPass(proxy, e, "MustUnderstand=0",			TestMustUnderstand_0);
	TestForPass(proxy, e, "echoMap",					TestEchoMap);
	TestForPass(proxy, e, "echoDouble",					TestEchoDouble);
	TestForPass(proxy, e, "echoDoubleArray",			TestEchoDoubleArray);
	TestForPass(proxy, e, "echoDoubleArray_ZeroLen",	TestEchoDoubleArrayZeroLen);
	TestForPass(proxy, e, "echoHexBinary",				TestEchoHexBinary);
	}

	testresults.EndTag("Server");
}

int
hexval(int c)
{
	switch (c)
	{
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	case 'A': case 'a': return 10;
	case 'B': case 'b': return 11;
	case 'C': case 'c': return 12;
	case 'D': case 'd': return 13;
	case 'E': case 'e': return 14;
	case 'F': case 'f': return 15;
	}
	return 0;
}

char *
hexdecode(char *str)
{
	char *s = str;
	char *w = str;
	while (*w)
	{
		if (*w == '%')
		{
			++w;
			*s++ = (hexval(*w++) << 4) | hexval(*w++);
		}
		else
			*s++ = *w++;
	}
	*s++ = 0;
	return str;
}

void
ParseCGIQuery(SOAPHashMap<SOAPString,SOAPString>& jar, const char *str)
{
	SOAPString query = str;
	char *n = query.Str();
	while (n)
	{
		char *t = n;
		char *v;
		if (n = sp_strchr(n, '&'))
			*n++ = 0;
		if (v = sp_strchr(t, '='))
			*v++ = 0;
		jar[hexdecode(t)] = hexdecode(v);
	}
}

int
main(int argc, char* argv[])
{
	int ret = 0;
	srand(time(0));
	const char *xmlname = 0;
	try
	{
		const char *servicename = 0;
		bool doall = false;
		bool execute = true;
		bool doappend = false;
		bool makedirs = false;
		TestType test = round1;

		SOAPArray<Endpoint> endpoints;
		XMLComposer::SetAddWhiteSpace(true);
		SOAPHashMapNoCase<SOAPString, bool> skips;

		const char *soapaction = default_interop_soapaction;
		const char *nspace = default_interop_namespace;

		for (int i = 1; i < argc;)
		{
			SOAPString val = argv[i++];
			if (val == "-cgi")
			{
				//
				// We're running as a CGI.  Get args
				// from QUERY_STRING
				SOAPHashMap<SOAPString,SOAPString> jar;
				cgimode = true;
				makedirs = true;

				ParseCGIQuery(jar, getenv("QUERY_STRING"));

				const SOAPString& type = jar["type"];
				if (type == "round2a")
					test = round2a;
				else if (type == "round2b")
					test = round2b;
				else if (type == "round2c")
					test = round2c;
				else if (type == "misc")
					test = misc;

				Endpoint& e = endpoints.Add();
				e.endpoint = jar["endpoint"];
				e.name = e.endpoint.Hostname();
				char buff[32];
				sprintf(buff, "%d", rand() % 200);
				e.dir = buff;

				if (test == round1)
				{
					e.nspace = default_interop_namespace;
					e.soapaction = default_interop_soapaction;
					e.needsappend = false;
				}
				else
				{
					e.nspace = default_interop_namespace;
					e.soapaction = round2_soapaction;
					e.needsappend = false;
				}

			}
			else if (val == "-2a")
			{
				test = round2a;
				soapaction = round2_soapaction;
			}
			else if (val == "-2b")
			{
				test = round2b;
				soapaction = round2_soapaction;
			}
			else if (val == "-2c")
			{
				test = round2c;
				soapaction = round2_soapaction;
			}
			else if (val == "-misc")
			{
				test = misc;
			}
			else if (val == "-a")
			{
				doall = true;
			}
			else if (val == "-xml")
			{
				xmlname = argv[i++];
			}
			else if (val == "-l")
			{
				execute = false;
			}
			else if (val == "-a+")
			{
				doappend = true;
			}
			else if (val == "-a-")
			{
				doappend = false;
			}
			else if (val == "-n")
			{
				servicename = argv[i++];
			}
			else if (val == "-ns")
			{
				nspace = argv[++i];
			}
			else if (val == "-sa")
			{
				soapaction = argv[i++];
			}
			else if (val == "-skip")
			{
				skips[argv[i++]] = true;
			}
			else if (val == "-mkdir")
			{
				makedirs = true;
			}
			else if (val[0] == '-')
			{
				throw SOAPException("Unknown commandline argument: %s", (const char *)val);
			}
			else
			{
				Endpoint& e = endpoints.Add();
				e.endpoint = val;
				e.name = servicename ? servicename : (const char *)e.endpoint.Hostname();
				e.nspace = nspace;
				e.soapaction = soapaction;
				e.needsappend = doappend;
				servicename = 0;
			}
		}

		if (doall)
		{
			switch (test)
			{
			case round1:
				GetRound1Endpoints(endpoints);
				break;
			case round2a:
				GetRound2Endpoints(endpoints, "base");
				break;
			case round2b:
				GetRound2Endpoints(endpoints, "GroupB");
				break;
			case round2c:
				GetRound2Endpoints(endpoints, "GroupC");
				break;
			}
		}
		else if (endpoints.Size() == 0)
		{
			// Just test against sourceforge
			Endpoint& e = endpoints.Add();
			e.name = default_server_name;
			e.endpoint = default_server;
			e.nspace = default_interop_namespace;
			e.soapaction = default_interop_soapaction;
			e.needsappend = false;
		}


		char buffer[256];
		time_t ltime = time(0);
		struct tm *ltm = localtime(&ltime);
		strftime(buffer, 256, "%d-%b-%Y %H:%M", ltm);

		testresults.StartTag("InteropTests");
		testresults.StartTag("Date");
		testresults.WriteValue(buffer);
		testresults.EndTag("Date");


		std::sort(endpoints.Begin(), endpoints.End());

		for (size_t j = 0; j < endpoints.Size(); ++j)
		{
			Endpoint& e = endpoints[j];

			if (e.skip)
				continue;

			if (e.dir.IsEmpty())
				e.dir = e.name;

			if (makedirs)
			{
#ifdef _WIN32
				_mkdir(e.dir);
#else
				mkdir(e.dir, 0755);
#endif
			}

			if (execute && !skips.Find(e.name))
			{
				BeginEndpointTesting(e, test);
				TestInterop(e, test);
				EndEndpointTesting(e);
			}
		}

		testresults.EndTag("InteropTests");
	}
	catch (const SOAPMemoryException&)
	{
		std::cerr << "SOAP out of memory." << std::endl;
		ret = -1;
	}
	catch (const SOAPException& ex)
	{
		std::cerr << "Caught SOAP exception: " << ex.What() << std::endl;
		ret = 1;
	}

	if (xmlname)
	{
		FILE *xmlfile = fopen(xmlname, "wb");
		if (xmlfile)
		{
			fwrite(testresults.GetBytes(), 1, testresults.GetLength(), xmlfile);
			fclose(xmlfile);
		}
	}

	SOAPDebugger::Close();
	return ret;
}

