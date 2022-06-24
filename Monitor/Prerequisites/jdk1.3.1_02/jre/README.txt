                                README

           Java(TM) 2 Runtime Environment, Standard Edition
                            Version 1.3.1
                          

 *********************************************************************
 *               Notice of New Redistribution Options                 *
 *                                                                    *
 * Beginning October 17, 2001, it is permissable to redistribute      *
 * the "javac" compiler with the Java 2 Runtime Environment (JRE).    *
 * See the Sun Binary Code License and this README for terms          *
 * and conditions.  Items that have been added to the section         *
 * in this README entitled "Redistribution of Java 2 SDK files"       *
 * are:                                                               *
 *                                                                    *
 * bin/javac.exe  (Microsoft Windows)                                 *
 * bin/javac and bin/i386/native_threads/javac (Linux and Solaris IA) *
 * bin/javac and bin/sparc/native_threads/javac  (Solaris SPARC)      *
 * lib/tools.jar  (all platforms)                                     *
 *                                                                    *
 * These files include the Java 2 SDK tools classes, including        *
 * the classes for the "javac" compiler.                              *
 *                                                                    *
 * Additionally, on Microsoft Windows platforms it is now             *
 * permissible to redistribute the Java HotSpot Server VM (also       *
 * known as "C2") with the Microsoft Windows version of the           * 
 * JRE. (C2 is already included with the JREs for Linux and the       *
 * Solaris(TM) operating environment.)  Items that have been added    *
 * to the section on "Redistribution of Java 2 SDK files" are:        *       
 *                                                                    *
 * jre/bin/server/jvm.dll                                             * 
 * jre/bin/server/Xusage.txt                                          * 
 *                                                                    * 
 **********************************************************************



The Java 2 Runtime Environment is intended for software developers 
and vendors to redistribute with their applications.

The Java(TM) 2 Runtime Environment contains the Java virtual machine, 
runtime class libraries, and Java application launcher that are 
necessary to run programs written in the Java progamming language. 
It is not a development environment and does not contain development 
tools such as compilers or debuggers.  For development tools, see the 
Java 2 SDK, Standard Edition.


=======================================================================
           Installation Instructions and System Requirements
======================================================================= 

For installation instructions and system requirements for this 
release, see 

     http://java.sun.com/j2se/1.3/install.html 

=======================================================================
     Deploying Applications with the Java 2 Runtime Environment
======================================================================= 

A Java-language application, unlike an applet, cannot rely on a web 
browser for installation and runtime services. When you deploy an  
application written in the Java programming language, your software 
bundle will probably consist of the following parts: 

            Your own class, resource, and data files. 
            A runtime environment. 
            An installation procedure or program. 

You already have the first part, of course. The remainder of this
document covers the other two parts. See also the Notes for Developers 
page on the Java Software website:

     http://java.sun.com/j2se/1.3/runtime.html

-----------------------------------------------------------------------
Runtime Environment
-----------------------------------------------------------------------

To run your application, a user needs a Java virtual machine, the Java 
platform core classes, and various support programs and files. This 
collection of software is known as a runtime environment. 

The Java 2 SDK software can serve as a runtime environment. However, 
you probably can't assume your users have the Java 2 SDK installed, 
and your Java 2 SDK license doesn't allow you to redistribute SDK 
files. 

To solve this problem, Sun provides the Java 2 Runtime Environment 
as a free, redistributable runtime environment. (The Java 2 runtime 
environment should not be confused with the Java 2 SDK's own internal, 
non-redistributable version of the runtime environment housed in the 
SDK's 'jre' directory.)   

The final step in the deployment process occurs when the software is 
installed on individual user system. Installation consists of copying 
software onto the user's system, then configuring the user's system to 
support that software. 

This step includes installing and configuring the runtime environment. 
If you use the Java 2 Runtime Environment, you must make sure that your 
installation procedure never overwrites an existing installation, unless 
the existing runtime environment is an older version. 


=======================================================================
           Redistribution of the Java 2 Runtime Environment
=======================================================================
The term "vendors" used here refers to licensees, developers, and 
independent software vendors (ISVs) who license and distribute the 
Java 2 Runtime Environment with their programs.  

Vendors must follow the terms of the Binary Code License agreement  
which include, among others:

 - Arbitrary subsetting of the Java 2 Runtime Environment is not 
   allowed. See the section below entitled "Required vs. Optional Files" 
   for those files that may be optionally omitted from redistributions 
   of the runtime environment. 

 - You must include in your product's license the provisions called 
   out in the Binary Code license.

-----------------------------------------------------------------------
Required vs. Optional Files
-----------------------------------------------------------------------
Licensees must follow the terms of the Java 2 Runtime Environment 
license.  

The files that make up the Java 2 Runtime Environment are divided into 
two categories: required and optional.  Optional files may be excluded 
from redistributions of the Java 2 Runtime Environment at the 
licensee's discretion.  

The following section contains a list of the files and directories that 
may optionally be omitted from redistributions with the Java 2 Runtime 
Environment.  All files not in these lists of optional files must be 
included in redistributions of the runtime environment.


-----------------------------------------------------------------------
Optional Files and Directories
-----------------------------------------------------------------------
The following files may be optionally excluded from redistributions:

lib/i18n.jar                  
   Character conversion classes and all other locale support
lib/ext/                      
   Directory containing extension jar files
bin/rmid
   Java RMI Activation System Daemon
bin/rmiregistry
   Java Remote Object Registry
bin/tnameserv
   Java IDL Name Server
bin/keytool
   Key and Certificate Management Tool
bin/policytool
   Policy File Creation and Management Tool


-----------------------------------------------------------------------
Redistribution of Java 2 SDK Files
-----------------------------------------------------------------------

The Java 2 SDK, Standard Edition, may not be redistributed. However, 
the limited set of files from the SDK listed below may be included in 
vendor redistributions of the Java 2 Runtime Environment.  All paths 
are relative to the top-level directory of the SDK.

 - jre/lib/cmm/PYCC.pf
      Color-management profile. This file is required only if the 
      Java 2D API is used to perform color map conversions.

 - All .ttf font files in the jre/lib/fonts directory. Note that the 
   LucidaSansRegular.ttf font is already contained in the Java 2 
   Runtime Environment, so there is no need to bring that file over 
   from the SDK. 

 - jre/lib/audio/soundbank.gm
      This MIDI soundbank is present in the Java 2 SDK, 
      but has been removed from the Java 2 Runtime Environment in 
      order to reduce the size of the Runtime Environment's download 
      bundle. MIDI soundbanks are often available in hardware form 
      or as part of the operating system on modern systems, and it 
      therefore may not be necessary to redistribute the soundbank.gm 
      file with the Runtime Environment. The SDK's soundbank.gm file 
      may, however, be included in redistributions of the Runtime 
      Environment at the vendor's discretion. Several versions of 
      enhanced MIDI soundbanks are available from the Java Sound 
      web site: http://java.sun.com/products/java-media/sound/
      These alternative soundbanks may be included in redistributions 
      of the Java 2 Runtime Environment.

 - bin/javac.exe  (Microsoft Windows)
   bin/javac and bin/i386/native_threads/javac  (Linux and Solaris x86)
   bin/javac and bin/sparc/native_threads/javac  (Solaris SPARC)
   lib/tools.jar  (all platforms)
      These files include the Java 2 SDK tool classes, including the 
      classes for the javac compiler.

 - The Java HotSpot Server VM (also knowns as "C2") may now be 
   redistributed in the JRE for Microsoft Windows.  (C2 is already 
   included with the JREs for Linux and the Solaris(TM) operating 
   environment.)  The files from the SDK for Microsoft Windows    
   that may be redistribed with the JRE are these:
      jre/bin/server/jvm.dll
      jre/bin/server/Xusage.txt
      

-----------------------------------------------------------------------
Copyright (c) 1998-2001 Sun Microsystems(tm), Inc.
901 San Antonio Road, Palo Alto, CA 94303-4900
All rights reserved.

