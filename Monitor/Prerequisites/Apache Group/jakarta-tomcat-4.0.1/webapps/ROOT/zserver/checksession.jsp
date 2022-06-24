<%
 if ((String)session.getAttribute( "USERNAME")==null) 
 {
%>
   <script language=JavaScript>
   <!--
   top.document.location="index.htm";
   //-->
   </script>
<%
 }
%>
