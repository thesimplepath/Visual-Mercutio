<html>
<%@ page import="PsApp,java.sql.*,PsDbMgr,PsDbConn,PsDebug,PsConfig,PsAuthentication" %>
<%@ page session="true" %>
<head>
<%
 PsApp.init();
 
 session.setAttribute( "USERNAME",null);
 session.setAttribute( "USERROLE","-1");
 session.setAttribute( "USERID","-1");

 String mlogin=request.getParameter( "LOGIN" );
 String mpasswd=request.getParameter( "PASSWD" );

 PsAuthentication auth=new PsAuthentication();
 if (auth.logon(mlogin,mpasswd)==false)
 {
 	//not logged
 	out.println("<meta HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=index.htm\">");
 }
 else
 {
 	//logged
 	session.setAttribute( "USERNAME",mlogin);
 	session.setAttribute( "USERROLE",String.valueOf(auth.getRole()));
	session.setAttribute( "USERID",  String.valueOf(auth.getId()));
	out.println("<meta HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=zserver.htm\">");

	//workgroup assigned
	String wkass="";
	
	PsApp.init();
	PsDbConn conn;
	conn=PsDbMgr.newConnection();
	ResultSet rs;

	rs=conn.sqlQueryR("SELECT distinct(w.wkgname) as nm FROM pworkgroup w,pemployee as e,pempmap m WHERE e.login=m.login AND w.wkgid=m.wkgid AND m.login='"+mlogin+"'");
	boolean xout=rs.next();
	while (xout==true)
	{
		wkass+=rs.getString("nm");
		xout=rs.next();
		if (xout==true)
			wkass+=", ";
	}
	session.setAttribute( "USERWORKGROUPTXT",wkass);

	String roletxt="N.A.";
	rs=conn.sqlQueryR("SELECT rolename FROM pemproles WHERE roleid="+auth.getRole());
	if (rs.next()==true)
		roletxt=rs.getString("rolename");

	session.setAttribute( "USERROLETXT",roletxt);	

	//retrieve skin if selected
	String skin="1"; //default
	rs=conn.sqlQueryR("SELECT * FROM ppersonalize WHERE login='"+mlogin+"'");
	if (rs.next()==true)
	{
		skin=rs.getString("userskin");
	}
	

	session.setAttribute( "USERSKIN",skin);
	PsDebug.log("Session userskin: "+skin);

	//configure current session
	int seconds=Integer.valueOf((String)PsConfig.get("SESSION_TIMEOUT")).intValue();
	session.setMaxInactiveInterval(seconds);
	PsDebug.log("Session timeout: "+seconds+" s.");
 }
%>

</head>
<body>
</body>
</html>