// SOAPBuildersInteropHandler.cpp: implementation of the SOAPBuildersInteropHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "SOAPBuildersInteropHandler.h"
#include "interopstruct.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void
SOAPBuildersInteropHandler::RegisterArray()
{
	//
	// Array methods
	DispatchMethod("echoIntegerArray",	interop_namespace,
		&SOAPBuildersInteropHandler::echoIntegerArray);

	DispatchMethod("echoFloatArray",	interop_namespace,
		&SOAPBuildersInteropHandler::echoFloatArray);

	DispatchMethod("echoDoubleArray",	interop_namespace,
		&SOAPBuildersInteropHandler::echoDoubleArray);

	DispatchMethod("echoStringArray",	interop_namespace,
		&SOAPBuildersInteropHandler::echoStringArray);

	DispatchMethod("echoStructArray",	interop_namespace,
		&SOAPBuildersInteropHandler::echoStructArray);

	DispatchMethod("echo2DStringArray",	interop_namespace,
		&SOAPBuildersInteropHandler::echo2DStringArray);

	DispatchMethod("echoNestedArray",	interop_namespace,
		&SOAPBuildersInteropHandler::echoNestedArray);
}


void
SOAPBuildersInteropHandler::echoIntegerArray(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAPArray<int> val;

	req.GetParameter("inputIntegerArray") >> val;

	resp.AddParameter("return") << val;
}

void
SOAPBuildersInteropHandler::echoFloatArray(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAPArray<float> val;

	req.GetParameter("inputFloatArray") >> val;

	resp.AddParameter("return") << val;
}

void
SOAPBuildersInteropHandler::echoDoubleArray(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAPArray<double> val;

	req.GetParameter("inputDoubleArray") >> val;

	resp.AddParameter("return") << val;
}

void
SOAPBuildersInteropHandler::echoStringArray(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAPArray<SOAPString> val;

	req.GetParameter("inputStringArray") >> val;

	resp.AddParameter("return") << val;
}

void
SOAPBuildersInteropHandler::echoStructArray(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAPArray<SOAPStruct> val;

	req.GetParameter("inputStructArray") >> val;

	resp.AddParameter("return") << val;
}


void
SOAPBuildersInteropHandler::echoNestedArray(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAPArrayStruct val;
	req.GetParameter("inputStruct") >> val;
	resp.AddParameter("return") << val;
}


void
SOAPBuildersInteropHandler::echo2DStringArray(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAP2DArray< SOAPString > val;
	req.GetParameter("input2DStringArray") >> val;
	resp.AddParameter("return") << val;
}


