%define ver 0.6.1
%define rel 1
%define prefix /usr

Summary: SOAP Implemented in C++
Name: EasySoap++
Version: %{ver}
Release: %{rel}
Source: http://prdownloads.sourceforge.net/easysoap/EasySoap++-%{ver}.tar.gz
Copyright: LGPL
URL: http://easysoap.sourceforge.net
Group: System Environment/Libraries
Packager: Blaise St-Laurent <blaise@geeky.net>
Buildroot: /var/tmp/%{name}-root

%description
EasySoap++ is a lightweight SOAP implementation written in C++. It implements
most of the SOAP specification, and interoperates well with many other 
soap implementations.

%package devel
Summary: Libraries, includes and docs for development with EasySoap++
Requires: %{name} = %{ver}
Group: Development/Libraries

%description devel
<insert description here>

%prep
rm -rf $RPM_BUILD_ROOT

%setup
%build
CFLAGS="$RPM_OPT_FLAGS" ./configure --prefix=%{prefix}
make

%install
make prefix=${RPM_BUILD_ROOT}%{prefix} install

%post
ldconfig


%postun
ldconfig

%clean
rm -rf ${RPM_BUILD_ROOT}

%files
%defattr(-,root,root)
%{prefix}/lib/libeasysoap.so*

%files devel
%defattr(-,root,root)
%{prefix}/lib/libeasysoap.a
%{prefix}/lib/libeasysoap.la
%{prefix}/include/easysoap/es_comp.h
%{prefix}/include/easysoap/es_conf.h
%{prefix}/include/easysoap/es_config.h
%{prefix}/include/easysoap/es_msvc.h
%{prefix}/include/easysoap/es_mwerks.h
%{prefix}/include/easysoap/SOAPArray.h
%{prefix}/include/easysoap/SOAPBase64.h
%{prefix}/include/easysoap/SOAPBody.h
%{prefix}/include/easysoap/SOAPCGIServer.h
%{prefix}/include/easysoap/SOAPCGITransport.h
%{prefix}/include/easysoap/SOAPDebugger.h
%{prefix}/include/easysoap/SOAPDispatchHandler.h
%{prefix}/include/easysoap/SOAPEnvelope.h
%{prefix}/include/easysoap/SOAPException.h
%{prefix}/include/easysoap/SOAPFault.h
%{prefix}/include/easysoap/SOAP.h
%{prefix}/include/easysoap/SOAPHashMap.h
%{prefix}/include/easysoap/SOAPHeader.h
%{prefix}/include/easysoap/SOAPMethod.h
%{prefix}/include/easysoap/SOAPNamespaces.h
%{prefix}/include/easysoap/SOAPonHTTP.h
%{prefix}/include/easysoap/SOAPParameter.h
%{prefix}/include/easysoap/SOAPParseEventHandler.h
%{prefix}/include/easysoap/SOAPParse.h
%{prefix}/include/easysoap/SOAPPool.h
%{prefix}/include/easysoap/SOAPProxy.h
%{prefix}/include/easysoap/SOAPQName.h
%{prefix}/include/easysoap/SOAPResponse.h
%{prefix}/include/easysoap/SOAPServerDispatch.h
%{prefix}/include/easysoap/SOAPServer.h
%{prefix}/include/easysoap/SOAPSocket.h
%{prefix}/include/easysoap/SOAPSSLContext.h
%{prefix}/include/easysoap/SOAPStack.h
%{prefix}/include/easysoap/SOAPSTL.h
%{prefix}/include/easysoap/SOAPString.h
%{prefix}/include/easysoap/SOAPTransport.h
%{prefix}/include/easysoap/SOAPTypeTraits.h
%{prefix}/include/easysoap/SOAPUrl.h
%{prefix}/include/easysoap/SOAPUtil.h
%{prefix}/include/easysoap/XMLComposer.h
%{prefix}/include/easysoap/XMLParser.h

