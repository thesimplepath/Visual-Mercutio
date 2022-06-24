package org.apache.jsp;

import java.util.*;
import java.lang.*;
import java.sql.*;
import PsApp;
import PsDbMgr;
import PsDbConn;
import PsDebug;
import PsConfig;
import PsConv;
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

            // HTML // begin [file="/emessenger/newproc1.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(1,114);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(2,26);to=(5,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(5,0);to=(5,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(5,53);to=(6,0)]
                out.write("\r\n");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(6,2);to=(8,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(8,2);to=(9,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(9,19);to=(9,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(9,29);to=(99,2)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n<script language=JavaScript src=\"js/pss.js\"></script>\r\n<script language=JavaScript>\r\nvar jcaseid=-1;\r\nvar jtransid=-1;\r\nfunction doSetCb(frm,mcaseid,mtransid,mcasename,mtransname)\r\n{\r\n\tjcaseid=mcaseid;\r\n\tjtransid=mtransid;\r\n\tfrm.casename.value=mcasename;\r\n\t//frm.transname.value=mtransname;\r\n}\r\n\r\nfunction doSel(no)\r\n{\r\n\tdocument.all[\"Z1\"].style.visibility = \"hidden\";\r\n\tdocument.all[\"Z2\"].style.visibility = \"hidden\";\r\n\tdocument.all[\"Z3\"].style.visibility = \"hidden\";\r\n\tif (no==1) \tdocument.all[\"Z1\"].style.visibility = \"visible\";\t\t\r\n\tif (no==2) \tdocument.all[\"Z2\"].style.visibility = \"visible\";\t\t\r\n\tif (no==3) \tdocument.all[\"Z3\"].style.visibility = \"visible\";\t\t\t\t\r\n}\r\n</script>\r\n</head>\r\n<BODY>\r\n<TABLE class=msglistcntrl width=\"100%\" cellSpacing=2 cellPadding=0 border=0 >\r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <td width=\"8%\"></tb>\r\n    <TD width=\"81%\"class=NormalBlack vAlign=top width=\"89%\">\r\n  </TR>\r\n \r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <td width=\"8%\">Action :</tb>\r\n    <TD width=\"81%\"class=NormalBlack vAlign=top width=\"89%\"><input type=radio class=sbttn NAME=ACTION value=\"1\" onclick=\"doSel(1);\"> Nouveau cas\r\n  </TR>\r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <td width=\"8%\"></tb>\r\n    <TD width=\"81%\"class=NormalBlack vAlign=top width=\"89%\"><input type=radio class=sbttn NAME=ACTION value=\"2\" onclick=\"doSel(2);\"> Attacher   un cas existant\r\n  </TR>\r\n  \r\n  <TR>\r\n    <TD width=\"11%\">&nbsp;</TD>\r\n    <td width=\"8%\"></tb>\r\n    <TD width=\"81%\"class=NormalBlack vAlign=top width=\"89%\"><input type=radio class=sbttn NAME=ACTION value=\"3\" onclick=\"doSel(3);\"> Nouveau sous-cas\r\n  </TR>\r\n </table>\r\n <br>\r\n  <DIV ID=Z1 style=\"visibility:hidden;position:absolute;\">\r\n  <form name=\"F1\">\r\n  <TABLE class=msglistcntrl width=\"100%\" cellSpacing=2 cellPadding=0 border=0>\r\n  <tr>\r\n  <td width=\"11%\">&nbsp;</td>\r\n  <td width=\"8%\">Cas :</td>\r\n  <td width=\"81%\"><INPUT maxLength=80 size=80 name=casename></td>\r\n  </tr>\r\n  <tr>\r\n  <td width=\"11%\">&nbsp;</td>\r\n  <td width=\"8%\">Description :</td>\r\n  <td width=\"81%\"><INPUT maxLength=80 size=80 name=transname></td>\r\n  </tr>\r\n  <tr>\r\n  <td colspan=3 height=20>&nbsp;</td>\r\n  </tr>\r\n  <tr>\r\n  <td width=\"11%\">&nbsp;</td>\r\n  <td width=\"8%\">&nbsp;</td>\r\n  <td width=\"81%\"><INPUT class=sbttn title=\"CrÃ©er un nouveau.\" onclick=\"doSubmit(-1,-1,casename.value,transname.value);\" tabIndex=2 type=button value=\"DÃ©marrer\" name=create style=\"width:200px;\"></td>\r\n  </tr>\r\n  </table>\r\n  </form>\r\n  </div>\r\n  \r\n  <DIV ID=Z2 style=\"visibility:hidden;position:absolute;\">\r\n  <form name=\"F2\">\r\n  <TABLE class=msglistcntrl width=\"100%\" cellSpacing=2 cellPadding=0 border=0>\r\n  <tr valign=top>\r\n  <td width=\"11%\">&nbsp;</td>\r\n  <td width=\"8%\">Choisir un cas :</td>\r\n  <td width=\"81%\">\r\n  \r\n  <TABLE class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 width=\"100%\">\r\n\t  <TBODY>\r\n        <TR class=Bg>\r\n          <TD width=\"6%\" height=23>&nbsp; </TD>\r\n          <TD width=\"32%\"><NOBR><FONT class=swb>Cas existants</FONT></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"59%\"><NOBR><FONT class=swb>Processus</FONT></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n\t\t</TR>\r\n  ");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(99,4);to=(113,0)]
                
                 PsApp.init();
                
                 String username=(String)session.getAttribute("USERNAME");
                
                try {
                	PsDbConn conn=PsDbMgr.newConnection();
                	ResultSet rs;
                
                	rs=conn.sqlQueryR("SELECT count(*) as cnt,casename,transname ,ptrans.caseid,mvalue,ptrans.transid FROM pcase,ptrans,pproctrans,pproc,ppdattr WHERE ptrans.caseid=pproctrans.caseid AND ptrans.transid=pproctrans.transid AND ppdattr.pdattribid=pproc.pdattribid AND ppdattr.attribdefid=1310721 AND pproc.procid=pproctrans.procid AND pcase.caseid=pproctrans.caseid AND pproctrans.statusid in (0,1,2) GROUP BY casename,transname ORDER BY pcase.casename");
                
                	int cbcnt=0;
                	while (rs.next())
                	{
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(113,2);to=(115,83)]
                out.write("\r\n\t<TR>\r\n        <TD width=\"6%\" align=left><INPUT class=sbttn  onclick='doSetCb(document.F2,");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(115,86);to=(115,105)]
                out.print(rs.getInt("caseid"));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(115,107);to=(115,108)]
                out.write(",");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(115,111);to=(115,131)]
                out.print(rs.getInt("transid"));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(115,133);to=(115,135)]
                out.write(",\"");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(115,138);to=(115,175)]
                out.print(PsConv.c4JS(rs.getString("casename")));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(115,177);to=(115,180)]
                out.write("\",\"");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(115,183);to=(115,221)]
                out.print(PsConv.c4JS(rs.getString("transname")));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(115,223);to=(115,246)]
                out.write("\");' type=radio name=CB");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(115,249);to=(115,258)]
                out.print((cbcnt++));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(115,260);to=(117,24)]
                out.write(" >\r\n        </TD>\r\n        <TD width=\"32%\">");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(117,27);to=(117,51)]
                out.print(rs.getString("casename"));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(117,53);to=(117,55)]
                out.write(", ");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(117,58);to=(117,83)]
                out.print(rs.getString("transname"));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(117,85);to=(118,0)]
                out.write("</TD>\r\n");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(118,2);to=(121,0)]
                		
                        if (rs.getInt("cnt")==1) 
                		{
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(121,2);to=(122,21)]
                out.write("\t\t\r\n\t    <TD width=\"59%\">");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(122,24);to=(122,46)]
                out.print(rs.getString("mvalue"));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(122,48);to=(123,0)]
                out.write("</TD></TR>\r\n");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(123,2);to=(126,0)]
                		}			
                	else
                		{
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(126,2);to=(128,0)]
                out.write("\t\r\n\t    <TD width=\\\"59%\\\">...</TD></TR>\r\n");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(128,2);to=(137,0)]
                
                		}
                			
                	}
                    }
                catch (SQLException e)
                    {
                	PsDebug.fail("newcase1.jsp: SQLException: "+e.getMessage());
                    }
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(137,2);to=(176,2)]
                out.write("\r\n</TABLE>\r\n  </td>\r\n  </tr>\r\n  \r\n  <tr>  <td colspan=3 height=20>&nbsp;</td>  </tr>\r\n  \r\n  <tr>\r\n  <td width=\"11%\">&nbsp;</td>\r\n  <td width=\"8%\">Description :</td>\r\n  <td width=\"81%\"><input type=hidden name=casename><INPUT maxLength=80 size=80 name=transname></td>\r\n  </tr>\r\n  \r\n  <tr>  <td colspan=3 height=20>&nbsp;</td>  </tr>\r\n  \r\n  <tr>\r\n  <td width=\"11%\">&nbsp;</td>\r\n  <td width=\"8%\">&nbsp;</td>\r\n  <td width=\"81%\"><INPUT class=sbttn title=\"CrÃ©er un nouveau sous-cas Ã  partir du cas selectionnÃ©.\" onclick=\"doSubmit(jcaseid,jtransid,casename.value,transname.value);\" tabIndex=2 type=button value=\"DÃ©marrer\" name=createex style=\"width:200px;\"></td>\r\n  </tr>\r\n  </table>\r\n  </form>\r\n  </div>\r\n  \r\n  <DIV ID=Z3 style=\"visibility:hidden;position:absolute;\">\r\n  <form name=\"F3\">  \r\n  <TABLE class=msglistcntrl width=\"100%\" cellSpacing=2 cellPadding=0 border=0>\r\n  <tr valign=top>\r\n  <td width=\"11%\">&nbsp;</td>\r\n  <td width=\"8%\">Choisir un cas :</td>\r\n  <td width=\"81%\">\r\n  \r\n  <TABLE class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 width=\"100%\">\r\n\t  <TBODY>\r\n        <TR class=Bg>\r\n          <TD width=\"6%\" height=23>&nbsp; </TD>\r\n          <TD width=\"32%\"><NOBR><FONT class=swb>Cas existants</FONT></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n          <TD width=\"59%\"><NOBR><FONT class=swb>Processus</FONT></NOBR><NOBR></NOBR><NOBR>&nbsp;</NOBR></TD>\r\n\t\t</TR>\r\n  ");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(176,4);to=(187,0)]
                
                
                try {
                	PsDbConn conn=PsDbMgr.newConnection();
                	ResultSet rs;
                
                	rs=conn.sqlQueryR("SELECT count(*) as cnt,casename,transname ,ptrans.caseid,mvalue,ptrans.transid FROM pcase,ptrans,pproctrans,pproc,ppdattr WHERE ptrans.caseid=pproctrans.caseid AND ptrans.transid=pproctrans.transid AND ppdattr.pdattribid=pproc.pdattribid AND ppdattr.attribdefid=1310721 AND pproc.procid=pproctrans.procid AND pcase.caseid=pproctrans.caseid AND pproctrans.statusid in (0,1,2) GROUP BY casename,transname ORDER BY pcase.casename");
                
                	int cbcnt=0;
                	while (rs.next())
                	{
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(187,2);to=(189,83)]
                out.write("\r\n\t<TR>\r\n        <TD width=\"6%\" align=left><INPUT class=sbttn  onclick='doSetCb(document.F3,");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(189,86);to=(189,105)]
                out.print(rs.getInt("caseid"));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(189,107);to=(189,108)]
                out.write(",");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(189,111);to=(189,131)]
                out.print(rs.getInt("transid"));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(189,133);to=(189,135)]
                out.write(",\"");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(189,138);to=(189,175)]
                out.print(PsConv.c4JS(rs.getString("casename")));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(189,177);to=(189,180)]
                out.write("\",\"");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(189,183);to=(189,221)]
                out.print(PsConv.c4JS(rs.getString("transname")));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(189,223);to=(189,246)]
                out.write("\");' type=radio name=CB");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(189,249);to=(189,258)]
                out.print((cbcnt++));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(189,260);to=(191,24)]
                out.write(" >\r\n        </TD>\r\n        <TD width=\"32%\">");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(191,27);to=(191,51)]
                out.print(rs.getString("casename"));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(191,53);to=(191,55)]
                out.write(", ");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(191,58);to=(191,83)]
                out.print(rs.getString("transname"));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(191,85);to=(192,0)]
                out.write("</TD>\r\n");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(192,2);to=(195,0)]
                		
                        if (rs.getInt("cnt")==1) 
                		{
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(195,2);to=(196,21)]
                out.write("\t\t\r\n\t    <TD width=\"59%\">");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(196,24);to=(196,46)]
                out.print(rs.getString("mvalue"));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(196,48);to=(197,0)]
                out.write("</TD></TR>\r\n");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(197,2);to=(200,0)]
                		}			
                	else
                		{
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(200,2);to=(202,0)]
                out.write("\t\r\n\t    <TD width=\\\"59%\\\">...</TD></TR>\r\n");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(202,2);to=(211,0)]
                
                		}
                			
                	}
                    }
                catch (SQLException e)
                    {
                	PsDebug.fail("newcase1.jsp: SQLException: "+e.getMessage());
                    }
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(211,2);to=(241,10)]
                out.write("\r\n</TABLE>\r\n  </td>\r\n  </tr>\r\n  \r\n  <tr>  <td colspan=3 height=20>&nbsp;</td>  </tr>\r\n  \r\n  <tr>\r\n  <td width=\"11%\">&nbsp;</td>\r\n  <td width=\"8%\">Description :</td>\r\n  <td width=\"81%\"><input type=hidden name=casename><INPUT maxLength=80 size=80 name=transname></td>\r\n  </tr>\r\n  \r\n  <tr>  <td colspan=3 height=20>&nbsp;</td>  </tr>\r\n  \r\n  <tr>\r\n  <td width=\"11%\">&nbsp;</td>\r\n  <td width=\"8%\">&nbsp;</td>\r\n  <td width=\"81%\"><INPUT class=sbttn title=\"CrÃ©er un nouveau sous-cas Ã  partir du cas selectionnÃ©.\" onclick=\"doSubmit(jcaseid,-1,casename.value,transname.value);\" tabIndex=2 type=button value=\"DÃ©marrer\" name=createsc style=\"width:200px;\"></td>\r\n  </tr>\r\n  </table>\r\n  </form>\r\n  </div>\r\n     \r\n<SCRIPT language=javascript>\r\nfunction doSubmit(caseattachid,transattachid,casename,transname) {\r\n\tvar fromproc=-1; //no previous procedure\r\n\tvar transid;\r\n\r\n\tif (transattachid<0)\r\n\t\ttransid=");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(241,13);to=(241,54)]
                out.print(PsDbMgr.newConnection().nextVal("PTRANS"));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(241,56);to=(244,43)]
                out.write(";\r\n\telse\r\n\t\ttransid=transattachid;\r\n\tvar dta=new PssData(caseattachid,casename,");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(244,46);to=(244,86)]
                out.print((String)request.getParameter( "PROCID" ));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(244,88);to=(244,89)]
                out.write(",");

            // end
            // begin [file="/emessenger/newproc1.jsp";from=(244,92);to=(244,130)]
                out.print((String)session.getAttribute("USERID"));
            // end
            // HTML // begin [file="/emessenger/newproc1.jsp";from=(244,132);to=(260,7)]
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
