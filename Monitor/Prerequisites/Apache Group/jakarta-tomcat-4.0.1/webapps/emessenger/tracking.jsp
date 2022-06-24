<HTML>
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsWorkGroup,PsWf" %>
<HEAD><TITLE>Search Cases</TITLE>
<jsp:include page="checksession.jsp" flush="false" />
<%@ page session="true" %>
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">

<META http-equiv=Content-Type content="text/html; charset=utf-8">


<%
 PsApp.init();

 String username=(String)session.getAttribute("USERNAME");
 if (username==null) return;
 int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 int userrole=		Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();

 int caseid=		Integer.valueOf(request.getParameter("CASEID")).intValue();
 int transid=		Integer.valueOf(request.getParameter("TRANSID")).intValue();
%>

<!-- ------------------------------------ //-->
<script language=JavaScript>
//Display tab on top.jsp
var info1="Utilisateur:</td><td><b><%=(String)session.getAttribute("USERNAME")%></b>, <%=(String)session.getAttribute("USERROLETXT")%> (<%=(String)session.getAttribute("USERWORKGROUPTXT")%>)";
var info2="Historique du cas:</td><td><%=caseid%>.<%=transid%>";
var tabno=3;
top.showTabText(tabno,info1,info2);
</script>
<!-- ------------------------------------ //-->

</head>

<BODY>
<TABLE width="100%" border=0>
  <TR>
    <TD width="1%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%" nobr>
      <TABLE class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 width="100%">
        <TR class=Bg>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="10%"><NOBR><FONT class=menu>Statut&nbsp;</FONT></NOBR></TD>
          <TD width="17%"><NOBR><FONT class=menu>Procédure&nbsp;</FONT></NOBR></TD>
          <TD width="40%"><NOBR><FONT class=menu>Livrables démarrés&nbsp;</FONT></NOBR></TD>
          <TD width="10%"><NOBR><FONT class=menu>Date d'envoi du livrable&nbsp;</FONT></NOBR></TD>
          <TD width="10%"><NOBR><FONT class=menu>Utilisateur&nbsp;</FONT></NOBR></TD>
          <TD width="10%"><NOBR><FONT class=menu>Date d'arrivée&nbsp;</FONT></NOBR></TD>
        </TR>
<%
try {
	PsDbConn conn=PsDbMgr.newConnection();
	PsDbConn conn2=PsDbMgr.newConnection();
	ResultSet rs;
	ResultSet rs2;

	String statut;
	String proc;
	String delivs;
	String delivsdate;
	String dated;
	String users;
	String whichmenu;
	String whichimg;

	rs=conn.sqlQueryR("SELECT * FROM pemployee,ppdattr,pstatus,pproc,pproctrans WHERE pproctrans.caseid="+caseid+" AND pproctrans.transid="+transid+" AND pproc.procid=pproctrans.procid AND pstatus.statusid=pproctrans.statusid AND ppdattr.pdattribid=pproc.procid AND ppdattr.attribdefid= 1310721 AND pemployee.emplid=pproctrans.emplid");
	while (rs.next())
	{
	 //display different color for 'in progress procedures'
	 whichmenu="menu";
	 whichimg="img/arr.gif";
	 if (rs.getInt("statusid")<90)
	 {
		whichmenu="menu2";
		whichimg="img/arrok.gif";
         }

	 //get vars
	 statut=rs.getString("statusname");
	 proc=rs.getString("mvalue");	 
	 users="<a class=menu title=\""+rs.getString("fname")+" "+rs.getString("lname")+"\">"+rs.getString("login")+"</a>";
	 dated=rs.getString("indate");
	
	 //create the list of deliverables
	 delivs=null;
	 delivsdate=null;
	 rs2=conn.sqlQueryR("SELECT * FROM pdeliv,ppdattr,pdelivstatus WHERE pdelivstatus.caseid="+caseid+" AND pdelivstatus.transid="+transid+" AND pdelivstatus.procid="+rs.getString("procid")+" AND pdeliv.delivid=pdelivstatus.delivid AND ppdattr.pdattribid=pdeliv.delivid AND ppdattr.attribdefid=1310721");
	 while (rs2.next())
	 {
		if (delivs==null)
		{
			delivs=rs2.getString("mvalue");
			delivsdate=rs2.getString("mdated");
		}
		else
		{
			delivs=delivs+"<br>"+rs2.getString("mvalue");
			delivsdate=delivsdate+"<br>"+rs2.getString("mdated");
		}
	 }

	 if (delivs==null) //no deliv started yet
		delivs="";		
	 if (delivsdate==null)
		delivsdate="";
%>
	 <TR>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="<%=whichimg%>"></TD>
          <TD width="10%"><NOBR><FONT class=menu>&nbsp;<%=statut%></FONT></NOBR></TD>
          <TD width="17%"><NOBR><FONT class=<%=whichmenu%> ><%=proc%></FONT></NOBR></TD>
          <TD width="40%"><NOBR><FONT class=menu><%=delivs%>&nbsp;</FONT></NOBR></TD>
          <TD width="10%"><NOBR><FONT class=menu><%=delivsdate%>&nbsp;</FONT></NOBR></TD>
          <TD width="10%"><NOBR><FONT class=menu><%=users%></FONT></NOBR></TD>
          <TD width="10%"><NOBR><FONT class=menu><%=dated%></FONT></NOBR></TD>
        </TR>
<%
	}//while
    }
catch (SQLException e)
    {
	PsDebug.fail("listcase.jsp: SQLException: "+e.getMessage());
    }
%>
</TABLE>
</TD>
</TR>
</TABLE>
</FORM>
</BODY>
</HTML>
