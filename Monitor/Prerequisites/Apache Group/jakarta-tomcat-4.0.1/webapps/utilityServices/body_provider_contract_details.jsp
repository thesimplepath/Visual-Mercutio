<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
<META http-equiv="Content-Style-Type" content="text/css">
<TITLE>Provider Contracts</TITLE>
<LINK REL=STYLESHEET TYPE="text/css" HREF="style/style.css">
<script language="JavaScript">
 <!--
 function goBack()  {
  parent.location.href = "provider_contracts.html";
 }
 //-->
</script>
</HEAD>
<BODY TOPMARGIN=35 LEFTMARGIN=40 MARGINWIDTH=0 MARGINHEIGHT=0>

<%@page import="com.ibm.services.contract.*,
                com.ibm.services.contract.models.*,
                com.ibm.services.identity.*,
                com.ibm.services.identity.models.*,
                com.ibm.services.payment.*,
                com.ibm.services.payment.models.*,
                com.ibm.services.accounting.*,
                com.ibm.services.accounting.models.*,
                java.util.*,
                java.sql.*,
                com.ibm.services.*,
                com.ibm.services.util.*,
                org.apache.axis.encoding.BeanSerializer,
                javax.xml.rpc.namespace.QName" %>
<%@page session="true" %>
<%
// check if session is active and valid for Identity
 //String[] identityList = IdentityService.getIdentityList();

 // Get access to service properties
 ServiceProperties serviceProps = new ServiceProperties();

 // Get service to invoke operations
 WSDLService identityService = serviceProps.getService(ServiceConstants.IDENTITY);
 WSDLService contractService = serviceProps.getService(ServiceConstants.CONTRACT);
 WSDLService paymentService = serviceProps.getService(ServiceConstants.PAYMENT);
 WSDLService accountingService = serviceProps.getService(ServiceConstants.ACCOUNTING);


 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContract"),
                                        ProviderContractModel.class,
                                        BeanSerializer.getFactory());
 // Add deserializer
 identityService.addDeserializerFactory(new QName(ServiceConstants.NS_IDENTITY_TYPE, "identityModel"),
                                        IdentityModel.class,
                                        BeanSerializer.getFactory());
 // Add deserializer
 paymentService.addDeserializerFactory(new QName(ServiceConstants.NS_PAYMENT_TYPE, "paymentModel"),
                                       PaymentModel.class,
                                       BeanSerializer.getFactory());
 // Add deserializer
 accountingService.addDeserializerFactory(new QName(ServiceConstants.NS_ACCOUNTING_TYPE, "ratingModel"),
                                          RatingModel.class,
                                          BeanSerializer.getFactory());

 // Get identity list
 ArrayList identityArrayList = (ArrayList) identityService.invokeOperation("getIdentityList", new Object[] {});

 // DEBUG:
 // System.out.println("ArrayList:" + identityArrayList.toString());
 // System.out.println("ArrayList.get(0):" + identityArrayList.get(0).getClass().getName());

 // This code was added because the identityArrayList.toArray() fails
 String[] identityList = new String[identityArrayList.size()];
 for (int i = 0; i < identityArrayList.size(); i++)
 {
   identityList[i] = (String) identityArrayList.get(i);
 }

// String[] identityList = (String[]) identityService.invokeOperation("getIdentityList", new Object[] {});

 boolean validSession = false;
 String sessionID = (String)session.getValue(session.getId());
 String ukey = (String)session.getValue(session.getId());

 // DEBUG:
 // System.out.println("sessionID:" + sessionID + ", ukey: " + ukey + ", getId:" + session.getId());

 for (int i=0;sessionID != null && i<identityList.length;i++)  {
   // DEBUG:
   // System.out.println("sessionID:" + sessionID + ", identityList[" + i + "]: " + identityList[i]);
  if (sessionID.equals(identityList[i])) {
    // DEBUG:
    // System.out.println("validSession");
   validSession = true;
   break;
  }
 }

 if (validSession==false)  {
  String targetPage = "body_no_session.html";
  response.sendRedirect(targetPage);
  return;
 }
 ProviderContractModel providerContractModel = new ProviderContractModel();
 PaymentModel paymentModel = new PaymentModel();
 RatingModel ratingModel = new RatingModel();
 RatingModel[] ratingModels;
 String[] ratingKeys;
 String currency;
%>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD HEIGHT=30></TD><TD></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD ALIGN=CENTER><H3><U>Provider Contract Details</U></H3></TD>
 </TR>
</table>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD WIDTH=5 HEIGHT=20></TD><TD WIDTH=190></TD><TD></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD STYLE="text-align: left;"><H4><U>Contract:</U></H4></TD>
  <TD><H4>
   <%//providerContractModel = (ProviderContractModel)ContractService.getContractDetails(request.getParameter("contractkey"));
     providerContractModel = (ProviderContractModel) contractService.invokeOperation("getProviderContract",
                                                          new Object[] {request.getParameter("contractkey")});
     out.println(providerContractModel.getDescription());
   %></H4></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD STYLE="text-align: left;"><b>Provider Name:</TD>
  <TD><b>
   <%
    // Get identity model
      IdentityModel identityModel = (IdentityModel) identityService.invokeOperation("getIdentityDetails", new Object[] {providerContractModel.getIdentitykey()});
      //out.println(identityService.getIdentityDetails(providerContractModel.getIdentitykey()).getName());
      out.println(identityModel.getName());
   %>
  </TD>
 </TR>
 <TR>
  <TD Height=10></TD><TD></TD><TD></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD STYLE="text-align: left;"><b>Start date:</TD>
  <TD><b>
   <%out.println(providerContractModel.getStart());%>
  </TD>
 </TR>
 <TR>
  <TD></TD>
  <TD STYLE="text-align: left;"><b>End date:</TD>
  <TD><b>
   <%out.println(providerContractModel.getEnd());%>
  </TD>
 </TR>
 <TR>
  <TD Height=10></TD><TD></TD><TD></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD STYLE="text-align: left;"><b>Payment Model:</TD>
  <TD><b>
   <%//paymentModel = PaymentService.getPaymentModel(providerContractModel.getPaymentkey());
     paymentModel = (PaymentModel) paymentService.invokeOperation("getPaymentModel",
                       new Object[] {providerContractModel.getPaymentkey()});
     out.println(paymentModel.getDescription());%>
  </TD>
 </TR>
 <TR>
  <TD Height=10></TD><TD></TD><TD></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD STYLE="text-align: left;"><b>Rating(s):</TD>
  <TD></TD>
 </TR>
    <% ratingKeys = providerContractModel.getRatingkeys();
       HashMap ratingModelAttributes;
       for (int j=0; j<ratingKeys.length; j++)  {
         //ratingModel = AccountingService.getRatingModel(ratingKeys[j]);
         ratingModel = (RatingModel) accountingService.invokeOperation("getRatingModel",
                          new Object[] {ratingKeys[j]});
         ratingModelAttributes = ratingModel.getAttributes();
    %>
 <TR>
  <TD></TD>
  <TD><b>&nbsp;<% out.println("Rating Model "+(j+1)+":"); %></b></TD>
  <TD><b><% out.println(ratingModel.getDescription()); %></TD>
 </TR>
    <%
         Iterator i = ratingModelAttributes.keySet().iterator();
         while (i.hasNext()) {
           String key = i.next().toString();
    %>
 <TR>
  <TD></TD>
  <TD>&nbsp;&nbsp;<% out.println(key+":"); %></TD>
  <TD><% out.println(ratingModelAttributes.get(key)+" "+ratingModel.getCurrency()) ;%></TD>
 </TR>
    <%   } //end while
       } // end for %>
 <TR>
  <TD Height=10></TD><TD></TD><TD></TD>
 </TR>
</TABLE>
<HR>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=600>
 <TR>
  <TD WIDTH=5 HEIGHT=15></TD><TD WIDTH=190></TD><TD></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD STYLE="text-align: left;"><H4><U>Keys:</U></H4></TD>
  <TD></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD STYLE="text-align: left;"><b>Provider Key:</TD>
  <TD VALIGN=CENTER><b><font face="COURIER NEW" size="-1"><% out.println(providerContractModel.getIdentitykey());%></font></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD STYLE="text-align: left;"><b>ProviderContract Key:</TD>
  <TD VALIGN=CENTER><b><font face="COURIER NEW" size="-1"><% out.println(providerContractModel.getContractkey());%></font></TD>
 </TR>
</table>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD HEIGHT=30></TD><TD></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD ALIGN=MIDDLE><FORM><input type=button value="Return" onClick="goBack()"></FORM></TD>
  <TD></TD>
 </TR>
 <TR>
  <TD Height=30></TD><TD></TD><TD></TD>
 </TR>
</TABLE>
</BODY>
</HTML>
