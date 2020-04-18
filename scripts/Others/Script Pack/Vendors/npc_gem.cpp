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

class multi_gem : public CreatureScript
{
	public:
		multi_gem() : CreatureScript("multi_gem")
		{
		}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			Creature * npc_next = pPlayer->FindNearestCreature(600010, 30.0f, true);
			
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_JEWELCRAFTING_GEM_38:24|t|r Yellow", GOSSIP_SENDER_MAIN, 0);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_JEWELCRAFTING_GEM_42:24|t|r Blue", GOSSIP_SENDER_MAIN, 1);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_JEWELCRAFTING_GEM_37:24|t|r Red", GOSSIP_SENDER_MAIN, 2);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_JEWELCRAFTING_GEM_40:24|t|r Purple", GOSSIP_SENDER_MAIN, 3);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_JEWELCRAFTING_GEM_41:24|t|r Green", GOSSIP_SENDER_MAIN, 4);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_JEWELCRAFTING_GEM_39:24|t|r Orange", GOSSIP_SENDER_MAIN, 5);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_JEWELCRAFTING_GEM_31:24|t|r Meta", GOSSIP_SENDER_MAIN, 6);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\spell_magic_lesserinvisibilty:24|t|r Nevermind", GOSSIP_SENDER_MAIN, 7);
			pPlayer->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player * Player, Creature * Creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			if(!Player)
				return true;
			
			WorldSession * m_session = Player->GetSession();
			
			switch(uiAction)
			{
				case 0:
					{
						Player->vendorLoader = 500112;
						m_session->SendListCustomInventory(Creature->GetGUID(),500112);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 1:
					{

						Player->vendorLoader = 500014;
						m_session->SendListCustomInventory(Creature->GetGUID(),500014);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 2:
					{
						Player->vendorLoader = 500092;
						m_session->SendListCustomInventory(Creature->GetGUID(),500092);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 3:
					{
						Player->vendorLoader = 500073;
						m_session->SendListCustomInventory(Creature->GetGUID(),500073);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 4:
					{
						Player->vendorLoader = 500041;
						m_session->SendListCustomInventory(Creature->GetGUID(),500041);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 5:
					{
						Player->vendorLoader = 500067;
						m_session->SendListCustomInventory(Creature->GetGUID(),500067);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 6:
					{
						Player->vendorLoader = 2500062;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500062);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 7: // Close Gossips
					{
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
			}
			return true;
		}

};

void AddSC_multi_gem()
{
	new multi_gem();
}