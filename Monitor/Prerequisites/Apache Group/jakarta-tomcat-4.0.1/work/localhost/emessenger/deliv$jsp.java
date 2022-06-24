package org.apache.jsp;

import java.util.*;
import java.lang.*;
import PsWf;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsApp;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class deliv$jsp extends HttpJspBase {


    static {
    }
    public deliv$jsp( ) {
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

            // HTML // begin [file="/deliv.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/deliv.jsp";from=(1,80);to=(4,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/deliv.jsp";from=(4,0);to=(4,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/deliv.jsp";from=(4,53);to=(9,0)]
                out.write("\r\n<link href=\"css/doc.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n</head>\r\n\r\n<body>\r\n");

            // end
            // begin [file="/deliv.jsp";from=(9,2);to=(35,0)]
                
                 String username=(String)session.getAttribute("USERNAME");
                 int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
                 int procid=	Integer.valueOf(request.getParameter( "PROCID" )).intValue();
                 int caseid=	Integer.valueOf(request.getParameter( "CASEID" )).intValue();
                 int transid=	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
                 int delivid=	Integer.valueOf(request.getParameter( "DELIVID" )).intValue();
                
                 int lat=	Integer.valueOf(request.getParameter( "LATERAL" )).intValue(); //0=no,1=yes
                 String redirect=(String)request.getParameter( "REDIRECT" );
                
                 PsWf.doSendDeliv(caseid,procid,transid,userid,delivid,lat);
                
                 PsApp.init();
                
                 //manage dynamic attributes
                 PsDebug.log("Save dynamic attributs");
                 int nbr=	Integer.valueOf(request.getParameter( "NBR_INPUT" )).intValue(); 
                 PsDbConn conn=PsDbMgr.newConnection();
                 for (int i=1;i<=nbr;i++)
                 {
                	int modelid=1;
                	String attribdefid=request.getParameter( "CTL2_"+i );
                	String mval=request.getParameter( "CTL_"+i );
                	conn.sqlExec("INSERT INTO pinputdata VALUES("+modelid+","+delivid+","+attribdefid+","+caseid+","+transid+",'"+mval+"',"+conn.now()+")");
                 }
            // end
            // HTML // begin [file="/deliv.jsp";from=(35,2);to=(40,19)]
                out.write("\r\n\r\n<script language=JavaScript>\r\n<!--\r\n//alert(document.location);\r\ndocument.location=\"");

            // end
            // begin [file="/deliv.jsp";from=(40,22);to=(40,30)]
                out.print(redirect);
            // end
            // HTML // begin [file="/deliv.jsp";from=(40,32);to=(40,41)]
                out.write("&SESSION=");

            // end
            // begin [file="/deliv.jsp";from=(40,44);to=(40,59)]
                out.print(session.getId());
            // end
            // HTML // begin [file="/deliv.jsp";from=(40,61);to=(45,7)]
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
