#include "ScriptPCH.h"
#include "Chat.h"
#include "Player.h"

class Queue_NPC : public CreatureScript
{
public:
    Queue_NPC() : CreatureScript("Queue_NPC") { }
    
    bool OnGossipHello(Player * player, Creature * creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Join Rated Battleground Queue.", GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Leave Rated Battleground Queue.", GOSSIP_SENDER_MAIN, 2);
        switch (QueryResult Get_If_In_Queue = CharacterDatabase.PQuery("SELECT in_queue FROM rated_battlegrounds WHERE guid = '%u'", player->GetGUID()))
        {
        case 0:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Currently: |cffff0000Not In Queue|r.", GOSSIP_SENDER_MAIN, 3);
            break;
        case 1:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Currently: |cff00ff00In Queue|r.", GOSSIP_SENDER_MAIN, 3);
            break;
        }
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "What's this?", GOSSIP_SENDER_MAIN, 4);
        player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
        return true;
    }
    
    bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        
        switch(uiAction)
        {
        case 1: // Join Rated Battleground Queue.
            CharacterDatabase.PExecute("DELETE FROM characters.rated_battlegrounds WHERE guid = %u", player->GetGUID());
            CharacterDatabase.PExecute("INSERT INTO characters.rated_battlegrounds (guid, in_queue) VALUES ('%u', 1)", player->GetGUID());
            player->PlayerTalkClass->SendCloseGossip();
            break;
        case 2: // Leave Rated Battleground Queue.
			CharacterDatabase.PExecute("DELETE FROM characters.rated_battlegrounds WHERE guid = %u", player->GetGUID());
            player->PlayerTalkClass->SendCloseGossip();
            break;
        case 3: // Currently: In Queue/Not In Queue.
			player->PlayerTalkClass->SendCloseGossip();
            break;
        case 4: // What's this?
			creature->MonsterWhisper("Still a work in progress obviously.", player->GetGUID());
			player->PlayerTalkClass->SendCloseGossip();
            break;
        case 5:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Join Rated Battleground Queue.", GOSSIP_SENDER_MAIN, 1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Leave Rated Battleground Queue.", GOSSIP_SENDER_MAIN, 2);
            switch (QueryResult Get_If_In_Queue = CharacterDatabase.PQuery("SELECT in_queue FROM rated_battlegrounds WHERE guid = '%u'", player->GetGUID()))
        {
        case 0:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Currently: |cffff0000Not In Queue|r.", GOSSIP_SENDER_MAIN, 3);
            break;
        case 1:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Currently: |cff00ff00In Queue|r.", GOSSIP_SENDER_MAIN, 3);
            break;
        }
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "What's this?", GOSSIP_SENDER_MAIN, 4);
            player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
            break;
        }
        return true;
    }
};

void AddSC_Queue_NPC()
{
    new Queue_NPC;
}
