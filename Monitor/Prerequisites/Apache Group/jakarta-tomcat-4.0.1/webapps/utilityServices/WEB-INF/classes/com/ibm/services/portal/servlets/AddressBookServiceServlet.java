/*
 * (C) Copyright IBM Corp. 2001  All rights reserved.
 *
 * US Government Users Restricted Rights Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * The program is provided "as is" without any warranty express or
 * implied, including the warranty of non-infringement and the implied
 * warranties of merchantibility and fitness for a particular purpose.
 * IBM will not be liable for any damages suffered by you as a result
 * of using the Program. In no event will IBM be liable for any
 * special, indirect or consequential damages or lost profits even if
 * IBM has been advised of the possibility of their occurrence. IBM
 * will not be liable for any third party claims against you.
 */
package com.ibm.services.portal.servlets;

import com.ibm.wstk.util.*;

import javax.servlet.*;
import javax.servlet.http.*;

import java.util.*;
import java.net.*;
import java.io.*;

import org.apache.axis.client.Service ;
import org.apache.axis.client.Call;
import org.apache.axis.encoding.BeanSerializer;
import org.apache.axis.message.SOAPBodyElement;
import org.apache.axis.utils.XMLUtils;
import javax.xml.rpc.namespace.QName;

import com.ibm.services.data.*;

/**
 * AddressBookService servlet.
 */
public class AddressBookServiceServlet 
  extends BaseServlet 
{
  public static final String OPERATIONS_PAGE_URL = 
    "/body_demo_addressbook.html";
  public static final String ADDRESSBOOKSERVICE_NAMESPACE = 
    "http://tempuri.org/wsdl/AddressBookService-impl";
  public static final String ADDRESSBOOKSERVICE_XSD_NAMESPACE = 
    "http://tempuri.org/xsd/AddressBook";
  public static final String SERVICE_NAME = "AddressBookService";
  public static String WSDL_SVC_IMPL_URL = 
    Util.formatURL("AddressBookService/AddressBookService-impl.wsdl");
  public static String PORT_NAME = "Demo";
  public static String ADDRESS_TYPE = "AddressType";
  public static String PHONE_NUMBER_TYPE = "phoneNumberType";
  public static String LISTING_TYPE = "ListingType";
  public static String OPERATION = "operation";
  public static String ADD_ENTRY = "addEntry";
  public static String LIST_ENTRY = "listEntry";
  public static String LIST_ALL = "listAll";
  public static String REMOVE_ENTRY = "removeEntry";
  public static String REMOVE_ALL = "removeAll";
  public static String NAME_TEXT_FIELD = "nameTextField";
  public static String STREET_NUM_TEXT_FIELD = "streetNumTextField";
  public static String STREET_NAME_TEXT_FIELD = "streetNameTextField";
  public static String CITY_TEXT_FIELD = "cityTextField";
  public static String STATE_TEXT_FIELD = "stateTextField";
  public static String ZIP_TEXT_FIELD = "zipTextField";
  public static String AREA_CODE_TEXT_FIELD = "areaCodeTextField";
  public static String EXCHANGE_TEXT_FIELD = "exchangeTextField";
  public static String NUMBER_TEXT_FIELD = "numberTextField";
  
  private Call call;
  private QName portQN;


  /**
   * Handles Post requests.
   *
   * @param request a <code>HttpServletRequest</code> value
   * @param response a <code>HttpServletResponse</code> value
   * @exception ServletException if an error occurs
   * @exception IOException if an error occurs
   */
  public void doPost(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException 
  {
    performTask(request, response);
  }


  /**
   * Initialize servlet.
   *
   */
  public void init() 
  {
    try 
    {
      // Create Axis stuff
      String   namespace = ADDRESSBOOKSERVICE_NAMESPACE;
      QName    serviceQN = new QName(namespace, SERVICE_NAME);
      Service  service   = new Service(new URL(WSDL_SVC_IMPL_URL), serviceQN );

      portQN = new QName(namespace, PORT_NAME);
      
      // This Call object will be reused for all invocations
      if (call == null) 
        call = (Call)service.createCall();
      
      // Add ser/deser for Address
      /////////////////////////////////////////////////////////////////////////
      String  ns = ADDRESSBOOKSERVICE_XSD_NAMESPACE;
      call.addSerializer( Address.class, new QName(ns, ADDRESS_TYPE), 
                          new BeanSerializer(Address.class));
      call.addDeserializerFactory( new QName(ns, ADDRESS_TYPE),
                                   Address.class, BeanSerializer.getFactory());
      
      // Add ser/deser for PhoneNumber
      /////////////////////////////////////////////////////////////////////////
      call.addSerializer( PhoneNumber.class, new QName(ns, PHONE_NUMBER_TYPE), 
                          new BeanSerializer(PhoneNumber.class));
      call.addDeserializerFactory( new QName(ns, PHONE_NUMBER_TYPE),
                                   PhoneNumber.class, BeanSerializer.getFactory());
      
      // Add ser/deser for Listing
      /////////////////////////////////////////////////////////////////////////
      call.addSerializer(Listing.class, new QName(ns, LISTING_TYPE), 
                         new BeanSerializer(Listing.class));
      call.addDeserializerFactory( new QName(ns, LISTING_TYPE),
                                   Listing.class, BeanSerializer.getFactory());
    }
    catch (Exception e) 
    {
      e.printStackTrace();
    }
  }

  /**
   * Main handler.
   *
   * @param request a <code>HttpServletRequest</code> value
   * @param response a <code>HttpServletResponse</code> value
   * @exception ServletException if an error occurs
   */
  public void performTask(HttpServletRequest request,
                          HttpServletResponse response) 
    throws ServletException 
  {
    String operation = request.getParameter(OPERATION);


    if (operation.startsWith(ADD_ENTRY)) 
      performAddEntry(request, response);
    else
      if (operation.startsWith(LIST_ENTRY)) 
        performListEntry(request, response);
      else
        if (operation.startsWith(LIST_ALL)) 
          performListAllEntries(request, response);
        else
          if (operation.startsWith(REMOVE_ENTRY)) 
            performRemoveEntry(request, response);
          else
            if (operation.startsWith(REMOVE_ALL)) 
              performRemoveAllEntries(request, response);
            else 
              throw new ServletException("Invalid operation requested");
  }

  /**
   * Handles addEntry operation.
   *
   * @param request a <code>HttpServletRequest</code> value
   * @param response a <code>HttpServletResponse</code> value
   */
  private void performAddEntry(HttpServletRequest request, 
                               HttpServletResponse response) 
  {
    String nameTextField = request.getParameter(NAME_TEXT_FIELD);
    String streetNumTextField = request.getParameter(STREET_NUM_TEXT_FIELD);
    String streetNameTextField = request.getParameter(STREET_NAME_TEXT_FIELD);
    String cityTextField = request.getParameter(CITY_TEXT_FIELD);
    String stateTextField = request.getParameter(STATE_TEXT_FIELD);
    String zipTextField = request.getParameter(ZIP_TEXT_FIELD);
    String areaCodeTextField = request.getParameter(AREA_CODE_TEXT_FIELD);
    String exchangeTextField = request.getParameter(EXCHANGE_TEXT_FIELD);
    String numberTextField = request.getParameter(NUMBER_TEXT_FIELD);
    StringWriter writer = new StringWriter();
    PrintWriter out = new PrintWriter(writer, true);

    try
    {
      if (nameTextField.equals(""))
        throw new Exception("Name field is empty");
              
      // Create phoneNumber object
      PhoneNumber phoneNumber = 
        new PhoneNumber(Integer.parseInt(areaCodeTextField),
                        exchangeTextField, numberTextField);

      // Create address object
      Address address = new Address(Integer.parseInt(streetNumTextField),
                                    streetNameTextField,
                                    cityTextField,
                                    stateTextField,
                                    Integer.parseInt(zipTextField),
                                    phoneNumber);

      // Invoke operation
      call.setOperation(portQN, ADD_ENTRY);
          
      String result = 
        (String)call.invoke(new Object[] {nameTextField, address});
          
      if (result == null) 
        throw new Exception();
      
      // Show result
      if (result.equals(StatusCodeType.SUCCESS)) 
        out.println("Entry " + nameTextField + " has been added.");
      else
        out.println("Problems adding entry " + nameTextField);
    }
    catch (Exception ex) 
    {
      out.println("Problems adding entry " + nameTextField);
      out.println(ex.getMessage());
    }

    // Send response
    sendResponse(request, response, writer);
  }

  /**
   * Handles listEntry operation.
   *
   * @param request a <code>HttpServletRequest</code> value
   * @param response a <code>HttpServletResponse</code> value
   */
  private void performListEntry(HttpServletRequest request,
                                HttpServletResponse response)
  {
    String nameTextField = request.getParameter(NAME_TEXT_FIELD);
    StringWriter writer = new StringWriter();
    PrintWriter out = new PrintWriter(writer, true);


    try 
    {
      call.setOperation(portQN, LIST_ENTRY);

      Address result = (Address) call.invoke(new Object[] {nameTextField});

      if (result != null) 
        out.println("Address:\n " + result + "\n");
      else      
        out.println("Entry not found!\n");
    }
    catch (Exception e) 
    {
      out.println("Problems listing entry " + nameTextField);
      out.println(e.getMessage());
    }

    // Send response
    sendResponse(request, response, writer);
  }

  /**
   * Handles listAllEntries operation.
   *
   * @param request a <code>HttpServletRequest</code> value
   * @param response a <code>HttpServletResponse</code> value
   */
  private void performListAllEntries(HttpServletRequest request,
                                     HttpServletResponse response)
  {
    StringWriter writer = new StringWriter();
    PrintWriter out = new PrintWriter(writer, true);


    try 
    {
      call.setOperation( portQN, LIST_ALL);
      
      ArrayList result = (ArrayList) call.invoke( new Object[] {} );

      if (result != null)
        for (int i = 0; i < result.size(); i++) 
        {
          out.println("Entry [" + i + "]:\n " + result.get(i));
          out.println("<br>");
        }
      else    
        out.println("Address book is empty!\n");

    }
    catch (Exception e) 
    {
      out.println("Problems listing all entries");
      out.println(e.getMessage());
    }    

    // Send response
    sendResponse(request, response, writer);
  }

  /**
   * Handles removeEntry operation.
   *
   * @param request a <code>HttpServletRequest</code> value
   * @param response a <code>HttpServletResponse</code> value
   */
  private void performRemoveEntry(HttpServletRequest request,
                                  HttpServletResponse response)
  {
    String nameTextField = request.getParameter(NAME_TEXT_FIELD);
    StringWriter writer = new StringWriter();
    PrintWriter out = new PrintWriter(writer, true);


    try 
    {
      call.setOperation(portQN, REMOVE_ENTRY);
      
      String result = (String)call.invoke(new Object[] {nameTextField});
      
      if (result == null) 
        throw new Exception();
      
      if (result.equals(StatusCodeType.SUCCESS)) 
        out.println("Entry " + nameTextField + " has been removed\n" );
      else
        out.println("Problems removing entry!\n");
    }
    catch (Exception e) 
    {
      out.println("Problems removing entry " + nameTextField);
      out.println(e.getMessage());
    }

    // Send response
    sendResponse(request, response, writer);
  }

  /**
   * Handles removeAllEntries operation.
   *
   * @param request a <code>HttpServletRequest</code> value
   * @param response a <code>HttpServletResponse</code> value
   */
  private void performRemoveAllEntries(HttpServletRequest request,
                                       HttpServletResponse response)
  {
    StringWriter writer = new StringWriter();
    PrintWriter out = new PrintWriter(writer, true);


    try 
    {
      call.setOperation( portQN, REMOVE_ALL);

      String result = (String)call.invoke( new Object[] {} );
      
      if (result == null) 
        throw new Exception();
      
      if (result.equals(StatusCodeType.SUCCESS)) 
        out.println("All entries have been removed\n");
      else
        out.println("Problems removing all entries!\n");
    }
    catch (Exception e) 
    {
      out.println("Problems removing all entries");
      out.println(e.getMessage());
    }    

    // Send response
    sendResponse(request, response, writer);
  }


  /**
   * Creates HTML response.
   *
   * @param request a <code>HttpServletRequest</code> value
   * @param response a <code>HttpServletResponse</code> value
   * @param writer a <code>Writer</code> value
   */
  private void sendResponse(HttpServletRequest request, 
                            HttpServletResponse response, Writer writer)
  {
    try 
    {
      response.setContentType("text/html");

      PrintWriter out = response.getWriter();
      
      out.println("<html>");
      out.println("<head>");
      out.println("<LINK REL=STYLESHEET TYPE=\"text/css\" HREF=\"style/style.css\">");
      out.println("</head>");
      out.println("<body>");

      out.println("<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=550>");

      out.println("<TR><TD></TD>");
      out.println("<TD HEIGHT=40></TD></TR>");

      out.println("<TR><TD>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</TD>");
      out.println("<TD ALIGN=CENTER><H3><U>Result</U></H3></TD></TR>");
      
      out.println("<TR><TD></TD>");
      out.println("<TD>" + writer.toString() + "</TD></TR>");
      
      out.println("<TR><TD></TD>");
      out.println("<TD HEIGHT=40></TD></TR>");

      out.println("<TR><TD></TD>");
      out.println("<TD><P><A href=\"" + request.getContextPath() + 
                  OPERATIONS_PAGE_URL + "\">Back</A></TD></TR>");
      
      out.println("</table>");
      out.println("</body></html>");
    }
    catch (IOException e) 
    {
      e.printStackTrace();
    }
  }
}
