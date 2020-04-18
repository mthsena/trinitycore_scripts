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

class multi_allinone : public CreatureScript
{
	public:
		multi_allinone() : CreatureScript("multi_allinone")
		{
		}
		
		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			Creature * npc_next = pPlayer->FindNearestCreature(600010, 30.0f, true);
			
			
			
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mage_ConjureFoodRank10:24|t|r Food", GOSSIP_SENDER_MAIN, 0);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Trade_Herbalism:24|t|r Reagents", GOSSIP_SENDER_MAIN, 1);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\ABILITY_POISONS:24|t|r Poisons", GOSSIP_SENDER_MAIN, 2);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_BigBlizzardBear:24|t|r Ground Mounts", GOSSIP_SENDER_MAIN, 3);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Mount_FlyingCarpet:24|t|r Flying Mounts", GOSSIP_SENDER_MAIN, 4);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_Drink_27_BlueSoup:24|t|r Hunter food", GOSSIP_SENDER_MAIN, 5);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\spell_magic_lesserinvisibilty:24|t|r Nevermind", GOSSIP_SENDER_MAIN, 6);
			
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
						Player->vendorLoader = 2500026;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500026);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 1:
					{

						Player->vendorLoader = 2500027;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500027);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 2:
					{
						Player->vendorLoader = 3334;
						m_session->SendListCustomInventory(Creature->GetGUID(),3334);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 3:
					{
						Player->vendorLoader = 2500028;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500028);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 4:
					{
						Player->vendorLoader = 2500029;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500029);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 5:
					{
						Player->vendorLoader = 2500100;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500100);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
			    case 6: // Close Gossips
					{
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
			}
			return true;
		}

};

void AddSC_multi_allinone()
{
	new multi_allinone();
}