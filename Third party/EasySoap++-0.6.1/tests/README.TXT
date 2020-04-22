
This directory includes two programs.

The first program is "interopserver" which is a VERY primitive
SOAP server which needs to be run as a CGI behind Apache for
example.  This server is used for tests defined by the
SOAPBuilders Interoperability Lab.  To install it, copy the
interopserver binary to your servers cgi-bin directory.
If you install the interopserver binary on your webserver, just
pass the location to the command line:

	interopclient http://mymachine:8080/mybindir/interopserver

The second program is a SOAP client for the SOAPBuilders
Interopability Lab and can be run against the above SOAP
server.  By default it trys to run against the endpoint at:

	http://easysoap.sourcefoge.net/cgi-bin/interopserver


You can run it against all known Interop servers by passing "-a"
on the command line.  It uses SOAP to retrieve a list of servers
from www.xmethods.com.  The retrieved information may not be
up-to-date so you may get errors.

	interopclient -a

Be sure to wash behind the ears.

