package samples.bidbuy.shared;

import java.io.*;
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
public class AddressSerializer implements Serializer, Deserializer
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

    Address addr = (Address)src;
    String name = addr.getName();
    String address = addr.getAddress();
    String city = addr.getCity();
    String state = addr.getState();
    String zipCode = addr.getZipCode();

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

    if (address != null)
    {
      xjmr.marshall(inScopeEncStyle,
                    String.class,
                    address,
                    "address",
                    sink,
                    nsStack,
                    ctx);

      sink.write(StringUtils.lineSeparator);
    }

    if (city != null)
    {
      xjmr.marshall(inScopeEncStyle,
                    String.class,
                    city,
                    "city",
                    sink,
                    nsStack,
                    ctx);

      sink.write(StringUtils.lineSeparator);
    }

    if (state != null)
    {
      xjmr.marshall(inScopeEncStyle,
                    String.class,
                    state,
                    "state",
                    sink,
                    nsStack,
                    ctx);

      sink.write(StringUtils.lineSeparator);
    }

    if (zipCode != null)
    {
      xjmr.marshall(inScopeEncStyle,
                    String.class,
                    zipCode,
                    "zipCode",
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
    Element addrElement = (Element)src;
    Element tempEl = DOMUtils.getFirstChildElement(addrElement);
    Address addr = new Address();

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

        addr.setName((String)param.getValue());
      }
      else if (tagName.equals("address"))
      {
        Bean bean = xjmr.unmarshall(inScopeEncStyle,
                                    RPCConstants.Q_ELEM_PARAMETER,
                                    tempEl,
                                    ctx);
        Parameter param = (Parameter)bean.value;

        addr.setAddress((String)param.getValue());
      }
      else if (tagName.equals("city"))
      {
        Bean bean = xjmr.unmarshall(inScopeEncStyle,
                                    RPCConstants.Q_ELEM_PARAMETER,
                                    tempEl,
                                    ctx);
        Parameter param = (Parameter)bean.value;

        addr.setCity((String)param.getValue());
      }
      else if (tagName.equals("state"))
      {
        Bean bean = xjmr.unmarshall(inScopeEncStyle,
                                    RPCConstants.Q_ELEM_PARAMETER,
                                    tempEl,
                                    ctx);
        Parameter param = (Parameter)bean.value;

        addr.setState((String)param.getValue());
      }
      else if (tagName.equals("zipCode"))
      {
        Bean bean = xjmr.unmarshall(inScopeEncStyle,
                                    RPCConstants.Q_ELEM_PARAMETER,
                                    tempEl,
                                    ctx);
        Parameter param = (Parameter)bean.value;

        addr.setZipCode((String)param.getValue());
      }

      tempEl = DOMUtils.getNextSiblingElement(tempEl);
    }

    return new Bean(Address.class, addr);
  }
}
