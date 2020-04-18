DROP PROCEDURE IF EXISTS myproc;
DELIMITER //
CREATE PROCEDURE myproc()
BEGIN
  DECLARE a INT DEFAULT 9;
  WHILE a < 69 DO
    SET a = a + 1;
    SET @ENTRY = 80000 + a;
    SET @DESCR = CONCAT('Level ', a);
    REPLACE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `HealthModifier`, `ManaModifier`, `ArmorModifier`, `DamageModifier`, `ExperienceModifier`, `RacialLeader`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES(@ENTRY,'0','0','0','0','0','24978','0','0','0','Weapons',@DESCR,NULL,'0','80','80','0','35','0','1','1','1','0','0','0','0','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','7','1','1','1','1','1','1','0','0','0','0','0','','0');
    INSERT INTO npc_vendor SELECT @ENTRY, 0, entry, 0, 0, 2, 0 FROM item_template WHERE requiredlevel = a AND inventorytype IN (13,14,15,17,21,22,23,25,26,28);
  END WHILE;
END //

CALL myproc();
