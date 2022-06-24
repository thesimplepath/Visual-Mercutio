package org.apache.jsp;

import java.util.*;
import java.lang.*;
import java.sql.*;
import PsApp;
import PsDbMgr;
import PsDbConn;
import PsWf;
import PsDebug;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class chief$jsp extends HttpJspBase {


    static {
    }
    public chief$jsp( ) {
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

            // HTML // begin [file="/chief.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/chief.jsp";from=(1,32);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/chief.jsp";from=(2,32);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/chief.jsp";from=(3,31);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/chief.jsp";from=(4,26);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/chief.jsp";from=(5,28);to=(6,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/chief.jsp";from=(6,29);to=(7,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/chief.jsp";from=(7,25);to=(8,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/chief.jsp";from=(8,28);to=(11,0)]
                out.write("\r\n\r\n<head>\r\n");

            // end
            // begin [file="/chief.jsp";from=(11,0);to=(11,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/chief.jsp";from=(11,53);to=(17,0)]
                out.write("\r\n<link href=\"css/doc.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n</head>\r\n\r\n<body>\r\n");

            // end
            // begin [file="/chief.jsp";from=(17,2);to=(49,0)]
                
                 String username=(String)session.getAttribute("USERNAME");
                 int modelid=1;//TODO
                 int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
                 int procid=	Integer.valueOf(request.getParameter( "PROCID" )).intValue();
                 int caseid=	Integer.valueOf(request.getParameter( "CASEID" )).intValue();
                 int transid=	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
                 String msg=	(String)request.getParameter( "MSG" );
                 String redirect=	(String)request.getParameter( "REDIRECT" );
                
                 //remise au chef
                 PsWf.doChiefReturn(caseid,procid,transid,userid);
                
                 try
                   {
                	 //text
                	 if (msg!=null)
                	 {
                		PsApp.init();
                		PsDbConn conn=PsDbMgr.newConnection();
                		ResultSet rs=conn.sqlQueryR("SELECT * FROM pproctranstxt WHERE modelid="+modelid+" AND procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
                		if (rs.next()==true)
                			conn.sqlExec("UPDATE pproctranstxt SET msg='"+PsDbConn.cnv_sql(msg)+"' WHERE modelid="+modelid+" AND procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
                		else
                			conn.sqlExec("INSERT INTO pproctranstxt VALUES ("+modelid+","+procid+","+caseid+","+transid+",'"+PsDbConn.cnv_sql(msg)+"')");
                	 }
                   }
                catch (SQLException e)
                    {
                	PsDebug.fail("return.jsp: SQLException: "+e.getMessage());
                    }
                
            // end
            // HTML // begin [file="/chief.jsp";from=(49,2);to=(53,19)]
                out.write("\r\n\r\n<script language=JavaScript>\r\n<!--\r\ndocument.location=\"");

            // end
            // begin [file="/chief.jsp";from=(53,22);to=(53,30)]
                out.print(redirect);
            // end
            // HTML // begin [file="/chief.jsp";from=(53,32);to=(58,7)]
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
