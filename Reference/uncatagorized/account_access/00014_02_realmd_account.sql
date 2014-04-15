ALTER TABLE realmd_db_version CHANGE COLUMN required_00014_01_realmd_account_access required_00015_01_realmd_account BIT;

ALTER TABLE `account` DROP `gmlevel`;