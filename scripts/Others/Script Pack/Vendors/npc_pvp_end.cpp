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

class multi_pvp_end : public CreatureScript
{
	public:
		multi_pvp_end() : CreatureScript("multi_pvp_end")
		{
		}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			Creature * npc_next = pPlayer->FindNearestCreature(600010, 30.0f, true);
			
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_Chest_Plate_PVPWarrior_C_02:24|t|r Season 8 Mainset", GOSSIP_SENDER_MAIN, 0);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_Bracer_36A:24|t|r Season 8 Offset", GOSSIP_SENDER_MAIN, 1);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_JEWELRY_NECKLACE_15:24|t|r Season 8 Accessories", GOSSIP_SENDER_MAIN, 2);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_SWORD_107:24|t|r Season 8 Weapons T1", GOSSIP_SENDER_MAIN, 3);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Mace_2H_Blacksmithing_D_04_icon:24|t|r Season 8 Weapons T2", GOSSIP_SENDER_MAIN, 4);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\spell_magic_lesserinvisibilty:24|t|r Nevermind", GOSSIP_SENDER_MAIN, 5);
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
						Player->vendorLoader = 2500038;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500038);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 1:
					{
						Player->vendorLoader = 2500039;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500039);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 2:
					{
						Player->vendorLoader = 2500058;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500058);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 3:
					{
						Player->vendorLoader = 2500040;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500040);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 4:
					{
						Player->vendorLoader = 2500056;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500056);
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

void AddSC_multi_pvp_end()
{
	new multi_pvp_end();
}