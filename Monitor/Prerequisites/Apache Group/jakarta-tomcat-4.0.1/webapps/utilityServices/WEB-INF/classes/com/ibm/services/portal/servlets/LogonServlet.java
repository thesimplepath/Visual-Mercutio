package com.ibm.services.portal.servlets;

import com.ibm.services.util.EnablingServicesUtilities;
import com.ibm.services.identity.models.IdentityModel;
import com.ibm.services.identity.IdentityService;

import com.ibm.services.util.WSDLService;

import com.ibm.wstk.WSTKConstants;

import javax.servlet.*;
import javax.servlet.http.*;

import java.io.*;


/**
 * Logon servlet.
 */
public class LogonServlet 
  extends BaseServlet 
{

  public final static String DEFAULT_IDENTITY_FILENAME = "/services/demos/utilityServices/client/identity.xml";
  String identityFilename = DEFAULT_IDENTITY_FILENAME;

	public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		performTask(request, response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		performTask(request, response);
	}

	public String getServletInfo() {
		return super.getServletInfo();
	}

	public void init() 
        {
          identityFilename = getInitParameter("identityFilename");
          if ((identityFilename == null) || (identityFilename.equals(""))) {
            identityFilename = DEFAULT_IDENTITY_FILENAME;
          }

          if (identityFilename.startsWith("/")) {
            identityFilename = WSTKConstants.WSTK_HOME + identityFilename;
          }
        }

	public void performTask(HttpServletRequest request,HttpServletResponse response) throws IOException 
        {
	  String targetPage ="";
	  String identityKey = "";
	  String userid = request.getParameter("userid");
       	  String passwd = request.getParameter("passwd");
       	  boolean logonOk = true;

    	  try 
          {
	    //userKey = IdentityService.getIdentitykeyForUserIDAndPassword(userid, passwd);

            // Get identity service
            WSDLService identityService = getService(IDENTITY);

            // DEBUG:
            // System.out.println("*** LogonServlet.performTask: userid:" + userid + ", passwd:" + passwd);

            // Get user key
            identityKey = (String) identityService.invokeOperation("getIdentityKey", 
                                                               new Object[] {userid, passwd});

            // If the identity key was not found, then throw exception
            if ((identityKey == null) || (identityKey.equals(""))) {
              throw new IllegalArgumentException("Userid or password were invalid.");
            }
	  } 

          catch (Exception e) 
          { 
            // DEBUG: 
            System.out.println("EXCEPTION:");
            e.printStackTrace();

            // no valid Identity, return to logon_failed
	    targetPage = "logon_failed.html";
	    response.sendRedirect(targetPage);
	    logonOk = false;
	  }
	    
	  if (logonOk) {   	
              HttpSession session = request.getSession(true); 
       	      session.putValue(session.getId(), identityKey);
              targetPage = "logon_ok.html";
              response.sendRedirect(targetPage);

              // Create entry for identity.xml file which contains the userid and password 
              String identity = "<?xml version=\"1.0\"?>" + 
                                "<identity:identity " +
                                "   xmlns:identity=\"http://tempuri.org/xsd/2001/12/Identity/\"" +
                                "   userid=\"" + userid + "\"" + 
                                "   passwd=\"" + passwd + "\"/>";

              // DEBUG:
              // System.out.println("*** LogonServlet.performTask: identityFilename: " + identityFilename);
              
              // Write out the file
              FileWriter fw = new FileWriter(identityFilename);

              // Write out the file
              fw.write(identity);

              // Close
              fw.close();
          }
	}
}
