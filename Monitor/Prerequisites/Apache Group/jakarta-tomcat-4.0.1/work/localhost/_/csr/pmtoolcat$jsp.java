package org.apache.jsp;

import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class pmtoolcat$jsp extends HttpJspBase {


    static {
    }
    public pmtoolcat$jsp( ) {
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

            // HTML // begin [file="/csr/pmtoolcat.jsp";from=(0,31);to=(25,0)]
                out.write("\r\n<html> \r\n\t<head> \r\n\t\t<title>APIM Designer 1.0</title> \r\n\t\t<link href=\"css/style.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n\t\t<script language=JavaScript>\r\n\t\t<!--\r\n\t\tfunction window.onresize()\r\n\t\t{\r\n\t\t\tdocument.FRM.CAT.style.width=document.body.offsetWidth+2;\r\n\t\t} \r\n\r\n\t\tfunction onSelect(vv)\r\n\t\t{\r\n\t\t\ttop.apimtoolkit.document.location=\"pmtool.jsp?PANEL=\"+vv;\r\n\t\t}\r\n\t\t//--> \r\n\t\t</script> \r\n\t</head> \r\n \r\n\r\n<body leftmargin=0 topmargin=0\" bgcolor=#c0c0c0> \r\n<form action=\"javascript:onAction();\" name=\"FRM\">\r\n<select name=\"CAT\" style=\"width:142;\" onchange=\"javascript:onSelect(FRM.CAT.value)\">\r\n\r\n");

            // end
            // begin [file="/csr/pmtoolcat.jsp";from=(25,2);to=(37,0)]
                
                try
                 {
                  // Load the driver class
                  Class.forName("com.microsoft.jdbc.sqlserver.SQLServerDriver");
                	
                  Connection conn = DriverManager.getConnection("jdbc:microsoft:sqlserver://rsc66:1433;databasename=apim;","sa","");
                  Statement stmt=conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,ResultSet.CONCUR_READ_ONLY);
                  ResultSet rs=stmt.executeQuery("SELECT * FROM ATactionpanel");
                  
                  while (rs.next())
                  {
            // end
            // HTML // begin [file="/csr/pmtoolcat.jsp";from=(37,2);to=(38,15)]
                out.write("\r\n<option value=\"");

            // end
            // begin [file="/csr/pmtoolcat.jsp";from=(38,18);to=(38,38)]
                out.print(rs.getInt("idpanel"));
            // end
            // HTML // begin [file="/csr/pmtoolcat.jsp";from=(38,40);to=(38,42)]
                out.write("\">");

            // end
            // begin [file="/csr/pmtoolcat.jsp";from=(38,45);to=(38,66)]
                out.print(rs.getString("mname"));
            // end
            // HTML // begin [file="/csr/pmtoolcat.jsp";from=(38,68);to=(39,0)]
                out.write("</option>\r\n");

            // end
            // begin [file="/csr/pmtoolcat.jsp";from=(39,2);to=(50,0)]
                
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
            // HTML // begin [file="/csr/pmtoolcat.jsp";from=(50,2);to=(58,0)]
                out.write("\r\n\r\n</select>\r\n</form>\r\n</body> \r\n</html> \r\n\r\n\r\n");

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
