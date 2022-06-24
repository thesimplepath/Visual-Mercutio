package org.apache.jsp;

import java.util.*;
import java.lang.*;
import java.sql.*;
import PsApp;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsConfig;
import PsConv;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class detaildeliv$jsp extends HttpJspBase {


    static {
    }
    public detaildeliv$jsp( ) {
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

            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<HTML>\r\n");

            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(1,102);to=(4,0)]
                out.write("\r\n\r\n<HEAD><TITLE>Detailed Case</TITLE>\r\n");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(4,0);to=(4,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(4,53);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(5,26);to=(7,0)]
                out.write("\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(7,2);to=(9,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(9,2);to=(10,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(10,19);to=(10,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(10,29);to=(33,13)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n<SCRIPT language=JavaScript src=\"js/pssdyn.js\"></SCRIPT>\r\n\r\n<script language=JavaScript>\r\n<!--\r\n\r\nfunction doChangeStatus(mode,caseid,transid,statusid)\r\n{\r\n\tvar url;\r\n\turl=escape(document.location);\r\n\tdocument.location=\"statustrans.jsp?MODE=\"+mode+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&STATUSID=\"+statusid+\"&REDIRECT=\"+url;\r\n}\r\n\r\nfunction sendChief(procid,caseid,transid)\r\n{\r\n\tvar url;\r\n\turl=escape(\"listcase.jsp?MODE=0\");\r\n\tdocument.location=\"chief.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&REDIRECT=\"+url;\r\n}\r\n\r\nfunction doStartDeliv(procid,caseid,transid,delivid,lateral)\r\n{\r\n\tvar url;\r\n\turl=escape('");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(33,16);to=(33,58)]
                out.print((String)request.getParameter( "REDIRECT" ));
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(33,60);to=(109,69)]
                out.write("');\r\n\r\n\tvar n=NBR_INPUT.value;\r\n\r\n\tvar st=\"&NBR_INPUT=\"+n;\r\n\tfor (i=1;i<=n;i++)\r\n\t{\r\n\t\tst=st+\"&CTL_\"+i+\"=\"+escape(document.getElementById(\"CTL_\"+i).value);\r\n\t\tst=st+\"&CTL2_\"+i+\"=\"+escape(document.getElementById(\"CTL2_\"+i).value);\r\n\t}\r\n\t//TODO: faire un POST\r\ndocument.location=\"deliv.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&DELIVID=\"+delivid+\"&LATERAL=\"+lateral+\"&REDIRECT=\"+url+st;\r\n}\r\n\r\nfunction doUpload(caseid,transid)\r\n{\r\n\tvar dialogWindow = window.open(\"upload.jsp?MODE=0&CASEID=\"+caseid+\"&TRANSID=\"+transid,\"\",\"height=200,width=300,modal=yes\");\r\n}\r\n\r\nfunction retSender(procid,caseid,transid)\r\n{\r\n\tvar url;\r\n\turl=escape(\"listcase.jsp?MODE=0\");\r\n\tdocument.location=\"return.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&REDIRECT=\"+url;\r\n}\r\n\r\nfunction terminate(url)\r\n{\r\n\tif (DelivValidator.validator()==true)\r\n\t\tdocument.location=url;\r\n}\r\n\r\nfunction writeObj(id,text)\r\n{\r\n  if (document.getElementById)\r\n\t{\r\n\t\tx = document.getElementById(id);\r\n\t\tx.innerHTML = text;\r\n\t}\r\n\telse if (document.all)\r\n\t{\r\n\t\tx = document.all[id];\r\n\t\tx.innerHTML = text;\r\n\t}\r\n\telse if (document.layers)\r\n\t{\r\n\t\tx = document.layers[id];\r\n\t\tx.document.open();\r\n\t\tx.document.write(text);\r\n\t\tx.document.close();\r\n\t}\r\n}\r\n\r\nfunction processRow(rowno,ncnt)\r\n{\r\n\tobjname=\"\"+rowno;\r\n\twriteObj(\"CNT\"+objname,ncnt);\r\n\tif (ncnt==0) {document.all[\"ROW\"+objname].style.display=\"none\";}\r\n}\r\n\r\n//-->\r\n</script>\r\n\r\n\r\n</HEAD>\r\n<BODY>\r\n<applet name=CTL code=AppLauncher.class archive=AppLauncher.jar width=1 height=1></applet>\r\n<TABLE width=\"100%\" border=0>\r\n  <TBODY>\r\n  <TR id=ROW1>\r\n    <TD width=\"1%\" >&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(109,72);to=(109,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(109,82);to=(112,0)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"96%\"><NOBR><FONT class=menu>Informations</FONT> (<a class=menu name=CNT1></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(112,2);to=(174,0)]
                
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
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(174,2);to=(179,56)]
                out.write("\r\n\r\n<script language=JavaScript>\r\n// ----------------------------------------------------------------\r\n//Display tab on top.jsp\r\nvar info1=\"Utilisateur:</td><td colspan=2 nobr><NOBR><b>");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(179,59);to=(179,99)]
                out.print((String)session.getAttribute("USERNAME"));
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(179,101);to=(179,107)]
                out.write("</b>, ");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(179,110);to=(179,153)]
                out.print((String)session.getAttribute("USERROLETXT"));
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(179,155);to=(179,157)]
                out.write(" (");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(179,160);to=(179,208)]
                out.print((String)session.getAttribute("USERWORKGROUPTXT"));
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(179,210);to=(180,27)]
                out.write(")</NOBR>\";\r\nvar info2=\"Cas:</td><td><b>");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(180,30);to=(180,38)]
                out.print(casename);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(180,40);to=(180,42)]
                out.write(", ");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(180,45);to=(180,54)]
                out.print(transname);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(180,56);to=(180,118)]
                out.write("</b></td><td align=right><FONT class=menu>Livrable:</font> <b>");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(180,121);to=(180,130)]
                out.print(delivname);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(180,132);to=(187,13)]
                out.write("</b>\";\r\ntop.showText(info1,info2);\r\n// ----------------------------------------------------------------\r\n</script>\r\n\r\n</tbody></table></td></tr>\r\n<script language=JavaScript>\r\nprocessRow(1,");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(187,16);to=(187,20)]
                out.print(ncnt);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(187,22);to=(197,69)]
                out.write(");\r\n</script>\r\n\r\n <TR id=ROW2>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(197,72);to=(197,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(197,82);to=(199,109)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"82%\"><NOBR><FONT class=menu>RÃ¨gles</FONT> (<a class=menu name=CNT2></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" class=BgL><NOBR><IMG height=7 alt=\"triÃ© par ordre dÃ©croissant\" hspace=3 src=\"img/");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(199,112);to=(199,120)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(199,122);to=(202,0)]
                out.write("/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=sbbd>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(202,2);to=(232,0)]
                
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
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(232,2);to=(235,13)]
                out.write("\r\n</tbody></table></td></tr>\r\n<script language=JavaScript>\r\nprocessRow(2,");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(235,16);to=(235,20)]
                out.print(ncnt);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(235,22);to=(245,69)]
                out.write(");\r\n</script>\r\n\r\n  <TR id=ROW3>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(245,72);to=(245,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(245,82);to=(247,109)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"82%\"><NOBR><FONT class=menu>RÃ©fÃ©rences</FONT> (<a class=menu name=CNT3></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" class=BgL><NOBR><IMG height=7 alt=\"triÃ© par ordre dÃ©croissant\" hspace=3 src=\"img/");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(247,112);to=(247,120)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(247,122);to=(250,0)]
                out.write("/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=sbbd>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(250,2);to=(301,0)]
                
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
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(301,2);to=(304,13)]
                out.write("\r\n</tbody></table></td></tr>\r\n<script language=JavaScript>\r\nprocessRow(3,");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(304,16);to=(304,20)]
                out.print(ncnt);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(304,22);to=(313,69)]
                out.write(");\r\n</script>\r\n <TR id=ROW4>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(313,72);to=(313,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(313,82);to=(316,109)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"41%\"><NOBR><FONT class=menu>Fichier(s) joints</FONT> (<a class=menu name=CNT4></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>\r\n\t  <TD width=\"41%\"><NOBR><FONT class=menu>Utilisateur</FONT>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" class=BgL><NOBR><IMG height=7 alt=\"triÃ© par ordre dÃ©croissant\" hspace=3 src=\"img/");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(316,112);to=(316,120)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(316,122);to=(319,0)]
                out.write("/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=sbbd>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(319,2);to=(344,0)]
                
                
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
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(344,2);to=(347,13)]
                out.write("\r\n</tbody></table></td></tr>\r\n<script language=JavaScript>\r\nprocessRow(4,");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(347,16);to=(347,20)]
                out.print(ncnt);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(347,22);to=(357,69)]
                out.write(");\r\n</script>\r\n\r\n  <TR id=ROW5>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(357,72);to=(357,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(357,82);to=(359,109)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"82%\"><NOBR><FONT class=menu>Saisie d'attributs</FONT> (<a class=menu name=CNT5></a>)</NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" class=BgL><NOBR><IMG height=7 alt=\"triÃ© par ordre dÃ©croissant\" hspace=3 src=\"img/");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(359,112);to=(359,120)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(359,122);to=(362,0)]
                out.write("/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=sbbd>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(362,2);to=(401,0)]
                
                
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
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(401,2);to=(404,13)]
                out.write("\r\n</tbody></table></td></tr>\r\n<script language=JavaScript>\r\nprocessRow(5,");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(404,16);to=(404,20)]
                out.print(ncnt);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(404,22);to=(413,11)]
                out.write(");\r\n</script>\r\n\r\n\r\n\r\n</TBODY></TABLE>\r\n\r\n<script language=JavaScript>\r\n//display text if nothing is visible\r\nvar ntotal=");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(413,14);to=(413,20)]
                out.print(ntotal);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(413,22);to=(429,89)]
                out.write(";\r\nif (ntotal==0)\r\n{\r\n\tdocument.writeln(\"<TABLE width=\\\"100%\\\" border=0><TBODY><TR><TD width=\\\"1%\\\" >&nbsp;</TD><TD class=NormalBlack vAlign=top width=\\\"99%\\\">\");\r\n\tdocument.writeln(\"<TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\\\"100%\\\"><TBODY><TR>\");\r\n\tdocument.writeln(\"Aucun traitements ou informations.<br>\");\r\n\tdocument.writeln(\"Veuillez clicker sur 'Envoyer' pour valider et continuer.\");\r\n\tdocument.writeln(\"<TD></TD></TR></TABLE></TD></TR></TABLE>\");\r\n}\r\n</script>\r\n\r\n<TABLE width=\"100%\" border=0>\r\n  <TBODY>\r\n  <TR>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\">\r\n\t<input type=button class=sbttn value=\"Joindre un document\" onclick='javascript:doUpload(");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(429,92);to=(429,98)]
                out.print(caseid);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(429,100);to=(429,101)]
                out.write(",");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(429,104);to=(429,111)]
                out.print(transid);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(429,113);to=(431,98)]
                out.write(");'>&nbsp;\r\n<!--\r\n\t<input type=button class=sbttn value=\"Retour pour non conformitÃ©\" onclick='javascript:retSender(");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(431,101);to=(431,107)]
                out.print(procid);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(431,109);to=(431,110)]
                out.write(",");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(431,113);to=(431,119)]
                out.print(caseid);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(431,121);to=(431,122)]
                out.write(",");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(431,125);to=(431,132)]
                out.print(transid);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(431,134);to=(432,85)]
                out.write(");'>&nbsp;\r\n\t<input type=button class=sbttn value=\"Remise au chef\" onclick='javascript:sendChief(");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(432,88);to=(432,94)]
                out.print(procid);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(432,96);to=(432,97)]
                out.write(",");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(432,100);to=(432,106)]
                out.print(caseid);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(432,108);to=(432,109)]
                out.write(",");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(432,112);to=(432,119)]
                out.print(transid);
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(432,121);to=(434,111)]
                out.write(");'>&nbsp;\r\n-->\r\n        <input type=button class=sbttn value=\"Revenir Ã  la procÃ©dure\" onclick='javascript:document.location=\"");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(434,114);to=(434,156)]
                out.print((String)request.getParameter( "REDIRECT" ));
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(434,158);to=(435,0)]
                out.write("\"'>&nbsp;\r\n");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(435,2);to=(435,73)]
                if (Integer.valueOf(request.getParameter( "LATERAL" )).intValue()>=0) {
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(435,75);to=(436,103)]
                out.write("\r\n\t<input type=button class=sbttn value=\"Envoyer\" style=\"width:200px;\"  onclick='javascript:doStartDeliv(");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(436,106);to=(436,146)]
                out.print((String)request.getParameter( "PROCID" ));
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(436,148);to=(436,149)]
                out.write(",");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(436,152);to=(436,192)]
                out.print((String)request.getParameter( "CASEID" ));
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(436,194);to=(436,195)]
                out.write(",");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(436,198);to=(436,239)]
                out.print((String)request.getParameter( "TRANSID" ));
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(436,241);to=(436,242)]
                out.write(",");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(436,245);to=(436,286)]
                out.print((String)request.getParameter( "DELIVID" ));
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(436,288);to=(436,289)]
                out.write(",");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(436,292);to=(436,333)]
                out.print((String)request.getParameter( "LATERAL" ));
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(436,335);to=(437,0)]
                out.write(");'>\r\n");

            // end
            // begin [file="/emessenger/detaildeliv.jsp";from=(437,2);to=(437,3)]
                }
            // end
            // HTML // begin [file="/emessenger/detaildeliv.jsp";from=(437,5);to=(444,0)]
                out.write("\r\n\t</td>\r\n    </tr>\r\n  </tbody>\r\n</table>\r\n</BODY>\r\n</HTML>\r\n");

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
