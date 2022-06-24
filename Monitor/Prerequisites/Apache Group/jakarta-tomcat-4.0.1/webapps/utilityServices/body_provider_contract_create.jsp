<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
<META http-equiv="Content-Style-Type" content="text/css">
<TITLE>Create Provider Contract</TITLE>
<LINK REL=STYLESHEET TYPE="text/css" HREF="style/style.css">
<script language="JavaScript">
  <!--
  function chkForm() {
    if (document.NewProviderContractData.description.value=="") {
      alert("The Title field must not be empty!");
      document.NewProviderContractData.description.focus();
      return false;
    }
    if (!(document.NewProviderContractData.ratings.selectedIndex>=0)) {
      alert("Select one or more Rating Models!");
      return false;
    }
    var check = confirm("Do you really want to create this Contract?");
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
                com.ibm.services.accounting.*,
                com.ibm.services.accounting.models.*,
                com.ibm.services.payment.*,
                com.ibm.services.payment.models.*,
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

 //PaymentModel[] paymentModels = PaymentService.getPaymentModels();
 ArrayList paymentArrayList = (ArrayList) paymentService.invokeOperation("getPaymentModels", new Object[] {});
 PaymentModel[] paymentModels = (PaymentModel[]) paymentArrayList.toArray(new PaymentModel[paymentArrayList.size()]);
 // System.out.println("paymentArrayList:" + paymentArrayList.toString());

 //RatingModel[] ratingModels = AccountingService.getRatingModels();
 ArrayList ratingArrayList = (ArrayList) accountingService.invokeOperation("getRatingModels",new Object[] {});
 RatingModel[] ratingModels = (RatingModel[]) ratingArrayList.toArray(new RatingModel[ratingArrayList.size()]);
 // System.out.println("ratingsArrayList:" + ratingArrayList.toString());
%>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <!--
 <TR>
  <TD HEIGHT=30></TD><TD></TD>
 </TR>
 -->
 <TR>
  <TD></TD>
  <TD ALIGN=CENTER><H3><U>Create Provider Contract</U></H3></TD>
 </TR>
 <!--
 <TR>
  <TD HEIGHT=20></TD><TD></TD>
 </TR>
 -->
 <TR>
  <TD></TD>
  <TD ALIGN=LEFT><B>Enter the title of your Provider Contract in the <B>Title</B> field, select a
         Payment Model, and one or more Rating Models:</B>
  </TD>
 <TR
</TABLE>
<FORM NAME="NewProviderContractData" METHOD="POST" ACTION="CreateProviderContract" onSubmit="return chkForm()">
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=500>
 <TR>
  <TD WIDTH=40 HEIGHT=50></TD>
  <TD WIDTH=150></TD>
  <TD WIDTH=260></TD>
 </TR>
 <TR>
  <TD></TD>
  <TD><P><B>Contract Title:</B></TD>
  <TD>
   <INPUT TYPE=TEXT NAME="description" VALUE="" SIZE=40 MAXLENGTH=100>
  </TD>
 </TR>
 <TR>
  <TD HEIGHT=10></TD><TD></TD><TD></TD>
 <TR>
 <TR>
  <TD></TD>
  <TD><P><B>Service Name:</B></TD>
  <TD>
   <INPUT TYPE=TEXT NAME="serviceName" VALUE="" SIZE=60 MAXLENGTH=100>
  </TD>
 </TR>
 <TR>
  <TD HEIGHT=10></TD><TD></TD><TD></TD>
 <TR>
  <TD></TD>
  <TD><P><B>Payment Model:</B></TD>
  <TD>
   <SELECT NAME="payment" SIZE=1>
    <%  for (int i=0;i<paymentModels.length;i++) {
         out.println("<option value="+'"'+paymentModels[i].getPaymentkey()+'"'+">"+paymentModels[i].getDescription());
        } %>
   </SELECT>
  </TD>
 </TR>
 <TR>
  <TD HEIGHT=10></TD><TD></TD><TD></TD>
 <TR>
 <TR>
  <TD></TD>
  <TD VALIGN=TOP><P><B>Rating Models:</B></TD>
  <TD>
   <SELECT NAME="ratings" SIZE=3 MULTIPLE>
    <%  for (int i=0; i<ratingModels.length;i++) {
         out.println("<option value="+'"'+ratingModels[i].getRatingkey()+'"'+">"+ratingModels[i].getDescription());
        } %>
   </SELECT>
   <br>(press the ctrl-key to select
   <br> multiple Rating Models)
  </TD>
 </TR>
 <TR>
  <TD HEIGHT=50 colspan=3 align=center>
    <input type=submit value="Submit Contract">
    <input type=button value="Cancel" onClick="parent.body.location.href = 'body_provider_contracts.jsp'">
 </TR>
</TABLE>
</FORM>
</BODY>
</HTML>
