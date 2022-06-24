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


public class action$jsp extends HttpJspBase {


    static {
    }
    public action$jsp( ) {
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

            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(0,0);to=(1,0)]
                out.write("<html>\r\n");

            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(1,26);to=(2,0)]
                out.write("\r\n");

            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(2,80);to=(7,0)]
                out.write("\r\n<head>\r\n<META HTTP-EQUIV=\"Content-type\" CONTENT=\"text/html; charset=UTF-8\">\r\n</head>\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(7,2);to=(22,0)]
                
                 int action =		Integer.valueOf(request.getParameter( "ACTION" )).intValue();
                
                 String query=  	request.getParameter( "QUERY" );
                 String queryend= 	request.getParameter( "QUERYEND" );
                 String tablename=  	request.getParameter( "TABLE" );
                 String idname=		request.getParameter( "IDNAME" );
                 String id=	  	request.getParameter( "ID" );
                
                 ApimApp.init(); 
                
                 ApimDebug.log("action.jsp: ACTION "+action);
                
                 ApimDbConn conn=ApimDbMgr.newConnection();
                 ResultSet rs;
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(22,2);to=(26,0)]
                out.write("\r\n\r\n<body leftmargin=\"0\" topmargin=\"0\" marginwidth=\"0\" marginheight=\"0\">\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(26,2);to=(62,0)]
                
                 //ACTION 3: sql update 
                 if (action==3)
                 {
                	rs=conn.sqlQueryR("SELECT * from "+tablename);
                	ResultSetMetaData md=rs.getMetaData();
                
                	int cols=md.getColumnCount();
                	String sql="UPDATE "+tablename+" SET ";
                
                	for (int i=1;i<=cols;i++)
                	{
                		int coltype=md.getColumnType(i);//4=long 3=numeric
                		String colname=md.getColumnName(i);
                	
                		sql+=colname;
                		sql+="=";
                		if (coltype!=4 && coltype!=3)
                		  sql+="'";
                
                		String fieldno="FIELD"+i;
                System.out.println(fieldno+"="+request.getParameter( fieldno ));
                		sql+=request.getParameter( fieldno );//TODO SQL convert
                
                		if (coltype!=4 && coltype!=3)
                		  sql+="'";
                
                		if (i<cols)
                			sql+=",";
                
                	}
                
                	sql+=" WHERE "+idname+"="+id;	
                
                	rs=conn.sqlQuery(sql);
                 }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(62,2);to=(64,0)]
                out.write("\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(64,2);to=(69,2)]
                
                 //ACTION 4: sql + redirect
                 if (action==4)
                 {
                	conn.sqlExec(query);
                  
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(69,4);to=(70,1)]
                out.write("\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(70,1);to=(70,106)]
                if (true) {
                    out.clear();
                    String _jspx_qfStr = "";
                    pageContext.forward("../../ecatalog/settings/table_edit.jsp?TABLE=<%=tablename%>&MSG=delete%20successful" +  _jspx_qfStr);
                    return;
                }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(70,106);to=(71,2)]
                out.write("\r\n  ");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(71,4);to=(73,0)]
                
                 }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(73,2);to=(75,0)]
                out.write("\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(75,2);to=(80,2)]
                
                 //ACTION 2: sql +redirect
                 if (action==2)
                 {
                	conn.sqlExec(query);
                  
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(80,4);to=(81,1)]
                out.write("\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(81,1);to=(81,118)]
                if (true) {
                    out.clear();
                    String _jspx_qfStr = "";
                    pageContext.forward("../../ecatalog/settings/table_edit.jsp?REFRESH=yes&TABLE=<%=tablename%>&MSG=update%20successful" +  _jspx_qfStr);
                    return;
                }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(81,118);to=(82,2)]
                out.write("\r\n  ");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(82,4);to=(84,0)]
                
                 }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(84,2);to=(86,0)]
                out.write("\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(86,2);to=(91,2)]
                
                 //ACTION 6: sql +redirect
                 if (action==6)
                 {
                	conn.sqlExec(query);
                  
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(91,4);to=(92,1)]
                out.write("\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(92,1);to=(92,129)]
                if (true) {
                    out.clear();
                    String _jspx_qfStr = "";
                    pageContext.forward("../../ecatalog/settings/table_edit_combo_gvat.jsp?REFRESH=yes&TABLE=<%=tablename%>&MSG=update%20successful" +  _jspx_qfStr);
                    return;
                }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(92,129);to=(93,2)]
                out.write("\r\n  ");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(93,4);to=(95,0)]
                
                 }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(95,2);to=(97,0)]
                out.write("\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(97,2);to=(102,2)]
                
                 //ACTION 7: sql +redirect
                 if (action==7)
                 {
                	conn.sqlExec(query);
                  
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(102,4);to=(103,1)]
                out.write("\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(103,1);to=(103,131)]
                if (true) {
                    out.clear();
                    String _jspx_qfStr = "";
                    pageContext.forward("../../ecatalog/settings/table_edit_combo_state.jsp?&REFRESH=yes&TABLE=<%=tablename%>&MSG=update%20successful" +  _jspx_qfStr);
                    return;
                }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(103,131);to=(104,2)]
                out.write("\r\n  ");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(104,4);to=(106,0)]
                
                 }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(106,2);to=(108,0)]
                out.write("\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(108,2);to=(120,2)]
                
                 //ACTION 10: sql +redirect
                 if (action==10)
                 {
                	conn.sqlExec("UPDATE gidentity SET nxt=nxt+1 WHERE id='i"+tablename+"'");
                	rs=conn.sqlQueryR("SELECT nxt FROM gidentity WHERE id='i"+tablename+"'");
                	if (rs.next()==false)
                	{
                		ApimDebug.fail("Indentity not found for table"+tablename);
                	}
                	
                	conn.sqlExec(query+rs.getString("nxt")+queryend+",1,"+conn.now()+","+conn.now()+")");
                  
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(120,4);to=(121,1)]
                out.write("\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(121,1);to=(121,118)]
                if (true) {
                    out.clear();
                    String _jspx_qfStr = "";
                    pageContext.forward("../../ecatalog/settings/table_edit.jsp?REFRESH=yes&TABLE=<%=tablename%>&MSG=insert%20successful" +  _jspx_qfStr);
                    return;
                }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(121,118);to=(122,2)]
                out.write("\r\n  ");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(122,4);to=(124,0)]
                
                 }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(124,2);to=(126,0)]
                out.write("\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(126,2);to=(138,2)]
                
                 //ACTION 21: sql+redirect
                 if (action==21)
                 {
                	conn.sqlExec("UPDATE gidentity SET nxt=nxt+1 WHERE id='igvat'");
                	rs=conn.sqlQueryR("SELECT nxt FROM gidentity WHERE id='igvat'");
                	if (rs.next()==false)
                	{
                		ApimDebug.fail("Indentity not found for table gvat");
                	}
                	
                	conn.sqlExec("INSERT INTO gvat VALUES("+rs.getString("nxt")+","+request.getParameter( "COUNTRYID" )+","+request.getParameter( "STATEID" )+","+request.getParameter( "VATTYPEID" )+","+request.getParameter( "VAT" )+",1,"+conn.now()+","+conn.now()+")");
                  
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(138,4);to=(139,1)]
                out.write("\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(139,1);to=(139,119)]
                if (true) {
                    out.clear();
                    String _jspx_qfStr = "";
                    pageContext.forward("../../ecatalog/settings/table_edit_combo_gvat.jsp?REFRESH=yes&TABLE=gvat&MSG=update%20successful" +  _jspx_qfStr);
                    return;
                }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(139,119);to=(140,2)]
                out.write("\r\n  ");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(140,4);to=(142,0)]
                
                 }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(142,2);to=(146,0)]
                out.write("\r\n\r\n\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(146,2);to=(151,2)]
                
                 //ACTION 22: sql+redirect
                 if (action==22)
                 {
                	conn.sqlExec("UPDATE gvat SET idcountry = "+request.getParameter( "COUNTRYID" )+",idstate = "+request.getParameter( "STATEIDID" )+",idvattype ="+request.getParameter( "VATTYPEID" )+",vat ="+request.getParameter( "VAT" )+" WHERE idvat = "+request.getParameter( "VATID" ));
                  
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(151,4);to=(152,1)]
                out.write("\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(152,1);to=(152,124)]
                if (true) {
                    out.clear();
                    String _jspx_qfStr = "";
                    pageContext.forward("../../ecatalog/settings/table_edit_combo_gvat.jsp?REFRESH=yes&TABLE=idcountry&MSG=update%20successful" +  _jspx_qfStr);
                    return;
                }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(152,124);to=(153,2)]
                out.write("\r\n  ");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(153,4);to=(155,0)]
                
                 }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(155,2);to=(158,0)]
                out.write("\r\n\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(158,2);to=(163,2)]
                
                 //ACTION 23: sql+redirect
                 if (action==23)
                 {
                	conn.sqlExec("DELETE FROM gvat WHERE idvat="+request.getParameter( "VATID" ));
                  
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(163,4);to=(164,1)]
                out.write("\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(164,1);to=(164,119)]
                if (true) {
                    out.clear();
                    String _jspx_qfStr = "";
                    pageContext.forward("../../ecatalog/settings/table_edit_combo_gvat.jsp?REFRESH=yes&TABLE=gvat&MSG=update%20successful" +  _jspx_qfStr);
                    return;
                }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(164,119);to=(165,2)]
                out.write("\r\n  ");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(165,4);to=(167,0)]
                
                 }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(167,2);to=(170,0)]
                out.write("\r\n\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(170,2);to=(182,2)]
                
                 //ACTION 31: sql +redirect
                 if (action==31)
                 {
                	conn.sqlExec("UPDATE gidentity SET nxt=nxt+1 WHERE id='igstate'");
                	rs=conn.sqlQueryR("SELECT nxt FROM gidentity WHERE id='igstate'");
                	if (rs.next()==false)
                	{
                		ApimDebug.fail("Indentity not found for table gstate");
                	}
                	
                	conn.sqlExec("INSERT INTO gstate VALUES("+rs.getString("nxt")+","+request.getParameter( "COUNTRYID" )+","+request.getParameter( "CODE" )+","+request.getParameter( "TEXT" )+",1,"+conn.now()+","+conn.now()+")");
                  
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(182,4);to=(183,1)]
                out.write("\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(183,1);to=(183,122)]
                if (true) {
                    out.clear();
                    String _jspx_qfStr = "";
                    pageContext.forward("../../ecatalog/settings/table_edit_combo_state.jsp?REFRESH=yes&TABLE=gstate&MSG=update%20successful" +  _jspx_qfStr);
                    return;
                }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(183,122);to=(184,2)]
                out.write("\r\n  ");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(184,4);to=(186,0)]
                
                 }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(186,2);to=(188,0)]
                out.write("\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(188,2);to=(193,2)]
                
                 //ACTION 32: sql+redirect
                 if (action==32)
                 {
                	conn.sqlExec("UPDATE gstate SET idcountry = "+request.getParameter( "COUNTRYID" )+",code = '"+request.getParameter( "CODE" )+"', text = '"+request.getParameter( "TEXT" )+"' WHERE idstate = "+request.getParameter( "IDSTATE" ));
                  
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(193,4);to=(194,1)]
                out.write("\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(194,1);to=(194,123)]
                if (true) {
                    out.clear();
                    String _jspx_qfStr = "";
                    pageContext.forward("../../ecatalog/settings/table_edit_combo_gstate.jsp?REFRESH=yes&TABLE=gstate&MSG=update%20successful" +  _jspx_qfStr);
                    return;
                }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(194,123);to=(195,2)]
                out.write("\r\n  ");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(195,4);to=(197,0)]
                
                 }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(197,2);to=(199,0)]
                out.write("\r\n\r\n");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(199,2);to=(204,2)]
                
                 //ACTION 33: sql+redirect
                 if (action==33)
                 {
                	conn.sqlExec("DELETE FROM gstate WHERE idstate = "+request.getParameter( "IDSTATE" ));
                  
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(204,4);to=(205,1)]
                out.write("\r\n\t");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(205,1);to=(205,122)]
                if (true) {
                    out.clear();
                    String _jspx_qfStr = "";
                    pageContext.forward("../../ecatalog/settings/table_edit_combo_state.sty&REFRESH=yes&TABLE=gstate&MSG=update%20successful" +  _jspx_qfStr);
                    return;
                }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(205,122);to=(206,2)]
                out.write("\r\n  ");

            // end
            // begin [file="/csr/ecatalog/settings/action.jsp";from=(206,4);to=(208,0)]
                
                 }
            // end
            // HTML // begin [file="/csr/ecatalog/settings/action.jsp";from=(208,2);to=(276,7)]
                out.write("\r\n\r\n\r\n\r\n\r\n[[[IF [[[ACTION]]] == 41]]]\r\n[[[THEN [[[LET GIDENTITY = [[[DB.IDENTITY igship]]] ]]]\r\n\t\t[[[DB.SQL= \r\n\t\t\t\tinsert into \r\n\t\t\t\t\tgship \r\n\t\t\t\t\t\tvalues(\r\n\t\t\t\t[[[GIDENTITY]]],\r\n\t\t\t\t[[[IDPROVIDER]]], \r\n\t\t\t\t'[[[SERVICE]]]',\r\n\t\t\t\t[[[COSTWEIGHT]]],\r\n\t\t\t\t[[[COSTVOL]]],\r\n\t\t\t\t[[[COSTITEM]]],\r\n\t\t\t\t[[[COSTBASE]]],\r\n\t\t\t\t1,\r\n\t\t\t\t[[[DB.NOW]]],\r\n\t\t\t\t[[[DB.NOW]]])\r\n\t\t]]]\r\n\t\t\r\n\t\t[[[DOC.REDIRECT [[[CGIURL]]]/composer.exe?FRM=[[[ISOLANG]]]/ecatalog/settings/table_edit_combo_ship.sty&REFRESH=yes&TABLE=[[[TABLE]]]&MSG=update%20successful&[[[STRLOGIN]]] ]]]\r\n]]]\r\n\r\n[[[IF [[[ACTION]]] == 42]]]\r\n[[[THEN [[[DB.SQL= update gship set idprovider = [[[IDPROVIDER]]], service = '[[[SERVICE]]]', costweight = [[[COSTWEIGHT]]], costvol = [[[COSTVOL]]], costitem = [[[COSTITEM]]], costbase = [[[COSTBASE]]] where idship = [[[SHIPID]]] ]]]\r\n\t\t[[[DOC.REDIRECT [[[CGIURL]]]/composer.exe?FRM=[[[ISOLANG]]]/ecatalog/settings/table_edit_combo_ship.sty&REFRESH=yes&TABLE=[[[TABLE]]]&MSG=update%20successful&[[[STRLOGIN]]] ]]]\r\n]]]\r\n\r\n[[[IF [[[ACTION]]] == 43]]]\r\n[[[THEN [[[DB.SQL= delete from gship where idship = [[[SHIPID]]] ]]]\r\n\t\t[[[DOC.REDIRECT [[[CGIURL]]]/composer.exe?FRM=[[[ISOLANG]]]/ecatalog/settings/table_edit_combo_ship.sty&REFRESH=yes&TABLE=[[[TABLE]]]&MSG=update%20successful&[[[STRLOGIN]]] ]]]\r\n]]]\r\n\r\n[[[IF [[[ACTION]]] == 51]]]\r\n[[[THEN [[[LET GIDENTITY = [[[DB.IDENTITY igccy]]] ]]]\r\n\t\t[[[IF [[[RATE]]] == \"\"]]] [[[THEN [[[LET RATE = 0]]] ]]]\r\n\t\t[[[DB.SQL= \r\n\t\t\t\tinsert into \r\n\t\t\t\t\tgccy \r\n\t\t\t\t\t\tvalues(\r\n\t\t\t\t[[[GIDENTITY]]],\r\n\t\t\t\t[[[IDCOUNTRY]]], \r\n\t\t\t\t'[[[ISOCCY]]]',\r\n\t\t\t\t'[[[CCY]]]',\r\n\t\t\t\t[[[RATE]]],\r\n\t\t\t\t'[[[DATED]]]',\r\n\t\t\t\t1,\r\n\t\t\t\t[[[DB.NOW]]],\r\n\t\t\t\t[[[DB.NOW]]])\r\n\t\t]]]\r\n\t\t\r\n\t\t[[[DOC.REDIRECT [[[CGIURL]]]/composer.exe?FRM=[[[ISOLANG]]]/ecatalog/settings/table_edit_combo_ccy.sty&REFRESH=yes&TABLE=[[[TABLE]]]&MSG=update%20successful&[[[STRLOGIN]]] ]]]\r\n]]]\r\n\r\n[[[IF [[[ACTION]]] == 52]]]\r\n[[[THEN [[[IF [[[RATE]]] == \"\"]]] [[[THEN [[[LET RATE = 0]]] ]]]\r\n\t\t[[[DB.SQL= update gccy set idcountry = [[[IDCOUNTRY]]], isoccy = '[[[ISOCCY]]]', ccy = '[[[CCY]]]', rate = [[[RATE]]], dated = '[[[DATED]]]' where idccy = [[[CCYID]]] ]]]\r\n\t\t[[[DOC.REDIRECT [[[CGIURL]]]/composer.exe?FRM=[[[ISOLANG]]]/ecatalog/settings/table_edit_combo_ccy.sty&REFRESH=yes&TABLE=[[[TABLE]]]&MSG=update%20successful&[[[STRLOGIN]]] ]]]\r\n]]]\r\n\r\n[[[IF [[[ACTION]]] == 53]]]\r\n[[[THEN [[[DB.SQL= delete from gccy where idccy = [[[CCYID]]] ]]]\r\n\t\t[[[DOC.REDIRECT [[[CGIURL]]]/composer.exe?FRM=[[[ISOLANG]]]/ecatalog/settings/table_edit_combo_ccy.sty&REFRESH=yes&TABLE=[[[TABLE]]]&MSG=update%20successful&[[[STRLOGIN]]] ]]]\r\n]]]\r\n</body>\r\n</html>");

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
