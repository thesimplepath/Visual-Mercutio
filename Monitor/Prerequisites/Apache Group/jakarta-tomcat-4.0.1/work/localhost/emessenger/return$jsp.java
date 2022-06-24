package org.apache.jsp;

import java.util.*;
import java.lang.*;
import java.sql.*;
import PsApp;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsConfig;
import PsDebug;
import PsWorkGroup;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class return$jsp extends HttpJspBase {


    static {
    }
    public return$jsp( ) {
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

            // HTML // begin [file="/return.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/return.jsp";from=(1,115);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/return.jsp";from=(2,26);to=(5,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/return.jsp";from=(5,0);to=(5,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/return.jsp";from=(5,53);to=(16,0)]
                out.write("\r\n<link href=\"css/doc.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n<script language=JavaScript src=\"js/pss.js\"></script>\r\n\r\n<script language=JavaScript>\r\n<!--\r\n//-->\r\n</script>\r\n</head>\r\n\r\n<body>\r\n");

            // end
            // begin [file="/return.jsp";from=(16,2);to=(84,0)]
                
                 PsApp.init();
                
                 String username=(String)session.getAttribute("USERNAME");
                 int modelid=1;
                 int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
                 int procid=	Integer.valueOf(request.getParameter( "PROCID" )).intValue();
                 int caseid=	Integer.valueOf(request.getParameter( "CASEID" )).intValue();
                 int transid=	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
                 String redirect=	(String)request.getParameter( "REDIRECT" );
                 String msg=		(String)request.getParameter( "MSG" );
                
                out.println("Retour a l'envoyeur...<br>");
                
                try {
                	PsDbConn conn=PsDbMgr.newConnection();
                	PsDbConn conn2=PsDbMgr.newConnection();
                	ResultSet rs;
                	ResultSet rs2;
                
                	rs=conn.sqlQueryR("SELECT * FROM pproctransfrom WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
                
                	boolean foundParent=false;
                
                	while (rs.next())
                	{			
                		foundParent=true;
                
                		//process history
                		conn2.sqlExecR("UPDATE pproctrans SET emplid="+userid+",statusid=0 WHERE procid="+rs.getInt("refprocid")+" AND caseid="+caseid+" AND transid="+transid);		
                		PsDebug.log("Return.jsp: Sent to "+rs.getInt("refprocid"));
                
                		//text
                		 if (msg!=null && msg.length()>0)
                		 {
                			rs2=conn2.sqlQueryR("SELECT * FROM pproctranstxt WHERE modelid="+modelid+" AND procid="+rs.getInt("refprocid")+" AND caseid="+caseid+" AND transid="+transid);
                			if (rs2.next()==true)	
                				conn2.sqlExec("UPDATE pproctranstxt SET msg='"+PsDbConn.cnv_sql(msg)+"' WHERE modelid="+modelid+" AND procid="+rs.getInt("refprocid")+" AND caseid="+caseid+" AND transid="+transid);	
                			else
                				conn2.sqlExec("INSERT INTO pproctranstxt VALUES ("+modelid+","+rs.getInt("refprocid")+","+caseid+","+transid+",'"+PsDbConn.cnv_sql(msg)+"')");
                		}
                	}
                	if (foundParent==true)
                	{
                		out.println("Remove current process "+procid+"<br>");
                		conn2.sqlExecR("DELETE FROM pproctrans WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
                		conn2.sqlExecR("DELETE FROM pproctransfrom WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
                		conn2.sqlExecR("DELETE FROM pdelivstatus WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
                		conn2.sqlExecR("DELETE FROM ptaskstatus WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
                		conn2.sqlExecR("DELETE FROM preferencestatus WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
                		conn2.sqlExecR("DELETE FROM psystemstatus WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
                
                	}
                	else
                	{
                		out.println("Pas de procedure precedentes... retour du travail impossible!<br>");
                	}	
                    }
                catch (SQLException e)
                    {
                	PsDebug.fail("return.jsp: SQLException: "+e.getMessage());
                    }
                
                out.println("<script language=JavaScript>");
                out.println("<!--");
                out.println("document.location=\""+redirect+"\";");
                out.println("//-->");
                out.println("</script>");
            // end
            // HTML // begin [file="/return.jsp";from=(84,2);to=(86,7)]
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
