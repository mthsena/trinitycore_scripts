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
 - Developer(s): Styler
 - Complete: 100%
 - ScriptName: 'global_teleporter' 
 - Comment: Updated with Icons
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"
#include "Chat.h"

const int PLAYER_QUEUE = 4;
static const Position playerSpawnPoint[PLAYER_QUEUE] = 
{
	{-7473.95f, -1088.11f, 896.78f, 4.38455f},
    {-6379.22f, 1256.77f, 7.18803f, 2.9329f},
    {-775.036f, 1511.92f, 137.398f, 4.71829f},
    {-6414.02f, -3507.6f, 402.778f, 2.03819f},
};

class global_teleporter : public CreatureScript
{
public:
    global_teleporter() : CreatureScript("global_teleporter") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->isInCombat())
        {
            pPlayer->GetSession()->SendNotification("You are in combat");
            return false;
        }
		pPlayer->ADD_GOSSIP_ITEM(1, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Mimiron_01:24|t|r Mall", GOSSIP_SENDER_MAIN, 0);
		pPlayer->ADD_GOSSIP_ITEM(1, "|cff00ff00|TInterface\\icons\\Spell_Shaman_SpectralTransformation:24|t|r Transmogrification", GOSSIP_SENDER_MAIN, 2);
		pPlayer->ADD_GOSSIP_ITEM(1, "|cff00ff00|TInterface\\icons\\Achievement_Arena_3v3_2:24|t|r Duel Zone", GOSSIP_SENDER_MAIN, 4);
		pPlayer->ADD_GOSSIP_ITEM(1, "|cff00ff00|TInterface\\icons\\Achievement_Arena_2v2_2:24|t|r Gurubashi", GOSSIP_SENDER_MAIN, 5);
		pPlayer->ADD_GOSSIP_ITEM(1, "|cff00ff00|TInterface\\icons\\Ability_FiegnDead:24|t|r FFA Zone", GOSSIP_SENDER_MAIN, 6);
		pPlayer->ADD_GOSSIP_ITEM(1, "|cff00ff00|TInterface\\icons\\INV_AXE_100:24|t|r Personal Queue Area", GOSSIP_SENDER_MAIN, 8);
		pPlayer->SEND_GOSSIP_MENU(7, pCreature->GetGUID());        
        return true;
    }

	bool OnGossipSelect(Player* pPlayer, Creature* pCreature,uint32 uiSender, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();

        switch (uiAction)
        {
		  case 0: // Starter Mall
			  { 
				  pCreature->CastSpell(pPlayer,35517,false);
                  pPlayer->TeleportTo(571, 4629.569f, -5635.509f, 110.448f, 4.134f);
				  ChatHandler(pPlayer->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You have been teleported to the |cFFFF4500Mall|r!", pPlayer->GetName());
			  }break;
		  case 1: // Global Mall
              {
                  pCreature->CastSpell(pPlayer,35517,false);
                  pPlayer->TeleportTo(230, 1380.61f, -822.44f, -92.72f, 4.752445f);
				  ChatHandler(pPlayer->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You have been teleported to the |cFFFF4500Global Mall|r!", pPlayer->GetName());
              }break;
		  case 2: // Transmogrification
			  {
				  pCreature->CastSpell(pPlayer,35517,false);
                  pPlayer->TeleportTo(571, 4651.711f, -5535.464f, 28.918f, 0.906f);
                  ChatHandler(pPlayer->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You have been teleported to the |cFFFF4500Transmogrification Mall|r!", pPlayer->GetName());
			  }break;
		  case 3: // Icecrown Citadel
              {
                  pCreature->CastSpell(pPlayer,35517,false);
                  pPlayer->TeleportTo(571, 5869.05f, 2108.62f, 636.01f, 3.621913f);
                  ChatHandler(pPlayer->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You have been teleported to the |cFFFF4500Icecrown Citadel|r!", pPlayer->GetName());
              }break;
		  
		  case 4: // Duel Zone
              {
                  pCreature->CastSpell(pPlayer,35517,false);
                  pPlayer->TeleportTo(1, 6392.199f, -4046.620f, 658.283f, 0.004f);
                  ChatHandler(pPlayer->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You have been teleported to the |cFFFF4500Duel Zone|r!", pPlayer->GetName());
              }break;
		  case 5: // Gurubashi
              {
                  pCreature->CastSpell(pPlayer,35517,false);
                  pPlayer->TeleportTo(0, -13260.70f, 163.11f, 35.99f, 1.118780f);
                  ChatHandler(pPlayer->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You have been teleported to the |cFFFF4500Gurubashi|r!", pPlayer->GetName());
			  }break;
		  case 6: // FFA Zone
			  {
				  pCreature->CastSpell(pPlayer,35517,false);
				  pPlayer->TeleportTo(0, -14599.00f, -237.766f, 24.85f, 2.43732f);
                  ChatHandler(pPlayer->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You have been teleported to the |cFFFF4500FFA Zone|r!", pPlayer->GetName());
			  }break;
		  case 7: // Event Zone
			  {
				  pCreature->CastSpell(pPlayer,35517,false);
                  pPlayer->TeleportTo(230, 990.414f, -218.775f, -61.7892f, 5.49272f);
                  ChatHandler(pPlayer->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You have been teleported to the |cFFFF4500Event Zone|r!", pPlayer->GetName());

			  }break;
		  case 8: // Personal Queue Area
			  {
				  pCreature->CastSpell(pPlayer,35517,false);
				  int i = urand(0, PLAYER_QUEUE - 1);
                  pPlayer->TeleportTo(0, playerSpawnPoint[i].GetPositionX(), playerSpawnPoint[i].GetPositionY(), playerSpawnPoint[i].GetPositionZ(), playerSpawnPoint[i].GetOrientation());
				  ChatHandler(pPlayer->GetSession()).PSendSysMessage("|cffff6060[Information]:|r You have been teleported to the |cFFFF4500Personal Queue Area|r!", pPlayer->GetName());
			  }

			  {
                  OnGossipHello(pPlayer, pCreature);
                return true;
              }break;
		}
		pPlayer->CLOSE_GOSSIP_MENU();
        return true;
	}

};

void AddSC_global_teleporter()
{
    new global_teleporter();
}
