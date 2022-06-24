<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
<META http-equiv="Content-Style-Type" content="text/css">
<TITLE>Provider Contract Deletion</TITLE>
<LINK REL=STYLESHEET TYPE="text/css" HREF="style/style.css">
<script language="JavaScript">
  <!--
  function chkForm() {
    var check = confirm("Do you really want to delete this Contract?");
    if (check == false) return false;
    else return true;
  }
  //-->
</script>
</HEAD>
<BODY TOPMARGIN=35 LEFTMARGIN=40 MARGINWIDTH=0 MARGINHEIGHT=0>

<%@page import="com.ibm.services.contract.*,
                com.ibm.services.contract.models.*,
                com.ibm.services.accounting.*,
                com.ibm.services.accounting.models.*,
                com.ibm.services.payment.*,
                com.ibm.services.payment.models.*,
                com.ibm.services.identity.*,
                com.ibm.services.identity.models.*,
                java.util.Date, java.text.DateFormat,
                com.ibm.services.*,
                com.ibm.services.util.*,
                org.apache.axis.encoding.BeanSerializer,
                javax.xml.rpc.namespace.QName,
                java.util.*"%>
<%@page session="true" %>
<%
 // Get access to service properties
 ServiceProperties serviceProps = new ServiceProperties();

 // Get service to invoke operations
 WSDLService identityService = serviceProps.getService(ServiceConstants.IDENTITY);
 WSDLService contractService = serviceProps.getService(ServiceConstants.CONTRACT);
 WSDLService paymentService = serviceProps.getService(ServiceConstants.PAYMENT);
 WSDLService accountingService = serviceProps.getService(ServiceConstants.ACCOUNTING);

 // Add deserializer
 identityService.addDeserializerFactory(new QName(ServiceConstants.NS_IDENTITY_TYPE, "identityModel"),
                                        IdentityModel.class,
                                        BeanSerializer.getFactory());
 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContract"),
                                        ProviderContractModel.class, BeanSerializer.getFactory());

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

 String[] identityList = (String[]) identityArrayList.toArray(new String[identityArrayList.size()]);

 boolean validSession = false;
 String sessionID = (String)session.getValue(session.getId());
 String ukey = (String)session.getValue(session.getId());


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

 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContractModel"),
                                        ProviderContractModel.class,
                                        BeanSerializer.getFactory());

 ProviderContractModel[] providerContracts = null ;

 // Get provider contract model
 ArrayList pcArrayList = (ArrayList) contractService.invokeOperation("getProviderContractList",
                                                                               new Object[] {});

 if ( pcArrayList != null )
   providerContracts = (ProviderContractModel[]) pcArrayList.toArray(new ProviderContractModel[pcArrayList.size()]);

 //String[] myContracts = ContractService.getContractListForIdentity(ukey);
 
 // Get contract list for identity
 ArrayList contractArrayList = (ArrayList) contractService.invokeOperation("getContractKeyListForIdentity", 
                                                                           new Object[] {ukey});

 String[] myContracts = (String []) ((contractArrayList == null) ? null :
             contractArrayList.toArray(new String[contractArrayList.size()]));

 ProviderContractModel providerContractModel = new ProviderContractModel();
 IdentityModel identityModel = new IdentityModel();
 PaymentModel paymentModel = new PaymentModel();
 RatingModel[] ratingModels;
 String[] ratingKeys;
 Date today = new Date();
 boolean noUsageContractModel = true;
 boolean atLeastOneProviderContract = false;
 int count = 0;
%>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD HEIGHT=30 WIDTH=100%></TD>
 </TR>
 <TR>
  <TD ALIGN=CENTER><H3><U>Provider Contract Deletion</U></H3></TD>
 </TR>
 <TR>
  <TD HEIGHT=20></TD>
 </TR>
 <TR>
  <TD><B>This table lists your Provider Contracts.
     <br>In order to delete a contract, select it from the list and press
         the delete button.</B>
  </TD>
 </TR>
 <TR>
  <TD HEIGHT=50></TD>
 </TR>
 <TR>
  <TD><P><B>Select a contract for deletion:</B></TD>
 </TR>
 <TR>
  <TD HEIGHT=15></TD>
 </TR>
  <% if (myContracts != null && myContracts.length > 0) { %>
 <TR>
  <TD>
   <FORM NAME="ContractData" METHOD="POST" ACTION="DeleteProviderContract" onSubmit="return chkForm()">
   <TABLE BORDER=0 CELLSPACING=2 CELLPADDING=0 WIDTH=540>
    <TR bgcolor="#4E6A9E" height=30 valign=middle>
     <TH WIDTH=15></TH>
     <TH WIDTH=175 align=center><font color="#FFFFFF">Contract</font></TH>
     <TH WIDTH=150 align=center><font color="#FFFFFF">Rating-Models</font></TH>
     <TH WIDTH=150 align=center><font color="#FFFFFF">Payment-Model</font></TH>
     <TH WIDTH=50 align=center><font color="#FFFFFF">Status</font></TH>
    </TR>
     <%for (int i=0; myContracts != null && i<myContracts.length; i++) {
        try {
          providerContractModel = (ProviderContractModel) contractService.invokeOperation("getProviderContract", 
                                                                                 new Object[] {myContracts[i]});
        } catch(ClassCastException cce) {            // if ContractModel is not a ProviderContractModel
           noUsageContractModel = false;
           continue; }
        if ( providerContractModel == null ) {
          noUsageContractModel = false ;
          continue ;
        }
        noUsageContractModel = true;
        atLeastOneProviderContract = true;
     %>
    <TR class=tableRow0 height=40 valign=middle>
     <TD><% if (count==0)  { %>
           <input type=radio name="contractkey" checked value=<%=myContracts[i]%>><%;%>
          <%} else {%>
            <input type=radio name="contractkey" value=<%=myContracts[i]%>><%; }
            count++;

            ratingKeys = providerContractModel.getRatingkeys();
            //paymentModel = PaymentService.getPaymentModel(providerContractModel.getPaymentkey());
            paymentModel = (PaymentModel)paymentService.invokeOperation("getPaymentModel",
                                new Object[] {providerContractModel.getPaymentkey()});
          %>
     </TD>
     <TD STYLE="text-align: center;"><P><% out.println(providerContractModel.getDescription()); %></TD>
     <TD STYLE="text-align: center;">
         <% for (int j=0; j<ratingKeys.length; j++)  {
             //out.println(AccountingService.getRatingModel(ratingKeys[j]).getDescription());
             out.println(((RatingModel)accountingService.invokeOperation("getRatingModel",
                           new Object[] {(ratingKeys[j])})).getDescription());
            } %>
     </TD>
     <TD STYLE="text-align: center;"><P><% out.println(paymentModel.getDescription()); %></TD>
     <TD STYLE="text-align: center;"><P>
         <%if (today.after(providerContractModel.startTimestamp()) && 
               today.before(providerContractModel.endTimestamp()))
             out.println("active");
           else  {
             if (providerContractModel.getStart().equals(providerContractModel.getEnd()))
               out.println("not activated");
             else  {
               if (today.after(providerContractModel.endTimestamp())) out.println("expired");
               if (today.before(providerContractModel.startTimestamp())) out.println("future");
             }
           } %>
     </TD>
    </TR>
     <% }  //end for%>
   </TABLE>
  </TD>
 </TR>
 <TR>
  <TD HEIGHT=100 ALIGN=CENTER>
   <% if (atLeastOneProviderContract) { %>
      <input type=submit value="Delete Contract">
      <input type=button value="Cancel" onClick="parent.body.location.href = 'body_provider_contracts.jsp'">
   <% } %>
  </TD>
 </TR>
  </FORM>
  <% } // end if { %>
 <TR>
  <TD align=center>
   <% if (!atLeastOneProviderContract) {%>
       <B><font color="red">There are no contracts available for deletion</font></B>
  </TD>
 </TR>
 </TR>
  <TD HEIGHT=30></TD><TD></TD><TD></TD>
 <TR>
 <TR>
  <TD align=center>
   <form><input type=button value="Cancel" onClick="parent.body.location.href = 'body_provider_contracts.jsp'"></form>
  </TD>
 </TR>
  <% } %>
</TABLE>
</BODY>
</HTML>
