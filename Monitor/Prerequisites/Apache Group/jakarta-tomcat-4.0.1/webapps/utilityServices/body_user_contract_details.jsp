<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
<META http-equiv="Content-Style-Type" content="text/css">
<TITLE>Requestor Contract Details</TITLE>
<LINK REL=STYLESHEET TYPE="text/css" HREF="style/style.css">
<script language="JavaScript">
  <!--
 function goBack()  {
  parent.location.href = "user_contracts.html";
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
                com.ibm.services.metering.*,
                com.ibm.services.metering.events.*,
                com.ibm.services.metering.conditions.*,
                java.util.*,
                java.sql.*,
                com.ibm.services.*,
                com.ibm.services.util.*,
                org.apache.axis.encoding.BeanSerializer,
                javax.xml.rpc.namespace.QName" %>
<%@page session="true" %>
<%
// check if session is active and valid for Identity
// String[] identityList = IdentityService.getIdentityList();

 // Get access to service properties
 ServiceProperties serviceProps = new ServiceProperties();

 // Get service to invoke operations
 WSDLService identityService = serviceProps.getService(ServiceConstants.IDENTITY);
 WSDLService contractService = serviceProps.getService(ServiceConstants.CONTRACT);
 WSDLService paymentService = serviceProps.getService(ServiceConstants.PAYMENT);
 WSDLService accountingService = serviceProps.getService(ServiceConstants.ACCOUNTING);
 WSDLService meterService = serviceProps.getService(ServiceConstants.METERING);

 // Add deserializer
 identityService.addDeserializerFactory(new QName(ServiceConstants.NS_IDENTITY_TYPE, "identityModel"),
                                        IdentityModel.class, BeanSerializer.getFactory());
 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContract"),
                                        ProviderContractModel.class, BeanSerializer.getFactory());
 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "usageContract"),
                                        UsageContractModel.class,BeanSerializer.getFactory());
 // Add deserializer
 accountingService.addDeserializerFactory(new QName(ServiceConstants.NS_ACCOUNTING_TYPE, "ratingModel"),
                                          RatingModel.class,
                                          BeanSerializer.getFactory());
 // Add deserializer
 paymentService.addDeserializerFactory(new QName(ServiceConstants.NS_PAYMENT_TYPE, "paymentModel"),
                                       PaymentModel.class,
                                       BeanSerializer.getFactory());
 // Add deserializer
 meterService.addDeserializerFactory(new QName(ServiceConstants.NS_METERING_TYPE, "metereventext"),
                                       MeterEventExt.class,
                                       BeanSerializer.getFactory());
 // Add serializers
 meterService.addSerializer(ReportConditions.class,
                            new QName(ServiceConstants.NS_METERING_TYPE, "reportConditions"),
                            new BeanSerializer(ReportConditions.class));
 meterService.addSerializer(Columns.class,
                            new QName(ServiceConstants.NS_METERING_TYPE, "columns"),
                            new ColumnsSerializer());
 meterService.addSerializer(Operators.class,
                            new QName(ServiceConstants.NS_METERING_TYPE, "operators"),
                            new OperatorsSerializer());
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

 UsageContractModel usageContractModel = new UsageContractModel();
 ProviderContractModel providerContractModel = new ProviderContractModel();
 PaymentModel paymentModel = new PaymentModel();
 MeterEventExt[] meterEventsForUsageContract = null ;
 MeterEventExt[] meterEventsForProviderContract= null ;
 ReportConditions[] reportConditions = new ReportConditions[2];
 String currency;
%>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD HEIGHT=30></TD><TD></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD ALIGN=CENTER><H3><U>Requestor Contract Details</U></H3></TD>
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
   <%//usageContractModel = (UsageContractModel)ContractService.getContractDetails(request.getParameter("contractkey"));
     usageContractModel = (UsageContractModel) contractService.invokeOperation("getUsageContract",
                                                       new Object[] {request.getParameter("contractkey")});
     //providerContractModel = (ProviderContractModel)ContractService.getContractDetails(usageContractModel.getProvidercontractkey());
     providerContractModel = (ProviderContractModel) contractService.invokeOperation("getProviderContract",
                                                       new Object[] {usageContractModel.getProvidercontractkey()});
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
   <%out.println(usageContractModel.getStart());%>
  </TD>
 </TR>
 <TR>
  <TD></TD>
  <TD STYLE="text-align: left;"><b>End date:</TD>
  <TD><b>
   <%out.println(usageContractModel.getEnd());%>
  </TD>
 </TR>
 <TR>
  <TD Height=10></TD><TD></TD><TD></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD STYLE="text-align: left;"><b>Payment Model:</TD>
  <TD><b>
   <%//paymentModel = PaymentService.getPaymentModel(usageContractModel.getPaymentkey());
     paymentModel = (PaymentModel) paymentService.invokeOperation("getPaymentModel",
                             new Object[] {usageContractModel.getPaymentkey()});
     out.println(paymentModel.getDescription());%>
  </TD>
 </TR>
 <TR>
  <TD Height=10></TD><TD></TD><TD></TD>
 </TR>
   <% String ratingKey = usageContractModel.getRatingkey();
      //RatingModel ratingModel = AccountingService.getRatingModel(ratingKey);
      RatingModel ratingModel = (RatingModel)accountingService.invokeOperation("getRatingModel",
                                     new Object[] {ratingKey});
      HashMap usageContractAttributes = usageContractModel.getAttributes();
   %>
 <TR>
  <TD></TD>
  <TD><b>Rating Model:</b></TD>
  <TD><b><% out.println(ratingModel.getDescription()); %></b></TD>
 </TR>
    <% HashMap attrs = ratingModel.getAttributes();
       attrs.putAll(usageContractAttributes);
       Iterator e = attrs.keySet().iterator();
       while (e.hasNext()) {
        String key = e.next().toString();
    %>
 <TR>
  <TD></TD>
  <TD>&nbsp;<% out.println(key+":"); %></TD>
  <TD><% out.println(attrs.get(key)+" "+ratingModel.getCurrency()); %></TD>
 </TR>
    <% } //end while %>
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
  <TD STYLE="text-align: left;"><b>Requestor Key:</TD>
  <TD VALIGN=CENTER><b><font face="COURIER NEW" size="-1"><%out.println(usageContractModel.getIdentitykey());%></font></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD STYLE="text-align: left;"><b>UsageContract Key:</TD>
  <TD VALIGN=CENTER><b><font face="COURIER NEW" size="-1"><% out.println(usageContractModel.getContractkey());%></font></TD>
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
 <TR>
  <TD Height=10></TD><TD></TD><TD></TD>
 </TR>
</TABLE>
<HR>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD WIDTH=5 HEIGHT=25></TD><TD WIDTH=215></TD><TD WIDTH=200></TD><TD WIDTH=80></TD>
 </TR>
   <% // System.out.println("***JSP Generate ReportConditions");
      reportConditions[0] = new ReportConditions(Columns.REQUESTERIDENTITYKEY, Operators.EQUALS, usageContractModel.getIdentitykey());
     reportConditions[1] = new ReportConditions(Columns.PROVIDERCONTRACTKEY, Operators.EQUALS, providerContractModel.getContractkey());
     // System.out.println("***JSP invokeOperation getMeterEvents");
     //meterEventsForUsageContract = MeterService.getMeterEvents(reportConditions);
     ArrayList meArrayList = (ArrayList) meterService.invokeOperation("getMeterEvents",
                                                          new Object[] {reportConditions});
     if ( meArrayList != null )
       meterEventsForUsageContract = (MeterEventExt[]) meArrayList.toArray(new MeterEventExt[meArrayList.size()]);
     if (meterEventsForUsageContract == null || 
         meterEventsForUsageContract.length<1)  { %>
 <tr>
  <td colspan=4 align=center>
       <B><font color="red">There is currently no usage for this contract</font></B>
  </td
 </tr>
  <% } else { %>
 <TR>
  <TD></TD>
  <TD STYLE="text-align: left;"><H4><U>Usage:</U></H4></TD>
  <TD></TD>
  <TD></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD STYLE="text-align: center;"><B>from:</B></TD>
  <TD STYLE="text-align: center;"><B>till:</B></TD>
  <TD STYLE="text-align: center;"><B>Status:</B></TD>
 </TR>
    <% for (int i=0; i<meterEventsForUsageContract.length; i++) { %>
 <TR>
  <TD></TD>
  <TD ALIGN=LEFT>
         <%  if (meterEventsForUsageContract[i].getProviderContractkey().equals(providerContractModel.getContractkey()) &&
                 meterEventsForUsageContract[i].getTypeAsString().equals("StartTime"))
             {
               out.println(meterEventsForUsageContract[i].getDataTimestamp()); %>
  </TD>
  <TD ALIGN=LEFT>
           <%  out.println(meterEventsForUsageContract[i+2].getDataTimestamp()); %>
  </TD>
  <TD ALIGN=CENTER>
           <%  out.println(meterEventsForUsageContract[i+1].getTypeAsString()); %>
         <%  } // end if %>
  </TD>
   <%  } // end for
     }   // end else %>
 </TR>
 <TR>
  <TD HEIGHT=30></TD><TD></TD><TD></TD><TD></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD></TD>
  <TD ALIGN=LEFT><FORM><input type=button value="Return" onClick="goBack()"></FORM></TD>
  <TD></TD>
 </TR>
 <TR>
  <TD Height=30></TD><TD></TD><TD></TD><TD></TD>
 </TR>
 <TR>
</TABLE>
</BODY>
</HTML>
