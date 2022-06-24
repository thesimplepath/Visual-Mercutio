<%@ page import="java.util.*" %> <%@ page import="java.lang.*" %> <%@ page import="java.sql.*" %>
<%@ page import="PsApp" %> <%@ page import="PsDbMgr" %> <%@ page import="PsDbConn" %> 
<%@ page import="PsDebug" %> <%@ page import="PsConfig" %> <%@ page import="PsWorkGroup" %>
<%@ page import="PsWf" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML><HEAD><TITLE>Detailed Case</TITLE>
<META http-equiv=Content-Type content="text/html; charset=iso-8859-1">
<LINK href="css/global.css" rel=STYLESHEET>
<SCRIPT language=JavaScript src="js/global.js"></SCRIPT>
<SCRIPT language=JavaScript src="js/pss.js"></SCRIPT>

<script language=JavaScript>
<!--
function doChangeStatus(mode,caseid,transid,statusid)
{
	var url;
	url=escape(document.location);
	document.location="statustrans.jsp?MODE="+mode+"&CASEID="+caseid+"&TRANSID="+transid+"&STATUSID="+statusid+"&REDIRECT="+url;
}

function sendChief(procid,caseid,transid)
{
	var url;
	url=escape("listcase.jsp?MODE=0");
	document.location="chief.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&REDIRECT="+url;
}

function doStartDeliv(procid,caseid,transid,delivid,lateral)
{
	var url;
	url=escape('<%=(String)request.getParameter( "REDIRECT" )%>');
	document.location="deliv.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&DELIVID="+delivid+"&LATERAL="+lateral+"&REDIRECT="+url;
}

function retSender(procid,caseid,transid)
{
	var url;
	url=escape("listcase.jsp?MODE=0");
	document.location="return.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&REDIRECT="+url;
}

function terminate(url)
{
	if (DelivValidator.validator()==true)
		document.location=url;
}

//-->
</script>


</HEAD>
<BODY text=#000000 vLink=#666666 link=#003399 bgColor=#ffffff leftMargin=0 topMargin=0 MARGINHEIGHT="0" MARGINWIDTH="0">
<TABLE width="100%" border=0>
  <TBODY>
  <TR>
    <TD width="11%" >&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="89%">
      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width="100%">
        <TBODY>
        <TR bgColor=#336699>
          <TD align=middle width="1%" height=23><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23><INPUT title=""    onclick='alert("NA");' tabIndex=105 type=checkbox name=allbox> </TD>
          <TD width="96%"><NOBR><FONT class=swb color=#ffffff>Informations</FONT></NOBR><NOBR>&nbsp;</NOBR></TD>
        </TR>
<%
 PsApp.init();

 String redirect;
 String username;
 int userid,userrole,procid,delivid,caseid,transid,lateral;
 PsDbConn conn;
 PsDbConn conn2;
 conn=PsDbMgr.newConnection();
 conn2=PsDbMgr.newConnection();
 ResultSet rs,rs2; 

 username=(String)session.getAttribute("USERNAME");
 userid=	 Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 userrole=	 Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();

 caseid = 		Integer.valueOf(request.getParameter( "CASEID" )).intValue();
 procid = 		Integer.valueOf(request.getParameter( "PROCID" )).intValue();
 transid=		Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
 delivid=		Integer.valueOf(request.getParameter( "DELIVID" )).intValue();
 lateral=		Integer.valueOf(request.getParameter( "LATERAL" )).intValue();
 redirect=		(String)request.getParameter( "REDIRECT" );

 rs=conn.sqlQueryR("SELECT * FROM pdeliv,ppdattr WHERE pdeliv.delivid="+delivid+" AND pdeliv.pdattribid=ppdattr.pdattribid AND attribdefid>=60 AND attribdefid<=79");

 //deliv input
 while (rs.next())
 {	
	if (rs.getString("mvalue").length()>0)
	{
		out.println("<TR>");
	        out.println("<TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>");
		String checked="";
		rs2=conn2.sqlQueryR("SELECT * FROM pinfostatus WHERE caseid="+caseid+" AND procid="+procid+" AND transid="+transid+" AND infoid="+rs.getInt("attribdefid"));
		if (rs2.next()==true)
			if (rs2.getInt("mstate")==1)
				checked="checked";
 	        out.println("<TD width=\"3%\"><INPUT "+checked+" onclick='javascript:document.location=\"setinfo.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&DELIVID="+delivid+"&REDIR=\"+escape(document.location)+\"&INFOID="+rs.getString("attribdefid")+"\";' type=checkbox> </TD>");
		out.println("<TD width=\"96%\">"+rs.getString("mvalue")+"</TD></TR>");
	}
 }
%>
</tbody></table></td></tr>
  <TR>
    <TD width="11%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="89%">
      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width="100%">
        <TBODY>
        <TR bgColor=#336699>
          <TD align=middle width="1%" height=23><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23><INPUT title="Démarrer toutes les références" onclick='alert("NA");' tabIndex=105 type=checkbox name=allbox> </TD>
          <TD width="82%"><NOBR><FONT class=swb color=#ffffff>Références</FONT></NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" bgColor=#93bee2><NOBR><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/desc.gif" width=7 border=0>
		<FONT class=sbbd color=#003366>Date</FONT>&nbsp;</NOBR></TD>
        </TR>
<%
 PsApp.init();

 conn=PsDbMgr.newConnection();
 conn2=PsDbMgr.newConnection();
 
 username=(String)session.getAttribute("USERNAME");
 userid=	 Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 userrole=	 Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();

 caseid = 		Integer.valueOf(request.getParameter( "CASEID" )).intValue();
 procid = 		Integer.valueOf(request.getParameter( "PROCID" )).intValue();
 transid=		Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
 delivid=		Integer.valueOf(request.getParameter( "DELIVID" )).intValue();

 rs=conn.sqlQueryR("SELECT ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue FROM pdeliv,ppdattr WHERE pdeliv.delivid="+delivid+" AND pdeliv.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid in (9,10)");

 //references
 while (rs.next())
 {	
	if (rs.getInt("attribdefid")!=9)
		PsDebug.fail("detailcase.jsp: references order scrambled");
	String titreRef=rs.getString("mvalue");
	if (rs.next()==false)
		PsDebug.fail("detailcase.jsp: data link broken");
	if (rs.getInt("attribdefid")!=10)
		PsDebug.fail("detailcase.jsp: references order scrambled");
	String reference=rs.getString("mvalue");

	String checked="";
	String mdated="&nbsp;";
/*
	rs2=conn2.sqlQueryR("SELECT * FROM ptaskstatus WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid+" AND taskid="+rs.getString("attribdefid"));
	if (rs2.next()==true)
	{
		if (rs2.getInt("mstate")==1)
			checked="checked";
		mdated=rs2.getString("mdated");
	}
*/
	if (reference.length()>0)
	{
	out.println("<TR>");
        out.println("<TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>");
	out.println("<TD width=\"3%\"><INPUT "+checked+" onclick='javascript:document.location=\"settask.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&ATTRIBID="+rs.getString("attribdefid")+"&REDIRECT=detailcase.jsp%3FCASEID%3D"+caseid+"%26PROCID%3D"+procid+"%26TRANSID%3D"+transid+"\";' type=checkbox> </TD>");
	out.println("<TD width=\"82%\"><a href='javascript:alert(\""+reference+"\");' >"+titreRef+"</a></TD>");
	out.println("<TD width=\"14%\">"+mdated+"</TD></TR>");
	}
 }
%>
</tbody></table></td></tr>
</TBODY></TABLE>

<TABLE width="100%" border=0>
  <TBODY>
  <TR>
    <TD width="11%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="89%">
<!--
	<input type=button value="Retour pour non conformité" onclick='javascript:retSender(<%=procid%>,<%=caseid%>,<%=transid%>);'>&nbsp;
	<input type=button value="Remise au chef" onclick='javascript:sendChief(<%=procid%>,<%=caseid%>,<%=transid%>);'>&nbsp;
-->
        <input type=button value="Revenir à la procédure" onclick='javascript:document.location="<%=(String)request.getParameter( "REDIRECT" )%>"'>&nbsp;
<%if (Integer.valueOf(request.getParameter( "LATERAL" )).intValue()>=0) {%>
	<input type=button value="Terminé" onclick='javascript:doStartDeliv(<%=(String)request.getParameter( "PROCID" )%>,<%=(String)request.getParameter( "CASEID" )%>,<%=(String)request.getParameter( "TRANSID" )%>,<%=(String)request.getParameter( "DELIVID" )%>,<%=(String)request.getParameter( "LATERAL" )%>);'>
<%}%>
	</td>
    </tr>
  </tbody>
</table>
</BODY></HTML>
