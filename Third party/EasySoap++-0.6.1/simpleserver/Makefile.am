noinst_PROGRAMS = simpleserver simpleclient

simpleserver_SOURCES = \
	simpleserver.cpp \
	calchandler.h

simpleclient_SOURCES = \
	simpleclient.cpp \
	calchandler.h

LDADD = ../src/libeasysoap.la
INCLUDES = -I@top_srcdir@/include

EXTRA_DIST = README.TXT \
	simpleisapi.cpp
