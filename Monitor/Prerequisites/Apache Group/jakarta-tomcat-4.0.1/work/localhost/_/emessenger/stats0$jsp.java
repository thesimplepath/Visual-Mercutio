package org.apache.jsp;

import PsApp;
import java.sql.*;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsConfig;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class stats0$jsp extends HttpJspBase {


    static {
    }
    public stats0$jsp( ) {
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

            // HTML // begin [file="/emessenger/stats0.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/emessenger/stats0.jsp";from=(1,71);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger/stats0.jsp";from=(2,26);to=(5,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/emessenger/stats0.jsp";from=(5,0);to=(5,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/emessenger/stats0.jsp";from=(5,53);to=(6,0)]
                out.write("\r\n");

            // end
            // begin [file="/emessenger/stats0.jsp";from=(6,2);to=(8,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/emessenger/stats0.jsp";from=(8,2);to=(9,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/emessenger/stats0.jsp";from=(9,19);to=(9,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/stats0.jsp";from=(9,29);to=(21,69)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n<link href=\"css/tree.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n\r\n<body>\r\n<TABLE width=\"100%\">\r\n<TR><TD width=\"2%\">&nbsp;</TD>\r\n<TD width=\"98%\">\r\n<TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/stats0.jsp";from=(21,72);to=(21,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/stats0.jsp";from=(21,82);to=(49,7)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"96%\"><NOBR><FONT class=menu>Statistiques:</FONT></NOBR></TD>\r\n        </TR>\r\n</TBODY>\r\n</TABLE>\r\n</TD></TR>\r\n<TR><TD width=\"2%\">&nbsp;</TD>\r\n<TD>\r\n<br>\r\n<script language=javaScript src=\"js/tree.js\"></script>\r\n<script language=JavaScript>\r\n<!--\r\n var m=new oMenu;\r\n m.add(1,0,'Analyse des stocks','stats100.jsp');\r\n\r\n m.setTarget(\"usr\");\r\n m.setIconDocument(\"img/doc.gif\");\r\n m.setIconCollapse(\"img/close.gif\");\r\n m.setIconExpand(\"img/open.gif\");\r\n\r\n m.gen(true);\r\n\r\n-->\r\n</script>\r\n</TD>\r\n</TR>\r\n</TABLE>\r\n</body>\r\n</html>");

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
