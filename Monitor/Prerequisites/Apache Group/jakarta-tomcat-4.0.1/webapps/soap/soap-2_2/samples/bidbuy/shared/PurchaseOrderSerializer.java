package samples.bidbuy.shared;

import java.io.*;
import java.util.*;
import org.w3c.dom.*;
import org.apache.soap.*;
import org.apache.soap.encoding.soapenc.*;
import org.apache.soap.rpc.*;
import org.apache.soap.util.*;
import org.apache.soap.util.xml.*;
import samples.bidbuy.shared.*;

/**
 * @author Matthew J. Duftler (duftler@us.ibm.com)
 */
public class PurchaseOrderSerializer implements Serializer, Deserializer
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

    PurchaseOrder po = (PurchaseOrder)src;
    String poID = po.getPoID();
    Date createDate = po.getCreateDate();
    Address shipTo = po.getShipTo();
    Address billTo = po.getBillTo();
    LineItem[] items = po.getItems();

    if (poID != null)
    {
      xjmr.marshall(inScopeEncStyle,
                    String.class,
                    poID,
                    "poID",
                    sink,
                    nsStack,
                    ctx);

      sink.write(StringUtils.lineSeparator);
    }

    if (createDate != null)
    {
      xjmr.marshall(inScopeEncStyle,
                    Date.class,
                    createDate,
                    "createDate",
                    sink,
                    nsStack,
                    ctx);

      sink.write(StringUtils.lineSeparator);
    }

    if (shipTo != null)
    {
      xjmr.marshall(inScopeEncStyle,
                    Address.class,
                    shipTo,
                    "shipTo",
                    sink,
                    nsStack,
                    ctx);

      sink.write(StringUtils.lineSeparator);
    }

    if (billTo != null)
    {
      xjmr.marshall(inScopeEncStyle,
                    Address.class,
                    billTo,
                    "billTo",
                    sink,
                    nsStack,
                    ctx);

      sink.write(StringUtils.lineSeparator);
    }

    if (items != null)
    {
      Parameter param = new Parameter("items",
                                      LineItem[].class,
                                      items,
                                      null);

      xjmr.marshall(inScopeEncStyle,
                    Parameter.class,
                    param,
                    null,
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
    Element poElement = (Element)src;
    Element tempEl = DOMUtils.getFirstChildElement(poElement);
    PurchaseOrder po = new PurchaseOrder();

    while (tempEl != null)
    {
      String tagName = tempEl.getTagName();

      if (tagName.equals("poID"))
      {
        Bean bean = xjmr.unmarshall(inScopeEncStyle,
                                    RPCConstants.Q_ELEM_PARAMETER,
                                    tempEl,
                                    ctx);
        Parameter param = (Parameter)bean.value;

        po.setPoID((String)param.getValue());
      }
      else if (tagName.equals("createDate"))
      {
        Bean bean = xjmr.unmarshall(inScopeEncStyle,
                                    RPCConstants.Q_ELEM_PARAMETER,
                                    tempEl,
                                    ctx);
        Parameter param = (Parameter)bean.value;

        po.setCreateDate((Date)param.getValue());
      }
      else if (tagName.equals("shipTo"))
      {
        Bean bean = xjmr.unmarshall(inScopeEncStyle,
                                    RPCConstants.Q_ELEM_PARAMETER,
                                    tempEl,
                                    ctx);
        Parameter param = (Parameter)bean.value;

        po.setShipTo((Address)param.getValue());
      }
      else if (tagName.equals("billTo"))
      {
        Bean bean = xjmr.unmarshall(inScopeEncStyle,
                                    RPCConstants.Q_ELEM_PARAMETER,
                                    tempEl,
                                    ctx);
        Parameter param = (Parameter)bean.value;

        po.setBillTo((Address)param.getValue());
      }
      else if (tagName.equals("items"))
      {
        Bean bean = xjmr.unmarshall(inScopeEncStyle,
                                    RPCConstants.Q_ELEM_PARAMETER,
                                    tempEl,
                                    ctx);
        Parameter param = (Parameter)bean.value;

        po.setItems((LineItem[])param.getValue());
      }

      tempEl = DOMUtils.getNextSiblingElement(tempEl);
    }

    System.err.println("Returning: " + po);

    return new Bean(PurchaseOrder.class, po);
  }
}
