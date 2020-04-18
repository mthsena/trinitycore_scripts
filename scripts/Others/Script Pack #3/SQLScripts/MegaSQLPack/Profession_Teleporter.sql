SET
@GOSSIP_MENU1       := 60000,
@GOSSIP_MENU2       := 60001,
@TEXT_ID             := 300005,

@ENTRY1              := 190001,
@ENTRY2              := 190002;

REPLACE INTO `creature_template` VALUES ('190001', '0', '0', '0', '0', '0', '30414', '0', '0', '0', 'Professions Teleporter', null, 'Directions', '60000', '80', '80', '0', '35', '35', '3', '1', '1.14286', '2.5', '0', '0', '0', '0', '0', '1', '0', '0', '1', '2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'SmartAI', '0', '3', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '2','', '1');
REPLACE INTO `creature_template` VALUES ('190002', '0', '0', '0', '0', '0', '30414', '0', '0', '0', 'Professions Teleporter', null, 'Directions', '60001', '80', '80', '0', '35', '35', '3', '1', '1.14286', '2.5', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'SmartAI', '0', '3', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '2', '', '1');

REPLACE INTO `npc_text` VALUES (@TEXT_ID, '$BChoose your profession!$B', null, '0', '0', '0', '6', '0', '0', '0', '0', null, null, '0', '0', '0', '0', '0', '0', '0', '0', null, null, '0', '0', '0', '0', '0', '0', '0', '0', null, null, '0', '0', '0', '0', '0', '0', '0', '0', null, null, '0', '0', '0', '0', '0', '0', '0', '0', null, null, '0', '0', '0', '0', '0', '0', '0', '0', null, null, '0', '0', '0', '0', '0', '0', '0', '0', null, null, '0', '0', '0', '0', '0', '0', '0', '0', '1');

REPLACE INTO gossip_menu (entry, text_id) VALUES
(@GOSSIP_MENU1, @TEXT_ID),
(@GOSSIP_MENU2, @TEXT_ID);

REPLACE INTO gossip_menu_option (menu_id, id, option_icon, option_text, option_id, npc_option_npcflag, action_menu_id, action_poi_id, box_coded, box_money, box_text) VALUES
(@GOSSIP_MENU1, 9, 0, "Namestie", 1, 1, @GOSSIP_MENU1, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU1, 4, 0, "Enchanting", 1, 1, @GOSSIP_MENU1, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU1, 5, 0, "Inscription", 1, 1, @GOSSIP_MENU1, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU1, 6, 0, "Jewelcrafting", 1, 1, @GOSSIP_MENU1, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU1, 7, 0, "Leatherworking", 1, 1, @GOSSIP_MENU1, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU1, 8, 0, "Tailoring", 1, 1, @GOSSIP_MENU1, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU1, 3, 0, "Engineering", 1, 1, @GOSSIP_MENU1, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU1, 2, 0, "Cooking", 1, 1, @GOSSIP_MENU1, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU1, 1, 0, "Blacksmithing", 1, 1, @GOSSIP_MENU1, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU1, 0, 0, "Alchemy", 1, 1, @GOSSIP_MENU1, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU2, 0, 0, "Alchemy", 1, 1, @GOSSIP_MENU2, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU2, 1, 0, "Blacksmithing", 1, 1, @GOSSIP_MENU2, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU2, 2, 0, "Cooking", 1, 1, @GOSSIP_MENU2, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU2, 3, 0, "Engineering", 1, 1, @GOSSIP_MENU2, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU2, 4, 0, "Enchanting", 1, 1, @GOSSIP_MENU2, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU2, 5, 0, "Inscription", 1, 1, @GOSSIP_MENU2, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU2, 6, 0, "Jewelcrafting", 1, 1, @GOSSIP_MENU2, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU2, 7, 0, "Leatherworking", 1, 1, @GOSSIP_MENU2, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU2, 8, 0, "Tailoring", 1, 1, @GOSSIP_MENU2, 0, 0, 0, "Are you sure?"),
(@GOSSIP_MENU2, 9, 0, "Namestie", 1, 1, @GOSSIP_MENU1, 0, 0, 0, "Are you sure?");


REPLACE INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment) VALUES
(15, @GOSSIP_MENU1, 0, 0, 0, 6, 0, 67, 0, 0, 0, 0, 0,'', "Alchemy"),
(15, @GOSSIP_MENU1, 1, 0, 0, 6, 0, 67, 0, 0, 0, 0, 0,'', "Blacksmithing"),
(15, @GOSSIP_MENU1, 2, 0, 0, 6, 0, 67, 0, 0, 0, 0, 0,'', "Cooking"),
(15, @GOSSIP_MENU1, 3, 0, 0, 6, 0, 67, 0, 0, 0, 0, 0,'', "Engineering"),
(15, @GOSSIP_MENU1, 4, 0, 0, 6, 0, 67, 0, 0, 0, 0, 0,'', "Enchanting"),
(15, @GOSSIP_MENU1, 5, 0, 0, 6, 0, 67, 0, 0, 0, 0, 0,'', "Inscription"),
(15, @GOSSIP_MENU1, 6, 0, 0, 6, 0, 67, 0, 0, 0, 0, 0,'', "Jewelcrafting"),
(15, @GOSSIP_MENU1, 7, 0, 0, 6, 0, 67, 0, 0, 0, 0, 0,'', "Leatherworking"),
(15, @GOSSIP_MENU1, 8, 0, 0, 6, 0, 67, 0, 0, 0, 0, 0,'', "Tailoring"),
(15, @GOSSIP_MENU2, 0, 0, 0, 6, 0, 496, 0, 0, 0, 0, 0,'', "Alchemy"),
(15, @GOSSIP_MENU2, 1, 0, 0, 6, 0, 496, 0, 0, 0, 0, 0,'', "Blacksmithing"),
(15, @GOSSIP_MENU2, 2, 0, 0, 6, 0, 496, 0, 0, 0, 0, 0,'', "Cooking"),
(15, @GOSSIP_MENU2, 3, 0, 0, 6, 0, 496, 0, 0, 0, 0, 0,'', "Engineering"),
(15, @GOSSIP_MENU2, 4, 0, 0, 6, 0, 496, 0, 0, 0, 0, 0,'', "Enchanting"),
(15, @GOSSIP_MENU2, 5, 0, 0, 6, 0, 496, 0, 0, 0, 0, 0,'', "Inscription"),
(15, @GOSSIP_MENU2, 6, 0, 0, 6, 0, 496, 0, 0, 0, 0, 0,'', "Jewelcrafting"),
(15, @GOSSIP_MENU2, 7, 0, 0, 6, 0, 496, 0, 0, 0, 0, 0,'', "Leatherworking"),
(15, @GOSSIP_MENU2, 8, 0, 0, 6, 0, 496, 0, 0, 0, 0, 0,'', "Tailoring"),
(14, @TEXT_ID, 0, 0, 0, 6, 0, 67, 0, 0, 0, 0, 0,'', "Profession"),
(14, @TEXT_ID, 1, 0, 0, 6, 0, 496, 0, 0, 0, 0, 0,'', "Profession"),
(15, @GOSSIP_MENU1, 9, 0, 0, 6, 0, 67, 0, 0, 0, 0, 0,'', "Namestie"),
(15, @GOSSIP_MENU2, 9, 0, 0, 6, 0, 496, 0, 0, 0, 0, 0,'', "Namestie");

REPLACE INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment) VALUES 
(@ENTRY1, 0, 8, 0, 62, 0, 100, 0, @GOSSIP_MENU1, 8, 0, 0, 62, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1799.66, -4557.08, 23.0063, 4.61495, "teleporter"),
(@ENTRY1, 0, 7, 0, 62, 0, 100, 0, @GOSSIP_MENU1, 7, 0, 0, 62, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1850.56, -4561.53, 24.9852, 5.12546, "teleporter"),
(@ENTRY1, 0, 6, 0, 62, 0, 100, 0, @GOSSIP_MENU1, 6, 0, 0, 62, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1896.6, -4324.84, 23.396, 2.7575, "teleporter"),
(@ENTRY1, 0, 5, 0, 62, 0, 100, 0, @GOSSIP_MENU1, 5, 0, 0, 62, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1840.64, -4471.6, 47.6865, 1.60295, "teleporter"),
(@ENTRY1, 0, 4, 0, 62, 0, 100, 0, @GOSSIP_MENU1, 4, 0, 0, 62, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1916.94, -4432.5, 24.7964, 3.37011, "teleporter"),
(@ENTRY1, 0, 3, 0, 62, 0, 100, 0, @GOSSIP_MENU1, 3, 0, 0, 62, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 2040.66, -4741.5, 29.3859, 4.45787, "teleporter"),
(@ENTRY1, 0, 2, 0, 62, 0, 100, 0, @GOSSIP_MENU1, 2, 0, 0, 62, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1774.08, -4487.64, 45.6483, 1.46157, "teleporter"),
(@ENTRY1, 0, 1, 0, 62, 0, 100, 0, @GOSSIP_MENU1, 1, 0, 0, 62, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 2059, -4829.45, 24.5775, 4.28902, "teleporter"),
(@ENTRY1, 0, 0, 0, 62, 0, 100, 0, @GOSSIP_MENU1, 0, 0, 0, 62, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1953.83, -4472.89, 25.9586, 6.22502, "teleporter"),
(@ENTRY2, 0, 8, 0, 62, 0, 100, 0, @GOSSIP_MENU2, 8, 0, 0, 62, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, -8943.3, 794.673, 90.9426, 1.64026 , "teleporter"),
(@ENTRY2, 0, 7, 0, 62, 0, 100, 0, @GOSSIP_MENU2, 7, 0, 0, 62, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, -8721.74, 473.066, 98.6133, 1.76591, "teleporter"),
(@ENTRY2, 0, 6, 0, 62, 0, 100, 0, @GOSSIP_MENU2, 6, 0, 0, 62, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, -8664.52, 431.722, 100.909, 3.81188, "teleporter"),
(@ENTRY2, 0, 5, 0, 62, 0, 100, 0, @GOSSIP_MENU2, 5, 0, 0, 62, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, -8855.72, 859.289, 99.6101, 3.26603, "teleporter"),
(@ENTRY2, 0, 4, 0, 62, 0, 100, 0, @GOSSIP_MENU2, 4, 0, 0, 62, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, -8855.05, 799.975, 96.3345, 1.91122, "teleporter"),
(@ENTRY2, 0, 3, 0, 62, 0, 100, 0, @GOSSIP_MENU2, 3, 0, 0, 62, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, -8350.34, 642.508, 95.2935, 0.685993, "teleporter"),
(@ENTRY2, 0, 2, 0, 62, 0, 100, 0, @GOSSIP_MENU2, 2, 0, 0, 62, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, -8612.35, 361.786, 99.6287, 5.46514, "teleporter"),
(@ENTRY2, 0, 1, 0, 62, 0, 100, 0, @GOSSIP_MENU2, 1, 0, 0, 62, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, -8424.08, 623.769, 95.5974, 3.85508, "teleporter"),
(@ENTRY2, 0, 0, 0, 62, 0, 100, 0, @GOSSIP_MENU2, 0, 0, 0, 62, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, -8985.07, 757.731, 98.3301, 3.89043, "teleporter"),
(@ENTRY1, 0, 9, 0, 62, 0, 100, 0, @GOSSIP_MENU1, 9, 0, 0, 62, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1629.36, -4373.39, 31.2564, 3.54839, "teleporter"),
(@ENTRY2, 0, 9, 0, 62, 0, 100, 0, @GOSSIP_MENU2, 9, 0, 0, 62, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, -8833.38, 628.628, 94.0066, 1.06535, "teleporter");

REPLACE INTO creature (guid, id, map, spawnMask, phaseMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, MovementType, npcflag, unit_flags, dynamicflags) VALUES
(15118039, @ENTRY2, 0, 1, 1, 0, 0, -8821.24, 629.276, 95.0752, 3.79853, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118029, @ENTRY1, 1, 1, 1, 0, 0, 1947.13, -4467.18, 26.111, 0.201015, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118030, @ENTRY1, 1, 1, 1, 0, 0, 2062.72, -4827.95, 24.5775, 4.39504, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118031, @ENTRY1, 1, 1, 1, 0, 0, 1781.69, -4485.41, 45.6483, 3.17766, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118032, @ENTRY1, 1, 1, 1, 0, 0, 2046.37, -4738.03, 29.3859, 4.5364, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118033, @ENTRY1, 1, 1, 1, 0, 0, 1920.59, -4428.35, 24.8743, 4.47753, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118034, @ENTRY1, 1, 1, 1, 0, 0, 1847.85, -4470.82, 47.6834, 3.61357, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118035, @ENTRY1, 1, 1, 1, 0, 0, 1900.29, -4322.06, 23.396, 3.21695, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118036, @ENTRY1, 1, 1, 1, 0, 0, 1850.78, -4553.21, 24.9852, 5.37678, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118037, @ENTRY1, 1, 1, 1, 0, 0, 1808.36, -4551.12, 23.0063, 4.96444, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118038, @ENTRY1, 1, 1, 1, 0, 0, 1582, -4397.73, 6.19751, 5.35872, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118040, @ENTRY2, 0, 1, 1, 0, 0, -8981.73, 756.245, 98.3301, 2.55133, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118041, @ENTRY2, 0, 1, 1, 0, 0, -8424.03, 632.014, 95.7757, 5.01354, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118042, @ENTRY2, 0, 1, 1, 0, 0, -8610.73, 357.527, 99.6241, 1.80518, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118043, @ENTRY2, 0, 1, 1, 0, 0, -8353.03, 649.004, 95.8509, 4.49911, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118044, @ENTRY2, 0, 1, 1, 0, 0, -8853.94, 793.865, 97.2772, 1.74236, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118045, @ENTRY2, 0, 1, 1, 0, 0, -8856.07, 852.924, 99.6101, 2.3157, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118046, @ENTRY2, 0, 1, 1, 0, 0, -8670.02, 435.984, 100.909, 5.312, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118047, @ENTRY2, 0, 1, 1, 0, 0, -8724.78, 471.346, 98.6133, 0.603521, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(15118048, @ENTRY2, 0, 1, 1, 0, 0, -8945.98, 792.96, 90.9426, 0.175492, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(400001, 14847, 1, 1, 1, 0, 1, 1585.16, -4396.49, 6.07318, 5.23651, 300, 0, 0, 1220, 0, 0, 0, 0, 0),
(400002, 14847, 0, 1, 1, 0, 1, -8823.42, 631.996, 94.8723, 3.77105, 300, 0, 0, 1220, 0, 0, 0, 0, 0);
