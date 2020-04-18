SET
@ENTRY1   := 800001,
@ENTRY2   := 800002,
@ENTRY3   := 800003,
@ENTRY4   := 800004,
@ENTRY5   := 800005,
@ENTRY6   := 800006,
@ENTRY7   := 800007,
@ENTRY8   := 800008,
@ENTRY300 := 300300;

REPLACE INTO `creature_template` VALUES 
 (@ENTRY300, '0', '0', '0', '0', '0', '23428', '0', '0', '0', 'Guild House quests', 'Guild House quests giver', null, '0', '80', '80', '0', '35', '35', '2', '1', '1.14286', '0.2', '0', '0', '0', '0', '0', '1', '0', '0', '0', '2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'SmartAI', '0', '3', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '', '1');

REPLACE INTO `quest_template` (`Id`,`Method`,`Level`,`MinLevel`,`PrevQuestId`,`NextQuestId`,`ExclusiveGroup`,`NextQuestIdChain`,`Flags`,`RewardChoiceItemId1`,`RewardChoiceItemCount1`,`Title`,`Objectives`,`Details`,`EndText`,`OfferRewardText`,`RequestItemsText`,`CompletedText`,`RequiredNpcOrGo1`,`RequiredNpcOrGo2`,`RequiredNpcOrGo3`,`RequiredNpcOrGo4`,`RequiredNpcOrGoCount1`,`RequiredNpcOrGoCount2`,`RequiredNpcOrGoCount3`,`RequiredNpcOrGoCount4`,`RequiredSourceItemId1`,`RequiredSourceItemId2`,`RequiredSourceItemId3`,`RequiredSourceItemId4`,`RequiredSourceItemCount1`,`RequiredSourceItemCount2`,`RequiredSourceItemCount3`,`RequiredSourceItemCount4`,`RequiredItemId1`,`RequiredItemId2`,`RequiredItemId3`,`RequiredItemId4`,`RequiredItemId5`,`RequiredItemId6`,`RequiredItemCount1`,`RequiredItemCount2`,`RequiredItemCount3`,`RequiredItemCount4`,`RequiredItemCount5`,`RequiredItemCount6`,`Unknown0`) VALUES 
 (@ENTRY1,'2','1','80','0', @ENTRY2,'0',@ENTRY2,'0','0','0','|cff298A08Guild House #1 HLAD','Vitam Ta. Mam pre teba velmi jednoduchu ulohu. Tvojou ulohou je doniest mi 9999x Fish Feast,9999x Gigantic Feast,9999x Small Feast a 9999x Dragonfin Filet.',NULL,NULL,NULL,NULL,NULL,'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','43000','43015','43478','43480','0','0','9999','9999','9999','9999','0','0','0'),
 (@ENTRY2,'2','1','80',@ENTRY1,@ENTRY3,'0',@ENTRY3,'64','0','0','|cff298A08Guild House #2 OBS','Vitam Ta opat bojovnik. Tvoja uloha je teraz mimoriadne narocna ziada si vsetky tvoje schopnosti rovnako ako aj schopnosti tvojich spoluhracov kedze to nemozes dat sam.Tvoja uloha tentokrat smeruje do prostredia The Obsidian Sanctum. Potrebujem od teba,aby si zabil Sarthariona 10x.Pokial uspejes,zvestuj mi spravy o tvojom uspechu a ja ti dam dalsi quest.', NULL,NULL,NULL,NULL,NULL,'28860','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),
 (@ENTRY3,'2','1','80',@ENTRY2,@ENTRY4,'0',@ENTRY4,'64','0','0','|cff298A08Guild House #3 NAXX','Vitam Ta opat bojovnik. Tvoja uloha je teraz mimoriadne narocna ziada si vsetky tvoje schopnosti rovnako ako aj schopnosti tvojich spoluhracov kedze to nemozes dat sam.Tvoja uloha tentokrat smeruje do prostredia Naxxramas. Potrebujem od teba,aby si zabil Kel\\\'Thuzada 10x a Sapphirona 10x.Pokial uspejes,zvestuj mi spravy o tvojom uspechu a ja ti dam dalsi quest. ',NULL,NULL,NULL,NULL,NULL,'15989','15990','0','0','10','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),
 (@ENTRY4,'2','1','80',@ENTRY3,@ENTRY5,'0',@ENTRY5,'64','0','0','|cff298A08Guild House #4 ULD','Vitam Ta opat bojovnik. Tvoja uloha je teraz mimoriadne narocna ziada si vsetky tvoje schopnosti rovnako ako aj schopnosti tvojich spoluhracov kedze to nemozes dat sam.Tvoja uloha tentokrat smeruje do prostredia Ulduar. Potrebujem od teba,aby si zabil Flame Leviathana 10x,Yogg-Sarona 10x a Algalona 10x.Pokial uspejes,zvestuj mi spravy o tvojom uspechu a ja ti dam dalsi quest.',NULL,NULL,NULL,NULL,NULL,'33113','33288','32871','0','10','10','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),
 (@ENTRY5,'2','1','80',@ENTRY4,@ENTRY6,'0',@ENTRY6,'64','0','0','|cff298A08Guild House #5 TOC','Vitam Ta opat bojovnik. Tvoja uloha je teraz mimoriadne narocna ziada si vsetky tvoje schopnosti rovnako ako aj schopnosti tvojich spoluhracov kedze to nemozes dat sam.Tvoja uloha tentokrat smeruje do prostredia Trial of the Crusader. Potrebujem od teba,aby si zabil Lorda Jaraxxa 10x,Obidve Valkyrie 10x a Anub\\\'araka 10x.Pokial uspejes,zvestuj mi spravy o tvojom uspechu a ja ti dam dalsi quest.',NULL,NULL,NULL,NULL,NULL,'34780','34497','34496','34564','10','10','10','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),
 (@ENTRY6,'2','1','80',@ENTRY5,@ENTRY7,'0',@ENTRY7,'64','0','0','|cff298A08Guild House #6 ICC','Vitam Ta opat bojovnik. Tvoja uloha je teraz mimoriadne narocna ziada si vsetky tvoje schopnosti rovnako ako aj schopnosti tvojich spoluhracov kedze to nemozes dat sam.Tvoja uloha tentokrat smeruje do prostredia Icecrown Citadel. Potrebujem od teba,aby si zabil Professora Putricida 10x,Blood Queenu Lana\\\'thel 10x,Sindragosu 10x a Lich Kinga 10x. Pokial uspejes,zvestuj mi spravy o tvojom uspechu a ja ti dam dalsi quest.',NULL,NULL,NULL,NULL,NULL,'36678','37955','36853','36597','10','10','10','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'),
 (@ENTRY7,'2','1','80',@ENTRY6,@ENTRY8,'0',@ENTRY8,'64','0','0','|cff298A08Guild House #7 POPLATOK','Vitam Ta. Tentokrat bude vsetko zavisiet len od teba. Pokial si dobry ekonom a nemas problemy sporit,nebudes mat problem. Kedze naklady na GH su obrovske potrebujem aby si mi priniesol 1000x Zlatu tehlicku. Tehlicku mozes kupit u vendora v OG alebo SW.', NULL,NULL,NULL,NULL,NULL,'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','100000','0','0','0','0','0','1000','0','0','0','0','0','0'),
 (@ENTRY8,'2','1','80',@ENTRY7,'0','0','0','0','200000','1','|cff298A08Guild House #8 POVOLENIE','Vitam Ta. ZVLADOL SI TO.Po narocnych hodinach,utrapach a mozno aj hadkam si to konecne dokazal a tak mas pravo na vlastny GH.Povolenie,ktore dostanes,ukaz akemukolvek GM a ten nasledne kontaktuje Administratora,ktory ti postavi GH\',',NULL,NULL,NULL,NULL,NULL,'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0');

REPLACE INTO `creature_queststarter` VALUES
 (@ENTRY300, @ENTRY1),
 (@ENTRY300, @ENTRY2),
 (@ENTRY300, @ENTRY3),
 (@ENTRY300, @ENTRY4),
 (@ENTRY300, @ENTRY5),
 (@ENTRY300, @ENTRY6),
 (@ENTRY300, @ENTRY7),
 (@ENTRY300, @ENTRY8);
REPLACE INTO `creature_questender` VALUES
 (@ENTRY300, @ENTRY1),
 (@ENTRY300, @ENTRY2),
 (@ENTRY300, @ENTRY3),
 (@ENTRY300, @ENTRY4),
 (@ENTRY300, @ENTRY5),
 (@ENTRY300, @ENTRY6),
 (@ENTRY300, @ENTRY7),
 (@ENTRY300, @ENTRY8);

REPLACE INTO `creature` VALUES
 ('15120327', @ENTRY300, '1', '1', '1', '0', '0', '1593.48', '-4394.13', '8.21305', '5.31632', '300', '0', '0', '5342', '0', '0', '0', '0', '0'),
 ('15120328', @ENTRY300, '0', '1', '1', '0', '0', '-8850.27', '634.797', '98.2182', '0.287801', '300', '0', '0', '5342', '0', '0', '0', '0', '0');