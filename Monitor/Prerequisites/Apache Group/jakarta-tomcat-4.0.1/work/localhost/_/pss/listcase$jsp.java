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
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class listcase$jsp extends HttpJspBase {


    static {
    }
    public listcase$jsp( ) {
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

            // HTML // begin [file="/pss/listcase.jsp";from=(0,32);to=(1,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/listcase.jsp";from=(1,32);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/listcase.jsp";from=(2,31);to=(3,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/listcase.jsp";from=(3,26);to=(4,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/listcase.jsp";from=(4,28);to=(5,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/listcase.jsp";from=(5,29);to=(6,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/listcase.jsp";from=(6,28);to=(7,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/listcase.jsp";from=(7,29);to=(8,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/listcase.jsp";from=(8,32);to=(9,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/pss/listcase.jsp";from=(9,25);to=(17,0)]
                out.write("\r\n\r\n<html>\r\n<head>\r\n<link href=\"css/doc.css\" rel=\"styleSheet\" type=\"text/css\"> \r\n<script language=JavaScript src=\"js/pss.js\"></script>\r\n<script language=JavaScript>\r\n<!--\r\n");

            // end
            // begin [file="/pss/listcase.jsp";from=(17,2);to=(25,0)]
                
                //session check
                 String xusername=(String)session.getAttribute( "USERNAME");
                 int    userrole;
                 if (xusername==null) 
                   out.println("alert('Not logged');");
                 else
                   userrole=Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();
            // end
            // HTML // begin [file="/pss/listcase.jsp";from=(25,2);to=(60,0)]
                out.write("\r\n//-->\r\n</script>\r\n\r\n<script language=JavaScript>\r\n<!--\r\nfunction doChangeStatus(mode,caseid,transid,statusid)\r\n{\r\n\tvar url;\r\n\turl=document.location;\r\n\tdocument.location=\"statustrans.jsp?MODE=\"+mode+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&STATUSID=\"+statusid+\"&REDIRECT=\"+url;\r\n}\r\n\r\nfunction sendChief(procid,caseid,transid)\r\n{\r\n//  alert(\"Send to chief \"+procid+\" / \"+transid);\r\n  document.location=\"chief.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid;\r\n}\r\n\r\nfunction doStartDeliv(procid,caseid,transid,delivid,lateral)\r\n{\r\n//  alert(\"Start Deliv :\"+delivid);\r\n  document.location=\"deliv.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid+\"&DELIVID=\"+delivid+\"&LATERAL=\"+lateral;\r\n}\r\n\r\nfunction retSender(procid,caseid,transid)\r\n{\r\n//  alert(\"Retour a l'envoyeur\");\r\n  document.location=\"return.jsp?PROCID=\"+procid+\"&CASEID=\"+caseid+\"&TRANSID=\"+transid;\r\n}\r\n\r\n//-->\r\n</script>\r\n</head>\r\n<body>\r\n");

            // end
            // begin [file="/pss/listcase.jsp";from=(60,2);to=(184,0)]
                
                 PsApp.init();
                
                 String username=(String)session.getAttribute("USERNAME");
                 int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
                 userrole=		Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();
                
                out.println("Liste des procedures libres pour <i>"+username+"</i>");
                if (userrole==2)
                 out.println("&nbsp;&nbsp;(Chef)");
                out.println("<hr>");
                
                try {
                	PsDbConn conn=PsDbMgr.newConnection();
                	PsDbConn conn2=PsDbMgr.newConnection();
                	ResultSet rs;
                	ResultSet rs2;
                
                	PsWorkGroup w=new PsWorkGroup();
                 	Vector r=w.listProcAllGranted(username);
                 	int l=r.size();
                	String procin;
                	procin="";
                 	for (int i=0;i<l;i++)
                 	{
                		int proc=((Integer)r.elementAt(i)).intValue();
                		procin+=proc;
                		if (i<l-1)
                			procin+=",";
                	}
                
                	String chefflag;
                	chefflag="";
                	if (userrole==3) //hide "remise au chef" for simple employees
                		chefflag=" AND chiefflag=0";
                
                	rs=conn.sqlQueryR("SELECT distinct pcase.caseid ,pstatus.*,pproctrans.*,pproc.*,pmodel.*,pcase.* FROM pstatus,pproctrans,pproc,pmodel,pcase WHERE pstatus.statusid=pproctrans.statusid AND pproctrans.statusid<=9 AND pcase.caseid=pproctrans.caseid AND pmodel.modelid=pproc.modelid AND pproctrans.procid=pproc.procid AND pproc.procid in ("+procin+") AND (pproctrans.statusid in (0,2) OR (pproctrans.statusid=1 AND pproctrans.emplid="+userid+")) "+chefflag+" GROUP BY pcase.caseid,pproctrans.caseid");
                	while (rs.next())
                	{
                	String xx;
                	xx="";
                	
                	out.println(rs.getString("modelname")+": #"+rs.getInt("procid")+" => "+rs.getString("casename")+" ("+rs.getString("statusname")+"/"+rs.getInt("emplid")+") "+xx+"<br>");
                
                	int procid=rs.getInt("procid");
                	rs2=conn2.sqlQueryR("SELECT pprocattr.attribdefid as attribdefid,pprocattr.mvalue as mvalue FROM pproc,pprocattr WHERE pproc.procid="+procid+" AND pproc.procattribid=pprocattr.procattribid AND pprocattr.attribdefid>=13 AND pprocattr.attribdefid<=32");
                	//tasks
                	while (rs2.next())
                	{
                		if (rs2.getString("mvalue").length()>0)
                			out.println("&nbsp;&nbsp;Task ("+rs2.getInt("attribdefid")+") = "+rs2.getString("mvalue")+"<br>");
                	}
                	//decisions
                	rs2=conn2.sqlQueryR("SELECT * FROM pproc,pprocattr WHERE pproc.procid="+procid+" AND pproc.procattribid=pprocattr.procattribid AND pprocattr.attribdefid>=33 AND pprocattr.attribdefid<=52");
                	while (rs2.next())
                	{
                		if (rs2.getString("mvalue").length()>0)
                			out.println("&nbsp;&nbsp;Decision ("+rs2.getInt("attribdefid")+") = "+rs2.getString("mvalue")+"<br>");
                	}
                
                int transid=0;
                int caseid=rs.getInt("caseid");
                	rs2=conn2.sqlQueryR("SELECT pproctrans.statusid as sid,pstatus.statusname as sname,pstatus.*,pcase.*,pproctrans.*,ptrans.* FROM pstatus,pcase,pproctrans,ptrans WHERE ptrans.transid=pproctrans.transid AND pstatus.statusid=pproctrans.statusid AND pproctrans.statusid<=9 AND pcase.caseid="+rs.getInt("caseid")+" AND pcase.caseid=pproctrans.caseid AND (pproctrans.statusid in (0,2) OR (pproctrans.statusid=1 AND pproctrans.emplid="+userid+")) AND pproctrans.procid in ("+procin+")");
                	//open cases
                	while (rs2.next())
                	 {
                	transid=rs.getInt("transid");
                		if (rs2.getInt("sid")==0 || rs2.getInt("sid")==2)		
                		xx="<input type=button value=\"bloquer\" onclick=\"doChangeStatus(1,"+rs.getInt("procid")+","+rs.getInt("transid")+",1);\">";
                		if (rs2.getInt("sid")==1)
                			xx="<input type=button value=\"liberer\" onclick=\"doChangeStatus(1,"+rs.getInt("procid")+","+rs.getInt("transid")+",2);\">";
                		if (rs2.getInt("sid")==1)
                		{
                			xx+="<br>&nbsp;&nbsp;Livrable lateraux:";
                			PsDbConn c1=PsDbMgr.newConnection();
                			ResultSet rx2=c1.sqlQueryR("SELECT * FROM pdeliv WHERE procidsrc="+rs.getInt("procid")+" AND lateral=1");
                			while (rx2.next())
                			{
                				xx+="<input type=button value=\""+rx2.getString("delivname")+"\" onclick=\"doStartDeliv("+procid+","+caseid+","+transid+","+rx2.getString("delivid")+",1);\">";
                
                				PsDbConn kc=PsDbMgr.newConnection();
                				int retdelivid=PsWf.getLateralReturn(procid,rx2.getInt("delivid"));
                				ResultSet ks=kc.sqlQueryR("SELECT openclose FROM pdelivlateralstate WHERE procid="+procid+" AND caseid="+caseid+" AND transid="+transid+" AND delivid="+retdelivid);
                				if (ks.next()==true)
                				{
                					if (ks.getInt("openclose")==1)
                						xx+="(done) ";
                					else
                						xx+="(wait) ";
                				}
                
                				//mendatory deliv
                				double pct=PsWf.percentageDeliv(rx2.getInt("delivid"));
                				if (pct>=99.999)
                					xx+="(mandatory) ";
                				
                			}
                
                			xx+="<br>&nbsp;&nbsp;Livrable:";
                			PsDbConn c=PsDbMgr.newConnection();
                			ResultSet rx=c.sqlQueryR("SELECT * FROM pdeliv WHERE procidsrc="+rs.getInt("procid")+" AND lateral=0");
                			while (rx.next())
                			{
                				xx+="<input type=button value=\""+rx.getString("delivname")+"\" onclick=\"doStartDeliv("+procid+","+caseid+","+transid+","+rx.getInt("delivid")+",0);\">";
                
                				//mendatory deliv
                				double pct=PsWf.percentageDeliv(rx.getInt("delivid"));
                				if (pct>=99.999)
                					xx+="(mandatory) ";
                
                			}
                		}
                		out.println("&nbsp;&nbsp;&nbsp;<a href=\"showattrib.jsp?CASEID="+rs2.getInt("caseid")+"&TRANSID="+rs2.getInt("transid")+"\">"+rs2.getInt("transid")+"</a> : "+rs2.getString("transname")+" ("+rs2.getString("statusname")+"/"+rs2.getInt("emplid")+")"+xx+"<br>");
                	 }
                	out.println("<input type=button value=\"Retour à l'envoyeur\" onclick=\"retSender("+procid+","+caseid+","+transid+");\">");
                if (userrole==3)
                        out.println("<input type=button value=\"Remise au chef\" onclick=\"sendChief("+procid+","+caseid+","+transid+");\">");
                out.println("<hr><hr>");
                	}
                    }
                catch (SQLException e)
                    {
                	PsDebug.fail("listcase.jsp: SQLException: "+e.getMessage());
                    }
            // end
            // HTML // begin [file="/pss/listcase.jsp";from=(184,2);to=(186,7)]
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
