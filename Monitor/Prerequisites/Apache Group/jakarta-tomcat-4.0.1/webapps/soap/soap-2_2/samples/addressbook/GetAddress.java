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

package samples.addressbook;

import java.io.*;
import java.util.*;
import java.net.*;
import org.w3c.dom.*;
import org.apache.soap.util.xml.*;
import org.apache.soap.*;
import org.apache.soap.encoding.*;
import org.apache.soap.encoding.soapenc.*;
import org.apache.soap.rpc.*;

/**
 * See \samples\addressbook\readme for info.
 *
 * @author Matthew J. Duftler (duftler@us.ibm.com)
 */
public class GetAddress
{
  public static void main(String[] args) throws Exception 
  {
    if (args.length != 2
        && (args.length != 3 || !args[0].startsWith("-")))
    {
      System.err.println("Usage:");
      System.err.println("  java " + GetAddress.class.getName() +
                         " [-encodingStyleURI] SOAP-router-URL nameToLookup");
      System.exit (1);
    }

    // Process the arguments.
    int offset = 3 - args.length;
    String encodingStyleURI = args.length == 3
                              ? args[0].substring(1)
                              : Constants.NS_URI_SOAP_ENC;
    URL url = new URL(args[1 - offset]);
    String nameToLookup = args[2 - offset];
    SOAPMappingRegistry smr = new SOAPMappingRegistry();
    BeanSerializer beanSer = new BeanSerializer();

    // Map the types.
    smr.mapTypes(Constants.NS_URI_SOAP_ENC,
                 new QName("urn:xml-soap-address-demo", "address"),
                 Address.class, beanSer, beanSer);
    smr.mapTypes(Constants.NS_URI_SOAP_ENC,
                 new QName("urn:xml-soap-address-demo", "phone"),
                 PhoneNumber.class, beanSer, beanSer);

    // Build the call.
    Call call = new Call();

    call.setSOAPMappingRegistry(smr);
    call.setTargetObjectURI("urn:AddressFetcher");
    call.setMethodName("getAddressFromName");
    call.setEncodingStyleURI(encodingStyleURI);

    Vector params = new Vector();

    params.addElement(new Parameter("nameToLookup", String.class,
                                    nameToLookup, null));
    call.setParams(params);

    // Invoke the call.
    Response resp;

    try
    {
      resp = call.invoke(url, "");
    }
    catch (SOAPException e)
    {
      System.err.println("Caught SOAPException (" +
                         e.getFaultCode() + "): " +
                         e.getMessage());
      return;
    }

    // Check the response.
    if (!resp.generatedFault())
    {
      Parameter ret = resp.getReturnValue();
      Object value = ret.getValue();

      System.out.println(value != null ? "\n" + value : "I don't know.");
    }
    else
    {
      Fault fault = resp.getFault();

      System.err.println("Generated fault: ");
      System.out.println ("  Fault Code   = " + fault.getFaultCode());  
      System.out.println ("  Fault String = " + fault.getFaultString());
    }
  }
}