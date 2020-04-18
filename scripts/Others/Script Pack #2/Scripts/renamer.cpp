/* Custom Shadowhack renamer */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
#include "BattlegroundMgr.h"
#include "Battleground.h"
#include "Log.h"
#include "Guild.h"
//#include "ArenaTeam.h"

class renamer : public CreatureScript
{
    public: 
        renamer() : CreatureScript("renamer") { }
        //std::vector<StringList*>::iterator string_iter;
        //uint32 HONOR_COST;
        //std::string name[2];

    bool OnGossipHello(Player* player, Creature* pCreature)
    {   
        if (ArenaTeam *at = sObjectMgr->GetArenaTeamById(player->GetArenaTeamId(0)))
            if (at->GetCaptain() == player->GetGUID())
                player->ADD_GOSSIP_ITEM_EXTENDED(0, "Rename 2x2", GOSSIP_SENDER_MAIN, 1002, "", 0, true);

        if (ArenaTeam *at = sObjectMgr->GetArenaTeamById(player->GetArenaTeamId(1)))
            if (at->GetCaptain() == player->GetGUID())
                player->ADD_GOSSIP_ITEM_EXTENDED(0, "Rename 3x3", GOSSIP_SENDER_MAIN, 1003, "", 0, true);

        if (ArenaTeam *at = sObjectMgr->GetArenaTeamById(player->GetArenaTeamId(2)))
            if (at->GetCaptain() == player->GetGUID())
                player->ADD_GOSSIP_ITEM_EXTENDED(0, "Rename 5x5", GOSSIP_SENDER_MAIN, 1004, "", 0, true);

        if (Guild* guild = sObjectMgr->GetGuildById(player->GetGuildId()))
            if (guild->GetLeaderGUID() == player->GetGUID())
                player->ADD_GOSSIP_ITEM_EXTENDED(0, "Rename гильдию", GOSSIP_SENDER_MAIN, 1005, "", 0, true);

        player->ADD_GOSSIP_ITEM_EXTENDED( 4, "Bye!", GOSSIP_SENDER_MAIN, 1224, "", 0, true);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
        return true;
    }
                
    bool OnGossipSelect(Player* player, Creature* pCreature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->GetGossipMenu().ClearMenu();
        if (player->InBattlegroundQueue())
            return false;
        switch (action)
        {
            case 1224:
                player->CLOSE_GOSSIP_MENU();
                break;
        }
        return true;
    }
    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            switch(action)
            {
                case 1002:
                {
                    if (ArenaTeam *at = sObjectMgr->GetArenaTeamById(player->GetArenaTeamId(0)))
                        if (at->GetCaptain() == player->GetGUID())
                        {
                            at->SetName(code);
                            at->BroadcastEvent(ERR_ARENA_TEAM_LEADER_CHANGED_SSS, 0, 3, player->GetName(), player->GetName(), at->GetName());
                        }
                    break;
                }
                case 1003:
                {
                    if (ArenaTeam *at = sObjectMgr->GetArenaTeamById(player->GetArenaTeamId(1)))
                        if (at->GetCaptain() == player->GetGUID())
                        {
                            at->SetName(code);
                            at->BroadcastEvent(ERR_ARENA_TEAM_LEADER_CHANGED_SSS, 0, 3, player->GetName(), player->GetName(), at->GetName());
                        }
                }
                case 1004:
                {
                    if (ArenaTeam *at = sObjectMgr->GetArenaTeamById(player->GetArenaTeamId(2)))
                        if (at->GetCaptain() == player->GetGUID())
                        {
                            at->SetName(code);
                            at->BroadcastEvent(ERR_ARENA_TEAM_LEADER_CHANGED_SSS, 0, 3, player->GetName(), player->GetName(), at->GetName());
                        }
                }
                case 1005:
                {
                    if (Guild* guild = sObjectMgr->GetGuildById(player->GetGuildId()))
                        if (guild->GetLeaderGUID() == player->GetGUID())
                        {
                            guild->SetName(code);
                            guild->HandleQuery(player->GetSession());
                        }
                }
            }
        }
        return true;
    }

    bool GossipSelect_renamer(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        // Main menu
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};

void AddSC_renamer()
{
    new renamer;
}
