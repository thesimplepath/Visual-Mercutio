package com.ibm.services.portal.servlets;

import com.ibm.services.contract.ContractService;
import com.ibm.services.util.EnablingServicesUtilities;
import com.ibm.services.identity.models.IdentityModel;
import com.ibm.services.identity.IdentityService;

import com.ibm.services.util.WSDLService;
import com.ibm.services.ServiceConstants;
import com.ibm.services.ServiceProperties;

import com.ibm.wstk.WSTKConstants;
import com.ibm.wstk.util.Util;

import javax.servlet.*;
import javax.servlet.http.*;

import java.io.*;


/**
 * Base servlet.
 */
public class BaseServlet 
  extends HttpServlet 
  implements ServiceConstants
{
  // Get access to service properties
  ServiceProperties serviceProperties = new ServiceProperties();;
  

  public String getServletInfo() 
  {
    return super.getServletInfo();
  }


  protected WSDLService getService(String serviceName)  
  {
    // Get service
    return serviceProperties.getService(serviceName);
  }
}
