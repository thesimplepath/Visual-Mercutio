# Monitor server
The Monitor server is a set of several services which allows to publish data exported from the Visual Mercutio application into a database, which may be accessed from a network. The services composing the Monitor server are:

- **Messenger**. This web service allows to publish a model database (also called model universe) from the Visual Mercuto application.
- **Team editor**. This is a tool allowing to show all the existing universes and to select the active one.
- **BatchMessages**. This is a directory server containing the configuration files required for the java environment.

The project contains also several tools required to administer the Monitor server.

## Prerequisites
In order to compile and install the Monitor server applications and services, you will need the following features:
- **MySQL server**. You can download it at https://www.mysql.com/
- **SQL Connector/NET API**. This is a Visual Studio connector for MySQL database. You can download it from the following website: https://www.mysql.com/ **NOTE** the version originally used to develop the Monitor connectors was the 1.0.7
- **Java Development Kit**. You can download it at https://www.oracle.com/java/technologies/ **NOTE** the version originally used to develop the Monitor connectors was the 5.0.06 (the 3.1.02 was also used on the beginning of the project)
- **Apache HTTP server**. You can download it at https://httpd.apache.org/
- **Apache Tomcat**. You can download it at http://tomcat.apache.org/ **NOTE** the version originally used to develop the Monitor connectors was the 4.0.1
- **.NET Framework 4.7 or higher**. Just check your installed version and update it from the Microsoft website if required at https://dotnet.microsoft.com/download/dotnet-framework
- **Eclipse**. You can optionnally download this development platform at https://www.eclipse.org/

**NOTE** the prerequisites folder contains a frozen snapshot of the working directory used for the development. This is because some data were customized and may be required to install the Monitor server on a new computer.

## Compilation
Please read the Monitor.chm document available in the Documentation directory.
