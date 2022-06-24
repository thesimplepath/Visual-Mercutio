package org.apache.jsp;

import java.util.*;
import java.lang.*;
import java.sql.*;
import PsApp;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsConfig;
import PsWorkGroup;
import PsWf;
import HttpUpload;
import HttpFile;
import HttpFiles;
import HttpRequest;
import HttpUploadException;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class upload$jsp extends HttpJspBase {

    // begin [file="/emessenger/upload.jsp";from=(12,0);to=(12,59)]
    // end

    static {
    }
    public upload$jsp( ) {
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

            // HTML // begin [file="/emessenger/upload.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<HTML>\r\n");

            // end
            // HTML // begin [file="/emessenger/upload.jsp";from=(1,174);to=(3,0)]
                out.write("\r\n<HEAD><TITLE>ProcessSoft Mercutio Messenger - Upload</TITLE>\r\n");

            // end
            // begin [file="/emessenger/upload.jsp";from=(3,0);to=(3,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/emessenger/upload.jsp";from=(3,53);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger/upload.jsp";from=(4,26);to=(5,0)]
                out.write("\r\n");

            // end
            // begin [file="/emessenger/upload.jsp";from=(5,2);to=(7,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/emessenger/upload.jsp";from=(7,2);to=(8,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/emessenger/upload.jsp";from=(8,19);to=(8,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/upload.jsp";from=(8,29);to=(12,0)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n\r\n");

            // end
            // begin [file="/emessenger/upload.jsp";from=(12,0);to=(12,59)]
                HttpUpload doupld = null;
                boolean _jspx_specialdoupld  = false;
                 synchronized (pageContext) {
                    doupld= (HttpUpload)
                    pageContext.getAttribute("doupld",PageContext.PAGE_SCOPE);
                    if ( doupld == null ) {
                        _jspx_specialdoupld = true;
                        try {
                            doupld = (HttpUpload) java.beans.Beans.instantiate(this.getClass().getClassLoader(), "HttpUpload");
                        } catch (ClassNotFoundException exc) {
                             throw new InstantiationException(exc.getMessage());
                        } catch (Exception exc) {
                             throw new ServletException (" Cannot create bean of class "+"HttpUpload", exc);
                        }
                        pageContext.setAttribute("doupld", doupld, PageContext.PAGE_SCOPE);
                    }
                 } 
                if(_jspx_specialdoupld == true) {
            // end
            // begin [file="/emessenger/upload.jsp";from=(12,0);to=(12,59)]
                }
            // end
            // HTML // begin [file="/emessenger/upload.jsp";from=(12,59);to=(15,0)]
                out.write("\r\n</jsp:useBean>\r\n\r\n");

            // end
            // begin [file="/emessenger/upload.jsp";from=(15,2);to=(67,1)]
                
                 PsApp.init();
                
                 PsDbConn conn=PsDbMgr.newConnection();
                 ResultSet rs;
                
                 String username=(String)session.getAttribute("USERNAME");
                 if (username==null) return;
                 int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
                 int userrole=		Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();
                
                 int caseid=-1;
                 if (request.getParameter( "CASEID" )!=null)		
                	caseid=Integer.valueOf(request.getParameter( "CASEID" )).intValue();
                 int transid=-1;
                 if (request.getParameter( "TRANSID" )!=null)
                	transid=Integer.valueOf(request.getParameter( "TRANSID" )).intValue();
                 int mode=2;
                 
                 if (request.getParameter( "MODE" )!=null)
                	mode=Integer.valueOf(request.getParameter( "MODE" )).intValue();
                
                 if (mode==2)
                 {
                	PsDebug.log("upload.jsp starting upload");
                	doupld.initialize(pageContext);
                	//doupld.setTotalMaxFileSize(2000000);
                	//doupld.setAllowedFilesList("htm,html,txt,doc,xls,ppt,xml,tif,jpg,gif,png,bmp,,");
                	doupld.upload();
                
                	caseid=Integer.valueOf((String)doupld.getRequest().getParameter("CASEID")).intValue();
                	transid=Integer.valueOf((String)doupld.getRequest().getParameter("TRANSID")).intValue();
                	PsDebug.log("upload.jsp processing");
                
                	try {
                			HttpFile myFile = doupld.getFiles().getFile(0);
                			PsDebug.log("upload.jsp "+myFile.getFileName());
                			if (!myFile.isMissing()) 
                			{
                				String fname		= ""+caseid+"-"+transid+"-"+myFile.getFileName();
                				PsDebug.log("upload.jsp saving file docs/"+fname);
                				myFile.saveAs("docs/"+fname);
                	
                				conn.sqlExec("INSERT INTO pattach VALUES("+caseid+","+transid+",'"+PsDbConn.cnv_sql(fname)+"',"+conn.now()+",'"+username+"')");
                			}					
                			
                	} catch (Exception e) { 
                		PsDebug.fail(e.toString());
                	} 
                	 
                
                	PsDebug.log("upload.jsp done");
                	
            // end
            // HTML // begin [file="/emessenger/upload.jsp";from=(67,3);to=(71,1)]
                out.write("\r\n\t<script language=\"JavaScript\">\r\n\twindow.close();\r\n\t</script>\r\n\t");

            // end
            // begin [file="/emessenger/upload.jsp";from=(71,3);to=(73,0)]
                
                 }
            // end
            // HTML // begin [file="/emessenger/upload.jsp";from=(73,2);to=(89,69)]
                out.write("\r\n\r\n</head>\r\n\r\n<BODY>\r\n<TABLE width=\"100%\">\r\n<TR>\r\n<TD width=\"2%\">\r\n&nbsp;\r\n</TD>\r\n<TD width=\"98%\">\r\n\r\n<TABLE class=Mtable id=TaskTable cellSpacing=0 cellPadding=0  width=\"100%\">\r\n        <TBODY>\r\n        <TR class=Bg>\r\n          <TD align=middle width=\"1%\" height=23><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/emessenger/upload.jsp";from=(89,72);to=(89,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/upload.jsp";from=(89,82);to=(96,0)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"96%\"><NOBR><FONT class=menu>TÃ©lÃ©chargement</FONT></NOBR></TD>\r\n        </TR>\r\n</TBODY>\r\n</TABLE>\r\n<br>\r\n\r\n");

            // end
            // begin [file="/emessenger/upload.jsp";from=(96,2);to=(99,0)]
                
                if (mode!=2)
                	{
            // end
            // HTML // begin [file="/emessenger/upload.jsp";from=(99,2);to=(101,0)]
                out.write("\r\nTÃ©lÃ©chargement de fichiers vers le cas:<br>\r\n");

            // end
            // begin [file="/emessenger/upload.jsp";from=(101,2);to=(105,0)]
                
                	PsDebug.log("upload.jsp caseid="+caseid+" transid="+transid);
                	rs=conn.sqlQueryR("SELECT * FROM pcase,ptrans WHERE pcase.caseid="+caseid+" AND pcase.caseid=ptrans.caseid AND ptrans.transid="+transid);
                	rs.next();
            // end
            // HTML // begin [file="/emessenger/upload.jsp";from=(105,2);to=(106,3)]
                out.write("\r\n<b>");

            // end
            // begin [file="/emessenger/upload.jsp";from=(106,6);to=(106,30)]
                out.print(rs.getString("casename"));
            // end
            // HTML // begin [file="/emessenger/upload.jsp";from=(106,32);to=(106,36)]
                out.write("<br>");

            // end
            // begin [file="/emessenger/upload.jsp";from=(106,39);to=(106,64)]
                out.print(rs.getString("transname"));
            // end
            // HTML // begin [file="/emessenger/upload.jsp";from=(106,66);to=(111,39)]
                out.write("</b>\r\n<br> \r\n<FORM action=\"upload.jsp\" method=\"POST\" ENCTYPE=\"multipart/form-data\">\r\n<INPUT TYPE=\"FILE\" style=\"width:100%\" NAME=FILE1>\r\n<INPUT TYPE=\"HIDDEN\" NAME=MODE VALUE=\"2\">\r\n<INPUT TYPE=\"HIDDEN\" NAME=CASEID VALUE=");

            // end
            // begin [file="/emessenger/upload.jsp";from=(111,42);to=(111,48)]
                out.print(caseid);
            // end
            // HTML // begin [file="/emessenger/upload.jsp";from=(111,50);to=(112,40)]
                out.write(" >\r\n<INPUT TYPE=\"HIDDEN\" NAME=TRANSID VALUE=");

            // end
            // begin [file="/emessenger/upload.jsp";from=(112,43);to=(112,50)]
                out.print(transid);
            // end
            // HTML // begin [file="/emessenger/upload.jsp";from=(112,52);to=(118,0)]
                out.write(" >\r\n<br><br>\r\n<p align=center>\r\n<INPUT TYPE=SUBMIT VALUE=\"Envoi du fichier\">\r\n</p>\r\n</FORM>\r\n");

            // end
            // begin [file="/emessenger/upload.jsp";from=(118,2);to=(120,0)]
                
                	}
            // end
            // HTML // begin [file="/emessenger/upload.jsp";from=(120,2);to=(124,0)]
                out.write("\r\n</TABLE>\r\n</BODY>\r\n</HTML>\r\n");

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
