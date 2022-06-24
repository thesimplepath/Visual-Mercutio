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
public class ServiceSerializer implements Serializer, Deserializer
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

    Service svc = (Service)src;
    String serviceName = svc.getServiceName();
    String serviceUrl = svc.getServiceUrl();
    String serviceType = svc.getServiceType();
    String serviceWsdl = svc.getServiceWsdl();

    if (serviceName != null)
    {
      xjmr.marshall(inScopeEncStyle,
                    String.class,
                    serviceName,
                    "serviceName",
                    sink,
                    nsStack,
                    ctx);

      sink.write(StringUtils.lineSeparator);
    }

    if (serviceUrl != null)
    {
      xjmr.marshall(inScopeEncStyle,
                    String.class,
                    serviceUrl,
                    "serviceUrl",
                    sink,
                    nsStack,
                    ctx);

      sink.write(StringUtils.lineSeparator);
    }

    if (serviceType != null)
    {
      xjmr.marshall(inScopeEncStyle,
                    String.class,
                    serviceType,
                    "serviceType",
                    sink,
                    nsStack,
                    ctx);

      sink.write(StringUtils.lineSeparator);
    }

    if (serviceWsdl != null)
    {
      xjmr.marshall(inScopeEncStyle,
                    String.class,
                    serviceWsdl,
                    "serviceWsdl",
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
    Element svcElement = (Element)src;
    Element tempEl = DOMUtils.getFirstChildElement(svcElement);
    Service svc = new Service();

    while (tempEl != null)
    {
      String tagName = tempEl.getTagName();

      if (tagName.equals("serviceName"))
      {
        Bean bean = xjmr.unmarshall(inScopeEncStyle,
                                    RPCConstants.Q_ELEM_PARAMETER,
                                    tempEl,
                                    ctx);
        Parameter param = (Parameter)bean.value;

        svc.setServiceName((String)param.getValue());
      }
      else if (tagName.equals("serviceUrl"))
      {
        Bean bean = xjmr.unmarshall(inScopeEncStyle,
                                    RPCConstants.Q_ELEM_PARAMETER,
                                    tempEl,
                                    ctx);
        Parameter param = (Parameter)bean.value;

        svc.setServiceUrl((String)param.getValue());
      }
      else if (tagName.equals("serviceType"))
      {
        Bean bean = xjmr.unmarshall(inScopeEncStyle,
                                    RPCConstants.Q_ELEM_PARAMETER,
                                    tempEl,
                                    ctx);
        Parameter param = (Parameter)bean.value;

        svc.setServiceType((String)param.getValue());
      }
      else if (tagName.equals("serviceWsdl"))
      {
        Bean bean = xjmr.unmarshall(inScopeEncStyle,
                                    RPCConstants.Q_ELEM_PARAMETER,
                                    tempEl,
                                    ctx);
        Parameter param = (Parameter)bean.value;

        svc.setServiceWsdl((String)param.getValue());
      }

      tempEl = DOMUtils.getNextSiblingElement(tempEl);
    }

    return new Bean(Service.class, svc);
  }
}
