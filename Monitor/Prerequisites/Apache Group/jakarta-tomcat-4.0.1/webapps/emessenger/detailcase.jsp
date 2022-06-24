<HTML>
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsWorkGroup,PsWf,PsConv,java.io.*" %>
<HEAD><TITLE>Detailed Case</TITLE>
<jsp:include page="checksession.jsp" flush="false" />
<%@ page session="true" %>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache"> 
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">

<script language=JavaScript src="js/tools.js"></script>
<script language=JavaScript src="js/pss.js"></script>
<SCRIPT language=JavaScript src="js/pssdyn.js"></SCRIPT>

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

 ars=aconn.sqlQueryR("SELECT * FROM pproc,ppdattr WHERE ppdattr.pdattribid=pproc.pdattribid AND ppdattr.attribdefid=1310721 AND  pproc.procid="+Integer.valueOf(request.getParameter( "PROCID" )).intValue()); 
 ars.next();
 String procname=ars.getString("mvalue");
%>

// ----------------------------------------------------------------
//Display tab on top.jsp
var info1="Utilisateur:</td><td colspan=2 nobr><NOBR><b><%=(String)session.getAttribute("USERNAME")%></b>, <%=(String)session.getAttribute("USERROLETXT")%> (<%=(String)session.getAttribute("USERWORKGROUPTXT")%>)</NOBR>";
var info2="Cas:</td><td><b><%=casename%>, <%=transname%></b></td><td align=right><FONT class=menu>Procédure:</font> <b><%=procname%></b>";
top.showText(info1,info2);
// ----------------------------------------------------------------

function doUpload(caseid,transid)
{
	var dialogWindow = window.open("upload.jsp?MODE=0&CASEID="+caseid+"&TRANSID="+transid,"","height=200,width=300,modal=yes");
}

function doChangeStatus(mode,procid,caseid,transid,statusid)
{
	var url;
	url=escape("listcase.jsp?MODE=0");
	document.location="statustrans.jsp?MODE="+mode+"&PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&STATUSID="+statusid+"&REDIRECT="+url;
}

function sendChief(procid,caseid,transid)
{
	var url;
	var msg;
	url="listcase.jsp?MODE=0";
	msg=window.prompt("Veuillez décrire la remise au chef","");
	if (msg=="null")
		msg="";
	document.writeln("<form method=post name=go action=\"chief.jsp\">");
	document.writeln("<input type=hidden name=PROCID value=\""+procid+"\">");
	document.writeln("<input type=hidden name=CASEID value=\""+caseid+"\">");
	document.writeln("<input type=hidden name=TRANSID value=\""+transid+"\">");
	document.writeln("<input type=hidden name=REDIRECT value=\""+url+"\">");
	document.writeln("<input type=hidden name=MSG value=\""+msg+"\">");
	document.writeln("</form>");
	document.writeln("<script language=JavaScript>");
	document.writeln("document.go.submit();");
	document.writeln("</script>");
}

function capsuleTravail(procid,caseid,transid)
{
	window.open("capsuleTravailGenerate.jsp?procid="+procid+"&caseid="+caseid+"&transid="+transid, "ProcessSoft", 'resizable=no,menubar=no,scrollbars=yes,statusbar=no,width=500,height=200') ;
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
	var msg;
	url="listcase.jsp?MODE=0";
	msg=window.prompt("Veuillez décrire le retour pour non conformité","");	
	if (msg=="null")
		msg="";
	document.writeln("<form method=post name=go action=\"return.jsp\">");
	document.writeln("<input type=hidden name=PROCID value=\""+procid+"\">");
	document.writeln("<input type=hidden name=CASEID value=\""+caseid+"\">");
	document.writeln("<input type=hidden name=TRANSID value=\""+transid+"\">");
	document.writeln("<input type=hidden name=REDIRECT value=\""+url+"\">");
	document.writeln("<input type=hidden name=MSG value=\""+msg+"\">");
	document.writeln("</form>");
	document.writeln("<script language=JavaScript>");
	document.writeln("document.go.submit();");
	document.writeln("</script>");

}

function terminate(url,delivLatMandatory,delivLatInProgress,delivLatReturned,delivNextStarted,delivNextMandatory,delivTotalNbr)
{
	if (delivTotalNbr==0)
	{
		//'stop' - don't check
	}
	else
	{
		if (delivLatInProgress>0)
		{
			alert("Vous devez attendre le retour des livrables latéraux pour terminer la procédure en cours");
			return;
		}
		if (delivNextStarted==0)
		{
			alert("Vous devez envoyer au moins un livrable suivant pour terminer la procédure en cours");
			return;
		}
	}

	var n=NBR_INPUT.value;
	var st="&NBR_INPUT="+n;
	for (i=1;i<=n;i++)
	{
		st=st+"&CTL_"+i+"="+escape(document.getElementById("CTL_"+i).value);
		st=st+"&CTL2_"+i+"="+escape(document.getElementById("CTL2_"+i).value);
	}

	if (DelivValidator.validator()==true)
		document.location=url+st;	//TODO: faire un POST
}

function signature(url,delivLatMandatory,delivLatInProgress,delivLatReturned,delivNextStarted,delivNextMandatory,delivTotalNbr)
{

	if (delivTotalNbr==0)
	{
		//'stop' - don't check
	}
	else
	{
		if (delivLatInProgress>0)
		{
			alert("Vous devez attendre le retour des livrables latéraux pour signer la procédure en cours!");
			return;
		}
		if (delivNextStarted==0)
		{
			alert("Vous devez envoyer au moins un livrable suivant pour signer la procédure en cours!");
			return;
		}
	}

	var n=NBR_INPUT.value;
	var st="&NBR_INPUT="+n;
	for (i=1;i<=n;i++)
	{
		st=st+"&CTL_"+i+"="+escape(document.getElementById("CTL_"+i).value);
		st=st+"&CTL2_"+i+"="+escape(document.getElementById("CTL2_"+i).value);
	}
	//TODO: faire un POST

	if (DelivValidator.validator()==true)
		document.location=url+st;
}


function showDeliv(procid,caseid,transid,delivid,lateral,delivLatInProgress,delivLatMandatory)
{
	if (delivLatMandatory>0)
	{
		alert("Vous devez démarrer les livrables latéraux obligatoires pour envoyer un livrable suivant!");
		return;
	}
	if (delivLatInProgress>0)
	{
		alert("Vous devez attendre le retour des livrables latéraux en cours pour envoyer un livrable suivant!");
		return;
	}

	var url;
	url=escape(document.location);

	document.location="detaildeliv.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&DELIVID="+delivid+"&REDIRECT="+url+"&LATERAL="+lateral;
}


function writeObj(id,text)
{
  if (document.getElementById)
	{
		x = document.getElementById(id);
		x.innerHTML = text;
	}
	else if (document.all)
	{
		x = document.all[id];
		x.innerHTML = text;
	}
	else if (document.layers)
	{
		x = document.layers[id];
		x.document.open();
		x.document.write(text);
		x.document.close();
	}

}

function processRow(rowno,ncnt)
{
	objname=""+rowno;
	writeObj("CNT"+objname,ncnt);
	if (ncnt==0) {document.all["ROW"+objname].style.display="none";}
	
}

//-->
</script>


</HEAD>
<BODY>
<TABLE width="100%" border=0>
  <TBODY><applet name=CTL code=AppLauncher.class archive=AppLauncher.jar width=1 height=1></applet>
  <TR id=ROW1>
    <TD width="1%" >&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%" nobr>
      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width="100%">
        <TBODY>
        <TR class=Bg>
          <TD align=middle width="1%" height=23><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="82%"><NOBR><FONT class=menu>Livrables en entrée</FONT> (<a class=menu name=CNT1></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" class=BgL><NOBR><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/<%=userskin%>/desc.gif" width=7 border=0>
		<FONT class=swnub>Date</FONT>&nbsp;</NOBR></TD>
        </TR>
<%
 PsApp.init();

 //automatic shrink empty rows
 boolean autoShrinkMode=true;

 int ncnt=0;

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

 rs=conn.sqlQueryR("SELECT mvalue FROM pproc,ppdattr WHERE pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid=31522830 AND pproc.procid="+procid);//master
 String delivMaster;
 if (rs.next()==true)
	 delivMaster=rs.getString("mvalue");
 else
	 delivMaster="Start";

 rs=conn.sqlQueryR("SELECT * FROM pdeliv,pdelivstatus WHERE pdelivstatus.procid=pdeliv.procidsrc AND pdelivstatus.caseid="+caseid+" AND pdelivstatus.transid="+transid+" AND pdelivstatus.delivid=pdeliv.delivid AND procidtrg="+procid);

 //deliv input
 ncnt=0;
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

	String dlink="javascript:showDeliv("+procid+","+caseid+","+transid+","+rs.getInt("delivid")+",-1,0,0);";

 	ncnt++;  	

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
<script language=JavaScript>
processRow(1,<%=ncnt%>);
</script>

</tbody></table></td></tr>
  <TR id=ROW2>
    <TD width="1%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%">
      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width="100%">
        <TBODY>
        <TR class=Bg>
          <TD align=middle width="1%" height=23><NOBR>&nbsp;</NOBR></TD>        
	<TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="82%"><NOBR><FONT class=menu>Tâches</FONT> (<a class=menu name=CNT2></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" class=BgL><NOBR><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/<%=userskin%>/desc.gif" width=7 border=0>
		<FONT class=swnub>Date</FONT>&nbsp;</NOBR></TD>
        </TR>
<%
 rs=conn.sqlQueryR("SELECT ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue FROM pproc,ppdattr WHERE pproc.procid="+procid+" AND pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid>=41943041 AND ppdattr.attribdefid<=41943421");

 //tasks
 ncnt=0;
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
	ncnt++;
	out.println("<TR>");
        out.println("<TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>");
	out.println("<TD width=\"3%\"><INPUT class=sbttn "+checked+" onclick='javascript:top.hide.document.location=\"settask.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&ATTRIBID="+rs.getString("attribdefid")+"&REDIRECT=detailcase.jsp%3FCASEID%3D"+caseid+"%26PROCID%3D"+procid+"%26TRANSID%3D"+transid+"\";' type=checkbox> </TD>");
	out.println("<TD width=\"82%\">"+rs.getString("mvalue")+"</TD>");
	out.println("<TD width=\"14%\">"+mdated+"</TD></TR>");
	}
 }
%>
</tbody></table></td></tr>
<script language=JavaScript>
processRow(2,<%=ncnt%>);
</script>

  <TR id=ROW3>
    <TD width="1%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%">
      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width="100%">
        <TBODY>
        <TR class=Bg>
          <TD align=middle width="1%"><NOBR>&nbsp;</NOBR></TD>
          	<TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="82%"><NOBR><FONT class=menu>Décisions</FONT> (<a class=menu name=CNT3></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" class=BgL><NOBR><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/<%=userskin%>/desc.gif" width=7 border=0>
		<FONT class=swnub>Date</FONT>&nbsp;</NOBR></TD>
        </TR>
<%
 rs=conn.sqlQueryR("SELECT ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue FROM pproc,ppdattr WHERE pproc.procid="+procid+" AND pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid>=43253761 AND ppdattr.attribdefid<=43254141");//decision

 //decisions
 ncnt=0;
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
	ncnt++;
	out.println("<TR>");
	out.println("<TD width=\"1%\">&nbsp;</TD>"); //getInt("attribdefid")
	out.println("<TD width=\"3%\"><INPUT class=sbttn "+checked+" onclick='javascript:top.hide.document.location=\"setdecision.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&ATTRIBID="+rs.getString("attribdefid")+"&REDIRECT=detailcase.jsp%3FCASEID%3D"+caseid+"%26PROCID%3D"+procid+"%26TRANSID%3D"+transid+"\";' type=checkbox> </TD>");
	out.println("<TD width=\"82%\">"+rs.getString("mvalue")+"</TD>");
	out.println("<TD width=\"14%\">"+mdated+"</TD></TR>");
	}
 }
%>   
</tbody></table></td></tr>
<script language=JavaScript>
processRow(3,<%=ncnt%>);
</script>

  <TR id=ROW4>
    <TD width="1%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%">
      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width="100%">
        <TBODY>
        <TR class=Bg>
          <TD align=middle width="1%" height=23><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="82%"><NOBR><FONT class=menu>Règles</FONT> (<a class=menu name=CNT4></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" class=BgL><NOBR><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/<%=userskin%>/desc.gif" width=7 border=0>
		<FONT class=swnub>Date</FONT>&nbsp;</NOBR></TD>
        </TR>
<%
 rs=conn.sqlQueryR("SELECT ppdattr.prow as prow,ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue FROM pproc,ppdattr WHERE pproc.procid="+procid+" AND pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid >= 68157441 AND ppdattr.attribdefid <= 68157821 ORDER BY ppdattr.pdattribid");//ref title,ref

 //regles
 ncnt=0;
 while (rs.next())
 {	
	String rule=rs.getString("mvalue");

	String checked="";
	String mdated="&nbsp;";

	rs2=conn2.sqlQueryR("SELECT * FROM prulesstatus WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid+" AND delivid=-1 AND refid="+rs.getInt("attribdefid"));
	if (rs2.next()==true)
	{
		if (rs2.getInt("mstate")==1)
			checked="checked";
		mdated=rs2.getString("mdated");
	}

	if (rule.length()>0)
	{
	ncnt++;
	out.println("<TR>");
        out.println("<TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>");
	out.println("<TD width=\"3%\"><INPUT class=sbttn "+checked+" onclick='javascript:top.hide.document.location=\"setrules.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&DELIVID=-1&REFID="+rs.getString("attribdefid")+"&REDIRECT=\"+escape(document.location);' type=checkbox> </TD>");
	out.println("<TD width=\"82%\">"+rule+"</TD>");
	out.println("<TD width=\"14%\">"+mdated+"</TD></TR>");
	}
 }
%>
</tbody></table></td></tr>
<script language=JavaScript>
processRow(4,<%=ncnt%>);
</script>


 <TR id=ROW5>
    <TD width="1%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%">
      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width="100%">
        <TBODY>
        <TR class=Bg>
          <TD align=middle width="1%" height=23><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="82%"><NOBR><FONT class=menu>Systèmes</FONT> (<a class=menu name=CNT5></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" class=BgL><NOBR><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/<%=userskin%>/desc.gif" width=7 border=0>
		<FONT class=swnub>Date</FONT>&nbsp;</NOBR></TD>
        </TR>
<%
 rs=conn.sqlQueryR("SELECT ppdattr.prow as prow,psystem.* FROM pproc,ppdattr,psystem WHERE pproc.procid="+procid+" AND pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid = 47185921 AND psystem.systemtitle=ppdattr.mvalue ORDER BY ppdattr.pdattribid");//ref title,ref

 //systems
 ncnt=0;
 while (rs.next())
 {	
	String systemid=rs.getString("systemid");
	String titreSys=rs.getString("systemtitle");
	String command=rs.getString("command");
	String parameters=rs.getString("parameters");
	String directory=rs.getString("directory");
	String priority=rs.getString("priority");
	String windowst=rs.getString("windowst");

	String checked="";
	String mdated="&nbsp;";

	rs2=conn2.sqlQueryR("SELECT * FROM psystemstatus WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid+" AND delivid=-1 AND refid="+rs.getInt("prow"));
	if (rs2.next()==true)
	{
		if (rs2.getInt("mstate")==1)
			checked="checked";
		mdated=rs2.getString("mdated");
	}

	if (command.length()>0)
	{
	ncnt++;
	out.println("<TR>");
        out.println("<TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>");
	out.println("<TD width=\"3%\"><INPUT class=sbttn "+checked+" onclick='javascript:document.location=\"setsystem.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&DELIVID=-1&REFID="+rs.getString("prow")+"&REDIRECT=\"+escape(document.location);' type=checkbox> </TD>");
	String url="\""+PsConv.c4JS(command)+" "+PsConv.c4JS(parameters)+"\"";
	out.println("<TD width=\"82%\"><a href='javascript:CTL.startUp("+url+");' >"+titreSys+"</a></TD>");
	out.println("<TD width=\"14%\">"+mdated+"</TD></TR>");
	}
 }
%>
</tbody></table></td></tr>
<script language=JavaScript>
processRow(5,<%=ncnt%>);
</script>


  <TR id=ROW6>
    <TD width="1%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%">
      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width="100%">
        <TBODY>
        <TR class=Bg>
          <TD align=middle width="1%" height=23><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="82%"><NOBR><FONT class=menu>Références</FONT> (<a class=menu name=CNT6></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" class=BgL><NOBR><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/<%=userskin%>/desc.gif" width=7 border=0>
		<FONT class=swnub>Date</FONT>&nbsp;</NOBR></TD>
        </TR>
<%
 rs=conn.sqlQueryR("SELECT ppdattr.prow as prow,ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue FROM pproc,ppdattr WHERE pproc.procid="+procid+" AND pproc.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid in (20971521,20971522) ORDER BY ppdattr.pdattribid");//ref title,ref

 //references
 ncnt=0;
 while (rs.next())
 {	
	if (rs.getInt("attribdefid")!=20971521)
		PsDebug.fail("detailcase.jsp: references order scrambled");
	String titreRef=rs.getString("mvalue");
	if (rs.next()==false)
		PsDebug.fail("detailcase.jsp: data link broken");
	if (rs.getInt("attribdefid")!=20971522)
		PsDebug.fail("detailcase.jsp: references order scrambled");
	String reference=rs.getString("mvalue");

	String checked="";
	String mdated="&nbsp;";

	rs2=conn2.sqlQueryR("SELECT * FROM preferencestatus WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid+" AND delivid=-1 AND refid="+rs.getInt("prow"));
	if (rs2.next()==true)
	{
		if (rs2.getInt("mstate")==1)
			checked="checked";
		mdated=rs2.getString("mdated");
	}

	if (reference.length()>0)
	{
	ncnt++;
	out.println("<TR>");
        out.println("<TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>");
	out.println("<TD width=\"3%\"><INPUT class=sbttn "+checked+" onclick='javascript:top.hide.document.location=\"setreference.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&DELIVID=-1&REFID="+rs.getString("prow")+"&REDIRECT=\"+escape(document.location);' type=checkbox> </TD>");

	//String baseDir=PsConfig.get("TEMPLATE_DIR"); if (baseDir.substring(baseDir.trim().length()-1).equals(File.separator)) baseDir=baseDir.trim().substring(0,baseDir.trim().length()-1);
	String ext=reference.substring(reference.trim().length()-3).trim();
	String doc=reference.trim();
	String url="";
	String prg="explorer";	
	if (ext.equalsIgnoreCase("plf")==true)
	{
		prg=PsConfig.get("SCRIPTOR_LAUNCHER");

		url=PsConv.c4JS(prg)+" -caseid "+caseid+" -transid \\\""+transid+titreRef+"\\\" -sessionid 0000 -template \\\""+PsConv.c4JS(titreRef)+"\\\"";
	}
	else
	{
		url=PsConv.c4JS(prg)+" "+PsConv.c4JS(doc);
	}
	out.println("<TD width=\"82%\"><a href='javascript:CTL.startUp(\""+url+"\");' >"+titreRef+"</a></TD>");
	out.println("<TD width=\"14%\">"+mdated+"</TD></TR>");
	}
 }
%>
</tbody></table></td></tr>
<script language=JavaScript>
processRow(6,<%=ncnt%>);
</script>

<TR id=ROW7>
    <TD width="1%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%">
      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width="100%">
        <TBODY>
        <TR class=Bg>
          <TD align=middle width="1%" height=23><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="36%"><NOBR><FONT class=menu>Fichier(s) joints</FONT> (<a class=menu name=CNT7></a>)</NOBR></TD>
	  <TD width="46%"><NOBR><FONT class=menu>Utilisateur</FONT></NOBR></TD>
          <TD width="14%" class=BgL><NOBR><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/<%=userskin%>/desc.gif" width=7 border=0>
		<FONT class=sbbd>Date</FONT>&nbsp;</NOBR></TD>
        </TR>
<%

 rs=conn.sqlQueryR("SELECT * FROM pattach WHERE caseid="+caseid+" AND transid="+transid);
 int ntotal=0;
 //attach
 ncnt=0;
 while (rs.next())
 {	
	String filename=rs.getString("filename");
	String mlogin=rs.getString("mlogin");
	String mdated=rs.getString("filedate");

	ncnt++;ntotal++;
	out.println("<TR>");
        out.println("<TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>");
	out.println("<TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/arr.gif\"></TD>");
	out.println("<TD width=\"36%\">");
	out.println("<a href=\"docs/"+filename+"\">");
	out.println(filename);
	out.println("</a>");
	out.println("</TD>");
	out.println("<TD width=\"46%\">");
	out.println(mlogin);
	out.println("</TD>");
	out.println("<TD width=\"14%\">"+mdated+"</TD></TR>");

 }
%>
</tbody></table></td></tr>
<script language=JavaScript>
processRow(7,<%=ncnt%>);
</script>



  <TR id=ROW8>
    <TD width="1%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%">
      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width="100%">
        <TBODY>
        <TR class=Bg>
          <TD align=middle width="1%" height=23><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="82%"><NOBR><FONT class=menu>Saisie d'attributs</FONT> (<a class=menu name=CNT8></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" class=BgL><NOBR><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/<%=userskin%>/desc.gif" width=7 border=0>
		<FONT class=swnub>Date</FONT>&nbsp;</NOBR></TD>
        </TR>
<%

 rs=conn.sqlQueryR("SELECT distinct pattribdef.attribdefname as attribdefname,pinput.modelid as modelid,pattribdef.attribdeftype,ppdattr.prow as prow,ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue,pinput.pdattribid as pdattribid,pinput.mdefval as mdefval,pinput.mflag as mflag,pinput.constraintid as constraintid,pattribdef.attribdeftype as attribdeftype FROM pinput,ppdattr,pattribdef WHERE ppdattr.pdattribid="+procid+" AND pinput.attribdefid=ppdattr.attribdefid AND pinput.pdattribid=ppdattr.pdattribid AND pattribdef.attribdefid=pinput.attribdefid AND ppdattr.attribdefid=pattribdef.attribdefid  ORDER BY ppdattr.pdattribid");
 //input
 int cnt=1;
 ncnt=0;
 while (rs.next())
 {	
	String att=rs.getString("mvalue");
	String dval=rs.getString("mdefval");
	String mdated="&nbsp;";

	//get value already edited if any
	rs2=conn2.sqlQueryR("SELECT mval,mdate FROM pinputdata WHERE modelid="+rs.getInt("modelid")+" AND pdattribid="+rs.getInt("pdattribid")+" AND attribdefid="+rs.getInt("attribdefid")+" AND caseid="+caseid+" AND transid="+transid+" ORDER BY mdate desc");
	if (rs2.next()==true)
	{
		dval=rs2.getString("mval");
		mdated=rs2.getString("mdate");
	}
	ncnt++;
	out.println("<TR>");
        out.println("<TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>");
	out.println("<TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/arr.gif\"></TD>");
	out.println("<TD width=\"80%\">");
	out.println("<TABLE class=no cellSpacing=0 cellPadding=0  width=\"100%\"><TR><TD width=150>");
	out.println(rs.getString("attribdefname"));
	out.println("</TD><TD>");
	out.println("<input type=hidden name=CTL2_"+cnt+" value="+rs.getString("attribdefid")+">");
	out.println("<script language=JavaScript>");
	out.println("new Adyn("+ (cnt++) +",\""+att+"\",\""+dval+"\","+rs.getString("attribdeftype")+").show();");
	out.println("</script>");
	out.println("</TD></TR></TABLE>");
	out.println("</TD>");
	out.println("<TD width=\"14%\">"+mdated+"</TD></TR>");

 }
 out.print("<input type=hidden name=NBR_INPUT value="+(cnt-1)+">");
%>

</TR></TBODY></TABLE>
<script language=JavaScript>
processRow(8,<%=ncnt%>);
</script>

<%
	int delivTotalNbr=0;
	int delivLatMandatory=0;
	int delivLatInProgress=0;
	int delivLatReturned=0;
	int delivNextStarted=0;
	int delivNextMandatory=0;
%>

  <TR id=ROW9>
    <TD width="1%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%">
      <TABLE class=Mtable id=LateralDelivTable cellSpacing=0 cellPadding=0
      width="100%"> 
        <TBODY>
        <TR class=Bg>
          <TD align=middle width="1%"><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="36%"><NOBR><A title="Trier par expéditeur" 
            href=""><FONT class=menu>Livrables latéraux</FONT></A> (<a class=menu name=CNT9></a>)</NOBR><NOBR></NOBR></TD>
          <TD width="46%"><NOBR><A title="Trier par livrable" 
            href=""><FONT 
            class=menu>Procédure</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" class=BgL><NOBR><A title="Trier par date" 
            href=""><IMG 
            height=7 alt="trié par ordre décroissant" hspace=3 
            src="img/<%=userskin%>/desc.gif" width=7 border=0><FONT 
            class=swnub>Date</FONT></A>&nbsp;</NOBR></TD>
	</TR>

<%
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
 ncnt=0;
 while (rs.next())
 {
	int proctrg=rs.getInt("procidtrg");

	if (rs.getString("delivname").length()>0)
	{
	String dlink="javascript:showDeliv("+procid+","+caseid+","+transid+","+rs.getInt("delivid")+",1,0,0);";
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

	ncnt++;
	delivTotalNbr++;

	if (ks.next()==true)
	{
		if (ks.getInt("openclose")==0)
		{
			delivLatInProgress++;

			dlink="javascript:showDeliv("+procid+","+caseid+","+transid+","+rs.getInt("delivid")+",-1,0,0);";
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
			delivLatReturned++;

			dlink="javascript:showDeliv("+procid+","+caseid+","+transid+","+rs.getInt("delivid")+",-1,0,0);";
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
		delivLatMandatory++;

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
	int nbrr=PsWf.delivNbrReferences(rs.getInt("delivid"));if (nbrr>0) out.println("<img src=img/reference.gif alt=\"Informations\"> ");
	int nbri=PsWf.delivNbrInformations(rs.getInt("delivid"));if (nbri>0) out.println("<img src=img/info.gif alt=\"References\"> ");
	out.println("</TD>");

        out.println("<TD width=\"46%\">");

	conn2=PsDbMgr.newConnection();
	rs2=conn2.sqlQueryR("SELECT * FROM pproc,ppdattr WHERE pproc.procid="+proctrg+" and pproc.pdattribid=ppdattr.pdattribid and ppdattr.attribdefid=1310721");
	if (rs2.next()==true)
	{
		PsDebug.log("Deliv name not found: procid="+proctrg);
		out.println(rs2.getString("mvalue"));	
	}
	out.println("</TD>");
        out.println("<TD width=\"14%\">"+mdated+"</TD>");
	out.println("</TR>");
	}
 }
%>
  </TBODY></TABLE></TD></TR>
<script language=JavaScript>
processRow(9,<%=ncnt%>);
</script>

  <TR id=ROW10>
    <TD width="1%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%">
      <TABLE class=Mtable id=FollowingDelivTable cellSpacing=0 cellPadding=0 
      width="100%">
        <TBODY>
        <TR class=Bg>
          <TD align=middle width="1%"><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="36%"><NOBR><A title="Trier par expéditeur" 
            href=""><FONT class=menu>Livrables 
            suivants</FONT></A> (<a class=menu name=CNT10></a>)</NOBR><NOBR></NOBR><NOBR></NOBR><NOBR></NOBR></TD>
          <TD width="46%"><NOBR><A title="Trier par livrable" 
            href=""><FONT 
            class=menu>Procédure</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" class=BgL><NOBR><A title="Trier par date" 
            href=""><IMG 
            height=7 alt="trié par ordre décroissant" hspace=3 
            src="img/<%=userskin%>/desc.gif" width=7 border=0><FONT 
            class=swnub>Date</FONT></A>&nbsp;</NOBR></TD>
	</TR>
<%
 rs=conn.sqlQueryR("SELECT * FROM pdeliv WHERE procidsrc="+procid+" AND lateral=0");

 //deliv
 ncnt=0;
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

			delivNextStarted++;
		}
else
		mdated=rs2.getString("mdated");
	}


	double pct=PsWf.percentageDeliv(rs.getInt("delivid"));

	//set validator
	if (pct>=99.999) 
	{
		delivNextMandatory++;
		out.println("<script language=JavaScript>");
		out.println("DelivValidator.set(\""+rs.getString("delivname")+"\","+delivcompleted+");");
		out.println("</script>");
	}

	String dlink="javascript:showDeliv("+procid+","+caseid+","+transid+","+rs.getInt("delivid")+",0,"+delivLatInProgress+","+delivLatMandatory+");";

	ncnt++;
	delivTotalNbr++;

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
	int nbrr=PsWf.delivNbrReferences(rs.getInt("delivid"));if (nbrr>0) out.println("<img src=img/reference.gif alt=\"Informations\"> ");
	int nbri=PsWf.delivNbrInformations(rs.getInt("delivid"));if (nbri>0) out.println("<img src=img/info.gif alt=\"References\"> ");
	out.println("</TD>");
        out.println("<TD width=\"46%\">");

	conn2=PsDbMgr.newConnection();
	rs2=conn2.sqlQueryR("SELECT * FROM pproc,ppdattr WHERE pproc.procid="+proctrg+" and pproc.pdattribid=ppdattr.pdattribid and ppdattr.attribdefid=1310721;");
	if (rs2.next()==true)
		out.println(rs2.getString("mvalue"));
	out.println("</TD>");
        out.println("<TD width=\"14%\">"+mdated+"</TD>");
	out.println("</TR>");
	}
 }
%>
</TBODY></TABLE></TD>
<script language=JavaScript>
processRow(10,<%=ncnt%>);
</script>

<TABLE width="100%" border=0>
  <TBODY>
  <TR>
    <TD width="1%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%">
	<input type=button class=sbttn value="Joindre un document" onclick='javascript:doUpload(<%=caseid%>,<%=transid%>);'>&nbsp;
	<input type=button class=sbttn value="Mise en attente" onclick='javascript:doChangeStatus(1,<%=procid%>,<%=caseid%>,<%=transid%>,2);'>&nbsp;
	<input type=button class=sbttn value="Retour pour non conformité" onclick='javascript:retSender(<%=procid%>,<%=caseid%>,<%=transid%>);'>&nbsp;
	<input type=button class=sbttn value="Remise au chef" onclick='javascript:sendChief(<%=procid%>,<%=caseid%>,<%=transid%>);'>&nbsp;
	<input type=button class=sbttn value="Capsule de travail" onclick='javascript:capsuleTravail(<%=procid%>,<%=caseid%>,<%=transid%>);'>&nbsp;
<% 
 rs=conn.sqlQueryR("SELECT * FROM pproc WHERE procid="+procid);
 rs.next();
 signaturemode=rs.getInt("doublesign");
 if (signaturemode==0)
	out.println("	<input class=sbttn type=button value=\"Terminé\" style=\"width:200px;\" onclick='javascript:terminate(\"termin.jsp?REDIRECT=\"+escape(\"listcase.jsp?MODE=0\")+\"&PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"\","+delivLatMandatory+","+delivLatInProgress+","+delivLatReturned+","+delivNextStarted+","+delivNextMandatory+","+delivTotalNbr+");'>");
 if (signaturemode>0)
	out.println("	<input class=sbttn type=button value=\"Signature\" onclick='javascript:signature(\"sign.jsp?REDIRECT=\"+escape(\"listcase.jsp?MODE=0\")+\"&PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"\","+delivLatMandatory+","+delivLatInProgress+","+delivLatReturned+","+delivNextStarted+","+delivNextMandatory+","+delivTotalNbr+");'>");
%>
	</td>
    </tr>
  </tbody>
</table>
</BODY></HTML>
