<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
<META http-equiv="Content-Style-Type" content="text/css">
<META name="GENERATOR" content="IBM WebSphere Homepage Builder V5.0.1 for Windows">
<TITLE>Logon ok</TITLE>
<BASE target="_parent">
<LINK REL=STYLESHEET TYPE="text/css" HREF="style/style.css">
</HEAD>
<BODY TOPMARGIN=35 LEFTMARGIN=40 MARGINWIDTH=2 MARGINHEIGHT=2>

<%@page import="com.ibm.services.*,
                com.ibm.services.util.*,
                com.ibm.services.contract.*,
                com.ibm.services.identity.models.*,
                com.ibm.services.identity.*,
                org.apache.axis.encoding.BeanSerializer,
                javax.xml.rpc.namespace.QName" %>
<%@page session="true" %>
<%
 String ukey = (String)session.getValue(session.getId());
 //String welcomeName = IdentityService.getIdentityDetails(ukey).getName();

 if (ukey==null)  {
  String targetPage = "body_logon_failed.html";
  response.sendRedirect(targetPage);
  return;
 }

 // Get access to service properties
 ServiceProperties serviceProps = new ServiceProperties();

 // Get service to invoke operations
 WSDLService identityService = serviceProps.getService(ServiceConstants.IDENTITY);

 // Add deserializer
 identityService.addDeserializerFactory(new QName(ServiceConstants.NS_IDENTITY_TYPE, "identityModel"), 
                                        IdentityModel.class, 
                                        BeanSerializer.getFactory());

 // Get identity model
 IdentityModel identityModel = (IdentityModel) identityService.invokeOperation("getIdentityDetails",
                                                                               new Object[] {ukey});  

 // Get name
 String welcomeName = identityModel.getName();

%>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD width="40" height="28"></TD>
  <TD width="460" height="28"></TD>
 </TR>
 <TR>
  <TD height="41"></TD>
  <TD style="text-align: center;" height="41"><H3><U>Welcome, <%=welcomeName%></U></H3></TD>
 </TR>
 <TR>
  <TD height="11"></TD><TD height="11"></TD>
 </TR>
 <TR>
  <TD height="52"></TD>
  <TD align="center" height="52"><P><B>Logon was successful!</b></p>
  </TD>
  <TR>
  <TD height="20"></TD><TD height="20"></TD>
 </TR>
    <TR>
  <TD height="80"></TD>
  <TD height="80">
      <UL>
        <LI><B>The service provider functions can be accessed
        by selecting &quot;Provider&quot; or &quot;Accounting&quot;.
        </B>
        <LI><B>The service requestor functions can be accessed
        by selecting &quot;Requestor&quot; or &quot;Use
        Application Services&quot;.</B>
        <LI><B>You can also update your user identity information.</B>
      </UL>
      </TD>
 </TR>
</TABLE>
</BODY>
</HTML>
