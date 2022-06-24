echo This test assumes server URLs of http://localhost:8080/soap/servlet/rpcrouter
echo and http://localhost:8080/soap/servlet/messagerouter
echo Deploying the messaging service...
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter deploy DeploymentDescriptor.xml
echo
echo Verify that it\'s there
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter list
echo
echo Sending some messages...
java samples.messaging.SendMessage http://localhost:8080/soap/servlet/messagerouter msg1.xml
java samples.messaging.SendMessage http://localhost:8080/soap/servlet/messagerouter msg2.xml
java samples.messaging.SendMessage http://localhost:8080/soap/servlet/messagerouter msg3.xml
echo 
echo Undeploy it now
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter undeploy urn:po-processor
echo 
echo Verify that it\'s gone
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter list
