package com.ibm.services.portal.servlets;

import java.io.*;
import com.ibm.services.contract.models.UsageContractModel;
import com.ibm.services.contract.models.ProviderContractModel;
import com.ibm.services.identity.IdentityService;
import com.ibm.services.payment.models.PaymentModel;
import com.ibm.services.payment.PaymentService;

import com.ibm.services.*;
import com.ibm.services.util.*;
import org.apache.axis.encoding.BeanSerializer;
import javax.xml.rpc.namespace.QName;

import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
import java.sql.*;

public class CreateUserContractServlet 
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
	    java.util.Date today = new java.util.Date();
	    String targetPage;
	    Timestamp startdate = new Timestamp(0);
	    byte[] testByteArray = {};		//replace testByteArray with certificates and signatures
	    HashMap contractProperties = new HashMap();

       	HttpSession session = request.getSession(true);
       	if (session.isNew())  return;
           	
       	UsageContractModel ucm = new UsageContractModel();
       	
        //ProviderContractModel pcm = (ProviderContractModel)ContractService.getContractDetails(request.getParameter("contractkey"));
       	
        // Get service
        WSDLService contractService = getService(CONTRACT);

        // Add deserializer
        contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContract"), 
                                               ProviderContractModel.class, BeanSerializer.getFactory());
        // Add deserializer
        contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "usageContract"), 
                                               UsageContractModel.class, BeanSerializer.getFactory());
        
        // Add serializer
        contractService.addSerializer(ProviderContractModel.class, 
                                      new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContract"),
                                      new BeanSerializer(UsageContractModel.class));
        // Add serializer
        contractService.addSerializer(UsageContractModel.class, 
                                      new QName(ServiceConstants.NS_CONTRACT_TYPE, "usageContract"),
                                      new BeanSerializer(ProviderContractModel.class));
        
        // Get usage contract model
       	ProviderContractModel pcm = (ProviderContractModel) contractService.invokeOperation("getProviderContract", 
                                                              new Object[] {request.getParameter("contractkey")});
       	
       	
       	ucm.setIdentitykey((String)session.getValue(session.getId()));
       	ucm.setProvidercontractkey(request.getParameter("contractkey"));
       	ucm.setRatingkey(request.getParameter("ratingkey"));
       	ucm.setPaymentkey(pcm.getPaymentkey());
       	ucm.setIdentitycert(testByteArray);
       	ucm.setIdentitysig(testByteArray);
       	ucm.setProvidercert(testByteArray);
       	ucm.setProvidersig(testByteArray);
       	//ucm.setStart(startdate);
       	//ucm.setEnd(startdate);
       	ucm.setStart(startdate.toString());
       	ucm.setEnd(startdate.toString());
		ucm.setAttributes(contractProperties);
           	
       	//ContractService.createContract(ucm); //this creates the contractkey also

        String statusCode = (String) contractService.invokeOperation("createUsageContract", new Object[] {ucm});
       	
       	targetPage = "body_user_contracts.jsp";
       	response.sendRedirect(targetPage);
	}
}
