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

            // HTML // begin [file="/newproc2.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/newproc2.jsp";from=(1,88);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/newproc2.jsp";from=(2,26);to=(5,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/newproc2.jsp";from=(5,0);to=(5,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/newproc2.jsp";from=(5,53);to=(6,0)]
                out.write("\r\n");

            // end
            // begin [file="/newproc2.jsp";from=(6,2);to=(8,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/newproc2.jsp";from=(8,2);to=(9,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/newproc2.jsp";from=(9,19);to=(9,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/newproc2.jsp";from=(9,29);to=(14,0)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n<script language=JavaScript src=\"js/pss.js\"></script>\r\n</head>\r\n<BODY>\r\n<TABLE width=\"100%\" border=0>\r\n");

            // end
            // begin [file="/newproc2.jsp";from=(14,2);to=(30,2)]
                
                  PsApp.init();
                
                  int caseattachid = 	Integer.valueOf(request.getParameter( "CASEATTACHID" )).intValue();
                  String casename =     request.getParameter("CASENAME" );
                  int procid = 			Integer.valueOf(request.getParameter( "PROCID" )).intValue();
                  int transid = 		Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
                  String transname = 	request.getParameter( "TRANSNAME" );
                  int parenttransid= 	Integer.valueOf(request.getParameter( "PARENTTRANSID" )).intValue();
                  int empid= 			Integer.valueOf(request.getParameter( "EMPID" )).intValue();
                  int statusid = 		Integer.valueOf(request.getParameter( "STATUSID" )).intValue();
                  int globalyn = 		Integer.valueOf(request.getParameter( "GLOBALYN" )).intValue();
                  int qty = 			Integer.valueOf(request.getParameter( "QTY" )).intValue();
                
                  int fromproc = 		Integer.valueOf(request.getParameter( "FROMPROC" )).intValue();
                
                  
            // end
            // HTML // begin [file="/newproc2.jsp";from=(30,4);to=(34,68)]
                out.write("\r\n  <TBODY>\r\n  <TR>\r\n  \t<TD width=\"11%\">&nbsp;</TD>\r\n  \t<TD class=NormalBlack vAlign=top width=\"89%\">Nouveau cas crÃ©Ã©: ");

            // end
            // begin [file="/newproc2.jsp";from=(34,71);to=(34,79)]
                out.print(casename);
            // end
            // HTML // begin [file="/newproc2.jsp";from=(34,81);to=(34,83)]
                out.write(", ");

            // end
            // begin [file="/newproc2.jsp";from=(34,86);to=(34,95)]
                out.print(transname);
            // end
            // HTML // begin [file="/newproc2.jsp";from=(34,97);to=(39,0)]
                out.write("</TD>\r\n  </TR>\r\n  <TR>\r\n  \t<TD width=\"11%\">&nbsp;</TD>\r\n  \t<TD class=NormalBlack vAlign=top width=\"89%\"><P>&nbsp;</P><P>Le message a Ã©tÃ© envoyÃ© dans la boÃ®te de travail de la procÃ©dure:</P>\r\n");

            // end
            // begin [file="/newproc2.jsp";from=(39,2);to=(45,1)]
                
                 try {
                	PsDbConn conn=PsDbMgr.newConnection();
                
                	ResultSet rs=conn.sqlQueryR("SELECT * FROM pdeliv WHERE procidsrc="+procid);
                	rs.next();
                	
            // end
            // HTML // begin [file="/newproc2.jsp";from=(45,3);to=(46,8)]
                out.write("\r\n\t\t<P><B>");

            // end
            // begin [file="/newproc2.jsp";from=(46,11);to=(46,36)]
                out.print(rs.getString("delivname"));
            // end
            // HTML // begin [file="/newproc2.jsp";from=(46,38);to=(47,1)]
                out.write("</B></P></TD></TR>\r\n\t");

            // end
            // begin [file="/newproc2.jsp";from=(47,3);to=(70,0)]
                
                	int caseid;
                	if (caseattachid<0)
                		caseid=conn.nextVal("PCASE");
                	else
                		caseid=caseattachid;
                
                	int attribid=conn.nextVal("PATTRIB");
                	String txindate=conn.now();
                
                	if (caseattachid==-1)
                		conn.sqlExecR("INSERT INTO pcase VALUES ("+caseid+","+txindate+",'"+PsDbConn.cnv_sql(casename)+"')");
                	conn.sqlExecR("INSERT INTO ptrans VALUES ("+caseid+","+transid+","+parenttransid+",'"+PsDbConn.cnv_sql(transname)+"',"+globalyn+","+attribid+",0)");
                	conn.sqlExecR("INSERT INTO pproctrans VALUES ("+procid+","+caseid+","+transid+",0,"+empid+",0,"+fromproc+","+conn.now()+")");
                
                  	for (int i=0;i<qty;i++)
                	{
                	    int segid=		Integer.valueOf(request.getParameter( "SEG"+i)).intValue();
                	    int attribdefid=Integer.valueOf(request.getParameter( "ATTRIBID"+i)).intValue();
                	    String mkey=	request.getParameter( "KEY"+i );
                	    String mval=	request.getParameter( "VAL"+i );
                		conn.sqlExecR("INSERT INTO pattrib VALUES ("+caseid+","+transid+","+segid+","+attribid+","+attribdefid+",'"+mkey+"','"+mval+"')");
                	}	
            // end
            // HTML // begin [file="/newproc2.jsp";from=(70,2);to=(82,32)]
                out.write("\r\n</TR>\r\n  <TR>\r\n  \t<TD width=\"11%\">&nbsp;</TD>\r\n  \t<TD class=NormalBlack vAlign=top width=\"89%\"><P>&nbsp;</P><P>Veuillez valider le(s) livrable(s) en sortie du point de dÃ©marrage en cliquant sur le bouton ci-dessous.</p>\r\n<INPUT TYPE=button class=sbttn value=\"Validation Livrable(s)\" onclick=\"javascript:goDetail();\">\r\n</TD>\r\n  </TR>\r\n</tbody></table>\r\n<script language=JavaScript>\r\nfunction goDetail()\r\n{\r\n\tvar url=\"detailcase.jsp?CASEID=");

            // end
            // begin [file="/newproc2.jsp";from=(82,35);to=(82,41)]
                out.print(caseid);
            // end
            // HTML // begin [file="/newproc2.jsp";from=(82,43);to=(82,51)]
                out.write("&PROCID=");

            // end
            // begin [file="/newproc2.jsp";from=(82,54);to=(82,60)]
                out.print(procid);
            // end
            // HTML // begin [file="/newproc2.jsp";from=(82,62);to=(82,71)]
                out.write("&TRANSID=");

            // end
            // begin [file="/newproc2.jsp";from=(82,74);to=(82,81)]
                out.print(transid);
            // end
            // HTML // begin [file="/newproc2.jsp";from=(82,83);to=(87,0)]
                out.write("\";\r\n\tdocument.location=url;\r\n\treturn false;\r\n}\r\n</script>\r\n");

            // end
            // begin [file="/newproc2.jsp";from=(87,2);to=(93,0)]
                
                   }
                 catch (SQLException e)
                    {
                		PsDebug.fail("newproc2.jsp: SQLException: "+e.getMessage());
                    }
            // end
            // HTML // begin [file="/newproc2.jsp";from=(93,2);to=(95,7)]
                out.write("\r\n</body>\r\n</html>");

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
