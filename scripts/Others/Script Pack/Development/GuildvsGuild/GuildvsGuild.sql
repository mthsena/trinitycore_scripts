DROP TABLE IF EXISTS `GuildvsGuild`;
CREATE TABLE `GuildvsGuild` (
  `id` int(10) unsigned NOT NULL,
  `win` int(10) unsigned NOT NULL DEFAULT '0',
  `total` bigint(20) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
