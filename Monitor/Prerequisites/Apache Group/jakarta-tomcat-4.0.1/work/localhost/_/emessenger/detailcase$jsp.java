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
import PsConv;
import java.io.*;
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

            // HTML // begin [file="/emessenger/detailcase.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<HTML>\r\n");

            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(1,129);to=(3,0)]
                out.write("\r\n<HEAD><TITLE>Detailed Case</TITLE>\r\n");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(3,0);to=(3,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(3,53);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(4,26);to=(7,0)]
                out.write("\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n<META HTTP-EQUIV=\"Pragma\" CONTENT=\"no-cache\"> \r\n");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(7,2);to=(9,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(9,2);to=(10,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(10,19);to=(10,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(10,29);to=(22,0)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n<script language=JavaScript src=\"js/tools.js\"></script>\r\n<script language=JavaScript src=\"js/pss.js\"></script>\r\n<SCRIPT language=JavaScript src=\"js/pssdyn.js\"></SCRIPT>\r\n\r\n<script language=JavaScript>\r\nvar DelivValidator=new PssProcedureValidator();\r\n</script>\r\n\r\n<script language=JavaScript>\r\n<!--\r\n");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(22,2);to=(34,0)]
                
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
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(34,2);to=(38,56)]
                out.write("\r\n\r\n// ----------------------------------------------------------------\r\n//Display tab on top.jsp\r\nvar info1=\"Utilisateur:</td><td colspan=2 nobr><NOBR><b>");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(38,59);to=(38,99)]
                out.print((String)session.getAttribute("USERNAME"));
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(38,101);to=(38,107)]
                out.write("</b>, ");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(38,110);to=(38,153)]
                out.print((String)session.getAttribute("USERROLETXT"));
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(38,155);to=(38,157)]
                out.write(" (");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(38,160);to=(38,208)]
                out.print((String)session.getAttribute("USERWORKGROUPTXT"));
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(38,210);to=(39,27)]
                out.write(")</NOBR>\";\r\nvar info2=\"Cas:</td><td><b>");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(39,30);to=(39,38)]
                out.print(casename);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(39,40);to=(39,42)]
                out.write(", ");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(39,45);to=(39,54)]
                out.print(transname);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(39,56);to=(39,120)]
                out.write("</b></td><td align=right><FONT class=menu>ProcÃ©dure:</font> <b>");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(39,123);to=(39,131)]
                out.print(procname);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(39,133);to=(235,69)]
                out.write("</b>\";\r\ntop.showText(info1,info2);\r\n// ----------------------------------------------------------------\r\n\r\nfunction doUpload(caseid,transid)\r\n{\r\n\tvar dialogWindow = window.open(\"upload.jsp?MODE=0&CASEID=\"+caseid+\"&TRANSID=\"+transid,\"\",\"height=200,width=300,modal=yes\");\r\n}\r\n\r\nfunction doChangeStatus(mode,procid,caseid,transid,statusid)\r\n{\r\n\tvar url;\r\n\turl=escape(\"listcase.jsp?MODE=0\");\r\n\tdocument.location=\"statustrans.jsp?MODE=\"+mode+\"&PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&STATUSID=\"+statusid+\"&REDIRECT=\"+url;\r\n}\r\n\r\nfunction sendChief(procid,caseid,transid)\r\n{\r\n\tvar url;\r\n\tvar msg;\r\n\turl=\"listcase.jsp?MODE=0\";\r\n\tmsg=window.prompt(\"Veuillez dÃ©crire la remise au chef\",\"\");\r\n\tif (msg==\"null\")\r\n\t\tmsg=\"\";\r\n\tdocument.writeln(\"<form method=post name=go action=\\\"chief.jsp\\\">\");\r\n\tdocument.writeln(\"<input type=hidden name=PROCID value=\\\"\"+procid+\"\\\">\");\r\n\tdocument.writeln(\"<input type=hidden name=CASEID value=\\\"\"+caseid+\"\\\">\");\r\n\tdocument.writeln(\"<input type=hidden name=TRANSID value=\\\"\"+transid+\"\\\">\");\r\n\tdocument.writeln(\"<input type=hidden name=REDIRECT value=\\\"\"+url+\"\\\">\");\r\n\tdocument.writeln(\"<input type=hidden name=MSG value=\\\"\"+msg+\"\\\">\");\r\n\tdocument.writeln(\"</form>\");\r\n\tdocument.writeln(\"<script language=JavaScript>\");\r\n\tdocument.writeln(\"document.go.submit();\");\r\n\tdocument.writeln(\"</script>\");\r\n}\r\n\r\nfunction doStartDeliv(procid,caseid,transid,delivid,lateral)\r\n{\r\n\tvar url;\r\n\turl=escape(document.location);\r\n\tdocument.location=\"deliv.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&DELIVID=\"+delivid+\"&LATERAL=\"+lateral+\"&REDIRECT=\"+url;\r\n}\r\n\r\nfunction retSender(procid,caseid,transid)\r\n{\r\n\tvar url;\r\n\tvar msg;\r\n\turl=\"listcase.jsp?MODE=0\";\r\n\tmsg=window.prompt(\"Veuillez dÃ©crire le retour pour non conformitÃ©\",\"\");\t\r\n\tif (msg==\"null\")\r\n\t\tmsg=\"\";\r\n\tdocument.writeln(\"<form method=post name=go action=\\\"return.jsp\\\">\");\r\n\tdocument.writeln(\"<input type=hidden name=PROCID value=\\\"\"+procid+\"\\\">\");\r\n\tdocument.writeln(\"<input type=hidden name=CASEID value=\\\"\"+caseid+\"\\\">\");\r\n\tdocument.writeln(\"<input type=hidden name=TRANSID value=\\\"\"+transid+\"\\\">\");\r\n\tdocument.writeln(\"<input type=hidden name=REDIRECT value=\\\"\"+url+\"\\\">\");\r\n\tdocument.writeln(\"<input type=hidden name=MSG value=\\\"\"+msg+\"\\\">\");\r\n\tdocument.writeln(\"</form>\");\r\n\tdocument.writeln(\"<script language=JavaScript>\");\r\n\tdocument.writeln(\"document.go.submit();\");\r\n\tdocument.writeln(\"</script>\");\r\n\r\n}\r\n\r\nfunction terminate(url,delivLatMandatory,delivLatInProgress,delivLatReturned,delivNextStarted,delivNextMandatory,delivTotalNbr)\r\n{\r\n\tif (delivTotalNbr==0)\r\n\t{\r\n\t\t//'stop' - don't check\r\n\t}\r\n\telse\r\n\t{\r\n\t\tif (delivLatInProgress>0)\r\n\t\t{\r\n\t\t\talert(\"Vous devez attendre le retour des livrables latÃ©raux pour terminer la procÃ©dure en cours\");\r\n\t\t\treturn;\r\n\t\t}\r\n\t\tif (delivNextStarted==0)\r\n\t\t{\r\n\t\t\talert(\"Vous devez envoyer au moins un livrable suivant pour terminer la procÃ©dure en cours\");\r\n\t\t\treturn;\r\n\t\t}\r\n\t}\r\n\r\n\tvar n=NBR_INPUT.value;\r\n\tvar st=\"&NBR_INPUT=\"+n;\r\n\tfor (i=1;i<=n;i++)\r\n\t{\r\n\t\tst=st+\"&CTL_\"+i+\"=\"+escape(document.getElementById(\"CTL_\"+i).value);\r\n\t\tst=st+\"&CTL2_\"+i+\"=\"+escape(document.getElementById(\"CTL2_\"+i).value);\r\n\t}\r\n\r\n\tif (DelivValidator.validator()==true)\r\n\t\tdocument.location=url+st;\t//TODO: faire un POST\r\n}\r\n\r\nfunction signature(url,delivLatMandatory,delivLatInProgress,delivLatReturned,delivNextStarted,delivNextMandatory,delivTotalNbr)\r\n{\r\n\r\n\tif (delivTotalNbr==0)\r\n\t{\r\n\t\t//'stop' - don't check\r\n\t}\r\n\telse\r\n\t{\r\n\t\tif (delivLatInProgress>0)\r\n\t\t{\r\n\t\t\talert(\"Vous devez attendre le retour des livrables latÃ©raux pour signer la procÃ©dure en cours!\");\r\n\t\t\treturn;\r\n\t\t}\r\n\t\tif (delivNextStarted==0)\r\n\t\t{\r\n\t\t\talert(\"Vous devez envoyer au moins un livrable suivant pour signer la procÃ©dure en cours!\");\r\n\t\t\treturn;\r\n\t\t}\r\n\t}\r\n\r\n\tvar n=NBR_INPUT.value;\r\n\tvar st=\"&NBR_INPUT=\"+n;\r\n\tfor (i=1;i<=n;i++)\r\n\t{\r\n\t\tst=st+\"&CTL_\"+i+\"=\"+escape(document.getElementById(\"CTL_\"+i).value);\r\n\t\tst=st+\"&CTL2_\"+i+\"=\"+escape(document.getElementById(\"CTL2_\"+i).value);\r\n\t}\r\n\t//TODO: faire un POST\r\n\r\n\tif (DelivValidator.validator()==true)\r\n\t\tdocument.location=url+st;\r\n}\r\n\r\n\r\nfunction showDeliv(procid,caseid,transid,delivid,lateral,delivLatInProgress,delivLatMandatory)\r\n{\r\n\tif (delivLatMandatory>0)\r\n\t{\r\n\t\talert(\"Vous devez dÃ©marrer les livrables latÃ©raux obligatoires pour envoyer un livrable suivant!\");\r\n\t\treturn;\r\n\t}\r\n\tif (delivLatInProgress>0)\r\n\t{\r\n\t\talert(\"Vous devez attendre le retour des livrables latÃ©raux en cours pour envoyer un livrable suivant!\");\r\n\t\treturn;\r\n\t}\r\n\r\n\tvar url;\r\n\turl=escape(document.location);\r\n\r\n\tdocument.location=\"detaildeliv.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&DELIVID=\"+delivid+\"&REDIRECT=\"+url+\"&LATERAL=\"+lateral;\r\n}\r\n\r\n\r\nfunction writeObj(id,text)\r\n{\r\n  if (document.getElementById)\r\n\t{\r\n\t\tx = document.getElementById(id);\r\n\t\tx.innerHTML = text;\r\n\t}\r\n\telse if (document.all)\r\n\t{\r\n\t\tx = document.all[id];\r\n\t\tx.innerHTML = text;\r\n\t}\r\n\telse if (document.layers)\r\n\t{\r\n\t\tx = document.layers[id];\r\n\t\tx.document.open();\r\n\t\tx.document.write(text);\r\n\t\tx.document.close();\r\n\t}\r\n\r\n}\r\n\r\nfunction processRow(rowno,ncnt)\r\n{\r\n\tobjname=\"\"+rowno;\r\n\twriteObj(\"CNT\"+objname,ncnt);\r\n\tif (ncnt==0) {document.all[\"ROW\"+objname].style.display=\"none\";}\r\n\t\r\n}\r\n\r\n//-->\r\n</script>\r\n\r\n\r\n</HEAD>\r\n<BODY>\r\n<TABLE width=\"100%\" border=0>\r\n  <TBODY><applet name=CTL code=AppLauncher.class archive=AppLauncher.jar width=1 height=1></applet>\r\n  <TR id=ROW1>\r\n    <TD width=\"1%\" >&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\" nobr>\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(235,72);to=(235,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(235,82);to=(237,109)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"82%\"><NOBR><FONT class=menu>Livrables en entrÃ©e</FONT> (<a class=menu name=CNT1></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" class=BgL><NOBR><IMG height=7 alt=\"triÃ© par ordre dÃ©croissant\" hspace=3 src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(237,112);to=(237,120)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(237,122);to=(240,0)]
                out.write("/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=swnub>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(240,2);to=(317,0)]
                
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
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(317,2);to=(319,13)]
                out.write("\r\n<script language=JavaScript>\r\nprocessRow(1,");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(319,16);to=(319,20)]
                out.print(ncnt);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(319,22);to=(330,60)]
                out.write(");\r\n</script>\r\n\r\n</tbody></table></td></tr>\r\n  <TR id=ROW2>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>        \r\n\t<TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(330,63);to=(330,71)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(330,73);to=(332,109)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"82%\"><NOBR><FONT class=menu>TÃ¢ches</FONT> (<a class=menu name=CNT2></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" class=BgL><NOBR><IMG height=7 alt=\"triÃ© par ordre dÃ©croissant\" hspace=3 src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(332,112);to=(332,120)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(332,122);to=(335,0)]
                out.write("/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=swnub>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(335,2);to=(361,0)]
                
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
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(361,2);to=(364,13)]
                out.write("\r\n</tbody></table></td></tr>\r\n<script language=JavaScript>\r\nprocessRow(2,");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(364,16);to=(364,20)]
                out.print(ncnt);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(364,22);to=(374,70)]
                out.write(");\r\n</script>\r\n\r\n  <TR id=ROW3>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>\r\n          \t<TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(374,73);to=(374,81)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(374,83);to=(376,109)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"82%\"><NOBR><FONT class=menu>DÃ©cisions</FONT> (<a class=menu name=CNT3></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" class=BgL><NOBR><IMG height=7 alt=\"triÃ© par ordre dÃ©croissant\" hspace=3 src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(376,112);to=(376,120)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(376,122);to=(379,0)]
                out.write("/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=swnub>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(379,2);to=(406,0)]
                
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
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(406,2);to=(409,13)]
                out.write("   \r\n</tbody></table></td></tr>\r\n<script language=JavaScript>\r\nprocessRow(3,");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(409,16);to=(409,20)]
                out.print(ncnt);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(409,22);to=(419,69)]
                out.write(");\r\n</script>\r\n\r\n  <TR id=ROW4>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(419,72);to=(419,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(419,82);to=(421,109)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"82%\"><NOBR><FONT class=menu>RÃ¨gles</FONT> (<a class=menu name=CNT4></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" class=BgL><NOBR><IMG height=7 alt=\"triÃ© par ordre dÃ©croissant\" hspace=3 src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(421,112);to=(421,120)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(421,122);to=(424,0)]
                out.write("/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=swnub>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(424,2);to=(454,0)]
                
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
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(454,2);to=(457,13)]
                out.write("\r\n</tbody></table></td></tr>\r\n<script language=JavaScript>\r\nprocessRow(4,");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(457,16);to=(457,20)]
                out.print(ncnt);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(457,22);to=(468,69)]
                out.write(");\r\n</script>\r\n\r\n\r\n <TR id=ROW5>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(468,72);to=(468,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(468,82);to=(470,109)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"82%\"><NOBR><FONT class=menu>SystÃ¨mes</FONT> (<a class=menu name=CNT5></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" class=BgL><NOBR><IMG height=7 alt=\"triÃ© par ordre dÃ©croissant\" hspace=3 src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(470,112);to=(470,120)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(470,122);to=(473,0)]
                out.write("/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=swnub>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(473,2);to=(510,0)]
                
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
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(510,2);to=(513,13)]
                out.write("\r\n</tbody></table></td></tr>\r\n<script language=JavaScript>\r\nprocessRow(5,");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(513,16);to=(513,20)]
                out.print(ncnt);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(513,22);to=(524,69)]
                out.write(");\r\n</script>\r\n\r\n\r\n  <TR id=ROW6>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(524,72);to=(524,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(524,82);to=(526,109)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"82%\"><NOBR><FONT class=menu>RÃ©fÃ©rences</FONT> (<a class=menu name=CNT6></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" class=BgL><NOBR><IMG height=7 alt=\"triÃ© par ordre dÃ©croissant\" hspace=3 src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(526,112);to=(526,120)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(526,122);to=(529,0)]
                out.write("/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=swnub>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(529,2);to=(578,0)]
                
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
                
                	String prg="explorer";	
                	if (ext.equalsIgnoreCase("plf")==true)
                		prg=PsConfig.get("SCRIPTOR_LAUNCHER");
                
                
                	String url=PsConv.c4JS(prg)+" "+PsConv.c4JS(doc);
                
                	out.println("<TD width=\"82%\"><a href='javascript:CTL.startUp(\""+url+"\");' >"+titreRef+"</a></TD>");
                	out.println("<TD width=\"14%\">"+mdated+"</TD></TR>");
                	}
                 }
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(578,2);to=(581,13)]
                out.write("\r\n</tbody></table></td></tr>\r\n<script language=JavaScript>\r\nprocessRow(6,");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(581,16);to=(581,20)]
                out.print(ncnt);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(581,22);to=(591,69)]
                out.write(");\r\n</script>\r\n\r\n<TR id=ROW7>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(591,72);to=(591,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(591,82);to=(594,109)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"36%\"><NOBR><FONT class=menu>Fichier(s) joints</FONT> (<a class=menu name=CNT7></a>)</NOBR></TD>\r\n\t  <TD width=\"46%\"><NOBR><FONT class=menu>xxUtilisateur</FONT></NOBR></TD>\r\n          <TD width=\"14%\" class=BgL><NOBR><IMG height=7 alt=\"triÃ© par ordre dÃ©croissant\" hspace=3 src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(594,112);to=(594,120)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(594,122);to=(597,0)]
                out.write("/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=sbbd>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(597,2);to=(624,0)]
                
                
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
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(624,2);to=(627,13)]
                out.write("\r\n</tbody></table></td></tr>\r\n<script language=JavaScript>\r\nprocessRow(7,");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(627,16);to=(627,20)]
                out.print(ncnt);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(627,22);to=(639,69)]
                out.write(");\r\n</script>\r\n\r\n\r\n\r\n  <TR id=ROW8>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(639,72);to=(639,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(639,82);to=(641,109)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"82%\"><NOBR><FONT class=menu>Saisie d'attributs</FONT> (<a class=menu name=CNT8></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" class=BgL><NOBR><IMG height=7 alt=\"triÃ© par ordre dÃ©croissant\" hspace=3 src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(641,112);to=(641,120)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(641,122);to=(644,0)]
                out.write("/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=swnub>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(644,2);to=(681,0)]
                
                
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
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(681,2);to=(685,13)]
                out.write("\r\n\r\n</TR></TBODY></TABLE>\r\n<script language=JavaScript>\r\nprocessRow(8,");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(685,16);to=(685,20)]
                out.print(ncnt);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(685,22);to=(688,0)]
                out.write(");\r\n</script>\r\n\r\n");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(688,2);to=(695,0)]
                
                	int delivTotalNbr=0;
                	int delivLatMandatory=0;
                	int delivLatInProgress=0;
                	int delivLatReturned=0;
                	int delivNextStarted=0;
                	int delivNextMandatory=0;
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(695,2);to=(705,69)]
                out.write("\r\n\r\n  <TR id=ROW9>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\">\r\n      <TABLE class=Mtable id=LateralDelivTable cellSpacing=0 cellPadding=0\r\n      width=\"100%\"> \r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(705,72);to=(705,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(705,82);to=(714,21)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"36%\"><NOBR><A title=\"Trier par expÃ©diteur\" \r\n            href=\"\"><FONT class=menu>Livrables latÃ©raux</FONT></A> (<a class=menu name=CNT9></a>)</NOBR><NOBR></NOBR></TD>\r\n          <TD width=\"46%\"><NOBR><A title=\"Trier par livrable\" \r\n            href=\"\"><FONT \r\n            class=menu>ProcÃ©dure</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" class=BgL><NOBR><A title=\"Trier par date\" \r\n            href=\"\"><IMG \r\n            height=7 alt=\"triÃ© par ordre dÃ©croissant\" hspace=3 \r\n            src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(714,24);to=(714,32)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(714,34);to=(718,0)]
                out.write("/desc.gif\" width=7 border=0><FONT \r\n            class=swnub>Date</FONT></A>&nbsp;</NOBR></TD>\r\n\t</TR>\r\n\r\n");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(718,2);to=(843,0)]
                
                	//check if already locked (concurrency check)
                	rs=conn.sqlQueryR("SELECT statusid,emplid FROM pproctrans WHERE procid="+procid+" AND transid="+transid);
                	rs.next();
                	if (rs.getInt("statusid")==1 && rs.getInt("emplid")!=userid)
                	{
                		out.println("alert(\"Travail dÃ©jÃ  encours par le user "+rs.getInt("emplid")+"\");");
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
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(843,2);to=(846,13)]
                out.write("\r\n  </TBODY></TABLE></TD></TR>\r\n<script language=JavaScript>\r\nprocessRow(9,");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(846,16);to=(846,20)]
                out.print(ncnt);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(846,22);to=(857,69)]
                out.write(");\r\n</script>\r\n\r\n  <TR id=ROW10>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\">\r\n      <TABLE class=Mtable id=FollowingDelivTable cellSpacing=0 cellPadding=0 \r\n      width=\"100%\">\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\"><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(857,72);to=(857,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(857,82);to=(867,21)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"36%\"><NOBR><A title=\"Trier par expÃ©diteur\" \r\n            href=\"\"><FONT class=menu>Livrables \r\n            suivants</FONT></A> (<a class=menu name=CNT10></a>)</NOBR><NOBR></NOBR><NOBR></NOBR><NOBR></NOBR></TD>\r\n          <TD width=\"46%\"><NOBR><A title=\"Trier par livrable\" \r\n            href=\"\"><FONT \r\n            class=menu>ProcÃ©dure</FONT></A></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" class=BgL><NOBR><A title=\"Trier par date\" \r\n            href=\"\"><IMG \r\n            height=7 alt=\"triÃ© par ordre dÃ©croissant\" hspace=3 \r\n            src=\"img/");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(867,24);to=(867,32)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(867,34);to=(870,0)]
                out.write("/desc.gif\" width=7 border=0><FONT \r\n            class=swnub>Date</FONT></A>&nbsp;</NOBR></TD>\r\n\t</TR>\r\n");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(870,2);to=(949,0)]
                
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
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(949,2);to=(952,14)]
                out.write("\r\n</TBODY></TABLE></TD>\r\n<script language=JavaScript>\r\nprocessRow(10,");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(952,17);to=(952,21)]
                out.print(ncnt);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(952,23);to=(960,89)]
                out.write(");\r\n</script>\r\n\r\n<TABLE width=\"100%\" border=0>\r\n  <TBODY>\r\n  <TR>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\">\r\n\t<input type=button class=sbttn value=\"Joindre un document\" onclick='javascript:doUpload(");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(960,92);to=(960,98)]
                out.print(caseid);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(960,100);to=(960,101)]
                out.write(",");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(960,104);to=(960,111)]
                out.print(transid);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(960,113);to=(961,93)]
                out.write(");'>&nbsp;\r\n\t<input type=button class=sbttn value=\"Mise en attente\" onclick='javascript:doChangeStatus(1,");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(961,96);to=(961,102)]
                out.print(procid);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(961,104);to=(961,105)]
                out.write(",");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(961,108);to=(961,114)]
                out.print(caseid);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(961,116);to=(961,117)]
                out.write(",");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(961,120);to=(961,127)]
                out.print(transid);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(961,129);to=(962,98)]
                out.write(",2);'>&nbsp;\r\n\t<input type=button class=sbttn value=\"Retour pour non conformitÃ©\" onclick='javascript:retSender(");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(962,101);to=(962,107)]
                out.print(procid);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(962,109);to=(962,110)]
                out.write(",");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(962,113);to=(962,119)]
                out.print(caseid);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(962,121);to=(962,122)]
                out.write(",");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(962,125);to=(962,132)]
                out.print(transid);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(962,134);to=(963,85)]
                out.write(");'>&nbsp;\r\n\t<input type=button class=sbttn value=\"Remise au chef\" onclick='javascript:sendChief(");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(963,88);to=(963,94)]
                out.print(procid);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(963,96);to=(963,97)]
                out.write(",");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(963,100);to=(963,106)]
                out.print(caseid);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(963,108);to=(963,109)]
                out.write(",");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(963,112);to=(963,119)]
                out.print(transid);
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(963,121);to=(964,0)]
                out.write(");'>&nbsp;\r\n");

            // end
            // begin [file="/emessenger/detailcase.jsp";from=(964,2);to=(972,0)]
                 
                 rs=conn.sqlQueryR("SELECT * FROM pproc WHERE procid="+procid);
                 rs.next();
                 signaturemode=rs.getInt("doublesign");
                 if (signaturemode==0)
                	out.println("	<input class=sbttn type=button value=\"TerminÃ©\" style=\"width:200px;\" onclick='javascript:terminate(\"termin.jsp?REDIRECT=\"+escape(\"listcase.jsp?MODE=0\")+\"&PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"\","+delivLatMandatory+","+delivLatInProgress+","+delivLatReturned+","+delivNextStarted+","+delivNextMandatory+","+delivTotalNbr+");'>");
                 if (signaturemode>0)
                	out.println("	<input class=sbttn type=button value=\"Signature\" onclick='javascript:signature(\"sign.jsp?REDIRECT=\"+escape(\"listcase.jsp?MODE=0\")+\"&PROCID="+procid+"&CASEID="+caseid+"&TRANSID="+transid+"\","+delivLatMandatory+","+delivLatInProgress+","+delivLatReturned+","+delivNextStarted+","+delivNextMandatory+","+delivTotalNbr+");'>");
            // end
            // HTML // begin [file="/emessenger/detailcase.jsp";from=(972,2);to=(978,0)]
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
