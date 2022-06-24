echo This test assumes a server URL of http://localhost:8080/soap/servlet/rpcrouter
echo Deploying the addressbook2 service...
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter deploy DeploymentDescriptor.xml
echo 
echo Verify that it\'s there
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter list
echo 
echo Running demo...
java samples.addressbook2.Main http://localhost:8080/soap/servlet/rpcrouter
echo 
echo Undeploy it now
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter undeploy urn:AddressFetcher2
echo 
echo Verify that it\'s gone
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter list
