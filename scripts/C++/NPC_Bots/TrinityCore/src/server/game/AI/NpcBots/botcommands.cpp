/*
Name: script_bot_commands
%Complete: ???
Comment: Npcbot related commands
Category: commandscripts/custom/
*/

#include "bot_ai.h"
#include "bothelper.h"
#include "Chat.h"
#include "Config.h"
#include "Group.h"
#include "Language.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"

class script_bot_commands : public CommandScript
{
public:
    script_bot_commands() : CommandScript("script_bot_commands") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand npcbotCommandTable[] =
        {
            { "add",        rbac::RBAC_PERM_COMMAND_NPCBOT_ADD,     false, &HandleNpcBotAddCommand,             "", NULL },
            { "remove",     rbac::RBAC_PERM_COMMAND_NPCBOT_REMOVE,  false, &HandleNpcBotRemoveCommand,          "", NULL },
            { "reset",      rbac::RBAC_PERM_COMMAND_NPCBOT_RESET,   false, &HandleNpcBotResetCommand,           "", NULL },
            { "command",    rbac::RBAC_PERM_COMMAND_NPCBOT_CMD,     false, &HandleNpcBotCommandCommand,         "", NULL },
            { "distance",   rbac::RBAC_PERM_COMMAND_NPCBOT_DIST,    false, &HandleNpcBotDistanceCommand,        "", NULL },
            { "info",       rbac::RBAC_PERM_COMMAND_NPCBOT_INFO,    false, &HandleNpcBotInfoCommand,            "", NULL },
            { "helper",     rbac::RBAC_PERM_COMMAND_NPCBOT_HELPER,  false, &HandleBotHelperCommand,             "", NULL },
            { "revive",     rbac::RBAC_PERM_COMMAND_NPCBOT_REVIVE,  false, &HandleNpcBotReviveCommand,          "", NULL },
            { NULL,         0,                                      false, NULL,                                "", NULL }
        };

        static ChatCommand commandTable[] =
        {
            { "npcbot",     rbac::RBAC_PERM_COMMAND_NPCBOT,         false, NULL,                  "", npcbotCommandTable },
            { NULL,         0,                                      false, NULL,                                "", NULL }
        };
        return commandTable;
    }

    //static bool HandleReloadEquipsCommand(ChatHandler* handler, const char* /*args*/)
    //{
    //    sLog->outInfo(LOG_FILTER_GENERAL, "Re-Loading Creature Equips...");
    //    sObjectMgr->LoadEquipmentTemplates();
    //    handler->SendGlobalGMSysMessage("DB table `creature_equip_template` (creature equipment) reloaded.");
    //    return true;
    //}

    static bool HandleBotHelperCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* player = handler->GetSession()->GetPlayer();
        handler->SetSentErrorMessage(true);
        if (/*player->IsInCombat() ||*/
            player->isDead() ||
            !player->IsAlive() ||
            player->IsInFlight() ||
            player->IsCharmed() ||
            bot_ai::CCed(player))
        {
            handler->SendSysMessage("You cannot do this right now");
            return false;
        }
        //close current menu
        player->PlayerTalkClass->SendCloseGossip();
        if (player->GetTrader())
            player->GetSession()->SendCancelTrade();

        BotHelper* hlpr = player->GetBotHelper();
        if (!hlpr)
        {
            hlpr = new BotHelper(player);
            player->SetBotHelper(hlpr);
        }
        return hlpr->OnGossipHello(player);
    }

    static bool HandleNpcBotInfoCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* owner = handler->GetSession()->GetPlayer();
        if (!owner->GetTarget())
        {
            handler->PSendSysMessage(".npcbot info");
            handler->PSendSysMessage("Lists NpcBots count of each class owned by selected player. You can use this on self and your party members");
            handler->SetSentErrorMessage(true);
            return false;
        }
        Player* master = owner->GetSelectedPlayer();
        if (!master || (owner->GetGroup() ? !owner->GetGroup()->IsMember(master->GetGUID()) : master->GetGUID() != owner->GetGUID()))
        {
            handler->PSendSysMessage("You should select self or one of your party members.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (!master->HaveBot())
        {
            handler->PSendSysMessage("%s has no NpcBots!", master->GetName().c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        handler->PSendSysMessage("Listing NpcBots for %s", master->GetName().c_str());
        handler->PSendSysMessage("Owned NpcBots: %u", master->GetNpcBotsCount());
        for (uint8 i = CLASS_WARRIOR; i != MAX_CLASSES; ++i)
        {
            uint8 count = 0;
            uint8 alivecount = 0;
            for (uint8 pos = 0; pos != master->GetMaxNpcBots(); ++pos)
            {
                if (Creature* cre = master->GetBotMap(pos)->_Cre())
                {
                    if (cre->GetBotClass() == i)
                    {
                        ++count;
                        if (cre->IsAlive())
                            ++alivecount;
                    }
                }
            }
            char const* bclass;
            switch (i)
            {
            case CLASS_WARRIOR:         bclass = "Warriors";        break;
            case CLASS_PALADIN:         bclass = "Paladins";        break;
            case CLASS_MAGE:            bclass = "Mages";           break;
            case CLASS_PRIEST:          bclass = "Priests";         break;
            case CLASS_WARLOCK:         bclass = "Warlocks";        break;
            case CLASS_DRUID:           bclass = "Druids";          break;
            case CLASS_DEATH_KNIGHT:    bclass = "Death Knights";    break;
            case CLASS_ROGUE:           bclass = "Rogues";          break;
            case CLASS_SHAMAN:          bclass = "Shamans";         break;
            case CLASS_HUNTER:          bclass = "Hunters";         break;
            default:                    bclass = "Unknown Class";   break;
            }
            if (count > 0)
                handler->PSendSysMessage("%s: %u (alive: %u)", bclass, count, alivecount);
        }
        return true;
    }

    static bool HandleNpcBotDistanceCommand(ChatHandler* handler, const char* args)
    {
        Player* owner = handler->GetSession()->GetPlayer();
        if (!*args)
        {
            if (owner->HaveBot())
            {
                handler->PSendSysMessage("bot follow distance is %u", owner->GetBotFollowDist());
                handler->SetSentErrorMessage(true);
                return false;
            }
            handler->PSendSysMessage(".npcbot distance");
            handler->PSendSysMessage("Sets 'distance to target' at which bots will follow you");
            handler->PSendSysMessage("if set to 0, bots will not attack anything unless you point them");
            handler->PSendSysMessage("min: 0, max: 75");
            handler->SetSentErrorMessage(true);
            return false;
        }
        char* distance = strtok((char*)args, " ");
        int8 dist = -1;

        if (distance)
            dist = (int8)atoi(distance);

        if (dist >= 0 && dist <= 75)
        {
            owner->SetBotFollowDist(dist);
            if (!owner->IsInCombat() && owner->HaveBot())
            {
                for (uint8 i = 0; i != owner->GetMaxNpcBots(); ++i)
                {
                    Creature* cre = owner->GetBotMap(i)->_Cre();
                    if (!cre || !cre->IsInWorld()) continue;
                    owner->SendBotCommandState(cre, COMMAND_FOLLOW);
                }
            }
            Group* gr = owner->GetGroup();
            if (gr && owner->GetMap()->Instanceable() && /*gr->isRaidGroup() &&*/ gr->IsLeader(owner->GetGUID()))
            {
                for (GroupReference* itr = gr->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    Player* pl = itr->GetSource();
                    if (pl && pl->IsInWorld() && pl->GetMap() == owner->GetMap())
                    {
                        pl->SetBotFollowDist(dist);
                        if (!pl->IsInCombat() && pl->HaveBot())
                        {
                            for (uint8 i = 0; i != pl->GetMaxNpcBots(); ++i)
                            {
                                Creature* cre = pl->GetBotMap(i)->_Cre();
                                if (!cre || !cre->IsInWorld()) continue;
                                pl->SendBotCommandState(cre, COMMAND_FOLLOW);
                            }
                        }
                    }
                }
            }
            handler->PSendSysMessage("bot follow distance set to %u", dist);
            return true;
        }
        handler->SendSysMessage("follow distance should be between 0 and 75");
        handler->SetSentErrorMessage(true);
        return false;
    }

    static bool HandleNpcBotCommandCommand(ChatHandler* handler, const char* args)
    {
        Player* owner = handler->GetSession()->GetPlayer();
        if (!*args)
        {
            handler->PSendSysMessage(".npcbot command <command>");
            handler->PSendSysMessage("Forces npcbots to either follow you or hold position.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        char* command = strtok((char*)args, " ");
        int8 state = -1;
        if (!strncmp(command, "s", 2) || !strncmp(command, "st", 3) || !strncmp(command, "stay", 5) || !strncmp(command, "stand", 6))
            state = COMMAND_STAY;
        else if (!strncmp(command, "f", 2) || !strncmp(command, "follow", 7) || !strncmp(command, "fol", 4) || !strncmp(command, "fo", 3))
            state = COMMAND_FOLLOW;
        if (state >= 0 && owner->HaveBot())
        {
            for (uint8 i = 0; i != owner->GetMaxNpcBots(); ++i)
            {
                Creature* cre = owner->GetBotMap(i)->_Cre();
                if (!cre || !cre->IsInWorld()) continue;
                owner->SendBotCommandState(cre, CommandStates(state));
            }
            return true;
        }
        handler->SetSentErrorMessage(true);
        return false;
    }

    static bool HandleNpcBotRemoveCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* owner = handler->GetSession()->GetPlayer();
        uint64 guid = owner->GetTarget();
        if (!guid)
        {
            handler->PSendSysMessage(".npcbot remove");
            handler->PSendSysMessage("Remove selected npcbots. Select yourself to remove all npcbots");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (guid == owner->GetGUID())
        {
            if (owner->HaveBot())
            {
                for (uint8 i = 0; i != owner->GetMaxNpcBots(); ++i)
                    owner->RemoveBot(owner->GetBotMap(i)->_Guid(), true);

                if (!owner->HaveBot())
                {
                    handler->PSendSysMessage("Npcbots successfully removed");
                    handler->SetSentErrorMessage(true);
                    return true;
                }
                handler->PSendSysMessage("Some npcbots were not removed!");
                handler->SetSentErrorMessage(true);
                return false;
            }
            handler->PSendSysMessage("Npcbots are not found!");
            handler->SetSentErrorMessage(true);
            return false;
        }

        Creature* cre = ObjectAccessor::GetCreature(*owner, guid);
        if (cre && cre->GetIAmABot())
        {
            Player* master = cre->GetBotOwner();
            if (!master || (master->GetGUID() != owner->GetGUID()))
            {
                handler->PSendSysMessage("You can only remove your own bots");
                handler->SetSentErrorMessage(true);
                return false;
            }
            uint8 pos = master->GetNpcBotSlot(guid);
            master->RemoveBot(cre->GetGUID(), true);
            if (master->GetBotMap(pos)->_Cre() == NULL)
            {
                handler->PSendSysMessage("NpcBot successfully removed");
                handler->SetSentErrorMessage(true);
                return true;
            }
            handler->PSendSysMessage("NpcBot was NOT removed for some stupid reason!");
            handler->SetSentErrorMessage(true);
            return false;
        }
        handler->PSendSysMessage("You should select self or your npcbot!");
        handler->SetSentErrorMessage(true);
        return false;
    }

    static bool HandleNpcBotResetCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* owner = handler->GetSession()->GetPlayer();
        Player* master = NULL;
        bool all = false;
        uint64 guid = owner->GetTarget();
        if (!guid)
        {
            handler->PSendSysMessage(".npcbot reset");
            handler->PSendSysMessage("Reset selected npcbot, or all npcbots if used on self");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (IS_PLAYER_GUID(guid))
        {
            master = owner;
            all = true;
        }
        else if (IS_CREATURE_GUID(guid))
        {
            if (Creature* cre = ObjectAccessor::GetCreature(*owner, guid))
                master = cre->GetBotOwner();
        }
        if (master && master->GetGUID() == owner->GetGUID())
        {
            if (!master->HaveBot())
            {
                handler->PSendSysMessage("Npcbots are not found!");
                handler->SetSentErrorMessage(true);
                return false;
            }
            for (uint8 i = 0; i != master->GetMaxNpcBots(); ++i)
            {
                if (all)
                    master->RemoveBot(master->GetBotMap(i)->_Guid());
                else if (master->GetBotMap(i)->_Guid() == guid)
                {
                    master->RemoveBot(guid);
                    break;
                }
            }
            handler->SetSentErrorMessage(true);
            return true;
        }
        handler->PSendSysMessage(".npcbot reset");
        handler->PSendSysMessage("Reset selected npcbot. Cannot be used in combat");
        handler->SetSentErrorMessage(true);
        return false;
    }
    //For debug purposes only
    static bool HandleNpcBotReviveCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* owner = handler->GetSession()->GetPlayer();
        if (owner->InBattleground())
        {
            handler->PSendSysMessage("Bot revival is disabled in pvp matches");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (!owner->IsInFlight() && owner->HaveBot())
        {
            for (uint8 i = 0; i != owner->GetMaxNpcBots(); ++i)
            {
                Creature* bot = owner->GetBotMap(i)->_Cre();
                if (bot && !bot->IsAlive())
                {
                    owner->SetBot(bot);
                    owner->CreateBot(0, 0, 0, true);
                }
            }
            handler->PSendSysMessage("NpcBots revived");
            handler->SetSentErrorMessage(true);
            return true;
        }
        handler->PSendSysMessage(".npcbot revive");
        handler->PSendSysMessage("Revive your npcbots if you are all hopelessly dead");
        handler->SetSentErrorMessage(true);
        return false;
    }

    static bool HandleNpcBotAddCommand(ChatHandler* handler, const char* args)
    {
        Player* owner = handler->GetSession()->GetPlayer();
        uint64 sel = owner->GetTarget();
        if (!*args || sel != owner->GetGUID())
        {
            handler->PSendSysMessage(".npcbot add");
            handler->PSendSysMessage("Allows to create npcbot of given class, you should select yourself");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (owner->RestrictBots())
        {
            handler->GetSession()->SendNotification("This place is restricted for NpcBots");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (owner->isDead())
        {
            owner->GetSession()->SendNotification("You're dead!");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (owner->GetGroup() && owner->GetGroup()->isRaidGroup() && owner->GetGroup()->IsFull())
        {
            handler->PSendSysMessage("Group is full, aborted");
            handler->SetSentErrorMessage(true);
            return false;
        }
        if (owner->GetNpcBotsCount() >= owner->GetMaxNpcBots())
        {
            handler->PSendSysMessage("NpcBots limit exceed");
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* bclass = strtok((char*)args, " ");
        uint8 botclass = CLASS_NONE;

        if (!strncmp(bclass, "deathknight", 12) || !strncmp(bclass, "deathk", 7) || !strncmp(bclass, "death", 6) || !strncmp(bclass, "deat", 5) ||
            !strncmp(bclass, "dea", 4) || !strncmp(bclass, "dk", 3) || !strncmp(bclass, "de", 3))
            botclass = CLASS_DEATH_KNIGHT;
        else if (!strncmp(bclass, "druid", 6) || !strncmp(bclass, "dru", 4) || !strncmp(bclass, "dr", 3))
            botclass = CLASS_DRUID;
        else if (!strncmp(bclass, "hunter", 7) || !strncmp(bclass, "hunt", 5) || !strncmp(bclass, "hun", 4) || !strncmp(bclass, "hu", 3))
            botclass = CLASS_HUNTER;
        else if (!strncmp(bclass, "mage", 5) || !strncmp(bclass, "ma", 3))
            botclass = CLASS_MAGE;
        else if (!strncmp(bclass, "paladin", 8) || !strncmp(bclass, "pal", 4) || !strncmp(bclass, "pa", 3))
            botclass = CLASS_PALADIN;
        else if (!strncmp(bclass, "priest", 7) || !strncmp(bclass, "pri", 4) || !strncmp(bclass, "pr", 3))
            botclass = CLASS_PRIEST;
        else if (!strncmp(bclass, "rogue", 6) || !strncmp(bclass, "rog", 4) || !strncmp(bclass, "ro", 3))
            botclass = CLASS_ROGUE;
        else if (!strncmp(bclass, "shaman", 7) || !strncmp(bclass, "sham", 5) || !strncmp(bclass, "sha", 4) || !strncmp(bclass, "sh", 3))
            botclass = CLASS_SHAMAN;
        else if (!strncmp(bclass, "warlock", 8) || !strncmp(bclass, "warl", 5) || !strncmp(bclass, "lock", 5))
            botclass = CLASS_WARLOCK;
        else if (!strncmp(bclass, "warrior", 8) || !strncmp(bclass, "warr", 5))
            botclass = CLASS_WARRIOR;

        if (botclass == CLASS_NONE)
        {
            handler->PSendSysMessage("Wrong bot class");
            handler->SetSentErrorMessage(true);
            return false;
        }
        else if (botclass == CLASS_DEATH_KNIGHT && owner->getLevel() < 55)
        {
            handler->PSendSysMessage("Death Knights will not join you until you reach level 55...");
            handler->SetSentErrorMessage(true);
            return false;
        }

        uint8 bots = owner->GetNpcBotsCount();
        owner->CreateNPCBot(botclass);
        owner->RefreshBot(0);
        if (owner->GetNpcBotsCount() > bots)
        {
            if (owner->IsInCombat())
                handler->PSendSysMessage("NpcBot successfully created (%s). Will appear out of combat", owner->GetName().c_str());
            else
                handler->PSendSysMessage("NpcBot successfully created (%s).", owner->GetName().c_str());
            handler->SetSentErrorMessage(true);
            return true;
        }
        handler->PSendSysMessage("NpcBot is NOT created for some reason!");
        handler->SetSentErrorMessage(true);
        return false;
    }
};

void AddSC_script_bot_commands()
{
    new script_bot_commands();
}
