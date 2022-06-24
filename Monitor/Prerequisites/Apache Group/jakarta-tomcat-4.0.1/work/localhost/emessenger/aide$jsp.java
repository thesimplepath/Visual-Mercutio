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


public class aide$jsp extends HttpJspBase {


    static {
    }
    public aide$jsp( ) {
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

            // HTML // begin [file="/aide.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/aide.jsp";from=(1,26);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/aide.jsp";from=(2,31);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/aide.jsp";from=(3,28);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/aide.jsp";from=(4,29);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/aide.jsp";from=(5,28);to=(6,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/aide.jsp";from=(6,29);to=(8,0)]
                out.write("\r\n<body>\r\n");

            // end
            // begin [file="/aide.jsp";from=(8,2);to=(27,0)]
                
                try {
                	PsDebug.log("Delete all cases from database");
                	PsDbConn conn=PsDbMgr.newConnection();
                	conn.sqlExecR("delete from pcase");
                	conn.sqlExecR("delete from ptrans");
                	conn.sqlExecR("delete from pproctrans");
                	conn.sqlExecR("delete from pattrib");
                	conn.sqlExecR("delete from pproctransfrom");
                	conn.sqlExecR("delete from pdelivlateralstate");
                	conn.sqlExecR("delete from pdelivstatus");
                	conn.sqlExecR("delete from ptaskstatus");
                	conn.sqlExecR("delete from pdecisionstatus");
                	conn.sqlExecR("delete from pinfostatus");
                    }
                 catch (SQLException e)
                    {
                	PsDebug.fail("aide.jsp: SQLException: "+e.getMessage());
                    }
            // end
            // HTML // begin [file="/aide.jsp";from=(27,2);to=(29,14)]
                out.write("\r\nDatabase cleaned !\r\n</body></html>");

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
