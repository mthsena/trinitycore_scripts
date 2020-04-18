DELETE FROM creature_template WHERE entry >= 500000 AND entry <= 500144;
DELETE FROM npc_vendor WHERE entry >= 500000 AND entry <= 500144;
DELETE FROM npc_trainer WHERE entry=500144;
DELETE FROM creature WHERE guid >= 500000 AND guid <= 500144;