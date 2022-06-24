@echo off
REM Script to simplify the server setup for the COM Pluggable Provider
set _DEF_SOAP_URL=http://localhost:8080/soap/servlet/rpcrouter
if not "%2" == "" set _DEF_SOAP_URL=%2
if "%1" == "deploy" goto deploy
if "%1" == "undeploy" goto undeploy
echo "Usage: rundemo deploy|undeploy"
goto :eof
:undeploy
echo Un-Deploying SOAP services.
@echo on
regsvr32 /u /s apacheadder.dll
regsvr32 /u /s apachesum.dll
java org.apache.soap.server.ServiceManagerClient %_DEF_SOAP_URL% undeploy urn:adder-COM
java org.apache.soap.server.ServiceManagerClient %_DEF_SOAP_URL% undeploy urn:sum-COM
@echo Listing deployed services. 
java org.apache.soap.server.ServiceManagerClient %_DEF_SOAP_URL% list
@goto :eof
:deploy
@echo on
@echo Registering the COM objects.
regsvr32 /s apacheadder.dll
regsvr32 /s apachesum.dll
@echo Deploying SOAP Services.
java org.apache.soap.server.ServiceManagerClient %_DEF_SOAP_URL% deploy adder.xml
java org.apache.soap.server.ServiceManagerClient %_DEF_SOAP_URL% deploy sum.xml
@echo Listing deployed services. 
java org.apache.soap.server.ServiceManagerClient %_DEF_SOAP_URL% list
