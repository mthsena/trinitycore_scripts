#include "ScriptPCH.h"

class Exchanger_NPC : public CreatureScript
{
public:
    Exchanger_NPC() : CreatureScript("Exchanger_NPC") { }

    bool OnGossipHello(Player *player, Creature *_creature)
	{
		if (player->isInCombat())
        {
            player->CLOSE_GOSSIP_MENU();
            _creature->MonsterWhisper("You are in combat!", player->GetGUID());
            return true;
        }
        else
    {
            player->ADD_GOSSIP_ITEM( 7, "100 BoJ --> 10000 Honor Pts."                     , GOSSIP_SENDER_MAIN, 1); 
            player->ADD_GOSSIP_ITEM( 5, "100 BoJ --> 100 Arena Pts."                     , GOSSIP_SENDER_MAIN, 2); 
            player->ADD_GOSSIP_ITEM( 8, "100 Arena Pts. --> 10000 Honor Pts."			, GOSSIP_SENDER_MAIN, 3);
			player->ADD_GOSSIP_ITEM( 8, "60000 Honor Pts. -> 1 S8 BG Token."			, GOSSIP_SENDER_MAIN, 4);
        }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());         
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            player->PlayerTalkClass->ClearMenus();
            switch(uiAction)
            {          
               
               

            case 1: 
                if (player->HasItemCount( 29434, 100, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(29434, 100, true, false);
                    player->ModifyHonorPoints(+10000);
                    _creature->MonsterWhisper("You exchanged succesfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("Don't even try it!", player->GetGUID());
                    return false;
				}
				break;

            case 2: 
                if (player->HasItemCount( 29434, 100, false ))
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->DestroyItemCount(29434, 100, true, false);
                    player->ModifyArenaPoints(+100);
                    _creature->MonsterWhisper("You exchanged succesfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("Don't even try it!", player->GetGUID());
                    return false;
                }
                break;
            
			case 3: 
                if (player->GetArenaPoints () >= 100)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->ModifyArenaPoints(-100);
                    player->ModifyHonorPoints(+10000);
                    _creature->MonsterWhisper("You exchanged succesfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("Don't even try it!", player->GetGUID());
                    return false;
                }
                break;
			case 4: 
                if (player->GetHonorPoints () >= 60000)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->AddItem(37829,1);
                    player->ModifyHonorPoints(-60000);
                    _creature->MonsterWhisper("You exchanged succesfully!", player->GetGUID());
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("Don't even try it!", player->GetGUID());
                    return false;
                }
                break;

            } 
        } 
        return true;
    } 
};

void AddSC_Exchanger_NPC()
{
    new Exchanger_NPC();
}