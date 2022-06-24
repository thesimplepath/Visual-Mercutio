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
package samples.mime;

import java.io.*;
import java.util.*;
import java.net.*;
import org.w3c.dom.*;
import org.xml.sax.*;
import org.apache.soap.util.xml.*;
import org.apache.soap.util.mime.*;
import org.apache.soap.*;
import org.apache.soap.transport.*;
import org.apache.soap.encoding.*;
import org.apache.soap.encoding.soapenc.*;
import org.apache.soap.rpc.*;
import org.apache.soap.messaging.*;
import javax.activation.*;
import javax.mail.internet.*;
import javax.xml.parsers.*;

/**
 * MIME attachment test client.
 *
 * @author Wouter Cloetens (wcloeten@raleigh.ibm.com)
 */
public class MimeTestClient {
  public static void main(String[] args) throws Exception {
    String encodingStyleURI = Constants.NS_URI_SOAP_ENC;
    URL url = new URL(args[0]);
    SOAPMappingRegistry smr = new SOAPMappingRegistry();
    BeanSerializer beanSer = new BeanSerializer();

    try {
        if (!args[1].equals("loopProcessor")) {
            // Build the call.
            Call call = new Call();

            call.setSOAPMappingRegistry(smr);
            call.setTargetObjectURI("urn:mimetest");
            call.setMethodName(args[1]);
            call.setEncodingStyleURI(encodingStyleURI);

            Vector params = new Vector();
            if (args[1].equals("sendFile") || args[1].equals("loopFile"))
                for (int i = 2; i < args.length; i++) {
                    DataSource ds = new ByteArrayDataSource(new File(args[i]),
                                                            null);
                    DataHandler dh = new DataHandler(ds);
                    params.addElement(new Parameter("addedfile",
                        javax.activation.DataHandler.class, dh, null));
                }
            else if (args[1].equals("loopFileVector")) {
                Vector v = new Vector();
                for (int i = 2; i < args.length; i++) {
                    DataSource ds = new ByteArrayDataSource(new File(args[i]),
                                                            null);
                    DataHandler dh = new DataHandler(ds);
                    v.addElement(dh);
                }
                params.addElement(new Parameter("addedfiles", Vector.class,
                                                v, null));
            } else if (args[1].equals("loopFileArray")) {
                DataHandler dhs[] = new DataHandler[args.length - 2];
                for (int i = 2; i < args.length; i++) {
                    DataSource ds = new ByteArrayDataSource(new File(args[i]),
                                                            null);
                    dhs[i - 2] = new DataHandler(ds);
                }
                params.addElement(new Parameter("addedfiles", DataSource[].class,
                                                dhs, null));
            } else if (args[1].equals("getFileVector")
                       || args[1].equals("getFileArray")) {
                String s[] = new String[args.length - 2];
                for (int i = 2; i < args.length; i++) {
                    s[i - 2] = args[i];
                }
                params.addElement(new Parameter("filenames", String[].class,
                                                s, null));
            } else if (args[1].equals("listAttachments")) {
                for (int i = 2; i < args.length; i++) {
                    DataSource ds = new ByteArrayDataSource(new File(args[i]),
                                                            null);
                    DataHandler dh = new DataHandler(ds);
                    MimeBodyPart bp = new MimeBodyPart();
                    bp.setDataHandler(dh);
                    bp.setFileName(args[i]);
                    bp.setHeader(
                        org.apache.soap.Constants.HEADER_CONTENT_LOCATION,
                        "myfile" + (i - 2));
                    call.addBodyPart(bp);
                }
            }
            call.setParams(params);

            // System.out.println("Call: " + call);
            // System.out.println("Context: " + SOAPContext.getSOAPContext());

            // Invoke the call.
            Response resp;

            try {
              resp = call.invoke(url, "");
            } catch (SOAPException e) {
              System.err.println("Caught SOAPException (" +
                                 e.getFaultCode() + "): " +
                                 e.getMessage());
              e.printStackTrace();
              return;
            }

            // Check the response.
            if (!resp.generatedFault()) {
                Parameter ret = resp.getReturnValue();
                if(ret == null)
                    System.out.println("No response.");
                else  {
                    // System.out.println("Response: " + resp);

                    printObject(ret.getValue());
                }
            } else {
              Fault fault = resp.getFault();

              System.err.println("Generated fault: ");
              System.err.println ("  Fault Code   = " + fault.getFaultCode());
              System.err.println ("  Fault String = " + fault.getFaultString());
            }
        } else {
            // Build the Message.
            Message msg = new Message();

            // Add attachments.
            String attachments = "";
            for (int i = 2; i < args.length; i++) {
                ByteArrayDataSource ds =
                    new ByteArrayDataSource(new File(args[i]), null);
                DataHandler dh = new DataHandler(ds);
                MimeBodyPart bp = new MimeBodyPart();
                bp.setDataHandler(dh);
                bp.setFileName(args[i]);
                bp.setHeader(org.apache.soap.Constants.HEADER_CONTENT_LOCATION,
                             "myfile" + (i - 2));
                msg.addBodyPart(bp);
                attachments += "\n<file size=\"" + ds.getSize()
                    + "\" location =\"myfile" + (i - 2) + "\">" + args[i]
                    + "</file>";
            }

            // Build the envelope.
            String xmlmsg = "";
            xmlmsg += "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\">";
            xmlmsg += "\n<s:Body>\n<" + args[1] + " xmlns=\"urn:mimetestprocessor\">";
            xmlmsg += attachments;
            xmlmsg += "\n</" + args[1] + "></s:Body></s:Envelope>";
            DocumentBuilder xdb = XMLParserUtils.getXMLDocBuilder();
            Document doc =
              xdb.parse(new InputSource(new StringReader(xmlmsg)));
            if (doc == null) {
                System.err.println("Failed to parse XML");
                return;
            }
            Envelope msgEnv = Envelope.unmarshall(doc.getDocumentElement());

            // Invoke.
            msg.send(url, "", msgEnv);

            // Receive response as DataHandler.
            printObject(msg.receive());
        }
    } catch(Exception e) {
        e.printStackTrace();
    }
  }

  public static void printObject(Object obj) {
      if (obj instanceof DataHandler) {
          DataHandler dh = (DataHandler)obj;
          Object o;
          try {
              o = dh.getContent();
          } catch(IOException ioe) {
              o = ioe;
          }
          System.out.println("DataHandler, name=" + dh.getName()
                             + ", type=" + dh.getContentType()
                             + ", content: (" + o.getClass().getName()
                             + ")\n" + o);
          DataSource ds = dh.getDataSource();
          String fname = "" + System.currentTimeMillis() + ".out";
          System.out.println(" Writing attachment to file: " + fname);
          try {
              ByteArrayDataSource bds = new ByteArrayDataSource(
                  ds.getInputStream(), dh.getContentType());
              bds.writeTo(new FileOutputStream(fname));
          } catch(IOException ioe) {
              System.out.println(ioe);
              ioe.printStackTrace(System.err);
          }
      } else if (obj instanceof Vector) {
          for(Enumeration enum = ((Vector)obj).elements(); enum.hasMoreElements(); )
              printObject(enum.nextElement());
      } else if (obj instanceof Object[]) {
          Object[] s = (Object[])obj;
          for (int i = 0; i < s.length; i++)
              printObject(s[i]);
      } else
          System.out.println(obj);
  }
}
