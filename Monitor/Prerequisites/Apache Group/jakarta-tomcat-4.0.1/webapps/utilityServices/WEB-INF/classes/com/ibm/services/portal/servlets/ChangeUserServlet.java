package com.ibm.services.portal.servlets;

import java.io.*;
import com.ibm.services.util.EnablingServicesUtilities;
import com.ibm.services.identity.models.IdentityModel;
import com.ibm.services.identity.exceptions.ChangeIdentityException;
import com.ibm.services.identity.IdentityService;
import javax.servlet.*;
import javax.servlet.http.*;

import org.apache.axis.encoding.BeanSerializer;
import javax.xml.rpc.namespace.QName;
import com.ibm.services.util.WSDLService;
import com.ibm.services.*;

public class ChangeUserServlet extends BaseServlet 
{
  public void doGet(HttpServletRequest request,HttpServletResponse response) 
    throws ServletException, IOException 
  {
    performTask(request, response);
  }

  public void doPost(HttpServletRequest request,HttpServletResponse response) 
    throws ServletException, IOException 
  {
    performTask(request, response);
  }

  public String getServletInfo() 
  {
    return super.getServletInfo();
  }

  public void init() 
  {
  }

  public void performTask(HttpServletRequest request, 
                          HttpServletResponse response) 
    throws IOException 
  {
    String targetPage;
    String dn;
    String ca;
    HttpSession session = request.getSession(false);
  
    if (session.isNew())  
      return;
       								
    try 
    {
      String userkey = (String)session.getValue(session.getId());

      // IdentityModel im = identityService.getIdentityDetails(userkey);

      // Get identity service
      WSDLService identityService = getService(IDENTITY);

      // DEBUG:
      // System.out.println("*** ChangeUserServlet.performTask: userkey:" + userkey);

      // Add deserializer
      identityService.addDeserializerFactory(new QName(ServiceConstants.NS_IDENTITY_TYPE, "identityModel"), IdentityModel.class, BeanSerializer.getFactory());

      // Get identityModel
      IdentityModel im = 
        (IdentityModel) identityService.invokeOperation("getIdentityDetails", 
                                                       new Object[] {userkey});
        	
      im.setName(request.getParameter("name"));
      im.setCompany(request.getParameter("company"));
      im.setAddress1(request.getParameter("address1"));
      im.setAddress2(request.getParameter("address2"));
      im.setAddress3(request.getParameter("address3"));
      im.setZipcode(request.getParameter("zipcode"));
      im.setPlace(request.getParameter("place"));
      im.setState(request.getParameter("state"));
      im.setCountry(request.getParameter("country"));
      im.setEmail(request.getParameter("email"));
        	
      dn = request.getParameter("dn");
      ca = request.getParameter("ca");
      if (ca.equals("[self signed]")) ca = dn;
      im.setDn(dn);
      im.setCa(ca);
        	
      // identityService.changeIdentity(im);	

      // Change identity
      identityService.invokeOperation("changeIdentity", 
                                      new Object[] {im});
    } 
    catch (Exception changeIdentityException) 
    {
      // DEBUG: 
      // System.out.println("EXCEPTION:");
      changeIdentityException.printStackTrace();

      // update Identity with new data
      targetPage = "body_show_failure_page.html";
      response.sendRedirect(targetPage);
    }

    targetPage = "customer_maintenance_ok.html";
    response.sendRedirect(targetPage);
  }
}
