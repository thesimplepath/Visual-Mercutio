package samples.addressbook2;

import java.io.*;
import org.w3c.dom.*;
import org.apache.soap.*;
import org.apache.soap.encoding.soapenc.*;
import org.apache.soap.rpc.*;
import org.apache.soap.util.*;
import org.apache.soap.util.xml.*;

public class AddressSerializer implements Serializer, Deserializer
{
  public void marshall(String inScopeEncStyle, Class javaType,
  Object src, Object context, Writer sink,
  NSStack nsStack, XMLJavaMappingRegistry xjmr, SOAPContext ctx)
  throws IllegalArgumentException, IOException
  {
    nsStack.pushScope();

    SoapEncUtils.generateStructureHeader(inScopeEncStyle, javaType, context,
      sink, nsStack, xjmr);

    sink.write(StringUtils.lineSeparator);

    samples.addressbook2.Address src2 = (samples.addressbook2.Address)src;
    Parameter param;

    param = new Parameter("streetNum", int.class, new Integer
      (src2.streetNum_Elem), null);
    xjmr.marshall(inScopeEncStyle, Parameter.class, param, null,
    sink, nsStack, ctx);
    sink.write(StringUtils.lineSeparator);

    param = new Parameter("streetName", java.lang.String.class,
      src2.streetName_Elem, null);
    xjmr.marshall(inScopeEncStyle, Parameter.class, param, null,
    sink, nsStack, ctx);
    sink.write(StringUtils.lineSeparator);

    param = new Parameter("city", java.lang.String.class, src2.city_Elem, null);
    xjmr.marshall(inScopeEncStyle, Parameter.class, param, null,
    sink, nsStack, ctx);
    sink.write(StringUtils.lineSeparator);

    param = new Parameter("state", java.lang.String.class, src2.state_Elem,
      null);
    xjmr.marshall(inScopeEncStyle, Parameter.class, param, null,
    sink, nsStack, ctx);
    sink.write(StringUtils.lineSeparator);

    param = new Parameter("zip", int.class, new Integer(src2.zip_Elem), null);
    xjmr.marshall(inScopeEncStyle, Parameter.class, param, null,
    sink, nsStack, ctx);
    sink.write(StringUtils.lineSeparator);

    param = new Parameter("phoneNumber", samples.addressbook2.Phone.class,
      src2.phoneNumber_Elem, null);
    xjmr.marshall(inScopeEncStyle, Parameter.class, param, null,
    sink, nsStack, ctx);
    sink.write(StringUtils.lineSeparator);


    sink.write("</" + context + '>');

    nsStack.popScope();
  }

  public Bean unmarshall(String inScopeEncStyle, QName elementType,
  Node src, XMLJavaMappingRegistry xjmr, SOAPContext ctx)
  throws IllegalArgumentException
  {
    Element root = (Element)src;
    Element tempEl = DOMUtils.getFirstChildElement(root);
    samples.addressbook2.Address target;

    try
    {
      target =
        (samples.addressbook2.Address)samples.addressbook2.Address.class.newInstance
        ();
    }
    catch (Exception e)
    {
      throw new IllegalArgumentException("Problem instantiating bean: "
        + e.getMessage());
    }

    while (tempEl != null)
    {
      Bean paramBean = xjmr.unmarshall(inScopeEncStyle,
      RPCConstants.Q_ELEM_PARAMETER,
      tempEl, ctx);
      Parameter param = (Parameter)paramBean.value;
      String tagName = tempEl.getTagName();


      if (tagName.equals("streetNum"))
      {
        target.streetNum_Elem = ((Integer)param.getValue()).intValue();
      }

      if (tagName.equals("streetName"))
      {
        target.streetName_Elem = (java.lang.String)param.getValue();
      }

      if (tagName.equals("city"))
      {
        target.city_Elem = (java.lang.String)param.getValue();
      }

      if (tagName.equals("state"))
      {
        target.state_Elem = (java.lang.String)param.getValue();
      }

      if (tagName.equals("zip"))
      {
        target.zip_Elem = ((Integer)param.getValue()).intValue();
      }

      if (tagName.equals("phoneNumber"))
      {
        target.phoneNumber_Elem = (samples.addressbook2.Phone)param.getValue();
      }


      tempEl = DOMUtils.getNextSiblingElement(tempEl);
    }

    return new Bean(samples.addressbook2.Address.class, target);
  }
}
