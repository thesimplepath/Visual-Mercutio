@echo off
rem - set up MQ as needed for testing HTTPR

set mqsetup_rc=999

if NOT "%*%" == "" (
  echo '%0%' will set up MQSeries for use with HTTPR demonstration code.
  echo It should be called with no parameters.
  goto :endup
)

rem -------------------------------------------------------------
rem - check that we can find MQ programs
call :findfile runmqsc.exe mqsetup_xxx
if "%mqsetup_xxx%" == "" (
  echo Cannot find 'runmqsc'.  
  echo Please check that MQSeries is properly installed and included in your PATH.
  set mqsetup_rc=101
  goto :endup
)

rem - check that we can find MQ java programs
call :findfile mqjbnd02.dll mqsetup_xxx
if "%mqsetup_xxx%" == "" (
  echo --------------------------------------------------
  echo Warning, MQSeries JMS is not correctly setup.
  echo Continuing with %0%, but MQSeries JMS programs may not execute correctly.
  echo --------------------------------------------------
)

rem -------------------------------------------------------------
rem - check for running default queue manager
:checkqm
echo end | runmqsc >noshow.txt 2>noshow2.txt

rem - case QM running ok
if %errorlevel%==0 goto :qmok

rem - case no QM running
if %errorlevel%==20 goto :strmqm

rem - case ???
echo Unexpected return code %errorlevel% from "runmqsc". Cannot continue.
set mqsetup_rc=102
goto :eendup


rem -------------------------------------------------------------
rem - we must start the (default) queue manager
:strmqm
strmqm >noshow.txt 2>noshow2.txt

rem - case no queue manager, must create one (create will then start it)
if %errorlevel%==16 goto :crtmqm

rem - case queue manager started ok
if %errorlevel%==0 (
  echo Default queue manager started.
  goto :qmok
)

rem - case ???
echo Unexpected return code %errorlevel% from "strmqm". Cannot continue.
set mqsetup_rc=103
goto :eendup

rem -------------------------------------------------------------
rem - we must create (and start) the queue manager
:crtmqm

rem - Create queue manager.  -q means default queue manager
echo Creating HTTPR_QM as default queue manager.
crtmqm -q HTTPR_QM >noshow.txt 2>noshow2.txt

rem - case ok, start it
if %errorlevel%==0 (
  echo Queue manager HTTPR_QM created and set as default queue mananger.
  goto :strmqm
)

rem - case ???
echo Cannot create queue manager, reason %errorlevel%
set mqsetup_rc=104
goto :eendup


rem -------------------------------------------------------------
rem - define queues.
:qmok

rem - HTTPR.CHANNEL.QUEUE is where MQ stores channel and message status
call :createqueue HTTPR.CHANNEL.QUEUE

rem - HTTPR.OUTGOING is where all messages FROM MQ to HTTPR are stored.
rem -   (effectively transmission queue, but not technically)
call :createqueue HTTPR.OUTGOING

rem - soap is used as sample target for messages written from
rem - HTTPR into MQ ready for axis.
rem - eg for target-uri: //localhost:8080#soapin
call :createqueue soapin

rem - echo "MQSeries setup complete"
set mqsetup_rc=0
goto :endup

rem ---------------------------------------------------------------
rem ---------------------------------------------------------------
rem - create queue subroutine
rem - if it already exista, runmqsc will just give an unimportant error
:createqueue
echo define qlocal('%1%') | runmqsc -e  >noshow.txt 2>noshow2.txt

if %errorlevel% == 0 (
  echo Queue '%1%' created.
) else (  
  if %errorlevel% == 10 (
    rem - echo Queue '%1%' already existed.
  ) else (
    echo Serious error %errorlevel% creating queue %1%.
    goto :eendup
  )
)

exit /b

rem ---------------------------------------------------------------
rem - find in the path the file specified in %1, and return in environment varible named %2:
rem - eg findfile mqm.bat fred
rem - may set fred=c:\Program Files\MQSeries\bin\mqm.dll
:findfile
set %2=%~$PATH:1
exit /b
       
rem ---------------------------------------------------------------
rem - error ending, give a little information before cleanup
:eendup
echo ------------------------ output from failing command
echo --
type noshow.txt
echo --
echo ------------------------ error output from failing command
echo --
type noshow2.txt
echo --

rem - tidy up the scratch file and exit
:endup
if exist noshow.txt erase noshow.txt
if exist noshow2.txt erase noshow2.txt
exit /b %mqsetup_rc%
