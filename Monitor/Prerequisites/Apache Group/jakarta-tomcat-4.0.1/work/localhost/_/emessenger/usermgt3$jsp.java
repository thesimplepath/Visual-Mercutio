package org.apache.jsp;

import PsApp;
import java.sql.*;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsConfig;
import PsMD5;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class usermgt3$jsp extends HttpJspBase {


    static {
    }
    public usermgt3$jsp( ) {
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

            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(1,77);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(2,26);to=(4,0)]
                out.write("\r\n<head>\r\n");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(4,0);to=(4,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(4,53);to=(5,0)]
                out.write("\r\n");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(5,2);to=(7,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(7,2);to=(8,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(8,19);to=(8,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(8,29);to=(11,0)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n</head>\r\n");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(11,2);to=(53,0)]
                
                 PsApp.init();
                 
                 try {
                  PsDbConn co;
                  ResultSet rs;
                  co=PsDbMgr.newConnection();	
                
                  String mode=request.getParameter( "MODE" );
                  String login=request.getParameter("LOGIN");
                  String passwd=request.getParameter("PASSWD");
                  String roleid=request.getParameter("ROLEID");
                  String fname=request.getParameter("FNAME");
                  String lname=request.getParameter("LNAME");
                  String email=request.getParameter("EMAIL");
                
                  if (mode!=null)
                  {
                   	if (mode.equals("1")==true)
                	{
                		//add
                		rs=co.sqlQueryR("SELECT max(emplid)+1 as id FROM pemployee");
                		rs.next();
                		int id=rs.getInt("id");			
                
                		co.sqlExecR("INSERT INTO pemployee VALUES ("+id+",'"+login+"',"+roleid+",'"+fname+"','"+lname+"','"+email+"')");
                		co.sqlExecR("INSERT INTO pemppasswd VALUES("+id+",'"+PsMD5.encode(passwd)+"')");
                	} 
                   	if (mode.equals("2")==true)
                	{
                		//del
                		rs=co.sqlQueryR("SELECT emplid as id FROM pemployee WHERE login='"+login+"'");
                		if (rs.next()==true)
                		{
                			int id=rs.getInt("id");
                	
                			co.sqlExecR("DELETE FROM pemployee WHERE emplid="+id);
                			co.sqlExecR("DELETE FROM pemppasswd WHERE emplid="+id);
                			co.sqlExecR("DELETE FROM pempmap WHERE login='"+login+"'");
                		}
                	} 
                  }
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(53,2);to=(76,0)]
                out.write("\r\n<body>\r\n\r\n<table width=\"100%\" border=0>\r\n<form action=\"usermgt3.jsp\" method=POST>\r\n<input type=hidden name=MODE value=1>\r\n<tr>\r\n<td><a class=menu>Login</a></td>\r\n<td><a class=menu>Passwd</a></td>\r\n<td><a class=menu>First Name</a></td>\r\n<td><a class=menu>Last Name</a></td>\r\n<td><a class=menu>Email</a></td>\r\n<td><a class=menu>Role</a></td>\r\n<td>&nbsp</td>\r\n</tr>\r\n\r\n<tr>\r\n<td><input type=text name=LOGIN style=\"width:100%\"></td>\r\n<td><input type=text name=PASSWD style=\"width:100%\"></td>\r\n<td><input type=text name=FNAME style=\"width:100%\"></td>\r\n<td><input type=text name=LNAME style=\"width:100%\"></td>\r\n<td><input type=text name=EMAIL style=\"width:100%\"></td>\r\n<td><SELECT name=ROLEID style=\"width:100%\">\r\n");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(76,2);to=(83,0)]
                	String rolelist="";
                	rs=co.sqlQueryR("SELECT * FROM pemproles");
                	while (rs.next())
                	{
                	rolelist+="<option value=\""+rs.getInt("roleid")+"\">"+rs.getString("rolename")+"</option>\n";
                	}
                	out.println(rolelist);
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(83,2);to=(99,0)]
                out.write("\r\n</SELECT></td>\r\n<td>&nbsp;<input type=submit value=Add></td>\r\n</tr>\r\n</form>\r\n\r\n<tr class=Bg height=2>\r\n<td> </td>\r\n<td> </td>\r\n<td> </td>\r\n<td> </td>\r\n<td> </td>\r\n<td> </td>\r\n<td> </td>\r\n</tr>\r\n\r\n");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(99,2);to=(105,0)]
                
                	rs=co.sqlQueryR("SELECT * FROM pemployee,pemppasswd WHERE pemployee.emplid=pemppasswd.emplid ORDER BY login");
                	int frmcnt=0;
                	while (rs.next())
                	{
                	frmcnt++;
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(105,2);to=(106,46)]
                out.write("\r\n<form action=usermgt3.jsp method=POST name=FRM");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(106,49);to=(106,55)]
                out.print(frmcnt);
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(106,57);to=(109,95)]
                out.write(">\r\n<input type=hidden name=MODE value=2>\r\n<tr>\r\n<td><input readonly type=text name=LOGIN  style=\"background-color:lightgrey;width:100%\" value=\"");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(109,98);to=(109,119)]
                out.print(rs.getString("login"));
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(109,121);to=(110,59)]
                out.write("\"></td>\r\n<td><input type=text name=PASSWD style=\"width:100%\" value=\"");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(110,62);to=(110,84)]
                out.print(rs.getString("passwd"));
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(110,86);to=(111,59)]
                out.write("\"></td>\r\n<td><input type=text name=FNAME style=\"width:100%\"  value=\"");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(111,62);to=(111,83)]
                out.print(rs.getString("fname"));
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(111,85);to=(112,59)]
                out.write("\"></td>\r\n<td><input type=text name=LNAME style=\"width:100%\"  value=\"");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(112,62);to=(112,83)]
                out.print(rs.getString("lname"));
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(112,85);to=(113,59)]
                out.write("\"></td>\r\n<td><input type=text name=EMAIL style=\"width:100%\"  value=\"");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(113,62);to=(113,83)]
                out.print(rs.getString("email"));
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(113,85);to=(114,43)]
                out.write("\"></td>\r\n<td><SELECT name=ROLEID style=\"width:100%\">");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(114,46);to=(114,54)]
                out.print(rolelist);
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(114,56);to=(116,13)]
                out.write("</SELECT>\r\n<script language=javascript>\r\n document.FRM");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(116,16);to=(116,22)]
                out.print(frmcnt);
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(116,24);to=(116,38)]
                out.write(".ROLEID.value=");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(116,41);to=(116,63)]
                out.print(rs.getString("roleid"));
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(116,65);to=(122,0)]
                out.write(";\r\n</script>\r\n</td>\r\n<td>&nbsp;<input type=submit value=Del></td>\r\n</tr>\r\n</form>\r\n");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(122,2);to=(124,0)]
                
                	}
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(124,2);to=(127,0)]
                out.write("\r\n</table>\r\n</body>\r\n");

            // end
            // begin [file="/emessenger/usermgt3.jsp";from=(127,2);to=(134,0)]
                
                 }
                 catch (SQLException e)
                 {
                   PsDebug.fail("wkgtree.jsp: "+e.getMessage());
                 }
                
            // end
            // HTML // begin [file="/emessenger/usermgt3.jsp";from=(134,2);to=(135,7)]
                out.write("\r\n</html>");

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
