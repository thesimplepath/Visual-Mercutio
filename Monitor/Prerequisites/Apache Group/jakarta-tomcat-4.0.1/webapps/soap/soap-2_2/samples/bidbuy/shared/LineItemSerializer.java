package samples.bidbuy.shared;

import java.io.*;
import java.math.*;
import java.util.*;
import org.w3c.dom.*;
import org.apache.soap.*;
import org.apache.soap.encoding.soapenc.*;
import org.apache.soap.rpc.*;
import org.apache.soap.util.*;
import org.apache.soap.util.xml.*;

/**
 * @author Matthew J. Duftler (duftler@us.ibm.com)
 */
public class LineItemSerializer implements Serializer, Deserializer
{
  public void marshall(String inScopeEncStyle, Class javaType, Object src,
                       Object context, Writer sink, NSStack nsStack,
                       XMLJavaMappingRegistry xjmr, SOAPContext ctx)
    throws IllegalArgumentException, IOException
  {
    nsStack.pushScope();

    SoapEncUtils.generateStructureHeader(inScopeEncStyle,
                                         javaType,
                                         context,
                                         sink,
                                         nsStack,
                                         xjmr);

    sink.write(StringUtils.lineSeparator);

    LineItem lineItem = (LineItem)src;
    String name = lineItem.getName();
    int quantity = lineItem.getQuantity();
    BigDecimal price = lineItem.getPrice();

    if (name != null)
    {
      xjmr.marshall(inScopeEncStyle,
                    String.class,
                    name,
                    "name",
                    sink,
                    nsStack,
                    ctx);

      sink.write(StringUtils.lineSeparator);
    }

    xjmr.marshall(inScopeEncStyle,
                  int.class,
                  new Integer(quantity),
                  "quantity",
                  sink,
                  nsStack,
                  ctx);

    sink.write(StringUtils.lineSeparator);

    if (price != null)
    {
      xjmr.marshall(inScopeEncStyle,
                    BigDecimal.class,
                    price,
                    "price",
                    sink,
                    nsStack,
                    ctx);

      sink.write(StringUtils.lineSeparator);
    }

    sink.write("</" + context + '>');

    nsStack.popScope();
  }

  public Bean unmarshall(String inScopeEncStyle, QName elementType, Node src,
                         XMLJavaMappingRegistry xjmr, SOAPContext ctx)
    throws IllegalArgumentException
  {
    Element lineItemElement = (Element)src;
    Element tempEl = DOMUtils.getFirstChildElement(lineItemElement);
    LineItem lineItem = new LineItem();

    while (tempEl != null)
    {
      String tagName = tempEl.getTagName();

      if (tagName.equals("name"))
      {
        Bean bean = xjmr.unmarshall(inScopeEncStyle,
                                    RPCConstants.Q_ELEM_PARAMETER,
                                    tempEl,
                                    ctx);
        Parameter param = (Parameter)bean.value;

        lineItem.setName((String)param.getValue());
      }
      else if (tagName.equals("quantity"))
      {
        Bean bean = xjmr.unmarshall(inScopeEncStyle,
                                    RPCConstants.Q_ELEM_PARAMETER,
                                    tempEl,
                                    ctx);
        Parameter param = (Parameter)bean.value;

        lineItem.setQuantity(((Integer)param.getValue()).intValue());
      }
      else if (tagName.equals("price"))
      {
        Bean bean = xjmr.unmarshall(inScopeEncStyle,
                                    RPCConstants.Q_ELEM_PARAMETER,
                                    tempEl,
                                    ctx);
        Parameter param = (Parameter)bean.value;

        lineItem.setPrice((BigDecimal)param.getValue());
      }

      tempEl = DOMUtils.getNextSiblingElement(tempEl);
    }

    return new Bean(LineItem.class, lineItem);
  }
}
