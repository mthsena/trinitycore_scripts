/*
**
** http://www.mthsena.info
**
*/

#define DEFAULT_MESSAGE 907

#define PRIZE_IN_GOLD 10000 // Prêmio em gold a cada reset, 10k.

class NPC_Reset : public CreatureScript
{
public:
    NPC_Reset() : CreatureScript("NPC_Reset") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "Reset!", GOSSIP_SENDER_MAIN, 1, "Are you sure?", 0, false);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "About", GOSSIP_SENDER_MAIN, 2);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Exit", GOSSIP_SENDER_MAIN, 3);
        player->SEND_GOSSIP_MENU(DEFAULT_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
        case 1:
            if (player->getLevel() < DEFAULT_MAX_LEVEL)
            {
                player->GetSession()->SendAreaTriggerMessage("You not reached level %u.", SERVER_MAX_LEVEL);
                return false;
            }
            uint32 startLevel = player->getClass() == CLASS_DEATH_KNIGHT ? sWorld->getIntConfig(CONFIG_START_HEROIC_PLAYER_LEVEL) : sWorld->getIntConfig(CONFIG_START_PLAYER_LEVEL);
            player->SetLevel(startLevel);
            player->GetSession()->SendAreaTriggerMessage("You has been reset successfully!");
            player->ModifyMoney(PRIZE_IN_GOLD * GOLD);
            player->CLOSE_GOSSIP_MENU();
            break;
        case 2:
            ChatHandler(player->GetSession()).PSendSysMessage("# You need be level %u to make a reset.", SERVER_MAX_LEVEL);
            ChatHandler(player->GetSession()).PSendSysMessage("# Earn %u gold every reset done.", PRIZE_IN_GOLD);
            OnGossipHello(player, creature);
            break;
        case 3:
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        return true;
    }
};

void AddSC_NPC_Reset()
{
    new NPC_Reset();
}