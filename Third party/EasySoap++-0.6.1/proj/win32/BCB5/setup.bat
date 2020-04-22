REM CommandInterpreter: command.com /E:1024
REM Set EXPATHOME to the top directiory of the Expat sources

SET EXPATHOME=..\..\..\..\Expat-1.95.2

if not exist ..\..\..\win32\nul mkdir ..\..\..\win32
if not exist ..\..\..\win32\release\nul mkdir ..\..\..\win32\release
if not exist ..\..\..\win32\release\obj\nul mkdir ..\..\..\win32\release\obj

if exist %EXPATHOME%\Libs\expat.dll copy %EXPATHOME%\Libs\expat.dll ..\..\..\win32\release
if exist %EXPATHOME%\Libs\expat.tds copy %EXPATHOME%\Libs\expat.tds ..\..\..\win32\release
