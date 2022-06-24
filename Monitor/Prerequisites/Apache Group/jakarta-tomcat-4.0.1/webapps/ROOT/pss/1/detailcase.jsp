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
var DelivValidator=new PssProcedureValidator();
</script>

<script language=JavaScript>
<!--
<%
 int caseid=Integer.valueOf(request.getParameter( "CASEID" )).intValue();
 int transid=Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
 PsDbConn aconn=PsDbMgr.newConnection();
 ResultSet ars=aconn.sqlQueryR("SELECT casename,transname FROM pcase,ptrans WHERE pcase.caseid="+caseid+" AND ptrans.caseid=pcase.caseid AND ptrans.transid="+transid);
 ars.next();
 String casename=ars.getString("casename");
 String transname=ars.getString("transname");
 ars=aconn.sqlQueryR("SELECT * FROM pproc,ppdattr WHERE ppdattr.pdattribid=pproc.pdattribid AND ppdattr.prow=0 AND pproc.procid="+Integer.valueOf(request.getParameter( "PROCID" )).intValue());
 ars.next();
 String procname=ars.getString("mvalue");
%>
top.menu.showText("Utilisateur:</td><td><%=(String)session.getAttribute("USERNAME")%>","Cas:</td><td><%=casename%> <%=transname%> =&gt; <%=procname%>");
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
	url=escape(document.location);
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

function signature(url)
{
	if (DelivValidator.validator()==true)
		document.location=url;
}


function showDeliv(procid,caseid,transid,delivid,lateral)
{
	var url;
	url=escape(document.location);
	document.location="detaildeliv.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&DELIVID="+delivid+"&REDIRECT="+url+"&LATERAL="+lateral;
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
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/ard.gif"></TD>
          <TD width="82%"><NOBR><FONT class=swb color=#ffffff>Livrables en entrée</FONT></NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" bgColor=#93bee2><NOBR><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/desc.gif" width=7 border=0>
		<FONT class=sbbd color=#003366>Date</FONT>&nbsp;</NOBR></TD>
        </TR>
<%
 PsApp.init();

 String username;
 int userid,userrole,procid;
 PsDbConn conn;
 PsDbConn conn2;
 conn=PsDbMgr.newConnection();
 conn2=PsDbMgr.newConnection();
 ResultSet rs,rs2; 
 
 int signaturemode=0;

 username=(String)session.getAttribute("USERNAME");
 userid=	 Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 userrole=	 Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();

 caseid = 		Integer.valueOf(request.getParameter( "CASEID" )).intValue();
 procid = 		Integer.valueOf(request.getParameter( "PROCID" )).intValue();
 transid=		Integer.valueOf(request.getParameter( "TRANSID" )).intValue();

 //Display from delivs
 boolean readyOrNot=false;

 rs=conn.sqlQueryR("SELECT mvalue FROM pproc,ppdattr WHERE pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid=59 AND pproc.procid="+procid);
 String delivMaster;
 if (rs.next()==true)
	 delivMaster=rs.getString("mvalue");
 else
	 delivMaster="Start";

 rs=conn.sqlQueryR("SELECT * FROM pdeliv,pdelivstatus WHERE pdelivstatus.procid=pdeliv.procidsrc AND pdelivstatus.caseid="+caseid+" AND pdelivstatus.transid="+transid+" AND pdelivstatus.delivid=pdeliv.delivid AND procidtrg="+procid);

 //deliv input
 while (rs.next())
 {	
	String checked="arr.gif";
	String mdated="&nbsp;";
	String font1="";
	String font2="";
	if (rs.getInt("mstate")==1)
	{
		checked="arrok.gif";
		mdated=rs.getString("mdated");

		if (rs.getString("delivname").equalsIgnoreCase(delivMaster))
		{
			readyOrNot=true;

			font1="<font color=red>";
			font2="</font>";
		}
	}

	String dlink="javascript:showDeliv("+procid+","+caseid+","+transid+","+rs.getInt("delivid")+",-1);";

	out.println("<TR>");
        out.println("<TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>");
	out.println("<TD width=\"3%\" valign=bottom>");
	out.println("&nbsp;<IMG SRC=\"img/"+checked+"\"></TD>");
	out.println("<TD width=\"82%\"><a href=\""+dlink+"\">"+font1+rs.getString("delivname")+font2+"</a>&nbsp;");
	int nbrr=PsWf.delivNbrReferences(rs.getInt("delivid"));if (nbrr>0) out.println("<img src=img/reference.gif> ");
	int nbri=PsWf.delivNbrInformations(rs.getInt("delivid"));if (nbri>0) out.println("<img src=img/info.gif> ");
	out.println("</TD>");

	out.println("<TD width=\"14%\">"+mdated+"</TD></TR>");

	//if readyOrNot is false, all the rest must be READONLY
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
          <TD width="3%" height=23><INPUT title="Sélectionner ou annuler la sélection de toutes les tâches"    onclick='alert("NA");' tabIndex=105 type=checkbox name=allbox> </TD>
          <TD width="82%"><NOBR><FONT class=swb color=#ffffff>Tâche</FONT></NOBR><NOBR>&nbsp;</NOBR></TD>
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

 rs=conn.sqlQueryR("SELECT ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue FROM pproc,ppdattr WHERE pproc.procid="+procid+" AND pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid>=13 AND ppdattr.attribdefid<=32");

 //tasks
 while (rs.next())
 {	
	String checked="";
	String mdated="&nbsp;";
	rs2=conn2.sqlQueryR("SELECT * FROM ptaskstatus WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid+" AND taskid="+rs.getString("attribdefid"));
	if (rs2.next()==true)
	{
		if (rs2.getInt("mstate")==1)
			checked="checked";
		mdated=rs2.getString("mdated");
	}

	if (rs.getString("mvalue").length()>0)
	{
	out.println("<TR>");
        out.println("<TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>");
	out.println("<TD width=\"3%\"><INPUT "+checked+" onclick='javascript:document.location=\"settask.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&ATTRIBID="+rs.getString("attribdefid")+"&REDIRECT=detailcase.jsp%3FCASEID%3D"+caseid+"%26PROCID%3D"+procid+"%26TRANSID%3D"+transid+"\";' type=checkbox> </TD>");
	out.println("<TD width=\"82%\">"+rs.getString("mvalue")+"</TD>");
	out.println("<TD width=\"14%\">"+mdated+"</TD></TR>");
	}
 }
%>
</tbody></table></td></tr>
  <TR>
    <TD width="11%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="89%">
      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width="100%">
	<INPUT type=hidden value=F000000001 name=curmbox> 
	<INPUT type=hidden name=js> <INPUT type=hidden name=_HMaction> 
	<INPUT type=hidden value=inbox name=foo> <INPUT type=hidden name=page> 
        <TBODY>
        <TR bgColor=#336699>
          <TD align=middle width="1%"><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23><INPUT title="Sélectionner ou annuler la sélection de toutes les tâches"    onclick='alert("NA");' tabIndex=105 type=checkbox name=allbox> </TD>
          <TD width="82%"><NOBR><FONT class=swb color=#ffffff>Décision</FONT></NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" bgColor=#93bee2><NOBR><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/desc.gif" width=7 border=0>
		<FONT class=sbbd color=#003366>Date</FONT>&nbsp;</NOBR></TD>
        </TR>
<%
 username=(String)session.getAttribute("USERNAME");
 userid=	 Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
 userrole=	 Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();

 caseid = 		Integer.valueOf(request.getParameter( "CASEID" )).intValue();
 procid = 		Integer.valueOf(request.getParameter( "PROCID" )).intValue();

 transid=		Integer.valueOf(request.getParameter( "TRANSID" )).intValue();

 conn=PsDbMgr.newConnection();
 rs=conn.sqlQueryR("SELECT ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue FROM pproc,ppdattr WHERE pproc.procid="+procid+" AND pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid>=33 AND ppdattr.attribdefid<=52");

 //decisions
 while (rs.next())
 {
	String checked="";
	String mdated="&nbsp;";
	rs2=conn2.sqlQueryR("SELECT * FROM pdecisionstatus WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid+" AND decisionid="+rs.getString("attribdefid"));
	if (rs2.next()==true)
	{
		if (rs2.getInt("mstate")==1)
			checked="checked";
		mdated=rs2.getString("mdated");
	}

	if (rs.getString("mvalue").length()>0)
	{
	out.println("<TR>");
	out.println("<TD width=\"1%\">&nbsp;</TD>"); //getInt("attribdefid")
	out.println("<TD width=\"3%\"><INPUT "+checked+" onclick='javascript:document.location=\"setdecision.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&ATTRIBID="+rs.getString("attribdefid")+"&REDIRECT=detailcase.jsp%3FCASEID%3D"+caseid+"%26PROCID%3D"+procid+"%26TRANSID%3D"+transid+"\";' type=checkbox> </TD>");
	out.println("<TD width=\"82%\">"+rs.getString("mvalue")+"</TD>");
	out.println("<TD width=\"14%\">"+mdated+"</TD></TR>");
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
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/ard.gif"></TD>
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

 rs=conn.sqlQueryR("SELECT ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue FROM pproc,ppdattr WHERE pproc.procid="+procid+" AND pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid in (9,10)");

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
  <TR>
    <TD width="11%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="89%">
      <TABLE class=Mtable id=LateralDelivTable cellSpacing=0 cellPadding=0
      width="100%"><INPUT type=hidden value=F000000001 name=curmbox2> <INPUT 
        type=hidden name=js2> <INPUT type=hidden name=_HMaction2> <INPUT 
        type=hidden value=inbox name=foo2> <INPUT type=hidden name=page2> 
        <TBODY>
        <TR bgColor=#336699>
          <TD align=middle width="1%"><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/ard.gif"></TD>
          <TD width="36%"><NOBR><A title="Trier par expéditeur" 
            href=""><FONT class=swb color=#ffffff>Livrables latéraux</FONT></A></NOBR><NOBR></NOBR></TD>
          <TD width="46%"><NOBR><A title="Trier par livrable" 
            href=""><FONT 
            class=swb 
            color=#ffffff>Processus</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" bgColor=#93bee2><NOBR><A title="Trier par date" 
            href=""><IMG 
            height=7 alt="trié par ordre décroissant" hspace=3 
            src="img/desc.gif" width=7 border=0><FONT 
            class=sbbd color=#003366>Date</FONT></A>&nbsp;</NOBR></TD>
	</TR>

<%
 caseid = 		Integer.valueOf(request.getParameter( "CASEID" )).intValue();
 procid = 		Integer.valueOf(request.getParameter( "PROCID" )).intValue();
 transid=		Integer.valueOf(request.getParameter( "TRANSID" )).intValue();

	//check if already locked (concurrency check)
	rs=conn.sqlQueryR("SELECT statusid,emplid FROM pproctrans WHERE procid="+procid+" AND transid="+transid);
	rs.next();
	if (rs.getInt("statusid")==1 && rs.getInt("emplid")!=userid)
	{
		out.println("alert(\"Travail déjà encours par le user "+rs.getInt("emplid")+"\");");
//		return;
	}

	//automatic locking
	conn.sqlExecR("UPDATE pproctrans SET statusid=1,emplid="+userid+" WHERE procid="+procid+" AND transid="+transid+" AND (statusid=0 OR statusid=2)");	


 conn=PsDbMgr.newConnection();
 rs=conn.sqlQueryR("SELECT * FROM pdeliv WHERE procidsrc="+procid+" AND lateral=1");

 //lateral deliv
 while (rs.next())
 {
	int proctrg=rs.getInt("procidtrg");

	if (rs.getString("delivname").length()>0)
	{
	String dlink="javascript:showDeliv("+procid+","+caseid+","+transid+","+rs.getInt("delivid")+",1);";
	String url=dlink;//	//String url="javascript:doStartDeliv("+procid+","+caseid+","+transid+","+rs.getString("delivid")+",1);";
	out.println("<TR>");
        out.println("<TD width=\"1%\">&nbsp;</TD>");

	double pct=PsWf.percentageDeliv(rs.getInt("delivid"));
	int retdelivid=PsWf.getLateralReturn(procid,rs.getInt("delivid"));
	PsDbConn kc=PsDbMgr.newConnection();
	ResultSet ks=kc.sqlQueryR("SELECT openclose FROM pdelivlateralstate WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid+" AND delivid="+retdelivid);
	int delivcompleted=0;
	String st="";
	String mdated="&nbsp;";
	if (ks.next()==true)
	{
		if (ks.getInt("openclose")==0)
		{
			dlink="javascript:showDeliv("+procid+","+caseid+","+transid+","+rs.getInt("delivid")+",-1);";
			url=dlink;//	//String url="javascript:doStartDeliv("+procid+","+caseid+","+transid+","+rs.getString("delivid")+",1);";

			//in progress
		        out.println("<TD width=\"3%\" valign=bottom>&nbsp;<img src=\"img/arr.gif\"></TD><TD width=\"36%\">");
		        out.print("<A href=\""+url+"\">");
			out.print(rs.getString("delivname"));//en cours (wait)
			out.println("</a>");
			st="(en cours)";		

		}
		else
		{
			dlink="javascript:showDeliv("+procid+","+caseid+","+transid+","+rs.getInt("delivid")+",-1);";
			url=dlink;//	//String url="javascript:doStartDeliv("+procid+","+caseid+","+transid+","+rs.getString("delivid")+",1);";

			//completed
		        out.println("<TD width=\"3%\" valign=bottom>&nbsp;<img src=\"img/arrok.gif\"></TD><TD width=\"36%\">");
		        out.print("<A href=\""+url+"\">");
			out.print(rs.getString("delivname"));
			out.println("</A>");

			ks=kc.sqlQuery("SELECT * FROM pdelivstatus WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid+" AND delivid="+retdelivid);
			if (ks.next()==true)
				mdated=ks.getString("mdated");
			
			delivcompleted=1;
		}
	}
        else
	if (pct>=99.999)
	{
	        out.println("<TD width=\"3%\" valign=bottom>&nbsp;<img src=\"img/arrwarn.gif\"></TD><TD width=\"36%\">");
	        out.print("<A href=\""+url+"\">");
		out.print("<FONT color=red>"+rs.getString("delivname")+"</FONT>"); //mandatory
		out.println("</A>");
	}
	else
	{
	        out.println("<TD width=\"3%\" valign=bottom>&nbsp;<img src=\"img/arr.gif\"></TD><TD width=\"36%\">");
	        out.print("<A href=\""+url+"\">");
		out.print(rs.getString("delivname"));
		out.println("</A>");
	}

	//set validator
	if (pct>=99.999) 
	{
		out.println("<script language=JavaScript>");
		out.println("DelivValidator.set(\""+rs.getString("delivname")+"\","+delivcompleted+");");
		out.println("</script>");
	}


	out.println("&nbsp;"+st+"&nbsp");
	int nbrr=PsWf.delivNbrReferences(rs.getInt("delivid"));if (nbrr>0) out.println("<img src=img/reference.gif> ");
	int nbri=PsWf.delivNbrInformations(rs.getInt("delivid"));if (nbri>0) out.println("<img src=img/info.gif> ");
	out.println("</TD>");

        out.println("<TD width=\"46%\">");

	conn2=PsDbMgr.newConnection();
	rs2=conn2.sqlQueryR("SELECT * FROM pproc,ppdattr WHERE pproc.procid="+proctrg+" and pproc.pdattribid=ppdattr.pdattribid and ppdattr.prow=0;");
	rs2.next();	
	out.println(rs2.getString("mvalue"));
	out.println("</TD>");
        out.println("<TD width=\"14%\">"+mdated+"</TD>");
	out.println("</TR>");
	}
 }
%>
  </TBODY></TABLE></TD></TR>
  <TR>
    <TD width="11%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="89%" >
      <TABLE class=Mtable id=FollowingDelivTable cellSpacing=0 cellPadding=0 
      width="100%"><INPUT type=hidden value=F000000001 name=curmbox22> <INPUT 
        type=hidden name=js22> <INPUT type=hidden name=_HMaction22> <INPUT 
        type=hidden value=inbox name=foo22> <INPUT type=hidden name=page22> 
        <TBODY>
        <TR bgColor=#336699>
          <TD align=middle width="1%"><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/ard.gif"></TD>
          <TD width="36%"><NOBR><A title="Trier par expéditeur" 
            href=""><FONT 
            class=swb color=#ffffff>Livrables 
            suivants</FONT></A></NOBR><NOBR></NOBR><NOBR></NOBR><NOBR></NOBR></TD>
          <TD width="46%"><NOBR><A title="Trier par livrable" 
            href=""><FONT 
            class=swb 
            color=#ffffff>Processus</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" bgColor=#93bee2><NOBR><A title="Trier par date" 
            href=""><IMG 
            height=7 alt="trié par ordre décroissant" hspace=3 
            src="img/desc.gif" width=7 border=0><FONT 
            class=sbbd color=#003366>Date</FONT></A>&nbsp;</NOBR></TD>
	</TR>
<%
 caseid = 		Integer.valueOf(request.getParameter( "CASEID" )).intValue();
 procid = 		Integer.valueOf(request.getParameter( "PROCID" )).intValue();

 conn=PsDbMgr.newConnection();
 rs=conn.sqlQueryR("SELECT * FROM pdeliv WHERE procidsrc="+procid+" AND lateral=0");
System.out.println("SELECT * FROM pdeliv WHERE procidsrc="+procid+" AND lateral=0");

 //deliv
 while (rs.next())
 {
	int delivcompleted=0;

	int proctrg=rs.getInt("procidtrg");

	if (rs.getString("delivname").length()>0)
	{
	boolean checked=false;
	String mdated="&nbsp;";
	rs2=conn2.sqlQueryR("SELECT * FROM pdelivstatus WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid+" AND delivid="+rs.getString("delivid"));

	if (rs2.next()==true)
	{
		if (rs2.getInt("mstate")==1)
		{
			checked=true;
			delivcompleted=1;
		}
else
		mdated=rs2.getString("mdated");
	}


	double pct=PsWf.percentageDeliv(rs.getInt("delivid"));

	//set validator
	if (pct>=99.999) 
	{
		out.println("<script language=JavaScript>");
		out.println("DelivValidator.set(\""+rs.getString("delivname")+"\","+delivcompleted+");");
		out.println("</script>");
	}

	String dlink="javascript:showDeliv("+procid+","+caseid+","+transid+","+rs.getInt("delivid")+",0);";

	out.println("<TR>");
        out.println("<TD width=\"1%\">&nbsp;</TD>");
        out.print("<TD width=\"3%\" valign=bottom>&nbsp;");
        if (checked==true)
	  out.println("<img src=\"img/arrok.gif\">");
	else
	  if (pct>=99.999)
		  out.println("<img src=\"img/arrwarn.gif\">");
	  else
		  out.println("<img src=\"img/arr.gif\">");
	out.println("</TD>");
        out.println("<TD width=\"36%\">");
	String url="javascript:doStartDeliv("+procid+","+caseid+","+transid+","+rs.getString("delivid")+",0);";
	out.print("<A href=\""+dlink+"\">");//url
	if (pct>=99.999) out.print("<FONT color=red>");//red ink for mandatory delivs
	out.print(rs.getString("delivname"));
	if (pct>=99.999) out.print("</FONT>");
	out.println("</A>&nbsp;");
	int nbrr=PsWf.delivNbrReferences(rs.getInt("delivid"));if (nbrr>0) out.println("<img src=img/reference.gif> ");
	int nbri=PsWf.delivNbrInformations(rs.getInt("delivid"));if (nbri>0) out.println("<img src=img/info.gif> ");
	out.println("</TD>");
        out.println("<TD width=\"46%\">");

	conn2=PsDbMgr.newConnection();
	rs2=conn2.sqlQueryR("SELECT * FROM pproc,ppdattr WHERE pproc.procid="+proctrg+" and pproc.pdattribid=ppdattr.pdattribid and ppdattr.prow=0;");
	rs2.next();	
	out.println(rs2.getString("mvalue"));
	out.println("</TD>");
        out.println("<TD width=\"14%\">"+mdated+"</TD>");
	out.println("</TR>");
	}
 }
%>
</TBODY></TABLE></TD></TR></TBODY></TABLE>

<TABLE width="100%" border=0>
  <TBODY>
  <TR>
    <TD width="11%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="89%">
	<input type=button value="Retour pour non conformité" onclick='javascript:retSender(<%=procid%>,<%=caseid%>,<%=transid%>);'>&nbsp;
	<input type=button value="Remise au chef" onclick='javascript:sendChief(<%=procid%>,<%=caseid%>,<%=transid%>);'>&nbsp;
<% 
 rs=conn.sqlQueryR("SELECT * FROM pproc WHERE procid="+procid);
 rs.next();
 signaturemode=rs.getInt("doublesign");
 if (signaturemode==0)
	out.println("	<input type=button value=\"Terminé\" onclick='javascript:terminate(\"termin.jsp?REDIRECT=\"+escape(\"listcase.jsp?MODE=0\")+\"&PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"\");'>");
 if (signaturemode>0)
	out.println("	<input type=button value=\"Signature\" onclick='javascript:signature(\"sign.jsp?REDIRECT=\"+escape(\"listcase.jsp?MODE=0\")+\"&PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"\");'>");
%>
	</td>
    </tr>
  </tbody>
</table>
</BODY></HTML>
