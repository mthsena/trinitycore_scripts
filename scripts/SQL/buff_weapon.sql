SET @NPC := '150001'; --   200000[Free]        300000[PvE]       400000[PvP]           150000 | 150001 [V.I.P]
SET @VALUE := 1.6;

UPDATE item_template SET 
armor = armor * @VALUE,
dmg_min1 = dmg_min1 * @VALUE,
dmg_max1 = dmg_max1 * @VALUE,
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
WHERE entry IN(SELECT item FROM npc_vendor WHERE entry = @NPC) AND scriptname IN('Mace Spell','Off-Hand','Shield','Sword One-Hand','Sword Two-Hand','Axe One-Hand','Axe Two-Hand','Mace One-Hand','Mace Two-Hand','Dagger Damage','Staff Damage','Bow','Crossbow','Gun','Wand','Polearm','Staff Healing','Dagger Spell','Thrown','Sword Main-Hand','Sword Off-Hand','Fist Main-Hand','Fist Off-Hand');