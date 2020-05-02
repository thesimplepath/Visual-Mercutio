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
-- Create schema mercutio2
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ mercutio2;
USE mercutio2;

--
-- Table structure for table `mercutio2`.`aile`
--

DROP TABLE IF EXISTS `aile`;
CREATE TABLE `aile` (
  `emplid` int(10) unsigned NOT NULL default '0',
  `wkgid` int(10) unsigned NOT NULL default '0',
  `calmonth` int(10) unsigned NOT NULL default '0',
  `calyear` int(10) unsigned NOT NULL default '0',
  `taux` decimal(10,2) NOT NULL default '0.00',
  PRIMARY KEY  (`emplid`,`wkgid`,`calmonth`,`calyear`)
);

--
-- Dumping data for table `mercutio2`.`aile`
--

/*!40000 ALTER TABLE `aile` DISABLE KEYS */;
INSERT INTO `aile` (`emplid`,`wkgid`,`calmonth`,`calyear`,`taux`) VALUES 
 (2,1000993,1,2005,'1.00'),
 (2,1000993,1,2006,'1.00'),
 (2,1000993,2,2005,'1.00'),
 (2,1000993,2,2006,'1.00'),
 (2,1000993,3,2005,'1.00'),
 (2,1000993,3,2006,'1.00'),
 (2,1000993,4,2005,'1.00'),
 (2,1000993,4,2006,'1.00'),
 (2,1000993,5,2005,'1.00'),
 (2,1000993,5,2006,'1.00'),
 (2,1000993,6,2005,'1.00'),
 (2,1000993,6,2006,'1.00'),
 (2,1000993,7,2005,'1.00'),
 (2,1000993,7,2006,'1.00'),
 (2,1000993,8,2005,'1.00'),
 (2,1000993,8,2006,'1.00'),
 (2,1000993,9,2005,'1.00'),
 (2,1000993,9,2006,'1.00'),
 (2,1000993,10,2005,'1.00'),
 (2,1000993,10,2006,'1.00'),
 (2,1000993,11,2005,'1.00'),
 (2,1000993,11,2006,'1.00'),
 (2,1000993,12,2005,'1.00'),
 (2,1000993,12,2006,'1.00'),
 (3,1000995,1,2005,'1.00'),
 (3,1000995,1,2006,'1.00'),
 (3,1000995,2,2005,'1.00'),
 (3,1000995,2,2006,'1.00'),
 (3,1000995,3,2005,'1.00'),
 (3,1000995,3,2006,'1.00'),
 (3,1000995,4,2005,'1.00'),
 (3,1000995,4,2006,'1.00'),
 (3,1000995,5,2005,'1.00'),
 (3,1000995,5,2006,'1.00');
INSERT INTO `aile` (`emplid`,`wkgid`,`calmonth`,`calyear`,`taux`) VALUES 
 (3,1000995,6,2005,'1.00'),
 (3,1000995,6,2006,'1.00'),
 (3,1000995,7,2005,'1.00'),
 (3,1000995,7,2006,'1.00'),
 (3,1000995,8,2005,'1.00'),
 (3,1000995,8,2006,'1.00'),
 (3,1000995,9,2005,'1.00'),
 (3,1000995,9,2006,'1.00'),
 (3,1000995,10,2005,'1.00'),
 (3,1000995,10,2006,'1.00'),
 (3,1000995,11,2005,'1.00'),
 (3,1000995,11,2006,'1.00'),
 (3,1000995,12,2005,'1.00'),
 (3,1000995,12,2006,'1.00');
/*!40000 ALTER TABLE `aile` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`ailecriteria`
--

DROP TABLE IF EXISTS `ailecriteria`;
CREATE TABLE `ailecriteria` (
  `ailecriteriaid` int(10) unsigned NOT NULL auto_increment,
  `ailecriteria` varchar(100) NOT NULL default '',
  PRIMARY KEY  (`ailecriteriaid`)
);

--
-- Dumping data for table `mercutio2`.`ailecriteria`
--

/*!40000 ALTER TABLE `ailecriteria` DISABLE KEYS */;
INSERT INTO `ailecriteria` (`ailecriteriaid`,`ailecriteria`) VALUES 
 (1,'Affectation'),
 (2,'Ancienneté');
/*!40000 ALTER TABLE `ailecriteria` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`aip`
--

DROP TABLE IF EXISTS `aip`;
CREATE TABLE `aip` (
  `emplid` int(10) unsigned NOT NULL default '0',
  `calmonth` int(10) unsigned NOT NULL default '0',
  `calyear` int(10) unsigned NOT NULL default '0',
  `taux` decimal(10,2) NOT NULL default '0.00',
  PRIMARY KEY  (`emplid`,`calmonth`,`calyear`)
);

--
-- Dumping data for table `mercutio2`.`aip`
--

/*!40000 ALTER TABLE `aip` DISABLE KEYS */;
/*!40000 ALTER TABLE `aip` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`aipcriteria`
--

DROP TABLE IF EXISTS `aipcriteria`;
CREATE TABLE `aipcriteria` (
  `aipcriteriaid` int(11) NOT NULL auto_increment,
  `aipcriteria` varchar(250) NOT NULL default '',
  PRIMARY KEY  (`aipcriteriaid`)
);

--
-- Dumping data for table `mercutio2`.`aipcriteria`
--

/*!40000 ALTER TABLE `aipcriteria` DISABLE KEYS */;
INSERT INTO `aipcriteria` (`aipcriteriaid`,`aipcriteria`) VALUES 
 (1,'Performance'),
 (2,'Vacances');
/*!40000 ALTER TABLE `aipcriteria` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`calendar`
--

DROP TABLE IF EXISTS `calendar`;
CREATE TABLE `calendar` (
  `calmonth` int(20) NOT NULL,
  `calyear` int(20) NOT NULL,
  `firstdayofmonth` int(20) NOT NULL,
  `lastdayofmonth` int(20) NOT NULL,
  `daysavailable` varchar(20) NOT NULL,
  PRIMARY KEY  (`calmonth`,`calyear`)
);

--
-- Dumping data for table `mercutio2`.`calendar`
--

/*!40000 ALTER TABLE `calendar` DISABLE KEYS */;
INSERT INTO `calendar` (`calmonth`,`calyear`,`firstdayofmonth`,`lastdayofmonth`,`daysavailable`) VALUES 
 (1,2006,1,31,'20'),
 (2,2006,1,28,'18'),
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
 (1,2005,1,31,'20'),
 (2,2005,1,28,'18'),
 (3,2005,1,31,'20'),
 (4,2005,1,30,'20'),
 (5,2005,1,31,'20'),
 (6,2005,1,30,'20'),
 (7,2005,1,31,'20'),
 (8,2005,1,31,'20'),
 (9,2005,1,30,'20'),
 (10,2005,1,31,'20'),
 (11,2005,1,30,'20'),
 (12,2005,1,31,'20');
/*!40000 ALTER TABLE `calendar` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`delivlog`
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
);

--
-- Dumping data for table `mercutio2`.`delivlog`
--

/*!40000 ALTER TABLE `delivlog` DISABLE KEYS */;
INSERT INTO `delivlog` (`DELIVLOGID`,`IDPROCLOG`,`DELIVID`,`MESSAGEDELIVID`,`WKGID`,`TEMPSSTANDARD`) VALUES 
 (4860,4864,10,5057,1000993,'0.0104166996'),
 (4861,4865,9,5058,1000993,'0.0312500000'),
 (4862,4866,9,5059,1000993,'0.0312500000'),
 (4863,4867,9,5060,1000993,'0.0312500000'),
 (4864,4868,9,5061,1000993,'0.0312500000'),
 (4865,4869,9,5062,1000993,'0.0312500000'),
 (4866,4870,9,5063,1000993,'0.0312500000'),
 (4867,4871,9,5064,1000993,'0.0312500000'),
 (4868,4872,9,5065,1000993,'0.0312500000'),
 (4869,4873,9,5066,1000993,'0.0312500000'),
 (4870,4874,9,5067,1000993,'0.0312500000'),
 (4871,4875,9,5068,1000993,'0.0312500000'),
 (4872,4876,9,5069,1000993,'0.0312500000'),
 (4873,4877,9,5070,1000993,'0.0312500000'),
 (4874,4878,8,5071,1000993,'0.0104166996'),
 (4875,4879,8,5072,1000993,'0.0104166996'),
 (4876,4880,8,5073,1000993,'0.0104166996'),
 (4877,4881,8,5074,1000993,'0.0104166996'),
 (4878,4882,8,5075,1000993,'0.0104166996'),
 (4879,4883,8,5076,1000993,'0.0104166996'),
 (4880,4884,8,5077,1000993,'0.0104166996'),
 (4881,4885,8,5078,1000993,'0.0104166996');
INSERT INTO `delivlog` (`DELIVLOGID`,`IDPROCLOG`,`DELIVID`,`MESSAGEDELIVID`,`WKGID`,`TEMPSSTANDARD`) VALUES 
 (4882,4886,8,5079,1000993,'0.0104166996'),
 (4883,4887,8,5080,1000993,'0.0104166996'),
 (4884,4888,8,5081,1000993,'0.0104166996'),
 (4885,4889,8,5082,1000993,'0.0104166996'),
 (4886,4890,8,5083,1000993,'0.0104166996'),
 (4887,4891,8,5084,1000993,'0.0104166996'),
 (4888,4892,8,5085,1000993,'0.0104166996'),
 (4889,4893,8,5086,1000993,'0.0104166996'),
 (4890,4894,8,5087,1000993,'0.0104166996'),
 (4891,4895,8,5088,1000993,'0.0104166996'),
 (4892,4896,8,5089,1000993,'0.0104166996'),
 (4893,4897,8,5090,1000993,'0.0104166996'),
 (4894,4898,8,5091,1000993,'0.0104166996'),
 (4895,4899,8,5092,1000993,'0.0104166996'),
 (4896,4900,18,5128,1000993,'0.0104166996'),
 (4897,4901,18,5127,1000993,'0.0104166996'),
 (4898,4902,18,5126,1000993,'0.0104166996'),
 (4899,4903,18,5125,1000993,'0.0104166996'),
 (4900,4904,18,5124,1000993,'0.0104166996'),
 (4901,4905,18,5123,1000993,'0.0104166996'),
 (4902,4906,18,5122,1000993,'0.0104166996'),
 (4903,4907,18,5121,1000993,'0.0104166996');
INSERT INTO `delivlog` (`DELIVLOGID`,`IDPROCLOG`,`DELIVID`,`MESSAGEDELIVID`,`WKGID`,`TEMPSSTANDARD`) VALUES 
 (4904,4908,18,5120,1000993,'0.0104166996'),
 (4905,4909,18,5119,1000993,'0.0104166996'),
 (4906,4910,18,5118,1000993,'0.0104166996'),
 (4907,4911,18,5117,1000993,'0.0104166996'),
 (4908,4912,18,5116,1000993,'0.0104166996'),
 (4909,4913,18,5115,1000993,'0.0104166996'),
 (4910,4914,18,5114,1000993,'0.0104166996'),
 (4911,4915,18,5113,1000993,'0.0104166996'),
 (4912,4916,18,5112,1000993,'0.0104166996'),
 (4913,4917,18,5111,1000993,'0.0104166996'),
 (4914,4918,18,5110,1000993,'0.0104166996'),
 (4915,4919,18,5109,1000993,'0.0104166996'),
 (4916,4920,18,5108,1000993,'0.0104166996'),
 (4917,4921,18,5107,1000993,'0.0104166996'),
 (4918,4922,19,5106,1000993,'0.0312500000'),
 (4919,4923,19,5105,1000993,'0.0312500000'),
 (4920,4924,19,5104,1000993,'0.0312500000'),
 (4921,4925,19,5103,1000993,'0.0312500000'),
 (4922,4926,19,5102,1000993,'0.0312500000'),
 (4923,4927,19,5101,1000993,'0.0312500000'),
 (4924,4928,19,5100,1000993,'0.0312500000');
INSERT INTO `delivlog` (`DELIVLOGID`,`IDPROCLOG`,`DELIVID`,`MESSAGEDELIVID`,`WKGID`,`TEMPSSTANDARD`) VALUES 
 (4925,4929,19,5099,1000993,'0.0312500000'),
 (4926,4930,19,5098,1000993,'0.0312500000'),
 (4927,4931,19,5097,1000993,'0.0312500000'),
 (4928,4932,19,5096,1000993,'0.0312500000'),
 (4929,4933,19,5095,1000993,'0.0312500000'),
 (4930,4934,19,5094,1000993,'0.0312500000'),
 (4931,4935,20,5093,1000993,'0.0104166996');
/*!40000 ALTER TABLE `delivlog` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`employeeaile`
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
);

--
-- Dumping data for table `mercutio2`.`employeeaile`
--

/*!40000 ALTER TABLE `employeeaile` DISABLE KEYS */;
INSERT INTO `employeeaile` (`employeeaileid`,`wkgid`,`emplid`,`ailecriteriaid`,`motif`,`taux`,`startdate`,`enddate`) VALUES 
 (1,1000993,2,1,'Affectation','1.00','2005-01-01 00:00:00','2006-12-31 00:00:00'),
 (2,1000995,3,1,'Affectation','1.00','2005-01-01 00:00:00','2006-12-31 00:00:00');
/*!40000 ALTER TABLE `employeeaile` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`employeeaip`
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
);

--
-- Dumping data for table `mercutio2`.`employeeaip`
--

/*!40000 ALTER TABLE `employeeaip` DISABLE KEYS */;
/*!40000 ALTER TABLE `employeeaip` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`employeecalendar`
--

DROP TABLE IF EXISTS `employeecalendar`;
CREATE TABLE `employeecalendar` (
  `emplid` int(20) NOT NULL,
  `calmonth` int(20) NOT NULL,
  `calyear` int(20) NOT NULL,
  `daysplanned` int(20) NOT NULL,
  PRIMARY KEY  (`emplid`,`calmonth`,`calyear`)
);

--
-- Dumping data for table `mercutio2`.`employeecalendar`
--

/*!40000 ALTER TABLE `employeecalendar` DISABLE KEYS */;
INSERT INTO `employeecalendar` (`emplid`,`calmonth`,`calyear`,`daysplanned`) VALUES 
 (2,1,2005,20),
 (2,1,2006,20),
 (2,2,2005,18),
 (2,2,2006,18),
 (2,3,2005,20),
 (2,3,2006,20),
 (2,4,2005,20),
 (2,4,2006,20),
 (2,5,2005,20),
 (2,5,2006,20),
 (2,6,2005,20),
 (2,6,2006,20),
 (2,7,2005,20),
 (2,7,2006,20),
 (2,8,2005,20),
 (2,8,2006,20),
 (2,9,2005,20),
 (2,9,2006,20),
 (2,10,2005,20),
 (2,10,2006,20),
 (2,11,2005,20),
 (2,11,2006,20),
 (2,12,2005,20),
 (2,12,2006,20),
 (3,1,2005,20),
 (3,1,2006,20),
 (3,2,2005,18),
 (3,2,2006,18),
 (3,3,2005,20),
 (3,3,2006,20),
 (3,4,2005,20),
 (3,4,2006,20),
 (3,5,2005,20),
 (3,5,2006,20),
 (3,6,2005,20),
 (3,6,2006,20),
 (3,7,2005,20),
 (3,7,2006,20),
 (3,8,2005,20),
 (3,8,2006,20),
 (3,9,2005,20),
 (3,9,2006,20),
 (3,10,2005,20),
 (3,10,2006,20),
 (3,11,2005,20),
 (3,11,2006,20),
 (3,12,2005,20),
 (3,12,2006,20);
/*!40000 ALTER TABLE `employeecalendar` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`employeetitle`
--

DROP TABLE IF EXISTS `employeetitle`;
CREATE TABLE `employeetitle` (
  `EmployeeTitleID` int(11) NOT NULL auto_increment,
  `EmployeeTitle` varchar(100) NOT NULL default '',
  PRIMARY KEY  (`EmployeeTitleID`)
);

--
-- Dumping data for table `mercutio2`.`employeetitle`
--

/*!40000 ALTER TABLE `employeetitle` DISABLE KEYS */;
INSERT INTO `employeetitle` (`EmployeeTitleID`,`EmployeeTitle`) VALUES 
 (1,'Directeur'),
 (2,'Collaborateur');
/*!40000 ALTER TABLE `employeetitle` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`eptteamauto`
--

DROP TABLE IF EXISTS `eptteamauto`;
CREATE TABLE `eptteamauto` (
  `calmonth` int(11) NOT NULL default '0',
  `calyear` int(11) NOT NULL default '0',
  `eptvalue` decimal(10,0) NOT NULL default '0',
  `wkgid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`wkgid`,`calyear`,`calmonth`)
);

--
-- Dumping data for table `mercutio2`.`eptteamauto`
--

/*!40000 ALTER TABLE `eptteamauto` DISABLE KEYS */;
/*!40000 ALTER TABLE `eptteamauto` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`eptteammanual`
--

DROP TABLE IF EXISTS `eptteammanual`;
CREATE TABLE `eptteammanual` (
  `wkgid` int(11) NOT NULL default '0',
  `calyear` int(11) NOT NULL default '0',
  `calmonth` int(11) NOT NULL default '0',
  `eptvalue` decimal(10,0) NOT NULL default '0',
  PRIMARY KEY  (`wkgid`,`calyear`,`calmonth`)
);

--
-- Dumping data for table `mercutio2`.`eptteammanual`
--

/*!40000 ALTER TABLE `eptteammanual` DISABLE KEYS */;
/*!40000 ALTER TABLE `eptteammanual` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`externdeliv`
--

DROP TABLE IF EXISTS `externdeliv`;
CREATE TABLE `externdeliv` (
  `EXTERNDELIVID` int(11) NOT NULL auto_increment,
  `EXTERNPROCID` int(11) NOT NULL default '0',
  `DELIVSTABLEID` int(11) default NULL,
  `EXTERNDELIVDESC` varchar(100) NOT NULL default '',
  `EXTERNDELIVTRANS` varchar(50) default '',
  PRIMARY KEY  (`EXTERNDELIVID`)
);

--
-- Dumping data for table `mercutio2`.`externdeliv`
--

/*!40000 ALTER TABLE `externdeliv` DISABLE KEYS */;
INSERT INTO `externdeliv` (`EXTERNDELIVID`,`EXTERNPROCID`,`DELIVSTABLEID`,`EXTERNDELIVDESC`,`EXTERNDELIVTRANS`) VALUES 
 (39,31,5,'','5'),
 (40,32,9,'','9'),
 (41,32,11,'','11'),
 (42,32,17,'','17'),
 (43,32,18,'','18'),
 (44,32,19,'','19'),
 (45,33,23,'','23');
/*!40000 ALTER TABLE `externdeliv` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`externprestation`
--

DROP TABLE IF EXISTS `externprestation`;
CREATE TABLE `externprestation` (
  `externprestationID` int(11) NOT NULL auto_increment,
  `externsystemID` int(10) unsigned NOT NULL default '0',
  `prestationID` int(10) unsigned NOT NULL default '0',
  `externprestation` varchar(45) NOT NULL default '',
  PRIMARY KEY  (`externprestationID`)
);

--
-- Dumping data for table `mercutio2`.`externprestation`
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
-- Table structure for table `mercutio2`.`externproc`
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
);

--
-- Dumping data for table `mercutio2`.`externproc`
--

/*!40000 ALTER TABLE `externproc` DISABLE KEYS */;
INSERT INTO `externproc` (`EXTERNPROCID`,`SYSTEMID`,`PROCSTABLEID`,`EXTERNPROCDESC`,`MODELREF`,`EXTERNPROCTRANS`) VALUES 
 (31,1,2,'','_:[v0]732425496-4810','2'),
 (32,1,4,'','_:[v0]732425496-4810','4'),
 (33,1,21,'','_:[v0]732425496-4810','21');
/*!40000 ALTER TABLE `externproc` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`externsystem`
--

DROP TABLE IF EXISTS `externsystem`;
CREATE TABLE `externsystem` (
  `EXTERNSYSTEMID` int(11) NOT NULL,
  `EXTERNSYSTEMDESC` varchar(25) default NULL,
  PRIMARY KEY  (`EXTERNSYSTEMID`)
);

--
-- Dumping data for table `mercutio2`.`externsystem`
--

/*!40000 ALTER TABLE `externsystem` DISABLE KEYS */;
INSERT INTO `externsystem` (`EXTERNSYSTEMID`,`EXTERNSYSTEMDESC`) VALUES 
 (1,'Systeme 1');
/*!40000 ALTER TABLE `externsystem` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`externuser`
--

DROP TABLE IF EXISTS `externuser`;
CREATE TABLE `externuser` (
  `EXTERNUSERID` int(11) NOT NULL auto_increment,
  `EXTERNSYSTEMID` int(11) default NULL,
  `EMPLID` int(11) default NULL,
  `EXTERNUSER` varchar(25) default NULL,
  PRIMARY KEY  (`EXTERNUSERID`)
);

--
-- Dumping data for table `mercutio2`.`externuser`
--

/*!40000 ALTER TABLE `externuser` DISABLE KEYS */;
INSERT INTO `externuser` (`EXTERNUSERID`,`EXTERNSYSTEMID`,`EMPLID`,`EXTERNUSER`) VALUES 
 (12,1,2,'SEPPEY'),
 (13,1,3,'FOURNIER');
/*!40000 ALTER TABLE `externuser` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`indiccasprocteam`
--

DROP TABLE IF EXISTS `indiccasprocteam`;
CREATE TABLE `indiccasprocteam` (
  `monthid` int(10) unsigned NOT NULL default '0',
  `monthdesc` varchar(20) NOT NULL default '',
  `team` varchar(50) NOT NULL default '',
  `typequantity` varchar(20) NOT NULL default '',
  `quantity` decimal(7,2) NOT NULL default '0.00'
);

--
-- Dumping data for table `mercutio2`.`indiccasprocteam`
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
-- Table structure for table `mercutio2`.`indicchargeteam`
--

DROP TABLE IF EXISTS `indicchargeteam`;
CREATE TABLE `indicchargeteam` (
  `monthid` int(10) unsigned NOT NULL default '0',
  `month` varchar(45) NOT NULL default '',
  `forecast` decimal(10,2) NOT NULL default '0.00',
  `produced` decimal(10,2) NOT NULL default '0.00',
  PRIMARY KEY  (`monthid`)
);

--
-- Dumping data for table `mercutio2`.`indicchargeteam`
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
-- Table structure for table `mercutio2`.`indiclabel`
--

DROP TABLE IF EXISTS `indiclabel`;
CREATE TABLE `indiclabel` (
  `labelyear` int(10) unsigned NOT NULL default '0',
  `labeltext` varchar(100) NOT NULL default ''
);

--
-- Dumping data for table `mercutio2`.`indiclabel`
--

/*!40000 ALTER TABLE `indiclabel` DISABLE KEYS */;
INSERT INTO `indiclabel` (`labelyear`,`labeltext`) VALUES 
 (2006,'Saisie de demande état civil');
/*!40000 ALTER TABLE `indiclabel` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`indicnbrcastraite`
--

DROP TABLE IF EXISTS `indicnbrcastraite`;
CREATE TABLE `indicnbrcastraite` (
  `monthid` int(10) unsigned NOT NULL default '0',
  `monthdesc` varchar(20) NOT NULL default '',
  `prestation` varchar(45) NOT NULL default '',
  `typequantity` varchar(45) NOT NULL default '',
  `quantity` decimal(7,2) NOT NULL default '0.00'
);

--
-- Dumping data for table `mercutio2`.`indicnbrcastraite`
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
-- Table structure for table `mercutio2`.`indicproducteam`
--

DROP TABLE IF EXISTS `indicproducteam`;
CREATE TABLE `indicproducteam` (
  `monthid` int(10) unsigned NOT NULL auto_increment,
  `month` varchar(45) NOT NULL default '',
  `forecast` decimal(10,2) NOT NULL default '0.00',
  `produced` decimal(10,2) NOT NULL default '0.00',
  PRIMARY KEY  (`monthid`)
);

--
-- Dumping data for table `mercutio2`.`indicproducteam`
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
-- Table structure for table `mercutio2`.`indicstock`
--

DROP TABLE IF EXISTS `indicstock`;
CREATE TABLE `indicstock` (
  `monthid` int(10) unsigned NOT NULL default '0',
  `month` varchar(20) NOT NULL default '',
  `forecast` int(10) unsigned NOT NULL default '0',
  `produced` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`monthid`)
);

--
-- Dumping data for table `mercutio2`.`indicstock`
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
-- Table structure for table `mercutio2`.`message`
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
);

--
-- Dumping data for table `mercutio2`.`message`
--

/*!40000 ALTER TABLE `message` DISABLE KEYS */;
/*!40000 ALTER TABLE `message` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`messagedeliv`
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
);

--
-- Dumping data for table `mercutio2`.`messagedeliv`
--

/*!40000 ALTER TABLE `messagedeliv` DISABLE KEYS */;
/*!40000 ALTER TABLE `messagedeliv` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`messagedelivlog`
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
);

--
-- Dumping data for table `mercutio2`.`messagedelivlog`
--

/*!40000 ALTER TABLE `messagedelivlog` DISABLE KEYS */;
INSERT INTO `messagedelivlog` (`MESSAGEDELIVID`,`IDMESSAGEINTERNE`,`EXTERNDELIVTRANS`,`EXTERNUSERID`,`TIMESTAMPDELIV`,`DOUBLECONTROL`) VALUES 
 (5057,5058,'19','SEPPEY','2005-01-03 15:48:27',0),
 (5058,5059,'18','SEPPEY','2005-01-03 16:05:42',0),
 (5059,5060,'18','SEPPEY','2005-01-03 16:07:56',0),
 (5060,5061,'18','SEPPEY','2005-01-04 11:30:33',0),
 (5061,5062,'18','SEPPEY','2005-01-04 15:28:24',0),
 (5062,5063,'18','SEPPEY','2005-01-08 20:04:07',0),
 (5063,5064,'18','SEPPEY','2005-01-05 11:44:00',0),
 (5064,5065,'18','SEPPEY','2005-01-06 12:32:02',0),
 (5065,5066,'18','SEPPEY','2005-01-12 22:51:08',0),
 (5066,5067,'18','SEPPEY','2005-01-09 15:17:33',0),
 (5067,5068,'18','SEPPEY','2005-01-13 13:21:03',0),
 (5068,5069,'18','SEPPEY','2005-01-13 22:34:05',0),
 (5069,5070,'18','SEPPEY','2005-01-10 10:37:24',0),
 (5070,5071,'18','SEPPEY','2005-01-10 15:22:02',0),
 (5071,5072,'17','SEPPEY','2005-01-10 16:19:05',0),
 (5072,5073,'17','SEPPEY','2005-01-11 14:48:58',0),
 (5073,5074,'17','SEPPEY','2005-01-11 15:38:24',0),
 (5074,5075,'17','SEPPEY','2005-01-12 10:08:49',0);
INSERT INTO `messagedelivlog` (`MESSAGEDELIVID`,`IDMESSAGEINTERNE`,`EXTERNDELIVTRANS`,`EXTERNUSERID`,`TIMESTAMPDELIV`,`DOUBLECONTROL`) VALUES 
 (5075,5076,'17','SEPPEY','2005-01-13 13:23:42',0),
 (5076,5077,'17','SEPPEY','2005-01-19 21:24:04',0),
 (5077,5078,'17','SEPPEY','2005-01-16 12:10:23',0),
 (5078,5079,'17','SEPPEY','2005-01-16 15:58:36',0),
 (5079,5080,'17','SEPPEY','2005-01-16 16:45:04',0),
 (5080,5081,'17','SEPPEY','2005-01-16 17:13:34',0),
 (5081,5082,'17','SEPPEY','2005-01-20 22:13:01',0),
 (5082,5083,'17','SEPPEY','2005-01-17 14:15:44',0),
 (5083,5084,'17','SEPPEY','2005-01-17 14:24:30',0),
 (5084,5085,'17','SEPPEY','2005-01-17 15:31:58',0),
 (5085,5086,'17','SEPPEY','2005-01-17 15:31:58',0),
 (5086,5087,'17','SEPPEY','2005-01-17 15:31:58',0),
 (5087,5088,'17','SEPPEY','2005-01-17 15:31:58',0),
 (5088,5089,'17','SEPPEY','2005-01-17 15:31:58',0),
 (5089,5090,'17','SEPPEY','2005-01-17 15:31:58',0),
 (5090,5091,'17','SEPPEY','2005-01-17 15:31:58',0),
 (5091,5092,'17','SEPPEY','2005-01-17 15:31:58',0),
 (5092,5093,'17','SEPPEY','2005-01-17 15:31:58',0);
INSERT INTO `messagedelivlog` (`MESSAGEDELIVID`,`IDMESSAGEINTERNE`,`EXTERNDELIVTRANS`,`EXTERNUSERID`,`TIMESTAMPDELIV`,`DOUBLECONTROL`) VALUES 
 (5093,5094,'19','SEPPEY','2006-01-03 15:48:27',0),
 (5094,5095,'18','SEPPEY','2006-01-03 16:05:42',0),
 (5095,5096,'18','SEPPEY','2006-01-03 16:07:56',0),
 (5096,5097,'18','SEPPEY','2006-01-04 11:30:33',0),
 (5097,5098,'18','SEPPEY','2006-01-04 15:28:24',0),
 (5098,5099,'18','SEPPEY','2006-01-08 20:04:07',0),
 (5099,5100,'18','SEPPEY','2006-01-05 11:44:00',0),
 (5100,5101,'18','SEPPEY','2006-01-06 12:32:02',0),
 (5101,5102,'18','SEPPEY','2006-01-12 22:51:08',0),
 (5102,5103,'18','SEPPEY','2006-01-09 15:17:33',0),
 (5103,5104,'18','SEPPEY','2006-01-13 13:21:03',0),
 (5104,5105,'18','SEPPEY','2006-01-13 22:34:05',0),
 (5105,5106,'18','SEPPEY','2006-01-10 10:37:24',0),
 (5106,5107,'18','SEPPEY','2006-01-10 15:22:02',0),
 (5107,5108,'17','SEPPEY','2006-01-10 16:19:05',0),
 (5108,5109,'17','SEPPEY','2006-01-11 14:48:58',0),
 (5109,5110,'17','SEPPEY','2006-01-11 15:38:24',0),
 (5110,5111,'17','SEPPEY','2006-01-12 10:08:49',0);
INSERT INTO `messagedelivlog` (`MESSAGEDELIVID`,`IDMESSAGEINTERNE`,`EXTERNDELIVTRANS`,`EXTERNUSERID`,`TIMESTAMPDELIV`,`DOUBLECONTROL`) VALUES 
 (5111,5112,'17','SEPPEY','2006-01-13 13:23:42',0),
 (5112,5113,'17','SEPPEY','2006-01-19 21:24:04',0),
 (5113,5114,'17','SEPPEY','2006-01-16 12:10:23',0),
 (5114,5115,'17','SEPPEY','2006-01-16 15:58:36',0),
 (5115,5116,'17','SEPPEY','2006-01-16 16:45:04',0),
 (5116,5117,'17','SEPPEY','2006-01-16 17:13:34',0),
 (5117,5118,'17','SEPPEY','2006-01-20 22:13:01',0),
 (5118,5119,'17','SEPPEY','2006-01-17 14:15:44',0),
 (5119,5120,'17','SEPPEY','2006-01-17 14:24:30',0),
 (5120,5121,'17','SEPPEY','2006-01-17 15:31:58',0),
 (5121,5122,'17','SEPPEY','2006-01-17 15:31:58',0),
 (5122,5123,'17','SEPPEY','2006-01-17 15:31:58',0),
 (5123,5124,'17','SEPPEY','2006-01-17 15:31:58',0),
 (5124,5125,'17','SEPPEY','2006-01-17 15:31:58',0),
 (5125,5126,'17','SEPPEY','2006-01-17 15:31:58',0),
 (5126,5127,'17','SEPPEY','2006-01-17 15:31:58',0),
 (5127,5128,'17','SEPPEY','2006-01-17 15:31:58',0),
 (5128,5129,'17','SEPPEY','2006-01-17 15:31:58',0);
/*!40000 ALTER TABLE `messagedelivlog` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`messageerror`
--

DROP TABLE IF EXISTS `messageerror`;
CREATE TABLE `messageerror` (
  `MESSAGEERRORID` int(11) NOT NULL,
  `ERRORDESCRIPTION` varchar(255) default NULL,
  PRIMARY KEY  (`MESSAGEERRORID`)
);

--
-- Dumping data for table `mercutio2`.`messageerror`
--

/*!40000 ALTER TABLE `messageerror` DISABLE KEYS */;
/*!40000 ALTER TABLE `messageerror` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`messagelog`
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
);

--
-- Dumping data for table `mercutio2`.`messagelog`
--

/*!40000 ALTER TABLE `messagelog` DISABLE KEYS */;
INSERT INTO `messagelog` (`IDMESSAGEINTERNE`,`EXTERNMESSAGEID`,`EXTERNSYSTEMID`,`EXTERNPROCTRANS`,`EXTERNUSERID`,`TIMESTAMPPROC`,`MESSAGETIME`,`STATUT`,`CASEID`,`CASEIDREMARK`,`PRESTATIONID`) VALUES 
 (5058,'CH06000444',1,'4','SEPPEY','2005-01-04 11:24:38','2005-01-03 15:48:27',1,10,'aucune',1),
 (5059,'CH06000464',1,'4','SEPPEY','2005-01-03 17:09:41','2005-01-03 16:05:42',1,10,'aucune',1),
 (5060,'CH06000467',1,'4','SEPPEY','2005-01-04 11:35:47','2005-01-03 16:07:56',1,10,'aucune',1),
 (5061,'CH06000686',1,'4','SEPPEY','2005-01-04 12:16:39','2005-01-04 11:30:33',1,10,'aucune',1),
 (5062,'CH06000807',1,'4','SEPPEY','2005-05-22 12:20:15','2005-01-04 15:28:24',1,10,'aucune',1),
 (5063,'CH06000933',1,'4','SEPPEY','2005-01-05 14:11:00','2005-01-08 20:04:07',1,10,'aucune',1),
 (5064,'CH06001022',1,'4','SEPPEY','2005-01-05 12:20:33','2005-01-05 11:44:00',1,10,'aucune',1),
 (5065,'CH06001239',1,'4','SEPPEY','2005-01-12 10:48:05','2005-01-06 12:32:02',1,10,'aucune',1),
 (5066,'CH06001428',1,'4','SEPPEY','2005-01-09 15:07:09','2005-01-12 22:51:08',1,10,'aucune',1),
 (5067,'CH06001629',1,'4','SEPPEY','2005-01-09 15:45:25','2005-01-09 15:17:33',1,10,'aucune',1);
INSERT INTO `messagelog` (`IDMESSAGEINTERNE`,`EXTERNMESSAGEID`,`EXTERNSYSTEMID`,`EXTERNPROCTRANS`,`EXTERNUSERID`,`TIMESTAMPPROC`,`MESSAGETIME`,`STATUT`,`CASEID`,`CASEIDREMARK`,`PRESTATIONID`) VALUES 
 (5068,'CH06001709',1,'4','SEPPEY','2005-01-10 10:03:50','2005-01-13 13:21:03',1,10,'aucune',1),
 (5069,'CH06001762',1,'4','SEPPEY','2005-01-10 11:49:38','2005-01-13 22:34:05',1,10,'aucune',1),
 (5070,'CH06001870',1,'4','SEPPEY','2005-02-03 10:56:53','2005-01-10 10:37:24',1,10,'aucune',1),
 (5071,'CH06001992',1,'4','SEPPEY','2005-01-10 15:59:24','2005-01-10 15:22:02',1,10,'aucune',1),
 (5072,'CH06002090',1,'4','SEPPEY','2005-01-10 16:53:21','2005-01-10 16:19:05',1,10,'aucune',1),
 (5073,'CH06002525',1,'4','SEPPEY','2005-01-11 15:37:17','2005-01-11 14:48:58',1,10,'aucune',1),
 (5074,'CH06002553',1,'4','SEPPEY','2005-01-23 16:30:37','2005-01-11 15:38:24',1,10,'aucune',1),
 (5075,'CH06002740',1,'4','SEPPEY','2005-01-12 11:32:00','2005-01-12 10:08:49',1,10,'aucune',1),
 (5076,'CH06003369',1,'4','SEPPEY','2005-01-13 14:54:41','2005-01-13 13:23:42',1,10,'aucune',1),
 (5077,'CH06003510',1,'4','SEPPEY','2005-01-16 15:40:04','2005-01-19 21:24:04',1,10,'aucune',1);
INSERT INTO `messagelog` (`IDMESSAGEINTERNE`,`EXTERNMESSAGEID`,`EXTERNSYSTEMID`,`EXTERNPROCTRANS`,`EXTERNUSERID`,`TIMESTAMPPROC`,`MESSAGETIME`,`STATUT`,`CASEID`,`CASEIDREMARK`,`PRESTATIONID`) VALUES 
 (5078,'CH06003659',1,'4','SEPPEY','2005-02-13 12:37:18','2005-01-16 12:10:23',1,10,'aucune',1),
 (5079,'CH06003796',1,'4','SEPPEY','2005-01-20 13:04:03','2005-01-16 15:58:36',1,10,'aucune',1),
 (5080,'CH06003832',1,'4','SEPPEY','2005-01-20 22:23:01','2005-01-16 16:45:04',1,10,'aucune',1),
 (5081,'CH06003855',1,'4','SEPPEY','2005-01-23 10:18:26','2005-01-16 17:13:34',1,10,'aucune',1),
 (5082,'CH06003931',1,'4','SEPPEY','2005-01-17 10:21:47','2005-01-20 22:13:01',1,10,'aucune',1),
 (5083,'CH06004089',1,'4','SEPPEY','2005-01-17 16:28:08','2005-01-17 14:15:44',1,10,'aucune',1),
 (5084,'CH06004093',1,'4','SEPPEY','2005-01-17 16:29:37','2005-01-17 14:24:30',1,10,'aucune',1),
 (5085,'CH06004138',1,'4','SEPPEY','2005-01-18 16:42:15','2005-01-17 15:31:58',1,10,'aucune',1),
 (5086,'CH06004138',1,'4','SEPPEY','2005-01-18 16:42:15','2005-01-17 15:31:58',1,10,'aucune',1),
 (5087,'CH06004138',1,'4','SEPPEY','2005-01-18 16:42:15','2005-01-17 15:31:58',1,10,'aucune',1);
INSERT INTO `messagelog` (`IDMESSAGEINTERNE`,`EXTERNMESSAGEID`,`EXTERNSYSTEMID`,`EXTERNPROCTRANS`,`EXTERNUSERID`,`TIMESTAMPPROC`,`MESSAGETIME`,`STATUT`,`CASEID`,`CASEIDREMARK`,`PRESTATIONID`) VALUES 
 (5088,'CH06004138',1,'4','SEPPEY','2005-01-18 16:42:15','2005-01-17 15:31:58',1,10,'aucune',1),
 (5089,'CH06004138',1,'4','SEPPEY','2005-01-18 16:42:15','2005-01-17 15:31:58',1,10,'aucune',1),
 (5090,'CH06004138',1,'4','SEPPEY','2005-01-18 16:42:15','2005-01-17 15:31:58',1,10,'aucune',1),
 (5091,'CH06004138',1,'4','SEPPEY','2005-01-18 16:42:15','2005-01-17 15:31:58',1,10,'aucune',1),
 (5092,'CH06004138',1,'4','SEPPEY','2005-01-18 16:42:15','2005-01-17 15:31:58',1,10,'aucune',1),
 (5093,'CH06004138',1,'4','SEPPEY','2005-01-18 16:42:15','2005-01-17 15:31:58',1,10,'aucune',1),
 (5094,'CH06000444',1,'4','SEPPEY','2006-01-04 11:24:38','2006-01-03 15:48:27',1,10,'aucune',1),
 (5095,'CH06000464',1,'4','SEPPEY','2006-01-03 17:09:41','2006-01-03 16:05:42',1,10,'aucune',1),
 (5096,'CH06000467',1,'4','SEPPEY','2006-01-04 11:35:47','2006-01-03 16:07:56',1,10,'aucune',1),
 (5097,'CH06000686',1,'4','SEPPEY','2006-01-04 12:16:39','2006-01-04 11:30:33',1,10,'aucune',1);
INSERT INTO `messagelog` (`IDMESSAGEINTERNE`,`EXTERNMESSAGEID`,`EXTERNSYSTEMID`,`EXTERNPROCTRANS`,`EXTERNUSERID`,`TIMESTAMPPROC`,`MESSAGETIME`,`STATUT`,`CASEID`,`CASEIDREMARK`,`PRESTATIONID`) VALUES 
 (5098,'CH06000807',1,'4','SEPPEY','2006-05-22 12:20:15','2006-01-04 15:28:24',1,10,'aucune',1),
 (5099,'CH06000933',1,'4','SEPPEY','2006-01-05 14:11:00','2006-01-08 20:04:07',1,10,'aucune',1),
 (5100,'CH06001022',1,'4','SEPPEY','2006-01-05 12:20:33','2006-01-05 11:44:00',1,10,'aucune',1),
 (5101,'CH06001239',1,'4','SEPPEY','2006-01-12 10:48:05','2006-01-06 12:32:02',1,10,'aucune',1),
 (5102,'CH06001428',1,'4','SEPPEY','2006-01-09 15:07:09','2006-01-12 22:51:08',1,10,'aucune',1),
 (5103,'CH06001629',1,'4','SEPPEY','2006-01-09 15:45:25','2006-01-09 15:17:33',1,10,'aucune',1),
 (5104,'CH06001709',1,'4','SEPPEY','2006-01-10 10:03:50','2006-01-13 13:21:03',1,10,'aucune',1),
 (5105,'CH06001762',1,'4','SEPPEY','2006-01-10 11:49:38','2006-01-13 22:34:05',1,10,'aucune',1),
 (5106,'CH06001870',1,'4','SEPPEY','2006-02-03 10:56:53','2006-01-10 10:37:24',1,10,'aucune',1),
 (5107,'CH06001992',1,'4','SEPPEY','2006-01-10 15:59:24','2006-01-10 15:22:02',1,10,'aucune',1);
INSERT INTO `messagelog` (`IDMESSAGEINTERNE`,`EXTERNMESSAGEID`,`EXTERNSYSTEMID`,`EXTERNPROCTRANS`,`EXTERNUSERID`,`TIMESTAMPPROC`,`MESSAGETIME`,`STATUT`,`CASEID`,`CASEIDREMARK`,`PRESTATIONID`) VALUES 
 (5108,'CH06002090',1,'4','SEPPEY','2006-01-10 16:53:21','2006-01-10 16:19:05',1,10,'aucune',1),
 (5109,'CH06002525',1,'4','SEPPEY','2006-01-11 15:37:17','2006-01-11 14:48:58',1,10,'aucune',1),
 (5110,'CH06002553',1,'4','SEPPEY','2006-01-23 16:30:37','2006-01-11 15:38:24',1,10,'aucune',1),
 (5111,'CH06002740',1,'4','SEPPEY','2006-01-12 11:32:00','2006-01-12 10:08:49',1,10,'aucune',1),
 (5112,'CH06003369',1,'4','SEPPEY','2006-01-13 14:54:41','2006-01-13 13:23:42',1,10,'aucune',1),
 (5113,'CH06003510',1,'4','SEPPEY','2006-01-16 15:40:04','2006-01-19 21:24:04',1,10,'aucune',1),
 (5114,'CH06003659',1,'4','SEPPEY','2006-02-13 12:37:18','2006-01-16 12:10:23',1,10,'aucune',1),
 (5115,'CH06003796',1,'4','SEPPEY','2006-01-20 13:04:03','2006-01-16 15:58:36',1,10,'aucune',1),
 (5116,'CH06003832',1,'4','SEPPEY','2006-01-20 22:23:01','2006-01-16 16:45:04',1,10,'aucune',1),
 (5117,'CH06003855',1,'4','SEPPEY','2006-01-23 10:18:26','2006-01-16 17:13:34',1,10,'aucune',1);
INSERT INTO `messagelog` (`IDMESSAGEINTERNE`,`EXTERNMESSAGEID`,`EXTERNSYSTEMID`,`EXTERNPROCTRANS`,`EXTERNUSERID`,`TIMESTAMPPROC`,`MESSAGETIME`,`STATUT`,`CASEID`,`CASEIDREMARK`,`PRESTATIONID`) VALUES 
 (5118,'CH06003931',1,'4','SEPPEY','2006-01-17 10:21:47','2006-01-20 22:13:01',1,10,'aucune',1),
 (5119,'CH06004089',1,'4','SEPPEY','2006-01-17 16:28:08','2006-01-17 14:15:44',1,10,'aucune',1),
 (5120,'CH06004093',1,'4','SEPPEY','2006-01-17 16:29:37','2006-01-17 14:24:30',1,10,'aucune',1),
 (5121,'CH06004138',1,'4','SEPPEY','2006-01-18 16:42:15','2006-01-17 15:31:58',1,10,'aucune',1),
 (5122,'CH06004138',1,'4','SEPPEY','2006-01-18 16:42:15','2006-01-17 15:31:58',1,10,'aucune',1),
 (5123,'CH06004138',1,'4','SEPPEY','2006-01-18 16:42:15','2006-01-17 15:31:58',1,10,'aucune',1),
 (5124,'CH06004138',1,'4','SEPPEY','2006-01-18 16:42:15','2006-01-17 15:31:58',1,10,'aucune',1),
 (5125,'CH06004138',1,'4','SEPPEY','2006-01-18 16:42:15','2006-01-17 15:31:58',1,10,'aucune',1),
 (5126,'CH06004138',1,'4','SEPPEY','2006-01-18 16:42:15','2006-01-17 15:31:58',1,10,'aucune',1),
 (5127,'CH06004138',1,'4','SEPPEY','2006-01-18 16:42:15','2006-01-17 15:31:58',1,10,'aucune',1);
INSERT INTO `messagelog` (`IDMESSAGEINTERNE`,`EXTERNMESSAGEID`,`EXTERNSYSTEMID`,`EXTERNPROCTRANS`,`EXTERNUSERID`,`TIMESTAMPPROC`,`MESSAGETIME`,`STATUT`,`CASEID`,`CASEIDREMARK`,`PRESTATIONID`) VALUES 
 (5128,'CH06004138',1,'4','SEPPEY','2006-01-18 16:42:15','2006-01-17 15:31:58',1,10,'aucune',1),
 (5129,'CH06004138',1,'4','SEPPEY','2006-01-18 16:42:15','2006-01-17 15:31:58',1,10,'aucune',1);
/*!40000 ALTER TABLE `messagelog` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pattach`
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
);

--
-- Dumping data for table `mercutio2`.`pattach`
--

/*!40000 ALTER TABLE `pattach` DISABLE KEYS */;
/*!40000 ALTER TABLE `pattach` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pattribdef`
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
);

--
-- Dumping data for table `mercutio2`.`pattribdef`
--

/*!40000 ALTER TABLE `pattribdef` DISABLE KEYS */;
INSERT INTO `pattribdef` (`attribdefid`,`attribgrpid`,`attribdefname`,`attribdeftype`,`attribreq`) VALUES 
 (1310721,1,'Nom',1,1),
 (1310722,2,'Description',1,1),
 (1310723,3,'Référence',2,1),
 (2621441,1,'Cas de gestion',1,1),
 (73400321,1,'Nom',1,1),
 (73400322,2,'Pourcentage',2,1),
 (73400323,3,'Prest. du proces.',2,1),
 (73400324,4,'Identifiant',1,1),
 (39321601,1,'Charge',2,1),
 (39321602,2,'Coût',2,1),
 (39321603,3,'Coût HMO',2,1),
 (39321604,4,'Somme livraisons',2,1),
 (39321605,5,'Charge / Livraison',3,1),
 (39321606,6,'Coût / Livraison',2,1),
 (76021761,1,'Titre livraison',1,1),
 (76021762,2,'Livrables',1,1),
 (76021763,3,'Quantité',2,1),
 (76021764,4,'Pourcentage',2,1),
 (76021765,5,'Principal',1,1),
 (26214403,3,'Guid',1,1),
 (26214401,1,'Unité',1,1),
 (26214402,2,'Coût',2,1),
 (47185921,1,'Titre Sys.',1,1),
 (20971521,1,'Titre lien',1,1),
 (20971522,2,'Lien',1,1),
 (68157441,1,'Règle 1',1,1),
 (68157461,21,'Règle 2',1,1),
 (68157481,41,'Règle 3',1,1),
 (68157501,61,'Règle 4',1,1),
 (68157521,81,'Règle 5',1,1);
INSERT INTO `pattribdef` (`attribdefid`,`attribgrpid`,`attribdefname`,`attribdeftype`,`attribreq`) VALUES 
 (68157541,101,'Règle 6',1,1),
 (68157561,121,'Règle 7',1,1),
 (68157581,141,'Règle 8',1,1),
 (68157601,161,'Règle 9',1,1),
 (68157621,181,'Règle 10',1,1),
 (68157641,201,'Règle 11',1,1),
 (68157661,221,'Règle 12',1,1),
 (68157681,241,'Règle 13',1,1),
 (68157701,261,'Règle 14',1,1),
 (68157721,281,'Règle 15',1,1),
 (68157741,301,'Règle 16',1,1),
 (68157761,321,'Règle 17',1,1),
 (68157781,341,'Règle 18',1,1),
 (68157801,361,'Règle 19',1,1),
 (68157821,381,'Règle 20',1,1),
 (41943041,1,'Tâche 1',1,1),
 (41943061,21,'Tâche 2',1,1),
 (41943081,41,'Tâche 3',1,1),
 (41943101,61,'Tâche 4',1,1),
 (41943121,81,'Tâche 5',1,1),
 (41943141,101,'Tâche 6',1,1),
 (41943161,121,'Tâche 7',1,1),
 (41943181,141,'Tâche 8',1,1),
 (41943201,161,'Tâche 9',1,1),
 (41943221,181,'Tâche 10',1,1),
 (41943241,201,'Tâche 11',1,1),
 (41943261,221,'Tâche 12',1,1),
 (41943281,241,'Tâche 13',1,1),
 (41943301,261,'Tâche 14',1,1);
INSERT INTO `pattribdef` (`attribdefid`,`attribgrpid`,`attribdefname`,`attribdeftype`,`attribreq`) VALUES 
 (41943321,281,'Tâche 15',1,1),
 (41943341,301,'Tâche 16',1,1),
 (41943361,321,'Tâche 17',1,1),
 (41943381,341,'Tâche 18',1,1),
 (41943401,361,'Tâche 19',1,1),
 (41943421,381,'Tâche 20',1,1),
 (43253761,1,'Décision 1',1,1),
 (43253781,21,'Décision 2',1,1),
 (43253801,41,'Décision 3',1,1),
 (43253821,61,'Décision 4',1,1),
 (43253841,81,'Décision 5',1,1),
 (43253861,101,'Décision 6',1,1),
 (43253881,121,'Décision 7',1,1),
 (43253901,141,'Décision 8',1,1),
 (43253921,161,'Décision 9',1,1),
 (43253941,181,'Décision 10',1,1),
 (43253961,201,'Décision 11',1,1),
 (43253981,221,'Décision 12',1,1),
 (43254001,241,'Décision 13',1,1),
 (43254021,261,'Décision 14',1,1),
 (43254041,281,'Décision 15',1,1),
 (43254061,301,'Décision 16',1,1),
 (43254081,321,'Décision 17',1,1),
 (43254101,341,'Décision 18',1,1),
 (43254121,361,'Décision 19',1,1),
 (43254141,381,'Décision 20',1,1),
 (18350081,1,'Multiplicateur',2,1);
INSERT INTO `pattribdef` (`attribdefid`,`attribgrpid`,`attribdefname`,`attribdeftype`,`attribreq`) VALUES 
 (18350082,2,'Temps standard',2,1),
 (18350083,3,'Coût unitaire',2,1),
 (18350084,4,'Durée moyenne (pondérée)',2,1),
 (18350085,5,'Durée moyenne (maximum)',2,1),
 (26214404,4,'Double validation',2,1),
 (31457281,1,'Titre Comb.',1,1),
 (31457282,2,'Livrables',1,1),
 (31457283,3,'Pourcentage',2,1),
 (31457284,4,'Maître',1,1),
 (36700161,1,'Activation',2,1),
 (36700162,2,'Coût HMO',2,1),
 (36700163,3,'Charge',2,1),
 (36700164,4,'Coût',2,1),
 (36700165,5,'Charge / activation',2,1),
 (36700166,6,'Coût / activation',2,1),
 (44564481,1,'Information 1',1,1),
 (44564501,21,'Information 2',1,1),
 (44564521,41,'Information 3',1,1),
 (44564541,61,'Information 4',1,1),
 (44564561,81,'Information 5',1,1),
 (44564581,101,'Information 6',1,1),
 (44564601,121,'Information 7',1,1),
 (44564621,141,'Information 8',1,1),
 (44564641,161,'Information 9',1,1),
 (44564661,181,'Information 10',1,1),
 (44564681,201,'Information 11',1,1);
INSERT INTO `pattribdef` (`attribdefid`,`attribgrpid`,`attribdefname`,`attribdeftype`,`attribreq`) VALUES 
 (44564701,221,'Information 12',1,1),
 (44564721,241,'Information 13',1,1),
 (44564741,261,'Information 14',1,1),
 (44564761,281,'Information 15',1,1),
 (44564781,301,'Information 16',1,1),
 (44564801,321,'Information 17',1,1),
 (44564821,341,'Information 18',1,1),
 (44564841,361,'Information 19',1,1),
 (44564861,381,'Information 20',1,1),
 (15728641,1,'Temps standard',2,1),
 (15728643,3,'% en sortie',2,1),
 (15728644,4,'Coût unitaire',2,1),
 (15728645,5,'Age du cas (pondéré)',2,1),
 (15728648,8,'Age du cas (maximum)',2,1),
 (15728646,6,'Durée cible',2,1),
 (15728647,7,'Ligne verte',2,1),
 (49807361,1,'Quantité',2,1),
 (49807374,14,'Bloquer',2,1),
 (49807387,27,'Forcer',2,1),
 (49807362,2,'Quantité Janvier',2,1),
 (49807375,15,'Bloquer Janvier',2,1),
 (49807363,3,'Quantité Février',2,1),
 (49807376,16,'Bloquer Février',2,1),
 (49807364,4,'Quantité Mars',2,1),
 (49807377,17,'Bloquer Mars',2,1),
 (49807365,5,'Quantité Avril',2,1);
INSERT INTO `pattribdef` (`attribdefid`,`attribgrpid`,`attribdefname`,`attribdeftype`,`attribreq`) VALUES 
 (49807378,18,'Bloquer Avril',2,1),
 (49807366,6,'Quantité Mai',2,1),
 (49807379,19,'Bloquer Mai',2,1),
 (49807367,7,'Quantité Juin',2,1),
 (49807380,20,'Bloquer Juin',2,1),
 (49807368,8,'Quantité Juillet',2,1),
 (49807381,21,'Bloquer Juillet',2,1),
 (49807369,9,'Quantité Août',2,1),
 (49807382,22,'Bloquer Août',2,1),
 (49807370,10,'Quantité Septembre',2,1),
 (49807383,23,'Bloquer Septembre',2,1),
 (49807371,11,'Quantité Octobre',2,1),
 (49807384,24,'Bloquer Octobre',2,1),
 (49807372,12,'Quantité Novembre',2,1),
 (49807385,25,'Bloquer Novembre',2,1),
 (49807373,13,'Quantité Décembre',2,1),
 (49807386,26,'Bloquer Décembre',2,1),
 (34078721,1,'Coût',2,1),
 (34078722,2,'Charge de travail',3,1);
/*!40000 ALTER TABLE `pattribdef` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pattribgrp`
--

DROP TABLE IF EXISTS `pattribgrp`;
CREATE TABLE `pattribgrp` (
  `attribgrpid` int(11) NOT NULL default '0',
  `attribgrpname` varchar(255) default NULL,
  PRIMARY KEY  (`attribgrpid`)
);

--
-- Dumping data for table `mercutio2`.`pattribgrp`
--

/*!40000 ALTER TABLE `pattribgrp` DISABLE KEYS */;
/*!40000 ALTER TABLE `pattribgrp` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pattribtype`
--

DROP TABLE IF EXISTS `pattribtype`;
CREATE TABLE `pattribtype` (
  `attribtypeid` int(11) NOT NULL default '0',
  `attribtypename` varchar(255) default NULL,
  `cfrmt` varchar(255) default NULL,
  PRIMARY KEY  (`attribtypeid`)
);

--
-- Dumping data for table `mercutio2`.`pattribtype`
--

/*!40000 ALTER TABLE `pattribtype` DISABLE KEYS */;
/*!40000 ALTER TABLE `pattribtype` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pcase`
--

DROP TABLE IF EXISTS `pcase`;
CREATE TABLE `pcase` (
  `caseid` int(11) NOT NULL default '0',
  `txindate` datetime NOT NULL default '0000-00-00 00:00:00',
  `casename` varchar(255) default NULL,
  PRIMARY KEY  (`caseid`),
  KEY `pcase_idx1` (`casename`),
  KEY `pcase_idx2` (`txindate`)
);

--
-- Dumping data for table `mercutio2`.`pcase`
--

/*!40000 ALTER TABLE `pcase` DISABLE KEYS */;
/*!40000 ALTER TABLE `pcase` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pclsidmapper`
--

DROP TABLE IF EXISTS `pclsidmapper`;
CREATE TABLE `pclsidmapper` (
  `mid` int(11) NOT NULL default '0',
  `clsid` varchar(128) NOT NULL default '',
  PRIMARY KEY  (`mid`),
  KEY `pclsidmapper_idx1` (`clsid`)
);

--
-- Dumping data for table `mercutio2`.`pclsidmapper`
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
-- Table structure for table `mercutio2`.`pdecisionstatus`
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
);

--
-- Dumping data for table `mercutio2`.`pdecisionstatus`
--

/*!40000 ALTER TABLE `pdecisionstatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `pdecisionstatus` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pdeliv`
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
);

--
-- Dumping data for table `mercutio2`.`pdeliv`
--

/*!40000 ALTER TABLE `pdeliv` DISABLE KEYS */;
INSERT INTO `pdeliv` (`delivid`,`modelid`,`procidsrc`,`procidtrg`,`pdattribid`,`delivname`,`lateral`,`lateraldirection`,`doublesign`,`delivstableid`) VALUES 
 (1,1,2,4,5,'Demande état civil',0,0,0,5),
 (2,1,3,4,6,'Demande état civil',0,0,0,6),
 (3,1,4,6,9,'Demande payement émolument',1,1,0,9),
 (4,1,6,4,10,'Payement émolument',0,0,0,10),
 (5,1,4,5,11,'Facture état civil',1,3,0,11),
 (6,1,5,4,12,'Payement facture état civil',0,0,0,12),
 (7,1,5,4,13,'Absence de payement état civil',0,0,0,13),
 (8,1,4,8,17,'Acte état civil posté',0,0,0,17),
 (9,1,4,9,18,'Acte état civil remis',0,0,0,18),
 (10,1,4,7,19,'Demande état civil sans suite',0,0,0,19),
 (11,2,11,13,5,'Demande état civil (d)',0,0,0,5),
 (12,2,12,13,6,'Demande état civil (g)',0,0,0,6),
 (13,2,13,15,9,'Demande payement émolument',1,1,0,9),
 (14,2,15,13,10,'Payement émolument',0,0,0,10),
 (15,2,13,14,11,'Facture état civil',1,3,0,11),
 (16,2,14,13,12,'Payement facture état civil',0,0,0,12),
 (17,2,14,13,13,'Absence de payement état civil',0,0,0,13),
 (18,2,13,17,17,'Acte état civil posté',0,0,0,17);
INSERT INTO `pdeliv` (`delivid`,`modelid`,`procidsrc`,`procidtrg`,`pdattribid`,`delivname`,`lateral`,`lateraldirection`,`doublesign`,`delivstableid`) VALUES 
 (19,2,13,18,18,'Acte état civil remis',0,0,0,18),
 (20,2,13,16,19,'Demande état civil sans suite',0,0,0,19),
 (21,2,19,20,22,'Demande état civil en ligne',0,0,0,22),
 (22,2,20,13,23,'Demande état civil validée par système (l)',0,0,0,23);
/*!40000 ALTER TABLE `pdeliv` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pdelivlateralstate`
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
);

--
-- Dumping data for table `mercutio2`.`pdelivlateralstate`
--

/*!40000 ALTER TABLE `pdelivlateralstate` DISABLE KEYS */;
/*!40000 ALTER TABLE `pdelivlateralstate` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pdelivstable`
--

DROP TABLE IF EXISTS `pdelivstable`;
CREATE TABLE `pdelivstable` (
  `DELIVSTABLEID` int(11) NOT NULL,
  `DELIVSTABLEDESC` varchar(35) default NULL,
  PRIMARY KEY  (`DELIVSTABLEID`)
);

--
-- Dumping data for table `mercutio2`.`pdelivstable`
--

/*!40000 ALTER TABLE `pdelivstable` DISABLE KEYS */;
/*!40000 ALTER TABLE `pdelivstable` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pdelivstatus`
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
);

--
-- Dumping data for table `mercutio2`.`pdelivstatus`
--

/*!40000 ALTER TABLE `pdelivstatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `pdelivstatus` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pdistrib`
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
);

--
-- Dumping data for table `mercutio2`.`pdistrib`
--

/*!40000 ALTER TABLE `pdistrib` DISABLE KEYS */;
/*!40000 ALTER TABLE `pdistrib` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pdistribmap`
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
);

--
-- Dumping data for table `mercutio2`.`pdistribmap`
--

/*!40000 ALTER TABLE `pdistribmap` DISABLE KEYS */;
/*!40000 ALTER TABLE `pdistribmap` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pdoublesign`
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
);

--
-- Dumping data for table `mercutio2`.`pdoublesign`
--

/*!40000 ALTER TABLE `pdoublesign` DISABLE KEYS */;
/*!40000 ALTER TABLE `pdoublesign` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pemployee`
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
);

--
-- Dumping data for table `mercutio2`.`pemployee`
--

/*!40000 ALTER TABLE `pemployee` DISABLE KEYS */;
INSERT INTO `pemployee` (`emplid`,`employeeTitleID`,`login`,`roleid`,`fname`,`lname`,`flagAsynchronous`,`email`,`phone`) VALUES 
 (1,2,'admin',0,'admin','admin',0,'admin@test.com',''),
 (2,2,'SEPPEY',3,'Dominique','Seppey',0,'seppey@localhost',''),
 (3,2,'FOURNIER',3,'Stéphane','Fournier',0,'fournier@localhost','');
/*!40000 ALTER TABLE `pemployee` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pempmap`
--

DROP TABLE IF EXISTS `pempmap`;
CREATE TABLE `pempmap` (
  `wkgid` int(11) NOT NULL default '0',
  `login` varchar(32) NOT NULL default '',
  UNIQUE KEY `pempmap_idx1` (`wkgid`,`login`)
);

--
-- Dumping data for table `mercutio2`.`pempmap`
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
-- Table structure for table `mercutio2`.`pemppasswd`
--

DROP TABLE IF EXISTS `pemppasswd`;
CREATE TABLE `pemppasswd` (
  `emplid` int(11) NOT NULL default '0',
  `passwd` varchar(80) NOT NULL default '',
  PRIMARY KEY  (`emplid`),
  KEY `pemppasswd_idx1` (`passwd`)
);

--
-- Dumping data for table `mercutio2`.`pemppasswd`
--

/*!40000 ALTER TABLE `pemppasswd` DISABLE KEYS */;
INSERT INTO `pemppasswd` (`emplid`,`passwd`) VALUES 
 (0,'3dba7f2d2578ffb4bd657af94b1add80'),
 (1,'f71dbe52628a3f83a77ab494817525c6'),
 (3,'f71dbe52628a3f83a77ab494817525c6'),
 (2,'3dba7f2d2578ffb4bd657af94b1add80');
/*!40000 ALTER TABLE `pemppasswd` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pemproles`
--

DROP TABLE IF EXISTS `pemproles`;
CREATE TABLE `pemproles` (
  `roleid` int(11) NOT NULL default '0',
  `rolename` varchar(255) default NULL,
  PRIMARY KEY  (`roleid`)
);

--
-- Dumping data for table `mercutio2`.`pemproles`
--

/*!40000 ALTER TABLE `pemproles` DISABLE KEYS */;
INSERT INTO `pemproles` (`roleid`,`rolename`) VALUES 
 (0,'Administrateur du systÃ¨me'),
 (1,'Administrateur de groupe'),
 (2,'Chef de groupe'),
 (3,'EmployÃ©');
/*!40000 ALTER TABLE `pemproles` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pexec`
--

DROP TABLE IF EXISTS `pexec`;
CREATE TABLE `pexec` (
  `execid` int(11) NOT NULL default '0',
  `prgid` int(11) NOT NULL default '0',
  `exectype` int(11) NOT NULL default '0',
  `execname` varchar(255) default NULL,
  `execpath` varchar(255) default NULL,
  PRIMARY KEY  (`execid`,`prgid`)
);

--
-- Dumping data for table `mercutio2`.`pexec`
--

/*!40000 ALTER TABLE `pexec` DISABLE KEYS */;
/*!40000 ALTER TABLE `pexec` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pidentity`
--

DROP TABLE IF EXISTS `pidentity`;
CREATE TABLE `pidentity` (
  `idname` varchar(32) NOT NULL default '',
  `idv` int(11) NOT NULL default '0',
  PRIMARY KEY  (`idname`),
  KEY `pidentity_idx1` (`idv`)
);

--
-- Dumping data for table `mercutio2`.`pidentity`
--

/*!40000 ALTER TABLE `pidentity` DISABLE KEYS */;
INSERT INTO `pidentity` (`idname`,`idv`) VALUES 
 ('PTRANS',191),
 ('PCASE',170),
 ('PATTRIB',177),
 ('PCLSIDMAPPER',1020),
 ('PSCRDATAGROUP',1),
 ('PSCRDATAEL',1);
/*!40000 ALTER TABLE `pidentity` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pinfostatus`
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
);

--
-- Dumping data for table `mercutio2`.`pinfostatus`
--

/*!40000 ALTER TABLE `pinfostatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `pinfostatus` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pinput`
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
);

--
-- Dumping data for table `mercutio2`.`pinput`
--

/*!40000 ALTER TABLE `pinput` DISABLE KEYS */;
INSERT INTO `pinput` (`modelid`,`pdattribid`,`attribdefid`,`mdefval`,`mflag`,`constraintid`) VALUES 
 (1,-1,-1,'',-1,-1),
 (2,-1,-1,'',-1,-1);
/*!40000 ALTER TABLE `pinput` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pinputdata`
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
);

--
-- Dumping data for table `mercutio2`.`pinputdata`
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
-- Table structure for table `mercutio2`.`pinputflag`
--

DROP TABLE IF EXISTS `pinputflag`;
CREATE TABLE `pinputflag` (
  `flagid` int(11) NOT NULL default '0',
  `flagtxt` varchar(32) default NULL,
  PRIMARY KEY  (`flagid`)
);

--
-- Dumping data for table `mercutio2`.`pinputflag`
--

/*!40000 ALTER TABLE `pinputflag` DISABLE KEYS */;
INSERT INTO `pinputflag` (`flagid`,`flagtxt`) VALUES 
 (1,'Non visible'),
 (2,'Visible'),
 (3,'Editable');
/*!40000 ALTER TABLE `pinputflag` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`plogicop`
--

DROP TABLE IF EXISTS `plogicop`;
CREATE TABLE `plogicop` (
  `lopid` int(11) NOT NULL default '0',
  `mlop` varchar(16) default NULL,
  PRIMARY KEY  (`lopid`)
);

--
-- Dumping data for table `mercutio2`.`plogicop`
--

/*!40000 ALTER TABLE `plogicop` DISABLE KEYS */;
INSERT INTO `plogicop` (`lopid`,`mlop`) VALUES 
 (0,'AND'),
 (1,'OR');
/*!40000 ALTER TABLE `plogicop` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pmenu`
--

DROP TABLE IF EXISTS `pmenu`;
CREATE TABLE `pmenu` (
  `menuid` int(11) NOT NULL default '0',
  `menugroup` varchar(255) default NULL,
  PRIMARY KEY  (`menuid`)
);

--
-- Dumping data for table `mercutio2`.`pmenu`
--

/*!40000 ALTER TABLE `pmenu` DISABLE KEYS */;
INSERT INTO `pmenu` (`menuid`,`menugroup`) VALUES 
 (1,'Workgroup Menu');
/*!40000 ALTER TABLE `pmenu` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pmenuitem`
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
);

--
-- Dumping data for table `mercutio2`.`pmenuitem`
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
-- Table structure for table `mercutio2`.`pmodel`
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
);

--
-- Dumping data for table `mercutio2`.`pmodel`
--

/*!40000 ALTER TABLE `pmodel` DISABLE KEYS */;
INSERT INTO `pmodel` (`modelid`,`modelname`,`modelref`,`versionno`,`startdate`,`enddate`,`isvalid`,`pubdate`) VALUES 
 (1,'LaSonnazClassique2.mlf\0\0\0\0\0\0','_:[v0]732425496-4810',1,'2005-01-01 00:00:00','2005-12-31 00:00:00',1,'2006-10-24 09:52:59'),
 (2,'LaSonnazActuelle1.mlf\0\0\0\0','_:[v0]732425496-4810',1,'2006-01-01 00:00:00',NULL,1,'2006-10-24 11:13:43');
/*!40000 ALTER TABLE `pmodel` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`poperator`
--

DROP TABLE IF EXISTS `poperator`;
CREATE TABLE `poperator` (
  `opid` int(11) NOT NULL default '0',
  `mop` varchar(32) default NULL,
  PRIMARY KEY  (`opid`)
);

--
-- Dumping data for table `mercutio2`.`poperator`
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
-- Table structure for table `mercutio2`.`ppdattr`
--

DROP TABLE IF EXISTS `ppdattr`;
CREATE TABLE `ppdattr` (
  `pdattribid` int(11) NOT NULL default '0',
  `prow` int(11) NOT NULL default '0',
  `attribdefid` int(11) NOT NULL default '0',
  `mvalue` varchar(255) default NULL,
  `modelid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`pdattribid`,`prow`,`modelid`)
);

--
-- Dumping data for table `mercutio2`.`ppdattr`
--

/*!40000 ALTER TABLE `ppdattr` DISABLE KEYS */;
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (1,0,1310721,'Demande état civil',1),
 (1,1,1310722,'',1),
 (1,2,1310723,'1',1),
 (1,3,2621441,'',1),
 (1,4,73400321,'Acte de naissance',1),
 (1,5,73400322,'0.400000',1),
 (1,6,73400323,'40.000004',1),
 (1,7,73400324,'_:[v0]1557648201-45698',1),
 (1,8,73400321,'Acte de marriage',1),
 (1,9,73400322,'0.200000',1),
 (1,10,73400323,'20.000002',1),
 (1,11,73400324,'_:[v0]-1698303281-31489',1),
 (1,12,73400321,'Acte de décès',1),
 (1,13,73400322,'0.400000',1),
 (1,14,73400323,'40.000004',1),
 (1,15,73400324,'_:[v0]-1048620994-5003',1),
 (1,16,39321601,'29.9167',1),
 (1,17,39321602,'14287.7',1),
 (1,18,39321603,'5290',1),
 (1,19,39321604,'100.000008',1),
 (1,20,39321605,'0.299167',1),
 (1,21,39321606,'142.877075',1),
 (1,22,76021761,'Sans suite',1),
 (1,23,76021762,'Demande état civil sans suite',1),
 (1,24,76021763,'2.000000',1),
 (1,25,76021764,'0.020000',1),
 (1,26,76021765,'Demande état civil sans suite',1),
 (1,27,76021761,'courrier',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (1,28,76021762,'Acte état civil remis',1),
 (1,29,76021763,'18.000002',1),
 (1,30,76021764,'0.180000',1),
 (1,31,76021765,'Acte état civil remis',1),
 (1,32,76021761,'guichet',1),
 (1,33,76021762,'Acte état civil posté',1),
 (1,34,76021763,'80.000008',1),
 (1,35,76021764,'0.800000',1),
 (1,36,76021765,'Acte état civil posté',1),
 (2,37,1310721,'Demander acte état civil',1),
 (2,38,1310722,'à distance',1),
 (2,39,1310723,'2',1),
 (2,40,26214403,'_:[v0]205489264-15020',1),
 (2,41,26214401,'Administrés',1),
 (2,42,26214402,'200.000000',1),
 (3,43,1310721,'Demander acte état  civil',1),
 (3,44,1310722,'au guichet',1),
 (3,45,1310723,'3',1),
 (3,46,26214403,'_:[v0]205489264-15020',1),
 (3,47,26214401,'Administrés',1),
 (3,48,26214402,'200.000000',1),
 (4,49,1310721,'Traitement demande état civil',1),
 (4,50,1310722,'',1),
 (4,51,1310723,'4',1),
 (4,52,47185921,'BD état civil',1),
 (4,53,20971521,'',1),
 (4,54,20971522,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (4,55,68157441,'Attestation délivrée que pour les résident de la commune',1),
 (4,56,68157461,'Attestation délivrée dès émolument reçu',1),
 (4,57,68157481,'',1),
 (4,58,68157501,'',1),
 (4,59,68157521,'',1),
 (4,60,68157541,'',1),
 (4,61,68157561,'',1),
 (4,62,68157581,'',1),
 (4,63,68157601,'',1),
 (4,64,68157621,'',1),
 (4,65,68157641,'',1),
 (4,66,68157661,'',1),
 (4,67,68157681,'',1),
 (4,68,68157701,'',1),
 (4,69,68157721,'',1),
 (4,70,68157741,'',1),
 (4,71,68157761,'',1),
 (4,72,68157781,'',1),
 (4,73,68157801,'',1),
 (4,74,68157821,'',1),
 (4,75,41943041,'Verifier si dans la BD d\'état civil',1),
 (4,76,41943061,'Enregistrer la demande',1),
 (4,77,41943081,'Facturer acte état civil',1),
 (4,78,41943101,'Délivrer acte état civil',1),
 (4,79,41943121,'',1),
 (4,80,41943141,'',1),
 (4,81,41943161,'',1),
 (4,82,41943181,'',1),
 (4,83,41943201,'',1),
 (4,84,41943221,'',1),
 (4,85,41943241,'',1),
 (4,86,41943261,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (4,87,41943281,'',1),
 (4,88,41943301,'',1),
 (4,89,41943321,'',1),
 (4,90,41943341,'',1),
 (4,91,41943361,'',1),
 (4,92,41943381,'',1),
 (4,93,41943401,'',1),
 (4,94,41943421,'',1),
 (4,95,43253761,'',1),
 (4,96,43253781,'',1),
 (4,97,43253801,'',1),
 (4,98,43253821,'',1),
 (4,99,43253841,'',1),
 (4,100,43253861,'',1),
 (4,101,43253881,'',1),
 (4,102,43253901,'',1),
 (4,103,43253921,'',1),
 (4,104,43253941,'',1),
 (4,105,43253961,'',1),
 (4,106,43253981,'',1),
 (4,107,43254001,'',1),
 (4,108,43254021,'',1),
 (4,109,43254041,'',1),
 (4,110,43254061,'',1),
 (4,111,43254081,'',1),
 (4,112,43254101,'',1),
 (4,113,43254121,'',1),
 (4,114,43254141,'',1),
 (4,115,18350081,'1.000000',1),
 (4,116,18350082,'0.25',1),
 (4,117,18350083,'30.000000',1),
 (4,118,18350084,'3.52379',1),
 (4,119,18350085,'15.0209',1),
 (4,120,26214402,'305.000000',1),
 (4,121,26214404,'0',1),
 (4,122,26214403,'_:[v0]-1851353336-60382',1),
 (4,123,26214401,'Secrétariat',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (4,124,31457281,'distant',1),
 (4,125,31457282,'Demande état civil',1),
 (4,126,31457283,'0.200000',1),
 (4,127,31457284,'Demande état civil',1),
 (4,128,31457281,'guichet',1),
 (4,129,31457282,'Demande état civil',1),
 (4,130,31457283,'0.800000',1),
 (4,131,31457284,'Demande état civil',1),
 (4,132,36700161,'100',1),
 (4,133,36700162,'3170',1),
 (4,134,36700163,'28.7083',1),
 (4,135,36700164,'11926',1),
 (4,136,36700165,'0.287083',1),
 (4,137,36700166,'119.26',1),
 (5,138,1310721,'Demande état civil',1),
 (5,139,1310722,'',1),
 (5,140,1310723,'5',1),
 (5,141,47185921,'Fax',1),
 (5,142,47185921,'Téléphone',1),
 (5,143,47185921,'Courrier',1),
 (5,144,47185921,'Fax',1),
 (5,145,20971521,'',1),
 (5,146,20971522,'',1),
 (5,147,68157441,'',1),
 (5,148,68157461,'',1),
 (5,149,68157481,'',1),
 (5,150,68157501,'',1),
 (5,151,68157521,'',1),
 (5,152,68157541,'',1),
 (5,153,68157561,'',1),
 (5,154,68157581,'',1),
 (5,155,68157601,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (5,156,68157621,'',1),
 (5,157,68157641,'',1),
 (5,158,68157661,'',1),
 (5,159,68157681,'',1),
 (5,160,68157701,'',1),
 (5,161,68157721,'',1),
 (5,162,68157741,'',1),
 (5,163,68157761,'',1),
 (5,164,68157781,'',1),
 (5,165,68157801,'',1),
 (5,166,68157821,'',1),
 (5,167,44564481,'Nom',1),
 (5,168,44564501,'Prénom',1),
 (5,169,44564521,'Date de naissance',1),
 (5,170,44564541,'Adresse',1),
 (5,171,44564561,'Nr AVS',1),
 (5,172,44564581,'',1),
 (5,173,44564601,'',1),
 (5,174,44564621,'',1),
 (5,175,44564641,'',1),
 (5,176,44564661,'',1),
 (5,177,44564681,'',1),
 (5,178,44564701,'',1),
 (5,179,44564721,'',1),
 (5,180,44564741,'',1),
 (5,181,44564761,'',1),
 (5,182,44564781,'',1),
 (5,183,44564801,'',1),
 (5,184,44564821,'',1),
 (5,185,44564841,'',1),
 (5,186,44564861,'',1),
 (5,187,15728641,'0',1),
 (5,188,15728643,'1.000000',1),
 (5,189,15728644,'40.000000',1),
 (5,190,15728645,'-1',1),
 (5,191,15728648,'-1',1),
 (5,192,15728646,'1',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (5,193,15728647,'1',1),
 (5,194,49807361,'20',1),
 (5,195,49807374,'0',1),
 (5,196,49807387,'0',1),
 (5,197,49807362,'1.66667',1),
 (5,198,49807375,'0',1),
 (5,199,49807363,'1.66667',1),
 (5,200,49807376,'0',1),
 (5,201,49807364,'1.66667',1),
 (5,202,49807377,'0',1),
 (5,203,49807365,'1.66667',1),
 (5,204,49807378,'0',1),
 (5,205,49807366,'1.66667',1),
 (5,206,49807379,'0',1),
 (5,207,49807367,'1.66667',1),
 (5,208,49807380,'0',1),
 (5,209,49807368,'1.66667',1),
 (5,210,49807381,'0',1),
 (5,211,49807369,'1.66667',1),
 (5,212,49807382,'0',1),
 (5,213,49807370,'1.66667',1),
 (5,214,49807383,'0',1),
 (5,215,49807371,'1.66667',1),
 (5,216,49807384,'0',1),
 (5,217,49807372,'1.66667',1),
 (5,218,49807385,'0',1),
 (5,219,49807373,'1.66667',1),
 (5,220,49807386,'0',1),
 (5,221,34078721,'800',1),
 (5,222,34078722,'0.000000',1),
 (5,223,26214403,'',1),
 (5,224,26214401,'',1),
 (5,225,26214402,'0.000000',1),
 (5,226,26214404,'0',1),
 (6,227,1310721,'Demande état civil',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (6,228,1310722,'',1),
 (6,229,1310723,'6',1),
 (6,230,47185921,'Visite',1),
 (6,231,20971521,'',1),
 (6,232,20971522,'',1),
 (6,233,68157441,'',1),
 (6,234,68157461,'',1),
 (6,235,68157481,'',1),
 (6,236,68157501,'',1),
 (6,237,68157521,'',1),
 (6,238,68157541,'',1),
 (6,239,68157561,'',1),
 (6,240,68157581,'',1),
 (6,241,68157601,'',1),
 (6,242,68157621,'',1),
 (6,243,68157641,'',1),
 (6,244,68157661,'',1),
 (6,245,68157681,'',1),
 (6,246,68157701,'',1),
 (6,247,68157721,'',1),
 (6,248,68157741,'',1),
 (6,249,68157761,'',1),
 (6,250,68157781,'',1),
 (6,251,68157801,'',1),
 (6,252,68157821,'',1),
 (6,253,44564481,'Nom',1),
 (6,254,44564501,'Prénom',1),
 (6,255,44564521,'Date de naissance',1),
 (6,256,44564541,'Adresse',1),
 (6,257,44564561,'Nr AVS',1),
 (6,258,44564581,'',1),
 (6,259,44564601,'',1),
 (6,260,44564621,'',1),
 (6,261,44564641,'',1),
 (6,262,44564661,'',1),
 (6,263,44564681,'',1),
 (6,264,44564701,'',1),
 (6,265,44564721,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (6,266,44564741,'',1),
 (6,267,44564761,'',1),
 (6,268,44564781,'',1),
 (6,269,44564801,'',1),
 (6,270,44564821,'',1),
 (6,271,44564841,'',1),
 (6,272,44564861,'',1),
 (6,273,15728641,'0',1),
 (6,274,15728643,'1.000000',1),
 (6,275,15728644,'100.000000',1),
 (6,276,15728645,'1',1),
 (6,277,15728648,'1',1),
 (6,278,15728646,'1',1),
 (6,279,15728647,'1',1),
 (6,280,49807361,'80',1),
 (6,281,49807374,'0',1),
 (6,282,49807387,'0',1),
 (6,283,49807362,'6.66667',1),
 (6,284,49807375,'0',1),
 (6,285,49807363,'6.66667',1),
 (6,286,49807376,'0',1),
 (6,287,49807364,'6.66667',1),
 (6,288,49807377,'0',1),
 (6,289,49807365,'6.66667',1),
 (6,290,49807378,'0',1),
 (6,291,49807366,'6.66667',1),
 (6,292,49807379,'0',1),
 (6,293,49807367,'6.66667',1),
 (6,294,49807380,'0',1),
 (6,295,49807368,'6.66667',1),
 (6,296,49807381,'0',1),
 (6,297,49807369,'6.66667',1),
 (6,298,49807382,'0',1),
 (6,299,49807370,'6.66667',1),
 (6,300,49807383,'0',1),
 (6,301,49807371,'6.66667',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (6,302,49807384,'0',1),
 (6,303,49807372,'6.66667',1),
 (6,304,49807385,'0',1),
 (6,305,49807373,'6.66667',1),
 (6,306,49807386,'0',1),
 (6,307,34078721,'8000',1),
 (6,308,34078722,'0.000000',1),
 (6,309,26214403,'',1),
 (6,310,26214401,'',1),
 (6,311,26214402,'0.000000',1),
 (6,312,26214404,'0',1),
 (7,313,1310721,'Payer facture à état civil',1),
 (7,314,1310722,'',1),
 (7,315,1310723,'7',1),
 (7,316,47185921,'',1),
 (7,317,20971521,'',1),
 (7,318,20971522,'',1),
 (7,319,68157441,'',1),
 (7,320,68157461,'',1),
 (7,321,68157481,'',1),
 (7,322,68157501,'',1),
 (7,323,68157521,'',1),
 (7,324,68157541,'',1),
 (7,325,68157561,'',1),
 (7,326,68157581,'',1),
 (7,327,68157601,'',1),
 (7,328,68157621,'',1),
 (7,329,68157641,'',1),
 (7,330,68157661,'',1),
 (7,331,68157681,'',1),
 (7,332,68157701,'',1),
 (7,333,68157721,'',1),
 (7,334,68157741,'',1),
 (7,335,68157761,'',1),
 (7,336,68157781,'',1),
 (7,337,68157801,'',1),
 (7,338,68157821,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (7,339,41943041,'',1),
 (7,340,41943061,'',1),
 (7,341,41943081,'',1),
 (7,342,41943101,'',1),
 (7,343,41943121,'',1),
 (7,344,41943141,'',1),
 (7,345,41943161,'',1),
 (7,346,41943181,'',1),
 (7,347,41943201,'',1),
 (7,348,41943221,'',1),
 (7,349,41943241,'',1),
 (7,350,41943261,'',1),
 (7,351,41943281,'',1),
 (7,352,41943301,'',1),
 (7,353,41943321,'',1),
 (7,354,41943341,'',1),
 (7,355,41943361,'',1),
 (7,356,41943381,'',1),
 (7,357,41943401,'',1),
 (7,358,41943421,'',1),
 (7,359,43253761,'',1),
 (7,360,43253781,'',1),
 (7,361,43253801,'',1),
 (7,362,43253821,'',1),
 (7,363,43253841,'',1),
 (7,364,43253861,'',1),
 (7,365,43253881,'',1),
 (7,366,43253901,'',1),
 (7,367,43253921,'',1),
 (7,368,43253941,'',1),
 (7,369,43253961,'',1),
 (7,370,43253981,'',1),
 (7,371,43254001,'',1),
 (7,372,43254021,'',1),
 (7,373,43254041,'',1),
 (7,374,43254061,'',1),
 (7,375,43254081,'',1),
 (7,376,43254101,'',1),
 (7,377,43254121,'',1),
 (7,378,43254141,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (7,379,18350081,'1.000000',1),
 (7,380,18350082,'0',1),
 (7,381,18350083,'0.000000',1),
 (7,382,18350084,'7.01042',1),
 (7,383,18350085,'7.01042',1),
 (7,384,26214402,'200.000000',1),
 (7,385,26214404,'0',1),
 (7,386,26214403,'_:[v0]205489264-15020',1),
 (7,387,26214401,'Administrés',1),
 (7,388,31457281,'Comb 1',1),
 (7,389,31457282,'Facture état civil',1),
 (7,390,31457283,'1.000000',1),
 (7,391,31457284,'Facture état civil',1),
 (7,392,36700161,'20',1),
 (7,393,36700162,'40',1),
 (7,394,36700163,'0.208333',1),
 (7,395,36700164,'81.6667',1),
 (7,396,36700165,'0.0104167',1),
 (7,397,36700166,'4.08333',1),
 (8,398,1310721,'Régler comptant état civil',1),
 (8,399,1310722,'',1),
 (8,400,1310723,'8',1),
 (8,401,47185921,'',1),
 (8,402,20971521,'',1),
 (8,403,20971522,'',1),
 (8,404,68157441,'',1),
 (8,405,68157461,'',1),
 (8,406,68157481,'',1),
 (8,407,68157501,'',1),
 (8,408,68157521,'',1),
 (8,409,68157541,'',1),
 (8,410,68157561,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (8,411,68157581,'',1),
 (8,412,68157601,'',1),
 (8,413,68157621,'',1),
 (8,414,68157641,'',1),
 (8,415,68157661,'',1),
 (8,416,68157681,'',1),
 (8,417,68157701,'',1),
 (8,418,68157721,'',1),
 (8,419,68157741,'',1),
 (8,420,68157761,'',1),
 (8,421,68157781,'',1),
 (8,422,68157801,'',1),
 (8,423,68157821,'',1),
 (8,424,41943041,'Payer les émoluments',1),
 (8,425,41943061,'',1),
 (8,426,41943081,'',1),
 (8,427,41943101,'',1),
 (8,428,41943121,'',1),
 (8,429,41943141,'',1),
 (8,430,41943161,'',1),
 (8,431,41943181,'',1),
 (8,432,41943201,'',1),
 (8,433,41943221,'',1),
 (8,434,41943241,'',1),
 (8,435,41943261,'',1),
 (8,436,41943281,'',1),
 (8,437,41943301,'',1),
 (8,438,41943321,'',1),
 (8,439,41943341,'',1),
 (8,440,41943361,'',1),
 (8,441,41943381,'',1),
 (8,442,41943401,'',1),
 (8,443,41943421,'',1),
 (8,444,43253761,'',1),
 (8,445,43253781,'',1),
 (8,446,43253801,'',1),
 (8,447,43253821,'',1),
 (8,448,43253841,'',1),
 (8,449,43253861,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (8,450,43253881,'',1),
 (8,451,43253901,'',1),
 (8,452,43253921,'',1),
 (8,453,43253941,'',1),
 (8,454,43253961,'',1),
 (8,455,43253981,'',1),
 (8,456,43254001,'',1),
 (8,457,43254021,'',1),
 (8,458,43254041,'',1),
 (8,459,43254061,'',1),
 (8,460,43254081,'',1),
 (8,461,43254101,'',1),
 (8,462,43254121,'',1),
 (8,463,43254141,'',1),
 (8,464,18350081,'1.000000',1),
 (8,465,18350082,'0.0104167',1),
 (8,466,18350083,'25.000000',1),
 (8,467,18350084,'0.0145833',1),
 (8,468,18350085,'0.0145833',1),
 (8,469,26214402,'200.000000',1),
 (8,470,26214404,'0',1),
 (8,471,26214403,'_:[v0]205489264-15020',1),
 (8,472,26214401,'Administrés',1),
 (8,473,31457281,'Comb 1',1),
 (8,474,31457282,'Demande payement émolument',1),
 (8,475,31457283,'1.000000',1),
 (8,476,31457284,'Demande payement émolument',1),
 (8,477,36700161,'80',1),
 (8,478,36700162,'2080',1),
 (8,479,36700163,'1',1),
 (8,480,36700164,'2280',1),
 (8,481,36700165,'0.0125',1),
 (8,482,36700166,'28.5',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (9,483,1310721,'Demande payement émolument',1),
 (9,484,1310722,'',1),
 (9,485,1310723,'9',1),
 (9,486,20971521,'',1),
 (9,487,20971522,'',1),
 (9,488,68157441,'',1),
 (9,489,68157461,'',1),
 (9,490,68157481,'',1),
 (9,491,68157501,'',1),
 (9,492,68157521,'',1),
 (9,493,68157541,'',1),
 (9,494,68157561,'',1),
 (9,495,68157581,'',1),
 (9,496,68157601,'',1),
 (9,497,68157621,'',1),
 (9,498,68157641,'',1),
 (9,499,68157661,'',1),
 (9,500,68157681,'',1),
 (9,501,68157701,'',1),
 (9,502,68157721,'',1),
 (9,503,68157741,'',1),
 (9,504,68157761,'',1),
 (9,505,68157781,'',1),
 (9,506,68157801,'',1),
 (9,507,68157821,'',1),
 (9,508,44564481,'',1),
 (9,509,44564501,'',1),
 (9,510,44564521,'',1),
 (9,511,44564541,'',1),
 (9,512,44564561,'',1),
 (9,513,44564581,'',1),
 (9,514,44564601,'',1),
 (9,515,44564621,'',1),
 (9,516,44564641,'',1),
 (9,517,44564661,'',1),
 (9,518,44564681,'',1),
 (9,519,44564701,'',1),
 (9,520,44564721,'',1),
 (9,521,44564741,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (9,522,44564761,'',1),
 (9,523,44564781,'',1),
 (9,524,44564801,'',1),
 (9,525,44564821,'',1),
 (9,526,44564841,'',1),
 (9,527,44564861,'',1),
 (9,528,15728641,'0.0208333',1),
 (9,529,15728643,'0.800000',1),
 (9,530,15728644,'2.000000',1),
 (9,531,15728645,'0.0104167',1),
 (9,532,15728648,'0.0104167',1),
 (9,533,15728646,'0.0104167',1),
 (9,534,15728647,'0.0125',1),
 (9,535,49807361,'80',1),
 (9,536,49807374,'0',1),
 (9,537,49807387,'0',1),
 (9,538,49807362,'6.66667',1),
 (9,539,49807375,'0',1),
 (9,540,49807363,'6.66667',1),
 (9,541,49807376,'0',1),
 (9,542,49807364,'6.66667',1),
 (9,543,49807377,'0',1),
 (9,544,49807365,'6.66667',1),
 (9,545,49807378,'0',1),
 (9,546,49807366,'6.66667',1),
 (9,547,49807379,'0',1),
 (9,548,49807367,'6.66667',1),
 (9,549,49807380,'0',1),
 (9,550,49807368,'6.66667',1),
 (9,551,49807381,'0',1),
 (9,552,49807369,'6.66667',1),
 (9,553,49807382,'0',1),
 (9,554,49807370,'6.66667',1),
 (9,555,49807383,'0',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (9,556,49807371,'6.66667',1),
 (9,557,49807384,'0',1),
 (9,558,49807372,'6.66667',1),
 (9,559,49807385,'0',1),
 (9,560,49807373,'6.66667',1),
 (9,561,49807386,'0',1),
 (9,562,34078721,'160',1),
 (9,563,34078722,'1.666667',1),
 (9,564,26214403,'',1),
 (9,565,26214401,'',1),
 (9,566,26214402,'0.000000',1),
 (9,567,26214404,'0',1),
 (10,568,1310721,'Payement émolument',1),
 (10,569,1310722,'',1),
 (10,570,1310723,'10',1),
 (10,571,20971521,'',1),
 (10,572,20971522,'',1),
 (10,573,68157441,'',1),
 (10,574,68157461,'',1),
 (10,575,68157481,'',1),
 (10,576,68157501,'',1),
 (10,577,68157521,'',1),
 (10,578,68157541,'',1),
 (10,579,68157561,'',1),
 (10,580,68157581,'',1),
 (10,581,68157601,'',1),
 (10,582,68157621,'',1),
 (10,583,68157641,'',1),
 (10,584,68157661,'',1),
 (10,585,68157681,'',1),
 (10,586,68157701,'',1),
 (10,587,68157721,'',1),
 (10,588,68157741,'',1),
 (10,589,68157761,'',1),
 (10,590,68157781,'',1),
 (10,591,68157801,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (10,592,68157821,'',1),
 (10,593,44564481,'',1),
 (10,594,44564501,'',1),
 (10,595,44564521,'',1),
 (10,596,44564541,'',1),
 (10,597,44564561,'',1),
 (10,598,44564581,'',1),
 (10,599,44564601,'',1),
 (10,600,44564621,'',1),
 (10,601,44564641,'',1),
 (10,602,44564661,'',1),
 (10,603,44564681,'',1),
 (10,604,44564701,'',1),
 (10,605,44564721,'',1),
 (10,606,44564741,'',1),
 (10,607,44564761,'',1),
 (10,608,44564781,'',1),
 (10,609,44564801,'',1),
 (10,610,44564821,'',1),
 (10,611,44564841,'',1),
 (10,612,44564861,'',1),
 (10,613,15728641,'0.00208333',1),
 (10,614,15728643,'1.000000',1),
 (10,615,15728644,'1.000000',1),
 (10,616,15728645,'0.025',1),
 (10,617,15728648,'0.025',1),
 (10,618,15728646,'0.00208333',1),
 (10,619,15728647,'0.00208333',1),
 (10,620,49807361,'80',1),
 (10,621,49807374,'0',1),
 (10,622,49807387,'0',1),
 (10,623,49807362,'6.66667',1),
 (10,624,49807375,'0',1),
 (10,625,49807363,'6.66667',1),
 (10,626,49807376,'0',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (10,627,49807364,'6.66667',1),
 (10,628,49807377,'0',1),
 (10,629,49807365,'6.66667',1),
 (10,630,49807378,'0',1),
 (10,631,49807366,'6.66667',1),
 (10,632,49807379,'0',1),
 (10,633,49807367,'6.66667',1),
 (10,634,49807380,'0',1),
 (10,635,49807368,'6.66667',1),
 (10,636,49807381,'0',1),
 (10,637,49807369,'6.66667',1),
 (10,638,49807382,'0',1),
 (10,639,49807370,'6.66667',1),
 (10,640,49807383,'0',1),
 (10,641,49807371,'6.66667',1),
 (10,642,49807384,'0',1),
 (10,643,49807372,'6.66667',1),
 (10,644,49807385,'0',1),
 (10,645,49807373,'6.66667',1),
 (10,646,49807386,'0',1),
 (10,647,34078721,'80',1),
 (10,648,34078722,'0.166667',1),
 (10,649,26214403,'',1),
 (10,650,26214401,'',1),
 (10,651,26214402,'0.000000',1),
 (10,652,26214404,'0',1),
 (11,653,1310721,'Facture état civil',1),
 (11,654,1310722,'',1),
 (11,655,1310723,'11',1),
 (11,656,47185921,'Courrier',1),
 (11,657,20971521,'',1),
 (11,658,20971522,'',1),
 (11,659,68157441,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (11,660,68157461,'',1),
 (11,661,68157481,'',1),
 (11,662,68157501,'',1),
 (11,663,68157521,'',1),
 (11,664,68157541,'',1),
 (11,665,68157561,'',1),
 (11,666,68157581,'',1),
 (11,667,68157601,'',1),
 (11,668,68157621,'',1),
 (11,669,68157641,'',1),
 (11,670,68157661,'',1),
 (11,671,68157681,'',1),
 (11,672,68157701,'',1),
 (11,673,68157721,'',1),
 (11,674,68157741,'',1),
 (11,675,68157761,'',1),
 (11,676,68157781,'',1),
 (11,677,68157801,'',1),
 (11,678,68157821,'',1),
 (11,679,44564481,'',1),
 (11,680,44564501,'',1),
 (11,681,44564521,'',1),
 (11,682,44564541,'',1),
 (11,683,44564561,'',1),
 (11,684,44564581,'',1),
 (11,685,44564601,'',1),
 (11,686,44564621,'',1),
 (11,687,44564641,'',1),
 (11,688,44564661,'',1),
 (11,689,44564681,'',1),
 (11,690,44564701,'',1),
 (11,691,44564721,'',1),
 (11,692,44564741,'',1),
 (11,693,44564761,'',1),
 (11,694,44564781,'',1),
 (11,695,44564801,'',1),
 (11,696,44564821,'',1),
 (11,697,44564841,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (11,698,44564861,'',1),
 (11,699,15728641,'0.03125',1),
 (11,700,15728643,'0.200000',1),
 (11,701,15728644,'10.000000',1),
 (11,702,15728645,'7',1),
 (11,703,15728648,'7',1),
 (11,704,15728646,'7',1),
 (11,705,15728647,'7',1),
 (11,706,49807361,'20',1),
 (11,707,49807374,'0',1),
 (11,708,49807387,'0',1),
 (11,709,49807362,'1.66667',1),
 (11,710,49807375,'0',1),
 (11,711,49807363,'1.66667',1),
 (11,712,49807376,'0',1),
 (11,713,49807364,'1.66667',1),
 (11,714,49807377,'0',1),
 (11,715,49807365,'1.66667',1),
 (11,716,49807378,'0',1),
 (11,717,49807366,'1.66667',1),
 (11,718,49807379,'0',1),
 (11,719,49807367,'1.66667',1),
 (11,720,49807380,'0',1),
 (11,721,49807368,'1.66667',1),
 (11,722,49807381,'0',1),
 (11,723,49807369,'1.66667',1),
 (11,724,49807382,'0',1),
 (11,725,49807370,'1.66667',1),
 (11,726,49807383,'0',1),
 (11,727,49807371,'1.66667',1),
 (11,728,49807384,'0',1),
 (11,729,49807372,'1.66667',1),
 (11,730,49807385,'0',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (11,731,49807373,'1.66667',1),
 (11,732,49807386,'0',1),
 (11,733,34078721,'200',1),
 (11,734,34078722,'0.625000',1),
 (11,735,26214403,'',1),
 (11,736,26214401,'',1),
 (11,737,26214402,'0.000000',1),
 (11,738,26214404,'0',1),
 (12,739,1310721,'Payement facture état civil',1),
 (12,740,1310722,'',1),
 (12,741,1310723,'12',1),
 (12,742,20971521,'',1),
 (12,743,20971522,'',1),
 (12,744,68157441,'',1),
 (12,745,68157461,'',1),
 (12,746,68157481,'',1),
 (12,747,68157501,'',1),
 (12,748,68157521,'',1),
 (12,749,68157541,'',1),
 (12,750,68157561,'',1),
 (12,751,68157581,'',1),
 (12,752,68157601,'',1),
 (12,753,68157621,'',1),
 (12,754,68157641,'',1),
 (12,755,68157661,'',1),
 (12,756,68157681,'',1),
 (12,757,68157701,'',1),
 (12,758,68157721,'',1),
 (12,759,68157741,'',1),
 (12,760,68157761,'',1),
 (12,761,68157781,'',1),
 (12,762,68157801,'',1),
 (12,763,68157821,'',1),
 (12,764,44564481,'',1),
 (12,765,44564501,'',1),
 (12,766,44564521,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (12,767,44564541,'',1),
 (12,768,44564561,'',1),
 (12,769,44564581,'',1),
 (12,770,44564601,'',1),
 (12,771,44564621,'',1),
 (12,772,44564641,'',1),
 (12,773,44564661,'',1),
 (12,774,44564681,'',1),
 (12,775,44564701,'',1),
 (12,776,44564721,'',1),
 (12,777,44564741,'',1),
 (12,778,44564761,'',1),
 (12,779,44564781,'',1),
 (12,780,44564801,'',1),
 (12,781,44564821,'',1),
 (12,782,44564841,'',1),
 (12,783,44564861,'',1),
 (12,784,15728641,'0.0104167',1),
 (12,785,15728643,'0.900000',1),
 (12,786,15728644,'2.000000',1),
 (12,787,15728645,'14.0104',1),
 (12,788,15728648,'14.0104',1),
 (12,789,15728646,'0.0104167',1),
 (12,790,15728647,'0.0104167',1),
 (12,791,49807361,'18',1),
 (12,792,49807374,'0',1),
 (12,793,49807387,'0',1),
 (12,794,49807362,'1.5',1),
 (12,795,49807375,'0',1),
 (12,796,49807363,'1.5',1),
 (12,797,49807376,'0',1),
 (12,798,49807364,'1.5',1),
 (12,799,49807377,'0',1),
 (12,800,49807365,'1.5',1),
 (12,801,49807378,'0',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (12,802,49807366,'1.5',1),
 (12,803,49807379,'0',1),
 (12,804,49807367,'1.5',1),
 (12,805,49807380,'0',1),
 (12,806,49807368,'1.5',1),
 (12,807,49807381,'0',1),
 (12,808,49807369,'1.5',1),
 (12,809,49807382,'0',1),
 (12,810,49807370,'1.5',1),
 (12,811,49807383,'0',1),
 (12,812,49807371,'1.5',1),
 (12,813,49807384,'0',1),
 (12,814,49807372,'1.5',1),
 (12,815,49807385,'0',1),
 (12,816,49807373,'1.5',1),
 (12,817,49807386,'0',1),
 (12,818,34078721,'36',1),
 (12,819,34078722,'0.187500',1),
 (12,820,26214403,'',1),
 (12,821,26214401,'',1),
 (12,822,26214402,'0.000000',1),
 (12,823,26214404,'0',1),
 (13,824,1310721,'Absence de payement état civil',1),
 (13,825,1310722,'',1),
 (13,826,1310723,'13',1),
 (13,827,20971521,'',1),
 (13,828,20971522,'',1),
 (13,829,68157441,'',1),
 (13,830,68157461,'',1),
 (13,831,68157481,'',1),
 (13,832,68157501,'',1),
 (13,833,68157521,'',1),
 (13,834,68157541,'',1),
 (13,835,68157561,'',1),
 (13,836,68157581,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (13,837,68157601,'',1),
 (13,838,68157621,'',1),
 (13,839,68157641,'',1),
 (13,840,68157661,'',1),
 (13,841,68157681,'',1),
 (13,842,68157701,'',1),
 (13,843,68157721,'',1),
 (13,844,68157741,'',1),
 (13,845,68157761,'',1),
 (13,846,68157781,'',1),
 (13,847,68157801,'',1),
 (13,848,68157821,'',1),
 (13,849,44564481,'',1),
 (13,850,44564501,'',1),
 (13,851,44564521,'',1),
 (13,852,44564541,'',1),
 (13,853,44564561,'',1),
 (13,854,44564581,'',1),
 (13,855,44564601,'',1),
 (13,856,44564621,'',1),
 (13,857,44564641,'',1),
 (13,858,44564661,'',1),
 (13,859,44564681,'',1),
 (13,860,44564701,'',1),
 (13,861,44564721,'',1),
 (13,862,44564741,'',1),
 (13,863,44564761,'',1),
 (13,864,44564781,'',1),
 (13,865,44564801,'',1),
 (13,866,44564821,'',1),
 (13,867,44564841,'',1),
 (13,868,44564861,'',1),
 (13,869,15728641,'0.0104167',1),
 (13,870,15728643,'0.100000',1),
 (13,871,15728644,'2.000000',1),
 (13,872,15728645,'14.0104',1),
 (13,873,15728648,'14.0104',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (13,874,15728646,'0.0104167',1),
 (13,875,15728647,'0.0104167',1),
 (13,876,49807361,'2',1),
 (13,877,49807374,'0',1),
 (13,878,49807387,'0',1),
 (13,879,49807362,'0.166667',1),
 (13,880,49807375,'0',1),
 (13,881,49807363,'0.166667',1),
 (13,882,49807376,'0',1),
 (13,883,49807364,'0.166667',1),
 (13,884,49807377,'0',1),
 (13,885,49807365,'0.166667',1),
 (13,886,49807378,'0',1),
 (13,887,49807366,'0.166667',1),
 (13,888,49807379,'0',1),
 (13,889,49807367,'0.166667',1),
 (13,890,49807380,'0',1),
 (13,891,49807368,'0.166667',1),
 (13,892,49807381,'0',1),
 (13,893,49807369,'0.166667',1),
 (13,894,49807382,'0',1),
 (13,895,49807370,'0.166667',1),
 (13,896,49807383,'0',1),
 (13,897,49807371,'0.166667',1),
 (13,898,49807384,'0',1),
 (13,899,49807372,'0.166667',1),
 (13,900,49807385,'0',1),
 (13,901,49807373,'0.166667',1),
 (13,902,49807386,'0',1),
 (13,903,34078721,'4',1),
 (13,904,34078722,'0.020833',1),
 (13,905,26214403,'',1),
 (13,906,26214401,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (13,907,26214402,'0.000000',1),
 (13,908,26214404,'0',1),
 (14,909,1310721,'Abandonner demander état civil',1),
 (14,910,1310722,'',1),
 (14,911,1310723,'14',1),
 (14,912,26214403,'_:[v0]205489264-15020',1),
 (14,913,26214401,'Administrés',1),
 (14,914,26214402,'200.000000',1),
 (15,915,1310721,'Recevoir acte état civil',1),
 (15,916,1310722,'',1),
 (15,917,1310723,'15',1),
 (15,918,26214403,'_:[v0]205489264-15020',1),
 (15,919,26214401,'Administrés',1),
 (15,920,26214402,'200.000000',1),
 (16,921,1310721,'Obtenir acte état civil',1),
 (16,922,1310722,'',1),
 (16,923,1310723,'16',1),
 (16,924,26214403,'_:[v0]205489264-15020',1),
 (16,925,26214401,'Administrés',1),
 (16,926,26214402,'200.000000',1),
 (17,927,1310721,'Acte état civil posté',1),
 (17,928,1310722,'',1),
 (17,929,1310723,'17',1),
 (17,930,47185921,'Visite',1),
 (17,931,20971521,'',1),
 (17,932,20971522,'',1),
 (17,933,68157441,'',1),
 (17,934,68157461,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (17,935,68157481,'',1),
 (17,936,68157501,'',1),
 (17,937,68157521,'',1),
 (17,938,68157541,'',1),
 (17,939,68157561,'',1),
 (17,940,68157581,'',1),
 (17,941,68157601,'',1),
 (17,942,68157621,'',1),
 (17,943,68157641,'',1),
 (17,944,68157661,'',1),
 (17,945,68157681,'',1),
 (17,946,68157701,'',1),
 (17,947,68157721,'',1),
 (17,948,68157741,'',1),
 (17,949,68157761,'',1),
 (17,950,68157781,'',1),
 (17,951,68157801,'',1),
 (17,952,68157821,'',1),
 (17,953,44564481,'',1),
 (17,954,44564501,'',1),
 (17,955,44564521,'',1),
 (17,956,44564541,'',1),
 (17,957,44564561,'',1),
 (17,958,44564581,'',1),
 (17,959,44564601,'',1),
 (17,960,44564621,'',1),
 (17,961,44564641,'',1),
 (17,962,44564661,'',1),
 (17,963,44564681,'',1),
 (17,964,44564701,'',1),
 (17,965,44564721,'',1),
 (17,966,44564741,'',1),
 (17,967,44564761,'',1),
 (17,968,44564781,'',1),
 (17,969,44564801,'',1),
 (17,970,44564821,'',1),
 (17,971,44564841,'',1),
 (17,972,44564861,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (17,973,15728641,'0.0104167',1),
 (17,974,15728643,'0.800000',1),
 (17,975,15728644,'0.000000',1),
 (17,976,15728645,'4.52375',1),
 (17,977,15728648,'16.0208',1),
 (17,978,15728646,'0',1),
 (17,979,15728647,'0',1),
 (17,980,49807361,'80',1),
 (17,981,49807374,'0',1),
 (17,982,49807387,'0',1),
 (17,983,49807362,'6.66667',1),
 (17,984,49807375,'0',1),
 (17,985,49807363,'6.66667',1),
 (17,986,49807376,'0',1),
 (17,987,49807364,'6.66667',1),
 (17,988,49807377,'0',1),
 (17,989,49807365,'6.66667',1),
 (17,990,49807378,'0',1),
 (17,991,49807366,'6.66667',1),
 (17,992,49807379,'0',1),
 (17,993,49807367,'6.66667',1),
 (17,994,49807380,'0',1),
 (17,995,49807368,'6.66667',1),
 (17,996,49807381,'0',1),
 (17,997,49807369,'6.66667',1),
 (17,998,49807382,'0',1),
 (17,999,49807370,'6.66667',1),
 (17,1000,49807383,'0',1),
 (17,1001,49807371,'6.66667',1),
 (17,1002,49807384,'0',1),
 (17,1003,49807372,'6.66667',1),
 (17,1004,49807385,'0',1),
 (17,1005,49807373,'6.66667',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (17,1006,49807386,'0',1),
 (17,1007,34078721,'0',1),
 (17,1008,34078722,'0.833333',1),
 (17,1009,26214403,'',1),
 (17,1010,26214401,'',1),
 (17,1011,26214402,'0.000000',1),
 (17,1012,26214404,'0',1),
 (18,1013,1310721,'Acte état civil remis',1),
 (18,1014,1310722,'',1),
 (18,1015,1310723,'18',1),
 (18,1016,47185921,'Courrier',1),
 (18,1017,20971521,'',1),
 (18,1018,20971522,'',1),
 (18,1019,68157441,'',1),
 (18,1020,68157461,'',1),
 (18,1021,68157481,'',1),
 (18,1022,68157501,'',1),
 (18,1023,68157521,'',1),
 (18,1024,68157541,'',1),
 (18,1025,68157561,'',1),
 (18,1026,68157581,'',1),
 (18,1027,68157601,'',1),
 (18,1028,68157621,'',1),
 (18,1029,68157641,'',1),
 (18,1030,68157661,'',1),
 (18,1031,68157681,'',1),
 (18,1032,68157701,'',1),
 (18,1033,68157721,'',1),
 (18,1034,68157741,'',1),
 (18,1035,68157761,'',1),
 (18,1036,68157781,'',1),
 (18,1037,68157801,'',1),
 (18,1038,68157821,'',1),
 (18,1039,44564481,'',1),
 (18,1040,44564501,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (18,1041,44564521,'',1),
 (18,1042,44564541,'',1),
 (18,1043,44564561,'',1),
 (18,1044,44564581,'',1),
 (18,1045,44564601,'',1),
 (18,1046,44564621,'',1),
 (18,1047,44564641,'',1),
 (18,1048,44564661,'',1),
 (18,1049,44564681,'',1),
 (18,1050,44564701,'',1),
 (18,1051,44564721,'',1),
 (18,1052,44564741,'',1),
 (18,1053,44564761,'',1),
 (18,1054,44564781,'',1),
 (18,1055,44564801,'',1),
 (18,1056,44564821,'',1),
 (18,1057,44564841,'',1),
 (18,1058,44564861,'',1),
 (18,1059,15728641,'0.03125',1),
 (18,1060,15728643,'0.180000',1),
 (18,1061,15728644,'0.000000',1),
 (18,1062,15728645,'4.52375',1),
 (18,1063,15728648,'16.0208',1),
 (18,1064,15728646,'0',1),
 (18,1065,15728647,'0',1),
 (18,1066,49807361,'18',1),
 (18,1067,49807374,'0',1),
 (18,1068,49807387,'0',1),
 (18,1069,49807362,'1.5',1),
 (18,1070,49807375,'0',1),
 (18,1071,49807363,'1.5',1),
 (18,1072,49807376,'0',1),
 (18,1073,49807364,'1.5',1),
 (18,1074,49807377,'0',1),
 (18,1075,49807365,'1.5',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (18,1076,49807378,'0',1),
 (18,1077,49807366,'1.5',1),
 (18,1078,49807379,'0',1),
 (18,1079,49807367,'1.5',1),
 (18,1080,49807380,'0',1),
 (18,1081,49807368,'1.5',1),
 (18,1082,49807381,'0',1),
 (18,1083,49807369,'1.5',1),
 (18,1084,49807382,'0',1),
 (18,1085,49807370,'1.5',1),
 (18,1086,49807383,'0',1),
 (18,1087,49807371,'1.5',1),
 (18,1088,49807384,'0',1),
 (18,1089,49807372,'1.5',1),
 (18,1090,49807385,'0',1),
 (18,1091,49807373,'1.5',1),
 (18,1092,49807386,'0',1),
 (18,1093,34078721,'0',1),
 (18,1094,34078722,'0.562500',1),
 (18,1095,26214403,'',1),
 (18,1096,26214401,'',1),
 (18,1097,26214402,'0.000000',1),
 (18,1098,26214404,'0',1),
 (19,1099,1310721,'Demande état civil sans suite',1),
 (19,1100,1310722,'',1),
 (19,1101,1310723,'19',1),
 (19,1102,20971521,'',1),
 (19,1103,20971522,'',1),
 (19,1104,68157441,'',1),
 (19,1105,68157461,'',1),
 (19,1106,68157481,'',1),
 (19,1107,68157501,'',1),
 (19,1108,68157521,'',1),
 (19,1109,68157541,'',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (19,1110,68157561,'',1),
 (19,1111,68157581,'',1),
 (19,1112,68157601,'',1),
 (19,1113,68157621,'',1),
 (19,1114,68157641,'',1),
 (19,1115,68157661,'',1),
 (19,1116,68157681,'',1),
 (19,1117,68157701,'',1),
 (19,1118,68157721,'',1),
 (19,1119,68157741,'',1),
 (19,1120,68157761,'',1),
 (19,1121,68157781,'',1),
 (19,1122,68157801,'',1),
 (19,1123,68157821,'',1),
 (19,1124,44564481,'',1),
 (19,1125,44564501,'',1),
 (19,1126,44564521,'',1),
 (19,1127,44564541,'',1),
 (19,1128,44564561,'',1),
 (19,1129,44564581,'',1),
 (19,1130,44564601,'',1),
 (19,1131,44564621,'',1),
 (19,1132,44564641,'',1),
 (19,1133,44564661,'',1),
 (19,1134,44564681,'',1),
 (19,1135,44564701,'',1),
 (19,1136,44564721,'',1),
 (19,1137,44564741,'',1),
 (19,1138,44564761,'',1),
 (19,1139,44564781,'',1),
 (19,1140,44564801,'',1),
 (19,1141,44564821,'',1),
 (19,1142,44564841,'',1),
 (19,1143,44564861,'',1),
 (19,1144,15728641,'0.0104167',1),
 (19,1145,15728643,'0.020000',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (19,1146,15728644,'5.000000',1),
 (19,1147,15728645,'4.52583',1),
 (19,1148,15728648,'16.0229',1),
 (19,1149,15728646,'0.00208333',1),
 (19,1150,15728647,'0.00416667',1),
 (19,1151,49807361,'2',1),
 (19,1152,49807374,'0',1),
 (19,1153,49807387,'0',1),
 (19,1154,49807362,'0.166667',1),
 (19,1155,49807375,'0',1),
 (19,1156,49807363,'0.166667',1),
 (19,1157,49807376,'0',1),
 (19,1158,49807364,'0.166667',1),
 (19,1159,49807377,'0',1),
 (19,1160,49807365,'0.166667',1),
 (19,1161,49807378,'0',1),
 (19,1162,49807366,'0.166667',1),
 (19,1163,49807379,'0',1),
 (19,1164,49807367,'0.166667',1),
 (19,1165,49807380,'0',1),
 (19,1166,49807368,'0.166667',1),
 (19,1167,49807381,'0',1),
 (19,1168,49807369,'0.166667',1),
 (19,1169,49807382,'0',1),
 (19,1170,49807370,'0.166667',1),
 (19,1171,49807383,'0',1),
 (19,1172,49807371,'0.166667',1),
 (19,1173,49807384,'0',1),
 (19,1174,49807372,'0.166667',1),
 (19,1175,49807385,'0',1),
 (19,1176,49807373,'0.166667',1);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (19,1177,49807386,'0',1),
 (19,1178,34078721,'10',1),
 (19,1179,34078722,'0.020833',1),
 (19,1180,26214403,'',1),
 (19,1181,26214401,'',1),
 (19,1182,26214402,'0.000000',1),
 (19,1183,26214404,'0',1),
 (1,0,1310721,'Demande état civil',2),
 (1,1,1310722,'',2),
 (1,2,1310723,'1',2),
 (1,3,2621441,'',2),
 (1,4,73400321,'Acte de naissance',2),
 (1,5,73400322,'0.400000',2),
 (1,6,73400323,'40.000004',2),
 (1,7,73400324,'_:[v0]1557648201-45698',2),
 (1,8,73400321,'Acte de marriage',2),
 (1,9,73400322,'0.200000',2),
 (1,10,73400323,'20.000002',2),
 (1,11,73400324,'_:[v0]-1698303281-31489',2),
 (1,12,73400321,'Acte de décès',2),
 (1,13,73400322,'0.400000',2),
 (1,14,73400323,'40.000004',2),
 (1,15,73400324,'_:[v0]-1048620994-5003',2),
 (1,16,39321601,'31.1667',2),
 (1,17,39321602,'13981.5',2),
 (1,18,39321603,'4690',2),
 (1,19,39321604,'100.000008',2),
 (1,20,39321605,'0.311667',2),
 (1,21,39321606,'139.814575',2),
 (1,22,76021761,'Sans suite',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (1,23,76021762,'Demande état civil sans suite',2),
 (1,24,76021763,'2.000000',2),
 (1,25,76021764,'0.020000',2),
 (1,26,76021765,'Demande état civil sans suite',2),
 (1,27,76021761,'courrier',2),
 (1,28,76021762,'Acte état civil remis',2),
 (1,29,76021763,'18.000002',2),
 (1,30,76021764,'0.180000',2),
 (1,31,76021765,'Acte état civil remis',2),
 (1,32,76021761,'guichet',2),
 (1,33,76021762,'Acte état civil posté',2),
 (1,34,76021763,'80.000008',2),
 (1,35,76021764,'0.800000',2),
 (1,36,76021765,'Acte état civil posté',2),
 (2,37,1310721,'Demander acte état civil',2),
 (2,38,1310722,'à distance',2),
 (2,39,1310723,'2',2),
 (2,40,26214403,'_:[v0]205489264-15020',2),
 (2,41,26214401,'Administrés',2),
 (2,42,26214402,'200.000000',2),
 (3,43,1310721,'Demander acte état  civil',2),
 (3,44,1310722,'au guichet',2),
 (3,45,1310723,'3',2),
 (3,46,26214403,'_:[v0]205489264-15020',2),
 (3,47,26214401,'Administrés',2),
 (3,48,26214402,'200.000000',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (4,49,1310721,'Traitement demande état civil',2),
 (4,50,1310722,'',2),
 (4,51,1310723,'4',2),
 (4,52,47185921,'BD état civil',2),
 (4,53,20971521,'',2),
 (4,54,20971522,'',2),
 (4,55,68157441,'Attestation délivrée que pour les résident de la commune',2),
 (4,56,68157461,'Attestation délivrée dès émolument reçu',2),
 (4,57,68157481,'',2),
 (4,58,68157501,'',2),
 (4,59,68157521,'',2),
 (4,60,68157541,'',2),
 (4,61,68157561,'',2),
 (4,62,68157581,'',2),
 (4,63,68157601,'',2),
 (4,64,68157621,'',2),
 (4,65,68157641,'',2),
 (4,66,68157661,'',2),
 (4,67,68157681,'',2),
 (4,68,68157701,'',2),
 (4,69,68157721,'',2),
 (4,70,68157741,'',2),
 (4,71,68157761,'',2),
 (4,72,68157781,'',2),
 (4,73,68157801,'',2),
 (4,74,68157821,'',2),
 (4,75,41943041,'Verifier si dans la BD d\'état civil',2),
 (4,76,41943061,'Enregistrer la demande',2),
 (4,77,41943081,'Facturer acte état civil',2),
 (4,78,41943101,'Délivrer acte état civil',2),
 (4,79,41943121,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (4,80,41943141,'',2),
 (4,81,41943161,'',2),
 (4,82,41943181,'',2),
 (4,83,41943201,'',2),
 (4,84,41943221,'',2),
 (4,85,41943241,'',2),
 (4,86,41943261,'',2),
 (4,87,41943281,'',2),
 (4,88,41943301,'',2),
 (4,89,41943321,'',2),
 (4,90,41943341,'',2),
 (4,91,41943361,'',2),
 (4,92,41943381,'',2),
 (4,93,41943401,'',2),
 (4,94,41943421,'',2),
 (4,95,43253761,'',2),
 (4,96,43253781,'',2),
 (4,97,43253801,'',2),
 (4,98,43253821,'',2),
 (4,99,43253841,'',2),
 (4,100,43253861,'',2),
 (4,101,43253881,'',2),
 (4,102,43253901,'',2),
 (4,103,43253921,'',2),
 (4,104,43253941,'',2),
 (4,105,43253961,'',2),
 (4,106,43253981,'',2),
 (4,107,43254001,'',2),
 (4,108,43254021,'',2),
 (4,109,43254041,'',2),
 (4,110,43254061,'',2),
 (4,111,43254081,'',2),
 (4,112,43254101,'',2),
 (4,113,43254121,'',2),
 (4,114,43254141,'',2),
 (4,115,18350081,'1.000000',2),
 (4,116,18350082,'0.25',2),
 (4,117,18350083,'30.000000',2),
 (4,118,18350084,'7.44629',2),
 (4,119,18350085,'13.8959',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (4,120,26214402,'305.000000',2),
 (4,121,26214404,'0',2),
 (4,122,26214403,'_:[v0]-1851353336-60382',2),
 (4,123,26214401,'Secrétariat',2),
 (4,124,31457281,'distant',2),
 (4,125,31457282,'Demande état civil (d)',2),
 (4,126,31457283,'0.200000',2),
 (4,127,31457284,'Demande état civil (d)',2),
 (4,128,31457281,'guichet',2),
 (4,129,31457282,'Demande état civil (g)',2),
 (4,130,31457283,'0.400000',2),
 (4,131,31457284,'Demande état civil (g)',2),
 (4,132,31457281,'en ligne',2),
 (4,133,31457282,'Demande état civil validée par système (l)',2),
 (4,134,31457283,'0.400000',2),
 (4,135,31457284,'Demande état civil validée par système (l)',2),
 (4,136,36700161,'100',2),
 (4,137,36700162,'3090',2),
 (4,138,36700163,'29.125',2),
 (4,139,36700164,'11973.1',2),
 (4,140,36700165,'0.29125',2),
 (4,141,36700166,'119.731',2),
 (5,142,1310721,'Demande état civil (d)',2),
 (5,143,1310722,'',2),
 (5,144,1310723,'5',2),
 (5,145,47185921,'Fax',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (5,146,47185921,'Téléphone',2),
 (5,147,47185921,'Courrier',2),
 (5,148,47185921,'Fax',2),
 (5,149,20971521,'',2),
 (5,150,20971522,'',2),
 (5,151,68157441,'',2),
 (5,152,68157461,'',2),
 (5,153,68157481,'',2),
 (5,154,68157501,'',2),
 (5,155,68157521,'',2),
 (5,156,68157541,'',2),
 (5,157,68157561,'',2),
 (5,158,68157581,'',2),
 (5,159,68157601,'',2),
 (5,160,68157621,'',2),
 (5,161,68157641,'',2),
 (5,162,68157661,'',2),
 (5,163,68157681,'',2),
 (5,164,68157701,'',2),
 (5,165,68157721,'',2),
 (5,166,68157741,'',2),
 (5,167,68157761,'',2),
 (5,168,68157781,'',2),
 (5,169,68157801,'',2),
 (5,170,68157821,'',2),
 (5,171,44564481,'Nom',2),
 (5,172,44564501,'Prénom',2),
 (5,173,44564521,'Date de naissance',2),
 (5,174,44564541,'Adresse',2),
 (5,175,44564561,'Nr AVS',2),
 (5,176,44564581,'',2),
 (5,177,44564601,'',2),
 (5,178,44564621,'',2),
 (5,179,44564641,'',2),
 (5,180,44564661,'',2),
 (5,181,44564681,'',2),
 (5,182,44564701,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (5,183,44564721,'',2),
 (5,184,44564741,'',2),
 (5,185,44564761,'',2),
 (5,186,44564781,'',2),
 (5,187,44564801,'',2),
 (5,188,44564821,'',2),
 (5,189,44564841,'',2),
 (5,190,44564861,'',2),
 (5,191,15728641,'0.0104167',2),
 (5,192,15728643,'1.000000',2),
 (5,193,15728644,'50.000000',2),
 (5,194,15728645,'-1',2),
 (5,195,15728648,'-1',2),
 (5,196,15728646,'1',2),
 (5,197,15728647,'1',2),
 (5,198,49807361,'20',2),
 (5,199,49807374,'0',2),
 (5,200,49807387,'0',2),
 (5,201,49807362,'1.66667',2),
 (5,202,49807375,'0',2),
 (5,203,49807363,'1.66667',2),
 (5,204,49807376,'0',2),
 (5,205,49807364,'1.66667',2),
 (5,206,49807377,'0',2),
 (5,207,49807365,'1.66667',2),
 (5,208,49807378,'0',2),
 (5,209,49807366,'1.66667',2),
 (5,210,49807379,'0',2),
 (5,211,49807367,'1.66667',2),
 (5,212,49807380,'0',2),
 (5,213,49807368,'1.66667',2),
 (5,214,49807381,'0',2),
 (5,215,49807369,'1.66667',2),
 (5,216,49807382,'0',2),
 (5,217,49807370,'1.66667',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (5,218,49807383,'0',2),
 (5,219,49807371,'1.66667',2),
 (5,220,49807384,'0',2),
 (5,221,49807372,'1.66667',2),
 (5,222,49807385,'0',2),
 (5,223,49807373,'1.66667',2),
 (5,224,49807386,'0',2),
 (5,225,34078721,'1000',2),
 (5,226,34078722,'0.000000',2),
 (5,227,26214403,'',2),
 (5,228,26214401,'',2),
 (5,229,26214402,'0.000000',2),
 (5,230,26214404,'0',2),
 (6,231,1310721,'Demande état civil (g)',2),
 (6,232,1310722,'',2),
 (6,233,1310723,'6',2),
 (6,234,47185921,'Visite',2),
 (6,235,20971521,'',2),
 (6,236,20971522,'',2),
 (6,237,68157441,'',2),
 (6,238,68157461,'',2),
 (6,239,68157481,'',2),
 (6,240,68157501,'',2),
 (6,241,68157521,'',2),
 (6,242,68157541,'',2),
 (6,243,68157561,'',2),
 (6,244,68157581,'',2),
 (6,245,68157601,'',2),
 (6,246,68157621,'',2),
 (6,247,68157641,'',2),
 (6,248,68157661,'',2),
 (6,249,68157681,'',2),
 (6,250,68157701,'',2),
 (6,251,68157721,'',2),
 (6,252,68157741,'',2),
 (6,253,68157761,'',2),
 (6,254,68157781,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (6,255,68157801,'',2),
 (6,256,68157821,'',2),
 (6,257,44564481,'Nom',2),
 (6,258,44564501,'Prénom',2),
 (6,259,44564521,'Date de naissance',2),
 (6,260,44564541,'Adresse',2),
 (6,261,44564561,'Nr AVS',2),
 (6,262,44564581,'',2),
 (6,263,44564601,'',2),
 (6,264,44564621,'',2),
 (6,265,44564641,'',2),
 (6,266,44564661,'',2),
 (6,267,44564681,'',2),
 (6,268,44564701,'',2),
 (6,269,44564721,'',2),
 (6,270,44564741,'',2),
 (6,271,44564761,'',2),
 (6,272,44564781,'',2),
 (6,273,44564801,'',2),
 (6,274,44564821,'',2),
 (6,275,44564841,'',2),
 (6,276,44564861,'',2),
 (6,277,15728641,'0',2),
 (6,278,15728643,'1.000000',2),
 (6,279,15728644,'100.000000',2),
 (6,280,15728645,'-1',2),
 (6,281,15728648,'-1',2),
 (6,282,15728646,'1',2),
 (6,283,15728647,'1',2),
 (6,284,49807361,'40',2),
 (6,285,49807374,'0',2),
 (6,286,49807387,'0',2),
 (6,287,49807362,'3.33333',2),
 (6,288,49807375,'0',2),
 (6,289,49807363,'3.33333',2),
 (6,290,49807376,'0',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (6,291,49807364,'3.33333',2),
 (6,292,49807377,'0',2),
 (6,293,49807365,'3.33333',2),
 (6,294,49807378,'0',2),
 (6,295,49807366,'3.33333',2),
 (6,296,49807379,'0',2),
 (6,297,49807367,'3.33333',2),
 (6,298,49807380,'0',2),
 (6,299,49807368,'3.33333',2),
 (6,300,49807381,'0',2),
 (6,301,49807369,'3.33333',2),
 (6,302,49807382,'0',2),
 (6,303,49807370,'3.33333',2),
 (6,304,49807383,'0',2),
 (6,305,49807371,'3.33333',2),
 (6,306,49807384,'0',2),
 (6,307,49807372,'3.33333',2),
 (6,308,49807385,'0',2),
 (6,309,49807373,'3.33333',2),
 (6,310,49807386,'0',2),
 (6,311,34078721,'4000',2),
 (6,312,34078722,'0.000000',2),
 (6,313,26214403,'',2),
 (6,314,26214401,'',2),
 (6,315,26214402,'0.000000',2),
 (6,316,26214404,'0',2),
 (7,317,1310721,'Payer facture à état civil',2),
 (7,318,1310722,'',2),
 (7,319,1310723,'7',2),
 (7,320,47185921,'',2),
 (7,321,20971521,'',2),
 (7,322,20971522,'',2),
 (7,323,68157441,'',2),
 (7,324,68157461,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (7,325,68157481,'',2),
 (7,326,68157501,'',2),
 (7,327,68157521,'',2),
 (7,328,68157541,'',2),
 (7,329,68157561,'',2),
 (7,330,68157581,'',2),
 (7,331,68157601,'',2),
 (7,332,68157621,'',2),
 (7,333,68157641,'',2),
 (7,334,68157661,'',2),
 (7,335,68157681,'',2),
 (7,336,68157701,'',2),
 (7,337,68157721,'',2),
 (7,338,68157741,'',2),
 (7,339,68157761,'',2),
 (7,340,68157781,'',2),
 (7,341,68157801,'',2),
 (7,342,68157821,'',2),
 (7,343,41943041,'',2),
 (7,344,41943061,'',2),
 (7,345,41943081,'',2),
 (7,346,41943101,'',2),
 (7,347,41943121,'',2),
 (7,348,41943141,'',2),
 (7,349,41943161,'',2),
 (7,350,41943181,'',2),
 (7,351,41943201,'',2),
 (7,352,41943221,'',2),
 (7,353,41943241,'',2),
 (7,354,41943261,'',2),
 (7,355,41943281,'',2),
 (7,356,41943301,'',2),
 (7,357,41943321,'',2),
 (7,358,41943341,'',2),
 (7,359,41943361,'',2),
 (7,360,41943381,'',2),
 (7,361,41943401,'',2),
 (7,362,41943421,'',2),
 (7,363,43253761,'',2),
 (7,364,43253781,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (7,365,43253801,'',2),
 (7,366,43253821,'',2),
 (7,367,43253841,'',2),
 (7,368,43253861,'',2),
 (7,369,43253881,'',2),
 (7,370,43253901,'',2),
 (7,371,43253921,'',2),
 (7,372,43253941,'',2),
 (7,373,43253961,'',2),
 (7,374,43253981,'',2),
 (7,375,43254001,'',2),
 (7,376,43254021,'',2),
 (7,377,43254041,'',2),
 (7,378,43254061,'',2),
 (7,379,43254081,'',2),
 (7,380,43254101,'',2),
 (7,381,43254121,'',2),
 (7,382,43254141,'',2),
 (7,383,18350081,'1.000000',2),
 (7,384,18350082,'0',2),
 (7,385,18350083,'0.000000',2),
 (7,386,18350084,'7.01042',2),
 (7,387,18350085,'7.01042',2),
 (7,388,26214402,'200.000000',2),
 (7,389,26214404,'0',2),
 (7,390,26214403,'_:[v0]205489264-15020',2),
 (7,391,26214401,'Administrés',2),
 (7,392,31457281,'Comb 1',2),
 (7,393,31457282,'Facture état civil',2),
 (7,394,31457283,'1.000000',2),
 (7,395,31457284,'Facture état civil',2),
 (7,396,36700161,'60',2),
 (7,397,36700162,'120',2),
 (7,398,36700163,'0.625',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (7,399,36700164,'245',2),
 (7,400,36700165,'0.0104167',2),
 (7,401,36700166,'4.08333',2),
 (8,402,1310721,'Régler comptant état civil',2),
 (8,403,1310722,'',2),
 (8,404,1310723,'8',2),
 (8,405,47185921,'',2),
 (8,406,20971521,'',2),
 (8,407,20971522,'',2),
 (8,408,68157441,'',2),
 (8,409,68157461,'',2),
 (8,410,68157481,'',2),
 (8,411,68157501,'',2),
 (8,412,68157521,'',2),
 (8,413,68157541,'',2),
 (8,414,68157561,'',2),
 (8,415,68157581,'',2),
 (8,416,68157601,'',2),
 (8,417,68157621,'',2),
 (8,418,68157641,'',2),
 (8,419,68157661,'',2),
 (8,420,68157681,'',2),
 (8,421,68157701,'',2),
 (8,422,68157721,'',2),
 (8,423,68157741,'',2),
 (8,424,68157761,'',2),
 (8,425,68157781,'',2),
 (8,426,68157801,'',2),
 (8,427,68157821,'',2),
 (8,428,41943041,'Payer les émoluments',2),
 (8,429,41943061,'',2),
 (8,430,41943081,'',2),
 (8,431,41943101,'',2),
 (8,432,41943121,'',2),
 (8,433,41943141,'',2),
 (8,434,41943161,'',2),
 (8,435,41943181,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (8,436,41943201,'',2),
 (8,437,41943221,'',2),
 (8,438,41943241,'',2),
 (8,439,41943261,'',2),
 (8,440,41943281,'',2),
 (8,441,41943301,'',2),
 (8,442,41943321,'',2),
 (8,443,41943341,'',2),
 (8,444,41943361,'',2),
 (8,445,41943381,'',2),
 (8,446,41943401,'',2),
 (8,447,41943421,'',2),
 (8,448,43253761,'',2),
 (8,449,43253781,'',2),
 (8,450,43253801,'',2),
 (8,451,43253821,'',2),
 (8,452,43253841,'',2),
 (8,453,43253861,'',2),
 (8,454,43253881,'',2),
 (8,455,43253901,'',2),
 (8,456,43253921,'',2),
 (8,457,43253941,'',2),
 (8,458,43253961,'',2),
 (8,459,43253981,'',2),
 (8,460,43254001,'',2),
 (8,461,43254021,'',2),
 (8,462,43254041,'',2),
 (8,463,43254061,'',2),
 (8,464,43254081,'',2),
 (8,465,43254101,'',2),
 (8,466,43254121,'',2),
 (8,467,43254141,'',2),
 (8,468,18350081,'1.000000',2),
 (8,469,18350082,'0.0104167',2),
 (8,470,18350083,'25.000000',2),
 (8,471,18350084,'0.0145833',2),
 (8,472,18350085,'0.0145833',2),
 (8,473,26214402,'200.000000',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (8,474,26214404,'0',2),
 (8,475,26214403,'_:[v0]205489264-15020',2),
 (8,476,26214401,'Administrés',2),
 (8,477,31457281,'Comb 1',2),
 (8,478,31457282,'Demande payement émolument',2),
 (8,479,31457283,'1.000000',2),
 (8,480,31457284,'Demande payement émolument',2),
 (8,481,36700161,'40',2),
 (8,482,36700162,'1040',2),
 (8,483,36700163,'0.5',2),
 (8,484,36700164,'1140',2),
 (8,485,36700165,'0.0125',2),
 (8,486,36700166,'28.5',2),
 (9,487,1310721,'Demande payement émolument',2),
 (9,488,1310722,'',2),
 (9,489,1310723,'9',2),
 (9,490,20971521,'',2),
 (9,491,20971522,'',2),
 (9,492,68157441,'',2),
 (9,493,68157461,'',2),
 (9,494,68157481,'',2),
 (9,495,68157501,'',2),
 (9,496,68157521,'',2),
 (9,497,68157541,'',2),
 (9,498,68157561,'',2),
 (9,499,68157581,'',2),
 (9,500,68157601,'',2),
 (9,501,68157621,'',2),
 (9,502,68157641,'',2),
 (9,503,68157661,'',2),
 (9,504,68157681,'',2),
 (9,505,68157701,'',2),
 (9,506,68157721,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (9,507,68157741,'',2),
 (9,508,68157761,'',2),
 (9,509,68157781,'',2),
 (9,510,68157801,'',2),
 (9,511,68157821,'',2),
 (9,512,44564481,'',2),
 (9,513,44564501,'',2),
 (9,514,44564521,'',2),
 (9,515,44564541,'',2),
 (9,516,44564561,'',2),
 (9,517,44564581,'',2),
 (9,518,44564601,'',2),
 (9,519,44564621,'',2),
 (9,520,44564641,'',2),
 (9,521,44564661,'',2),
 (9,522,44564681,'',2),
 (9,523,44564701,'',2),
 (9,524,44564721,'',2),
 (9,525,44564741,'',2),
 (9,526,44564761,'',2),
 (9,527,44564781,'',2),
 (9,528,44564801,'',2),
 (9,529,44564821,'',2),
 (9,530,44564841,'',2),
 (9,531,44564861,'',2),
 (9,532,15728641,'0.0208333',2),
 (9,533,15728643,'0.400000',2),
 (9,534,15728644,'2.000000',2),
 (9,535,15728645,'0.0104167',2),
 (9,536,15728648,'0.0104167',2),
 (9,537,15728646,'0.0104167',2),
 (9,538,15728647,'0.0125',2),
 (9,539,49807361,'40',2),
 (9,540,49807374,'0',2),
 (9,541,49807387,'0',2),
 (9,542,49807362,'3.33333',2),
 (9,543,49807375,'0',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (9,544,49807363,'3.33333',2),
 (9,545,49807376,'0',2),
 (9,546,49807364,'3.33333',2),
 (9,547,49807377,'0',2),
 (9,548,49807365,'3.33333',2),
 (9,549,49807378,'0',2),
 (9,550,49807366,'3.33333',2),
 (9,551,49807379,'0',2),
 (9,552,49807367,'3.33333',2),
 (9,553,49807380,'0',2),
 (9,554,49807368,'3.33333',2),
 (9,555,49807381,'0',2),
 (9,556,49807369,'3.33333',2),
 (9,557,49807382,'0',2),
 (9,558,49807370,'3.33333',2),
 (9,559,49807383,'0',2),
 (9,560,49807371,'3.33333',2),
 (9,561,49807384,'0',2),
 (9,562,49807372,'3.33333',2),
 (9,563,49807385,'0',2),
 (9,564,49807373,'3.33333',2),
 (9,565,49807386,'0',2),
 (9,566,34078721,'80',2),
 (9,567,34078722,'0.833333',2),
 (9,568,26214403,'',2),
 (9,569,26214401,'',2),
 (9,570,26214402,'0.000000',2),
 (9,571,26214404,'0',2),
 (10,572,1310721,'Payement émolument',2),
 (10,573,1310722,'',2),
 (10,574,1310723,'10',2),
 (10,575,20971521,'',2),
 (10,576,20971522,'',2),
 (10,577,68157441,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (10,578,68157461,'',2),
 (10,579,68157481,'',2),
 (10,580,68157501,'',2),
 (10,581,68157521,'',2),
 (10,582,68157541,'',2),
 (10,583,68157561,'',2),
 (10,584,68157581,'',2),
 (10,585,68157601,'',2),
 (10,586,68157621,'',2),
 (10,587,68157641,'',2),
 (10,588,68157661,'',2),
 (10,589,68157681,'',2),
 (10,590,68157701,'',2),
 (10,591,68157721,'',2),
 (10,592,68157741,'',2),
 (10,593,68157761,'',2),
 (10,594,68157781,'',2),
 (10,595,68157801,'',2),
 (10,596,68157821,'',2),
 (10,597,44564481,'',2),
 (10,598,44564501,'',2),
 (10,599,44564521,'',2),
 (10,600,44564541,'',2),
 (10,601,44564561,'',2),
 (10,602,44564581,'',2),
 (10,603,44564601,'',2),
 (10,604,44564621,'',2),
 (10,605,44564641,'',2),
 (10,606,44564661,'',2),
 (10,607,44564681,'',2),
 (10,608,44564701,'',2),
 (10,609,44564721,'',2),
 (10,610,44564741,'',2),
 (10,611,44564761,'',2),
 (10,612,44564781,'',2),
 (10,613,44564801,'',2),
 (10,614,44564821,'',2),
 (10,615,44564841,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (10,616,44564861,'',2),
 (10,617,15728641,'0.00208333',2),
 (10,618,15728643,'1.000000',2),
 (10,619,15728644,'1.000000',2),
 (10,620,15728645,'0.025',2),
 (10,621,15728648,'0.025',2),
 (10,622,15728646,'0.00208333',2),
 (10,623,15728647,'0.00208333',2),
 (10,624,49807361,'40',2),
 (10,625,49807374,'0',2),
 (10,626,49807387,'0',2),
 (10,627,49807362,'3.33333',2),
 (10,628,49807375,'0',2),
 (10,629,49807363,'3.33333',2),
 (10,630,49807376,'0',2),
 (10,631,49807364,'3.33333',2),
 (10,632,49807377,'0',2),
 (10,633,49807365,'3.33333',2),
 (10,634,49807378,'0',2),
 (10,635,49807366,'3.33333',2),
 (10,636,49807379,'0',2),
 (10,637,49807367,'3.33333',2),
 (10,638,49807380,'0',2),
 (10,639,49807368,'3.33333',2),
 (10,640,49807381,'0',2),
 (10,641,49807369,'3.33333',2),
 (10,642,49807382,'0',2),
 (10,643,49807370,'3.33333',2),
 (10,644,49807383,'0',2),
 (10,645,49807371,'3.33333',2),
 (10,646,49807384,'0',2),
 (10,647,49807372,'3.33333',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (10,648,49807385,'0',2),
 (10,649,49807373,'3.33333',2),
 (10,650,49807386,'0',2),
 (10,651,34078721,'40',2),
 (10,652,34078722,'0.083333',2),
 (10,653,26214403,'',2),
 (10,654,26214401,'',2),
 (10,655,26214402,'0.000000',2),
 (10,656,26214404,'0',2),
 (11,657,1310721,'Facture état civil',2),
 (11,658,1310722,'',2),
 (11,659,1310723,'11',2),
 (11,660,47185921,'Courrier',2),
 (11,661,20971521,'',2),
 (11,662,20971522,'',2),
 (11,663,68157441,'',2),
 (11,664,68157461,'',2),
 (11,665,68157481,'',2),
 (11,666,68157501,'',2),
 (11,667,68157521,'',2),
 (11,668,68157541,'',2),
 (11,669,68157561,'',2),
 (11,670,68157581,'',2),
 (11,671,68157601,'',2),
 (11,672,68157621,'',2),
 (11,673,68157641,'',2),
 (11,674,68157661,'',2),
 (11,675,68157681,'',2),
 (11,676,68157701,'',2),
 (11,677,68157721,'',2),
 (11,678,68157741,'',2),
 (11,679,68157761,'',2),
 (11,680,68157781,'',2),
 (11,681,68157801,'',2),
 (11,682,68157821,'',2),
 (11,683,44564481,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (11,684,44564501,'',2),
 (11,685,44564521,'',2),
 (11,686,44564541,'',2),
 (11,687,44564561,'',2),
 (11,688,44564581,'',2),
 (11,689,44564601,'',2),
 (11,690,44564621,'',2),
 (11,691,44564641,'',2),
 (11,692,44564661,'',2),
 (11,693,44564681,'',2),
 (11,694,44564701,'',2),
 (11,695,44564721,'',2),
 (11,696,44564741,'',2),
 (11,697,44564761,'',2),
 (11,698,44564781,'',2),
 (11,699,44564801,'',2),
 (11,700,44564821,'',2),
 (11,701,44564841,'',2),
 (11,702,44564861,'',2),
 (11,703,15728641,'0.03125',2),
 (11,704,15728643,'0.600000',2),
 (11,705,15728644,'10.000000',2),
 (11,706,15728645,'7',2),
 (11,707,15728648,'7',2),
 (11,708,15728646,'7',2),
 (11,709,15728647,'7',2),
 (11,710,49807361,'60',2),
 (11,711,49807374,'0',2),
 (11,712,49807387,'0',2),
 (11,713,49807362,'5',2),
 (11,714,49807375,'0',2),
 (11,715,49807363,'5',2),
 (11,716,49807376,'0',2),
 (11,717,49807364,'5',2),
 (11,718,49807377,'0',2),
 (11,719,49807365,'5',2),
 (11,720,49807378,'0',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (11,721,49807366,'5',2),
 (11,722,49807379,'0',2),
 (11,723,49807367,'5',2),
 (11,724,49807380,'0',2),
 (11,725,49807368,'5',2),
 (11,726,49807381,'0',2),
 (11,727,49807369,'5',2),
 (11,728,49807382,'0',2),
 (11,729,49807370,'5',2),
 (11,730,49807383,'0',2),
 (11,731,49807371,'5',2),
 (11,732,49807384,'0',2),
 (11,733,49807372,'5',2),
 (11,734,49807385,'0',2),
 (11,735,49807373,'5',2),
 (11,736,49807386,'0',2),
 (11,737,34078721,'600',2),
 (11,738,34078722,'1.875000',2),
 (11,739,26214403,'',2),
 (11,740,26214401,'',2),
 (11,741,26214402,'0.000000',2),
 (11,742,26214404,'0',2),
 (12,743,1310721,'Payement facture état civil',2),
 (12,744,1310722,'',2),
 (12,745,1310723,'12',2),
 (12,746,20971521,'',2),
 (12,747,20971522,'',2),
 (12,748,68157441,'',2),
 (12,749,68157461,'',2),
 (12,750,68157481,'',2),
 (12,751,68157501,'',2),
 (12,752,68157521,'',2),
 (12,753,68157541,'',2),
 (12,754,68157561,'',2),
 (12,755,68157581,'',2),
 (12,756,68157601,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (12,757,68157621,'',2),
 (12,758,68157641,'',2),
 (12,759,68157661,'',2),
 (12,760,68157681,'',2),
 (12,761,68157701,'',2),
 (12,762,68157721,'',2),
 (12,763,68157741,'',2),
 (12,764,68157761,'',2),
 (12,765,68157781,'',2),
 (12,766,68157801,'',2),
 (12,767,68157821,'',2),
 (12,768,44564481,'',2),
 (12,769,44564501,'',2),
 (12,770,44564521,'',2),
 (12,771,44564541,'',2),
 (12,772,44564561,'',2),
 (12,773,44564581,'',2),
 (12,774,44564601,'',2),
 (12,775,44564621,'',2),
 (12,776,44564641,'',2),
 (12,777,44564661,'',2),
 (12,778,44564681,'',2),
 (12,779,44564701,'',2),
 (12,780,44564721,'',2),
 (12,781,44564741,'',2),
 (12,782,44564761,'',2),
 (12,783,44564781,'',2),
 (12,784,44564801,'',2),
 (12,785,44564821,'',2),
 (12,786,44564841,'',2),
 (12,787,44564861,'',2),
 (12,788,15728641,'0.0104167',2),
 (12,789,15728643,'0.900000',2),
 (12,790,15728644,'2.000000',2),
 (12,791,15728645,'14.0104',2),
 (12,792,15728648,'14.0104',2),
 (12,793,15728646,'0.0104167',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (12,794,15728647,'0.0104167',2),
 (12,795,49807361,'54',2),
 (12,796,49807374,'0',2),
 (12,797,49807387,'0',2),
 (12,798,49807362,'4.5',2),
 (12,799,49807375,'0',2),
 (12,800,49807363,'4.5',2),
 (12,801,49807376,'0',2),
 (12,802,49807364,'4.5',2),
 (12,803,49807377,'0',2),
 (12,804,49807365,'4.5',2),
 (12,805,49807378,'0',2),
 (12,806,49807366,'4.5',2),
 (12,807,49807379,'0',2),
 (12,808,49807367,'4.5',2),
 (12,809,49807380,'0',2),
 (12,810,49807368,'4.5',2),
 (12,811,49807381,'0',2),
 (12,812,49807369,'4.5',2),
 (12,813,49807382,'0',2),
 (12,814,49807370,'4.5',2),
 (12,815,49807383,'0',2),
 (12,816,49807371,'4.5',2),
 (12,817,49807384,'0',2),
 (12,818,49807372,'4.5',2),
 (12,819,49807385,'0',2),
 (12,820,49807373,'4.5',2),
 (12,821,49807386,'0',2),
 (12,822,34078721,'108',2),
 (12,823,34078722,'0.562500',2),
 (12,824,26214403,'',2),
 (12,825,26214401,'',2),
 (12,826,26214402,'0.000000',2),
 (12,827,26214404,'0',2),
 (13,828,1310721,'Absence de payement état civil',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (13,829,1310722,'',2),
 (13,830,1310723,'13',2),
 (13,831,20971521,'',2),
 (13,832,20971522,'',2),
 (13,833,68157441,'',2),
 (13,834,68157461,'',2),
 (13,835,68157481,'',2),
 (13,836,68157501,'',2),
 (13,837,68157521,'',2),
 (13,838,68157541,'',2),
 (13,839,68157561,'',2),
 (13,840,68157581,'',2),
 (13,841,68157601,'',2),
 (13,842,68157621,'',2),
 (13,843,68157641,'',2),
 (13,844,68157661,'',2),
 (13,845,68157681,'',2),
 (13,846,68157701,'',2),
 (13,847,68157721,'',2),
 (13,848,68157741,'',2),
 (13,849,68157761,'',2),
 (13,850,68157781,'',2),
 (13,851,68157801,'',2),
 (13,852,68157821,'',2),
 (13,853,44564481,'',2),
 (13,854,44564501,'',2),
 (13,855,44564521,'',2),
 (13,856,44564541,'',2),
 (13,857,44564561,'',2),
 (13,858,44564581,'',2),
 (13,859,44564601,'',2),
 (13,860,44564621,'',2),
 (13,861,44564641,'',2),
 (13,862,44564661,'',2),
 (13,863,44564681,'',2),
 (13,864,44564701,'',2),
 (13,865,44564721,'',2),
 (13,866,44564741,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (13,867,44564761,'',2),
 (13,868,44564781,'',2),
 (13,869,44564801,'',2),
 (13,870,44564821,'',2),
 (13,871,44564841,'',2),
 (13,872,44564861,'',2),
 (13,873,15728641,'0.0104167',2),
 (13,874,15728643,'0.100000',2),
 (13,875,15728644,'2.000000',2),
 (13,876,15728645,'14.0104',2),
 (13,877,15728648,'14.0104',2),
 (13,878,15728646,'0.0104167',2),
 (13,879,15728647,'0.0104167',2),
 (13,880,49807361,'6',2),
 (13,881,49807374,'0',2),
 (13,882,49807387,'0',2),
 (13,883,49807362,'0.5',2),
 (13,884,49807375,'0',2),
 (13,885,49807363,'0.5',2),
 (13,886,49807376,'0',2),
 (13,887,49807364,'0.5',2),
 (13,888,49807377,'0',2),
 (13,889,49807365,'0.5',2),
 (13,890,49807378,'0',2),
 (13,891,49807366,'0.5',2),
 (13,892,49807379,'0',2),
 (13,893,49807367,'0.5',2),
 (13,894,49807380,'0',2),
 (13,895,49807368,'0.5',2),
 (13,896,49807381,'0',2),
 (13,897,49807369,'0.5',2),
 (13,898,49807382,'0',2),
 (13,899,49807370,'0.5',2),
 (13,900,49807383,'0',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (13,901,49807371,'0.5',2),
 (13,902,49807384,'0',2),
 (13,903,49807372,'0.5',2),
 (13,904,49807385,'0',2),
 (13,905,49807373,'0.5',2),
 (13,906,49807386,'0',2),
 (13,907,34078721,'12',2),
 (13,908,34078722,'0.062500',2),
 (13,909,26214403,'',2),
 (13,910,26214401,'',2),
 (13,911,26214402,'0.000000',2),
 (13,912,26214404,'0',2),
 (14,913,1310721,'Abandonner demander état civil',2),
 (14,914,1310722,'',2),
 (14,915,1310723,'14',2),
 (14,916,26214403,'_:[v0]205489264-15020',2),
 (14,917,26214401,'Administrés',2),
 (14,918,26214402,'200.000000',2),
 (15,919,1310721,'Recevoir acte état civil',2),
 (15,920,1310722,'',2),
 (15,921,1310723,'15',2),
 (15,922,26214403,'_:[v0]205489264-15020',2),
 (15,923,26214401,'Administrés',2),
 (15,924,26214402,'200.000000',2),
 (16,925,1310721,'Obtenir acte état civil',2),
 (16,926,1310722,'',2),
 (16,927,1310723,'16',2),
 (16,928,26214403,'_:[v0]205489264-15020',2),
 (16,929,26214401,'Administrés',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (16,930,26214402,'200.000000',2),
 (17,931,1310721,'Acte état civil posté',2),
 (17,932,1310722,'',2),
 (17,933,1310723,'17',2),
 (17,934,47185921,'Visite',2),
 (17,935,20971521,'',2),
 (17,936,20971522,'',2),
 (17,937,68157441,'',2),
 (17,938,68157461,'',2),
 (17,939,68157481,'',2),
 (17,940,68157501,'',2),
 (17,941,68157521,'',2),
 (17,942,68157541,'',2),
 (17,943,68157561,'',2),
 (17,944,68157581,'',2),
 (17,945,68157601,'',2),
 (17,946,68157621,'',2),
 (17,947,68157641,'',2),
 (17,948,68157661,'',2),
 (17,949,68157681,'',2),
 (17,950,68157701,'',2),
 (17,951,68157721,'',2),
 (17,952,68157741,'',2),
 (17,953,68157761,'',2),
 (17,954,68157781,'',2),
 (17,955,68157801,'',2),
 (17,956,68157821,'',2),
 (17,957,44564481,'',2),
 (17,958,44564501,'',2),
 (17,959,44564521,'',2),
 (17,960,44564541,'',2),
 (17,961,44564561,'',2),
 (17,962,44564581,'',2),
 (17,963,44564601,'',2),
 (17,964,44564621,'',2),
 (17,965,44564641,'',2),
 (17,966,44564661,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (17,967,44564681,'',2),
 (17,968,44564701,'',2),
 (17,969,44564721,'',2),
 (17,970,44564741,'',2),
 (17,971,44564761,'',2),
 (17,972,44564781,'',2),
 (17,973,44564801,'',2),
 (17,974,44564821,'',2),
 (17,975,44564841,'',2),
 (17,976,44564861,'',2),
 (17,977,15728641,'0.0104167',2),
 (17,978,15728643,'0.800000',2),
 (17,979,15728644,'0.000000',2),
 (17,980,15728645,'7.57125',2),
 (17,981,15728648,'14.0208',2),
 (17,982,15728646,'0',2),
 (17,983,15728647,'0',2),
 (17,984,49807361,'80',2),
 (17,985,49807374,'0',2),
 (17,986,49807387,'0',2),
 (17,987,49807362,'6.66667',2),
 (17,988,49807375,'0',2),
 (17,989,49807363,'6.66667',2),
 (17,990,49807376,'0',2),
 (17,991,49807364,'6.66667',2),
 (17,992,49807377,'0',2),
 (17,993,49807365,'6.66667',2),
 (17,994,49807378,'0',2),
 (17,995,49807366,'6.66667',2),
 (17,996,49807379,'0',2),
 (17,997,49807367,'6.66667',2),
 (17,998,49807380,'0',2),
 (17,999,49807368,'6.66667',2),
 (17,1000,49807381,'0',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (17,1001,49807369,'6.66667',2),
 (17,1002,49807382,'0',2),
 (17,1003,49807370,'6.66667',2),
 (17,1004,49807383,'0',2),
 (17,1005,49807371,'6.66667',2),
 (17,1006,49807384,'0',2),
 (17,1007,49807372,'6.66667',2),
 (17,1008,49807385,'0',2),
 (17,1009,49807373,'6.66667',2),
 (17,1010,49807386,'0',2),
 (17,1011,34078721,'0',2),
 (17,1012,34078722,'0.833333',2),
 (17,1013,26214403,'',2),
 (17,1014,26214401,'',2),
 (17,1015,26214402,'0.000000',2),
 (17,1016,26214404,'0',2),
 (18,1017,1310721,'Acte état civil remis',2),
 (18,1018,1310722,'',2),
 (18,1019,1310723,'18',2),
 (18,1020,47185921,'Courrier',2),
 (18,1021,20971521,'',2),
 (18,1022,20971522,'',2),
 (18,1023,68157441,'',2),
 (18,1024,68157461,'',2),
 (18,1025,68157481,'',2),
 (18,1026,68157501,'',2),
 (18,1027,68157521,'',2),
 (18,1028,68157541,'',2),
 (18,1029,68157561,'',2),
 (18,1030,68157581,'',2),
 (18,1031,68157601,'',2),
 (18,1032,68157621,'',2),
 (18,1033,68157641,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (18,1034,68157661,'',2),
 (18,1035,68157681,'',2),
 (18,1036,68157701,'',2),
 (18,1037,68157721,'',2),
 (18,1038,68157741,'',2),
 (18,1039,68157761,'',2),
 (18,1040,68157781,'',2),
 (18,1041,68157801,'',2),
 (18,1042,68157821,'',2),
 (18,1043,44564481,'',2),
 (18,1044,44564501,'',2),
 (18,1045,44564521,'',2),
 (18,1046,44564541,'',2),
 (18,1047,44564561,'',2),
 (18,1048,44564581,'',2),
 (18,1049,44564601,'',2),
 (18,1050,44564621,'',2),
 (18,1051,44564641,'',2),
 (18,1052,44564661,'',2),
 (18,1053,44564681,'',2),
 (18,1054,44564701,'',2),
 (18,1055,44564721,'',2),
 (18,1056,44564741,'',2),
 (18,1057,44564761,'',2),
 (18,1058,44564781,'',2),
 (18,1059,44564801,'',2),
 (18,1060,44564821,'',2),
 (18,1061,44564841,'',2),
 (18,1062,44564861,'',2),
 (18,1063,15728641,'0.03125',2),
 (18,1064,15728643,'0.180000',2),
 (18,1065,15728644,'0.000000',2),
 (18,1066,15728645,'7.57125',2),
 (18,1067,15728648,'14.0208',2),
 (18,1068,15728646,'0',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (18,1069,15728647,'0',2),
 (18,1070,49807361,'18',2),
 (18,1071,49807374,'0',2),
 (18,1072,49807387,'0',2),
 (18,1073,49807362,'1.5',2),
 (18,1074,49807375,'0',2),
 (18,1075,49807363,'1.5',2),
 (18,1076,49807376,'0',2),
 (18,1077,49807364,'1.5',2),
 (18,1078,49807377,'0',2),
 (18,1079,49807365,'1.5',2),
 (18,1080,49807378,'0',2),
 (18,1081,49807366,'1.5',2),
 (18,1082,49807379,'0',2),
 (18,1083,49807367,'1.5',2),
 (18,1084,49807380,'0',2),
 (18,1085,49807368,'1.5',2),
 (18,1086,49807381,'0',2),
 (18,1087,49807369,'1.5',2),
 (18,1088,49807382,'0',2),
 (18,1089,49807370,'1.5',2),
 (18,1090,49807383,'0',2),
 (18,1091,49807371,'1.5',2),
 (18,1092,49807384,'0',2),
 (18,1093,49807372,'1.5',2),
 (18,1094,49807385,'0',2),
 (18,1095,49807373,'1.5',2),
 (18,1096,49807386,'0',2),
 (18,1097,34078721,'0',2),
 (18,1098,34078722,'0.562500',2),
 (18,1099,26214403,'',2),
 (18,1100,26214401,'',2),
 (18,1101,26214402,'0.000000',2),
 (18,1102,26214404,'0',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (19,1103,1310721,'Demande état civil sans suite',2),
 (19,1104,1310722,'',2),
 (19,1105,1310723,'19',2),
 (19,1106,20971521,'',2),
 (19,1107,20971522,'',2),
 (19,1108,68157441,'',2),
 (19,1109,68157461,'',2),
 (19,1110,68157481,'',2),
 (19,1111,68157501,'',2),
 (19,1112,68157521,'',2),
 (19,1113,68157541,'',2),
 (19,1114,68157561,'',2),
 (19,1115,68157581,'',2),
 (19,1116,68157601,'',2),
 (19,1117,68157621,'',2),
 (19,1118,68157641,'',2),
 (19,1119,68157661,'',2),
 (19,1120,68157681,'',2),
 (19,1121,68157701,'',2),
 (19,1122,68157721,'',2),
 (19,1123,68157741,'',2),
 (19,1124,68157761,'',2),
 (19,1125,68157781,'',2),
 (19,1126,68157801,'',2),
 (19,1127,68157821,'',2),
 (19,1128,44564481,'',2),
 (19,1129,44564501,'',2),
 (19,1130,44564521,'',2),
 (19,1131,44564541,'',2),
 (19,1132,44564561,'',2),
 (19,1133,44564581,'',2),
 (19,1134,44564601,'',2),
 (19,1135,44564621,'',2),
 (19,1136,44564641,'',2),
 (19,1137,44564661,'',2),
 (19,1138,44564681,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (19,1139,44564701,'',2),
 (19,1140,44564721,'',2),
 (19,1141,44564741,'',2),
 (19,1142,44564761,'',2),
 (19,1143,44564781,'',2),
 (19,1144,44564801,'',2),
 (19,1145,44564821,'',2),
 (19,1146,44564841,'',2),
 (19,1147,44564861,'',2),
 (19,1148,15728641,'0.0104167',2),
 (19,1149,15728643,'0.020000',2),
 (19,1150,15728644,'5.000000',2),
 (19,1151,15728645,'7.57333',2),
 (19,1152,15728648,'14.0229',2),
 (19,1153,15728646,'0.00208333',2),
 (19,1154,15728647,'0.00416667',2),
 (19,1155,49807361,'2',2),
 (19,1156,49807374,'0',2),
 (19,1157,49807387,'0',2),
 (19,1158,49807362,'0.166667',2),
 (19,1159,49807375,'0',2),
 (19,1160,49807363,'0.166667',2),
 (19,1161,49807376,'0',2),
 (19,1162,49807364,'0.166667',2),
 (19,1163,49807377,'0',2),
 (19,1164,49807365,'0.166667',2),
 (19,1165,49807378,'0',2),
 (19,1166,49807366,'0.166667',2),
 (19,1167,49807379,'0',2),
 (19,1168,49807367,'0.166667',2),
 (19,1169,49807380,'0',2),
 (19,1170,49807368,'0.166667',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (19,1171,49807381,'0',2),
 (19,1172,49807369,'0.166667',2),
 (19,1173,49807382,'0',2),
 (19,1174,49807370,'0.166667',2),
 (19,1175,49807383,'0',2),
 (19,1176,49807371,'0.166667',2),
 (19,1177,49807384,'0',2),
 (19,1178,49807372,'0.166667',2),
 (19,1179,49807385,'0',2),
 (19,1180,49807373,'0.166667',2),
 (19,1181,49807386,'0',2),
 (19,1182,34078721,'10',2),
 (19,1183,34078722,'0.020833',2),
 (19,1184,26214403,'',2),
 (19,1185,26214401,'',2),
 (19,1186,26214402,'0.000000',2),
 (19,1187,26214404,'0',2),
 (20,1188,1310721,'Demander acte état civil',2),
 (20,1189,1310722,'en ligne',2),
 (20,1190,1310723,'20',2),
 (20,1191,26214403,'_:[v0]205489264-15020',2),
 (20,1192,26214401,'Administrés',2),
 (20,1193,26214402,'200.000000',2),
 (21,1194,1310721,'Saisie de demande état civil',2),
 (21,1195,1310722,'',2),
 (21,1196,1310723,'21',2),
 (21,1197,47185921,'',2),
 (21,1198,20971521,'',2),
 (21,1199,20971522,'',2),
 (21,1200,68157441,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (21,1201,68157461,'',2),
 (21,1202,68157481,'',2),
 (21,1203,68157501,'',2),
 (21,1204,68157521,'',2),
 (21,1205,68157541,'',2),
 (21,1206,68157561,'',2),
 (21,1207,68157581,'',2),
 (21,1208,68157601,'',2),
 (21,1209,68157621,'',2),
 (21,1210,68157641,'',2),
 (21,1211,68157661,'',2),
 (21,1212,68157681,'',2),
 (21,1213,68157701,'',2),
 (21,1214,68157721,'',2),
 (21,1215,68157741,'',2),
 (21,1216,68157761,'',2),
 (21,1217,68157781,'',2),
 (21,1218,68157801,'',2),
 (21,1219,68157821,'',2),
 (21,1220,41943041,'',2),
 (21,1221,41943061,'',2),
 (21,1222,41943081,'',2),
 (21,1223,41943101,'',2),
 (21,1224,41943121,'',2),
 (21,1225,41943141,'',2),
 (21,1226,41943161,'',2),
 (21,1227,41943181,'',2),
 (21,1228,41943201,'',2),
 (21,1229,41943221,'',2),
 (21,1230,41943241,'',2),
 (21,1231,41943261,'',2),
 (21,1232,41943281,'',2),
 (21,1233,41943301,'',2),
 (21,1234,41943321,'',2),
 (21,1235,41943341,'',2),
 (21,1236,41943361,'',2),
 (21,1237,41943381,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (21,1238,41943401,'',2),
 (21,1239,41943421,'',2),
 (21,1240,43253761,'',2),
 (21,1241,43253781,'',2),
 (21,1242,43253801,'',2),
 (21,1243,43253821,'',2),
 (21,1244,43253841,'',2),
 (21,1245,43253861,'',2),
 (21,1246,43253881,'',2),
 (21,1247,43253901,'',2),
 (21,1248,43253921,'',2),
 (21,1249,43253941,'',2),
 (21,1250,43253961,'',2),
 (21,1251,43253981,'',2),
 (21,1252,43254001,'',2),
 (21,1253,43254021,'',2),
 (21,1254,43254041,'',2),
 (21,1255,43254061,'',2),
 (21,1256,43254081,'',2),
 (21,1257,43254101,'',2),
 (21,1258,43254121,'',2),
 (21,1259,43254141,'',2),
 (21,1260,18350081,'1.000000',2),
 (21,1261,18350082,'0.0208333',2),
 (21,1262,18350083,'10.000000',2),
 (21,1263,18350084,'0.125',2),
 (21,1264,18350085,'0.125',2),
 (21,1265,26214402,'200.000000',2),
 (21,1266,26214404,'0',2),
 (21,1267,26214403,'_:[v0]205489264-15020',2),
 (21,1268,26214401,'Administrés',2),
 (21,1269,31457281,'Comb 1',2),
 (21,1270,31457282,'Demande état civil en ligne',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (21,1271,31457283,'1.000000',2),
 (21,1272,31457284,'Demande état civil en ligne',2),
 (21,1273,36700161,'40',2),
 (21,1274,36700162,'440',2),
 (21,1275,36700163,'0.916667',2),
 (21,1276,36700164,'623.333',2),
 (21,1277,36700165,'0.0229167',2),
 (21,1278,36700166,'15.5833',2),
 (22,1279,1310721,'Demande état civil en ligne',2),
 (22,1280,1310722,'',2),
 (22,1281,1310723,'22',2),
 (22,1282,20971521,'',2),
 (22,1283,20971522,'',2),
 (22,1284,68157441,'',2),
 (22,1285,68157461,'',2),
 (22,1286,68157481,'',2),
 (22,1287,68157501,'',2),
 (22,1288,68157521,'',2),
 (22,1289,68157541,'',2),
 (22,1290,68157561,'',2),
 (22,1291,68157581,'',2),
 (22,1292,68157601,'',2),
 (22,1293,68157621,'',2),
 (22,1294,68157641,'',2),
 (22,1295,68157661,'',2),
 (22,1296,68157681,'',2),
 (22,1297,68157701,'',2),
 (22,1298,68157721,'',2),
 (22,1299,68157741,'',2),
 (22,1300,68157761,'',2),
 (22,1301,68157781,'',2),
 (22,1302,68157801,'',2),
 (22,1303,68157821,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (22,1304,44564481,'',2),
 (22,1305,44564501,'',2),
 (22,1306,44564521,'',2),
 (22,1307,44564541,'',2),
 (22,1308,44564561,'',2),
 (22,1309,44564581,'',2),
 (22,1310,44564601,'',2),
 (22,1311,44564621,'',2),
 (22,1312,44564641,'',2),
 (22,1313,44564661,'',2),
 (22,1314,44564681,'',2),
 (22,1315,44564701,'',2),
 (22,1316,44564721,'',2),
 (22,1317,44564741,'',2),
 (22,1318,44564761,'',2),
 (22,1319,44564781,'',2),
 (22,1320,44564801,'',2),
 (22,1321,44564821,'',2),
 (22,1322,44564841,'',2),
 (22,1323,44564861,'',2),
 (22,1324,15728641,'0',2),
 (22,1325,15728643,'1.000000',2),
 (22,1326,15728644,'0.000000',2),
 (22,1327,15728645,'0',2),
 (22,1328,15728648,'0',2),
 (22,1329,15728646,'0',2),
 (22,1330,15728647,'0',2),
 (22,1331,49807361,'40',2),
 (22,1332,49807374,'0',2),
 (22,1333,49807387,'0',2),
 (22,1334,49807362,'3.33333',2),
 (22,1335,49807375,'0',2),
 (22,1336,49807363,'3.33333',2),
 (22,1337,49807376,'0',2),
 (22,1338,49807364,'3.33333',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (22,1339,49807377,'0',2),
 (22,1340,49807365,'3.33333',2),
 (22,1341,49807378,'0',2),
 (22,1342,49807366,'3.33333',2),
 (22,1343,49807379,'0',2),
 (22,1344,49807367,'3.33333',2),
 (22,1345,49807380,'0',2),
 (22,1346,49807368,'3.33333',2),
 (22,1347,49807381,'0',2),
 (22,1348,49807369,'3.33333',2),
 (22,1349,49807382,'0',2),
 (22,1350,49807370,'3.33333',2),
 (22,1351,49807383,'0',2),
 (22,1352,49807371,'3.33333',2),
 (22,1353,49807384,'0',2),
 (22,1354,49807372,'3.33333',2),
 (22,1355,49807385,'0',2),
 (22,1356,49807373,'3.33333',2),
 (22,1357,49807386,'0',2),
 (22,1358,34078721,'0',2),
 (22,1359,34078722,'0.000000',2),
 (22,1360,26214403,'',2),
 (22,1361,26214401,'',2),
 (22,1362,26214402,'0.000000',2),
 (22,1363,26214404,'0',2),
 (23,1364,1310721,'Demande état civil validée par système (l)',2),
 (23,1365,1310722,'',2),
 (23,1366,1310723,'23',2),
 (23,1367,20971521,'',2),
 (23,1368,20971522,'',2),
 (23,1369,68157441,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (23,1370,68157461,'',2),
 (23,1371,68157481,'',2),
 (23,1372,68157501,'',2),
 (23,1373,68157521,'',2),
 (23,1374,68157541,'',2),
 (23,1375,68157561,'',2),
 (23,1376,68157581,'',2),
 (23,1377,68157601,'',2),
 (23,1378,68157621,'',2),
 (23,1379,68157641,'',2),
 (23,1380,68157661,'',2),
 (23,1381,68157681,'',2),
 (23,1382,68157701,'',2),
 (23,1383,68157721,'',2),
 (23,1384,68157741,'',2),
 (23,1385,68157761,'',2),
 (23,1386,68157781,'',2),
 (23,1387,68157801,'',2),
 (23,1388,68157821,'',2),
 (23,1389,44564481,'',2),
 (23,1390,44564501,'',2),
 (23,1391,44564521,'',2),
 (23,1392,44564541,'',2),
 (23,1393,44564561,'',2),
 (23,1394,44564581,'',2),
 (23,1395,44564601,'',2),
 (23,1396,44564621,'',2),
 (23,1397,44564641,'',2),
 (23,1398,44564661,'',2),
 (23,1399,44564681,'',2),
 (23,1400,44564701,'',2),
 (23,1401,44564721,'',2),
 (23,1402,44564741,'',2),
 (23,1403,44564761,'',2),
 (23,1404,44564781,'',2),
 (23,1405,44564801,'',2),
 (23,1406,44564821,'',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (23,1407,44564841,'',2),
 (23,1408,44564861,'',2),
 (23,1409,15728641,'0.00208333',2),
 (23,1410,15728643,'1.000000',2),
 (23,1411,15728644,'1.000000',2),
 (23,1412,15728645,'0.125',2),
 (23,1413,15728648,'0.125',2),
 (23,1414,15728646,'0.125',2),
 (23,1415,15728647,'0.375',2),
 (23,1416,49807361,'40',2),
 (23,1417,49807374,'0',2),
 (23,1418,49807387,'0',2),
 (23,1419,49807362,'3.33333',2),
 (23,1420,49807375,'0',2),
 (23,1421,49807363,'3.33333',2),
 (23,1422,49807376,'0',2),
 (23,1423,49807364,'3.33333',2),
 (23,1424,49807377,'0',2),
 (23,1425,49807365,'3.33333',2),
 (23,1426,49807378,'0',2),
 (23,1427,49807366,'3.33333',2),
 (23,1428,49807379,'0',2),
 (23,1429,49807367,'3.33333',2),
 (23,1430,49807380,'0',2),
 (23,1431,49807368,'3.33333',2),
 (23,1432,49807381,'0',2),
 (23,1433,49807369,'3.33333',2),
 (23,1434,49807382,'0',2),
 (23,1435,49807370,'3.33333',2),
 (23,1436,49807383,'0',2),
 (23,1437,49807371,'3.33333',2),
 (23,1438,49807384,'0',2);
INSERT INTO `ppdattr` (`pdattribid`,`prow`,`attribdefid`,`mvalue`,`modelid`) VALUES 
 (23,1439,49807372,'3.33333',2),
 (23,1440,49807385,'0',2),
 (23,1441,49807373,'3.33333',2),
 (23,1442,49807386,'0',2),
 (23,1443,34078721,'40',2),
 (23,1444,34078722,'0.083333',2),
 (23,1445,26214403,'',2),
 (23,1446,26214401,'',2),
 (23,1447,26214402,'0.000000',2),
 (23,1448,26214404,'0',2);
/*!40000 ALTER TABLE `ppdattr` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`ppersonalize`
--

DROP TABLE IF EXISTS `ppersonalize`;
CREATE TABLE `ppersonalize` (
  `login` varchar(32) NOT NULL default '',
  `userskin` varchar(32) NOT NULL default '',
  `defaulttab` int(11) NOT NULL default '0',
  PRIMARY KEY  (`login`)
);

--
-- Dumping data for table `mercutio2`.`ppersonalize`
--

/*!40000 ALTER TABLE `ppersonalize` DISABLE KEYS */;
INSERT INTO `ppersonalize` (`login`,`userskin`,`defaulttab`) VALUES 
 ('grime','2',0),
 ('gmd','2',0),
 ('admin','1',0);
/*!40000 ALTER TABLE `ppersonalize` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pprestations`
--

DROP TABLE IF EXISTS `pprestations`;
CREATE TABLE `pprestations` (
  `prestationtitle` varchar(100) NOT NULL default '',
  `prestationparent` int(11) NOT NULL default '0',
  `prestationid` int(11) NOT NULL auto_increment,
  PRIMARY KEY  (`prestationid`)
);

--
-- Dumping data for table `mercutio2`.`pprestations`
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
-- Table structure for table `mercutio2`.`pproc`
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
);

--
-- Dumping data for table `mercutio2`.`pproc`
--

/*!40000 ALTER TABLE `pproc` DISABLE KEYS */;
INSERT INTO `pproc` (`procid`,`wkgid`,`pdattribid`,`modelid`,`execid`,`proctype`,`doublesign`,`procidprocessus`,`procstableid`) VALUES 
 (1,0,1,1,-1,4,0,0,1),
 (2,995,2,1,-1,0,0,1,2),
 (3,995,3,1,-1,0,0,1,3),
 (4,993,4,1,-1,2,0,1,4),
 (5,995,7,1,-1,2,0,1,7),
 (6,995,8,1,-1,2,0,1,8),
 (7,995,14,1,-1,1,0,1,14),
 (8,995,15,1,-1,1,0,1,15),
 (9,995,16,1,-1,1,0,1,16),
 (10,0,1,2,-1,4,0,0,1),
 (11,995,2,2,-1,0,0,10,2),
 (12,995,3,2,-1,0,0,10,3),
 (13,993,4,2,-1,2,0,10,4),
 (14,995,7,2,-1,2,0,10,7),
 (15,995,8,2,-1,2,0,10,8),
 (16,995,14,2,-1,1,0,10,14),
 (17,995,15,2,-1,1,0,10,15),
 (18,995,16,2,-1,1,0,10,16),
 (19,995,20,2,-1,0,0,10,20),
 (20,995,21,2,-1,2,0,10,21);
/*!40000 ALTER TABLE `pproc` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pprocstable`
--

DROP TABLE IF EXISTS `pprocstable`;
CREATE TABLE `pprocstable` (
  `PROCSTABLEID` int(11) NOT NULL,
  `PROCSTABLEDESC` varchar(35) default NULL,
  PRIMARY KEY  (`PROCSTABLEID`)
);

--
-- Dumping data for table `mercutio2`.`pprocstable`
--

/*!40000 ALTER TABLE `pprocstable` DISABLE KEYS */;
/*!40000 ALTER TABLE `pprocstable` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pproctrans`
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
);

--
-- Dumping data for table `mercutio2`.`pproctrans`
--

/*!40000 ALTER TABLE `pproctrans` DISABLE KEYS */;
/*!40000 ALTER TABLE `pproctrans` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pproctransfrom`
--

DROP TABLE IF EXISTS `pproctransfrom`;
CREATE TABLE `pproctransfrom` (
  `procid` int(11) NOT NULL default '0',
  `caseid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `refprocid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`procid`,`caseid`,`transid`,`refprocid`),
  KEY `pproctransfrom_idx1` (`procid`,`caseid`,`transid`,`refprocid`)
);

--
-- Dumping data for table `mercutio2`.`pproctransfrom`
--

/*!40000 ALTER TABLE `pproctransfrom` DISABLE KEYS */;
/*!40000 ALTER TABLE `pproctransfrom` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pproctranstxt`
--

DROP TABLE IF EXISTS `pproctranstxt`;
CREATE TABLE `pproctranstxt` (
  `modelid` int(11) NOT NULL default '0',
  `procid` int(11) NOT NULL default '0',
  `caseid` int(11) NOT NULL default '0',
  `transid` int(11) NOT NULL default '0',
  `msg` varchar(255) default NULL,
  PRIMARY KEY  (`modelid`,`procid`,`caseid`,`transid`)
);

--
-- Dumping data for table `mercutio2`.`pproctranstxt`
--

/*!40000 ALTER TABLE `pproctranstxt` DISABLE KEYS */;
/*!40000 ALTER TABLE `pproctranstxt` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`preferencestatus`
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
);

--
-- Dumping data for table `mercutio2`.`preferencestatus`
--

/*!40000 ALTER TABLE `preferencestatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `preferencestatus` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`proclog`
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
);

--
-- Dumping data for table `mercutio2`.`proclog`
--

/*!40000 ALTER TABLE `proclog` DISABLE KEYS */;
INSERT INTO `proclog` (`IDPROCLOG`,`PROCID`,`EXTERNSYSTEMID`,`IDMESSAGEINTERNE`,`WKGID`,`MESSAGETIME`,`TEMPSSTANDARD`,`CASEID`,`prestationID`,`statut`) VALUES 
 (4864,4,1,5058,1000993,'2005-01-03 15:48:27','0.2500000000',10,1016,1),
 (4865,4,1,5059,1000993,'2005-01-03 16:05:42','0.2500000000',10,1016,1),
 (4866,4,1,5060,1000993,'2005-01-03 16:07:56','0.2500000000',10,1016,1),
 (4867,4,1,5061,1000993,'2005-01-04 11:30:33','0.2500000000',10,1016,1),
 (4868,4,1,5062,1000993,'2005-01-04 15:28:24','0.2500000000',10,1016,1),
 (4869,4,1,5063,1000993,'2005-01-08 20:04:07','0.2500000000',10,1016,1),
 (4870,4,1,5064,1000993,'2005-01-05 11:44:00','0.2500000000',10,1016,1),
 (4871,4,1,5065,1000993,'2005-01-06 12:32:02','0.2500000000',10,1016,1),
 (4872,4,1,5066,1000993,'2005-01-12 22:51:08','0.2500000000',10,1016,1),
 (4873,4,1,5067,1000993,'2005-01-09 15:17:33','0.2500000000',10,1016,1),
 (4874,4,1,5068,1000993,'2005-01-13 13:21:03','0.2500000000',10,1016,1),
 (4875,4,1,5069,1000993,'2005-01-13 22:34:05','0.2500000000',10,1016,1),
 (4876,4,1,5070,1000993,'2005-01-10 10:37:24','0.2500000000',10,1016,1);
INSERT INTO `proclog` (`IDPROCLOG`,`PROCID`,`EXTERNSYSTEMID`,`IDMESSAGEINTERNE`,`WKGID`,`MESSAGETIME`,`TEMPSSTANDARD`,`CASEID`,`prestationID`,`statut`) VALUES 
 (4877,4,1,5071,1000993,'2005-01-10 15:22:02','0.2500000000',10,1016,1),
 (4878,4,1,5072,1000993,'2005-01-10 16:19:05','0.2500000000',10,1016,1),
 (4879,4,1,5073,1000993,'2005-01-11 14:48:58','0.2500000000',10,1016,1),
 (4880,4,1,5074,1000993,'2005-01-11 15:38:24','0.2500000000',10,1016,1),
 (4881,4,1,5075,1000993,'2005-01-12 10:08:49','0.2500000000',10,1016,1),
 (4882,4,1,5076,1000993,'2005-01-13 13:23:42','0.2500000000',10,1016,1),
 (4883,4,1,5077,1000993,'2005-01-19 21:24:04','0.2500000000',10,1016,1),
 (4884,4,1,5078,1000993,'2005-01-16 12:10:23','0.2500000000',10,1016,1),
 (4885,4,1,5079,1000993,'2005-01-16 15:58:36','0.2500000000',10,1016,1),
 (4886,4,1,5080,1000993,'2005-01-16 16:45:04','0.2500000000',10,1016,1),
 (4887,4,1,5081,1000993,'2005-01-16 17:13:34','0.2500000000',10,1016,1),
 (4888,4,1,5082,1000993,'2005-01-20 22:13:01','0.2500000000',10,1016,1),
 (4889,4,1,5083,1000993,'2005-01-17 14:15:44','0.2500000000',10,1016,1);
INSERT INTO `proclog` (`IDPROCLOG`,`PROCID`,`EXTERNSYSTEMID`,`IDMESSAGEINTERNE`,`WKGID`,`MESSAGETIME`,`TEMPSSTANDARD`,`CASEID`,`prestationID`,`statut`) VALUES 
 (4890,4,1,5084,1000993,'2005-01-17 14:24:30','0.2500000000',10,1016,1),
 (4891,4,1,5085,1000993,'2005-01-17 15:31:58','0.2500000000',10,1016,1),
 (4892,4,1,5086,1000993,'2005-01-17 15:31:58','0.2500000000',10,1016,1),
 (4893,4,1,5087,1000993,'2005-01-17 15:31:58','0.2500000000',10,1016,1),
 (4894,4,1,5088,1000993,'2005-01-17 15:31:58','0.2500000000',10,1016,1),
 (4895,4,1,5089,1000993,'2005-01-17 15:31:58','0.2500000000',10,1016,1),
 (4896,4,1,5090,1000993,'2005-01-17 15:31:58','0.2500000000',10,1016,1),
 (4897,4,1,5091,1000993,'2005-01-17 15:31:58','0.2500000000',10,1016,1),
 (4898,4,1,5092,1000993,'2005-01-17 15:31:58','0.2500000000',10,1016,1),
 (4899,4,1,5093,1000993,'2005-01-17 15:31:58','0.2500000000',10,1016,1),
 (4900,13,1,5129,1000993,'2006-01-17 15:31:58','0.2500000000',10,1016,1),
 (4901,13,1,5128,1000993,'2006-01-17 15:31:58','0.2500000000',10,1016,1),
 (4902,13,1,5127,1000993,'2006-01-17 15:31:58','0.2500000000',10,1016,1);
INSERT INTO `proclog` (`IDPROCLOG`,`PROCID`,`EXTERNSYSTEMID`,`IDMESSAGEINTERNE`,`WKGID`,`MESSAGETIME`,`TEMPSSTANDARD`,`CASEID`,`prestationID`,`statut`) VALUES 
 (4903,13,1,5126,1000993,'2006-01-17 15:31:58','0.2500000000',10,1016,1),
 (4904,13,1,5125,1000993,'2006-01-17 15:31:58','0.2500000000',10,1016,1),
 (4905,13,1,5124,1000993,'2006-01-17 15:31:58','0.2500000000',10,1016,1),
 (4906,13,1,5123,1000993,'2006-01-17 15:31:58','0.2500000000',10,1016,1),
 (4907,13,1,5122,1000993,'2006-01-17 15:31:58','0.2500000000',10,1016,1),
 (4908,13,1,5121,1000993,'2006-01-17 15:31:58','0.2500000000',10,1016,1),
 (4909,13,1,5120,1000993,'2006-01-17 14:24:30','0.2500000000',10,1016,1),
 (4910,13,1,5119,1000993,'2006-01-17 14:15:44','0.2500000000',10,1016,1),
 (4911,13,1,5118,1000993,'2006-01-20 22:13:01','0.2500000000',10,1016,1),
 (4912,13,1,5117,1000993,'2006-01-16 17:13:34','0.2500000000',10,1016,1),
 (4913,13,1,5116,1000993,'2006-01-16 16:45:04','0.2500000000',10,1016,1),
 (4914,13,1,5115,1000993,'2006-01-16 15:58:36','0.2500000000',10,1016,1),
 (4915,13,1,5114,1000993,'2006-01-16 12:10:23','0.2500000000',10,1016,1);
INSERT INTO `proclog` (`IDPROCLOG`,`PROCID`,`EXTERNSYSTEMID`,`IDMESSAGEINTERNE`,`WKGID`,`MESSAGETIME`,`TEMPSSTANDARD`,`CASEID`,`prestationID`,`statut`) VALUES 
 (4916,13,1,5113,1000993,'2006-01-19 21:24:04','0.2500000000',10,1016,1),
 (4917,13,1,5112,1000993,'2006-01-13 13:23:42','0.2500000000',10,1016,1),
 (4918,13,1,5111,1000993,'2006-01-12 10:08:49','0.2500000000',10,1016,1),
 (4919,13,1,5110,1000993,'2006-01-11 15:38:24','0.2500000000',10,1016,1),
 (4920,13,1,5109,1000993,'2006-01-11 14:48:58','0.2500000000',10,1016,1),
 (4921,13,1,5108,1000993,'2006-01-10 16:19:05','0.2500000000',10,1016,1),
 (4922,13,1,5107,1000993,'2006-01-10 15:22:02','0.2500000000',10,1016,1),
 (4923,13,1,5106,1000993,'2006-01-10 10:37:24','0.2500000000',10,1016,1),
 (4924,13,1,5105,1000993,'2006-01-13 22:34:05','0.2500000000',10,1016,1),
 (4925,13,1,5104,1000993,'2006-01-13 13:21:03','0.2500000000',10,1016,1),
 (4926,13,1,5103,1000993,'2006-01-09 15:17:33','0.2500000000',10,1016,1),
 (4927,13,1,5102,1000993,'2006-01-12 22:51:08','0.2500000000',10,1016,1),
 (4928,13,1,5101,1000993,'2006-01-06 12:32:02','0.2500000000',10,1016,1);
INSERT INTO `proclog` (`IDPROCLOG`,`PROCID`,`EXTERNSYSTEMID`,`IDMESSAGEINTERNE`,`WKGID`,`MESSAGETIME`,`TEMPSSTANDARD`,`CASEID`,`prestationID`,`statut`) VALUES 
 (4929,13,1,5100,1000993,'2006-01-05 11:44:00','0.2500000000',10,1016,1),
 (4930,13,1,5099,1000993,'2006-01-08 20:04:07','0.2500000000',10,1016,1),
 (4931,13,1,5098,1000993,'2006-01-04 15:28:24','0.2500000000',10,1016,1),
 (4932,13,1,5097,1000993,'2006-01-04 11:30:33','0.2500000000',10,1016,1),
 (4933,13,1,5096,1000993,'2006-01-03 16:07:56','0.2500000000',10,1016,1),
 (4934,13,1,5095,1000993,'2006-01-03 16:05:42','0.2500000000',10,1016,1),
 (4935,13,1,5094,1000993,'2006-01-03 15:48:27','0.2500000000',10,1016,1);
/*!40000 ALTER TABLE `proclog` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`prulesstatus`
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
);

--
-- Dumping data for table `mercutio2`.`prulesstatus`
--

/*!40000 ALTER TABLE `prulesstatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `prulesstatus` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pscrdatael`
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
);

--
-- Dumping data for table `mercutio2`.`pscrdatael`
--

/*!40000 ALTER TABLE `pscrdatael` DISABLE KEYS */;
/*!40000 ALTER TABLE `pscrdatael` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pscrdataellog`
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
);

--
-- Dumping data for table `mercutio2`.`pscrdataellog`
--

/*!40000 ALTER TABLE `pscrdataellog` DISABLE KEYS */;
/*!40000 ALTER TABLE `pscrdataellog` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pscrdatagroup`
--

DROP TABLE IF EXISTS `pscrdatagroup`;
CREATE TABLE `pscrdatagroup` (
  `gid` int(11) NOT NULL default '0',
  `groupname` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`gid`)
);

--
-- Dumping data for table `mercutio2`.`pscrdatagroup`
--

/*!40000 ALTER TABLE `pscrdatagroup` DISABLE KEYS */;
/*!40000 ALTER TABLE `pscrdatagroup` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pserverinfo`
--

DROP TABLE IF EXISTS `pserverinfo`;
CREATE TABLE `pserverinfo` (
  `infid` int(11) NOT NULL default '0',
  `inf` varchar(255) default NULL,
  PRIMARY KEY  (`infid`)
);

--
-- Dumping data for table `mercutio2`.`pserverinfo`
--

/*!40000 ALTER TABLE `pserverinfo` DISABLE KEYS */;
INSERT INTO `pserverinfo` (`infid`,`inf`) VALUES 
 (1,'1'),
 (2,'FR');
/*!40000 ALTER TABLE `pserverinfo` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pstatus`
--

DROP TABLE IF EXISTS `pstatus`;
CREATE TABLE `pstatus` (
  `statusid` int(11) NOT NULL default '0',
  `statusname` varchar(255) default NULL,
  PRIMARY KEY  (`statusid`)
);

--
-- Dumping data for table `mercutio2`.`pstatus`
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
-- Table structure for table `mercutio2`.`psystem`
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
);

--
-- Dumping data for table `mercutio2`.`psystem`
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
-- Table structure for table `mercutio2`.`psystemstatus`
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
);

--
-- Dumping data for table `mercutio2`.`psystemstatus`
--

/*!40000 ALTER TABLE `psystemstatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `psystemstatus` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`ptaskstatus`
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
);

--
-- Dumping data for table `mercutio2`.`ptaskstatus`
--

/*!40000 ALTER TABLE `ptaskstatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `ptaskstatus` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`ptrans`
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
);

--
-- Dumping data for table `mercutio2`.`ptrans`
--

/*!40000 ALTER TABLE `ptrans` DISABLE KEYS */;
/*!40000 ALTER TABLE `ptrans` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`puniverse`
--

DROP TABLE IF EXISTS `puniverse`;
CREATE TABLE `puniverse` (
  `guidSystem` varchar(50) NOT NULL default '',
  `guidPrestation` varchar(50) NOT NULL default '',
  `guidWorkgroup` varchar(50) NOT NULL default '',
  PRIMARY KEY  (`guidWorkgroup`,`guidPrestation`,`guidSystem`)
);

--
-- Dumping data for table `mercutio2`.`puniverse`
--

/*!40000 ALTER TABLE `puniverse` DISABLE KEYS */;
INSERT INTO `puniverse` (`guidSystem`,`guidPrestation`,`guidWorkgroup`) VALUES 
 ('_:[v0]-451384832-47598\0\0\0\0\0\0','_:[v0]64689102-28669\0\0\0\0\0','_:[v0]-640172442-62918\0\0\0\0\0\0');
/*!40000 ALTER TABLE `puniverse` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pworkgroup`
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
);

--
-- Dumping data for table `mercutio2`.`pworkgroup`
--

/*!40000 ALTER TABLE `pworkgroup` DISABLE KEYS */;
INSERT INTO `pworkgroup` (`wkgid`,`wkgparent`,`wkgname`,`wkgpercent`,`eptflag`,`mission`,`vocation`,`street`,`npalocality`,`municipality`,`country`,`email`,`creationdate`,`wkgtype`,`phone`,`daycost`) VALUES 
 (990,0,'LaSonnaz et environnement',0,0,'','','','','','','',NULL,0,'',''),
 (1000990,990,'LaSonnaz et environnement',100,0,'','','','','','','',NULL,1,'',''),
 (991,990,'LaSonnaz',0,0,'','','','','','','',NULL,0,'',''),
 (1000991,991,'LaSonnaz',100,0,'','','','','','','',NULL,1,'',''),
 (992,991,'Administration',0,0,'Execute les actes d\'administrations préfvus cadre légale','','','','','','',NULL,0,'',''),
 (1000992,992,'Administration',100,0,'Execute les actes d\'administrations préfvus cadre légale','','','','','','',NULL,1,'',''),
 (993,992,'Secrétariat',0,0,'Execute les tâches administratives ne demandant pas d\'expértise','','','','','','',NULL,0,'',''),
 (1000993,993,'Secrétariat',100,0,'Execute les tâches administratives ne demandant pas d\'expértise','','','','','','',NULL,1,'',''),
 (994,990,'Environnement',0,0,'','','','','','','',NULL,0,'','');
INSERT INTO `pworkgroup` (`wkgid`,`wkgparent`,`wkgname`,`wkgpercent`,`eptflag`,`mission`,`vocation`,`street`,`npalocality`,`municipality`,`country`,`email`,`creationdate`,`wkgtype`,`phone`,`daycost`) VALUES 
 (1000994,994,'Environnement',100,0,'','','','','','','',NULL,1,'',''),
 (995,994,'Administrés',0,0,'','','','','','','',NULL,0,'',''),
 (1000995,995,'Administrés',100,0,'','','','','','','',NULL,1,'',''),
 (996,990,'Acteurs Techniques',0,0,'','','','','','','',NULL,0,'',''),
 (1000996,996,'Acteurs Techniques',100,0,'','','','','','','',NULL,1,'',''),
 (997,996,'Autre Processus',0,0,'','','','','','','',NULL,0,'',''),
 (1000997,997,'Autre Processus',100,0,'','','','','','','',NULL,1,'',''),
 (998,996,'Automatisme',0,0,'','','','','','','',NULL,0,'',''),
 (1000998,998,'Automatisme',100,0,'','','','','','','',NULL,1,'','');
/*!40000 ALTER TABLE `pworkgroup` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pzsrvempmap`
--

DROP TABLE IF EXISTS `pzsrvempmap`;
CREATE TABLE `pzsrvempmap` (
  `grpid` int(11) NOT NULL default '0',
  `login` varchar(32) NOT NULL default '',
  UNIQUE KEY `pzsrvempmap_idx1` (`grpid`,`login`)
);

--
-- Dumping data for table `mercutio2`.`pzsrvempmap`
--

/*!40000 ALTER TABLE `pzsrvempmap` DISABLE KEYS */;
/*!40000 ALTER TABLE `pzsrvempmap` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pzsrvfiles`
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
);

--
-- Dumping data for table `mercutio2`.`pzsrvfiles`
--

/*!40000 ALTER TABLE `pzsrvfiles` DISABLE KEYS */;
/*!40000 ALTER TABLE `pzsrvfiles` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pzsrvgroup`
--

DROP TABLE IF EXISTS `pzsrvgroup`;
CREATE TABLE `pzsrvgroup` (
  `grpid` int(11) NOT NULL default '0',
  `grpparent` int(11) default NULL,
  `grpname` varchar(255) default NULL,
  PRIMARY KEY  (`grpid`),
  KEY `pzsrvgroup_idx1` (`grpparent`)
);

--
-- Dumping data for table `mercutio2`.`pzsrvgroup`
--

/*!40000 ALTER TABLE `pzsrvgroup` DISABLE KEYS */;
INSERT INTO `pzsrvgroup` (`grpid`,`grpparent`,`grpname`) VALUES 
 (1,0,'Entreprise');
/*!40000 ALTER TABLE `pzsrvgroup` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pzsrvlock`
--

DROP TABLE IF EXISTS `pzsrvlock`;
CREATE TABLE `pzsrvlock` (
  `dirname` varchar(250) NOT NULL default '',
  `filename` varchar(250) NOT NULL default '',
  `lockstate` int(11) NOT NULL default '0',
  `lockuser` int(11) NOT NULL default '0',
  `lockdate` datetime default NULL,
  PRIMARY KEY  (`dirname`,`filename`)
);

--
-- Dumping data for table `mercutio2`.`pzsrvlock`
--

/*!40000 ALTER TABLE `pzsrvlock` DISABLE KEYS */;
/*!40000 ALTER TABLE `pzsrvlock` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`pzsrvusermap`
--

DROP TABLE IF EXISTS `pzsrvusermap`;
CREATE TABLE `pzsrvusermap` (
  `dirname` varchar(255) NOT NULL default '',
  `login` varchar(32) NOT NULL default '',
  KEY `pzsrvusermap_idx1` (`dirname`,`login`)
);

--
-- Dumping data for table `mercutio2`.`pzsrvusermap`
--

/*!40000 ALTER TABLE `pzsrvusermap` DISABLE KEYS */;
/*!40000 ALTER TABLE `pzsrvusermap` ENABLE KEYS */;


--
-- Table structure for table `mercutio2`.`testtable`
--

DROP TABLE IF EXISTS `testtable`;
CREATE TABLE `testtable` (
  `formule` varchar(40) NOT NULL default '',
  PRIMARY KEY  (`formule`)
);

--
-- Dumping data for table `mercutio2`.`testtable`
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
