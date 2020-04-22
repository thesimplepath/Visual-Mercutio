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
 * SOAPSecureSocketImp.cpp,v 1.27 2002/05/14 08:43:26 dcrowley Exp
 */


#ifdef _MSC_VER
#pragma warning (disable: 4786)
#endif // _MSC_VER

#include <easysoap/SOAP.h>
#include <easysoap/SOAPDebugger.h>
#include <easysoap/SOAPSSLContext.h>

#include "SOAPSecureSocketImp.h"

USING_EASYSOAP_NAMESPACE

#ifndef HAVE_LIBSSL

SOAPSecureSocketImp::SOAPSecureSocketImp()
{
	throw SOAPSocketException("Secure sockets not supported.");
}

SOAPSecureSocketImp::SOAPSecureSocketImp(SOAPSSLContext& ctx) 
{
	throw SOAPSocketException("Secure sockets not supported.");
}

SOAPSecureSocketImp::~SOAPSecureSocketImp()
{
}

bool SOAPSecureSocketImp::WaitRead(int, int) {return false;}
bool SOAPSecureSocketImp::WaitWrite(int, int) { return false; }
void SOAPSecureSocketImp::Close() { }
bool SOAPSecureSocketImp::IsOpen() { return false; }
bool SOAPSecureSocketImp::Connect(const char *, unsigned int, bool client) {return false;}
size_t SOAPSecureSocketImp::Read(char *, size_t) {return 0;}
size_t SOAPSecureSocketImp::Write(const char *, size_t) {return 0;}
void SOAPSecureSocketImp::InitSSL() {}
void SOAPSecureSocketImp::VerifyCert(const char*) {  }

#else // HAVE_LIBSSL

#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

extern "C" {
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>
};

SOAPSecureSocketImp::SOAPSecureSocketImp()
: m_ssl(0)
, m_delctx(true)
{
	m_context = new SOAPSSLContext;
}

SOAPSecureSocketImp::SOAPSecureSocketImp(SOAPSSLContext& ctx) 
: m_ssl(0)
, m_context(&ctx)
, m_delctx(false)
{
}

SOAPSecureSocketImp::~SOAPSecureSocketImp()
{
	if (m_delctx)
			delete m_context;
	Close();
}

bool
SOAPSecureSocketImp::HandleError(const char *context, int retcode)
{
	// we may have an error.
	// we need to call SSL_get_error()
	bool retry = false;
	char tmp[2048];
	memset(&tmp, 0, sizeof(tmp));
	unsigned long err = SSL_get_error(m_ssl, retcode);
	switch (err)
	{
	case SSL_ERROR_NONE:
		SOAPDebugger::Print(2, "%s: SSL_ERROR_NONE caught. retcode = %d\r\n", context, retcode);
		break;

	case SSL_ERROR_ZERO_RETURN:
		SOAPDebugger::Print(2, "%s: SSL_ERROR_ZERO_RETURN caught\r\n", context);
		Close();
		break;

	case SSL_ERROR_WANT_WRITE:
		SOAPDebugger::Print(2, "%s: SSL_ERROR_WANT_WRITE caught\r\n", context);
		WaitWrite();
		retry = true;
		break;
	case SSL_ERROR_WANT_READ:
		SOAPDebugger::Print(2, "%s: SSL_ERROR_WANT_READ caught\r\n", context);
		WaitRead();
		retry = true;
		break;
	case SSL_ERROR_WANT_X509_LOOKUP:
		SOAPDebugger::Print(2, "%s: SSL_ERROR_WANT_X509_LOOKUP caught\r\n", context);
		retry = true;
		break;

	case SSL_ERROR_SYSCALL:
		SOAPDebugger::Print(2, "%s: SSL_ERROR_SYSCALL caught\r\n", context);
		if (retcode == 0)
		{
			// premature EOF, but not necessarily an error
			SOAPDebugger::Print(2, "%s: premature close on socket\r\n", context);
			// shouldn't we retry here?
			retry = true;
			break;
		}
		if (retcode == -1)
		{
#ifdef HAVE_STRERROR
			sp_strncpy(tmp, strerror(errno), sizeof(tmp));
#else // dont HAVE_STRERROR
			snprintf(tmp, sizeof(tmp), "socket error, errno=%d\r\n", errno);
			tmp[sizeof(tmp) - 1] = 0;
#endif // HAVE_STRERROR
			throw SOAPSocketException(context, tmp);
		}
		break;
	case SSL_ERROR_SSL:
	default:
		SOAPString msg;
		if (ERR_peek_error()) {
			unsigned long sslerror = ERR_get_error();
			msg = "An SSL error occured. Here are the contents of the SSL error queue";
			for (  ; sslerror != 0 ; sslerror = ERR_get_error()) 
			{
				
#if OPENSSL_VERSION_NUMBER >= 0x00906000L
				ERR_error_string_n(sslerror, tmp, sizeof(tmp) - 1);
#else
				// dangerous
				ERR_error_string(sslerror, tmp);
				tmp[sizeof(tmp) - 1] = \0;
#endif // OPENSSL_VERSION_NUMBER
				SOAPDebugger::Print(2, "Error handled.\r\ncontext: %s\r\nMsg: %s\r\n", context, tmp);
				msg += tmp;
				msg += ".     "; // create some space to make it readable
			}
		} else {
			msg = "Unkown error";
		}
		throw SOAPSocketException(context, msg.Str());
	}
	return retry;
	
}

	
void
SOAPSecureSocketImp::InitSSL()
{
	//
	// set up SSL
	//
	m_ssl = SSL_new(m_context->GetContext());
	if (!m_ssl)
		throw SOAPMemoryException();
	
	int retcode;

	if ((retcode = SSL_set_fd(m_ssl, m_socket.GetRawSocketHandle())) != 1)
		HandleError("Error attaching security layer to socket : %s\r\n", retcode);

	if ((retcode = SSL_connect(m_ssl)) != 1)
		HandleError("Error negotiating secure connection : %s\r\n", retcode);
}

const char*  
SOAPSecureSocketImp::CheckForCertError(int rc) {
	SOAPString msg = "";
	if (!m_context->IgnoreCertError(rc)) {
		switch(rc) {
			case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:
				msg = "the issuer certificate could not be found";
				break;
			case X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE:
				msg = "the certificate signature could not be decrypted.";
				break;
			case X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY:
				msg = "the public key in the certificate SubjectPublicKeyInfo could not be read.";
				break;
			case X509_V_ERR_CERT_SIGNATURE_FAILURE:
				msg = "the signature of the certificate is invalid.";
				break;
			case X509_V_ERR_CERT_NOT_YET_VALID:
				msg = " the certificate is not yet valid. ";
				break;
			case X509_V_ERR_CERT_HAS_EXPIRED:
				msg = " the certificate has expired.";
				break;
			case X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD:
				msg = "the certificate notBefore field contains an invalid time.";
				break;
			case X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD:
				msg = " the certificate notAfter field contains an invalid time.";
				break;
			case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
				msg = "the passed certificate is self signed and the same certificate cannot be found in the list of trusted certificates.";
				break;
			case X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN:
				msg = "self signed certificate in certificate chain.";
				break;
			case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
				msg = "unable to get local issuer certificate. ";
				break;
			case X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE:
				msg = " unable to verify the first certificate.";
				break;
			case X509_V_ERR_INVALID_CA:
				msg = "Invalid CA certificate.";
				break;
			case X509_V_ERR_PATH_LENGTH_EXCEEDED:
				msg = "Certificate chain too long.";
				break;
			case X509_V_ERR_INVALID_PURPOSE:
				msg = "Unsupported certificate purpose.";
				break;
			case X509_V_ERR_CERT_UNTRUSTED:
				msg = "the root CA is not marked as trusted for the specified purpose.";
				break;
			case X509_V_ERR_CERT_REJECTED:
				msg = "the root CA is marked to reject the specified purpose.";
				break;
			case X509_V_ERR_KEYUSAGE_NO_CERTSIGN:
				msg = "key usage does not include certificate signing.";
				break;
			default:
				msg = "Server certificate verification failed due to an unknown error";
				break;
		}
	}
	return msg.Str();
}

void
SOAPSecureSocketImp::VerifyCert(const char* host)
{
	X509* server_cert = SSL_get_peer_certificate(m_ssl);
	if (!server_cert)
		throw SOAPException("Error getting server certificate.");

	int rc = SSL_get_verify_result(m_ssl);
	
	SOAPString msg = CheckForCertError(rc);
	if (msg != "")
		throw SOAPException("Error verifying peer certificate: %s", msg.Str());

	char buf[256];
	X509_NAME_get_text_by_NID(X509_get_subject_name(server_cert),
							  NID_commonName, buf, sizeof(buf));
	if (sp_strcasecmp(buf, host))
		throw SOAPException("Server certificate hostname does not match (%s != %s)", buf, host);

	X509_free(server_cert);
}

bool
SOAPSecureSocketImp::WaitRead(int sec, int usec)
{
	if (!m_ssl)
		return m_socket.WaitRead(sec, usec);

	if (SSL_pending(m_ssl) > 0)
		return true;

	// we have to wait...
	m_socket.Wait(sec, usec);
	return SSL_pending(m_ssl) > 0;
}

bool
SOAPSecureSocketImp::WaitWrite(int sec, int usec)
{
	// not sure if this is correct or not
	return m_socket.WaitWrite(sec, usec);

}
bool
SOAPSecureSocketImp::IsOpen()
{
	SOAPDebugger::Print(5, "SOAPSecureSocketImp::IsOpen()");
	// more to be done?
	return m_socket.IsOpen();
}

bool
SOAPSecureSocketImp::Connect(const char *host, unsigned int port, bool client)
{
	SOAPDebugger::Print(5, "SOAPSecureSocketImp::Connect()\r\n");
	if (!m_socket.Connect(host, port))
		return false;

	InitSSL();
	if (m_context->VerifyServerCert())
		VerifyCert(host);

	SOAPDebugger::Print(5, "Connected to %s:%d \r\n", host, port);
	return true;
}


size_t
SOAPSecureSocketImp::Read(char *buff, size_t bufflen)
{
	if (!m_ssl)
		return m_socket.Read(buff, bufflen);

	int bytes = 0;
	if (bufflen > 0)
	{
		bool retry = false;
		do
		{
			bytes = SSL_read(m_ssl, buff, bufflen);
			SOAPDebugger::Print(2, "SRECV: %d bytes\r\n", bytes);
			if (bytes > 0)
			{
				// good, we read some bytes.
				retry = false;
			}
			else 
			{
				// check for an error
				retry = HandleError("Error reading from secure socket", bytes);
				bytes = 0;
			}
		} while (retry);
		SOAPDebugger::Write(1, buff, bytes);
	}
	return bytes;
}

size_t
SOAPSecureSocketImp::Write(const char *buff, size_t bufflen)
{
	if (!m_ssl)
		return m_socket.Write(buff, bufflen);

	if (bufflen > 0)
	{
		bool retry = false;
		do
		{
			int bytes = SSL_write(m_ssl, buff, bufflen);
			SOAPDebugger::Print(2, "SSEND: %d bytes\n", bytes);
			if (bytes > 0)
			{
				if ((unsigned int)bytes != bufflen)
					throw SOAPSocketException("Error writing to secure socket, "
						   "expected to write %d bytes, wrote %d bytes",
						   bufflen, bytes);
				retry = false;
			}
			else 
			{
				// check for an error
				retry = HandleError("Error writing to secure socket\r\n", bytes);
				bytes = 0;
			}
		} while (retry);
		SOAPDebugger::Write(1, buff, bufflen);
	}
	return 0;
}

void
SOAPSecureSocketImp::Close()
{
	SOAPDebugger::Print(5, "SOAPSecureSocketImp::Close()\r\n");
	if (m_ssl)
		SSL_shutdown(m_ssl);

	m_socket.Close();

	if (m_ssl)
	{
		SSL_free(m_ssl);
		m_ssl = 0;
	}

}

#endif // HAVE_LIBSSL

