<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
<META http-equiv="Content-Style-Type" content="text/css">
<TITLE>Create Requestor Contract</TITLE>
<LINK REL=STYLESHEET TYPE="text/css" HREF="style/style.css">
<script language="JavaScript">
  <!--
 function chkForm() {
  var check = confirm("Do you really want to create this Contract?");
  if (check == false) return false;
  else return true;
 }
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
// String[] identityList = IdentityService.getIdentityList();

 // Get access to service properties
 ServiceProperties serviceProps = new ServiceProperties();

 // Get service to invoke operations
 WSDLService identityService = serviceProps.getService(ServiceConstants.IDENTITY);
 WSDLService contractService = serviceProps.getService(ServiceConstants.CONTRACT);
 WSDLService paymentService = serviceProps.getService(ServiceConstants.PAYMENT);
 WSDLService accountingService = serviceProps.getService(ServiceConstants.ACCOUNTING);

 // Add deserializer
 identityService.addDeserializerFactory(new QName(ServiceConstants.NS_IDENTITY_TYPE, "identityModel"),
                                        IdentityModel.class, BeanSerializer.getFactory());

 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContract"),
                                        ProviderContractModel.class, BeanSerializer.getFactory());
 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "usageContract"),
                                        UsageContractModel.class, BeanSerializer.getFactory());
 // Add deserializer
 accountingService.addDeserializerFactory(new QName(ServiceConstants.NS_ACCOUNTING_TYPE, "ratingModel"),
                                          RatingModel.class,
                                          BeanSerializer.getFactory());
 // Add deserializer
 paymentService.addDeserializerFactory(new QName(ServiceConstants.NS_PAYMENT_TYPE, "paymentModel"),
                                       PaymentModel.class,
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
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=550>
<!--
 <TR>
  <TD HEIGHT=30></TD><TD></TD>
 </TR>
 -->
 <TR>
  <TD></TD>
  <TD ALIGN=CENTER><H3><U>Create Usage Contract [2]</U></H3></TD>
 </TR>
</table>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD WIDTH=200 HEIGHT=10></TD><TD WIDTH=300></TD>
 </TR>
 <TR>
  <TD STYLE="text-align: left;"><H4><U>Contract:</U></H4></TD>
  <TD><H4>
   <%//providerContractModel = (ProviderContractModel)ContractService.getContractDetails(request.getParameter("contractkey"));
     providerContractModel = (ProviderContractModel) contractService.invokeOperation("getProviderContract",
                                                              new Object[] {request.getParameter("contractkey")});
     if ( providerContractModel != null )
       out.println(providerContractModel.getDescription());
   %></H4></TD>
 </TR>
 <TR>
  <TD STYLE="text-align: left;"><b>Provider Name:</TD>
  <TD><b>
   <%
    // Get identity model
      IdentityModel identityModel = (IdentityModel) identityService.invokeOperation("getIdentityDetails", new Object[] {providerContractModel.getIdentitykey()});  
      //out.println(identityService.getIdentityDetails(providerContractModel.getIdentitykey()).getName());
      if ( identityModel != null ) out.println(identityModel.getName());
   %>
  </TD>
 </TR>
 <TR>
  <TD Height=10></TD><TD></TD>
 </TR>
 <tr>
  <td STYLE="text-align: left;"><b>Contract Availability:</TD>
  <td><b>from:&nbsp;</b><% out.println(providerContractModel.getStart()); %></td>
 </tr>
 <tr>
  <td></td>
  <td><b>until:&nbsp;</b><% out.println(providerContractModel.getEnd()); %></td>
 </tr>
 <TR>
  <TD Height=10></TD><TD></TD>
 </TR>
 <TR>
  <TD STYLE="text-align: left;"><b>Paymentmodel:</b></TD>
  <TD><b>
   <%//paymentModel = PaymentService.getPaymentModel(providerContractModel.getPaymentkey());
     paymentModel = (PaymentModel) paymentService.invokeOperation("getPaymentModel",
                                                   new Object[] {providerContractModel.getPaymentkey()});
     out.println(paymentModel.getDescription());%>
  </TD>
 </TR>
 <TR>
  <TD Height=10></TD><TD></TD>
 </TR>
 <TR>
  <TD STYLE="text-align: left;"><b>Rating(s):</TD>
  <td></td>
 </TR>
     <% ratingKeys = providerContractModel.getRatingkeys();
        HashMap ratingModelAttributes;
        for (int j=0; j<ratingKeys.length; j++)  {
         //ratingModel = AccountingServicegetRatingModel(ratingKeys[j]);
         ratingModel = (RatingModel) accountingService.invokeOperation("getRatingModel",
                                                                       new Object[] {ratingKeys[j]});
         ratingModelAttributes = ratingModel.getAttributes();
     %>
 <TR>
  <TD><b>&nbsp;<% out.println("Rating Model "+(j+1)+":"); %></b></TD>
  <TD><b><% out.println(ratingModel.getDescription()); %></TD>
 </TR>
     <%
         Iterator e = ratingModelAttributes.keySet().iterator();
         while (e.hasNext()) {
           String key = e.next().toString();
     %>
 <TR>
  <TD>&nbsp;&nbsp;<% out.println(key+":"); %></TD>
  <TD><% out.println(ratingModelAttributes.get(key)+" "+ratingModel.getCurrency()) ;%></TD>
 </TR>
    <%   } //end while
        } //end for %>
 <TR>
  <TD Height=10></TD><TD></TD>
 </TR>
</table>
<HR>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD width=125 height=20></TD><TD width=250></TD><TD width=125></TD>
 </TR>
     <% if (ratingKeys.length>1)  { %>
 <tr>
  <td colspan=3>
    <B>This contract provides more than one rating models. Please select the model which suites your
       needs!</B>
  </td>
 </tr>
 <TR>
  <TD height=20></TD><td></td><td></td>
 </TR>
 <TR>
  <td></td>
  <td align=center>
    <TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=245>
     <TR bgcolor="#4E6A9E" height=30 valign=middle align=center>
      <TH width=15></TH>
      <TH width=230><font color="#FFFFFF">Rating Model</font></TH>
     </TR>
      <FORM NAME="NewUserContractData" METHOD="POST" ACTION="CreateUserContract" onSubmit="return chkForm()">
       <input type=hidden name="contractkey" value=<%=providerContractModel.getContractkey()%>>
       <% for (int j=0; j<ratingKeys.length; j++)  {
          //ratingModel = AccountingService.getRatingModel(ratingKeys[j]); %>
          ratingModel = accountingService.invokeOperation("getRatingModel",
                           new Object[] {ratingKeys[j]}); %>
     <TR class=tableRow0 height=40 valign=middle align=center>
      <TD><input type=radio name="ratingkey" checked value=<%=ratingKeys[j]%>></TD>
      <TD STYLE="text-align: center;"><% out.println(ratingModel.getDescription()); %></TD>
     </TR>
      <% } //end j %>
    </TABLE>
  </td>
  <td></td>
 </tr>
 <tr>
  <td height=30></td><td></td><td></td>
 </tr>
   <% } else { %>
      <FORM NAME="NewUserContractData" METHOD="POST" ACTION="CreateUserContract" onSubmit="return chkForm()">
       <input type=hidden name="contractkey" value=<%=providerContractModel.getContractkey()%>>
       <input type=hidden name="ratingkey" value=<%=ratingKeys[0]%>
     <% } //end else %>
 <TR>
  <td></td>
  <TD align=center><input type=submit value="Submit Contract">
                   <input type=button value="Cancel" onClick="history.back()">
  <td></td>
 </TR>
      </FORM>
 <!--
 <TR>
  <TD Height=30></TD><td></td><td></td>
 </TR>
 -->
</TABLE>
</BODY>
</HTML>
