#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "ScriptedGossip.h"
#include "Config.h"
#include "Chat.h"

using namespace std;

#define DEFAULT_MESSAGE 907

struct TitleData
{
    uint32 Menu;
    uint32 Submenu;
    uint32 Icon;
    uint32 Id;
    string Name;
};

TitleData tData[] =
{
    { 1, 0, GOSSIP_ICON_BATTLE, 78, "The Explorer" },
    { 1, 0, GOSSIP_ICON_BATTLE, 84, "Chef" },
    { 1, 0, GOSSIP_ICON_BATTLE, 83, "Salty" },
    { 1, 0, GOSSIP_ICON_BATTLE, 125, "Loremaster" },
    { 1, 0, GOSSIP_ICON_BATTLE, 81, "The Seeker" },
    { 1, 0, GOSSIP_ICON_BATTLE, 172, "the Patient" },
    { 1, 0, GOSSIP_ICON_BATTLE, 74, "Elder" },
    { 1, 0, GOSSIP_ICON_BATTLE, 135, "The Love Fool" },
    { 1, 0, GOSSIP_ICON_BATTLE, 155, "The Noble" },
    { 1, 0, GOSSIP_ICON_BATTLE, 133, "Brewmaster" },
    { 1, 0, GOSSIP_ICON_BATTLE, 124, "The Hallowed" },
    { 1, 0, GOSSIP_ICON_BATTLE, 168, "Pilgrim" },
    { 1, 0, GOSSIP_ICON_BATTLE, 134, "Merrymaker" },
    { 1, 0, GOSSIP_ICON_BATTLE, 143, "Jenkins" },
    { 1, 2, GOSSIP_ICON_TALK, 0, "Next.." },

    { 2, 0, GOSSIP_ICON_BATTLE, 46, "Scarab Lord" },
    { 2, 0, GOSSIP_ICON_BATTLE, 129, "Champion of the Frozen Wastes" },
    { 2, 0, GOSSIP_ICON_BATTLE, 142, "The Undying" },
    { 2, 0, GOSSIP_ICON_BATTLE, 141, "The Immortal" },
    { 2, 0, GOSSIP_ICON_BATTLE, 140, "of the Nightfall" },
    { 2, 0, GOSSIP_ICON_BATTLE, 121, "Twilight Vanquisher" },
    { 2, 0, GOSSIP_ICON_BATTLE, 164, "Starcaller" },
    { 2, 0, GOSSIP_ICON_BATTLE, 165, "The Astral Walker" },
    { 2, 0, GOSSIP_ICON_BATTLE, 166, "Herald of the Titans" },
    { 2, 0, GOSSIP_ICON_BATTLE, 161, "Champion of Ulduar" },
    { 2, 0, GOSSIP_ICON_BATTLE, 160, "Conqueror of Ulduar" },
    { 2, 0, GOSSIP_ICON_BATTLE, 174, "Bane of the Fallen King" },
    { 2, 0, GOSSIP_ICON_BATTLE, 173, "The Light of Dawn" },
    { 2, 3, GOSSIP_ICON_TALK, 0, "Next.." },
    { 2, 1, GOSSIP_ICON_TALK, 0, "..Back" },

    { 3, 0, GOSSIP_ICON_BATTLE, 175, "The Kingslayer" },
    { 3, 0, GOSSIP_ICON_BATTLE, 63, "of the Shattered Sun" },
    { 3, 0, GOSSIP_ICON_BATTLE, 130, "Ambassador" },
    { 3, 0, GOSSIP_ICON_BATTLE, 144, "Bloodsail Admiral" },
    { 3, 0, GOSSIP_ICON_BATTLE, 79, "The Diplomat" },
    { 3, 0, GOSSIP_ICON_BATTLE, 132, "Guardian of Cenarius" },
    { 3, 0, GOSSIP_ICON_BATTLE, 131, "The Argent Champion" },
    { 3, 0, GOSSIP_ICON_BATTLE, 176, "of the Ashen Verdict" },
    { 3, 0, GOSSIP_ICON_BATTLE, 77, "The Exalted" },
    { 3, 0, GOSSIP_ICON_BATTLE, 145, "The Insane" },
    { 3, 0, GOSSIP_ICON_BATTLE, 72, "Battlemaster" },
    { 3, 0, GOSSIP_ICON_BATTLE, 82, "Arena Master" },
    { 3, 0, GOSSIP_ICON_BATTLE, 43, "Duelist" },
    { 3, 4, GOSSIP_ICON_TALK, 0, "Next.." },
    { 3, 2, GOSSIP_ICON_TALK, 0, "..Back" },

    { 4, 0, GOSSIP_ICON_BATTLE, 44, "Rival" },
    { 4, 0, GOSSIP_ICON_BATTLE, 45, "Challenger" },
    { 4, 0, GOSSIP_ICON_BATTLE, 163, "Vanquisher" },
    { 4, 0, GOSSIP_ICON_BATTLE, 156, "Crusader" },
    { 4, 0, GOSSIP_ICON_BATTLE, 93, "Archmage" },
    { 4, 0, GOSSIP_ICON_BATTLE, 53, "Champion of the Naaru" },
    { 4, 0, GOSSIP_ICON_BATTLE, 64, "Hand of A'dal" },
    { 4, 0, GOSSIP_ICON_BATTLE, 128, "Flawless Victor" },
    { 4, 3, GOSSIP_ICON_TALK, 0, "..Back" },
};

class NPC_Title : public CreatureScript
{
public:
    NPC_Title() : CreatureScript("NPC_Title") { }

    void GetMenu(Player* player, Creature* creature, uint32 menuId)
    {
        for (uint8 i = 0; i < (sizeof(tData) / sizeof(*tData)); i++)
        {
            if (tData[i].Menu == menuId)
                AddGossipItemFor(player, tData[i].Icon, tData[i].Name, GOSSIP_SENDER_MAIN, i);
        }

        SendGossipMenuFor(player, DEFAULT_MESSAGE, creature->GetGUID());
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        GetMenu(player, creature, 1);
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        uint32 token = sConfigMgr->GetIntDefault("NT.Token", 0);
        uint32 count = sConfigMgr->GetIntDefault("NT.Count", 0);

        uint8 menuData = tData[action].Submenu;

        if (menuData == 0)
        {
            if (!player->HasItemCount(token, count, false))
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Failure! You not have the token.");
                CloseGossipMenuFor(player);
                return false;
            }

            player->SetTitle(sCharTitlesStore.LookupEntry(tData[action].Id));
            player->DestroyItemCount(token, count, true, false);
            ChatHandler(player->GetSession()).PSendSysMessage("Success! Title added.");
            menuData = tData[action].Menu;
        }

        GetMenu(player, creature, menuData);
        return true;
    }
};

void AddSC_NPC_Title()
{
    new NPC_Title;
}