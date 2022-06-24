package samples.addressbook2;

import java.io.*;
import org.w3c.dom.*;
import org.apache.soap.*;
import org.apache.soap.encoding.soapenc.*;
import org.apache.soap.rpc.*;
import org.apache.soap.util.*;
import org.apache.soap.util.xml.*;

public class PhoneSerializer implements Serializer, Deserializer
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

    samples.addressbook2.Phone src2 = (samples.addressbook2.Phone)src;
    Parameter param;

    param = new Parameter("areaCode", int.class, new Integer
      (src2.areaCode_Elem), null);
    xjmr.marshall(inScopeEncStyle, Parameter.class, param, null,
    sink, nsStack, ctx);
    sink.write(StringUtils.lineSeparator);

    param = new Parameter("exchange", java.lang.String.class,
      src2.exchange_Elem, null);
    xjmr.marshall(inScopeEncStyle, Parameter.class, param, null,
    sink, nsStack, ctx);
    sink.write(StringUtils.lineSeparator);

    param = new Parameter("number", java.lang.String.class, src2.number_Elem,
      null);
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
    samples.addressbook2.Phone target;

    try
    {
      target =
        (samples.addressbook2.Phone)samples.addressbook2.Phone.class.newInstance
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


      if (tagName.equals("areaCode"))
      {
        target.areaCode_Elem = ((Integer)param.getValue()).intValue();
      }

      if (tagName.equals("exchange"))
      {
        target.exchange_Elem = (java.lang.String)param.getValue();
      }

      if (tagName.equals("number"))
      {
        target.number_Elem = (java.lang.String)param.getValue();
      }


      tempEl = DOMUtils.getNextSiblingElement(tempEl);
    }

    return new Bean(samples.addressbook2.Phone.class, target);
  }
}
