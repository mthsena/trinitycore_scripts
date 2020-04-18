/* Goblin */
UPDATE `playercreateinfo_spell_custom` SET `racemask` = `racemask` + 256 WHERE `racemask` & 2;

-- ----------
-- ----------

/* Worgen */
UPDATE `playercreateinfo_spell_custom` SET `racemask` = `racemask` + 2048 WHERE `racemask` & 1;

-- ----------
-- ----------

/* All */
UPDATE `playercreateinfo_spell_custom` SET `racemask` = 4095 WHERE `racemask` = 0;