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
import org.apache.soap.transport.http.*;

/**
 * This class shows how to use the SOAPHTTPConnection's ability to
 * maintain an http session. 
 *
 * @author Sanjiva Weerawarana <sanjiva@watson.ibm.com>
 */
public class Main {
  static String name1 = "Purdue Boilermaker";
  static Address addr1 = new Address (1, "University Drive", 
				      "West Lafayette", "IN", 47907,
				      new Phone (765, "494", "4900"));

  private static void printAddress (Address ad) {
    if (ad == null) {
      System.err.println ("\t[ADDRESS NOT FOUND!]");
      return;
    }
    System.err.println ("\t" + ad.streetNum_Elem + " " + 
			ad.streetName_Elem);
    System.err.println ("\t" + ad.city_Elem + ", " + ad.state_Elem + " " +
			ad.zip_Elem);
    Phone ph = ad.phoneNumber_Elem;
    System.err.println ("\tPhone: (" + ph.areaCode_Elem + ") " +
			ph.exchange_Elem + "-" + ph.number_Elem);
  }

  private static void doit (AddressBookProxy ab) throws Exception {
    System.err.println (">> Storing address for '" + name1 + "'");
    ab.addEntry (name1, addr1);
    System.err.println (">> Querying address for '" + name1 + "'");
    Address resp = ab.getAddressFromName (name1);
    System.err.println (">> Response is:");
    printAddress (resp);
    System.err.println (">> Querying address for '" + name1 + "' again");
    resp = ab.getAddressFromName (name1);
    System.err.println (">> Response is:");
    printAddress (resp);
  }

  public static void main (String[] args) throws Exception {
    URL serviceURL = null;
    SOAPHTTPConnection shc = new SOAPHTTPConnection ();

    if (args.length > 1) {
      System.err.println ("Usage: java " + Main.class.getName () + 
			  " [Service-URL]");
      System.exit (1);
    } else if (args.length == 1) {
      serviceURL = new URL (args[0]);
    }

    System.err.println ("Using proxy without session maintenance.");
    AddressBookProxy ab1 = new AddressBookProxy ();
    if (serviceURL != null) {
      ab1.setEndPoint (serviceURL);
    }
    shc.setMaintainSession (false);
    ab1.setSOAPTransport (shc);
    doit (ab1);

    System.err.println ("\n\nUsing proxy with session maintenance.");
    AddressBookProxy ab2 = new AddressBookProxy ();
    if (serviceURL != null) {
      ab2.setEndPoint (serviceURL);
    }
    shc.setMaintainSession (true);
    ab2.setSOAPTransport (shc);
    doit (ab2);
  }
}
