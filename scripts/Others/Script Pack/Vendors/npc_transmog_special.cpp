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

enum arenarating 
{
        arenarating		= 0,
		arenarating1	= 0,
		arenarating2	= 0,
		arenarating3	= 0,
		arenarating4	= 0,
		arenarating5	= 0,
		arenarating6	= 0,
		arenarating7	= 0
};

class multi_transmog_special : public CreatureScript
{
	public:
		multi_transmog_special() : CreatureScript("multi_transmog_special")
		{
		}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			Creature * npc_next = pPlayer->FindNearestCreature(600010, 30.0f, true);
						
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Spell_Arcane_Arcane04:24|t|r 1500 - Special Offers", GOSSIP_SENDER_MAIN, 0);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_SWORD_52:24|t|r 1850 - Weapons", GOSSIP_SENDER_MAIN, 1);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_CHEST_PLATE_25:24|t|r 1850 - Armor", GOSSIP_SENDER_MAIN, 500);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\spell_magic_lesserinvisibilty:24|t|r Nevermind", GOSSIP_SENDER_MAIN, 600);
			pPlayer->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player * Player, Creature * Creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			Player->PlayerTalkClass->ClearMenus();
			if(!Player)
				return true;
			
			WorldSession * m_session = Player->GetSession();
			
			switch(uiAction)
			{
				case 0: // Special Offers
					if (Player->GetArenaPersonalRating(ARENA_TYPE_2v2) >= arenarating)
					{
						Player->vendorLoader = 1500085;
						m_session->SendListCustomInventory(Creature->GetGUID(),1500085);
						Player->PlayerTalkClass->SendCloseGossip();
					}else
					{
						ChatHandler(Player->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You need atleast |cFFFF4500%u|r 2v2 or 3v3 rating to buy this item!", arenarating);
						Player->CLOSE_GOSSIP_MENU();
                        return false;
					}break;

					case 1: // Weapons
						if (Player->GetArenaPersonalRating(ARENA_TYPE_2v2) >= arenarating1)
					{
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r 1850 - Weapons Tier 1", GOSSIP_SENDER_MAIN, 100);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Trade_Archaeology_SkullMug:24|t|r 2250 - Weapons Tier 2", GOSSIP_SENDER_MAIN, 200);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Draenei_B_01:24|t|r 2500 - Epic Weapons!", GOSSIP_SENDER_MAIN, 300);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\spell_magic_lesserinvisibilty:24|t|r Nevermind", GOSSIP_SENDER_MAIN, 600);
						Player->PlayerTalkClass->SendGossipMenu(9425, Creature->GetGUID());
					}else
					{
						ChatHandler(Player->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You need atleast |cFFFF4500%u|r 2v2 or 3v3 rating to buy this item!", arenarating);
						Player->CLOSE_GOSSIP_MENU();
                        return false;
					}break;

					case 100: // Weapons - Tier 1
						if (Player->GetArenaPersonalRating(ARENA_TYPE_2v2) >= arenarating2)
					{
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r One-Handed Swords", GOSSIP_SENDER_MAIN, 101);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r One-Handed Axes", GOSSIP_SENDER_MAIN, 102);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r One-Handed Maces", GOSSIP_SENDER_MAIN, 103);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Two-Handed Swords", GOSSIP_SENDER_MAIN, 104);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Two-Handed Axes", GOSSIP_SENDER_MAIN, 105);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Two-Handed Maces", GOSSIP_SENDER_MAIN, 106);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Fist Weapons", GOSSIP_SENDER_MAIN, 107);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Polearms", GOSSIP_SENDER_MAIN, 108);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Daggers", GOSSIP_SENDER_MAIN, 109);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Shields", GOSSIP_SENDER_MAIN, 110);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Staves", GOSSIP_SENDER_MAIN, 111);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Bows", GOSSIP_SENDER_MAIN, 112);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\spell_magic_lesserinvisibilty:24|t|r Nevermind", GOSSIP_SENDER_MAIN, 500);
						Player->PlayerTalkClass->SendGossipMenu(9425, Creature->GetGUID());
					}else
					{
						ChatHandler(Player->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You need atleast |cFFFF4500%u|r 2v2 or 3v3 rating to buy this item!", arenarating);
						Player->CLOSE_GOSSIP_MENU();
                        return false;
					}break;

					case 101:
						{
						}break;
					case 102:
					case 103:
					case 104:
					case 105:
					case 106:
					case 107:
					case 108:
					case 109:
					case 110:
					case 112:

					case 200: // Weapons - Tier 2
						if (Player->GetArenaPersonalRating(ARENA_TYPE_2v2) >= arenarating3)
					{
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r One-Handed Swords", GOSSIP_SENDER_MAIN, 201);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r One-Handed Axes", GOSSIP_SENDER_MAIN, 202);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r One-Handed Maces", GOSSIP_SENDER_MAIN, 203);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Two-Handed Swords", GOSSIP_SENDER_MAIN, 204);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Two-Handed Axes", GOSSIP_SENDER_MAIN, 205);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Two-Handed Maces", GOSSIP_SENDER_MAIN, 206);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Fist Weapons", GOSSIP_SENDER_MAIN, 207);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Polearms", GOSSIP_SENDER_MAIN, 208);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Daggers", GOSSIP_SENDER_MAIN, 209);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Shields", GOSSIP_SENDER_MAIN, 210);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Staves", GOSSIP_SENDER_MAIN, 211);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Bows", GOSSIP_SENDER_MAIN, 212);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\spell_magic_lesserinvisibilty:24|t|r Nevermind", GOSSIP_SENDER_MAIN, 500);
						Player->PlayerTalkClass->SendGossipMenu(9425, Creature->GetGUID());
					}else
					{
						ChatHandler(Player->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You need atleast |cFFFF4500%u|r 2v2 or 3v3 rating to buy this item!", arenarating);
						Player->CLOSE_GOSSIP_MENU();
                        return false;
					}break;

					case 201:
						{
						}break;
					case 202:
					case 203:
					case 204:
					case 205:
					case 206:
					case 207:
					case 208:
					case 209:
					case 210:
					case 212:

					case 300: // Weapons - EPIC Weapons
						if (Player->GetArenaPersonalRating(ARENA_TYPE_2v2) >= arenarating5)
					{
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r One-Handed Swords", GOSSIP_SENDER_MAIN, 301);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r One-Handed Axes", GOSSIP_SENDER_MAIN, 302);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r One-Handed Maces", GOSSIP_SENDER_MAIN, 303);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Two-Handed Swords", GOSSIP_SENDER_MAIN, 304);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Two-Handed Axes", GOSSIP_SENDER_MAIN, 305);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Two-Handed Maces", GOSSIP_SENDER_MAIN, 306);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Fist Weapons", GOSSIP_SENDER_MAIN, 307);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Polearms", GOSSIP_SENDER_MAIN, 308);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Daggers", GOSSIP_SENDER_MAIN, 309);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Shields", GOSSIP_SENDER_MAIN, 310);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Staves", GOSSIP_SENDER_MAIN, 311);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Bows", GOSSIP_SENDER_MAIN, 312);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\spell_magic_lesserinvisibilty:24|t|r Nevermind", GOSSIP_SENDER_MAIN, 600);
						Player->PlayerTalkClass->SendGossipMenu(9425, Creature->GetGUID());
					}else
					{
						ChatHandler(Player->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You need atleast |cFFFF4500%u|r 2v2 or 3v3 rating to buy this item!", arenarating);
						Player->CLOSE_GOSSIP_MENU();
                        return false;
					}break;

					case 302:
					case 303:
					case 304:
					case 305:
					case 306:
					case 307:
					case 308:
					case 309:
					case 310:
					case 312:

					case 400: // Weapons - EPIC Weapons
						if (Player->GetArenaPersonalRating(ARENA_TYPE_2v2) >= arenarating5)
					{
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r One-Handed Swords", GOSSIP_SENDER_MAIN, 401);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r One-Handed Axes", GOSSIP_SENDER_MAIN, 402);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r One-Handed Maces", GOSSIP_SENDER_MAIN, 403);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Two-Handed Swords", GOSSIP_SENDER_MAIN, 404);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Two-Handed Axes", GOSSIP_SENDER_MAIN, 405);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Two-Handed Maces", GOSSIP_SENDER_MAIN, 406);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Fist Weapons", GOSSIP_SENDER_MAIN, 407);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Polearms", GOSSIP_SENDER_MAIN, 408);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Daggers", GOSSIP_SENDER_MAIN, 409);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Shields", GOSSIP_SENDER_MAIN, 410);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Staves", GOSSIP_SENDER_MAIN, 411);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Bows", GOSSIP_SENDER_MAIN, 412);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\spell_magic_lesserinvisibilty:24|t|r Nevermind", GOSSIP_SENDER_MAIN, 500);
						Player->PlayerTalkClass->SendGossipMenu(9425, Creature->GetGUID());
					}else
					{
						ChatHandler(Player->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You need atleast |cFFFF4500%u|r 2v2 or 3v3 rating to buy this item!", arenarating);
						Player->CLOSE_GOSSIP_MENU();
                        return false;
					}break;

					case 401:
						{
						}break;
					case 402:
					case 403:
					case 404:
					case 405:
					case 406:
					case 407:
					case 408:
					case 409:
					case 410:
					case 412:

					case 500: // Weapons - Tier 2
					if (Player->GetArenaPersonalRating(ARENA_TYPE_2v2) >= arenarating4)
					{
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Head", GOSSIP_SENDER_MAIN, 501);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Shoulders", GOSSIP_SENDER_MAIN, 502);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Chest", GOSSIP_SENDER_MAIN, 503);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Back", GOSSIP_SENDER_MAIN, 504);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Hands", GOSSIP_SENDER_MAIN, 505);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Legs", GOSSIP_SENDER_MAIN, 506);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Feet", GOSSIP_SENDER_MAIN, 507);
						Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\spell_magic_lesserinvisibilty:24|t|r Nevermind", GOSSIP_SENDER_MAIN, 600);
						Player->PlayerTalkClass->SendGossipMenu(9425, Creature->GetGUID());
					}else
					{
						ChatHandler(Player->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You need atleast |cFFFF4500%u|r 2v2 or 3v3 rating to buy this item!", arenarating);
						Player->CLOSE_GOSSIP_MENU();
                        return false;
					}break;

					case 301:
						{
						}break;
					case 502:
					case 503:
					case 504:
					case 505:
					case 506:
					case 507:
				case 600:
					{
					Player->PlayerTalkClass->SendCloseGossip();
					}break;
				}
			return true;
		}

};

void AddSC_multi_transmog_special()
{
	new multi_transmog_special();
}