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
 * $Id: SOAPDispatchHandler.h,v 1.4 2002/05/20 16:56:11 jgorlick Exp $
 */


#if !defined(AFX_SOAPDISPATCHHANDLER_H__6D5D16BD_6AE8_48F6_A8FF_D7A56A9CAB34__INCLUDED_)
#define AFX_SOAPDISPATCHHANDLER_H__6D5D16BD_6AE8_48F6_A8FF_D7A56A9CAB34__INCLUDED_

#include <easysoap/SOAP.h>


BEGIN_EASYSOAP_NAMESPACE

/**
*
*/
class EASYSOAP_EXPORT SOAPDispatchHandlerInterface
{
public:
	virtual ~SOAPDispatchHandlerInterface() {}
	virtual bool ExecuteMethod(const SOAPEnvelope& request, SOAPMethod& response) = 0;
};

/**
*
*/
template <typename T>
class SOAPDispatchHandler : public SOAPDispatchHandlerInterface
{
private:
	typedef void (T::*HandlerFunction)(const SOAPMethod& request, SOAPMethod& response);
	typedef SOAPHashMap<SOAPQName, HandlerFunction> DispatchMap;

	SOAPDispatchHandler(const SOAPDispatchHandler&);
	SOAPDispatchHandler& operator=(const SOAPDispatchHandler&);

	DispatchMap	m_dispatchMap;

protected:
	SOAPDispatchHandler()
	{
	}

	bool ExecuteMethod(const SOAPEnvelope& request, SOAPMethod& response)
	{
		const SOAPMethod& method = request.GetBody().GetMethod();
		DispatchMap::Iterator i = m_dispatchMap.Find(method.GetName());
		if (i)
		{
			T *target= GetTarget(request);
			(target->*(*i))(method, response);
			return true;
		}
		return false;
	}

	virtual T* GetTarget(const SOAPEnvelope& request) = 0;

	void DispatchMethod(const char *name, const char *ns, HandlerFunction func)
	{
		m_dispatchMap[SOAPQName(name, ns)] = func;
	}

	void DispatchMethod(const SOAPQName& name, HandlerFunction func)
	{
		m_dispatchMap[name] = func;
	}
};

/**
*
*/
class EASYSOAP_EXPORT SOAPHeaderHandlerInterface
{
public:
	virtual ~SOAPHeaderHandlerInterface() {}
	virtual bool HandleHeader(const SOAPParameter& header, SOAPEnvelope& request, SOAPEnvelope& response) = 0;
};

/**
*
*/
template <typename T>
class SOAPHeaderHandler : public SOAPHeaderHandlerInterface
{
private:
	typedef void (T::*HandlerFunction)(const SOAPParameter& header, SOAPEnvelope& request, SOAPEnvelope& response);
	typedef SOAPHashMap<SOAPQName, HandlerFunction> DispatchMap;

	SOAPHeaderHandler(const SOAPHeaderHandler&);
	SOAPHeaderHandler& operator=(const SOAPHeaderHandler&);

	bool HandleHeader(const SOAPParameter& header, SOAPEnvelope& request, SOAPEnvelope& response)
	{
		DispatchMap::Iterator i = m_dispatchMap.Find(header.GetName());

		if (i)
		{
			T *target= GetTarget(request);
			(target->*(*i))(header, request, response);
			return true;
		}
		return false;
	}

	DispatchMap	m_dispatchMap;

protected:
	SOAPHeaderHandler()
	{
	}

	virtual T* GetTarget(const SOAPEnvelope& request) = 0;

	void DispatchHeader(const char *name, const char *ns, HandlerFunction func)
	{
		m_dispatchMap[SOAPQName(name, ns)] = func;
	}

	void DispatchHeader(const SOAPQName& name, HandlerFunction func)
	{
		m_dispatchMap[name] = func;
	}
};

END_EASYSOAP_NAMESPACE

#endif // !defined(AFX_SOAPDISPATCHHANDLER_H__6D5D16BD_6AE8_48F6_A8FF_D7A56A9CAB34__INCLUDED_)

