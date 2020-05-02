set JAVA_HOME=C:\jdk1.3.1
  set CLASSPATH=C:\Program Files\Apache Group\jakarta-tomcat-4.0.1\webapps\soap\soap-2_2\lib\soap.jar
  set CLASSPATH=%CLASSPATH%;C:\Program Files\Apache Group\jakarta-tomcat-4.0.1\common\lib\mail.jar
  set CLASSPATH=%CLASSPATH%;C:\Program Files\Apache Group\jakarta-tomcat-4.0.1\common\lib\activation.jar
  set CLASSPATH=%CLASSPATH%;C:\Program Files\Apache Group\jakarta-tomcat-4.0.1\common\lib\xerces.jar
  java org.apache.soap.server.ServiceManagerClient http://localhost:8080/soap/servlet/rpcrouter deploy %1
  pause
