<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
<META http-equiv="Content-Style-Type" content="text/css">
<TITLE>Requestor Contract Deletion</TITLE>
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
                com.ibm.services.identity.*,
                com.ibm.services.identity.models.*,
                java.util.Date, java.text.DateFormat,
                com.ibm.services.*,
                com.ibm.services.util.*,
                org.apache.axis.encoding.BeanSerializer,
                javax.xml.rpc.namespace.QName,
                java.util.*" %>
<%@page session="true" %>
<%
// check if session is active and valid for Identity
// String[] identityList = IdentityService.getIdentityList();

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

 //ProviderContractModel[] providerContracts = ContractService.getProviderContractsDetailed();
 ArrayList pcArrayList = (ArrayList) contractService.invokeOperation("getProviderContractList", new Object[] {});

 ProviderContractModel[] providerContracts = (ProviderContractModel[])pcArrayList.toArray(new ProviderContractModel[pcArrayList.size()]);
 
 //String[] requestorContracts = ContractService.getContractListForIdentity(ukey);
 ArrayList rcArrayList = (ArrayList)contractService.invokeOperation("getContractKeyListForIdentity",
                                                       new Object[] {ukey});
 
 String[] requestorContracts = (String[])rcArrayList.toArray(new String[rcArrayList.size()]);

 UsageContractModel usageContractModel = new UsageContractModel();
 ProviderContractModel providerContractModel = new ProviderContractModel();
// IdentityModel identityModel = new IdentityModel();
 Date today = new Date();
 boolean noProviderContractModel = true;
 boolean atLeastOneUsageContract = false;
 int count = 0;
%>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD HEIGHT=30 WIDTH=100%></TD>
 </TR>
 <TR>
  <TD ALIGN=CENTER><H3><U>Requestor Contract Deletion</U></H3></TD>
 </TR>
 <TR>
  <TD HEIGHT=20></TD>
 </TR>
 <TR>
  <TD><B>This table lists your Requestor Contracts.
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
  <% if (requestorContracts.length > 0) { %>
 <TR>
  <TD>
   <FORM NAME="ContractData" METHOD="POST" ACTION="DeleteUserContract" onSubmit="return chkForm()">
   <TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
    <TR bgcolor="#4E6A9E" height=30 valign=middle>
     <TH WIDTH=15></TD>
     <TH WIDTH=200 align=center><font color="#FFFFFF">Contract</font></TH>
     <TH WIDTH=200 align=center><font color="#FFFFFF">Provider</font></TH>
     <TH WIDTH=85 align=center><font color="#FFFFFF">Status</font></TH>
    </TR>
     <%for (int i=0; i<requestorContracts.length; i++) {
        try {
          //usageContractModel = (UsageContractModel)ContractService.getContractDetails(requestorContracts[i]);
          usageContractModel = (UsageContractModel) contractService.invokeOperation("getUsageContract",
                                                                      new Object[] {requestorContracts[i]});
        } catch(ClassCastException cce) {            // if ContractModel is not a UsageContractModel
           noProviderContractModel = false;
           continue; }
        if ( usageContractModel == null ) {
          noProviderContractModel = false ;
          continue ;
        }
        noProviderContractModel = true;
        //providerContractModel = (ProviderContractModel)ContractService.getContractDetails(usageContractModel.getProvidercontractkey());
        providerContractModel = (ProviderContractModel) contractService.invokeOperation("getContractDetails",
                                                     new Object[] {usageContractModel.getProvidercontractkey()});
        if ( providerContractModel == null ) continue ;
        atLeastOneUsageContract = true;
     %>
    <TR class=tableRow0 height=40 valign=middle>
     <TD><% if (count==0)  { %>
           <input type=radio name="contractkey" checked value=<%=requestorContracts[i]%>><%;%>
          <%} else {%>
            <input type=radio name="contractkey" value=<%=requestorContracts[i]%>><%; }
            count++; %>
     </TD>
     <TD STYLE="text-align: center;"><P><% out.println(providerContractModel.getDescription()); %></TD>
     <TD STYLE="text-align: center;"><P>
     <% 
    // Get identity model
      IdentityModel identityModel = (IdentityModel) identityService.invokeOperation("getIdentityDetails", new Object[] {providerContractModel.getIdentitykey()});  
      //out.println(identityService.getIdentityDetails(providerContractModel.getIdentitykey()).getName());
      out.println(identityModel.getName());
     %></TD>
     <TD STYLE="text-align: center;"><P>
         <%if (today.after(usageContractModel.startTimestamp()) && 
               today.before(usageContractModel.endTimestamp()))
             out.println("active");
           else  {
             if (usageContractModel.getStart().equals(usageContractModel.getEnd()))
               out.println("not activated");
             else  {
               if (today.after(usageContractModel.endTimestamp())) out.println("expired");
               if (today.before(usageContractModel.startTimestamp())) out.println("future");
             }
           } %>
     </TD>
    </TR>
     <% }  //end for%>
   </TABLE>
  </TD>
 </TR>
 <TR>
  <TD HEIGHT=100 align=center>
   <% if (atLeastOneUsageContract) { %>
      <input type=submit value="Delete Contract">
      <input type=button value="Cancel" onClick="parent.body.location.href = 'body_user_contracts.jsp'">
   <% } %>
  </TD>
 </TR>
  </FORM>
  <% } // end if { %>
 <TR>
  <TD align=center>
   <% if (!atLeastOneUsageContract) {%>
       <B><font color="red">There are no contracts available for deletion</font></B>
  </TD>
 </TR>
 </TR>
  <TD HEIGHT=30></TD><TD></TD><TD></TD>
 <TR>
 <TR>
  <TD align=center>
   <form><input type=button value="Cancel" onClick="parent.body.location.href = 'body_user_contracts.jsp'"></form>
  </TD>
 </TR>
  <% } %>
</TABLE>
</BODY>
</HTML>
