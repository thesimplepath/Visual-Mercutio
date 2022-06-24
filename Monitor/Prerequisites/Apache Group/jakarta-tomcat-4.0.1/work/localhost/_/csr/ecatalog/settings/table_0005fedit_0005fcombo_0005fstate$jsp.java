package org.apache.jsp;

import ApimApp;
import ApimDbMgr;
import ApimDbConn;
import ApimDebug;
import ApimConfig;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.jsp.*;
import org.apache.jasper.runtime.*;


public class table_0005fedit_0005fcombo_0005fstate$jsp extends HttpJspBase {


    static {
    }
    public table_0005fedit_0005fcombo_0005fstate$jsp( ) {
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

            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(0,0);to=(1,0)]
                out.write("<html>\r\n");

            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(1,26);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(2,80);to=(9,0)]
                out.write("\r\n<head>\r\n<META HTTP-EQUIV=\"Content-type\" CONTENT=\"text/html; charset=UTF-8\">\r\n<link href=\"../../css/style.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n<script language=\"javascript\" src=\"../../js/dbadmin.js\"></script>\r\n<script language=\"JavaScript\">\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(9,2);to=(20,0)]
                
                 String msg=	request.getParameter( "MSG" );
                 String tablename=	request.getParameter( "TABLE" );
                 String refresh=	request.getParameter( "REFRESH" );
                 String nbstart=        request.getParameter( "NBSTART" );
                 String nbend=        request.getParameter( "NBEND" );
                 if (refresh!=null && refresh.toUpperCase().equals("YES")==true)
                 {
                	String sUrl="../../ecatalog/settings/onglet.jsp?TABLENAME="+tablename;
                	out.println("top.onglet.document.location=\""+sUrl+"\";");
                 } 
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(20,2);to=(23,0)]
                out.write("\r\n</script>\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(23,2);to=(38,0)]
                
                 ApimApp.init();
                
                 int dbtype=9;//TODO read it from configuration
                
                 ApimDbConn conn=ApimDbMgr.newConnection();
                 ResultSet rs;
                
                 rs=conn.sqlQueryR("SELECT count(*) as nbline from "+tablename);
                 rs.next();
                 int nbline=rs.getInt("nbline");
                
                 int nbresult=10;
                
                 rs=conn.sqlQueryR("SELECT gcountry.country as country,gcountry.idcountry as idcountry FROM gcountry ORDER BY country");
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(38,2);to=(46,0)]
                out.write("\r\n\r\n<script language=\"JavaScript\">\r\n<!--\r\n\tfunction country(idcountry)\r\n\t\t{\r\n\t\t\tvar combocountry = \"\";\r\n\t\t\tcombocountry = \"<select name=\\\"IDCOUNTRY\\\">\";\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(46,2);to=(49,1)]
                
                	while(rs.next())
                	{
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(49,3);to=(50,21)]
                out.write("\r\n\t\t\t\tif (idcountry == ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(50,24);to=(50,46)]
                out.print(rs.getInt("idcountry"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(50,48);to=(52,38)]
                out.write(")\r\n\t\t\t\t\t{\r\n\t\t\t\t\tcombocountry += \"<option value=\\\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(52,41);to=(52,63)]
                out.print(rs.getInt("idcountry"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(52,65);to=(52,77)]
                out.write("\\\" selected>");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(52,80);to=(52,103)]
                out.print(rs.getString("country"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(52,105);to=(56,38)]
                out.write("</option>\";\r\n\t\t\t\t\t}\r\n\t\t\t\telse\r\n\t\t\t\t\t{\r\n\t\t\t\t\tcombocountry += \"<option value=\\\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(56,41);to=(56,63)]
                out.print(rs.getInt("idcountry"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(56,65);to=(56,68)]
                out.write("\\\">");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(56,71);to=(56,94)]
                out.print(rs.getString("country"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(56,96);to=(58,1)]
                out.write("</option>\";\r\n\t\t\t\t\t}\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(58,3);to=(60,1)]
                
                	}
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(60,3);to=(81,15)]
                out.write("\r\n\t\t\tcombocountry += \"</select>\";\r\n\t\t\treturn combocountry;\r\n\t\t}\r\n//-->\r\n</script>\r\n\r\n\r\n\r\n\r\n<script language=\"JavaScript\">\r\n<!--\r\nfunction savefrm()\r\n{\t\t\t\r\n\tdocument.addressfrm.submit();\r\n}\t\r\n\t\r\nvar oArray \t\t\t= new oFieldsArray();\r\n\t\t\r\nfunction genPages()\r\n{\r\n\tvar nbLine\t\t= ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(81,18);to=(81,24)]
                out.print(nbline);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(81,26);to=(82,16)]
                out.write(";\r\n\tvar nbResult\t= ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(82,19);to=(82,27)]
                out.print(nbresult);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(82,29);to=(85,70)]
                out.write(";\r\n\tvar nbPages\t\t= parseInt(nbLine / nbResult) + 1;\r\n\t\r\n\tvar sUrl = \"../../ecatalog/settings/table_edit_combo_state.jsp?TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(85,73);to=(85,82)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(85,84);to=(150,0)]
                out.write("\";\r\n\t\r\n\tvar nbStart = -9;\r\n\tvar nbEnd\t= nbResult;\r\n\t\t\r\n\tfor(i=1; i <= nbPages; i++)\r\n\t{\r\n\t\tif (i == 1)\r\n\t\t{\r\n\t\t\tnbStart = 1;\r\n\t\t}\r\n\t\telse\r\n\t\t{\r\n\t\t\tnbStart = nbEnd;\r\n\t\t}\r\n\t\tnbEnd\t= i * nbResult;\r\n\t\tdocument.writeln(\"<a href=\\\"\"+ sUrl +\"&NBSTART=\"+ nbStart +\"&NBEND=\"+ nbEnd +\"\\\" class\\\"mmenu\\\">\"+ i +\"</a>\");\r\n\t}\r\n}\r\n\r\nfunction ReplaceQuote(theForm) \r\n{ \r\n\tvar ElemVal = \"\"; \r\n\tvar posn = 0; \r\n\tvar nstring = \"\"; \r\n\tvar c = \"\"; \r\n\tvar newval = \"\";\r\n\r\n\tfor (i = 0; i < document[theForm].length; i++) \r\n\t{ \r\n\r\n\tif (document[theForm].elements[i].type == \"text\" || document[theForm].elements[i].type == \"hidden\" || document[theForm].elements[i].type == \"textarea\")\r\n\t{\r\n\t\tElemVal = document[theForm].elements[i].value; \r\n\t\tposn = document[theForm].elements[i].value.length; \r\n\t\t \r\n\t\tfor (var j=0; j < posn; j++) \r\n\t\t{ \r\n\t\t\tc = ElemVal.substring(j,j+1);\r\n\t\t\t\r\n\t\t\tif (c == \"'\") \r\n\t\t\t{ \r\n\t\t\t\tnstring += \"`\"; \r\n\t\t\t} \r\n\t\t\telse \r\n\t\t\t{ \r\n\t\t\t\tnstring += c; \r\n\t\t\t} \r\n\t\t}\r\n\t\t\r\n\t\tnewval = nstring;\r\n\t\tif (document[theForm].elements[i].type == \"text\" || document[theForm].elements[i].type == \"hidden\" || document[theForm].elements[i].type == \"textarea\")\r\n\t\t{\r\n\t\t\tdocument[theForm].elements[i].value = newval; \r\n\t\t}\r\n\t\tnstring = \"\";\r\n\t}\r\n  }\r\n  return;  \r\n}\r\n\t\t\r\n//-->\r\n</script>\r\n\r\n<script language=\"javascript\">\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(150,2);to=(154,1)]
                
                	rs=conn.sqlQueryR("SELECT a.fkey as fkey,a.idfield as idfield,c.fieldtype as fieldtype,b.typename as typename,a.name as name,a.minlength as minlength,a.maxlength as maxlength,a.publics as publics,a.acols as acols,a.arows as arows,a.required as required,a.allowed as allowed,a.freadonly as freadonly,a.fvisible as fvisible,a.fprecint as fprecint,a.fprecdec as fprecdec FROM gfields a, gviewtype b, gfieldtype c, gtables d WHERE a.idviewtype = b.idviewtype and a.idfieldtype = c.idfieldtype and a.idtable = d.idtable and d.name = '"+tablename+"' ORDER BY a.idfield");
                	while (rs.next())
                	{
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(154,3);to=(155,19)]
                out.write("\r\n\t\toArray.AddFields(");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,22);to=(155,42)]
                out.print(rs.getInt("idfield"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,44);to=(155,46)]
                out.write(",'");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,49);to=(155,58)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,60);to=(155,63)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,66);to=(155,91)]
                out.print(rs.getString("fieldtype"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,93);to=(155,96)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,99);to=(155,123)]
                out.print(rs.getString("typename"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,125);to=(155,128)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,131);to=(155,151)]
                out.print(rs.getString("name"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,153);to=(155,155)]
                out.write("',");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,158);to=(155,178)]
                out.print(rs.getString("fkey"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,180);to=(155,181)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,184);to=(155,190)]
                out.print(dbtype);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,192);to=(155,193)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,196);to=(155,221)]
                out.print(rs.getString("minlength"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,223);to=(155,224)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,227);to=(155,252)]
                out.print(rs.getString("maxlength"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,254);to=(155,255)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,258);to=(155,281)]
                out.print(rs.getString("publics"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,283);to=(155,284)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,287);to=(155,308)]
                out.print(rs.getString("acols"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,310);to=(155,311)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,314);to=(155,335)]
                out.print(rs.getString("arows"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,337);to=(155,339)]
                out.write(",'");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,342);to=(155,366)]
                out.print(rs.getString("required"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,368);to=(155,371)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,374);to=(155,397)]
                out.print(rs.getString("allowed"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,399);to=(155,401)]
                out.write("',");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,404);to=(155,429)]
                out.print(rs.getString("freadonly"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,431);to=(155,432)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,435);to=(155,459)]
                out.print(rs.getString("fvisible"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,461);to=(155,462)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,465);to=(155,489)]
                out.print(rs.getString("fprecint"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,491);to=(155,492)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,495);to=(155,519)]
                out.print(rs.getString("fprecdec"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(155,521);to=(156,1)]
                out.write(");\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(156,3);to=(158,0)]
                
                	}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(158,2);to=(170,18)]
                out.write("\r\n\t\r\n\tfunction sendUpdate(frmName)\r\n\t{\r\n\t\tvar sUrl = \"../../ecatalog/settings/action.jsp?ACTION=32\";\r\n\t\t\r\n\t\tReplaceQuote(frmName);\r\n\t\t\r\n\t\tsUrl += \"&STATEID=\"+ document[frmName].IDSTATE.value;\r\n\t\tsUrl += \"&COUNTRYID=\"+ document[frmName].IDCOUNTRY.value;\r\n\t\tsUrl += \"&CODE=\"+ document[frmName].CODE.value;\r\n\t\tsUrl += \"&TEXT=\"+ document[frmName].TEXT.value;\r\n\t\tsUrl += \"&TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(170,21);to=(170,30)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(170,32);to=(182,19)]
                out.write("\";\r\n\t\t\r\n\t\tdocument.location = sUrl;\r\n\t}\r\n\t\r\n\tfunction sendDelete(frmName,id)\r\n\t{\r\n\t\tvar Hnd = confirm(\"Are you sure to delete this Element ?\");\r\n\t\tif (Hnd == true)\r\n\t\t{\r\n\t\t\tvar sUrl = \"../../ecatalog/settings/action.jsp?ACTION=33\";\r\n\t\t\tsUrl += \"&STATEID=\"+ document[frmName].IDSTATE.value;\r\n\t\t\tsUrl += \"&TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(182,22);to=(182,31)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(182,33);to=(198,18)]
                out.write("\";\r\n\t\t\r\n\t\t\tdocument.location = sUrl;\r\n\t\t}\r\n\t\treturn;\r\n\t}\r\n\t\r\n\tfunction sendInsert(frmName)\r\n\t{\r\n\t\tvar sUrl = \"../../ecatalog/settings/action.jsp?ACTION=31\";\r\n\t\t\r\n\t\tReplaceQuote(frmName);\r\n\t\t\r\n\t\tsUrl += \"&COUNTRYID=\"+ document[frmName].IDCOUNTRY.value;\r\n\t\tsUrl += \"&CODE=\"+ document[frmName].CODE.value;\r\n\t\tsUrl += \"&TEXT=\"+ document[frmName].TEXT.value;\r\n\t\tsUrl += \"&TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(198,21);to=(198,30)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(198,32);to=(207,0)]
                out.write("\";\r\n\t\t\r\n\t\tdocument.location = sUrl;\r\n\t}\r\n</script>\r\n</head>\r\n\r\n<body bgcolor=\"#F6F6F6\" leftmargin=\"0\" rightmargin=\"0\" topmargin=\"0\" marginwidth=\"0\" marginheight=\"0\">\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(207,2);to=(210,1)]
                
                	if (msg!=null)
                	{
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(210,3);to=(211,46)]
                out.write("\r\n\t<b><font color=\"Red\" size=\"3\" class=\"notice\">");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(211,49);to=(211,52)]
                out.print(msg);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(211,54);to=(212,1)]
                out.write("</font></b>\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(212,3);to=(214,0)]
                
                	}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(214,2);to=(234,0)]
                out.write("\r\n\r\n<!--start nesting content table--> \r\n<table bgcolor=\"#CFD9E2\" border=0 cellspacing=0 cellpadding=0 width=\"100\"> \r\n <tr><td> \r\n <!--start content table--> \r\n  <table border=0 width=\"100\" cellspacing=1 cellpadding=2 width=\"98%\"> \r\n         <tr bgcolor=\"#CFD9E2\"> \r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"15\">&nbsp;</td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>COUNTRY</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>CODE</b></td>\r\n\t  \t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>TEXT</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>SYNCUSER</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>SYNCINDATE</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>SYNCUPDATE</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>&nbsp;</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"left\"><b>&nbsp;</b></td>\r\n\t\t </tr> \r\n<!-- start content row --> \r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(234,2);to=(243,3)]
                
                	rs=conn.sqlQueryR("SELECT distinct idcountry,idstate,code,text,syncuser,syncindate,syncupdate from gstate order by code,text,idcountry");
                	try 
                	{
                		int incr=1;
                		while (rs.next())
                		{
                			if ((nbstart!=null && incr>=Integer.valueOf(nbstart).intValue() && incr<Integer.valueOf(nbend).intValue())||(nbstart==null && incr<10))
                			{
                			
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(243,5);to=(245,18)]
                out.write("\r\n\t\t<tr bgcolor=\"#E2E8ED\"> \r\n\t\t<form name=\"FORM");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(245,21);to=(245,25)]
                out.print(incr);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(245,27);to=(246,32)]
                out.write("\" action=\"\" method=\"post\">\r\n\t\t  <input type=\"hidden\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(246,35);to=(246,44)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(246,46);to=(247,32)]
                out.write("\" name=\"TABLE\">\r\n\t\t  <input type=\"hidden\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(247,35);to=(247,58)]
                out.print(rs.getString("idstate"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(247,60);to=(252,29)]
                out.write("\" name=\"IDSTATE\">\r\n\t\t  <td bgcolor=\"#AFBFCD\" class=\"corps\" align=\"center\" width=\"15\"><img src=\"../../img/ecatalog/button/b_flopen.gif\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"20\">\r\n\t\t\t<script language=\"JavaScript\">\r\n\t\t\t<!--\r\n\t\t\t\tdocument.writeln(country(");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(252,32);to=(252,57)]
                out.print(rs.getString("idcountry"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(252,59);to=(256,104)]
                out.write("));\r\n\t\t\t//-->\r\n\t\t\t</script>\r\n\t\t  </td>\r\n\t  \t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"CODE\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(256,107);to=(256,127)]
                out.print(rs.getString("code"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(256,129);to=(257,102)]
                out.write("\" size=\"5\" maxlength=\"5\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"TEXT\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(257,105);to=(257,125)]
                out.print(rs.getString("text"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(257,127);to=(258,106)]
                out.write("\" size=\"25\" maxlength=\"255\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"SYNCUSER\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(258,109);to=(258,133)]
                out.print(rs.getString("syncuser"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(258,135);to=(259,108)]
                out.write("\" size=\"5\" maxlength=\"5\" style=\"background-color:#E2E8ED align:center; border-width:0;\" disabled></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"SYNCINDATE\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(259,111);to=(259,137)]
                out.print(rs.getString("syncindate"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(259,139);to=(260,108)]
                out.write("\" size=\"8\" maxlength=\"20\" style=\"background-color:#E2E8ED; border-width:0;\" disabled></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"SYNCUPDATE\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(260,111);to=(260,137)]
                out.print(rs.getString("syncupdate"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(260,139);to=(261,107)]
                out.write("\" size=\"8\" maxlength=\"20\" style=\"background-color:#E2E8ED; border-width:0;\" disabled></td>\r\n\t\t  <td class=\"corps\" align=\"left\" width=\"20\"><input type=\"button\" value=\"Update\" onclick=\"sendUpdate('FORM");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(261,110);to=(261,114)]
                out.print(incr);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(261,116);to=(262,96)]
                out.write("');\"></td>\r\n\t\t  <td class=\"corps\" align=\"left\"><input type=\"button\" value=\"Delete\" onclick=\"sendDelete('FORM");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(262,99);to=(262,103)]
                out.print(incr);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(262,105);to=(262,107)]
                out.write("',");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(262,110);to=(262,133)]
                out.print(rs.getString("idstate"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(262,135);to=(265,3)]
                out.write(");\"></td>\r\n\t\t</form>\r\n\t  </tr>\r\n\t\t\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(265,5);to=(274,0)]
                
                			}
                		incr++;
                		}
                	}
                	catch(SQLException e)
                	{
                		ApimDebug.fail("Exception:"+e.getMessage());
                	}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_state.jsp";from=(274,2);to=(327,7)]
                out.write("\r\n   </table> \r\n <!--end content table--> \r\n  </td> \r\n </tr>  \r\n</table> \r\n<!--end nesting content table--> \r\n<br>\r\n<font size=\"3\" class=\"corps\">\r\nPages :&nbsp;\r\n<script language=\"JavaScript\">\r\n\tgenPages();\r\n</script>\r\n</font>\r\n\r\n<br>\r\n<br>\r\n<!--start nesting content table--> \r\n<table bgcolor=\"#CFD9E2\" border=0 cellspacing=0 cellpadding=0 width=\"100\"> \r\n <tr><td> \r\n <!--start content table--> \r\n  <table border=0 width=\"100\" cellspacing=1 cellpadding=2 width=\"98%\"> \r\n         <tr bgcolor=\"#CFD9E2\"> \r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"15\">&nbsp;</td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>COUNTRY</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>CODE</b></td>\r\n\t  \t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>TEXT</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>&nbsp;</b></td>\r\n\t\t </tr> \r\n<!-- start content row --> \r\n\t\t<tr bgcolor=\"#E2E8ED\"> \r\n\t\t<form name=\"frmInsert\" action=\"\" method=\"post\">\r\n\t\t  <td bgcolor=\"#AFBFCD\" class=\"corps\" align=\"center\" width=\"15\"><img src=\"../../img/ecatalog/button/b_flopen.gif\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"20\">\r\n\t\t\t<script language=\"JavaScript\">\r\n\t\t\t<!--\r\n\t\t\t\tdocument.writeln(country(-1));\r\n\t\t\t//-->\r\n\t\t\t</script>\r\n\t\t  </td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"CODE\" value=\"\" size=\"5\" maxlength=\"5\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"TEXT\" value=\"\" size=\"25\" maxlength=\"255\"></td>\r\n\t\t  <td class=\"corps\" width=\"20\"><input type=\"button\" value=\"Insert\" onclick=\"sendInsert('frmInsert');\"></td> \r\n\t\t</form>\r\n\t  </tr>\r\n   </table> \r\n <!--end content table--> \r\n  </td> \r\n </tr>  \r\n</table> \r\n<!--end nesting content table--> \r\n\r\n</body>\r\n</html>");

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
