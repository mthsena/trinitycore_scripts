
SET @ITEM_ID = 42780;
DELETE FROM `creature_loot_template` WHERE item = @ITEM_ID;
DELETE FROM `disenchant_loot_template` WHERE item = @ITEM_ID;
DELETE FROM `fishing_loot_template` WHERE item = @ITEM_ID;
DELETE FROM `gameobject_loot_template` WHERE item = @ITEM_ID;
DELETE FROM `item_loot_template` WHERE item = @ITEM_ID;
DELETE FROM `mail_loot_template` WHERE item = @ITEM_ID;
DELETE FROM `milling_loot_template` WHERE item = @ITEM_ID;
DELETE FROM `pickpocketing_loot_template` WHERE item = @ITEM_ID;
DELETE FROM `prospecting_loot_template` WHERE item = @ITEM_ID;
DELETE FROM `reference_loot_template` WHERE item = @ITEM_ID;
DELETE FROM `skinning_loot_template` WHERE item = @ITEM_ID;
DELETE FROM `spell_loot_template` WHERE item = @ITEM_ID;
