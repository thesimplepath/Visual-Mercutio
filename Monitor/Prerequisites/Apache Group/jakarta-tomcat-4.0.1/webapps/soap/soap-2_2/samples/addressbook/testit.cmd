@echo off
echo This test assumes a server URL of http://localhost:8080/soap/servlet/rpcrouter
echo Deploying the addressbook service...
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter deploy DeploymentDescriptor.xml
echo .
echo Verify that it's there
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter list
echo .
echo Getting info for "Mr Good"
java samples.addressbook.GetAddress http://localhost:8080/soap/servlet/rpcrouter "John B. Good"
echo .
echo Adding "John Doe"
java samples.addressbook.PutAddress http://localhost:8080/soap/servlet/rpcrouter "John Doe" 123 "Main Street" AnyTown SS 12345 800 555 1212
echo .
echo Query "Mr Doe" to make sure it was added
java samples.addressbook.GetAddress http://localhost:8080/soap/servlet/rpcrouter "John Doe"
echo .
echo Adding an XML file of listings
java samples.addressbook.PutListings http://localhost:8080/soap/servlet/rpcrouter sample_listings.xml
echo .
echo Get everyone!
java samples.addressbook.GetAllListings http://localhost:8080/soap/servlet/rpcrouter
echo .
echo Undeploy it now
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter undeploy urn:AddressFetcher
echo .
echo Verify that it's gone
java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter list
