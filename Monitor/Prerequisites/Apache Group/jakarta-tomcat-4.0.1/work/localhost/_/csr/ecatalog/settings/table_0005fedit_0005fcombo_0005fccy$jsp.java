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


public class table_0005fedit_0005fcombo_0005fccy$jsp extends HttpJspBase {


    static {
    }
    public table_0005fedit_0005fcombo_0005fccy$jsp( ) {
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

            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(0,0);to=(1,0)]
                out.write("<html>\r\n");

            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(1,26);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(2,80);to=(9,0)]
                out.write("\r\n<head>\r\n<META HTTP-EQUIV=\"Content-type\" CONTENT=\"text/html; charset=UTF-8\">\r\n<link href=\"../../css/style.css\" rel=\"styleSheet\" type=\"text/css\">\r\n\r\n<script language=\"javascript\" src=\"../../js/dbadmin.js\"></script>\r\n<script language=\"JavaScript\">\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(9,2);to=(20,0)]
                
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
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(20,2);to=(23,0)]
                out.write("\r\n</script>\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(23,2);to=(38,0)]
                
                 ApimApp.init();
                
                 int dbtype=9;//TODO read it from configuration
                
                 ApimDbConn conn=ApimDbMgr.newConnection();
                 ResultSet rs;
                
                 rs=conn.sqlQueryR("SELECT count(*) as nbline from "+tablename);
                 rs.next();
                 int nbline=rs.getInt("nbline");
                
                 int nbresult=10;
                
                 rs=conn.sqlQueryR("SELECT country,idcountry from gcountry order by country");
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(38,2);to=(45,0)]
                out.write("\r\n<script language=\"JavaScript\">\r\n<!--\r\n\tfunction country(idcountry)\r\n\t\t{\r\n\t\t\tvar combocountry = \"\";\r\n\t\t\tcombocountry = \"<select name=\\\"IDCOUNTRY\\\">\";\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(45,2);to=(48,1)]
                
                	while(rs.next())
                	{
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(48,3);to=(49,21)]
                out.write("\r\n\t\t\t\tif (idcountry == ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(49,24);to=(49,46)]
                out.print(rs.getInt("idcountry"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(49,48);to=(51,38)]
                out.write(")\r\n\t\t\t\t\t{\r\n\t\t\t\t\tcombocountry += \"<option value=\\\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(51,41);to=(51,63)]
                out.print(rs.getInt("idcountry"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(51,65);to=(51,77)]
                out.write("\\\" selected>");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(51,80);to=(51,103)]
                out.print(rs.getString("country"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(51,105);to=(55,38)]
                out.write("</option>\";\r\n\t\t\t\t\t}\r\n\t\t\t\telse\r\n\t\t\t\t\t{\r\n\t\t\t\t\tcombocountry += \"<option value=\\\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(55,41);to=(55,63)]
                out.print(rs.getInt("idcountry"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(55,65);to=(55,68)]
                out.write("\\\">");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(55,71);to=(55,94)]
                out.print(rs.getString("country"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(55,96);to=(57,1)]
                out.write("</option>\";\r\n\t\t\t\t\t}\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(57,3);to=(59,1)]
                
                	}
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(59,3);to=(78,15)]
                out.write("\r\n\t\t\tcombocountry += \"</select>\";\r\n\t\t\treturn combocountry;\r\n\t\t}\r\n//-->\r\n</script>\r\n\r\n\r\n<script language=\"JavaScript\">\r\n<!--\r\nfunction savefrm()\r\n{\t\t\t\r\n\tdocument.addressfrm.submit();\r\n}\t\r\n\t\r\nvar oArray \t\t\t= new oFieldsArray();\r\n\t\t\r\nfunction genPages()\r\n{\r\n\tvar nbLine\t\t= ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(78,18);to=(78,24)]
                out.print(nbline);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(78,26);to=(79,16)]
                out.write(";\r\n\tvar nbResult\t= ");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(79,19);to=(79,27)]
                out.print(nbresult);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(79,29);to=(82,68)]
                out.write(";\r\n\tvar nbPages\t\t= parseInt(nbLine / nbResult) + 1;\r\n\t\r\n\tvar sUrl = \"../../ecatalog/settings/table_edit_combo_ccy.jsp?TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(82,71);to=(82,80)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(82,82);to=(158,0)]
                out.write("\";\r\n\t\r\n\tvar nbStart = -9;\r\n\tvar nbEnd\t= nbResult;\r\n\t\t\r\n\tfor(i=1; i <= nbPages; i++)\r\n\t{\r\n\t\tif (i == 1)\r\n\t\t{\r\n\t\t\tnbStart = 1;\r\n\t\t}\r\n\t\telse\r\n\t\t{\r\n\t\t\tnbStart = nbEnd;\r\n\t\t}\r\n\t\tnbEnd\t= i * nbResult;\r\n\t\tdocument.writeln(\"<a href=\\\"\"+ sUrl +\"&NBSTART=\"+ nbStart +\"&NBEND=\"+ nbEnd +\"\\\" class\\\"mmenu\\\">\"+ i +\"</a>\");\r\n\t}\r\n}\r\n\r\nfunction showCalendar(formName,field)\r\n{\r\n\tvar\thwnd = null;\r\n\tsUrl = \"../../ecatalog/calendar.jsp?FIELD=\"+ field+\"&FORMNAME=\"+formName;\r\n\r\n\t\r\n\tif (hwnd != null) {\r\n\thwnd.close();\r\n\t}\r\n\thwnd = window.open(sUrl,\"\",\"resizable=yes,width=260,height=250\");\r\n}\t\r\n\r\nfunction ReplaceQuote(theForm) \r\n\t{ \r\n\t\tvar ElemVal = \"\"; \r\n\t\tvar posn = 0; \r\n\t\tvar nstring = \"\"; \r\n\t\tvar c = \"\"; \r\n\t\tvar newval = \"\";\r\n\r\n\t\tfor (i = 0; i < document[theForm].length; i++) \r\n\t\t{ \r\n\r\n\t\tif (document[theForm].elements[i].type == \"text\" || document[theForm].elements[i].type == \"hidden\" || document[theForm].elements[i].type == \"textarea\")\r\n\t\t{\r\n\t\t\tElemVal = document[theForm].elements[i].value; \r\n\t\t\tposn = document[theForm].elements[i].value.length; \r\n\t\t\t \r\n\t\t\tfor (var j=0; j < posn; j++) \r\n\t\t\t{ \r\n\t\t\t\tc = ElemVal.substring(j,j+1);\r\n\t\t\t\t\r\n\t\t\t\tif (c == \"'\") \r\n\t\t\t\t{ \r\n\t\t\t\t\tnstring += \"`\"; \r\n\t\t\t\t} \r\n\t\t\t\telse \r\n\t\t\t\t{ \r\n\t\t\t\t\tnstring += c; \r\n\t\t\t\t} \r\n\t\t\t}\r\n\t\t\t\r\n\t\t\tnewval = nstring;\r\n\t\t\tif (document[theForm].elements[i].type == \"text\" || document[theForm].elements[i].type == \"hidden\" || document[theForm].elements[i].type == \"textarea\")\r\n\t\t\t{\r\n\t\t\t\tdocument[theForm].elements[i].value = newval; \r\n\t\t\t}\r\n\t\t\tnstring = \"\";\r\n\t\t}\r\n\t  }\r\n\t  return;  \r\n\t}\r\n\r\n//-->\r\n</script>\r\n<script language=\"javascript\">\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(158,2);to=(162,1)]
                
                	rs=conn.sqlQueryR("SELECT a.fkey as fkey,a.idfield as idfield,c.fieldtype as fieldtype,b.typename as typename,a.name as name,a.minlength as minlength,a.maxlength as maxlength,a.publics as publics,a.acols as acols,a.arows as arows,a.required as required,a.allowed as allowed,a.freadonly as freadonly,a.fvisible as fvisible,a.fprecint as fprecint,a.fprecdec as fprecdec FROM gfields a, gviewtype b, gfieldtype c, gtables d WHERE a.idviewtype = b.idviewtype and a.idfieldtype = c.idfieldtype and a.idtable = d.idtable and d.name = '"+tablename+"' ORDER BY a.idfield");
                	while (rs.next())
                	{
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(162,3);to=(163,19)]
                out.write("\r\n\t\toArray.AddFields(");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,22);to=(163,42)]
                out.print(rs.getInt("idfield"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,44);to=(163,46)]
                out.write(",'");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,49);to=(163,58)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,60);to=(163,63)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,66);to=(163,91)]
                out.print(rs.getString("fieldtype"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,93);to=(163,96)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,99);to=(163,123)]
                out.print(rs.getString("typename"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,125);to=(163,128)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,131);to=(163,151)]
                out.print(rs.getString("name"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,153);to=(163,155)]
                out.write("',");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,158);to=(163,178)]
                out.print(rs.getString("fkey"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,180);to=(163,181)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,184);to=(163,190)]
                out.print(dbtype);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,192);to=(163,193)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,196);to=(163,221)]
                out.print(rs.getString("minlength"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,223);to=(163,224)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,227);to=(163,252)]
                out.print(rs.getString("maxlength"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,254);to=(163,255)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,258);to=(163,281)]
                out.print(rs.getString("publics"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,283);to=(163,284)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,287);to=(163,308)]
                out.print(rs.getString("acols"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,310);to=(163,311)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,314);to=(163,335)]
                out.print(rs.getString("arows"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,337);to=(163,339)]
                out.write(",'");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,342);to=(163,366)]
                out.print(rs.getString("required"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,368);to=(163,371)]
                out.write("','");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,374);to=(163,397)]
                out.print(rs.getString("allowed"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,399);to=(163,401)]
                out.write("',");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,404);to=(163,429)]
                out.print(rs.getString("freadonly"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,431);to=(163,432)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,435);to=(163,459)]
                out.print(rs.getString("fvisible"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,461);to=(163,462)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,465);to=(163,489)]
                out.print(rs.getString("fprecint"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,491);to=(163,492)]
                out.write(",");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,495);to=(163,519)]
                out.print(rs.getString("fprecdec"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(163,521);to=(164,1)]
                out.write(");\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(164,3);to=(166,1)]
                
                	}
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(166,3);to=(180,18)]
                out.write("\r\n\t\r\n\tfunction sendUpdate(frmName)\r\n\t{\r\n\t\tvar sUrl = \"../../ecatalog/settings/action.jsp?ACTION=52\";\r\n\t\t\r\n\t\tReplaceQuote(frmName);\r\n\t\t\r\n\t\tsUrl += \"&CCYID=\"+ document[frmName].IDCCY.value;\r\n\t\tsUrl += \"&IDCOUNTRY=\"+ document[frmName].IDCOUNTRY.value;\r\n\t\tsUrl += \"&ISOCCY=\"+ document[frmName].ISOCCY.value;\r\n\t\tsUrl += \"&CCY=\"+ document[frmName].CCY.value;\r\n\t\tsUrl += \"&RATE=\"+ document[frmName].RATE.value;\r\n\t\tsUrl += \"&DATED=\"+ document[frmName].DATED.value;\r\n\t\tsUrl += \"&TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(180,21);to=(180,30)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(180,32);to=(192,19)]
                out.write("\";\r\n\t\t\r\n\t\tdocument.location = sUrl;\r\n\t}\r\n\t\r\n\tfunction sendDelete(frmName,id)\r\n\t{\r\n\t\tvar Hnd = confirm(\"Are you sure to delete this Element ?\");\r\n\t\tif (Hnd == true)\r\n\t\t{\r\n\t\t\tvar sUrl = \"../../ecatalog/settings/action.jsp?ACTION=53\";\r\n\t\t\tsUrl += \"&CCYID=\"+ id;\r\n\t\t\tsUrl += \"&TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(192,22);to=(192,31)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(192,33);to=(210,18)]
                out.write("\";\r\n\t\t\r\n\t\t\tdocument.location = sUrl;\r\n\t\t}\r\n\t\treturn;\r\n\t}\r\n\t\r\n\tfunction sendInsert(frmName)\r\n\t{\r\n\t\tvar sUrl = \"../../ecatalog/settings/action.jsp?ACTION=51\";\r\n\t\t\r\n\t\tReplaceQuote(frmName);\r\n\t\t\r\n\t\tsUrl += \"&IDCOUNTRY=\"+ document[frmName].IDCOUNTRY.value;\r\n\t\tsUrl += \"&ISOCCY=\"+ document[frmName].ISOCCY.value;\r\n\t\tsUrl += \"&CCY=\"+ document[frmName].CCY.value;\r\n\t\tsUrl += \"&RATE=\"+ document[frmName].RATE.value;\r\n\t\tsUrl += \"&DATED=\"+ document[frmName].DATED.value;\r\n\t\tsUrl += \"&TABLE=");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(210,21);to=(210,30)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(210,32);to=(239,0)]
                out.write("\";\r\n\t\t\r\n\t\tdocument.location = sUrl;\r\n\t}\r\n\t\r\n\tfunction formatNbr(nbre)\r\n\t{\r\n\t\tvar posn = nbre.indexOf(\".\",0);\r\n\t\tvar nstring = \"\";\r\n\t\r\n\t\tif (posn==0)\r\n\t\t{\r\n\t\t\tnstring = \"0\"+ nbre.substring(0,posn+3)\r\n\t\t}\r\n\t\telse if (posn>=0)\r\n\t\t{\r\n\t\t\tnstring = nbre.substring(0,posn+3)\r\n\t\t}\r\n\t\telse\r\n\t\t{\r\n\t\t\tnstring = nbre + \"00\";\r\n\t\t}\r\n\t\treturn nstring;\r\n\t}\r\n</script>\r\n</head>\r\n\r\n<body bgcolor=\"#F6F6F6\" leftmargin=\"0\" rightmargin=\"0\" topmargin=\"0\" marginwidth=\"0\" marginheight=\"0\">\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(239,2);to=(242,1)]
                
                	if (msg!=null)
                	{
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(242,3);to=(243,46)]
                out.write("\r\n\t<b><font color=\"Red\" size=\"3\" class=\"notice\">");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(243,49);to=(243,52)]
                out.print(msg);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(243,54);to=(244,1)]
                out.write("</font></b>\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(244,3);to=(246,0)]
                
                	}
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(246,2);to=(268,0)]
                out.write("\r\n\r\n<!--start nesting content table--> \r\n<table bgcolor=\"#CFD9E2\" border=0 cellspacing=0 cellpadding=0 width=\"100\"> \r\n <tr><td> \r\n <!--start content table--> \r\n  <table border=0 width=\"100\" cellspacing=1 cellpadding=2 width=\"98%\"> \r\n         <tr bgcolor=\"#CFD9E2\"> \r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"15\">&nbsp;</td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>COUNTRY</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>ISOCODE</b></td>\r\n\t  \t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>CCY</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>RATE</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"90\" nowrap><b>DATED</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>SYNCUSER</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>SYNCINDATE</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>SYNCUPDATE</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"20\"><b>&nbsp;</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"left\"><b>&nbsp;</b></td>\r\n\t\t </tr> \r\n<!-- start content row --> \r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(268,2);to=(277,3)]
                
                	rs=conn.sqlQueryR("SELECT idccy,idcountry,isoccy,ccy,rate,dated,syncuser,syncindate,syncupdate FROM gccy ORDER BY ccy");
                	try 
                	{
                		int incr=1;
                		while (rs.next())
                		{
                			if ((nbstart!=null && incr>=Integer.valueOf(nbstart).intValue() && incr<Integer.valueOf(nbend).intValue())||(nbstart==null && incr<10))
                			{
                			
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(277,5);to=(279,19)]
                out.write("\r\n\t\t<tr bgcolor=\"#E2E8ED\"> \r\n\t\t <form name=\"FORM");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(279,22);to=(279,26)]
                out.print(incr);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(279,28);to=(280,32)]
                out.write("\" action=\"\" method=\"post\">\r\n\t\t  <input type=\"hidden\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(280,35);to=(280,44)]
                out.print(tablename);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(280,46);to=(281,32)]
                out.write("\" name=\"TABLE\">\r\n\t\t  <input type=\"hidden\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(281,35);to=(281,56)]
                out.print(rs.getString("idccy"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(281,58);to=(286,29)]
                out.write("\" name=\"IDCCY\">\r\n\t\t  <td bgcolor=\"#AFBFCD\" class=\"corps\" align=\"center\" width=\"15\"><img src=\"../../img/ecatalog/button/b_flopen.gif\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"20\">\r\n\t\t  <script language=\"JavaScript\">\r\n\t\t   <!--\r\n\t \t\tdocument.writeln(country(");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(286,32);to=(286,57)]
                out.print(rs.getString("idcountry"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(286,59);to=(290,106)]
                out.write("));\r\n\t\t   //-->\r\n\t\t   </script>\r\n\t\t  </td>\r\n\t  \t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"20\"><input type=\"text\" name=\"ISOCCY\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(290,109);to=(290,131)]
                out.print(rs.getString("isoccy"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(290,133);to=(291,101)]
                out.write("\" size=\"5\" maxlength=\"100\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"CCY\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(291,104);to=(291,123)]
                out.print(rs.getString("ccy"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(291,125);to=(293,148)]
                out.write("\" size=\"20\" maxlength=\"100\"></td>\r\n\t\t  <script language=\"JavaScript\">\r\n\t\t  \tdocument.writeln(\"<td bgcolor=\\\"#D6D6D6\\\" class=\\\"corps\\\" align=\\\"left\\\" width=\\\"10\\\"><input type=\\\"text\\\" name=\\\"RATE\\\" value=\\\"\"+ formatNbr('");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(293,151);to=(293,171)]
                out.print(rs.getString("rate"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(293,173);to=(295,103)]
                out.write("') +\"\\\" size=\\\"5\\\" maxlength=\\\"10\\\"></td>\");\r\n\t\t  </script>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"90\"><input type=\"text\" name=\"DATED\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(295,106);to=(295,127)]
                out.print(rs.getString("dated"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(295,129);to=(295,216)]
                out.write("\" size=\"8\" maxlength=\"100\"><input type=\"Button\" value=\"...\" onclick=\"showCalendar('FORM");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(295,219);to=(295,223)]
                out.print(incr);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(295,225);to=(296,106)]
                out.write("','DATED');\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"SYNCUSER\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(296,109);to=(296,133)]
                out.print(rs.getString("syncuser"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(296,135);to=(297,108)]
                out.write("\" size=\"5\" maxlength=\"5\" style=\"background-color:#E2E8ED; align:center; border-width:0;\" disabled></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"SYNCINDATE\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(297,111);to=(297,137)]
                out.print(rs.getString("syncindate"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(297,139);to=(298,108)]
                out.write("\" size=\"8\" maxlength=\"20\" style=\"background-color:#E2E8ED; border-width:0;\" disabled></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"SYNCUPDATE\" value=\"");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(298,111);to=(298,137)]
                out.print(rs.getString("syncupdate"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(298,139);to=(299,107)]
                out.write("\" size=\"8\" maxlength=\"20\" style=\"background-color:#E2E8ED; border-width:0;\" disabled></td>\r\n\t\t  <td class=\"corps\" align=\"left\" width=\"20\"><input type=\"button\" value=\"Update\" onclick=\"sendUpdate('FORM");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(299,110);to=(299,114)]
                out.print(incr);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(299,116);to=(300,96)]
                out.write("');\"></td>\r\n\t\t  <td class=\"corps\" align=\"left\"><input type=\"button\" value=\"Delete\" onclick=\"sendDelete('FORM");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(300,99);to=(300,103)]
                out.print(incr);
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(300,105);to=(300,107)]
                out.write("',");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(300,110);to=(300,131)]
                out.print(rs.getString("idccy"));
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(300,133);to=(303,3)]
                out.write(");\"></td>\r\n\t\t </form>\r\n\t        </tr>\r\n\t\t\t");

            // end
            // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(303,5);to=(314,1)]
                
                			}
                		incr++;
                		}
                	}
                	catch(SQLException e)
                	{
                		ApimDebug.fail("Exception:"+e.getMessage());
                	}
                
                
                	
            // end
            // HTML // begin [file="/csr/ecatalog/settings/table_edit_combo_ccy.jsp";from=(314,3);to=(371,7)]
                out.write("\r\n   </table> \r\n <!--end content table--> \r\n  </td> \r\n </tr>  \r\n</table> \r\n<!--end nesting content table--> \r\n<br>\r\n<font size=\"3\" class=\"corps\">\r\nPages :&nbsp;\r\n<script language=\"JavaScript\">\r\n\tgenPages();\r\n</script>\r\n</font>\r\n\r\n<br>\r\n<br>\r\n<!--start nesting content table--> \r\n<table bgcolor=\"#CFD9E2\" border=0 cellspacing=0 cellpadding=0 width=\"100\"> \r\n <tr><td> \r\n <!--start content table--> \r\n  <table border=0 width=\"100\" cellspacing=1 cellpadding=2> \r\n         <tr bgcolor=\"#CFD9E2\"> \r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"15\">&nbsp;</td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>COUNTRY</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>ISOCODE</b></td>\r\n\t  \t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>CCY</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"10\"><b>RATE</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\" width=\"90\"><b>DATED</b></td>\r\n\t\t  <td class=\"corpslittle\" align=\"center\"><b>&nbsp;</b></td>\r\n\t\t </tr> \r\n<!-- start content row --> \r\n\t\t<tr bgcolor=\"#43596E\"> \r\n\t\t<form name=\"frmInsert\" action=\"\" method=\"post\">\r\n\t\t  <td bgcolor=\"#AFBFCD\" class=\"corps\" align=\"center\" width=\"15\"><img src=\"../../img/ecatalog/button/b_flopen.gif\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\">\r\n\t\t\t<script language=\"JavaScript\">\r\n\t\t\t<!--\r\n\t\t\t\tdocument.writeln(country(0));\r\n\t\t\t//-->\r\n\t\t\t</script>\r\n\t\t  </td>\r\n\t  \t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"ISOCCY\" value=\"\" size=\"5\" maxlength=\"100\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"CCY\" value=\"\" size=\"20\" maxlength=\"100\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"10\"><input type=\"text\" name=\"RATE\" value=\"\" size=\"5\" maxlength=\"10\"></td>\r\n\t\t  <td bgcolor=\"#E2E8ED\" class=\"corps\" align=\"left\" width=\"90\"><input type=\"text\" name=\"DATED\" value=\"[[[DATED]]]\" size=\"8\" maxlength=\"100\"><input type=\"Button\" value=\"...\" onclick=\"showCalendar('frmInsert','DATED');\"></td>\r\n\t\t  <td class=\"corps\" bgcolor=\"#E2E8ED\"><input type=\"button\" value=\"Insert\" onclick=\"sendInsert('frmInsert');\"></td> \r\n\t\t</form>\r\n\t  </tr>\r\n   </table> \r\n <!--end content table--> \r\n  </td> \r\n </tr>  \r\n</table> \r\n<!--end nesting content table--> \r\n\r\n</body>\r\n</html>");

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
