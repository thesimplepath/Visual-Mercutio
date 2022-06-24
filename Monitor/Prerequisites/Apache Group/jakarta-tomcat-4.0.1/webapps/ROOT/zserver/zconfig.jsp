<html>
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,java.sql.*,PsDbMgr,PsDbConn,PsDebug,PsConfig" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">

<jsp:include page="checksession.jsp" flush="false" />
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">

<!-- ------------------------------------ //-->
<script language=JavaScript>
//Display tab on top.jsp
var info1="Utilisateur:</td><td><b><%=(String)session.getAttribute("USERNAME")%></b>, <%=(String)session.getAttribute("USERROLETXT")%> (<%=(String)session.getAttribute("USERWORKGROUPTXT")%>)";
var info2="";
var tabno=4;
top.showTabText(tabno,info1,info2);
</script>
<!-- ------------------------------------ //-->

</head>
<body>
<TABLE width="100%" border=0>
  <TR>
    <TD width="11%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="89%" >

<form name=FRM action="config.jsp" method=POST>
<table cellSpacing=0 cellPadding=0 width="100%">
 <tr class=Bg height=23 >
 <td>&nbsp;<img src="img/<%=userskin%>/ard.gif">&nbsp;</td>
 <td><font class=swb>Paramètre</font></td>
 <td><font class=swf>Valeur</font></td>
 </tr>

<% 
  int mode=Integer.valueOf(request.getParameter( "MODE" )).intValue();
  PsApp.init(); 

  //mode 1
  if (mode==1)
  {
	PsDebug.log("CONFIG.JSP update configuration...");
	Enumeration pn=request.getParameterNames();
	for (; pn.hasMoreElements();) 
	{
		String key=(String)pn.nextElement();
		if (key.startsWith("CFG_")==true)
		{
			String val=(String)request.getParameter(key);
			key=key.substring(4) ;
			PsDebug.log("Set config "+key+"=("+val+")");
			PsConfig.set(key,val);			
		}	
	}
	PsConfig.save("config.ini");
	PsDebug.log("Configuration Saved!");	
	System.out.println("Configuration updated successfully!");
	PsConfig.reset();
	PsConfig.load("config.ini");
  }

  Hashtable v; 
  v=PsConfig.getHashTable(); 
  Enumeration f=v.elements();
  for (Enumeration e = v.keys(); e.hasMoreElements() ;) {	 
	 String kn=(String)e.nextElement();
         out.println("<tr><td></td><td>"+kn+" :</td>");
	 out.println("<td><input  style=\"width:100%;\" type=text size=80 name=\"CFG_"+kn+"\" value=\""+(String)f.nextElement()+"\"></td></tr>");
     }
  out.println("<input type=HIDDEN name=MODE value=1>");
 
%>
</table>
<input type=submit value="Save Configuration" class=sbttn>
</form>
</tr></tr>
</table>
</body>
</html>