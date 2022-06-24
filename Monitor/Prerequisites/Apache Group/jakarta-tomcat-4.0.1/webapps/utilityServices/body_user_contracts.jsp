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
                java.util.*,
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

 // Add deserializer
 identityService.addDeserializerFactory(new QName(ServiceConstants.NS_IDENTITY_TYPE, "identityModel"), 
                                        IdentityModel.class, BeanSerializer.getFactory());

 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContract"), 
                                        ProviderContractModel.class, BeanSerializer.getFactory());
 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "ArrayOfProviderContracts"), 
                                        ProviderContractModel.class, BeanSerializer.getFactory());
 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "usageContract"), 
                                        UsageContractModel.class, BeanSerializer.getFactory());

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
 ArrayList pcArrayList = (ArrayList) contractService.invokeOperation("getProviderContractList",
                                                                               new Object[] {});  
 
 ProviderContractModel[] providerContracts = (ProviderContractModel[]) pcArrayList.toArray(new ProviderContractModel[pcArrayList.size()]);

 //String[] requestorContracts = ContractService.getContractListForIdentity(ukey);
 
 // Get contract list for identity
 ArrayList contractArrayList = (ArrayList) contractService.invokeOperation("getContractKeyListForIdentity",
                                                                               new Object[] {ukey});  
 
 String[] requestorContracts = (String[]) contractArrayList.toArray(new String[contractArrayList.size()]);
 
 // DEBUG:
 // System.out.println("*** JSP: After get requestorContracts: length:" + requestorContracts.length);

 UsageContractModel usageContractModel = new UsageContractModel();
 ProviderContractModel providerContractModel = new ProviderContractModel();
 IdentityModel identityModel = new IdentityModel();
 Date today = new Date();
 boolean noProviderContractModel = true;
 boolean atLeastOneUsageContract = false;
 int count = 0;

%>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=550>
 <!--
 <TR>
  <TD HEIGHT=30></TD>
 </TR>
 -->
 <TR>
  <TD ALIGN=CENTER><H3><U>Requestor (Usage) Contracts</U></H3></TD>
 </TR>
 <TR>
  <TD HEIGHT=10></TD>
 </TR>
 <TR>
  <TD><P><B>You may now create new usage contracts, or review, activate and
            delete existing usage contracts.</B></TD>
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
      <LI><B><A HREF="body_user_contract_create.jsp" target="body"><u>Create</u> a new requestor contract</A></B></LI>
      <LI><B><A HREF="body_user_contract_activation.jsp" target="body"><u>Activate</u> a requestor contract</A></B></LI>
      <LI><B><A HREF="body_user_contract_delete.jsp" target="body"><u>Delete</u> a requestor contract</A></B></LI>
      </UL>
      </td>
     </tr>
    </TABLE>
  </TD>
 </TR>
 <TR>
  <TD HEIGHT=30></TD>
 </TR>
 <TR>
  <TD><P><B>This table shows your existing usage contracts and their status:</B></TD>
 </TR>
 <TR>
  <TD HEIGHT=15></TD>
 </TR>
  <% if (requestorContracts.length > 0) { %>
 <TR>
  <TD>
   <FORM NAME="ContractData" METHOD="POST" ACTION="body_user_contract_details.jsp" target="body">
   <TABLE BORDER=0 CELLSPACING=2 CELLPADDING=0 WIDTH=550>
    <TR bgcolor="#4E6A9E" height=30 valign=middle align=center>
     <TH WIDTH=15><font color="#FFFFFF"></font></TH>
     <TH WIDTH=225><font color="#FFFFFF">Contract</font></TH>
     <TH WIDTH=225><font color="#FFFFFF">Provider</font></TH>
     <TH WIDTH=85><font color="#FFFFFF">Status</TH>
    </TR>
     <%for (int i=0; i<requestorContracts.length; i++) {
        try {
         //usageContractModel = (UsageContractModel)ContractService.getContractDetails(requestorContracts[i]);
         usageContractModel = (UsageContractModel) contractService.invokeOperation("getUsageContract", 
                                                                         new Object[] {requestorContracts[i]});
        } catch(ClassCastException cce) {            // if ContractModel is not a UsageContractModel
           noProviderContractModel = false;
           continue;
          }
        
        // dug - is this correct?
        if ( usageContractModel == null ) {
            noProviderContractModel = false ;
            continue ;
        }

        noProviderContractModel = true;
        atLeastOneUsageContract = true;

        //providerContractModel = (ProviderContractModel)ContractService.getContractDetails(usageContractModel.getProvidercontractkey());
        providerContractModel = (ProviderContractModel) contractService.invokeOperation("getProviderContract", 
                                                   new Object[] {usageContractModel.getProvidercontractkey()});
     %>
    <TR class=tableRow0 height=40 valign=middle align=center>
     <TD><%if (count==0) {%>
       <input type=radio name="contractkey" checked value=<%=requestorContracts[i]%>><%;%>
         <%} else {%>
             <input type=radio name="contractkey" value=<%=requestorContracts[i]%>><%; }
           count++; %>
     </TD>
     <TD><% out.println(providerContractModel.getDescription()); %></TD>
     <TD><% IdentityModel imExisting = (IdentityModel) identityService.invokeOperation("getIdentityDetails", 
                                                             new Object[] {providerContractModel.getIdentitykey()});
            out.println(imExisting.getName()); %></TD>
     <TD>
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
     <% }  // end for %>
   </TABLE>
   <TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=550>
    <tr>
     <td height=30></td>
    </tr>
    <tr>
     <td align=center>
      <%if (atLeastOneUsageContract) {%><P><input type=submit value="Show Contract Details"><% }%>
     </td>
    </tr>
   </FORM>
  </TD>
 </TR>
  <% } //end if %>
 <TR>
  <TD align=center>
    <%if (!atLeastOneUsageContract) {%><P><B><font color="red">
      You currently have no usage contracts.</font></B><%}%>
  </TD>
 </TR>
 <TR>
  <TD HEIGHT=50></TD>
 </TR>
 <TR>
  <TD><P><B>This table lists all type of services which are available for contracting:</B></TD>
 </TR>
 <TR>
  <TD HEIGHT=15></TD>
 </TR>
  <%
    if (providerContracts.length > 0) { %>
 <TR>
  <TD>
   <TABLE BORDER=0 CELLSPACING=2 CELLPADDING=0 WIDTH=550>
    <TR bgcolor="#4E6A9E" height=30 valign=middle align=center>
     <TH WIDTH=275><font color="#FFFFFF">Contract</font></TH>
     <TH WIDTH=275><font color="#FFFFFF">Provider</font></TH>
    </TR>
     <% for (int i=0; i<providerContracts.length; i++) {
         // DEBUG:
         // System.out.println("*** Before if: i: " + i + ", providerContracts.length:" + providerContracts.length); 
         if (!(providerContracts[i].startTimestamp().equals(providerContracts[i].endTimestamp()) ||
             today.after(providerContracts[i].endTimestamp()) ||
             today.before(providerContracts[i].startTimestamp())))  {
      %>
    <TR class=tableRow0 height=40 valign=middle align=center>
     <TD><% out.println(providerContracts[i].getDescription()); %></TD>
     <TD><% IdentityModel imAvail = (IdentityModel) identityService.invokeOperation("getIdentityDetails", 
                                                             new Object[] {providerContracts[i].getIdentitykey()});
           out.println(imAvail.getName()); %></TD>
    </TR>
     <%  } //end if
        } //end for %>
   </TABLE>
  </TD>
 </TR>
  <% } else { %>
 <TR>
  <TD><P><B><font color="red">There currently are no services available.</font></B></TD>
 </TR>
  <% } %>
 <TR>
  <TD HEIGHT=40></TD>
 </TR>
</TABLE>
</BODY>
</HTML>
