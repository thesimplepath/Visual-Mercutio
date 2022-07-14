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

package org.apache.soap.transport;

import java.net.URL;
import java.io.BufferedReader;
import java.util.Hashtable;
import org.apache.soap.*;
import org.apache.soap.encoding.*;
import org.apache.soap.rpc.SOAPContext;

/**
 * This interface is an abstraction of the transport layer that's carrying
 * the messages.
 *
 * @author Sanjiva Weerawarana (sanjiva@watson.ibm.com)
 */
public interface SOAPTransport {
  /**
   * This method is used to request that an envelope be sent.
   *
   * @param sendTo the URL to send the envelope to
   * @param action the SOAPAction header field value
   * @param headers any other header fields to go to as protocol headers
   * @param env the envelope to send
   * @param smr the XML<->Java type mapping registry (passed on)
   * @param ctx the request SOAPContext
   *
   * @exception SOAPException with appropriate reason code if problem
   */
  public void send (URL sendTo, String action, Hashtable headers,
                    Envelope env, SOAPMappingRegistry smr,
                    SOAPContext ctx)
    throws SOAPException;

  /**
   * Return a buffered reader to receive back the response to whatever
   * was sent to whatever.
   *
   * @return a reader to read the results from or null if that's not
   *         possible.
   */
  public BufferedReader receive ();

  /**
   * Return access to headers generated by the protocol.
   * 
   * @return a hashtable containing all the headers
   */
  public Hashtable getHeaders ();

  /**
   * Return the SOAPContext associated with the response.
   *
   * @return response SOAPContext
   */
  public SOAPContext getResponseSOAPContext ();
}