@echo off
rem
rem DS Undeployment Utility.
rem

rem Set up env
call %WSTK_HOME%\bin\wstkenv.bat

:setcp
rem Save current CLASSPATH
set SAVE_CP=%CLASSPATH%

rem Run command 
"%JAVA_CMD%" -cp "%WSTK_CP% com.ibm.services.data.service.DSServicesSetup undeploy

:exit
set CLASSPATH=%SAVE_CP%
if "%OS%" == "Windows_NT" endlocal


