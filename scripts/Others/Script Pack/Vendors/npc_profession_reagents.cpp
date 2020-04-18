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

class multi_profession : public CreatureScript
{
	public:
		multi_profession() : CreatureScript("multi_profession")
		{
		}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			Creature * npc_next = pPlayer->FindNearestCreature(600010, 30.0f, true);
			
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_Drink_27_BlueSoup:24|t|r Cooking", GOSSIP_SENDER_MAIN, 0);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_Fabric_Silk_01:24|t|r Cloth", GOSSIP_SENDER_MAIN, 1);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Trade_Engineering:24|t|r Crafting", GOSSIP_SENDER_MAIN, 2);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_ELEMENTAL_CRYSTAL_EARTH:24|t|r Elemental", GOSSIP_SENDER_MAIN, 3);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_Enchant_AbyssCrystal:24|t|r Enchanting", GOSSIP_SENDER_MAIN, 4);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Trade_Herbalism:24|t|r Herbs", GOSSIP_SENDER_MAIN, 5);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\inv_misc_mastersinscription:24|t|r Inscription", GOSSIP_SENDER_MAIN, 6);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_JEWELCRAFTING_GEM_31:24|t|r Jewelcrafting", GOSSIP_SENDER_MAIN, 7);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Trade_Archaeology_Dwarf_RuneStone:24|t|r Metal & Stone", GOSSIP_SENDER_MAIN, 8);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Trade_LeatherWorking:24|t|r Leather", GOSSIP_SENDER_MAIN, 9);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\spell_magic_lesserinvisibilty:24|t|r Nevermind", GOSSIP_SENDER_MAIN, 10);
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
						Player->vendorLoader = 2500046;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500046);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 1:
					{

						Player->vendorLoader = 2500047;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500047);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 2:
					{
						Player->vendorLoader = 2500048;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500048);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 3:
					{
						Player->vendorLoader = 2500049;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500049);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 4:
					{
						Player->vendorLoader = 2500050;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500050);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 5:
					{
						Player->vendorLoader = 2500051;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500051);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 6:
					{
						Player->vendorLoader = 2500052;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500052);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 7:
					{
						Player->vendorLoader = 2500053;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500053);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 8:
					{
						Player->vendorLoader = 2500054;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500054);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 9:
					{
						Player->vendorLoader = 2500055;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500055);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 10:
					{
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
			}
			return true;
		}

};

void AddSC_multi_profession()
{
	new multi_profession();
}