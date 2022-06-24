@echo off
echo This test assumes a server URL of http://localhost:8080/soap/servlet/rpcrouter
echo Deploying the bid service...
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter deploy DeploymentDescriptor.xml
echo .
