noinst_PROGRAMS = interopserver interopclient SSLClient SSLServer

interopserver_SOURCES = \
	interopstruct.h \
	SOAPBuildersInteropHandler.h \
	SOAPBuildersInteropHandler.cpp \
	SOAPBuildersInteropHandlerA.cpp \
	SOAPBuildersInteropHandlerB.cpp \
	SOAPBuildersHeaderHandler.h \
	SOAPBuildersHeaderHandler.cpp \
	interopserver.cpp 

interopclient_SOURCES = \
	interopclient.cpp \
	interopstruct.h

SSLClient_SOURCES = \
	SSLClient.cpp

SSLServer_SOURCES = \
	SSLServer.cpp

LDADD = ../src/libeasysoap.la
INCLUDES = -I@top_srcdir@/include

EXTRA_DIST = README.TXT README.SSL
