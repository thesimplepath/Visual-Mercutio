<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
  <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
  <META http-equiv="Content-Style-Type" content="text/css">
  <TITLE>Provider Contract Activation</TITLE>
  <LINK REL="STYLESHEET" TYPE="text/css" HREF="style/style.css">
  <script language="JavaScript">
  function checkDate() {
     var today = new Date();
     var startYear = document.ContractData.startyear.value;
     var startMonth = document.ContractData.startmonth.value;
     var startDay = document.ContractData.startday.value;
     var endYear = document.ContractData.endyear.value;
     var endMonth = document.ContractData.endmonth.value;
     var endDay = document.ContractData.endday.value;
     var startDate = new Date(startYear,startMonth-1,startDay,23,59,59);
     var endDate   = new Date(endYear,endMonth-1,endDay,23,59,59);

     if (startDate.getTime()<today.getTime()) {
        alert("ERROR: Start Date must not be in the past!");
        return false;
     }
     if (startDate.getTime()>=endDate.getTime()) {
        alert("ERROR: Start Date must be lower than End Date!");
        return false;
     }
     if ((startMonth==4||startMonth==6||startMonth==9||startMonth==11)&&(startDay==31)) {
        alert("ERROR: Start Day not valid!");
        return false;
     }
     if ((endMonth==4||endMonth==6||endMonth==9||endMonth==11)&&(endDay==31)) {
        alert("ERROR: End Day not valid!");
        return false;
     }
     if (startMonth==2) {     /* February  */
        if ((startYear%4==0 && startDay>29) || (startYear%4!=0 && startDay>28)) {
           alert("ERROR: Start Day not valid for February!");
           return false;
        }
     }
     if (endMonth==2) {     /* February  */
        if ((endYear%4==0 && endDay>29) || (endYear%4!=0 && endDay>28)) {
           alert("ERROR: End Day not valid for February!");
           return false;
        }
     }
  }
  </script>
</HEAD>
  <BODY TOPMARGIN="35" LEFTMARGIN="40" MARGINWIDTH="0" MARGINHEIGHT="0">

  <%@page import="com.ibm.services.contract.*,
                com.ibm.services.contract.models.*,
                com.ibm.services.identity.*,
                com.ibm.services.identity.models.*,
                java.util.Date, java.text.DateFormat,
                com.ibm.services.*,
                com.ibm.services.util.*,
                org.apache.axis.encoding.BeanSerializer,
                javax.xml.rpc.namespace.QName,
                java.util.*" %><%@page session="true" %>
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

 // Add deserializer
 contractService.addDeserializerFactory(new QName(ServiceConstants.NS_CONTRACT_TYPE, "providerContract"),
                                        ProviderContractModel.class,
                                        BeanSerializer.getFactory());

 // Get provider contract model
 //ArrayList pcArrayList = (ArrayList) contractService.invokeOperation("getProviderContractList",
 //                                                                              new Object[] {});

 //ProviderContractModel[] providerContracts = (ProviderContractModel[]) pcArrayList.toArray(new ProviderContractModel[pcArrayList.size()]);

// String[] myContracts = ContractService.getContractListForIdentity(ukey);

 // Get contract list for identity
 ArrayList contractArrayList = (ArrayList) contractService.invokeOperation("getContractKeyListForIdentity",
                                                                               new Object[] {ukey});

 String[] myContracts = (String[]) contractArrayList.toArray(new String[contractArrayList.size()]);

 ProviderContractModel providerContractModel = new ProviderContractModel();
 IdentityModel identityModel = new IdentityModel();
 boolean noUsageContractModel = false;
 boolean noActiveContracts = false;
 int count = 0;
%>
  <TABLE BORDER="0" CELLSPACING="0" CELLPADDING="0" WIDTH="500">
    <!--
     <TR>
      <TD HEIGHT=30 WIDTH=100%></TD>
     </TR>
    -->
    <TR>
      <TD ALIGN="CENTER"><H3><U>Activate Provider Contract</U></H3></TD>
    </TR>
    <TR>
      <TD HEIGHT="10"></TD>
    </TR>
    <TR>
      <TD>
        <P>
        <b>This table lists the Provider Contracts which you have created, but not
        activated yet. To activate a contract, select it from the list, and then set the
        start and end date for the contract. The contract will be activated for usage
        within this timeframe.</b>
        <p>
        <b>The start date must be either today or a future date, and the end date must
        be later than the start date.</b>
        <p>
        <b>If you choose today's date as the start date, the contract will be activated
        immediately (the status will be "active"). Otherwise, it will be activated in
        the future (the status will be "future").</B></TD>
    </TR>
    <%for (int i=0; i<myContracts.length; i++) {
     try {
         providerContractModel = (ProviderContractModel) contractService.invokeOperation("getProviderContract",
                                                                          new Object[] {myContracts[i]});
     } catch(ClassCastException cce) { continue; }
     if (providerContractModel == null) continue ;
     if (providerContractModel.getStart().equals(providerContractModel.getEnd())) noActiveContracts = true;
   }
   if ((myContracts.length>0) && noActiveContracts) { %>
    <FORM NAME="ContractData" METHOD="POST" ACTION="ActivateProviderContract" onSubmit="return checkDate()">
      <tr>
        <td height="20"></td>
      </tr>
      <TR>
        <TD>
          <P>
          <B>Select a contract for activation and define the start and end date:</B></TD>
      </TR>
      <TR>
        <TD HEIGHT="10"></TD>
      </TR>
      <TR>
        <TD>
          <TABLE BORDER="0" CELLSPACING="2" CELLPADDING="0" WIDTH="500">
            <TR bgcolor="#4E6A9E" height="30" valign="middle">
              <TH WIDTH="15"></TH>
              <TH WIDTH="300" align="center"><font color="#FFFFFF">Contract</font></TH>
              <TH WIDTH="200" align="center"><font color="#FFFFFF">Provider</font></TH>
            </TR>
            <%for (int i=0; i<myContracts.length; i++) {
           try {
             providerContractModel = (ProviderContractModel) contractService.invokeOperation("getProviderContract",
                                                               new Object[] {myContracts[i]});
           } catch(ClassCastException cce) { continue; }   // if ContractModel is not a ProviderContractModel
           if (providerContractModel == null ) continue ;

           if (!(providerContractModel.getStart().equals(providerContractModel.getEnd()))) continue;
           noUsageContractModel = true;
           %>
            <TR class=tableRow0 height="40" valign="middle">
              <TD><%if (count==0) {%>
                <input type="radio" name="contractkey" checked value=<%=myContracts[i]%>
                ><%;%><%} else {%>
                <input type="radio" name="contractkey" value=<%=myContracts[i]%>
                ><%;
         }
         count++; %></TD>
              <TD STYLE="text-align: center;"><% out.println(providerContractModel.getDescription()); %></TD>
              <TD STYLE="text-align: center;"><%
         IdentityModel imAvail = (IdentityModel) identityService.invokeOperation("getIdentityDetails",
                                             new Object[] {providerContractModel.getIdentitykey()});
           out.println(imAvail.getName());
       %></TD>
            </TR>
        <% } // end for %></TD>
  </TABLE>
  </TD>
  </TR>
  </TABLE>
  <TABLE BORDER="0" CELLSPACING="0" CELLPADDING="0" WIDTH="500">
    <TR>
      <TD WIDTH="10%" HEIGHT="10"></TD>
      <TD WIDTH="45%"></TD>
      <TD WIDTH="45%"></TD>
    </TR>
    <TR>
      <TD></TD>
      <TD ALIGN="CENTER"><B>Start Date:</TD>
      <TD ALIGN="CENTER"><B>End Date:</TD>
    </TR>
    <TR>
      <TD HEIGHT="50"></TD>
      <TD><font face="Verdana,Geneva,Arial,Helvetica,sans-serif" size="1">
        <select name='startday' class='pull'>
          <option value='01' >1</option> <option value='02' >2</option> <option value='03' >3</option>
          <option value='04' >4</option> <option value='05' >5</option> <option value='06' >6</option>
          <option value='07' >7</option> <option value='08' >8</option> <option value='09' >9</option>
          <option value='10' >10</option> <option value='11' >11</option> <option value='12' >12</option>
          <option value='13' >13</option> <option value='14' >14</option> <option value='15' >15</option>
          <option value='16' >16</option> <option value='17' >17</option> <option value='18' >18</option>
          <option value='19' >19</option> <option value='20' >20</option> <option value='21' >21</option>
          <option value='22' >22</option> <option value='23' >23</option> <option value='24' >24</option>
          <option value='25' >25</option> <option value='26' >26</option> <option value='27' >27</option>
          <option value='28' >28</option> <option value='29' >29</option> <option value='30' >30</option>
          <option value='31' >31</option>
        </select>
        <font face="Verdana,Geneva,Arial,Helvetica,sans-serif" size="1">
        <select name='startmonth' class='pull'>
          <option value='01'>January</option> <option value='02'>February</option> <option value='03'>March</option>
          <option value='04'>April</option> <option value='05'>May</option> <option value='06'>June</option>
          <option value='07'>July</option> <option value='08'>August</option> <option value='09'>September</option>
          <option value='10'>October</option> <option value='11'>November</option> <option value='12'>December</option>
        </select>
        <font face="Verdana,Geneva,Arial,Helvetica,sans-serif" size="1">
        <select name='startyear' class='pull'>
          <option value='2001'>2001</option> <option value='2002'>2002</option> <option value='2003'>2003</option>
          <option value='2004'>2004</option> <option value='2005'>2005</option>
        </select>
      </TD>
      <TD><font face="Verdana,Geneva,Arial,Helvetica,sans-serif" size="1">
        <select name='endday' class='pull'>
          <option value='01' >1</option> <option value='02' >2</option> <option value='03' >3</option>
          <option value='04' >4</option> <option value='05' >5</option> <option value='06' >6</option>
          <option value='07' >7</option> <option value='08' >8</option> <option value='09' >9</option>
          <option value='10' >10</option> <option value='11' >11</option> <option value='12' >12</option>
          <option value='13' >13</option> <option value='14' >14</option> <option value='15' >15</option>
          <option value='16' >16</option> <option value='17' >17</option> <option value='18' >18</option>
          <option value='19' >19</option> <option value='20' >20</option> <option value='21' >21</option>
          <option value='22' >22</option> <option value='23' >23</option> <option value='24' >24</option>
          <option value='25' >25</option> <option value='26' >26</option> <option value='27' >27</option>
          <option value='28' >28</option> <option value='29' >29</option> <option value='30' >30</option>
          <option value='31' >31</option>
        </select>
        <font face="Verdana,Geneva,Arial,Helvetica,sans-serif" size="1">
        <select name='endmonth' class='pull'>
          <option value='01'>January</option> <option value='02'>February</option> <option value='03'>March</option>
          <option value='04'>April</option> <option value='05'>May</option> <option value='06'>June</option>
          <option value='07'>July</option> <option value='08'>August</option> <option value='09'>September</option>
          <option value='10'>October</option> <option value='11'>November</option> <option value='12'>December</option>
        </select>
        <font face="Verdana,Geneva,Arial,Helvetica,sans-serif" size="1">
        <select name='endyear' class='pull'>
          <option value='2001'>2001</option> <option value='2002'>2002</option> <option value='2003'>2003</option>
          <option value='2004'>2004</option> <option value='2005'>2005</option>
        </select>
      </TD>
    </TR>
    <TR>
      <TD colspan="3" HEIGHT="50" ALIGN="CENTER">
   <% if (noUsageContractModel==true) { %>

        <input type="submit" value="Activate Contract">
        <input type="button" value="Cancel" onClick="parent.body.location.href = 'body_provider_contracts.jsp'">
   <% } %>
  </TD>
    </TR>
    </FORM>
   <% } else { %>

    <TR>
      <TD HEIGHT="30"></TD>
      <TD></TD>
      <TD></TD>
    </TR>
    <TR>
      <TD colspan="3" align="center"><b><font color="red">There are no contracts
      available for activation</font></b></TD>
    </TR>
    <TD HEIGHT="30"></TD>
    <TD></TD>
    <TD></TD>
    <TR>
      <TD colspan="3" align="center">
        <FORM>
          <input type="button" value="Cancel" onClick="parent.body.location.href = 'body_provider_contracts.jsp'">
        </FORM>
      </TD>
    </TR>
   <% } %>
  </TABLE>
  </BODY>
</HTML>
