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

class npc_event : public CreatureScript
{
	public:
		npc_event() : CreatureScript("npc_event")
		{
		}
		
		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			Creature * npc_next = pPlayer->FindNearestCreature(600010, 30.0f, true);
			
			// Main menus:
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_Ore_Gold_01:24|t|r Gold Dust rewards", GOSSIP_SENDER_MAIN, 1);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_Ore_Iron_01:24|t|r Silver Dust rewards", GOSSIP_SENDER_MAIN, 2);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_Misc_QuestionMark:24|t|r Nevermind..", GOSSIP_SENDER_MAIN, 300);
			pPlayer->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
			return true;
		}
};

		bool OnGossipSelect(Player * Player, Creature * Creature, uint32 /*uiSender*/, uint32 uiAction)
		{
		switch (uiAction) {

			case 1:	// Gold Menu
			Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_BigBlizzardBear:24|t|r Mounts", GOSSIP_SENDER_MAIN, 3);
			Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_BigBlizzardBear:24|t|r Companions", GOSSIP_SENDER_MAIN, 6);
			Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_BigBlizzardBear:24|t|r Transmogrification", GOSSIP_SENDER_MAIN, 8);
			Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_BigBlizzardBear:24|t|r Morphs", GOSSIP_SENDER_MAIN, 10);
			Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_BigBlizzardBear:24|t|r Titles", GOSSIP_SENDER_MAIN, 12);
			
			// Sub Menus
			case 3: // Mounts
				{
				Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_BigBlizzardBear:24|t|r Ground Mounts", GOSSIP_SENDER_MAIN, 4);
				Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_FlyingCarpet:24|t|r Flying Mounts", GOSSIP_SENDER_MAIN, 5);
				return true;
				}
		
			case 6: // Companions
				{
				Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_FlyingCarpet:24|t|r Companions", GOSSIP_SENDER_MAIN, 7);
				return true;
				}

			case 8: // Transmogrification
				{
				Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_FlyingCarpet:24|t|r Transmogrification", GOSSIP_SENDER_MAIN, 9);
				return true;
				}

			case 10: // Morphs
				{
				Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_FlyingCarpet:24|t|r Morphs", GOSSIP_SENDER_MAIN, 11);
				return true;
				}

			case 11: // Titles
				{
				Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_FlyingCarpet:24|t|r Titles", GOSSIP_SENDER_MAIN, 12);
				return true;
				}

			case 2: // Silver Menu 
				{
				Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_BigBlizzardBear:24|t|r Ground Mounts", GOSSIP_SENDER_MAIN, 13);
				Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_BigBlizzardBear:24|t|r Companions", GOSSIP_SENDER_MAIN, 15);
				Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_Misc_QuestionMark:24|t|r Nevermind..", GOSSIP_SENDER_MAIN, 300);
				return true;
				}

			case 13: // Companions
				{
				Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_FlyingCarpet:24|t|r Companions", GOSSIP_SENDER_MAIN, 14);
				return true;
				break;
				}

			case 15: // Companions
			Player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_FlyingCarpet:24|t|r Companions", GOSSIP_SENDER_MAIN, 16);
				return true;
				break;

			case 300: // Will close the gossip menu
				{
				Player->PlayerTalkClass->SendCloseGossip();
				return true;
			    break;
				}

			// Prevents a server crash
			default:
				{
				return true;
			break;
				}

		/* GOSSIP END */
			
		if(!Player)
			return true;
			WorldSession * m_session = Player->GetSession();
			switch(uiAction)
			{
				case 0:
					{
						Player->vendorLoader = 2500026;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500026);
						Player->PlayerTalkClass->SendCloseGossip();
					}
					return true;
					break;
				case 1:
					{

						Player->vendorLoader = 2500027;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500027);
						Player->PlayerTalkClass->SendCloseGossip();
					}
					return true;
					break;
				case 2:
					{
						Player->vendorLoader = 2500028;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500028);
						Player->PlayerTalkClass->SendCloseGossip();
					}
					return true;
					break;
				case 3:
					{
						Player->vendorLoader = 2500029;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500029);
						Player->PlayerTalkClass->SendCloseGossip();
					}
					return true;
					break;
			    case 4: // Close Gossips
					{
						Player->PlayerTalkClass->SendCloseGossip();
					}
					return true;
					break;
			}
		}
};

void AddSC_npc_event()
{
	new npc_event();
}