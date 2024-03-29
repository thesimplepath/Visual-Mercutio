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


public class newcasesend$jsp extends HttpJspBase {


    static {
    }
    public newcasesend$jsp( ) {
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

            // HTML // begin [file="/pss/newcasesend.jsp";from=(0,26);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/newcasesend.jsp";from=(1,31);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/newcasesend.jsp";from=(2,28);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/newcasesend.jsp";from=(3,29);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/newcasesend.jsp";from=(4,28);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/newcasesend.jsp";from=(5,29);to=(6,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/newcasesend.jsp";from=(6,37);to=(10,0)]
                out.write("\r\n<html>\r\n<body>\r\nNew transaction:<hr>\r\n");

            // end
            // begin [file="/pss/newcasesend.jsp";from=(10,2);to=(48,0)]
                
                  PsApp.init();
                
                  String casename =     request.getParameter("CASENAME" );
                  int procid = 		Integer.valueOf(request.getParameter( "PROCID" )).intValue();
                  int transid = 	Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
                  String transname = 	request.getParameter( "TRANSNAME" );
                  int parenttransid= 	Integer.valueOf(request.getParameter( "PARENTTRANSID" )).intValue();
                  int empid= 		Integer.valueOf(request.getParameter( "EMPID" )).intValue();
                  int statusid = 	Integer.valueOf(request.getParameter( "STATUSID" )).intValue();
                  int globalyn = 	Integer.valueOf(request.getParameter( "GLOBALYN" )).intValue();
                  int qty = 		Integer.valueOf(request.getParameter( "QTY" )).intValue();
                
                  int fromproc = 	Integer.valueOf(request.getParameter( "FROMPROC" )).intValue();
                
                 try {
                	PsDbConn conn=PsDbMgr.newConnection();
                	int caseid=conn.nextVal("PCASE");
                	int attribid=conn.nextVal("PATTRIB");
                	String txindate=conn.now();
                
                	conn.sqlExec("INSERT INTO pcase VALUES ("+caseid+","+txindate+",'"+casename+"')");
                	conn.sqlExec("INSERT INTO ptrans VALUES ("+caseid+","+transid+","+parenttransid+",'"+transname+"',"+globalyn+","+attribid+",0)");
                	conn.sqlExec("INSERT INTO pproctrans VALUES ("+procid+","+caseid+","+transid+",0,"+empid+",0,"+fromproc+")");
                
                  	for (int i=0;i<qty;i++)
                	{
                	    int segid=		Integer.valueOf(request.getParameter( "SEG"+i)).intValue();
                	    int attribdefid=	Integer.valueOf(request.getParameter( "ATTRIBID"+i)).intValue();
                	    String mkey=	request.getParameter( "KEY"+i );
                	    String mval=	request.getParameter( "VAL"+i );
                	conn.sqlExec("INSERT INTO pattrib VALUES ("+caseid+","+transid+","+segid+","+attribid+","+attribdefid+",'"+mkey+"','"+mval+"')");
                	}	
                    }
                 catch (SQLException e)
                    {
                	PsDebug.fail("newcasesend.jsp: SQLException: "+e.getMessage());
                    }
            // end
            // HTML // begin [file="/pss/newcasesend.jsp";from=(48,2);to=(50,14)]
                out.write("\r\n\r\n</body></html>");

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
