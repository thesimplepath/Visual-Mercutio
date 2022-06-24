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


public class termin$jsp extends HttpJspBase {


    static {
    }
    public termin$jsp( ) {
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

            // HTML // begin [file="/termin.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/termin.jsp";from=(1,112);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/termin.jsp";from=(2,26);to=(5,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/termin.jsp";from=(5,0);to=(5,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/termin.jsp";from=(5,53);to=(10,0)]
                out.write("\r\n<link href=\"css/doc.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n</head>\r\n\r\n<body>\r\n");

            // end
            // begin [file="/termin.jsp";from=(10,2);to=(55,0)]
                
                 PsApp.init();
                
                 String username=(String)session.getAttribute("USERNAME");
                 int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
                 int procid=	Integer.valueOf(request.getParameter( "PROCID" )).intValue();
                 int caseid=	Integer.valueOf(request.getParameter( "CASEID" )).intValue();
                 int transid=	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
                
                 String redirect=(String)request.getParameter( "REDIRECT" );
                
                try {
                	PsDbConn conn=PsDbMgr.newConnection();
                
                	//check approval (all mandatory delivs must have been completed)	
                	//TODO
                
                	//terminate the current procedure	
                	conn.sqlExecR("UPDATE pproctrans SET emplid="+userid+",statusid=98 WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
                
                
                	//manage dynamic attributes
                	 PsDebug.log("Save dynamic attributs");
                	 int nbr=	Integer.valueOf(request.getParameter( "NBR_INPUT" )).intValue(); 
                	
                	 for (int i=1;i<=nbr;i++)
                	 {
                		int modelid=1;
                		String attribdefid=request.getParameter( "CTL2_"+i );
                		String mval=request.getParameter( "CTL_"+i );
                		conn.sqlExec("INSERT INTO pinputdata VALUES("+modelid+","+procid+","+attribdefid+","+caseid+","+transid+",'"+mval+"',"+conn.now()+")");
                	 }
                
                    }
                catch (SQLException e)
                    {
                	PsDebug.fail("deliv.jsp: SQLException: "+e.getMessage());
                    }
                
                out.println("<script language=JavaScript>");
                out.println("<!--");
                out.println("document.location=\""+redirect+"\";");
                out.println("//-->");
                out.println("</script>");
                
            // end
            // HTML // begin [file="/termin.jsp";from=(55,2);to=(57,7)]
                out.write("\r\n</body>\r\n</html>");

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
