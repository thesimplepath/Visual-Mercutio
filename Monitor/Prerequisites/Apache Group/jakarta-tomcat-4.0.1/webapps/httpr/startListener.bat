@echo off
if "%OS%" == "Windows_NT" setlocal

rem Check if WSTK_HOME is set
if not "%WSTK_HOME%" == "" goto run1
echo ERROR: WSTK_HOME must be set to the Web Services Toolkit home directory.
goto end

:run1
if not "%WSTK_CP%" == "" goto run
echo ERROR: WSTK_CP must be set
goto end

:run
rem run program
set CLASSPATH=%WSTK_CP%;%CLASSPATH%
@echo Starting the Axis-HTTPR Listener
%JAVA_HOME%\bin\java -cp "%WSTK_CP%" com.ibm.httpr.axis.HTTPRListener %WSTK_HOME%\demos\httpr\stateFile.ser

:end
if "%OS%" == "Windows_NT" endlocal

