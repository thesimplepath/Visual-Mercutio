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

package samples.calculator;

import java.io.*;
import java.net.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import org.apache.soap.util.xml.*;
import org.apache.soap.*;
import org.apache.soap.rpc.*;

/**
 * This silly little calculator talks to a SOAP calculator service to
 * do the real operations. 
 */
public class Calculator extends Frame {
  String encodingStyleURI;
  URL url;
  TextField ef = new TextField ();
  int state = 0; // 0 => got 0 args, 1 => got 1 arg
  double arg1 = Double.NaN;
  boolean dotpressed = false;
  String lastop;
  Label status;
  boolean freshstart = true;

  public Calculator (String title) {
    super (title);

    addWindowListener (new WindowAdapter () {
      public void windowClosing (WindowEvent e) {
	System.exit (0);
      }
    });

    ef.setEditable (false);
    add ("North", ef);

    Panel p = new Panel ();
    p.setLayout (new GridLayout (-1, 4, 5, 5));
    String bs[] = {"7", "8", "9", "/", 
		   "4", "5", "6", "*",
		   "1", "2", "3", "-",
		   "0", "+/-", ".", "+"};
    for (int i = 0; i < bs.length; i++) {
      Button b = new Button (" " + bs[i] + " ");
      ActionListener al = null;
      if ((i != 3) && (i != 7) && (i != 11) && (i != 13) && (i != 14) && 
	  (i != 15)) {
	// digit pressed
	b.setActionCommand (bs[i]);
	al = new ActionListener () {
	  public void actionPerformed (ActionEvent e) {
	    if (freshstart) {
	      ef.setText ("");
	      freshstart = false;
	    }
	    Button bb = (Button) e.getSource ();
	    ef.setText (ef.getText () + bb.getActionCommand ());
	    status.setText ("");
	  }
	};
      } else if (i == 14) {
	// '.' pressed
	al = new ActionListener () {
	  public void actionPerformed (ActionEvent e) {
	    if (freshstart) {
	      ef.setText ("");
	      freshstart = false;
	    }
	    status.setText ("");
	    if (dotpressed) {
	      return;
	    } else {
	      dotpressed = true;
	      ef.setText (ef.getText () + '.');
	    }
	  }
	};
      } else if (i == 13) {
	// +/- pressed
	al = new ActionListener () {
	  public void actionPerformed (ActionEvent e) {
	    if (freshstart) {
	      ef.setText ("");
	      freshstart = false;
	    }
	    String t = ef.getText ();
	    if (t.charAt (0) == '-') {
	      ef.setText (t.substring (1));
	    } else {
	      ef.setText ('-' + t);
	    }
	    status.setText ("");
	  }
	};
      } else {
	// operation
	String ac = null;
	if (bs[i].equals ("/")) {
	  ac = "divide";
	} else if (bs[i].equals ("*")) {
	  ac = "times";
	} else if (bs[i].equals ("-")) {
	  ac = "minus";
	} else {
	  ac = "plus";
	}
	b.setActionCommand (ac);
	al = new ActionListener () {
	  public void actionPerformed (ActionEvent e) {
	    Button bb = (Button) e.getSource ();
	    double arg = stringToDouble (ef.getText ());
	    if (state == 0) {
	      arg1 = arg;
	      lastop = bb.getActionCommand ();
	      freshstart = true;
	      state = 1;
	    } else {
	      try {
		status.setText ("Working ..");
		arg1 = doOp (lastop, arg1, arg);
		lastop = bb.getActionCommand ();
		ef.setText ("" + arg1);
		freshstart = true;
		status.setText ("");
	      } catch (SOAPException e2) {
		status.setText ("Ouch, excepted: " + e2.getMessage ());
		e2.printStackTrace ();
	      }
	    }
	  }
	};
      }
      b.addActionListener (al);
      p.add (b);
    }

    add ("Center", p);
    add ("South", status = new Label ("Ready .."));

    pack ();
    show ();
  }

  private double doOp (String op, double arg1, double arg2) 
       throws SOAPException {
    // Build the call.
    Call call = new Call ();
    call.setTargetObjectURI ("urn:xml-soap-demo-calculator");
    call.setMethodName (op);
    call.setEncodingStyleURI(encodingStyleURI);
    Vector params = new Vector ();
    params.addElement (new Parameter("arg1", double.class, 
				     new Double (arg1), null));
    params.addElement (new Parameter("arg2", double.class, 
				     new Double (arg2), null));
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
      return Double.NaN;
    } else {
      Parameter result = resp.getReturnValue ();
      return ((Double)result.getValue ()).doubleValue ();
    }
  }

  private double stringToDouble (String s) {
    // try as a double, float or by appending a ".0" to it
    try {
      return Double.valueOf (s).doubleValue ();
    } catch (NumberFormatException e1) {
      try {
	return Float.valueOf (s).floatValue () * 1.0;
      } catch (NumberFormatException e2) {
	if (s.indexOf (".") == -1) {
	  return stringToDouble (s + '.' + '0');
	} else {
	  return Double.NaN;
	}
      }
    }
  }

  public static void main (String[] args) throws Exception {
    int maxargs = 2;
    if (args.length != (maxargs-1)
        && (args.length != maxargs || !args[0].startsWith ("-"))) {
      System.err.println ("Usage: java " + Calculator.class.getName () +
                          " [-encodingStyleURI] SOAP-router-URL");
      System.exit (1);
    }

    Calculator c = new Calculator ("XML-SOAP Calculator");

    int offset = maxargs - args.length;
    c.encodingStyleURI = (args.length == maxargs)
                         ? args[0].substring(1)
                         : Constants.NS_URI_SOAP_ENC;
    c.url = new URL (args[1 - offset]);
  }
}
