@echo off
rem
rem DS Deployment Utility.
rem

rem Set up env
call %WSTK_HOME%\bin\wstkenv.bat

:setcp
rem Save current CLASSPATH
set SAVE_CP=%CLASSPATH%

rem Run command 
"%JAVA_CMD%" -cp "%WSTK_CP% -DWSTK_HOME=%WSTK_HOME% com.ibm.services.data.service.DSServicesSetup deploy

:exit
set CLASSPATH=%SAVE_CP%
if "%OS%" == "Windows_NT" endlocal


