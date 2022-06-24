/*
 * CreateProviderContractServlet.java
 *
 * Created on October 21, 2001, 6:02 PM
 */

/*
 * $Log: CreateProviderContractServlet.java,v $
 * Revision 1.9  2001/12/15 01:13:34  pbrittenham
 * Updates to get address book service working with utility services
 *
 * Revision 1.8  2001/12/13 19:44:07  pbrittenham
 * Utility services portal fixes
 *
 * Revision 1.7  2001/12/05 17:42:15  pbrittenham
 * Fix create and activate contract
 *
 * Revision 1.6  2001/12/03 07:36:57  pbrittenham
 * Updates for utility services
 *
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
 * Revision 1.8  2001/11/12 01:20:54  bruchlj
 * no message
 *
 * Revision 1.6  2001/10/31 10:51:45  bruchlj
 * no message
 *
 * Revision 1.5  2001/10/29 10:17:08  bruchlj
 * no message
 *
 * Revision 1.2  2001/10/25 08:08:49  joret
 * Added the Log Tag
 *
 */

package com.ibm.services.portal.servlets;

import com.ibm.services.*;
import com.ibm.services.util.*;
import com.ibm.services.contract.*;
import com.ibm.services.contract.models.*;

import org.apache.axis.encoding.BeanSerializer;
import javax.xml.rpc.namespace.QName;

import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;


public class CreateProviderContractServlet 
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
	/** Returns a short description of the servlet.
    */
	public String getServletInfo() {
		return super.getServletInfo();
	}
	

  protected void processRequest(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, java.io.IOException {

    //Date currentDate = new Date();
    Timestamp startdate = new Timestamp(0);

    String targetPage;
    HttpSession session = request.getSession(false);
		if (session.isNew())  return;

		String strDescription = request.getParameter("description");
		String strPayment = request.getParameter("payment");
		String[] strRating = request.getParameterValues("ratings");
                String strServiceName = request.getParameter("serviceName");
		String strContractKey = EnablingServicesUtilities.createUuid();
		String strUserKey = (String)session.getValue(session.getId());
		byte[] dummyValue = {};
     
		targetPage = "body_provider_contracts.jsp";
      
    try 
    {
	ProviderContractModel pcm = new ProviderContractModel(strContractKey,
				       		strUserKey,strPayment,startdate.toString(),startdate.toString(),
				         	dummyValue,dummyValue,dummyValue,dummyValue,
					 	strServiceName,strDescription,strRating);

      // Get service
      WSDLService contractService = getService(CONTRACT);

      // Add deserializer
      contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContract"), 
                                             ProviderContractModel.class, BeanSerializer.getFactory());
      // Add serializer
      contractService.addSerializer(ProviderContractModel.class, 
                                    new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContract"),
                                    new BeanSerializer(ProviderContractModel.class));
    
      //ContractService.createContract(pcm);
    
      // Get contract details
      String providerContractKey = (String) contractService.invokeOperation("createProviderContract", 
                                                                            new Object[] {pcm});

    } 
    
    catch (Exception e) {
			targetPage = "body_show_failure_page.html";
		 }
		response.sendRedirect(targetPage);
	}
}
