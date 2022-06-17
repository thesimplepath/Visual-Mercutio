# Visual Mercutio
This repository contains the full source code of the process management solution **Visual Mercutio**, as well as its **Monitor** server system, originally developed by ProcessSoft. This code source is published with the kind permission of Mr. Eric Bouchez.

![Visual Mercutio main frame](Documents/Screenshots/VisualMercutio_MainFrame.png)

**Visual Mercutio** source code and all its relative tools and services are provided under the terms of the MIT License. Please find the complete product documentation in the Documents directory.

## Prerequisites
To compile the **Visual Mercutio** source code, Visual Studio 2019 needs to be installed, along with the MFC library. A newer version of Visual Studio may theorically be used but I never tested it.

Also several third party libraries are required:
- **CJ60Lib**. The CodeJockeys library is an extended component set for MFC applications. This library is no longer developed, but you can find the source code in the Third Party directory.
- **easysoap++**. The easysoap+ + is a c++ library for SOAP (Simple Object Access Protocol). The project seems no longer active since 2006, however a working copy may be found in the Third Party directory. Further info about this project may be found here: http://easysoap.sourceforge.net
- **expat**. Expat is a c library for parsing XML. A submodule to the official project may be found in the Third Party directory. Further info about this project may be found here: https://libexpat.github.io/
- **Stingray Studio**. This library isn't open source, for that reason it cannot be found in the Third Party directory. Please contact the developer website to get a copy: https://www.roguewave.com/
- Additionaly you may need the following DLLs: ddao35.dll, msvcp71.dll, msvcr71.dll and vc6-re200l.dll

## Compilation
Install **Visual Studio 2019** with the **MFC** library (should be selected explicitly in the installation options). You can download a copy from here: https://visualstudio.microsoft.com/vs/older-downloads/

Here are the steps to compile:
1. Build the CJ60Lib library, and copy the compiled DLL to the \Visual Mercutio\exe\ directory (for the Debug version), and the \Visual Mercutio\exeR\ directory (for the Release version), respectively
2. Build the easysoap++ library, and copy the compiled DLL to the \Visual Mercutio\exe\ directory (for the Debug version), and the \Visual Mercutio\exeR\ directory (for the Release version), respectively
3. Build the expat library, and copy the compiled DLL to the \Visual Mercutio\exe\ directory (for the Debug version), and the \Visual Mercutio\exeR\ directory (for the Release version), respectively
4. Build the Stingray Studio library, and copy the following compiled DLLs: RWUXThemeS.dll, sfl204as.dll, og904as.dll, OT804as.dll and OV804as.dll, to the \Visual Mercutio\exe\ directory (for the Debug version), and the \Visual Mercutio\exeR\ directory (for the Release version), respectively
5. Open the VisualMercutio.sln solution in Visual Studio 2019, right click on zProcess32 project and select Rebuild

## Monitor
The Monitor server is a set of several services which allows to publish data exported from the Visual Mercutio application into a database, which may be accessed from a network. The services composing the Monitor server are:

- **Messenger**. This web service allows to publish a model database (also called model universe) from the Visual Mercuto application.
- **Team editor**. This is a tool allowing to show all the existing universes and to select the active one.
- **BatchMessages**. This is a directory server containing the configuration files required for the java environment.

The project contains also several tools required to administer the Monitor server.

## Side note
The paper size visible on the application depends directly on the selected paper size of your default printer. Since the latest Windows 10 updates, there is an option to let the printer manager to automatically select you default printer. This may cause previously created models to be shown on a page with an incorrect size, which may crop a part of your model. If this situation happens, please disable the "Let Windows manage my default printer" option in the "Printers & Scanners" tab, and select your correct default printer, which contain the expected paper size manually.
