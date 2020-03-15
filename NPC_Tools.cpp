#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "Creature.h"
#include "SpellHistory.h"
#include "Chat.h"

#define DEFAULT_MESSAGE 907

class NPC_Tools : public CreatureScript
{
public:
    NPC_Tools() : CreatureScript("NPC_Tools") { }

    bool OnGossipHello(Player *player, Creature *creature)
    {
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Restore HP and MP", GOSSIP_SENDER_MAIN, 1);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Reset Instances", GOSSIP_SENDER_MAIN, 2);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Reset Cooldowns", GOSSIP_SENDER_MAIN, 3);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Reset Combat", GOSSIP_SENDER_MAIN, 4);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Remove Sickness", GOSSIP_SENDER_MAIN, 5);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Repair Items", GOSSIP_SENDER_MAIN, 6);
        SendGossipMenuFor(player, DEFAULT_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
        case 1: // Restore HP and MP
            if (player->IsInCombat())
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Failure! You are in combat.");
                CloseGossipMenuFor(player);
                return false;
            }

            if (player->getPowerType() == POWER_MANA)
                player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));

            player->SetHealth(player->GetMaxHealth());
            ChatHandler(player->GetSession()).PSendSysMessage("Success! HP and MP restored.");
            CloseGossipMenuFor(player);
            break;

        case 2: // Reset Instances
            for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
            {
                Player::BoundInstancesMap &binds = player->GetBoundInstances(Difficulty(i));
                for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end();)
                    player->UnbindInstance(itr, Difficulty(i));
            }

            ChatHandler(player->GetSession()).PSendSysMessage("Success! Instances reseted.");
            CloseGossipMenuFor(player);
            break;

        case 3: // Reset Cooldowns
            if (player->IsInCombat())
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Failure! You are in combat.");
                CloseGossipMenuFor(player);
                return false;
            }

            player->GetSpellHistory()->ResetAllCooldowns();
            ChatHandler(player->GetSession()).PSendSysMessage("Success! Cooldowns reseted.");
            CloseGossipMenuFor(player);
            break;

        case 4: // Reset Combat
            player->CombatStop();
            ChatHandler(player->GetSession()).PSendSysMessage("Success! Combat reseted.");
            CloseGossipMenuFor(player);
            break;

        case 5: // Remove Sickness
            if (player->HasAura(15007))
                player->RemoveAura(15007);

            ChatHandler(player->GetSession()).PSendSysMessage("Success! Sickness removed.");
            CloseGossipMenuFor(player);
            break;

        case 6: // Repair Items
            player->DurabilityRepairAll(false, 0, false);
            ChatHandler(player->GetSession()).PSendSysMessage("Success! Items repaired.");
            CloseGossipMenuFor(player);
            break;
        }
        return true;
    }
};

void AddSC_NPC_Tools()
{
    new NPC_Tools();
}