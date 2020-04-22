#!/bin/sh
mkdir -p interop
cd interop

../interopclient -a -2a -mkdir -xml interop2a.xml
../interopclient -a -2b -mkdir -xml interop2b.xml
../interopclient -a -2c -mkdir -xml interop2c.xml

sabcmd ../interop2a.xsl interop2a.xml interop2a.html
sabcmd ../interop2b.xsl interop2b.xml interop2b.html
sabcmd ../interop2c.xsl interop2c.xml interop2c.html

tar czf interop.tar.gz *.html */*.txt
