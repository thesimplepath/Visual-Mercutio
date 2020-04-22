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
 * $Id: SOAPSSLContext.cpp,v 1.9 2002/06/10 18:55:48 kingmob Exp $
 */

#include <easysoap/SOAP.h>
#include <easysoap/SOAPDebugger.h>
#include <easysoap/SOAPException.h>

#include <easysoap/SOAPSSLContext.h>

USING_EASYSOAP_NAMESPACE

#ifdef HAVE_LIBSSL

extern "C" {
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>
};

//
// Initialize OpenSSL
//


class OpenSSLinit
{
	private:
		static rsa_st* m_tmpRSAKey;
	public:

	OpenSSLinit()
	{
		// TODO: Add correct use of the /dev/random port.
		static const char rnd_seed[] = 
			"string to make the random number generator"
			"think it has some entropy.";
		SSL_library_init();
		ERR_load_crypto_strings();
		SSL_load_error_strings();
		RAND_seed(rnd_seed, sizeof rnd_seed);
	}
	~OpenSSLinit()
	{
			if (m_tmpRSAKey)
		{
				RSA_free(m_tmpRSAKey);
				m_tmpRSAKey = 0;
		}
	}

	static rsa_st* tmpRSAkey_cb(SSL* s, int SSLexport, int keylen) {
		if (m_tmpRSAKey)
				RSA_free(m_tmpRSAKey);
#if OPENSSL_VERSION_NUMBER >= 0x0900
		m_tmpRSAKey = RSA_generate_key(keylen, RSA_F4, NULL, NULL);
#else 
		m_tmpRSAKey = RSA_generate_key(keylen, RSA_F4, NULL);
#endif //OPENSSL_VERSION_NUMBER
		return m_tmpRSAKey;
	}


};
rsa_st* OpenSSLinit::m_tmpRSAKey = 0;
// *******************************************************************


SOAPSSLContext::SOAPSSLContext() 
	:	m_ctx(0)
	, m_verifyserver(true)
{
	sslinit();
	m_ctx = SSL_CTX_new(SSLv23_client_method());
	if (!m_ctx)
		throw SOAPMemoryException();
}

SOAPSSLContext::SOAPSSLContext(const char* cafile) 
		: m_cafile(cafile)
		, m_ctx(0)
	, m_verifyserver(true)
{
	sslinit();
	m_ctx = SSL_CTX_new(SSLv23_client_method());
	if (!m_ctx)
		throw SOAPMemoryException();
	SetCAInfo(cafile);
}

SOAPSSLContext::SOAPSSLContext(const char* certfile, const char* keyfile, const char* password, const char* cafile)
		: m_cafile(cafile)
		, m_certfile(certfile)
		, m_keyfile(keyfile)
		, m_password(password)
		, m_ctx(0)
	, m_verifyserver(true)
{
	sslinit();
	m_ctx = SSL_CTX_new(SSLv23_client_method());
	if (!m_ctx)
		throw SOAPMemoryException();
	SetCertInfo(certfile, keyfile, password);
	if (cafile)
		SetCAInfo(cafile);
}

void
SOAPSSLContext::sslinit()
{
		static OpenSSLinit __opensslinit;
}

/*
SOAPSSLContext::SOAPSSLContext(const SOAPSSLContext& ctx)
{

}

SOAPSSLContext& SOAPSSLContext::operator=(const SOAPSSLContext& ctx)
{
	return *this;	
}
*/

void SOAPSSLContext::SetCAInfo(const char* cafile)
{
	int retcode;

	SSL_CTX_set_verify(m_ctx, SSL_VERIFY_PEER, NULL);

	if ((retcode = SSL_CTX_load_verify_locations(m_ctx, m_cafile.Str(), 0)) != 1)
			HandleError("Error loading the certificate authority file: %s\n", retcode);
}

void SOAPSSLContext::SetCertInfo(const char* certfile, const char* keyfile, const char* password)
{
	int retcode;

	// TODO: figure out what kind of certificate we are dealing with.
	type = RSA_cert;
	
	// RSA requires a callback function that can generate the correct sized key on the fly...
	SSL_CTX_set_tmp_rsa_callback(m_ctx, &OpenSSLinit::tmpRSAkey_cb);
		
	// set the certificate file.
	if ((retcode = SSL_CTX_use_certificate_chain_file(m_ctx, m_certfile.Str()))!= 1)
			HandleError("Error trying to use the certificate file: %s\n", retcode);

	// now set our password callback function...
	SSL_CTX_set_default_passwd_cb(m_ctx, &password_cb);
	// setup the callback userdata.
	SSL_CTX_set_default_passwd_cb_userdata(m_ctx, this);
	
	// call the right function based on the certificate type.
	if (type == DSA_cert) {
		if ((retcode = SSL_CTX_use_PrivateKey_file(m_ctx, m_keyfile.Str(), SSL_FILETYPE_PEM)) != 1) 
			HandleError("Error trying to use the private key from file : %s\n", retcode);
	} else {
		if ((retcode = SSL_CTX_use_RSAPrivateKey_file(m_ctx, m_keyfile.Str(), SSL_FILETYPE_PEM)) != 1)
			HandleError("Error trying to use the RSA private key from file: %s\n", retcode);
	}

	if ((retcode = SSL_CTX_check_private_key(m_ctx) != 1))
			HandleError("Error while checking the private key : %s\n", retcode);
	
}

int SOAPSSLContext::password_cb(char* buf, int size, int rwflag, void *userdata) 
{
		SOAPString password = ((SOAPSSLContext*)userdata)->m_password;
		if ((unsigned int)size < password.Length())
				throw SOAPMemoryException();
		
		sp_strcpy(buf, password.Str());
		
		return(password.Length());
}
void SOAPSSLContext::HandleError(const char* context, int retcode)
{
	char msg[2048];
	int err = ERR_get_error();
#if OPENSSL_VERSION_NUMBER >= 0x00906000L
	ERR_error_string_n(err, msg, sizeof(msg) - 1);
#else
	// dangerous
	ERR_error_string(err, msg);
#endif // OPENSSL_VERSION_NUMBER

	msg[sizeof(msg) - 1] = 0;
	throw SOAPSocketException(context, msg);
		
}

SSL_CTX* SOAPSSLContext::GetContext()
{
		return m_ctx;
}

SOAPSSLContext::~SOAPSSLContext() 
{
		if (m_ctx)
		{
				SSL_CTX_free(m_ctx);
				m_ctx = 0;
		}
			
}
bool
SOAPSSLContext::IgnoreCertError(int rc) 
{
	for (SOAPArray<int>::const_iterator i = m_certerrors.begin();
			i != m_certerrors.end(); 
			i++) {
		if (*i == rc)
			return true;
	}
	return false;
}

void 
SOAPSSLContext::AddCertErrorToIgnoreList(int rc)
{
	m_certerrors.Add(rc);
}

bool SOAPSSLContext::RemoveCertErrorFromIgnoreList(int rc)
{
	int index = 0;
	for (SOAPArray<int>::const_iterator i = m_certerrors.begin();
			i != m_certerrors.end(); 
			i++) {
		index++;
		if (*i == rc) {
			m_certerrors.RemoveAt(index);
			return true;
		}
	} 
	return false;


}
#endif // EASYSOAP_SSLCONTEXT
