package org.apache.jsp;

import java.util.*;
import  org.apache.soap.server.*;
import  org.apache.soap.util.xml.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class showdetails$jsp extends HttpJspBase {


    static {
    }
    public showdetails$jsp( ) {
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

            // HTML // begin [file="/admin/showdetails.jsp";from=(0,86);to=(4,0)]
                out.write("\r\n\r\n<h1>Deployed Service Information</h1>\r\n\r\n");

            // end
            // begin [file="/admin/showdetails.jsp";from=(4,2);to=(109,0)]
                 
                  ServiceManager serviceManager =
                    org.apache.soap.server.http.ServerHTTPUtils.getServiceManagerFromContext(application);
                
                  String id = request.getParameter ("id");
                  DeploymentDescriptor dd = (id != null) 
                                            ? serviceManager.query (id) 
                			    : null;
                  String[] scopes = {"Request", "Session", "Application"}; 
                
                  if (id == null) {
                    out.println ("<p>Huh? You hafta select a service to display ..</p>");
                  } else if (dd == null) {
                    out.println ("<p>Service '" + id + "' is not known.</p>");
                  } else {
                    out.println ("<table border='1' width='100%'>");
                    out.println ("<tr>");
                    out.println ("<th colspan='2'><h2>'" + id + 
                		 "' Service Deployment Descriptor</h2></th>");
                    out.println ("</tr>");
                    out.println ("<tr>");
                    out.println ("<th>Property</th>");
                    out.println ("<th>Details</th>");
                    out.println ("</tr>");
                    out.println ("<tr>");
                    out.println ("<td>ID</td>");
                    out.println ("<td>" + dd.getID()+ "</td>");
                    out.println ("</tr>");
                    out.println ("<tr>");
                    out.println ("<td>Scope</td>");
                    out.println ("<td>" + scopes[dd.getScope()]+ "</td>");
                    out.println ("</tr>");
                
                    byte ptb = dd.getProviderType ();
                    String ptLabel = "Provider Type";
                    String pt = null;
                
                    if (ptb == DeploymentDescriptor.PROVIDER_JAVA) {
                      pt = "java";
                    } else if (ptb == DeploymentDescriptor.PROVIDER_USER_DEFINED) {
                      ptLabel = "User-Defined " + ptLabel;
                      pt = dd.getServiceClass();
                    } else {
                      pt = "script";
                    }
                
                    out.println ("<tr>");
                    out.println ("<td>" + ptLabel + "</td>");
                    out.println ("<td>" + pt + "</td>");
                    out.println ("</tr>");
                    out.println ("<tr>");
                    if (ptb == DeploymentDescriptor.PROVIDER_JAVA
                        || ptb == DeploymentDescriptor.PROVIDER_USER_DEFINED) {
                      out.println ("<td>Provider Class</td>");
                      out.println ("<td>" + dd.getProviderClass()+ "</td>");
                      out.println ("</tr>");
                      out.println ("<tr>");
                      out.println ("<td>Use Static Class</td>");
                      out.println ("<td>" + dd.getIsStatic()+ "</td>");
                    } else {
                      out.println ("<td>Scripting Language</td>");
                      out.println ("<td>" + dd.getScriptLanguage () + "</td>");
                      out.println ("</tr>");
                      out.println ("<tr>");
                      if (ptb == DeploymentDescriptor.PROVIDER_SCRIPT_FILE) {
                	out.println ("<td>Filename</td>");
                	out.println ("<td>" + dd.getScriptFilenameOrString () + "</td>");
                      } else {
                	out.println ("<td>Script</td>");
                	out.println ("<td><pre>" + dd.getScriptFilenameOrString () +
                		     "</pre></td>");
                      }
                    }
                    out.println ("</tr>");
                    out.println ("<tr>");
                    out.println ("<td>Methods</td>");
                    out.print ("<td>");
                    String[] m = dd.getMethods ();
                    for (int i = 0; i < m.length; i++) {
                      out.print (m[i]);
                      if (i < m.length-1) {
                	out.print (", ");
                      }
                    }
                    out.println ("</td>");
                    out.println ("</tr>");
                    out.println ("<tr>");
                    out.println ("<td>Type Mappings</td>");
                    out.println ("<td>");
                    TypeMapping[] mappings = dd.getMappings();
                    if (mappings != null) {
                      for (int i = 0; i < mappings.length; i++) {
                	out.print (mappings[i]);
                	if (i < mappings.length-1) {
                	  out.print ("<br>");
                	} else {
                	  break;
                	}
                      }
                    }
                    out.println ("</td>");
                    out.println ("</tr>");
                    out.println("<tr><td>Default Mapping Registry Class</td><td>" + (dd.getDefaultSMRClass() != null ? dd.getDefaultSMRClass() : "") + "</td></tr>");
                    out.println ("</table>");
                  }
            // end
            // HTML // begin [file="/admin/showdetails.jsp";from=(109,2);to=(110,0)]
                out.write("\r\n");

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
