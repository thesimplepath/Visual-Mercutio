<html>
<%@ page session="true" %>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<script language=Javascript>
top.showTabText(9,"Utilisateur:</td><td><%=(String)session.getAttribute("USERNAME")%>","Statistiques de processus...");

function show(url)
{
	usr.document.location=url;
}
</script>
 <frameset cols="15%,*" framespacing="2" frameborder="0" bordercolor="#FFFFFF">
  <frame src="stats0.jsp" name="wkg" id="wkg" scrolling="Auto">
  <frame src="blank.htm" name="usr" id="usr" scrolling="Auto">
 </frameset>
</html>
