SET
@ENTRY  := 190004,
@ID     := 190010;
REPLACE INTO `creature_template` VALUES 
 (@ENTRY, '0', '0', '0', '0', '0', '31011', '0', '0', '0', 'Welcome Quester', '', null, '0', '80', '80', '0', '35', '35', '2', '1', '1.14286', '0.5', '0', '0', '0', '0', '0', '1', '0', '0', '0', '2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'SmartAI', '0', '3', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '', '1');
REPLACE INTO quest_template (Id, RewardChoiceItemId1, RewardChoiceItemCount1, Title, Objectives) VALUES 
   (@ID, 999999, 1, "|cff58FAF4WELCOME", "Vitam Ta. Takze si sa rozhodol, ze chces hrat an nasom serveri. Vyborne! Tento quest len odovzdaj a ako uvitanie od nas dostanes prenosneho Teleportera. Dufame, ze sa Ti bude u nas pacit.");
 REPLACE INTO `creature_queststarter` VALUES
 (@ENTRY, @ID);
REPLACE INTO `creature_questender` VALUES
 (@ENTRY, @ID);
REPLACE INTO creature (guid, id, map, spawnMask, phaseMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, MovementType, npcflag, unit_flags, dynamicflags) VALUE
   (15121656, 190004, 1, 1, 1, 0, 0, -611.809, -4244.23, 38.9562, 3.05946, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
   (15121657, 190004, 1, 1, 1, 0, 0, -2914.23, -261.105, 53.2086, 3.34024, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
   (15121658, 190004, 1, 1, 1, 0, 0, 10335.8, 828.057, 1326.29, 2.38637, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
   (15121659, 190004, 530, 1, 1, 0, 0, -3973.83, -13917.4, 99.4282, 0.44767, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
   (15121660, 190004, 530, 1, 1, 0, 0, 10354, -6363.58, 34.9047, 3.15741, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
   (15121661, 190004, 0, 1, 1, 0, 0, 1660.83, 1665.7, 120.719, 1.65421, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
   (15121662, 190004, 0, 1, 1, 0, 0, -8916.02, -120.186, 82.0557, 3.97086, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
   (15121663, 190004, 0, 1, 1, 0, 0, -6217.81, 334.406, 383.246, 3.31351, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
   (15121664, 190004, 0, 1, 1, 0, 0, -8844.87, 629.432, 94.8839, 0.382052, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
   (15121665, 190004, 1, 1, 1, 0, 0, 1602.82, -4401.24, 9.7374, 1.98458, 300, 0, 0, 5342, 0, 0, 0, 0, 0);
