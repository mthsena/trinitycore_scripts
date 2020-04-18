/*
  _____                        ____               
 |  ___| __ ___ _______ _ __  / ___|___  _ __ ___ 
 | |_ | '__/ _ \_  / _ \ '_ \| |   / _ \| '__/ _ \
 |  _|| | | (_) / /  __/ | | | |__| (_) | | |  __/
 |_|  |_|  \___/___\___|_| |_|\____\___/|_|  \___|
	 Lightning speed and strength
		 conjured directly from the depths of logic!   
			Infusion-WoW 2011 - 2012 (C)
<--------------------------------------------------------------------------->
 - Developer(s): N/A
 - Complete: N/A
 - ScriptName: '' 
 - Comment: N/A
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"

uint32 Spells[12][227]=
{
	{},	// 0	- ---------															
	// 1	- Warrior  //
	{7384,47436,47450,11578,47465,47502,34428,1715,2687,71,7386,355,72,47437,57823,694,2565,676,47520,20230,12678,47471,1161,871,2458,20252,47475,18499,1680,6552,47488,1719,23920,47440,3411,64382,55694,57755,42459,750,5246,3127,34093,33392,54197,750,196,197,198,199,200,201,202,264,5011,266,2567},		
	// 2	- Paladin -  //
	{3127,19746,19752,750,48942,48782,48932,20271,498,10308,1152,10278,48788,53408,48950,48936,31789,62124,54043,25780,1044,20217,48819,48801,48785,5502,20164,10326,1038,53407,48943,20165,48945,642,48947,20166,4987,48806,6940,48817,48934,48938,25898,32223,31884,54428,61411,53601,33388,33391,34093,33392,54197,750,196,197,198,199,200,201,202},									
	// 3	- Hunter - //
	{3043,3127,3045,3034,8737,1494,13163,48996,49001,49045,53338,5116,27044,883,2641,6991,982,1515,19883,20736,48990,2974,6197,1002,14327,5118,49056,53339,49048,19884,34074,781,14311,1462,19885,19880,13809,13161,5384,1543,19878,49067,3034,13159,19882,58434,49071,49052,19879,19263,19801,34026,34600,34477,61006,61847,53271,60192,62757,34093,33392,54197,15590,8737,196,197,200,201,202,264,266,5011,42459},
	// 4	- Rogue - //
	{3127,42459,48668,48638,1784,48657,921,1776,26669,51724,6774,11305,1766,48676,48659,1804,8647,48691,51722,48672,1725,26889,2836,1833,1842,8643,2094,1860,57993,48674,31224,5938,57934,51723,34093,33392,54197,196,198,201,1180,2567,264,5011,15590},
	// 5	- Priest - //
	{528,2053,48161,48126,48125,48066,586,48068,48127,48171,48168,10890,6064,988,48300,6346,48071,48135,48078,453,10955,10909,8129,48073,605,48072,48169,552,1706,48063,48162,48170,48074,48158,48120,34433,48113,32375,64843,64901,53023,34093,33392,54197},
	// 6	- Death Knight - //
	{3127,50842,49941,49930,47476,45529,3714,56222,48743,48263,49909,47528,45524,48792,57623,56815,47568,49895,50977,49576,49921,46584,49938,48707,48265,61999,42650,53428,53331,54447,53342,54446,53323,53344,70164,62158,33391,48778,51425,49924,34093,33392,54197,750,196,197,198,199,200,201,202},
	// 7	- Shaman - //
	{8737,49273,49238,10399,49231,58753,2484,49281,58582,49233,58790,58704,58643,49277,61657,8012,526,2645,57994,8143,49236,58796,58757,49276,57960,131,58745,6196,58734,58774,58739,58656,546,556,66842,51994,8177,58749,20608,36936,58804,4927,8512,6495,8170,66843,55459,66844,3738,2894,60043,51514,34093,33392,54197,8737,196,197,198,199,227,15590,49271},
	// 8	- Mage - //
	{42921,42842,42995,42833,27090,33717,42873,42846,12826,28271,61780,61721,28272,42917,43015,130,42926,43017,475,1953,42940,12051,43010,43020,43012,42859,2139,42931,42985,43008,45438,43024,43002,43046,42897,42914,66,58659,30449,42956,47610,61316,61024,55342,53142,7301,34093,33392,54197,201,196,227,1180},
	// 9	- Warlock - //
	{696,47811,47809,688,47813,50511,57946,47864,6215,47878,47855,697,47856,47857,5697,47884,47815,47889,47820,698,712,126,5138,5500,11719,132,60220,18647,61191,47823,691,47865,47891,47888,17928,47860,47825,1122,47867,18540,47893,47838,29858,58887,47836,61290,48018,48020,33388,33391,23161,34093,33392,54197,196,227,1180},
	// 10	- ---------
	{},
	// 11	- Druid - //
	{48378,48469,48461,48463,48441,53307,53308,5487,48560,6795,48480,53312,18960,5229,48443,50763,8983,8946,1066,48562,783,770,16857,18658,768,1082,16979,49376,5215,48477,49800,48465,48572,26995,48574,2782,50213,2893,33357,5209,48575,48447,48577,48579,5225,22842,49803,9634,20719,48467,29166,62600,22812,48470,48565,48566,33943,49802,48451,48568,33786,40120,62078,52610,50464,48570,34093,33392,54197,198,199,200,227},
};

void TeachSpells(Creature* creature, Player * plr, uint32 Class)
{
	for (int i = 0; i < 227; i++)
	{
		if (Spells[Class][i] == 0)
			break;

		plr->learnSpell(Spells[Class][i],false);
	}
	
	switch(Class)
	{
		case 1:
		{
			if(plr->HasSpell(12294))
			{
				plr->learnSpell(47486, false);
			}
			if(plr->HasSpell(20243))
			{
				plr->learnSpell(47498, false);
			}
			plr->UpdateSkillsToMaxSkillsForLevel();
			plr->SaveToDB();
		}break;
		
		case 2:
		{
			if(plr->HasSpell(20925))
			{
				plr->learnSpell(48952, false);
			}

			if(plr->HasSpell(12294))
			{
				plr->learnSpell(48827, false);
			}
			
			if(plr->HasSpell(20911))
			{
				plr->learnSpell(25899, false);
			}

			if(plr->HasSpell(20473))
			{
				plr->learnSpell(48825, false);
			}

			if(plr->GetTeam() == ALLIANCE)
			{
				plr->learnSpell(31801, false);
				plr->learnSpell(13819, false);
				plr->learnSpell(23214, false);
			}
			else
			{
				plr->learnSpell(53736, false);
				plr->learnSpell(34769, false);
				plr->learnSpell(34767, false);
			}
			plr->UpdateSkillsToMaxSkillsForLevel();
			plr->SaveToDB();
		}break;
		
		case 3:
		{
			if(plr->HasSpell(19386))
			{
				plr->learnSpell(49012, false);
			}
			
			if(plr->HasSpell(53301))
			{
				plr->learnSpell(60053, false);
			}
			
			if(plr->HasSpell(19306))
			{
				plr->learnSpell(48999, false);
			}
			
			if(plr->HasSpell(19434))
			{
				plr->learnSpell(49050, false);
			}
			plr->UpdateSkillsToMaxSkillsForLevel();
			plr->SaveToDB();
		}break;
		
		case 4:
		{
			if(plr->HasSpell(16511))
			{
				plr->learnSpell(48660, false);
			}
			
			if(plr->HasSpell(1329))
			{
				plr->learnSpell(48666, false);
			}
			plr->UpdateSkillsToMaxSkillsForLevel();
			plr->SaveToDB();
		}break;
		
		case 5:
		{
			if(plr->HasSpell(34914))
			{
				plr->learnSpell(48160, false);
			}
			
			if(plr->HasSpell(47540))
			{
				plr->learnSpell(53007, false);
			}
			
			if(plr->HasSpell(724))
			{
				plr->learnSpell(48087, false);
			}
			
			if(plr->HasSpell(19236))
			{
				plr->learnSpell(48173, false);
			}

			if(plr->HasSpell(34861))
			{
				plr->learnSpell(48089, false);
			}
			
			if(plr->HasSpell(15407))
			{
				plr->learnSpell(48156, false);
			}
			plr->UpdateSkillsToMaxSkillsForLevel();
			plr->SaveToDB();
		}break;
		
		case 6:
		{

			if(plr->HasSpell(55050))
			{
				plr->learnSpell(55262, false);
			}
			
			if(plr->HasSpell(49143))
			{
				plr->learnSpell(55268, false);
			}
			
			if(plr->HasSpell(49184))
			{
				plr->learnSpell(51411, false);
			}
			
			if(plr->HasSpell(55090))
			{
				plr->learnSpell(55271, false);
			}
			
			if(plr->HasSpell(49158))
			{
				plr->learnSpell(51328, false);
			}
			plr->UpdateSkillsToMaxSkillsForLevel();
			plr->SaveToDB();
		}break;
		
		case 7:
		{
			if(plr->GetTeam() == ALLIANCE)
			{
				plr->learnSpell(32182, false);
			}
			else
			{
				plr->learnSpell(2825, false);
			}

			if(plr->HasSpell(61295))
			{
				plr->learnSpell(61301, false);
			}

			if(plr->HasSpell(974))
			{
				plr->learnSpell(49284, false);
			}

			if(plr->HasSpell(30706))
			{
				plr->learnSpell(57722, false);
			}
			
			if(plr->HasSpell(51490))
			{
				plr->learnSpell(59159, false);
			}
			plr->UpdateSkillsToMaxSkillsForLevel();
			plr->SaveToDB();
		}break;
		
		case 8:
		{
			if(plr->GetTeam() == ALLIANCE)
			{
				plr->learnSpell(32271, false);
				plr->learnSpell(49359, false);
				plr->learnSpell(3565,  false);
				plr->learnSpell(33690, false);
				plr->learnSpell(3562,  false);
				plr->learnSpell(3561,  false);
				plr->learnSpell(11419, false);
				plr->learnSpell(32266, false);
				plr->learnSpell(11416, false);
				plr->learnSpell(33691, false);
				plr->learnSpell(49360, false);
			}
			else
			{
				plr->learnSpell(3567,  false);
				plr->learnSpell(35715, false);
				plr->learnSpell(3566,  false);
				plr->learnSpell(49358, false);
				plr->learnSpell(32272, false);
				plr->learnSpell(3563,  false);
				plr->learnSpell(11417, false);
				plr->learnSpell(35717, false);
				plr->learnSpell(32267, false);
				plr->learnSpell(49361, false);
				plr->learnSpell(11420, false);
				plr->learnSpell(11418, false);
			}
			
			if(plr->HasSpell(11366))
			{
				plr->learnSpell(42891, false);
			}
			
			if(plr->HasSpell(11426))
			{
				plr->learnSpell(43039, false);
			}
			
			if(plr->HasSpell(44457))
			{
				plr->learnSpell(55360, false);
			}
			
			if(plr->HasSpell(31661))
			{
				plr->learnSpell(42950, false);
			}
	
			if(plr->HasSpell(11113))
			{
				plr->learnSpell(42945, false);
			}
			
			if(plr->HasSpell(44425))
			{
				plr->learnSpell(44781, false);
			}
			plr->UpdateSkillsToMaxSkillsForLevel();
			plr->SaveToDB();
		}break;
		
		case 9:
		{
			if(plr->HasSpell(17877))
			{
				plr->learnSpell(47827, false);
			}
			
			if(plr->HasSpell(30283))
			{
				plr->learnSpell(47847, false);
			}

			if(plr->HasSpell(30108))
			{
				plr->learnSpell(47843, false);
			}
			
			if(plr->HasSpell(50796))
			{
				plr->learnSpell(59172, false);
			}
			
			if(plr->HasSpell(48181))
			{
				plr->learnSpell(59164, false);
			}
			
			if(plr->HasSpell(18220))
			{
				plr->learnSpell(59092, false);
			}
			plr->UpdateSkillsToMaxSkillsForLevel();
			plr->SaveToDB();
		}break;
		
		case 11:
		{
			if(plr->HasSpell(50516))
			{
				plr->learnSpell(61384, false);
			}
			
			if(plr->HasSpell(48505))
			{
				plr->learnSpell(53201, false);
			}
			
			if(plr->HasSpell(48438))
			{
				plr->learnSpell(53251, false);
			}

			if(plr->HasSpell(5570))
			{
				plr->learnSpell(48468, false);
			}
			plr->UpdateSkillsToMaxSkillsForLevel();
			plr->SaveToDB();
		}break;
	}

	creature->MonsterWhisper("I tought you all your spells", plr->GetGUID(), true);
	plr->CastSpell(plr,63680,true,NULL,NULL,plr->GetGUID());
	plr->CastSpell(plr,63624,true,NULL,NULL,plr->GetGUID());
	plr->SaveToDB();
}


void GlyphVendor(Creature * creature, Player * player, uint32 Class)
{
		WorldSession * m_session = player->GetSession();
		
		switch (player->getClass())
		{
					case CLASS_WARRIOR:
					{
						player->vendorLoader = 2500001;
						m_session->SendListCustomInventory(creature->GetGUID(),2500001);
						player->PlayerTalkClass->SendCloseGossip();
					}break;

					case CLASS_PALADIN:
					{
						player->vendorLoader = 2500002;
						m_session->SendListCustomInventory(creature->GetGUID(),2500002);
						player->PlayerTalkClass->SendCloseGossip();
					}break;

					case CLASS_HUNTER:
					{	
						player->vendorLoader = 2500003;
						m_session->SendListCustomInventory(creature->GetGUID(),2500003);
						player->PlayerTalkClass->SendCloseGossip();
					}break;

					case CLASS_ROGUE:
					{
						player->vendorLoader = 2500004;
						m_session->SendListCustomInventory(creature->GetGUID(),2500004);
						player->PlayerTalkClass->SendCloseGossip();
					}break;

					case CLASS_PRIEST:
					{
						player->vendorLoader = 2500005;
						m_session->SendListCustomInventory(creature->GetGUID(),2500005);
						player->PlayerTalkClass->SendCloseGossip();
					}break;

					case CLASS_DEATH_KNIGHT:
					{
						player->vendorLoader = 2500006;
						m_session->SendListCustomInventory(creature->GetGUID(),2500006);
						player->PlayerTalkClass->SendCloseGossip();
					}break;

					case CLASS_SHAMAN:
					{
						player->vendorLoader = 2500007;
						m_session->SendListCustomInventory(creature->GetGUID(),2500007);
						player->PlayerTalkClass->SendCloseGossip();
					}break;

					case CLASS_MAGE:
					{
						player->vendorLoader = 2500008;
						m_session->SendListCustomInventory(creature->GetGUID(),2500008);
						player->PlayerTalkClass->SendCloseGossip();
					}break;

					case CLASS_WARLOCK:
					{
						player->vendorLoader = 2500009;
						m_session->SendListCustomInventory(creature->GetGUID(),2500009);
						player->PlayerTalkClass->SendCloseGossip();
					}break;

					case CLASS_DRUID:
					{
						player->vendorLoader = 2500010;
						m_session->SendListCustomInventory(creature->GetGUID(),2500010);
						player->PlayerTalkClass->SendCloseGossip();
					}break;
				}
};

class npc_trainer : public CreatureScript
{
public:
    npc_trainer() : CreatureScript("npc_trainer") { }

    bool OnGossipHello(Player* player, Creature* creature)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "|cff00ff00|TInterface\\icons\\Spell_Arcane_Arcane04:24|t|r I want to Learn my class spells", GOSSIP_SENDER_MAIN, 100);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR,  "|cff00ff00|TInterface\\icons\\INV_Glyph_MajorMage:24|t|r I want to buy glyphs", GOSSIP_SENDER_MAIN, 101);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR,  "|cff00ff00|TInterface\\icons\\ABILITY_MAGE_WINTERSGRASP:24|t|r I want to reset my talents", GOSSIP_SENDER_MAIN, 102);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Goodbye", GOSSIP_SENDER_MAIN, 2222);
		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player * player, Creature * creature, uint32 uiSender, uint32 uiAction) 
	{
		player->PlayerTalkClass->ClearMenus();
		switch(uiAction)
		{

			// Close gossips
			case 2222:
            {
                player->PlayerTalkClass->SendCloseGossip();
            }break;	

			// Training
			case 100:
			{
				TeachSpells(creature,player,player->getClass());
				player->PlayerTalkClass->SendCloseGossip();
			}break;
	
			// GlyphVendor
			case 101:
			{
				GlyphVendor(creature,player,player->getClass());
				player->PlayerTalkClass->SendCloseGossip();
			}break;
			
			// Reset Talents
			case 102:
			{
				player->CLOSE_GOSSIP_MENU();
				player->SendTalentWipeConfirm(creature->GetGUID());
			}break;
	
		}
		return true;
	}
};
	
void AddSC_npc_trainer()
{
    new npc_trainer();
}