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


public class logon$jsp extends HttpJspBase {


    static {
    }
    public logon$jsp( ) {
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

            // HTML // begin [file="/zserver/logon.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/zserver/logon.jsp";from=(1,88);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/zserver/logon.jsp";from=(2,26);to=(4,0)]
                out.write("\r\n<head>\r\n");

            // end
            // begin [file="/zserver/logon.jsp";from=(4,2);to=(71,0)]
                
                 PsApp.init();
                 
                 session.setAttribute( "USERNAME",null);
                 session.setAttribute( "USERROLE","-1");
                 session.setAttribute( "USERID","-1");
                
                 String mlogin=request.getParameter( "LOGIN" );
                 String mpasswd=request.getParameter( "PASSWD" );
                
                 PsAuthentication auth=new PsAuthentication();
                 if (auth.logon(mlogin,mpasswd)==false)
                 {
                 	//not logged
                 	out.println("<meta HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=index.htm\">");
                 }
                 else
                 {
                 	//logged
                 	session.setAttribute( "USERNAME",mlogin);
                 	session.setAttribute( "USERROLE",String.valueOf(auth.getRole()));
                	session.setAttribute( "USERID",  String.valueOf(auth.getId()));
                	out.println("<meta HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=zserver.htm\">");
                
                	//workgroup assigned
                	String wkass="";
                	
                	PsApp.init();
                	PsDbConn conn;
                	conn=PsDbMgr.newConnection();
                	ResultSet rs;
                
                	rs=conn.sqlQueryR("SELECT distinct(w.wkgname) as nm FROM pworkgroup w,pemployee as e,pempmap m WHERE e.login=m.login AND w.wkgid=m.wkgid AND m.login='"+mlogin+"'");
                	boolean xout=rs.next();
                	while (xout==true)
                	{
                		wkass+=rs.getString("nm");
                		xout=rs.next();
                		if (xout==true)
                			wkass+=", ";
                	}
                	session.setAttribute( "USERWORKGROUPTXT",wkass);
                
                	String roletxt="N.A.";
                	rs=conn.sqlQueryR("SELECT rolename FROM pemproles WHERE roleid="+auth.getRole());
                	if (rs.next()==true)
                		roletxt=rs.getString("rolename");
                
                	session.setAttribute( "USERROLETXT",roletxt);	
                
                	//retrieve skin if selected
                	String skin="1"; //default
                	rs=conn.sqlQueryR("SELECT * FROM ppersonalize WHERE login='"+mlogin+"'");
                	if (rs.next()==true)
                	{
                		skin=rs.getString("userskin");
                	}
                	
                
                	session.setAttribute( "USERSKIN",skin);
                	PsDebug.log("Session userskin: "+skin);
                
                	//configure current session
                	int seconds=Integer.valueOf((String)PsConfig.get("SESSION_TIMEOUT")).intValue();
                	session.setMaxInactiveInterval(seconds);
                	PsDebug.log("Session timeout: "+seconds+" s.");
                 }
            // end
            // HTML // begin [file="/zserver/logon.jsp";from=(71,2);to=(76,7)]
                out.write("\r\n\r\n</head>\r\n<body>\r\n</body>\r\n</html>");

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
