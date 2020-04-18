SET @NPC := '400002';  -- 200002[Free]        300003[PvE]      400002[PvP]
SET @VALUE := 1.4;

UPDATE item_template SET 
armor = armor * @VALUE,
stat_value1 = stat_value1 * @VALUE,
stat_value2 = stat_value2 * @VALUE,
stat_value3 = stat_value3 * @VALUE,
stat_value4 = stat_value4 * @VALUE,
stat_value5 = stat_value5 * @VALUE,
stat_value6 = stat_value6 * @VALUE,
stat_value7 = stat_value7 * @VALUE,
stat_value8 = stat_value8 * @VALUE,
stat_value9 = stat_value9 * @VALUE,
stat_value10 = stat_value10 * @VALUE 
WHERE entry IN(SELECT item FROM npc_vendor WHERE entry = @NPC) AND scriptname IN('Plate Offset','Mail Offset','Leather Offset','Cloth Offset');