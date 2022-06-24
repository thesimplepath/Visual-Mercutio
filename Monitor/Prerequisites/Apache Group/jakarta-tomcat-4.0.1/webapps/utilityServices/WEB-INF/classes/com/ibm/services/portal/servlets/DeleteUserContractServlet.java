package com.ibm.services.portal.servlets;

import com.ibm.services.*;
import com.ibm.services.util.*;
import com.ibm.services.contract.exceptions.DeleteContractException;
import com.ibm.services.util.EnablingServicesUtilities;

import org.apache.axis.encoding.BeanSerializer;
import javax.xml.rpc.namespace.QName;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class DeleteUserContractServlet 
  extends BaseServlet 
{

	public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		performTask(request, response);
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		performTask(request, response);
	}
	//Returns the servlet info string.
	public String getServletInfo() {
		return super.getServletInfo();
	}

	public void init() { }

	public void performTask(HttpServletRequest request,HttpServletResponse response) throws IOException {
	    String targetPage;

       	HttpSession session = request.getSession(true);
       	if (session.isNew())  return;
       	
        /*
       	try  {
          // ADD: Delete contract
       	   //ContractService.deleteContract(request.getParameter("contractkey"));
       	} catch(DeleteContractException dce)  {}   
        */
        
        // Get contract service
        WSDLService contractService = getService(CONTRACT);

        // Get user key
        String statusCode = (String) contractService.invokeOperation("deleteContract", 
                                                            new Object[] {request.getParameter("contractkey")});

       	targetPage = "body_user_contracts.jsp";
       	response.sendRedirect(targetPage);
	}
}
