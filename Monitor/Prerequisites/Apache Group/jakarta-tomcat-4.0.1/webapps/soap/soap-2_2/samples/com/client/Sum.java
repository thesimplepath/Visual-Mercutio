/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001 The Apache Software Foundation.  All rights 
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
 * originally based on software copyright (c) 2001, International
 * Business Machines, Inc., http://www.apache.org.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */
package samples.com.client;

import java.io.*;
import java.net.*;
import java.util.*;

import org.apache.soap.*;
import org.apache.soap.rpc.*;

public class Sum
{
 public static void main( String[] args) throws Exception
 {
   final String urn= "urn:sum-COM";
   Integer n1=null;
   Integer n2=null;
   boolean doset=false;
   if(args.length == 2 && 0 == "-set".compareTo(args[0])) 
   {
     
     try{
        n1= new Integer( args[1]);
       doset= true;
     }catch ( NumberFormatException e)
     {
       explain();
     }
     
   }
   else if( args.length == 1 ) 
   {
     try{
     n1= new Integer( args[0]);
     }catch ( NumberFormatException e)
     {
       explain();
   }
   }
   else
     explain();


   Vector params = new Vector ();
   params.addElement (new Parameter("n1" , Integer.class,  n1, null)); 
  
   URL url = new URL ("http://" + serverhost + ":" + serverport+ soapservlet);

   // Build the call.
   Call call = new Call ();
   call.setTargetObjectURI (urn);
   call.setMethodName ( doset ? "set_total" : "sum");
   call.setEncodingStyleURI(Constants.NS_URI_SOAP_ENC);
   
   call.setParams (params);
   Response resp = call.invoke (/* router URL */ url, /* actionURI */ "" );
   
   if (resp.generatedFault ()) {
     Fault fault = resp.getFault ();
     System.out.println ("Ouch, the call failed: ");
     System.out.println ("  Fault Code   = " + fault.getFaultCode ());  
     System.out.println ("  Fault String = " + fault.getFaultString ());
   } 


   // Build the call.
   call = new Call ();
   call.setTargetObjectURI (urn);
   call.setMethodName ("get_total");
   call.setEncodingStyleURI(Constants.NS_URI_SOAP_ENC);
   
   call.setParams (null);
   resp = call.invoke (/* router URL */ url, /* actionURI */ "" );
   
   if (resp.generatedFault ()) {
     Fault fault = resp.getFault ();
     System.out.println ("Ouch, the call failed: ");
     System.out.println ("  Fault Code   = " + fault.getFaultCode ());  
     System.out.println ("  Fault String = " + fault.getFaultString ());
   } else {
     Parameter result = resp.getReturnValue ();
     System.out.println( ( doset?  "Value is now " : "The total so far is ") + result.getValue());
   }
 }
 private static void explain()
 {
   System.err.println("Please provide either an integer to add to the running total!");
   System.err.println("   -or-");
   System.err.println("the option \"-set\" and and an integer to set the current total.");
   System.exit(8);
 }
 static String serverhost= "localhost";
 static String serverport= "8080";
 static String soapservlet= "/soap/servlet/rpcrouter";
} // end  addit
