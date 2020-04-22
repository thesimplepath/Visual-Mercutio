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

#include "WhichToolkitHandler.h"

//
//  Return information about our toolkit
//
//
// Added an optional feature, not part of the validation test. We try to
// call a handler called whichToolkit. It takes no parameters and returns
// a struct containing the following elements, all strings: toolkitDocsUrl,
// toolkitName, toolkitVersion, toolkitOperatingSystem. If the call works,
// and all the elements are returned, we construct the string in the
// "software" column of the readout using this information. In previous
// versions we read the HTTP header for this information, often yielding
// the name of the server, and not the SOAP toolkit being used. 

void
WhichToolkitHandler::whichToolkit(const SOAPMethod& request, SOAPMethod& response)
{
	//response.SetName("whichToolkitResult");
	SOAPParameter& param = response.AddParameter("Result");

	param.AddParameter("toolkitDocsUrl") << EASYSOAP_HOMEPAGE;
	param.AddParameter("toolkitName") << EASYSOAP_STRING;
	param.AddParameter("toolkitVersion") << EASYSOAP_VERSION_STRING;
	param.AddParameter("toolkitOperatingSystem") <<
	// TODO: This is a bit broken...
#ifdef _WIN32
		"Windows 2000";
#else
		"Linux";
#endif
	param.SetIsStruct();
}
