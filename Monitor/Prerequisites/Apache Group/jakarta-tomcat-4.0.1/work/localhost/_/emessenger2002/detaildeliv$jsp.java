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

            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(0,32);to=(0,33)]
                out.write(" ");

            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(0,65);to=(0,66)]
                out.write(" ");

            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(0,97);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(1,26);to=(1,27)]
                out.write(" ");

            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(1,55);to=(1,56)]
                out.write(" ");

            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(1,85);to=(2,0)]
                out.write(" \r\n");

            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(2,28);to=(2,29)]
                out.write(" ");

            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(2,58);to=(2,59)]
                out.write(" ");

            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(2,91);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(3,25);to=(30,13)]
                out.write("\r\n<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\r\n<HTML><HEAD><TITLE>Detailed Case</TITLE>\r\n<META http-equiv=Content-Type content=\"text/html; charset=iso-8859-1\">\r\n<LINK href=\"css/global.css\" rel=STYLESHEET>\r\n<SCRIPT language=JavaScript src=\"js/global.js\"></SCRIPT>\r\n<SCRIPT language=JavaScript src=\"js/pss.js\"></SCRIPT>\r\n\r\n<script language=JavaScript>\r\n<!--\r\nfunction doChangeStatus(mode,caseid,transid,statusid)\r\n{\r\n\tvar url;\r\n\turl=escape(document.location);\r\n\tdocument.location=\"statustrans.jsp?MODE=\"+mode+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&STATUSID=\"+statusid+\"&REDIRECT=\"+url;\r\n}\r\n\r\nfunction sendChief(procid,caseid,transid)\r\n{\r\n\tvar url;\r\n\turl=escape(\"listcase.jsp?MODE=0\");\r\n\tdocument.location=\"chief.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&REDIRECT=\"+url;\r\n}\r\n\r\nfunction doStartDeliv(procid,caseid,transid,delivid,lateral)\r\n{\r\n\tvar url;\r\n\turl=escape('");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(30,16);to=(30,58)]
                out.print((String)request.getParameter( "REDIRECT" ));
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(30,60);to=(65,0)]
                out.write("');\r\n\tdocument.location=\"deliv.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&DELIVID=\"+delivid+\"&LATERAL=\"+lateral+\"&REDIRECT=\"+url;\r\n}\r\n\r\nfunction retSender(procid,caseid,transid)\r\n{\r\n\tvar url;\r\n\turl=escape(\"listcase.jsp?MODE=0\");\r\n\tdocument.location=\"return.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&REDIRECT=\"+url;\r\n}\r\n\r\nfunction terminate(url)\r\n{\r\n\tif (DelivValidator.validator()==true)\r\n\t\tdocument.location=url;\r\n}\r\n\r\n//-->\r\n</script>\r\n\r\n\r\n</HEAD>\r\n<BODY text=#000000 vLink=#666666 link=#003399 bgColor=#ffffff leftMargin=0 topMargin=0 MARGINHEIGHT=\"0\" MARGINWIDTH=\"0\">\r\n<TABLE width=\"100%\" border=0>\r\n  <TBODY>\r\n  <TR>\r\n    <TD width=\"11%\" >&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"89%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR bgColor=#336699>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23><INPUT title=\"\"    onclick='alert(\"NA\");' tabIndex=105 type=checkbox name=allbox> </TD>\r\n          <TD width=\"96%\"><NOBR><FONT class=swb color=#ffffff>Informations</FONT></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(65,2);to=(106,0)]
                
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
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(106,2);to=(120,0)]
                out.write("\r\n</tbody></table></td></tr>\r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"89%\">\r\n      <TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR bgColor=#336699>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23><INPUT title=\"Démarrer toutes les références\" onclick='alert(\"NA\");' tabIndex=105 type=checkbox name=allbox> </TD>\r\n          <TD width=\"82%\"><NOBR><FONT class=swb color=#ffffff>Références</FONT></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"14%\" bgColor=#93bee2><NOBR><IMG height=7 alt=\"trié par ordre décroissant\" hspace=3 src=\"img/desc.gif\" width=7 border=0>\r\n\t\t<FONT class=sbbd color=#003366>Date</FONT>&nbsp;</NOBR></TD>\r\n        </TR>\r\n");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(120,2);to=(169,0)]
                
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
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(169,2);to=(179,85)]
                out.write("\r\n</tbody></table></td></tr>\r\n</TBODY></TABLE>\r\n\r\n<TABLE width=\"100%\" border=0>\r\n  <TBODY>\r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"89%\">\r\n<!--\r\n\t<input type=button value=\"Retour pour non conformité\" onclick='javascript:retSender(");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(179,88);to=(179,94)]
                out.print(procid);
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(179,96);to=(179,97)]
                out.write(",");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(179,100);to=(179,106)]
                out.print(caseid);
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(179,108);to=(179,109)]
                out.write(",");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(179,112);to=(179,119)]
                out.print(transid);
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(179,121);to=(180,73)]
                out.write(");'>&nbsp;\r\n\t<input type=button value=\"Remise au chef\" onclick='javascript:sendChief(");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(180,76);to=(180,82)]
                out.print(procid);
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(180,84);to=(180,85)]
                out.write(",");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(180,88);to=(180,94)]
                out.print(caseid);
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(180,96);to=(180,97)]
                out.write(",");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(180,100);to=(180,107)]
                out.print(transid);
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(180,109);to=(182,97)]
                out.write(");'>&nbsp;\r\n-->\r\n        <input type=button value=\"Revenir à la procédure\" onclick='javascript:document.location=\"");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(182,100);to=(182,142)]
                out.print((String)request.getParameter( "REDIRECT" ));
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(182,144);to=(183,0)]
                out.write("\"'>&nbsp;\r\n");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(183,2);to=(183,73)]
                if (Integer.valueOf(request.getParameter( "LATERAL" )).intValue()>=0) {
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(183,75);to=(184,69)]
                out.write("\r\n\t<input type=button value=\"Terminé\" onclick='javascript:doStartDeliv(");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(184,72);to=(184,112)]
                out.print((String)request.getParameter( "PROCID" ));
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(184,114);to=(184,115)]
                out.write(",");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(184,118);to=(184,158)]
                out.print((String)request.getParameter( "CASEID" ));
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(184,160);to=(184,161)]
                out.write(",");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(184,164);to=(184,205)]
                out.print((String)request.getParameter( "TRANSID" ));
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(184,207);to=(184,208)]
                out.write(",");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(184,211);to=(184,252)]
                out.print((String)request.getParameter( "DELIVID" ));
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(184,254);to=(184,255)]
                out.write(",");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(184,258);to=(184,299)]
                out.print((String)request.getParameter( "LATERAL" ));
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(184,301);to=(185,0)]
                out.write(");'>\r\n");

            // end
            // begin [file="/emessenger2002/detaildeliv.jsp";from=(185,2);to=(185,3)]
                }
            // end
            // HTML // begin [file="/emessenger2002/detaildeliv.jsp";from=(185,5);to=(191,0)]
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
