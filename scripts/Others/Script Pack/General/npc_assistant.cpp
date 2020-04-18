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

class player_assistant : public CreatureScript
{
public:
    player_assistant() : CreatureScript("player_assistant") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->isInCombat())
        {
            pPlayer->GetSession()->SendNotification("You are in combat");
            return false;
        }
        pPlayer->GetSession()->SendNotification("Welcome to the Player Assistant");
        pPlayer->ADD_GOSSIP_ITEM(5, "Give me Soul Shards", GOSSIP_SENDER_MAIN, 1);
        pPlayer->ADD_GOSSIP_ITEM(5, "Give me some Refreshments", GOSSIP_SENDER_MAIN, 2);
        pPlayer->ADD_GOSSIP_ITEM(5, "Give me a Mana Gem", GOSSIP_SENDER_MAIN, 3);
        pPlayer->ADD_GOSSIP_ITEM(5, "Reset my talent points", GOSSIP_SENDER_MAIN, 4);
        pPlayer->ADD_GOSSIP_ITEM(5, "Reset my Mount's and Spells ", GOSSIP_SENDER_MAIN, 5);
        pPlayer->ADD_GOSSIP_ITEM(5, "Reset my honor", GOSSIP_SENDER_MAIN, 6);
        pPlayer->ADD_GOSSIP_ITEM(5, "Reset my gold", GOSSIP_SENDER_MAIN, 7);
        pPlayer->ADD_GOSSIP_ITEM(5, "Heal me please", GOSSIP_SENDER_MAIN, 8);
        pPlayer->ADD_GOSSIP_ITEM(7, "Close", GOSSIP_SENDER_MAIN, 9);
        pPlayer->SEND_GOSSIP_MENU(907, pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();

        switch (uiAction)
        {
          case 1:
              {
                  pPlayer->CLOSE_GOSSIP_MENU();
                  pPlayer->CastSpell(pPlayer,24827,false);
                  pPlayer->MonsterWhisper("Soul Shard Created.", pPlayer->GetGUID());
              }break;
          case 2:
              {
                  pPlayer->CLOSE_GOSSIP_MENU();
                  pPlayer->CastSpell(pPlayer,42956,false);
                  pPlayer->MonsterWhisper("Refreshments Created.", pPlayer->GetGUID());
              }break;
          case 3:
              {
                  pPlayer->CLOSE_GOSSIP_MENU();
                  pPlayer->CastSpell(pPlayer,42985,false);;
                  pPlayer->MonsterWhisper("Mana Gem Created.", pPlayer->GetGUID());
              }break;
         case 4:
              {
                  pPlayer->CLOSE_GOSSIP_MENU();
                  pPlayer->resetTalents(true);
                  pCreature->MonsterWhisper("Your talents has been reset.", pPlayer->GetGUID());
              }break;
         case 5:
              {
                  pPlayer->CLOSE_GOSSIP_MENU();
                  pPlayer->resetSpells(false);
                  pCreature->MonsterWhisper("Your spells has been reset.", pPlayer->GetGUID());
              }break;
         case 6:
              {
                  pPlayer->CLOSE_GOSSIP_MENU();
                  pPlayer->SetHonorPoints(0);
                  pCreature->MonsterWhisper("Your honor has been reset.", pPlayer->GetGUID());
              }break;
         case 7:
              {
                  pPlayer->CLOSE_GOSSIP_MENU();
                  pPlayer->SetMoney(0);
                  pCreature->MonsterWhisper("Your gold has been reset.", pPlayer->GetGUID());
              }break;
         case 8:
              {
                  pPlayer->CLOSE_GOSSIP_MENU();
                  pCreature->CastSpell(pPlayer,38588,false);
                  pCreature->MonsterWhisper("You have been healed.", pPlayer->GetGUID());
              }break;
         case 9:
              {
                  pPlayer->CLOSE_GOSSIP_MENU();
                return true;
              }break;
        }
        pPlayer->CLOSE_GOSSIP_MENU();
        return true;
    }

};

void AddSC_player_assistant()
{
    new player_assistant();
}