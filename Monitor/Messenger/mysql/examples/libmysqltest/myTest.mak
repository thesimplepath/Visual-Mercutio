# Microsoft Developer Studio Generated NMAKE File, Based on myTest.dsp
!IF "$(CFG)" == ""
CFG=myTest - Win32 Debug
!MESSAGE No configuration specified. Defaulting to myTest - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "myTest - Win32 Release" && "$(CFG)" != "myTest - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "myTest.mak" CFG="myTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "myTest - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "myTest - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "myTest - Win32 Release"

OUTDIR=.\release
INTDIR=.\release
# Begin Custom Macros
OutDir=.\release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\myTest.exe"

!ELSE 

ALL : "libmySQL - Win32 Release" "$(OUTDIR)\myTest.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libmySQL - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Mytest.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\myTest.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /ML /W3 /O2 /I "..\include" /D "NDEBUG" /D "DBUG_UFF" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\myTest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=libmysql.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\myTest.pdb" /machine:I386 /out:"$(OUTDIR)\myTest.exe" /libpath:"..\lib_release" 
LINK32_OBJS= \
	"$(INTDIR)\Mytest.obj" \
	"..\libmysql\release\libmySQL.lib"

"$(OUTDIR)\myTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "myTest - Win32 Debug"

OUTDIR=.\debug
INTDIR=.\debug
# Begin Custom Macros
OutDir=.\debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\myTest.exe"

!ELSE 

ALL : "libmySQL - Win32 Debug" "$(OUTDIR)\myTest.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libmySQL - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Mytest.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\myTest.exe"
	-@erase "$(OUTDIR)\myTest.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /G6 /MTd /W3 /Gm /ZI /Od /I "..\include" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\myTest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=libmysql.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\myTest.pdb" /debug /machine:I386 /out:"$(OUTDIR)\myTest.exe" /pdbtype:sept /libpath:"..\lib_debug" 
LINK32_OBJS= \
	"$(INTDIR)\Mytest.obj" \
	"..\libmysql\debug\libmySQL.lib"

"$(OUTDIR)\myTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("myTest.dep")
!INCLUDE "myTest.dep"
!ELSE 
!MESSAGE Warning: cannot find "myTest.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "myTest - Win32 Release" || "$(CFG)" == "myTest - Win32 Debug"

!IF  "$(CFG)" == "myTest - Win32 Release"

"libmySQL - Win32 Release" : 
   cd "\MYSQL-3.23\libmysql"
   $(MAKE) /$(MAKEFLAGS) /F ".\libmySQL.mak" CFG="libmySQL - Win32 Release" 
   cd "..\libmysqltest"

"libmySQL - Win32 ReleaseCLEAN" : 
   cd "\MYSQL-3.23\libmysql"
   $(MAKE) /$(MAKEFLAGS) /F ".\libmySQL.mak" CFG="libmySQL - Win32 Release" RECURSE=1 CLEAN 
   cd "..\libmysqltest"

!ELSEIF  "$(CFG)" == "myTest - Win32 Debug"

"libmySQL - Win32 Debug" : 
   cd "\MYSQL-3.23\libmysql"
   $(MAKE) /$(MAKEFLAGS) /F ".\libmySQL.mak" CFG="libmySQL - Win32 Debug" 
   cd "..\libmysqltest"

"libmySQL - Win32 DebugCLEAN" : 
   cd "\MYSQL-3.23\libmysql"
   $(MAKE) /$(MAKEFLAGS) /F ".\libmySQL.mak" CFG="libmySQL - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\libmysqltest"

!ENDIF 

SOURCE=.\Mytest.c

"$(INTDIR)\Mytest.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

