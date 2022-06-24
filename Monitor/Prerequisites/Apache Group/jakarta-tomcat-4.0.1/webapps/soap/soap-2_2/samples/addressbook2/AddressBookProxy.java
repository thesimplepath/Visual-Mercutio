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

package samples.addressbook2;

import java.net.*;
import java.util.*;
import org.apache.soap.*;
import org.apache.soap.encoding.*;
import org.apache.soap.rpc.*;
import org.apache.soap.util.xml.*;
import org.apache.soap.transport.*;

/**
 * Proxy for the address book service described in the AddressBook.wsdl
 * file found in this directory. The base proxy was generated using 
 * IBM's WSDL Toolkit v1.1 using the following command:
 *	java com.ibm.wsdl.Main -in AddressBook.wsdl \
 *                             -package samples.addressbook2 \
 *                             -dir ../..
 * The generated proxy was hand edited to add the setSOAPTransport
 * method and the generated serializer was hand edited to have the 
 * SOAPContext argument required by Apache SOAP v2.1 (the WSDL 
 * Toolkit v1.1 assumes Apache SOAP v2.0).
 *
 * @author Sanjiva Weerawarana <sanjiva@watson.ibm.com>
 */
public class AddressBookProxy
{
  private Call call = new Call();
  private URL url = null;
  private String SOAPActionURI = "";
  private SOAPMappingRegistry smr = call.getSOAPMappingRegistry();

  public AddressBookProxy() throws MalformedURLException
  {
    call.setTargetObjectURI("urn:AddressFetcher2");
    call.setEncodingStyleURI("http://schemas.xmlsoap.org/soap/encoding/");
    this.url = new URL("http://localhost:2020/soap/servlet/rpcrouter");
    this.SOAPActionURI = "";
  }

  public synchronized void setEndPoint(URL url)
  {
    this.url = url;
  }

  public synchronized URL getEndPoint()
  {
    return url;
  }

  public synchronized void setSOAPTransport (SOAPTransport st)
  {
    call.setSOAPTransport (st);
  }

  public synchronized void addEntry(java.lang.String name,
    samples.addressbook2.Address address) throws SOAPException
  {
    if (url == null)
    {
      throw new SOAPException(Constants.FAULT_CODE_CLIENT,
      "A URL must be specified via " +
      "AddressBookProxy.setEndPoint(URL).");
    }

    call.setMethodName("addEntry");
    Vector params = new Vector();
    Parameter nameParam = new Parameter("name", java.lang.String.class, name,
      null);
    params.addElement(nameParam);
    Parameter addressParam = new Parameter("address",
      samples.addressbook2.Address.class, address, null);
    params.addElement(addressParam);
    call.setParams(params);
    Response resp = call.invoke(url, SOAPActionURI);

    // Check the response.
    if (resp.generatedFault())
    {
      Fault fault = resp.getFault();

      throw new SOAPException(fault.getFaultCode(), fault.getFaultString());
    }
  }

  public synchronized samples.addressbook2.Address getAddressFromName
    (java.lang.String name) throws SOAPException
  {
    if (url == null)
    {
      throw new SOAPException(Constants.FAULT_CODE_CLIENT,
      "A URL must be specified via " +
      "AddressBookProxy.setEndPoint(URL).");
    }

    call.setMethodName("getAddressFromName");
    Vector params = new Vector();
    Parameter nameParam = new Parameter("name", java.lang.String.class, name,
      null);
    params.addElement(nameParam);
    call.setParams(params);
    Response resp = call.invoke(url, SOAPActionURI);

    // Check the response.
    if (resp.generatedFault())
    {
      Fault fault = resp.getFault();

      throw new SOAPException(fault.getFaultCode(), fault.getFaultString());
    }
    else
    {
      Parameter retValue = resp.getReturnValue();
      return (samples.addressbook2.Address)retValue.getValue();
    }
  }

  {
    samples.addressbook2.PhoneSerializer ser_0 = new samples.addressbook2.PhoneSerializer
      ();
    smr.mapTypes("http://schemas.xmlsoap.org/soap/encoding/", new QName(
      "urn:xml-soap-address-demo", "phone"), samples.addressbook2.Phone.class,
      ser_0, ser_0);
    samples.addressbook2.AddressSerializer ser_1 = new samples.addressbook2.AddressSerializer
      ();
    smr.mapTypes("http://schemas.xmlsoap.org/soap/encoding/", new QName(
      "urn:xml-soap-address-demo", "address"),
      samples.addressbook2.Address.class, ser_1, ser_1);
  }

}
