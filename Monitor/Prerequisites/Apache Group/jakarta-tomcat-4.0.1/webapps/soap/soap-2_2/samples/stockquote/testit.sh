echo This test assumes a server URL of http://localhost:8080/soap/servlet/rpcrouter
echo Deploying the stockquote service...
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter deploy DeploymentDescriptor.xml
echo 
echo Verify that it\'s there
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter list
echo 
echo Running the stockquote test
java samples.stockquote.GetQuote http://localhost:8080/soap/servlet/rpcrouter IBM
echo 
echo Undeploy it now
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter undeploy urn:xmltoday-delayed-quotes
echo 
echo Verify that it\'s gone
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter list
