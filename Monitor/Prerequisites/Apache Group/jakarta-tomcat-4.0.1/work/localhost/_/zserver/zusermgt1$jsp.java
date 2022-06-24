package org.apache.jsp;

import PsApp;
import java.sql.*;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsConfig;
import PsConv;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class zusermgt1$jsp extends HttpJspBase {


    static {
    }
    public zusermgt1$jsp( ) {
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

            // HTML // begin [file="/zserver/zusermgt1.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/zserver/zusermgt1.jsp";from=(1,78);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/zserver/zusermgt1.jsp";from=(2,26);to=(5,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/zserver/zusermgt1.jsp";from=(5,0);to=(5,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/zserver/zusermgt1.jsp";from=(5,53);to=(6,0)]
                out.write("\r\n");

            // end
            // begin [file="/zserver/zusermgt1.jsp";from=(6,2);to=(8,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/zserver/zusermgt1.jsp";from=(8,2);to=(9,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/zserver/zusermgt1.jsp";from=(9,19);to=(9,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/zserver/zusermgt1.jsp";from=(9,29);to=(39,0)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n<link href=\"css/tree.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n\r\n<script language=javaScript src=\"js/tree.js\"></script>\r\n<script language=JavaScript>\r\n<!--\r\n function doAdd(parent)\r\n {\r\n\tname=window.prompt(\"Veuillez saisir le nom du nouveau groupe\",\"\");\r\n\tif (name==\"null\")\r\n\t\tname=\"\";\r\n\r\n\tdocument.writeln(\"<form name=frm action=\\\"zusermgt1.jsp\\\" method=POST>\");\r\n\tdocument.writeln(\"<input type=hidden name=MODE value=1>\");\r\n\tdocument.writeln(\"<input type=hidden name=GRPPARENT value=\"+parent+\">\");\r\n\tdocument.writeln(\"<input type=hidden name=GRPNAME value=\\\"\"+name+\"\\\">\");\r\n\tdocument.writeln(\"</form>\");\r\n\tdocument.writeln(\"<script language=JavaScript>\");\r\n\tdocument.writeln(\"frm.submit();\");\r\n\tdocument.writeln(\"</script>\");\r\n\t//document.location=\"zusermgt1.jsp?MODE=1&GRPPARENT=\"+parent+\"&GRPNAME=\"+escape(name);\r\n }\r\n\r\n function doDel(grpid)\r\n {\r\n\tdocument.location=\"zusermgt1.jsp?MODE=2&GRPID=\"+grpid;\r\n }\r\n\r\n var m=new oMenu;\r\n");

            // end
            // begin [file="/zserver/zusermgt1.jsp";from=(39,2);to=(96,0)]
                
                 PsApp.init();
                 
                 try {
                	String mode=request.getParameter( "MODE" );
                	String grpid=request.getParameter( "GRPID" );
                	String grpparent=request.getParameter( "GRPPARENT" );
                	String grpname=request.getParameter( "GRPNAME" );
                
                	PsDbConn co=PsDbMgr.newConnection();
                
                	if (mode!=null)
                	  {
                	   	if (mode.equals("1")==true)
                		{
                			//add
                			ResultSet nxt=co.sqlQueryR("SELECT max(grpid)+1 as nxt FROM pzsrvgroup");
                			nxt.next();
                			grpid=nxt.getString("nxt");
                			co.sqlExec("INSERT INTO pzsrvgroup VALUES ("+grpid+","+grpparent+",'"+co.cnv_sql(grpname)+"')");
                		} 
                	   	if (mode.equals("2")==true)
                		{
                			//del
                			co.sqlExec("DELETE FROM pzsrvempmap WHERE grpid="+grpid);
                			co.sqlExec("DELETE FROM pzsrvgroup WHERE grpid="+grpid);		
                		} 
                       }
                	boolean firstPass=true;
                	int maxWkgId=-1;
                	ResultSet rs=co.sqlQueryR("SELECT * FROM pzsrvgroup ORDER BY grpid");
                	while (rs.next())
                	{
                		String lnk="zusermgt2.jsp?WKGID="+rs.getInt("grpid");
                		if (maxWkgId<rs.getInt("grpid")) 
                			maxWkgId=rs.getInt("grpid")+1;		
                		String txt=rs.getString("grpname");
                
                		txt+=" <img src='img/add.gif' border=0 onclick=doAdd("+rs.getInt("grpid")+");>";
                
                		if (firstPass==false)
                		{
                			txt+="<img src='img/remove.gif' border=0 onclick=doDel("+rs.getInt("grpid")+");>";
                		}
                		else
                		{
                			firstPass=false;
                		}
                		out.println("m.add("+rs.getInt("grpid")+","+rs.getInt("grpparent")+",\""+txt+"\",\""+lnk+"\");");
                	}	
                
                 }
                 catch (SQLException e)
                 {
                   PsDebug.fail("wkgtree.jsp: "+e.getMessage());
                 }
                
            // end
            // HTML // begin [file="/zserver/zusermgt1.jsp";from=(96,2);to=(113,7)]
                out.write("\r\n//-->\r\n</script>\r\n</head>\r\n\r\n<body>\r\n<script language=JavaScript>\r\n<!--\r\n m.setTarget(\"usr\");\r\n m.setIconDocument(\"img/doc.gif\");\r\n m.setIconCollapse(\"img/close.gif\");\r\n m.setIconExpand(\"img/open.gif\");\r\n\r\n m.gen(true);\r\n//-->\r\n</script>\r\n</body>\r\n</html>");

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
