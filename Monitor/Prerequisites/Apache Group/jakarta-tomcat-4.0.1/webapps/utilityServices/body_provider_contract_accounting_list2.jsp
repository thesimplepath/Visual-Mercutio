<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
<META http-equiv="Content-Style-Type" content="text/css">
<TITLE>Provider Contract Requestor Billing</TITLE>
<LINK REL=STYLESHEET TYPE="text/css" HREF="style/style.css">
</HEAD>
<BODY TOPMARGIN=35 LEFTMARGIN=40 MARGINWIDTH=0 MARGINHEIGHT=0>

<%@page import="com.ibm.services.*,
                com.ibm.services.contract.*,
                com.ibm.services.contract.models.*,
                com.ibm.services.accounting.*,
                com.ibm.services.accounting.models.*,
                com.ibm.services.accounting.exceptions.*,
                com.ibm.services.metering.*,
                com.ibm.services.metering.events.*,
                com.ibm.services.metering.conditions.*,
                com.ibm.services.payment.*,
                com.ibm.services.payment.models.*,
                com.ibm.services.payment.exceptions.*,
                com.ibm.services.identity.*,
                com.ibm.services.identity.models.*,
                com.ibm.services.util.*,
                org.apache.axis.encoding.BeanSerializer,
                javax.xml.rpc.namespace.QName,
                java.util.*,
                java.sql.*" %>
<%@page session="true" %>
<%
// check if session is active and valid for Identity
 //String[] identityList = IdentityService.getIdentityList();

 // Get access to service properties
 ServiceProperties serviceProps = new ServiceProperties();

 // Get service to invoke operations
 WSDLService identityService = serviceProps.getService(ServiceConstants.IDENTITY);
 WSDLService contractService = serviceProps.getService(ServiceConstants.CONTRACT);
 WSDLService paymentService  = serviceProps.getService(ServiceConstants.PAYMENT);
 WSDLService accountingService  = serviceProps.getService(ServiceConstants.ACCOUNTING);

 // Add deserializer
 identityService.addDeserializerFactory(new QName(ServiceConstants.NS_IDENTITY_TYPE, "identityModel"),
                                        IdentityModel.class,
                                        BeanSerializer.getFactory());
 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "usageContract"),
                                        UsageContractModel.class,
                                        BeanSerializer.getFactory());
 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContract"),
                                        ProviderContractModel.class,
                                        BeanSerializer.getFactory());
 // Add deserializer
 paymentService.addDeserializerFactory(new QName(ServiceConstants.NS_PAYMENT_TYPE, "paymentModel"),
                                       PaymentModel.class,
                                       BeanSerializer.getFactory());
 // Add deserializer
 accountingService.addDeserializerFactory(new QName(ServiceConstants.NS_ACCOUNTING_TYPE, "ratingModel"),
                                          RatingModel.class,
                                          BeanSerializer.getFactory());
 // Add deserializers
 accountingService.addDeserializerFactory(new QName(ServiceConstants.NS_ACCOUNTING_TYPE, "reportModelSample"),
                                          ReportModelSample.class,
                                          BeanSerializer.getFactory());
 accountingService.addDeserializerFactory(new QName(ServiceConstants.NS_ACCOUNTING_TYPE, "metereventext"),
                                          MeterEventExt.class,
                                          BeanSerializer.getFactory());

 // Get identity list
 ArrayList identityArrayList = (ArrayList) identityService.invokeOperation("getIdentityList", new Object[] {});

 String[] identityList = (String[]) identityArrayList.toArray(new String[identityArrayList.size()]);

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

 String providerContractKey = request.getParameter("providercontractkey");
 String userContractKey = request.getParameter("usercontractkey");

 UsageContractModel ucm = (UsageContractModel) contractService.invokeOperation("getUsageContract",
                                                                 new Object[] {userContractKey});
 //UsageContractModel ucm = (UsageContractModel)ContractService.getContractDetails(userContractKey);

 ProviderContractModel pcm = (ProviderContractModel) contractService.invokeOperation("getProviderContract",
                                                                 new Object[] {providerContractKey});
 //ProviderContractModel pcm = (ProviderContractModel)ContractService.getContractDetails(providerContractKey);

 IdentityModel im = (IdentityModel) identityService.invokeOperation("getIdentityDetails",
                                                                 new Object[] {ucm.getIdentitykey()});
 //IdentityModel im = IdentityService.getIdentityDetails(ucm.getIdentitykey());

 String ratingKey = ucm.getRatingkey();
 String paymentKey = ucm.getPaymentkey();
 String ratingDetails;
 HashMap userContractAttributes = ucm.getAttributes();
 //RatingModel ratingModel = AccountingService.getRatingModel(ratingKey);
 RatingModel ratingModel = (RatingModel) accountingService.invokeOperation("getRatingModel",
                                                              new Object[] {ratingKey});
 //PaymentModel paymentModel = PaymentService.getPaymentModel(paymentKey);
 PaymentModel paymentModel = (PaymentModel) paymentService.invokeOperation("getPaymentModel",
                                                              new Object[] {paymentKey});
%>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <!--
 <TR>
  <TD HEIGHT=30 WIDTH=100%></TD>
 </TR>
 -->
 <TR>
  <TD ALIGN=CENTER><H3><U>Accounting [3]</U></H3></TD>
 </TR>
 <TR>
  <TD HEIGHT=10></TD>
 </TR>
 <TR>
  <TD><B>This table lists the accounting and billing details for the selected user
            contract.</B>
  </TD>
 </TR>
</TABLE>
<TABLE BORDER=0 CELLSPACING=2 CELLPADDING=0 WIDTH=500 NOF=LY>
 <TR>
  <TD WIDTH=10 HEIGHT=50></TD><TD WIDTH=150></TD><TD WIDTH=340></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD><B>Customer:</B></TD>
  <TD><% out.println(im.getName()); %>
 </TR>
 <TR>
  <TD></TD><TD></TD>
  <TD><% out.println(im.getAddress1()); %>
 </TR>
 <TR>
  <TD></TD><TD></TD>
  <TD><% out.println(im.getPlace()+" "+im.getZipcode()+", "+im.getCountry()); %>
 </TR>
 <TR>
  <TD HEIGHT=10></TD><TD></TD><TD></TD>
 <TR>
  <TD></TD>
  <TD><B>Service:</B></TD>
  <TD><% out.println(pcm.getDescription()); %>
 </TR>
 <TR>
  <TD HEIGHT=20></TD><TD></TD><TD></TD>
 </TR>
</TABLE>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500 NOF=LY>
 <TR>
  <TD WIDTH=10></TD><TD WIDTH=150></TD><TD WIDTH=140></TD><TD WIDTH=200></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD><B>Rating:</B></TD>
  <TD>Rating Model:</TD>
  <TD><%out.println(ratingModel.getDescription());%></TD>
 </TR>
    <% HashMap attrs = ratingModel.getAttributes();
       attrs.putAll(userContractAttributes);
       Iterator i = attrs.keySet().iterator();
       while (i.hasNext()) {
        String key = i.next().toString();
    %>
 <TR>
  <TD></TD><TD></TD>
  <TD><%out.println(key+":");%></TD>
  <TD><%out.println(attrs.get(key)+" "+ratingModel.getCurrency());%></TD>
 </TR>
    <% } //end while %>
 <TR>
  <TD HEIGHT=10></TD><TD></TD><TD></TD><TD></TD>
 </TR>
</TABLE>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500 NOF=LY>
 <TR>
  <TD WIDTH=10></TD><TD WIDTH=150></TD><TD WIDTH=340></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD><B>Payment:</B></TD>
  <TD><%out.println(paymentModel.getDescription());%></TD>
 </TR>
 <TR>
  <TD HEIGHT=10></TD><TD></TD><TD></TD>
 </TR>
</TABLE>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD WIDTH=10></TD><TD WIDTH=150></TD><TD WIDTH=340></TD>
 </TR>
 <TR>
 <TR>
  <TD></TD>
  <TD><B>Billing:</B></TD>
  <TD></TD>
 </TR>
 <TR>
  <TD></TD><TD></TD>
  <TD>
   <%
    try  {
     //ReportModel reportModel = AccountingService.generateReport(userContractKey,ucm.getStart(),ucm.getEnd());
     ReportModel reportModel = (ReportModel) accountingService.invokeOperation("generateReport",
                               new Object[] {userContractKey,ucm.getStart(),ucm.getEnd()});
     ReportItem reportItem = reportModel.buildReportItem();
     out.println(reportItem.toHtmlTable(0,280,60,ratingModel.getCurrency()));
    } catch (Exception rme)  {
      rme.printStackTrace();
    }
   %>
  </TD>
 </TR>
 <TR>
  <TD HEIGHT=10></TD><TD></TD><TD></TD>
 </TR>
 <TR align=center>
  <TD colspan=3 HEIGHT=40><FORM><input type=button value="Return" onClick="history.back()"></FORM></TD>
 </TR>
</TABLE>
</BODY>
</HTML>
