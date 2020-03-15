#include "ScriptMgr.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "Config.h"
#include "Chat.h"

#define DEFAULT_MESSAGE 907

void SetFlag(Player* player, Creature* creature, AtLoginFlags flag)
{
    uint32 token = sConfigMgr->GetIntDefault("NS.Token", 0);
    uint32 count = sConfigMgr->GetIntDefault("NS.Count", 0);

    if (!player->HasItemCount(token, count, false))
    {
        ChatHandler(player->GetSession()).PSendSysMessage("Failure! You not have the token.");
        return;
    }

    ChatHandler(player->GetSession()).PSendSysMessage("Success! Logout to take effect.");
    player->DestroyItemCount(token, count, true, false);
    player->SetAtLoginFlag(flag);
}

class NPC_Stuff : public CreatureScript
{
public:
    NPC_Stuff() : CreatureScript("NPC_Stuff") { }

    bool OnGossipHello(Player *player, Creature *creature)
    {
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Change Faction", GOSSIP_SENDER_MAIN, 1, "Tem certeza ?", 0, false);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Change Race", GOSSIP_SENDER_MAIN, 2, "Tem certeza ?", 0, false);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Customize", GOSSIP_SENDER_MAIN, 3, "Tem certeza ?", 0, false);
        SendGossipMenuFor(player, DEFAULT_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (uiAction)
        {
        case 1:// Change Faction
            SetFlag(player, creature, AT_LOGIN_CHANGE_FACTION);
            CloseGossipMenuFor(player);
            break;

        case 2:// Change Race
            SetFlag(player, creature, AT_LOGIN_CHANGE_RACE);
            CloseGossipMenuFor(player);
            break;

        case 3:// Customize
            SetFlag(player, creature, AT_LOGIN_CUSTOMIZE);
            CloseGossipMenuFor(player);
            break;
        }
        return true;
    }
};

void AddSC_NPC_Stuff()
{
    new NPC_Stuff();
}