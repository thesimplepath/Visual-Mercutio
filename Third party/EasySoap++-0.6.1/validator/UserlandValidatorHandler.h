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

#if !defined(AFX_USERLANDVALIDATORHANDLER_H__D2938615_0A93_4675_9446_13E981BEF182__INCLUDED_)
#define AFX_USERLANDVALIDATORHANDLER_H__D2938615_0A93_4675_9446_13E981BEF182__INCLUDED_

#include <easysoap/SOAP.h>
#include <easysoap/SOAPDispatchHandler.h>

USING_EASYSOAP_NAMESPACE

class UserlandValidatorHandler :
	public SOAPDispatchHandler<UserlandValidatorHandler>
{
public:
	UserlandValidatorHandler()
	{
		DispatchMethod("countTheEntities",	&UserlandValidatorHandler::countTheEntities);
		DispatchMethod("easyStructTest",	&UserlandValidatorHandler::easyStructTest);
		DispatchMethod("echoStructTest",	&UserlandValidatorHandler::echoStructTest);
		DispatchMethod("manyTypesTest",		&UserlandValidatorHandler::manyTypesTest);
		DispatchMethod("moderateSizeArrayCheck",&UserlandValidatorHandler::moderateSizeArrayCheck);
		DispatchMethod("nestedStructTest",		&UserlandValidatorHandler::nestedStructTest);
		DispatchMethod("simpleStructReturnTest",&UserlandValidatorHandler::simpleStructReturnTest);
	}

	UserlandValidatorHandler* GetTarget(const SOAPEnvelope& request)
	{
		return this;
	}

	void countTheEntities(const SOAPMethod& req, SOAPMethod& resp);
	void easyStructTest(const SOAPMethod& req, SOAPMethod& resp);
	void echoStructTest(const SOAPMethod& req, SOAPMethod& resp);
	void manyTypesTest(const SOAPMethod& req, SOAPMethod& resp);
	void moderateSizeArrayCheck(const SOAPMethod& req, SOAPMethod& resp);
	void nestedStructTest(const SOAPMethod& req, SOAPMethod& resp);
	void simpleStructReturnTest(const SOAPMethod& req, SOAPMethod& resp);


	// The first struct we have to handle
	struct stooges
	{
		int larry;
		int curly;
		int moe;
	};

	// struct we use for the echoStructTest
	// It's just a bunch of stooges
	struct echostruct
	{
		stooges substruct0;
		stooges substruct1;
		stooges substruct2;
		stooges substruct3;
		stooges substruct4;
		stooges substruct5;
		stooges substruct6;
		stooges substruct7;
		stooges substruct8;
		stooges substruct9;
	};
};

// how we de-serialize the stooges struct
inline const SOAPParameter&
operator>>(const SOAPParameter& param, UserlandValidatorHandler::stooges& st)
{
	param.GetParameter("larry") >> st.larry;
	param.GetParameter("curly") >> st.curly;
	param.GetParameter("moe") >> st.moe;
	return param;
}

// how we serialize ths stooges struct;
inline SOAPParameter&
operator<<(SOAPParameter& param, const UserlandValidatorHandler::stooges& st)
{
	param.AddParameter("larry") << st.larry;
	param.AddParameter("curly") << st.curly;
	param.AddParameter("moe") << st.moe;
	param.SetIsStruct();
	return param;
}


// how we de-serialze the echo struct.
// notice how easy it is with operator overloading :)
inline const SOAPParameter&
operator>>(const SOAPParameter& param, UserlandValidatorHandler::echostruct& st)
{
	param.GetParameter("substruct0") >> st.substruct0;
	param.GetParameter("substruct1") >> st.substruct1;
	param.GetParameter("substruct2") >> st.substruct2;
	param.GetParameter("substruct3") >> st.substruct3;
	param.GetParameter("substruct4") >> st.substruct4;
	param.GetParameter("substruct5") >> st.substruct5;
	param.GetParameter("substruct6") >> st.substruct6;
	param.GetParameter("substruct7") >> st.substruct7;
	param.GetParameter("substruct8") >> st.substruct8;
	param.GetParameter("substruct9") >> st.substruct9;
	return param;
}

// and here we serialize it.  It's so easy.
inline SOAPParameter&
operator<<(SOAPParameter& param, const UserlandValidatorHandler::echostruct& st)
{
	param.AddParameter("substruct0") << st.substruct0;
	param.AddParameter("substruct1") << st.substruct1;
	param.AddParameter("substruct2") << st.substruct2;
	param.AddParameter("substruct3") << st.substruct3;
	param.AddParameter("substruct4") << st.substruct4;
	param.AddParameter("substruct5") << st.substruct5;
	param.AddParameter("substruct6") << st.substruct6;
	param.AddParameter("substruct7") << st.substruct7;
	param.AddParameter("substruct8") << st.substruct8;
	param.AddParameter("substruct9") << st.substruct9;
	param.SetIsStruct();
	return param;
}

#endif // !defined(AFX_USERLANDVALIDATORHANDLER_H__D2938615_0A93_4675_9446_13E981BEF182__INCLUDED_)



