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


public class newproc2$jsp extends HttpJspBase {


    static {
    }
    public newproc2$jsp( ) {
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

            // HTML // begin [file="/emessenger2002/newproc2.jsp";from=(0,26);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc2.jsp";from=(1,31);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc2.jsp";from=(2,28);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc2.jsp";from=(3,29);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc2.jsp";from=(4,28);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc2.jsp";from=(5,29);to=(6,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc2.jsp";from=(6,37);to=(14,0)]
                out.write("\r\n<html>\r\n<head>\r\n<LINK href=\"css/global.css\" rel=STYLESHEET type=\"text/css\">\r\n<script language=JavaScript src=\"js/pss.js\"></script>\r\n</head>\r\n<BODY text=#000000 vLink=#666666 link=#003399 bgColor=#ffffff leftMargin=0 topMargin=0 MARGINHEIGHT=0 MARGINWIDTH=0>\r\n<TABLE width=\"100%\" border=0>\r\n");

            // end
            // begin [file="/emessenger2002/newproc2.jsp";from=(14,2);to=(74,0)]
                
                  PsApp.init();
                
                  int caseattachid = 	Integer.valueOf(request.getParameter( "CASEATTACHID" )).intValue();
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
                
                  out.println("<TBODY>");
                  out.println("<TR>");
                  out.println(" <TD width=\"11%\">&nbsp;</TD>");
                  out.println(" <TD class=NormalBlack vAlign=top width=\"89%\">Nouveau cas créé: "+casename+"</TD>");
                  out.println(" <TR>");
                  out.println(" <TD width=\"11%\" height=454>&nbsp;</TD>");
                  out.println(" <TD class=NormalBlack vAlign=top width=\"89%\" height=454>");
                  out.println("   <P>&nbsp;</P>");
                  out.println("   <P>Le message a été envoyé dans la boîte de travail de la procédure:</P>");
                
                 try {
                	PsDbConn conn=PsDbMgr.newConnection();
                
                	ResultSet rs=conn.sqlQueryR("SELECT * FROM pdeliv WHERE procidsrc="+procid);
                	rs.next();
                	out.println("   <P><B>"+rs.getString("delivname")+"</B></P></TD></TR>");
                
                	int caseid;
                	if (caseattachid<0)
                		caseid=conn.nextVal("PCASE");
                	else
                		caseid=caseattachid;
                
                	int attribid=conn.nextVal("PATTRIB");
                	String txindate=conn.now();
                
                	if (caseattachid==-1)
                		conn.sqlExecR("INSERT INTO pcase VALUES ("+caseid+","+txindate+",'"+casename+"')");
                	conn.sqlExecR("INSERT INTO ptrans VALUES ("+caseid+","+transid+","+parenttransid+",'"+transname+"',"+globalyn+","+attribid+",0)");
                	conn.sqlExecR("INSERT INTO pproctrans VALUES ("+procid+","+caseid+","+transid+",0,"+empid+",0,"+fromproc+","+conn.now()+")");
                
                  	for (int i=0;i<qty;i++)
                	{
                	    int segid=		Integer.valueOf(request.getParameter( "SEG"+i)).intValue();
                	    int attribdefid=	Integer.valueOf(request.getParameter( "ATTRIBID"+i)).intValue();
                	    String mkey=	request.getParameter( "KEY"+i );
                	    String mval=	request.getParameter( "VAL"+i );
                	conn.sqlExecR("INSERT INTO pattrib VALUES ("+caseid+","+transid+","+segid+","+attribid+","+attribdefid+",'"+mkey+"','"+mval+"')");
                	}	
                    }
                 catch (SQLException e)
                    {
                	PsDebug.fail("newproc2.jsp: SQLException: "+e.getMessage());
                    }
            // end
            // HTML // begin [file="/emessenger2002/newproc2.jsp";from=(74,2);to=(81,7)]
                out.write("\r\n</tbody></table>\r\n\r\n<SCRIPT language=javascript>\r\n//top.menu.showTab(4);\r\n</script>\r\n</body>\r\n</html>");

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
