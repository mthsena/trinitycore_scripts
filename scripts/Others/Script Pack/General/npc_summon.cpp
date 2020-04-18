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

class summon_all_npc : public CreatureScript
{
public:
    summon_all_npc() : CreatureScript("summon_all_npc") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->isInCombat())
        {
            pPlayer->GetSession()->SendNotification("You are in combat");
            return false;
        }
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Summon Teleporter", GOSSIP_SENDER_MAIN, 1);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Summon The Bounty Hunter", GOSSIP_SENDER_MAIN, 2);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Summon Mr. T", GOSSIP_SENDER_MAIN, 3);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Summon Guild House Master", GOSSIP_SENDER_MAIN, 4);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Summon The All in One", GOSSIP_SENDER_MAIN, 5);
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
                   pPlayer->SummonCreature(10,pPlayer->GetPositionX()+4 ,pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,20000);
               }break;
            case 2:
              {
                   pPlayer->SummonCreature(16,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+2, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,20000);
              }break;
            case 3:
               {
                   pPlayer->SummonCreature(32478,pPlayer->GetPositionX() ,pPlayer->GetPositionY(), pPlayer->GetPositionZ()+2, 0,TEMPSUMMON_TIMED_DESPAWN,20000);
               }break;
            case 4:
               {
                   pPlayer->SummonCreature(13,pPlayer->GetPositionX()+2 ,pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,20000);
               }break;
            case 5:
               {
                   pPlayer->SummonCreature(50,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+4, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,20000);
               } break;
        }
        pPlayer->CLOSE_GOSSIP_MENU();
        return true;
    }
};

void AddSC_summon_all_npc()
{
    new summon_all_npc();
}