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

class multi_transmog_tier : public CreatureScript
{
	public:
		multi_transmog_tier() : CreatureScript("multi_transmog_tier")
		{
		}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			Creature * npc_next = pPlayer->FindNearestCreature(600010, 30.0f, true);
			
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Ragnaros:24|t|r Tier 1", GOSSIP_SENDER_MAIN, 0);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Nefarion:24|t|r Tier 2", GOSSIP_SENDER_MAIN, 1);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_Boss_KelThuzad_01:24|t|r Tier 3", GOSSIP_SENDER_MAIN, 2);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_Boss_PrinceMalchezaar_02:24|t|r Tier 4", GOSSIP_SENDER_MAIN, 3);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_Boss_KargathBladefist_01:24|t|r Tier 5", GOSSIP_SENDER_MAIN, 4);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Illidan:24|t|r Tier 6", GOSSIP_SENDER_MAIN, 5);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_Dungeon_Naxxramas_10man:24|t|r Tier 7", GOSSIP_SENDER_MAIN, 6);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_Dungeon_UlduarRaid_IceGiant_01:24|t|r Tier 8", GOSSIP_SENDER_MAIN, 7);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\spell_magic_lesserinvisibilty:24|t|r Nevermind", GOSSIP_SENDER_MAIN, 8);
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
						Player->vendorLoader = 1500072;
						m_session->SendListCustomInventory(Creature->GetGUID(),1500072);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 1:
					{

						Player->vendorLoader = 1500073;
						m_session->SendListCustomInventory(Creature->GetGUID(),1500073);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 2:
					{
						Player->vendorLoader = 1500074;
						m_session->SendListCustomInventory(Creature->GetGUID(),1500074);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 3:
					{
						Player->vendorLoader = 1500075;
						m_session->SendListCustomInventory(Creature->GetGUID(),1500075);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 4:
					{
						Player->vendorLoader = 1500076;
						m_session->SendListCustomInventory(Creature->GetGUID(),1500076);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 5:
					{
						Player->vendorLoader = 1500077;
						m_session->SendListCustomInventory(Creature->GetGUID(),1500077);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 6:
					{
						Player->vendorLoader = 1500078;
						m_session->SendListCustomInventory(Creature->GetGUID(),1500078);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 7:
					{
						Player->vendorLoader = 1500079;
						m_session->SendListCustomInventory(Creature->GetGUID(),1500079);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 8:
					{
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
			}
			return true;
		}

};

void AddSC_multi_transmog_tier()
{
	new multi_transmog_tier();
}