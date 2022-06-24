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
import javax.activation.*;
import javax.mail.*;
import javax.mail.internet.*;
import org.apache.soap.*;
import org.apache.soap.util.mime.*;
import org.apache.soap.rpc.SOAPContext;

/**
 * NOTE!!! This service has a *huge* security hole and is provided for
 * demonstration purposes only. Do not leave this service in the classpath
 * of your server!
 *
 * @author Wouter Cloetens (wcloeten@raleigh.ibm.com)
 */
public class MimeTest {
    public MimeTest() {
    }

    public static String sendFile(DataHandler dh) throws IOException {
        StringBuffer sb = new StringBuffer("Received attachment:\n");
        sb.append("Content type: ").append(dh.getContentType());
        sb.append("\nName: ").append(dh.getName());
        Object o = dh.getContent();
        sb.append("\nContent class: ").append(o.getClass().getName());
        sb.append("\nContent: ").append(o.toString());
        return sb.toString();
    }

    public static DataHandler loopFile(DataHandler dh) throws IOException {
        return dh;
    }

    public static Vector getFileVector(String[] fname) throws IOException {
        Vector res = new Vector();

        for (int i = 0; i < fname.length; i++) {
            // Security hole is here:
            DataSource ds = new ByteArrayDataSource(new File(fname[i]), null);
            res.addElement(new DataHandler(ds));
        }
        return res;
    }

    public static Vector loopFileVector(Vector dhs) {
        return dhs;
    }

    public static DataHandler[] getFileArray(String[] fname)
        throws IOException {
        Vector v = getFileVector(fname);
        DataHandler[] dhs = new DataHandler[v.size()];
        for (int i = 0; i < dhs.length; i++)
            dhs[i] = (DataHandler)v.elementAt(i);
        return dhs;
    }

    public static Object[] loopFileArray(Object[] dhs) {
        return dhs;
    }

    public static String listAttachments()
        throws IOException, MessagingException {
            return("Not yet implemented.");
        /*
        // List attachments.
        StringBuffer sb = new StringBuffer("Received attachments:\n");
        MimeBodyPart rootPart = ctx.getRootPart();
        MimeBodyPart bp;
        for (int i = 0; i < ctx.getCount(); i++) {
            bp = (MimeBodyPart)ctx.getBodyPart(i);
            if (bp.equals(rootPart))
                continue;
            sb.append("Content type: ").append(bp.getContentType());
            sb.append("\nContent-ID: ").append(bp.getContentID());
            sb.append("\nContent-Location: ");
            sb.append(bp.getHeader(
                org.apache.soap.Constants.HEADER_CONTENT_LOCATION, null));
            sb.append("\nName: ").append(bp.getFileName());
            Object o = bp.getContent();
            sb.append("\nContent class: ").append(o.getClass().getName());
            if (bp.isMimeType("text/*"))
                sb.append("\nContent: ").append(o.toString()).append('\n');
        }
        return sb.toString();
        */
    }

    /**
     * This is a method for use by Messaging.
     */
    public static void loopProcessor(Envelope env, SOAPContext reqCtx, 
                                                   SOAPContext retCtx)
        throws IOException, MessagingException {
        System.err.println(reqCtx);
        // List attachments.
        StringBuffer sb = new StringBuffer("Received attachments:\n");
        MimeBodyPart rootPart = reqCtx.getRootPart();
        MimeBodyPart bp;
        for (int i = 0; i < reqCtx.getCount(); i++) {
            bp = reqCtx.getBodyPart(i);
            if (bp.equals(rootPart))
                continue;
            sb.append("Content type: ").append(bp.getContentType());
            sb.append("\nContent-ID: ").append(bp.getContentID());
            sb.append("\nContent-Location: ");
            sb.append(bp.getHeader(
                org.apache.soap.Constants.HEADER_CONTENT_LOCATION, null));
            sb.append("\nName: ").append(bp.getFileName());
            Object o = bp.getContent();
            sb.append("\nContent class: ").append(o.getClass().getName());
            if (bp.isMimeType("text/*"))
                sb.append("\nContent: ").append(o.toString()).append('\n');
        }
        System.err.println(sb.toString());
        retCtx.setRootPart(reqCtx.getBodyPart(reqCtx.getCount() - 1));
    }
}
