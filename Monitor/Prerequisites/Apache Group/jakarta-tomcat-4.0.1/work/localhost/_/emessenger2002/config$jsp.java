package org.apache.jsp;

import java.util.*;
import java.lang.*;
import java.sql.*;
import PsApp;
import java.sql.*;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsConfig;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class config$jsp extends HttpJspBase {


    static {
    }
    public config$jsp( ) {
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

            // HTML // begin [file="/emessenger2002/config.jsp";from=(0,32);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/config.jsp";from=(1,32);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/config.jsp";from=(2,31);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/config.jsp";from=(3,26);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/config.jsp";from=(4,31);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/config.jsp";from=(5,28);to=(6,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/config.jsp";from=(6,29);to=(7,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/config.jsp";from=(7,28);to=(8,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/config.jsp";from=(8,29);to=(19,0)]
                out.write("\r\n<html>\r\n<head>\r\n<script language=JavaScript>\r\n<!--\r\n//-->\r\n</script>\r\n</head>\r\n<body>\r\n<form name=FRM action=\"config.jsp\" method=POST>\r\n<table>\r\n");

            // end
            // begin [file="/emessenger2002/config.jsp";from=(19,2);to=(56,0)]
                 
                  int mode=Integer.valueOf(request.getParameter( "MODE" )).intValue();
                  PsApp.init(); 
                
                  //mode 1
                  if (mode==1)
                  {
                	PsDebug.log("CONFIG.JSP update configuration...");
                	Enumeration pn=request.getParameterNames();
                	for (; pn.hasMoreElements();) 
                	{
                		String key=(String)pn.nextElement();
                		if (key.startsWith("CFG_")==true)
                		{
                			String val=(String)request.getParameter(key);
                			key=key.substring(4) ;
                			PsDebug.log("Set config "+key+"=("+val+")");
                			PsConfig.set(key,val);
                		}	
                	}
                	PsConfig.save("config.ini");
                	PsDebug.log("Configuration Saved!");	
                	System.out.println("Configuration updated successfully!");
                	PsConfig.reset();
                	PsConfig.load("config.ini");
                  }
                
                  Hashtable v; 
                  v=PsConfig.getHashTable(); 
                  Enumeration f=v.elements();
                  for (Enumeration e = v.keys(); e.hasMoreElements() ;) {	 
                	 String kn=(String)e.nextElement();
                         out.println("<tr><td>"+kn+"</td>");
                	 out.println("<td><input type=text size=80 name=\"CFG_"+kn+"\" value=\""+(String)f.nextElement()+"\"></td></tr>");
                     }
                  out.println("<input type=HIDDEN name=MODE value=1>");
                 
            // end
            // HTML // begin [file="/emessenger2002/config.jsp";from=(56,2);to=(61,7)]
                out.write("\r\n</table>\r\n<input type=submit value=Save>\r\n</form>\r\n</body>\r\n</html>");

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
