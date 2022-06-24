<html>
<%@ page import="java.util.*,java.lang.*,java.sql.*,PsApp,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsConv,PsWorkGroup" %>
<%@ page session="true" %>
<head>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<%
 String userskin="skin"+(String)session.getAttribute("USERSKIN");
%>
<link href="css/<%=userskin%>/global.css" rel="styleSheet" type="text/css">
<script language=JavaScript src="js/pss.js"></script>
<script language=JavaScript>
var jcaseid=-1;
var jtransid=-1;
function doSetCb(frm,mcaseid,mtransid,mcasename,mtransname)
{
	jcaseid=mcaseid;
	jtransid=mtransid;
	frm.casename.value=mcasename;
	//frm.transname.value=mtransname;
}

function doSel(no)
{
	document.all["Z1"].style.visibility = "hidden";
	document.all["Z2"].style.visibility = "hidden";
	document.all["Z3"].style.visibility = "hidden";
	if (no==1) 	document.all["Z1"].style.visibility = "visible";		
	if (no==2) 	document.all["Z2"].style.visibility = "visible";		
	if (no==3) 	document.all["Z3"].style.visibility = "visible";				
}
</script>
</head>
<BODY>
<TABLE class=msglistcntrl width="100%" cellSpacing=2 cellPadding=0 border=0 >
  <TR>
    <TD width="11%">&nbsp;</TD>
    <td width="8%"></tb>
    <TD width="81%"class=NormalBlack vAlign=top width="89%">
  </TR>
 
  <TR>
    <TD width="11%">&nbsp;</TD>
    <td width="8%">Action :</tb>
    <TD width="81%"class=NormalBlack vAlign=top width="89%"><input type=radio class=sbttn NAME=ACTION value="1" onclick="doSel(1);"> Nouveau cas
  </TR>
  <TR>
    <TD width="11%">&nbsp;</TD>
    <td width="8%"></tb>
    <TD width="81%"class=NormalBlack vAlign=top width="89%"><input type=radio class=sbttn NAME=ACTION value="2" onclick="doSel(2);"> Attacher   un cas existant
  </TR>
  
  <TR>
    <TD width="11%">&nbsp;</TD>
    <td width="8%"></tb>
    <TD width="81%"class=NormalBlack vAlign=top width="89%"><input type=radio class=sbttn NAME=ACTION value="3" onclick="doSel(3);"> Nouveau sous-cas
  </TR>
 </table>
 <br>
  <DIV ID=Z1 style="visibility:hidden;position:absolute;">
  <form name="F1">
  <TABLE class=msglistcntrl width="100%" cellSpacing=2 cellPadding=0 border=0>
  <tr>
  <td width="11%">&nbsp;</td>
  <td width="8%">Cas :</td>
  <td width="81%"><INPUT maxLength=80 size=80 name=casename></td>
  </tr>
  <tr>
  <td width="11%">&nbsp;</td>
  <td width="8%">Description :</td>
  <td width="81%"><INPUT maxLength=80 size=80 name=transname></td>
  </tr>
  <tr>
  <td colspan=3 height=20>&nbsp;</td>
  </tr>
  <tr>
  <td width="11%">&nbsp;</td>
  <td width="8%">&nbsp;</td>
  <td width="81%"><INPUT class=sbttn title="Créer un nouveau." onclick="doSubmit(-1,-1,casename.value,transname.value);" tabIndex=2 type=button value="Démarrer" name=create style="width:200px;"></td>
  </tr>
  </table>
  </form>
  </div>
  
  <DIV ID=Z2 style="visibility:hidden;position:absolute;">
  <form name="F2">
  <TABLE class=msglistcntrl width="100%" cellSpacing=2 cellPadding=0 border=0>
  <tr valign=top>
  <td width="11%">&nbsp;</td>
  <td width="8%">Choisir un cas :</td>
  <td width="81%">
  
  <TABLE class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 width="100%">
	  <TBODY>
        <TR class=Bg>
          <TD width="6%" height=23>&nbsp; </TD>
          <TD width="32%"><NOBR><FONT class=swb>Cas existants</FONT></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="59%"><NOBR><FONT class=swb>Processus</FONT></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
		</TR>
  <%
 PsApp.init();

 String username=(String)session.getAttribute("USERNAME");

try {
	PsDbConn conn=PsDbMgr.newConnection();
	ResultSet rs;

	rs=conn.sqlQueryR("SELECT count(*) as cnt,casename,transname ,ptrans.caseid,mvalue,ptrans.transid FROM pcase,ptrans,pproctrans,pproc,ppdattr WHERE ptrans.caseid=pproctrans.caseid AND ptrans.transid=pproctrans.transid AND ppdattr.pdattribid=pproc.pdattribid AND ppdattr.attribdefid=1310721 AND pproc.procid=pproctrans.procid AND pcase.caseid=pproctrans.caseid AND pproctrans.statusid in (0,1,2) GROUP BY casename,transname ORDER BY pcase.casename");

	int cbcnt=0;
	while (rs.next())
	{
%>
	<TR>
        <TD width="6%" align=left><INPUT class=sbttn  onclick='doSetCb(document.F2,<%=rs.getInt("caseid")%>,<%=rs.getInt("transid")%>,"<%=PsConv.c4JS(rs.getString("casename"))%>","<%=PsConv.c4JS(rs.getString("transname"))%>");' type=radio name=CB<%=(cbcnt++)%> >
        </TD>
        <TD width="32%"><%=rs.getString("casename")%>, <%=rs.getString("transname")%></TD>
<%		
        if (rs.getInt("cnt")==1) 
		{
%>		
	    <TD width="59%"><%=rs.getString("mvalue")%></TD></TR>
<%		}			
	else
		{
%>	
	    <TD width=\"59%\">...</TD></TR>
<%
		}
			
	}
    }
catch (SQLException e)
    {
	PsDebug.fail("newcase1.jsp: SQLException: "+e.getMessage());
    }
%>
</TABLE>
  </td>
  </tr>
  
  <tr>  <td colspan=3 height=20>&nbsp;</td>  </tr>
  
  <tr>
  <td width="11%">&nbsp;</td>
  <td width="8%">Description :</td>
  <td width="81%"><input type=hidden name=casename><INPUT maxLength=80 size=80 name=transname></td>
  </tr>
  
  <tr>  <td colspan=3 height=20>&nbsp;</td>  </tr>
  
  <tr>
  <td width="11%">&nbsp;</td>
  <td width="8%">&nbsp;</td>
  <td width="81%"><INPUT class=sbttn title="Créer un nouveau sous-cas à partir du cas selectionné." onclick="doSubmit(jcaseid,jtransid,casename.value,transname.value);" tabIndex=2 type=button value="Démarrer" name=createex style="width:200px;"></td>
  </tr>
  </table>
  </form>
  </div>
  
  <DIV ID=Z3 style="visibility:hidden;position:absolute;">
  <form name="F3">  
  <TABLE class=msglistcntrl width="100%" cellSpacing=2 cellPadding=0 border=0>
  <tr valign=top>
  <td width="11%">&nbsp;</td>
  <td width="8%">Choisir un cas :</td>
  <td width="81%">
  
  <TABLE class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 width="100%">
	  <TBODY>
        <TR class=Bg>
          <TD width="6%" height=23>&nbsp; </TD>
          <TD width="32%"><NOBR><FONT class=swb>Cas existants</FONT></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
          <TD width="59%"><NOBR><FONT class=swb>Processus</FONT></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>
		</TR>
  <%

try {
	PsDbConn conn=PsDbMgr.newConnection();
	ResultSet rs;

	rs=conn.sqlQueryR("SELECT count(*) as cnt,casename,transname ,ptrans.caseid,mvalue,ptrans.transid FROM pcase,ptrans,pproctrans,pproc,ppdattr WHERE ptrans.caseid=pproctrans.caseid AND ptrans.transid=pproctrans.transid AND ppdattr.pdattribid=pproc.pdattribid AND ppdattr.attribdefid=1310721 AND pproc.procid=pproctrans.procid AND pcase.caseid=pproctrans.caseid AND pproctrans.statusid in (0,1,2) GROUP BY casename,transname ORDER BY pcase.casename");

	int cbcnt=0;
	while (rs.next())
	{
%>
	<TR>
        <TD width="6%" align=left><INPUT class=sbttn  onclick='doSetCb(document.F3,<%=rs.getInt("caseid")%>,<%=rs.getInt("transid")%>,"<%=PsConv.c4JS(rs.getString("casename"))%>","<%=PsConv.c4JS(rs.getString("transname"))%>");' type=radio name=CB<%=(cbcnt++)%> >
        </TD>
        <TD width="32%"><%=rs.getString("casename")%>, <%=rs.getString("transname")%></TD>
<%		
        if (rs.getInt("cnt")==1) 
		{
%>		
	    <TD width="59%"><%=rs.getString("mvalue")%></TD></TR>
<%		}			
	else
		{
%>	
	    <TD width=\"59%\">...</TD></TR>
<%
		}
			
	}
    }
catch (SQLException e)
    {
	PsDebug.fail("newcase1.jsp: SQLException: "+e.getMessage());
    }
%>
</TABLE>
  </td>
  </tr>
  
  <tr>  <td colspan=3 height=20>&nbsp;</td>  </tr>
  
  <tr>
  <td width="11%">&nbsp;</td>
  <td width="8%">Description :</td>
  <td width="81%"><input type=hidden name=casename><INPUT maxLength=80 size=80 name=transname></td>
  </tr>
  
  <tr>  <td colspan=3 height=20>&nbsp;</td>  </tr>
  
  <tr>
  <td width="11%">&nbsp;</td>
  <td width="8%">&nbsp;</td>
  <td width="81%"><INPUT class=sbttn title="Créer un nouveau sous-cas à partir du cas selectionné." onclick="doSubmit(jcaseid,-1,casename.value,transname.value);" tabIndex=2 type=button value="Démarrer" name=createsc style="width:200px;"></td>
  </tr>
  </table>
  </form>
  </div>
     
<SCRIPT language=javascript>
function doSubmit(caseattachid,transattachid,casename,transname) {
	var fromproc=-1; //no previous procedure
	var transid;

	if (transattachid<0)
		transid=<%=PsDbMgr.newConnection().nextVal("PTRANS")%>;
	else
		transid=transattachid;
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