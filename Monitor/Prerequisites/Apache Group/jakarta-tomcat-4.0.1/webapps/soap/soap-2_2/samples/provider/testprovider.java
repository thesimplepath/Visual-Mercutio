package samples.provider;

import java.io.*;
import java.net.*;
import java.util.*;
import org.apache.soap.*;
import org.apache.soap.rpc.*;

public class testprovider {
  public static void main (String[] args) throws Exception {
    if (args.length != 1 ) {
      System.err.println ("Usage: java " + testprovider.class.getName () +
                          " SOAP-router-URL");
      System.exit (1);
    }

    // Process the arguments.
    URL url = new URL (args[0]);

    // Build the call.
    Call call = new Call ();
    call.setTargetObjectURI ("urn:testprovider");
    call.setMethodName ("hello");
    Vector params = new Vector ();
    // params.addElement (new Parameter("symbol", String.class, symbol, null));
    call.setParams (params);

    // make the call: note that the action URI is empty because the 
    // XML-SOAP rpc router does not need this. This may change in the
    // future.
    Response resp = call.invoke (/* router URL */ url, /* actionURI */ "" );

    // Check the response.
    if (resp.generatedFault ()) {
      Fault fault = resp.getFault ();
      System.out.println ("Ouch, the call failed: ");
      System.out.println ("  Fault Code   = " + fault.getFaultCode ());  
      System.out.println ("  Fault String = " + fault.getFaultString ());
    } else {
      Parameter result = resp.getReturnValue ();
      System.out.println ( "Done" );
    }
  }
}
