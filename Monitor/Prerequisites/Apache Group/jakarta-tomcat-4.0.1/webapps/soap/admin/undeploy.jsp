<%@ page import="org.apache.soap.*" %>
<%@ page import="org.apache.soap.server.*" %>

<h1>Un-Deploy a Service</h1>

<% 
ServiceManager serviceManager =
  org.apache.soap.server.http.ServerHTTPUtils.getServiceManagerFromContext(application);

String id = request.getParameter ("id");
if (id == null) {
  String[] serviceNames = serviceManager.list ();
  if (serviceNames.length == 0) {
    out.println ("<p>Sorry, there are no services currently deployed.</p>");
  } else {
    out.println ("<p>Select the service to be undeployed:</p>");
    %>
    <ul>
    <%
    for (int i = 0; i < serviceNames.length; i++) {
      id = serviceNames[i];
    %>
      <li><a href="undeploy.jsp?id=<%=id%>"><%= id%></li>
    <%
    }
    %>
    </ul>
    <%
  }
} else {
  try {
    DeploymentDescriptor dd = serviceManager.undeploy (id);
    out.println ("OK, service named '" + id + "' undeployed successfully!");
  } catch (SOAPException e) {
    out.println ("Ouch, coudn't undeploy service '" + id + "' because: ");
    e.getMessage ();
  }
}
%>
