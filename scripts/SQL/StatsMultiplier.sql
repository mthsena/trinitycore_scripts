/*
** Criado por mthsena - www.mthsena.info
*/

SET @STATS := '0'; -- Valor a ser multiplicado os status.
SET @DMG   := '0'; -- Valor a ser multiplicado os damages.

-- ---------------------------------------------------------
UPDATE item_template SET stat_value1 = stat_value1 * @STATS;
UPDATE item_template SET stat_value2 = stat_value2 * @STATS;
UPDATE item_template SET stat_value3 = stat_value3 * @STATS;
UPDATE item_template SET stat_value4 = stat_value4 * @STATS;
UPDATE item_template SET stat_value5 = stat_value5 * @STATS;
UPDATE item_template SET stat_value6 = stat_value6 * @STATS;
UPDATE item_template SET stat_value7 = stat_value7 * @STATS;
UPDATE item_template SET stat_value8 = stat_value8 * @STATS;
UPDATE item_template SET stat_value9 = stat_value9 * @STATS;
UPDATE item_template SET stat_value10 = stat_value10 * @STATS;
UPDATE item_template SET dmg_min1 = dmg_min1 * @DMG;
UPDATE item_template SET dmg_max1 = dmg_max1 * @DMG;