/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2000 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation and was
 * originally based on software copyright (c) 2000, International
 * Business Machines, Inc., http://www.apache.org.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

package samples.guidgen;

import java.io.*;
import java.util.*;
import java.net.*;
import org.w3c.dom.*;
import org.apache.soap.util.xml.*;
import org.apache.soap.*;
import org.apache.soap.encoding.*;
import org.apache.soap.encoding.soapenc.*;
import org.apache.soap.rpc.*;
import org.apache.soap.transport.http.SOAPHTTPConnection;

/**
 * Client to speak to MS SOAP implemented GUIDGen service at
 * http://www.itfinity.net/soap/guid/details.html
 *
 * @author Sanjiva Weerawarana (sanjiva@watson.ibm.com)
 */
public class GuidGenClient {
  public static final String DEFAULT_SERVICE_URL =
    "http://www.itfinity.net/soap/guid/Default.asp";

  public static void main(String[] args) throws Exception {
    String serviceURL = null;
    boolean goodUsage = true;
    String proxyHost = null;
    int proxyPort = -1;

    // parse command line arguments
    for (int i = 0; i < args.length; i++) {
      if ("-p".equalsIgnoreCase(args[i])) {
        goodUsage = false;
        if (args.length > i) {
          i++;
          int pos = args[i].indexOf(':');
          if (pos != -1) {
            try {
              proxyPort = Integer.parseInt(args[i].substring(pos + 1));
              proxyHost = args[i].substring(0, pos);
              goodUsage = true;
            } catch(NumberFormatException nfe) {
            }
          }
        }
      } else if (serviceURL == null)
        serviceURL = args[i];
      else {
        goodUsage = false;
        break;
      }
    }

    if (!goodUsage) {
      System.err.println ("Usage: java samples.guidgen.GuidGenClient " +
                          "[service-URL] [-p <HTTP proxy hostname:port>]");
      System.exit (1);
    }

    if (serviceURL == null)
      serviceURL = DEFAULT_SERVICE_URL;
    URL url = new URL (serviceURL);

    // define deserializers for the return things (without xsi:type)
    SOAPMappingRegistry smr = new SOAPMappingRegistry ();
    StringDeserializer sd = new StringDeserializer ();
    smr.mapTypes (Constants.NS_URI_SOAP_ENC,
                  new QName ("", "Result"), null, null, sd);

    // create the transport and set parameters
    SOAPHTTPConnection st = new SOAPHTTPConnection();
    if (proxyHost != null) {
        st.setProxyHost(proxyHost);
        st.setProxyPort(proxyPort);
    }

    // build the call.
    Call call = new Call ();
    call.setSOAPTransport(st);
    call.setSOAPMappingRegistry (smr);
    call.setTargetObjectURI ("http://www.itfinity.net/soap/guid/guid.xsd");
    call.setMethodName("NextGUID");
    call.setEncodingStyleURI ("http://schemas.xmlsoap.org/soap/encoding/");

    // invoke it
    System.err.println ("Invoking GUID generator service at: ");
    System.err.println ("\t" + serviceURL);
    Response resp;
    try {
      resp = call.invoke (url, DEFAULT_SERVICE_URL);
    } catch (SOAPException e) {
      System.err.println("Caught SOAPException (" +
                         e.getFaultCode () + "): " +
                         e.getMessage ());
      return;
    }

    // check response 
    if (!resp.generatedFault()) {
      Parameter ret = resp.getReturnValue();
      Object value = ret.getValue();

      System.out.println ("Next GUID is: " + value);
    }
    else {
      Fault fault = resp.getFault ();
      System.err.println ("Generated fault: ");
      System.out.println ("  Fault Code   = " + fault.getFaultCode());  
      System.out.println ("  Fault String = " + fault.getFaultString());
    }
  }
}
