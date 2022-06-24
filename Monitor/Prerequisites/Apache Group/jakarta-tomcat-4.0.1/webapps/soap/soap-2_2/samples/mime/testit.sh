export URL=http://localhost:8080/soap/servlet/rpcrouter
#export URL=http://localhost:8081/soap/servlet/rpcrouter

export BASEDIR=$HOME/projects/soap/build/samples/mime

echo This test assumes a server URL of:
echo  $URL
echo This test assumes that the server has access to a directory containing
echo the sample files foo.txt, infile.txt and fields.gif:
echo  $BASEDIR
echo Edit this file if the above parameters are incorrect.

echo ------------------------------------------------------------------------
echo Deploying the sample MIME service...
echo .
java org.apache.soap.server.ServiceManagerClient $URL deploy DeploymentDescriptor.xml

echo ------------------------------------------------------------------------
echo "Verifying that it's there..."
echo .
java org.apache.soap.server.ServiceManagerClient $URL list

echo ------------------------------------------------------------------------
echo Sending a small text file \(foo.txt\) as an attachment parameter.
echo This should return details about the file.
echo .
java samples.mime.MimeTestClient $URL sendFile foo.txt

echo ------------------------------------------------------------------------
echo Looping a binary file \(fields.gif\) as an attachment parameter.
echo This should return the exact same file as the response.
echo .
java samples.mime.MimeTestClient $URL loopFile fields.gif

echo ------------------------------------------------------------------------
echo Retrieving a text file with international characters \(infile.txt\) and
echo a binary file \(fields.gif\) from the server as a vector of parameters.
echo .
java samples.mime.MimeTestClient $URL getFileVector $BASEDIR/infile.txt $BASEDIR/fields.gif

echo ------------------------------------------------------------------------
echo Passing a text file with international characters \(infile.txt\) and
echo a binary file \(fields.gif\) as a Vector of attachment parameters. The
echo result should be the same as above.
echo .
java samples.mime.MimeTestClient $URL loopFileVector infile.txt fields.gif

echo ------------------------------------------------------------------------
echo Retrieving a text file with international characters \(infile.txt\) and
echo a binary file \(fields.gif\) from the server as an array of attachment
echo parameters.
echo .
java samples.mime.MimeTestClient $URL getFileArray $BASEDIR/infile.txt $BASEDIR/fields.gif

echo ------------------------------------------------------------------------
echo Passing a text file with international characters \(infile.txt\) and
echo a binary file \(fields.gif\) as an array of attachment parameters. The
echo result should be the same as above.
echo .
java samples.mime.MimeTestClient $URL loopFileArray infile.txt fields.gif

echo ------------------------------------------------------------------------
echo Passing a text file \(foo.txt\) and a binary file \(fields.gif\) as
echo attachments not referred to in the SOAP envelope.
echo .
java samples.mime.MimeTestClient $URL listAttachments foo.txt fields.gif

echo ------------------------------------------------------------------------
echo Undeploying...
echo .
java org.apache.soap.server.ServiceManagerClient $URL undeploy urn:mimetest

echo ------------------------------------------------------------------------
echo "Verifying that it's gone..."
echo .
java org.apache.soap.server.ServiceManagerClient $URL list

echo ------------------------------------------------------------------------
echo "That's all folks!"
