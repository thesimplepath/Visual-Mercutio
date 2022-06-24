<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
<TITLE>Customer Data Maintenance</TITLE>
<BASE TARGET="_top">
<LINK REL=STYLESHEET TYPE="text/css" HREF="style/style.css">
<script language="JavaScript">
  function chkForm() {
   if(document.UserData.company.value == ""  ||
      document.UserData.name.value == ""     ||
      document.UserData.address1.value == "" ||
      document.UserData.zipcode.value == ""  ||
      document.UserData.place.value == ""    ||
      document.UserData.email.value == "")  {
     alert("Form incomplete! Please insert missing data!");
     return false;
    }
    if(document.UserData.email.value.indexOf('@') == -1) {
     alert("E-mail address not valid!");
     document.UserData.email.focus();
     return false;
    }
    if(document.UserData.dn.value.indexOf('CN=') == -1) {
     alert("Distinguished name must be LDAP compatible!\n(CN=...)");
     document.UserData.dn.focus();
     return false;
    }
  }
</script>
</HEAD>
<BODY TOPMARGIN=35 LEFTMARGIN=40 MARGINWIDTH=2 MARGINHEIGHT=2>

<%@page import="com.ibm.services.identity.*,
                com.ibm.services.identity.models.*,
                com.ibm.services.identity.exceptions.*,
                java.sql.*,
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

 // Add deserializer
 identityService.addDeserializerFactory(new QName(ServiceConstants.NS_IDENTITY_TYPE, "identityModel"), 
                                        IdentityModel.class, BeanSerializer.getFactory());

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
 
// IdentityModel imod = IdentityService.getIdentityDetails(ukey);

IdentityModel imod = (IdentityModel) identityService.invokeOperation("getIdentityDetails", new Object[] {ukey});
%>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD HEIGHT=30 WIDTH=100%></TD>
 </TR>
 <TR>
  <TD ALIGN=CENTER><H3><U>User Data Update</U></H3></TD>
 </TR>
 <TR>
  <TD HEIGHT=20></TD>
 </TR>
 <TR>
  <TD WIDTH=100%><B>Please review your data below and update any changes as appropriate.
  </TD>
 </TR>
</TABLE>
<P><HR>
<P><B>(Fields marked with <font color="#FF0000">*</font> are required data fields!)</B>
<FORM NAME="UserData" METHOD="POST" ACTION="ChangeUser" onSubmit="return chkForm()">
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD WIDTH=5%></TD><TD WIDTH=5%><TD WIDTH=40%></TD><TD WIDTH=50%></TD>
 <TR>
  <TD HEIGHT=30></TD>
  <TD><font color="#FF0000">*</font></TD><TD><B>Company:</B></TD>
  <TD><INPUT TYPE=TEXT NAME="company" VALUE="<%=imod.getCompany()%> "SIZE=30 MAXLENGTH=100></TD>
 </TR>
 <TR>
  <TD HEIGHT=30></TD>
  <TD><font color="#FF0000">*</font></TD><TD><B>Your Name:</B></TD>
  <TD><INPUT TYPE=TEXT NAME="name" VALUE="<%=imod.getName()%> "SIZE=30 MAXLENGTH=100></TD>
 </TR>
 <TR>
  <TD HEIGHT=30></TD>
  <TD><font color="#FF0000">*</font></TD><TD><B>1.Address Field:</B></TD>
  <TD><INPUT TYPE=TEXT NAME="address1" VALUE="<%=imod.getAddress1()%>" SIZE=30 MAXLENGTH=100></TD>
 </TR>
 <TR>
  <TD HEIGHT=30></TD>
  <TD></TD><TD><B>2.Address Field:</B></TD>
  <TD><INPUT TYPE=TEXT NAME="address2" VALUE="<%=imod.getAddress2()%>" SIZE=30 MAXLENGTH=100></TD>
 </TR>
 <TR>
  <TD HEIGHT=30></TD>
  <TD></TD><TD><B>3.Address Field:</B></TD>
  <TD><INPUT TYPE=TEXT NAME="address3" VALUE="<%=imod.getAddress3()%>" SIZE=30 MAXLENGTH=100></TD>
 </TR>
 <TR>
  <TD HEIGHT=30></TD>
  <TD><font color="#FF0000">*</font></TD><TD><B>Zip-Code:</B></TD>
  <TD><INPUT TYPE=TEXT NAME="zipcode" VALUE="<%=imod.getZipcode()%>" SIZE=10 MAXLENGTH=20></TD>
 </TR>
 <TR>
  <TD HEIGHT=30></TD>
  <TD><font color="#FF0000">*</font></TD><TD><B>City:</B></TD>
  <TD><INPUT TYPE=TEXT NAME="place" VALUE="<%=imod.getPlace()%>" SIZE=30 MAXLENGTH=50></TD>
 </TR>
 <TR>
  <TD HEIGHT=30></TD>
  <TD></TD><TD><B>State:</B></TD>
  <TD><INPUT TYPE=TEXT NAME="state" VALUE="<%=imod.getState()%>" SIZE=20 MAXLENGTH=100></TD>
 </TR>
 <TR>
  <TD HEIGHT=30></TD>
  <TD><font color="#FF0000">*</font></TD><TD><B>Country:</B></TD>
  <TD><SELECT NAME="country" SIZE=1><option selected><%=imod.getCountry()%>
                                    <option>Canada
                                    <option>France
                                    <option>Germany
                                    <option>Italy
                                    <option>Spain
                                    <option>United Kingdom
                                    <option>United States
                                    <option>other Country
                                    </SELECT>
 </TR>
 <TR>
  <TD HEIGHT=30></TD>
  <TD><font color="#FF0000">*</font></TD><TD><B>e-mail:</B></TD>
  <TD><INPUT TYPE=TEXT NAME="email" VALUE="<%=imod.getEmail()%>" SIZE=30 MAXLENGTH=50></TD>
 </TR>
 <TR>
  <TD HEIGHT=30></TD>
  <TD></TD><TD><B>Distinguished Name:</B></TD>
  <TD><INPUT TYPE=TEXT NAME="dn" VALUE="<%=imod.getDn()%>" SIZE=30 MAXLENGTH=50></TD>
 </TR>
 <TR>
  <TD HEIGHT=30></TD>
  <TD></TD><TD><B>Certification Agency:</B></TD>
  <TD><SELECT NAME="ca" SIZE=1><option selected><%=imod.getCa()%>
                               <option>IBM CA
                               <option>other Agency
                               <option>[self signed]
     </SELECT>
 </TR>
</TABLE>
<TABLE WIDTH=500 BORDER=0 CELLSPACING=0 CELLPADDING=0>
 <tr><td height=50></td></tr>
 <TR>
  <TD ALIGN="CENTER"><INPUT TYPE=SUBMIT NAME="SubmitButton" VALUE="Submit"></TD>
 </TR>
</TABLE>
</FORM>
<hr>
</b>
</BODY>
</HTML>
