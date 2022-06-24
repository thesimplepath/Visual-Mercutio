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

package org.apache.soap.util.xml;

import java.io.*;
import java.util.*;
import org.w3c.dom.*;
import org.apache.soap.util.*;

/**
 * This class is a utility to serialize a DOM node as XML. This class
 * uses the <code>DOM Level 2</code> APIs.
 * The main difference between this class and DOMWriter is that this class
 * generates and prints out namespace declarations.
 *
 * @author Matthew J. Duftler (duftler@us.ibm.com)
 * @author Joseph Kesselman
 */
public class DOM2Writer
{
  /**
   * The namespaceURI represented by the prefix <code>xmlns</code>.
   */
  private static String NS_URI_XMLNS = "http://www.w3.org/2000/xmlns/";

  /**
   * Return a string containing this node serialized as XML.
   */
  public static String nodeToString(Node node)
  {
    StringWriter sw = new StringWriter();

    serializeAsXML(node, sw);

    return sw.toString();
  }

  /**
  * Serialize this node into the writer as XML.
  */
  public static void serializeAsXML(Node node, Writer writer)
  {
    print(node, null, new PrintWriter(writer));
  }

  private static void print(Node node, ObjectRegistry namespaceStack,
                            PrintWriter out)
  {
    if (node == null)
    {
      return;
    }

    boolean hasChildren = false;
    int type = node.getNodeType();

    switch (type)
    {
      case Node.DOCUMENT_NODE :
      {
        out.println("<?xml version=\"1.0\"?>");

        NodeList children = node.getChildNodes();

        if (children != null)
        {
          int numChildren = children.getLength();

          for (int i = 0; i < numChildren; i++)
          {
            print(children.item(i), namespaceStack, out);
          }
        }
        break;
      }

      case Node.ELEMENT_NODE :
      {
        namespaceStack = new ObjectRegistry(namespaceStack);

        out.print('<' + node.getNodeName());

        String elPrefix = node.getPrefix();
        String elNamespaceURI = node.getNamespaceURI();

        if (elPrefix != null && elNamespaceURI != null)
        {
          boolean prefixIsDeclared = false;

          try
          {
            String namespaceURI = (String)namespaceStack.lookup(elPrefix);

            if (elNamespaceURI.equals(namespaceURI))
            {
              prefixIsDeclared = true;
            }
          }
          catch (IllegalArgumentException e)
          {
          }

          if (!prefixIsDeclared)
          {
            printNamespaceDecl(node, namespaceStack, out);
          }
        }

        NamedNodeMap attrs = node.getAttributes();
        int len = (attrs != null) ? attrs.getLength() : 0;

        for (int i = 0; i < len; i++)
        {
          Attr attr = (Attr)attrs.item(i);

          out.print(' ' + attr.getNodeName() +"=\"" +
                    normalize(attr.getValue()) + '\"');

          String attrPrefix = attr.getPrefix();
          String attrNamespaceURI = attr.getNamespaceURI();

          if (attrPrefix != null && attrNamespaceURI != null)
          {
            boolean prefixIsDeclared = false;

            try
            {
              String namespaceURI = (String)namespaceStack.lookup(attrPrefix);

              if (attrNamespaceURI.equals(namespaceURI))
              {
                prefixIsDeclared = true;
              }
            }
            catch (IllegalArgumentException e)
            {
            }

            if (!prefixIsDeclared)
            {
              printNamespaceDecl(attr, namespaceStack, out);
            }
          }
        }

        NodeList children = node.getChildNodes();

        if (children != null)
        {
          int numChildren = children.getLength();

          hasChildren = (numChildren > 0);

          if (hasChildren)
          {
            out.print('>');
          }

          for (int i = 0; i < numChildren; i++)
          {
            print(children.item(i), namespaceStack, out);
          }
        }
        else
        {
          hasChildren = false;
        }

        if (!hasChildren)
        {
          out.print("/>");
        }
        break;
      }

      case Node.ENTITY_REFERENCE_NODE :
      {
        out.print('&');
        out.print(node.getNodeName());
        out.print(';');
        break;
      }

      case Node.CDATA_SECTION_NODE :
      {
        out.print("<![CDATA[");
        out.print(node.getNodeValue());
        out.print("]]>");
        break;
      }

      case Node.TEXT_NODE :
      {
        out.print(normalize(node.getNodeValue()));
        break;
      }

      case Node.COMMENT_NODE :
      {
        out.print("<!--");
        out.print(node.getNodeValue());
        out.print("-->");
        break;
      }

      case Node.PROCESSING_INSTRUCTION_NODE :
      {
        out.print("<?");
        out.print(node.getNodeName());

        String data = node.getNodeValue();

        if (data != null && data.length() > 0)
        {
          out.print(' ');
          out.print(data);
        }

        out.println("?>");
        break;
      }
    }

    if (type == Node.ELEMENT_NODE && hasChildren == true)
    {
      out.print("</");
      out.print(node.getNodeName());
      out.print('>');
      hasChildren = false;
    }
  }

  private static void printNamespaceDecl(Node node,
                                         ObjectRegistry namespaceStack,
                                         PrintWriter out)
  {
    switch (node.getNodeType())
    {
      case Node.ATTRIBUTE_NODE :
      {
        printNamespaceDecl(((Attr)node).getOwnerElement(), node,
                           namespaceStack, out);
        break;
      }

      case Node.ELEMENT_NODE :
      {
        printNamespaceDecl((Element)node, node, namespaceStack, out);
        break;
      }
    }
  }

  private static void printNamespaceDecl(Element owner, Node node,
                                         ObjectRegistry namespaceStack,
                                         PrintWriter out)
  {
    String namespaceURI = node.getNamespaceURI();
    String prefix = node.getPrefix();

    if (!(namespaceURI.equals(NS_URI_XMLNS) && prefix.equals("xmlns")))
    {
      if (DOMUtils.getAttributeNS(owner, NS_URI_XMLNS, prefix) == null)
      {
        out.print(" xmlns:" + prefix + "=\"" + namespaceURI + '\"');
      }
    }
    else
    {
      prefix = node.getLocalName();
      namespaceURI = node.getNodeValue();
    }

    namespaceStack.register(prefix, namespaceURI);
  }

  private static String normalize(String s)
  {
    StringBuffer str = new StringBuffer();
    int len = (s != null) ? s.length() : 0;

    for (int i = 0; i < len; i++)
    {
      char ch = s.charAt(i);

      switch (ch)
      {
        case '<' :
        {
          str.append("&lt;");
          break;
        }
        case '>' :
        {
          str.append("&gt;");
          break;
        }
        case '&' :
        {
          str.append("&amp;");
          break;
        }
        case '"' :
        {
          str.append("&quot;");
          break;
        }
        case '\n' :
        {
          if (i > 0)
          {
            char lastChar = str.charAt(str.length() - 1);

            if (lastChar != '\r')
            {
              str.append(StringUtils.lineSeparator);
            }
            else
            {
              str.append('\n');
            }
          }
          else
          {
            str.append(StringUtils.lineSeparator);
          }
          break;
        }
        default :
        {
          str.append(ch);
        }
      }
    }

    return (str.toString());
  }
}
