// SOAPBuildersHeaderHandler.h: interface for the SOAPBuildersHeaderHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOAPBUILDERSHEADERHANDLER_H__C0C1D23F_D31D_4118_BB27_C85AB1FA7645__INCLUDED_)
#define AFX_SOAPBUILDERSHEADERHANDLER_H__C0C1D23F_D31D_4118_BB27_C85AB1FA7645__INCLUDED_

#include <easysoap/SOAPDispatchHandler.h>

USING_EASYSOAP_NAMESPACE

//
// See http://www.whitemesa.com/interop.htm
//
class SOAPBuildersHeaderHandler
: public SOAPHeaderHandler<SOAPBuildersHeaderHandler>
{
private:
	static const char *echoHeaderNamespace;

public:
	SOAPBuildersHeaderHandler();
	virtual ~SOAPBuildersHeaderHandler();

	SOAPBuildersHeaderHandler* GetTarget(const SOAPEnvelope& request)
	{
		return this;
	}

	//
	// Group C header handlers
	void echoHdrString(const SOAPParameter& header, SOAPEnvelope& request, SOAPEnvelope& response);
	void echoHdrStruct(const SOAPParameter& header, SOAPEnvelope& request, SOAPEnvelope& response);
};

#endif // !defined(AFX_SOAPBUILDERSHEADERHANDLER_H__C0C1D23F_D31D_4118_BB27_C85AB1FA7645__INCLUDED_)
