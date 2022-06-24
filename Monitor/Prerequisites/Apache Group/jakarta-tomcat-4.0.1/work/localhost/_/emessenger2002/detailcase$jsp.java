package org.apache.jsp;

import java.util.*;
import java.lang.*;
import java.sql.*;
import PsApp;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsConfig;
import PsWorkGroup;
import PsWf;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class detailcase$jsp extends HttpJspBase {


    static {
    }
    public detailcase$jsp( ) {
    }

    private static boolean _jspx_inited = false;

    public final void _jspx_init() throws org.apache.jasper.runtime.JspException {
    }

    public void _jspService(HttpServletRequest request, HttpServletResponse  response)
        throws java.io.IOException, ServletException {

        JspFactory _jspxFactory = null;
        PageContext pageContext = null;
        HttpSession session = null;
        ServletContext application = null;
        ServletConfig config = null;
        JspWriter out = null;
        Object page = this;
        String  _value = null;
        try {

            if (_jspx_inited == false) {
                synchronized (this) {
                    if (_jspx_inited == false) {
                        _jspx_init();
                        _jspx_inited = true;
                    }
                }
            }
            _jspxFactory = JspFactory.getDefaultFactory();
            response.setContentType("text/html;charset=ISO-8859-1");
            pageContext = _jspxFactory.getPageContext(this, request, response,
			"", true, 8192, true);

            application = pageContext.getServletContext();
            config = pageContext.getServletConfig();
            session = pageContext.getSession();
            out = pageContext.getOut();

            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(0,32);to=(0,33)]
                out.write(" ");

            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(0,65);to=(0,66)]
                out.write(" ");

            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(0,97);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(1,26);to=(1,27)]
                out.write(" ");

            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(1,55);to=(1,56)]
                out.write(" ");

            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(1,85);to=(2,0)]
                out.write(" \r\n");

            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(2,28);to=(2,29)]
                out.write(" ");

            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(2,58);to=(2,59)]
                out.write(" ");

            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(2,91);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(3,25);to=(17,0)]
                out.write("\r\n<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\r\n<HTML><HEAD><TITLE>Detailed Case</TITLE>\r\n<META http-equiv=Content-Type content=\"text/html; charset=iso-8859-1\">\r\n<LINK href=\"css/global.css\" rel=STYLESHEET>\r\n<SCRIPT language=JavaScript src=\"js/global.js\"></SCRIPT>\r\n<SCRIPT language=JavaScript src=\"js/pss.js\"></SCRIPT>\r\n\r\n<script language=JavaScript>\r\nvar DelivValidator=new PssProcedureValidator();\r\n</script>\r\n\r\n<script language=JavaScript>\r\n<!--\r\n");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(17,2);to=(28,0)]
                
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
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(28,2);to=(29,40)]
                out.write("\r\ntop.menu.showText(\"Utilisateur:</td><td>");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(29,43);to=(29,83)]
                out.print((String)session.getAttribute("USERNAME"));
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(29,85);to=(29,101)]
                out.write("\",\"Cas:</td><td>");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(29,104);to=(29,112)]
                out.print(casename);
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(29,114);to=(29,115)]
                out.write(" ");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(29,118);to=(29,127)]
                out.print(transname);
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(29,129);to=(29,136)]
                out.write(" =&gt; ");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(29,139);to=(29,147)]
                out.print(procname);
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(29,149);to=(97,0)]
                out.write("\");\r\nfunction doChangeStatus(mode,caseid,transid,statusid)\r\n{\r\n\tvar url;\r\n\turl=escape(document.location);\r\n\tdocument.location=\"statustrans.jsp?MODE=\"+mode+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&STATUSID=\"+statusid+\"&REDIRECT=\"+url;\r\n}\r\n\r\nfunction sendChief(procid,caseid,transid)\r\n{\r\n\tvar url;\r\n\turl=escape(\"listcase.jsp?MODE=0\");\r\n\tdocument.location=\"chief.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&REDIRECT=\"+url;\r\n}\r\n\r\nfunction doStartDeliv(procid,caseid,transid,delivid,lateral)\r\n{\r\n\tvar url;\r\n\turl=escape(document.location);\r\n\tdocument.location=\"deliv.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&DELIVID=\"+delivid+\"&LATERAL=\"+lateral+\"&REDIRECT=\"+url;\r\n}\r\n\r\nfunction retSender(procid,caseid,transid)\r\n{\r\n\tvar url;\r\n\turl=escape(\"listcase.jsp?MODE=0\");\r\n\tdocument.location=\"return.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&REDIRECT=\"+url;\r\n}\r\n\r\nfunction terminate(url)\r\n{\r\n\tif (DelivValidator.validator()==true)\r\n\t\tdocument.location=url;\r\n}\r\n\r\nfunction signature(url)\r\n{\r\n\tif (DelivValidator.validator()==true)\r\n\t\tdocument.location=url;\r\n}\r\n\r\n\r\nfunction showDeliv(procid,caseid,transid,delivid,lateral)\r\n{\r\n\tvar url;\r\n\turl=escape(document.location);\r\n\tdocument.location=\"detaildeliv.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&DELIVID=\"+delivid+\"&REDIRECT=\"+url+\"&LATERAL=\"+lateral;\r\n}\r\n//-->\r\n</script>\r\n\r\n\r\n</HEAD>\r\n<BODY text=#000000 vLink=#666666 link=#003399 bgColor=#ffffff leftMargin=0 topMargin=0 MARGINHEIGHT=\"0\" MARGINWIDTH=\"0\">\r\n<TABLE width=\"100%\" border=0>\r\n  <TBODY>\r\n  <TR>\r\n    <TD width=\"11%\" >&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"89%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR bgColor=#336699>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/ard.gif\"></TD>\r\n          <TD width=\"82%\"><NOBR><FONT class=swb color=#ffffff>Livrables en entrée</FONT></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" bgColor=#93bee2><NOBR><IMG height=7 alt=\"trié par ordre décroissant\" hspace=3 src=\"img/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=sbbd color=#003366>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(97,2);to=(166,0)]
                
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
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(166,2);to=(180,0)]
                out.write("\r\n</tbody></table></td></tr>\r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"89%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR bgColor=#336699>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23><INPUT title=\"Sélectionner ou annuler la sélection de toutes les tâches\"    onclick='alert(\"NA\");' tabIndex=105 type=checkbox name=allbox> </TD>\r\n          <TD width=\"82%\"><NOBR><FONT class=swb color=#ffffff>Tâche</FONT></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" bgColor=#93bee2><NOBR><IMG height=7 alt=\"trié par ordre décroissant\" hspace=3 src=\"img/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=sbbd color=#003366>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(180,2);to=(218,0)]
                
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
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(218,2);to=(235,0)]
                out.write("\r\n</tbody></table></td></tr>\r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"89%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n\t<INPUT type=hidden value=F000000001 name=curmbox> \r\n\t<INPUT type=hidden name=js> <INPUT type=hidden name=_HMaction> \r\n\t<INPUT type=hidden value=inbox name=foo> <INPUT type=hidden name=page> \r\n        <TBODY>\r\n        <TR bgColor=#336699>\r\n          <TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23><INPUT title=\"Sélectionner ou annuler la sélection de toutes les tâches\"    onclick='alert(\"NA\");' tabIndex=105 type=checkbox name=allbox> </TD>\r\n          <TD width=\"82%\"><NOBR><FONT class=swb color=#ffffff>Décision</FONT></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" bgColor=#93bee2><NOBR><IMG height=7 alt=\"trié par ordre décroissant\" hspace=3 src=\"img/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=sbbd color=#003366>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(235,2);to=(270,0)]
                
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
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(270,2);to=(284,0)]
                out.write("   \r\n</tbody></table></td></tr>\r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"89%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR bgColor=#336699>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/ard.gif\"></TD>\r\n          <TD width=\"82%\"><NOBR><FONT class=swb color=#ffffff>Références</FONT></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" bgColor=#93bee2><NOBR><IMG height=7 alt=\"trié par ordre décroissant\" hspace=3 src=\"img/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=sbbd color=#003366>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(284,2);to=(332,0)]
                
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
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(332,2);to=(358,0)]
                out.write("\r\n</tbody></table></td></tr>\r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"89%\">\r\n      <TABLE class=Mtable id=LateralDelivTable cellSpacing=0 cellPadding=0\r\n      width=\"100%\"><INPUT type=hidden value=F000000001 name=curmbox2> <INPUT \r\n        type=hidden name=js2> <INPUT type=hidden name=_HMaction2> <INPUT \r\n        type=hidden value=inbox name=foo2> <INPUT type=hidden name=page2> \r\n        <TBODY>\r\n        <TR bgColor=#336699>\r\n          <TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/ard.gif\"></TD>\r\n          <TD width=\"36%\"><NOBR><A title=\"Trier par expéditeur\" \r\n            href=\"\"><FONT class=swb color=#ffffff>Livrables latéraux</FONT></A></NOBR><NOBR></NOBR></TD>\r\n          <TD width=\"46%\"><NOBR><A title=\"Trier par livrable\" \r\n            href=\"\"><FONT \r\n            class=swb \r\n            color=#ffffff>Processus</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" bgColor=#93bee2><NOBR><A title=\"Trier par date\" \r\n            href=\"\"><IMG \r\n            height=7 alt=\"trié par ordre décroissant\" hspace=3 \r\n            src=\"img/desc.gif\" width=7 border=0><FONT \r\n            class=sbbd color=#003366>Date</FONT></A>&nbsp;</NOBR></TD>\r\n\t</TR>\r\n\r\n");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(358,2);to=(472,0)]
                
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
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(472,2);to=(499,0)]
                out.write("\r\n  </TBODY></TABLE></TD></TR>\r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"89%\" >\r\n      <TABLE class=Mtable id=FollowingDelivTable cellSpacing=0 cellPadding=0 \r\n      width=\"100%\"><INPUT type=hidden value=F000000001 name=curmbox22> <INPUT \r\n        type=hidden name=js22> <INPUT type=hidden name=_HMaction22> <INPUT \r\n        type=hidden value=inbox name=foo22> <INPUT type=hidden name=page22> \r\n        <TBODY>\r\n        <TR bgColor=#336699>\r\n          <TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/ard.gif\"></TD>\r\n          <TD width=\"36%\"><NOBR><A title=\"Trier par expéditeur\" \r\n            href=\"\"><FONT \r\n            class=swb color=#ffffff>Livrables \r\n            suivants</FONT></A></NOBR><NOBR></NOBR><NOBR></NOBR><NOBR></NOBR></TD>\r\n          <TD width=\"46%\"><NOBR><A title=\"Trier par livrable\" \r\n            href=\"\"><FONT \r\n            class=swb \r\n            color=#ffffff>Processus</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" bgColor=#93bee2><NOBR><A title=\"Trier par date\" \r\n            href=\"\"><IMG \r\n            height=7 alt=\"trié par ordre décroissant\" hspace=3 \r\n            src=\"img/desc.gif\" width=7 border=0><FONT \r\n            class=sbbd color=#003366>Date</FONT></A>&nbsp;</NOBR></TD>\r\n\t</TR>\r\n");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(499,2);to=(576,0)]
                
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
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(576,2);to=(584,85)]
                out.write("\r\n</TBODY></TABLE></TD></TR></TBODY></TABLE>\r\n\r\n<TABLE width=\"100%\" border=0>\r\n  <TBODY>\r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"89%\">\r\n\t<input type=button value=\"Retour pour non conformité\" onclick='javascript:retSender(");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(584,88);to=(584,94)]
                out.print(procid);
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(584,96);to=(584,97)]
                out.write(",");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(584,100);to=(584,106)]
                out.print(caseid);
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(584,108);to=(584,109)]
                out.write(",");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(584,112);to=(584,119)]
                out.print(transid);
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(584,121);to=(585,73)]
                out.write(");'>&nbsp;\r\n\t<input type=button value=\"Remise au chef\" onclick='javascript:sendChief(");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(585,76);to=(585,82)]
                out.print(procid);
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(585,84);to=(585,85)]
                out.write(",");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(585,88);to=(585,94)]
                out.print(caseid);
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(585,96);to=(585,97)]
                out.write(",");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(585,100);to=(585,107)]
                out.print(transid);
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(585,109);to=(586,0)]
                out.write(");'>&nbsp;\r\n");

            // end
            // begin [file="/emessenger2002/detailcase.jsp";from=(586,2);to=(594,0)]
                 
                 rs=conn.sqlQueryR("SELECT * FROM pproc WHERE procid="+procid);
                 rs.next();
                 signaturemode=rs.getInt("doublesign");
                 if (signaturemode==0)
                	out.println("	<input type=button value=\"Terminé\" onclick='javascript:terminate(\"termin.jsp?REDIRECT=\"+escape(\"listcase.jsp?MODE=0\")+\"&PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"\");'>");
                 if (signaturemode>0)
                	out.println("	<input type=button value=\"Signature\" onclick='javascript:signature(\"sign.jsp?REDIRECT=\"+escape(\"listcase.jsp?MODE=0\")+\"&PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"\");'>");
            // end
            // HTML // begin [file="/emessenger2002/detailcase.jsp";from=(594,2);to=(600,0)]
                out.write("\r\n\t</td>\r\n    </tr>\r\n  </tbody>\r\n</table>\r\n</BODY></HTML>\r\n");

            // end

        } catch (Throwable t) {
            if (out != null && out.getBufferSize() != 0)
                out.clearBuffer();
            if (pageContext != null) pageContext.handlePageException(t);
        } finally {
            if (_jspxFactory != null) _jspxFactory.releasePageContext(pageContext);
        }
    }
}
