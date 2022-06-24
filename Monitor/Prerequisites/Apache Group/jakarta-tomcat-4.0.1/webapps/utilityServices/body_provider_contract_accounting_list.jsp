<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
<META http-equiv="Content-Style-Type" content="text/css">
<TITLE>Provider Contract Requestor Listing</TITLE>
<LINK REL=STYLESHEET TYPE="text/css" HREF="style/style.css">
</HEAD>
<BODY TOPMARGIN=35 LEFTMARGIN=40 MARGINWIDTH=0 MARGINHEIGHT=0>

<%@page import="com.ibm.services.*,
                com.ibm.services.contract.*,
                com.ibm.services.contract.models.*,
                com.ibm.services.identity.*,
                com.ibm.services.identity.models.*,
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
                                        IdentityModel.class,
                                        BeanSerializer.getFactory());

 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "usageContract"),
                                        UsageContractModel.class,
                                        BeanSerializer.getFactory());

 // Get identity list
 ArrayList identityArrayList = (ArrayList) identityService.invokeOperation("getIdentityList", new Object[] {});

 // This code was added because the identityArrayList.toArray() fails
 String[] identityList = (String[]) identityArrayList.toArray(new String[identityArrayList.size()]);

 boolean validSession = false;
 String sessionID = (String)session.getValue(session.getId());

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
 String providerContractKey = request.getParameter("contractkey");

 ArrayList ckArrayList = (ArrayList) contractService.invokeOperation("getContractKeyListForProviderContract",
                                                                     new Object[] {providerContractKey});

 String[] myCustomerContracts = (String []) ckArrayList.toArray(new String[ckArrayList.size()]);

%>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
<!--
 <TR>
  <TD HEIGHT=30 WIDTH=100%></TD>
 </TR>
 -->
 <TR>
  <TD ALIGN=CENTER><H3><U>Accounting [2]</U></H3></TD>
 </TR>
 <TR>
  <TD HEIGHT=10></TD>
 </TR>
 <TR>
  <TD><B>This table lists all User Contracts (Requestor Contracts) signed for the selected service
            contract.
        Select a contract in order to calculate the related accounting and billing information.
      </B>
  </TD>
 </TR>
 <TR><TD HEIGHT=10></TD><TD>
</TABLE>
 <% if (myCustomerContracts.length>0)  { %>
<FORM NAME="ContractData" METHOD="POST" ACTION="body_provider_contract_accounting_list2.jsp" target="body">
<TABLE BORDER=0 CELLSPACING=2 CELLPADDING=0 WIDTH=500>
 <TR bgcolor="#4E6A9E" height=30 valign=middle>
  <TH WIDTH=15></TH>
  <TH WIDTH=170 align=center><font color="#FFFFFF">Requestor</font></TH>
  <TH WIDTH=315 align=center><font color="#FFFFFF">Contract Key</font></TH>
 </TR>
   <% for (int i=0;i<myCustomerContracts.length;i++)  { %>
 <TR class=tableRow0 height=40 valign=middle>
  <TD>
    <% if (i==0)  { %>
          <input type=radio name="usercontractkey" checked value=<%=myCustomerContracts[i]%>><%;%>
     <%} else {%>
          <input type=radio name="usercontractkey" value=<%=myCustomerContracts[i]%>><%;
        } %>
          <input type=hidden name="providercontractkey" value=<%=providerContractKey%>
  </TD>
  <TD STYLE="text-align: center;"><P>
  <% UsageContractModel usageContract = (UsageContractModel) contractService.invokeOperation("getUsageContract",
                                                              new Object[] {myCustomerContracts[i]});
     IdentityModel identity = (IdentityModel) identityService.invokeOperation("getIdentityDetails",
                                                      new Object[] {usageContract.getIdentitykey()});


    //out.println(IdentityService.getIdentityDetails(ContractService.getContractDetails(myCustomerContracts[i]).getIdentitykey()).getName());
     out.println(identity.getName());
    %></TD>
  <TD STYLE="text-align: center;"><P><% out.println(myCustomerContracts[i]); %></TD>
 </TR>
   <% } //end for %>
</TABLE>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD HEIGHT=10></TD>
 </TR>
 <TR>
  <TD ALIGN=CENTER><input type=submit value="Continue">
                   <input type=button value="Cancel" onClick="history.back()">
  </TD>
 </TR>
</TABLE>
</FORM>
 <% } else { %>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD HEIGHT=10></TD>
 </TR>
 <TR align=center>
  <TD>
   <B><font color="red">This service was not contracted by requestors</font></B>
  </TD>
 </TR>
 <TR>
  <TD HEIGHT=10></TD>
 </TR>
</TABLE>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD HEIGHT=10 ALIGN=CENTER><FORM><input type=button value="Cancel" onClick="history.back()"></FORM></TD>
 </TR>
</TABLE>
   <% } //end else %>
</BODY>
</HTML>
