<%@ page import="java.util.*" %>
<%@ page import="java.lang.*" %>
<%@ page import="java.sql.*" %>
<%@ page import="PsApp" %>
<%@ page import="PsDbMgr" %>
<%@ page import="PsDbConn" %>
<%@ page import="PsDebug" %>
<%@ page import="PsConfig" %>
<%@ page import="PsWorkGroup" %>
<html>
<head>
<LINK href="css/global.css" rel=STYLESHEET type="text/css">
<script language=JavaScript src="js/pss.js"></script>
</head>
<BODY text=#000000 vLink=#666666 link=#003399 bgColor=#ffffff leftMargin=0 topMargin=0 MARGINHEIGHT=0 MARGINWIDTH=0>
<TABLE width="100%" border=0>
  <TBODY>
  <TR>
    <TD width="11%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="89%">
      <TABLE class=msglistcntrl id=msglistcntrl cellSpacing=2 cellPadding=0 
      border=0>
        <TBODY>
        <TR>          
          <TD width=188><INPUT maxLength=80 size=80 name=casename> </TD>
          <TD noWrap align=right width=121>
	<INPUT class=sbttn title="Créer un nouveau cas à partir du nom saisi." onclick="doSubmit(-1,casename.value,transname.value);" tabIndex=2 type=button value="Nouveau cas" name=create> 
          </TD></FORM></TR></TBODY></TABLE></TD>
  <TR>
 	<TD width="11%">&nbsp;</TD>
	<TD class=NormalBlack vAlign=top width="89%">
	<INPUT maxLength=80 size=80 name=transname>
	</TD>
  </TR>
  <TR>
    <TD width="11%" height=559>&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="89%" height=559>
      <TABLE class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 
        width="100%"><TBODY>
        <TR bgColor=#336699>
          <TD align=middle width="3%"><NOBR>&nbsp;</NOBR></TD>
          <TD width="6%" height=23>&nbsp; </TD>
          <TD width="32%"><NOBR><FONT class=swb color=#ffffff>Cas existants</FONT></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="59%"><NOBR><FONT class=swb color=#ffffff>Processus</FONT></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD></TR>
<%
 PsApp.init();

 String username=(String)session.getAttribute("USERNAME");

try {
	PsDbConn conn=PsDbMgr.newConnection();
	ResultSet rs;
	rs=conn.sqlQueryR("SELECT casename,ptrans.caseid,mvalue,transname FROM pcase,ptrans,pproctrans,pproc,pprocattr WHERE ptrans.caseid=pproctrans.caseid AND ptrans.transid=pproctrans.transid AND pprocattr.procattribid=pproc.procattribid AND pprocattr.prow=0 AND pproc.procid=pproctrans.procid AND pcase.caseid=pproctrans.caseid AND pproctrans.statusid in (0,1,2) ORDER BY pcase.casename");
	while (rs.next())
	{
        out.println("<TR>");
        out.println("  <TD width=\"3%\">&nbsp;</TD>");
        out.println("  <TD width=\"6%\"><INPUT onclick='doSubmit("+rs.getInt("caseid")+",\""+rs.getString("casename")+"\",transname.value);' type=checkbox> ");
        out.println("  </TD>");
        out.println("  <TD width=\"32%\">"+rs.getString("casename")+" "+rs.getString("transname")+"</TD>");
        out.println("  <TD width=\"59%\">"+rs.getString("mvalue")+"</TD></TR>");
	}
    }
catch (SQLException e)
    {
	PsDebug.fail("newcase1.jsp: SQLException: "+e.getMessage());
    }
%>
</TBODY></TABLE>
    </TD></FORM></TR></TBODY></TABLE>
<SCRIPT language=javascript>
//top.menu.showTab(4);

function doSubmit(caseattachid,casename,transname) {
	var fromproc=-1; //no previous procedure
	var transid=<%=PsDbMgr.newConnection().nextVal("PTRANS")%>;
	var dta=new PssData(caseattachid,casename,<%=(String)request.getParameter( "PROCID" )%>,<%=(String)session.getAttribute("USERID")%>,transname,transid,0,0,0,-1);
	//var cnt=0;
	//for (i=0;i<rowid;i++)
	{
	//	var mkey=document.FRM.all["PSSKEY"+i];
	//	var mval=document.FRM.all["PSSVAL"+i];

	//	if (mkey!=null)
		{
	//		dta.addAttrib(new PssDataAttrib(i,mkey.name,mkey.value,mval.value));
		}
	}
	dta.post("newproc2.jsp");
}
</script>
</body>
</html>