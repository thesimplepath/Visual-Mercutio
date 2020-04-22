/* 
 * EasySoap++ - A C++ library for SOAP (Simple Object Access Protocol)
 * Copyright (C) 2001 David Crowley; SciTegic, Inc.
 *
 * SSLServer - A test tool to test EasySoap's SSL capabilitys
 * Copyright (C) 2001 Blaise St-Laurent
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
 * $Id: SSLServer.cpp,v 1.1 2001/12/13 22:23:11 kingmob Exp $
 */

#include <easysoap/SOAP.h>
#include <easysoap/SOAPDispatchHandler.h>
#include <easysoap/SOAPCGIServer.h>

USING_EASYSOAP_NAMESPACE

// SSL environment variables we are interested in
//

const char* SSLEnvVars[] = {  
"SSL_PROTOCOL",
"SSL_VERSION_LIBRARY",
"SSL_CIPHER_USEKEYSIZE",
"SSL_CIPHER_ALGKEYSIZE",
"SSL_CIPHER",
"SSL_CIPHER_EXPORT",
"SSL_CIPHER_ALGKEYSIZE",
"SSL_SERVER_CERT",
"SSL_SERVER_V_START",
"SSL_SERVER_V_END",
"SSL_SERVER_M_SERIAL",
"SSL_SERVER_A_SIG",
"SSL_SERVER_S_DN",
"SSL_SERVER_S_DN_CN",
"SSL_SERVER_S_DN_Email",
"SSL_SERVER_S_DN_O",
"SSL_SERVER_S_DN_OU",
"SSL_SERVER_S_DN_C",
"SSL_SERVER_S_DN_SP",
"SSL_SERVER_S_DN_L",
"SSL_SERVER_I_DN",
"SSL_SERVER_I_DN_CN",
"SSL_SERVER_I_DN_Email",
"SSL_SERVER_I_DN_O",
"SSL_SERVER_I_DN_OU",
"SSL_SERVER_I_DN_C",
"SSL_SERVER_I_DN_SP",
"SSL_SERVER_I_DN_L",
"SSL_CLIENT_CERT",
"SSL_CLIENT_V_START",
"SSL_CLIENT_V_END",
"SSL_CLIENT_M_SERIAL",
"SSL_CLIENT_A_SIG",
"SSL_CLIENT_S_DN",
"SSL_CLIENT_S_DN_CN",
"SSL_CLIENT_S_DN_Email",
"SSL_CLIENT_S_DN_O",
"SSL_CLIENT_S_DN_OU",
"SSL_CLIENT_S_DN_C",
"SSL_CLIENT_S_DN_SP",
"SSL_CLIENT_S_DN_L",
"SSL_CLIENT_I_DN",
"SSL_CLIENT_I_DN_CN",
"SSL_CLIENT_I_DN_Email",
"SSL_CLIENT_I_DN_O",
"SSL_CLIENT_I_DN_OU",
"SSL_CLIENT_I_DN_C",
"SSL_CLIENT_I_DN_SP",
"SSL_CLIENT_I_DN_L",
"SSL_CIPHER_EXPORT",
"SSL_CIPHER_ALGKEYSIZE",
"SSL_CIPHER_USEKEYSIZE",
"SSL_VERSION_LIBRARY",
0L
} ;

class SSLServer : public SOAPDispatchHandler < SSLServer > 
{
		private:
			SOAPString ns;
		protected:

		public:
			SSLServer() 
			{
					ns = "http://www.earthshattering.org/test";
					DispatchMethod("EchoSSL", ns.Str(), &SSLServer::EchoSSL);
			}
			void EchoSSL(const SOAPMethod& request, SOAPMethod& response)
			{
				int i = 0;
				while (0L != SSLEnvVars[i]) {
					SOAPString tmp = getenv(SSLEnvVars[i]);
					if (!tmp.IsEmpty()) {
						response.AddParameter(SSLEnvVars[i]) << tmp;
					} else {
						response.AddParameter(SSLEnvVars[i]) << "Not Set";
					}
				++i;
					
				}
			}
			SSLServer* GetTarget(const SOAPEnvelope& request)
			{
					return this;
			}


};

int main(int argc, char* argv[])
{
		SOAPCGIServer cgi;
		SSLServer Obj;

		int rc = cgi.DispatchTo(&Obj).Handle();

}

