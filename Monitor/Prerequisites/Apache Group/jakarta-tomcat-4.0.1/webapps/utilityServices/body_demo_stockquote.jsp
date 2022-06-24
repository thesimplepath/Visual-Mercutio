<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
<META http-equiv="Content-Style-Type" content="text/css">
<TITLE>Stock Quote Service</TITLE>
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
 // Get access to service properties
 ServiceProperties serviceProps = new ServiceProperties();

 // Get service to invoke operations
 WSDLService stockquoteService = serviceProps.getService(ServiceConstants.STOCKQUOTE);

 boolean firstTime = false;
 String symbol = request.getParameter("symbol");
 if (symbol == null) {
   firstTime = true;
   symbol = "XXX";
 }
%>
<FORM NAME="StockQuote" METHOD="POST" ACTION="body_demo_stockquote.jsp" target="body">
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=550>
 <!--
 <TR>
  <TD HEIGHT=30></TD>
 </TR>
 -->
 <TR>
  <TD ALIGN=CENTER><H3><U>Stock Quote Service</U></H3></TD>
 </TR>
 <TR>
  <TD HEIGHT=10></TD>
 </TR>
 <TR>
  <TD><P><B>Enter a stock symbol and then press the Get Stock Quote button.</B></TD>
 </TR>
 <TR>
  <TD HEIGHT=30></TD>
 </TR>
 <TR>
  <TD>Symbol: 
   <input type="TEXT" name="symbol" size="8" maxlength="8" VALUE="<%=symbol%>">
   </TD>
   </TR>
   
  <% // Determine if this is the first time the JSP is run
     if (firstTime || (symbol == null) || (symbol.equals("")))
    {
      // ADD: ????
    }

    else
    {%>  
 <TR>
  <TD HEIGHT=30></TD>
 </TR>
   <TR>
   <TD>
      Quote for <%=symbol%>:
    <% // Get stock quote
       Float quote = (Float) stockquoteService.invokeOperation("getQuote", new Object[] {symbol});
    %>
    <%=quote%>
    <% if (quote == null)
      out.println("<P><B>[NOTE: Result was null.  Please verify that the service was deployed using " +
                  "the UtilityServicesSetup command.]</B>");
    %>
  </TD>
  </TR>    
    <%}%>
 <TR>
  <TD HEIGHT=30></TD>
 </TR>
   <TR>
   <TD>
   <input type="submit" value="Get Stock Quote">
  </TD>
  </TR>
 </TABLE>
</BODY>
</HTML>
