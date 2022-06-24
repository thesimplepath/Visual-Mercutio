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


public class statustrans$jsp extends HttpJspBase {


    static {
    }
    public statustrans$jsp( ) {
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

            // HTML // begin [file="/emessenger2002/statustrans.jsp";from=(0,26);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/statustrans.jsp";from=(1,31);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/statustrans.jsp";from=(2,28);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/statustrans.jsp";from=(3,29);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/statustrans.jsp";from=(4,28);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/statustrans.jsp";from=(5,29);to=(9,0)]
                out.write("\r\n<html>\r\n<SCRIPT LANGUAGE=\"JavaScript\">\r\n<!--\t\r\n");

            // end
            // begin [file="/emessenger2002/statustrans.jsp";from=(9,2);to=(32,0)]
                
                  PsApp.init();
                
                  int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
                
                  int mode=             Integer.valueOf(request.getParameter( "MODE" )).intValue();
                  int procid = 		Integer.valueOf(request.getParameter( "CASEID" )).intValue();
                  int transid = 	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
                  int statusid = 	Integer.valueOf(request.getParameter( "STATUSID" )).intValue();
                  String redir= request.getParameter("REDIRECT");
                 try {
                	PsDbConn conn=PsDbMgr.newConnection();
                	if (mode==0)
                		conn.sqlExecR("UPDATE pproctrans SET statusid="+statusid+",emplid="+userid+" WHERE procid="+procid);
                	if (mode==1)
                		conn.sqlExecR("UPDATE pproctrans SET statusid="+statusid+",emplid="+userid+" WHERE procid="+procid+" AND transid="+transid);
                
                	out.println("var sUrl = \""+redir+"\";");
                    }
                 catch (SQLException e)
                    {
                	PsDebug.fail("statustrans.jsp: SQLException: "+e.getMessage());
                    }
            // end
            // HTML // begin [file="/emessenger2002/statustrans.jsp";from=(32,2);to=(38,20)]
                out.write("\r\n\r\ndocument.location = sUrl;\r\n// --> \r\n</SCRIPT>\r\n\r\n<body></body></html>");

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
