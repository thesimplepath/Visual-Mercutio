<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
  <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
  <META http-equiv="Content-Style-Type" content="text/css">
  <TITLE>Create Requestor Contract</TITLE>
  <LINK REL="STYLESHEET" TYPE="text/css" HREF="style/style.css">
  <script language="JavaScript">
  <!--
  function chkForm() {
     var check = confirm("Do you really want to create this Contract?");
     if (check == false) return false;
     else return true;
  }
  //-->
  </script>
</HEAD>
  <BODY TOPMARGIN="35" LEFTMARGIN="40" MARGINWIDTH="0" MARGINHEIGHT="0">

  <%@page import="com.ibm.services.contract.*,
                com.ibm.services.contract.models.*,
                com.ibm.services.accounting.*,
                com.ibm.services.accounting.models.*,
                com.ibm.services.identity.*,
                com.ibm.services.identity.models.*,
                java.util.Date,
                com.ibm.services.*,
                com.ibm.services.util.*,
                org.apache.axis.encoding.BeanSerializer,
                javax.xml.rpc.namespace.QName,
                java.util.*"%><%@page session="true" %>
<%
 // Get access to service properties
 ServiceProperties serviceProps = new ServiceProperties();

 // Get service to invoke operations
 WSDLService identityService = serviceProps.getService(ServiceConstants.IDENTITY);
 WSDLService contractService = serviceProps.getService(ServiceConstants.CONTRACT);
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

 // Get identity list
 ArrayList identityArrayList = (ArrayList) identityService.invokeOperation("getIdentityList", new Object[] {});
 String[] identityList = (String[]) identityArrayList.toArray(new String[identityArrayList.size()]);

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

  ProviderContractModel[] providerContracts;

  // Get provider contract model
  ArrayList pcArrayList = (ArrayList) contractService.invokeOperation("getProviderContractList",
                                                                                new Object[] {});
  
  providerContracts = (ProviderContractModel[]) pcArrayList.toArray(new ProviderContractModel[pcArrayList.size()]); 

 RatingModel[] ratingModels;
 Date today = new Date();
 String[] ratingKeys;
 boolean  hasOne = false ;
%>
   
  <FORM NAME="NewUserContractData" METHOD="POST" ACTION="body_user_contract_create2.jsp" target="body">
    <TABLE BORDER="0" CELLSPACING="0" CELLPADDING="0" WIDTH="550">
      <!--
      <TR>
       <TD HEIGHT=30 WIDTH=100%></TD>
      </TR>
      -->
      <TR>
        <TD ALIGN="CENTER"><H3><U>Create Usage Contract [1]</U></H3></TD>
      </TR>
      <TR>
        <TD HEIGHT="20"></TD>
      </TR>
      <TR>
        <TD><B>Select a service to use:</B></TD>
      </TR>
      <TR>
        <TD HEIGHT="20"></TD>
      </TR>
   <% if (providerContracts.length > 0) { %>
      <TR>
        <TD>
          <TABLE BORDER="0" CELLSPACING="2" CELLPADDING="0" WIDTH="550">
            <TR bgcolor="#4E6A9E" height="30" valign="middle" align="center">
              <TH width="15"></TH>
              <TH width="180"><font color="#FFFFFF">Contract</font></TH>
              <TH width="175"><font color="#FFFFFF">Provider</font></TH>
              <TH width="180"><font color="#FFFFFF">Ratings</font></TH>
            </TR>
     <% for (int i=0; i<providerContracts.length; i++) {
         ratingKeys = providerContracts[i].getRatingkeys();

         // DEBUG:
         // System.out.println("start:" + providerContracts[i].getStart() + ", " + providerContracts[i].endTimestamp().toString() + 
                            // " end: " + providerContracts[i].getEnd() + "," + providerContracts[i].startTimestamp().toString() + 
                            // " today: " + today.toString());

         if (!(providerContracts[i].getStart().equals(providerContracts[i].getEnd()) ||
             today.after(providerContracts[i].endTimestamp()) ||
             today.before(providerContracts[i].startTimestamp())))  {
     %>

    
            <TR class=tableRow0 height="40" valign="middle" align="center">
              <TD>
                <% if (i == 0) 
                   {%>
                   <input type="radio" name="contractkey" checked value="<%=providerContracts[i].getContractkey()%>">
                   <%}
                   else
                   {%>
                   <input type="radio" name="contractkey" value="<%=providerContracts[i].getContractkey()%>">
                   <%}%>
              </TD>
              <TD><%out.println(providerContracts[i].getDescription());%></TD>
              <TD><%
    // Get identity model
      hasOne = true ;
      IdentityModel identityModel = (IdentityModel) identityService.invokeOperation("getIdentityDetails", new Object[] {providerContracts[i].getIdentitykey()});  
      out.println(identityModel.getName());
     %></TD>
              <TD>
         <% for (int j=0; j<ratingKeys.length; j++)  {
              //out.println(AccountingService.getRatingModel(ratingKeys[j]).getDescription());%>
                <BR>
<%
              out.println(((RatingModel)accountingService.invokeOperation("getRatingModel", new Object[] {(ratingKeys[j])})).getDescription());%>
                <BR>
<%
            } //end j%>
     </TD>
            </TR>
     <%  } //end if
        } //end i %>
   
          </TABLE>
        </TD>
      </TR>
      <tr>
        <td height="10"></td>
      </tr>
      <TR>
        <TD ALIGN="CENTER">
    <% if ( hasOne ) { %>
    
          <input type="submit" value="Continue...">
          <input type="button" value="Cancel" onClick="history.back()">
    <% } else { %>
      
          <p>
          <font color="red"><b>There are no services available.</b></font>
          <p>
          <input type="button" value="Return" onClick="history.back()">
    <% } %>
  </TD>
      </TR>

   <% } else { %>
 
      <TR>
        <TD align="center"><B><font color="red">There are currently no services 
        available.</font></B></TD>
      </TR>
    <% } %>
 
      <TR>
        <TD HEIGHT="40"></TD>
      </TR>
    </TABLE>
  </FORM>
  </BODY>
</HTML>
