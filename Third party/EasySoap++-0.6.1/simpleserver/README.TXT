
This directory contains a simple CGI server program
and a simple client program to demonstrate writing a
simple SOAP method.

The program calls two SOAP methods, one which adds two
numbers together and another which multiplies the two
numbers together.

The client program by default runs against the following
endpoint:

	http://easysoap.sourceforge.net/cgi-bin/simpleserver

Or you can install the simpleserver CGI program on your
own webserver and pass the client the URL on the command line.

For IIS Users, you can also compile up the simpleisapi.dll and
which demonstrated how one writes an ISAPI DLL.

Hopefully an Apache module is on the way....

