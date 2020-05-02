set JAVA_HOME=c:\jdk1.5.0_06
set PATH=%PATH%;c:\jdk1.5.0_06\bin

java  -cp .;mysql-connector-java-3.1.7-bin.jar BatchMessages "C:\Program Files\Apache Group\jakarta-tomcat-4.0.1\bin\alias.ini" "workflow"
pause

