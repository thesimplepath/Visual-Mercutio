// SOAPBuildersInteropHandler.cpp: implementation of the SOAPBuildersInteropHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "SOAPBuildersInteropHandler.h"
#include "interopstruct.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void
SOAPBuildersInteropHandler::RegisterMiscellaneous()
{
	DispatchMethod("echoBase64",	interop_namespace,
		&SOAPBuildersInteropHandler::echoBase64);

	DispatchMethod("echoSimpleTypesAsStruct",	interop_namespace,
		&SOAPBuildersInteropHandler::echoSimpleTypesAsStruct);

	DispatchMethod("echoStructAsSimpleTypes",	interop_namespace,
		&SOAPBuildersInteropHandler::echoStructAsSimpleTypes);

	DispatchMethod("echoNestedStruct",	interop_namespace,
		&SOAPBuildersInteropHandler::echoNestedStruct);

	DispatchMethod("echoHexBinary",	interop_namespace,
		&SOAPBuildersInteropHandler::echoHexBinary);

	DispatchMethod("echoMap",	interop_namespace,
		&SOAPBuildersInteropHandler::echoMap);

}

void
SOAPBuildersInteropHandler::echoBase64(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAPArray<char> val;
	SOAPBase64 base64(val);

	req.GetParameter("inputBase64") >> base64;
	resp.AddParameter("return") << base64;
}


void
SOAPBuildersInteropHandler::echoHexBinary(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAPArray<char> val;
	SOAPHex hex(val);

	req.GetParameter("inputHexBinary") >> hex;
	resp.AddParameter("return") << hex;
}


void
SOAPBuildersInteropHandler::echoStructAsSimpleTypes(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAPStruct val;
	req.GetParameter("inputStruct") >> val;

	resp.AddParameter("outputString") << val.varString;
	resp.AddParameter("outputInteger") << val.varInt;
	resp.AddParameter("outputFloat") << val.varFloat;
}


void
SOAPBuildersInteropHandler::echoSimpleTypesAsStruct(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAPStruct val;
	req.GetParameter("inputString") >> val.varString;
	req.GetParameter("inputInteger") >> val.varInt;
	req.GetParameter("inputFloat") >> val.varFloat;

	resp.AddParameter("return") << val;
}


void
SOAPBuildersInteropHandler::echoNestedStruct(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAPStructStruct val;
	req.GetParameter("inputStruct") >> val;
	resp.AddParameter("return") << val;
}


BEGIN_EASYSOAP_NAMESPACE
template<>
class SOAPTypeTraits< SOAPHashMap<SOAPString, int> > : public SOAPMapTypeTraits
{
};
END_EASYSOAP_NAMESPACE

void
SOAPBuildersInteropHandler::echoMap(const SOAPMethod& req, SOAPMethod& resp)
{
	SOAPHashMap<SOAPString, int> val;
	req.GetParameter((size_t)0) >> val;
	resp.AddParameter("return") << val;
}



