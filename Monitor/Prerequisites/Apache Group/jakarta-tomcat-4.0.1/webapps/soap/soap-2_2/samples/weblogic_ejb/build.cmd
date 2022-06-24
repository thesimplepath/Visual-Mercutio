
@REM Adjust these variables to match your environment
if "" == "%JAVA_HOME%" set JAVA_HOME=\java
if "" == "%WL_HOME%" set WL_HOME=\weblogic
set MYSERVER=%WL_HOME%\myserver
set MYCLASSPATH=%JAVA_HOME%\lib\classes.zip;%WL_HOME%\classes;%WL_HOME%\lib\weblogicaux.jar;%MYSERVER%\clientclasses

@REM Create the build directory, and copy the deployment descriptors into it
mkdir build build\META-INF 
copy *.xml build\META-INF

@REM Compile ejb classes into the build directory (jar preparation)
javac -d build -classpath %MYCLASSPATH% HelloService.java HelloServiceBean.java HelloServiceHome.java

@REM Make a standard ejb jar file, including XML deployment descriptors
cd build
jar cv0f ejb_helloServiceSession.jar META-INF samples
cd ..

@REM Run ejbc to create the deployable jar file
java -classpath %MYCLASSPATH% -Dweblogic.home=%WL_HOME% weblogic.ejbc -compiler javac build\ejb_helloServiceSession.jar %MYSERVER%\ejb_helloServiceSession.jar

