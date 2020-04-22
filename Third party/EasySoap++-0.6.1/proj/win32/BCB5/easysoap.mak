# ---------------------------------------------------------------------------
!if !$d(BCB)
BCB = $(MAKEDIR)\..
!endif

# ---------------------------------------------------------------------------
# IDE SECTION
# ---------------------------------------------------------------------------
# The following section of the project makefile is managed by the BCB IDE.
# It is recommended to use the IDE to change any of the values in this
# section.
# ---------------------------------------------------------------------------

VERSION = BCB.05.03
# ---------------------------------------------------------------------------
PROJECT = ..\..\..\win32\Release\easysoap.dll
OBJFILES = ..\..\..\win32\Release\obj\isapi.obj \
    ..\..\..\win32\Release\obj\SOAPBase64.obj \
    ..\..\..\win32\Release\obj\SOAPBody.obj \
    ..\..\..\win32\Release\obj\SOAPBodyHandler.obj \
    ..\..\..\win32\Release\obj\SOAPCGIServer.obj \
    ..\..\..\win32\Release\obj\SOAPCGITransport.obj \
    ..\..\..\win32\Release\obj\SOAPClientSocketImp.obj \
    ..\..\..\win32\Release\obj\SOAPDebugger.obj \
    ..\..\..\win32\Release\obj\SOAPEnvelope.obj \
    ..\..\..\win32\Release\obj\SOAPEnvelopeHandler.obj \
    ..\..\..\win32\Release\obj\SOAPFault.obj \
    ..\..\..\win32\Release\obj\SOAPHeader.obj \
    ..\..\..\win32\Release\obj\SOAPHeaderHandler.obj \
    ..\..\..\win32\Release\obj\SOAPHTTPServer.obj \
    ..\..\..\win32\Release\obj\SOAPISAPIServer.obj \
    ..\..\..\win32\Release\obj\SOAPMethod.obj \
    ..\..\..\win32\Release\obj\SOAPMethodHandler.obj \
    ..\..\..\win32\Release\obj\SOAPNamespaces.obj \
    ..\..\..\win32\Release\obj\SOAPonHTTP.obj \
    ..\..\..\win32\Release\obj\SOAPParameter.obj \
    ..\..\..\win32\Release\obj\SOAPParameterHandler.obj \
    ..\..\..\win32\Release\obj\SOAPParse.obj \
    ..\..\..\win32\Release\obj\SOAPProxy.obj \
    ..\..\..\win32\Release\obj\SOAPResponse.obj \
    ..\..\..\win32\Release\obj\SOAPSecureSocketImp.obj \
    ..\..\..\win32\Release\obj\SOAPServerDispatch.obj \
    ..\..\..\win32\Release\obj\SOAPSocket.obj \
    ..\..\..\win32\Release\obj\SOAPStructHandler.obj \
    ..\..\..\win32\Release\obj\SOAPTypeTraits.obj \
    ..\..\..\win32\Release\obj\SOAPUrl.obj \
    ..\..\..\win32\Release\obj\SOAPWinInetTransport.obj \
    ..\..\..\win32\Release\obj\XMLComposer.obj \
    ..\..\..\win32\Release\obj\XMLParser.obj \
    ..\..\..\win32\Release\obj\conn.obj ..\..\..\win32\Release\obj\data.obj \
    ..\..\..\win32\Release\obj\file.obj ..\..\..\win32\Release\obj\http.obj \
    ..\..\..\win32\Release\obj\server.obj \
    ..\..\..\win32\Release\obj\socket.obj ..\..\..\win32\Release\obj\thread.obj \
    ..\..\..\win32\Release\obj\threadpool.obj \
    ..\..\..\win32\Release\obj\trace.obj
RESFILES = 
MAINSOURCE = easysoap.bpf
RESDEPEN = $(RESFILES)
LIBFILES = ..\..\..\..\Expat-1.95.2\Libs\expat.lib
IDLFILES = 
IDLGENFILES = 
LIBRARIES = 
PACKAGES = VCL50.bpi VCLX50.bpi dclocx50.bpi bcbsmp50.bpi QRPT50.bpi VCLDB50.bpi \
    VCLBDE50.bpi ibsmp50.bpi VCLDBX50.bpi TEEUI50.bpi TEEDB50.bpi TEE50.bpi \
    TEEQR50.bpi VCLIB50.bpi bcbie50.bpi VCLIE50.bpi INETDB50.bpi INET50.bpi \
    NMFAST50.bpi bcb2kaxserver50.bpi
SPARELIBS = 
DEFFILE = 
# ---------------------------------------------------------------------------
PATHCPP = .;..\..\..\src;..\..\..\src\abyss\src
PATHASM = .;
PATHPAS = .;
PATHRC = .;
DEBUGLIBPATH = $(BCB)\lib\debug
RELEASELIBPATH = $(BCB)\lib\release
USERDEFINES = WIN32;NDEBUG;_WINDOWS;_MBCS;_USRDLL;EASYSOAP_DLL;_DEBUG
SYSDEFINES = _NO_VCL;_ASSERTE;NO_STRICT;_RTLDLL
INCLUDEPATH = ..\..\..\include;..\..\..\..\Expat-1.95.2\Source\Lib;..\..\..\src;..\..\..\src\abyss\src;$(BCB)\include
LIBPATH = ..\..\..\src;..\..\..\src\abyss\src;$(BCB)\lib
WARNINGS= -w-8026 -w-8027 -w-par
# ---------------------------------------------------------------------------
CFLAG1 = -WD -Od -w -X- -r- -a8 -5 -b -k -y -v -vi- -q -tWR -tWM -I../include \
    -I../../expat-1.95.2/source/lib -Iabyss/src -c -tWD
IDLCFLAGS = -I$(BCB)\include
PFLAGS = -N2..\..\..\win32\Release\obj -N0..\..\..\win32\Release\obj -$YD -$W -$O-
RFLAGS = /l 0x409 /d "NDEBUG" /i$(BCB)\include;$(BCB)\include\mfc
AFLAGS = /mx /w2 /zi
LFLAGS = -I..\..\..\win32\Release\obj -D"" -aa -Tpd -x -Gn -Gi -v -q
# ---------------------------------------------------------------------------
ALLOBJ = c0d32.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) $(LIBRARIES) WININET.LIB import32.lib cw32mti.lib
# ---------------------------------------------------------------------------
!ifdef IDEOPTIONS

[Version Info]
IncludeVerInfo=0
AutoIncBuild=0
MajorVer=1
MinorVer=0
Release=0
Build=0
Debug=0
PreRelease=0
Special=0
Private=0
DLL=0

[Version Info Keys]
CompanyName=
FileDescription=
FileVersion=1.0.0.0
InternalName=
LegalCopyright=
LegalTrademarks=
OriginalFilename=
ProductName=
ProductVersion=1.0.0.0
Comments=

[Debugging]
DebugSourceDirs=$(BCB)\source\vcl

!endif





# ---------------------------------------------------------------------------
# MAKE SECTION
# ---------------------------------------------------------------------------
# This section of the project file is not used by the BCB IDE.  It is for
# the benefit of building from the command-line using the MAKE utility.
# ---------------------------------------------------------------------------

.autodepend
# ---------------------------------------------------------------------------
!if "$(USERDEFINES)" != ""
AUSERDEFINES = -d$(USERDEFINES:;= -d)
!else
AUSERDEFINES =
!endif

!if !$d(BCC32)
BCC32 = bcc32
!endif

!if !$d(CPP32)
CPP32 = cpp32
!endif

!if !$d(DCC32)
DCC32 = dcc32
!endif

!if !$d(TASM32)
TASM32 = tasm32
!endif

!if !$d(LINKER)
LINKER = ilink32
!endif

!if !$d(BRCC32)
BRCC32 = brcc32
!endif


# ---------------------------------------------------------------------------
!if $d(PATHCPP)
.PATH.CPP = $(PATHCPP)
.PATH.C   = $(PATHCPP)
!endif

!if $d(PATHPAS)
.PATH.PAS = $(PATHPAS)
!endif

!if $d(PATHASM)
.PATH.ASM = $(PATHASM)
!endif

!if $d(PATHRC)
.PATH.RC  = $(PATHRC)
!endif
# ---------------------------------------------------------------------------
$(PROJECT): $(IDLGENFILES) $(OBJFILES) $(RESDEPEN) $(DEFFILE)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) -L$(LIBPATH) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES)
!
# ---------------------------------------------------------------------------
.pas.hpp:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) -U$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -O$(INCLUDEPATH) --BCB {$< }

.pas.obj:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) -U$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -O$(INCLUDEPATH) --BCB {$< }

.cpp.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n. {$< }

.cpp.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n. {$< }

.asm.obj:
    $(BCB)\BIN\$(TASM32) $(AFLAGS) -i$(INCLUDEPATH:;= -i) $(AUSERDEFINES) -d$(SYSDEFINES:;= -d) $<, $@

.rc.res:
    $(BCB)\BIN\$(BRCC32) $(RFLAGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -fo$@ $<
# ---------------------------------------------------------------------------




