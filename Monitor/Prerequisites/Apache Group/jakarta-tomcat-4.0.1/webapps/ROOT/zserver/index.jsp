<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<%@ page session="true" %>
<%@ page import="PsConfig" %>
<HEAD><TITLE>Sign In</TITLE>
<META HTTP-EQUIV="Content-type" CONTENT="text/html; charset=UTF-8">
<% 
	//String userskin = ServletUtils.getCookie(request, "userskin"); 
	Cookie cookies[]= request.getCookies();
	String userskin=null;
	if (cookies!=null)
	{
		int l=cookies.length;
		for (int i=0;i<l;i++)
		{
		System.out.println(cookies[i].getName()+"="+cookies[i].getValue());
			if (cookies[i].getName().equals("userskin")==true)
			{
				userskin=cookies[i].getValue();
				break;
			}
		}
	}
	if (userskin==null)
		userskin="1";
	userskin="skin"+userskin;
%>
<LINK href="css/<%=userskin%>/global.css" rel=STYLESHEET>

<SCRIPT language=JavaScript>
function checkForm()
{
	if (document.InputInfo.LOGIN.value == "")
	{
		alert("Merci d'indiquer votre identifiant.");
		document.InputInfo.ID.focus();
		return false;
	}
	return true;
}

function resetForm()
{
	document.InputInfo.reset();
	return false;
}
</SCRIPT>

</HEAD>

<BODY>
<TABLE width="72%" border=0>
  <TBODY>
  <TR class=Bg>
    <TD noWrap width="15%" height=51>&nbsp;</TD>
    <TD noWrap width="85%" height=51><A class=menu><FONT 
      class=TitleLineBg><%=PsConfig.get("COMPANY")%></FONT></A></TD></TR>
  <TR>
    <TD width="16%" height=477>&nbsp;</TD>
    <TD class=NormalBlack vAlign=top width="84%" height=477>
      <P>Bienvenue sur la page d'Identification de Mercutio – Messenger 2002 Beta 1.</P>
      <P>Veuillez saisir votre Identifiant et votre mot de passe.</P>
      <P>&nbsp;</P>
      <FORM name=InputInfo action="logon.jsp" method=post>
      <TABLE class=MTable cellSpacing=0 cellPadding=0 width="100%" border=0>
        <TBODY>
        <TR class=Bg>
          <TD height=25><FONT class=swb>Identification</FONT></TD></TR>
        <TR>
          <TD>
            <TABLE cellSpacing=0 cellPadding=0 width="100%" border=0>
              <TBODY>
              <TR>
                <TD class=TableInfoBackground width=225 height=25>Identifiant 
                <TD class=TableFieldBackground width=434 height=25><INPUT maxLength=30 size=30 name=LOGIN> </TD>
              <TR>
                <TD class=TableInfoBackground width=225 height=25>Mot de passe 

                <TD class=TableFieldBackground width=434 height=25><INPUT type=password maxLength=256 size=30 name=PASSWD> 
              </TD></TR></TBODY></TABLE></TD></TR></TBODY></TABLE>
      <TABLE height=26 width=181>
        <TBODY>
        <TR>
          <TD width=80><INPUT class=sbttn title="Clicker sur ce bouton pour vous signer" tabIndex=1 type=submit value=Signer name=sign> 
          </TD>
          <TD width=80><INPUT class=sbttn title="Clicker sur ce bouton pour effacer le contenu de la forme" onclick="return resetForm();" tabIndex=2 type=reset value=Effacer name=clear> 
          </TD></TR></TBODY></TABLE></FORM>
      <P>&nbsp;</P></TD></TR></TBODY></TABLE></BODY></HTML>
