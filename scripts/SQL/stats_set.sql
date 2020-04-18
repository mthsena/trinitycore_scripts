-- Clean Spells
UPDATE item_template SET spellid_1='0', spelltrigger_1='0', spellid_2='0', spelltrigger_2='0', spellid_3='0', spelltrigger_3='0', spellid_4='0', spelltrigger_4='0', spellid_5='0', spelltrigger_5='0' WHERE entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001'));

-- Offsets
UPDATE `item_template` SET `spellid_1`='12300', `spelltrigger_1`='1' WHERE `inventorytype`='8' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200002','300003','400002'));
UPDATE `item_template` SET `spellid_1`='12299', `spelltrigger_1`='1' WHERE `inventorytype`='9' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200002','300003','400002'));
UPDATE `item_template` SET `spellid_1`='28996', `spelltrigger_1`='1' WHERE `inventorytype`='6' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200002','300003','400002'));

-- Death Knight
/*Helm*/    UPDATE `item_template` SET `spellid_5`='70652', `spelltrigger_5`='1' WHERE `inventorytype`='1' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 32;
/*Shoulder*/UPDATE `item_template` SET `spellid_5`='67119', `spelltrigger_5`='1' WHERE `inventorytype`='3' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 32;
/*Chest*/   UPDATE `item_template` SET `spellid_5`='64962', `spelltrigger_5`='1' WHERE `inventorytype` IN ('5','20') AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 32;
/*Legs*/    UPDATE `item_template` SET `spellid_5`='67120', `spelltrigger_5`='1' WHERE `inventorytype`='7' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 32;
/*Gloves*/  UPDATE `item_template` SET `spellid_5`='64735', `spelltrigger_5`='1' WHERE `inventorytype`='10' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 32;

-- Druid
/*Helm*/    UPDATE `item_template` SET `spellid_5`='37327', `spelltrigger_5`='1' WHERE `inventorytype`='1' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 1024;
/*Shoulder*/UPDATE `item_template` SET `spellid_5`='64742', `spelltrigger_5`='1' WHERE `inventorytype`='3' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 1024;
/*Chest*/   UPDATE `item_template` SET `spellid_5`='67128', `spelltrigger_5`='1' WHERE `inventorytype` IN ('5','20') AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 1024;
/*Legs*/    UPDATE `item_template` SET `spellid_5`='64818', `spelltrigger_5`='1' WHERE `inventorytype`='7' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 1024;
/*Gloves*/  UPDATE `item_template` SET `spellid_5`='64824', `spelltrigger_5`='1' WHERE `inventorytype`='10' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 1024;

-- Hunter
/*Helm*/    UPDATE `item_template` SET `spellid_5`='23578', `spelltrigger_5`='1' WHERE `inventorytype`='1' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 4;
/*Shoulder*/UPDATE `item_template` SET `spellid_5`='67150', `spelltrigger_5`='1' WHERE `inventorytype`='3' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 4;
/*Chest*/   UPDATE `item_template` SET `spellid_5`='60143', `spelltrigger_5`='1' WHERE `inventorytype` IN ('5','20') AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 4;
/*Legs*/    UPDATE `item_template` SET `spellid_5`='70727', `spelltrigger_5`='1' WHERE `inventorytype`='7' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 4;
/*Gloves*/  UPDATE `item_template` SET `spellid_5`='64854', `spelltrigger_5`='1' WHERE `inventorytype`='10' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 4;

-- Mage
/*Helm*/    UPDATE `item_template` SET `spellid_5`='37438', `spelltrigger_5`='1' WHERE `inventorytype`='1' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 128;
/*Shoulder*/UPDATE `item_template` SET `spellid_5`='64185', `spelltrigger_5`='1' WHERE `inventorytype`='3' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 128;
/*Chest*/   UPDATE `item_template` SET `spellid_5`='22007', `spelltrigger_5`='1' WHERE `inventorytype` IN ('5','20') AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 128;
/*Legs*/    UPDATE `item_template` SET `spellid_5`='67164', `spelltrigger_5`='1' WHERE `inventorytype`='7' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 128;
/*Gloves*/  UPDATE `item_template` SET `spellid_5`='64867', `spelltrigger_5`='1' WHERE `inventorytype`='10' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 128;

-- Paladin
/*Helm*/    UPDATE `item_template` SET `spellid_5`='70765', `spelltrigger_5`='1' WHERE `inventorytype`='1' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 2;
/*Shoulder*/UPDATE `item_template` SET `spellid_5`='64881', `spelltrigger_5`='1' WHERE `inventorytype`='3' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 2;
/*Chest*/   UPDATE `item_template` SET `spellid_5`='67186', `spelltrigger_5`='1' WHERE `inventorytype` IN ('5','20') AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 2;
/*Legs*/    UPDATE `item_template` SET `spellid_5`='64878', `spelltrigger_5`='1' WHERE `inventorytype`='7' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 2;
/*Gloves*/  UPDATE `item_template` SET `spellid_5`='23564', `spelltrigger_5`='1' WHERE `inventorytype`='10' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 2;

-- Priest
/*Helm*/    UPDATE `item_template` SET `spellid_5`='70798', `spelltrigger_5`='1' WHERE `inventorytype`='1' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 16;
/*Shoulder*/UPDATE `item_template` SET `spellid_5`='38412', `spelltrigger_5`='1' WHERE `inventorytype`='3' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 16;
/*Chest*/   UPDATE `item_template` SET `spellid_5`='70801', `spelltrigger_5`='1' WHERE `inventorytype` IN ('5','20') AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 16;
/*Legs*/    UPDATE `item_template` SET `spellid_5`='64912', `spelltrigger_5`='1' WHERE `inventorytype`='7' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 16;
/*Gloves*/  UPDATE `item_template` SET `spellid_5`='67193', `spelltrigger_5`='1' WHERE `inventorytype`='10' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 16;

-- Rogue
/*Helm*/    UPDATE `item_template` SET `spellid_5`='67211', `spelltrigger_5`='1' WHERE `inventorytype`='1' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 8;
/*Shoulder*/UPDATE `item_template` SET `spellid_5`='64915', `spelltrigger_5`='1' WHERE `inventorytype`='3' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 8;
/*Chest*/   UPDATE `item_template` SET `spellid_5`='70803', `spelltrigger_5`='1' WHERE `inventorytype` IN ('5','20') AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 8;
/*Legs*/    UPDATE `item_template` SET `spellid_5`='21975', `spelltrigger_5`='1' WHERE `inventorytype`='7' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 8;
/*Gloves*/  UPDATE `item_template` SET `spellid_5`='21881', `spelltrigger_5`='1' WHERE `inventorytype`='10' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 8;

-- Shaman
/*Helm*/    UPDATE `item_template` SET `spellid_5`='67227', `spelltrigger_5`='1' WHERE `inventorytype`='1' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 64;
/*Shoulder*/UPDATE `item_template` SET `spellid_5`='67221', `spelltrigger_5`='1' WHERE `inventorytype`='3' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 64;
/*Chest*/   UPDATE `item_template` SET `spellid_5`='67225', `spelltrigger_5`='1' WHERE `inventorytype` IN ('5','20') AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 64;
/*Legs*/    UPDATE `item_template` SET `spellid_5`='64921', `spelltrigger_5`='1' WHERE `inventorytype`='7' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 64;
/*Gloves*/  UPDATE `item_template` SET `spellid_5`='64928', `spelltrigger_5`='1' WHERE `inventorytype`='10' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 64;

-- Warlock
/*Helm*/    UPDATE `item_template` SET `spellid_5`='67230', `spelltrigger_5`='1' WHERE `inventorytype`='1' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 256;
/*Shoulder*/UPDATE `item_template` SET `spellid_5`='64931', `spelltrigger_5`='1' WHERE `inventorytype`='3' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 256;
/*Chest*/   UPDATE `item_template` SET `spellid_5`='67231', `spelltrigger_5`='1' WHERE `inventorytype` IN ('5','20') AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 256;
/*Legs*/    UPDATE `item_template` SET `spellid_5`='37381', `spelltrigger_5`='1' WHERE `inventorytype`='7' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 256;
/*Gloves*/  UPDATE `item_template` SET `spellid_5`='37380', `spelltrigger_5`='1' WHERE `inventorytype`='10' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 256;

-- Warrior
/*Helm*/    UPDATE `item_template` SET `spellid_5`='67234', `spelltrigger_5`='1' WHERE `inventorytype`='1' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 1;
/*Shoulder*/UPDATE `item_template` SET `spellid_5`='21890', `spelltrigger_5`='1' WHERE `inventorytype`='3' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 1;
/*Chest*/   UPDATE `item_template` SET `spellid_5`='21838', `spelltrigger_5`='1' WHERE `inventorytype` IN ('5','20') AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 1;
/*Legs*/    UPDATE `item_template` SET `spellid_5`='37522', `spelltrigger_5`='1' WHERE `inventorytype`='7' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 1;
/*Gloves*/  UPDATE `item_template` SET `spellid_5`='64933', `spelltrigger_5`='1' WHERE `inventorytype`='10' AND entry IN (SELECT item FROM npc_vendor WHERE entry IN ('200001','300001','300002','400001','150000','150001')) AND allowableclass = 1;