package com.ibm.services.portal.servlets;

import java.io.*;
import com.ibm.services.util.EnablingServicesUtilities;
import com.ibm.services.identity.models.IdentityModel;
import com.ibm.services.identity.exceptions.CreateIdentityException;
import com.ibm.services.identity.IdentityService;
import javax.servlet.*;
import javax.servlet.http.*;

import org.apache.axis.encoding.BeanSerializer;
import javax.xml.rpc.namespace.QName;
import com.ibm.services.util.WSDLService;
import com.ibm.services.*;

public class RegistrationServlet 
  extends BaseServlet 
{
  public IdentityModel checkParameters(ServletRequest req) 
    throws IllegalArgumentException 
  {
    String userkey = EnablingServicesUtilities.createUuid();
    String userid = req.getParameter("userid");
    String passwd = req.getParameter("passwd");
    String confPasswd = passwd; 								/*req.getParameter("confPasswd")*/
    String name = req.getParameter("name");
    String company = req.getParameter("company");
    String address1 = req.getParameter("address1");
    String address2 = req.getParameter("address2");
    String address3 = req.getParameter("address3");
    String zipcode = req.getParameter("zipcode");
    String place = req.getParameter("place");
    String state = req.getParameter("state");
    String country = req.getParameter("country");
    String email = req.getParameter("email");
    String curr = "";
    String dn = req.getParameter("dn");
    String ca = req.getParameter("ca");
  
    if (ca.equals("[self signed]")) 
      ca = dn;
    	
    if (userid == null || passwd == null || confPasswd == null) 
    {
      throw new IllegalArgumentException("one ore more required parameters have not been set");
    }

    if (userid.equals("")) 
    {
      throw new IllegalArgumentException("userid not specified");
    }

    if (passwd.equals("")) 
    {
      throw new IllegalArgumentException("password not specified");
    }

    if (!passwd.equals(confPasswd)) 
    {
      throw new IllegalArgumentException("passwords do not match");
    }

    return new IdentityModel(userkey,userid,passwd,name,company,address1,address2,address3,zipcode,place,state,country,email,curr,dn,ca);
  }

  public void doGet(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException 
  {
    performTask(request, response);
  }
  
  public void doPost(HttpServletRequest request, HttpServletResponse response)
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
    IdentityModel ii = new IdentityModel();
    String targetPage = "";
    boolean authorizationOk = true;
  
    try 
    {
      ii = checkParameters(request);

      // identityService.createIdentity(ii);

      // Get identity service
      WSDLService identityService = getService(IDENTITY);

      // DEBUG:
      // System.out.println("*** RegistrationServlet.performTask:");

      // Add serializer
      identityService.addSerializer(IdentityModel.class, new QName(ServiceConstants.NS_IDENTITY_TYPE, "identityModel"), new BeanSerializer(IdentityModel.class));

      // Create identity
      identityService.invokeOperation("createIdentity", new Object[] {ii});
    } 
    catch (Exception createIdentityException) 
    { 
      // DEBUG: 
      System.out.println("EXCEPTION:");
      createIdentityException.printStackTrace();

      // userId already registered?
      targetPage = "authorization_failed.html";
      response.sendRedirect(targetPage);
      authorizationOk = false;
    }
       	
    if (authorizationOk)  
    {
      targetPage = "authorization_ok.html";
      response.sendRedirect(targetPage);
    }        
  }
}
