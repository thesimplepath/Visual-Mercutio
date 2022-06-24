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

            // HTML // begin [file="/pss/deliv.jsp";from=(0,32);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/deliv.jsp";from=(1,32);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/deliv.jsp";from=(2,31);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/deliv.jsp";from=(3,26);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/deliv.jsp";from=(4,28);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/deliv.jsp";from=(5,29);to=(6,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/deliv.jsp";from=(6,28);to=(7,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/deliv.jsp";from=(7,29);to=(8,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/deliv.jsp";from=(8,32);to=(9,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/deliv.jsp";from=(9,25);to=(17,0)]
                out.write("\r\n\r\n<html>\r\n<head>\r\n<link href=\"css/doc.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n<script language=JavaScript src=\"js/pss.js\"></script>\r\n<script language=JavaScript>\r\n<!--\r\n");

            // end
            // begin [file="/pss/deliv.jsp";from=(17,2);to=(25,0)]
                
                //session check
                 String xusername=(String)session.getAttribute( "USERNAME");
                 int    userrole;
                 if (xusername==null) 
                   out.println("alert('Not logged');");
                 else
                   userrole=Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();
            // end
            // HTML // begin [file="/pss/deliv.jsp";from=(25,2);to=(36,0)]
                out.write("\r\n//-->\r\n</script>\r\n\r\n<script language=JavaScript>\r\n<!--\r\n//-->\r\n</script>\r\n</head>\r\n\r\n<body>\r\n");

            // end
            // begin [file="/pss/deliv.jsp";from=(36,2);to=(101,0)]
                
                 PsApp.init();
                
                 String username=(String)session.getAttribute("USERNAME");
                 int userid=	Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
                 int procid=	Integer.valueOf(request.getParameter( "PROCID" )).intValue();
                 int caseid=	Integer.valueOf(request.getParameter( "CASEID" )).intValue();
                 int transid=	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
                 int delivid=	Integer.valueOf(request.getParameter( "DELIVID" )).intValue();
                
                 int lat=	Integer.valueOf(request.getParameter( "LATERAL" )).intValue(); //0=no,1=yes
                 
                
                out.println("Envoi du livrable...<br>");
                
                try {
                	PsDbConn conn=PsDbMgr.newConnection();
                	ResultSet rs;
                
                	rs=conn.sqlQueryR("SELECT * FROM pdeliv WHERE delivid="+delivid+" AND procidsrc="+procid);
                
                	if (rs.next()==true)
                	{			
                
                		int proctrgid=rs.getInt("procidtrg");
                
                		//to do list for laterals
                		//new lateral
                		if (lat==1)
                		{
                			PsWf wf=new PsWf();			
                			int delividret=wf.getLateralReturn(procid,delivid);
                			conn.sqlExecR("INSERT INTO pdelivlateralstate VALUES("+procid+","+caseid+","+transid+","+delividret+",0,"+conn.now()+")");
                		}
                		else
                		{
                			rs=conn.sqlQueryR("SELECT * FROM pdelivlateralstate WHERE caseid="+caseid+" AND transid="+transid+" AND delivid="+delivid);
                			if (rs.next()==true)
                			{
                out.println("<h1>Retour de livrable !!!</h1>");
                				conn.sqlExecR("UPDATE pdelivlateralstate set openclose=1 WHERE caseid="+caseid+" AND transid="+transid+" AND delivid="+delivid);
                			}
                			
                		}
                		//process history
                		conn.sqlExecR("INSERT INTO pproctransfrom VALUES ("+proctrgid+","+caseid+","+transid+","+procid+")");
                
                		//change status to "done" (except for laterals)
                		if (lat==0)
                			conn.sqlExecR("UPDATE pproctrans SET emplid="+userid+",statusid=98 WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid);
                
                		boolean returnLateral=false;
                		rs=conn.sqlQueryR("SELECT count(*) FROM pproctrans WHERE procid="+proctrgid+" AND caseid="+caseid+" AND transid="+transid);
                		if (rs.next()==true)
                			returnLateral=true;
                if (returnLateral==true) out.println("Fin d'execution du retour lateral<br>");//TODO
                
                		conn.sqlExecR("INSERT INTO pproctrans VALUES("+proctrgid+","+caseid+","+transid+",0,"+userid+",0,"+procid+")");
                
                	}
                    }
                catch (SQLException e)
                    {
                	PsDebug.fail("deliv.jsp: SQLException: "+e.getMessage());
                    }
            // end
            // HTML // begin [file="/pss/deliv.jsp";from=(101,2);to=(103,7)]
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
