<html>
<%@ page session="true" %>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<script language=Javascript>
top.showTabText(1,"Utilisateur:</td><td><%=(String)session.getAttribute("USERNAME")%>","Explorateur de fichiers");

function show(url)
{
alert(url);
	usr.document.location=url;
}
</script>
<frameset rows="*"  framespacing="0" frameborder="0" bordercolor="#FFFFFF">
 <frameset cols="15%,*" framespacing="2" frameborder="0" bordercolor="#FFFFFF">
  <frame src="zbrowse1.jsp" name="wkg" id="wkg" scrolling="Auto">
  <frame src="blank.htm" name="usr" id="usr" scrolling="Auto">
 </frameset>
</frameset>
</html>
