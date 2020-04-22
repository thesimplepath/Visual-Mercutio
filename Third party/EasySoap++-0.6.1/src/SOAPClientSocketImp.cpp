/* 
 * EasySoap++ - A C++ library for SOAP (Simple Object Access Protocol)
 * Copyright (C) 2001 David Crowley; SciTegic, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * $Id: SOAPClientSocketImp.cpp,v 1.35 2002/07/01 18:25:28 dcrowley Exp $
 */


#ifdef _MSC_VER
#pragma warning (disable: 4786)
#endif // _MSC_VER

#include <easysoap/SOAPDebugger.h>

#include "SOAPClientSocketImp.h"

#if defined (_WIN32)
#if !defined (__MWERKS__)
#include <winsock2.h>
#endif

//
// Initialize Windows socket library
//
static class WinSockInit
{
private:
	bool didinit;
public:
	WinSockInit() : didinit(false)
	{
	}

	void Init()
	{
		if (!didinit)
		{
			WSADATA wsaData;
			WSAStartup( MAKEWORD(2,0), &wsaData );
			didinit = true;
		}
	}

	~WinSockInit()
	{
		if (didinit)
			WSACleanup();
	}
} __winsockinit;

#else // not _WIN32

#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef TIME_WITH_SYS_TIME
#include <sys/time.h>
#endif

#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif

#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif

#ifdef HAVE_NETINET_TCP_H
#include <netinet/tcp.h>
#endif

#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif

#ifdef HAVE_ARPA_NAMESER_H
#include <arpa/nameser.h>
#endif

#ifdef HAVE_RESOLV_H
#include <resolv.h>
#endif

#ifdef HAVE_NETDB_H
#include <netdb.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_MEMORY_H
#include <memory.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#else
#ifdef HAVE_SYS_UNISTD_H
#include <sys/unistd.h>
#endif
#endif

#define INVALID_SOCKET 0xFFFFFFFF
#define SOCKET_ERROR -1
#define closesocket close

#endif // _WIN32

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

USING_EASYSOAP_NAMESPACE

SOAPClientSocketImp::SOAPClientSocketImp()
: m_socket(INVALID_SOCKET)
{
#if defined (_WIN32)
	__winsockinit.Init();
#endif
}

SOAPClientSocketImp::~SOAPClientSocketImp()
{
	Close();
}

void
SOAPClientSocketImp::Close()
{
	SOAPDebugger::Print(5, "SOAPClientSocketImp::Close()\r\n");
	if (m_socket != INVALID_SOCKET)
	{
		closesocket(m_socket);
	}

	m_socket = INVALID_SOCKET;
}


void
SOAPClientSocketImp::Wait(int sec, int usec)
{
	struct timeval tv;
	tv.tv_sec = sec;
	tv.tv_usec = usec;
	select(0, 0, 0, 0, sec == -1 ? 0 : &tv);
}

bool
SOAPClientSocketImp::WaitRead(int sec, int usec)
{
	struct timeval tv;
	fd_set rset, eset;

	FD_ZERO(&rset);
	FD_SET(m_socket, &rset);
	FD_ZERO(&eset);
	FD_SET(m_socket, &eset);

	tv.tv_sec = sec;
	tv.tv_usec = usec;

	int ret = select(m_socket+1, &rset, 0, &eset, sec == -1 ? 0 : &tv);
	int rsetresult = FD_ISSET(m_socket, &rset);
	int esetresult = FD_ISSET(m_socket, &eset);
	SOAPDebugger::Print(3, "read select() return: %d\n", ret);
	SOAPDebugger::Print(4, "write select() wset: %d\n", rsetresult);
	SOAPDebugger::Print(4, "write select() eset: %d\n", esetresult);
	if (ret == (int)SOCKET_ERROR)
		throw SOAPException("WaitRead select error");

	return rsetresult != 0;
}

bool
SOAPClientSocketImp::WaitWrite(int sec, int usec)
{
	struct timeval tv;
	fd_set wset, eset;

	FD_ZERO(&eset);
	FD_SET(m_socket, &eset);
	FD_ZERO(&wset);
	FD_SET(m_socket, &wset);

	tv.tv_sec = sec;
	tv.tv_usec = usec;

	int ret = select(m_socket+1, 0, &wset, &eset, sec == -1 ? 0 : &tv);
	int wsetresult = FD_ISSET(m_socket, &wset);
	int esetresult = FD_ISSET(m_socket, &eset);
	SOAPDebugger::Print(3, "write select() return: %d\n", ret);
	SOAPDebugger::Print(4, "write select() wset: %d\n", wsetresult);
	SOAPDebugger::Print(4, "write select() eset: %d\n", esetresult);
	if (ret == (int)SOCKET_ERROR)
		throw SOAPException("WaitWrite select error");

	return wsetresult != 0;
}

bool
SOAPClientSocketImp::IsOpen()
{
	return m_socket != INVALID_SOCKET;
}


bool
SOAPClientSocketImp::Connect(const char *server, unsigned int port)
{
	SOAPDebugger::Print(5, "SOAPClientSocketImp::Connect()\r\n");
	Close();

	//
	// TODO: Abstract this away into other class/methods
	//
	m_socket = 0;
	m_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
#ifdef HAVE_STRERROR
		throw SOAPSocketException("Error creating socket: %s", strerror(errno));
#else
		throw SOAPSocketException("Error creating socket");
#endif
	}

	struct sockaddr_in sockAddr;
	sp_memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(m_socket, (struct sockaddr*)&sockAddr, sizeof(sockAddr)) == (int)SOCKET_ERROR)
	{
#ifdef HAVE_STRERROR
		throw SOAPSocketException("Error binding socket: %s", strerror(errno));
#else
		throw SOAPSocketException("Error binding socket");
#endif
	}

	sp_memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(server);
	sockAddr.sin_port = htons((u_short)port);
	if (sockAddr.sin_addr.s_addr == (unsigned int)-1)
	{
		struct hostent *lphost = gethostbyname(server);
		if (lphost != NULL)
		{
			sockAddr.sin_addr.s_addr = ((struct in_addr *)lphost->h_addr)->s_addr;
		}
		else
		{
			Close();
			throw SOAPSocketException("Could not resolve host name: %s", server);
		}
	}

	if (connect(m_socket, (struct sockaddr*)&sockAddr, sizeof(sockAddr)) == (int)SOCKET_ERROR)
	{
		Close();
#ifdef HAVE_STRERROR
		throw SOAPSocketException("Failed to connect to host %s, port %d: %s", server, port, strerror(errno));
#else
		throw SOAPSocketException("Failed to connect to host %s, port %d", server, port);
#endif
	}

	int nodelay = 1;
	struct protoent *tcpproto = getprotobyname("tcp");
	if (!tcpproto)
	{
		//
		// Couldn't get the struct by name (/etc/protocols missing?)
		// So lets try by number.  TCP should always be 6, we hope...
		tcpproto = getprotobynumber(6);
		if (!tcpproto)
			throw SOAPSocketException("Could not get TCP protocol struct.");
	}

	if (setsockopt(m_socket, tcpproto->p_proto, TCP_NODELAY, (const char *)&nodelay, sizeof(nodelay)) == -1)
	{
#ifdef HAVE_STRERROR
		throw SOAPSocketException("Error setting TCP_NODELAY: %s", strerror(errno));
#else
		throw SOAPSocketException("Error setting TCP_NODELAY");
#endif
	}
	SOAPDebugger::Print(5, "SOAPClientSocketImp::Connect() successful\r\n");
	return true;
}

size_t
SOAPClientSocketImp::Read(char *buff, size_t bufflen)
{
	int bytes = 0;
	if (bufflen > 0)
	{
		*buff = 0;
		bytes = recv(m_socket, buff, bufflen, 0);
		SOAPDebugger::Print(2, "RECV: %d bytes\n", bytes);
		if (bytes == 0)
		{
			Close(); // other side dropped the connection
		}
		else if (bytes == (int)SOCKET_ERROR)
		{
			Close();
			throw SOAPSocketException("Error reading socket");
		}
		SOAPDebugger::Write(1, buff, bytes);
	}
	return bytes;
}

size_t
SOAPClientSocketImp::Write(const char *buff, size_t bufflen)
{
	int bytes = 0;
	if (bufflen > 0)
	{
		bytes = send(m_socket, buff, bufflen, 0);
		SOAPDebugger::Print(2, "SEND: %d bytes\n", bytes);
		if (bytes == (int)SOCKET_ERROR)
		{
			Close();
			throw SOAPSocketException("Error writing to socket");
		}
		else if (bytes != (int)bufflen)
		{
			Close();
			throw SOAPSocketException("Error writing to socket, "
					"tried to write %d bytes, wrote %d",
					bufflen, bytes);
		}
		SOAPDebugger::Write(1, buff, bytes);
	}
	return bytes;
}

