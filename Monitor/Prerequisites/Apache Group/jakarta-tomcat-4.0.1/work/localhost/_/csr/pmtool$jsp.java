package org.apache.jsp;

import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class pmtool$jsp extends HttpJspBase {


    static {
    }
    public pmtool$jsp( ) {
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

            // HTML // begin [file="/csr/pmtool.jsp";from=(0,31);to=(19,0)]
                out.write("\r\n<html>\r\n\t\t<head> \r\n\t\t<title>APIM Designer 1.0</title> \r\n\t\t<link href=\"css/style.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n\t\t<script language=JavaScript>\t\r\n\t\t<!--\r\n\t\tfunction newGw(mname,actionid)\r\n\t\t{\t\t\r\n\t\tmname=mname+\"-\"+top.nextGwId;\r\n\t\ttop.Apim.addGw(top.nextGwId,null,null,mname,actionid);\r\n\t\ttop.apimio.document.location=\"pmincgw.jsp?GWID=\"+top.nextGwId+\"&ACTIONID=\"+actionid+\"&MNAME=\"+escape(mname);\r\n\t\t}\r\n\t\t//--> \r\n\t\t</script> \r\n\t</head> \r\n \r\n\r\n<body leftmargin=0 topmargin=0 bgcolor=#c0c0c0> \r\n");

            // end
            // begin [file="/csr/pmtool.jsp";from=(19,2);to=(32,0)]
                
                String jdbcDSN="jdbc:microsoft:sqlserver://rsc66:1433;databasename=apim;";
                String jdbcLogin="sa";
                String jdbcPassword="";
                
                 try
                 {
                	// Load the driver class
                	Class.forName("com.microsoft.jdbc.sqlserver.SQLServerDriver");
                	
                	Connection conn = DriverManager.getConnection(jdbcDSN,jdbcLogin,jdbcPassword);
                	Statement stmt=conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,ResultSet.CONCUR_READ_ONLY);
                	ResultSet rs=stmt.executeQuery("SELECT * FROM ATaction WHERE idpanel="+request.getParameter("PANEL"));
            // end
            // HTML // begin [file="/csr/pmtool.jsp";from=(32,2);to=(34,0)]
                out.write("\r\n<table cellspacing=\"2\" cellpadding=\"2\" border=0>\r\n");

            // end
            // begin [file="/csr/pmtool.jsp";from=(34,2);to=(37,0)]
                
                	while (rs.next())
                	{
            // end
            // HTML // begin [file="/csr/pmtool.jsp";from=(37,2);to=(40,27)]
                out.write("\r\n<tr>\r\n<td valign=middle>\r\n<a href='javascript:newGw(\"");

            // end
            // begin [file="/csr/pmtool.jsp";from=(40,30);to=(40,51)]
                out.print(rs.getString("mname"));
            // end
            // HTML // begin [file="/csr/pmtool.jsp";from=(40,53);to=(40,55)]
                out.write("\",");

            // end
            // begin [file="/csr/pmtool.jsp";from=(40,58);to=(40,82)]
                out.print(rs.getString("idaction"));
            // end
            // HTML // begin [file="/csr/pmtool.jsp";from=(40,84);to=(40,106)]
                out.write(");'><img src=\"img/ico/");

            // end
            // begin [file="/csr/pmtool.jsp";from=(40,109);to=(40,129)]
                out.print(rs.getString("pic") );
            // end
            // HTML // begin [file="/csr/pmtool.jsp";from=(40,131);to=(43,27)]
                out.write("\" alt=\"\" border=0></a>\r\n</td>\r\n<td valign=middle>\r\n<a href='javascript:newGw(\"");

            // end
            // begin [file="/csr/pmtool.jsp";from=(43,30);to=(43,51)]
                out.print(rs.getString("mname"));
            // end
            // HTML // begin [file="/csr/pmtool.jsp";from=(43,53);to=(43,55)]
                out.write("\",");

            // end
            // begin [file="/csr/pmtool.jsp";from=(43,58);to=(43,82)]
                out.print(rs.getString("idaction"));
            // end
            // HTML // begin [file="/csr/pmtool.jsp";from=(43,84);to=(44,0)]
                out.write(");'>\r\n");

            // end
            // begin [file="/csr/pmtool.jsp";from=(44,3);to=(44,24)]
                out.print(rs.getString("mname"));
            // end
            // HTML // begin [file="/csr/pmtool.jsp";from=(44,26);to=(48,0)]
                out.write("\r\n</a>\r\n</td>\r\n</tr>\r\n");

            // end
            // begin [file="/csr/pmtool.jsp";from=(48,2);to=(50,0)]
                
                	}	 
            // end
            // HTML // begin [file="/csr/pmtool.jsp";from=(50,2);to=(52,0)]
                out.write("\r\n</table>\r\n");

            // end
            // begin [file="/csr/pmtool.jsp";from=(52,2);to=(63,0)]
                
                
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
            // HTML // begin [file="/csr/pmtool.jsp";from=(63,2);to=(68,0)]
                out.write("\r\n</body> \r\n</html> \r\n\r\n\r\n");

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
