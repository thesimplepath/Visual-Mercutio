<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
<META http-equiv="Content-Style-Type" content="text/css">
<TITLE>Requestor Contracts</TITLE>
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
                com.ibm.services.*,
                com.ibm.services.util.*,
                org.apache.axis.encoding.BeanSerializer,
                javax.xml.rpc.namespace.QName,
                java.util.*" %>
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
 //ProviderContractModel[] providerContracts = ContractService.getProviderContractsDetailed();

 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContract"),
                                        ProviderContractModel.class,
                                        BeanSerializer.getFactory());

 // Get provider contract model
 //ArrayList pcArrayList = (ArrayList) contractService.invokeOperation("getProviderContractList", 
 //                                                                    new Object[] {});

 //ProviderContractModel[] providerContracts = (ProviderContractModel[]) pcArrayList.toArray(new ProviderContractModel[pcArrayList.size()]);

 //String[] myContracts = ContractService.getContractListForIdentity(ukey);
 
 // Get contract list for identity (which should be a service provider identity)
 ArrayList ckArrayList = (ArrayList) contractService.invokeOperation("getContractKeyListForIdentity",
                                                                               new Object[] {ukey});

 String[] myContracts = (String []) ckArrayList.toArray(new String[ckArrayList.size()]);

 ProviderContractModel providerContractModel = new ProviderContractModel();
 PaymentModel paymentModel = new PaymentModel();
 RatingModel[] ratingModels;
 String[] ratingKeys;
 Date today = new Date();
 boolean noUsageContractModel = true;
 boolean atLeastOneProviderContract = false;
 int count = 0;
%>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=550>
 <!--
 <TR>
  <TD HEIGHT=30></TD>
 </TR>
 -->
 <TR>
  <TD ALIGN=CENTER><H3><U>Provider Contracts</U></H3></TD>
 </TR>
 <TR>
  <TD HEIGHT=10></TD>
 </TR>
 <TR>
  <TD><P><B>In order to sell services to customers (service requestors), you provide
            service contracts which can be signed by these customers.
            Such a contract comprises a service description, a rating model which is
            used for billing and a payment model (e.g. credit card payment).</b>
      <P><b>You may now create new provider contracts, or review, activate and
            delete existing provider contracts.</B></TD>
 </TR>
 <TR>
  <TD HEIGHT=10></TD>
 </TR>
 <TR>
  <TD>
    <TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=550>
     <tr>
      <td width=130></td><td width=420></td>
     </tr>
     <tr>
      <td></td>
      <td align=left>
      <UL>
      <LI><B><A HREF="body_provider_contract_create.jsp" target="body"><u>Create</u> a new provider contract</A></B></LI>
      <LI><B><A HREF="body_provider_contract_activation.jsp" target="body"><u>Activate</u> a provider contract</A></B></LI>
      <LI><B><A HREF="body_provider_contract_delete.jsp" target="body"><u>Delete</u> a provider contract</A></B></LI>
      </UL>
      </td>
     </tr>
    </TABLE>
  </TD>
 </TR>
 <TR>
  <TD HEIGHT=20></TD>
 </TR>
 <TR>
  <TD><P><B>This table shows your existing provider contracts and their status:</B></TD>
 </TR>
 <TR>
  <TD HEIGHT=15></TD>
 </TR>
  <% if (myContracts.length > 0) { %>
 <TR>
  <TD>
   <FORM NAME="ContractData" METHOD="POST" ACTION="body_provider_contract_details.jsp" target="body">
   <TABLE BORDER=0 CELLSPACING=2 CELLPADDING=0 WIDTH=550>
    <TR bgcolor="#4E6A9E" height=30 valign=middle align=center>
     <TH WIDTH=15></TH>
     <TH WIDTH=175><font color="#FFFFFF">Contract</font></TH>
     <TH WIDTH=150><font color="#FFFFFF">Rating-Models</font></TH>
     <TH WIDTH=140><font color="#FFFFFF">Payment-Model</font></TH>
     <TH WIDTH=70><font color="#FFFFFF">Status</font></TH>
    </TR>
     <%for (int i=0; i<myContracts.length; i++) {
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
     %>
    <TR class=tableRow0 height=40 valign=middle align=center>
     <TD><%if (count==0) {%>
       <input type=radio name="contractkey" checked value=<%=myContracts[i]%>><%;%>
         <%} else {%>
             <input type=radio name="contractkey" value=<%=myContracts[i]%>><%; }
           count++;

           ratingKeys = providerContractModel.getRatingkeys();
           //paymentModel = PaymentService.getPaymentModel(providerContractModel.getPaymentkey());
           paymentModel = (PaymentModel) paymentService.invokeOperation("getPaymentModel",
                              new Object[] {providerContractModel.getPaymentkey()});
         %>
     </TD>
     <TD><% out.println(providerContractModel.getDescription()); %></TD>
     <TD>
         <% for (int j=0; j<ratingKeys.length; j++)  {
              //out.println(AccountingService.getRatingModel(ratingKeys[j]).getDescription());
              RatingModel ratingModel = (RatingModel) accountingService.invokeOperation("getRatingModel",
                                                                  new Object[] {ratingKeys[j]});
              out.println(ratingModel.getDescription());
                            
            } %>
     </TD>
     <TD><% out.println(paymentModel.getDescription()); %></TD>
     <TD>
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
     <% }  // end for %>
   </TABLE>
   <TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=550>
    <tr>
     <td height=20></td>
    </tr>
    <tr>
     <td align=center>
      <%if (atLeastOneProviderContract) {%><P><input type=submit value="Show Contract Details"><% }%>
     </td>
    </tr>
   </FORM>
  </TD>
 </TR>
  <% } //end if %>
  <!--
 <tr>
  <td height=30></td>
 </tr>
 -->
 <tr>
  <TD align=center>
    <%if (!atLeastOneProviderContract) {%>
    <P><B><font color="red">You currently have no provider contracts.</font></B>
    <%}%>
  </TD>
 </TR>
 <TR>
  <TD HEIGHT=40></TD>
 </TR>
</TABLE>
</BODY>
</HTML>
