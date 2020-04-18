/*
The Mechanical Alterac Valley
Name: Vehicle Spawning Npc

Author: Nexus
Alliance Version
Created for: UnforgivenWoW
*/

#include "ScriptPCH.h"
#include "ScriptedGossip.h"

class npc_vehiclespawner : public CreatureScript
{
public:
	npc_vehiclespawner() : CreatureScript("npc_vehiclespawner") { }

	bool OnGossipHello(Player * player, Creature * creature)
	{
		if (player->isInCombat())
		{
			player->PlayerTalkClass->SendCloseGossip();
			creature->MonsterSay("You are in combat!", LANG_UNIVERSAL, NULL);
			return true;
		}
		if (player->HasAura(57724))
		{
			player->PlayerTalkClass->SendCloseGossip();
			creature->MonsterSay("You have already spawned a vehicle, you need to wait till your not sated anymore.", LANG_UNIVERSAL, NULL);
			return true;
		}

		creature->MonsterSay("Welcome my lord, please choose the desired vehicle that suits you the best!", LANG_UNIVERSAL, NULL);

		player->ADD_GOSSIP_ITEM(10, "WARRIORS" 	 		 , GOSSIP_SENDER_MAIN, 100);
		player->ADD_GOSSIP_ITEM(10, "PALADINS" 	 	 	 , GOSSIP_SENDER_MAIN, 200);
		player->ADD_GOSSIP_ITEM(10, "HUNTERS"               	 , GOSSIP_SENDER_MAIN, 300);
		player->ADD_GOSSIP_ITEM(10, "ROGUES"               	 , GOSSIP_SENDER_MAIN, 400);
		player->ADD_GOSSIP_ITEM(10, "PRIESTS"               	 , GOSSIP_SENDER_MAIN, 500);
		player->ADD_GOSSIP_ITEM(10, "DEATH KNIGHTS"              , GOSSIP_SENDER_MAIN, 600);
		player->ADD_GOSSIP_ITEM(10, "SHAMANS"               	 , GOSSIP_SENDER_MAIN, 700);
		player->ADD_GOSSIP_ITEM(10, "MAGES"               	 , GOSSIP_SENDER_MAIN, 800);
		player->ADD_GOSSIP_ITEM(10, "WARLOCKS"               	 , GOSSIP_SENDER_MAIN, 900);
		player->ADD_GOSSIP_ITEM(10, "DRUIDS"               	 , GOSSIP_SENDER_MAIN, 1000);
		if(player->GetSession()->GetSecurity() >= 1)
		{
		player->ADD_GOSSIP_ITEM(10, "THE VIP SUPER DEMON - 1"            , GOSSIP_SENDER_MAIN, 1200);
		} else {
		player->ADD_GOSSIP_ITEM(10, "THE SUPER DEMON - 5"            , GOSSIP_SENDER_MAIN, 1100);
		}
		player->ADD_GOSSIP_ITEM(10, "Maybe later."               , GOSSIP_SENDER_MAIN, 11);
		player->PlayerTalkClass->SendGossipMenu(86000, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 action)
	{

		switch(action)
		{
		case 1:
		player->ADD_GOSSIP_ITEM(10, "WARRIORS" 	 		 , GOSSIP_SENDER_MAIN, 100);
		player->ADD_GOSSIP_ITEM(10, "PALADINS" 	 	 	 , GOSSIP_SENDER_MAIN, 200);
		player->ADD_GOSSIP_ITEM(10, "HUNTERS"               	 , GOSSIP_SENDER_MAIN, 300);
		player->ADD_GOSSIP_ITEM(10, "ROGUES"               	 , GOSSIP_SENDER_MAIN, 400);
		player->ADD_GOSSIP_ITEM(10, "PRIESTS"               	 , GOSSIP_SENDER_MAIN, 500);
		player->ADD_GOSSIP_ITEM(10, "DEATH KNIGHTS"              , GOSSIP_SENDER_MAIN, 600);
		player->ADD_GOSSIP_ITEM(10, "SHAMANS"               	 , GOSSIP_SENDER_MAIN, 700);
		player->ADD_GOSSIP_ITEM(10, "MAGES"               	 , GOSSIP_SENDER_MAIN, 800);
		player->ADD_GOSSIP_ITEM(10, "WARLOCKS"               	 , GOSSIP_SENDER_MAIN, 900);
		player->ADD_GOSSIP_ITEM(10, "DRUIDS"               	 , GOSSIP_SENDER_MAIN, 1000);
		player->ADD_GOSSIP_ITEM(10, "Maybe later."               , GOSSIP_SENDER_MAIN, 11);
		player->PlayerTalkClass->SendGossipMenu(86000, creature->GetGUID());
                return true;
		break;

		case 100:
                player->PlayerTalkClass->ClearMenus();
	         if (player->GetTeam() == ALLIANCE)
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "DPS Warrior", GOSSIP_SENDER_MAIN, 101);
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Protection Warrior", GOSSIP_SENDER_MAIN, 102);
	         }
	         else // Main Menu for Horde
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "DPS Warrior", GOSSIP_SENDER_MAIN, 103);
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Protection Warrior", GOSSIP_SENDER_MAIN, 104);
	         }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Exit.", GOSSIP_SENDER_MAIN, 11);
                player->PlayerTalkClass->SendGossipMenu(86000, creature->GetGUID());
                return true;
                break;
		case 101:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75025,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a DPS Warrior, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 102:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75026,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned Tank Warrior, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 103:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75043,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a DPS Warrior, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 104:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75044,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned Tank Warrior, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;

		case 200:
                player->PlayerTalkClass->ClearMenus();
	         if (player->GetTeam() == ALLIANCE)
	         {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Holy Paladin", GOSSIP_SENDER_MAIN, 201);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Retribution Paladin", GOSSIP_SENDER_MAIN, 202);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Protection Paladin", GOSSIP_SENDER_MAIN, 203);
	         }
	         else // Main Menu for Horde
	         {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Holy Paladin", GOSSIP_SENDER_MAIN, 204);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Retribution Paladin", GOSSIP_SENDER_MAIN, 205);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Protection Paladin", GOSSIP_SENDER_MAIN, 206);
	         }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Exit.", GOSSIP_SENDER_MAIN, 11);
                player->PlayerTalkClass->SendGossipMenu(86000, creature->GetGUID());
                return true;
                break;
		case 201:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75027,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned Healing Paladin, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 202:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75028,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned DPS Paladin, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 203:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75029,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned Tanky Paladin, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 204:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75045,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned Healing Paladin, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 205:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75046,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned DPS Paladin, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 206:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75047,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned Tanky Paladin, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;

		case 300:
                player->PlayerTalkClass->ClearMenus();
	         if (player->GetTeam() == ALLIANCE)
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Marksmanship Hunter", GOSSIP_SENDER_MAIN, 301);
	         }
	         else // Main Menu for Horde
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Marksmanship Hunter", GOSSIP_SENDER_MAIN, 302);
	         }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Exit.", GOSSIP_SENDER_MAIN, 11);
                player->PlayerTalkClass->SendGossipMenu(86000, creature->GetGUID());
                return true;
                break;
		case 301:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75030,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Hunter, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 302:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75048,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Hunter, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;

		case 400:
                player->PlayerTalkClass->ClearMenus();
	         if (player->GetTeam() == ALLIANCE)
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Rogue", GOSSIP_SENDER_MAIN, 401);
	         }
	         else // Main Menu for Horde
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Rogue", GOSSIP_SENDER_MAIN, 402);
	         }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Exit.", GOSSIP_SENDER_MAIN, 11);
                player->PlayerTalkClass->SendGossipMenu(86000, creature->GetGUID());
                return true;
                break;
		case 401:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75031,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Rogue, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 402:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75049,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Rogue, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;

		case 500:
                player->PlayerTalkClass->ClearMenus();
	         if (player->GetTeam() == ALLIANCE)
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Shadow Priest", GOSSIP_SENDER_MAIN, 501);
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Holy Priest", GOSSIP_SENDER_MAIN, 502);
	         }
	         else // Main Menu for Horde
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Shadow Priest", GOSSIP_SENDER_MAIN, 503);
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Holy Priest", GOSSIP_SENDER_MAIN, 504);
	         }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Exit.", GOSSIP_SENDER_MAIN, 11);
                player->PlayerTalkClass->SendGossipMenu(86000, creature->GetGUID());
                return true;
                break;
		case 501:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75032,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned Shadow Priest, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 502:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75033,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned Holy Priest, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 503:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75050,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned Shadow Priest, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 504:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75051,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned Holy Priest, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;

		case 600:
                player->PlayerTalkClass->ClearMenus();
	         if (player->GetTeam() == ALLIANCE)
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Death Knight", GOSSIP_SENDER_MAIN, 601);
	         }
	         else // Main Menu for Horde
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Death Knight", GOSSIP_SENDER_MAIN, 602);
	         }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Exit.", GOSSIP_SENDER_MAIN, 11);
                player->PlayerTalkClass->SendGossipMenu(86000, creature->GetGUID());
                return true;
                break;
		case 601:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75034,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Death Knight, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 602:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75052,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Death Knight, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;

		case 700:
                player->PlayerTalkClass->ClearMenus();
	         if (player->GetTeam() == ALLIANCE)
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Elemental Shaman", GOSSIP_SENDER_MAIN, 701);
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Enhancement Shaman", GOSSIP_SENDER_MAIN, 702);
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Restoration Shaman", GOSSIP_SENDER_MAIN, 703);
	         }
	         else // Main Menu for Horde
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Elemental Shaman", GOSSIP_SENDER_MAIN, 704);
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Enhancement Shaman", GOSSIP_SENDER_MAIN, 705);
               	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Restoration Shaman", GOSSIP_SENDER_MAIN, 706);
	         }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Exit.", GOSSIP_SENDER_MAIN, 11);
                player->PlayerTalkClass->SendGossipMenu(86000, creature->GetGUID());
                return true;
                break;
		case 701:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75035,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned an Elemental Shaman, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 702:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75036,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned an Enhancement Shaman, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 703:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75037,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Healing Shaman, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 704:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75053,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned an Elemental Shaman, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 705:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75054,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned an Enhancement Shaman, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 706:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75055,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Healing Shaman, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;

		case 800:
                player->PlayerTalkClass->ClearMenus();
	         if (player->GetTeam() == ALLIANCE)
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Mage", GOSSIP_SENDER_MAIN, 801);
	         }
	         else // Main Menu for Horde
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Mage", GOSSIP_SENDER_MAIN, 802);
	         }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Exit.", GOSSIP_SENDER_MAIN, 11);
                player->PlayerTalkClass->SendGossipMenu(86000, creature->GetGUID());
                return true;
                break;
		case 801:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75038,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Mage, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 802:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75056,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Mage, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;

		case 900:
                player->PlayerTalkClass->ClearMenus();
	         if (player->GetTeam() == ALLIANCE)
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Warlock", GOSSIP_SENDER_MAIN, 901);
	         }
	         else // Main Menu for Horde
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Warlock", GOSSIP_SENDER_MAIN, 902);
	         }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Exit.", GOSSIP_SENDER_MAIN, 11);
                player->PlayerTalkClass->SendGossipMenu(86000, creature->GetGUID());
                return true;
                break;
		case 901:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75039,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Warlock, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 902:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75057,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Warlock, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;

		case 1000:
                player->PlayerTalkClass->ClearMenus();
	         if (player->GetTeam() == ALLIANCE)
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Restoration Druid", GOSSIP_SENDER_MAIN, 1001);
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Balance Druid", GOSSIP_SENDER_MAIN, 1002);
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Feral Druid", GOSSIP_SENDER_MAIN, 1003);
	         }
	         else // Main Menu for Horde
	         {
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Restoration Druid", GOSSIP_SENDER_MAIN, 1004);
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Balance Druid", GOSSIP_SENDER_MAIN, 1005);
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Feral Druid", GOSSIP_SENDER_MAIN, 1006);
	         }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Exit.", GOSSIP_SENDER_MAIN, 11);
                player->PlayerTalkClass->SendGossipMenu(86000, creature->GetGUID());
                return true;
                break;
		case 1001:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75040,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Healing Druid, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 1002:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75041,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a DPS Druid, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 1003:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75042,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Feral Druid, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 1004:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75058,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Healing Druid, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 1005:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75059,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a DPS Druid, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 1006:
			player->PlayerTalkClass->SendCloseGossip();
			player->AddAura(57724, player);
			player->SummonCreature(75060,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Feral Druid, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;

		case 1100:
                player->PlayerTalkClass->ClearMenus();
		  if (player->HasItemCount(28558, 5))
		  {
	         	if (player->GetTeam() == ALLIANCE)
	         	{
                		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "This Demon Costs 5 Alterac Valley Tokens. You want it?", GOSSIP_SENDER_MAIN, 1100);
                		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Yes. GIVE ME THE DEMON!", GOSSIP_SENDER_MAIN, 1101);
                		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "No thanks.", GOSSIP_SENDER_MAIN, 11);
	         	}
	         	else // Main Menu for Horde
	         	{
                		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "This Demon Costs 5 Alterac Valley Tokens. You want it?", GOSSIP_SENDER_MAIN, 1100);
                		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Yes. GIVE ME THE DEMON!", GOSSIP_SENDER_MAIN, 1102);
                		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "No thanks.", GOSSIP_SENDER_MAIN, 11);
	         	}
		  } else {
		  creature->MonsterWhisper("You do not have enough Alterac Valley tokens to spawn this demon.", player->GetGUID());
		  player->PlayerTalkClass->SendCloseGossip();
		  }
                player->PlayerTalkClass->SendGossipMenu(86000, creature->GetGUID());
                return true;
                break;

		case 1101:
			player->PlayerTalkClass->SendCloseGossip();
			player->DestroyItemCount(28558, 5, true);
			player->AddAura(57724, player);
			player->SummonCreature(75061,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned an Alliance Demon Master, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 1102:
			player->PlayerTalkClass->SendCloseGossip();
			player->DestroyItemCount(28558, 5, true);
			player->AddAura(57724, player);
			player->SummonCreature(75062,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Horde Demon Master, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;

		case 1200:
                player->PlayerTalkClass->ClearMenus();
		  if (player->HasItemCount(28558, 1))
		  {
	         	if (player->GetTeam() == ALLIANCE)
	         	{
                		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "This Demon Costs 1 Alterac Valley Tokens. You want it?", GOSSIP_SENDER_MAIN, 1200);
                		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Yes. GIVE ME THE DEMON!", GOSSIP_SENDER_MAIN, 1201);
                		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "No thanks.", GOSSIP_SENDER_MAIN, 11);
	         	}
	         	else // Main Menu for Horde
	         	{
                		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "This Demon Costs 1 Alterac Valley Tokens. You want it?", GOSSIP_SENDER_MAIN, 1200);
                		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Yes. GIVE ME THE DEMON!", GOSSIP_SENDER_MAIN, 1202);
                		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "No thanks.", GOSSIP_SENDER_MAIN, 11);
	         	}
		  } else {
		  creature->MonsterWhisper("You do not have enough Alterac Valley tokens to spawn this demon.", player->GetGUID());
		  player->PlayerTalkClass->SendCloseGossip();
		  }
                player->PlayerTalkClass->SendGossipMenu(86000, creature->GetGUID());
                return true;
                break;

		case 1201:
			player->PlayerTalkClass->SendCloseGossip();
			player->DestroyItemCount(28558, 1, true);
			player->AddAura(57724, player);
			player->SummonCreature(75061,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned an Alliance Demon Master, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;
		case 1202:
			player->PlayerTalkClass->SendCloseGossip();
			player->DestroyItemCount(28558, 1, true);
			player->AddAura(57724, player);
			player->SummonCreature(75062,player->GetPositionX() ,player->GetPositionY()+3, player->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,600000);
			creature->MonsterWhisper("You have spawned a Horde Demon Master, You are the owner of this fine battle machine. It only has enough fuel for to survive for 10 minutes, when those 10 has passed your vehicle will go away then you can come and get a new one. ", player->GetGUID());
			break;

		case 11:
			creature->MonsterSay("Please come again in a hurry my warrior!", LANG_UNIVERSAL, NULL);
			player->PlayerTalkClass->SendCloseGossip();
			break;

		}

		return true;
	}

};

void AddSC_npc_vehiclespawner()
{
	new npc_vehiclespawner();
}
