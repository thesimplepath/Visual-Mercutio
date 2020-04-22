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

#include "UserlandValidatorHandler.h"

//
// validator1.countTheEntities (s)
// returns struct
//
//
// This handler takes a single parameter named s, a string,
// that contains any number of predefined entities, namely <, >,
// &, ' and ".
//
// Your handler must return a struct that contains five fields,
// all numbers: ctLeftAngleBrackets, ctRightAngleBrackets,
// ctAmpersands, ctApostrophes, ctQuotes. 
//
// To validate, the numbers must be correct.
//

void
UserlandValidatorHandler::countTheEntities(const SOAPMethod& req, SOAPMethod& resp)
{
	const SOAPString& s = req.GetParameter("s").GetString();
	const char *str = s;

	int ctAmpersands = 0;
	int ctApostrophes = 0;
	int ctLeftAngleBrackets = 0;
	int ctQuotes = 0;
	int ctRightAngleBrackets = 0;

	while (*str)
	{
		switch (*str++)
		{
		case '&':
			++ctAmpersands;
			break;
		case '\'':
			++ctApostrophes;
			break;
		case '\"':
			++ctQuotes;
			break;
		case '<':
			++ctLeftAngleBrackets;
			break;
		case '>':
			++ctRightAngleBrackets;
			break;
		default:
			break;
		}
	}

	SOAPParameter& result = resp.AddParameter("Result");
	result.AddParameter("ctAmpersands") << ctAmpersands;
	result.AddParameter("ctApostrophes") << ctApostrophes;
	result.AddParameter("ctLeftAngleBrackets") << ctLeftAngleBrackets;
	result.AddParameter("ctQuotes") << ctQuotes;
	result.AddParameter("ctRightAngleBrackets") << ctRightAngleBrackets;
	result.SetIsStruct();
}

//
//
// validator1.easyStructTest (stooges)
// returns number
//
// This handler takes a single parameter named stooges, a struct,
// containing at least three elements named moe, larry and curly,
// all ints. Your handler must add the three numbers and return
// the result.
//

void
UserlandValidatorHandler::easyStructTest(const SOAPMethod& req, SOAPMethod& resp)
{
	stooges st;
	const SOAPParameter& p = req.GetParameter("stooges");

	p >> st;

	int sum = st.moe + st.curly + st.larry;

	resp.AddParameter("Result") << sum;
}


//
// validator1.echoStructTest (myStruct)
// returns struct
//
//
// This handler takes a single parameter named myStruct, a
// struct. Your handler must return the struct.
//


//
// Now lets do it!
//
void
UserlandValidatorHandler::echoStructTest(const SOAPMethod& req, SOAPMethod& resp)
{
	echostruct st;
	const SOAPParameter& p = req.GetParameter("myStruct");

	p >> st;

	resp.AddParameter("Result") << st;
}

//
// validator1.manyTypesTest (num, bool, state, doub, dat, bin)
// returns array
//
//
// This handler takes six parameters and returns an array containing
// all the parameters.
//


void
UserlandValidatorHandler::manyTypesTest(const SOAPMethod& req, SOAPMethod& resp)
{
	int			num;
	bool		b;
	SOAPString	state;
	double		doub;
	SOAPString	dat;
	SOAPString	bin;

	req.GetParameter("num") >> num;
	req.GetParameter("bool") >> b;
	req.GetParameter("state") >> state;
	req.GetParameter("doub") >> doub;
	req.GetParameter("dat") >> dat;
	req.GetParameter("bin") >> bin;

	SOAPParameter& result = resp.AddParameter("Result");

	// This is ugly.  Really ugly.  Because the validator
	// demands 1999 schema, we have to set everything manually...
	SOAPQName	type1999("type", XMLSchema1999::xsi);


	SOAPTypeTraits<int>::Serialize(result.AddParameter(), num)
		.AddAttribute(type1999).Set("int", XMLSchema1999::xsd);

	SOAPTypeTraits<bool>::Serialize(result.AddParameter(), b)
		.AddAttribute(type1999).Set("boolean", XMLSchema1999::xsd);

	SOAPTypeTraits<SOAPString>::Serialize(result.AddParameter(), state)
		.AddAttribute(type1999).Set("string", XMLSchema1999::xsd);

	// The validator is wrong.  It wants double accuracy but wire type is float
	SOAPTypeTraits<double>::Serialize(result.AddParameter(), doub)
		.AddAttribute(type1999).Set("float", XMLSchema1999::xsd);

	SOAPTypeTraits<SOAPString>::Serialize(result.AddParameter(), dat)
		.AddAttribute(type1999).Set("timeInstant", XMLSchema1999::xsd);

	SOAPTypeTraits<SOAPString>::Serialize(result.AddParameter(), bin)
		.AddAttribute(type1999).Set("string", XMLSchema1999::xsd);

	// Have to add array encoding attributes ...
	result.AddAttribute(SOAPEnc::arrayType).Set("ur-type[6]", XMLSchema1999::xsd);
	result.AddAttribute(type1999) = SOAPEnc::Array;
}

//
// validator1.moderateSizeArrayCheck (myArray)
// returns string
//
//
// This handler takes a single parameter named myArray, which is
// an array containing between 100 and 200 elements. Each of the
// items is a string, your handler must return a string containing
// the concatenated text of the first and last elements.
//

void
UserlandValidatorHandler::moderateSizeArrayCheck(const SOAPMethod& req, SOAPMethod& resp)
{
	const SOAPParameter& p = req.GetParameter("myArray");
	size_t numels = p.GetArray().Size();

	SOAPString result;
	result += p.GetArray()[0]->GetString();
	result += p.GetArray()[numels - 1]->GetString();

	resp.AddParameter("Result") << result;
}

//
// validator1.nestedStructTest (myStruct)
// returns number
//
//
// This handler takes a single parameter named myStruct, a struct,
// that models a daily calendar. At the top level, there is one struct
// for each year. Each year is broken down into months, and months
// into days. Most of the days are empty in the struct you receive, but
// the entry for April 1, 2000 contains a least three elements named moe,
// larry and curly, all <i4>s. Your handler must add the three numbers
// and return the result.
//
// Ken MacLeod: "This description isn't clear, I expected '2000.April.1'
// when in fact it's '2000.04.01'. Adding a note saying that month and day
// are two-digits with leading 0s, and January is 01 would help." Done.
//

void
UserlandValidatorHandler::nestedStructTest(const SOAPMethod& req, SOAPMethod& resp)
{
	stooges st;
	const SOAPParameter& p = req.GetParameter("myStruct");
	p.GetParameter("year2000").GetParameter("month04").GetParameter("day01") >> st;

	int sum = st.curly + st.larry + st.moe;

	resp.AddParameter("Result") << sum;
}

//
// validator1.simpleStructReturnTest (myNumber)
// returns struct
//
//
// This handler takes one parameter a number named myNumber, and returns
// a struct containing three elements, times10, times100 and times1000,
// the result of multiplying the number by 10, 100 and 1000.
void
UserlandValidatorHandler::simpleStructReturnTest(const SOAPMethod& req, SOAPMethod& resp)
{
	int myNumber;
	req.GetParameter("myNumber") >> myNumber;

	SOAPParameter& result = resp.AddParameter("Result");
	result.AddParameter("times10") << myNumber * 10;
	result.AddParameter("times100") << myNumber * 100;
	result.AddParameter("times1000") << myNumber * 1000;
	result.SetIsStruct();
}
