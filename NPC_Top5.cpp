#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "Creature.h"
#include "Chat.h"

#define DEFAULT_MESSAGE 907

class NPC_Top5 : public CreatureScript
{
public:
    NPC_Top5() : CreatureScript("NPC_Top5") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Top 5 Kills", GOSSIP_SENDER_MAIN, 1);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Top 5 Arena", GOSSIP_SENDER_MAIN, 2);
        SendGossipMenuFor(player, DEFAULT_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        QueryResult topkill = CharacterDatabase.Query("SELECT name, totalKills FROM characters ORDER BY totalKills DESC LIMIT 5");
        QueryResult toparena = CharacterDatabase.Query("SELECT name, rating FROM arena_team ORDER BY rating DESC LIMIT 5");
        Field * fields = NULL;

        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
        case 1:// Top 5 Kills
            if (!topkill)
                return false;

            ChatHandler(player->GetSession()).PSendSysMessage("- Top 5 Kills -");
            do
            {
                fields = topkill->Fetch();
                std::string name = fields[0].GetString();
                uint32 kills = fields[1].GetUInt32();

                ChatHandler(player->GetSession()).PSendSysMessage("Name: |CFFFFFFFF%s|r, Kills: |cFFFFFFFF%u|r \n", name.c_str(), kills);
            } while (topkill->NextRow());

            CloseGossipMenuFor(player);
            break;

        case 2:// Top 5 Arena
            if (!toparena)
                return false;
            ChatHandler(player->GetSession()).PSendSysMessage("- Top 5 Arena -");
            do
            {
                fields = toparena->Fetch();
                std::string team = fields[0].GetString();
                uint32 rating = fields[1].GetUInt32();

                ChatHandler(player->GetSession()).PSendSysMessage("Team: |CFFFFFFFF%s|r, Rating: |CFFFFFFFF%u|r \n", team.c_str(), rating);
            } while (toparena->NextRow());

            CloseGossipMenuFor(player);
            break;

        case 4:// Exit
            CloseGossipMenuFor(player);
            break;
        }

        return true;
    }
};

void AddSC_NPC_Top5()
{
    new NPC_Top5();
}
