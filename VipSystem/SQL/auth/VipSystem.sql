
SET FOREIGN_KEY_CHECKS = 0;

DELETE FROM `rbac_permissions` WHERE `id` BETWEEN '192' AND '199';
INSERT INTO `rbac_permissions` (`id`, `name`) VALUES 
('190','Rank: 4 Administrator'),
('191','Rank: 3 Gamemaster'),
('192','Rank: 2 Moderator'),
('193','Rank: 1 Vip'),
('194','Rank: 0 Player');

DELETE FROM `rbac_linked_permissions` WHERE `id` BETWEEN '192' AND '195' AND `linkedId` BETWEEN '192' AND '199';
UPDATE `rbac_linked_permissions` SET `id` = '190' WHERE `id` IN ('192', '196');
UPDATE `rbac_linked_permissions` SET `id` = '191' WHERE `id` IN ('193', '197');
UPDATE `rbac_linked_permissions` SET `id` = '192' WHERE `id` IN ('194', '198');
UPDATE `rbac_linked_permissions` SET `id` = '194' WHERE `id` IN ('195', '199');
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) VALUES 
('190','191'),
('191','192'),
('192','193'),
('193','194');

DELETE FROM `rbac_default_permissions`;
INSERT INTO `rbac_default_permissions` (`secId`, `permissionId`) VALUES 
('4','190'),
('3','191'),
('2','192'),
('1','193'),
('0','194');

ALTER TABLE `account_access` ADD COLUMN `vipTime` BIGINT(20) UNSIGNED DEFAULT 0 NOT NULL AFTER `RealmID`;

INSERT INTO `rbac_permissions` (`id`, `name`) VALUES ('1000', 'Command: .vipsystem');
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) VALUES ('190', '1000');

SET FOREIGN_KEY_CHECKS = 1;
