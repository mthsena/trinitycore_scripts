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

class multi_donation : public CreatureScript
{
	public:
		multi_donation() : CreatureScript("multi_donation")
		{
		}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			Creature * npc_next = pPlayer->FindNearestCreature(600010, 30.0f, true);
			
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_CHEST_PLATE_23:24|t|r Season 8 mainset", GOSSIP_SENDER_MAIN, 0);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_CHEST_PLATE_25:24|t|r Tier 10.5 heroic", GOSSIP_SENDER_MAIN, 1);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_Bracer_36A:24|t|r Season 8 offparts", GOSSIP_SENDER_MAIN, 2);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_Belt_32:24|t|r PvE offsets", GOSSIP_SENDER_MAIN, 3);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Axe_1H_Horde_D_04_icon:24|t|r Weapons", GOSSIP_SENDER_MAIN, 4);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_Misc_QuestionMark:24|t|r Nevermind", GOSSIP_SENDER_MAIN, 5);
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
						Player->vendorLoader = 2500041;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500041);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 1:
					{

						Player->vendorLoader = 2500043;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500043);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 2:
					{
						Player->vendorLoader = 2500042;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500042);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 3:
					{
						Player->vendorLoader = 2500044;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500044);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 4:
					{
						Player->vendorLoader = 2500045;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500045);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 5:
					{
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
			}
			return true;
		}

};

void AddSC_multi_donation()
{
	new multi_donation();
}