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
 * Reset servlet.
 */
public class ResetServlet 
  extends BaseServlet 
{
  final static String[] fileList= new String[] {"/services/utilities/accounting/server/ratings.xml",
                                                "/services/utilities/contract/server/contracts.xml",
                                                "/services/utilities/identity/server/identities.xml", 
                                                "/services/utilities/payment/server/payments.xml"};
  
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

  public String getServletInfo() {
    return super.getServletInfo();
  }

  public void init() 
  {
  }

  public void performTask(HttpServletRequest request,HttpServletResponse response) 
    throws IOException 
  {
    String targetPage ="";
    boolean resetOk = false;
    BufferedReader br;
    FileWriter fw;
    String nextLine;

    // Set default target page
    targetPage = "reset_failed.html";

    try 
    {
      for (int i = 0; i < fileList.length; i++) 
      {
       // Read the file
       br = new BufferedReader(new FileReader(WSTKConstants.WSTK_HOME + fileList[i] + ".orig"));

       // Get file writer
       fw = new FileWriter(WSTKConstants.WSTK_HOME + fileList[i]);

       while ((nextLine = br.readLine()) != null) 
       {
         // Write out the file
         fw.write(nextLine);
       }
                
       // Close
       fw.close();
     }

     // Reset done
     resetOk = true;
   } 

   catch (Exception e) 
   { 
     // DEBUG: 
     System.out.println("EXCEPTION:");
     e.printStackTrace();
     
     // no valid Identity, return to logon_failed
     targetPage = "reset_failed.html";
     response.sendRedirect(targetPage);
     resetOk = false;
   }
	    
   if (resetOk) 
   {   	
     targetPage = "reset_ok.html";
     response.sendRedirect(targetPage);
   }
 }
}
