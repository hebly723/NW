# Host: localhost  (Version: 5.6.0-m4)
# Date: 2016-08-21 12:27:03
# Generator: MySQL-Front 5.3  (Build 4.214)

/*!40101 SET NAMES utf8 */;

#
# Structure for table "user"
#

DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `USER_ID` varchar(11) NOT NULL,
  `USER_NAME` varchar(30) DEFAULT NULL,
  `USER_PASSWORD` varchar(10) DEFAULT NULL,
  `USER_ROLE` char(1) DEFAULT NULL,
  PRIMARY KEY (`USER_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

#
# Data for table "user"
#

INSERT INTO `user` VALUES ('1123710501','领导1','lingdao1','2'),('1123710502','领导2','lingdao2','2'),('1133710501','刘导员','liudaoyuan','1'),('1133710502','李导员','lidaoyuan','1'),('1143710501','张钊晋','12345678','0'),('1143710502','流控和','12345678','0'),('1143710503','黑寡妇','66666666','0'),('1143710506','王志强','19951102','0');

#
# Structure for table "task"
#

DROP TABLE IF EXISTS `task`;
CREATE TABLE `task` (
  `TAS_ID` int(11) NOT NULL AUTO_INCREMENT,
  `TAS_CRE_ID` varchar(11) DEFAULT NULL,
  `TAS_CRE_DATE` datetime DEFAULT NULL,
  `TAS_DUE_DATE` datetime DEFAULT NULL,
  `TAS_DUE_ID` varchar(11) DEFAULT NULL,
  `TAS_TITLE` varchar(40) DEFAULT NULL,
  `TAS_DESC` varchar(300) DEFAULT NULL,
  `TAS_DOC_ID` varchar(36) DEFAULT NULL,
  `TAS_DOC1_NAME` varchar(30) DEFAULT NULL,
  `TAS_DOC2_NAME` varchar(30) DEFAULT NULL,
  `TAS_DOC3_NAME` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`TAS_ID`),
  KEY `fk_NO_SEN_ID_6` (`TAS_CRE_ID`),
  KEY `fk_NO_SEN_ID_7` (`TAS_DUE_ID`),
  CONSTRAINT `fk_NO_SEN_ID_6` FOREIGN KEY (`TAS_CRE_ID`) REFERENCES `user` (`USER_ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_NO_SEN_ID_7` FOREIGN KEY (`TAS_DUE_ID`) REFERENCES `user` (`USER_ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

#
# Data for table "task"
#


#
# Structure for table "message"
#

DROP TABLE IF EXISTS `message`;
CREATE TABLE `message` (
  `NOT_ID` int(11) NOT NULL AUTO_INCREMENT,
  `NOT_SEN_ID` varchar(11) DEFAULT NULL,
  `NOT_REC_ID` varchar(11) DEFAULT NULL,
  `NOT_DET` varchar(300) DEFAULT NULL,
  `NOT_STATUS` char(1) DEFAULT '0',
  `NOT_SEN_DATE` datetime DEFAULT NULL,
  PRIMARY KEY (`NOT_ID`),
  KEY `fk_NO_SEN_ID_1` (`NOT_SEN_ID`),
  KEY `fk_NO_SEN_ID_2` (`NOT_REC_ID`),
  CONSTRAINT `fk_NO_SEN_ID_1` FOREIGN KEY (`NOT_SEN_ID`) REFERENCES `user` (`USER_ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_NO_SEN_ID_2` FOREIGN KEY (`NOT_REC_ID`) REFERENCES `user` (`USER_ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8;

#
# Data for table "message"
#

INSERT INTO `message` VALUES (1,'1143710502','1143710501','你也早上好','1','1916-08-16 09:09:00'),(8,'1143710503','1143710501','你干嘛呢','0','1916-08-17 09:09:00'),(9,'1133710501','1143710501','表错误','0','1916-08-18 09:09:00'),(10,'1143710501','1143710502','成功了！！','1','1916-08-19 09:09:00'),(11,'1143710501','1143710502','早上好','0','1916-08-20 09:09:00'),(12,'1143710502','1143710501','哈哈哈','1','1999-06-06 09:09:00');

#
# Structure for table "checks"
#

DROP TABLE IF EXISTS `checks`;
CREATE TABLE `checks` (
  `CHE_ID` varchar(11) NOT NULL,
  `CHE_YEAR` int(6) DEFAULT NULL,
  `TAS_REC_NUM` int(11) DEFAULT NULL,
  `TAS_EXE_NUM` int(11) DEFAULT NULL,
  `APP_NUM` int(11) DEFAULT NULL,
  `APP_HAN_NUM` int(11) DEFAULT NULL,
  PRIMARY KEY (`CHE_ID`),
  CONSTRAINT `fk_NO_SEN_ID_8` FOREIGN KEY (`CHE_ID`) REFERENCES `user` (`USER_ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

#
# Data for table "checks"
#


#
# Structure for table "announcement"
#

DROP TABLE IF EXISTS `announcement`;
CREATE TABLE `announcement` (
  `AN_ID` int(11) NOT NULL AUTO_INCREMENT,
  `AN_CRE_ID` varchar(11) DEFAULT NULL,
  `AN_TITLE` varchar(40) DEFAULT NULL,
  `AN_DESC` varchar(140) DEFAULT NULL,
  `AN_CRE_DATE` datetime DEFAULT NULL,
  PRIMARY KEY (`AN_ID`),
  KEY `fk_NO_SEN_ID_9` (`AN_CRE_ID`),
  CONSTRAINT `fk_NO_SEN_ID_9` FOREIGN KEY (`AN_CRE_ID`) REFERENCES `user` (`USER_ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

#
# Data for table "announcement"
#
INSERT INTO `announcement` VALUES (1,'1133710501','植树节','今年春天大家一起去植树','1916-03-01 09:09:00');
INSERT INTO `announcement` VALUES (2,'1133710502','国庆节','放七天假，一块去玩！！！！','1916-09-28 09:05:00');
INSERT INTO `announcement` VALUES (3,'1133710501','圣诞节','平安夜，送苹果','1916-12-20 09:07:00');
INSERT INTO `announcement` VALUES (4,'1133710502','愚人节','玩玩','1916-04-1 09:05:00');
#
# Structure for table "activity"
#

DROP TABLE IF EXISTS `activity`;
CREATE TABLE `activity` (
  `AC_ID` int(11) NOT NULL AUTO_INCREMENT,
  `AC_CRE_ID` varchar(11) DEFAULT NULL,
  `AC_CRE_DATE` datetime DEFAULT NULL,
  `AC_DUE_DATE` datetime DEFAULT NULL,
  `AC_TITLE` varchar(40) DEFAULT NULL,
  `AC_DESC` varchar(300) DEFAULT NULL,
  `AC_DOC_ID` varchar(36) DEFAULT NULL,
  `AC_DOC1_NAME` varchar(30) DEFAULT NULL,
  `AC_DOC2_NAME` varchar(30) DEFAULT NULL,
  `AC_DOC3_NAME` varchar(30) DEFAULT NULL,
  `AC_SIG_NUM` int(11) DEFAULT '0',
  PRIMARY KEY (`AC_ID`),
  KEY `fk_NO_SEN_ID_3` (`AC_CRE_ID`),
  CONSTRAINT `fk_NO_SEN_ID_3` FOREIGN KEY (`AC_CRE_ID`) REFERENCES `user` (`USER_ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

#
# Data for table "activity"
#

INSERT INTO `activity` VALUES (4,'1133710501','1916-08-17 09:09:00','2016-08-19 09:09:00','测试活动','测试测试','0e1d8833-1bb8-4b98-a01e-821981f271f1','QQ截图20160712195042.png','文件2','文件三',2);

#
# Structure for table "sign"
#

DROP TABLE IF EXISTS `sign`;
CREATE TABLE `sign` (
  `SIG_ID` int(11) NOT NULL AUTO_INCREMENT,
  `AC_ID` int(11) NOT NULL,
  `SIG_PER_ID` varchar(11) DEFAULT NULL,
  `SIG_DATE` datetime DEFAULT NULL,
  `SIG_DOC_ID` varchar(36) DEFAULT NULL,
  `SIG_DOC1_NAME` varchar(30) DEFAULT NULL,
  `SIG_DOC2_NAME` varchar(30) DEFAULT NULL,
  `SIG_DOC3_NAME` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`SIG_ID`),
  KEY `fk_NO_SEN_ID_5` (`SIG_PER_ID`),
  KEY `fk_NO_SEN_ID_4` (`AC_ID`),
  CONSTRAINT `fk_NO_SEN_ID_4` FOREIGN KEY (`AC_ID`) REFERENCES `activity` (`AC_ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_NO_SEN_ID_5` FOREIGN KEY (`SIG_PER_ID`) REFERENCES `user` (`USER_ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

#
# Data for table "sign"
#

