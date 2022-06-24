package samples.bidbuy.client;

import java.io.*;
import java.math.*;
import java.net.*;
import java.util.*;
import org.apache.soap.*;
import org.apache.soap.encoding.*;
import org.apache.soap.encoding.soapenc.*;
import org.apache.soap.rpc.*;
import org.apache.soap.util.xml.*;
import samples.bidbuy.shared.*;

/**
 * @author Matthew J. Duftler (duftler@us.ibm.com)
 */
public class ApacheSoapV2 implements vInterface
{
  SOAPMappingRegistry smr = new SOAPMappingRegistry();

  {
    PurchaseOrderSerializer poSer = new PurchaseOrderSerializer();
    AddressSerializer addrSer = new AddressSerializer();
    LineItemSerializer lineItemSer = new LineItemSerializer();
    DoubleDeserializer doubleDeser = new DoubleDeserializer();
    StringDeserializer stringDeser = new StringDeserializer();
    ServiceSerializer serviceSer = new ServiceSerializer();
    ArraySerializer arraySer = new ArraySerializer();

    smr.mapTypes(Constants.NS_URI_SOAP_ENC,
                 new QName("http://www.soapinterop.org/Bid", "PurchaseOrder"),
                 PurchaseOrder.class,
                 poSer,
                 poSer);
    smr.mapTypes(Constants.NS_URI_SOAP_ENC,
                 new QName("http://www.soapinterop.org/Bid", "Address"),
                 Address.class,
                 addrSer,
                 addrSer);
    smr.mapTypes(Constants.NS_URI_SOAP_ENC,
                 new QName("http://www.soapinterop.org/Bid", "LineItem"),
                 LineItem.class,
                 lineItemSer,
                 lineItemSer);
    smr.mapTypes(Constants.NS_URI_SOAP_ENC,
                 new QName("http://www.soapinterop.org/Registry", "Service"),
                 Service.class,
                 serviceSer,
                 serviceSer);
    smr.mapTypes(Constants.NS_URI_SOAP_ENC,
                 new QName ("", "LookupResult"),
                 null,
                 null,
                 arraySer);
    smr.mapTypes(Constants.NS_URI_SOAP_ENC,
                 new QName ("", "LookupAsStringResult"),
                 null,
                 null,
                 stringDeser);
    smr.mapTypes(Constants.NS_URI_SOAP_ENC,
                 new QName ("", "RequestForQuoteResult"),
                 null,
                 null,
                 doubleDeser);
    smr.mapTypes(Constants.NS_URI_SOAP_ENC,
                 new QName ("", "SimpleBuyResult"),
                 null,
                 null,
                 stringDeser);
    smr.mapTypes(Constants.NS_URI_SOAP_ENC,
                 new QName ("", "BuyResult"),
                 null,
                 null,
                 stringDeser);
  }

  public void register(String registryURL, Service s) throws Exception
  {
    URL url = new URL(registryURL);

    // Build the call.
    Call call = new Call();

    call.setTargetObjectURI("http://www.soapinterop.org/Registry");
    call.setMethodName("Register");
    call.setEncodingStyleURI(Constants.NS_URI_SOAP_ENC);
    call.setSOAPMappingRegistry(smr);

    Vector params = new Vector();

    params.addElement(new Parameter("ServiceName",
                                    String.class,
                                    s.getServiceName(),
                                    null));
    params.addElement(new Parameter("ServiceURL",
                                    String.class,
                                    s.getServiceUrl(),
                                    null));
    params.addElement(new Parameter("ServiceType",
                                    String.class,
                                    s.getServiceType(),
                                    null));
    params.addElement(new Parameter("ServiceWSDL",
                                    String.class,
                                    s.getServiceWsdl(),
                                    null));
    call.setParams(params);

    Response resp = call.invoke(url, "http://www.soapinterop.org/Register");

    // Check the response.
    if (resp.generatedFault())
    {
      Fault fault = resp.getFault();

      throw new SOAPException(fault.getFaultCode(),
                              fault.getFaultString());
    }
  }

  public void unregister(String registryURL, String name) throws Exception
  {
    URL url = new URL(registryURL);

    // Build the call.
    Call call = new Call();

    call.setTargetObjectURI("http://www.soapinterop.org/Registry");
    call.setMethodName("Unregister");
    call.setEncodingStyleURI(Constants.NS_URI_SOAP_ENC);
    call.setSOAPMappingRegistry(smr);

    Vector params = new Vector();

    params.addElement(new Parameter("ServiceName", String.class, name, null));
    call.setParams(params);

    Response resp = call.invoke(url, "http://www.soapinterop.org/Unregister");

    // Check the response.
    if (resp.generatedFault())
    {
      Fault fault = resp.getFault();

      throw new SOAPException(fault.getFaultCode(),
                              fault.getFaultString());
    }
  }

  public Boolean ping(String serverURL) throws Exception
  {
    URL url = new URL(serverURL);

    // Build the call.
    Call call = new Call();

    call.setTargetObjectURI("http://www.soapinterop.org/Bid");
    call.setMethodName("Ping");
    call.setEncodingStyleURI(Constants.NS_URI_SOAP_ENC);
    call.setSOAPMappingRegistry(smr);

    Response resp = call.invoke(url, "http://www.soapinterop.org/Ping");

    // Check the response.
    if (resp.generatedFault())
    {
      Fault fault = resp.getFault();

      throw new SOAPException(fault.getFaultCode(),
                              fault.getFaultString());
    }
    else
    {
      return new Boolean(true);
    }
  }

  public Vector lookupAsString(String registryURL) throws Exception
  {
    URL url = new URL(registryURL);

    // Build the call.
    Call call = new Call();

    call.setTargetObjectURI("http://www.soapinterop.org/Registry");
    call.setMethodName("LookupAsString");
    call.setEncodingStyleURI(Constants.NS_URI_SOAP_ENC);
    call.setSOAPMappingRegistry(smr);

    Vector params = new Vector();

    params.addElement(new Parameter("ServiceType", String.class, "Bid", null));
    call.setParams(params);

    Response resp = call.invoke(url,
                                "http://www.soapinterop.org/LookupAsString");

    // Check the response.
    if (resp.generatedFault())
    {
      Fault fault = resp.getFault();

      throw new SOAPException(fault.getFaultCode(),
                              fault.getFaultString());
    }

    String res = (String)resp.getReturnValue().getValue();
    StringTokenizer lineParser = new StringTokenizer(res, "\n");
    Vector services = new Vector();

    while (lineParser.hasMoreTokens())
    {
      String          line       = (String)lineParser.nextElement();
      StringTokenizer wordParser = new StringTokenizer(line, "\t");
      Service         service    = null;

      for (int i = 0; wordParser.hasMoreTokens() && i < 4; i++)
      {
        switch(i)
        {
          case 0 : service = new Service();
                   if (services == null) services = new Vector();
                   services.add(service);
                   service.setServiceName((String)wordParser.nextToken());
                   break ;
          case 1 : service.setServiceUrl((String)wordParser.nextToken());
                   break ;
          case 2 : service.setServiceType((String)wordParser.nextToken());
                   break ;
          case 3 : service.setServiceWsdl((String)wordParser.nextToken());
                   break ;
        }
      }
    }

    return services;
  }

  public Service[] lookup(String registryURL) throws Exception
  {
    URL url = new URL(registryURL);

    // Build the call.
    Call call = new Call();

    call.setTargetObjectURI("http://www.soapinterop.org/Registry");
    call.setMethodName("Lookup");
    call.setEncodingStyleURI(Constants.NS_URI_SOAP_ENC);
    call.setSOAPMappingRegistry(smr);

    Vector params = new Vector();

    params.addElement(new Parameter("ServiceType", String.class, "Bid", null));
    call.setParams(params);

    Response resp = call.invoke(url,
                                "http://www.soapinterop.org/Lookup");

    // Check the response.
    if (resp.generatedFault())
    {
      Fault fault = resp.getFault();

      throw new SOAPException(fault.getFaultCode(),
                              fault.getFaultString());
    }

    return (Service[])resp.getReturnValue().getValue();
  }

  public double requestForQuote(String serverURL) throws Exception
  {
    URL url = new URL(serverURL);

    // Build the call.
    Call call = new Call();

    call.setTargetObjectURI("http://www.soapinterop.org/Bid");
    call.setMethodName("RequestForQuote");
    call.setEncodingStyleURI(Constants.NS_URI_SOAP_ENC);
    call.setSOAPMappingRegistry(smr);

    Vector params = new Vector();

    params.addElement(new Parameter("ProductName",
                                    String.class,
                                    "widget",
                                    null));
    params.addElement(new Parameter("Quantity",
                                    int.class,
                                    new Integer(10),
                                    null));
    call.setParams(params);

    Response resp = call.invoke(url,
                                "http://www.soapinterop.org/RequestForQuote");

    // Check the response.
    if (resp.generatedFault())
    {
      Fault fault = resp.getFault();

      throw new SOAPException(fault.getFaultCode(),
                              fault.getFaultString());
    }
    else
    {
      String result = resp.getReturnValue().getValue().toString();

      return new Double(result).doubleValue();
    }
  }

  public String simpleBuy(String serverURL, int quantity) throws Exception
  {
    URL url = new URL(serverURL);

    // Build the call.
    Call call = new Call();

    call.setTargetObjectURI("http://www.soapinterop.org/Bid");
    call.setMethodName("SimpleBuy");
    call.setEncodingStyleURI(Constants.NS_URI_SOAP_ENC);
    call.setSOAPMappingRegistry(smr);

    Vector params = new Vector();

    params.addElement(new Parameter("Address",
                                    String.class,
                                    "123 Main St.",
                                    null));
    params.addElement(new Parameter("ProductName",
                                    String.class,
                                    "widget",
                                    null));
    params.addElement(new Parameter("Quantity",
                                    int.class,
                                    new Integer(quantity),
                                    null));
    call.setParams(params);

    Response resp = call.invoke(url,
                                "http://www.soapinterop.org/SimpleBuy");

    // Check the response.
    if (resp.generatedFault())
    {
      Fault fault = resp.getFault();

      throw new SOAPException(fault.getFaultCode(),
                              fault.getFaultString());
    }
    else
    {
      return (String)resp.getReturnValue().getValue();
    }
  }

  public String buy(String serverURL, int quantity, int numItems, double price) 
    throws Exception
  {
    LineItem[] lineItems = new LineItem[numItems];

    for (int i = 0; i < numItems; i++)
    {
      lineItems[i] = new LineItem("Widget" + i,
                                  quantity,
                                  new BigDecimal(price));
    }

    PurchaseOrder po = new PurchaseOrder("PO1",
                                         new Date(),
                                         new Address("Mr Big",
                                                     "40 Wildwood Lane",
                                                     "Weston",
                                                     "CT",
                                                     "06883"),
                                         new Address("Mr Big's Dad",
                                                     "40 Wildwood Lane",
                                                     "Weston",
                                                     "CT",
                                                     "06883"),
                                         lineItems);

    return buy(serverURL, po);
  }

  public String buy(String serverURL, PurchaseOrder po) throws Exception
  {
    URL url = new URL(serverURL);

    // Build the call.
    Call call = new Call();

    call.setTargetObjectURI("http://www.soapinterop.org/Bid");
    call.setMethodName("Buy");
    call.setEncodingStyleURI(Constants.NS_URI_SOAP_ENC);
    call.setSOAPMappingRegistry(smr);

    Vector params = new Vector();

    params.addElement(new Parameter("PO",
                                    PurchaseOrder.class,
                                    po,
                                    null));
    call.setParams(params);

    Response resp = call.invoke(url,
                                "http://www.soapinterop.org/Buy");

    // Check the response.
    if (resp.generatedFault())
    {
      Fault fault = resp.getFault();

      throw new SOAPException(fault.getFaultCode(),
                              fault.getFaultString());
    }
    else
    {
      return (String)resp.getReturnValue().getValue();
    }
  }
}
