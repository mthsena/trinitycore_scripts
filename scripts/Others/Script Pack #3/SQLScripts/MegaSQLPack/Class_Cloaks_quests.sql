SET
@ENTRY  := 190003,
@ID0    := 190000,
@ID1    := 190001,
@ID2    := 190002,
@ID3    := 190003,
@ID4    := 190004,
@ID5    := 190005,
@ID6    := 190006,
@ID7    := 190007,
@ID8    := 190008,
@ID9    := 190009;

REPLACE INTO `creature_template` VALUES 
 (@ENTRY, '0', '0', '0', '0', '0', '31011', '0', '0', '0', 'Special Class quests', '', null, '0', '80', '80', '0', '35', '35', '2', '1', '1.14286', '0.5', '0', '0', '0', '0', '0', '1', '0', '0', '0', '2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'SmartAI', '0', '3', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '', '1');

REPLACE INTO quest_template (Id, RequiredClasses, Flags, RewardChoiceItemId1, RewardChoiceItemCount1, Title, Objectives, RequiredItemId1, RequiredItemId2, RequiredItemId3, RequiredItemId4, RequiredItemId5, RequiredItemCount1, RequiredItemCount2, RequiredItemCount3, RequiredItemCount4, RequiredItemCount5) VALUES 
   (@ID0, 32, 32, 300060, 1, "|cffB40431Death Knight Cloak special quest", "Vitam Ta. Takze si sa rozhodol, ze chces plast pre svoju classu, vyborne! Mam pre teba velmi jednoduchu ulohu. Tvojou ulohou je doniest mi 9999x Fish Feast,9999x Gigantic Feast,9999x Small Feast a 9999x Dragonfin Filet a kedze vyroba takehoto plasta nieco stoji potrebuje aby si mi priniesol aj 10x Gold Bar.", 43000, 43015, 43478, 43480, 100000, 9999, 9999, 9999, 9999, 10),
   (@ID1, 1024, 1024, 300061, 1, "|cffFF8000Druid Cloak special quest", "Vitam Ta. Takze si sa rozhodol, ze chces plast pre svoju classu, vyborne! Mam pre teba velmi jednoduchu ulohu. Tvojou ulohou je doniest mi 9999x Fish Feast,9999x Gigantic Feast,9999x Small Feast a 9999x Dragonfin Filet a kedze vyroba takehoto plasta nieco stoji potrebuje aby si mi priniesol aj 10x Gold Bar.", 43000, 43015, 43478, 43480, 100000, 9999, 9999, 9999, 9999, 10),
   (@ID2, 4, 4, 300062, 1, "|cff088A08Hunter Cloak special quest", "Vitam Ta. Takze si sa rozhodol, ze chces plast pre svoju classu, vyborne! Mam pre teba velmi jednoduchu ulohu. Tvojou ulohou je doniest mi 9999x Fish Feast,9999x Gigantic Feast,9999x Small Feast a 9999x Dragonfin Filet a kedze vyroba takehoto plasta nieco stoji potrebuje aby si mi priniesol aj 10x Gold Bar.", 43000, 43015, 43478, 43480, 100000, 9999, 9999, 9999, 9999, 10),
   (@ID3, 128, 128, 300063, 1, "|cff2E9AFEMage Cloak special quest", "Vitam Ta. Takze si sa rozhodol, ze chces plast pre svoju classu, vyborne! Mam pre teba velmi jednoduchu ulohu. Tvojou ulohou je doniest mi 9999x Fish Feast,9999x Gigantic Feast,9999x Small Feast a 9999x Dragonfin Filet a kedze vyroba takehoto plasta nieco stoji potrebuje aby si mi priniesol aj 10x Gold Bar.", 43000, 43015, 43478, 43480, 100000, 9999, 9999, 9999, 9999, 10),
   (@ID4, 2, 2, 300064, 1, "|cffDF01D7Paladin Cloak special quest", "Vitam Ta. Takze si sa rozhodol, ze chces plast pre svoju classu, vyborne! Mam pre teba velmi jednoduchu ulohu. Tvojou ulohou je doniest mi 9999x Fish Feast,9999x Gigantic Feast,9999x Small Feast a 9999x Dragonfin Filet a kedze vyroba takehoto plasta nieco stoji potrebuje aby si mi priniesol aj 10x Gold Bar.", 43000, 43015, 43478, 43480, 100000, 9999, 9999, 9999, 9999, 10),
   (@ID5, 8, 8, 300065, 1, "|cffFFFFFFPriest Cloak special quest", "Vitam Ta. Takze si sa rozhodol, ze chces plast pre svoju classu, vyborne! Mam pre teba velmi jednoduchu ulohu. Tvojou ulohou je doniest mi 9999x Fish Feast,9999x Gigantic Feast,9999x Small Feast a 9999x Dragonfin Filet a kedze vyroba takehoto plasta nieco stoji potrebuje aby si mi priniesol aj 10x Gold Bar.", 43000, 43015, 43478, 43480, 100000, 9999, 9999, 9999, 9999, 10),
   (@ID6, 16, 16, 300066, 1, "|cffFFFF00Rogue Cloak special quest", "Vitam Ta. Takze si sa rozhodol, ze chces plast pre svoju classu, vyborne! Mam pre teba velmi jednoduchu ulohu. Tvojou ulohou je doniest mi 9999x Fish Feast,9999x Gigantic Feast,9999x Small Feast a 9999x Dragonfin Filet a kedze vyroba takehoto plasta nieco stoji potrebuje aby si mi priniesol aj 10x Gold Bar.", 43000, 43015, 43478, 43480, 100000, 9999, 9999, 9999, 9999, 10),
   (@ID7, 64, 64, 300067, 1, "|cff0404B4Shaman Cloak special quest", "Vitam Ta. Takze si sa rozhodol, ze chces plast pre svoju classu, vyborne! Mam pre teba velmi jednoduchu ulohu. Tvojou ulohou je doniest mi 9999x Fish Feast,9999x Gigantic Feast,9999x Small Feast a 9999x Dragonfin Filet a kedze vyroba takehoto plasta nieco stoji potrebuje aby si mi priniesol aj 10x Gold Bar.", 43000, 43015, 43478, 43480, 100000, 9999, 9999, 9999, 9999, 10),
   (@ID8, 256, 256, 300068, 1, "|cff7401DFWarlock Cloak special quest", "Vitam Ta. Takze si sa rozhodol, ze chces plast pre svoju classu, vyborne! Mam pre teba velmi jednoduchu ulohu. Tvojou ulohou je doniest mi 9999x Fish Feast,9999x Gigantic Feast,9999x Small Feast a 9999x Dragonfin Filet a kedze vyroba takehoto plasta nieco stoji potrebuje aby si mi priniesol aj 10x Gold Bar.", 43000, 43015, 43478, 43480, 100000, 9999, 9999, 9999, 9999, 10),
   (@ID9, 1, 1, 300069, 1, "|cff61380BWarrior Cloak special quest", "Vitam Ta. Takze si sa rozhodol, ze chces plast pre svoju classu, vyborne! Mam pre teba velmi jednoduchu ulohu. Tvojou ulohou je doniest mi 9999x Fish Feast,9999x Gigantic Feast,9999x Small Feast a 9999x Dragonfin Filet a kedze vyroba takehoto plasta nieco stoji potrebuje aby si mi priniesol aj 10x Gold Bar.", 43000, 43015, 43478, 43480, 100000, 9999, 9999, 9999, 9999, 10);

REPLACE INTO `creature_queststarter` VALUES
 (@ENTRY, @ID0),
 (@ENTRY, @ID1),
 (@ENTRY, @ID2),
 (@ENTRY, @ID3),
 (@ENTRY, @ID4),
 (@ENTRY, @ID5),
 (@ENTRY, @ID6),
 (@ENTRY, @ID7),
 (@ENTRY, @ID8),
 (@ENTRY, @ID9);

REPLACE INTO `creature_questender` VALUES
 (@ENTRY, @ID0),
 (@ENTRY, @ID1),
 (@ENTRY, @ID2),
 (@ENTRY, @ID3),
 (@ENTRY, @ID4),
 (@ENTRY, @ID5),
 (@ENTRY, @ID6),
 (@ENTRY, @ID7),
 (@ENTRY, @ID8),
 (@ENTRY, @ID9);

REPLACE INTO creature (guid, id, map, spawnMask, phaseMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, MovementType, npcflag, unit_flags, dynamicflags) VALUES 
   (15121488, @ENTRY, 0, 1, 1, 0, 0, -8825.6, 630.186, 94.081, 3.85155, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
   (15121487, @ENTRY, 1, 1, 1, 0, 0, 1605.02, -4400.83, 10.2867, 2.06596, 300, 0, 0, 5342, 0, 0, 0, 0, 0);