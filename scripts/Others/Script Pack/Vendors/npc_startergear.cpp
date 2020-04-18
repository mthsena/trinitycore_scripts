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

class multi_startergear : public CreatureScript
{
	public:
		multi_startergear() : CreatureScript("multi_startergear")
		{
		}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			Creature * npc_next = pPlayer->FindNearestCreature(600010, 30.0f, true);
			
			pPlayer->ADD_GOSSIP_ITEM(4, "Yellow", GOSSIP_SENDER_MAIN, 0);
			pPlayer->ADD_GOSSIP_ITEM(4, "Blue", GOSSIP_SENDER_MAIN, 1);
			pPlayer->ADD_GOSSIP_ITEM(4, "Red", GOSSIP_SENDER_MAIN, 2);
			pPlayer->ADD_GOSSIP_ITEM(4, "Purple", GOSSIP_SENDER_MAIN, 3);
			pPlayer->ADD_GOSSIP_ITEM(4, "Orange", GOSSIP_SENDER_MAIN, 4);
			pPlayer->ADD_GOSSIP_ITEM(4, "Nevermind..", GOSSIP_SENDER_MAIN, 4);
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
						Player->vendorLoader = 600010;
						m_session->SendListCustomInventory(Creature->GetGUID(),600010);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 1:
					{

						Player->vendorLoader = 600122;
						m_session->SendListCustomInventory(Creature->GetGUID(),600122);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 2:
					{
						Player->vendorLoader = 600145;
						m_session->SendListCustomInventory(Creature->GetGUID(),600145);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 3:
					{
						Player->vendorLoader = 600145;
						m_session->SendListCustomInventory(Creature->GetGUID(),600145);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				
				case 4: // Close Gossips
					{
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
			}
			return true;
		}

};

void AddSC_multi_startergear()
{
	new multi_startergear();
}