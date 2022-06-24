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
import PsWorkGroup;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class newproc$jsp extends HttpJspBase {


    static {
    }
    public newproc$jsp( ) {
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

            // HTML // begin [file="/emessenger/newproc.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/emessenger/newproc.jsp";from=(1,114);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger/newproc.jsp";from=(2,26);to=(5,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/emessenger/newproc.jsp";from=(5,0);to=(5,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/emessenger/newproc.jsp";from=(5,53);to=(6,0)]
                out.write("\r\n");

            // end
            // begin [file="/emessenger/newproc.jsp";from=(6,2);to=(8,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/emessenger/newproc.jsp";from=(8,2);to=(9,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/emessenger/newproc.jsp";from=(9,19);to=(9,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/newproc.jsp";from=(9,29);to=(12,40)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n<script language=JavaScript src=\"js/pss.js\"></script>\r\n<SCRIPT language=javascript>\r\ntop.showTabText(4,\"Utilisateur:</td><td>");

            // end
            // begin [file="/emessenger/newproc.jsp";from=(12,43);to=(12,83)]
                out.print((String)session.getAttribute("USERNAME"));
            // end
            // HTML // begin [file="/emessenger/newproc.jsp";from=(12,85);to=(39,63)]
                out.write("\",\"\");\r\n</SCRIPT>\r\n</head>\r\n<BODY>\r\n<TABLE width=\"100%\" border=0 cellSpacing=0 cellPadding=0>\r\n  <TBODY>\r\n  <TR class=Bg>\r\n    <TD noWrap width=\"15%\"><A class=menu><FONT class=menu></FONT></A>&nbsp;</TD>\r\n    <TD noWrap width=\"85%\"><A class=menu><FONT class=menu>SÃ©lection d'un point de dÃ©marrage</FONT></A>&nbsp;</TD></TR>\r\n  <TR class=Bg>\r\n    <TD noWrap width=\"15%\">&nbsp;</TD>\r\n    <TD class=menu noWrap width=\"85%\"><DIV align=right>Nouveau processus</DIV></TD></TR>\r\n  <TR class=Bg>\r\n    <TD noWrap width=\"15%\">&nbsp;</TD>\r\n    <TD class=NormalBlack width=\"85%\">Pour dÃ©marrer un nouveau processus, veuillez sÃ©lectionner un modÃ¨le ci-dessous. Vous pourrez ensuite naviguer au sein du modÃ¨le en sÃ©lectionnant les symboles de processus, de page et de porte. </TD>\r\n  </TR>\r\n  </TBODY>\r\n</TABLE>\r\n<br>\r\n<br>\r\n<center>\r\n<table cellSpacing=0 cellPadding=0 width=\"100%\">\r\n<tr>\r\n <td valign=bottom width=\"11%\">&nbsp;</td>\r\n <td class=Bg width=\"89%\">\r\n  <table border=0 cellSpacing=0 cellPadding=0 width=\"100%\">\r\n   <tr>\r\n    <TD width=\"26\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/newproc.jsp";from=(39,66);to=(39,74)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/newproc.jsp";from=(39,76);to=(63,0)]
                out.write("/ard.gif\" border=0></TD>\r\n    <TD nobr><font class=swb>&nbsp;Choisir un modÃ¨le:</font></td>\r\n   </tr>\r\n  </table>\r\n </td>\r\n</tr>\r\n\r\n<tr>\r\n<td width=\"11%\">&nbsp;</td>\r\n<td width=\"89%\">\r\n<table class=Mtable cellSpacing=0 cellPadding=0 width=\"100%\">\r\n<tr >\r\n<td width=26>&nbsp;</td>\r\n<td width=\"10%\" nowrap>\r\n<a class=menu>Version</a>\r\n</td>\r\n<td width=\"10%\" nowrap>\r\n<a class=menu>Mise-Ã -jour</a>\r\n</td>\r\n<td nowrap>\r\n<a class=menu>Nom du modÃ¨le</a>\r\n</td>\r\n</tr>\r\n\r\n");

            // end
            // begin [file="/emessenger/newproc.jsp";from=(63,2);to=(78,0)]
                
                 PsApp.init();
                
                try {
                	PsDbConn conn=PsDbMgr.newConnection();
                	PsDbConn conn2=PsDbMgr.newConnection();
                	ResultSet rs;
                	ResultSet rs2;
                
                	rs=conn.sqlQueryR("SELECT * FROM pmodel GROUP BY modelref");
                	while (rs.next())
                	{
                		rs2=conn2.sqlQueryR("SELECT * FROM pmodel WHERE modelid="+rs.getString("modelid"));
                		if (rs2.next()==true)
                		{
            // end
            // HTML // begin [file="/emessenger/newproc.jsp";from=(78,2);to=(81,55)]
                out.write("\r\n\r\n<tr>\r\n<td valign=bottom width=\"2%\"><a href=\"bpml.jsp?MODELID=");

            // end
            // begin [file="/emessenger/newproc.jsp";from=(81,58);to=(81,81)]
                out.print(rs.getString("modelid"));
            // end
            // HTML // begin [file="/emessenger/newproc.jsp";from=(81,83);to=(83,0)]
                out.write("\"><img src=\"img/arr.gif\" border=\"0\"></a></td>\r\n<td valign=bottom>\r\n");

            // end
            // begin [file="/emessenger/newproc.jsp";from=(83,3);to=(83,26)]
                out.print(rs2.getInt("versionno"));
            // end
            // HTML // begin [file="/emessenger/newproc.jsp";from=(83,28);to=(86,0)]
                out.write("\r\n</td>\r\n<td valign=bottom>\r\n");

            // end
            // begin [file="/emessenger/newproc.jsp";from=(86,3);to=(86,27)]
                out.print(rs2.getString("pubdate"));
            // end
            // HTML // begin [file="/emessenger/newproc.jsp";from=(86,29);to=(89,27)]
                out.write("\r\n</td>\r\n<td valign=bottom>\r\n<a title=\"Model Reference: ");

            // end
            // begin [file="/emessenger/newproc.jsp";from=(89,30);to=(89,54)]
                out.print(rs.getString("modelref"));
            // end
            // HTML // begin [file="/emessenger/newproc.jsp";from=(89,56);to=(89,73)]
                out.write("\" href=\"public/1/");

            // end
            // begin [file="/emessenger/newproc.jsp";from=(89,76);to=(89,121)]
                out.print(PsConv.c4FS(rs.getString("modelname").trim()));
            // end
            // HTML // begin [file="/emessenger/newproc.jsp";from=(89,123);to=(90,0)]
                out.write(".htm\">\r\n");

            // end
            // begin [file="/emessenger/newproc.jsp";from=(90,3);to=(90,28)]
                out.print(rs.getString("modelname"));
            // end
            // HTML // begin [file="/emessenger/newproc.jsp";from=(90,30);to=(95,0)]
                out.write("\r\n</a>\r\n</td>\r\n</tr>\r\n\r\n");

            // end
            // begin [file="/emessenger/newproc.jsp";from=(95,2);to=(104,0)]
                
                		}
                	}		
                
                    }
                catch (SQLException e)
                    {
                	PsDebug.fail("newcase.jsp: SQLException: "+e.getMessage());
                    }
            // end
            // HTML // begin [file="/emessenger/newproc.jsp";from=(104,2);to=(110,7)]
                out.write("\r\n</td>\r\n</tr>\r\n</table></center>\r\n\r\n</body>\r\n</html>");

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
