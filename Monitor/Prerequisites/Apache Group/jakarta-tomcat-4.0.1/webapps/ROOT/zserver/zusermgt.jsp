<html>
<%@ page session="true" %>
<META http-equiv=Content-Type content="text/html; charset=utf-8">
<jsp:include page="checksession.jsp" flush="false" />
<script language=Javascript>
top.showTabText(5,"Utilisateur:</td><td><%=(String)session.getAttribute("USERNAME")%>","");

function show(url)
{
alert(url);
	usr.document.location=url;
}
</script>
<frameset rows="32,*"  framespacing="0" frameborder="0" bordercolor="#FFFFFF">
<frame src="zusermgt0.jsp" name="usertop" id "usertop" scrolling="No">
 <frameset cols="15%,*" framespacing="2" frameborder="0" bordercolor="#FFFFFF">
  <frame src="zusermgt1.jsp" name="wkg" id="wkg" scrolling="Auto">
  <frame src="blank.htm" name="usr" id="usr" scrolling="Auto">
 </frameset>
</frameset>
</html>
