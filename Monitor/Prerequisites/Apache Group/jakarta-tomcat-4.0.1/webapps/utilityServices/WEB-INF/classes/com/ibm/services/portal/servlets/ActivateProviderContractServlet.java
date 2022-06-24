package com.ibm.services.portal.servlets;

import com.ibm.services.*;
import com.ibm.services.contract.models.ProviderContractModel;
import com.ibm.services.util.EnablingServicesUtilities;
import com.ibm.services.util.WSDLService;

import org.apache.axis.encoding.BeanSerializer;
import javax.xml.rpc.namespace.QName;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
import java.sql.*;

public class ActivateProviderContractServlet 
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

	public void init() 
        {
        }

	public void performTask(HttpServletRequest request,HttpServletResponse response) throws IOException {
	    String targetPage;
	    Timestamp std = new Timestamp(0);
	    Timestamp etd = new Timestamp(0);

       	HttpSession session = request.getSession(true);
       	if (session.isNew())
       		return;
         
   		String startDay   = request.getParameter("startday"); 
   		String startMonth = request.getParameter("startmonth");
   		String startYear  = request.getParameter("startyear");
   		String endDay     = request.getParameter("endday");
   		String endMonth   = request.getParameter("endmonth");
   		String endYear    = request.getParameter("endyear");
   		String startDate  = startYear+"-"+startMonth+"-"+startDay+" 00:00:00.000000000";
   		String endDate    = endYear+"-"+endMonth+"-"+endDay+" 23:59:59.000000000";
   		 	
       	ProviderContractModel pcm = new ProviderContractModel();
       	
        // Get service
        WSDLService contractService = getService(CONTRACT);

        // Add deserializer
        contractService.addSerializer(ProviderContractModel.class,
		    new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContract"),
			new BeanSerializer(ProviderContractModel.class));
        contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContract"), 
                                               ProviderContractModel.class, BeanSerializer.getFactory());

        // Get contract details
       	pcm = (ProviderContractModel) contractService.invokeOperation("getProviderContract", 
                                                      new Object[] {request.getParameter("contractkey")});
       	
       	try  
        {
          // Change contract date
       	  contractService.invokeOperation("changeProviderContractDate", 
                                          new Object[] {pcm, startDate, endDate});
          /*
          // Change contract date
       	  contractService.invokeOperation("changeProviderContractDate", 
                                          new Object[] {pcm, Timestamp.valueOf(startDate), 
                                            Timestamp.valueOf(endDate)});
       	  */
        } 
        
        catch (Exception e)  {
       		e.printStackTrace();
       	}

       	targetPage = "body_provider_contracts.jsp";
       	response.sendRedirect(targetPage);
	}
}
