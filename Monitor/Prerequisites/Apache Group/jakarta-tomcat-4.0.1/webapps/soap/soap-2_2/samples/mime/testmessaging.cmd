@echo off

rem set URL=http://localhost:8080/soap/servlet/
set URL=http://localhost:81/soap/servlet/

set RPCURL=%URL%rpcrouter
set MSGURL=%URL%messagerouter

echo This test assumes a server RPC router URL of:
echo  %RPCURL%
echo and a message router URL of:
echo  %MSGURL%
echo Edit this file if the above parameters are incorrect.

echo ------------------------------------------------------------------------
echo Deploying the sample messaging MIME service...
echo .
java org.apache.soap.server.ServiceManagerClient %RPCURL% deploy MessagingDeploymentDescriptor.xml

echo ------------------------------------------------------------------------
echo Verifying that it's there...
echo .
java org.apache.soap.server.ServiceManagerClient %RPCURL% list

echo ------------------------------------------------------------------------
echo Passing a manually generated SOAP envelope, and a text file (foo.txt)
echo and a binary file (fields.gif) as attachments not referred to in the SOAP
echo envelope to the message router. The result should be the last attachment
echo returned as a single part response.
echo .
java samples.mime.MimeTestClient %MSGURL% loopProcessor foo.txt fields.gif

echo ------------------------------------------------------------------------
echo Undeploying message service...
echo .
java org.apache.soap.server.ServiceManagerClient %RPCURL% undeploy urn:mimetestprocessor

echo ------------------------------------------------------------------------
echo Verifying that it's gone...
echo .
java org.apache.soap.server.ServiceManagerClient %RPCURL% list

echo ------------------------------------------------------------------------
echo That's all folks!
