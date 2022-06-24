/*
 * $Log: DeleteProviderContractServlet.java,v $
 * Revision 1.5  2001/11/30 19:42:36  pbrittenham
 * Updates for contract service
 *
 * Revision 1.4  2001/11/30 19:23:49  pbrittenham
 * Contract service updates
 *
 * Revision 1.3  2001/11/30 15:17:28  pbrittenham
 * Removed static references to contract service
 *
 * Revision 1.2  2001/11/29 13:33:10  pbrittenham
 * Move utility services to WSTK src directory and update portal code.
 *
 * Revision 1.1  2001/11/16 23:15:48  pbrittenham
 * Add new demo for utility services
 *
 * Revision 1.4  2001/11/12 01:20:54  bruchlj
 * no message
 *
 * Revision 1.2  2001/10/31 10:51:45  bruchlj
 * no message
 *
 * Revision 1.1  2001/10/25 08:49:23  joret
 * Delete a Provider Contract according to the contractkey sent in the request
 *
 */
package com.ibm.services.portal.servlets;

import javax.servlet.*;
import javax.servlet.http.*;
import java.util.Properties;
import java.io.*;
import java.util.*;

import com.ibm.services.*;
import com.ibm.services.contract.exceptions.*;
import com.ibm.services.contract.models.*;
import com.ibm.services.util.*;

import org.apache.axis.encoding.BeanSerializer;
import javax.xml.rpc.namespace.QName;


/**
 *
 */
public class DeleteProviderContractServlet 
  extends BaseServlet 
{
   
	public void init(ServletConfig config) throws ServletException {
		super.init(config);
	}
	public void destroy() {}
	
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
							throws ServletException, java.io.IOException {
		processRequest(request, response);
	}
	protected void doPost(HttpServletRequest request, HttpServletResponse response)
							throws ServletException, java.io.IOException {
		processRequest(request, response);
	}
	public String getServletInfo() {
		return "Test Servlet ...";
	}

  protected void processRequest(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, java.io.IOException 
  {
		String targetPage;
		HttpSession session = request.getSession(false);
		if (session.isNew())  return;
		
		String strContractKey = request.getParameter("contractkey");
		targetPage = "body_provider_contracts.jsp";
		
    // Get service
    WSDLService contractService = getService(CONTRACT);

    //String[] contractList = ContractService.getContractListForProviderContract(strContractKey);
    
    // Check if ProviderContract is locked by an active or future UsageContract
    ArrayList ckArrayList = (ArrayList) contractService.invokeOperation("getContractKeyListForProviderContract", 
                                                                        new Object[] {strContractKey});

    // Get contract key list
    String[] contractList = (String[]) ckArrayList.toArray(new String[ckArrayList.size()]);

		if (contractList.length>0)  {
			targetPage = "body_provider_contract_delete_failed.html";
			response.sendRedirect(targetPage);
			return;
		}
		
                /*
		try  
                {
                  // ADD:
		  //ContractService.deleteContract(request.getParameter("contractkey"));
		} 
                
                catch(DeleteContractException dce)  
                {
			targetPage = "body_show_failure_page.html";			
		} 
                */  

		response.sendRedirect(targetPage);
	}
}
