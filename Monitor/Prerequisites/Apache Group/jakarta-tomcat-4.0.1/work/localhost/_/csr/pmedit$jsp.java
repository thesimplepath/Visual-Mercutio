package org.apache.jsp;

import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class pmedit$jsp extends HttpJspBase {


    static {
    }
    public pmedit$jsp( ) {
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

            // HTML // begin [file="/csr/pmedit.jsp";from=(0,31);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(1,25);to=(23,0)]
                out.write("\r\n<html> \r\n\t<head> \r\n\t\t<title>APIM Designer 1.0</title> \r\n\t\t<link href=\"css/style.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n\t\t<script language=JavaScript>\r\n\t\t<!--\r\n \r\n\t\t//--> \r\n\t\t</script> \r\n\t</head> \r\n \r\n\r\n<body leftmargin=0 topmargin=0 bgcolor=white onload=\"javascript:LoadDta();\"> \r\n<APPLET NAME=APIM ID=APIM CODE=Apim2.class ARCHIVE=class/apim.jar WIDTH=4096 HEIGHT=4096>\r\n</APPLET>\r\n\r\n<script language=JavaScript>\r\n<!--\r\nfunction LoadDta() { \r\n APIM.doReset();\t\r\n\r\n");

            // end
            // begin [file="/csr/pmedit.jsp";from=(23,2);to=(37,0)]
                
                String viewid = request.getParameter( "VIEWID" );
                session = request.getSession();
                session.setAttribute( "VIEWID", viewid );
                
                try
                 {
                	// Load the driver class
                	Class.forName("com.microsoft.jdbc.sqlserver.SQLServerDriver");
                	
                	Connection conn = DriverManager.getConnection("jdbc:microsoft:sqlserver://rsc66:1433;databasename=apim;","sa","");
                	Statement stmt=conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,ResultSet.CONCUR_READ_ONLY);
                	ResultSet rs=stmt.executeQuery("SELECT ival FROM ATidentity where iname='ATgw'");
                	rs.next();
            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(37,2);to=(38,14)]
                out.write("\r\n\ttop.nextGwId=");

            // end
            // begin [file="/csr/pmedit.jsp";from=(38,17);to=(38,34)]
                out.print(rs.getInt("ival"));
            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(38,36);to=(39,0)]
                out.write("+1;\r\n");

            // end
            // begin [file="/csr/pmedit.jsp";from=(39,2);to=(45,0)]
                
                //actions
                	rs=stmt.executeQuery("SELECT * FROM ATaction");
                
                	while (rs.next())
                	{
            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(45,2);to=(46,19)]
                out.write("\r\ntop.Apim.addAction(");

            // end
            // begin [file="/csr/pmedit.jsp";from=(46,22);to=(46,43)]
                out.print(rs.getInt("idaction"));
            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(46,45);to=(46,56)]
                out.write(",unescape(\"");

            // end
            // begin [file="/csr/pmedit.jsp";from=(46,59);to=(46,80)]
                out.print(rs.getString("mname"));
            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(46,82);to=(46,86)]
                out.write("\"),\"");

            // end
            // begin [file="/csr/pmedit.jsp";from=(46,89);to=(46,108)]
                out.print(rs.getString("pic"));
            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(46,110);to=(47,0)]
                out.write("\");\r\n");

            // end
            // begin [file="/csr/pmedit.jsp";from=(47,2);to=(55,0)]
                
                	}
                
                //gw
                	rs=stmt.executeQuery("SELECT * FROM ATgw,ATxy WHERE ATgw.idgw=ATxy.idgw AND ATgw.idview="+viewid);
                
                	while (rs.next())
                	{
            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(55,2);to=(56,15)]
                out.write("\r\ntop.Apim.addGw(");

            // end
            // begin [file="/csr/pmedit.jsp";from=(56,18);to=(56,35)]
                out.print(rs.getInt("idgw"));
            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(56,37);to=(56,38)]
                out.write(",");

            // end
            // begin [file="/csr/pmedit.jsp";from=(56,41);to=(56,56)]
                out.print(rs.getInt("xx"));
            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(56,58);to=(56,59)]
                out.write(",");

            // end
            // begin [file="/csr/pmedit.jsp";from=(56,62);to=(56,77)]
                out.print(rs.getInt("yy"));
            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(56,79);to=(56,90)]
                out.write(",unescape(\"");

            // end
            // begin [file="/csr/pmedit.jsp";from=(56,93);to=(56,114)]
                out.print(rs.getString("mname"));
            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(56,116);to=(56,119)]
                out.write("\"),");

            // end
            // begin [file="/csr/pmedit.jsp";from=(56,122);to=(56,143)]
                out.print(rs.getInt("idaction"));
            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(56,145);to=(57,0)]
                out.write(");\r\n");

            // end
            // begin [file="/csr/pmedit.jsp";from=(57,2);to=(65,0)]
                
                	}
                
                //links
                	rs=stmt.executeQuery("SELECT * FROM ATlink WHERE ATlink.idview="+viewid);
                
                	while (rs.next())
                	{
            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(65,2);to=(66,17)]
                out.write("\r\ntop.Apim.addLink(");

            // end
            // begin [file="/csr/pmedit.jsp";from=(66,20);to=(66,38)]
                out.print(rs.getInt("lfrom"));
            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(66,40);to=(66,41)]
                out.write(",");

            // end
            // begin [file="/csr/pmedit.jsp";from=(66,44);to=(66,60)]
                out.print(rs.getInt("lto"));
            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(66,62);to=(67,0)]
                out.write(");\r\n");

            // end
            // begin [file="/csr/pmedit.jsp";from=(67,2);to=(78,0)]
                
                	}
                 }
                 catch(ClassNotFoundException cnfe)
                 {
                	 System.err.println(cnfe);
                 }
                 catch(SQLException sqle)
                 {
                	 System.err.println(sqle);
                 }
            // end
            // HTML // begin [file="/csr/pmedit.jsp";from=(78,2);to=(88,0)]
                out.write("\r\n\r\n APIM.repaint();\r\n}\r\n//-->\r\n</script>\r\n</body> \r\n</html> \r\n\r\n\r\n");

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
