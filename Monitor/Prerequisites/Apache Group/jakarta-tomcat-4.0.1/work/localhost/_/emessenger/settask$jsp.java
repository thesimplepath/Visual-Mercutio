package org.apache.jsp;

import java.util.*;
import java.lang.*;
import PsWf;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class settask$jsp extends HttpJspBase {


    static {
    }
    public settask$jsp( ) {
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

            // HTML // begin [file="/emessenger/settask.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/emessenger/settask.jsp";from=(1,49);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger/settask.jsp";from=(2,26);to=(5,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/emessenger/settask.jsp";from=(5,0);to=(5,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/emessenger/settask.jsp";from=(5,53);to=(11,0)]
                out.write("\r\n<link href=\"css/doc.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n<script language=JavaScript src=\"js/pss.js\"></script>\r\n</head>\r\n\r\n<body>\r\n");

            // end
            // begin [file="/emessenger/settask.jsp";from=(11,2);to=(22,0)]
                
                 //String username=(String)session.getAttribute("USERNAME");
                 //int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
                 int procid=	Integer.valueOf(request.getParameter( "PROCID" )).intValue();
                 int caseid=	Integer.valueOf(request.getParameter( "CASEID" )).intValue();
                 int transid=	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
                 int attribid=  Integer.valueOf(request.getParameter( "ATTRIBID" )).intValue();
                 String redirect=	(String)request.getParameter( "REDIRECT" );
                
                 PsWf.setTaskStatus(caseid,procid,transid,attribid);
                
            // end
            // HTML // begin [file="/emessenger/settask.jsp";from=(22,2);to=(26,21)]
                out.write("\r\n\r\n<script language=JavaScript>\r\n<!--\r\n//document.location=\"");

            // end
            // begin [file="/emessenger/settask.jsp";from=(26,24);to=(26,32)]
                out.print(redirect);
            // end
            // HTML // begin [file="/emessenger/settask.jsp";from=(26,34);to=(31,7)]
                out.write("\";\r\n//-->\r\n</script>\r\n\r\n</body>\r\n</html>");

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
