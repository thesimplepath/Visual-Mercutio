package org.apache.jsp;

import java.io.*;
import  java.util.*;
import  org.w3c.dom.*;
import org.apache.soap.util.*;
import  org.apache.soap.util.xml.*;
import  org.apache.soap.server.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class deploy$jsp extends HttpJspBase {


    static {
    }
    public deploy$jsp( ) {
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

            // HTML // begin [file="/admin/deploy.jsp";from=(0,58);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/admin/deploy.jsp";from=(1,97);to=(5,0)]
                out.write("\r\n\r\n<h1>Deploy a Service</h1>\r\n\r\n");

            // end
            // begin [file="/admin/deploy.jsp";from=(5,2);to=(10,0)]
                 
                ServiceManager serviceManager =
                  org.apache.soap.server.http.ServerHTTPUtils.getServiceManagerFromContext(application);
                
                if (!request.getMethod().equals ("POST")) { 
            // end
            // HTML // begin [file="/admin/deploy.jsp";from=(10,2);to=(320,0)]
                out.write("\r\n\r\n<form action=\"deploy.jsp\" method=\"POST\">\r\n    <table border=\"1\" width=\"100%\">\r\n        <tr>\r\n            <th colspan=\"2\"><h2>Service Deployment Descriptor\r\n            Template</h2>\r\n            </th>\r\n        </tr>\r\n        <tr>\r\n            <th>Property</th>\r\n            <th>Details</th>\r\n        </tr>\r\n        <tr>\r\n            <td>ID</td>\r\n            <td><input type=\"text\" size=\"60\" name=\"id\"></td>\r\n        </tr>\r\n        <tr>\r\n            <td>Scope</td>\r\n            <td><select name=\"scope\" size=\"1\">\r\n                <option selected value=\"0\">Request</option>\r\n                <option value=\"1\">Session</option>\r\n                <option value=\"2\">Application</option>\r\n            </select></td>\r\n        </tr>\r\n        <tr>\r\n            <td>Methods</td>\r\n            <td><input type=\"text\" size=\"60\" name=\"methods\"><br>\r\n            (Whitespace separated list of method names) </td>\r\n        </tr>\r\n        <tr>\r\n            <td>Provider Type</td>\r\n      \r\n            <td><select name=\"providerType\" size=\"1\">\r\n                <option selected value=\"0\">Java</option>\r\n                <option value=\"1\">Script</option>\r\n\t\t<option value=\"3\">User-Defined</option>\r\n            \t</select></td>\r\n        </tr>\r\n\t<tr>\r\n\t\t<td> </td>\r\n\t\t<td><div align=\"left\"><table border=\"0\">\r\n                <tr>\r\n                    <td>For User-Defined Provider Type, Enter FULL Class Name:</td>\r\n\t\t</tr>\r\n\t\t<tr>\r\n                    <td><input type=\"text\" size=\"60\" name=\"userProviderClassString\"></td>\r\n                </tr>\r\n\t\t</table></div></td>\r\n\t</tr>\r\n\t<tr>\r\n\t\t<td> </td>\r\n\t\t<td>Number of Options: <input type=\"text\" size=\"10\" name=\"noOpts\" /><br>\r\n            \t<div align=\"center\"><center><table border=\"0\">\r\n                <tr>\r\n                    <td align=\"center\" >Key</td>\r\n                    <td align=\"center\" >Value</td>\r\n\t\t</tr>\r\n                <tr>\r\n                    <td><input type=\"text\" size=\"15\" name=\"optionkey1\"></td>\r\n                    <td><input type=\"text\" size=\"20\" name=\"optionvalue1\"></td>\r\n                </tr>\r\n                <tr>\r\n                    <td><input type=\"text\" size=\"15\" name=\"optionkey2\"></td>\r\n                    <td><input type=\"text\" size=\"20\" name=\"optionvalue2\"></td>\r\n                </tr>\r\n                <tr>\r\n                    <td><input type=\"text\" size=\"15\" name=\"optionkey3\"></td>\r\n                    <td><input type=\"text\" size=\"20\" name=\"optionvalue3\"></td>\r\n                </tr>\r\n                <tr>\r\n                    <td><input type=\"text\" size=\"15\" name=\"optionkey4\"></td>\r\n                    <td><input type=\"text\" size=\"20\" name=\"optionvalue4\"></td>\r\n                </tr>\r\n\t\t</table></center></div></td>\r\n\t</tr>\r\n        <tr>\r\n            <td>Java Provider</td>\r\n            <td><div align=\"left\"><table border=\"0\">\r\n                <tr>\r\n                    <td>Provider Class</td>\r\n                    <td><input type=\"text\" size=\"40\"\r\n                    name=\"providerClass\"></td>\r\n                </tr>\r\n                <tr>\r\n                    <td width=\"150\">Static?</td>\r\n                    <td><select name=\"isStatic\" size=\"1\">\r\n                        <option value=\"true\">Yes</option>\r\n                        <option selected value=\"no\">No</option>\r\n                    </select></td>\r\n                </tr>\r\n            </table>\r\n            </div></td>\r\n        </tr>\r\n        <tr>\r\n            <td>Script Provider</td>\r\n            <td><div align=\"left\"><table border=\"0\">\r\n                <tr>\r\n                    <td>Script Language</td>\r\n                    <td><select name=\"scriptLanguage\" size=\"1\">\r\n                        <option value=\"bml\">BML</option>\r\n                        <option value=\"jacl\">Jacl</option>\r\n                        <option value=\"javascript\">JavaScript (Rhino)</option>\r\n                        <option value=\"jpython\">JPython</option>\r\n                        <option value=\"jscript\">JScript</option>\r\n                        <option value=\"perlscript\">PerlScript</option>\r\n                        <option value=\"vbscript\">VBScript</option>\r\n                        <option value=\"other\">Other .. (type in)</option>\r\n                    </select><input type=\"text\" size=\"20\"\r\n                    name=\"scriptLanguageTypein\"></td>\r\n                </tr>\r\n                <tr>\r\n                    <td width=\"150\">Script Filename, or</td>\r\n                    <td><input type=\"text\" size=\"40\"\r\n                    name=\"scriptFilename\"></td>\r\n                </tr>\r\n                <tr>\r\n                    <td>Script</td>\r\n                    <td><textarea name=\"script\" rows=\"10\"\r\n                    cols=\"40\"></textarea></td>\r\n                </tr>\r\n            </table>\r\n            </div></td>\r\n        </tr>\r\n        <tr>\r\n            <td>Type Mappings</td>\r\n            <td>Number of mappings: <input type=\"text\" size=\"10\"\r\n            name=\"nmaps\" /><br>\r\n            <div align=\"center\"><center><table border=\"0\">\r\n                <tr>\r\n                    <td align=\"center\" rowspan=\"2\">Encoding Style</td>\r\n                    <td align=\"center\" colspan=\"2\">Element Type </td>\r\n                    <td align=\"center\" rowspan=\"2\">Java Type</td>\r\n                    <td align=\"center\" rowspan=\"2\">Java to XML\r\n                    Serializer </td>\r\n                    <td align=\"center\" rowspan=\"2\">XML to Java\r\n                    Deserializer </td>\r\n                </tr>\r\n                <tr>\r\n                    <td align=\"center\">Namespace URI</td>\r\n                    <td align=\"center\">Local Part</td>\r\n                </tr>\r\n                <tr>\r\n                    <td><select name=\"encstyle1\" size=\"1\">\r\n                        <option selected value=\"0\">SOAP</option>\r\n                        <option value=\"1\">XMI</option>\r\n                    </select></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"nsuri1\"></td>\r\n                    <td><input type=\"text\" size=\"10\"\r\n                    name=\"localpart1\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"classname1\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"java2xml1\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"xml2java1\"></td>\r\n                </tr>\r\n                <tr>\r\n                    <td><select name=\"encstyle2\" size=\"1\">\r\n                        <option selected value=\"0\">SOAP</option>\r\n                        <option value=\"1\">XMI</option>\r\n                    </select></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"nsuri2\"></td>\r\n                    <td><input type=\"text\" size=\"10\"\r\n                    name=\"localpart2\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"classname2\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"java2xml2\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"xml2java2\"></td>\r\n                </tr>\r\n                <tr>\r\n                    <td><select name=\"encstyle3\" size=\"1\">\r\n                        <option selected value=\"0\">SOAP</option>\r\n                        <option value=\"1\">XMI</option>\r\n                    </select></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"nsuri3\"></td>\r\n                    <td><input type=\"text\" size=\"10\"\r\n                    name=\"localpart3\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"classname3\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"java2xml3\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"xml2java3\"></td>\r\n                </tr>\r\n                <tr>\r\n                    <td><select name=\"encstyle4\" size=\"1\">\r\n                        <option selected value=\"0\">SOAP</option>\r\n                        <option value=\"1\">XMI</option>\r\n                    </select></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"nsuri4\"></td>\r\n                    <td><input type=\"text\" size=\"10\"\r\n                    name=\"localpart4\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"classname4\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"java2xml4\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"xml2java4\"></td>\r\n                </tr>\r\n                <tr>\r\n                    <td><select name=\"encstyle5\" size=\"1\">\r\n                        <option selected value=\"0\">SOAP</option>\r\n                        <option value=\"1\">XMI</option>\r\n                    </select></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"nsuri5\"></td>\r\n                    <td><input type=\"text\" size=\"10\"\r\n                    name=\"localpart5\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"classname5\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"java2xml5\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"xml2java5\"></td>\r\n                </tr>\r\n                <tr>\r\n                    <td><select name=\"encstyle6\" size=\"1\">\r\n                        <option selected value=\"0\">SOAP</option>\r\n                        <option value=\"1\">XMI</option>\r\n                    </select></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"nsuri6\"></td>\r\n                    <td><input type=\"text\" size=\"10\"\r\n                    name=\"localpart6\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"classname6\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"java2xml6\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"xml2java6\"></td>\r\n                </tr>\r\n                <tr>\r\n                    <td><select name=\"encstyle7\" size=\"1\">\r\n                        <option selected value=\"0\">SOAP</option>\r\n                        <option value=\"1\">XMI</option>\r\n                    </select></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"nsuri7\"></td>\r\n                    <td><input type=\"text\" size=\"10\"\r\n                    name=\"localpart7\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"classname7\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"java2xml7\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"xml2java7\"></td>\r\n                </tr>\r\n                <tr>\r\n                    <td><select name=\"encstyle8\" size=\"1\">\r\n                        <option selected value=\"0\">SOAP</option>\r\n                        <option value=\"1\">XMI</option>\r\n                    </select></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"nsuri8\"></td>\r\n                    <td><input type=\"text\" size=\"10\"\r\n                    name=\"localpart8\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"classname8\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"java2xml8\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"xml2java8\"></td>\r\n                </tr>\r\n                <tr>\r\n                    <td><select name=\"encstyle9\" size=\"1\">\r\n                        <option selected value=\"0\">SOAP</option>\r\n                        <option value=\"1\">XMI</option>\r\n                    </select></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"nsuri9\"></td>\r\n                    <td><input type=\"text\" size=\"10\"\r\n                    name=\"localpart9\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"classname9\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"java2xml9\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"xml2java9\"></td>\r\n                </tr>\r\n                <tr>\r\n                    <td><select name=\"encstyle10\" size=\"1\">\r\n                        <option selected value=\"0\">SOAP</option>\r\n                        <option value=\"1\">XMI</option>\r\n                    </select></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"nsuri10\"></td>\r\n                    <td><input type=\"text\" size=\"10\"\r\n                    name=\"localpart10\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"classname10\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"java2xml10\"></td>\r\n                    <td><input type=\"text\" size=\"15\"\r\n                    name=\"xml2java10\"></td>\r\n                </tr>\r\n            </table>\r\n            </center></div></td>\r\n        </tr>\r\n\t<tr><td>Default Mapping Registry Class</td><td><input type=\"text\" size=\"60\" name=\"defaultSMR\"></td></tr>\r\n    </table>\r\n    <p><input type=\"submit\" value=\"Deploy\" /></p>\r\n</form>\r\n\r\n");

            // end
            // begin [file="/admin/deploy.jsp";from=(320,2);to=(438,0)]
                
                } else {
                  String id = request.getParameter ("id");
                  DeploymentDescriptor dd = new DeploymentDescriptor ();
                  dd.setID (id);
                
                  // get the provider info
                  int scope = Integer.parseInt (request.getParameter ("scope"));
                  String providerTypeStr = request.getParameter ("providerType");
                  String className = request.getParameter ("providerClass");
                  boolean isStatic = request.getParameter ("isStatic").equals ("true");
                  String scriptLang = request.getParameter ("scriptLanguage");
                  String userClass = request.getParameter ("userProviderClassString");
                
                  if (scriptLang.equals ("other")) {
                    scriptLang = request.getParameter ("scriptLanguageTypeIn");
                  }
                  String scriptFilename = request.getParameter ("scriptFilename");
                  String script = request.getParameter ("script");
                  String methodsStr = request.getParameter ("methods");
                  StringTokenizer st = new StringTokenizer (methodsStr);
                  int nTokens = st.countTokens ();
                  String[] methods = new String[nTokens];
                  for (int i = 0; i < nTokens; i++) {
                    methods[i] = st.nextToken ();
                  }
                
                  dd.setScope (scope);
                  dd.setMethods (methods);
                
                  if (providerTypeStr.equals ("0")) {
                    dd.setProviderType (DeploymentDescriptor.PROVIDER_JAVA);
                    dd.setProviderClass (className);
                    dd.setIsStatic (isStatic);
                  } else {
                	if (providerTypeStr.equals("3")) {
                		dd.setProviderType (DeploymentDescriptor.PROVIDER_USER_DEFINED);
                		dd.setServiceClass(userClass);
                		dd.setProviderClass (className);
                		dd.setIsStatic (isStatic);
                
                		// get any options
                		int optnum = 0;
                
                
                		try {
                		    optnum = Integer.parseInt (request.getParameter ("noOpts"));
                		} catch (NumberFormatException e) {
                			optnum = 0;
                		}
                
                		if (optnum != 0) {
                		
                			Hashtable optionsTble = new Hashtable();
                		
                			for (int j = 1; j <= optnum; j++) { 
                			      String keyS= request.getParameter ("optionkey" + j);
                			      String valueS= request.getParameter ("optionvalue" + j);
                				optionsTble.put(keyS, valueS);
                			}
                			dd.setProps(optionsTble);
                    		}
                
                	
                   	} else {
                    		if (!scriptFilename.equals ("")) { // filename specified
                      			dd.setProviderType (DeploymentDescriptor.PROVIDER_SCRIPT_FILE);
                    		} else { // there better be a script to run
                      			dd.setProviderType (DeploymentDescriptor.PROVIDER_SCRIPT_STRING);
                    		}
                    		dd.setScriptLanguage (scriptLang);
                    		dd.setScriptFilenameOrString (scriptFilename);
                  	}
                  }
                  String[] encs = {org.apache.soap.Constants.NS_URI_SOAP_ENC,
                       org.apache.soap.Constants.NS_URI_XMI_ENC};
                
                  // set up any type mappings
                  int nmaps = 0;
                
                  try {
                    nmaps = Integer.parseInt (request.getParameter ("nmaps"));
                  } catch (NumberFormatException e) {
                  }
                
                  if (nmaps != 0) {
                    TypeMapping[] mappings = new TypeMapping[nmaps];
                    for (int i = 1; i <= nmaps; i++) { // the form is hard-coded to a max of 10
                      int encStyle = Integer.parseInt (request.getParameter ("encstyle" + i));
                      String nsuri = request.getParameter ("nsuri" + i);
                      String localPart = request.getParameter ("localpart" + i);
                      String classNameStr = request.getParameter ("classname" + i);
                      String java2XMLClass = request.getParameter ("java2xml" + i);
                      String xml2JavaClass = request.getParameter ("xml2java" + i);
                      QName elementType = (nsuri.equals ("") || localPart.equals ("")) 
                                          ? null : new QName (nsuri, localPart);
                      // map "" to null (the unfilled params come as empty strings because
                      // they are infact actual parameters)
                      classNameStr = classNameStr.equals ("") ? null : classNameStr;
                      java2XMLClass = java2XMLClass.equals ("") ? null : java2XMLClass;
                      xml2JavaClass = xml2JavaClass.equals ("") ? null : xml2JavaClass;
                      mappings[i-1] = new TypeMapping (encs[encStyle], elementType,
                				       classNameStr, java2XMLClass,
                				       xml2JavaClass);
                    }
                    dd.setMappings (mappings);
                  }
                
                  String defaultSMR = request.getParameter("defaultSMR");
                  if (defaultSMR != null) {
                	dd.setDefaultSMRClass(defaultSMR);
                  }
                  // ok now deploy it
                  serviceManager.deploy (dd);
                
                  // show what was deployed
                  out.println ("<p>Service <b>" + dd.getID () + "</b> deployed.</p>");
                }
            // end
            // HTML // begin [file="/admin/deploy.jsp";from=(438,2);to=(439,0)]
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
