<html>
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,java.sql.*,PsDbMgr,PsDbConn,PsDebug,PsConfig,javax.servlet.ServletContext" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">

<link href="css/skin1/global.css" rel="styleSheet" type="text/css">

</head>
<body>
<table cellSpacing=0 cellPadding=0 width="100%">
<tr height=23>
<TD width="11%">&nbsp;</TD>
<td width="89%" class=Bg >
<center>
<font class=swb>
Installation <%=application.getServletContextName()%>
</font><br>
</center>
</td>
</tr>
</table>

<br>
<TABLE width="100%" border=0>
  <TR>
    <TD width="11%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="89%" >

<form name=FRM action="setup.jsp" method=POST>
<table cellSpacing=0 cellPadding=0 width="100%">
 <tr class=Bg height=23 >
 <td>&nbsp;<img src="img/skin1/ard.gif">&nbsp;</td>
 <td><font class=swb>Paramètre</font></td>
 <td><font class=swf>Valeur</font></td>
 </tr>

<% 
  int mode=0;
  if (request.getParameter( "MODE" )!=null)
  	mode=Integer.valueOf(request.getParameter( "MODE" )).intValue();
  PsApp.init(); 
System.out.println("------------>"+application.getAttribute("*") );
  //mode 1
  if (mode==1)
  {
	PsDebug.log("SETUP.JSP update configuration...");
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
  else
  {
  	PsDebug.log("SETUP.JSP create configuration file");
	PsConfig.reset();
	PsConfig.set("COMPANY","Entreprise Modèle");

	PsConfig.set("JNDIFACTORY","com.sun.jndi.ldap.LdapCtxFactory");
	PsConfig.set("JNDIPROVIDER","ldap://localhost:389/o=MyEnterprise");
	PsConfig.set("USELDAP","0");

	PsConfig.set("JDBCDRIVER","org.gjt.mm.mysql.Driver");
	PsConfig.set("JDBCDNS","jdbc:mysql://localhost:3306/test2");
	PsConfig.set("JDBCLOGIN","");
	PsConfig.set("JDBCPASSWD","");

	PsConfig.set("SESSION_TIMEOUT","1800");

	PsConfig.set("ZSERVER_ROOT","");
	PsConfig.set("FILE_PRIVATE_DIR","/Program Files/Apache Group/jakarta-tomcat-4.0.1/webapps/emessenger/private");
	PsConfig.set("FILE_PUBLIC_DIR","/Program Files/Apache Group/jakarta-tomcat-4.0.1/webapps/emessenger/public");
	PsConfig.set("WELCOME_SCREEN","<br><h1><center><font name=arial color=#c0c0c0>Bienvenue...</font></center></h1>");

	PsConfig.set("SCRIPTOR_LAUNCHER","C:\\Program Files\\ProcessSoft\\Visual Mercutio\\zScriptor.exe");

	PsConfig.set("DEBUG","1");
	
	PsConfig.save("config.ini");
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
<br>

<center>
<input type=submit value="Apply Changes" class=sbttn>
</center>
</form>
</tr></tr>
</table>

<table cellSpacing=0 cellPadding=0 width="100%">
<tr height=13>
<TD width="11%">&nbsp;</TD>
<td width="89%" class=Bg >&nbsp;</td>
</tr>
</table>

</body>
</html>