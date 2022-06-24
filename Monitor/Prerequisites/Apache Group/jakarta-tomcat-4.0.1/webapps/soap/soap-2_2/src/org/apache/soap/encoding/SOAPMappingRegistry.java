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

package org.apache.soap.encoding;

import java.io.*;
import java.util.*;
import java.math.*;
import org.w3c.dom.*;
import org.apache.soap.util.*;
import org.apache.soap.util.xml.*;
import org.apache.soap.*;
import org.apache.soap.rpc.*;
import org.apache.soap.encoding.literalxml.*;
import org.apache.soap.encoding.soapenc.*;
import org.apache.soap.encoding.xmi.*;

/**
 * A <code>SOAPMappingRegistry</code> object is an
 * <code>XMLJavaMappingRegistry</code> with pre-registered
 * serializers and deserializers to support <em>SOAP</em>.
 *
 * @author Matthew J. Duftler (duftler@us.ibm.com)
 * @author Sanjiva Weerawarana (sanjiva@watson.ibm.com)
 * @author Francisco Curbera (curbera@us.ibm.com)
 * @author Sam Ruby (rubys@us.ibm.com)
 * @author Glen Daniels (gdaniels@allaire.com)
 */
public class SOAPMappingRegistry extends XMLJavaMappingRegistry
{
  private static final String soapEncURI = Constants.NS_URI_SOAP_ENC;
  
  private static final QName arrayQName = new QName(soapEncURI, "Array");

  private final StringDeserializer stringDeser = new StringDeserializer();
  private final IntDeserializer intDeser =  new IntDeserializer();
  private final DecimalDeserializer decimalDeser =  new DecimalDeserializer();
  private final FloatDeserializer floatDeser =  new FloatDeserializer();
  private final DoubleDeserializer doubleDeser =  new DoubleDeserializer();
  private final BooleanDeserializer booleanDeser =  new BooleanDeserializer();
  private final LongDeserializer longDeser =  new LongDeserializer();
  private final ShortDeserializer shortDeser =  new ShortDeserializer();
  private final ByteDeserializer byteDeser =  new ByteDeserializer();

  private final QNameSerializer qNameSer = new QNameSerializer();
  private final ParameterSerializer paramSer = new ParameterSerializer();
  private final ArraySerializer arraySer = new ArraySerializer();
  private final VectorSerializer vectorSer = new VectorSerializer();
  private final HashtableSerializer hashtableSer = new HashtableSerializer();
  public static final MimePartSerializer partSer = new MimePartSerializer();
  private final XMLParameterSerializer xmlParamSer =
                                                    new XMLParameterSerializer();
  private final DateSerializer dateSer = new DateSerializer();
  private final CalendarSerializer calSer = new CalendarSerializer();
  private final UrTypeDeserializer objDeser = new UrTypeDeserializer();
  
  /**
   * The following stuff is here to deal with the slight differences
   * between 1999 schema and 2000/10 schema.  This system allows us to
   * register type mappings for both sets of QNames, and to default to
   * whichever one is set as current.
   * 
   * !!! The order of the elements in these arrays is critical.  Be
   *     careful when editing.
   */
  QName schema1999QNames [] = {
    Constants.string1999QName,
    Constants.int1999QName,
    Constants.int1999QName,
    Constants.decimal1999QName,
    Constants.float1999QName,
    Constants.float1999QName,
    Constants.double1999QName,
    Constants.double1999QName,
    Constants.boolean1999QName,
    Constants.boolean1999QName,
    Constants.long1999QName,
    Constants.long1999QName,
    Constants.short1999QName,
    Constants.short1999QName,
    Constants.byte1999QName,
    Constants.byte1999QName,
    Constants.qName1999QName,
    Constants.date1999QName,
    Constants.timeInst1999QName,
    Constants.object1999QName,
    Constants.object1999QName,
    Constants.object1999QName,
    Constants.object1999QName,
    Constants.object1999QName,
  };
  
  QName schema2000QNames [] = {
    Constants.string2000QName,
    Constants.int2000QName,
    Constants.int2000QName,
    Constants.decimal2000QName,
    Constants.float2000QName,
    Constants.float2000QName,
    Constants.double2000QName,
    Constants.double2000QName,
    Constants.boolean2000QName,
    Constants.boolean2000QName,
    Constants.long2000QName,
    Constants.long2000QName,
    Constants.short2000QName,
    Constants.short2000QName,
    Constants.byte2000QName,
    Constants.byte2000QName,
    Constants.qName2000QName,
    Constants.date2000QName,
    Constants.timeInst2000QName,
    Constants.object2000QName,
    Constants.object2000QName,
    Constants.object2000QName,
    Constants.object2000QName,
    Constants.object2000QName,
  };
  
  QName schema2001QNames [] = {
    Constants.string2001QName,
    Constants.int2001QName,
    Constants.int2001QName,
    Constants.decimal2001QName,
    Constants.float2001QName,
    Constants.float2001QName,
    Constants.double2001QName,
    Constants.double2001QName,
    Constants.boolean2001QName,
    Constants.boolean2001QName,
    Constants.long2001QName,
    Constants.long2001QName,
    Constants.short2001QName,
    Constants.short2001QName,
    Constants.byte2001QName,
    Constants.byte2001QName,
    Constants.qName2001QName,
    Constants.date2001QName,
    Constants.timeInst2001QName,
    Constants.object2001QName,
    Constants.object2001QName,
    Constants.object2001QName,
    Constants.object2001QName,
    Constants.object2001QName,
  };

  public String schemaURI = Constants.NS_URI_1999_SCHEMA_XSD;
  QName [] schemaQNames = schema1999QNames;
  
  Class classes [] = {
    String.class,
    Integer.class,
    int.class,
    BigDecimal.class,
    Float.class,
    float.class,
    Double.class,
    double.class,
    Boolean.class,
    boolean.class,
    Long.class,
    long.class,
    Short.class,
    short.class,
    Byte.class,
    byte.class,
    QName.class,
    GregorianCalendar.class,
    Date.class,
    javax.mail.internet.MimeBodyPart.class,
    java.io.InputStream.class,
    javax.activation.DataSource.class,
    javax.activation.DataHandler.class,
    Object.class,
  };

  /*
    This serializer runs its content through a mechanism to replace
    the characters {&, ", ', <, >} with their appropriate escape
    sequences.
  */
  Serializer cleanSer = new Serializer()
  {
    public void marshall(String inScopeEncStyle, Class javaType, Object src,
                         Object context, Writer sink, NSStack nsStack,
                         XMLJavaMappingRegistry xjmr, SOAPContext ctx)
      throws IllegalArgumentException, IOException {
      nsStack.pushScope();

      SoapEncUtils.generateStructureHeader(inScopeEncStyle,
                                           javaType,
                                           context,
                                           sink,
                                           nsStack,
                                           xjmr);

      sink.write(Utils.cleanString(src.toString()) + "</" + context + '>');

      nsStack.popScope();
    }
  };

  /*
    This serializer does not apply escape sequences to its content.
    This serializer should be used for numbers and other things that
    will not have any of the following characters: {&, ", ', <, >}
  */
  Serializer ser = new Serializer()
  {
    public void marshall(String inScopeEncStyle, Class javaType, Object src,
                         Object context, Writer sink, NSStack nsStack,
                         XMLJavaMappingRegistry xjmr, SOAPContext ctx)
      throws IllegalArgumentException, IOException {
      nsStack.pushScope();

      SoapEncUtils.generateStructureHeader(inScopeEncStyle,
                                           javaType,
                                           context,
                                           sink,
                                           nsStack,
                                           xjmr);

      sink.write(src + "</" + context + '>');

      nsStack.popScope();
    }
  };

  Serializer serializers [] = {
    cleanSer,  // String
    ser,       // Integer
    ser,       // int
    ser,       // BigDecimal
    ser,       // Float
    ser,       // float
    ser,       // Double
    ser,       // double
    ser,       // Boolean
    ser,       // boolean
    ser,       // Long
    ser,       // long
    ser,       // Short
    ser,       // short
    ser,       // Byte
    ser,       // byte
    qNameSer,  // QName
    calSer,    // GregorianCalendar
    dateSer,   // Date
    partSer,   // MimeBodyPart
    partSer,   // InputStream
    partSer,   // DataSource
    partSer,   // DataHandler
    null,      // Object
  };

  Deserializer deserializers [] = {
    stringDeser,
    null,
    intDeser,
    decimalDeser,
    null,
    floatDeser,
    null,
    doubleDeser,
    null,
    booleanDeser,
    null,
    longDeser,
    null,
    shortDeser,
    null,
    byteDeser,
    qNameSer,
    calSer,
    dateSer,
    null,
    null,
    null,
    null,
    objDeser,
  };

  public SOAPMappingRegistry()
  {
    this(Constants.NS_URI_CURRENT_SCHEMA_XSD);
  }

  /**
   * Sets up serializers for the specified Schema typeset.
   * @param schemaURI Should be one of Constants.NS_URI_1999_SCHEMA_XSD,
   * Constants.NS_URI_2000_SCHEMA_XSD, or Constants.NS_URI_2001_SCHEMA_XSD.
   */
  public SOAPMappingRegistry(String schemaURI)
  {
    // Set up the correct "current" schema typeset.
    if (schemaURI.equals(Constants.NS_URI_1999_SCHEMA_XSD)) {
      schemaQNames = schema1999QNames;
      mapSchemaTypes(schema2000QNames, false);
      mapSchemaTypes(schema2001QNames, false);
    } else if (schemaURI.equals(Constants.NS_URI_2000_SCHEMA_XSD)) {
      schemaQNames = schema2000QNames;
      mapSchemaTypes(schema1999QNames, false);
      mapSchemaTypes(schema2001QNames, false);
    } else if (schemaURI.equals(Constants.NS_URI_2001_SCHEMA_XSD)) {
      schemaQNames = schema2001QNames;
      mapSchemaTypes(schema1999QNames, false);
      mapSchemaTypes(schema2000QNames, false);
    } else {
      System.err.println("WARNING: Unrecognized Schema URI '" + schemaURI +
                         "' specified.  Defaulting to '" + this.schemaURI +
                         "'.");
    }
    
    mapSchemaTypes(schemaQNames, true);
    
    // Register parameter serializer for SOAP-ENC encoding style.
    mapTypes(soapEncURI, RPCConstants.Q_ELEM_PARAMETER, Parameter.class,
             paramSer, paramSer);

    // Register array deserializer for SOAP-ENC encoding style.
    mapTypes(soapEncURI, arrayQName, null, null, arraySer);

    // Register parameter serializer for literal xml encoding style.
    mapTypes(Constants.NS_URI_LITERAL_XML, RPCConstants.Q_ELEM_PARAMETER,
             Parameter.class, xmlParamSer, xmlParamSer);

    try {
      Class XMISerializer = 
        Class.forName("org.apache.soap.util.xml.XMISerializer");
      Class XMIParameterSerializer =
        Class.forName("org.apache.soap.encoding.xmi.XMIParameterSerializer");

      // Register default serializers for XMI encoding style.
      mapTypes(Constants.NS_URI_XMI_ENC, null, null,
               (Serializer)XMISerializer.newInstance(),
               (Deserializer)XMIParameterSerializer.newInstance());

      // Register serializer for Parameter class - not deserializer!
      mapTypes(Constants.NS_URI_XMI_ENC, null, Parameter.class,
               (Serializer)XMIParameterSerializer.newInstance(), null);
    } catch (IllegalAccessException iae) {
    } catch (InstantiationException ie) {
    } catch (ClassNotFoundException cnfe) {
    } catch (NoClassDefFoundError ncdfe) {
      // If the class can't be loaded, continue without it...
    }

    /*
      Basic collection types - these should map fine to Perl, Python, C++...
      (but an encoding like this needs to be agreed upon)
    */
    mapTypes(soapEncURI, new QName(Constants.NS_URI_XML_SOAP, "Vector"),
             Vector.class, vectorSer, vectorSer);
    mapTypes(soapEncURI, new QName(Constants.NS_URI_XML_SOAP, "Map"),
             Hashtable.class, hashtableSer, hashtableSer);

    try {
      Class mapClass = Class.forName("java.util.Map");
      MapSerializer mapSer = new MapSerializer();

      mapTypes(soapEncURI, new QName(Constants.NS_URI_XML_SOAP, "Map"),
               mapClass, mapSer, mapSer);
    } catch (ClassNotFoundException cnfe) {
    } catch (NoClassDefFoundError ncdfe) {
      // If the class can't be loaded, continue without it...
    }

    /*
      Map a Java byte array to the SOAP-ENC:base64 subtype.
    */
    Base64Serializer base64Ser = new Base64Serializer();
    QName base64QName = new QName(soapEncURI, "base64");
    mapTypes(soapEncURI, base64QName, byte[].class, base64Ser, base64Ser);
  }
  
  /**
   * Map a set of schema types defined in the arrays above.  If
   * the "serialize" arg is set to true, we'll map the serializer
   * side (i.e. when output gets generated it'll be as those QNames),
   * otherwise we just do deserializers.
   */
  public void mapSchemaTypes(QName [] schemaQNames, boolean serialize)
  {    
    for (int i = 0; i < schemaQNames.length; i++) {
      QName qName = schemaQNames[i];
      Class cls = classes[i];
      Serializer ser = serialize ? serializers[i] : null;
      Deserializer dser = deserializers[i];
      
      mapTypes(soapEncURI, qName, cls, ser, dser);
    }
  }

  /**
   * This function overrides the one in XMLJavaMappingRegistry for the sole
   * purpose of returning SOAP-ENC:Array when javaType represents an array.
   * The XMLJavaMappingRegistry will be consulted first, and if no mapping
   * is found, SOAP-ENC:Array is returned. Obviously, this only applies when
   * the encoding style is soap encoding.
   */
  public QName queryElementType(Class javaType, String encodingStyleURI)
    throws IllegalArgumentException
  {
    try
    {
      return super.queryElementType(javaType, encodingStyleURI);
    }
    catch (IllegalArgumentException e)
    {
      if (javaType != null
          && (javaType.isArray())
          && encodingStyleURI != null
          && encodingStyleURI.equals(soapEncURI))
      {
        return arrayQName;
      }
      else
      {
        throw e;
      }
    }
  }

  /**
   * This function overrides the one in XMLJavaMappingRegistry for the sole
   * purpose of returning an ArraySerializer when javaType represents an
   * array. The XMLJavaMappingRegistry will be consulted first, and if no
   * serializer is found for javaType, ArraySerailizer is returned.
   * Obviously, this only applies when the encoding style is soap encoding.
   */
  public Serializer querySerializer(Class javaType, String encodingStyleURI)
    throws IllegalArgumentException
  {
    try
    {
      return super.querySerializer(javaType, encodingStyleURI);
    }
    catch (IllegalArgumentException e)
    {
      if (javaType != null
          && encodingStyleURI != null
          && encodingStyleURI.equals(soapEncURI))
      {
        if (javaType.isArray()) {
          return arraySer;
        }
      }
      throw e;
    }
  }
}
