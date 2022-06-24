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
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

package samples.interop;

import java.util.Vector;
import org.apache.soap.*;
import org.apache.soap.encoding.SOAPMappingRegistry;
import org.apache.soap.encoding.soapenc.*;
import org.apache.soap.rpc.*;
import org.apache.soap.messaging.*;
import java.net.URL;
import org.apache.soap.util.xml.*;
import java.io.*;
import org.w3c.dom.*;
import org.apache.soap.util.*;
import java.lang.reflect.*;
	
public class DataSerializer implements Serializer, Deserializer
{
  public void marshall(String inScopeEncStyle, Class javaType, Object src,
                       Object context, Writer sink, NSStack nsStack,
                       XMLJavaMappingRegistry xjmr, SOAPContext ctx)
    throws IllegalArgumentException, IOException
  {
    if(!javaType.equals(Data.class))
    {
      throw new IllegalArgumentException("Can only serialize Data instances");
    }
    
    Data data = (Data)src;
    
    nsStack.pushScope();
    if(src!=null)
    {
      SoapEncUtils.generateStructureHeader(inScopeEncStyle,
                                           javaType,
                                           context,
                                           sink,
                                           nsStack,xjmr);

      sink.write(StringUtils.lineSeparator);
      
      xjmr.marshall(inScopeEncStyle, Integer.class, data.myInt, "varInt",
                    sink, nsStack, ctx);
      sink.write(StringUtils.lineSeparator);
      xjmr.marshall(inScopeEncStyle, Float.class, data.myFloat, "varFloat",
                    sink, nsStack, ctx);
      sink.write(StringUtils.lineSeparator);
      xjmr.marshall(inScopeEncStyle, String.class, data.myString, "varString",
                    sink, nsStack, ctx);
      sink.write(StringUtils.lineSeparator);
      
      sink.write("</" + context + '>');
    }
    else
    {
      SoapEncUtils.generateNullStructure(inScopeEncStyle,
                                         javaType,
                                         context,
                                         sink,
                                         nsStack,xjmr);
    }
    nsStack.popScope();
  }
  
  public Bean unmarshall(String inScopeEncStyle, QName elementType, Node src,
                         XMLJavaMappingRegistry xjmr, SOAPContext ctx)
    throws IllegalArgumentException
  {
    Element root = (Element)src;
    String name = root.getTagName();

    if (SoapEncUtils.isNull(root))
    {
      return new Bean(Data.class, null);
    }
    
    Data ret = new Data();
    NodeList list = root.getElementsByTagName("varInt");
    if (list == null || list.getLength() == 0) {
      throw new IllegalArgumentException("No 'varInt' Element (deserializing Data struct)");
    }
    Element el = (Element)list.item(0);
    ret.myInt = new Integer(DOMUtils.getChildCharacterData(el));
    
    list = root.getElementsByTagName("varFloat");
    if (list == null || list.getLength() == 0) {
      throw new IllegalArgumentException("No 'varFloat' Element (deserializing Data struct)");
    }
    el = (Element)list.item(0);
    ret.myFloat = new Float(DOMUtils.getChildCharacterData(el));
    
    list = root.getElementsByTagName("varString");
    if (list == null || list.getLength() == 0) {
      throw new IllegalArgumentException("No 'varString' Element (deserializing Data struct)");
    }
    el = (Element)list.item(0);
    ret.myString = ((Text)el.getFirstChild()).getData();
    
    return new Bean(Data.class, ret);
  }
}
