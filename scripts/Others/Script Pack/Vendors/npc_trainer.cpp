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

class multi_glyphs : public CreatureScript
{
	public:
		multi_glyphs() : CreatureScript("multi_glyphs")
		{
		}
		
		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			Creature * npc_next = pPlayer->FindNearestCreature(600010, 30.0f, true);
			
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Warrior_talent_icon_InnerRage:24|t|r Warrior", GOSSIP_SENDER_MAIN, 0);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\spell_Paladin_divinecircle:24|t|r Paladin", GOSSIP_SENDER_MAIN, 1);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\ABILITY_HUNTER_MASTERSCALL:24|t|r Hunter", GOSSIP_SENDER_MAIN, 2);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\ability_rogue_deadliness:24|t|r Rogue", GOSSIP_SENDER_MAIN, 3);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Spell_Holy_DivineIllumination:24|t|r Priest", GOSSIP_SENDER_MAIN, 4);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\ability_deathknight_boneshield:24|t|r Death Knight", GOSSIP_SENDER_MAIN, 5);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Ability_Shaman_Heroism:24|t|r Shaman", GOSSIP_SENDER_MAIN, 6);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\ABILITY_MAGE_MOLTENARMOR:24|t|r Mage", GOSSIP_SENDER_MAIN, 7);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\ability_warlock_whiplash:24|t|r Warlock", GOSSIP_SENDER_MAIN, 8);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\ABILITY_DRUID_DEMORALIZINGROAR:24|t|r Druid", GOSSIP_SENDER_MAIN, 9);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_Misc_QuestionMark:24|t|r Nevermind..", GOSSIP_SENDER_MAIN, 10);
			
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
						Player->vendorLoader = 2500001;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500001);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 1:
					{

						Player->vendorLoader = 2500002;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500002);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 2:
					{
						Player->vendorLoader = 2500003;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500003);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 3:
					{
						Player->vendorLoader = 2500004;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500004);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 4:
					{
						Player->vendorLoader = 2500005;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500005);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 5:
					{
						Player->vendorLoader = 2500006;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500006);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 6:
					{
						Player->vendorLoader = 2500007;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500007);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 7:
					{
						Player->vendorLoader = 2500008;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500008);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 8:
					{
						Player->vendorLoader = 2500009;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500009);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 9:
					{
						Player->vendorLoader = 2500010;
						m_session->SendListCustomInventory(Creature->GetGUID(),2500010);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
			    case 10: // Close Gossips
					{
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
			}
			return true;
		}

};

void AddSC_multi_glyphs()
{
	new multi_glyphs();
}