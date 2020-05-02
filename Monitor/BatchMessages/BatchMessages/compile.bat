set JAVA_HOME=c:\jdk1.5.0_06
set PATH=%PATH%;c:\jdk1.5.0_06\bin

rem set CLASSPATH=C:\Monitor\BatchMessages\mysql-connector-java-3.1.7-bin.jar
rem set CLASSPATH=%CLASSPATH%;c:\jdk1.5.0_06\jre\lib\rt.jar
rem set CLASSPATH=%CLASSPATH%;c:\jdk1.5.0_06\jre\lib\jsse.jar
rem set CLASSPATH=%CLASSPATH%;c:\jdk1.5.0_06\jre\lib\jce.jar
rem set CLASSPATH=%CLASSPATH%;c:\jdk1.5.0_06\jre\lib\ext\dnsns.jar
rem set CLASSPATH=%CLASSPATH%;c:\jdk1.5.0_06\jre\lib\ext\sunjce_provider.jar
rem set CLASSPATH=%CLASSPATH%;c:\jdk1.5.0_06\jre\lib\ext\sunpkcs11.jar



javac  -cp .;D:\DemoMonitor\BatchMessages\mysql-connector-java-3.1.7-bin.jar BatchMessages.java
pause

