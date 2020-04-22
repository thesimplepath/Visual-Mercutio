all: setup easysoapdll interopclient interopserver simpleclient simpleisapi simpleserver validator

easysoapdll:
 make -f easysoap.mak

interopclient:
 make -f interopclient.mak

interopserver:
 make -f interopserver.mak

simpleclient:
 make -f simpleclient.mak

simpleisapi:
 make -f simpleisapi.mak

simpleserver:
 make -f simpleserver.mak

validator:
 make -f validator.mak

clean:
 del ..\..\..\win32\release\obj\*.obj

cleanall:
 deltree /y ..\..\..\win32

setup:
 setup
