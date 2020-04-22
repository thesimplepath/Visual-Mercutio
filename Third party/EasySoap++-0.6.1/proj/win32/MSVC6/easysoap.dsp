# Microsoft Developer Studio Project File - Name="easysoap" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=easysoap - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "easysoap.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "easysoap.mak" CFG="easysoap - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "easysoap - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "easysoap - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "easysoap - Win32 ReleaseSymbols" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "easysoap - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../win32/Release"
# PROP Intermediate_Dir "../../../win32/Release/obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EASYSOAP_DLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../../include" /I "../../../../expat-1.95.3/source/lib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EASYSOAP_DLL" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 ../../../../Expat-1.95.3/Libs/libexpat.lib wsock32.lib wininet.lib advapi32.lib user32.lib /nologo /dll /machine:I386
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "easysoap - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../win32/Debug"
# PROP Intermediate_Dir "../../../win32/Debug/obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EASYSOAP_DLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../include" /I "../../../../expat-1.95.3/source/lib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EASYSOAP_DLL" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ../../../../Expat-1.95.3/Libs/libexpat.lib wsock32.lib wininet.lib advapi32.lib user32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "easysoap - Win32 ReleaseSymbols"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "easysoap___Win32_ReleaseSymbols"
# PROP BASE Intermediate_Dir "easysoap___Win32_ReleaseSymbols"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../win32/ReleaseSymbols"
# PROP Intermediate_Dir "../../../win32/ReleaseSymbols/obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EASYSOAP_DLL" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "../../../include" /I "../../../../expat-1.95.3/source/lib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EASYSOAP_DLL" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ../win32/Release/expat.lib ws2_32.lib /nologo /dll /machine:I386
# ADD LINK32 ../../../../Expat-1.95.3/Libs/libexpat.lib wsock32.lib wininet.lib advapi32.lib user32.lib /nologo /dll /debug /machine:I386

!ENDIF 

# Begin Target

# Name "easysoap - Win32 Release"
# Name "easysoap - Win32 Debug"
# Name "easysoap - Win32 ReleaseSymbols"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\isapi.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPBase64.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPBody.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPBodyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPCGIServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPCGITransport.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPClientSocketImp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPDebugger.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPEnvelope.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPEnvelopeHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPFault.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPHeader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPHeaderHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPISAPIServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPMethod.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPMethodHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPNamespaces.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPonHTTP.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPParameter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPParameterHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPParse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPProxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPSecureSocketImp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPServerDispatch.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPSSLContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPStructHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPTypeTraits.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPUrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPWinInetTransport.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\XMLComposer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\XMLParser.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\include\easysoap\es_conf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\es_msvc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\es_namespaces.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAP.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPArray.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPBase64.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPBody.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPBodyHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPCGIServer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPCGITransport.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPClientSocketImp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPDebugger.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPDispatchHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPEnvelope.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPEnvelopeHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPFault.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPHashMap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPHeader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPHeaderHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPISAPIServer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPMethod.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPMethodHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPNamespaces.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPonHTTP.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPParameter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPParameterHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPParse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPParseEventHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPPool.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPProxy.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPQName.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPResponse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPSecureSocketImp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPServer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPServerDispatch.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPStack.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPSTL.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPString.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\SOAPStructHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPTransport.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPTypeTraits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPUrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\SOAPWinInetTransport.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\XMLComposer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\easysoap\XMLParser.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
