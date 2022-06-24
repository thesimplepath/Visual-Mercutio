<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
<META http-equiv="Content-Style-Type" content="text/css">
<TITLE>Application Services</TITLE>
<BASE TARGET="_parent">
<LINK REL=STYLESHEET TYPE="text/css" HREF="style/style.css">
</HEAD>
<BODY TOPMARGIN=35 LEFTMARGIN=40 MARGINWIDTH=0 MARGINHEIGHT=0>

<%@page import="com.ibm.services.contract.*,
                com.ibm.services.contract.models.*,
                com.ibm.services.identity.*,
                com.ibm.services.identity.models.*,
                com.ibm.services.accounting.*,
                com.ibm.services.accounting.models.*,
                com.ibm.services.payment.*,
                com.ibm.services.payment.models.*,
                java.util.Date,
                com.ibm.wstk.WSTKConstants,
                com.ibm.services.*,
                com.ibm.services.util.*,
                org.apache.axis.encoding.BeanSerializer,
                org.apache.axis.client.*,
                org.apache.axis.configuration.*,
                org.apache.axis.utils.*,              
                javax.xml.rpc.namespace.QName,
                java.util.*" %>
<%@page session="true" %>
<%
 // Get access to service properties
 ServiceProperties serviceProps = new ServiceProperties();

 // Get service to invoke operations
 WSDLService identityService = serviceProps.getService(ServiceConstants.IDENTITY);
 WSDLService contractService = serviceProps.getService(ServiceConstants.CONTRACT);

 // Add deserializer
 identityService.addDeserializerFactory(new QName(ServiceConstants.NS_IDENTITY_TYPE, "identityModel"),
                                        IdentityModel.class,
                                        BeanSerializer.getFactory());

 // Get identity list
 ArrayList identityArrayList = (ArrayList) identityService.invokeOperation("getIdentityList", new Object[] {});

 String[] identityList = (String[]) identityArrayList.toArray(new String[identityArrayList.size()]);


 boolean validSession = false;
 String sessionID = (String)session.getValue(session.getId());
 String ukey = (String)session.getValue(session.getId());

 // DEBUG:
 //System.out.println("sessionID:" + sessionID + ", ukey: " + ukey + ", getId:" + session.getId());

 for (int i=0;sessionID != null && i<identityList.length;i++)  {
   // DEBUG:
   //System.out.println("sessionID:" + sessionID + ", identityList[" + i + "]: " + identityList[i]);
  if (sessionID.equals(identityList[i])) {
    // DEBUG:
    //System.out.println("validSession");
   validSession = true;
   break;
  }
 }

 if (validSession==false)  {
  String targetPage = "body_no_session.html";
  response.sendRedirect(targetPage);
  return;
 }

 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContract"),
                                        ProviderContractModel.class,
                                        BeanSerializer.getFactory());

 // Get provider contract model
 ArrayList pcArrayList = (ArrayList) contractService.invokeOperation("getProviderContractList", new Object[] {});

 ProviderContractModel[] providerContracts = (ProviderContractModel[]) pcArrayList.toArray(new ProviderContractModel[pcArrayList.size()]);

 // Get contract list for identity
 ArrayList ckArrayList = (ArrayList) contractService.invokeOperation("getProviderContractKeyListForIdentity",
                                                                               new Object[] {ukey});

 String[] myContracts = (String []) ckArrayList.toArray(new String[ckArrayList.size()]);

 ProviderContractModel providerContractModel = new ProviderContractModel();
 //PaymentModel paymentModel = new PaymentModel();
 //RatingModel[] ratingModels;
 //String[] ratingKeys;
 Date today = new Date();
 boolean noUsageContractModel = true;
 boolean atLeastOneProviderContract = false;

 
 String[] deployList = new String[] {"StockQuoteService",
                                     "AddressBookService"};
 
 // Deploy the client-side handlers
 for (int i = 0; i < deployList.length; i++) {
   // Deploy client-side handlers
   Admin.main(new String[] {"client", WSTKConstants.WSTK_HOME + "/services/applications/" + 
                                      deployList[i] + "/deployment/client_deploy.xml"});
 }
 
 
%>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=550>
 <!--
 <TR>
  <TD HEIGHT=30></TD>
 </TR>
 -->
 <TR>
  <TD ALIGN=CENTER><H3><U>Application Services</U></H3></TD>
 </TR>
 <TR>
  <TD HEIGHT=10></TD>
 </TR>
 <TR>
  <TD><P><B>You have a contract to use one of the following services.
            Select the service that you'd like to use.</B></TD>
 </TR>
 <TR>
  <TD HEIGHT=30></TD>
 </TR>
  <% if (myContracts.length > 0) { %>
 <TR><TD><UL>
     <%for (int i = 0; i < myContracts.length; i++) {
        try {
          //providerContractModel = (ProviderContractModel)ContractService.getContractDetails(myContracts[i]);
          providerContractModel = (ProviderContractModel) contractService.invokeOperation("getProviderContract",
                                                                              new Object[] {myContracts[i]});
        } catch(ClassCastException cce) {      // if ContractModel is not a ProviderContractModel
           noUsageContractModel = false;
           continue;
          }

        if (providerContractModel == null) {
          noUsageContractModel = false;
          atLeastOneProviderContract = false;
          continue;
        }

        noUsageContractModel = true;
        atLeastOneProviderContract = true;
        String href;
        String desc = providerContractModel.getDescription();
        String descLowerCase = desc.toLowerCase();

        if ((descLowerCase.indexOf("stock quote") != -1) || (descLowerCase.indexOf("stockquote") != -1))
           href = "body_demo_stockquote.jsp";
        else if ((descLowerCase.indexOf("address book") != -1) || (descLowerCase.indexOf("addressbook") != -1))
          href = "body_demo_addressbook.html";
        else
          href = "body_demo_unknown.html";
     %>
     <LI>
     <A HREF="<%=href%>" target="body"><%=desc%></A>
     </LI>
     <% }  // end for %>
     </UL>
     </TD>
    </TR>
     <% }  // end if %>
   </TABLE>
</BODY>
</HTML>
