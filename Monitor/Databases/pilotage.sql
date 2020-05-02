-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.0.22-community-nt


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


--
-- Create schema pilotage
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ pilotage;
USE pilotage;

--
-- Table structure for table `pilotage`.`aile`
--

DROP TABLE IF EXISTS `aile`;
CREATE TABLE `aile` (
  `emplid` int(10) unsigned NOT NULL default '0',
  `wkgid` int(10) unsigned NOT NULL default '0',
  `calmonth` int(10) unsigned NOT NULL default '0',
  `calyear` int(10) unsigned NOT NULL default '0',
  `taux` decimal(10,2) NOT NULL default '0.00',
  PRIMARY KEY  (`emplid`,`wkgid`,`calmonth`,`calyear`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`aile`
--

/*!40000 ALTER TABLE `aile` DISABLE KEYS */;
/*!40000 ALTER TABLE `aile` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`ailecriteria`
--

DROP TABLE IF EXISTS `ailecriteria`;
CREATE TABLE `ailecriteria` (
  `ailecriteriaid` int(10) unsigned NOT NULL auto_increment,
  `ailecriteria` varchar(100) NOT NULL default '',
  PRIMARY KEY  (`ailecriteriaid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`ailecriteria`
--

/*!40000 ALTER TABLE `ailecriteria` DISABLE KEYS */;
INSERT INTO `ailecriteria` (`ailecriteriaid`,`ailecriteria`) VALUES 
 (1,'Affectation'),
 (2,'Ancienneté');
/*!40000 ALTER TABLE `ailecriteria` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`aip`
--

DROP TABLE IF EXISTS `aip`;
CREATE TABLE `aip` (
  `emplid` int(10) unsigned NOT NULL default '0',
  `calmonth` int(10) unsigned NOT NULL default '0',
  `calyear` int(10) unsigned NOT NULL default '0',
  `taux` decimal(10,2) NOT NULL default '0.00',
  PRIMARY KEY  (`emplid`,`calmonth`,`calyear`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`aip`
--

/*!40000 ALTER TABLE `aip` DISABLE KEYS */;
/*!40000 ALTER TABLE `aip` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`aipcriteria`
--

DROP TABLE IF EXISTS `aipcriteria`;
CREATE TABLE `aipcriteria` (
  `aipcriteriaid` int(11) NOT NULL auto_increment,
  `aipcriteria` varchar(250) NOT NULL default '',
  PRIMARY KEY  (`aipcriteriaid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`aipcriteria`
--

/*!40000 ALTER TABLE `aipcriteria` DISABLE KEYS */;
INSERT INTO `aipcriteria` (`aipcriteriaid`,`aipcriteria`) VALUES 
 (1,'Performance'),
 (2,'Vacances');
/*!40000 ALTER TABLE `aipcriteria` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`calendar`
--

DROP TABLE IF EXISTS `calendar`;
CREATE TABLE `calendar` (
  `calmonth` int(20) NOT NULL,
  `calyear` int(20) NOT NULL,
  `firstdayofmonth` int(20) NOT NULL,
  `lastdayofmonth` int(20) NOT NULL,
  `daysavailable` varchar(20) NOT NULL,
  PRIMARY KEY  (`calmonth`,`calyear`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`calendar`
--

/*!40000 ALTER TABLE `calendar` DISABLE KEYS */;
INSERT INTO `calendar` (`calmonth`,`calyear`,`firstdayofmonth`,`lastdayofmonth`,`daysavailable`) VALUES 
 (1,2006,1,31,'20'),
 (2,2006,1,28,'20'),
 (3,2006,1,31,'20'),
 (4,2006,1,30,'20'),
 (5,2006,1,31,'20'),
 (6,2006,1,30,'20'),
 (7,2006,1,31,'20'),
 (8,2006,1,31,'20'),
 (9,2006,1,30,'20'),
 (10,2006,1,31,'20'),
 (11,2006,1,30,'20'),
 (12,2006,1,31,'20'),
 (1,2007,1,31,'20'),
 (2,2007,1,28,'20'),
 (3,2007,1,31,'20'),
 (4,2007,1,30,'20'),
 (5,2007,1,31,'20'),
 (6,2007,1,30,'20'),
 (7,2007,1,31,'20'),
 (8,2007,1,31,'20'),
 (9,2007,1,30,'20'),
 (10,2007,1,31,'20'),
 (11,2007,1,30,'20'),
 (12,2007,1,31,'20');
/*!40000 ALTER TABLE `calendar` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`delivlog`
--

DROP TABLE IF EXISTS `delivlog`;
CREATE TABLE `delivlog` (
  `DELIVLOGID` bigint(20) NOT NULL auto_increment,
  `IDPROCLOG` bigint(20) default NULL,
  `DELIVID` int(11) default NULL,
  `MESSAGEDELIVID` bigint(20) default NULL,
  `WKGID` int(11) default NULL,
  `TEMPSSTANDARD` decimal(20,10) default '0.0000000000',
  PRIMARY KEY  (`DELIVLOGID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`delivlog`
--

/*!40000 ALTER TABLE `delivlog` DISABLE KEYS */;
/*!40000 ALTER TABLE `delivlog` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`employeeaile`
--

DROP TABLE IF EXISTS `employeeaile`;
CREATE TABLE `employeeaile` (
  `employeeaileid` int(10) unsigned NOT NULL auto_increment,
  `wkgid` int(10) unsigned NOT NULL default '0',
  `emplid` int(10) unsigned NOT NULL default '0',
  `ailecriteriaid` int(10) unsigned NOT NULL default '0',
  `motif` varchar(150) NOT NULL default '',
  `taux` decimal(10,2) NOT NULL default '0.00',
  `startdate` datetime NOT NULL default '0000-00-00 00:00:00',
  `enddate` datetime NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (`employeeaileid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`employeeaile`
--

/*!40000 ALTER TABLE `employeeaile` DISABLE KEYS */;
/*!40000 ALTER TABLE `employeeaile` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`employeeaip`
--

DROP TABLE IF EXISTS `employeeaip`;
CREATE TABLE `employeeaip` (
  `emplid` int(11) NOT NULL default '0',
  `aipcriteriaid` int(11) NOT NULL default '0',
  `motif` varchar(150) NOT NULL default '',
  `taux` float(10,2) NOT NULL default '0.00',
  `startdate` date NOT NULL default '0000-00-00',
  `enddate` datetime NOT NULL default '0000-00-00 00:00:00',
  `employeeaipid` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`employeeaipid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=FIXED;

--
-- Dumping data for table `pilotage`.`employeeaip`
--

/*!40000 ALTER TABLE `employeeaip` DISABLE KEYS */;
/*!40000 ALTER TABLE `employeeaip` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`employeecalendar`
--

DROP TABLE IF EXISTS `employeecalendar`;
CREATE TABLE `employeecalendar` (
  `emplid` int(20) NOT NULL,
  `calmonth` int(20) NOT NULL,
  `calyear` int(20) NOT NULL,
  `daysplanned` int(20) NOT NULL,
  PRIMARY KEY  (`emplid`,`calmonth`,`calyear`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`employeecalendar`
--

/*!40000 ALTER TABLE `employeecalendar` DISABLE KEYS */;
/*!40000 ALTER TABLE `employeecalendar` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`employeetitle`
--

DROP TABLE IF EXISTS `employeetitle`;
CREATE TABLE `employeetitle` (
  `EmployeeTitleID` int(11) NOT NULL auto_increment,
  `EmployeeTitle` varchar(100) NOT NULL default '',
  PRIMARY KEY  (`EmployeeTitleID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`employeetitle`
--

/*!40000 ALTER TABLE `employeetitle` DISABLE KEYS */;
INSERT INTO `employeetitle` (`EmployeeTitleID`,`EmployeeTitle`) VALUES 
 (1,'Directeur'),
 (2,'Collaborateur');
/*!40000 ALTER TABLE `employeetitle` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`eptteamauto`
--

DROP TABLE IF EXISTS `eptteamauto`;
CREATE TABLE `eptteamauto` (
  `calmonth` int(11) NOT NULL default '0',
  `calyear` int(11) NOT NULL default '0',
  `eptvalue` decimal(10,0) NOT NULL default '0',
  `wkgid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`wkgid`,`calyear`,`calmonth`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`eptteamauto`
--

/*!40000 ALTER TABLE `eptteamauto` DISABLE KEYS */;
/*!40000 ALTER TABLE `eptteamauto` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`eptteammanual`
--

DROP TABLE IF EXISTS `eptteammanual`;
CREATE TABLE `eptteammanual` (
  `wkgid` int(11) NOT NULL default '0',
  `calyear` int(11) NOT NULL default '0',
  `calmonth` int(11) NOT NULL default '0',
  `eptvalue` decimal(10,0) NOT NULL default '0',
  PRIMARY KEY  (`wkgid`,`calyear`,`calmonth`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`eptteammanual`
--

/*!40000 ALTER TABLE `eptteammanual` DISABLE KEYS */;
/*!40000 ALTER TABLE `eptteammanual` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`externdeliv`
--

DROP TABLE IF EXISTS `externdeliv`;
CREATE TABLE `externdeliv` (
  `EXTERNDELIVID` int(11) NOT NULL auto_increment,
  `EXTERNPROCID` int(11) NOT NULL default '0',
  `DELIVSTABLEID` int(11) default NULL,
  `EXTERNDELIVDESC` varchar(100) NOT NULL default '',
  `EXTERNDELIVTRANS` varchar(50) default '',
  PRIMARY KEY  (`EXTERNDELIVID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`externdeliv`
--

/*!40000 ALTER TABLE `externdeliv` DISABLE KEYS */;
/*!40000 ALTER TABLE `externdeliv` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`externprestation`
--

DROP TABLE IF EXISTS `externprestation`;
CREATE TABLE `externprestation` (
  `externprestationID` int(11) NOT NULL auto_increment,
  `externsystemID` int(10) unsigned NOT NULL default '0',
  `prestationID` int(10) unsigned NOT NULL default '0',
  `externprestation` varchar(45) NOT NULL default '',
  PRIMARY KEY  (`externprestationID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `pilotage`.`externprestation`
--

/*!40000 ALTER TABLE `externprestation` DISABLE KEYS */;
INSERT INTO `externprestation` (`externprestationID`,`externsystemID`,`prestationID`,`externprestation`) VALUES 
 (4,1,1012,'0'),
 (6,1,1016,'1'),
 (5,1,1013,'0'),
 (7,1,1017,'2'),
 (8,1,1018,'3');
/*!40000 ALTER TABLE `externprestation` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`externproc`
--

DROP TABLE IF EXISTS `externproc`;
CREATE TABLE `externproc` (
  `EXTERNPROCID` int(11) NOT NULL auto_increment,
  `SYSTEMID` int(11) NOT NULL default '0',
  `PROCSTABLEID` int(11) default NULL,
  `EXTERNPROCDESC` varchar(100) default NULL,
  `MODELREF` varchar(255) default '',
  `EXTERNPROCTRANS` varchar(50) default '',
  PRIMARY KEY  (`EXTERNPROCID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`externproc`
--

/*!40000 ALTER TABLE `externproc` DISABLE KEYS */;
/*!40000 ALTER TABLE `externproc` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`externsystem`
--

DROP TABLE IF EXISTS `externsystem`;
CREATE TABLE `externsystem` (
  `EXTERNSYSTEMID` int(11) NOT NULL,
  `EXTERNSYSTEMDESC` varchar(25) default NULL,
  PRIMARY KEY  (`EXTERNSYSTEMID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`externsystem`
--

/*!40000 ALTER TABLE `externsystem` DISABLE KEYS */;
INSERT INTO `externsystem` (`EXTERNSYSTEMID`,`EXTERNSYSTEMDESC`) VALUES 
 (1,'Systeme 1');
/*!40000 ALTER TABLE `externsystem` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`externuser`
--

DROP TABLE IF EXISTS `externuser`;
CREATE TABLE `externuser` (
  `EXTERNUSERID` int(11) NOT NULL auto_increment,
  `EXTERNSYSTEMID` int(11) default NULL,
  `EMPLID` int(11) default NULL,
  `EXTERNUSER` varchar(25) default NULL,
  PRIMARY KEY  (`EXTERNUSERID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`externuser`
--

/*!40000 ALTER TABLE `externuser` DISABLE KEYS */;
/*!40000 ALTER TABLE `externuser` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`indiccasprocteam`
--

DROP TABLE IF EXISTS `indiccasprocteam`;
CREATE TABLE `indiccasprocteam` (
  `monthid` int(10) unsigned NOT NULL default '0',
  `monthdesc` varchar(20) NOT NULL default '',
  `team` varchar(50) NOT NULL default '',
  `typequantity` varchar(20) NOT NULL default '',
  `quantity` decimal(7,2) NOT NULL default '0.00'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `pilotage`.`indiccasprocteam`
--

/*!40000 ALTER TABLE `indiccasprocteam` DISABLE KEYS */;
INSERT INTO `indiccasprocteam` (`monthid`,`monthdesc`,`team`,`typequantity`,`quantity`) VALUES 
 (1,'Quantité Janvier','Administrés','Référence','3.00'),
 (1,'Quantité Janvier','Administrés','Réalisé','0.00'),
 (2,'Quantité Février','Administrés','Référence','3.00'),
 (2,'Quantité Février','Administrés','Réalisé','0.00'),
 (3,'Quantité Mars','Administrés','Référence','3.00'),
 (3,'Quantité Mars','Administrés','Réalisé','0.00'),
 (4,'Quantité Avril','Administrés','Référence','3.00'),
 (4,'Quantité Avril','Administrés','Réalisé','0.00'),
 (5,'Quantité Mai','Administrés','Référence','3.00'),
 (5,'Quantité Mai','Administrés','Réalisé','0.00'),
 (6,'Quantité Juin','Administrés','Référence','3.00'),
 (6,'Quantité Juin','Administrés','Réalisé','0.00'),
 (7,'Quantité Juillet','Administrés','Référence','3.00'),
 (7,'Quantité Juillet','Administrés','Réalisé','0.00'),
 (8,'Quantité Août','Administrés','Référence','3.00'),
 (8,'Quantité Août','Administrés','Réalisé','0.00'),
 (9,'Quantité Septembre','Administrés','Référence','3.00');
INSERT INTO `indiccasprocteam` (`monthid`,`monthdesc`,`team`,`typequantity`,`quantity`) VALUES 
 (9,'Quantité Septembre','Administrés','Réalisé','0.00'),
 (10,'Quantité Octobre','Administrés','Référence','3.00'),
 (10,'Quantité Octobre','Administrés','Réalisé','0.00'),
 (11,'Quantité Novembre','Administrés','Référence','3.00'),
 (11,'Quantité Novembre','Administrés','Réalisé','0.00'),
 (12,'Quantité Décembre','Administrés','Référence','3.00'),
 (12,'Quantité Décembre','Administrés','Réalisé','0.00');
/*!40000 ALTER TABLE `indiccasprocteam` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`indicchargeteam`
--

DROP TABLE IF EXISTS `indicchargeteam`;
CREATE TABLE `indicchargeteam` (
  `monthid` int(10) unsigned NOT NULL default '0',
  `month` varchar(45) NOT NULL default '',
  `forecast` decimal(10,2) NOT NULL default '0.00',
  `produced` decimal(10,2) NOT NULL default '0.00',
  PRIMARY KEY  (`monthid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `pilotage`.`indicchargeteam`
--

/*!40000 ALTER TABLE `indicchargeteam` DISABLE KEYS */;
INSERT INTO `indicchargeteam` (`monthid`,`month`,`forecast`,`produced`) VALUES 
 (1,'Quantité Janvier','5.25','10.31'),
 (2,'Quantité Février','5.25','7.13'),
 (3,'Quantité Mars','5.25','6.00'),
 (4,'Quantité Avril','5.25','4.88'),
 (5,'Quantité Mai','5.25','3.94'),
 (6,'Quantité Juin','5.25','4.13'),
 (7,'Quantité Juillet','5.25','6.00'),
 (8,'Quantité Août','5.25','4.31'),
 (9,'Quantité Septembre','5.25','4.69'),
 (10,'Quantité Octobre','5.25','3.94'),
 (11,'Quantité Novembre','5.25','0.00'),
 (12,'Quantité Décembre','5.25','0.00');
/*!40000 ALTER TABLE `indicchargeteam` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`indiclabel`
--

DROP TABLE IF EXISTS `indiclabel`;
CREATE TABLE `indiclabel` (
  `labelyear` int(10) unsigned NOT NULL default '0',
  `labeltext` varchar(100) NOT NULL default ''
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `pilotage`.`indiclabel`
--

/*!40000 ALTER TABLE `indiclabel` DISABLE KEYS */;
INSERT INTO `indiclabel` (`labelyear`,`labeltext`) VALUES 
 (2006,'Demande état civil');
/*!40000 ALTER TABLE `indiclabel` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`indicnbrcastraite`
--

DROP TABLE IF EXISTS `indicnbrcastraite`;
CREATE TABLE `indicnbrcastraite` (
  `monthid` int(10) unsigned NOT NULL default '0',
  `monthdesc` varchar(20) NOT NULL default '',
  `prestation` varchar(45) NOT NULL default '',
  `typequantity` varchar(45) NOT NULL default '',
  `quantity` decimal(7,2) NOT NULL default '0.00'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `pilotage`.`indicnbrcastraite`
--

/*!40000 ALTER TABLE `indicnbrcastraite` DISABLE KEYS */;
INSERT INTO `indicnbrcastraite` (`monthid`,`monthdesc`,`prestation`,`typequantity`,`quantity`) VALUES 
 (1,'Quantité Janvier','Acte de naissance','Référence','3.20'),
 (1,'Quantité Janvier','Acte de naissance','Réalisé','36.00'),
 (2,'Quantité Février','Acte de naissance','Référence','3.20'),
 (2,'Quantité Février','Acte de naissance','Réalisé','0.00'),
 (3,'Quantité Mars','Acte de naissance','Référence','3.20'),
 (3,'Quantité Mars','Acte de naissance','Réalisé','0.00'),
 (4,'Quantité Avril','Acte de naissance','Référence','3.20'),
 (4,'Quantité Avril','Acte de naissance','Réalisé','0.00'),
 (5,'Quantité Mai','Acte de naissance','Référence','3.20'),
 (5,'Quantité Mai','Acte de naissance','Réalisé','0.00'),
 (6,'Quantité Juin','Acte de naissance','Référence','3.20'),
 (6,'Quantité Juin','Acte de naissance','Réalisé','0.00'),
 (7,'Quantité Juillet','Acte de naissance','Référence','3.20'),
 (7,'Quantité Juillet','Acte de naissance','Réalisé','0.00'),
 (8,'Quantité Août','Acte de naissance','Référence','3.20');
INSERT INTO `indicnbrcastraite` (`monthid`,`monthdesc`,`prestation`,`typequantity`,`quantity`) VALUES 
 (8,'Quantité Août','Acte de naissance','Réalisé','0.00'),
 (9,'Quantité Septembre','Acte de naissance','Référence','3.20'),
 (9,'Quantité Septembre','Acte de naissance','Réalisé','0.00'),
 (10,'Quantité Octobre','Acte de naissance','Référence','3.20'),
 (10,'Quantité Octobre','Acte de naissance','Réalisé','0.00'),
 (11,'Quantité Novembre','Acte de naissance','Référence','3.20'),
 (11,'Quantité Novembre','Acte de naissance','Réalisé','0.00'),
 (12,'Quantité Décembre','Acte de naissance','Référence','3.20'),
 (12,'Quantité Décembre','Acte de naissance','Réalisé','0.00'),
 (1,'Quantité Janvier','Acte de marriage','Référence','1.60'),
 (1,'Quantité Janvier','Acte de marriage','Réalisé','0.00'),
 (2,'Quantité Février','Acte de marriage','Référence','1.60'),
 (2,'Quantité Février','Acte de marriage','Réalisé','0.00'),
 (3,'Quantité Mars','Acte de marriage','Référence','1.60'),
 (3,'Quantité Mars','Acte de marriage','Réalisé','0.00');
INSERT INTO `indicnbrcastraite` (`monthid`,`monthdesc`,`prestation`,`typequantity`,`quantity`) VALUES 
 (4,'Quantité Avril','Acte de marriage','Référence','1.60'),
 (4,'Quantité Avril','Acte de marriage','Réalisé','0.00'),
 (5,'Quantité Mai','Acte de marriage','Référence','1.60'),
 (5,'Quantité Mai','Acte de marriage','Réalisé','0.00'),
 (6,'Quantité Juin','Acte de marriage','Référence','1.60'),
 (6,'Quantité Juin','Acte de marriage','Réalisé','0.00'),
 (7,'Quantité Juillet','Acte de marriage','Référence','1.60'),
 (7,'Quantité Juillet','Acte de marriage','Réalisé','0.00'),
 (8,'Quantité Août','Acte de marriage','Référence','1.60'),
 (8,'Quantité Août','Acte de marriage','Réalisé','0.00'),
 (9,'Quantité Septembre','Acte de marriage','Référence','1.60'),
 (9,'Quantité Septembre','Acte de marriage','Réalisé','0.00'),
 (10,'Quantité Octobre','Acte de marriage','Référence','1.60'),
 (10,'Quantité Octobre','Acte de marriage','Réalisé','0.00'),
 (11,'Quantité Novembre','Acte de marriage','Référence','1.60'),
 (11,'Quantité Novembre','Acte de marriage','Réalisé','0.00');
INSERT INTO `indicnbrcastraite` (`monthid`,`monthdesc`,`prestation`,`typequantity`,`quantity`) VALUES 
 (12,'Quantité Décembre','Acte de marriage','Référence','1.60'),
 (12,'Quantité Décembre','Acte de marriage','Réalisé','0.00'),
 (1,'Quantité Janvier','Acte de décès','Référence','3.20'),
 (1,'Quantité Janvier','Acte de décès','Réalisé','0.00'),
 (2,'Quantité Février','Acte de décès','Référence','3.20'),
 (2,'Quantité Février','Acte de décès','Réalisé','0.00'),
 (3,'Quantité Mars','Acte de décès','Référence','3.20'),
 (3,'Quantité Mars','Acte de décès','Réalisé','0.00'),
 (4,'Quantité Avril','Acte de décès','Référence','3.20'),
 (4,'Quantité Avril','Acte de décès','Réalisé','0.00'),
 (5,'Quantité Mai','Acte de décès','Référence','3.20'),
 (5,'Quantité Mai','Acte de décès','Réalisé','0.00'),
 (6,'Quantité Juin','Acte de décès','Référence','3.20'),
 (6,'Quantité Juin','Acte de décès','Réalisé','0.00'),
 (7,'Quantité Juillet','Acte de décès','Référence','3.20'),
 (7,'Quantité Juillet','Acte de décès','Réalisé','0.00');
INSERT INTO `indicnbrcastraite` (`monthid`,`monthdesc`,`prestation`,`typequantity`,`quantity`) VALUES 
 (8,'Quantité Août','Acte de décès','Référence','3.20'),
 (8,'Quantité Août','Acte de décès','Réalisé','0.00'),
 (9,'Quantité Septembre','Acte de décès','Référence','3.20'),
 (9,'Quantité Septembre','Acte de décès','Réalisé','0.00'),
 (10,'Quantité Octobre','Acte de décès','Référence','3.20'),
 (10,'Quantité Octobre','Acte de décès','Réalisé','0.00'),
 (11,'Quantité Novembre','Acte de décès','Référence','3.20'),
 (11,'Quantité Novembre','Acte de décès','Réalisé','0.00'),
 (12,'Quantité Décembre','Acte de décès','Référence','3.20'),
 (12,'Quantité Décembre','Acte de décès','Réalisé','0.00');
/*!40000 ALTER TABLE `indicnbrcastraite` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`indicproducteam`
--

DROP TABLE IF EXISTS `indicproducteam`;
CREATE TABLE `indicproducteam` (
  `monthid` int(10) unsigned NOT NULL auto_increment,
  `month` varchar(45) NOT NULL default '',
  `forecast` decimal(10,2) NOT NULL default '0.00',
  `produced` decimal(10,2) NOT NULL default '0.00',
  PRIMARY KEY  (`monthid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `pilotage`.`indicproducteam`
--

/*!40000 ALTER TABLE `indicproducteam` DISABLE KEYS */;
INSERT INTO `indicproducteam` (`monthid`,`month`,`forecast`,`produced`) VALUES 
 (1,'Quantité Janvier','20.00','9.00'),
 (2,'Quantité Février','18.00','0.00'),
 (3,'Quantité Mars','20.00','0.00'),
 (4,'Quantité Avril','20.00','0.00'),
 (5,'Quantité Mai','20.00','0.00'),
 (6,'Quantité Juin','20.00','0.00'),
 (7,'Quantité Juillet','20.00','0.00'),
 (8,'Quantité Août','20.00','0.00'),
 (9,'Quantité Septembre','20.00','0.00'),
 (10,'Quantité Octobre','20.00','0.00'),
 (11,'Quantité Novembre','20.00','0.00'),
 (12,'Quantité Décembre','20.00','0.00');
/*!40000 ALTER TABLE `indicproducteam` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`indicstock`
--

DROP TABLE IF EXISTS `indicstock`;
CREATE TABLE `indicstock` (
  `monthid` int(10) unsigned NOT NULL default '0',
  `month` varchar(20) NOT NULL default '',
  `forecast` int(10) unsigned NOT NULL default '0',
  `produced` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`monthid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `pilotage`.`indicstock`
--

/*!40000 ALTER TABLE `indicstock` DISABLE KEYS */;
INSERT INTO `indicstock` (`monthid`,`month`,`forecast`,`produced`) VALUES 
 (1,'Quantité Janvier',8,36),
 (2,'Quantité Février',8,0),
 (3,'Quantité Mars',8,0),
 (4,'Quantité Avril',8,0),
 (5,'Quantité Mai',8,0),
 (6,'Quantité Juin',8,0),
 (7,'Quantité Juillet',8,0),
 (8,'Quantité Août',8,0),
 (9,'Quantité Septembre',8,0),
 (10,'Quantité Octobre',8,0),
 (11,'Quantité Novembre',8,0),
 (12,'Quantité Décembre',8,0);
/*!40000 ALTER TABLE `indicstock` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`message`
--

DROP TABLE IF EXISTS `message`;
CREATE TABLE `message` (
  `IDMESSAGEINTERNE` bigint(20) NOT NULL auto_increment,
  `MESSAGEERRORID` int(11) default NULL,
  `EXTERNMESSAGEID` varchar(50) NOT NULL default '',
  `EXTERNSYSTEMID` int(11) NOT NULL default '0',
  `EXTERNPROCTRANS` varchar(50) NOT NULL default '',
  `EXTERNUSERID` varchar(100) NOT NULL default '',
  `TIMESTAMPPROC` datetime NOT NULL default '2006-06-01 00:00:00',
  `MESSAGETIME` datetime NOT NULL default '2006-06-01 00:00:00',
  `STATUT` int(11) default NULL,
  `CASEID` int(11) default NULL,
  `CASEIDREMARK` varchar(255) default NULL,
  `PRESTATIONID` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`IDMESSAGEINTERNE`),
  KEY `EXTERNMESSAGEID` (`EXTERNMESSAGEID`,`EXTERNSYSTEMID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`message`
--

/*!40000 ALTER TABLE `message` DISABLE KEYS */;
/*!40000 ALTER TABLE `message` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`messagedeliv`
--

DROP TABLE IF EXISTS `messagedeliv`;
CREATE TABLE `messagedeliv` (
  `MESSAGEDELIVID` bigint(20) NOT NULL auto_increment,
  `IDMESSAGEINTERNE` int(10) unsigned default NULL,
  `MESSAGEERRORID` int(11) default NULL,
  `EXTERNDELIVTRANS` varchar(50) default '',
  `EXTERNUSERID` varchar(100) default NULL,
  `TIMESTAMPDELIV` datetime default NULL,
  `DOUBLECONTROL` int(11) default NULL,
  PRIMARY KEY  (`MESSAGEDELIVID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`messagedeliv`
--

/*!40000 ALTER TABLE `messagedeliv` DISABLE KEYS */;
/*!40000 ALTER TABLE `messagedeliv` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`messagedelivlog`
--

DROP TABLE IF EXISTS `messagedelivlog`;
CREATE TABLE `messagedelivlog` (
  `MESSAGEDELIVID` bigint(20) NOT NULL,
  `IDMESSAGEINTERNE` bigint(20) default NULL,
  `EXTERNDELIVTRANS` varchar(50) default NULL,
  `EXTERNUSERID` varchar(100) default NULL,
  `TIMESTAMPDELIV` datetime default NULL,
  `DOUBLECONTROL` int(11) default NULL,
  PRIMARY KEY  (`MESSAGEDELIVID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`messagedelivlog`
--

/*!40000 ALTER TABLE `messagedelivlog` DISABLE KEYS */;
/*!40000 ALTER TABLE `messagedelivlog` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`messageerror`
--

DROP TABLE IF EXISTS `messageerror`;
CREATE TABLE `messageerror` (
  `MESSAGEERRORID` int(11) NOT NULL,
  `ERRORDESCRIPTION` varchar(255) default NULL,
  PRIMARY KEY  (`MESSAGEERRORID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`messageerror`
--

/*!40000 ALTER TABLE `messageerror` DISABLE KEYS */;
/*!40000 ALTER TABLE `messageerror` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`messagelog`
--

DROP TABLE IF EXISTS `messagelog`;
CREATE TABLE `messagelog` (
  `IDMESSAGEINTERNE` bigint(20) NOT NULL,
  `EXTERNMESSAGEID` varchar(50) NOT NULL default '',
  `EXTERNSYSTEMID` int(11) NOT NULL,
  `EXTERNPROCTRANS` varchar(50) NOT NULL default '',
  `EXTERNUSERID` varchar(100) NOT NULL,
  `TIMESTAMPPROC` datetime NOT NULL,
  `MESSAGETIME` datetime NOT NULL,
  `STATUT` int(11) default NULL,
  `CASEID` int(11) default NULL,
  `CASEIDREMARK` varchar(255) default NULL,
  `PRESTATIONID` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`IDMESSAGEINTERNE`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`messagelog`
--

/*!40000 ALTER TABLE `messagelog` DISABLE KEYS */;
/*!40000 ALTER TABLE `messagelog` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pattach`
--

DROP TABLE IF EXISTS `pattach`;
CREATE TABLE `pattach` (
  `caseid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `filename` varchar(255) NOT NULL default '',
  `filedate` datetime default NULL,
  `mlogin` varchar(32) default NULL,
  PRIMARY KEY  (`caseid`,`transid`,`filename`),
  KEY `pattach_idx01` (`caseid`,`transid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pattach`
--

/*!40000 ALTER TABLE `pattach` DISABLE KEYS */;
/*!40000 ALTER TABLE `pattach` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pattribdef`
--

DROP TABLE IF EXISTS `pattribdef`;
CREATE TABLE `pattribdef` (
  `attribdefid` int(11) NOT NULL default '0',
  `attribgrpid` int(11) NOT NULL default '0',
  `attribdefname` varchar(255) default NULL,
  `attribdeftype` int(11) NOT NULL default '0',
  `attribreq` tinyint(1) NOT NULL default '0',
  PRIMARY KEY  (`attribdefid`),
  KEY `pattribdef_idx1` (`attribreq`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pattribdef`
--

/*!40000 ALTER TABLE `pattribdef` DISABLE KEYS */;
/*!40000 ALTER TABLE `pattribdef` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pattribgrp`
--

DROP TABLE IF EXISTS `pattribgrp`;
CREATE TABLE `pattribgrp` (
  `attribgrpid` int(11) NOT NULL default '0',
  `attribgrpname` varchar(255) default NULL,
  PRIMARY KEY  (`attribgrpid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pattribgrp`
--

/*!40000 ALTER TABLE `pattribgrp` DISABLE KEYS */;
/*!40000 ALTER TABLE `pattribgrp` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pattribtype`
--

DROP TABLE IF EXISTS `pattribtype`;
CREATE TABLE `pattribtype` (
  `attribtypeid` int(11) NOT NULL default '0',
  `attribtypename` varchar(255) default NULL,
  `cfrmt` varchar(255) default NULL,
  PRIMARY KEY  (`attribtypeid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pattribtype`
--

/*!40000 ALTER TABLE `pattribtype` DISABLE KEYS */;
/*!40000 ALTER TABLE `pattribtype` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pcase`
--

DROP TABLE IF EXISTS `pcase`;
CREATE TABLE `pcase` (
  `caseid` int(11) NOT NULL default '0',
  `txindate` datetime NOT NULL default '0000-00-00 00:00:00',
  `casename` varchar(255) default NULL,
  PRIMARY KEY  (`caseid`),
  KEY `pcase_idx1` (`casename`),
  KEY `pcase_idx2` (`txindate`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pcase`
--

/*!40000 ALTER TABLE `pcase` DISABLE KEYS */;
/*!40000 ALTER TABLE `pcase` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pclsidmapper`
--

DROP TABLE IF EXISTS `pclsidmapper`;
CREATE TABLE `pclsidmapper` (
  `mid` int(11) NOT NULL default '0',
  `clsid` varchar(128) NOT NULL default '',
  PRIMARY KEY  (`mid`),
  KEY `pclsidmapper_idx1` (`clsid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pclsidmapper`
--

/*!40000 ALTER TABLE `pclsidmapper` DISABLE KEYS */;
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (2,'XzpbdjBdLTE2MTQyMDU2ODAtNDY3NTk=\n'),
 (3,'XzpbdjBdLTIxMTA4MTQxMzItNTA4NDk=\n'),
 (4,'XzpbdjBdMTAzNTE0MDQ1NC0yMDY1MQ==\n'),
 (5,'XzpbdjBdMTA2OTI4MDI0OS04NTIx'),
 (6,'XzpbdjBdMTY0MDk0NDcyNS00MTkzOQ==\n'),
 (7,'XzpbdjBdMjEzMzQwMjM0MC00MDg1NQ==\n'),
 (8,'XzpbdjBdNTA1MzMzMTg1LTIwODcy'),
 (9,'XzpbdjBdLTEwNzE5NzE4NTQtMjM0MQ==\n'),
 (10,'XzpbdjBdLTgwMjQ4Ny00NDU3'),
 (11,'XzpbdjBdLTg0NTc4MTM3NC01MTY1Nw==\n'),
 (12,'XzpbdjBdMTIzOTE3MTI5NS01MDQzNw==\n'),
 (13,'XzpbdjBdLTE2MDIwOTQ5NzItMTgwNjU=\n'),
 (14,'XzpbdjBdNjIxOTk2MzMwLTUxMzQ4'),
 (15,'XzpbdjBdLTM5MTY4MjM2LTMzNjc4'),
 (16,'XzpbdjBdMTAyNzk0NDU2My01NjkxNw==\n'),
 (17,'XzpbdjBdMTE4MDI1MjU1Ni01OTQ0Mw==\n'),
 (18,'XzpbdjBdLTIzNDQxNTM1Ni01ODUyMQ==\n'),
 (19,'XzpbdjBdLTM1MDg4OTg1Mi0xMDcwMA==\n'),
 (20,'XzpbdjBdLTE2Mjg3MDc2ODMtMTk1NzI=\n'),
 (21,'XzpbdjBdNzUyMDgzNjAwLTMyMzIy'),
 (22,'XzpbdjBdLTE2NTIwNTE3MDktNTI1Nzg=\n'),
 (23,'XzpbdjBdLTQ0MTE4ODY5Ny01MjMzNQ==\n'),
 (24,'XzpbdjBdLTkzNTY5OTExNS0zNDQ2NQ==\n'),
 (25,'XzpbdjBdLTc0MTE4Njc0MS00MDk2');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (26,'XzpbdjBdMTg5NzkzMTUyMC01MjQ1OQ==\n'),
 (27,'XzpbdjBdMTUwNzM2NzE1OS0xMTQyMw==\n'),
 (28,'XzpbdjBdNjMxMTAwODc0LTU3MTEw'),
 (29,'XzpbdjBdMTQwOTM4NTQ0Ni01MzI0OA==\n'),
 (30,'XzpbdjBdLTM1MDc5Nzc3LTEyMTY5'),
 (31,'XzpbdjBdMTMyMjcyNTY2Ny0xMDk2Mg==\n'),
 (32,'XzpbdjBdOTg4MDUwMTAxLTU5NDIz'),
 (33,'XzpbdjBdLTgyNjg0MTkwMC0xMjI4Mg==\n'),
 (34,'XzpbdjBdMjA1NjkyMDcyOS0xMjQyNg==\n'),
 (35,'XzpbdjBdLTEzMzExMDQ4NTYtMzM1MTg=\n'),
 (36,'XzpbdjBdMTMwMjY4ODQwNS0xODY4Mw==\n'),
 (37,'XzpbdjBdLTEyMTYwMDUxMTMtNTI0MjA=\n'),
 (38,'XzpbdjBdMzc1NTkwNDkwLTM1NjEw'),
 (39,'XzpbdjBdLTE5NzQwODcwNjEtMzExMjg=\n'),
 (40,'XzpbdjBdMTA5NjExMjcxMi01ODQxNQ==\n'),
 (41,'XzpbdjBdMzIyNzcwMzE5LTQ2NDkz'),
 (42,'XzpbdjBdLTE4NzI0MDQ5OTAtNTc0NDM=\n'),
 (43,'XzpbdjBdNjU0ODU3NjEtMzUzODU=\n'),
 (44,'XzpbdjBdNzgyMzAzMjU0LTYzMDUx'),
 (45,'XzpbdjBdMjA4ODkwNjQzNS01NDQ3OA==\n'),
 (46,'XzpbdjBdMTQzNzMwMTIxMi0xMjQzMQ==\n'),
 (47,'XzpbdjBdMTAwNTE2OTkwNC0yNjMwNw==\n'),
 (48,'XzpbdjBdLTEwMDE1NTEzNzItNTAwMTU=\n'),
 (49,'XzpbdjBdLTEzNzY5OTQxNjgtMzQyMTA=\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (50,'XzpbdjBdMTgzMDczNzI5Mi0xMzU0Nw==\n'),
 (51,'XzpbdjBdOTIyNTE4MDAyLTYxODQ5'),
 (52,'XzpbdjBdMTA3MDE0NzE5Ni0zNzkyNg==\n'),
 (53,'XzpbdjBdLTEyMTQwOTIwNzUtMTAzMjg=\n'),
 (54,'XzpbdjBdLTE2NjA1MTU0NjMtNDYwOTI=\n'),
 (55,'XzpbdjBdNjQzOTk4NTUzLTEyMzY=\n'),
 (56,'XzpbdjBdMzAzMjEyNzA2LTY0MTE2'),
 (57,'XzpbdjBdLTE3OTI4Nzk4NTEtNjAyMjg=\n'),
 (58,'XzpbdjBdLTIwMjU1NDc1MDEtNDE1NzA=\n'),
 (59,'XzpbdjBdLTE0MDY0NDQyNDAtMjIx'),
 (60,'XzpbdjBdMTQwNDUyODg5My0yNjg5OA==\n'),
 (61,'XzpbdjBdOTIxODA0NzI3LTM0MjA=\n'),
 (62,'XzpbdjBdMTk1NjA0ODkxNC02NDY5Nw==\n'),
 (63,'XzpbdjBdMzY2MDUzNTE0LTU0OTUz'),
 (64,'XzpbdjBdNTY5MDkzOTMzLTIyMjQy'),
 (65,'XzpbdjBdLTEzODczNTg1MTAtMzQ5MjM=\n'),
 (66,'XzpbdjBdLTcyOTkzMDcyNy00OTU1OQ==\n'),
 (67,'XzpbdjBdODg2NTYyMTYtNTg5NjA=\n'),
 (68,'XzpbdjBdNDg0NTQ4NjQwLTcwMTY=\n'),
 (69,'XzpbdjBdLTE2Njg0NjI3OC02MTU2MA==\n'),
 (70,'XzpbdjBdMTQzMzAxMTY3OC0yMTMwOA==\n'),
 (71,'XzpbdjBdMTA4NjMzNzIxNS02MDAzMQ==\n'),
 (72,'XzpbdjBdOTY2MTY3OTQtNTM1OTk=\n'),
 (73,'XzpbdjBdNzEyMTQwNjYxLTUwMjI5');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (74,'XzpbdjBdMTQ0MDA1Mzk2NC0xNTkyNA==\n'),
 (75,'XzpbdjBdNTI4MDM4MDM1LTQ0MjEx'),
 (76,'XzpbdjBdMTY1OTIzODI3NS0xNjAyOQ==\n'),
 (77,'XzpbdjBdLTk0MzY0ODEwMi01NzMyNw==\n'),
 (78,'XzpbdjBdLTYxMjE1NzUwNy00Mjg1Mg==\n'),
 (79,'XzpbdjBdNjc5NzMwNjU5LTMyMzIy'),
 (80,'XzpbdjBdLTUzNjk0NDQwNC0yOTY3Nw==\n'),
 (81,'XzpbdjBdMTk0MDQ4NjI5LTMyODg1'),
 (82,'XzpbdjBdLTc5NzM0OTUwLTMyNDI5'),
 (83,'XzpbdjBdLTExNzQ2OTkwNzctNDk3OTQ=\n'),
 (84,'XzpbdjBdMTcxNDE0NjcxOC02OTk=\n'),
 (85,'XzpbdjBdMTM2MjA1NjY5OS0yMzcxNg==\n'),
 (86,'XzpbdjBdMTg2NDk4NzUzOS01OTgyMA==\n'),
 (87,'XzpbdjBdMTg0NzQ0ODYwNi02MTE5Ng==\n'),
 (88,'XzpbdjBdMTE4Nzc5ODE4LTU1OTk0'),
 (89,'XzpbdjBdLTQ2MDA0MTYwNi0zNzUzMw==\n'),
 (90,'XzpbdjBdLTIxNDcxNzkzNjgtMTMzNA==\n'),
 (91,'XzpbdjBdMTE2OTg4NTQzMC0zMzk2'),
 (92,'XzpbdjBdMzgxNTk0NzgyLTgzNjU=\n'),
 (93,'XzpbdjBdLTE4NzA3Njc4ODAtMzgxODI=\n'),
 (94,'XzpbdjBdLTE4NzAyMDM5NjUtNDg2Njk=\n'),
 (95,'XzpbdjBdLTE0NzUyNjEwMTktMTQ4OTc=\n'),
 (96,'XzpbdjBdLTQ1OTMzODE4OC01NjgyNw==\n'),
 (97,'XzpbdjBdLTE4ODkyNTY2MTgtODkyOA==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (98,'XzpbdjBdLTE5MzE2MzgwOTMtNDI5Njk=\n'),
 (99,'XzpbdjBdMTE1MjcxNDQxNy0yMDQyOQ==\n'),
 (100,'XzpbdjBdMTE3Njc4ODM2NS0xNjQ1Ng==\n'),
 (101,'XzpbdjBdLTMxNzg4NDE0LTE0OTM1'),
 (102,'XzpbdjBdMjA5NjczNTEwOS0zODUzMg==\n'),
 (103,'XzpbdjBdMTM0MzMwMDI3Mi0yNzExNg==\n'),
 (104,'XzpbdjBdLTEzNjc0NDAwNjQtMzMwMDc=\n'),
 (105,'XzpbdjBdLTM2Mjg3NDUxLTM4MTE5'),
 (106,'XzpbdjBdODc3NTc2MDEtMjg0NzU=\n'),
 (107,'XzpbdjBdLTY1NTU1NzMyMi00ODk3'),
 (108,'XzpbdjBdMTI0ODg3ODI5LTU0MDAz'),
 (109,'XzpbdjBdNTUwNTI0NjItNDAyMjg=\n'),
 (110,'XzpbdjBdLTk4NzA2MzY1NS0xMjMxMQ==\n'),
 (111,'XzpbdjBdLTkxNzU0Nzc0NC00MDM1NA==\n'),
 (112,'XzpbdjBdLTk2MzQzNTQwNi0zNTgyNw==\n'),
 (113,'XzpbdjBdNDI5OTk0NzkxLTMyNTY2'),
 (114,'XzpbdjBdLTE4NTMzMTE0ODgtNTM0MDU=\n'),
 (115,'XzpbdjBdNjM4MjAxNDY3LTM1ODE4'),
 (116,'XzpbdjBdMTg5MTg1MTExOC0yNjA4MQ==\n'),
 (117,'XzpbdjBdMTY0ODExNDI5Ni01NTU5OQ==\n'),
 (118,'XzpbdjBdOTkyNTMwNTQ2LTUxMjg0'),
 (119,'XzpbdjBdLTc5NzM0NjMzOC0yMjU0Mg==\n'),
 (120,'XzpbdjBdLTg2NjE5NTA0NS0yNjA0Nw==\n'),
 (121,'XzpbdjBdMjAwMzQ0NjUyNS02NTI5Mg==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (122,'XzpbdjBdMTU5NTQxNTQ3NS0xODc1Mg==\n'),
 (123,'XzpbdjBdMzkyMDM1MzA2LTEzMjE5'),
 (124,'XzpbdjBdODY3NzExMTIwLTU2Njc2'),
 (125,'XzpbdjBdMTcxNzI1NTAtMjg2ODE=\n'),
 (126,'XzpbdjBdODY2MDI0OTIwLTYyNTU=\n'),
 (127,'XzpbdjBdMTcyMTk1MTk5OS02Nzk2'),
 (128,'XzpbdjBdMzczNjk0Mjg5LTUyOTI2'),
 (129,'XzpbdjBdMzczNjk0MjkzLTUyOTI2'),
 (130,'XzpbdjBdMzczNjk0Mjk2LTUyOTI2'),
 (131,'XzpbdjBdMzczNjk0Mjk3LTUyOTI2'),
 (132,'XzpbdjBdMjg0NDcwMDM1LTMyMjIx'),
 (133,'XzpbdjBdLTgzMjY2MDc4My02Mjc0Ng==\n'),
 (134,'XzpbdjBdMjEyOTExNzMwNS0zMTg0OA==\n'),
 (135,'XzpbdjBdMzczNjk0Mjk4LTUyOTI2'),
 (136,'XzpbdjBdNDU2MTc3MzA2LTUyOTUz'),
 (137,'XzpbdjBdNDYzMjY5MzYyLTQ5ODc4'),
 (138,'XzpbdjBdLTIwODQ0MDcxNTMtMjg4MTc=\n'),
 (139,'XzpbdjBdMzczNjk0Mjk0LTUyOTI2'),
 (140,'XzpbdjBdMTcwMDA3MjYzNi0zNjc5Mg==\n'),
 (141,'XzpbdjBdLTE3MTc5MjYxMDgtNDgxMzE=\n'),
 (142,'XzpbdjBdLTE2NTIzMjk4NjEtNTc5NDU=\n'),
 (143,'XzpbdjBdLTIxMzI2NjMyMzMtMzY1MA==\n'),
 (144,'XzpbdjBdMTgyMTM2NDA5MS0yMjc4Mw==\n'),
 (145,'XzpbdjBdLTI0NjAzNTcyOS05NDU3');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (146,'XzpbdjBdLTIzMzI4MDg1My0yNDg0Mw==\n'),
 (147,'XzpbdjBdMTk5MzE0ODQyMS01NjU1Mw==\n'),
 (148,'XzpbdjBdLTk4MTIwNzU4Mi0yMzM2Mg==\n'),
 (149,'XzpbdjBdLTE4MzMyMTMxNDItNTc4NTI=\n'),
 (150,'XzpbdjBdLTEyNDY1NDA1NjYtNTY2OTk=\n'),
 (151,'XzpbdjBdLTE5MzY4NzI0NTctMTA3NDA=\n'),
 (152,'XzpbdjBdOTQ0MDY3NTEyLTI4Mjcy'),
 (153,'XzpbdjBdLTQzOTY2NTY1NS02MjczOA==\n'),
 (154,'XzpbdjBdLTIwMDEzMDc1NTgtNjE1Mw==\n'),
 (155,'XzpbdjBdMTg5OTUwMzU4MC0yMjc2'),
 (156,'XzpbdjBdMjQzMjE2NTQ2LTMwNjgx'),
 (157,'XzpbdjBdLTk2OTI1MTA1Ny0zNzMxMQ==\n'),
 (158,'XzpbdjBdMTEwMDE0ODcxNC0zMDYyNQ==\n'),
 (159,'XzpbdjBdMTkyNTkwOTc2Mi01NjI1NA==\n'),
 (160,'XzpbdjBdMjEyNzI2Njg2My03NDE2'),
 (161,'XzpbdjBdLTM5Njg3MTg1My0yMTQwOA==\n'),
 (162,'XzpbdjBdLTIyNzgzNzY2MS01MjQ5OQ==\n'),
 (163,'XzpbdjBdLTIyNzgzNzY1OS01MjQ5OQ==\n'),
 (164,'XzpbdjBdLTIyNzgzNzY1Ny01MjQ5OQ==\n'),
 (165,'XzpbdjBdLTIyNzgzNzY1NS01MjQ5OQ==\n'),
 (166,'XzpbdjBdLTIwMzY0NTExMjEtNDQ1Mzc=\n'),
 (167,'XzpbdjBdLTIwODE5ODc2NjUtNTU4NTM=\n'),
 (168,'XzpbdjBdMjAwMTU5MTM5OS0zMzM5Nw==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (169,'XzpbdjBdLTE1NjU4OTI2MDYtNjIyNDk=\n'),
 (170,'XzpbdjBdLTIyNzgzNzY1My01MjQ5OQ==\n'),
 (171,'XzpbdjBdMTQzOTY1NTQ3Mi0yOTA5'),
 (172,'XzpbdjBdLTIyNzgzNzY1MS01MjQ5OQ==\n'),
 (173,'XzpbdjBdLTIyNzgzNzY0OS01MjQ5OQ==\n'),
 (174,'XzpbdjBdLTIyNzgzNzY0Ny01MjQ5OQ==\n'),
 (175,'XzpbdjBdLTIyNzgzNzY0NS01MjQ5OQ==\n'),
 (176,'XzpbdjBdLTIyNzgzNzY0My01MjQ5OQ==\n'),
 (177,'XzpbdjBdLTIyNzgzNzY0MS01MjQ5OQ==\n'),
 (178,'XzpbdjBdLTIyNzgzNzYzOS01MjQ5OQ==\n'),
 (179,'XzpbdjBdLTIyNzgzNzYzNy01MjQ5OQ==\n'),
 (180,'XzpbdjBdLTIyNzgzNzYzNS01MjQ5OQ==\n'),
 (181,'XzpbdjBdLTIyNzgzNzYzMy01MjQ5OQ==\n'),
 (182,'XzpbdjBdLTIyNzgzNzYzMS01MjQ5OQ==\n'),
 (183,'XzpbdjBdLTIyNzgzNzYyOS01MjQ5OQ==\n'),
 (184,'XzpbdjBdLTIyNzgzNzYyNy01MjQ5OQ==\n'),
 (185,'XzpbdjBdLTkwMDQyNTU2OC01Njk4Mg==\n'),
 (186,'XzpbdjBdLTIyNzgzNzYyNS01MjQ5OQ==\n'),
 (187,'XzpbdjBdLTIyNzgzNzYyMy01MjQ5OQ==\n'),
 (188,'XzpbdjBdLTIyNzgzNzYyMS01MjQ5OQ==\n'),
 (189,'XzpbdjBdLTIyNzgzNzYxOS01MjQ5OQ==\n'),
 (190,'XzpbdjBdLTIyNzgzNzYxNy01MjQ5OQ==\n'),
 (191,'XzpbdjBdLTEzMDcyNzU4NzUtNTY5NTY=\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (192,'XzpbdjBdLTIyNzgzNzYxNS01MjQ5OQ==\n'),
 (193,'XzpbdjBdLTIyNzgzNzYxMy01MjQ5OQ==\n'),
 (194,'XzpbdjBdLTIyNzgzNzYwNy01MjQ5OQ==\n'),
 (195,'XzpbdjBdLTIyNzgzNzYwMy01MjQ5OQ==\n'),
 (196,'XzpbdjBdLTEzMDcyNzU4NzQtNTY5NTY=\n'),
 (197,'XzpbdjBdLTIyNzgzNzYwMS01MjQ5OQ==\n'),
 (198,'XzpbdjBdLTIyNzgzNzU5OS01MjQ5OQ==\n'),
 (199,'XzpbdjBdLTIyNzgzNzU5Ny01MjQ5OQ==\n'),
 (200,'XzpbdjBdLTIyNzgzNzU5NS01MjQ5OQ==\n'),
 (201,'XzpbdjBdLTIyNzgzNzU5MS01MjQ5OQ==\n'),
 (202,'XzpbdjBdLTIyNzgzNzU4OS01MjQ5OQ==\n'),
 (203,'XzpbdjBdLTIyNzgzNzU4Ny01MjQ5OQ==\n'),
 (204,'XzpbdjBdLTIyNzgzNzU4NS01MjQ5OQ==\n'),
 (205,'XzpbdjBdLTIyNzgzNzU4My01MjQ5OQ==\n'),
 (206,'XzpbdjBdLTIyNzgzNzU3Ny01MjQ5OQ==\n'),
 (207,'XzpbdjBdLTIyNzgzNzU3NS01MjQ5OQ==\n'),
 (208,'XzpbdjBdNDU2MTc3MzA4LTUyOTUz'),
 (209,'XzpbdjBdNzg2OTgyNDUxLTUzODUw'),
 (210,'XzpbdjBdLTExOTQ0OTI0OTgtNDIyMg==\n'),
 (211,'XzpbdjBdNzU4MzEyNTI2LTMzMjM0'),
 (212,'XzpbdjBdLTM3NjA5NjI1OS0yMjAyNQ==\n'),
 (213,'XzpbdjBdNzA4MDAzNTQwLTQ3MTU0'),
 (214,'XzpbdjBdMTY4ODI1OTM2MS0xNDQ0MQ==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (215,'XzpbdjBdODMzNjcyODU1LTQ2NDYw'),
 (216,'XzpbdjBdODQ4NDQ4NzQzLTI3NDQ1'),
 (217,'XzpbdjBdLTExMjIyODk3MjEtNDUwNjU=\n'),
 (218,'XzpbdjBdOTI5ODQ0MDI3LTI1NTc2'),
 (219,'XzpbdjBdLTI3NTc1ODIxLTM3ODM2'),
 (220,'XzpbdjBdMTAyMjA5NzQ0Mi01NDEzOQ==\n'),
 (221,'XzpbdjBdMTg0NTcxNzc4NC01Mjk3OQ==\n'),
 (222,'XzpbdjBdMTU4OTQ0ODYxNS0yODc2NQ==\n'),
 (223,'XzpbdjBdLTE3MzgxOTQ3NjUtNzMxMg==\n'),
 (224,'XzpbdjBdNDcwOTkxMjczLTUzMjAy'),
 (225,'XzpbdjBdLTExMTMxOTk1ODktMzEwODg=\n'),
 (226,'XzpbdjBdMTQ0MTc3Mzk1Ni00MjU5Mw==\n'),
 (227,'XzpbdjBdNDQ2OTkxOTk1LTE1Mzcz'),
 (228,'XzpbdjBdOTEwNzA4MjIxLTM2NDU1'),
 (229,'XzpbdjBdLTEzMTg5ODgwMTgtMzE4OTY=\n'),
 (230,'XzpbdjBdLTE1NzE5OTUwMTEtNDI5NTk=\n'),
 (231,'XzpbdjBdLTIwNTk2ODcyODItMzg4MjQ=\n'),
 (232,'XzpbdjBdLTEwNTg0MjY0MTYtMzgxNTU=\n'),
 (233,'XzpbdjBdLTE2MjAxMzI4NDctNDY4Mzc=\n'),
 (234,'XzpbdjBdMTA2MjU3NjUxNi0zMzU4Nw==\n'),
 (235,'XzpbdjBdMTk2MTMwMTkxOS0yNjIwNQ==\n'),
 (236,'XzpbdjBdLTE2NDU1MTExNzMtNTQ5MjU=\n'),
 (237,'XzpbdjBdLTMyMjgyNTExOS0zOTk4NA==\n'),
 (238,'XzpbdjBdLTE3MTI1MjQxMS0yNzQ3NA==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (239,'XzpbdjBdLTEzMDY0OTA5MDMtMjY4ODg=\n'),
 (240,'XzpbdjBdMTgzODk2ODI0NS0xMjE4Mw==\n'),
 (241,'XzpbdjBdMzA3Nzc5ODQxLTUxMTQ5'),
 (242,'XzpbdjBdMjAzODg5NDIwLTc3MzA=\n'),
 (243,'XzpbdjBdMjAzMDE1MTQ0Ny0yOTYxOQ==\n'),
 (244,'XzpbdjBdNDYyNTkyOTMtNTE2OTU=\n'),
 (245,'XzpbdjBdLTQ3NzkwMjY0MC00MzU0'),
 (246,'XzpbdjBdLTMxNzE1ODk5NS02MTMyNQ==\n'),
 (247,'XzpbdjBdLTgzNjA4MTM1NS01NjA2NQ==\n'),
 (248,'XzpbdjBdNDI2MTA3Nzk5LTIxMjE2'),
 (249,'XzpbdjBdLTIwNTk2Mzg3MTEtMTI2MzM=\n'),
 (250,'XzpbdjBdLTEyNzk0Mjc2MjQtMjE4NTE=\n'),
 (251,'XzpbdjBdLTEyMjQ1OTk3NjUtNTg3NTU=\n'),
 (252,'XzpbdjBdLTE3NzI1MDQ4NTEtMzEyNzY=\n'),
 (253,'XzpbdjBdMTY0NDY2MTcwNi01MzYyNQ==\n'),
 (254,'XzpbdjBdLTE2NTMwNzA3ODItMjg2MQ==\n'),
 (255,'XzpbdjBdLTEwNTc1NDc2MTgtMTkyNzQ=\n'),
 (256,'XzpbdjBdLTUwNjgxNzc2MC0xMTQ4'),
 (257,'XzpbdjBdLTE5NjE2NjIzNzAtMjAxNjY=\n'),
 (258,'XzpbdjBdLTE1NDE3MDYxMjctMTk0MjA=\n'),
 (259,'XzpbdjBdLTEyOTQ2NjY1Ni00MzI3OQ==\n'),
 (260,'XzpbdjBdLTIyNTIxNTUwOS05Nzg2'),
 (261,'XzpbdjBdLTkxNzk1NTUyLTE1OTcy');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (262,'XzpbdjBdMTA0NTkwODI3LTQxNjQx'),
 (263,'XzpbdjBdMTU0MDcxMDAxMC00NTE0Mg==\n'),
 (264,'XzpbdjBdNjM0ODQ2MjYwLTE3MTM5'),
 (265,'XzpbdjBdNjc5MzcyNTAzLTE0NTI=\n'),
 (266,'XzpbdjBdMTIwMjIxMzEzOS0yNTc1OA==\n'),
 (267,'XzpbdjBdNzIyMTUzNTk3LTE3NjMy'),
 (268,'XzpbdjBdLTE0MzQ1OTUyNDEtNTUwNDA=\n'),
 (269,'XzpbdjBdMTY2MjcwODM1NS00MjA5NA==\n'),
 (270,'XzpbdjBdLTkyOTg0Mzc4Ny04ODEx'),
 (271,'XzpbdjBdLTg2MzYxMjc5NC0zMDgwMw==\n'),
 (272,'XzpbdjBdLTIwNjc1MDA1NjItMTE3MDg=\n'),
 (273,'XzpbdjBdLTQ2MTQ2MTYzOS0xMzg1NA==\n'),
 (274,'XzpbdjBdLTEwMzkyMTU3MDgtMjk0ODM=\n'),
 (275,'XzpbdjBdODAwNzU4NzU3LTI3NjUz'),
 (276,'XzpbdjBdLTMxMDI4NjkzMy0zODY5OA==\n'),
 (277,'XzpbdjBdODg0MzMwNzI0LTYzOTQ4'),
 (278,'XzpbdjBdLTE3OTY4MDkwMC0zNDg1MQ==\n'),
 (279,'XzpbdjBdLTQ3NTk1NTg1NS0xNTI0MQ==\n'),
 (280,'XzpbdjBdLTE4OTU0NTk3NjItOTkzMA==\n'),
 (281,'XzpbdjBdMzA4OTA4MzA0LTQ2MTQ=\n'),
 (282,'XzpbdjBdMTI2NjcyMTY1Mi0xNTU5OQ==\n'),
 (283,'XzpbdjBdNzIzMDIzNTU2LTQyNTcx'),
 (284,'XzpbdjBdLTE4NjgwNzIzOTUtNDg4NTk=\n'),
 (285,'XzpbdjBdMjEwNTQ3Mzc3My0zNDkzNA==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (286,'XzpbdjBdNjY4Njg1OTAxLTI3MTAw'),
 (287,'XzpbdjBdLTkyNzkxNzgzMC05Mjk3'),
 (288,'XzpbdjBdLTE4MTc1MDIxMC02MDIxMA==\n'),
 (289,'XzpbdjBdLTI4MDA2NjAwMi01NjIwMQ==\n'),
 (290,'XzpbdjBdOTk5OTQ3NjE5LTU2NTM1'),
 (291,'XzpbdjBdLTE3NDA5ODgyMjUtMjM1NDM=\n'),
 (292,'XzpbdjBdMTg4ODA1NjA1My0yOTc5'),
 (293,'XzpbdjBdMzM3NDg0OTUtNTgxODg=\n'),
 (294,'XzpbdjBdMTIyNjYyNTc0My01NDM4'),
 (295,'XzpbdjBdMjM0NjYyNjA0LTk0OA==\n'),
 (296,'XzpbdjBdLTEyNTAyNzUwNTQtMjU2Mzk=\n'),
 (297,'XzpbdjBdMTIzMDIzNTQ5My0xMzYzOQ==\n'),
 (298,'XzpbdjBdMjA0NDgxMDk4Ny0yMTI0Mg==\n'),
 (299,'XzpbdjBdMTM5MDExOTQyNi02Mzg3NQ==\n'),
 (300,'XzpbdjBdMjExNjA2MTIwNi01Njg5Mg==\n'),
 (301,'XzpbdjBdLTE1NzA2NTgxMDktMzU3NzM=\n'),
 (302,'XzpbdjBdNjI3MjA5MjYxLTEzNjU5'),
 (303,'XzpbdjBdOTg4MTM0NDY2LTM2NTU1'),
 (304,'XzpbdjBdLTIyNzgzNzYxMS01MjQ5OQ==\n'),
 (305,'XzpbdjBdLTIyNzgzNzYwOS01MjQ5OQ==\n'),
 (306,'XzpbdjBdLTIyNzgzNzYwNS01MjQ5OQ==\n'),
 (307,'XzpbdjBdLTIyNzgzNzU5My01MjQ5OQ==\n'),
 (308,'XzpbdjBdLTIyNzgzNzU4MS01MjQ5OQ==\n'),
 (309,'XzpbdjBdLTIyNzgzNzU3OS01MjQ5OQ==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (310,'XzpbdjBdLTIyNzgzNzU3My01MjQ5OQ==\n'),
 (311,'XzpbdjBdLTIyNzgzNzU3MS01MjQ5OQ==\n'),
 (312,'XzpbdjBdOTI3NzIyMjM5LTU2OTYw'),
 (313,'XzpbdjBdLTIyNzgzNzU2OS01MjQ5OQ==\n'),
 (314,'XzpbdjBdLTE3MjgyNjQ0ODMtNTY3Nzk=\n'),
 (315,'XzpbdjBdNDU2MTc3MzA3LTUyOTUz'),
 (316,'XzpbdjBdMTg3MTYzNzA2Ny02MzA2Mw==\n'),
 (317,'XzpbdjBdLTIwNTU5NTYxNDktMTg5NTY=\n'),
 (318,'XzpbdjBdOTY4MzQ1ODU5LTU4MTc2'),
 (319,'XzpbdjBdLTE0NTA5ODExNDgtNjA5NTY=\n'),
 (320,'XzpbdjBdNDk5MzkyOTM5LTM2MzE0'),
 (321,'XzpbdjBdLTE0NDc2NzI1MjYtMTMwNjg=\n'),
 (322,'XzpbdjBdMTI3MDA5MjgwLTM1MzMz'),
 (323,'XzpbdjBdMTM4NDU4ODEyNS00OTA1OA==\n'),
 (324,'XzpbdjBdLTUwNDAzNzU2NS04ODA1'),
 (325,'XzpbdjBdLTU5NjYwMDQyMS0zMzI3NQ==\n'),
 (326,'XzpbdjBdMTg5NzU2NDc1OC0yMTg5OA==\n'),
 (327,'XzpbdjBdLTc2NDc0MDM2OC0xMjEzNw==\n'),
 (328,'XzpbdjBdLTE4NTQ1NjE3MC01OTc1OQ==\n'),
 (329,'XzpbdjBdNzU0NzM5MjczLTE3MjE1'),
 (330,'XzpbdjBdLTU2NjU0ODI4Mi0zOTk2MA==\n'),
 (331,'XzpbdjBdMjEyMzg2NTQ1NS00MTAwNA==\n'),
 (332,'XzpbdjBdLTQ2NTc0NDAwMC00Mjg3NA==\n'),
 (333,'XzpbdjBdOTE3ODQwOTEwLTYyOTA=\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (334,'XzpbdjBdMTYyNDg2MTMzNi0zNDU0'),
 (335,'XzpbdjBdMTc5OTQ0MDMwLTYwOTc3'),
 (336,'XzpbdjBdMTY0NTc1MTk0My01ODUzOQ==\n'),
 (337,'XzpbdjBdLTE5NDUyNjk2OTItNTYzODQ=\n'),
 (338,'XzpbdjBdMzM2MDQyNDYzLTQ2MjQ5'),
 (339,'XzpbdjBdLTE2NTk4NTUyNTQtNDcyMjA=\n'),
 (340,'XzpbdjBdMTcyNzMzNDIwOS0xOTM0MA==\n'),
 (341,'XzpbdjBdMTA1MzY0Nzk2MS0zMzMwNg==\n'),
 (342,'XzpbdjBdLTE3MjI4NTYwMDMtMjc1NzQ=\n'),
 (343,'XzpbdjBdLTQ4ODUyODExMS00NDAwNw==\n'),
 (344,'XzpbdjBdMTM5NDk1MDk4OS0yNDQ4NA==\n'),
 (345,'XzpbdjBdNTc2Mzg2NTA3LTIzOTQ4'),
 (346,'XzpbdjBdMjc0MTAyOTMxLTkxNTI=\n'),
 (347,'XzpbdjBdLTIzMTIyMTg4MC02MjkyOA==\n'),
 (348,'XzpbdjBdMzM2OTI2NTM5LTYyOTA3'),
 (349,'XzpbdjBdLTIxMjcxNzM0NDUtMzA5OTI=\n'),
 (350,'XzpbdjBdLTUxMzI3Mjg1OC0yNzg1Nw==\n'),
 (351,'XzpbdjBdMzQ1MzkyOTA0LTI4MzA0'),
 (352,'XzpbdjBdMTc2NzA5NDkxNS00NzM3Nw==\n'),
 (353,'XzpbdjBdLTE5OTU4MjA3NTEtMTMwNjk=\n'),
 (354,'XzpbdjBdMTM4MzUyMTA0MS00MDYyNQ==\n'),
 (355,'XzpbdjBdLTg0NzgzNjQyMi01MjIyMg==\n'),
 (356,'XzpbdjBdLTE5ODkzMzgxMS0zOTQ1Mw==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (357,'XzpbdjBdLTE3MDc3NzQ1NjAtMjgxMzI=\n'),
 (358,'XzpbdjBdNTgwNTY5NTktNTU3MDk=\n'),
 (359,'XzpbdjBdLTE2OTkyMDYxNTUtNzcwNw==\n'),
 (360,'XzpbdjBdLTM4OTc2OTUxMS00Mjg=\n'),
 (361,'XzpbdjBdLTY2NDE3NjI3OC0zNTcyMQ==\n'),
 (362,'XzpbdjBdLTUxMDExMjk0Mi0zODcwOA==\n'),
 (363,'XzpbdjBdMTE1NzQxNjE3MC02MTA1MA==\n'),
 (364,'XzpbdjBdLTE5NzUxMzQ4NjUtMTk1NTU=\n'),
 (365,'XzpbdjBdLTY1ODIxMzA3Ni0yNjY=\n'),
 (366,'XzpbdjBdLTI0MjkwNjktNTk1MDU=\n'),
 (367,'XzpbdjBdMjAwNTcyODI2LTM4MTQ3'),
 (368,'XzpbdjBdLTIwODUyMjA2NTctMTI3NjM=\n'),
 (369,'XzpbdjBdNjQxNjg1NTYtMjgyOA==\n'),
 (370,'XzpbdjBdLTEyNTAyMzQ0MTUtMjYxMzQ=\n'),
 (371,'XzpbdjBdLTExNzE2MTk4MTMtMTAxNzc=\n'),
 (372,'XzpbdjBdMTc5OTMwMDUyNy0xODI3Mw==\n'),
 (373,'XzpbdjBdMTQxODgxNDgxNS01MTM5MA==\n'),
 (374,'XzpbdjBdLTcyNzc0MzItMzU3MzU=\n'),
 (375,'XzpbdjBdMjI1OTU0MDMwLTYwNzM1'),
 (376,'XzpbdjBdLTY2MDY2NzcxOC02MzM3MQ==\n'),
 (377,'XzpbdjBdLTEzMDU4ODIzNjEtNDgyNzk=\n'),
 (378,'XzpbdjBdODgzMDA4MzQ4LTI3Mzc2'),
 (379,'XzpbdjBdLTE3NDg5NjA0ODQtMzQ3ODU=\n'),
 (380,'XzpbdjBdNDU3NDU2MDAtNjQ0OTQ=\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (381,'XzpbdjBdLTE4MDkxODUxMjItMjE0NjE=\n'),
 (382,'XzpbdjBdMTU4MzMyNDg1Mi02NDgwMQ==\n'),
 (383,'XzpbdjBdLTE0MDEzMjU5OTgtMTk3ODE=\n'),
 (384,'XzpbdjBdLTEwODkwNDA0NTYtMTYxODc=\n'),
 (385,'XzpbdjBdMjAyMzExODI3Ny0xNTY2Mw==\n'),
 (386,'XzpbdjBdNjUxNTM0NjgxLTMwMjk3'),
 (387,'XzpbdjBdLTEwOTU2MzAyOTYtMjEzOTE=\n'),
 (388,'XzpbdjBdODg1Nzk2ODMyLTU1OTYz'),
 (389,'XzpbdjBdMzM2NDczOTc3LTYyNDY4'),
 (390,'XzpbdjBdMzU1MjIwMjk2LTgwMDk=\n'),
 (391,'XzpbdjBdLTk3MzIyOTk1My02MTU3MQ==\n'),
 (392,'XzpbdjBdLTE4Njc1NTY2NTEtMjUxODE=\n'),
 (393,'XzpbdjBdNDIzNjIzNjU0LTU5ODI4'),
 (394,'XzpbdjBdMTU5MjY2NDMzLTU2ODg1'),
 (395,'XzpbdjBdMTA5MzA1NjA1NS0yODk1OA==\n'),
 (396,'XzpbdjBdNzExMDQzNTk2LTcxMDM=\n'),
 (397,'XzpbdjBdLTE2MDIxNTYxMTEtNTg4NzQ=\n'),
 (398,'XzpbdjBdMjkxNjIyNzk5LTM4Nzkz'),
 (399,'XzpbdjBdLTIwODg5NDA0NTUtNTA1NjA=\n'),
 (400,'XzpbdjBdLTE0MjI2NDA5NzQtNDEwNw==\n'),
 (401,'XzpbdjBdMjc2NDM5OTU0LTMwOTA=\n'),
 (402,'XzpbdjBdMTgzNDg4NDE0MC0yNTQ4Ng==\n'),
 (403,'XzpbdjBdLTIwNzU2MTc4MDgtNTA1NDg=\n'),
 (404,'XzpbdjBdMTM0OTk0NTEwLTMzMDY2');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (405,'XzpbdjBdMTk1NDk3NTU4OC0zMTE3NA==\n'),
 (406,'XzpbdjBdMTQwOTI3NjI1OC0yNDM4OA==\n'),
 (407,'XzpbdjBdLTE4MjQ1MDQ5MzAtNDYzNTg=\n'),
 (408,'XzpbdjBdLTE2MjM5MjgzMTUtMzUxNjI=\n'),
 (409,'XzpbdjBdLTQxNTc2MDAxNC04NQ==\n'),
 (410,'XzpbdjBdLTIwNTMwNTU1NDctNjIxNTU=\n'),
 (411,'XzpbdjBdLTE0Mjg2NzU0NDEtNjIxODY=\n'),
 (412,'XzpbdjBdLTEzNjc1MjczMjItMjg1NjA=\n'),
 (413,'XzpbdjBdLTQ3ODIwODc4Mi00ODUzMg==\n'),
 (414,'XzpbdjBdMTc3ODA4MzE3Ni01ODI0'),
 (415,'XzpbdjBdLTE5MTE3NTI1NjMtMjkxNTk=\n'),
 (416,'XzpbdjBdMjcxMTM1MTY4LTU5MTI5'),
 (417,'XzpbdjBdLTI4MjgyNDM4Ny00NzA1OA==\n'),
 (418,'XzpbdjBdLTEwNzQ5OTc4NjQtMjAxNjg=\n'),
 (419,'XzpbdjBdLTEwNDQ3NjIyMDctMzQ3NjU=\n'),
 (420,'XzpbdjBdLTEzNjI4OTMxMjYtMjQ5NzQ=\n'),
 (421,'XzpbdjBdMTY2NDA5NDkyMi0zMDIyOA==\n'),
 (422,'XzpbdjBdLTE2MjgwNDY5MjktMzIyNzE=\n'),
 (423,'XzpbdjBdMTA5MTc2MTI3OS02Mzk1NQ==\n'),
 (424,'XzpbdjBdLTE1OTcxODg3MzctMTI5NzA=\n'),
 (425,'XzpbdjBdMTA3ODU3NzA0MS0xNjIy'),
 (426,'XzpbdjBdMTcyMTg0NDg1LTUyMzM=\n'),
 (427,'XzpbdjBdLTEwODA1NjY3MDYtNDE3OTM=\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (428,'XzpbdjBdMTQyNTg5MjI2MC01NTUxMQ==\n'),
 (429,'XzpbdjBdOTkyNTcxMjg4LTU0Nzk5'),
 (430,'XzpbdjBdLTEyODQwMTA5MzctNDM5OTY=\n'),
 (431,'XzpbdjBdLTEyMzMyMzM5MTEtNDkzNjE=\n'),
 (432,'XzpbdjBdMTM1MzAyNjYwMi01NDQyMw==\n'),
 (433,'XzpbdjBdMzY2MjExMTAxLTM3MjQ3'),
 (434,'XzpbdjBdODc4NTQyNzMwLTU3NDkz'),
 (435,'XzpbdjBdLTEzNTIyNjYyNzgtNTM4MjA=\n'),
 (436,'XzpbdjBdLTYwMTMwNjYzMS0yMDg3MQ==\n'),
 (437,'XzpbdjBdLTE1OTExMDQzMDgtNTEyNDI=\n'),
 (438,'XzpbdjBdLTEzNDAwOTI2OTYtMzAwMjM=\n'),
 (439,'XzpbdjBdLTIzNDk1Njc5MS01NTc1Nw==\n'),
 (440,'XzpbdjBdMjA4Mjc3NjMwNy0xMjU1Mg==\n'),
 (441,'XzpbdjBdLTIzMDUyNDAzOS00NTMxNQ==\n'),
 (442,'XzpbdjBdMjEwMTU5OTY4LTEwNTEy'),
 (443,'XzpbdjBdMTc4NTYyNTQ0OS0zOTczNA==\n'),
 (444,'XzpbdjBdMTQyNTExNjQ1MS0yODEyMg==\n'),
 (445,'XzpbdjBdLTIwNDg3MTU3MjgtMjQ4NzE=\n'),
 (446,'XzpbdjBdMjc0MDgxNDAwLTM1NTYx'),
 (447,'XzpbdjBdLTE2NzU4MjQ5ODktNDA0MzY=\n'),
 (448,'XzpbdjBdLTQ2NDkyMzQ2My0yNDk0OQ==\n'),
 (449,'XzpbdjBdLTg5OTQ2Njg5OC01NTgxMQ==\n'),
 (450,'XzpbdjBdMTE4MTk5OTU0NC0yMDM5NQ==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (451,'XzpbdjBdMTc5MDgzMTY2OC01Njk2Mg==\n'),
 (452,'XzpbdjBdLTE1NjE2NjExOTMtNTIwODY=\n'),
 (453,'XzpbdjBdLTI0MTMzODgwMC0zMzI0NA==\n'),
 (454,'XzpbdjBdMTY2ODYzMDA5MC0xMTgwMw==\n'),
 (455,'XzpbdjBdLTY3NjY2ODk3Ni01MTg0MQ==\n'),
 (456,'XzpbdjBdMjA2NjA5OTU2MC02MDQ4OQ==\n'),
 (457,'XzpbdjBdLTEyMzE0NjIzMTQtMzg5ODk=\n'),
 (458,'XzpbdjBdLTIwMzM1MzkwODYtMzI3NTE=\n'),
 (459,'XzpbdjBdMzQwNjE4Njc4LTY0Mzg4'),
 (460,'XzpbdjBdLTE4MTYxODc1MTUtMzAyMjg=\n'),
 (461,'XzpbdjBdLTE4NDc4ODQ3NTEtMjQ1NzE=\n'),
 (462,'XzpbdjBdLTE2Nzk4OTI3NzQtNzcyMw==\n'),
 (463,'XzpbdjBdLTE3NjQyOTgzMDAtMzY1OTE=\n'),
 (464,'XzpbdjBdLTk1MDk2Mzk3My00ODI1'),
 (465,'XzpbdjBdODE4NjExNDU5LTQ0OTA3'),
 (466,'XzpbdjBdMTYxNTAyMzczMC0zMTkz'),
 (467,'XzpbdjBdLTE3MDgzOTEzOS0zNDIzOQ==\n'),
 (468,'XzpbdjBdOTQxODc4NDU2LTQ2MDUz'),
 (469,'XzpbdjBdLTEzNzQwNDgwMjEtMTEyODk=\n'),
 (470,'XzpbdjBdLTY0OTgzMjAxMS02NDUwMg==\n'),
 (471,'XzpbdjBdMTY2MzA1OTYyOC02NDM1OQ==\n'),
 (472,'XzpbdjBdMTkzMTY1MDA0NC01OTAzNA==\n'),
 (473,'XzpbdjBdMzg0Njc0ODE1LTkyOA==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (474,'XzpbdjBdMTYzOTE0ODM1MS0yOTE0MA==\n'),
 (475,'XzpbdjBdLTI4MDMyOTgwMi03MDAw'),
 (476,'XzpbdjBdNzA4MDU0ODg0LTE0ODIy'),
 (477,'XzpbdjBdNTMwODkwOTYwLTY1MzAz'),
 (478,'XzpbdjBdMTE0MjEzMTEyNy00MTg4OA==\n'),
 (479,'XzpbdjBdMTQxNjQzMDE1OC0yMDIzNQ==\n'),
 (480,'XzpbdjBdMTM5NzA4NDgzNS00MTgyNQ==\n'),
 (481,'XzpbdjBdLTI1OTQxMzk5MS01MzE5OQ==\n'),
 (482,'XzpbdjBdLTIwNTM3MTAyNTMtMzA1NDM=\n'),
 (483,'XzpbdjBdLTE2ODk3MTc1NjEtNTM2NzM=\n'),
 (484,'XzpbdjBdLTE2MzI0Mzk2MTgtMTYxMTg=\n'),
 (485,'XzpbdjBdLTU5NjAxMDI0OS0yNzEz'),
 (486,'XzpbdjBdMTQwNzA5NjQ0MC00ODQxNA==\n'),
 (487,'XzpbdjBdLTE0NzkxMDY1MTQtNDE2ODM=\n'),
 (488,'XzpbdjBdLTE1OTM0MzIyNjUtMzUwNTE=\n'),
 (489,'XzpbdjBdMjA5MTI3MjAzMS02NzM1'),
 (490,'XzpbdjBdMTI5OTMxMzk2Ni01NzI2NQ==\n'),
 (491,'XzpbdjBdMTc3OTQxNTYwOS03MjUz'),
 (492,'XzpbdjBdLTUxMzYzNTM4MC00ODEzNQ==\n'),
 (493,'XzpbdjBdLTEyMDAwODI2OTAtMTc5MDE=\n'),
 (494,'XzpbdjBdMTY1NzQ2OTM1My00OTU4'),
 (495,'XzpbdjBdMTg3OTYzODg4My02MjI0Nw==\n'),
 (496,'XzpbdjBdLTE3NTExMTkzMC00NjQz'),
 (497,'XzpbdjBdLTExNjUyMzEwOTMtNDAxNzc=\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (498,'XzpbdjBdLTQwNjU4NTk2NC0xMDcxMw==\n'),
 (499,'XzpbdjBdLTIxNDQzMDQ0MjAtMTg5OTE=\n'),
 (500,'XzpbdjBdLTE1OTI3NjgwMzEtNTgyMDE=\n'),
 (501,'XzpbdjBdLTg3MjM3NjA4MC0xMjI0MQ==\n'),
 (502,'XzpbdjBdLTgyODMwMTM4OS01ODQ4Ng==\n'),
 (503,'XzpbdjBdMTMxNjg0OTg1NC00MTQ1Mg==\n'),
 (504,'XzpbdjBdMTUzMzYzNDA2Ny00ODA3Nw==\n'),
 (505,'XzpbdjBdNDkwNDE2NDgxLTQ4ODg5'),
 (506,'XzpbdjBdLTEwNzA5ODAzOTUtMjg2NjI=\n'),
 (507,'XzpbdjBdNTczOTE0NTI2LTUyOTE0'),
 (508,'XzpbdjBdLTIwODI4MzU0NjAtNTM5Mjg=\n'),
 (509,'XzpbdjBdLTE3NjkzNjI0MTgtNzE1MA==\n'),
 (510,'XzpbdjBdNDgxNTU0MjQ0LTIyOTcy'),
 (511,'XzpbdjBdMjEyODA1Mzk2MC0yOTQz'),
 (512,'XzpbdjBdLTQ2MTE3Nzg1OS0zNzYzNQ==\n'),
 (513,'XzpbdjBdMTU2MzUxNzUzMS0zNDcyNg==\n'),
 (514,'XzpbdjBdMTUxNzI0NzQ1OC01NTkyNg==\n'),
 (515,'XzpbdjBdLTE3NzM1NTQ0NDktMjMyMDI=\n'),
 (516,'XzpbdjBdMTkxMzE0NDYwMy0yNTI4OQ==\n'),
 (517,'XzpbdjBdLTg0NTI5ODA3MC02NDA4Mg==\n'),
 (518,'XzpbdjBdMTcxMzQ5NjA1Mi01MDU4Ng==\n'),
 (519,'XzpbdjBdLTk3ODUzNDMzOC0yMzQ2NA==\n'),
 (520,'XzpbdjBdLTIzNjQ4NjUzMy0yOTAyOA==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (521,'XzpbdjBdLTU3Mzk2MzEtNjI3NDU=\n'),
 (522,'XzpbdjBdLTM5MjIwMDI3Mi00NzMxMA==\n'),
 (523,'XzpbdjBdMTc4NTY3MjIxNy03NzI1'),
 (524,'XzpbdjBdOTA2NjIzNTgzLTMxMDYw'),
 (525,'XzpbdjBdOTA2NjIzNTg0LTMxMDYw'),
 (526,'XzpbdjBdLTEyMDIzMjk3My05ODA=\n'),
 (527,'XzpbdjBdMjI2MTczODQ3LTE5ODAy'),
 (528,'XzpbdjBdNzUyMTc2MDkwLTQ3MjE5'),
 (529,'XzpbdjBdOTA2NjIzNTg1LTMxMDYw'),
 (530,'XzpbdjBdOTA2NjIzNTg2LTMxMDYw'),
 (531,'XzpbdjBdOTA2NjIzNTg3LTMxMDYw'),
 (532,'XzpbdjBdOTA2NjIzNTg5LTMxMDYw'),
 (533,'XzpbdjBdOTA2NjIzNTg4LTMxMDYw'),
 (534,'XzpbdjBdMTk3MDM4MTYxMi0xNjQ0MA==\n'),
 (535,'XzpbdjBdLTE0MDI0NzcyMzYtMTYzMzU=\n'),
 (536,'XzpbdjBdLTE3NjQzODA0Ni0zMzI4NQ==\n'),
 (537,'XzpbdjBdLTI5ODkzODc1OC00MTU5MA==\n'),
 (538,'XzpbdjBdLTk0NDc4OTIwMC02MzkyNQ==\n'),
 (539,'XzpbdjBdMTc2NDg0MDA1LTQwNTIx'),
 (540,'XzpbdjBdMTgxNTQzMjMzMy01NjMxMw==\n'),
 (541,'XzpbdjBdMjA0MDgxODI0My0zNjExMg==\n'),
 (542,'XzpbdjBdLTgxMDY1OTczNi0xMTgyOQ==\n'),
 (543,'XzpbdjBdLTEyNTI4MjEzMzQtNTM1MjM=\n'),
 (544,'XzpbdjBdLTk1NTg4NTI3OS02MDM3Nw==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (545,'XzpbdjBdLTE3NDE3MzUwNDQtNDM4NDg=\n'),
 (546,'XzpbdjBdNTcwNjEyODI1LTQ5MTQ5'),
 (547,'XzpbdjBdLTE1ODYyNDgyMTctMzA3MA==\n'),
 (548,'XzpbdjBdLTEyNDUyODE5MTEtNjAyNzU=\n'),
 (549,'XzpbdjBdNjQyOTg3MjMyLTE1Mzc1'),
 (550,'XzpbdjBdODg0Mjk5NDkzLTIwNDI2'),
 (551,'XzpbdjBdMTQyMzMyNDQ0Ni01NzMz'),
 (552,'XzpbdjBdLTEzMDA0MTU2MjgtMzQwNjc=\n'),
 (553,'XzpbdjBdLTEyOTI3OTAyNS0xODE4MQ==\n'),
 (554,'XzpbdjBdLTMyNDE5MjY2MS0zNDU1Mg==\n'),
 (555,'XzpbdjBdLTExODA5NDIyLTYwOTg5'),
 (556,'XzpbdjBdLTExNjEwOTUxNzEtOTE3Mg==\n'),
 (557,'XzpbdjBdMTg2ODE4MTQzNi0yMDY2Mw==\n'),
 (558,'XzpbdjBdMTg3OTc0Nzk5Ni0zNTg3Nw==\n'),
 (559,'XzpbdjBdMTc0NDcxNTA2OS0yNjgwMg==\n'),
 (560,'XzpbdjBdLTIxMTIwNDcxOTAtNDkyNDQ=\n'),
 (561,'XzpbdjBdMzIyNDc4OTExLTMwNTcx'),
 (562,'XzpbdjBdLTE2ODYyODQ2NTItNTYwNg==\n'),
 (563,'XzpbdjBdNjk1NzQ1NjUwLTQ3NDI4'),
 (564,'XzpbdjBdLTUyMjc3MDg0MS0zODk2OA==\n'),
 (565,'XzpbdjBdLTE5MzgwMDcwNTctNDU0NDA=\n'),
 (566,'XzpbdjBdLTQxNjMxMTI3My02Mzc3Mw==\n'),
 (567,'XzpbdjBdLTIzODkzMjM1My0zODYzNw==\n'),
 (568,'XzpbdjBdLTc1Mjg4NjA0MS01NTgyOQ==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (569,'XzpbdjBdLTE2MzA0NTY0NzAtMjk3MzQ=\n'),
 (570,'XzpbdjBdLTU0NDkxMDgwNi00MTU2'),
 (571,'XzpbdjBdNTg1MDYzNjY4LTQ0Mzgy'),
 (572,'XzpbdjBdMTk4MTkyMDY3My01NDQ4'),
 (573,'XzpbdjBdLTExOTM5NzEwMTEtMTQwNTg=\n'),
 (574,'XzpbdjBdLTc2ODI4NzQzOC0yMzUyNw==\n'),
 (575,'XzpbdjBdOTYzNDM5OTEwLTY0Mjky'),
 (576,'XzpbdjBdLTE0OTI2MDM1MjUtMjU2MjI=\n'),
 (577,'XzpbdjBdMTg4MTQ0OTE3OS01MzAwMg==\n'),
 (578,'XzpbdjBdLTg5MjQ2NDU4My01NDYyNA==\n'),
 (579,'XzpbdjBdLTE5NjQ3MDY1NzctNDE3Mjc=\n'),
 (580,'XzpbdjBdLTM1NTI4NzYxMi0yODA4Ng==\n'),
 (581,'XzpbdjBdNTE5NjM1NzIxLTExMzA4'),
 (582,'XzpbdjBdNjY3MzU1NjM1LTM0MDkz'),
 (583,'XzpbdjBdMTExMjI3NjY0MS0xOTI3OA==\n'),
 (584,'XzpbdjBdLTE2NjQ5NjgyMDgtMzI5ODI=\n'),
 (585,'XzpbdjBdMzU3Nzk0NjA2LTI2MjA5'),
 (586,'XzpbdjBdMzk3Mjc0MTQ1LTM5ODEx'),
 (587,'XzpbdjBdMTY1NDIyNjE2MS0zOTQ3MQ==\n'),
 (588,'XzpbdjBdLTE1MTk2NTk4NDktNjM3Nzg=\n'),
 (589,'XzpbdjBdMjE3NzMwOTgwLTQ1MTYx'),
 (590,'XzpbdjBdNDQzMzc0NzIyLTMwMDgw'),
 (591,'XzpbdjBdLTExNjY4Mjk1MTQtNTk1MTU=\n'),
 (592,'XzpbdjBdLTk1NDg2Njk0MC0yMjQ1');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (593,'XzpbdjBdLTIwMjkxNDk4NDQtMTY1MzY=\n'),
 (594,'XzpbdjBdLTQ4NDI0MzU5Mi01Mjg5Mw==\n'),
 (595,'XzpbdjBdMTgwMTU3MTgwNC00MjU1OQ==\n'),
 (596,'XzpbdjBdMzU0MzExNjMyLTYwNzEw'),
 (597,'XzpbdjBdLTc0ODcwMjM0NC00OTQy'),
 (598,'XzpbdjBdLTcyMTgzNzU0Mi00MzAzMg==\n'),
 (599,'XzpbdjBdMjAyOTc3ODU2MC02MTI2'),
 (600,'XzpbdjBdLTY3NDMyNTQzNS0xMDkyMQ==\n'),
 (601,'XzpbdjBdMjA1ODk2NjMzOC0yMjMzMQ==\n'),
 (602,'XzpbdjBdMTkyNDY0Njg4OS01Mjk0NA==\n'),
 (603,'XzpbdjBdLTU3NjkxNTU3Ni0yNTUxNQ==\n'),
 (604,'XzpbdjBdLTg0NDEwODA5My00OTQ2MQ==\n'),
 (605,'XzpbdjBdMjAxNTkwNDE5Ny0yMjA2'),
 (606,'XzpbdjBdLTk4NDI1Nzc5MS0zOTc3Nw==\n'),
 (607,'XzpbdjBdLTg1NDYxNTc5Ny0zMTE0OQ==\n'),
 (608,'XzpbdjBdNzE2NzkzNTUzLTYxMTYz'),
 (609,'XzpbdjBdLTE5MDI2OTEwMzUtNzUyNg==\n'),
 (610,'XzpbdjBdLTE5OTk0MTg3OTgtNTMzMQ==\n'),
 (611,'XzpbdjBdMjcxMjAwOTYwLTYzNDUy'),
 (612,'XzpbdjBdLTE0NjY4NTI2NjYtNDg1MzA=\n'),
 (613,'XzpbdjBdLTExODI5MDE3MzMtMzY0OTk=\n'),
 (614,'XzpbdjBdMTIyMzM3ODc0NC01NDM5OA==\n'),
 (615,'XzpbdjBdLTg5NDgxMTMyNi0yMzkxNg==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (616,'XzpbdjBdMTk4NDgxMTY2LTU0NTU=\n'),
 (617,'XzpbdjBdMjU4OTMyNjIxLTE2NjA4'),
 (618,'XzpbdjBdODYwMzQ0MTc3LTU0Mzk=\n'),
 (619,'XzpbdjBdLTExMDMxOTE4NDctMzMwODg=\n'),
 (620,'XzpbdjBdMTY0Mzk5ODI4My00Njk3MQ==\n'),
 (621,'XzpbdjBdLTExNTgxMTIxODgtMTEzMjc=\n'),
 (622,'XzpbdjBdLTE1MTIzNDE5NDUtNzAyMw==\n'),
 (623,'XzpbdjBdMTU0ODcxMDMxMi03OTA1'),
 (624,'XzpbdjBdMTQxNzU4MDM2OC02NDk4Mw==\n'),
 (625,'XzpbdjBdLTYwNjI3NzczOS01NzEwMw==\n'),
 (626,'XzpbdjBdNDg1ODcwMjU4LTM1OTQ5'),
 (627,'XzpbdjBdOTg5MTIzNjk3LTU0MDQx'),
 (628,'XzpbdjBdMTk2NTUyMjE4My0yOTgwNw==\n'),
 (629,'XzpbdjBdLTc5MTQxOTYyNS01NTg2OA==\n'),
 (630,'XzpbdjBdLTI2MTQ0MDM3Ny02NDIz'),
 (631,'XzpbdjBdMjAyOTgwMTM0MS0xNzE2'),
 (632,'XzpbdjBdMTEwNDM0MjQ3MC01NTM2MA==\n'),
 (633,'XzpbdjBdLTQyMjkwNTk4OC0xMzAwOQ==\n'),
 (634,'XzpbdjBdLTI5OTU4NTc5My0xMjU5NQ==\n'),
 (635,'XzpbdjBdLTUyNDI3NjkwMy0zMzE0MQ==\n'),
 (636,'XzpbdjBdMTMwNTI0MjE1MS0zNjczNw==\n'),
 (637,'XzpbdjBdLTg1NzQ1NzU3Ni0zNzc2OA==\n'),
 (638,'XzpbdjBdMTg2MjUxMjAwMy0xOTM2NA==\n'),
 (639,'XzpbdjBdLTUyODkzNjQ5NC00ODcyNA==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (640,'XzpbdjBdLTE3MzYyMzQ0NjEtMzc=\n'),
 (641,'XzpbdjBdLTUyMzcxMzUyNi0xNjA0Mw==\n'),
 (642,'XzpbdjBdLTE4NzUwNjAyNTUtMjk3OTI=\n'),
 (643,'XzpbdjBdMTg0OTMyNDQ0My01MTM1'),
 (644,'XzpbdjBdMzI5MjA3MzI2LTYwMjQ3'),
 (645,'XzpbdjBdOTIyNjQ0Mjk3LTIwODQy'),
 (646,'XzpbdjBdMTk5ODQzNDQyOC0yNTc0Ng==\n'),
 (647,'XzpbdjBdMTk4NDc3NzExOC01NTk2MQ==\n'),
 (648,'XzpbdjBdLTgxNTU0Nzk1NS02MzIxMA==\n'),
 (649,'XzpbdjBdLTEzMzgyOTQ0NC0yMDk5NQ==\n'),
 (650,'XzpbdjBdMjEzMTEwMDcyLTI4NDcw'),
 (651,'XzpbdjBdLTE5MjU2NzY5MDYtNTI5MjI=\n'),
 (652,'XzpbdjBdLTcyMTQ4ODgwNC01MTQzMg==\n'),
 (653,'XzpbdjBdLTIxNDU5MDExMTgtNTI3OTM=\n'),
 (654,'XzpbdjBdMTgyODkxMTg1NC0yMjkwMg==\n'),
 (655,'XzpbdjBdNTk2MjY0NDYzLTI3NTE=\n'),
 (656,'XzpbdjBdLTIzOTc4MTMxOS00NTM2'),
 (657,'XzpbdjBdLTEwMTM0MTM2MS0zNjI1'),
 (658,'XzpbdjBdLTE1NzMyMTgxMy00NDU5NQ==\n'),
 (659,'XzpbdjBdLTE3MTkyMzEwNC02MTA1MQ==\n'),
 (660,'XzpbdjBdMjE0NDUzMjM2OS0xMzc1Nw==\n'),
 (661,'XzpbdjBdOTQ0MjY4MzQwLTE3MzIz'),
 (662,'XzpbdjBdNTk2NjAyOTAxLTUwNw==\n'),
 (663,'XzpbdjBdLTE0ODU0ODk2NzgtMzgxOTY=\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (664,'XzpbdjBdMTM4MTM1Mjk1My0xMDA0NQ==\n'),
 (665,'XzpbdjBdMTI3Mzc4NjIwNC01MjUy'),
 (666,'XzpbdjBdMTQzMTgzNzczMC02Njg4'),
 (667,'XzpbdjBdNTM2MDQ2NTMzLTUwODMz'),
 (668,'XzpbdjBdNTg0MjM5OC02MzQ2NQ==\n'),
 (669,'XzpbdjBdLTEzNzk0MzUzNDAtNjMyMTg=\n'),
 (670,'XzpbdjBdMTcxMTMyNzA5OS0xNTE5Mg==\n'),
 (671,'XzpbdjBdLTgxOTU2ODAxLTYzNzYx'),
 (672,'XzpbdjBdLTM3NzA0NzU4OC00NTY2NA==\n'),
 (673,'XzpbdjBdOTgyNTMwMzY5LTE2MjY5'),
 (674,'XzpbdjBdNDU2MzY5NTMtNDE3OTQ=\n'),
 (675,'XzpbdjBdMzg1NTMyMDkyLTIzMzUy'),
 (676,'XzpbdjBdNjY2NjYzMDA4LTMyOTMw'),
 (677,'XzpbdjBdLTIxMDI4MTQwNjctNTUxMTA=\n'),
 (678,'XzpbdjBdLTE0Njg4ODA0My0xNTM2NQ==\n'),
 (679,'XzpbdjBdMTc4MTUxNjIzLTQ1OTAx'),
 (680,'XzpbdjBdOTU4NTU2MDIzLTM2NTg5'),
 (681,'XzpbdjBdMTI3Mzk1MTgxNi0zNTc1Mw==\n'),
 (682,'XzpbdjBdLTIxMDgxMjg4NjYtMjUzMTY=\n'),
 (683,'XzpbdjBdLTk1MTcwNzYzLTY1NDIz'),
 (684,'XzpbdjBdNzIyNDkwNDc2LTI2OTY0'),
 (685,'XzpbdjBdLTUwNTkwMzE4LTYzMzUw'),
 (686,'XzpbdjBdMjExNTM1NjMxNi0zMjA1Ng==\n'),
 (687,'XzpbdjBdMTI3OTY5Mjk1MS0zNTY5MQ==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (688,'XzpbdjBdLTQxODE0MzYwNy02MjUzNQ==\n'),
 (689,'XzpbdjBdLTg2Njg1MTkxNy0yNzYwMw==\n'),
 (690,'XzpbdjBdLTEyODYxMTEyOTUtMjYzOTI=\n'),
 (691,'XzpbdjBdOTM0OTU3MjIzLTUyMDE3'),
 (692,'XzpbdjBdLTIxMDYzMTkwODctNTUzNDU=\n'),
 (693,'XzpbdjBdMTI2ODg1MzUwNy0xMTY4OA==\n'),
 (694,'XzpbdjBdODA1MDMyNDQ3LTUyOTk1'),
 (695,'XzpbdjBdLTEwODA4MTA2OTYtNTQyMA==\n'),
 (696,'XzpbdjBdMzEwNjkzNTc2LTUxNjUz'),
 (697,'XzpbdjBdMTY0NjYxNTg0NC05Nzgx'),
 (698,'XzpbdjBdLTk2MzIzMDg2LTYxMDk0'),
 (699,'XzpbdjBdLTkzMjg3MjU2Mi00MDkyNw==\n'),
 (700,'XzpbdjBdMTAwMjc1MjU4MS03ODA0'),
 (701,'XzpbdjBdLTE3NTk2MjY3OS03MjMz'),
 (702,'XzpbdjBdLTM4NzkwODkxLTIzNTgy'),
 (703,'XzpbdjBdNDM0NTU1MjYwLTI5MzYy'),
 (704,'XzpbdjBdLTE3NTcyNDkxNjctMTg3MDg=\n'),
 (705,'XzpbdjBdLTEwMTQ3ODMzNS02MzUxMA==\n'),
 (706,'XzpbdjBdLTE1NjcwODM2NjMtNjAyMjY=\n'),
 (707,'XzpbdjBdMTgwNzAwNzU1NC00OTYwOQ==\n'),
 (708,'XzpbdjBdNjU5MTY0MDE2LTM4NzY1'),
 (709,'XzpbdjBdOTYwNTI0MzIwLTEwMTU0'),
 (710,'XzpbdjBdLTgwOTY3ODQ5Mi00Mzc0Mg==\n'),
 (711,'XzpbdjBdNzE1NjEzNTkzLTE1MTcy');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (712,'XzpbdjBdNTg3NDkwNDcwLTM0NTU4'),
 (713,'XzpbdjBdMTg3NjQ0MDk4My0zODMyMA==\n'),
 (714,'XzpbdjBdMTIyNDIwNzY5NC02NTAzNQ==\n'),
 (715,'XzpbdjBdMjEzNDUwNTg5NC0yODU5MQ==\n'),
 (716,'XzpbdjBdLTcyNjAyNDI3MS02MTg4NQ==\n'),
 (717,'XzpbdjBdMTc2MjEwOTkzMy0yOTA2Mw==\n'),
 (718,'XzpbdjBdLTY4MDA2NDg5Ni00NzQwMA==\n'),
 (719,'XzpbdjBdLTE1MDc0MDQyMTItNjE1MTQ=\n'),
 (720,'XzpbdjBdLTY4NTcwMzYxMy0xNjM0MA==\n'),
 (721,'XzpbdjBdNjE2MTMzNzIyLTE1Njkw'),
 (722,'XzpbdjBdODExNDMzMTMyLTU4OTI4'),
 (723,'XzpbdjBdLTE3NTg4MDg5NC0zOTAzOQ==\n'),
 (724,'XzpbdjBdLTUxNDMwOTkwOC0zNTE2'),
 (725,'XzpbdjBdMjA5NDM3MzkwLTMyNDA=\n'),
 (726,'XzpbdjBdLTk2MjY2MDg0NS0zNTU0OQ==\n'),
 (727,'XzpbdjBdLTIxMjA5Mjk5NjItMzQyODI=\n'),
 (728,'XzpbdjBdNDc2ODIwMjU2LTI5OTQy'),
 (729,'XzpbdjBdMjM0OTY3NjEtMjQ3MjQ=\n'),
 (730,'XzpbdjBdMzg0ODI0MjI0LTEwNjc=\n'),
 (731,'XzpbdjBdLTEzNTAwNTI1MDgtNjA5ODM=\n'),
 (732,'XzpbdjBdLTE0OTIzMDczNTktMzUyMA==\n'),
 (733,'XzpbdjBdNjcxMjA4ODIxLTU0MzQ5'),
 (734,'XzpbdjBdMTM1ODU0NDczOS0zMTc1NA==\n'),
 (735,'XzpbdjBdMTk1NDM3MDQ4MC0zMDA5Nw==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (736,'XzpbdjBdLTEzNDY0NTczOTYtMzI5NTg=\n'),
 (737,'XzpbdjBdMTY0Njc3MDk5MS0yOTI3NQ==\n'),
 (738,'XzpbdjBdMzY2NjI1NDkwLTExNjI0'),
 (739,'XzpbdjBdLTExNzY5MDg5NjItMzAwNzQ=\n'),
 (740,'XzpbdjBdMTkwOTY3NDE0Ny0zODY1Mg==\n'),
 (741,'XzpbdjBdLTYzMjc3OTkxNS00NzcwNQ==\n'),
 (742,'XzpbdjBdNDg1Mzg5NDc1LTM5Nzc=\n'),
 (743,'XzpbdjBdMTc4ODE2NzY3NS02NTI1OA==\n'),
 (744,'XzpbdjBdLTEwNDQ0NDYzMTgtNTYzNTE=\n'),
 (745,'XzpbdjBdLTExODUwMTg1NjYtNTM1ODc=\n'),
 (746,'XzpbdjBdLTM3MjYyMTkzOS03NDk2'),
 (747,'XzpbdjBdLTIwNjE4MDMwMDgtNjg5'),
 (748,'XzpbdjBdLTE3MjU2ODM4MDUtNjMzNQ==\n'),
 (749,'XzpbdjBdNjQ0MzMwNDQxLTQ1NjA3'),
 (750,'XzpbdjBdODQ2Njk4MzkwLTIwNzk0'),
 (751,'XzpbdjBdLTE2Njc0NDIyMy0zMDM1Mw==\n'),
 (752,'XzpbdjBdLTU3NTEyMTI5OC00MzEzOA==\n'),
 (753,'XzpbdjBdLTExMDc4NTA3MTQtMjk0ODA=\n'),
 (754,'XzpbdjBdLTExNDgzNTg1Mi01OTY1MA==\n'),
 (755,'XzpbdjBdLTIwODUyNTcwOTktNjQ2OTc=\n'),
 (756,'XzpbdjBdMTcwMDUyMTU4NS0xODkyNg==\n'),
 (757,'XzpbdjBdMTQxMjc2MTg3My0xNjI4MA==\n'),
 (758,'XzpbdjBdLTU3ODU1Mjk2My0zMTk2');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (759,'XzpbdjBdLTkwNzg0NjgwOS0xODUwNw==\n'),
 (760,'XzpbdjBdLTIwMzY4NDU4OTItNDEx'),
 (761,'XzpbdjBdMjA5Mzk1MTI5Ny0xMTQyNg==\n'),
 (762,'XzpbdjBdLTUyNTIzMzQyNy0xNDgwNQ==\n'),
 (763,'XzpbdjBdNTU4NDA1NTQ3LTU4ODI4'),
 (764,'XzpbdjBdNTA5MTcxODM1LTE5NDUw'),
 (765,'XzpbdjBdLTEzNjMwNDI2MDctMzA1NjM=\n'),
 (766,'XzpbdjBdLTE1MTMzNzkwNzQtMjAyMTM=\n'),
 (767,'XzpbdjBdMjM1OTMzNTI2LTMzNjgx'),
 (768,'XzpbdjBdLTE1MTM5OTQ5NTctNDU2NDg=\n'),
 (769,'XzpbdjBdMTI2NDM0NzY0Ny0xMDkxNQ==\n'),
 (770,'XzpbdjBdMTQ4NzIzOTYxMi0yMDcwMg==\n'),
 (771,'XzpbdjBdNjMyMzI5MDIxLTM5MzE=\n'),
 (772,'XzpbdjBdLTc0Njk2NTQzNi0xNzc5MA==\n'),
 (773,'XzpbdjBdNzUxOTI0MzY5LTI0Mzg3'),
 (774,'XzpbdjBdLTM3ODQ2ODYxOC00OTYyMQ==\n'),
 (775,'XzpbdjBdMTI5NDQwODc4NC0zNzgzNg==\n'),
 (776,'XzpbdjBdMTI4MDIzMTc4NC0xNjI5MA==\n'),
 (777,'XzpbdjBdLTEyOTc4MjczNDItNTYyODg=\n'),
 (778,'XzpbdjBdNDA5Njg1NjcwLTIxNTQz'),
 (779,'XzpbdjBdOTY1ODA4ODc3LTI1NjM2'),
 (780,'XzpbdjBdLTQ1Mjk5MDMwNS02NDYxNg==\n'),
 (781,'XzpbdjBdLTc5NTcwODYwMS0yMjQ0OA==\n'),
 (782,'XzpbdjBdLTI1MjI2ODQ0Ny01MTc0Mg==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (783,'XzpbdjBdLTIwOTcyNzU4NzItMTQzMDE=\n'),
 (784,'XzpbdjBdLTE5MzUyNDY0MzctNDY3Mzk=\n'),
 (785,'XzpbdjBdLTE5MzUyNDY0MzktNDY3Mzk=\n'),
 (786,'XzpbdjBdLTE5MzUyNDY0MzQtNDY3Mzk=\n'),
 (787,'XzpbdjBdLTE5MzUyNDY0NDAtNDY3Mzk=\n'),
 (788,'XzpbdjBdLTQzMzMxNzE1OS0zODY4'),
 (789,'XzpbdjBdOTQ4MDQ2ODQtMzY0MjM=\n'),
 (790,'XzpbdjBdMTA3MjU0MTY4MS0zNzEzOQ==\n'),
 (791,'XzpbdjBdMjA4NDQyODg0Mi02MjY0MQ==\n'),
 (792,'XzpbdjBdMTgxMjEwMjQwOS0yNjE2MQ==\n'),
 (793,'XzpbdjBdMTc2NjAyODg2OS00OTU4Mg==\n'),
 (794,'XzpbdjBdLTE5MjYwMDAxNTctMjU5NTM=\n'),
 (795,'XzpbdjBdLTIxMTUyMTIwODktMzA5Njk=\n'),
 (796,'XzpbdjBdOTM4MDg2ODM2LTM3NTE3'),
 (797,'XzpbdjBdODEyNTc5MTQ4LTIwMDE2'),
 (798,'XzpbdjBdMTE3MTQxNjMyNS0zOTM0Mw==\n'),
 (799,'XzpbdjBdLTE5OTczNTI5NzItNTE1MTQ=\n'),
 (800,'XzpbdjBdLTE1MDEyNTY2ODEtMTIzMDc=\n'),
 (801,'XzpbdjBdMTgwNDc2MjkxMC0zNzU1OQ==\n'),
 (802,'XzpbdjBdLTcxNTAyNDg4LTIwOTE0'),
 (803,'XzpbdjBdLTEwNjY5OTc3OS01OTQzOQ==\n'),
 (804,'XzpbdjBdMTgwNjg2MTg4OS0zNTkyMg==\n'),
 (805,'XzpbdjBdMTQ1NDkzNjk3My0zMTM2MA==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (806,'XzpbdjBdLTE4OTQ3MTQwMzUtNTc0OA==\n'),
 (807,'XzpbdjBdMTQ3NTU3OTEyMy0zOTk0OA==\n'),
 (808,'XzpbdjBdOTE5NjQwOTgyLTQxNjkx'),
 (809,'XzpbdjBdMzI5MDY3NzUyLTIwMzUx'),
 (810,'XzpbdjBdMzU2OTMyMDQ0LTYxNTY0'),
 (811,'XzpbdjBdLTE2ODk3MTkzOTUtMjA4NQ==\n'),
 (812,'XzpbdjBdMzg0OTQyNDM1LTE4NzAz'),
 (813,'XzpbdjBdLTE5NjE1NDIzNTctMTUzMzc=\n'),
 (814,'XzpbdjBdLTg2MjUxMzg1Ny0xMDYzNg==\n'),
 (815,'XzpbdjBdNzcxMTc2MDM4LTUwODc5'),
 (816,'XzpbdjBdLTExMzczMDI4NzQtNTQ0MTg=\n'),
 (817,'XzpbdjBdMTIzODYzNjc2NC0xMTU4Ng==\n'),
 (818,'XzpbdjBdMTA0NTYzMjUzNS0xMDM3MQ==\n'),
 (819,'XzpbdjBdLTE1ODk4MjExNTAtNTI0MTE=\n'),
 (820,'XzpbdjBdOTAyNzYxMzkzLTMzNTE3'),
 (821,'XzpbdjBdMTYzMDIxOTAwNC0yNzY5Nw==\n'),
 (822,'XzpbdjBdLTE4MDE5NDM2NzktMjEyNzk=\n'),
 (823,'XzpbdjBdODgyMzMwMTk3LTEzMjIz'),
 (824,'XzpbdjBdLTEwNTI3NzAyNzQtMTk1NjA=\n'),
 (825,'XzpbdjBdLTE2OTQxMDU0NzYtMTkwOTk=\n'),
 (826,'XzpbdjBdMzQyODY4NTc1LTQ1MzAx'),
 (827,'XzpbdjBdLTU2ODAxNDExOS0zNTE3MA==\n'),
 (828,'XzpbdjBdLTEyMzY3ODY5MjAtMTczMjc=\n'),
 (829,'XzpbdjBdLTgwNTAwNDEwMi0yMTY5MQ==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (830,'XzpbdjBdLTIwMjg2Mjc0MDctNTY3Njc=\n'),
 (831,'XzpbdjBdLTE1ODA1MDM1OTMtMzY1ODA=\n'),
 (832,'XzpbdjBdLTEzNzI4MDE0MjAtNDU3Nw==\n'),
 (833,'XzpbdjBdODcyMzIxNDI5LTMzMzc1'),
 (834,'XzpbdjBdLTM5NjEzNzY2NC02MDIzNA==\n'),
 (835,'XzpbdjBdLTExMDE4NTg2MjgtMjUxMDI=\n'),
 (836,'XzpbdjBdLTE0MjQ4ODg1NjktMjg2MDU=\n'),
 (837,'XzpbdjBdMTE4MTI2Nzc0Ny0yMzg4'),
 (838,'XzpbdjBdLTE4MTA2MjY5NDctMjUwODg=\n'),
 (839,'XzpbdjBdMTU2NDc5NTI2MC0yMjY3MA==\n'),
 (840,'XzpbdjBdMTA2NzQ0MTUzMC01MDkxMA==\n'),
 (841,'XzpbdjBdLTY4MDQwNzc3MC01NzkyMg==\n'),
 (842,'XzpbdjBdMTM4Mjk1OTQ2MC02MTA0OQ==\n'),
 (843,'XzpbdjBdLTQ3ODk2NTg4My0yODMyNw==\n'),
 (844,'XzpbdjBdLTU3MTUzMzMzOC02MDc0OA==\n'),
 (845,'XzpbdjBdOTI5NzU0ODk0LTI5NTQz'),
 (846,'XzpbdjBdLTMyODkyMDMyMi0xOTQ1MQ==\n'),
 (847,'XzpbdjBdLTEzODAzMzQ5NDUtMjQxOQ==\n'),
 (848,'XzpbdjBdNDE2NzgyMDU3LTQ5MjQx'),
 (849,'XzpbdjBdLTM3MDc3ODM3Mi02MTI4OA==\n'),
 (850,'XzpbdjBdLTIwMDk3NzIyMTctNjM4MTk=\n'),
 (851,'XzpbdjBdMzU4MDk3Mjk3LTI3NzQx'),
 (852,'XzpbdjBdLTEzOTExMTk1MzItNDMyNDM=\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (853,'XzpbdjBdLTEwNzAxNzAzMDQtMjAwOTU=\n'),
 (854,'XzpbdjBdNjI3MzE0NTM5LTU2NTc0'),
 (855,'XzpbdjBdNTA0Njc3MjkxLTYyODgw'),
 (856,'XzpbdjBdMTEyMTk4Nzg0MC01MTMxNw==\n'),
 (857,'XzpbdjBdLTcwNzE4Njc0Ny0yMDgxNw==\n'),
 (858,'XzpbdjBdMjU3OTAzMTU1LTE5ODg2'),
 (859,'XzpbdjBdLTgyNjkxOTUxMy0zMTcwMQ==\n'),
 (860,'XzpbdjBdMTk1MzYxMjEwOC0yMTEy'),
 (861,'XzpbdjBdLTE0ODYzNzE3ODMtMzA1Nzk=\n'),
 (862,'XzpbdjBdLTE0NDQzNzM0OTktMTE4Mw==\n'),
 (863,'XzpbdjBdNjM4MjU3NzE5LTM0MTk0'),
 (864,'XzpbdjBdLTExOTAyMjI0NDAtNTkxMTI=\n'),
 (865,'XzpbdjBdLTg1NzgxNjQwLTM4MjM0'),
 (866,'XzpbdjBdLTQxNzkxNDU2NC02NTI5OQ==\n'),
 (867,'XzpbdjBdMTk2Njc0ODc2Ny01NzY2'),
 (868,'XzpbdjBdMTE5MjA3NDcyOS0yMDI4'),
 (869,'XzpbdjBdNTkwOTE4MzA3LTIyNjY=\n'),
 (870,'XzpbdjBdLTg0MTg4Mzk4Ni0yOTQwNA==\n'),
 (871,'XzpbdjBdMTIyNzI4Njk2MC0zMzQyMg==\n'),
 (872,'XzpbdjBdLTE4Mjg1Nzg0NzMtMjA4ODY=\n'),
 (873,'XzpbdjBdLTUwNjI0NTA0Mi01ODM5Nw==\n'),
 (874,'XzpbdjBdLTE4NjcxOTk5MzctNTkwMzc=\n'),
 (875,'XzpbdjBdLTEyMzg4NjA4OC0yOTY1NQ==\n'),
 (876,'XzpbdjBdLTkzMjk2MDkxOS01MTY2NQ==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (877,'XzpbdjBdLTY1NzU4MTgyLTI1MDcx'),
 (878,'XzpbdjBdNjEwNzQ0NDgtNjc1NA==\n'),
 (879,'XzpbdjBdLTIwNzQxOTk0NzUtMjYzNTU=\n'),
 (880,'XzpbdjBdLTE3MDgxMjkyNTctMjM5MDM=\n'),
 (881,'XzpbdjBdLTEyMDczODg0MTktNTg1NzQ=\n'),
 (882,'XzpbdjBdLTkxMTQ3MDUtNDU1Ng==\n'),
 (883,'XzpbdjBdNTI2MzIwMzM3LTI0NTM5'),
 (884,'XzpbdjBdLTk2ODEyMTIzMC0zNTE0Nw==\n'),
 (885,'XzpbdjBdLTIwNDA1MjkyNzYtNDQ2NjU=\n'),
 (886,'XzpbdjBdLTE4NjA2ODgwMDQtMTExMDg=\n'),
 (887,'XzpbdjBdNzAzOTcxMTU3LTM5Mjc2'),
 (888,'XzpbdjBdODUyOTQzNjE1LTMyOTM5'),
 (889,'XzpbdjBdMjUyNjg1MDMyLTI3ODM5'),
 (890,'XzpbdjBdOTUxNjM5Nzg0LTQ2ODI2'),
 (891,'XzpbdjBdODQ3NDcyMDAxLTEzODQ2'),
 (892,'XzpbdjBdLTQxMzQ4NjE5OS01NjMwNA==\n'),
 (893,'XzpbdjBdLTE0NDE5ODk2LTg3NA==\n'),
 (894,'XzpbdjBdNzE5NTczNjU5LTU3MDM1'),
 (895,'XzpbdjBdLTE3NDgwMzM0MC02MDQwNA==\n'),
 (896,'XzpbdjBdLTE2Njk0MjUzMjktMTAxMw==\n'),
 (897,'XzpbdjBdLTE4OTQxNDA2MTktMjgxNjY=\n'),
 (898,'XzpbdjBdLTE5MzQ1MDQ4MjUtNTQ4NzI=\n'),
 (899,'XzpbdjBdNDc1MDgzMjEwLTYxNTU4'),
 (900,'XzpbdjBdMTk3NTY5Njk1MS01NTU0NQ==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (901,'XzpbdjBdMTYzODQzMTIwLTExNDQz'),
 (902,'XzpbdjBdLTE1NjY3Nzk1NTEtNDMxMjQ=\n'),
 (903,'XzpbdjBdMTU5NDIxNzQxNi00NDM4MA==\n'),
 (904,'XzpbdjBdLTE4ODE4NjExNjAtNDM3MA==\n'),
 (905,'XzpbdjBdMTA4NTQwMDEwNi01MzIxMw==\n'),
 (906,'XzpbdjBdLTE2NDcwOTMxNDQtNDI2Mjc=\n'),
 (907,'XzpbdjBdMjAxMDQ4OTAyNC02MzcxNg==\n'),
 (908,'XzpbdjBdMTU1OTE2Mzg3Mi0xNDMwMQ==\n'),
 (909,'XzpbdjBdLTE3OTc2NzAxOTMtMjg4OQ==\n'),
 (910,'XzpbdjBdMTAzNzc4ODQyMC0zNzc3Nw==\n'),
 (911,'XzpbdjBdLTIxMTc0NDE5NTYtMjUwMTE=\n'),
 (912,'XzpbdjBdLTEwNzMyMzExMzYtMjY4NjQ=\n'),
 (913,'XzpbdjBdLTIwMzY3MjMyMDItNDY1OTM=\n'),
 (914,'XzpbdjBdLTEwNzAwMTAyNTAtMTk0MTE=\n'),
 (915,'XzpbdjBdLTE0MDAxNDgwMDktNTE4NTM=\n'),
 (916,'XzpbdjBdOTc3NDg0NjM0LTI0OTkx'),
 (917,'XzpbdjBdLTM2NDM2MjU3LTYwMzQw'),
 (918,'XzpbdjBdLTE4NjUxMjEwMjktMzAxOTM=\n'),
 (919,'XzpbdjBdNDI3Mjk0ODE5LTYzOTY3'),
 (920,'XzpbdjBdLTE3MjA4NjE5OTMtNDkyMg==\n'),
 (921,'XzpbdjBdNTQ5MTI5NjU1LTU0ODgy'),
 (922,'XzpbdjBdMTE5Mjc2NTExMi01MjIxMg==\n'),
 (923,'XzpbdjBdMzYwNDM0MTk3LTI3ODYw');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (924,'XzpbdjBdLTE5NzQwNjAwMjgtNzEwOA==\n'),
 (925,'XzpbdjBdLTg2ODk0MjI0Ny0xMTUy'),
 (926,'XzpbdjBdODk0OTA4MDQ1LTMzNTI4'),
 (927,'XzpbdjBdLTIwNDU2NjA5NDQtNDI3ODE=\n'),
 (928,'XzpbdjBdNjM1MjY2NDEzLTM1Nzk2'),
 (929,'XzpbdjBdLTIxODkwMzI4Ni00NjY5Mg==\n'),
 (930,'XzpbdjBdMTAzMzg2ODc3LTM1MDE1'),
 (931,'XzpbdjBdLTEzODg4NjEzNjEtNjQ3NjY=\n'),
 (932,'XzpbdjBdMTg4MDg0NjYzOC0yMzg2OA==\n'),
 (933,'XzpbdjBdLTUwMTM4MzUxMi0xMDI0Nw==\n'),
 (934,'XzpbdjBdLTExNjQ0Nzg4MTctMTkyNTk=\n'),
 (935,'XzpbdjBdNTY3NTc0MTkzLTI0MTA2'),
 (936,'XzpbdjBdLTE0OTgwMTE2OTUtNTk1MDc=\n'),
 (937,'XzpbdjBdMTYzMDQzMDkxNy04ODkx'),
 (938,'XzpbdjBdMTQ1ODI3NDIzLTM3MDI0'),
 (939,'XzpbdjBdNzAwNTIyNTMyLTI3ODI5'),
 (940,'XzpbdjBdLTEzMzI5NTYxMjctMTYyNDc=\n'),
 (941,'XzpbdjBdMjAzMTE0OTQ4Ni00MjY0'),
 (942,'XzpbdjBdMzU5MDYzMzAtNTc0MzM=\n'),
 (943,'XzpbdjBdLTEzNzgzMDgwMjUtMjE5NDg=\n'),
 (944,'XzpbdjBdMTM3NzQxODc5MC00NzE3Nw==\n'),
 (945,'XzpbdjBdLTIzNjg4NTU1My0zNTg3'),
 (946,'XzpbdjBdMjEwMzAzNzQ3NS00ODc2'),
 (947,'XzpbdjBdMzIwNDUyMzk3LTI4MDI0');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (948,'XzpbdjBdODU1OTk4MDctMzc4MDE=\n'),
 (949,'XzpbdjBdLTYyNTAzNzI5My0yNjM5OA==\n'),
 (950,'XzpbdjBdMjEyMDU0MzkwNS0yODI2Ng==\n'),
 (951,'XzpbdjBdNTk4MDExOTA1LTU0Njgy'),
 (952,'XzpbdjBdLTIyNzU3NDEyMS01Mzk5OQ==\n'),
 (953,'XzpbdjBdMTk4NTY2Mjk2MS0yOTU4Ng==\n'),
 (954,'XzpbdjBdMTI2NzI3OTQ1NS0yMjYzMg==\n'),
 (955,'XzpbdjBdLTE0NTY2NTEyLTI1NzI4'),
 (956,'XzpbdjBdMTUyNTk2MzY0OC0yMDAwNQ==\n'),
 (957,'XzpbdjBdLTI5MTA4NjIzMC0zNDc1Ng==\n'),
 (958,'XzpbdjBdLTEzMTIzMDE3MjctMjM4MTA=\n'),
 (959,'XzpbdjBdNzY3MTE5NTYwLTI5ODc=\n'),
 (960,'XzpbdjBdLTEwODAyMjM3MTAtNzM0'),
 (961,'XzpbdjBdLTIwNjc2MDAzMTUtMjU4MzE=\n'),
 (962,'XzpbdjBdMTczMTcyNTg4My0zNDY2OQ==\n'),
 (963,'XzpbdjBdLTEyMTc5OTk3MTUtNDc2OTM=\n'),
 (964,'XzpbdjBdLTM4NTE0MDI1MC02NTA1Mw==\n'),
 (965,'XzpbdjBdNTg5MDE1MDcyLTUxMDAy'),
 (966,'XzpbdjBdMTEwOTM1MzEyNC0zNDMzOA==\n'),
 (967,'XzpbdjBdLTg0MTY0NzcxLTM3NzUw'),
 (968,'XzpbdjBdLTE2MjIwNDcwNjMtMTgw'),
 (969,'XzpbdjBdMTMyNDM0MTg0NC01MjMyMA==\n'),
 (970,'XzpbdjBdLTEwNDcxODk5OTMtMTIwNzk=\n'),
 (971,'XzpbdjBdMTY3OTgxNzM5OC02MTM4NQ==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (972,'XzpbdjBdLTkxMDk0NjgzNi02Mzg1Nw==\n'),
 (973,'XzpbdjBdLTIwMTYyNDk2NDMtNjM1NDk=\n'),
 (974,'XzpbdjBdMjcxMjA4ODQ4LTUzMTU1'),
 (975,'XzpbdjBdMTc4NjY2OTk1Ny00NjU4NQ==\n'),
 (976,'XzpbdjBdLTE0OTk0OTI0ODAtMjIwNQ==\n'),
 (977,'XzpbdjBdLTIyNDY0OTA0My01NjQ0OQ==\n'),
 (978,'XzpbdjBdMzkwMDczMTU5LTM5MTEz'),
 (979,'XzpbdjBdMTY3MTE3NTQ2MC0xMDk5'),
 (980,'XzpbdjBdMzk3NzA4MjQ4LTM0MzI2'),
 (981,'XzpbdjBdLTE2MDEwNjc2NDEtNDYwODk=\n'),
 (982,'XzpbdjBdMTkwOTIwOTE5Ny0xNzAxOQ==\n'),
 (983,'XzpbdjBdNTYyNzE3NzU1LTQxNzA3'),
 (984,'XzpbdjBdMjA0NjkzNzEyOS0yNTc0NQ==\n'),
 (985,'XzpbdjBdLTc4NzkxMjMwNS0zMTc0NA==\n'),
 (986,'XzpbdjBdMTk3MzA3MzUwNi01MDI1MA==\n'),
 (987,'XzpbdjBdLTk4Mzg3MjQ2LTE1ODkz'),
 (988,'XzpbdjBdLTExMjA0NTc5ODItNTc4Njc=\n'),
 (989,'XzpbdjBdMzYzOTE1MjA0LTI2NjY1'),
 (990,'XzpbdjBdLTY0MDE3MjQ0Mi02MjkxOA==\n'),
 (991,'XzpbdjBdMTM2Mjg3NjMxMi0zMTIxOA==\n'),
 (992,'XzpbdjBdMjA5MjUwNTI1Ni0zMDQy'),
 (993,'XzpbdjBdLTE4NTEzNTMzMzYtNjAzODI=\n'),
 (994,'XzpbdjBdLTE0NjI1NzcyOTEtMzY4ODQ=\n'),
 (995,'XzpbdjBdMjA1NDg5MjY0LTE1MDIw');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (996,'XzpbdjBdLTYwMDEwMjIwNy0xOTE0OA==\n'),
 (997,'XzpbdjBdMjA1NzIxNDI0MS01NjIyMw==\n'),
 (998,'XzpbdjBdLTI2NDI4MDMyMi0zMzAxNw==\n'),
 (999,'XzpbdjBdLTQ1MTM4NDgzMi00NzU5OA==\n'),
 (1000,'XzpbdjBdLTUwNTk5MDE2LTU1MDA=\n'),
 (1001,'XzpbdjBdLTE5NzI2ODI3MjMtMTYyOTA=\n'),
 (1002,'XzpbdjBdLTg5NTQ5OTM3NS0zMTU5Nw==\n'),
 (1003,'XzpbdjBdNjg4NTQzNi02NDU3OA==\n'),
 (1004,'XzpbdjBdMTUzMTI0Mzg0MS03ODM4'),
 (1005,'XzpbdjBdMTU5NjM4NTYzMi0zNzM3OQ==\n'),
 (1006,'XzpbdjBdLTIwOTM3OTcwNzUtMTQ5NTQ=\n'),
 (1007,'XzpbdjBdMTQyNTE2MjM1Mi02MjgyNw==\n'),
 (1008,'XzpbdjBdMTM3NTA5NDY3NS02MDIxMw==\n'),
 (1009,'XzpbdjBdNjU2MDU0Mjc4LTM4ODI3'),
 (1010,'XzpbdjBdMTYwMjQ4NjgzLTk5NzM=\n'),
 (1011,'XzpbdjBdLTk4OTIzNzg5Ni0zMDcwMw==\n'),
 (1012,'XzpbdjBdNjQ2ODkxMDItMjg2Njk=\n'),
 (1013,'XzpbdjBdLTIxMDg0MzA0ODUtMzQxOTk=\n'),
 (1014,'XzpbdjBdMTA5OTA5MzQ0MC01NDYxNA==\n'),
 (1015,'XzpbdjBdMTIyMjI1NjQ2OC0yODE5'),
 (1016,'XzpbdjBdMTU1NzY0ODIwMS00NTY5OA==\n'),
 (1017,'XzpbdjBdLTE2OTgzMDMyODEtMzE0ODk=\n'),
 (1018,'XzpbdjBdLTEwNDg2MjA5OTQtNTAwMw==\n');
INSERT INTO `pclsidmapper` (`mid`,`clsid`) VALUES 
 (1019,'XzpbdjBdLTU4ODU4MTA0OS0zNzI5Nw==\n'),
 (1020,'XzpbdjBdLTQ3NTExNjk5Mi01MTQ1MQ==\n');
/*!40000 ALTER TABLE `pclsidmapper` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pdecisionstatus`
--

DROP TABLE IF EXISTS `pdecisionstatus`;
CREATE TABLE `pdecisionstatus` (
  `caseid` int(11) NOT NULL default '0',
  `procid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `decisionid` int(11) NOT NULL default '0',
  `mstate` int(11) NOT NULL default '0',
  `mdated` datetime default NULL,
  PRIMARY KEY  (`caseid`,`procid`,`transid`,`decisionid`),
  KEY `pdecisionstatus_idx1` (`caseid`,`procid`,`transid`),
  KEY `pdecisionstatus_idx2` (`caseid`,`procid`,`transid`,`decisionid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pdecisionstatus`
--

/*!40000 ALTER TABLE `pdecisionstatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `pdecisionstatus` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pdeliv`
--

DROP TABLE IF EXISTS `pdeliv`;
CREATE TABLE `pdeliv` (
  `delivid` int(11) NOT NULL default '0',
  `modelid` int(11) NOT NULL default '0',
  `procidsrc` int(11) NOT NULL default '0',
  `procidtrg` int(11) NOT NULL default '0',
  `pdattribid` int(11) NOT NULL default '0',
  `delivname` varchar(255) default NULL,
  `lateral` int(11) default NULL,
  `lateraldirection` int(11) default NULL,
  `doublesign` int(11) default NULL,
  `delivstableid` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`delivid`),
  KEY `pdeliv_idx1` (`procidsrc`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pdeliv`
--

/*!40000 ALTER TABLE `pdeliv` DISABLE KEYS */;
/*!40000 ALTER TABLE `pdeliv` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pdelivlateralstate`
--

DROP TABLE IF EXISTS `pdelivlateralstate`;
CREATE TABLE `pdelivlateralstate` (
  `procid` int(11) NOT NULL default '0',
  `caseid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `delivid` int(11) NOT NULL default '0',
  `openclose` int(11) NOT NULL default '0',
  `timestmp` datetime default NULL,
  PRIMARY KEY  (`procid`,`caseid`,`transid`,`delivid`),
  KEY `pdelivlateralstate_idx1` (`procid`,`caseid`,`transid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pdelivlateralstate`
--

/*!40000 ALTER TABLE `pdelivlateralstate` DISABLE KEYS */;
/*!40000 ALTER TABLE `pdelivlateralstate` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pdelivstable`
--

DROP TABLE IF EXISTS `pdelivstable`;
CREATE TABLE `pdelivstable` (
  `DELIVSTABLEID` int(11) NOT NULL,
  `DELIVSTABLEDESC` varchar(35) default NULL,
  PRIMARY KEY  (`DELIVSTABLEID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pdelivstable`
--

/*!40000 ALTER TABLE `pdelivstable` DISABLE KEYS */;
/*!40000 ALTER TABLE `pdelivstable` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pdelivstatus`
--

DROP TABLE IF EXISTS `pdelivstatus`;
CREATE TABLE `pdelivstatus` (
  `caseid` int(11) NOT NULL default '0',
  `procid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `delivid` int(11) NOT NULL default '0',
  `mstate` int(11) NOT NULL default '0',
  `mdated` datetime default NULL,
  PRIMARY KEY  (`caseid`,`procid`,`transid`,`delivid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pdelivstatus`
--

/*!40000 ALTER TABLE `pdelivstatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `pdelivstatus` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pdistrib`
--

DROP TABLE IF EXISTS `pdistrib`;
CREATE TABLE `pdistrib` (
  `modelid` int(11) NOT NULL default '0',
  `wkgid` int(11) NOT NULL default '0',
  `attribdefid` int(11) NOT NULL default '0',
  `mop` int(11) NOT NULL default '0',
  `mdata` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`modelid`,`wkgid`,`attribdefid`),
  KEY `pdistrib_idx1` (`modelid`,`wkgid`,`attribdefid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pdistrib`
--

/*!40000 ALTER TABLE `pdistrib` DISABLE KEYS */;
/*!40000 ALTER TABLE `pdistrib` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pdistribmap`
--

DROP TABLE IF EXISTS `pdistribmap`;
CREATE TABLE `pdistribmap` (
  `modelid` int(11) NOT NULL default '0',
  `pdattribid` int(11) NOT NULL default '0',
  `attribdefid` int(11) NOT NULL default '0',
  `mdata` varchar(255) NOT NULL default '',
  `mlop` int(11) NOT NULL default '0',
  PRIMARY KEY  (`modelid`,`pdattribid`,`attribdefid`),
  KEY `pdistribmap_idx1` (`modelid`,`pdattribid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pdistribmap`
--

/*!40000 ALTER TABLE `pdistribmap` DISABLE KEYS */;
/*!40000 ALTER TABLE `pdistribmap` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pdoublesign`
--

DROP TABLE IF EXISTS `pdoublesign`;
CREATE TABLE `pdoublesign` (
  `procid` int(11) NOT NULL default '0',
  `caseid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `delivid` int(11) NOT NULL default '0',
  `signempl1` int(11) default NULL,
  `signdate1` int(11) default NULL,
  `signempl2` int(11) default NULL,
  `signdate2` int(11) default NULL,
  `signstate` int(11) default NULL,
  PRIMARY KEY  (`procid`,`caseid`,`transid`),
  KEY `pdoublesign_idx1` (`caseid`,`procid`,`transid`,`signstate`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pdoublesign`
--

/*!40000 ALTER TABLE `pdoublesign` DISABLE KEYS */;
/*!40000 ALTER TABLE `pdoublesign` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pemployee`
--

DROP TABLE IF EXISTS `pemployee`;
CREATE TABLE `pemployee` (
  `emplid` int(11) NOT NULL default '0',
  `employeeTitleID` int(11) default '0',
  `login` varchar(32) NOT NULL default '',
  `roleid` int(11) NOT NULL default '0',
  `fname` varchar(128) default NULL,
  `lname` varchar(128) default NULL,
  `flagAsynchronous` int(11) default '0',
  `email` varchar(255) default NULL,
  `phone` varchar(20) default NULL,
  PRIMARY KEY  (`emplid`),
  UNIQUE KEY `pemployee_idx1` (`login`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pemployee`
--

/*!40000 ALTER TABLE `pemployee` DISABLE KEYS */;
INSERT INTO `pemployee` (`emplid`,`employeeTitleID`,`login`,`roleid`,`fname`,`lname`,`flagAsynchronous`,`email`,`phone`) VALUES 
 (1,2,'admin',0,'admin','admin',0,'admin@test.com',''),
 (2,2,'SEPPEY',3,'Dominique','Seppey',0,'seppey@localhost',''),
 (3,2,'FOURNIER',3,'Stéphane','Fournier',0,'fournier@localhost','');
/*!40000 ALTER TABLE `pemployee` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pempmap`
--

DROP TABLE IF EXISTS `pempmap`;
CREATE TABLE `pempmap` (
  `wkgid` int(11) NOT NULL default '0',
  `login` varchar(32) NOT NULL default '',
  UNIQUE KEY `pempmap_idx1` (`wkgid`,`login`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pempmap`
--

/*!40000 ALTER TABLE `pempmap` DISABLE KEYS */;
INSERT INTO `pempmap` (`wkgid`,`login`) VALUES 
 (2,'admin'),
 (3,'admin'),
 (10,'admin'),
 (10,'gsens'),
 (19,'admin'),
 (19,'dcartillier'),
 (34,'admin'),
 (38,'admin'),
 (38,'grime'),
 (52,'admin'),
 (52,'grime'),
 (74,'admin'),
 (74,'gsens'),
 (76,'admin'),
 (76,'dcartillier'),
 (81,'admin'),
 (91,'admin'),
 (91,'vottinger'),
 (95,'admin'),
 (95,'vottinger'),
 (97,'admin'),
 (99,'admin'),
 (111,'admin'),
 (111,'client'),
 (113,'admin'),
 (114,'admin'),
 (115,'admin'),
 (116,'admin'),
 (117,'admin'),
 (141,'admin'),
 (141,'vottinger'),
 (142,'admin'),
 (142,'ebouchez'),
 (143,'admin'),
 (143,'gsens'),
 (144,'admin'),
 (144,'grime'),
 (145,'ebouchez'),
 (146,'admin'),
 (146,'dcartillier'),
 (151,'admin'),
 (152,'admin'),
 (153,'admin'),
 (154,''),
 (154,'admin'),
 (155,'admin'),
 (156,'admin'),
 (157,'admin'),
 (162,'admin'),
 (164,'ebouchez'),
 (164,'grime'),
 (169,'admin'),
 (169,'grime'),
 (170,'admin'),
 (171,'admin'),
 (171,'vottinger'),
 (172,'admin'),
 (172,'dcartillier'),
 (176,'admin'),
 (176,'dcartillier');
INSERT INTO `pempmap` (`wkgid`,`login`) VALUES 
 (177,'admin'),
 (179,'admin'),
 (179,'client'),
 (180,'admin'),
 (180,'client'),
 (184,'admin'),
 (192,'admin'),
 (193,'admin'),
 (206,'admin'),
 (206,'grime'),
 (220,'admin'),
 (221,'admin'),
 (222,'admin'),
 (223,'admin'),
 (224,'admin'),
 (226,'admin'),
 (230,'admin'),
 (238,'admin'),
 (240,'admin'),
 (241,'admin'),
 (246,'admin'),
 (247,'admin'),
 (248,'admin'),
 (272,'admin'),
 (275,'admin'),
 (276,'admin'),
 (280,'gsens'),
 (281,'grime'),
 (284,'admin'),
 (285,'admin'),
 (286,'admin'),
 (287,'admin'),
 (291,'admin'),
 (296,'admin'),
 (297,'admin'),
 (298,'admin'),
 (316,'gsens'),
 (317,'grime'),
 (338,'admin'),
 (340,'admin'),
 (342,'admin'),
 (350,'admin'),
 (355,'admin'),
 (356,'admin'),
 (362,'admin'),
 (396,'admin'),
 (397,'admin'),
 (398,'admin'),
 (399,'admin'),
 (400,'admin'),
 (402,'admin'),
 (404,'admin'),
 (405,'admin'),
 (411,'admin'),
 (424,'ebouchez'),
 (428,'admin'),
 (432,'ebouchez'),
 (434,'admin'),
 (439,'admin'),
 (446,'admin');
INSERT INTO `pempmap` (`wkgid`,`login`) VALUES 
 (448,'admin'),
 (450,'admin'),
 (458,'admin'),
 (459,'admin'),
 (460,'admin'),
 (465,'admin'),
 (509,'admin'),
 (512,'admin'),
 (569,'admin'),
 (606,'admin'),
 (608,'admin'),
 (609,'ebouchez'),
 (610,'dcartillier'),
 (627,'admin'),
 (629,'admin'),
 (631,'admin'),
 (651,'admin'),
 (654,'admin'),
 (655,'admin'),
 (657,'admin'),
 (666,'admin'),
 (792,'admin'),
 (793,'admin'),
 (798,'admin'),
 (799,'admin'),
 (805,'admin'),
 (838,'admin'),
 (844,'admin'),
 (847,'ebouchez'),
 (848,'ebouchez'),
 (849,'admin'),
 (850,'admin');
/*!40000 ALTER TABLE `pempmap` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pemppasswd`
--

DROP TABLE IF EXISTS `pemppasswd`;
CREATE TABLE `pemppasswd` (
  `emplid` int(11) NOT NULL default '0',
  `passwd` varchar(80) NOT NULL default '',
  PRIMARY KEY  (`emplid`),
  KEY `pemppasswd_idx1` (`passwd`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pemppasswd`
--

/*!40000 ALTER TABLE `pemppasswd` DISABLE KEYS */;
INSERT INTO `pemppasswd` (`emplid`,`passwd`) VALUES 
 (0,'3dba7f2d2578ffb4bd657af94b1add80'),
 (1,'f71dbe52628a3f83a77ab494817525c6'),
 (3,'f71dbe52628a3f83a77ab494817525c6'),
 (2,'3dba7f2d2578ffb4bd657af94b1add80');
/*!40000 ALTER TABLE `pemppasswd` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pemproles`
--

DROP TABLE IF EXISTS `pemproles`;
CREATE TABLE `pemproles` (
  `roleid` int(11) NOT NULL default '0',
  `rolename` varchar(255) default NULL,
  PRIMARY KEY  (`roleid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pemproles`
--

/*!40000 ALTER TABLE `pemproles` DISABLE KEYS */;
INSERT INTO `pemproles` (`roleid`,`rolename`) VALUES 
 (0,'Administrateur du systÃ¨me'),
 (1,'Administrateur de groupe'),
 (2,'Chef de groupe'),
 (3,'EmployÃ©');
/*!40000 ALTER TABLE `pemproles` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pexec`
--

DROP TABLE IF EXISTS `pexec`;
CREATE TABLE `pexec` (
  `execid` int(11) NOT NULL default '0',
  `prgid` int(11) NOT NULL default '0',
  `exectype` int(11) NOT NULL default '0',
  `execname` varchar(255) default NULL,
  `execpath` varchar(255) default NULL,
  PRIMARY KEY  (`execid`,`prgid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pexec`
--

/*!40000 ALTER TABLE `pexec` DISABLE KEYS */;
/*!40000 ALTER TABLE `pexec` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pidentity`
--

DROP TABLE IF EXISTS `pidentity`;
CREATE TABLE `pidentity` (
  `idname` varchar(32) NOT NULL default '',
  `idv` int(11) NOT NULL default '0',
  PRIMARY KEY  (`idname`),
  KEY `pidentity_idx1` (`idv`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pidentity`
--

/*!40000 ALTER TABLE `pidentity` DISABLE KEYS */;
INSERT INTO `pidentity` (`idname`,`idv`) VALUES 
 ('PTRANS',192),
 ('PCASE',170),
 ('PATTRIB',177),
 ('PCLSIDMAPPER',1020),
 ('PSCRDATAGROUP',1),
 ('PSCRDATAEL',1);
/*!40000 ALTER TABLE `pidentity` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pinfostatus`
--

DROP TABLE IF EXISTS `pinfostatus`;
CREATE TABLE `pinfostatus` (
  `caseid` int(11) NOT NULL default '0',
  `procid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `delivid` int(11) NOT NULL default '0',
  `infoid` int(11) NOT NULL default '0',
  `mstate` int(11) NOT NULL default '0',
  `mdated` datetime default NULL,
  PRIMARY KEY  (`caseid`,`procid`,`transid`,`delivid`,`infoid`),
  KEY `pinfostatus_idx1` (`caseid`,`procid`,`transid`,`delivid`),
  KEY `pinfostatus_idx2` (`caseid`,`procid`,`transid`,`delivid`,`infoid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pinfostatus`
--

/*!40000 ALTER TABLE `pinfostatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `pinfostatus` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pinput`
--

DROP TABLE IF EXISTS `pinput`;
CREATE TABLE `pinput` (
  `modelid` int(11) NOT NULL default '0',
  `pdattribid` int(11) NOT NULL default '0',
  `attribdefid` int(11) NOT NULL default '0',
  `mdefval` varchar(255) default NULL,
  `mflag` int(11) NOT NULL default '0',
  `constraintid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`modelid`,`pdattribid`,`attribdefid`),
  KEY `pinput_idx1` (`modelid`,`pdattribid`,`attribdefid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pinput`
--

/*!40000 ALTER TABLE `pinput` DISABLE KEYS */;
INSERT INTO `pinput` (`modelid`,`pdattribid`,`attribdefid`,`mdefval`,`mflag`,`constraintid`) VALUES 
 (1,-1,-1,'',-1,-1),
 (2,-1,-1,'',-1,-1);
/*!40000 ALTER TABLE `pinput` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pinputdata`
--

DROP TABLE IF EXISTS `pinputdata`;
CREATE TABLE `pinputdata` (
  `modelid` int(11) NOT NULL default '0',
  `pdattribid` int(11) NOT NULL default '0',
  `attribdefid` int(11) NOT NULL default '0',
  `caseid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `mval` varchar(255) default NULL,
  `mdate` datetime default NULL,
  KEY `pinputdata_idx1` (`caseid`,`transid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pinputdata`
--

/*!40000 ALTER TABLE `pinputdata` DISABLE KEYS */;
INSERT INTO `pinputdata` (`modelid`,`pdattribid`,`attribdefid`,`caseid`,`transid`,`mval`,`mdate`) VALUES 
 (1,4,330301441,2,2,'gaya lala','2002-09-04 13:24:17'),
 (1,4,330301441,3,3,'gaya','2002-09-04 13:34:29'),
 (1,4,330301441,4,4,'gaya','2002-09-04 13:35:23'),
 (1,4,330301441,5,5,'gaya e','2002-09-04 13:36:44'),
 (1,4,330301441,5,5,'gaya e','2002-09-04 13:38:18'),
 (1,724,332922881,9,9,'CHF','2002-09-04 17:09:30'),
 (1,724,332922881,9,9,'CHF','2002-09-04 17:09:30'),
 (1,724,335544321,9,9,'Europe','2002-09-04 17:09:30'),
 (1,724,335544321,9,9,'Europe','2002-09-04 17:09:30'),
 (1,724,332922881,9,9,'CHF','2002-09-04 17:09:35'),
 (1,724,332922881,9,9,'CHF','2002-09-04 17:09:35'),
 (1,724,335544321,9,9,'Europe','2002-09-04 17:09:35'),
 (1,724,335544321,9,9,'Europe','2002-09-04 17:09:35'),
 (1,724,332922881,10,10,'CHF','2002-09-04 17:21:14'),
 (1,724,332922881,10,10,'CHF','2002-09-04 17:21:14'),
 (1,724,335544321,10,10,'Asie','2002-09-04 17:21:14'),
 (1,724,335544321,10,10,'Asie','2002-09-04 17:21:14'),
 (1,724,332922881,12,12,'CHF','2002-09-04 23:56:08');
INSERT INTO `pinputdata` (`modelid`,`pdattribid`,`attribdefid`,`caseid`,`transid`,`mval`,`mdate`) VALUES 
 (1,724,335544321,12,12,'Europe','2002-09-04 23:56:08'),
 (1,724,332922881,17,17,'CHF','2002-09-05 02:14:39'),
 (1,724,335544321,17,17,'Europe','2002-09-05 02:14:39'),
 (1,724,335544321,18,18,'Asie','2002-09-05 02:31:46'),
 (1,9,332922881,18,18,'USD','2002-09-05 02:35:14'),
 (1,724,335544321,22,22,'Europe','2002-09-09 13:21:34'),
 (1,724,335544321,23,23,'Europe','2002-09-10 11:26:11'),
 (1,724,335544321,24,24,'Europe','2002-09-11 11:53:13'),
 (1,724,335544321,25,25,'Europe','2002-09-11 15:38:32'),
 (1,724,335544321,26,26,'Europe','2002-09-12 14:47:53'),
 (1,15,330301441,61,64,'externe','2002-10-17 15:50:01'),
 (1,724,335544321,62,66,'Europe','2002-10-24 12:04:54'),
 (1,69,330301441,64,68,'3000','2002-10-25 07:34:54'),
 (1,71,330301441,65,69,'2000','2002-10-25 07:44:10'),
 (1,69,330301441,66,70,'50','2002-10-25 07:45:23'),
 (1,6,330301441,66,70,'1000','2002-10-25 07:46:46'),
 (1,71,330301441,67,71,'2000','2002-10-25 16:32:22'),
 (1,69,330301441,68,73,'2000','2002-10-25 16:57:51');
INSERT INTO `pinputdata` (`modelid`,`pdattribid`,`attribdefid`,`caseid`,`transid`,`mval`,`mdate`) VALUES 
 (1,71,330301441,69,74,'3000','2002-10-25 17:02:41'),
 (1,57,330301441,70,75,'Nord','2002-10-30 19:54:10'),
 (1,57,330301441,71,76,'Sud','2002-10-30 20:00:25'),
 (1,57,330301441,72,77,'Sud','2002-10-30 20:12:43'),
 (1,57,330301441,72,77,'Sud','2002-10-30 20:12:47'),
 (1,57,330301441,72,77,'Sud','2002-10-30 20:12:52'),
 (1,724,335544321,80,85,'Europe','2002-11-19 11:55:15'),
 (1,69,330301441,81,86,'8000','2002-11-19 16:41:26'),
 (1,724,335544321,84,89,'Europe','2002-11-26 15:51:40'),
 (1,724,335544321,86,91,'Europe','2002-11-29 18:43:14'),
 (1,9,332922881,86,91,'EUR','2002-11-29 18:48:54'),
 (1,724,335544321,87,92,'Europe','2003-01-21 15:20:03'),
 (1,724,335544321,87,92,'Europe','2003-01-21 15:20:31'),
 (1,724,335544321,88,93,'Europe','2003-01-21 15:40:32'),
 (1,724,335544321,89,94,'Europe','2003-02-18 08:34:37'),
 (1,724,335544321,90,95,'Europe','2003-02-18 12:15:26'),
 (1,724,335544321,99,104,'Europe','2003-03-19 17:55:31'),
 (1,724,335544321,100,105,'Europe','2003-03-19 17:56:45');
INSERT INTO `pinputdata` (`modelid`,`pdattribid`,`attribdefid`,`caseid`,`transid`,`mval`,`mdate`) VALUES 
 (1,724,335544321,101,106,'Europe','2003-03-19 17:58:38'),
 (1,724,335544321,115,121,'Europe','2003-04-29 14:14:48'),
 (1,724,335544321,116,122,'Europe','2003-04-30 09:45:14'),
 (1,376,330301441,125,131,'Rue marchebeuf','2003-06-05 09:08:50'),
 (1,376,330301441,126,132,'rue de milan','2003-06-05 11:20:43'),
 (1,376,330301441,128,135,'sdfsdfsdfsd','2003-06-16 18:07:31'),
 (1,376,330301441,129,137,'Rue DUPHOT','2003-06-17 09:57:07'),
 (1,724,335544321,130,138,'Europe','2003-11-03 07:41:09'),
 (1,724,332922881,132,141,'Switzerland','2003-11-05 16:07:18'),
 (1,724,332922882,132,141,'CHF','2003-11-05 16:07:18'),
 (1,724,332922881,133,142,'Switzerland','2003-11-06 16:24:04'),
 (1,724,332922882,133,142,'CHF','2003-11-06 16:24:04'),
 (1,724,332922881,134,143,'Switzerland','2003-11-07 15:03:25'),
 (1,724,332922882,134,143,'CHF','2003-11-07 15:03:25'),
 (1,724,335544321,135,144,'Europe','2003-12-11 12:13:29'),
 (1,724,335544321,136,145,'Europe','2004-02-03 14:59:50');
INSERT INTO `pinputdata` (`modelid`,`pdattribid`,`attribdefid`,`caseid`,`transid`,`mval`,`mdate`) VALUES 
 (1,724,335544321,136,145,'Europe','2004-02-03 14:59:55'),
 (1,724,335544321,137,146,'Europe','2004-02-03 15:04:56'),
 (1,724,335544321,141,151,'Europe','2004-02-19 12:27:03');
/*!40000 ALTER TABLE `pinputdata` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pinputflag`
--

DROP TABLE IF EXISTS `pinputflag`;
CREATE TABLE `pinputflag` (
  `flagid` int(11) NOT NULL default '0',
  `flagtxt` varchar(32) default NULL,
  PRIMARY KEY  (`flagid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pinputflag`
--

/*!40000 ALTER TABLE `pinputflag` DISABLE KEYS */;
INSERT INTO `pinputflag` (`flagid`,`flagtxt`) VALUES 
 (1,'Non visible'),
 (2,'Visible'),
 (3,'Editable');
/*!40000 ALTER TABLE `pinputflag` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`plogicop`
--

DROP TABLE IF EXISTS `plogicop`;
CREATE TABLE `plogicop` (
  `lopid` int(11) NOT NULL default '0',
  `mlop` varchar(16) default NULL,
  PRIMARY KEY  (`lopid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`plogicop`
--

/*!40000 ALTER TABLE `plogicop` DISABLE KEYS */;
INSERT INTO `plogicop` (`lopid`,`mlop`) VALUES 
 (0,'AND'),
 (1,'OR');
/*!40000 ALTER TABLE `plogicop` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pmenu`
--

DROP TABLE IF EXISTS `pmenu`;
CREATE TABLE `pmenu` (
  `menuid` int(11) NOT NULL default '0',
  `menugroup` varchar(255) default NULL,
  PRIMARY KEY  (`menuid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pmenu`
--

/*!40000 ALTER TABLE `pmenu` DISABLE KEYS */;
INSERT INTO `pmenu` (`menuid`,`menugroup`) VALUES 
 (1,'Workgroup Menu');
/*!40000 ALTER TABLE `pmenu` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pmenuitem`
--

DROP TABLE IF EXISTS `pmenuitem`;
CREATE TABLE `pmenuitem` (
  `menuid` int(11) NOT NULL default '0',
  `itemid` int(11) NOT NULL default '0',
  `parentid` int(11) NOT NULL default '0',
  `iname` varchar(255) default NULL,
  `ilink` varchar(255) default NULL,
  `itarget` varchar(255) default NULL,
  `linkorgroup` tinyint(1) default NULL,
  `roleid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`menuid`,`itemid`),
  KEY `pmenuitem_idx1` (`parentid`),
  KEY `pmenuitem_idx2` (`menuid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pmenuitem`
--

/*!40000 ALTER TABLE `pmenuitem` DISABLE KEYS */;
INSERT INTO `pmenuitem` (`menuid`,`itemid`,`parentid`,`iname`,`ilink`,`itarget`,`linkorgroup`,`roleid`) VALUES 
 (1,1,0,'ProcÃ©dure','','',0,-1),
 (1,2,1,'A traiter','','',0,-1),
 (1,3,2,'Rechercher','link','nav',1,-1),
 (1,4,2,'Lister','listcase.jsp','nav',1,-1),
 (1,5,1,'Nouveau','','',0,-1),
 (1,6,5,'Transaction','newcase.jsp','nav',1,-1);
/*!40000 ALTER TABLE `pmenuitem` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pmodel`
--

DROP TABLE IF EXISTS `pmodel`;
CREATE TABLE `pmodel` (
  `modelid` int(11) NOT NULL default '0',
  `modelname` varchar(255) default NULL,
  `modelref` varchar(255) NOT NULL default '',
  `versionno` int(11) NOT NULL default '0',
  `startdate` datetime default '0000-00-00 00:00:00',
  `enddate` datetime default '0000-00-00 00:00:00',
  `isvalid` int(11) NOT NULL default '1',
  `pubdate` datetime NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (`modelid`),
  KEY `pmodel_idx1` (`modelid`,`versionno`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pmodel`
--

/*!40000 ALTER TABLE `pmodel` DISABLE KEYS */;
/*!40000 ALTER TABLE `pmodel` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`poperator`
--

DROP TABLE IF EXISTS `poperator`;
CREATE TABLE `poperator` (
  `opid` int(11) NOT NULL default '0',
  `mop` varchar(32) default NULL,
  PRIMARY KEY  (`opid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`poperator`
--

/*!40000 ALTER TABLE `poperator` DISABLE KEYS */;
INSERT INTO `poperator` (`opid`,`mop`) VALUES 
 (1,'=='),
 (2,'<'),
 (3,'<='),
 (4,'>='),
 (5,'>'),
 (6,'!=');
/*!40000 ALTER TABLE `poperator` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`ppdattr`
--

DROP TABLE IF EXISTS `ppdattr`;
CREATE TABLE `ppdattr` (
  `pdattribid` int(11) NOT NULL default '0',
  `prow` int(11) NOT NULL default '0',
  `attribdefid` int(11) NOT NULL default '0',
  `mvalue` varchar(255) default NULL,
  `modelid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`pdattribid`,`prow`,`modelid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`ppdattr`
--

/*!40000 ALTER TABLE `ppdattr` DISABLE KEYS */;
/*!40000 ALTER TABLE `ppdattr` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`ppersonalize`
--

DROP TABLE IF EXISTS `ppersonalize`;
CREATE TABLE `ppersonalize` (
  `login` varchar(32) NOT NULL default '',
  `userskin` varchar(32) NOT NULL default '',
  `defaulttab` int(11) NOT NULL default '0',
  PRIMARY KEY  (`login`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`ppersonalize`
--

/*!40000 ALTER TABLE `ppersonalize` DISABLE KEYS */;
INSERT INTO `ppersonalize` (`login`,`userskin`,`defaulttab`) VALUES 
 ('grime','2',0),
 ('gmd','2',0),
 ('admin','1',0);
/*!40000 ALTER TABLE `ppersonalize` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pprestations`
--

DROP TABLE IF EXISTS `pprestations`;
CREATE TABLE `pprestations` (
  `prestationtitle` varchar(100) NOT NULL default '',
  `prestationparent` int(11) NOT NULL default '0',
  `prestationid` int(11) NOT NULL auto_increment,
  PRIMARY KEY  (`prestationid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pprestations`
--

/*!40000 ALTER TABLE `pprestations` DISABLE KEYS */;
INSERT INTO `pprestations` (`prestationtitle`,`prestationparent`,`prestationid`) VALUES 
 ('Prestations communales',0,1012),
 ('Prestations publiques',1012,1013),
 ('Contrôle de l\'habitant',1013,1014),
 ('Attestation d\'état civil',1014,1015),
 ('Acte de naissance',1015,1016),
 ('Acte de marriage',1015,1017),
 ('Acte de décès',1015,1018),
 ('Prestations de moyens',1012,1019),
 ('Prestations de pilotages',1012,1020);
/*!40000 ALTER TABLE `pprestations` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pproc`
--

DROP TABLE IF EXISTS `pproc`;
CREATE TABLE `pproc` (
  `procid` int(11) NOT NULL default '0',
  `wkgid` int(11) NOT NULL default '0',
  `pdattribid` int(11) NOT NULL default '0',
  `modelid` int(11) NOT NULL default '0',
  `execid` int(11) NOT NULL default '0',
  `proctype` int(11) NOT NULL default '0',
  `doublesign` int(11) NOT NULL default '0',
  `procidprocessus` int(11) NOT NULL default '0',
  `procstableid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`procid`),
  KEY `pproc_idx1` (`procid`,`wkgid`,`proctype`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pproc`
--

/*!40000 ALTER TABLE `pproc` DISABLE KEYS */;
/*!40000 ALTER TABLE `pproc` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pprocstable`
--

DROP TABLE IF EXISTS `pprocstable`;
CREATE TABLE `pprocstable` (
  `PROCSTABLEID` int(11) NOT NULL,
  `PROCSTABLEDESC` varchar(35) default NULL,
  PRIMARY KEY  (`PROCSTABLEID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pprocstable`
--

/*!40000 ALTER TABLE `pprocstable` DISABLE KEYS */;
/*!40000 ALTER TABLE `pprocstable` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pproctrans`
--

DROP TABLE IF EXISTS `pproctrans`;
CREATE TABLE `pproctrans` (
  `procid` int(11) NOT NULL default '0',
  `caseid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `statusid` int(11) NOT NULL default '0',
  `emplid` int(11) NOT NULL default '0',
  `chiefflag` int(11) NOT NULL default '0',
  `proclateralid` int(11) NOT NULL default '0',
  `indate` datetime NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (`procid`,`caseid`,`transid`),
  KEY `pproctrans_idx1` (`statusid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pproctrans`
--

/*!40000 ALTER TABLE `pproctrans` DISABLE KEYS */;
/*!40000 ALTER TABLE `pproctrans` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pproctransfrom`
--

DROP TABLE IF EXISTS `pproctransfrom`;
CREATE TABLE `pproctransfrom` (
  `procid` int(11) NOT NULL default '0',
  `caseid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `refprocid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`procid`,`caseid`,`transid`,`refprocid`),
  KEY `pproctransfrom_idx1` (`procid`,`caseid`,`transid`,`refprocid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pproctransfrom`
--

/*!40000 ALTER TABLE `pproctransfrom` DISABLE KEYS */;
/*!40000 ALTER TABLE `pproctransfrom` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pproctranstxt`
--

DROP TABLE IF EXISTS `pproctranstxt`;
CREATE TABLE `pproctranstxt` (
  `modelid` int(11) NOT NULL default '0',
  `procid` int(11) NOT NULL default '0',
  `caseid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `msg` varchar(255) default NULL,
  PRIMARY KEY  (`modelid`,`procid`,`caseid`,`transid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pproctranstxt`
--

/*!40000 ALTER TABLE `pproctranstxt` DISABLE KEYS */;
/*!40000 ALTER TABLE `pproctranstxt` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`preferencestatus`
--

DROP TABLE IF EXISTS `preferencestatus`;
CREATE TABLE `preferencestatus` (
  `caseid` int(11) NOT NULL default '0',
  `procid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `delivid` int(11) NOT NULL default '0',
  `refid` int(11) NOT NULL default '0',
  `mstate` int(11) NOT NULL default '0',
  `mdated` datetime default NULL,
  PRIMARY KEY  (`caseid`,`procid`,`transid`,`delivid`,`refid`),
  KEY `preferencestatus_idx1` (`caseid`,`procid`,`transid`,`delivid`),
  KEY `preferencestatus_idx2` (`caseid`,`procid`,`transid`,`delivid`,`refid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`preferencestatus`
--

/*!40000 ALTER TABLE `preferencestatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `preferencestatus` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`proclog`
--

DROP TABLE IF EXISTS `proclog`;
CREATE TABLE `proclog` (
  `IDPROCLOG` bigint(20) NOT NULL auto_increment,
  `PROCID` int(11) default NULL,
  `EXTERNSYSTEMID` int(11) default NULL,
  `IDMESSAGEINTERNE` bigint(20) default NULL,
  `WKGID` int(11) default NULL,
  `MESSAGETIME` datetime default NULL,
  `TEMPSSTANDARD` decimal(20,10) default NULL,
  `CASEID` int(11) default NULL,
  `prestationID` int(11) default NULL,
  `statut` int(11) default NULL,
  PRIMARY KEY  (`IDPROCLOG`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`proclog`
--

/*!40000 ALTER TABLE `proclog` DISABLE KEYS */;
/*!40000 ALTER TABLE `proclog` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`prulesstatus`
--

DROP TABLE IF EXISTS `prulesstatus`;
CREATE TABLE `prulesstatus` (
  `caseid` int(11) NOT NULL default '0',
  `procid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `delivid` int(11) NOT NULL default '0',
  `refid` int(11) NOT NULL default '0',
  `mstate` int(11) NOT NULL default '0',
  `mdated` datetime default NULL,
  PRIMARY KEY  (`caseid`,`procid`,`transid`,`delivid`,`refid`),
  KEY `prulesstatus_idx1` (`caseid`,`procid`,`transid`,`delivid`),
  KEY `prulesstatus_idx2` (`caseid`,`procid`,`transid`,`delivid`,`refid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`prulesstatus`
--

/*!40000 ALTER TABLE `prulesstatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `prulesstatus` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pscrdatael`
--

DROP TABLE IF EXISTS `pscrdatael`;
CREATE TABLE `pscrdatael` (
  `Gid` int(11) NOT NULL default '0',
  `Eid` int(11) NOT NULL default '0',
  `Utype` int(11) NOT NULL default '0',
  `mName` varchar(255) NOT NULL default '',
  `mVal` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`Gid`,`Eid`),
  KEY `pscrDataEl_idx01` (`mName`),
  KEY `pscrDataEl_idx02` (`Gid`),
  KEY `pscrDataEl_idx03` (`Eid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pscrdatael`
--

/*!40000 ALTER TABLE `pscrdatael` DISABLE KEYS */;
/*!40000 ALTER TABLE `pscrdatael` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pscrdataellog`
--

DROP TABLE IF EXISTS `pscrdataellog`;
CREATE TABLE `pscrdataellog` (
  `Gid` int(11) NOT NULL default '0',
  `login` varchar(32) NOT NULL default '',
  `updated` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `Utype` int(11) NOT NULL default '0',
  `mName` varchar(255) NOT NULL default '',
  `mVal` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`Gid`,`login`,`updated`,`Utype`),
  KEY `pscrDataElLog_idx01` (`mName`),
  KEY `pscrDataElLog_idx02` (`Gid`),
  KEY `pscrDataElLog_idx03` (`updated`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pscrdataellog`
--

/*!40000 ALTER TABLE `pscrdataellog` DISABLE KEYS */;
/*!40000 ALTER TABLE `pscrdataellog` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pscrdatagroup`
--

DROP TABLE IF EXISTS `pscrdatagroup`;
CREATE TABLE `pscrdatagroup` (
  `gid` int(11) NOT NULL default '0',
  `groupname` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`gid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pscrdatagroup`
--

/*!40000 ALTER TABLE `pscrdatagroup` DISABLE KEYS */;
/*!40000 ALTER TABLE `pscrdatagroup` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pserverinfo`
--

DROP TABLE IF EXISTS `pserverinfo`;
CREATE TABLE `pserverinfo` (
  `infid` int(11) NOT NULL default '0',
  `inf` varchar(255) default NULL,
  PRIMARY KEY  (`infid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pserverinfo`
--

/*!40000 ALTER TABLE `pserverinfo` DISABLE KEYS */;
INSERT INTO `pserverinfo` (`infid`,`inf`) VALUES 
 (1,'1'),
 (2,'FR');
/*!40000 ALTER TABLE `pserverinfo` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pstatus`
--

DROP TABLE IF EXISTS `pstatus`;
CREATE TABLE `pstatus` (
  `statusid` int(11) NOT NULL default '0',
  `statusname` varchar(255) default NULL,
  PRIMARY KEY  (`statusid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pstatus`
--

/*!40000 ALTER TABLE `pstatus` DISABLE KEYS */;
INSERT INTO `pstatus` (`statusid`,`statusname`) VALUES 
 (0,'Disponible'),
 (1,'BloquÃ©'),
 (2,'LibÃ©rÃ©'),
 (3,'Attente'),
 (4,'Attente Maitre'),
 (5,'Attente Signature'),
 (6,'Attente Signature du Chef'),
 (98,'TraitÃ©'),
 (99,'Fini');
/*!40000 ALTER TABLE `pstatus` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`psystem`
--

DROP TABLE IF EXISTS `psystem`;
CREATE TABLE `psystem` (
  `systemid` int(11) NOT NULL default '0',
  `systemparent` int(11) NOT NULL default '0',
  `clsid` varchar(255) default NULL,
  `systemtitle` varchar(255) default NULL,
  `command` varchar(255) default NULL,
  `parameters` varchar(255) default NULL,
  `directory` varchar(255) default NULL,
  `priority` int(11) NOT NULL default '0',
  `windowst` int(11) NOT NULL default '0',
  PRIMARY KEY  (`systemid`),
  KEY `psystem_idx1` (`systemparent`),
  KEY `psystem_idx2` (`clsid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`psystem`
--

/*!40000 ALTER TABLE `psystem` DISABLE KEYS */;
INSERT INTO `psystem` (`systemid`,`systemparent`,`clsid`,`systemtitle`,`command`,`parameters`,`directory`,`priority`,`windowst`) VALUES 
 (128,0,'XzpbdjBdMzczNjk0Mjg5LTUyOTI2','Systèmes Logiques\0\0\0\0','','','',0,0),
 (856,128,'XzpbdjBdMTEyMTk4Nzg0MC01MTMxNw==\n','Applications\0\0\0\0','','','',0,0),
 (857,856,'XzpbdjBdLTcwNzE4Njc0Ny0yMDgxNw==\n','Front-Office\0\0\0\0','','','',0,0),
 (858,857,'XzpbdjBdMjU3OTAzMTU1LTE5ODg2','Kondor\0\0\0\0','','','',0,0),
 (859,857,'XzpbdjBdLTgyNjkxOTUxMy0zMTcwMQ==\n','Swx\0\0\0\0','','','',0,0),
 (860,857,'XzpbdjBdMTk1MzYxMjEwOC0yMTEy','ROR\0\0\0\0','','','',0,0),
 (861,860,'XzpbdjBdLTE0ODYzNzE3ODMtMzA1Nzk=\n','ROR rÃ©ception\0\0\0\0\0','','','',0,0),
 (862,860,'XzpbdjBdLTE0NDQzNzM0OTktMTE4Mw==\n','ROR transmission\0\0\0\0\0\0','','','',0,0),
 (863,857,'XzpbdjBdNjM4MjU3NzE5LTM0MTk0','Triple A\0\0\0\0\0','','','',0,0),
 (864,857,'XzpbdjBdLTExOTAyMjI0NDAtNTkxMTI=\n','CrÃ©dit plus\0\0\0\0','','','',0,0),
 (865,857,'XzpbdjBdLTg1NzgxNjQwLTM4MjM0','MIT\0\0\0\0','','','',0,0),
 (866,857,'XzpbdjBdLTQxNzkxNDU2NC02NTI5OQ==\n','Intersystem\0\0\0\0\0','','','',0,0);
INSERT INTO `psystem` (`systemid`,`systemparent`,`clsid`,`systemtitle`,`command`,`parameters`,`directory`,`priority`,`windowst`) VALUES 
 (867,857,'XzpbdjBdMTk2Njc0ODc2Ny01NzY2','SIMC\0\0\0\0\0\0','','','',0,0),
 (868,857,'XzpbdjBdMTE5MjA3NDcyOS0yMDI4','Caisse\0\0\0\0','','','',0,0),
 (869,857,'XzpbdjBdNTkwOTE4MzA3LTIyNjY=\n','One Reason\0\0\0\0\0\0','','','',0,0),
 (870,857,'XzpbdjBdLTg0MTg4Mzk4Ni0yOTQwNA==\n','GAB TKRS\0\0\0\0\0','','','',0,0),
 (871,857,'XzpbdjBdMTIyNzI4Njk2MC0zMzQyMg==\n','IHB\0\0\0\0','','','',0,0),
 (872,856,'XzpbdjBdLTE4Mjg1Nzg0NzMtMjA4ODY=\n','IntÃ©gration\0\0\0\0','','','',0,0),
 (873,872,'XzpbdjBdLTUwNjI0NTA0Mi01ODM5Nw==\n','TIBCO\0\0\0\0\0','','','',0,0),
 (874,872,'XzpbdjBdLTE4NjcxOTk5MzctNTkwMzc=\n','Broad Vision\0\0\0\0','','','',0,0),
 (875,856,'XzpbdjBdLTEyMzg4NjA4OC0yOTY1NQ==\n','Back-Office\0\0\0\0\0','','','',0,0),
 (876,875,'XzpbdjBdLTkzMjk2MDkxOS01MTY2NQ==\n','New Banking\0\0\0\0\0','','','',0,0),
 (877,875,'XzpbdjBdLTY1NzU4MTgyLTI1MDcx','SCS\0\0\0\0','','','',0,0),
 (878,875,'XzpbdjBdNjEwNzQ0NDgtNjc1NA==\n','OSIRIS\0\0\0\0','','','',0,0);
INSERT INTO `psystem` (`systemid`,`systemparent`,`clsid`,`systemtitle`,`command`,`parameters`,`directory`,`priority`,`windowst`) VALUES 
 (879,878,'XzpbdjBdLTIwNzQxOTk0NzUtMjYzNTU=\n','NEGO\0\0\0\0\0\0','','','',0,0),
 (880,856,'XzpbdjBdLTE3MDgxMjkyNTctMjM5MDM=\n','Restitutions\0\0\0\0','','','',0,0),
 (881,856,'XzpbdjBdLTEyMDczODg0MTktNTg1NzQ=\n','Bureautique\0\0\0\0\0','','','',0,0),
 (882,881,'XzpbdjBdLTkxMTQ3MDUtNDU1Ng==\n','Excel\0\0\0\0\0','','','',0,0),
 (883,128,'XzpbdjBdNTI2MzIwMzM3LTI0NTM5','Infrastructure\0\0\0\0\0','','','',0,0),
 (884,128,'XzpbdjBdLTk2ODEyMTIzMC0zNTE0Nw==\n','Media\0\0\0\0\0','','','',0,0),
 (885,884,'XzpbdjBdLTIwNDA1MjkyNzYtNDQ2NjU=\n','Fax\0\0\0\0','','','',0,0),
 (886,884,'XzpbdjBdLTE4NjA2ODgwMDQtMTExMDg=\n','TÃ©lÃ©phone\0\0\0\0\0','','','',0,0),
 (887,884,'XzpbdjBdNzAzOTcxMTU3LTM5Mjc2','Courrier\0\0\0\0\0','','','',0,0),
 (888,884,'XzpbdjBdODUyOTQzNjE1LTMyOTM5','Internet\0\0\0\0\0','','','',0,0),
 (129,128,'XzpbdjBdMzczNjk0MjkzLTUyOTI2','Applications\0\0\0\0','','','',0,0),
 (130,129,'XzpbdjBdMzczNjk0Mjk2LTUyOTI2','Relation client\0\0\0\0','','','',0,0);
INSERT INTO `psystem` (`systemid`,`systemparent`,`clsid`,`systemtitle`,`command`,`parameters`,`directory`,`priority`,`windowst`) VALUES 
 (131,129,'XzpbdjBdMzczNjk0Mjk3LTUyOTI2','Legacy\0\0\0\0','','','',0,0),
 (132,131,'XzpbdjBdMjg0NDcwMDM1LTMyMjIx','Fichier Valeur\0\0\0\0\0','','','',0,0),
 (534,132,'XzpbdjBdMTk3MDM4MTYxMi0xNjQ0MA==\n','Création de valeur\0\0\0\0\0\0','','','',0,0),
 (535,132,'XzpbdjBdLTE0MDI0NzcyMzYtMTYzMzU=\n','Opération sur tiitre\0\0\0\0','','','',0,0),
 (133,131,'XzpbdjBdLTgzMjY2MDc4My02Mjc0Ng==\n','Fichier Central\0\0\0\0','','','',0,0),
 (134,131,'XzpbdjBdMjEyOTExNzMwNS0zMTg0OA==\n','Edition-Courrier\0\0\0\0\0\0','','','',0,0),
 (536,131,'XzpbdjBdLTE3NjQzODA0Ni0zMzI4NQ==\n','Opérations\0\0\0\0\0','','','',0,0),
 (537,536,'XzpbdjBdLTI5ODkzODc1OC00MTU5MA==\n','Bourse\0\0\0\0','','','',0,0),
 (538,536,'XzpbdjBdLTk0NDc4OTIwMC02MzkyNQ==\n','Change\0\0\0\0','','','',0,0),
 (539,536,'XzpbdjBdMTc2NDg0MDA1LTQwNTIx','Marché monétaire\0\0\0\0','','','',0,0),
 (135,129,'XzpbdjBdMzczNjk0Mjk4LTUyOTI2','Systèmes Comptables\0\0\0\0\0','','','',0,0),
 (137,129,'XzpbdjBdNDYzMjY5MzYyLTQ5ODc4','Recherche client\0\0\0\0\0\0','','','',0,0);
INSERT INTO `psystem` (`systemid`,`systemparent`,`clsid`,`systemtitle`,`command`,`parameters`,`directory`,`priority`,`windowst`) VALUES 
 (138,129,'XzpbdjBdLTIwODQ0MDcxNTMtMjg4MTc=\n','Bases juridiques\0\0\0\0\0\0','','','',0,0),
 (148,129,'XzpbdjBdLTk4MTIwNzU4Mi0yMzM2Mg==\n','Négociation\0\0\0\0','','','',0,0),
 (540,148,'XzpbdjBdMTgxNTQzMjMzMy01NjMxMw==\n','2000 Valeurs\0\0\0\0','','','',0,0),
 (541,148,'XzpbdjBdMjA0MDgxODI0My0zNjExMg==\n','2000 Marché monétaire\0\0\0\0\0','','','',0,0),
 (542,148,'XzpbdjBdLTgxMDY1OTczNi0xMTgyOQ==\n','2000 Change\0\0\0\0\0','','','',0,0),
 (543,148,'XzpbdjBdLTEyNTI4MjEzMzQtNTM1MjM=\n','Ordres express\0\0\0\0\0','','','',0,0),
 (544,129,'XzpbdjBdLTk1NTg4NTI3OS02MDM3Nw==\n','PMS\0\0\0\0','','','',0,0),
 (545,129,'XzpbdjBdLTE3NDE3MzUwNDQtNDM4NDg=\n','Messages\0\0\0\0\0','','','',0,0),
 (546,545,'XzpbdjBdNTcwNjEyODI1LTQ5MTQ5','Swift\0\0\0\0\0','','','',0,0),
 (547,545,'XzpbdjBdLTE1ODYyNDgyMTctMzA3MA==\n','SIC\0\0\0\0','','','',0,0),
 (139,128,'XzpbdjBdMzczNjk0Mjk0LTUyOTI2','Infrastructure\0\0\0\0\0','','','',0,0),
 (140,139,'XzpbdjBdMTcwMDA3MjYzNi0zNjc5Mg==\n','Scanning\0\0\0\0\0','','','',0,0);
INSERT INTO `psystem` (`systemid`,`systemparent`,`clsid`,`systemtitle`,`command`,`parameters`,`directory`,`priority`,`windowst`) VALUES 
 (811,0,'XzpbdjBdLTE2ODk3MTkzOTUtMjA4NQ==\n','Ressources\0\0\0\0\0\0','','','',0,0),
 (812,811,'XzpbdjBdMzg0OTQyNDM1LTE4NzAz','Applications\0\0\0\0','','','',0,0),
 (813,812,'XzpbdjBdLTE5NjE1NDIzNTctMTUzMzc=\n','SystÃ¨me d\'offre\0\0\0\0\0\0','','','',0,0),
 (814,812,'XzpbdjBdLTg2MjUxMzg1Ny0xMDYzNg==\n','Offres Internet\0\0\0\0','','','',0,0),
 (815,811,'XzpbdjBdNzcxMTc2MDM4LTUwODc5','Media\0\0\0\0\0','','','',0,0),
 (816,815,'XzpbdjBdLTExMzczMDI4NzQtNTQ0MTg=\n','Impression\0\0\0\0\0\0','','','',0,0),
 (817,815,'XzpbdjBdMTIzODYzNjc2NC0xMTU4Ng==\n','TÃ©lÃ©phone\0\0\0\0\0','','','',0,0),
 (818,815,'XzpbdjBdMTA0NTYzMjUzNS0xMDM3MQ==\n','Fax\0\0\0\0','','','',0,0),
 (819,815,'XzpbdjBdLTE1ODk4MjExNTAtNTI0MTE=\n','Email\0\0\0\0\0','','','',0,0),
 (820,811,'XzpbdjBdOTAyNzYxMzkzLTMzNTE3','Infrastructure\0\0\0\0\0','','','',0,0),
 (821,820,'XzpbdjBdMTYzMDIxOTAwNC0yNzY5Nw==\n','Archivage numÃ©rique\0\0\0\0\0','','','',0,0),
 (515,0,'XzpbdjBdLTE3NzM1NTQ0NDktMjMyMDI=\n','Systèmes Logiques\0\0\0\0','','','',0,0);
INSERT INTO `psystem` (`systemid`,`systemparent`,`clsid`,`systemtitle`,`command`,`parameters`,`directory`,`priority`,`windowst`) VALUES 
 (516,515,'XzpbdjBdMTkxMzE0NDYwMy0yNTI4OQ==\n','Applications\0\0\0\0','','','',0,0),
 (517,516,'XzpbdjBdLTg0NTI5ODA3MC02NDA4Mg==\n','Crédit +\0\0\0\0','','','',0,0),
 (518,517,'XzpbdjBdMTcxMzQ5NjA1Mi01MDU4Ng==\n','Devis\0\0\0\0\0','','','',0,0),
 (519,516,'XzpbdjBdLTk3ODUzNDMzOC0yMzQ2NA==\n','SIMC\0\0\0\0\0\0','','','',0,0),
 (520,516,'XzpbdjBdLTIzNjQ4NjUzMy0yOTAyOA==\n','Access crédit\0\0\0\0\0','','','',0,0),
 (521,516,'XzpbdjBdLTU3Mzk2MzEtNjI3NDU=\n','Osiris\0\0\0\0','','','',0,0),
 (522,516,'XzpbdjBdLTM5MjIwMDI3Mi00NzMxMA==\n','Internet\0\0\0\0\0','','','',0,0),
 (523,522,'XzpbdjBdMTc4NTY3MjIxNy03NzI1','Simulation Internet\0\0\0\0\0\0','','','',0,0),
 (524,516,'XzpbdjBdOTA2NjIzNTgzLTMxMDYw','Excel\0\0\0\0\0','','','',0,0),
 (525,516,'XzpbdjBdOTA2NjIzNTg0LTMxMDYw','Crédit Explorer\0\0\0\0\0\0','','','',0,0),
 (526,515,'XzpbdjBdLTEyMDIzMjk3My05ODA=\n','Infrastructure\0\0\0\0\0','','','',0,0),
 (527,515,'XzpbdjBdMjI2MTczODQ3LTE5ODAy','Media\0\0\0\0\0','','','',0,0);
INSERT INTO `psystem` (`systemid`,`systemparent`,`clsid`,`systemtitle`,`command`,`parameters`,`directory`,`priority`,`windowst`) VALUES 
 (528,527,'XzpbdjBdNzUyMTc2MDkwLTQ3MjE5','Courrier\0\0\0\0\0','','','',0,0),
 (529,527,'XzpbdjBdOTA2NjIzNTg1LTMxMDYw','SMS\0\0\0\0','','','',0,0),
 (530,527,'XzpbdjBdOTA2NjIzNTg2LTMxMDYw','Téléphone\0\0\0\0\0','','','',0,0),
 (531,527,'XzpbdjBdOTA2NjIzNTg3LTMxMDYw','Fax\0\0\0\0','','','',0,0),
 (532,527,'XzpbdjBdOTA2NjIzNTg5LTMxMDYw','E-mail\0\0\0\0','','','',0,0),
 (533,515,'XzpbdjBdOTA2NjIzNTg4LTMxMDYw','Entrevue\0\0\0\0\0','','','',0,0),
 (720,0,'XzpbdjBdLTY4NTcwMzYxMy0xNjM0MA==\n','Applications et infrastructures\0\0\0\0\0\0','','','',0,0),
 (721,720,'XzpbdjBdNjE2MTMzNzIyLTE1Njkw','Applications\0\0\0\0','','','',0,0),
 (722,721,'XzpbdjBdODExNDMzMTMyLTU4OTI4','SIEF\0\0\0\0\0\0','','','',0,0),
 (723,721,'XzpbdjBdLTE3NTg4MDg5NC0zOTAzOQ==\n','SIRH\0\0\0\0\0\0','','','',0,0),
 (724,723,'XzpbdjBdLTUxNDMwOTkwOC0zNTE2','SIRH - Saisie voeux web\0\0\0\0\0','','','',0,0),
 (725,723,'XzpbdjBdMjA5NDM3MzkwLTMyNDA=\n','SIRH - Validation voeux\0\0\0\0\0','','','',0,0);
INSERT INTO `psystem` (`systemid`,`systemparent`,`clsid`,`systemtitle`,`command`,`parameters`,`directory`,`priority`,`windowst`) VALUES 
 (726,723,'XzpbdjBdLTk2MjY2MDg0NS0zNTU0OQ==\n','SIRH - Candidature\0\0\0\0','','','',0,0),
 (727,723,'XzpbdjBdLTIxMjA5Mjk5NjItMzQyODI=\n','SIRH - Fonctions\0\0\0\0\0\0','','','',0,0),
 (728,723,'XzpbdjBdNDc2ODIwMjU2LTI5OTQy','SIRH - Besoin formation\0\0\0\0\0','','','',0,0),
 (729,723,'XzpbdjBdMjM0OTY3NjEtMjQ3MjQ=\n','SIRH - Offre formation\0\0\0\0\0\0','','','',0,0),
 (730,723,'XzpbdjBdMzg0ODI0MjI0LTEwNjc=\n','SIRH - Gestion des UO\0\0\0\0','','','',0,0),
 (731,723,'XzpbdjBdLTEzNTAwNTI1MDgtNjA5ODM=\n','SIRH - Besoins en personnel\0\0\0\0','','','',0,0),
 (732,723,'XzpbdjBdLTE0OTIzMDczNTktMzUyMA==\n','SIRH - Eléments de paie\0\0\0\0','','','',0,0),
 (733,723,'XzpbdjBdNjcxMjA4ODIxLTU0MzQ5','SIRH - Réglementaire de paie\0\0\0\0\0','','','',0,0),
 (734,723,'XzpbdjBdMTM1ODU0NDczOS0zMTc1NA==\n','SIRH - Résultats de paie\0\0\0\0\0\0','','','',0,0),
 (735,723,'XzpbdjBdMTk1NDM3MDQ4MC0zMDA5Nw==\n','SIRH - Exploitation\0\0\0\0\0\0','','','',0,0),
 (736,723,'XzpbdjBdLTEzNDY0NTczOTYtMzI5NTg=\n','SIRH - Workflow\0\0\0\0','','','',0,0);
INSERT INTO `psystem` (`systemid`,`systemparent`,`clsid`,`systemtitle`,`command`,`parameters`,`directory`,`priority`,`windowst`) VALUES 
 (737,723,'XzpbdjBdMTY0Njc3MDk5MS0yOTI3NQ==\n','SIRH - Absences\0\0\0\0','','','',0,0),
 (738,723,'XzpbdjBdMzY2NjI1NDkwLTExNjI0','SIRH - Accident\0\0\0\0','','','',0,0),
 (739,723,'XzpbdjBdLTExNzY5MDg5NjItMzAwNzQ=\n','SIRH - Gestion des postes\0\0\0\0\0\0','','','',0,0),
 (740,723,'XzpbdjBdMTkwOTY3NDE0Ny0zODY1Mg==\n','SIRH - Formation\0\0\0\0\0\0','','','',0,0),
 (741,723,'XzpbdjBdLTYzMjc3OTkxNS00NzcwNQ==\n','SIRH - Compétences\0\0\0\0\0\0','','','',0,0),
 (742,723,'XzpbdjBdNDg1Mzg5NDc1LTM5Nzc=\n','SIRH - Budget\0\0\0\0\0\0','','','',0,0),
 (743,723,'XzpbdjBdMTc4ODE2NzY3NS02NTI1OA==\n','SIRH - Gestion du dossier\0\0\0\0\0\0','','','',0,0),
 (744,723,'XzpbdjBdLTEwNDQ0NDYzMTgtNTYzNTE=\n','SIRH - Infocentre paye\0\0\0\0\0\0','','','',0,0),
 (745,723,'XzpbdjBdLTExODUwMTg1NjYtNTM1ODc=\n','SIRH - Horaires\0\0\0\0','','','',0,0),
 (746,723,'XzpbdjBdLTM3MjYyMTkzOS03NDk2','SIRH - Budget formation\0\0\0\0\0','','','',0,0),
 (747,723,'XzpbdjBdLTIwNjE4MDMwMDgtNjg5','SIRH - Entretien\0\0\0\0\0\0','','','',0,0);
INSERT INTO `psystem` (`systemid`,`systemparent`,`clsid`,`systemtitle`,`command`,`parameters`,`directory`,`priority`,`windowst`) VALUES 
 (748,723,'XzpbdjBdLTE3MjU2ODM4MDUtNjMzNQ==\n','SIRH - Enseignants\0\0\0\0','','','',0,0),
 (749,723,'XzpbdjBdNjQ0MzMwNDQxLTQ1NjA3','SIRH - Paie au guichet\0\0\0\0\0\0','','','',0,0),
 (750,723,'XzpbdjBdODQ2Njk4MzkwLTIwNzk0','SIRH - Gestion événementielle\0\0\0\0\0\0','','','',0,0),
 (752,721,'XzpbdjBdLTU3NTEyMTI5OC00MzEzOA==\n','Interfaces\0\0\0\0\0\0','','','',0,0),
 (753,752,'XzpbdjBdLTExMDc4NTA3MTQtMjk0ODA=\n','SIRH - SIEF\0\0\0\0\0','','','',0,0),
 (754,752,'XzpbdjBdLTExNDgzNTg1Mi01OTY1MA==\n','Aigle - SIRH\0\0\0\0','','','',0,0),
 (755,752,'XzpbdjBdLTIwODUyNTcwOTktNjQ2OTc=\n','SIRH - CFI Comptabilisation\0\0\0\0','','','',0,0),
 (756,752,'XzpbdjBdMTcwMDUyMTU4NS0xODkyNg==\n','SIRH - See-k\0\0\0\0','','','',0,0),
 (757,752,'XzpbdjBdMTQxMjc2MTg3My0xNjI4MA==\n','SIRH - CFI Budget\0\0\0\0\0','','','',0,0),
 (758,752,'XzpbdjBdLTU3ODU1Mjk2My0zMTk2','CFI -SIRH\0\0\0\0','','','',0,0),
 (759,752,'XzpbdjBdLTkwNzg0NjgwOS0xODUwNw==\n','SIRH - Pointage\0\0\0\0','','','',0,0);
INSERT INTO `psystem` (`systemid`,`systemparent`,`clsid`,`systemtitle`,`command`,`parameters`,`directory`,`priority`,`windowst`) VALUES 
 (760,752,'XzpbdjBdLTIwMzY4NDU4OTItNDEx','Evaluation -  SIRH\0\0\0\0','','','',0,0),
 (761,752,'XzpbdjBdMjA5Mzk1MTI5Ny0xMTQyNg==\n','Pointage - SIRH\0\0\0\0','','','',0,0),
 (762,752,'XzpbdjBdLTUyNTIzMzQyNy0xNDgwNQ==\n','See-k - SIRH\0\0\0\0','','','',0,0),
 (766,721,'XzpbdjBdLTE1MTMzNzkwNzQtMjAyMTM=\n','See-k\0\0\0\0\0','','','',0,0),
 (767,721,'XzpbdjBdMjM1OTMzNTI2LTMzNjgx','CFI\0\0\0\0','','','',0,0),
 (768,721,'XzpbdjBdLTE1MTM5OTQ5NTctNDU2NDg=\n','Evaluation\0\0\0\0\0\0','','','',0,0),
 (970,721,'XzpbdjBdLTEwNDcxODk5OTMtMTIwNzk=\n','E-learning\0\0\0\0\0\0','','','',0,0),
 (971,970,'XzpbdjBdMTY3OTgxNzM5OC02MTM4NQ==\n','bureautique\0\0\0\0\0','','','',0,0),
 (972,971,'XzpbdjBdLTkxMDk0NjgzNi02Mzg1Nw==\n','évaluation initiale\0\0\0\0\0','','','',0,0),
 (973,971,'XzpbdjBdLTIwMTYyNDk2NDMtNjM1NDk=\n','évaluation finale bureautique\0\0\0\0','','','',0,0),
 (974,971,'XzpbdjBdMjcxMjA4ODQ4LTUzMTU1','auto-formation super-U\0\0\0\0\0\0','','','',0,0);
INSERT INTO `psystem` (`systemid`,`systemparent`,`clsid`,`systemtitle`,`command`,`parameters`,`directory`,`priority`,`windowst`) VALUES 
 (975,970,'XzpbdjBdMTc4NjY2OTk1Ny00NjU4NQ==\n','technique\0\0\0\0','','','',0,0),
 (976,975,'XzpbdjBdLTE0OTk0OTI0ODAtMjIwNQ==\n','évaluation finale technique\0\0\0\0\0\0','','','',0,0),
 (977,975,'XzpbdjBdLTIyNDY0OTA0My01NjQ0OQ==\n','auto-formation technique\0\0\0\0','','','',0,0),
 (978,721,'XzpbdjBdMzkwMDczMTU5LTM5MTEz','GIP\0\0\0\0','','','',0,0),
 (979,721,'XzpbdjBdMTY3MTE3NTQ2MC0xMDk5','Lotus-Former\0\0\0\0','','','',0,0),
 (774,720,'XzpbdjBdLTM3ODQ2ODYxOC00OTYyMQ==\n','Infrastructure\0\0\0\0\0','','','',0,0),
 (775,774,'XzpbdjBdMTI5NDQwODc4NC0zNzgzNg==\n','Docubase\0\0\0\0\0','','','',0,0),
 (980,774,'XzpbdjBdMzk3NzA4MjQ4LTM0MzI2','Environnement recette e-learning\0\0\0\0\0','','','',0,0),
 (776,720,'XzpbdjBdMTI4MDIzMTc4NC0xNjI5MA==\n','Médias\0\0\0\0\0\0','','','',0,0),
 (777,776,'XzpbdjBdLTEyOTc4MjczNDItNTYyODg=\n','eMail\0\0\0\0\0','','','',0,0),
 (778,776,'XzpbdjBdNDA5Njg1NjcwLTIxNTQz','Téléphone\0\0\0\0\0','','','',0,0);
INSERT INTO `psystem` (`systemid`,`systemparent`,`clsid`,`systemtitle`,`command`,`parameters`,`directory`,`priority`,`windowst`) VALUES 
 (779,776,'XzpbdjBdOTY1ODA4ODc3LTI1NjM2','Entretien\0\0\0\0','','','',0,0),
 (780,776,'XzpbdjBdLTQ1Mjk5MDMwNS02NDYxNg==\n','Courrier (interne - externe)\0\0\0\0\0\0','','','',0,0),
 (781,776,'XzpbdjBdLTc5NTcwODYwMS0yMjQ0OA==\n','Intranet\0\0\0\0\0','','','',0,0),
 (782,776,'XzpbdjBdLTI1MjI2ODQ0Ny01MTc0Mg==\n','DTA\0\0\0\0','','','',0,0),
 (783,776,'XzpbdjBdLTIwOTcyNzU4NzItMTQzMDE=\n','Extranet\0\0\0\0\0','','','',0,0),
 (999,0,'XzpbdjBdLTQ1MTM4NDgzMi00NzU5OA==\n','Ressources\0\0\0\0\0\0','','','',0,0),
 (1000,999,'XzpbdjBdLTUwNTk5MDE2LTU1MDA=\n','Applications\0\0\0\0','','','',0,0),
 (1001,1000,'XzpbdjBdLTE5NzI2ODI3MjMtMTYyOTA=\n','BD état civil\0\0\0\0\0','','','',0,0),
 (1002,999,'XzpbdjBdLTg5NTQ5OTM3NS0zMTU5Nw==\n','Logistique\0\0\0\0\0\0','','','',0,0),
 (1003,999,'XzpbdjBdNjg4NTQzNi02NDU3OA==\n','Infrastructure\0\0\0\0\0','','','',0,0),
 (1004,1003,'XzpbdjBdMTUzMTI0Mzg0MS03ODM4','Accueil secrétariat\0\0\0\0\0','','','',0,0),
 (1005,999,'XzpbdjBdMTU5NjM4NTYzMi0zNzM3OQ==\n','Media\0\0\0\0\0','','','',0,0);
INSERT INTO `psystem` (`systemid`,`systemparent`,`clsid`,`systemtitle`,`command`,`parameters`,`directory`,`priority`,`windowst`) VALUES 
 (1006,1005,'XzpbdjBdLTIwOTM3OTcwNzUtMTQ5NTQ=\n','Fax\0\0\0\0','','','',0,0),
 (1007,1005,'XzpbdjBdMTQyNTE2MjM1Mi02MjgyNw==\n','Email\0\0\0\0\0','','','',0,0),
 (1008,1005,'XzpbdjBdMTM3NTA5NDY3NS02MDIxMw==\n','Téléphone\0\0\0\0\0','','','',0,0),
 (1009,1005,'XzpbdjBdNjU2MDU0Mjc4LTM4ODI3','Courrier\0\0\0\0\0','','','',0,0),
 (1010,1005,'XzpbdjBdMTYwMjQ4NjgzLTk5NzM=\n','Webservice\0\0\0\0\0\0','','','',0,0),
 (1011,1005,'XzpbdjBdLTk4OTIzNzg5Ni0zMDcwMw==\n','Visite\0\0\0\0','','','',0,0);
/*!40000 ALTER TABLE `psystem` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`psystemstatus`
--

DROP TABLE IF EXISTS `psystemstatus`;
CREATE TABLE `psystemstatus` (
  `caseid` int(11) NOT NULL default '0',
  `procid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `delivid` int(11) NOT NULL default '0',
  `refid` int(11) NOT NULL default '0',
  `mstate` int(11) NOT NULL default '0',
  `mdated` datetime default NULL,
  PRIMARY KEY  (`caseid`,`procid`,`transid`,`delivid`,`refid`),
  KEY `psystemstatus_idx1` (`caseid`,`procid`,`delivid`,`transid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`psystemstatus`
--

/*!40000 ALTER TABLE `psystemstatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `psystemstatus` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`ptaskstatus`
--

DROP TABLE IF EXISTS `ptaskstatus`;
CREATE TABLE `ptaskstatus` (
  `caseid` int(11) NOT NULL default '0',
  `procid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `taskid` int(11) NOT NULL default '0',
  `mstate` int(11) NOT NULL default '0',
  `mdated` datetime default NULL,
  PRIMARY KEY  (`caseid`,`procid`,`transid`,`taskid`),
  KEY `ptaskstatus_idx1` (`caseid`,`procid`,`transid`),
  KEY `ptaskstatus_idx2` (`caseid`,`procid`,`transid`,`taskid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`ptaskstatus`
--

/*!40000 ALTER TABLE `ptaskstatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `ptaskstatus` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`ptrans`
--

DROP TABLE IF EXISTS `ptrans`;
CREATE TABLE `ptrans` (
  `caseid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `parenttransid` int(11) NOT NULL default '0',
  `transname` varchar(255) default NULL,
  `globalyn` tinyint(1) NOT NULL default '0',
  `attribid` int(11) NOT NULL default '0',
  `statusid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`caseid`,`transid`),
  KEY `ptrans_idx1` (`parenttransid`),
  KEY `ptrans_idx2` (`statusid`),
  KEY `ptrans_idx3` (`transname`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`ptrans`
--

/*!40000 ALTER TABLE `ptrans` DISABLE KEYS */;
/*!40000 ALTER TABLE `ptrans` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`puniverse`
--

DROP TABLE IF EXISTS `puniverse`;
CREATE TABLE `puniverse` (
  `guidSystem` varchar(50) NOT NULL default '',
  `guidPrestation` varchar(50) NOT NULL default '',
  `guidWorkgroup` varchar(50) NOT NULL default '',
  PRIMARY KEY  (`guidWorkgroup`,`guidPrestation`,`guidSystem`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`puniverse`
--

/*!40000 ALTER TABLE `puniverse` DISABLE KEYS */;
/*!40000 ALTER TABLE `puniverse` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pworkgroup`
--

DROP TABLE IF EXISTS `pworkgroup`;
CREATE TABLE `pworkgroup` (
  `wkgid` int(11) NOT NULL default '0',
  `wkgparent` int(11) default NULL,
  `wkgname` varchar(255) default NULL,
  `wkgpercent` int(4) default '0',
  `eptflag` int(2) default '0',
  `mission` varchar(150) default '',
  `vocation` varchar(150) default '',
  `street` varchar(150) default '',
  `npalocality` varchar(25) default '',
  `municipality` varchar(50) default '',
  `country` varchar(50) default '',
  `email` varchar(50) default '',
  `creationdate` date default NULL,
  `wkgtype` int(2) default '0',
  `phone` varchar(25) default '',
  `daycost` varchar(20) default '',
  PRIMARY KEY  (`wkgid`),
  KEY `pworkgroup_idx1` (`wkgparent`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pworkgroup`
--

/*!40000 ALTER TABLE `pworkgroup` DISABLE KEYS */;
/*!40000 ALTER TABLE `pworkgroup` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pzsrvempmap`
--

DROP TABLE IF EXISTS `pzsrvempmap`;
CREATE TABLE `pzsrvempmap` (
  `grpid` int(11) NOT NULL default '0',
  `login` varchar(32) NOT NULL default '',
  UNIQUE KEY `pzsrvempmap_idx1` (`grpid`,`login`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pzsrvempmap`
--

/*!40000 ALTER TABLE `pzsrvempmap` DISABLE KEYS */;
/*!40000 ALTER TABLE `pzsrvempmap` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pzsrvfiles`
--

DROP TABLE IF EXISTS `pzsrvfiles`;
CREATE TABLE `pzsrvfiles` (
  `dirname` varchar(250) NOT NULL default '',
  `filename` varchar(250) NOT NULL default '',
  `filever` int(11) default NULL,
  `creationdate` datetime default NULL,
  `lastChange` datetime default NULL,
  `countaccess` int(11) default NULL,
  PRIMARY KEY  (`dirname`,`filename`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pzsrvfiles`
--

/*!40000 ALTER TABLE `pzsrvfiles` DISABLE KEYS */;
/*!40000 ALTER TABLE `pzsrvfiles` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pzsrvgroup`
--

DROP TABLE IF EXISTS `pzsrvgroup`;
CREATE TABLE `pzsrvgroup` (
  `grpid` int(11) NOT NULL default '0',
  `grpparent` int(11) default NULL,
  `grpname` varchar(255) default NULL,
  PRIMARY KEY  (`grpid`),
  KEY `pzsrvgroup_idx1` (`grpparent`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pzsrvgroup`
--

/*!40000 ALTER TABLE `pzsrvgroup` DISABLE KEYS */;
INSERT INTO `pzsrvgroup` (`grpid`,`grpparent`,`grpname`) VALUES 
 (1,0,'Entreprise');
/*!40000 ALTER TABLE `pzsrvgroup` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pzsrvlock`
--

DROP TABLE IF EXISTS `pzsrvlock`;
CREATE TABLE `pzsrvlock` (
  `dirname` varchar(250) NOT NULL default '',
  `filename` varchar(250) NOT NULL default '',
  `lockstate` int(11) NOT NULL default '0',
  `lockuser` int(11) NOT NULL default '0',
  `lockdate` datetime default NULL,
  PRIMARY KEY  (`dirname`,`filename`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pzsrvlock`
--

/*!40000 ALTER TABLE `pzsrvlock` DISABLE KEYS */;
/*!40000 ALTER TABLE `pzsrvlock` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`pzsrvusermap`
--

DROP TABLE IF EXISTS `pzsrvusermap`;
CREATE TABLE `pzsrvusermap` (
  `dirname` varchar(255) NOT NULL default '',
  `login` varchar(32) NOT NULL default '',
  KEY `pzsrvusermap_idx1` (`dirname`,`login`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pilotage`.`pzsrvusermap`
--

/*!40000 ALTER TABLE `pzsrvusermap` DISABLE KEYS */;
/*!40000 ALTER TABLE `pzsrvusermap` ENABLE KEYS */;


--
-- Table structure for table `pilotage`.`testtable`
--

DROP TABLE IF EXISTS `testtable`;
CREATE TABLE `testtable` (
  `formule` varchar(40) NOT NULL default '',
  PRIMARY KEY  (`formule`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `pilotage`.`testtable`
--

/*!40000 ALTER TABLE `testtable` DISABLE KEYS */;
INSERT INTO `testtable` (`formule`) VALUES 
 ('=A4/2');
/*!40000 ALTER TABLE `testtable` ENABLE KEYS */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
