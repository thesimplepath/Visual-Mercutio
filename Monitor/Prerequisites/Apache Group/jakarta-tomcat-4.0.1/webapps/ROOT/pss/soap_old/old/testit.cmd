@echo off
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter undeploy urn:emessenger
javac PssPublisherWSDL.java
javac pmodel.java
javac pproc.java
javac pdeliv.java
javac ppdattr.java
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter deploy DeploymentDescriptor.xml
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter list
javac A.java
java A