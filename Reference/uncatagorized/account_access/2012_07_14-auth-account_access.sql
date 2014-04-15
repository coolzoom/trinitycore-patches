-- Table structure for `account_access`
DROP TABLE IF EXISTS `account_access`;
CREATE TABLE `account_access` (
  `id` bigint(20) unsigned NOT NULL,
  `gmlevel` tinyint(3) unsigned NOT NULL,
  `RealmID` int(11) NOT NULL,
  PRIMARY KEY (`id`,`RealmID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;
-- export current gm account to the new table
-- RealmID -1 = all realms
INSERT INTO `account_access` (id, gmlevel, RealmID)
SELECT `id`, `gmlevel`, -1 FROM `account` WHERE `gmlevel` > 0;
-- Remove the gmlevel field from account
ALTER TABLE account DROP COLUMN `gmlevel`;

-- command table
UPDATE command 
SET help = 'Syntax: .account set gmlevel [$account] #level [#realmid]\r\n\r\nSet the security level for targeted player (can\'t be used at self) or for account $name to a level of #level on the realm #realmID.\r\n\r\n#level may range from 0 to 3.\r\n\r\n#reamID may be -1 for all realms.'
WHERE name = 'account set gmlevel';

INSERT INTO mangos_string VALUES 
(11001, 'You have not chosen -1 or the current realmID that you are on.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
