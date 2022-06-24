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

package samples.weblogic_ejb;

import java.io.*;
import java.net.*;
import java.util.*;
import org.apache.soap.*;
import org.apache.soap.rpc.*;

/**
 * This sample class makes use of a stateful ejb service.
 * The code contains a loop of 10 on one of the service's method to show that we are in a stateful mode.
 * On the server side an instance variable (counter) keeps track on how many time the service has been called.
 *
 * @author <a href="mailto:olivier@intraware.com">Olivier Brand</a>
 * @version 1.0
 * @since 1.0
 */
public class ejbtest {
    /**
     * Describe <code>main</code> method here.
     *
     * @param args a <code>String[]</code> value
     * @exception Exception if an error occurs
     */
    public static void main (String[] args) throws Exception {
    if (args.length != 2 ) {
      System.err.println ("Usage: java " + ejbtest.class.getName () +
                          " SOAP-router-URL helloword");
      System.exit (1);
    }

    // Process the arguments.
    URL url = new URL (args[0]);

    String ejbKey = null;

    // This is the main EJB service
    // After the first call and response processing, the service name contains the EJB
    // Base 64 encoded reference to keep the context between calls. It ensures that the same EJB instance is being called.
    //
    String service = "urn:ejbhello";


    // Build the call and loop 10 times to show the stateful behavior on the EJB provider
    for(int i=0; i < 10;i++)
        {
            Call call = new Call ();

            call.setTargetObjectURI (service);
            call.setMethodName ("hello");
            Vector params = new Vector ();
            // Olivier: Added
            String encodingStyleURI = Constants.NS_URI_SOAP_ENC;
            String symbol = args[1];
            // Olivier: uncommented
            call.setEncodingStyleURI(encodingStyleURI);
            params.addElement (new Parameter("symbol", String.class, symbol, null));

            call.setParams(params);

            // make the call: note that the action URI is empty because the
            // XML-SOAP rpc router does not need this. This may change in the
            // future.
            Response resp = call.invoke (/* router URL */ url, /* actionURI */ "" );

            // Check the response.
            if (resp.generatedFault ())
                {
                    Fault fault = resp.getFault ();
                    System.out.println ("Ouch, the call failed: ");
                    System.out.println ("  Fault Code   = " + fault.getFaultCode ());
                    System.out.println ("  Fault String = " + fault.getFaultString ());
                }
            else
                {
                    Parameter result = resp.getReturnValue ();
                    // This line is very important when using the stateful EJB.
                    // The SOAP provider concatenated the EJB reference to the URI, allowing to keep
                    // the state between client's call.
                    // Removing this line would make the service behaving like a stateless service with a big overhead though (creation of many EJBs)
                    service = resp.getFullTargetObjectURI();

                    System.out.println ( result.getValue() );
                }
        }
  }
}
