<HTML>
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsConv" %>

<HEAD><TITLE>Detailed Case</TITLE>
<jsp:include page="checksession.jsp" flush="false" />
<%@ page session="true" %>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">
<SCRIPT language=JavaScript src="js/pssdyn.js"></SCRIPT>

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

	var n=NBR_INPUT.value;

	var st="&NBR_INPUT="+n;
	for (i=1;i<=n;i++)
	{
		st=st+"&CTL_"+i+"="+escape(document.getElementById("CTL_"+i).value);
		st=st+"&CTL2_"+i+"="+escape(document.getElementById("CTL2_"+i).value);
	}
	//TODO: faire un POST
document.location="deliv.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&DELIVID="+delivid+"&LATERAL="+lateral+"&REDIRECT="+url+st;
}

function doUpload(caseid,transid)
{
	var dialogWindow = window.open("upload.jsp?MODE=0&CASEID="+caseid+"&TRANSID="+transid,"","height=200,width=300,modal=yes");
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
<applet name=CTL code=AppLauncher.class archive=AppLauncher.jar width=1 height=1></applet>
<TABLE width="100%" border=0>
  <TBODY>
  <TR id=ROW1>
    <TD width="1%" >&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%">
      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width="100%">
        <TBODY>
        <TR class=Bg>
          <TD align=middle width="1%" height=23><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="96%"><NOBR><FONT class=menu>Informations</FONT> (<a class=menu name=CNT1></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>
        </TR>
<%
 PsApp.init();

 int ncnt=0;
 int ntotal=0;

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

 String delivname="";
 String casename="";
 String transname="";

 rs=conn.sqlQueryR("SELECT delivname FROM pdeliv WHERE delivid="+delivid);
 if (rs.next()==true)
	delivname=rs.getString("delivname");

 rs=conn.sqlQueryR("SELECT casename,transname FROM pcase,ptrans WHERE pcase.caseid=ptrans.caseid AND pcase.caseid="+caseid+" AND ptrans.transid="+transid);
 if (rs.next()==true)
 {
	casename=rs.getString("casename");
	transname=rs.getString("transname");
 }

 rs=conn.sqlQueryR("SELECT * FROM pdeliv,ppdattr WHERE pdeliv.delivid="+delivid+" AND pdeliv.pdattribid=ppdattr.pdattribid AND attribdefid>=44564481 AND attribdefid<=44564861");

 //deliv input
 ncnt=0;
 while (rs.next())
 {	
	if (rs.getString("mvalue").length()>0)
	{
		ncnt++;ntotal++;
		out.println("<TR>");
	        out.println("<TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>");
		String checked="";
		rs2=conn2.sqlQueryR("SELECT * FROM pinfostatus WHERE caseid="+caseid+" AND transid="+transid+" AND delivid="+delivid+" AND infoid="+rs.getInt("attribdefid"));
		if (rs2.next()==true)
			if (rs2.getInt("mstate")==1)
				checked="checked";

 	        out.println("<TD width=\"3%\"><INPUT class=sbttn "+checked+" onclick='javascript:top.hide.document.location=\"setinfo.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&DELIVID="+delivid+"&REDIR=\"+escape(document.location)+\"&INFOID="+rs.getString("attribdefid")+"\";' type=checkbox> </TD>");
		out.println("<TD width=\"96%\">"+rs.getString("mvalue")+"</TD></TR>");
	}
 }
%>

<script language=JavaScript>
// ----------------------------------------------------------------
//Display tab on top.jsp
var info1="Utilisateur:</td><td colspan=2 nobr><NOBR><b><%=(String)session.getAttribute("USERNAME")%></b>, <%=(String)session.getAttribute("USERROLETXT")%> (<%=(String)session.getAttribute("USERWORKGROUPTXT")%>)</NOBR>";
var info2="Cas:</td><td><b><%=casename%>, <%=transname%></b></td><td align=right><FONT class=menu>Livrable:</font> <b><%=delivname%></b>";
top.showText(info1,info2);
// ----------------------------------------------------------------
</script>

</tbody></table></td></tr>
<script language=JavaScript>
processRow(1,<%=ncnt%>);
</script>

 <TR id=ROW2>
    <TD width="1%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%">
      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width="100%">
        <TBODY>
        <TR class=Bg>
          <TD align=middle width="1%" height=23><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="82%"><NOBR><FONT class=menu>Règles</FONT> (<a class=menu name=CNT2></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" class=BgL><NOBR><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/<%=userskin%>/desc.gif" width=7 border=0>
		<FONT class=sbbd>Date</FONT>&nbsp;</NOBR></TD>
        </TR>
<%
 rs=conn.sqlQueryR("SELECT ppdattr.prow as prow,ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue FROM pdeliv,ppdattr WHERE pdeliv.delivid="+delivid+" AND pdeliv.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid >= 68157441 AND ppdattr.attribdefid <= 68157821 ORDER BY ppdattr.pdattribid");//ref title,ref

 //regles
 ncnt=0;
 while (rs.next())
 {	
	String rule=rs.getString("mvalue");

	String checked="";
	String mdated="&nbsp;";

	rs2=conn2.sqlQueryR("SELECT * FROM prulesstatus WHERE delivid="+delivid+" AND caseid="+caseid+" AND transid="+transid+" AND delivid="+delivid+" AND refid="+rs.getInt("attribdefid"));
	if (rs2.next()==true)
	{
		if (rs2.getInt("mstate")==1)
			checked="checked";
		mdated=rs2.getString("mdated");
	}

	if (rule.length()>0)
	{
	ncnt++;ntotal++;
	out.println("<TR>");
        out.println("<TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>");
	out.println("<TD width=\"3%\"><INPUT class=sbttn "+checked+" onclick='javascript:top.hide.document.location=\"setrules.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&DELIVID="+delivid+"&REFID="+rs.getString("attribdefid")+"&REDIRECT=\"+escape(document.location);' type=checkbox> </TD>");
	out.println("<TD width=\"82%\">"+rule+"</TD>");
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
          <TD align=middle width="1%" height=23><NOBR>&nbsp;</NOBR></TD>
          <TD width="3%" height=23 valign=bottom>&nbsp;<img src="img/<%=userskin%>/ard.gif"></TD>
          <TD width="82%"><NOBR><FONT class=menu>Références</FONT> (<a class=menu name=CNT3></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" class=BgL><NOBR><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/<%=userskin%>/desc.gif" width=7 border=0>
		<FONT class=sbbd>Date</FONT>&nbsp;</NOBR></TD>
        </TR>
<%
 rs=conn.sqlQueryR("SELECT ppdattr.prow as prow,ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue FROM pdeliv,ppdattr WHERE pdeliv.delivid="+delivid+" AND pdeliv.pdattribid=ppdattr.pdattribid AND ppdattr.attribdefid in (20971521,20971522) ORDER BY ppdattr.pdattribid");

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

	rs2=conn2.sqlQueryR("SELECT * FROM preferencestatus WHERE caseid="+caseid+" AND transid="+transid+" AND refid="+rs.getInt("prow")+" AND delivid="+delivid);

	if (rs2.next()==true)
	{
		if (rs2.getInt("mstate")==1)
			checked="checked";
		mdated=rs2.getString("mdated");
	}

	if (reference.length()>0)
	{
	ncnt++;ntotal++;
	out.println("<TR>");
        out.println("<TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>");
	out.println("<TD width=\"3%\"><INPUT class=sbttn "+checked+" onclick='javascript:top.hide.document.location=\"setreference.jsp?PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"&DELIVID="+delivid+"&REFID="+rs.getString("prow")+"&REDIRECT=\"+escape(document.location);' type=checkbox> </TD>");

	//String baseDir=PsConfig.get("TEMPLATE_DIR"); if (baseDir.substring(baseDir.trim().length()-1).equals(File.separator)) baseDir=baseDir.trim().substring(0,baseDir.trim().length()-1);
	String ext=reference.substring(reference.trim().length()-3).trim();
	String doc=reference.trim();

	String prg="explorer";	
	if (ext.equalsIgnoreCase("plf")==true)
		prg=PsConfig.get("SCRIPTOR_LAUNCHER");


	String url=PsConv.c4JS(prg)+" "+PsConv.c4JS(doc);

	out.println("<TD width=\"82%\"><a href='javascript:CTL.startUp(\""+url+"\");' >"+titreRef+"</a></TD>");
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
          <TD width="41%"><NOBR><FONT class=menu>Fichier(s) joints</FONT> (<a class=menu name=CNT4></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>
	  <TD width="41%"><NOBR><FONT class=menu>Utilisateur</FONT>&nbsp;</NOBR></TD>
          <TD width="14%" class=BgL><NOBR><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/<%=userskin%>/desc.gif" width=7 border=0>
		<FONT class=sbbd>Date</FONT>&nbsp;</NOBR></TD>
        </TR>
<%

 rs=conn.sqlQueryR("SELECT * FROM pattach WHERE caseid="+caseid+" AND transid="+transid);
 //input
 while (rs.next())
 {	
	String filename=rs.getString("filename");
	String mlogin=rs.getString("mlogin");
	String mdated=rs.getString("filedate");

	ncnt++;ntotal++;
	out.println("<TR>");
        out.println("<TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>");
	out.println("<TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/arr.gif\"></TD>");
	out.println("<TD width=\"40%\">");
	out.println("<a href=\"docs/"+filename+"\">");
	out.println(filename);
	out.println("</a>");
	out.println("</TD>");
	out.println("<TD width=\"40%\">");
	out.println(mlogin);
	out.println("</TD>");
	out.println("<TD width=\"14%\">"+mdated+"</TD></TR>");

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
          <TD width="82%"><NOBR><FONT class=menu>Saisie d'attributs</FONT> (<a class=menu name=CNT5></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="14%" class=BgL><NOBR><IMG height=7 alt="trié par ordre décroissant" hspace=3 src="img/<%=userskin%>/desc.gif" width=7 border=0>
		<FONT class=sbbd>Date</FONT>&nbsp;</NOBR></TD>
        </TR>
<%

 rs=conn.sqlQueryR("SELECT distinct pattribdef.attribdefname as attribdefname,pinput.modelid as modelid,pattribdef.attribdeftype,ppdattr.prow as prow,ppdattr.attribdefid as attribdefid,ppdattr.mvalue as mvalue,pinput.pdattribid as pdattribid,pinput.mdefval as mdefval,pinput.mflag as mflag,pinput.constraintid as constraintid,pattribdef.attribdeftype as attribdeftype FROM pinput,ppdattr,pattribdef WHERE ppdattr.pdattribid="+delivid+" AND pinput.attribdefid=ppdattr.attribdefid AND pinput.pdattribid=ppdattr.pdattribid AND pattribdef.attribdefid=pinput.attribdefid AND ppdattr.attribdefid=pattribdef.attribdefid  ORDER BY ppdattr.pdattribid");
 //input
 int cnt=1;
 ncnt=0;
 while (rs.next())
 {	
System.out.println("**************");
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

	ncnt++;ntotal++;
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
</tbody></table></td></tr>
<script language=JavaScript>
processRow(5,<%=ncnt%>);
</script>



</TBODY></TABLE>

<script language=JavaScript>
//display text if nothing is visible
var ntotal=<%=ntotal%>;
if (ntotal==0)
{
	document.writeln("<TABLE width=\"100%\" border=0><TBODY><TR><TD width=\"1%\" >&nbsp;</TD><TD class=NormalBlack vAlign=top width=\"99%\">");
	document.writeln("<TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\"><TBODY><TR>");
	document.writeln("Aucun traitements ou informations.<br>");
	document.writeln("Veuillez clicker sur 'Envoyer' pour valider et continuer.");
	document.writeln("<TD></TD></TR></TABLE></TD></TR></TABLE>");
}
</script>

<TABLE width="100%" border=0>
  <TBODY>
  <TR>
    <TD width="1%">&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="99%">
	<input type=button class=sbttn value="Joindre un document" onclick='javascript:doUpload(<%=caseid%>,<%=transid%>);'>&nbsp;
<!--
	<input type=button class=sbttn value="Retour pour non conformité" onclick='javascript:retSender(<%=procid%>,<%=caseid%>,<%=transid%>);'>&nbsp;
	<input type=button class=sbttn value="Remise au chef" onclick='javascript:sendChief(<%=procid%>,<%=caseid%>,<%=transid%>);'>&nbsp;
-->
        <input type=button class=sbttn value="Revenir à la procédure" onclick='javascript:document.location="<%=(String)request.getParameter( "REDIRECT" )%>"'>&nbsp;
<%if (Integer.valueOf(request.getParameter( "LATERAL" )).intValue()>=0) {%>
	<input type=button class=sbttn value="Envoyer" style="width:200px;"  onclick='javascript:doStartDeliv(<%=(String)request.getParameter( "PROCID" )%>,<%=(String)request.getParameter( "CASEID" )%>,<%=(String)request.getParameter( "TRANSID" )%>,<%=(String)request.getParameter( "DELIVID" )%>,<%=(String)request.getParameter( "LATERAL" )%>);'>
<%}%>
	</td>
    </tr>
  </tbody>
</table>
</BODY>
</HTML>
