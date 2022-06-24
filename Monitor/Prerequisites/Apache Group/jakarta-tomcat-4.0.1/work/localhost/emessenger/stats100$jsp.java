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
import PsConv;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class stats100$jsp extends HttpJspBase {


    static {
    }
    public stats100$jsp( ) {
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

            // HTML // begin [file="/stats100.jsp";from=(0,0);to=(1,0)]
                out.write("ï»¿<html>\r\n");

            // end
            // HTML // begin [file="/stats100.jsp";from=(1,119);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/stats100.jsp";from=(2,26);to=(5,0)]
                out.write("\r\n<head>\r\n<META http-equiv=Content-Type content=\"text/html; charset=utf-8\">\r\n");

            // end
            // begin [file="/stats100.jsp";from=(5,0);to=(5,53)]
                {
                    String _jspx_qStr = "";
                    JspRuntimeLibrary.include(request, response, "checksession.jsp" + _jspx_qStr, out, false);
                }
            // end
            // HTML // begin [file="/stats100.jsp";from=(5,53);to=(6,0)]
                out.write("\r\n");

            // end
            // begin [file="/stats100.jsp";from=(6,2);to=(8,0)]
                
                 String userskin="skin"+(String)session.getAttribute("USERSKIN");
            // end
            // HTML // begin [file="/stats100.jsp";from=(8,2);to=(9,16)]
                out.write("\r\n<link href=\"css/");

            // end
            // begin [file="/stats100.jsp";from=(9,19);to=(9,27)]
                out.print(userskin);
            // end
            // HTML // begin [file="/stats100.jsp";from=(9,29);to=(12,0)]
                out.write("/global.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n</head>\r\n");

            // end
            // begin [file="/stats100.jsp";from=(12,2);to=(45,0)]
                
                  PsApp.init();
                
                  String username=(String)session.getAttribute("USERNAME");
                  if (username==null) return;
                  int userid=		Integer.valueOf((String)session.getAttribute( "USERID")).intValue();
                  int userrole=		Integer.valueOf((String)session.getAttribute( "USERROLE")).intValue();
                 
                  int modelid=1;//TODO
                
                  PsDbConn conn,conn2;
                  ResultSet rs,rs2;
                  conn=PsDbMgr.newConnection();	
                  conn2=PsDbMgr.newConnection();	
                
                  String searchKey=request.getParameter( "KEYSEARCH" );
                  if (searchKey==null)
                	searchKey="";
                
                  PsWorkGroup w=new PsWorkGroup();
                  Vector r=w.listProcAllGranted(username);
                  int l=r.size();
                  String procin;
                  procin="";
                  //build the proc granted list
                  for (int i=0;i<l;i++)
                  {
                	int proc=((Integer)r.elementAt(i)).intValue();
                	procin+=proc;
                	if (i<l-1)
                		procin+=",";
                  }		
                
            // end
            // HTML // begin [file="/stats100.jsp";from=(45,2);to=(57,71)]
                out.write("\r\n<body>\r\n<FORM action=\"stats100.jsp\" method=POST>\r\n<INPUT TYPE=HIDDEN NAME=MODE VALUE=2>\r\n<TABLE width=\"100%\" border=0>\r\n  <TR>\r\n    <TD width=\"1%\">&nbsp;</TD>\r\n    <TD class=NormalBlack vAlign=top width=\"99%\" nobr>\r\n      <TABLE class=Mtable id=MsgTable cellSpacing=0 cellPadding=0 width=\"100%\">\r\n\t<TR class=Bg>\r\n\t<TD width=\"3%\">&nbsp;</TD>\r\n\t<TD width=\"6%\">Recherche:</TD>\r\n\t<TD width=\"81%\" colspan=6><input type=\"text\" NAME=\"KEYSEARCH\"  value=\"");

            // end
            // begin [file="/stats100.jsp";from=(57,74);to=(57,83)]
                out.print(searchKey);
            // end
            // HTML // begin [file="/stats100.jsp";from=(57,85);to=(64,69)]
                out.write("\" style=\"width:100%;\"></td>\r\n\t<TD width=\"10%\" align=center><input type=submit class=sbttn value=\"Recherche\"></TD>\r\n\t</TR>\r\n\r\n\t<TR height=5><td colspan=9>&nbsp;</td></tr>\r\n\t\r\n\t<TR class=Bg>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;<img src=\"img/");

            // end
            // begin [file="/stats100.jsp";from=(64,72);to=(64,80)]
                out.print(userskin);
            // end
            // HTML // begin [file="/stats100.jsp";from=(64,82);to=(74,0)]
                out.write("/ard.gif\"></TD>\r\n          <TD width=\"6%\"><NOBR><FONT class=menu>Nombre</FONT>&nbsp;</NOBR></TD>\r\n\t  <TD width=\"6%\"><NOBR><FONT class=menu>Charge j*h</FONT>&nbsp;</NOBR></TD>\r\n\t  <TD width=\"26%\"><NOBR><FONT class=menu>Combinaisons</FONT>&nbsp;</NOBR></TD>\r\n\t  <TD width=\"20%\"><NOBR><FONT class=menu>ProcÃ©dure</FONT>&nbsp;</NOBR></TD>\r\n\t  <TD width=\"12%\"><NOBR><FONT class=menu>Age moyen</FONT>&nbsp;</NOBR></TD>\r\n\t  <TD width=\"12%\"><NOBR><FONT class=menu>Ligne verte</FONT>&nbsp;</NOBR></TD>\r\n\t  <TD width=\"6%\"><NOBR><FONT class=menu>Ecart %</FONT>&nbsp;</NOBR></TD>\r\n\t  <TD align=\"right\" width=\"3%\"><NOBR><FONT class=menu>Statut</FONT>&nbsp;</NOBR></TD>\r\n\t</TR>\r\n");

            // end
            // begin [file="/stats100.jsp";from=(74,2);to=(180,0)]
                
                	rs=conn.sqlQueryR("SELECT distinct pcase.caseid,ptrans.transid,pproc.procid as procid,ppdattr.mvalue as mvalue ,pstatus.*,pproctrans.*,pproc.*,pmodel.*,pcase.*,ppdattr.*,ptrans.* FROM ptrans,ppdattr,pstatus,pproctrans,pproc,pmodel,pcase WHERE ptrans.caseid=pcase.caseid AND ptrans.transid=pproctrans.transid AND pstatus.statusid=pproctrans.statusid AND pproctrans.statusid<=9 AND pcase.caseid=pproctrans.caseid AND pmodel.modelid=pproc.modelid AND pproctrans.procid=pproc.procid AND pproc.procid in ("+procin+") AND (pcase.casename like '%"+searchKey+"%' OR ptrans.transname like '%"+searchKey+"%') AND ppdattr.pdattribid=pproc.pdattribid AND ppdattr.attribdefid=1310721 GROUP BY pcase.txindate,pcase.caseid,ptrans.transid,pproctrans.caseid,pproctrans.procid");
                	String combinationname="";
                	int number=0;
                	int masterid=-1;
                	Calendar now;
                	long nowt;
                	while (rs.next())
                	{
                	int caseid=rs.getInt("caseid");
                	int transid=rs.getInt("transid");
                	int procid=rs.getInt("procid");
                
                	rs2=conn2.sqlQueryR("SELECT count(pdeliv.delivid) as number,pdeliv.delivname,pdelivstatus.mdated FROM pdeliv,pdelivstatus WHERE pdelivstatus.procid=pdeliv.procidsrc AND pdelivstatus.caseid="+rs.getInt("caseid")+" AND pdelivstatus.transid="+rs.getInt("transid")+" AND pdelivstatus.delivid=pdeliv.delivid AND procidtrg="+procid+" GROUP BY pdeliv.delivid");
                
                	if (rs2.next()==true)
                	{
                	combinationname=rs2.getString("delivname");//find out the right master
                	number=rs2.getInt("number");
                
                	//get info about master deliv - greenLine
                	masterid=PsWf.getMasterDelivFromCombination(modelid,procid,caseid,transid);
                	}//if rs2.next	
                
                	now=Calendar.getInstance();
                	nowt=now.get(Calendar.DAY_OF_YEAR)*86400+now.get(Calendar.HOUR_OF_DAY)*3600+now.get(Calendar.MINUTE)*60+now.get(Calendar.SECOND);
                	String tmp="";
                	rs2=conn2.sqlQueryR("SELECT ppdattr.mvalue FROM pdeliv,ppdattr WHERE pdeliv.modelid="+modelid+" AND pdeliv.delivid="+masterid+" AND ppdattr.pdattribid=pdeliv.delivid AND ppdattr.attribdefid=15728647 ORDER BY ppdattr.attribdefid");		
                	if (rs2.next()==true)
                		tmp=rs2.getString("mvalue").trim();
                	if (tmp.length()==0)
                		tmp="0";
                
                
                	tmp+="d 0:0:0"; //WARNING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!temporary fix
                
                
                System.out.println("*************"+tmp);
                	long greenLinet=0;
                	if (tmp.length()>0)
                	{
                		try 
                		{
                		StringTokenizer st = new StringTokenizer(tmp,"d");
                		greenLinet=Integer.valueOf((String)st.nextToken()).intValue()*24*3600;
                		StringTokenizer st2 = new StringTokenizer(st.nextToken().trim(),":");
                		greenLinet+=Integer.valueOf((String)st2.nextToken()).intValue()*3600;
                		greenLinet+=Integer.valueOf((String)st2.nextToken()).intValue()*60;
                		greenLinet+=Integer.valueOf((String)st2.nextToken()).intValue();
                		}
                		catch (NoSuchElementException e)
                		{
                			PsDebug.log("Green line has unexpected format: '"+tmp+"'");
                			greenLinet=0; //default value
                		}
                	}
                
                System.out.println("*************");
                	//get charge/Activation of procedure
                	double chargeActivation=0.0;
                	rs2=conn2.sqlQueryR("SELECT mvalue FROM ppdattr,pattribdef WHERE ppdattr.attribdefid=pattribdef.attribdefid and ppdattr.attribdefid=36700165 and ppdattr.pdattribid="+procid);
                	if (rs2.next()==true)
                	{
                		chargeActivation=Double.valueOf(rs2.getString("mvalue").trim()).doubleValue();;
                	}
                
                	//calculate median time
                	long medianTime=0;
                	long medianCount=0;	
                	rs2=conn2.sqlQueryR("SELECT pdeliv.delivname,pdelivstatus.mdated FROM pdeliv,pdelivstatus WHERE pdelivstatus.procid=pdeliv.procidsrc AND pdelivstatus.caseid="+rs.getInt("caseid")+" AND pdelivstatus.transid="+rs.getInt("transid")+" AND pdelivstatus.delivid=pdeliv.delivid AND procidtrg="+procid);
                	while (rs2.next())
                	{
                		Calendar dt=PsConv.parseSqlDate(rs2.getString("mdated"));
                
                		long lt=dt.get(Calendar.DAY_OF_YEAR)*86400+dt.get(Calendar.HOUR_OF_DAY)*3600+dt.get(Calendar.MINUTE)*60+dt.get(Calendar.SECOND);
                System.out.println("lt="+lt+" nowt="+nowt+"  "+dt.get(Calendar.DAY_OF_YEAR)+","+dt.get(Calendar.HOUR_OF_DAY)+","+dt.get(Calendar.MINUTE));
                System.out.println("    "+now.get(Calendar.DAY_OF_YEAR)+","+now.get(Calendar.HOUR_OF_DAY)+","+now.get(Calendar.MINUTE));
                		medianTime+=(nowt-lt);
                		medianCount++;	
                	}
                	if (medianCount!=0)
                		medianTime/=medianCount;
                	else
                		medianTime=0;
                
                	double deltaPercent;//ecart
                	deltaPercent=medianTime*100.0;
                	if (greenLinet!=0.0)
                		deltaPercent/=greenLinet;
                	else
                		deltaPercent=0.0;
                	if (medianTime<greenLinet)
                		deltaPercent*=-1;
                	int vtmp=(int)(deltaPercent*100);
                	deltaPercent=(double)(vtmp)/100.0;
                
                	String color="green";
                	if (deltaPercent<=100.0)
                	{}
                	else
                	if (deltaPercent<=105.0)
                	{color="orange";}
                	else
                	if (deltaPercent>105.0)
                	{color="red";}
                
            // end
            // HTML // begin [file="/stats100.jsp";from=(180,2);to=(183,48)]
                out.write("\r\n\t<TR>\r\n          <TD width=\"3%\" height=23 valign=bottom>&nbsp;</TD>\r\n          <TD width=\"6%\"><NOBR><FONT class=menu>");

            // end
            // begin [file="/stats100.jsp";from=(183,51);to=(183,57)]
                out.print(number);
            // end
            // HTML // begin [file="/stats100.jsp";from=(183,59);to=(184,41)]
                out.write("</FONT>&nbsp;</NOBR></TD>\r\n\t  <TD width=\"6%\"><NOBR><FONT class=menu>");

            // end
            // begin [file="/stats100.jsp";from=(184,44);to=(184,67)]
                out.print(chargeActivation*number);
            // end
            // HTML // begin [file="/stats100.jsp";from=(184,69);to=(185,36)]
                out.write("</FONT>&nbsp;</NOBR></TD>\r\n\t  <TD width=\"26%\"><FONT class=menu>");

            // end
            // begin [file="/stats100.jsp";from=(185,39);to=(185,54)]
                out.print(combinationname);
            // end
            // HTML // begin [file="/stats100.jsp";from=(185,56);to=(186,36)]
                out.write("</FONT>&nbsp;</TD>\r\n\t  <TD width=\"20%\"><FONT class=menu>");

            // end
            // begin [file="/stats100.jsp";from=(186,39);to=(186,61)]
                out.print(rs.getString("mvalue"));
            // end
            // HTML // begin [file="/stats100.jsp";from=(186,63);to=(187,42)]
                out.write("</FONT>&nbsp;</TD>\r\n\t  <TD width=\"12%\"><NOBR><FONT class=menu>");

            // end
            // begin [file="/stats100.jsp";from=(187,45);to=(187,87)]
                out.print(PsConv.secondsFrom1970ToString(medianTime));
            // end
            // HTML // begin [file="/stats100.jsp";from=(187,89);to=(188,42)]
                out.write("</FONT>&nbsp;</NOBR></TD>\r\n\t  <TD width=\"12%\"><NOBR><FONT class=menu>");

            // end
            // begin [file="/stats100.jsp";from=(188,45);to=(188,87)]
                out.print(PsConv.secondsFrom1970ToString(greenLinet));
            // end
            // HTML // begin [file="/stats100.jsp";from=(188,89);to=(189,41)]
                out.write("</FONT>&nbsp;</NOBR></TD>\r\n\t  <TD width=\"6%\"><NOBR><FONT class=menu>");

            // end
            // begin [file="/stats100.jsp";from=(189,44);to=(189,56)]
                out.print(deltaPercent);
            // end
            // HTML // begin [file="/stats100.jsp";from=(189,58);to=(190,69)]
                out.write("</FONT>&nbsp;</NOBR></TD>\r\n\t  <TD align=\"right\" width=\"3%\"><NOBR><FONT class=menu><img src=\"img/");

            // end
            // begin [file="/stats100.jsp";from=(190,72);to=(190,77)]
                out.print(color);
            // end
            // HTML // begin [file="/stats100.jsp";from=(190,79);to=(192,0)]
                out.write(".gif\" border=\"0\"></FONT>&nbsp;</NOBR></TD>\r\n\t</TR>\r\n");

            // end
            // begin [file="/stats100.jsp";from=(192,2);to=(194,0)]
                
                	}
            // end
            // HTML // begin [file="/stats100.jsp";from=(194,2);to=(201,7)]
                out.write("\r\n\r\n      </TABLE>\r\n     </TD>\r\n   </TR>\r\n</TABLE>\r\n</body>\r\n</html>");

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
