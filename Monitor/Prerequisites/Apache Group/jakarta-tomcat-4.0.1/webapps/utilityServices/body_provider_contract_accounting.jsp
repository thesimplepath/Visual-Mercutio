<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
<META http-equiv="Content-Style-Type" content="text/css">
<TITLE>Provider Contract Accounting</TITLE>
<LINK REL=STYLESHEET TYPE="text/css" HREF="style/style.css">
</HEAD>
<BODY TOPMARGIN=35 LEFTMARGIN=40 MARGINWIDTH=0 MARGINHEIGHT=0>

<%@page import="com.ibm.services.contract.*,
                com.ibm.services.contract.models.*,
                com.ibm.services.identity.*,
                com.ibm.services.identity.models.*,
                com.ibm.services.*,
                com.ibm.services.util.*,
                org.apache.axis.encoding.BeanSerializer,
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
                                                  IdentityModel.class, BeanSerializer.getFactory());

 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContract"), 
                                                       ProviderContractModel.class, BeanSerializer.getFactory());
 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "usageContract"), 
                                                       UsageContractModel.class, BeanSerializer.getFactory());

 // Get identity list
 ArrayList identityArrayList = (ArrayList) identityService.invokeOperation("getIdentityList", new Object[] {});  

 // This code was added because the identityArrayList.toArray() fails
 String[] identityList = new String[identityArrayList.size()];
 for (int i = 0; i < identityArrayList.size(); i++)
 {
   identityList[i] = (String) identityArrayList.get(i);
 }

 boolean validSession = false;
 String sessionID = (String)session.getValue(session.getId());
 String ukey = (String)session.getValue(session.getId());

 for (int i=0;sessionID != null && i<identityList.length;i++)  {
  if (sessionID.equals(identityList[i])) {
   validSession = true;
   break;
  }
 }

 if (validSession==false)  {
  String targetPage = "body_no_session.html";
  response.sendRedirect(targetPage);
  return;
 }

 ArrayList mcArrayList = (ArrayList) contractService.invokeOperation("getContractKeyListForIdentity", 
                                                                     new Object[] {ukey});
 
 String[] myContracts = (String[]) mcArrayList.toArray(new String[mcArrayList.size()]);

 ProviderContractModel providerContractModel = new ProviderContractModel();
 boolean noUsageContractModel = true;
 boolean atLeastOneProviderContract = false;
 int count = 0;
%>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
<!--
 <TR>
  <TD HEIGHT=30 WIDTH=100%></TD>
 </TR>
-->
 <TR>
  <TD ALIGN=CENTER><H3><U>Accounting [1]</U></H3></TD>
 </TR>
 <TR>
  <TD HEIGHT=10></TD>
 </TR>
 <TR>
  <TD><B>This table lists your Provider Contracts for accounting purposes.
        <br>Select a contract in order to show the users (requestors) which have signed
            the contract and to calculate accounting and billing information for each user.
      </B>
  </TD>
 </TR>
 <TR>
  <TD HEIGHT=20></TD>
 </TR>
 <TR align=center>
  <TD><P><B>Select a contract for accounting:</B></TD>
 </TR>
 <TR>
  <TD HEIGHT=10></TD>
 </TR>
  <% if (myContracts.length > 0) { %>
 <TR align=center>
  <TD>
   <FORM NAME="ContractData" METHOD="POST" ACTION="body_provider_contract_accounting_list.jsp" target="body">
   <TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=300>
    <TR bgcolor="#4E6A9E" height=30 valign=middle>
     <TH WIDTH=15></TH>
     <TH WIDTH=285 align=center><font color="#FFFFFF">Provider Contract</font></TH>
    </TR>
     <%for (int i=0; i<myContracts.length; i++) {
        try {
          //providerContractModel = (ProviderContractModel)ContractService.getContractDetails(myContracts[i]);

          providerContractModel = (ProviderContractModel) contractService.invokeOperation("getProviderContract",
                                                                   new Object[] {myContracts[i]});
        } catch(ClassCastException cce) {            // if ContractModel is not a ProviderContractModel
           noUsageContractModel = false;
           continue;
         }
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
            <input type=radio name="contractkey" value=<%=myContracts[i]%>><%;
             } %>
     </TD>
     <TD STYLE="text-align: center;"><P><% out.println(providerContractModel.getDescription()); %></TD>
    </TR>
     <% count++;  }  //end for %>
   </TABLE>
  </TD>
 </TR>
 <TR>
  <TD HEIGHT=10 ALIGN=CENTER>
   <% if (atLeastOneProviderContract) { %>
      <input type=submit value="Continue">
      <input type=button value="Cancel" onClick="history.back()">
   <% } %>
   </FORM>
  </TD>
 </TR>
  <% } // end if %>
 <TR align=center>
  <TD>
   <% if (!atLeastOneProviderContract) {%>
       <P><B><font color="red">There are no contracts available for accounting</font></B>
  </TD>
 </TR>
 <TR align=center>
  <TD HEIGHT=100><FORM><input type=button value="Cancel" onClick="history.back()"></FORM></TD>
 </TR>
  <% } %>
</TABLE>
</BODY>
</HTML>
