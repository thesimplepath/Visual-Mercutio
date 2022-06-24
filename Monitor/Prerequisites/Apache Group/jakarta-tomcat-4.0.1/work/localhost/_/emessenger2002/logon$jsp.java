package org.apache.jsp;

import PsApp;
import java.sql.*;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsConfig;
import PsAuthentication;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class logon$jsp extends HttpJspBase {


    static {
    }
    public logon$jsp( ) {
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

            // HTML // begin [file="/emessenger2002/logon.jsp";from=(0,26);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/logon.jsp";from=(1,31);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/logon.jsp";from=(2,28);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/logon.jsp";from=(3,29);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/logon.jsp";from=(4,28);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/logon.jsp";from=(5,29);to=(6,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/logon.jsp";from=(6,37);to=(10,0)]
                out.write("\r\n\r\n<html>\r\n<head>\r\n");

            // end
            // begin [file="/emessenger2002/logon.jsp";from=(10,2);to=(34,0)]
                
                 PsApp.init();
                 
                 session.setAttribute( "USERNAME",null);
                 session.setAttribute( "USERROLE","-1");
                 session.setAttribute( "USERID","-1");
                
                 String mlogin=request.getParameter( "LOGIN" );
                 String mpasswd=request.getParameter( "PASSWD" );
                
                 PsAuthentication auth=new PsAuthentication();
                 if (auth.logon(mlogin,mpasswd)==false)
                 {
                 	//not logged
                 	out.println("<meta HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=index.html\">");
                 }
                 else
                 {
                 	//logged
                 	session.setAttribute( "USERNAME",mlogin);
                 	session.setAttribute( "USERROLE",String.valueOf(auth.getRole()));
                	session.setAttribute( "USERID",  String.valueOf(auth.getId()));
                	out.println("<meta HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=main.htm\">");
                 }
            // end
            // HTML // begin [file="/emessenger2002/logon.jsp";from=(34,2);to=(39,7)]
                out.write("\r\n\r\n</head>\r\n<body>\r\n</body>\r\n</html>");

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
