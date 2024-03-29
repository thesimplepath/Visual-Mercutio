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

package org.apache.soap;

import java.io.*;
import java.util.*;
import javax.xml.parsers.*;
import org.w3c.dom.*;
import org.apache.soap.util.xml.*;

/**
 * <em>SOAP</em> utilities.
 *
 * @author Sanjiva Weerawarana (sanjiva@watson.ibm.com)
 * @author Matthew J. Duftler (duftler@us.ibm.com)
 * @author Michael Spreitzer (mspreitz@us.ibm.com)
 */
public class Utils
{
  public static String cleanString(String orig)
  {
    if (orig == null)
    {
      return "";
    }

    StringBuffer strBuf = new StringBuffer();
    char[] chars = orig.toCharArray();

    for (int i = 0; i < chars.length; i++)
    {
      switch (chars[i])
      {
        case '&'  : strBuf.append("&amp;");
                    break;
        case '\"' : strBuf.append("&quot;");
                    break;
        case '\'' : strBuf.append("&apos;");
                    break;
        case '<'  : strBuf.append("&lt;");
                    break;
        case '>'  : strBuf.append("&gt;");
                    break;
        default   : strBuf.append(chars[i]);
                    break;
      }
    }

    return strBuf.toString();
  }

  public static void marshallNode(Node node, Writer sink)
  {
    DOM2Writer.serializeAsXML(node, sink);
  }

  /**
   * Given a throwable, return a vector containing a single entry
   * which is an Element with one text node containing the stack
   * trace.
   */
  public static Vector buildFaultDetailsFromThrowable (Throwable t)
  {
    Vector details = new Vector();
    DocumentBuilder xdb = XMLParserUtils.getXMLDocBuilder();
    Document doc = xdb.newDocument();
    Element elem = doc.createElement("stackTrace");
    StringWriter sw = new StringWriter();
    PrintWriter pw = new PrintWriter(sw);
    t.printStackTrace(pw);
    pw.close();
    Text tn = doc.createTextNode(sw.toString());
    elem.appendChild(tn);
    details.addElement(elem);
    return details;
  }
  
  /**
   * Check for mustUnderstand headers, and throw a mustUnderstand
   * Fault if we find any.
   */
  public static void checkMustUnderstands(Header header) throws SOAPException
  {
    Vector entries = header.getHeaderEntries();

    for (int i = 0; i < entries.size(); i++)
    {
      Element el = (Element)entries.elementAt(i);
      String val = el.getAttributeNS(Constants.NS_URI_SOAP_ENV,
                                     Constants.ATTR_MUST_UNDERSTAND);

      if (val != null && val.equals("1"))
      {
        throw new SOAPException("mustUnderstand",
                                "Didn't understand header '" +
                                el.getLocalName() + "'");
      }
    }
  }
}
