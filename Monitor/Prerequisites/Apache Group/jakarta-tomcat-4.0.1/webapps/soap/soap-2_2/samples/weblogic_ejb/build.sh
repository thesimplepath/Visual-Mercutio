#!/bin/sh
WL_HOME=${WL_HOME:-"/local/weblogic"}
MYSERVER="$WL_HOME/myserver"

if [ -w /dev/null ]
then
  MYCLASSPATH="$JAVA_HOME/lib/classes.zip:$WL_HOME/classes:$WL_HOME/lib/weblogicaux.jar:$MYSERVER/clientclasses"
else
  MYCLASSPATH="$JAVA_HOME/lib/classes.zip;$WL_HOME/classes;$WL_HOME/lib/weblogicaux.jar;$MYSERVER/clientclasses"
fi

# Create the build directory, and copy the deployment descriptors into it
mkdir -p build build/META-INF
cp -f ejb-jar.xml weblogic-ejb-jar.xml build/META-INF

# Compile ejb classes into the build directory (jar preparation)
javac -d build -classpath $MYCLASSPATH HelloService.java HelloServiceBean.java HelloServiceHome.java

# Make a standard ejb jar file, including XML deployment descriptors
(cd build; jar cv0f ejb_helloServiceSession.jar META-INF samples)

# Run ejbc to create the deployable jar file
java -classpath $MYCLASSPATH \
   -Dweblogic.home=$WL_HOME weblogic.ejbc \
    -keepgenerated -compiler javac build/ejb_helloServiceSession.jar \
    $MYSERVER/ejb_helloServiceSession.jar

