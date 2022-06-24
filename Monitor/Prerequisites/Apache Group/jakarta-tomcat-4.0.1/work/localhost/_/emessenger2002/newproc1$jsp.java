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
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class newproc1$jsp extends HttpJspBase {


    static {
    }
    public newproc1$jsp( ) {
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

            // HTML // begin [file="/emessenger2002/newproc1.jsp";from=(0,32);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc1.jsp";from=(1,32);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc1.jsp";from=(2,31);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc1.jsp";from=(3,26);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc1.jsp";from=(4,28);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc1.jsp";from=(5,29);to=(6,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc1.jsp";from=(6,28);to=(7,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc1.jsp";from=(7,29);to=(8,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger2002/newproc1.jsp";from=(8,32);to=(44,0)]
                out.write("\r\n<html>\r\n<head>\r\n<LINK href=\"css/global.css\" rel=STYLESHEET type=\"text/css\">\r\n<script language=JavaScript src=\"js/pss.js\"></script>\r\n</head>\r\n<BODY text=#000000 vLink=#666666 link=#003399 bgColor=#ffffff leftMargin=0 topMargin=0 MARGINHEIGHT=0 MARGINWIDTH=0>\r\n<TABLE width=\"100%\" border=0>\r\n  <TBODY>\r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"89%\">\r\n      <TABLE class=msglistcntrl id=msglistcntrl cellSpacing=2 cellPadding=0 \r\n      border=0>\r\n        <TBODY>\r\n        <TR>          \r\n          <TD width=188><INPUT maxLength=80 size=80 name=casename> </TD>\r\n          <TD noWrap align=right width=121>\r\n\t<INPUT class=sbttn title=\"Créer un nouveau cas à partir du nom saisi.\" onclick=\"doSubmit(-1,casename.value,transname.value);\" tabIndex=2 type=button value=\"Nouveau cas\" name=create> \r\n          </TD></FORM></TR></TBODY></TABLE></TD>\r\n  <TR>\r\n \t<TD width=\"11%\">&nbsp;</TD>\r\n\t<TD class=NormalBlack vAlign=top width=\"89%\">\r\n\t<INPUT maxLength=80 size=80 name=transname>\r\n\t</TD>\r\n  </TR>\r\n  <TR>\r\n    <TD width=\"11%\" height=559>&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"89%\" height=559>\r\n      <TABLE class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 \r\n        width=\"100%\"><TBODY>\r\n        <TR bgColor=#336699>\r\n          <TD align=middle width=\"3%\"><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"6%\" height=23>&nbsp; </TD>\r\n          <TD width=\"32%\"><NOBR><FONT class=swb color=#ffffff>Cas existants</FONT></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"59%\"><NOBR><FONT class=swb color=#ffffff>Processus</FONT></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD></TR>\r\n");

            // end
            // begin [file="/emessenger2002/newproc1.jsp";from=(44,2);to=(67,0)]
                
                 PsApp.init();
                
                 String username=(String)session.getAttribute("USERNAME");
                
                try {
                	PsDbConn conn=PsDbMgr.newConnection();
                	ResultSet rs;
                	rs=conn.sqlQueryR("SELECT casename,ptrans.caseid,mvalue,transname FROM pcase,ptrans,pproctrans,pproc,ppdattr WHERE ptrans.caseid=pproctrans.caseid AND ptrans.transid=pproctrans.transid AND ppdattr.pdattribid=pproc.pdattribid AND ppdattr.prow=0 AND pproc.procid=pproctrans.procid AND pcase.caseid=pproctrans.caseid AND pproctrans.statusid in (0,1,2) ORDER BY pcase.casename");
                	while (rs.next())
                	{
                        out.println("<TR>");
                        out.println("  <TD width=\"3%\">&nbsp;</TD>");
                        out.println("  <TD width=\"6%\"><INPUT onclick='doSubmit("+rs.getInt("caseid")+",\""+rs.getString("casename")+"\",transname.value);' type=checkbox> ");
                        out.println("  </TD>");
                        out.println("  <TD width=\"32%\">"+rs.getString("casename")+" "+rs.getString("transname")+"</TD>");
                        out.println("  <TD width=\"59%\">"+rs.getString("mvalue")+"</TD></TR>");
                	}
                    }
                catch (SQLException e)
                    {
                	PsDebug.fail("newcase1.jsp: SQLException: "+e.getMessage());
                    }
            // end
            // HTML // begin [file="/emessenger2002/newproc1.jsp";from=(67,2);to=(75,13)]
                out.write("\r\n</TBODY></TABLE>\r\n    </TD></FORM></TR></TBODY></TABLE>\r\n<SCRIPT language=javascript>\r\n//top.menu.showTab(4);\r\n\r\nfunction doSubmit(caseattachid,casename,transname) {\r\n\tvar fromproc=-1; //no previous procedure\r\n\tvar transid=");

            // end
            // begin [file="/emessenger2002/newproc1.jsp";from=(75,16);to=(75,57)]
                out.print(PsDbMgr.newConnection().nextVal("PTRANS"));
            // end
            // HTML // begin [file="/emessenger2002/newproc1.jsp";from=(75,59);to=(76,43)]
                out.write(";\r\n\tvar dta=new PssData(caseattachid,casename,");

            // end
            // begin [file="/emessenger2002/newproc1.jsp";from=(76,46);to=(76,86)]
                out.print((String)request.getParameter( "PROCID" ));
            // end
            // HTML // begin [file="/emessenger2002/newproc1.jsp";from=(76,88);to=(76,89)]
                out.write(",");

            // end
            // begin [file="/emessenger2002/newproc1.jsp";from=(76,92);to=(76,130)]
                out.print((String)session.getAttribute("USERID"));
            // end
            // HTML // begin [file="/emessenger2002/newproc1.jsp";from=(76,132);to=(92,7)]
                out.write(",transname,transid,0,0,0,-1);\r\n\t//var cnt=0;\r\n\t//for (i=0;i<rowid;i++)\r\n\t{\r\n\t//\tvar mkey=document.FRM.all[\"PSSKEY\"+i];\r\n\t//\tvar mval=document.FRM.all[\"PSSVAL\"+i];\r\n\r\n\t//\tif (mkey!=null)\r\n\t\t{\r\n\t//\t\tdta.addAttrib(new PssDataAttrib(i,mkey.name,mkey.value,mval.value));\r\n\t\t}\r\n\t}\r\n\tdta.post(\"newproc2.jsp\");\r\n}\r\n</script>\r\n</body>\r\n</html>");

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
