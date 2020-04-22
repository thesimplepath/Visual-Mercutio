// SOAPBuildersHeaderHandler.cpp: implementation of the SOAPBuildersHeaderHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "SOAPBuildersHeaderHandler.h"
#include "interopstruct.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char *SOAPBuildersHeaderHandler::echoHeaderNamespace ="http://soapinterop.org/echoheader/";

SOAPBuildersHeaderHandler::SOAPBuildersHeaderHandler()
{
	DispatchHeader("echoMeStringRequest", echoHeaderNamespace,
			&SOAPBuildersHeaderHandler::echoHdrString);

	DispatchHeader("echoMeStructRequest", echoHeaderNamespace,
			&SOAPBuildersHeaderHandler::echoHdrStruct);
}

SOAPBuildersHeaderHandler::~SOAPBuildersHeaderHandler()
{
}

void
SOAPBuildersHeaderHandler::echoHdrString(const SOAPParameter& header,
										 SOAPEnvelope& request,
										 SOAPEnvelope& response)
{
	SOAPString str;
	header >> str;

	SOAPParameter& resph = response.GetHeader().AddHeader();
	resph.SetName("echoMeStringResponse", echoHeaderNamespace);
	
	resph << str;
}

void
SOAPBuildersHeaderHandler::echoHdrStruct(const SOAPParameter& header,
										 SOAPEnvelope& request,
										 SOAPEnvelope& response)
{
	SOAPStruct str;
	header >> str;

	SOAPParameter& resph = response.GetHeader().AddHeader();
	resph.SetName("echoMeStructResponse", echoHeaderNamespace);
	
	resph << str;
}



