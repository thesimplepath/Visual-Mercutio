// SOAPBuildersInteropHandler.cpp: implementation of the SOAPBuildersInteropHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "SOAPBuildersInteropHandler.h"
#include "interopstruct.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char *
SOAPBuildersInteropHandler::interop_namespace = "http://soapinterop.org/";

SOAPBuildersInteropHandler::SOAPBuildersInteropHandler()
{
	RegisterBasic();
	RegisterArray();
	RegisterMiscellaneous();
}

SOAPBuildersInteropHandler::~SOAPBuildersInteropHandler()
{
}


void
SOAPBuildersInteropHandler::RegisterBasic()
{
	//
	// Round 1
	DispatchMethod("echoVoid",	interop_namespace,
		&SOAPBuildersInteropHandler::echoVoid);

	DispatchMethod("echoInteger",	interop_namespace,
		&SOAPBuildersInteropHandler::echoInteger);

	DispatchMethod("echoFloat",		interop_namespace,
		&SOAPBuildersInteropHandler::echoFloat);

	DispatchMethod("echoDouble",	interop_namespace,
		&SOAPBuildersInteropHandler::echoDouble);

	DispatchMethod("echoString",	interop_namespace,
		&SOAPBuildersInteropHandler::echoString);

	DispatchMethod("echoStruct",	interop_namespace,
		&SOAPBuildersInteropHandler::echoStruct);

	DispatchMethod("echoDate",	interop_namespace,
		&SOAPBuildersInteropHandler::echoDate);

	DispatchMethod("echoBoolean",	interop_namespace,
		&SOAPBuildersInteropHandler::echoBoolean);

	DispatchMethod("echoDecimal",	interop_namespace,
		&SOAPBuildersInteropHandler::echoDecimal);
}


void
SOAPBuildersInteropHandler::echoVoid(const SOAPMethod& req, SOAPMethod& resp)
{
}

void
SOAPBuildersInteropHandler::echoInteger(const SOAPMethod& req, SOAPMethod& resp)
{
	int val;

	req.GetParameter("inputInteger") >> val;

	resp.AddParameter("return") << val;
}

void
SOAPBuildersInteropHandler::echoFloat(const SOAPMethod& req, SOAPMethod& resp)
{
	float val;

	req.GetParameter("inputFloat") >> val;

	resp.AddParameter("return") << val;
}

void
SOAPBuildersInteropHandler::echoDouble(const SOAPMethod& req, SOAPMethod& resp)
{
	double val;

	req.GetParameter("inputDouble") >> val;

	resp.AddParameter("return") << val;
}

void
SOAPBuildersInteropHandler::echoString(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAPString val;

	req.GetParameter("inputString") >> val;

	resp.AddParameter("return") << val;
}

void
SOAPBuildersInteropHandler::echoStruct(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAPStruct val;

	req.GetParameter("inputStruct") >> val;

	resp.AddParameter("return") << val;
}


void
SOAPBuildersInteropHandler::echoDate(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAPString val;

	req.GetParameter("inputDate") >> val;
	// we don't support the type natively so we have to set it.
	(resp.AddParameter("return") << val).SetType("dateTime", XMLSchema2001::xsd);
}


void
SOAPBuildersInteropHandler::echoBoolean(const SOAPMethod& req, SOAPMethod& resp)
{
	bool val;

	req.GetParameter("inputBoolean") >> val;
	resp.AddParameter("return") << val;
}


void
SOAPBuildersInteropHandler::echoDecimal(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAPString val;

	req.GetParameter("inputDecimal") >> val;
	// we don't support the type natively so we have to set it.
	(resp.AddParameter("return") << val).SetType("decimal", XMLSchema2001::xsd);
}


