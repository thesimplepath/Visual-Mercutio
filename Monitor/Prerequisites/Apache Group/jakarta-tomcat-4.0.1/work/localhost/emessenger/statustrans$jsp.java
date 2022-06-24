package org.apache.jsp;

import PsApp;
import java.sql.*;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsConfig;
import PsWf;
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

            // HTML // begin [file="/statustrans.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/statustrans.jsp";from=(1,76);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/statustrans.jsp";from=(2,26);to=(4,0)]
                out.write("\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/statustrans.jsp";from=(4,0);to=(4,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/statustrans.jsp";from=(4,53);to=(7,0)]
                out.write("\r\n<SCRIPT LANGUAGE=\"JavaScript\">\r\n<!--\t\r\n");

            // end
            // begin [file="/statustrans.jsp";from=(7,2);to=(21,0)]
                
                  PsApp.init();
                
                  int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
                
                  int mode=             Integer.valueOf(request.getParameter( "MODE" )).intValue();
                  int procid = 		Integer.valueOf(request.getParameter( "PROCID" )).intValue();
                  int caseid = 		Integer.valueOf(request.getParameter( "CASEID" )).intValue();
                  int transid = 	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
                  int statusid = 	Integer.valueOf(request.getParameter( "STATUSID" )).intValue();
                
                  String redir= 	request.getParameter("REDIRECT");
                  
                  PsWf.doChangeStatusTrans(mode,caseid,procid,transid,userid,statusid);
            // end
            // HTML // begin [file="/statustrans.jsp";from=(21,2);to=(23,21)]
                out.write("\r\n\r\ndocument.location = \"");

            // end
            // begin [file="/statustrans.jsp";from=(23,24);to=(23,29)]
                out.print(redir);
            // end
            // HTML // begin [file="/statustrans.jsp";from=(23,31);to=(27,20)]
                out.write("\";\r\n// --> \r\n</SCRIPT>\r\n\r\n<body></body></html>");

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
